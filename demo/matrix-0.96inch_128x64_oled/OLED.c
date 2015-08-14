#include <stdio.h>
#include "libfahw.h"

int display(int x, int y, char* str)
{
    int devFD;
    if ((devFD = OLEDInit(TINY4412_GPIO_PIN1, TINY4412_GPIO_PIN2)) == -1) {
        printf("Fail to init OLED\n");
        return -1;
    }
    // Char bitmap: 8x16
    OLEDDisp8x16Str(devFD, x, y, str);
    OLEDDeInit(devFD);
    return 0;
}

int main(int argc, char *argv[]) {
    display(0, 0, "1234567890");
    display(0, 16, "ABCDEFGHIJK");
    return 0;
}
