#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "libfahw.h"

static struct sensor IRCounter[] = {
        {
                TINY4412_GPIO_PIN1,
                IRQ_TYPE_EDGE_FALLING,
        }
};
static int devFD = -1;

void IRCounterHandler(int signNum)
{
    if (signNum == SIGINT) {
        printf("Quit counting\n");
    }
    sensorDeinit(devFD);
    exit(0);
}

int main(void)
{
    int i;
    int retSize = -1;
    char value[ARRAY_SIZE(IRCounter)];
    int counter = 0;

    if ((devFD = sensorInit(IRCounter, ARRAY_SIZE(IRCounter))) == -1) {
        printf("Fail to init sensor\n");
        return -1;
    }
    
    signal(SIGINT, IRCounterHandler);
    
    while(1)
    {        
        if (( retSize = sensorRead(devFD, value, ARRAY_SIZE(IRCounter)) ) == -1) {
            printf("Fail to read sensors\n");
        }
        if (retSize > 0) {
            i = 0;
            for(i=0; i<retSize; i++)
            {
                if(value[i] == 1) {
                    counter++;
                    printf("IRCounter:%d\n", counter);
                }
            }
            if(counter == 10) {
                printf("Reach 10 times\n");
                break;
            }
        }
    }
    sensorDeinit(devFD);
    return 0;
}
