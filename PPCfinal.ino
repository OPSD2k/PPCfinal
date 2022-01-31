//Made by Olivier Donker in January 2022. Inspired by https://microcontrollerslab.com/mq3-alcohol-sensor-arduino-tutorial/ .
//Keep sensor calibration in mind!
#include <Servo.h>

int ethanolSensorPin = A0;
int ethanolSensorValue;
int ethanolUpperLimit = 100; //Some number, will depend on sensor
boolean userBoozed = false;

int servoPin = 9;
Servo lockServo;

int keyPadDebounceDelay = 100;

int rowPins[] = {2, 3, 4, 5};
int columnPins[] = {6, 7, 8, 9};
int codeEnteredArray[5];
int currentCodeNumberToEnter = 0;
int keyCode[] = {1, 2, 3, 4, 5};

int padNumberMatrix[4][4] = {
  {0, 1, 2, 3},
  {4, 5, 6, 7},
  {8, 9, 0, 0},
  {0, 0, 0, 0},
};

boolean codesMatch = true;
boolean letUserInFromCode = false;



void setup() {
  Serial.begin(9600); //Open connection

  //Choose Arduino pin 2, 3, 4 and 5 for the rows, 6, 7, 8 and 9 for the columns.
  //Step 1 of algorithm below.
  for (int i = 0; i < 4; i++) { //Cycle through array of length 4
    pinMode(rowPins[i], OUTPUT);
    pinMode(columnPins[i], INPUT_PULLUP);
  }

}

void loop() {
  ethanolSensorValue = analogRead(ethanolSensorPin);  //Read the value
  Serial.print('E');  //Header E for ethanol
  Serial.println(ethanolSensorValue);
  if (ethanolSensorValue > 1200) { //Only send if there is too much ethanol sensed. value of 1000 seem to be normal for air.
    userBoozed = true;
  }
  else {
    userBoozed = false;
  }
  Serial.print("Boozed :");
  Serial.println(userBoozed);

  //Algorithm to determine keypresses in the keypad matrix:
  //1. Set all pins connected to the rows to HIGH
  //2. Set the first row to LOW
  //3. Listen to every column, one after another. If the respective key of a column is pressed, we will find LOW on that column, instead of HIGH.
  //4. Set the first row to HIGH and set the next row to LOW.
  //5. Continue this until the fourth row has been cycled from HIGH to LOW
  //6. Then loop this whole procedure.

  if (currentCodeNumberToEnter < 5) { //Only check for keypad inputs if we want another number in the entered code
    for (int i = 0; i < 4; i++) { //Big for loop to run through rows, works as step 5
      //Serial.print(i);
      digitalWrite(rowPins[i], LOW);   //Step 2 of algorithm
      for (int j = 0; j < 4; j++) {  //Step 3 of algorithm
        if (digitalRead(columnPins[j]) == LOW) { //If button pressed there
          Serial.println(padNumberMatrix[i][j]);              //Element (i, j) in pad numbers matrix. Works for individual pins, just not the right number yet
          codeEnteredArray[currentCodeNumberToEnter] = padNumberMatrix[i][j];
          currentCodeNumberToEnter += 1;  //Go to the next number to enter
          delay(keyPadDebounceDelay);
        }               //FUCKING WORKS RWOJRWAPENFPAWF
      }
      digitalWrite(rowPins[i], HIGH);    //step 4 of algorithm
      delay(keyPadDebounceDelay);
    }
  }

  else {
    currentCodeNumberToEnter = 0; //reset input
    for (int i = 0; i < 5; i++) {
      if (keyCode[i] != codeEnteredArray[i]) {
        codesMatch = false;
      }
    }
    if (!codesMatch) {
      Serial.println("Intruder alert");
      letUserInFromCode = false; //don't allow user in
      for (int i = 0; i < 5; i++) { //clear the code entered array
        codeEnteredArray[i] = 0;
      }
      codesMatch = true; //Reset codesMatch checker
    }
    else {
      //codesMatch = true;  //Reset codesMatch to true if they do
      Serial.println("Acces granted");
      letUserInFromCode = true; //do allow user in
      for (int i = 0; i < 5; i++) { //clear the code entered array
        codeEnteredArray[i] = 0;
      }
    }
  }
  Serial.print("User allowed in: ");
  Serial.println(letUserInFromCode);


  //doorUnlock true if !Boozed and letUserInFromCode
  

  //if(doorUnlock){
  //lockServo.write(180); 180 for open
}
