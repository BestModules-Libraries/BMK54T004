/*****************************************************************
File:        BMK54T004.cpp
Author:      BESTSOLUTIONS
Description: The Arduino communicates with the BMK54T004 for the IIC and gets the corresponding values  
Version:     V1.0.2   -- 2024-05-07
******************************************************************/
#include "BMK54T004.h"
/**********************************************************
Description: Constructor
Parameters:  intPin :INT Output pin connection with Arduino 
             theWire : Wire object if your board has more than one I2C interface  
             
Return:          
Others:      
**********************************************************/
BMK54T004::BMK54T004(uint8_t intPin,TwoWire *theWire)
{
     _intPin = intPin;
     _wire = theWire;    
}
/**********************************************************
Description: Module Initial
Parameters:  i2c_addr :Module IIC address           
Return:          
Others:      
**********************************************************/
void BMK54T004::begin(uint8_t i2c_addr)
{
       pinMode(_intPin,INPUT_PULLUP);
       _wire->begin();
       _i2caddr = i2c_addr;
}
/**********************************************************
Description: get Key Status
Parameters:              
Return:      Returns the INT state  
             0:INT output low level  press
             1:INT output high level   unpress    
Others:      
**********************************************************/
uint8_t BMK54T004::getINT()
{
     return (digitalRead(_intPin));
} 
/**********************************************************
Description: read Key Value
Parameters:        
Return:     kvalue:Variables for storing value Key
                 kvalue=0:No key is pressed
                  bit0=1 : key1 is pressed
                  bit1=1 : key2 is pressed
                  bit2=1 : key3 is pressed
                  bit3=1 : key4 is pressed     
Others:      
**********************************************************/
uint8_t BMK54T004::readKeyValue()
{
  uint8_t value[]={0};
  uint8_t KeyCMD[1]={0X0E};
  writeBytes(KeyCMD,1);
  delay(5);
  readBytes(value,1);
  uint8_t kvalue = value[0];
  delay(10);
  return kvalue;  
}
/**********************************************************
Description: read Slide Value
Parameters:        
Return:      svalue:Variables for storing value Slide
                   svalue = 0:The slider is untouched
                   svalue = n:the  Slide n is touched(1~8)
Others:      
**********************************************************/
uint8_t BMK54T004::readSlideValue()
{
  uint8_t value[]={0};
  uint8_t SlideCMD[1]={0X0D};
  writeBytes(SlideCMD,1);
  delay(5);
  readBytes(value,1);
  uint8_t svalue = value[0];
  delay(10);
  return svalue;
}
/**********************************************************
Description: get Threshold
Parameters:  buff :Store acquired 12 touch threshold 
               buff[0]~buff[7]：Store the threshold of the slider at positions 1 to 8
               buff[8]~buff[11]：Store the threshold of key1 to key4     
Return:        
Others:      
**********************************************************/
void BMK54T004::getThreshold(uint8_t buff[])
{
  writeBytes(TLCMD,1);  
  delay(5);
  readBytes(buff,12); 
  delay(10);
}
/**********************************************************
Description: set Threshold
Parameters:  buff :Set acquired 12 touch threshold 
               buff[0]~buff[7]：Set the threshold of the slider at positions 1 to 8,range: 10-64
               buff[8]~buff[11]：Set the threshold of key1 to key4,range: 10-64         
Return:      Implementation status:
              0:Success 
              1:Fail    
Others:      
**********************************************************/
int BMK54T004::setThreshold(uint8_t buff[])
{ 
  uint16_t total = 0;
  uint8_t TXbuff[14] = {0};
  for(u8 i=0;i<12;i++)                    //sum
  {
      total = total + buff[i];
      TXbuff[i+1] = buff[i];
  }
  if(160 <= total && total<= 1024)//10~64
  {
      TXbuff[0] = 0XD8;
      TXbuff[13] = (uint8_t)total;
      writeBytes(TXbuff,14);
      delay(10);
      return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}
/**********************************************************
Description: set all Threshold Level
Parameters:  level :Storing ThresholdLevel Data,range: 0-6        
Return:      Implementation status:
              0:Success 
              1:Fail  
Others:      threshold = 10+level*9
**********************************************************/
int BMK54T004::setAllThresholdLevel(uint8_t level)
{
 if(level >= 7)
 {
   return FAIL; 
 }
  uint8_t thr = 10+level*9;
  uint8_t sum = 12*thr;
  uint8_t STLCMD[] = {0xD8,thr,thr,thr,thr,thr,thr,thr,thr,thr,thr,thr,thr,sum};
  writeBytes(STLCMD,14);
  delay(10);
  return SUCCESS; 
}
/**********************************************************
Description: writeBytes
Parameters:  wbuf :the bytes sent
             wlen :the length of the data sent          
Return:        
Others:      
**********************************************************/
void BMK54T004::writeBytes(uint8_t wbuf[], uint8_t wlen)
{
    while (_wire->available() > 0)
    {
      _wire->read();
    }
    _wire->beginTransmission(_i2caddr);
    _wire->write(wbuf, wlen);
    _wire->endTransmission();
}
/**********************************************************
Description: read Bytes
Parameters:  rbuf :the bytes receive
             rlen :the length of the data receive
Return:      Implementation status:
              0:Success 
              1:Fail   
Others:      
**********************************************************/
uint8_t BMK54T004::readBytes(uint8_t rbuf[], uint8_t rlen)
{
  _wire->requestFrom(_i2caddr, rlen);
  if(_wire->available()==rlen)
  {
      for (uint8_t i = 0; i < rlen; i++)
      {
        rbuf[i] = _wire->read();
      }
      return SUCCESS;
  }
  else
  {
       return FAIL;
  }
}
