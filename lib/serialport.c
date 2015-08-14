#include "common.h"
#include <errno.h>
#include <termio.h>

#define SERIAL_BUF_SIZE     (64)

static int set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop, char flowCtrl) {
	struct termios newtio, oldtio;
	if (tcgetattr(fd, &oldtio) != 0) {
		setLastError("Fail to tcgetattr");
		return -1;
	}
	bzero(&newtio, sizeof(newtio));
	newtio.c_cflag |= CLOCAL | CREAD;
	newtio.c_cflag &= ~CSIZE;

	switch (nBits) {
	case 5:
		newtio.c_cflag |= CS5;
		break;
	case 6:
		newtio.c_cflag |= CS6;
		break;
	case 7:
		newtio.c_cflag |= CS7;
		break;
	case 8:
		newtio.c_cflag |= CS8;
		break;
	}

	switch (nEvent) {
	// 奇校验
	case 'O':
		newtio.c_cflag |= PARENB;

		newtio.c_cflag |= PARODD;
		// newtio.c_iflag |= (INPCK | ISTRIP);
		newtio.c_iflag |= INPCK;
		break;
		// 偶校验
	case 'E':
		newtio.c_cflag |= PARENB;

		newtio.c_cflag &= ~PARODD;
		// newtio.c_iflag |= (INPCK | ISTRIP);
		newtio.c_iflag |= INPCK;
		break;
		// 无校验
	case 'N':
		newtio.c_cflag &= ~PARENB;
		break;
	default:
		newtio.c_cflag &= ~PARENB;
		break;
	}

	switch (flowCtrl) {
	// 软件
	case 'S':
		newtio.c_iflag |= IXON|IXOFF|IXANY;
		break;
		// 硬件
	case 'H':
		newtio.c_iflag |= CRTSCTS;
		break;
		// 不使用数据流控
	case 'N':
		newtio.c_cflag &= ~CRTSCTS;
		break;
	default:
		newtio.c_cflag &= ~CRTSCTS;
		break;
	}


	if (nSpeed == 1200) {
		cfsetispeed(&newtio, B1200);
		cfsetospeed(&newtio, B1200);
	} else if (nSpeed == 1800) {
		cfsetispeed(&newtio, B1800);
		cfsetospeed(&newtio, B1800);
	} else if (nSpeed == 2400) {
		cfsetispeed(&newtio, B2400);
		cfsetospeed(&newtio, B2400);
	} else if (nSpeed == 4800) {
		cfsetispeed(&newtio, B4800);
		cfsetospeed(&newtio, B4800);
	} else if (nSpeed == 9600) {
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
	} else if (nSpeed == 19200) {
		cfsetispeed(&newtio, B19200);
		cfsetospeed(&newtio, B19200);
	} else if (nSpeed == 38400) {
		cfsetispeed(&newtio, B38400);
		cfsetospeed(&newtio, B38400);
	} else if (nSpeed == 57600) {
		cfsetispeed(&newtio, B57600);
		cfsetospeed(&newtio, B57600);
	} else if (nSpeed == 115200) {
		cfsetispeed(&newtio, B115200);
		cfsetospeed(&newtio, B115200);
	} else if (nSpeed == 230400) {
		cfsetispeed(&newtio, B230400);
		cfsetospeed(&newtio, B230400);
	} else if (nSpeed == 460800) {
		cfsetispeed(&newtio, B460800);
		cfsetospeed(&newtio, B460800);
	} else if (nSpeed == 500000) {
		cfsetispeed(&newtio, B500000);
		cfsetospeed(&newtio, B500000);
	} else if (nSpeed == 576000) {
		cfsetispeed(&newtio, B576000);
		cfsetospeed(&newtio, B576000);
	} else if (nSpeed == 921600) {
		cfsetispeed(&newtio, B921600);
		cfsetospeed(&newtio, B921600);
	} else {
		setLastError("Unsupport baud, using 9600");
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
	}

	if (nStop == 1)
		newtio.c_cflag &= ~CSTOPB;
	else if (nStop == 2)
		newtio.c_cflag |= CSTOPB;
	newtio.c_cc[VTIME] = 1;
	newtio.c_cc[VMIN] = SERIAL_BUF_SIZE;
	tcflush(fd, TCIFLUSH);
	if ((tcsetattr(fd, TCSANOW, &newtio)) != 0) {
		setLastError("Fail to tcsetattr");
		return -1;
	}

	return 0;
}

static int open_port(const char* devName) {
	int fd = open(devName, O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (-1 == fd) {
		setLastError("Fail to open Serial Port(%d)", errno);
		return (-1);
	}

	if (fcntl(fd, F_SETFL, 0) < 0)
		setLastError("Fail to fcntl %s", devName);

	if (isatty(STDIN_FILENO) == 0)
		setLastError("Fail to isatty %s", devName);

	return fd;
}

EXPORT int openSerialPort(
		const char *strDevName, long baud,
		int dataBits, int stopBits) {
	int fd = -1;
	
	clearLastError();
	fd = open_port(strDevName);
	if (fd >= 0) {
		int ret = set_opt(fd, baud, dataBits, 'N', stopBits, 'N');
		if (ret != 0) {
			setLastError("Fail to init SerialPort %s", strDevName);
			close(fd);
			fd = -1;
		}
	}
	return fd;
}

EXPORT int openSerialPortEx(
		const char * strDevName,long baud,
		int dataBits, int stopBits, const char * strParityBit, const char * strFlowCtrl) {
	int fd = -1;
    
    clearLastError();
	fd = open_port(strDevName);

	char pb = 'N';
	if (strlen(strParityBit)>0) {
		pb = strParityBit[0];
	}
	char fc = 'N';
	if (strlen(strFlowCtrl)>0) {
		fc = strFlowCtrl[0];
	}
	if (fd >= 0) {
		int ret = set_opt(fd, baud, dataBits, pb, stopBits, fc);
		if (ret != 0) {
			setLastError("Fail to init SerialPort %s", strDevName);
			close(fd);
			fd = -1;
		}
	}
	return fd;
}
