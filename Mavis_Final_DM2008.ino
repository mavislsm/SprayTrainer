#include <BitVoicer11.h>
#include <Servo.h>
Servo myServo;
BitVoicerSerial bvSerial = BitVoicerSerial();

//const int switchPin = 2; switch removed, was used for testing servo motor
const int motorPin = 9;
//int switchState = 0; switch removed, was used for testing servo motor
int pos = 0;
boolean sampleTest = false;
byte dataType = 0;

void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  //pinMode(switchPin, INPUT); switch removed, was used for testing servo motor
  myServo.attach(9);
  myServo.write(0);
  
}

void loop() {
  
  if (sampleTest == true){
      bvSerial.processAudio(46);
  }
  if (bvSerial.engineRunning){
      bvSerial.processAudio(46);
  } 
}

void serialEvent()
{
  dataType = bvSerial.getData();
    if (dataType == BV_STR){
    sprayWater();
  }
}

void sprayWater(){
  if (bvSerial.strData == "spray"){
    myServo.write(130);
    delay(500);
    myServo.write(0);
    delay(20);
  }
 
  else{
    bvSerial.startStopListening();
    bvSerial.sendToBV("ERROR:" + bvSerial.strData);
    bvSerial.startStopListening();
  } 
}
  



