#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "common.h"
#include "libfahw.h"

//欢乐颂  4/4  250ms [HZ,delay]
unsigned int Music_code[]={659, 250, 659, 250, 698, 250, 784, 250, 
 			784, 250, 698, 250, 659, 250, 587, 250,
 			523, 250, 523, 250, 587, 250, 659, 250,
 			659, 375, 587, 125, 587, 250,   1, 500,
 			659, 250, 659, 250, 698, 250, 784, 250,
 			784, 250, 698, 250, 659, 250, 587, 250,
 			523, 250, 523, 250, 587, 250, 659, 250,
 			587, 375, 523, 125, 523, 250,   1, 500,
 			587, 250, 587, 250, 659, 250, 523, 250,
 			587, 250, 659, 125, 698, 125, 659, 250, 523, 250,
 			523, 250, 587, 250, 392, 250,   1, 500,
 			659, 250, 659, 250, 698, 250, 784, 250,
 			784, 250, 698, 250, 659, 250, 587, 250,
 			523, 250, 523, 250, 587, 250, 659, 250,
 			587, 375, 523, 250, 523, 250,   1, 500};

int BUZZERpin = PWM_PIN1;
int REDpin = GPIO_PIN1;
int GREENpin = GPIO_PIN2;
int BLUEpin = GPIO_PIN3;

int pwm_HZ;

int stop = 0;
void Stop(int signo) {
	stop = 1;
}

int MusicBuzzer_init() {
	if ((exportGPIOPin(REDpin)) == -1) {   
	        printf("exportGPIOPin(%d) failed\n", REDpin);
		return -1;
	}
        if ((setGPIODirection(REDpin, GPIO_OUT)) == -1) {
        	printf("setGPIODirection(%d) failed\n", REDpin);
		return -1;
    	}
	if ((exportGPIOPin(GREENpin)) == -1) {   
	        printf("exportGPIOPin(%d) failed\n", GREENpin);
		return -1;
	}
        if ((setGPIODirection(GREENpin, GPIO_OUT)) == -1) {
        	printf("setGPIODirection(%d) failed\n", GREENpin);
		return -1;
    	}
	if ((exportGPIOPin(BLUEpin)) == -1) {   
	        printf("exportGPIOPin(%d) failed\n", BLUEpin);
		return -1;
	}
        if ((setGPIODirection(BLUEpin, GPIO_OUT)) == -1) {
        	printf("setGPIODirection(%d) failed\n", BLUEpin);
		return -1;
    	}
	return 0;
}

void MusicBuzzer_deinit() {
	unexportGPIOPin(REDpin);
	unexportGPIOPin(GREENpin);
	unexportGPIOPin(BLUEpin);
}

int LEDon() {
	if(setGPIOValue(REDpin, GPIO_HIGH) == -1) {
		printf("setGPIOValue(%d) failed\n", REDpin);
		return -1;
	}
	if(setGPIOValue(GREENpin, GPIO_HIGH) == -1) {
		printf("setGPIOValue(%d) failed\n", GREENpin);
		return -1;
	}
	if(setGPIOValue(BLUEpin, GPIO_HIGH) == -1) {
		printf("setGPIOValue(%d) failed\n", BLUEpin);
		return -1;
	}
	return 0;
}

int LEDoff() {
	if(setGPIOValue(REDpin, GPIO_LOW) == -1) {
		printf("setGPIOValue(%d) failed\n", REDpin);
		return -1;
	}
	if(setGPIOValue(GREENpin, GPIO_LOW) == -1) {
		printf("setGPIOValue(%d) failed\n", GREENpin);
		return -1;
	}
	if(setGPIOValue(BLUEpin, GPIO_LOW) == -1) {
		printf("setGPIOValue(%d) failed\n", BLUEpin);
		return -1;
	}
	return 0;
}

int main(int argc, char ** argv) {
	int state = 0;
	int len = ARRAY_SIZE(Music_code);

	signal(SIGINT, Stop);
	printf("you can press ctrl+c to stop\n");

	MusicBuzzer_init();

	while(!stop) {
		for(state = 0;(state <= len-1) && (!stop);) {
			pwm_HZ = Music_code[state++];
			PWMPlay(BUZZERpin, pwm_HZ, pwm_HZ / 2);
			LEDon();
			usleep(Music_code[state] * 500);
			LEDoff();
			usleep(Music_code[state++] * 500);
			PWMStop(BUZZERpin);
			
		}
		sleep(1);
	}
	
	MusicBuzzer_deinit();
	return 0;
}



















