一、编译运行
1. 一次性编译库和所有demo		
# cd fa-hardware
# make CROSS_COMPILE=arm-linux-gnueabihf clean
# make CROSS_COMPILE=arm-linux-gnueabihf

2. 单独编译库
# cd fa-hardware/lib
# make CROSS_COMPILE=arm-linux-gnueabihf clean
# make CROSS_COMPILE=arm-linux-gnueabihf

3. 单独编译demo
# cd fa-hardware/demo/LED
# make clean
# make 

4. 拷贝程序到开发板
scp LCD1602 root@192.168.1.104:/root			// 拷贝测试程序到开发板
scp *.so root@192.168.1.104:/lib 			// 拷贝库文件到开发板


二、GPIO
(1) 可用的GPIO
// Tiny4412
#define TINY4412_GPIO_PIN1      (219)
#define TINY4412_GPIO_PIN2      (220) 
#define TINY4412_GPIO_PIN3      (221) 
#define TINY4412_GPIO_PIN4      (222)
#define TINY4412_GPIO_PIN5      (20)
#define TINY4412_GPIO_PIN6      (21)
#define TINY4412_GPIO_PIN7      (22)
#define TINY4412_GPIO_PIN8      (23) 
#define TINY4412_GPIO_PIN9      (199) 
#define TINY4412_GPIO_PIN10     (206)
#define TINY4412_PWM0           (37)
#define TINY4412_PWM1           (38)

(2) 在sys/class/gpio下操作GPIO引脚
# cd /sys/class/gpio 
# for i in gpiochip* ; do echo `cat $i/label`: `cat $i/base` ; done
GPA0: 0
GPF2: 105
GPF3: 114
GPJ0: 121
GPJ1: 130
GPK0: 136
GPK1: 144
GPK2: 152
GPB: 16
GPK3: 160
GPL0: 168
GPL1: 177
GPL2: 181
GPX0: 190
GPX1: 199
GPX2: 208
GPX3: 217
GPY0: 226
GPY1: 233
GPY2: 238
GPY3: 245
GPC0: 25
GPY4: 254
GPY5: 263
GPY6: 272
GPZ: 281
GPC1: 31
GPD0: 37
GPD1: 42
GPM0: 47
GPM1: 56
GPM2: 64
GPM3: 70
GPM4: 79
GPF0: 87
GPA1: 9
GPF1: 96

(3) lib
fa-hardware/lib/gpio.c

(4) demo
fa-hardware/demo/gpio/gpio.c

(5) 测试效果
在t1上能将pin1-8输出为高或者低，也能读取到pin9-15的引脚值。

(6) 适配Tiny4412
ok


三、eeprom demo
(1) 访问接口
/dev/i2c-0

(2) driver
只是在应用层操作I2C接口

(2) lib
无

(3) demo
fa-hardware/demo/eeprom/eeprom.c

(5) 测试结果
通过i2c接口，能正常读写前128byte数据。

(6) 适配Tiny4412
ok


四、18b20 demo
(1) 访问接口
gpio引脚：TINY4412_GPIO_PIN1，可用引脚(1～10)

# cd /sys/devices/w1_bus_master/28-*/w1_slave
# cat w1_slave

(2) lib
/fa-hardware/lib/w1.c

(3) demo
fa-hardware/demo/ds18b20/ds18b20.c

(4) 测试结果
可以读到温度值。




五、板载LED
(1) 访问接口
# cd /sys/class/leds/led1/
# cat brightness
# echo 1 > brightness

(2) demo
fa-hardware/demo/led/led.c

(3) 测试结果
LED1 & LED2能正常闪烁

(4) 适配Tiny4412
ok



七、温湿度传感器dht11
(1) 访问接口
硬件：TINY4412_GPIO_PIN1, 必须使用中断引脚，可用引脚(1、2、3、4、9、10)
# cd /sys/devices/platform/dht11/iio:device0
# cat in_humidityrelative_input 	// 湿度
# cat in_temp_input	// 温度

(2) driver
/drivers/iio/humidity/dht11.c

(3) lib
fa-hardware/lib/iio.c

(4) demo
fa-hardware/demo/dht11/dht11.c

(5) 补充
 1.湿度的读取文件改为in_humidityrelative_input;
 2.内核驱动文件主机输出高电平后得把总线拉高
         ret = gpio_direction_output(dht11->gpio, 0);
            if (ret)
               goto err;
         msleep(DHT11_START_TRANSMISSION);
         ret = gpio_direction_output(dht11->gpio, 1);
	



八、红外IR
(1) 访问接口
G: 地
V: 5V
S: PIN10, 只支持pin10

input接口：/dev/input/event2



(2) 下载映射表：
apt-get install ir-keytable		// 可能会下载不了
dpkg -i ir-keytable_0.8.9-4_armhf.deb
ir-keytable -w nanopc_rc01		// 见编码表写给驱动

(3) 测试结果
./getevent -l				// 获取输入事件
./ir					    // 获取输入事件

(4) lib
无

(5) demo
fa-hardware/demo/IRRemote/IRRemote

(6) 适配Tiny4412
ok



九、继电器
(1) 访问接口
gpio引脚：TINY4412_GPIO_PIN1

(2) demo
fa-hardware/demo/relay/relay.c

(3) 测试结果
ok

(4) 适配Tiny4412
ok



十、LCD1602
(0) 功能
显示屏

(1) 访问接口
硬件连接：
vcc: 5V 
gnd: 地
sda: i2c sda
scl: i2c scl	

i2c接口：
/dev/i2c-0
通过i2c接口访问芯片pcf8574，再由pcf8574去控制LCD1602

(2) driver
并没有使用内核的驱动Gpio-pcf857x.c，而是在应用层使用i2c接口操作pcf8574;
优点是对内核的依赖会小一点，缺点的自己写的库功能会弱一点；

(3) lib
fa-hardware/lib/pcf8574.c

(4) demo
fa-hardware/demo/LCD1602/LCD1602.c

(5) 测试结果
# ./LCD1602 ABC 0 1
能在0、1行显示16个字符，默认在(0, 0)显示friendlyarm

(6) 适配Tiny4412
ok




十一、PCF8591
(0) 功能
数模转换和模数转换

(1) 访问接口
硬件连接：
vcc: 5v
gnd: 地
sda: i2c sda
scl: i2c scl

(2) driver
并没有使用内核的驱动pcf8591.c，而是在应用层使用i2c接口操作pcf8591。
内核的驱动并被不能实时的读到模拟值；

(3) lib
fa-hardware/lib/pcf8591.c

(4) demo
fa-hardware/demo/pcf8591/pcf8591.c

(5) bug
未支持DA功能

(6) 适配Tiny4412
ok



十二、MAX7219
(0) 功能
LED点阵

(2) 访问接口
硬件连接：
vcc: vcc
gnd: gnd
din: spi mosi
cs:  spics
sclk: spiclk

另一端的引脚不要有任何短接

spi接口：
/dev/spidev0.0

(3) lib
fa-hardware/lib/MAX7219.c

(4) demo
fa-hardware/demo/MAX7219/MAX7219.c

(5) 适配Tiny4412
在NanoPC正常，Tiny4412上不行




十三、摇杆模块
(1) 访问接口
参考十一章节先将pcf8591接好，然后pcf8591接ps2 rocker：
gnd:
5v:
vrx: pcf8591 ain0
vry: pcf8591 ain1
sw : pcf8591 ain2

(2) lib
fa-hardware/lib/pcf8591.c

(3) demo
fa-hardware/demo/PS2rocker/PS2rocker.c

(4) 适配Tiny4412
ok



十四、OLED
(1) 功能
显示屏

(2) 访问接口
引脚连接：
GND:  gnd
VCC:  vcc
CLK： spiclk
MOSI：spi mosi
RES： gpio190，复位引脚, T1_GPIO_SHIELD_PIN1
DC：  gpio192，数据命令选择引脚, T1_GPIO_SHIELD_PIN2
CS：  spics

spi接口：
/dev/spidev0.0

(3) lib
fa-hardware/lib/OLED.c

(4) demo
fa-hardware/demo/OLED/OLED.c

(5) 适配Tiny4412
ok



十五、舵机
(1) 功能
旋转角度0-180，不能大于180度

(2) 访问接口
引脚连接：
PWM0

红线：信号
棕线：地
红线：5V

(3) lib
fa-hardware/lib/pwm.c

(4) demo
fa-hardware/demo/servo/servo.c

(5) 适配Tiny4412
ok




十六、蜂鸣器
(1) 访问接口
引脚连接：
gpio190，模拟PWM，T1_GPIO_SHIELD_PIN1

(2) lib
fa-hardware/lib/pwm.c

(3) demo
fa-hardware/demo/buzzer/buzzer.c

(4) 适配Tiny4412
ok




十七、HC-SR04
(1) 功能
超声波测距

(2) 访问接口
引脚连接：
vcc:
gnd:
trig: PIN1
echo: PIN2

(3) lib
fa-hardware/lib/iio.c

(4) demo
fa-hardware/demo/hcsr04/hcsr04.c

(5) 适配Tiny4412
ok



十八、土壤湿度传感器
(1) 功能

(2) 访问接口
vcc:
gnd:
ao: pcf8591 ain0

(3) lib
fa-hardware/lib/pcf8591.c

(4) demo
fa-hardware/demo/soil/soil.c
 
(5) 适配Tiny4412
ok




二十、mq2
(1) 功能
烟雾传感器

(2) 访问接口
引脚连接：
vcc:
gnd:
ao: pcf8591 ain0

(3) lib
fa-hardware/lib/pcf8591.c

(4) demo
fa-hardware/demo/mq2/mq2.c

(5) 适配Tiny4412
ok



二十一、数码管
(1) 访问接口
引脚连接：
gnd:
vcc: 
sclk: T1_GPIO_SHIELD_PIN1 
rclk: T1_GPIO_SHIELD_PIN2
dio:  T1_GPIO_SHIELD_PIN3

(2) lib
fa-hardware/lib/digitron.c

(3) demo
fa-hardware/demo/digitron/digitron.c

(4) 适配Tiny4412
ok




二十二、adx134x
(1) 功能
重力加速度
http://www.analog.com/cn/products/mems/mems-accelerometers/adxl345.html#product-overview

(2) 访问接口
引脚连接：
int2：不用接
int1: 不用接
cs:   接高
scl:  i2c SCL
sda:  i2c SDA
sdo:  接高，用来决定slave address
5v:
gnd:

使用内核驱动：
./bus/i2c/drivers/adxl34x

(3) lib
fa-hardware/lib/adx134x.c

(4) demo
fa-hardware/demo/adx134x/adx134x.c

(5) 适配Tiny4412
ok



二十三、RGBLED
(1) 访问接口
引脚连接：
red:  PIN1 
gree: PIN2
blue: PIN3

(2) lib
fa-hardware/lib/RGBLED.c


(3) demo
fa-hardware/demo/RGBLED/RGBLED.c

(4) 适配Tiny4412
ok




二十四、外接LED
(1) 访问接口
V:
G:
S: PIN1

(2) lib
fa-hardware/lib/LED.c

(3) demo
fa-hardware/demo/LED/LED.c

(4) 适配Tiny4412
ok




二十五、外接按键
(1) 访问接口
V:
G:
S: PIN1

(2) driver
tiny4412_sensor.c，支持所有只使用1个GPIO中断的传感器；

(3) lib
fa-hardware/lib/GPIOSensor.c

(4) demo
fa-hardware/demo/button/button.c

(5) 适配Tiny4412
ok




二十六、 红外计数器
(1) 访问接口
V:
G:
S: PIN1

(2) driver
tiny4412_sensor.c，支持所有只使用1个GPIO中断的传感器；

(3) lib
fa-hardware/lib/GPIOSensor.c

(4) demo
fa-hardware/demo/IRCounter/IRCounter.c

(5) 适配Tiny4412
ok




二十七、红外避障
(1) 访问接口
V:
G:
S: PIN1

(2) driver
tiny4412_sensor.c，支持所有只使用1个GPIO中断的传感器；

(3) lib
fa-hardware/lib/GPIOSensor.c

(4) demo
fa-hardware/demo/obstacle/obstacle.c




二十八、红外寻迹
(1) 访问接口
V:
G:
S:PIN1

(2) driver
tiny4412_sensor.c，支持所有只使用1个GPIO中断的传感器；

(3) lib
fa-hardware/lib/GPIOSensor.c

(4) demo
fa-hardware/demo/track/track.c

(5) 适配Tiny4412
ok




二十九、倾斜模块
(1) 访问接口
V:
G:
S:PIN1

(2) driver
tiny4412_sensor.c，支持所有只使用1个GPIO中断的传感器；

(3) lib
fa-hardware/lib/GPIOSensor.c

(4) demo
fa-hardware/demo/lean/lean.c

(5) 适配Tiny4412
ok




三十：指南针
(1) 访问接口
V:
G: 
SCL: i2c0 scl
SDA: i2c0 sda
DRDY: 不用接，用于检测指南针状态变化用的

使用i2c0

(2) lib
fa-hardware/lib/hmc5883.c

(3) demo
fa-hardware/demo/compass/compass.c

(4) 适配Tiny4412
ok




三十一、L298N
(1) 功能
用于驱动2路马达

(2) 访问接口
ENA：PIN1
IN1：PIN2
IN2：PIN3
IN3：PIN4
IN4：PIN5
ENB：PIN6
12v:
GND:
必须是使用12V电源才能驱动马达；
有两路输出，ENA、IN1、IN2控制第1路，ENB、IN3、IN4控制第2路；

(3) lib
fa-hardware/lib/L298N.c
fa-hardware/lib/pwm.c

(4) demo
fa-hardware/demo/L298N/L298N.c

(5) 适配Tiny4412
ok




三十二、声音传感器
(1) 功能
检测声音

(2) 访问接口
V:
G:
S:PIN1

(3) driver
tiny4412_sensor.c，支持所有只使用1个GPIO中断的传感器；

(4) lib
fa-hardware/lib/GPIOSensor.c

(5) demo
fa-hardware/demo/sound/sound.c

(6) bug
没有反应




三十三、烟雾传感器
(1) 功能
检测烟雾

(2) 访问接口
gnd:
V:
AO:pcf8591 ain0

(3) lib
fa-hardware/lib/pcf8591.c

(4) demo
fa-hardware/demo/smoke/smoke.c
 
(5) 适配Tiny4412
ok




三十四、arduino nano
(1) 功能
NanoPC T1和arduino nano进行串口通讯

(2) 访问接口
用arduino nano的TX和RX 接 NanoPC T1的UART2的RX和TX
设备节点为/dev/ttySAC2

(3) lib
fa-hardware/lib/serialport.c

(4) demo
fa-hardware/demo/arduino/arduino.c

(5) 适配Tiny4412
ok




三十五、串口
(1) 功能
NanoPC T1和arduino nano进行串口通讯

(2) 访问接口
短接NanoPC T1的UART2的TX和RX
设备节点为/dev/ttySAC2

(3) lib
fa-hardware/lib/serialport.c

(4) demo
fa-hardware/demo/serial/serial.c

(5) 适配Tiny4412
ok


三十六、火焰传感器
(1) 功能
检测火焰

(2) 访问接口
V:
G:
S:PIN1

(3) lib
fa-hardware/lib/GPIOSensor.c

(4) demo
fa-hardware/demo/fire/fire.c

(5) 适配Tiny4412
ok


三十七、74hc595
(1) 功能
LED点阵

(2) 访问接口
连接模块右边的引脚：
GND：
5V：
LD：
CK：
DI：








