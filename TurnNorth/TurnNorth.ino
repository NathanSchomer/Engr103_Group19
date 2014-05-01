// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
#include <Wire.h>

#define STEER_SCALING 1
#define STEER_CENTERPOINT 90
#define STEER_CENTER_ADJUST 5 //  +/-5

Servo servo, ESC;
int HMC6352Address = 0x42;
int i, headingValue, slaveAddress;
double currHeading;
byte headingData[2];
 
void setup() { 
  servo.attach(10);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  
  slaveAddress = HMC6352Address >> 1;
  Wire.begin();
  delay(1000); //for ESC initialization
} 

void loop() {
  double steer[2] = {0, getHeading()};
  steerUpdate(steer);
  Serial.println(getHeading());
} 

double getHeading(){
    Wire.beginTransmission(slaveAddress);
    Wire.write("A");               //Get Data
    Wire.endTransmission();
    delay(10);                   // 70us delay
    Wire.requestFrom(slaveAddress, 2);        // Request the 2 byte heading
    i = 0;
    while(Wire.available() && i < 2)
    {
      headingData[i] = Wire.read();
      i++;
    }
    currHeading = (headingData[0]*256 + headingData[1])/10;  // Put the MSB and LSB together and divide by 10
    return currHeading;
}

void steerUpdate(double input[2]){ //input format: input[0, current heading]
  if(input[0] == 0){
    if(input[1] < 180 && input[1] > 0)
      servo.write(STEER_CENTERPOINT-STEER_SCALING*input[1]);
    else if(input[1] > 180 && input[1] < 360){
      servo.write((360+STEER_CENTERPOINT)-STEER_SCALING*input[1]); //90-(1/5)*input[1]
      Serial.print("Plus "); Serial.println(STEER_SCALING*input[1]-270);
    }
  }
  else if(input[1] == 1){servo.write(input[1]);}
}
