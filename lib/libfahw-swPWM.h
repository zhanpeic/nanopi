#ifndef __FRIENDLYARM_HARDWARE_SWPWM_H__
#define __FRIENDLYARM_HARDWARE_SWPWM_H__

// buzzer
#define BUZZER_PERIOD_MS               (1)                       // 1ms
#define BUZZER_HZ                      (1000/BUZZER_PERIOD_MS)   // 1KHZ

enum PWMDevice {
    PWM4SERVO = 0,
    PWM4BUZZER = 1,
    PWM4L298N = 2,
};

int PWMOutput(int pin, int freq, float duty, int periodCount, enum PWMDevice device);

#endif
