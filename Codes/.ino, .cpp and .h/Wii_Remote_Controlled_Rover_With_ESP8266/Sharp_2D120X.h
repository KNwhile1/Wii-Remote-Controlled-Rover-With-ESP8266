// ====================================================================================================
// Include File Block
// ====================================================================================================
#ifndef Sharp_2D120X_H
#define Sharp_2D120X_H

#include <Arduino.h>

// ====================================================================================================
// Sharp_2D120X Class Block
// ====================================================================================================
class Sharp_2D120X {
  private:
    uint8_t iPin;                    // Analog pin
    int iCode;                       // Variable for the <<switch case>>
    String* sMessage;                // Error messages as pointer
    
  public:
    Sharp_2D120X(uint8_t analogPin); // Constructor: initializes the sensor with the specified analog pin

    float vReadDistance();

    float vReadRaw();  // Renamed to match the method in the implementation file

    float vReadRaw1();

    void vErrorMessages(int iCode, String* sMessage);
};

#endif
