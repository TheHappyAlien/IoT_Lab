#!/usr/bin/env python3

import paho.mqtt.client as mqtt
import tkinter
import sqlite3
import RPi.GPIO as GPIO
import time

# The broker name or IP address.
broker = "localhost"
# broker = "127.0.0.1"
# broker = "10.0.0.1"

run = True

def buttonPressedCallback():
    global run
    run = False

# The MQTT client.
client = mqtt.Client()

# Thw main window.
window = tkinter.Tk()

def process_message(message):
    # Decode message.
    message_decoded = (str(message.payload.decode("utf-8"))).split(".")
    if message_decoded[0] == "Client connected" or message_decoded[0] == "Client disconnected":
        print(message_decoded[0] + " at: " +  message_decoded[1] + " on terminal " + message_decoded[2])
    else:
        print("Card " + message_decoded[0] + " has been read at: " + message_decoded[1] + " on terminal " + message_decoded[2])

def connect_to_broker():
    # Connect to the broker.
    client.connect(broker)
    # Send message about conenction.
    client.on_message = process_message
    # Starts client and subscribe.
    client.loop_start()
    client.subscribe("card_info")


def disconnect_from_broker():
    # Disconnet the client.
    client.loop_stop()
    
    while (run):
        time.sleep(0.1)
        
    client.disconnect()


def run_receiver():
    connect_to_broker()
    disconnect_from_broker()


if __name__ == "__main__":
    GPIO.add_event_detect(buttonRed, GPIO.FALLING, callback=buttonPressedCallback, bouncetime=200)
    run_receiver()
    GPIO.cleanup()