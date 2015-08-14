# ----------------------------------------------------------------------------
# Makefile for building demo
#
# Copyright 2015 FriendlyARM (http://www.arm9.net/)
#


SUBDIRS				= adxl34x \
					  buzzer \
					  dht11 \
					  ds18b20 \
					  eeprom \
					  gpio \
					  hcsr04 \
					  IRRemote \
					  LCD1602 \
					  onboardLED \
					  MAX7219 \
					  OLED \
					  pcf8591 \
					  PS2rocker \
					  relay \
					  serial \
					  servo \
					  soil \
					  mq2 \
					  digitron \
					  RGBLED \
					  LED \
					  IRCounter \
					  obstacle \
					  track \
					  lean \
					  compass \
					  L298N \
					  sound \
					  arduino \
					  fire

TARGET				= subdirs

PHONY			   += $(TARGET) $(SUBDIRS) %.clean


all: $(TARGET)


subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@


%.clean:
	@(cd $(patsubst %.clean, %, $@) && $(MAKE) clean)

clean distclean: $(patsubst %, %.clean, $(SUBDIRS))


# ----------------------------------------------------------------------------

.PHONY: $(PHONY) install clean distclean

# End of file
# vim: syntax=make

