#!/usr/bin/env python3

import time
from PIL import Image, ImageDraw, ImageFont
import lib.oled.SSD1331 as SSD1331
import board
import busio
import adafruit_bme280.advanced as adafruit_bme280

disp


def bme280_config():
    i2c = busio.I2C(board.SCL, board.SDA)
    bme280 = adafruit_bme280.Adafruit_BME280_I2C(i2c, 0x76)
    bme280.sea_level_pressure = 1013.25
    bme280.standby_period = adafruit_bme280.STANDBY_TC_500
    bme280.iir_filter = adafruit_bme280.IIR_FILTER_X16
    return bme280

def bme280_read(bme):
    bme.overscan_pressure = adafruit_bme280.OVERSCAN_X16
    bme.overscan_humidity = adafruit_bme280.OVERSCAN_X1
    bme.overscan_temperature = adafruit_bme280.OVERSCAN_X2
    print(bme.temperature)
    print(bme.humidity)
    print(bme.pressure)
    return {"temperature" : bme.temperature, "humidity" : bme.humidity, "pressure" : bme.pressure}


def initDisplay():
    global disp
    disp = SSD1331.SSD1331()
    global font
    font = ImageFont.truetype("./lib/oled/Font.ttf", 13)
    # Initialize library.
    disp.Init()

    
def showWeather(dict):
    # Clear display.
    disp.clear()
    
    # Create blank image for drawing.
    image1 = Image.new("RGB", (disp.width, disp.height), "BLACK")
    draw = ImageDraw.Draw(image1)
    
    # Thermometer?
    draw.line([(12, 10), (12, 20)], fill="YELLOW", width=1)
    draw.line([(17, 10), (17, 20)], fill="YELLOW", width=1)
    draw.arc([(12, 10), (17, 8)], 270, 90, fill="YELLOW", width=1)
    draw.ellipse([(9, 18), (20, 29)], fill="YELLOW", width=1)
    
    draw.text((25, 14), dict["temperature"], font=font, fill="YELLOW")

    # Raindrop
    draw.line([(15, 35), (12, 41)], fill="YELLOW", width=1)
    draw.line([(15, 35), (18, 41)], fill="YELLOW", width=1)
    draw.arc([(12, 41), (18, 46)], fill="YELLOW", width=1)
    
    draw.text((25, 36), dict["humidity"], font=font, fill="YELLOW")
    
    # Pressure
    draw.line([(15, 50), (15, 70)], fill="YELLOW", width=1)
    draw.line([(15, 70), (11, 66)], fill="YELLOW", width=1)
    draw.line([(15, 70), (19, 66)], fill="YELLOW", width=1)
    draw.line([(10, 70), (20, 70)], fill="YELLOW", width=1)

    draw.text((25, 54), dict["pressure"], font=font, fill="YELLOW")
    
def test():
    bme1 = bme280_config()
    while (True):
        showWeather(bme280_read(bme1))
        time.sleep(2)


if __name__ == "__main__":
    initDisplay()
    test()
