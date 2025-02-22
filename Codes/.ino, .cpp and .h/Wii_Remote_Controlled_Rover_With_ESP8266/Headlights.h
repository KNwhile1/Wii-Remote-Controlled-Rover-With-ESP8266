// ====================================================================================================
// Include File Block
// ====================================================================================================
#pragma once
#include <Arduino.h>

// ====================================================================================================
// Headlights Class Block
// ====================================================================================================
class Headlights {
  private:
    int iPinLED;
    int iCode;                           // Variable for the <<switch case>>
    String* sMessage;                    // Error messages as pointer
    
  public:
    Headlights(int iPin);

    void vManageAutomaticLight(int iPinSensor);

    float vReadRaw();  // Fixed method syntax (removed the colon)

    float vReadRaw1();
    
    void vErrorMessages(int iCode, String* sMessage);
};
