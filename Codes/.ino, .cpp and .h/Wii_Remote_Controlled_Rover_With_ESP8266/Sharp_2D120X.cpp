// ====================================================================================================
// Include File Block
// ====================================================================================================
#include "Sharp_2D120X.h"

// ====================================================================================================
// Constructor Block
// ====================================================================================================
Sharp_2D120X::Sharp_2D120X(uint8_t analogPin) {
  iPin = analogPin;
  pinMode(iPin, INPUT);
}

// ====================================================================================================
/**
* @Title        Function that captures the distance in cm
* @description  This function reads the analog value and converts it into distance
*
*
* @author [Kirstan Niamba]
* @date   November 6, 2024
*
* @param type and Variable name               type int and name iSensorValue
* @param type and Variable name               type int and name iPin
* @param type and Variable name               type float and name fVoltage
* @param type and Variable name               type float and name fDistance
* @return type                                 type float
*
*/
float Sharp_2D120X::vReadDistance() {
  int iSensorValue = analogRead(iPin);
  
  float fVoltage = iSensorValue * (5.0 / 1023.0);                  // Converts the analog reading to voltage (5V system)
  
  float fDistance = (-6 * fVoltage) + 30;                          // Converts the voltage to distance (cm)
  
  return fDistance;                                                // Returns the distance
}
// ====================================================================================================


// ====================================================================================================
/**
* @Title        Function that captures the current value
* @description  This function reads the raw analog value
*
*
* @author [Kirstan Niamba]
* @date   November 6, 2024
*
* @param type and Variable name               type int and name iSensorValue
* @param type and Variable name               type int and name iPin
* @return type                                 type float
*
*/
float Sharp_2D120X::vReadRaw() {
  int iSensorValue = analogRead(iPin);
  return iSensorValue;                                             // Returns the raw analog value
}
// ====================================================================================================


// ====================================================================================================
/**
* @Title        Function that captures the current value and sends error messages
* @description  This function sends error messages for the function
*               void vErrorMessages(int code, String* message);
*
* @author [Kirstan Niamba]
* @date   November 6, 2024
*
* @param type and Variable name               type int and name iSensorValue
* @param type and Variable name               type int and name iPin
* @param type and Variable name               type int and name iResult
* @return type                                 type int
*
*/
float Sharp_2D120X::vReadRaw1() {
  int iSensorValue = analogRead(iPin);
  int iResult;

  if (iSensorValue >= 3000){                                       // If the raw analog value is 3000
    iResult = -1;                                                  // iResult becomes -1
  }
  else if (iSensorValue <= 80){                                    // If the raw analog value is 80
    iResult = -2;                                                  // iResult becomes -2
  }
  else if (iSensorValue == 0){                                     // If the raw analog value is 0
    iResult = -3;                                                  // iResult becomes -3
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
* @description  This function sends error messages for a Sharp 2D120X in a main code
*
*
* @author [Kirstan Niamba]
* @date   November 6, 2024
*
* @param type and Variable name               type int and name iCode
* @param type and Variable name               type String and name sMessage
* @return type                                 type String
*
*/
void Sharp_2D120X::vErrorMessages(int iCode, String* sMessage) { // Function that changes cases and takes the corresponding message by pointer
  switch (iCode) {
    case -1:
      *sMessage = "ERROR #1: Sharp 2D120X sensor is out of range (too close).";
      break;
    case -2:
      *sMessage = "ERROR #2: Sharp 2D120X sensor is out of range (too far).";
      break;
    case -3:
      *sMessage = "ERROR #3: Sharp 2D120X sensor is disconnected.";
      break;
    default:
      *sMessage = "Valid value.";
      break;
  }
}
