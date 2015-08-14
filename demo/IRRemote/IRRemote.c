#include <linux/input.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "libfahw.h"

#define IR_PATH         "/dev/input/event2"
#define IR_EVENT_TIMES  (20)

void IRHandler(int signNum)
{
    if (signNum == SIGINT) {
        printf("Quit waiting IR event\n");
    }
    exit(0);
}

int main(int argc, char ** argv)
{
    int devFD;
    char *devName = IR_PATH;

    if (argc != 2) {
        printf("Using default IR device:%s\n", devName);
    } else {
        devName =  argv[1];
        printf("Using IR device:%s\n", devName);
    }

    struct input_event evKey;
    devFD = openHW(devName, O_RDWR);
    if (devFD < 0) {
        printf("Fail to open IR device.\n");
        return -1;
    }

    int i = 0;
    int j = 0;
    int retSize = -1;;
    signal(SIGINT, IRHandler);
    printf("Waiting IR event %d times\n", IR_EVENT_TIMES);
    for (i = 0; i < IR_EVENT_TIMES; ) {
        if (selectHW(devFD, 0, 0) == 1) {
            retSize = readHW(devFD, &evKey, sizeof(struct input_event));
            for (j = 0; j < (int) retSize / sizeof(struct input_event); j++) {
                if (evKey.type == EV_KEY) {
                    i++;
                    switch ( evKey.code ) {
                    case KEY_POWER:
                        printf("KEY_POWER:%d\n", evKey.value);
                        break;
                    case KEY_UP:
                        printf("KEY_UP:%d\n", evKey.value);
                        break;
                    case KEY_DOWN:
                        printf("KEY_DOWN:%d\n", evKey.value);
                        break;
                    case KEY_LEFT:
                        printf("KEY_LEFT:%d\n", evKey.value);
                        break;
                    case KEY_RIGHT:
                        printf("KEY_RIGHT:%d\n", evKey.value);
                        break;
                    case KEY_BACK:
                        printf("KEY_BACK:%d\n", evKey.value);
                        break;
                    case KEY_ENTER:
                        printf("KEY_ENTER:%d\n", evKey.value);
                        break;
                    case KEY_HOMEPAGE:
                        printf("KEY_HOMEPAGE:%d\n", evKey.value);
                        break;
                    case KEY_MENU:
                        printf("KEY_MENU:%d\n", evKey.value);
                        break;
                    case KEY_1:
                        printf("KEY_1:%d\n", evKey.value);
                        break;
                    case KEY_2:
                        printf("KEY_2:%d\n", evKey.value);
                        break;
                    case KEY_3:
                        printf("KEY_3:%d\n", evKey.value);
                        break;
                    case KEY_4:
                        printf("KEY_4:%d\n", evKey.value);
                        break;
                    case KEY_5:
                        printf("KEY_5:%d\n", evKey.value);
                        break;
                    case KEY_6:
                        printf("KEY_6:%d\n", evKey.value);
                        break;
                    case KEY_7:
                        printf("KEY_7:%d\n", evKey.value);
                        break;
                    case KEY_8:
                        printf("KEY_8:%d\n", evKey.value);
                        break;
                    case KEY_9:
                        printf("KEY_9:%d\n", evKey.value);
                        break;
                    case KEY_0:
                        printf("KEY_0:%d\n", evKey.value);
                        break;
                    case KEY_VOLUMEDOWN:
                        printf("KEY_VOLUMEDOWN:%d\n", evKey.value);
                        break;
                    case KEY_VOLUMEUP:
                        printf("KEY_VOLUMEUP:%d\n", evKey.value);
                        break;	
                    default: 
                        printf("Unsuppoted IR key\n");
                        break;
                    }
                }
            }
        }
    }

    closeHW(devFD);
    return 0;	
}

