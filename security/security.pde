
import processing.serial.*; // use serial port libraries
Serial myPort;                // make a fresh serial port
boolean access;
boolean deny;
Wrong Alarm;
Access Open;
String validate = "Access";
String state;
void setup()
{
  size(700, 700);
  Alarm= new Wrong (width, height);
  Open = new Access (width, height);
  println("Available serial ports:");
  for (int i = 0; i<Serial.list().length; i++) 
  { 
    print("[" + i + "] ");
    println(Serial.list()[i]);
  } 
  myPort = new Serial(this, Serial.list()[0], 9600); // open port 0 in the list at 9600 Baud
  myPort.bufferUntil(10);
}

void draw()
{
  
  if(state.equals("Access") == true ){
  Open.display();
  }
  if(state.equals("Denied") == true){
  Alarm.popUp();
  Alarm.securityLog();
  }
 
}

void serialEvent(Serial p) {
  validate = p.readStringUntil(10);
  println(validate);
  state=trim(validate);
  }
