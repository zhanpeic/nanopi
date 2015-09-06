#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "common.h"
#include "libfahw.h"

#define LCD_LENGTH 16

int HCSRpin = GPIO_PIN1;
int devFD_LCD = -1;

int HcsrShow_init() {
	if (Hcsr04Init(HCSRpin) == -1) {
		printf("Fail to init hcsr04\n");
	}
        if ((devFD_LCD = LCD1602Init()) == -1) {
        	printf("Fail to init LCD1602\n");
        	return -1;
        }
	if (LCD1602Clear(devFD_LCD) == -1) {
		printf("Fail to Clear\n");
		return -1;
	}
	return 0;
}

void HcsrShow_deinit() {
	Hcsr04DeInit();
	LCD1602DeInit(devFD_LCD);
}

int main(int argc, char ** argv) {
	int distance = -1;
	char *STR = "distance is :";
	char *ERR1 = "  Faid to get";
	char *ERR2 = "Please try again";
	char* BUF = (char *) malloc(LCD_LENGTH);
	memset(BUF, 0, LCD_LENGTH);

	HcsrShow_init();

	if ((Hcsr04Read(&distance)==0 && distance == -1) || distance == 0) {
		LCD1602DispLines(devFD_LCD, ERR1, ERR2);
	} else {
		LCD1602DispStr(devFD_LCD, 0, 0, STR);
		sprintf(BUF, "%d cm", distance);
		LCD1602DispStr(devFD_LCD, 6, 1, BUF);
	}
	
	free(BUF);
	HcsrShow_deinit();
	return 0;
}


















