#include <stdio.h>
#include <unistd.h>
#include "libfahw.h"

int main(int argc, char ** argv) 
{   
    int redPin = nanopi_GPIO_GPF1;
    int greenPin = nanopi_GPIO_GPF2; 
    int bluePin = nanopi_GPIO_GPF4;
    
    if (RGBLEDInit(redPin, greenPin, bluePin) == -1) {
        printf("Fail to init RGBLED");
    }
    
    RGBLEDOutput(RED, GPIO_HIGH);
    printf("Display red\n");
    sleep(1);
    
    RGBLEDOutput(GREEN, GPIO_HIGH);
    printf("Display green\n");
    sleep(1);
    
    RGBLEDOutput(BLUE, GPIO_HIGH);
    printf("Display blue\n");
    sleep(1);
    
    RGBLEDDeInit();
    return 0;
}
