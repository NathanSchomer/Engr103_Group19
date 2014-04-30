//EM406 10m accuracy

#include "SoftwareSerial.h"

// initialize variables
int mode =- 1;            //incoming request
char im[80];              //incoming message from GPS
char incoming_char = 0;   //hold caracter from GPS
int count = 0;            //length of message

SoftwareSerial gps(10,11);  

float lat;  //latitude
char latD;  //latitude direction
float lng;  //longitude
char lngD;  //longitude direction
float time; //timestamp

void setup(){
  gps.begin(4800);
  Serial.begin(9600);
  
  //GPS Initialization Wait (waits for "$")
  char b = 'a';
  while(b != 36){
    b = gps.read();
  }
  
  //Wait for Specific character from the PC
  Serial.println('c');
  char c = 'b';
  while(c != 'c'){
    c = Serial.read();
  }
}
  
void loop(){
  if(gps.available() >  0){
    incoming_char = gps.read();
    if(incoming_char == 36){
       if(im[0] == 'G' && im[1] == 'P' && im[2] == 'G' && im[3]=='G' && im[4] == 'A'){ //if line starts with "GPGGS"...
         //Create a char buffer to store the time before we convert it to a float
         char timeBuffer[10];
         for(int i = 0; i < 10; i++)
           timeBuffer[0+i] = im[6+i];
         time = atof(timeBuffer); //convert the char buffer into a float
         
         char latBuffer[9];
         for(int i = 0; i < 9; i++)
           latBuffer[0+i] = im[17+i];
         lat = atof(latBuffer);
         
         latD = im[27];
         
         char lngBuffer[10];
         for(int i = 0; i < 10; i++)
           lngBuffer[0+i] = im[29+i];
         lng = atof(lngBuffer);
         
         lngD = im[40];
       }
       count = 0;
    }else{//if the imcoming char is not $
      im[count] = incoming_char;
      count++;
    }
    if(Serial.available() > 0){
      mode=Serial.read();
      switch(mode){
        case 'T':
        Serial.println(time);
        break;
      
        case 'A':
        Serial.println(lat);
        break;
      
        case 'a':
        Serial.println(latD);
        break;
      
        case 'O':
        Serial.println(lng);
        break;
      
        case 'o':
        Serial.println(lngD);
        break;
      }
    }
  }
}


