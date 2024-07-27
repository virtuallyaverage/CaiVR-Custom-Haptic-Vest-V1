#include <ArduinoOSCWiFi.h>
#include "PCA9685.h"

// WiFi credentials
const char* ssid = "SlimeServer";
const char* pwd = "95815480";

// PCA9685 controller
PCA9685 pwmController;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  pwmController.init();

  // WiFi setup
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi connected, IP = " + WiFi.localIP().toString());

  Serial.println("Enter motor number (0-31) to vibrate, followed by Enter:");
}

String input;
void loop() {
  if (Serial.available() > 0) {
    input = Serial.readString();
    if (input) {
      Serial.println("Enter motor number to continue: ");
    }

    int motorIndex = input.toInt();

    if (motorIndex >= 0 && motorIndex < 32) {
      Serial.println("Vibrating motor " + String(motorIndex) + ". Press Enter to stop.");
      pwmController.setChannelPWM(motorIndex, floatToDuty(0.6));

      // Wait for next motor Enter key to stop the motor
      while (Serial.available() == 0) {
        delay(100);
      }
      pwmController.setChannelOff(motorIndex);
      Serial.println("Motor " + String(motorIndex) + " stopped.");
    } else {
      Serial.println("Invalid motor index. Please enter a number between 0 and 31.");
    }
  }
}

uint16_t floatToDuty(float e) {
  return static_cast<uint16_t>(e * 4096);
}
