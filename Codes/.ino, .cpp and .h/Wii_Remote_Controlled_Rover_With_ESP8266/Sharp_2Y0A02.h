// ====================================================================================================
// Include File Block
// ====================================================================================================
#ifndef Sharp_2Y0A02_H
#define Sharp_2Y0A02_H

#include <Arduino.h>

// ====================================================================================================
// Sharp_2Y0A02 Class Block
// ====================================================================================================
class Sharp_2Y0A02 {
  private:
    uint8_t iPin;                    // Analog pin
    int iCode;                       // Variable for the <<switch case>>
    String* sMessage;                // Error messages as pointer

  public:
    Sharp_2Y0A02(uint8_t analogPin); // Constructor: initializes the sensor with the specified analog pin

    float vReadDistance();            // Function to read the distance

    float vReadBrute();               // Function to read the raw value

    float vReadBrute1();              // Function to read the raw value with error handling

    void vMessagesDErreurs(int iCode, String* sMessage);  // Function to send error messages
};

#endif
