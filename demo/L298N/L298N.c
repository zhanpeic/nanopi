#include <stdio.h>
#include "libfahw.h"

int main(int argc, char ** argv)
{
    int ENAPin = TINY4412_GPIO_PIN1;
    int IN1Pin = TINY4412_GPIO_PIN2;
    int IN2Pin = TINY4412_GPIO_PIN3;
    int ENBPin = TINY4412_GPIO_PIN4;
    int IN3Pin = TINY4412_GPIO_PIN5;
    int IN4Pin = TINY4412_GPIO_PIN6;
    
    if (L298NInit(ENAPin, IN1Pin ,IN2Pin, ENBPin, IN3Pin, IN4Pin) == -1) {
        printf("Fail to init L298N\n");
        return -1;
    }
    L298NRunMotor(1, 700, MOTOR_FORWARD);
    L298NRunMotor(2, 300, MOTOR_REVERSE);
    L298NDeInit();
    return 0;
}
