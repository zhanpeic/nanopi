#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "libfahw.h"

#define SOIL_READ_TIMES      (10)

static int devFD;
void smokeHandler(int signNum)
{
    if (signNum == SIGINT) {
        printf("Quit reading smoke moisture\n");
        pcf8591DeInit(devFD);
    }
    exit(0);
}

int main(int argc, char ** argv)
{
    int mode = 0x0;
    if ((devFD = pcf8591Init()) == -1) {
        printf("Fail to init pcf8591 AD\n");
        return -1;
    }
    if (pcf8591SetCtrl(devFD, PCF8591_INIT_AD_CONTROL) == -1) {
        printf("Fail to Set pcf8591 control AD\n");
        pcf8591DeInit(devFD);
        return -1;
    }

    int i = 0;
    int data;
    signal(SIGINT, smokeHandler);
    for (i=0; i<SOIL_READ_TIMES; i++) {
        data = pcf8591Read(devFD, mode, PCF8591_AIN_CHANNEL0);
        printf("smoke moisture:%3d\n", data);
        sleep(1);
    }
    pcf8591DeInit(devFD);
    return 0;
}
