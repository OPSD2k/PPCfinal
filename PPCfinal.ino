//Made by Olivier Donker in January 2022. Inspired by https://microcontrollerslab.com/mq3-alcohol-sensor-arduino-tutorial/ .
//Keep sensor calibration in mind!
#include <Servo.h>

int ethanolSensorPin = A0;
int ethanolSensorValue;
int ethanolUpperLimit = 100; //Some number, will depend on sensor

int servoPin = 9;
Servo lockServo;

int padTestPin = 2; //Testing keypad on pin 2
int padTestPinValue; //To track current pin value
int padTestPinValueAfterBounce; //Track pin value after bouncing has happened
int padButton1State; //Track state of first button

int rowPins[] = {2, 3, 4, 5};
int columnPins[] = {6, 7, 8, 9};


void setup() {
  Serial.begin(9600); //Open connection
  //For testing
  ///////////////////////////////////////////////////////////////
  //Keypad test using internal pullup
  pinMode(padTestPin, INPUT_PULLUP);
  padButton1State = digitalRead(padTestPin);    //Read the pin that tests the button. This is the initial state
  //////////////////////////////////////////////////////////////

  //Choose Arduino pin 2, 3, 4 and 5 for the rows, 6, 7, 8 and 9 for the columns.
  //Step 1 of algorithm below.
  for (int i = 0; i < 4; i++) { //Cycle through array of length 4
    pinMode(rowPins[i], OUTPUT);
    pinMode(columnPins[i], INPUT_PULLUP);
  }

}

void loop() {
  ethanolSensorValue = analogRead(ethanolSensorPin);  //Read the value
  //Serial.print('E');  //Header E for ethanol
  //Serial.println(ethanolSensorValue);
  if (ethanolSensorValue > 100) { //Only send if there is too much ethanol sensed. Processing then handles what happens when it receives 'Boozed'
    //Serial.println('Boozed')
  }
  //For testing
  //////////////////////////////////////////////////////////////////////////////

  //  padTestPinValue = digitalRead(padTestPin);    //Store current pin value
  //  delay(3);
  //  padTestPinValueAfterBounce = digitalRead(padTestPin);   //Do it again after short delay. In this delay the contact bounces.
  //
  //  if (padTestPinValue != padTestPinValueAfterBounce) { //Only do something after these two have become equal (when debounce is over)
  //    //padButton1State = padTestPinValue;    //Change button state to what it is now
  //    Serial.print('K');
  //    Serial.print(1);
  //    delay(1000);      //Send a "K1" every time button is pressed
  //
  //  }
  //
  //  Serial.println(padTestPinValue);
  /////////////////////////////////////////////////////////////////////////////

  //Algorithm to determine keypresses in the keypad matrix:
  //1. Set all pins connected to the rows to HIGH
  //2. Set the first row to LOW
  //3. Listen to every column, one after another. If the respective key of a column is pressed, we will find LOW on that column, instead of HIGH.
  //4. Set the first row to HIGH and set the next row to LOW.
  //5. Continue this until the fourth row has been cycled from HIGH to LOW
  //6. Then loop this whole procedure.

  for(int i = 0; i < 3; i++){   //Big for loop to run through rows
    digitalWrite(rowPins[i], LOW)   //Step 2 of algorithm
    for(int j = 0; j < 3; j++){    //Step 3 of algorithm
    if(digitalRead(columnPins[j]) = LOW); //If button pressed there
    Serial.print()
    
    }
    
  }





  //if(doorUnlock){
  //lockServo.write(180); 180 for open
}
