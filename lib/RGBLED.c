#include "libfahw-RGBLED.h"
#include "libfahw-gpio.h"
#include "common.h"

static int RPin = -1;
static int GPin = -1;
static int BPin = -1;

// status can replace by pwm duty
EXPORT int RGBLEDOutput(int color, int status)
{
    if (color != RED && color != GREEN && color != BLUE)
        return -1;

    if(status != GPIO_HIGH && status != GPIO_LOW)
        return -1;

    switch (color) {
    case RED:
        setGPIOValue(RPin, status);
        break;
    case GREEN:
        setGPIOValue(GPin, status);
        break;
    case BLUE:
        setGPIOValue(BPin, status);
        break;
    }
    return 0;
}

EXPORT void RGBLEDDeInit()
{
    setGPIOValue(RPin, GPIO_LOW);
    setGPIOValue(GPin, GPIO_LOW);
    setGPIOValue(BPin, GPIO_LOW);
    unexportGPIOPin(RPin);
    unexportGPIOPin(GPin);
    unexportGPIOPin(BPin);    
}

EXPORT int RGBLEDInit(int redPin, int greenPin, int bluePin)
{
    int ret = 0;
    RPin = redPin;
    GPin = greenPin;
    BPin = bluePin;
    if ( exportGPIOPin(RPin) == -1) {   
        ret = -1;
    }
    if ( setGPIODirection(RPin, GPIO_OUT) == -1) {
        ret = -1;
    }
    if ( exportGPIOPin(GPin) == -1) {
        ret = -1;
    }
    if ( setGPIODirection(GPin, GPIO_OUT) == -1) {
        ret = -1;
    }
    if ( exportGPIOPin(BPin) == -1) {  
        ret = -1;
    }
    if ( setGPIODirection(BPin, GPIO_OUT) == -1) {
        ret = -1;
    }    
    if(ret == -1) {
        RGBLEDDeInit();
    }
    return 0;
}
