#ifndef __FRIENDLYARM_HARDWARE_MAX7219_H__
#define __FRIENDLYARM_HARDWARE_MAX7219_H__

#define  ARRAY_SIZE(a)               (sizeof(a) / sizeof((a)[0]))

int MAX7219DispChar(int devFD, unsigned char c);
int MAX7219Init();
int MAX7219CleanScreen(int devFD);
void MAX7219DeInit(int devFD);

#endif
