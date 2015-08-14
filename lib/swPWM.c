#include <signal.h>
#include "common.h"
#include "libfahw-gpio.h"
#include "libfahw-swPWM.h"

static int PWMPin = -1; 

void PWMHandler(int signNum)
{
    if (signNum == SIGINT) {
        printf("Quit outputing software PWM\n");
        if(PWMPin != -1) {
            unexportGPIOPin(PWMPin);
        }
    }
    exit(0);
}

EXPORT int PWMOutput(int pin, int freq, float duty, int periodCount, enum PWMDevice device)
{
    clearLastError();
    int ret = 0;
    float adjust = 1;
    PWMPin = pin;
    if (exportGPIOPin(PWMPin) == -1) { 
        return -1;
    }

    if (setGPIODirection(PWMPin, GPIO_OUT) == -1) {
        ret = -1;
    }

    float totalTime = 1000000 / freq;           // 1s = 1000000us
    float highTime = totalTime * duty / 100;
    float lowTime = totalTime * (100-duty) / 100;
    switch (device) {
    case PWM4SERVO:
        adjust = 1.08;                                
        break;
    case PWM4BUZZER:
        adjust = 1.29;    // for 1KHz
        adjust = 1;
        break;    
    case PWM4L298N:
        adjust = 1;
        break;
    default:
        setLastError("Unsupported PWM device");
        unexportGPIOPin(PWMPin);
        return -1;
    }
    signal(SIGINT, PWMHandler);
    if (periodCount == 0) {
        // will never return
        while(1) {
            setGPIOValue(PWMPin, GPIO_HIGH); 
            usleep(highTime/adjust);       
            setGPIOValue(PWMPin, GPIO_LOW);
            usleep(lowTime/adjust);
        }
    } else {
        while (periodCount) {
            setGPIOValue(PWMPin, GPIO_HIGH); 
            usleep(highTime/adjust);       
            setGPIOValue(PWMPin, GPIO_LOW);
            usleep(lowTime/adjust);
            periodCount--;
        }
    }
    unexportGPIOPin(PWMPin);
    return ret;
}
