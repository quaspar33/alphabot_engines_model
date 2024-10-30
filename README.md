# alphabot_engines_model

Using linear regression on data gathered from serial port to find relation between PWM and number of impulses.
That later allows us to send to engines number of impulses instead of PWM and make sure that engines go with same speed like so:

float a1 = 0.02;\
float b1 = 39.92;\
float a2 = -0.00;\
float b2 = 85.42;

int calculatePWM(int impulses, float a, float b) {\
    int pwm = a * impulses + b;\
    return constrain(pwm, 0, 255);\
}

void moveForward(int impulses) {\
    int motor1_pwm = calculatePWM(impulses, a1, b1);\
    int motor2_pwm = calculatePWM(impulses, a2, b2);
    
...\
}
