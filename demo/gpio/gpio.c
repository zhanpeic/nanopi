#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libfahw.h"

void parseCmd(int argc, char **argv, int *pin)
{
    int num = atoi(argv[1]);
    switch(num) {
    case 1:
        *pin = TINY4412_GPIO_PIN1; 
        break;
    case 2:
        *pin = TINY4412_GPIO_PIN2;
        break;
    case 3:
        *pin = TINY4412_GPIO_PIN3;
        break;
    case 4:
        *pin = TINY4412_GPIO_PIN4;
        break;
    case 5:
        *pin = TINY4412_GPIO_PIN5;
        break;
    case 6:
        *pin = TINY4412_GPIO_PIN6;
        break;
    case 7:
        *pin = TINY4412_GPIO_PIN7;
        break;
    case 8:
        *pin = TINY4412_GPIO_PIN8;
        break;
    case 9:
        *pin = TINY4412_GPIO_PIN9;
        break;
    case 10:
        *pin = TINY4412_GPIO_PIN10;
        break;
    default:
        printf("Unsupported pin TINY4412_GPIO_PIN%d\n", num);
        num = 1;
        *pin = TINY4412_GPIO_PIN1;
    }
    printf("Using pin TINY4412_GPIO_PIN%d\n", num);    
}

int main(int argc, char ** argv) 
{
    int pin = TINY4412_GPIO_PIN1;
    int pinValue = -1;
    int ret = -1;

    if (argc == 2) {
        parseCmd(argc, argv, &pin);
    } else {
        printf("Using default pin TINY4412_GPIO_PIN1\n");
    }

    if ((ret = exportGPIOPin(pin)) != 0) {	
        printf("exportGPIOPin(%d) failed\n", pin);
    }
    if ((ret = setGPIODirection(pin, GPIO_OUT)) != 0) {
        printf("setGPIODirection(%d) failed\n", pin);
    }

    ret = setGPIOValue(pin, GPIO_HIGH);
    if (ret == 0) {
        printf("Set pin value %d\n", GPIO_HIGH);
    } else {
        printf("Set pin failed\n");
    }
    sleep(1);

    ret = setGPIOValue(pin, GPIO_LOW);
    if (ret == 0) {
        printf("Set pin value %d\n", GPIO_LOW);
    } else {
        printf("Set pin failed\n");
    }

    sleep(1);
    if ((ret = setGPIODirection(pin, GPIO_IN)) != 0) {
        printf("setGPIODirection(%d) failed\n", pin);
    }
    pinValue = getGPIOValue(pin);
    if (ret == 0) {
        printf("Get pin value %d\n", pinValue);
    }
    else {
        printf("Get pin value failed\n");
    }
    unexportGPIOPin(pin);
    return 0;
}
