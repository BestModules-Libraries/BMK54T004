/*****************************************************************
File:             BMK54T004.h
Author:           YZY, BESTSOLUTIONS
Description:      Define classes and required variables
History：         
V1.0.1   -- initial version；2023-01-06；Arduino IDE :v1.8.16
******************************************************************/

#ifndef _BMK54T004_H_
#define _BMK54T004_H_

#include <Wire.h>
#include <Arduino.h>

#define SUCCESS           (0)
#define FAIL              (1)
#define BMK54T004_IICADDR 0x72

class BMK54T004
{
  public:
  BMK54T004(uint8_t intPin,TwoWire *theWire = &Wire);
  void begin(uint8_t i2c_addr = BMK54T004_IICADDR);
  uint8_t getINT();
  uint8_t readKeyValue();
  uint8_t readSlideValue();
  void getThreshold(uint8_t buff[]); 
  int setThreshold(uint8_t buff[]);
  int setAllThresholdLevel(uint8_t level);


  private:
  void writeBytes(uint8_t wbuf[], uint8_t wlen);
  uint8_t readBytes(uint8_t rbuf[], uint8_t rlen);
  uint8_t _intPin;
  uint8_t _i2caddr;
  TwoWire *_wire;
  uint8_t  TLCMD[1] = {0xD8};//threshold CMD
};

#endif
