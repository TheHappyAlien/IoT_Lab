#!/usr/bin/env python3

import time
import RPi.GPIO as GPIO
from config import *
from mfrc522 import MFRC522
from datetime import datetime

run = True
buzz = False
blink = False

scanTime = datetime.now()
alreadyScanned = False

def buttonPressedCallback():
    global run
    run = False

def doBuzzer():
    global buzz
    GPIO.output(buzzerPin, buzz) 

def doBlink():
    global blink
    voltage = GPIO.LOW
    if (blink): voltage = GPIO.HIGH
    GPIO.output(led1, voltage)


def rfidRead():
    global run
    MIFAREReader = MFRC522()
    
    while run:
        doBuzzer()
        doBlink()
        
        if (datetime.now - scanTime > 0.5):
            global buzz
            global blink
            buzz = False
            blink = False
            
        (status, TagType) = MIFAREReader.MFRC522_Request(MIFAREReader.PICC_REQIDL)
        if status == MIFAREReader.MI_OK:
            (status, uid) = MIFAREReader.MFRC522_Anticoll()
            global alreadyScanned
            
            if status != MIFAREReader.MI_OK:
                alreadyScanned = False
                
            if alreadyScanned == False and status == MIFAREReader.MI_OK:
                alreadyScanned = True
                num = 0
                global scanTime
                scanTime = datetime.now()
                for i in range(0, len(uid)):
                    num += uid[i] << (i*8)
                print(f"Card read UID: {uid} > {num}")
                print(f"Time of scanning: {scanTime}")
                buzz = True
                blink = True


if __name__ == "__main__":
    GPIO.add_event_detect(buttonRed, GPIO.FALLING, callback=buttonPressedCallback, bouncetime=200)
    rfidRead()
    GPIO.cleanup() 