// ====================================================================================================
// Include File Block
// ====================================================================================================
#include "Sharp_2Y0A02.h"

// ====================================================================================================
// Constructor Block
// ====================================================================================================
Sharp_2Y0A02::Sharp_2Y0A02(uint8_t analogPin) {
  iPin = analogPin;
  pinMode(iPin, INPUT);
}

// ====================================================================================================
/**
* @Title        Function to capture the distance in cm
* @description  This function reads the analog value and converts it to distance
*
*
* @author [Kirstan Niamba]
* @date   6 November 2024
*
* @param type and Variable Name               type int and name iSensorValue
* @param type and Variable Name               type int and name iPin
* @param type and Variable Name               type float and name fVoltage
* @param type and Variable Name               type float and name fDistance
* @return type                              type float
*
*/
float Sharp_2Y0A02::vReadDistance() {
  int iSensorValue = analogRead(iPin);
  
  float fVoltage = iSensorValue * (5.0 / 1023.0);                  // Converts analog reading to voltage (5V system)
  
  float fDistance = (-9 * fVoltage) + 150;                         // Converts voltage to distance (cm)
  
  return fDistance;                                                // Returns the distance
}
// ====================================================================================================



// ====================================================================================================
/**
* @Title        Function to capture the current value
* @description  This function reads the raw analog value
*
*
* @author [Kirstan Niamba]
* @date   6 November 2024
*
* @param type and Variable Name               type int and name iSensorValue
* @param type and Variable Name               type int and name iPin
* @return type                              type float
*
*/
float Sharp_2Y0A02::vReadBrute() {
  int iSensorValue = analogRead(iPin);
  return iSensorValue;                                             // Returns the raw analog value
}
// ====================================================================================================



// ====================================================================================================
/**
* @Title        Function to capture the current value and send it as error messages
* @description  This function sends error messages for the function
*               void vErrorMessages(int code, String* message);
*
* @author [Kirstan Niamba]
* @date   6 November 2024
*
* @param type and Variable Name               type int and name iSensorValue
* @param type and Variable Name               type int and name iPin
* @param type and Variable Name               type int and name iResultat
* @return type                              type int
*
*/
float Sharp_2Y0A02::vReadBrute1() {
  int iSensorValue = analogRead(iPin);
  int iResultat;

  if (iSensorValue >= 3000){                                       // If the raw analog value is 3000
    iResultat = -1;                                                // iResultat becomes -1
  }
  else if (iSensorValue <= 80){                                    // If the raw analog value is 80
    iResultat = -2;                                                // iResultat becomes -2
  }
  else if (iSensorValue == 0){                                     // If the raw analog value is 0
    iResultat = -3;                                                // iResultat becomes -3
  }
  else{
    iResultat = iSensorValue;
  }
  return iResultat;
};
// ====================================================================================================



// ====================================================================================================
/**
* @Title        Error message function
* @description  This function sends error messages for the Sharp 2Y0A02 in the main code
*
*
* @author [Kirstan Niamba]
* @date   6 November 2024
*
* @param type and Variable Name               type int and name iCode
* @param type and Variable Name               type String and name sMessage
* @return type                              type String
*
*/
void Sharp_2Y0A02::vErrorMessages(int iCode, String* sMessage) {
  switch (iCode) {
    case -1:
      *sMessage = "ERROR #1: Sharp 2Y0A02 sensor is out of range (too close).";
      break;
    case -2:
      *sMessage = "ERROR #2: Sharp 2Y0A02 sensor is out of range (too far).";
      break;
    case -3:
      *sMessage = "ERROR #3: Sharp 2Y0A02 sensor is disconnected.";
      break;
    default:
      *sMessage = "Valid value.";
      break;
  }
}
