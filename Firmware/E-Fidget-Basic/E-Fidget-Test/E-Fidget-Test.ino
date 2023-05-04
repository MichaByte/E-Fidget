#include <avr/sleep.h>
#include <avr/power.h>

#include "Vars.h"

bool shouldRestartSpin = false;

void stopSpinning() {
  shouldRestartSpin = true;
}

void setup() {
  pinMode(M1_PIN, OUTPUT);
  pinMode(M2_PIN, OUTPUT);
  pinMode(M3_PIN, OUTPUT);

  pinMode(B1_PIN, INPUT_PULLUP);
  pinMode(B2_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(B1_PIN), spin, CHANGE);

  digitalWrite(M1_PIN, LOW);
  digitalWrite(M2_PIN, LOW);
  digitalWrite(M3_PIN, LOW);
}



int motorOn(uint8_t pin) {
  for (uint32_t tStart = millis(); (millis()-tStart) < ON_DELAY;) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(pin, LOW);
    delayMicroseconds(100);  
  }
}

int spin() {
  for (int i=1; i<=10; i++) {
    motorOn(M1_PIN);
    digitalWrite(M1_PIN, LOW);
    delay(i * OFF_DELAY_MULTIPLIER);

    motorOn(M2_PIN);
    digitalWrite(M2_PIN, LOW);
    delay(i * OFF_DELAY_MULTIPLIER);

    motorOn(M3_PIN);
    digitalWrite(M3_PIN, LOW);
    delay(i * OFF_DELAY_MULTIPLIER);
  }
}

void loop() {
  // if (digitalRead(B1_PIN) == BTN_ON) {
  //   spin();
  // }
  // sleep_mode();
}
