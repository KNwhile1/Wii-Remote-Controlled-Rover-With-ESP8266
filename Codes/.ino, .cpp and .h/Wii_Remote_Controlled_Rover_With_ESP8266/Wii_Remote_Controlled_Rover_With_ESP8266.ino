// ====================================================================================================
// Name: Wii_Remote_Controlled_Rover_With_ESP8266
// Description: This code allows remote control of a rover using a Wii controller and ESP32 with web-based functions.
// Target: Arduino Uno
// Compiler: Arduino IDE
// Usage: Control rover movement, headlights, and sensors via a web interface or Wii controller.
// Restriction(s): None.
// History: 11/06/2024 | K. Niamba / P. Miguel / Creation;
//          2/21/2025 | K. Niamba / Modification ---> Documentation translation (FR to ENG);
// ====================================================================================================

// ====================================================================================================
// Header File Block
// ====================================================================================================
#include "HC_SR04.h"
#include "Sharp_2D120X.h"
#include "Sharp_2Y0A02.h"
#include "ESP32Wiimote.h"
#include "HN_GH12_1634T.h"
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "Headlights.h"

// ====================================================================================================
// Pin Declaration Block
// ====================================================================================================
HC_SR04 HC_SR04(17, 16);

Sharp_2D120X Sharp_2D120X(36);

Sharp_2Y0A02 Sharp_2Y0A02(34);

ESP32Wiimote wiimote;

const int iPinMoteurDevantDroite1 = 32;
const int iPinMoteurDevantDroite2 = 15;
const int iEnableMoteurDevantDroite = 14;
const int iPinMoteurDevantGauche1 = 27;
const int iPinMoteurDevantGauche2 = 33;
const int iEnableMoteurDevantGauche = 12;
const int iPinMoteurDerriereDroite1 = 5;
const int iPinMoteurDerriereDroite2 = 18;
const int iEnableMoteurDerriereDroite = 19;
const int iPinMoteurDerriereGauche1 = 23;
const int iPinMoteurDerriereGauche2 = 22;
const int iEnableMoteurDerriereGauche = 21;

const int iPinCapteurLumiere = 39;
const int iPinLumiere = 13;

HN_GH12_1634T HN_GH12_1634T(iPinMoteurDevantDroite1, iPinMoteurDevantDroite2, iEnableMoteurDevantDroite, 
            iPinMoteurDevantGauche1, iPinMoteurDevantGauche2, iEnableMoteurDevantGauche, 
            iPinMoteurDerriereDroite1, iPinMoteurDerriereDroite2, iEnableMoteurDerriereDroite, 
            iPinMoteurDerriereGauche1, iPinMoteurDerriereGauche2, iEnableMoteurDerriereGauche);

Headlights Headlights(iPinLumiere);

// ====================================================================================================
// Wi-Fi Initialization Block
// ====================================================================================================
const char* ssid = "CPI-IOT";
const char* password = "iOTN3t$$";

WebServer server(80);

// ====================================================================================================
// Variables and State Tracking Block
// ====================================================================================================
unsigned long lastDataTime = 0;

const unsigned long disconnectThreshold = 300;

float fAverageDistance = 0.0;

String sCurrentDirection = "stop";

bool bStopped = false;

TaskHandle_t WiimoteTaskHandle;                                                               // <<Task handle>> for the WiimoteTask function

bool bLedAutoMode = false;                                                                    // Flag to control automatic LED mode

// ====================================================================================================
// Wii Controller and HN_GH12_1634T Control Block
// ====================================================================================================
void WiimoteTask(void * parameter) {
    while(true) {
        if (!bStopped) {                                                                      // Process Wiimote input only if bStopped is false
            wiimote.task();
            if (wiimote.available() > 0) {
                lastDataTime = millis();
                AccelState accel = wiimote.getAccelState();

                accel.xAxis = constrain(accel.xAxis, 101, 150);
                accel.yAxis = constrain(accel.yAxis, 101, 150);

                if (accel.xAxis >= 130) {
                    int iPWMValue = map(accel.xAxis, 130, 150, 0, 255);
                    HN_GH12_1634T.vAvancer(iPWMValue);
                    sCurrentDirection = "up";
                } else if (accel.xAxis <= 120) {
                    int iPWMValue = map(accel.xAxis, 101, 120, 255, 0);
                    HN_GH12_1634T.vReculer(iPWMValue);
                    sCurrentDirection = "down";
                } else if (accel.yAxis >= 130) {
                    int iPWMValue = map(accel.yAxis, 130, 150, 0, 255);
                    HN_GH12_1634T.vTournerAGauche(iPWMValue);
                    sCurrentDirection = "left";
                } else if (accel.yAxis <= 120) {
                    int iPWMValue = map(accel.yAxis, 101, 120, 255, 0);
                    HN_GH12_1634T.vTournerADroite(iPWMValue);
                    sCurrentDirection = "right";
                } else {
                    HN_GH12_1634T.vArreter();
                    sCurrentDirection = "stop";
                }
            }
        } else {
            HN_GH12_1634T.vArreter();                                                         // Ensure HN_GH12_1634T stops if bStopped is true
            sCurrentDirection = "stop";
        }
        delay(10);
    }
}

// ====================================================================================================
// Setup Block
// ====================================================================================================
void setup() {
  Serial.begin(115200);
  wiimote.init();
  HN_GH12_1634T.vArreter();
  pinMode(iPinCapteurLumiere, INPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
  }
// ========================================================================================================================================================================================================
// Web Control Website Section
// ========================================================================================================================================================================================================

// ----------------------------------------------------------------------------------------------------
// Speed root block
// ----------------------------------------------------------------------------------------------------
  server.on("/Vitesse", []() {
    AccelState accel = wiimote.getAccelState();
    accel.xAxis = constrain(accel.xAxis, 101, 150);
    int iPWMValue = map(accel.xAxis, 130, 150, 0, 255);
    float sVitesse = abs(static_cast<float>(iPWMValue));

    String sReponseJson = "{\"vitesse\": " + String(sVitesse) + "}";                          // Speed in JSON Format
        
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "application/json", sReponseJson);
  });

// ----------------------------------------------------------------------------------------------------
// IP and MAC address root block
// ----------------------------------------------------------------------------------------------------
  server.on("/IP_et_MAC", []() {
    String sIP = WiFi.localIP().toString();
    String sMAC = WiFi.macAddress();
    String sReponse = sIP + "," + sMAC;
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", sReponse);
  });

// ----------------------------------------------------------------------------------------------------
// Average distance from three sensors (HC-SR04, Sharp 2D120X, and Sharp 2Y0A02)
// ----------------------------------------------------------------------------------------------------
  server.on("/Distance_moyenne", []() {
    float fDistance = HC_SR04.vReadDistance();
    float fSharpDistance = Sharp_2D120X.vReadDistance();
    float fLongRangeDistance = Sharp_2Y0A02.vReadDistance();
    fAverageDistance = (fDistance + fSharpDistance + fLongRangeDistance) / 3.0;
    String sReponse = String(fAverageDistance);
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", sReponse);       
  });

// ----------------------------------------------------------------------------------------------------
// HC-SR04 sensor and its distance (cm)
// ----------------------------------------------------------------------------------------------------
  server.on("/Capteur_HC_SR04", []() {
    float fDistance = HC_SR04.vReadDistance();
    String sReponse = String(fDistance);
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", sReponse);
  });

// ----------------------------------------------------------------------------------------------------
// Sharp 2D120X sensor and its distance (cm)
// ----------------------------------------------------------------------------------------------------
  server.on("/Capteur_Sharp_2D120X", []() {
    float fSharpDistance = Sharp_2D120X.vReadDistance();
    String sReponse = String(fSharpDistance);
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", sReponse);
  });

// ----------------------------------------------------------------------------------------------------
// Sharp 2Y0A02 sensor and its distance (cm)
// ----------------------------------------------------------------------------------------------------
  server.on("/Capteur_Sharp_2Y0A02", []() {
    float fLongRangeDistance = Sharp_2Y0A02.vReadDistance();
    String sReponse = String(fLongRangeDistance);
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", sReponse);
  });

// ----------------------------------------------------------------------------------------------------
// Headlights on
// ----------------------------------------------------------------------------------------------------
  server.on("/Headlights/on", []() {
    digitalWrite(iPinLumiere, HIGH);
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", "Headlights on");
  });

// ----------------------------------------------------------------------------------------------------
// Headlights off
// ----------------------------------------------------------------------------------------------------
  server.on("/Headlights/off", []() {
    digitalWrite(iPinLumiere, LOW);
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", "Headlights off");
  });

// ----------------------------------------------------------------------------------------------------
// Headlights automatic
// ----------------------------------------------------------------------------------------------------
 server.on("/Headlights/auto", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", bLedAutoMode ? "Automatic headlights activated" : "Automatic headlights deactivated");
  });

// ----------------------------------------------------------------------------------------------------
// Current direction root block
// ----------------------------------------------------------------------------------------------------
  server.on("/Direction", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", sCurrentDirection);
  });

// ----------------------------------------------------------------------------------------------------
// Wii controller and HN_GH12_1634T stop
// ----------------------------------------------------------------------------------------------------
  server.on("/Wii/arret", []() {
    bStopped = true;                                                                          // Set flag to true to stop the Wii controller and HN_GH12_1634T
    HN_GH12_1634T.vArreter();
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", "Wii controller and HN_GH12_1634T are stopped");
  });

// ----------------------------------------------------------------------------------------------------
// Wii controller running
// ----------------------------------------------------------------------------------------------------
  server.on("/Wii/marche", []() {
    bStopped = false;                                                                         // Set flag to false to start the Wii controller
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", "Wii controller is running");
  });

// ----------------------------------------------------------------------------------------------------
// Stop distance root block
// ----------------------------------------------------------------------------------------------------
  server.on("/Distance_d_arret", []() {
    float fDistance = HC_SR04.vReadDistance();
    if (server.hasArg("value")) {
        float fStopDistance = server.arg("value").toFloat();
        if (fDistance < fStopDistance) {
            HN_GH12_1634T.vAvancer(255);
            Serial.println(fStopDistance);
        }
        server.send(200, "text/plain", "Received distance: " + String(fStopDistance));
        HN_GH12_1634T.vArreter();
    } else {
        server.send(400, "text/plain", "No distance provided");
    }
  });

// ========================================================================================================================================================================================================
// Troubleshooting Web Section
// ========================================================================================================================================================================================================

// ----------------------------------------------------------------------------------------------------
// HC-SR04 sensor raw value root block
// ----------------------------------------------------------------------------------------------------
  server.on("/CapteurHC_SR04(1)", []() {
    float fDistance = HC_SR04.vReadDistance();
    String sReponse = String(fDistance);
    server.send(200, "text/plain", sReponse);
  });

// ----------------------------------------------------------------------------------------------------
// Debug Wiimote data root block
// ----------------------------------------------------------------------------------------------------
  server.on("/Wiimote", []() {
    String sReponse = String(wiimote.getAccelState().xAxis) + "," +
                       String(wiimote.getAccelState().yAxis) + "," +
                       String(wiimote.getAccelState().zAxis) + "," +
                       String(wiimote.getButtonState().left) + "," +
                       String(wiimote.getButtonState().right);
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", sReponse);
  });

// ====================================================================================================
// Start Wiimote Task and Server
// ====================================================================================================
  xTaskCreate(WiimoteTask, "WiimoteTask", 4096, NULL, 1, &WiimoteTaskHandle);

  server.begin();
}

// ====================================================================================================
// Loop Block
// ====================================================================================================
void loop() {
  server.handleClient();
}
