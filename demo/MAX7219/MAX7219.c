#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include "libfahw.h"

int main(int argc, char *argv[])
{
    int ret = 0;
    int devFD;
    int i;
    unsigned char ledString[]= "FRIENDLYARM";
    
    if ((devFD = MAX7219Init()) == -1) {
        printf("Fail to init MAX7219\n");
        return -1;
    }

    for(i = 0; i < sizeof(ledString)-1; i++) {
        printf("%c\n", ledString[i]);
        MAX7219DispChar(devFD, ledString[i]);
        sleep(1);
    }  

    MAX7219DeInit(devFD);
    return ret;
}
