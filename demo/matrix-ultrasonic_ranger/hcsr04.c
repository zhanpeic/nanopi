#include <stdio.h>
#include <unistd.h>
#include "libfahw.h"

int main(int argc, char ** argv)
{
    int distance = -1;
    
    int echoPin = nanopi_GPIO_GPF1;
    //int triggerPin = nanopi_GPIO_GPF2;
    
    //if (Hcsr04Init(echoPin, triggerPin) == -1) {
    if (Hcsr04Init(echoPin) == -1) {
        printf("Fail to init hcsr04\n");
    }
    
    if (Hcsr04Read(&distance)==0 && distance != -1) {
        printf("Get distance: %3d cm\n", distance);
    } else {
        printf("Faid to get distance\n");
    }
    Hcsr04DeInit();
    return 0;
}
