#ifndef __FRIENDLYARM_HARDWARE_L298N_H__
#define __FRIENDLYARM_HARDWARE_L298N_H__

#define MOTOR_FORWARD   (1)
#define MOTOR_REVERSE   (2)
#define L298N_HZ        (40000)   // 40KHZ

void L298NDeInit();
int L298NInit(int ena ,int in1 ,int in2, int enb, int in3, int in4);
int L298NRunMotor(int num, int speed, int direction);

#endif
