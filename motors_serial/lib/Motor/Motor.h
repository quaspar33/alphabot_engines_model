#ifndef LAB3_MOTOR_H
#define LAB3_MOTOR_H

#include "stdint.h"

enum gear {
    FORWARD,
    REVERSE,
    DISABLED
};

class Motor {
private:
    uint8_t pin_fwd;
    uint8_t pin_rev;
    uint8_t pin_pwm;
    uint8_t pin_interrupt;
    int encoder_count;


public:
    Motor(uint8_t fwd_pin, uint8_t rev_pin, uint8_t pwm_pin, uint8_t pin_interupt);

    void set_direction(gear g);
    void set_speed(uint8_t speed);
    void stop();
    void initialize();
    void handle_encoder() { encoder_count++; };
    int get_encoder_count() { return encoder_count; }
    void set_encoder_count(int val) { encoder_count = val; }
    void reset_encoder_count() { encoder_count = 0; }
};

#endif
