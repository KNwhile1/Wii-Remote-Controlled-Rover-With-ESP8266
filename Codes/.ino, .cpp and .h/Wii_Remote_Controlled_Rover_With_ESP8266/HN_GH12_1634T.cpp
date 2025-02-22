// ====================================================================================================
// Inclusion files block
// ====================================================================================================
#include "HN_GH12_1634T.h"

// ====================================================================================================
// Constructor block
// ====================================================================================================
HN_GH12_1634T::HN_GH12_1634T(int m1p1, int m1p2, int e1p, int m2p1, int m2p2, int e2p, int m3p1, int m3p2, int e3p, int m4p1, int m4p2, int e4p) {
    iPinMoteurDevantDroite1 = m1p1;
    iPinMoteurDevantDroite2 = m1p2;
    iEnableMoteurDevantDroite = e1p;

    iPinMoteurDevantGauche1 = m2p1;
    iPinMoteurDevantGauche2 = m2p2;
    iEnableMoteurDevantGauche = e2p;

    iPinMoteurDerriereDroite1 = m3p1;
    iPinMoteurDerriereDroite2 = m3p2;
    iEnableMoteurDerriereDroite = e3p;

    iPinMoteurDerriereGauche1 = m4p1;
    iPinMoteurDerriereGauche2 = m4p2;
    iEnableMoteurDerriereGauche = e4p;

    pinMode(iPinMoteurDevantDroite1, OUTPUT);
    pinMode(iPinMoteurDevantDroite2, OUTPUT);
    pinMode(iEnableMoteurDevantDroite, OUTPUT);
    
    pinMode(iPinMoteurDevantGauche1, OUTPUT);
    pinMode(iPinMoteurDevantGauche2, OUTPUT);
    pinMode(iEnableMoteurDevantGauche, OUTPUT);
    
    pinMode(iPinMoteurDerriereDroite1, OUTPUT);
    pinMode(iPinMoteurDerriereDroite2, OUTPUT);
    pinMode(iEnableMoteurDerriereDroite, OUTPUT);
    
    pinMode(iPinMoteurDerriereGauche1, OUTPUT);
    pinMode(iPinMoteurDerriereGauche2, OUTPUT);
    pinMode(iEnableMoteurDerriereGauche, OUTPUT);

    vArreter();
}
// ====================================================================================================

// ====================================================================================================
// Function to move forward with 4 HN-GH12-1634T
// ====================================================================================================
void HN_GH12_1634T::vAvancer(int iPwm) {
    digitalWrite(iPinMoteurDevantDroite1, LOW);
    digitalWrite(iPinMoteurDevantDroite2, HIGH);
    digitalWrite(iPinMoteurDevantGauche1, LOW);
    digitalWrite(iPinMoteurDevantGauche2, HIGH);
    
    digitalWrite(iPinMoteurDerriereDroite1, LOW);
    digitalWrite(iPinMoteurDerriereDroite2, HIGH);
    digitalWrite(iPinMoteurDerriereGauche1, LOW);
    digitalWrite(iPinMoteurDerriereGauche2, HIGH);

    analogWrite(iEnableMoteurDevantDroite, iPwm);
    analogWrite(iEnableMoteurDevantGauche, iPwm);
    analogWrite(iEnableMoteurDerriereDroite, iPwm);
    analogWrite(iEnableMoteurDerriereGauche, iPwm);
}
// ====================================================================================================

// ====================================================================================================
// Function to move backward with 4 HN-GH12-1634T
// ====================================================================================================
void HN_GH12_1634T::vReculer(int iPwm) {
    digitalWrite(iPinMoteurDevantDroite1, HIGH);
    digitalWrite(iPinMoteurDevantDroite2, LOW);
    digitalWrite(iPinMoteurDevantGauche1, HIGH);
    digitalWrite(iPinMoteurDevantGauche2, LOW);

    digitalWrite(iPinMoteurDerriereDroite1, HIGH);
    digitalWrite(iPinMoteurDerriereDroite2, LOW);
    digitalWrite(iPinMoteurDerriereGauche1, HIGH);
    digitalWrite(iPinMoteurDerriereGauche2, LOW);

    analogWrite(iEnableMoteurDevantDroite, iPwm);
    analogWrite(iEnableMoteurDevantGauche, iPwm);
    analogWrite(iEnableMoteurDerriereDroite, iPwm);
    analogWrite(iEnableMoteurDerriereGauche, iPwm);
}
// ====================================================================================================

// ====================================================================================================
// Function to turn left with 4 HN-GH12-1634T
// ====================================================================================================
void HN_GH12_1634T::vTournerAGauche(int iPwm) {
    digitalWrite(iPinMoteurDevantDroite1, LOW);
    digitalWrite(iPinMoteurDevantDroite2, HIGH);
    digitalWrite(iPinMoteurDerriereDroite1, LOW);
    digitalWrite(iPinMoteurDerriereDroite2, HIGH);

    digitalWrite(iPinMoteurDevantGauche1, HIGH);
    digitalWrite(iPinMoteurDevantGauche2, LOW);
    digitalWrite(iPinMoteurDerriereGauche1, HIGH);
    digitalWrite(iPinMoteurDerriereGauche2, LOW);

    analogWrite(iEnableMoteurDevantDroite, iPwm);
    analogWrite(iEnableMoteurDevantGauche, iPwm);
    analogWrite(iEnableMoteurDerriereDroite, iPwm);
    analogWrite(iEnableMoteurDerriereGauche, iPwm);
}
// ====================================================================================================

// ====================================================================================================
// Function to turn right with 4 HN-GH12-1634T
// ====================================================================================================
void HN_GH12_1634T::vTournerADroite(int iPwm) {
    digitalWrite(iPinMoteurDevantDroite1, HIGH);
    digitalWrite(iPinMoteurDevantDroite2, LOW);
    digitalWrite(iPinMoteurDerriereDroite1, HIGH);
    digitalWrite(iPinMoteurDerriereDroite2, LOW);

    digitalWrite(iPinMoteurDevantGauche1, LOW);
    digitalWrite(iPinMoteurDevantGauche2, HIGH);
    digitalWrite(iPinMoteurDerriereGauche1, LOW);
    digitalWrite(iPinMoteurDerriereGauche2, HIGH);

    analogWrite(iEnableMoteurDevantDroite, iPwm);
    analogWrite(iEnableMoteurDevantGauche, iPwm);
    analogWrite(iEnableMoteurDerriereDroite, iPwm);
    analogWrite(iEnableMoteurDerriereGauche, iPwm);
}
// ====================================================================================================

// ====================================================================================================
// Function to stop all motors with 4 HN-GH12-1634T
// ====================================================================================================
void HN_GH12_1634T::vArreter() {
    digitalWrite(iPinMoteurDevantDroite1, LOW);
    digitalWrite(iPinMoteurDevantDroite2, LOW);
    analogWrite(iEnableMoteurDevantDroite, 0);

    digitalWrite(iPinMoteurDevantGauche1, LOW);
    digitalWrite(iPinMoteurDevantGauche2, LOW);
    analogWrite(iEnableMoteurDevantGauche, 0);

    digitalWrite(iPinMoteurDerriereDroite1, LOW);
    digitalWrite(iPinMoteurDerriereDroite2, LOW);
    analogWrite(iEnableMoteurDerriereDroite, 0);

    digitalWrite(iPinMoteurDerriereGauche1, LOW);
    digitalWrite(iPinMoteurDerriereGauche2, LOW);
    analogWrite(iEnableMoteurDerriereGauche, 0);
}
// ====================================================================================================

// ====================================================================================================
// Function to send wheel control values to a website
// ====================================================================================================
void HN_GH12_1634T::vControlWheel(String sWheel, int iPwmValue) {
    if (sWheel == "front_right") {
        digitalWrite(iPinMoteurDevantDroite1, LOW);
        digitalWrite(iPinMoteurDevantDroite2, HIGH);
        analogWrite(iEnableMoteurDevantDroite, iPwmValue);
    } else if (sWheel == "front_left") {
        digitalWrite(iPinMoteurDevantGauche1, LOW);
        digitalWrite(iPinMoteurDevantGauche2, HIGH);
        analogWrite(iEnableMoteurDevantGauche, iPwmValue);
    } else if (sWheel == "rear_right") {
        digitalWrite(iPinMoteurDerriereDroite1, LOW);
        digitalWrite(iPinMoteurDerriereDroite2, HIGH);
        analogWrite(iEnableMoteurDerriereDroite, iPwmValue);
    } else if (sWheel == "rear_left") {
        digitalWrite(iPinMoteurDerriereGauche1, LOW);
        digitalWrite(iPinMoteurDerriereGauche2, HIGH);
        analogWrite(iEnableMoteurDerriereGauche, iPwmValue);
    }
}
