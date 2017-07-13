#!/usr/bin/env python
# -*- coding: utf-8 -*- 

from time import sleep
import RPi.GPIO as GPIO

DIR = 20
STEP = 21
CW = 1
CWW = 0 
SPR = 200									# Adım sayısı, tam tur 200 Adım					

GPIO.setmode(GPIO.BCM)
GPIO.setup(DIR, GPIO.OUT)
GPIO.setup(STEP, GPIO.OUT)
GPIO.output(DIR, CW)


step_count = SPR 
delay = 0.5									# 1 sn bekletme				 							

for x in range (step_count):				# saat yönü				
		GPIO.output(STEP, GPIO.HIGH)
		sleep(delay)
		GPIO.output(STEP, GPIO.LOW)
		sleep(delay)		


#sleep(.5)
#GPIO.output(DIR,CWW)
#
#for x in range (step_count):				# saat yönü tersi			
#		GPIO.output(STEP, GPIO.HIGH)
#		sleep(delay)
#		GPIO.output(STEP, GPIO.LOW)
#		sleep(delay)
		

