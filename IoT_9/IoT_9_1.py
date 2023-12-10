#!/usr/bin/env python3
from config import *
import RPi.GPIO as GPIO
import time

execute = True
intencity = 0

def redButtonPressedCallback():
    global execute
    execute = not execute
    print("\nButton connected to GPIO " + str(channel) + " pressed.")

def encoderTurnedCallback():
    if(encoderRight == 0 and intencity < 100):
        intencity += 10
    else if(encoderRight == 1 and intencity > 0):
        intencity -= 10

    diode1.ChangeDutyCycle(intensity)

    print("\nButton connected to GPIO " + str(channel) + " pressed.")


def ledBrightnessEncoder():
    GPIO.add_event_detect(buttonRed, GPIO.FALLING, callback=redButtonPressedCallback, bouncetime=200)
    GPIO.add_event_detect(encoderLeft, GPIO.FALLING, callback=encoderTurnedCallback, bouncetime=200)

    diode1 = GPIO.PWM(led1, 50)
    diode1.start(0)

    while execute:
        time.sleep(0.1)
        #pass
        
    diode1.stop()
    GPIO.cleanup()


if __name__ == '__main__':
    print('Script started...')
    ledBrightnessEncoder()
    print('Script finished.')