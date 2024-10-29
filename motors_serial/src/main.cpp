#include "Arduino.h"
#include "Motor.h"

#define PIN_DIRECTION_FWD_1 14
#define PIN_DIRECTION_REV_1 15
#define PIN_DIRECTION_PWM_1 5

#define PIN_DIRECTION_FWD_2 16
#define PIN_DIRECTION_REV_2 17
#define PIN_DIRECTION_PWM_2 6

Motor motor1(PIN_DIRECTION_FWD_1, PIN_DIRECTION_REV_1, PIN_DIRECTION_PWM_1, 2);
Motor motor2(PIN_DIRECTION_FWD_2, PIN_DIRECTION_REV_2, PIN_DIRECTION_PWM_2, 3);

float a1 = -1.30;
float b1 = 420.63;
float a2 = -2.04;
float b2 = 654.20;


int calculatePWM(int impulses, float a, float b) {
    int pwm = a * impulses + b;
    return constrain(pwm, 0, 255);
}

void moveForward(int impulses) {
    int motor1_pwm = calculatePWM(impulses, a1, b1);
    int motor2_pwm = calculatePWM(impulses, a2, b2);

    motor1.set_direction(REVERSE);
    motor2.set_direction(FORWARD);
    motor1.set_speed(motor1_pwm);
    motor2.set_speed(motor2_pwm);

    while (motor1.get_encoder_count() < impulses && motor2.get_encoder_count() < impulses) {
        delay(10);
    }

    motor1.stop();
    motor2.stop();
    Serial.println("Move complete");
}

void turnRight(int impulses) {
    int motor1_pwm = calculatePWM(impulses, a1, b1);
    int motor2_pwm = calculatePWM(impulses, a2, b2);

    motor1.set_direction(FORWARD);
    motor2.set_direction(FORWARD);
    motor1.set_speed(motor1_pwm);
    motor2.set_speed(motor2_pwm);

    while (motor1.get_encoder_count() < impulses && motor2.get_encoder_count() < impulses) {
        delay(10);
    }

    motor1.stop();
    motor2.stop();
    Serial.println("Turn complete");
}

void parseCommand(String command) {
    char cmdType = command.charAt(0);
    int value = command.substring(2).toInt();
    if (cmdType == 'M') {
        moveForward(value);
    } else if (cmdType == 'T') {
        turnRight(value);
    } else {
        Serial.println("Unknown command");
    }
}

void setup() {
    Serial.begin(9600);
    motor1.initialize();
    motor2.initialize();
}

//String command = "";

void loop() {
    motor1.reset_encoder_count();
    motor2.reset_encoder_count();
    if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n');
        command.trim();
        Serial.println(command);
        parseCommand(command);
    }
}
