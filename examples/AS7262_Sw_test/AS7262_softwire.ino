/***************************************************************************
  This is a library for the Adafruit AS7262 6-Channel Visible Light Sensor

  This sketch reads the sensor

  Designed specifically to work with the Adafruit AS7262 breakout
  ----> http://www.adafruit.com/products/3779
  
  These sensors use I2C to communicate. The device's I2C address is 0x49
  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!
  
  Written by Dean Miller for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <SoftWire.h>

SoftWire sw(2,3);  
#include "Adafruit_AS726xSoft.h"

#include <AsyncDelay.h>

//create the object
Adafruit_AS726xSoft ams;

//buffer to hold raw values
uint16_t sensorValues[AS726x_NUM_CHANNELS];

//buffer to hold calibrated values (not used by default in this example)
//float calibratedValues[AS726x_NUM_CHANNELS];

// SoftWire requires that the programmer declares the buffers used. This allows the amount of memory used to be set
// according to need. For the HIH61xx only a very small RX buffer is needed.
uint8_t i2cRxBuffer[32];
uint8_t i2cTxBuffer[32];

void setup() {
  Serial.begin(250000);
  while(!Serial);
   
  sw.setRxBuffer(i2cRxBuffer, sizeof(i2cRxBuffer));
  sw.setTxBuffer(i2cTxBuffer, sizeof(i2cTxBuffer));
  sw.setTimeout_ms(200);
  sw.begin();
    
  Serial.println("STARTING");
  //begin and make sure we can talk to the sensor
  if(!ams.begin(&sw)){
    Serial.println("could not connect to sensor! Please check your wiring.");
  }
  ams.setConversionType(MODE_2);

  Serial.println("INIT");
}


void loop() {

  if (ams.dataReady()) {
      uint8_t temp = ams.readTemperature();  
      ams.readRawValues(sensorValues);
      Serial.print("Temp: "); Serial.print(temp);
      Serial.print(" Violet: "); Serial.print(sensorValues[AS726x_VIOLET]);
      Serial.print(" Blue: "); Serial.print(sensorValues[AS726x_BLUE]);
      Serial.print(" Green: "); Serial.print(sensorValues[AS726x_GREEN]);
      Serial.print(" Yellow: "); Serial.print(sensorValues[AS726x_YELLOW]);
      Serial.print(" Orange: "); Serial.print(sensorValues[AS726x_ORANGE]);
      Serial.print(" Red: "); Serial.print(sensorValues[AS726x_RED]);
      Serial.println();
  }


}

