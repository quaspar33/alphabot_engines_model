#include "Motor.h"
#include "Arduino.h"
#include "../BindArg/BindArg.h"

#define DIRECTION_SWITCH_DELAY 100

Motor::Motor(uint8_t fwd_pin, uint8_t rev_pin, uint8_t pwm_pin, uint8_t interrupt_pin)
        : pin_fwd(fwd_pin), pin_rev(rev_pin), pin_pwm(pwm_pin), pin_interrupt(interrupt_pin) {}

void Motor::set_direction(gear g) {
    switch(g) {
        case FORWARD:
            digitalWrite(pin_rev, LOW);
            delay(DIRECTION_SWITCH_DELAY);
            digitalWrite(pin_fwd, HIGH);
            break;

        case REVERSE:
            digitalWrite(pin_rev, HIGH);
            delay(DIRECTION_SWITCH_DELAY);
            digitalWrite(pin_fwd, LOW);
            break;

        case DISABLED:
            digitalWrite(pin_rev, LOW);
            digitalWrite(pin_fwd, LOW);
            break;
    }
}

void Motor::set_speed(uint8_t speed) {
    analogWrite(pin_pwm, speed);
}

void Motor::stop() {
    set_speed(0);
    set_direction(DISABLED);
}

void Motor::initialize() {
    pinMode(pin_fwd, OUTPUT);
    digitalWrite(pin_fwd, LOW);
    pinMode(pin_rev, OUTPUT);
    digitalWrite(pin_rev, LOW);
    pinMode(pin_pwm, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(pin_interrupt), bindArgGateThisAllocate(&Motor::handle_encoder, this), RISING);
    analogWrite(pin_pwm, 0);
}
