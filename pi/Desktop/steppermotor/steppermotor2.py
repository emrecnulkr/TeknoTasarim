#!/usr/bin/env python
# -*- coding: utf-8 -*-

import RPi.GPIO as GPIO
import time
 
GPIO.setmode(GPIO.BCM)
 

coil_A_1_pin = 14
coil_A_2_pin = 15
coil_B_1_pin = 18
 

GPIO.setup(coil_A_1_pin, GPIO.OUT)
GPIO.setup(coil_A_2_pin, GPIO.OUT)
GPIO.setup(coil_B_1_pin, GPIO.OUT)
 
 
def forward(delay, steps):  
	
  for i in range(0, steps):
    setStep(1, 0, 1)
    time.sleep(delay)
    setStep(0, 1, 1)
    time.sleep(delay)
    setStep(0, 1, 0)
    time.sleep(delay)
    setStep(1, 0, 0)
    time.sleep(delay)
 
def backwards(delay, steps):  
  for i in range(0, steps):
    setStep(1, 0, 0)
    time.sleep(delay)
    setStep(0, 1, 0)
    time.sleep(delay)
    setStep(0, 1, 1)
    time.sleep(delay)
    setStep(1, 0, 1)
    time.sleep(delay)
 
  
def setStep(w1, w2, w3):
  GPIO.output(coil_A_1_pin, w1)
  GPIO.output(coil_A_2_pin, w2)
  GPIO.output(coil_B_1_pin, w3)
 
while True:
  delay = raw_input("Adim arasi bekleme suresi (milisaniye)?")
  steps = raw_input("Ileri kac adim? ")
  forward(int(delay) / 1000.0, int(steps))
  steps = raw_input("Geri kac adim? ")
  backwards(int(delay) / 1000.0, int(steps))
