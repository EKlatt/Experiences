# main.py on ESP 32

# ESP32 quick reference I2C:
# https://docs.micropython.org/en/latest/esp32/quickref.html
# Recommended values for SoftI2C: scl=Pin(22), sda=Pin(21)

# ssd1306 OLED driver, I2C:
# https://randomnerdtutorials.com/micropython-oled-display-esp32-esp8266/
# https://www.engineersgarage.com/micropython-esp8266-esp32-ssd1306/
# Python library for ssd1306:
# https://github.com/adafruit/micropython-adafruit-ssd1306/blob/master/ssd1306.py

# VL53L0X TOF Sensor with ESP32:
# https://www.az-delivery.de/en/blogs/azdelivery-blog-fur-arduino-und-raspberry-pi/digitales-theremin-mit-esp32-in-micropython
# https://www.electronicwings.com/esp32/vl53l0x-sensor-interfacing-with-esp32
# Python library for VL53L0X:
# https://www.grzesina.de/az/theremin/VL53L0X.py
# A def ping(self)-function has been added to vl53l0x.py

# HC-SR04 Ultrasonic Sensor with ESP32:
# https://randomnerdtutorials.com/micropython-hc-sr04-ultrasonic-esp32-esp8266/
# https://esp32io.com/tutorials/esp32-ultrasonic-sensor
# https://github.com/rsc1975/micropython-hcsr04/tree/master
# Python library for HCSR-04:
# https://github.com/rsc1975/micropython-hcsr04/blob/master/hcsr04.py

# UART duplex serial communication
# https://docs.micropython.org/en/latest/library/machine.UART.html#machine.UART
# https://docs.micropython.org/en/latest/esp32/quickref.html#uart-serial-bus

from machine import Pin, SoftI2C, UART
import ssd1306
from vl53l0x import VL53L0X
from hcsr04 import HCSR04
from time import sleep

# ESP32 Pin assignment
# Software I2C bus
i2c = SoftI2C(scl=Pin(22), sda=Pin(21))

# Create a ssd1306 "oled" object
oled = ssd1306.SSD1306_I2C(128, 64, i2c)

# Create a VL53L0X "time of flight" object
sensor_VL53L0X = VL53L0X(i2c)
correction_VL = (-70)

# Create a HCSR04 object
sensor_HCSR04 = HCSR04(trigger_pin=5, echo_pin=18, echo_timeout_us=10000)
correction_HC = (0)

# Create a StartButtonPin object
# physical Pin G32 => GPIO32 = 32
StartButton = 32
StartButtonPin = Pin( StartButton, mode=Pin.IN, pull=Pin.PULL_DOWN)   # pull down resistor enabled

# ------------------------------ code for USART to monitor ---------------------------------
# Create a UART object for EPS32 with UART2; GPIO17: tx=17, GPIO16: rx=16
uart = UART(2, 115200)
uart.write("Wait for 'sendData'\n") # Serial Monitor
print('MicropythonReady')           # REPL
oled.text('Press button', 0, 0)
oled.show()

# Wait for Python-Monitor and the start-message: 'sendData' or StartButton
while True:
    if StartButtonPin.value():
        break
    
    if uart.any() > 0:
        strMsg = uart.read()
        strMsg = strMsg.decode('utf-8')
        print(strMsg)               # REPL
        if 'sendData' in strMsg:
            break
        
print('Data will be send.')          # REPL
uart.write(b'Data will be send.\n')  # Serial Monitor
# ------------------------------ end of code for USART to monitor --------------------------
# ------------------------------ code for oled display -------------------------------------
def clearLine(_line):                                     # for a 128x64 oled-monochrome-display with 6 rows (0 to 5)
    oled.framebuf.fill_rect(0, 11 * _line, 128, 11, 0)    # width = 128, hight = 11
    
oled.fill(0)
oled.invert(0)
oled.text('EBW', 0, 0)
# ------------------------------ end of code oled display ----------------------------------

while True:
    
    distance_VL53L0X = sensor_VL53L0X.ping() + correction_VL   
    distance_HCSR04  = (sensor_HCSR04.distance_mm()) + correction_HC
    
    print('VL:' + str(distance_VL53L0X))             # REPL    
    print('HC:' + str(distance_HCSR04))
    uart.write('VL:' + str(distance_VL53L0X) + '\n') # Serial Monitor
    uart.write('HC:' + str(distance_HCSR04)  + '\n')
    
    clearLine(1)
    clearLine(2)
    oled.text('VL:' + str(distance_VL53L0X), 0, 11*1) # OLED
    oled.text('HC:' + str(distance_HCSR04),  0, 11*2)
    oled.show()

    sleep(.5)

