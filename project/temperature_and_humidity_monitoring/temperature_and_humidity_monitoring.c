#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "common.h"
#include "libfahw.h"

#define LCD_LENGTH 16 
#define SET_TEMP   37000   
                  
int DHT11pin = GPIO_PIN1;
int LEDpin = GPIO_PIN2;
int BUZZERpin = PWM_PIN1;

int devFD_LCD;
int devFD_DHT11;

int pwm_HZ = 1000;
int pwm_duty = 500;

int stop = 0;
void Stop(int signo) {
	stop = 1;
}

int THmonitoring_init() {
	//LED	
	if ((exportGPIOPin(LEDpin)) == -1) {   
	        printf("exportGPIOPin(%d) failed\n", LEDpin);
		return -1;
	}
        if ((setGPIODirection(LEDpin, GPIO_OUT)) == -1) {
        	printf("setGPIODirection(%d) failed\n", LEDpin);
		return -1;
    	}
	//LCD
        if ((devFD_LCD = LCD1602Init()) == -1) {
        	printf("Fail to init LCD1602\n");
        	return -1;
        }
	if (LCD1602Clear(devFD_LCD) == -1) {
		printf("Fail to Clear\n");
		return -1;
	}
	//dht11
	if ((devFD_DHT11 = dht11Init(DHT11pin)) == -1) {
        	printf("Fail to init dht11\n");
        	return -1;
        }
	return 0;
}

void THmonitoring_deinit() {
	PWMStop(BUZZERpin);
	unexportGPIOPin(LEDpin);	
	LCD1602DeInit(devFD_LCD);
	dht11DeInit(devFD_DHT11);
}

int THmonitoring_alart() {
	if(setGPIOValue(LEDpin, GPIO_HIGH) == -1) {
		printf("setGPIOValue(%d) failed\n", LEDpin);
		return -1;
	}
	if(PWMPlay(BUZZERpin, pwm_HZ, pwm_duty) == -1) {
		printf("Fail to output PWM\n");
	        return -1;
	}
	return 0;
}

int THmonitoring_noalart() {
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
	int dhtTemp = 0;
	int dhtHdty = 0;
	int INT_BUF = 0;
	char* buf = (char *) malloc(LCD_LENGTH);
	memset(buf, 0, LCD_LENGTH);
	char* line1 = " hum: ";
	char* line2 = " temp: ";
	THmonitoring_init();
	if (LCD1602DispLines(devFD_LCD, line1, line2) == -1) {
        	printf("Fail to Display String\n");
    	}
	signal(SIGINT, Stop);
	printf("you can press ctrl+c to stop\n");
	while(!stop) {
		if ((dht11Read(DHT_HUMIDITY, &dhtHdty)) == -1) {
			dhtHdty = 0;
		}
		if ((dht11Read(DHT_TEMP, &dhtTemp)) == -1) {
			dhtTemp = 0;
		}

		if (dhtHdty == 0) {
			sprintf(buf, "%s", "Er");
		} else {
			INT_BUF = dhtHdty / 1000;
			sprintf(buf, "%d", INT_BUF);
		}
		LCD1602DispStr(devFD_LCD, 6, 0, buf);

		if (dhtTemp == 0) {
			sprintf(buf, "%s", "Er");
		} else {
			INT_BUF = dhtTemp / 1000;
			sprintf(buf, "%d", INT_BUF);
		}
		LCD1602DispStr(devFD_LCD, 7, 1, buf);

		if (dhtTemp >= SET_TEMP) {
			 if (THmonitoring_alart() != 0) {
				printf("fail to alart!\n");
				break;
			 }
		}

		sleep(1);
		THmonitoring_noalart();
		sleep(1);		
	}
	free(buf);
	THmonitoring_deinit();
	return 0;
}
















