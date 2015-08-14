#include "common.h"

#define ADC_SET_CHANNEL		0xc000fa01
#define ADC_SET_ADCTSC		0xc000fa02

EXPORT int readADC() {
    int ret = -1;
    clearLastError();
    int fd = open("/dev/adc", 0);
    if (fd < 0) {
        setLastError("Can't open /dev/adc!");
        return -1;
    }
    char buffer[30] = { 0 };
    int len = read(fd, buffer, sizeof buffer - 1);
    if (len > 0) {
        buffer[len] = '\0';
        sscanf(buffer, "%d", &ret);
    } else {
        setLastError("Can't read adc, read() return %d", len);
    }
    close(fd);
    return ret;
}

EXPORT int readADCWithChannels(int channels[], int values[], int count) {
    clearLastError();
    if(channels == NULL || values == NULL || count == 0){
        setLastError("Invalid channels,values or count!");
        return -1;  
    }

    int fd = open("/dev/adc", 0);
    if (fd < 0) {
        setLastError("Can't open /dev/adc!");
        return -1;
    }

    int i;
    for (i=0; i < count; i++) {
        values[i] = -1;
        if (ioctl(fd, ADC_SET_CHANNEL, channels[i]) < 0) {
            setLastError("Can't set channel for /dev/adc!");
            close(fd);
            return -1;
        }

        char buffer[30] = { 0 };
        int len = read(fd, buffer, sizeof buffer - 1);
        int ret = -1;
        if (len > 0) {
            buffer[len] = '\0';
            sscanf(buffer, "%d", &ret);
            values[i] = ret;	
        } else {
            setLastError("Can't read adc, read() return %d", len);
        }
    }

    close(fd);
    return 0; 
}

EXPORT int readADCWithChannel(int channel) {
    int ret = -1;
    clearLastError();
    int fd = open("/dev/adc", 0);
    if (fd < 0) {
        setLastError("Can't open /dev/adc!");
        return -1;
    }

    if (ioctl(fd, ADC_SET_CHANNEL, channel) < 0) {
        setLastError("Can't set channel for /dev/adc!");
        close(fd);
        return -1;
    }

    char buffer[30] = { 0 };
    int len = read(fd, buffer, sizeof buffer - 1);
    if (len > 0) {
        buffer[len] = '\0';
        sscanf(buffer, "%d", &ret);
    } else {
        setLastError("Can't read adc, read() return %d", len);
    }
    close(fd);
    return ret;
}
