#ifndef __FRIENDLYARM_HARDWARE_GPIO_H__
#define __FRIENDLYARM_HARDWARE_GPIO_H__

// Direction
#define GPIO_IN                 (1) 
#define GPIO_OUT                (2) 

// Value
#define GPIO_LOW                (0)
#define GPIO_HIGH               (1)

//nanopi
#define nanopi_GPIO_GPF1   (161)
#define nanopi_GPIO_GPF2   (162)
#define nanopi_GPIO_GPF3   (163)
#define nanopi_GPIO_GPF4   (164)
#define nanopi_GPIO_GPF5   (165)
#define nanopi_GPIO_GPE11  (139)
#define nanopi_GPIO_GPE12  (140)
#define nanopi_GPIO_GPE13  (141)
#define nanopi_GPIO_GPB0   (32)
#define nanopi_GPIO_GPB1   (33)
#define nanopi_GPIO_GPB7   (39)
#define nanopi_GPIO_GPB8   (40)
#define nanopi_GPIO_GPG4   (196)
#define nanopi_GPIO_GPG5   (197)
#define nanopi_GPIO_GPG6   (198)
#define nanopi_GPIO_GPG7   (199)
#define nanopi_GPIO_GPG8   (200)
#define nanopi_GPIO_GPG9   (201)
#define nanopi_GPIO_GPG10  (202)
#define nanopi_GPIO_GPG11  (203)
#define nanopi_GPIO_GPL13  (333)
#define nanopi_PWM0        (32)
#define nanopi_PWM1        (33)

int exportGPIOPin(int pin);
int unexportGPIOPin(int pin);

// GPIO_LOW or GPIO_HIGH
int setGPIOValue(int pin, int value);
int getGPIOValue(int pin);

// GPIO_IN or GPIO_OUT
int setGPIODirection(int pin, int direction);
int getGPIODirection(int pin);

#endif
