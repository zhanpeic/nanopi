#include <stdio.h>
#include <unistd.h> 
#include "libfahw.h"

int main(int argc, char ** argv)
{   
    int sclkPin = TINY4412_GPIO_PIN1;
    int rclkPin = TINY4412_GPIO_PIN2;
    int dioPin = TINY4412_GPIO_PIN3;

    if (MatrixLedInit(sclkPin, rclkPin, dioPin) == -1) {
        printf("Fail to init matrix LED\n");
    }

    // for(;;)
        MatrixLedDispChar('0');
    
        sleep(3);
    MatrixLedDeInit();
    return 0;
}
