CROSS_COMPILE ?= arm-linux-
ifeq ($(CROSS_COMPILE),)
$(error "Not set CROSS_COMPILE=";)
endif
AS		= $(CROSS_COMPILE)as
LD		= $(CROSS_COMPILE)ld
CC		= $(CROSS_COMPILE)gcc
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm
STRIP	= $(CROSS_COMPILE)strip
OBJCOPY	= $(CROSS_COMPILE)objcopy
OBJDUMP	= $(CROSS_COMPILE)objdump
RANLIB	= $(CROSS_COMPILE)ranlib

INSTALLPATH=/tmp/libfahw
CFLAGS=-Wall -Os
LDFLAGS=-lpthread
LIB=libfahw.so
SLIB=libfahw.a
CFLAGS+=-fPIC

OBJDIR=.obj
DEPDIR=.deps
LIBSRC=common.c gpio.c i2c.c serialport.c spi.c w1.c led.c pwm.c iio.c adc.c eeprom.c filectl.c pcf8591.c 74hc595.c
LIBSRC+=pcf8574.c MAX7219.c OLED.c swPWM.c digitron.c adxl34x.c RGBLED.c GPIOSensor.c hmc5883.c L298N.c pwm.c
LIBOBJ=$(addprefix $(OBJDIR)/, $(addsuffix .o, $(basename $(LIBSRC))))
DEPS=$(patsubst %.c,$(DEPDIR)/%.Po,$(LIBSRC))


MV=mv

all: $(LIB) $(SLIB)
lib: $(LIB)
slib: $(SLIB)
$(OBJDIR)/%.o: %.c
	@test -d $(DEPDIR) || mkdir -p $(DEPDIR)
	@test -d $(OBJDIR) || mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ $<
	@mv $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
	
-include $(DEPS)
$(LIB): $(LIBOBJ)
	$(CC) $(LDFLAGS) -shared -o $@ $^
$(SLIB): $(LIBOBJ)
	$(AR) rcu $@ $^
	$(RANLIB) $@
install: $(LIB)
	rm -rf $(INSTALLPATH)
	mkdir -p $(INSTALLPATH)/includes
	mkdir -p $(INSTALLPATH)/libs
	cp libfahw*.h $(INSTALLPATH)/includes/
	cp libfahw.so $(INSTALLPATH)/libs/
	cp libfahw.a $(INSTALLPATH)/libs/
clean:
	rm -f $(LIB) $(LIBOBJ) $(SLIB) $(DEPS)
