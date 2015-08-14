#ifndef __FRIENDLYARM_HARDWARE_74HC_H__
#define __FRIENDLYARM_HARDWARE_74HC_H__

int MatrixLedInit(int sclkPin, int rclkPin, int dioPin);
void MatrixLedCleanScreen();
int MatrixLedDispChar(unsigned char c);
void MatrixLedDeInit(void);

#endif
