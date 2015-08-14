#if !defined(__EEPROM_H__)
#define __EEPROM_H__

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <errno.h>
#include <string.h>

#include "i2c-dev.h"

class T_EEPROM {
public:
	T_EEPROM();
	virtual ~T_EEPROM();

	bool Write(unsigned int pos, const unsigned char &byte);
	bool Read(unsigned int pos, unsigned char &byte);

	bool IsOk() const;

private:
	int fd;
	int Ok;
};

inline T_EEPROM::T_EEPROM(): fd(-1), Ok(false)
{
	fd = ::open("/dev/i2c/0", O_RDWR);
	if (fd < 0) {
		return;
	}

	if (::ioctl(fd, I2C_SLAVE, 0x50) < 0) {
		return;
	}

	Ok = true;
}

inline T_EEPROM::~T_EEPROM()
{
	::close(fd);
	fd = -1;
}

inline bool T_EEPROM::IsOk() const
{
	return Ok;
}


inline bool T_EEPROM::Write(unsigned pos, const unsigned char &byte)
{
	if (!Ok) {
		return Ok;
	}

	if (pos >= 256) {
		Ok = false;
		return Ok;
	}

	if (i2c_smbus_write_byte_data(fd, (unsigned char)pos, byte) < 0) {
		Ok = false;
		return Ok;
	}
	usleep(10);

	return Ok;
}

inline bool T_EEPROM::Read(unsigned pos, unsigned char &byte)
{
	if (!Ok) {
		return Ok;
	}

	if (pos >= 256) {
		Ok = false;
		return Ok;
	}

	ioctl(fd, BLKFLSBUF); // clear kernel read buffer

	if (i2c_smbus_write_byte(fd, (unsigned char)pos) < 0) {
		Ok = false;
		return Ok;
	}
	usleep(10);

	int r = i2c_smbus_read_byte(fd);
	if (r < 0) {
		Ok = false;
		return Ok;
	}
	byte = (unsigned char)r;

	return Ok;
}

#endif
