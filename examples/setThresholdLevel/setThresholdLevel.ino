/*****************************************************************
File:         setThresholdLevel.ino
Description:  Connect the IIC interface of BMK56T004 to Wire of 
              the Arduino using setThresholdLevel to set the thresholdLevel 
              and getThresholdLevel to obtain the thresholdLevel 
              via the I2C and then be displayed on the 
              Serial monitor.
******************************************************************/
#include "BMK54T004.h"
BMK54T004     BMK54(2,&Wire);//intPin,Please comment out this line of code if you don't use Wire
//BMK54T004     BMK54(22,&Wire1);//Please uncomment out this line of code if you use Wire1 on BMduino
//BMK54T004     BMK54(25,&Wire2);//Please uncomment out this line of code if you use Wire2 on BMduino
uint8_t Threshold[12]={0};
void setup() 
{
  Serial.begin(9600);
  BMK54.begin(); 
  BMK54.setAllThresholdLevel(2); 
  BMK54.getThreshold(Threshold);    
  for(uint8_t i=0;i<12;i++)
  {
    Serial.print("THR LEVEL");
    Serial.print(i);
    Serial.print("is:");
    Serial.println(Threshold[i]);  
  }
} 

void loop() 
{
   
}
