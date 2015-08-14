#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "libfahw.h"

#define LED_BLINK_TIMES 10

void ledHandler(int signNum)
{
    int i = 0;
    if (signNum == SIGINT) {
        for (i=1; i<=4; i++) {
            setLedState(LED1, LED_OFF);
            printf("Turn off LED%d\n", i);
        }
    }
    exit(0);
}

int main(int argc, char ** argv)
{
    int i = 0;
    int j = 0;
    signal(SIGINT, ledHandler);

    printf("LED blink %d times\n", LED_BLINK_TIMES);
    for (i = 0; i < LED_BLINK_TIMES; i++) {
        for (j = 0; j<4; j++) {
            setLedState(LED1+j, LED_ON);
            printf("LED%d=%d\n", j+1, getLedState(LED1+j));

        }
             
        sleep(1);
        for (j = 0; j<4; j++) {
            setLedState(LED1+j, LED_OFF);
            printf("LED%d=%d\n", j+1, getLedState(LED1+j));

        }
        sleep(1);
    }
    return 0;
}
