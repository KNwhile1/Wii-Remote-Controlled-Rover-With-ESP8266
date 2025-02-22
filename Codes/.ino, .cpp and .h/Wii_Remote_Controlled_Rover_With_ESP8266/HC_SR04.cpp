// ====================================================================================================
// Inclusion files block
// ====================================================================================================
#include "HC_SR04.h"

// ====================================================================================================
// Constructors block
// ====================================================================================================
HC_SR04::HC_SR04(int iTrigPin, int iEchoPin) : triggerPin(iTrigPin), echoPin(iEchoPin) {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

// ====================================================================================================
/**
* @Title        Function that captures the distance in cm
* @description  This function reads the analog value and converts it to distance
*
*
* @author [Kirstan Niamba]
* @date   November 6, 2024
*
* @param type and variable name               type int and name triggerPin
* @param type and variable name               type long and name lDuration
* @param type and variable name               type int and name echoPin
* @param type and variable name               type float and name fDistance
* @return type                              type float
*
*/
float HC_SR04::vReadDistance() {

    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);                                     // Sends a 10-microsecond pulse to trigger the sensor
    digitalWrite(triggerPin, LOW);

    long lDuration = pulseIn(echoPin, HIGH);                   // Measures the time for the echo's return

    float fDistance = (lDuration * 0.0343) / 2;                // Calculates the distance (cm)

    return fDistance;                                          // Returns the distance
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
* @param type and variable name               type long and name lDuration
* @param type and variable name               type int and name echoPin
* @return type                              type long
*
*/
float HC_SR04::vReadBrute() {
  long lDuration = pulseIn(echoPin, HIGH);
  return lDuration;                                            // Returns the raw analog value
}
// ====================================================================================================



// ====================================================================================================
/**
* @Title        Function that captures the current value and sends error messages
* @description  This function sends error messages for the function
*               void vMessagesDErreurs(int code, String* message);
*
* @author [Kirstan Niamba]
* @date   November 6, 2024
*
* @param type and variable name               type long and name lDuration
* @param type and variable name               type int and name echoPin
* @param type and variable name               type int and name iResultat
* @return type                              type int
*
*/
float HC_SR04::vReadBrute1() {
  long lDuration = pulseIn(echoPin, HIGH);
  int iResultat;

  if (lDuration >= 38000){                                     // If the duration is 38000
    iResultat = -1;                                            // Set iResultat to -1
  }
  else if (lDuration == 0){                                    // If the duration is 0
    iResultat = -2;                                            // Set iResultat to -2
  }
  else{
    iResultat = lDuration;
  }
  return iResultat;
};
// ====================================================================================================



// ====================================================================================================
/**
* @Title        Error messages function
* @description  This function sends error messages for a HC-SR04 in a main code
*
*
* @author [Kirstan Niamba]
* @date   November 6, 2024
*
* @param type and variable name               type int and name iCode
* @param type and variable name               type String and name sMessage
* @return type                              type String
*
*/
void HC_SR04::vMessagesDErreurs(int iCode, String* sMessage) { // Function that switches cases and takes the corresponding message by pointer
  switch (iCode) {
    case -1:
      *sMessage = "ERROR #1: The HC_SR04 sensor is short-circuited.";
      break;
    case -2:
      *sMessage = "ERROR #2: The HC_SR04 sensor is disconnected.";
      break;
    default:
      *sMessage = "Valid value.";
      break;
  }
}
