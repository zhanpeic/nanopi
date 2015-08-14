    
#include "common.h"
//#include "includes/eeprom.h"
#include "includes/i2c-dev.h"

#define I2CFILE "/dev/i2c-0"

EXPORT int openI2CDevice() {
    clearLastError();
	int fd = open(I2CFILE, O_RDWR);
	if (fd < 0) {
        setLastError("Can't open "I2CFILE);
		return -1;
	}

	if (ioctl(fd, I2C_SLAVE, 0x50) < 0) {
		setLastError("Can't ioctl "I2CFILE);
		close(fd);
		return -1;
	}

	return fd;
}

EXPORT int writeByteDataToI2C(int fd, int pos, unsigned char byteData) {
    clearLastError();
	if (pos < 0 || pos >= 256) {
		setLastError("Wrong pos, must be 0~255");
		return -1;
	}
	if (i2c_smbus_write_byte_data(fd, (unsigned char)pos, (unsigned char)byteData) < 0) {
        setLastError("i2c_smbus_write_byte_data return error");
		return -1;
	}
	usleep(1000*10);

	return 0;
}


EXPORT int readByteDataFromI2C(int fd, int pos) {
    clearLastError();
	if (pos < 0 || pos >= 256) {
		setLastError("Wrong pos, must be 0~255");
		return -1;
	}

	ioctl(fd, BLKFLSBUF); // clear kernel read buffer
	if (i2c_smbus_write_byte(fd, (unsigned char)pos) < 0) {
        setLastError("i2c_smbus_write_byte return error");
		return -1;
	}
	usleep(1000*10);

	return i2c_smbus_read_byte(fd);
}
