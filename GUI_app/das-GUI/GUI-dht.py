#!/usr/bin/env python3
# -*- coding: utf_8 -*-
import RPi.GPIO as GPIO
import time
#import datetime
from tkinter import *
import tkinter.font
import PIL
from PIL import Image, ImageTk
import os
import Adafruit_DHT


#Adafruit DHT lib setting
chosen_sensor = Adafruit_DHT.DHT22
GPIO.setmode(GPIO.BCM)
pin_sensor = 23


# tkinter das basic settings

das = Tk()
das.title(" Energer Harvesting project - v.1.0.0  ")
das.config(background= "#FDFEFE")
das.minsize(700,300)
Font1 = tkinter.font.Font(family = 'Helvetica', size = 20, weight = 'bold')
Font2 = tkinter.font.Font(family = 'Tahoma', size = 24, weight = 'bold')
Font3 = tkinter.font.Font(family = 'Arial', size = 18, weight = 'bold')

# tkinter simple das created

# Adding company icon to the GUI app
img1 = ImageTk.PhotoImage(Image.open("icon-das1.png"))
panel1 = Label(das, image = img1)
panel1.grid(row=8,columnspan=1, sticky = W)      #(side = "bottom", fill = "both", expand = "no")

img2 = ImageTk.PhotoImage(Image.open("icon-das2.png"))
panel2 = Label(das, image = img2)
panel2.grid(row=8,columnspan=3,sticky = E) 

# Funtion for started here
# Timer is from Here!
time1 = ''
clock = Label(das, font=('times', 15, 'bold'), bg='#FDFEFE', padx = 10, pady = 10)
clock.grid(row=1,column=1)

slaveID = Label(das, text=' Slave ID: 3 ', font=('times', 15, 'bold'), fg='red', bg='#FDFEFE', padx = 10, pady = 10)
slaveID.grid(row=1,column=0)

ValveState = Label(das,text='Vavle State', font = Font1, fg='#21618C', bg = '#FDFEFE', padx = 10, pady = 10)
ValveState.grid(row=1,column=2)

def ledON():
    #GPIO.output(LED, GPIO.HIGH) # led on
    onoff = Label(das,text=' ON ', font = Font3, bg = '#FDFEFE', fg='green', padx = 0)
    onoff.grid(row=1,column=2, sticky = E)

def ledOFF():
    #GPIO.output(LED, GPIO.LOW) # led off
    onoff = Label(das,text='OFF', font = Font3, bg = '#FDFEFE', fg='red', padx = 0)
    onoff.grid(row=1,column=2, sticky = E)

# clock.pack(fill=BOTH, expand=1)
def tick():
    global time1
    # get the current local time from the PC
    time2 = time.strftime('%Y-%m-%d') +'    '+ time.strftime('%H:%M:%S')
    # if time string has changed, update it
    if time2 != time1:
        time1 = time2
        clock.config(text= time2 )
    # calls itself every 200 milliseconds
    # to update the time display as needed
    # could use >200 ms, but display gets jerky
    clock.after(100, tick)
tick()

# Get Room Temperature from Here
temp1 = 0
humi1 = 0


roomTemp = Label(das, font = Font1, fg='#21618C', bg = '#FDFEFE')
roomTemp.grid(row=2,column=1, padx = 1, pady = 1)
degreeSign = Label(das, text= '\N{DEGREE SIGN}C', font = Font1, fg='#21618C', bg = '#FDFEFE')
degreeSign.grid(row=2,column=1,  sticky = E)

roomHumi = Label(das, font = Font1, fg='#21618C', bg = '#FDFEFE')
roomHumi.grid(row=3,column=1, padx = 1, pady = 1)
percent = Label(das, text= '%', font = Font1, fg='#21618C', bg = '#FDFEFE')
percent.grid(row=3,column=1,  sticky = E)

Text8 = Label(das,font = Font1, fg='#21618C', bg = '#FDFEFE', padx = 10, pady = 10)
Text8.grid(row=4,column=1)
voltV = Label(das, text= 'V', font = Font1, fg='#21618C', bg = '#FDFEFE', padx = 10, pady = 10)
voltV.grid(row=4,column=1,  sticky = E)


Text10 = Label(das, font = Font1, fg='#21618C', bg = '#FDFEFE', padx = 10, pady = 10)
Text10.grid(row=5,column=1)
currA = Label(das, text= 'A', font = Font1, fg='#21618C', bg = '#FDFEFE', padx = 10, pady = 10)
currA.grid(row=5,column=1,  sticky = E)

def temp():
   global temp1,humi1
   # get the current ltemperature from DHT22
   humi2, temp2 = Adafruit_DHT.read_retry(chosen_sensor, pin_sensor);
   tempR = round(temp2,1)
   humiR = round(humi2,1)
   # if time string has changed, update it
   if (tempR != temp1 or humiR != humi1):
       temp1 = tempR
       humi1 = humiR
       roomTemp.config(text=tempR)
       roomHumi.config(text=humiR)
   # calls itself every 200 milliseconds
   # to update the time display as needed
   # could use >200 ms, but display gets jerky
   roomTemp.after(200, temp)
temp ()



        

#########################

Text0 = Label(das,text='-IoT Smart Valve-', font = Font2, bg = '#21618C', fg='#FDFEFE', padx = 200, pady = 20)
Text0.grid(row=0,columnspan=3)

#date-time
# Textt = Label(das,text=datetime, font = Font2, bg = '#0080FF', fg='black', padx = 200, pady = 30)
# Textt.grid(row=1,columnspan=2)
# #

##Text1 = Label(das,text='Vavle State:', font = Font1, fg='#FFFFFF', bg = '#0080FF', padx = 10, pady = 10)
##Text1.grid(row=1,column=0)
##Text2 = Label(das,text='ON', font = Font1, fg='#FFFFFF', bg = '#0080FF', padx = 10, pady = 10)
##Text2.grid(row=1,column=1)

Text3 = Label(das,text='High Temperature', font = Font1, fg='#21618C', bg = '#FDFEFE', padx = 10, pady = 10)
Text3.grid(row=2,column=0)
#Text4 = Label(das,text='70', font = Font1, fg='#FFFFFF', bg = '#0080FF', padx = 10, pady = 10)
#Text4.grid(row=2,column=1)
Button1 = Button(das, text=' ON ', font = Font1, command = ledON, bg='bisque2', height = 1, width = 10)
Button1.grid(row=2,column=2)

Text5 = Label(das,text='Low Temperature', font = Font1, fg='#21618C', bg = '#FDFEFE', padx = 10, pady = 10)
Text5.grid(row=3,column=0)
##Text6 = Label(das,text='30', font = Font1, fg='#FFFFFF', bg = '#0080FF', padx = 10, pady = 10)
##Text6.grid(row=3,column=1)
Button2 = Button(das, text=' OFF ', font = Font1, command = ledON, bg='bisque2', height = 1, width = 10)
Button2.grid(row=3,column=2)

Text7 = Label(das,text='Voltage   ', font = Font1, fg='#21618C', bg = '#FDFEFE', padx = 10, pady = 10)
Text7.grid(row=4,column=0)
##Text8 = Label(das,font = Font1, fg='#21618C', bg = '#FDFEFE', padx = 10, pady = 10)
##Text8.grid(row=4,column=1)
##voltV = Label(das, text= 'V', font = Font1, fg='#21618C', bg = '#FDFEFE', padx = 10, pady = 10)
##voltV.grid(row=4,column=1,  sticky = E)

Text9 = Label(das,text='Current   ', font = Font1, fg='#21618C', bg = '#FDFEFE', padx = 10, pady = 10)
Text9.grid(row=5,column=0)
##Text10 = Label(das, font = Font1, fg='#21618C', bg = '#FDFEFE', padx = 10, pady = 10)
##Text10.grid(row=5,column=1)
##currA = Label(das, text= 'A', font = Font1, fg='#21618C', bg = '#FDFEFE', padx = 10, pady = 10)
##currA.grid(row=5,column=1,  sticky = E)

Text11 = Label(das,text='Power generation', font = Font1, fg='#21618C', bg = '#FDFEFE', padx = 10, pady = 10)
Text11.grid(row=6,column=0)
power = Label(das, text= '2.5', font = Font1, fg='#21618C', bg = '#FDFEFE', padx = 10, pady = 10)
power.grid(row=6,column=1)
powerW = Label(das, text= 'W', font = Font1, fg='#21618C', bg = '#FDFEFE', padx = 10, pady = 10)
powerW.grid(row=6,column=1,  sticky = E)


Text12 = Label(das,text='Battery life', font = Font1, fg='#21618C', bg = '#FDFEFE', padx = 10, pady = 10)
Text12.grid(row=7,column=0)
batt = Label(das, text= '75', font = Font1, fg='#21618C', bg = '#FDFEFE', padx = 10, pady = 10)
batt.grid(row=7,column=1)
percent = Label(das, text= '%', font = Font1, fg='#21618C', bg = '#FDFEFE', padx = 10, pady = 10)
percent.grid(row=7,column=1,  sticky = E)

##Button1 = Button(das, text=' LED ON', font = Font1, command = ledON, bg='bisque2', height = 1, width = 10)
##Button1.grid(row=1,column=0)

##Button2 = Button(das, text=' LED OFF', font = Font1, command = ledOFF, bg='bisque2', height = 1, width = 10)
##Button2.grid(row=1,column=1)

#Text3 = Label(das,text='DAScorporation', font = Font1, bg = '#FDFEFE', fg='#21618C', padx = 10, pady = 10)
#Text3.grid(row=7,columnspan=2)



das.mainloop()
