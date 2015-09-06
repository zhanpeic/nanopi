#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "libfahw.h"

#define SOUND   0
#define BUTTON  1
static struct sensor sensor_dev[2] = {
	{
		GPIO_PIN1,
                IRQ_TYPE_EDGE_BOTH,
        },
        {
                GPIO_PIN2,
                IRQ_TYPE_EDGE_FALLING,
        }
};

int devFD = -1;

int pwm_HZ = 1000;
int pwm_duty = 500;

int BUZZERpin = PWM_PIN1;
int LEDpin = GPIO_PIN3;

int stop = 0;
void Stop(int signo) {
	stop = 1;
}

int doorbell_init() {
	//sensor init
	if ((devFD = sensorInit(sensor_dev, ARRAY_SIZE(sensor_dev))) == -1) {
	        printf("Fail to init sensor sound\n");
	        return -1;
	}

	//LED init
	if ((exportGPIOPin(LEDpin)) == -1) {   
	        printf("exportGPIOPin(%d) failed\n", LEDpin);
		return -1;
	}
	if ((setGPIODirection(LEDpin, GPIO_OUT)) == -1) {
        	printf("setGPIODirection(%d) failed\n", LEDpin);
		return -1;
	}
	return 0;
}

void doorbell_deinit() {
	sensorDeinit(devFD);
	PWMStop(BUZZERpin);
	unexportGPIOPin(LEDpin);
}

int doorbell_open() {
	if(setGPIOValue(LEDpin, GPIO_HIGH) == -1) {
		printf("setGPIOValue(%d) failed\n", LEDpin);
		return -1;
	}

	if (PWMPlay(BUZZERpin, pwm_HZ, pwm_duty) == -1) {
        	printf("Fail to output PWM\n");
       		return -1;
	}
	return 0;
}

int doorbell_close() {
	if(setGPIOValue(LEDpin, GPIO_LOW) == -1) {
		printf("setGPIOValue(%d) failed\n", LEDpin);
		return -1;
	}
	if(PWMStop(BUZZERpin) == -1) {
		printf("Fail to stop PWM\n");
		return -1;
	}
	return 0;
}

int main(int argc, char ** argv) {
	int sensor_state;
	char value[ARRAY_SIZE(sensor_dev)];
	doorbell_init();
	signal(SIGINT, Stop);
	printf("you can press ctrl+c to stop\n");
	while(!stop) {
		sensor_state = sensorRead(devFD, value, ARRAY_SIZE(sensor_dev));
		if(value[SOUND] || value[BUTTON]) {
			if(doorbell_open() == -1) {
				printf("fail to open doorbell\n");
				return -1;		
			}
			value[SOUND] = 0;
			value[BUTTON] = 0;
			usleep(1000*500);
		}
		if(doorbell_close() == -1) {
			printf("fail to close doorbell\n");
			return -1;
		}
	}
	doorbell_deinit();
	return 0;
}
