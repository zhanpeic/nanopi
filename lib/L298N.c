#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libfahw-L298N.h"
#include "libfahw-gpio.h"
#include "libfahw-pwm.h"
#include "common.h"

static int ENA = -1;
static int IN1 = -1;
static int IN2 = -1;
static int ENB = -1;
static int IN3 = -1;
static int IN4 = -1;

EXPORT void L298NDeInit()
{
    unexportGPIOPin(IN1);
    unexportGPIOPin(IN2);
    unexportGPIOPin(IN3);
    unexportGPIOPin(IN4);
    ENA = IN1 = IN2 = ENB = IN3 = IN4 = -1;
}

EXPORT int L298NInit(int enaPin ,int in1Pin ,int in2Pin, int enbPin, int in3Pin, int in4Pin)
{    
    int ret = 0;   
    ENA = enaPin;
    IN1 = in1Pin;
    IN2 = in2Pin;
    ENB = enbPin;
    IN3 = in3Pin;
    IN4 = in4Pin; 
    if (exportGPIOPin(IN1) == -1) { 
        ret = -1;
    }
    if (exportGPIOPin(IN2) == -1) { 
        ret = -1;
    }
    if (exportGPIOPin(IN3) == -1) { 
        ret = -1;
    }
    if (exportGPIOPin(IN4) == -1) { 
        ret = -1;
    }

    if (setGPIODirection(IN1, GPIO_OUT) == -1) {
        ret = -1;
    }
    if (setGPIODirection(IN2, GPIO_OUT) == -1) {
        ret = -1;
    }
    if (setGPIODirection(IN3, GPIO_OUT) == -1) {
        ret = -1;
    }
    if (setGPIODirection(IN4, GPIO_OUT) == -1) {
        ret = -1;
    }

    if(ret == -1) {
        L298NDeInit();
    }
    return ret;
}

EXPORT int L298NRunMotor(int num, int speed, int direction)
{
    clearLastError();
    int en,firstIn,SecondIn;
    if( speed <0 || speed >1000) {
        setLastError("Unsupported motor speed,range is 0~1000");
        return -1;
    }
    if ( num != 1 && num != 2 ) {
        setLastError("Unsupported motor index,range is 1~2");
        return -1;
    }

    if ( direction != MOTOR_FORWARD && direction != MOTOR_REVERSE ) {
        setLastError("Unsupported motor direction,range is MOTOR_FORWARD/MOTOR_REVERSE");
        return -1;
    }

    if (num ==1) {
        en = ENA;
        firstIn = IN1;
        SecondIn = IN2;
    } else {
        en = ENB;
        firstIn = IN3;
        SecondIn = IN4;
    }

    if (direction == MOTOR_FORWARD) {
        setGPIOValue(firstIn, GPIO_HIGH);
        setGPIOValue(SecondIn, GPIO_LOW);
    } if (direction == MOTOR_REVERSE) {
        setGPIOValue(firstIn, GPIO_LOW);
        setGPIOValue(SecondIn, GPIO_HIGH);
    }
    
    if (PWMPlay(en, L298N_HZ, speed) == -1) {
        printf("Fail to output PWM\n");
    }
    
    return 0;
}
