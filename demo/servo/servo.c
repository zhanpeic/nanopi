#include <stdio.h>
#include <stdlib.h>
#include "libfahw.h"

#define SERVO_PERIOD_MS               (20)                      // 20ms
#define SERVO_HZ                      (1000/SERVO_PERIOD_MS)    // 50HZ

int parseCmd(int argc, char **argv, int *pin, float *angle)
{
    int num = atoi(argv[1]);
    float ag = (float)atoi(argv[2]);
    
    if (ag<0 || ag>180) {
        return -1;
    }
    switch(num) {
    case 0:
        *pin = TINY4412_PWM0; 
        break;
    case 1:
        *pin = TINY4412_PWM1;
        break;
    default:
        printf("Unsupported pin TINY4412_PWM%d\n", num);
        num = 0;
        *pin = TINY4412_PWM0;
    }
    *angle = ag;
    printf("Using config: pin=PWM%d angle=%.2f\n", num, ag);
    return 0;
}

int main(int argc, char ** argv)
{
    int pin = TINY4412_PWM0;
    float angle;
    float duty;
    
    if (argc == 3) {
        if (parseCmd(argc, argv, &pin, &angle) == -1) {
            return -1;
        }
    } else {
        angle = 90;
        printf("Usage:%s PWM[0~1] angle[0~180]\n", argv[0]);
        printf("Using default config: pin=PWM0 angle=%.2f\n", angle);
    }    
        
    // 0度：0.5ms，45度：1ms，90度：1.5ms，135度：2.0ms，180度：2.5ms
    duty = 0.5 + (angle/45) * 0.5;
    duty = duty / SERVO_PERIOD_MS * 1000;            // 千分比
    
    if (PWMPlay(pin, SERVO_HZ, duty) == -1) {
        printf("Fail to output PWM\n");
    }    
    return 0;
}
