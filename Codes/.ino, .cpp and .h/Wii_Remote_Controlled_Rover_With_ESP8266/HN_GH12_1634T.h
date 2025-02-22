// ====================================================================================================
// Include File Block
// ====================================================================================================
#pragma once
#include <Arduino.h>

// ====================================================================================================
// HN-GH12-1634T Class Block which contains 4 HN-GH12-1634T motors
// ====================================================================================================
class HN_GH12_1634T {
  private:
    int iPinMotorFrontRight1, iPinMotorFrontRight2, iEnableMotorFrontRight;
    int iPinMotorFrontLeft1, iPinMotorFrontLeft2, iEnableMotorFrontLeft;
    int iPinMotorBackRight1, iPinMotorBackRight2, iEnableMotorBackRight;
    int iPinMotorBackLeft1, iPinMotorBackLeft2, iEnableMotorBackLeft;

  public:
    HN_GH12_1634T(int m1p1, int m1p2, int e1p, int m2p1, int m2p2, int e2p, int m3p1, int m3p2, int e3p, int m4p1, int m4p2, int e4p);
    void vMoveForward(int iPwm);
    void vMoveBackward(int iPwm);
    void vTurnLeft(int iPwm);
    void vTurnRight(int iPwm);
    void vStop();
    void vControlWheel(String sWheel, int iPwm);
};
