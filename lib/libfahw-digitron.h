#ifndef __FRIENDLYARM_HARDWARE_DIGITRON_H__
#define __FRIENDLYARM_HARDWARE_DIGITRON_H__

void digitronDeInit(void);
int digitronDispChar(int pos, int number);
int digitronInit(int sclk, int rclk, int dio);

#endif
