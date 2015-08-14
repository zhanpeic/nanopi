#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>
#include "libfahw.h"

#define BUFF_SIZE 64

int main(int argc, char ** argv)
{
	int devFD = -1;
	int speed = 115200;
	int dataBits = 8;
	int stopBits = 1;
	int ret = -1;
	char *devName = "/dev/ttySAC2";
	char readBuf[BUFF_SIZE];
	char writeBuf[BUFF_SIZE] = "Hi, I am NanoPC T1";

	if (argc != 2) {
		printf("Using default serial:%s\n", devName);
	} else {
		devName =  argv[1];
		printf("Using serial:%s\n", devName);
	}

	devFD = openSerialPort(devName, speed, dataBits, stopBits);
	if (devFD == -1) {
		printf("Fail to open Serial device.\n");
		return -1;
	}

	ret = writeHW(devFD, writeBuf, strlen(writeBuf));
	if (ret <= 0) {
		printf("Fail to send data:%s\n", writeBuf);
		return -1;
	}
	printf("Send %d data:%s\n", ret, writeBuf);

	int secWait = 3;
	int usecWait = 0;
	printf("Waiting data for 3s\n");
	while(1) {
		memset(readBuf, 0, sizeof(readBuf));
		if (selectHW(devFD, secWait, usecWait) == 1) {
			int retSize = readHW(devFD, readBuf, BUFF_SIZE);
			if (retSize > 0) {
				printf("Read from arduino: %s\n", readBuf);
			}
		} else {
		    printf("Get nothing from arduino\n");
			break;
		}
	}
	return 0;
}
