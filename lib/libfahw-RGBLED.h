#ifndef __FRIENDLYARM_HARDWARE_RGBLED_H__
#define __FRIENDLYARM_HARDWARE_RGBLED_H__

#define RED      (1)
#define GREEN    (2)
#define BLUE     (3)

int RGBLEDOutput(int color, int status);
void RGBLEDDeInit();
int RGBLEDInit(int redPin, int greenPin, int bluePin);

#endif
