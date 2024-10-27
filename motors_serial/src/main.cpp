#include "Arduino.h"
#include "../lib/Motor/Motor.h"

#define PIN_DIRECTION_FWD_1 14
#define PIN_DIRECTION_REV_1 15
#define PIN_DIRECTION_PWM_1 5

#define PIN_DIRECTION_FWD_2 16
#define PIN_DIRECTION_REV_2 17
#define PIN_DIRECTION_PWM_2 6

#define MEASUREMENT_TIME_MS 1000

Motor motor1(PIN_DIRECTION_FWD_1, PIN_DIRECTION_REV_1, PIN_DIRECTION_PWM_1, 2);
Motor motor2(PIN_DIRECTION_FWD_2, PIN_DIRECTION_REV_2, PIN_DIRECTION_PWM_2, 3);

void setup() {
    Serial.begin(9600);
    motor1.set_encoder_count(0);
    motor2.set_encoder_count(0);
    motor1.initialize();
    motor2.initialize();
}

void loop() {
    delay(MEASUREMENT_TIME_MS);

    Serial.print("PWM1: ;");
    Serial.print(analogRead(PIN_DIRECTION_PWM_1));
    Serial.print(";PWM2: ;");
    Serial.print(analogRead(PIN_DIRECTION_PWM_2));
    Serial.print(";Motor 1 impulses/s: ;");
    Serial.print(motor1.get_encoder_count());
    Serial.print(";Motor 2 impulses/s: ;");
    Serial.println(motor2.get_encoder_count());

    motor1.reset_encoder_count();
    motor2.reset_encoder_count();
}
