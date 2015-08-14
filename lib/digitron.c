#include "common.h"
#include "libfahw-gpio.h"
#include "libfahw-digitron.h"

static int CK = -1;
static int LD = -1; 
static int DI = -1;

static unsigned char  digitronCharMap[] = {
      // 0     1    2    3    4    5    6    7    8    9    A    b    C    d    E    F    -  .
        0xEB,0x41,0xB3,0xBA,0x78,0xDA,0xDB,0xA8,0xFB,0xF8,0xF9,0x5B,0x13,0x3B,0xD3,0xD1,0x10,0x04
};

static void LEDOutput(unsigned char c)           
{   
    unsigned char i;
    for (i=8; i>=1; i--)
    {
        if (c&0x80) {
            setGPIOValue(DI, GPIO_HIGH);
        } else { 
            setGPIOValue(DI, GPIO_LOW);
        }
        c<<=1;
        setGPIOValue(CK, GPIO_LOW);
        setGPIOValue(CK, GPIO_HIGH);
    }
}

EXPORT void digitronDeInit(void)                       
{
    unexportGPIOPin(CK);
    unexportGPIOPin(LD);
    unexportGPIOPin(DI);
    CK = LD = DI = -1;
}

EXPORT int digitronDispChar(int pos, int number)                    
{
    clearLastError();
    if (pos < 1 || pos > 4) {
        setLastError("Unsupported digitron position");
        return -1;
    } 
    if (number < 0 || number > 9) {
        setLastError("Unsupported digitron number");
        return -1;
    } 

    LEDOutput(1 << (pos+3));     
    LEDOutput(digitronCharMap[number]);      

    setGPIOValue(LD, GPIO_LOW);
    setGPIOValue(LD, GPIO_HIGH);
    return 0;
}

EXPORT int digitronInit(int CKPin, int LDPin, int DIPin)               
{
    CK = CKPin;
    LD = LDPin;
    DI = DIPin;
    
    int ret = 0;
    if (exportGPIOPin(CK) == -1) {  
        return -1;
    }

    if (setGPIODirection(CK, GPIO_OUT) == -1) {
        ret = -1;
    }
    if (exportGPIOPin(LD) == -1) {
        unexportGPIOPin(CK);
        return -1;
    }

    if (setGPIODirection(LD, GPIO_OUT) == -1) {
        ret = -1;
    }

    if (exportGPIOPin(DI) == -1) {
        unexportGPIOPin(CK);
        unexportGPIOPin(LD);
        return -1;
    }

    if (setGPIODirection(DI, GPIO_OUT) == -1) {
        ret = -1;
    }

    return ret;
}   
