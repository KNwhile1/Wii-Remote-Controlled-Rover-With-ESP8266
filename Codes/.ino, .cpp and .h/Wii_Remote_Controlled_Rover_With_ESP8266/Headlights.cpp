// ====================================================================================================
// Include File Block
// ====================================================================================================
#include "Headlights.h"

// ====================================================================================================
// Constructor Block
// ====================================================================================================
Headlights::Headlights(int iPin) {
  iPinLED = iPin;
  pinMode(iPinLED, OUTPUT);                                 
}

// ====================================================================================================
/**
* @Title        Function that captures the light value
* @description  This function reads the analog light value
*               and automatically turns the LED on or off
*
* @author [Miguel Pachebat]
* @date   November 6, 2024
*
* @param type and Variable name                type int and name iPinSensor
* @param type and Variable name                type int and name iLightValue
* @param type and Variable name                type int and name iResult
* @param type and Variable name                type int and name iPinLED
* @param type and Variable name                type int and name iBlackThreshold
* @param type and Variable name                type int and name iPreviousState
* @return type                                 type int
*
*/
void Headlights::vManageAutomaticLight(int iPinSensor) {

  int iLightValue = analogRead(iPinSensor);

  Serial.println(iLightValue);

  int iResult;
    
  if (iLightValue == 4095) {
      digitalWrite(iPinLED, LOW);
      iResult = -1;

  } else {
      int iBlackThreshold = 800;

      static int iPreviousState = LOW;

      if (iLightValue < iBlackThreshold && iPreviousState != HIGH) {
          digitalWrite(iPinLED, HIGH);
          iPreviousState = HIGH;

      } else if (iLightValue >= iBlackThreshold && iPreviousState != LOW) {
          digitalWrite(iPinLED, LOW);
          iPreviousState = LOW;
      }
  }
  return iResult;
}
// ====================================================================================================


// ====================================================================================================
/**
* @Title        Function that captures the current value
* @description  This function reads the raw analog value
*
*
* @author [Miguel Pachebat]
* @date   November 6, 2024
*
* @param type and Variable name                type int and name iSensorValue
* @param type and Variable name                type int and name iPin
* @return type                                 type float
*
*/
float Headlights::vReadRaw() {
  int iSensorValue = analogRead(iPin);
  return iSensorValue;
}
// ====================================================================================================


// ====================================================================================================
/**
* @Title        Function that captures the current value and sends it as error messages
* @description  This function sends error messages for the function
*               void vErrorMessages(int code, String* message);
*
* @author [Miguel Pachebat]
* @date   November 6, 2024
*
* @param type and Variable name                type int and name iSensorValue
* @param type and Variable name                type int and name iResult
* @return type                                 type int
*
*/
float Headlights::vReadRaw1() {
  int iSensorValue = analogRead(iPin);
  int iResult;

  if (iSensorValue == 0){                                     // If the raw analog value is 0
    iResult = -2;                                             // The result becomes -2
  }
  else{
    iResult = iSensorValue;
  }
  return iResult;
};
// ====================================================================================================


// ====================================================================================================
/**
* @Title        Error messages function
* @description  This function sends error messages for headlights (combination of LEDs and
*               a photoresistor) in a main code
*
*
* @author [Miguel Pachebat]
* @date   November 6, 2024
*
* @param type and Variable name                type int and name iCode
* @param type and Variable name                type String and name sMessage
* @return type                                 type String
*
*/
void Headlights::vErrorMessages(int iCode, String* sMessage) { // Function that changes cases and takes the corresponding message by pointer
  switch (iCode) {
    case -1:
      *sMessage = "ERROR #1: The photoresistor is short-circuited.";
      break;
    case -2:
      *sMessage = "ERROR #2: The photoresistor is disconnected.";
      break;
    default:
      *sMessage = "Valid value.";
      break;
  }
}
