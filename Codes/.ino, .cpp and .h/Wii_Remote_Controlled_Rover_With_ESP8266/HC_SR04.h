// ====================================================================================================
// Inclusion files block
// ====================================================================================================
#ifndef HC_SR04_H
#define HC_SR04_H

#include <Arduino.h>

// ====================================================================================================
// HC_SR04 Class block
// ====================================================================================================
class HC_SR04 {
  private:
    int triggerPin;                      // Pin for triggering the sensor
    int echoPin;                         // Pin that reads the echo
    int iCode;                           // Variable for the "switch case"
    String* sMessage;                    // Error messages as a pointer

  public:
    HC_SR04(int iTrigPin, int iEchoPin); // Constructor: initializes the sensor with the specified analog pins
    
    void begin();

    float vReadDistance();

    float vReadBrute();

    float vReadBrute1();

    void vMessagesDErreurs(int iCode, String* sMessage);
};

#endif
