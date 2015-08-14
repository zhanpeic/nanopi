#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "libfahw.h"

// only first 128 byte can be read & write,
// last 128 byte can only be read.
#define EEPROM_SIZE     (128)
#define EEPROM_ADDRESS  (0x50)
#define EEPROM_PATH     "/dev/i2c-0"     

int main(int argc, char ** argv) 
{
    int devFD = -1;
    int ret = -1;

    devFD = openHW(EEPROM_PATH, O_RDWR);
    if (devFD < 0) {
        printf("Fail to open EEPROM\n");
        return ret;
    } else {
        if (setI2CSlave(devFD, EEPROM_ADDRESS) < 0) {
            printf("Fail to set I2C slave");
            closeHW(devFD);
            return ret;
        }
    }

    unsigned char epmData = 0xff;
    int pos;
    int waitMs = 10;
    printf("Writing data to eeprom\n");
    for (pos = 0; pos < EEPROM_SIZE; pos++) {
        if (I2CWriteByteTo(devFD, pos, epmData, waitMs) != 0) {
            printf("I2CWriteByteTo pos=%d data=%x failed\n", pos, epmData);
            break;
        }
        if (pos%8 == 0 && pos != 0) {
            printf("\n");
        }
        printf("%2x ", epmData);
        epmData = epmData-2;
    }
    printf("\n");

    waitMs = 10;
    printf("Reading data from eeprom\n");
    for (pos = 0; pos < EEPROM_SIZE; pos++) {
        ret = I2CReadByteFrom(devFD, pos, waitMs);
        if (ret < 0) {
            printf("I2CReadByteFrom failed\n");
            break;
        } else {
            epmData = (unsigned char) ret;
            if (pos%8 == 0 && pos != 0) {
                printf("\n");
            }
            printf("%2x ", epmData);
        }
    }
    printf("\n");
    closeHW(devFD);
    return ret;
}
