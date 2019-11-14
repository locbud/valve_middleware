#!/usr/bin/env python
# -*- coding: utf_8 -*-
import serial
 
import modbus_tk
import modbus_tk.defines as cst
from modbus_tk import modbus_rtu
import os
import time
import datetime
import glob
import MySQLdb
from time import strftime
import Adafruit_DHT
import RPi.GPIO as GPIO
import sys

PORT = "/dev/ttyAMA0"

#Variables for MySQL
# mysql already changed to  'auth' by  pi@localhost
#db = MySQLdb.connect(host="localhost", user="pi", passwd="123", db="temp_database")

# Try to write data to NAS mysql server
db = MySQLdb.connect(host="192.168.219.253", user="Dascorporation", passwd="Das.1018", db="IoT_Smart_Valve")
cur = db.cursor()

def tempRead1():
   H, T = Adafruit_DHT.read_retry(Adafruit_DHT.DHT22, 23)
   return (str(H), str(T))
def modtk():
    """main"""
    logger = modbus_tk.utils.create_logger("console")


    try:
        #Connect to the slave
        master = modbus_rtu.RtuMaster(serial.Serial(port=PORT, baudrate=9600, bytesize=8, parity='N', stopbits=1, xonxoff=0))
        master.set_timeout(5.0)
        master.set_verbose(True)
        logger.info("connected")
        ####
       # logger.info(master.execute(3, cst.READ_INPUT_REGISTERS, 2, 8 , data_format='>ffff'))
        #### 
        reg1 = master.execute(3, cst.READ_INPUT_REGISTERS, 2, 2, data_format = '>f')
        reg2 = master.execute(3, cst.READ_INPUT_REGISTERS, 4, 2, data_format = '>f')
        reg3 = master.execute(3, cst.READ_INPUT_REGISTERS, 6, 2, data_format = '>f')
        reg4 = master.execute(3, cst.READ_INPUT_REGISTERS, 8, 2, data_format = '>f')
        #####
    except modbus_tk.modbus.ModbusError as exc:
        logger.error("%s- Code=%d", exc, exc.get_exception_code())
    return (reg1,reg2, reg3, reg4)

while True:
   H, T = tempRead1()
   Tf = float(T)
   Hf = float(H)
   print "Current temperature"
   print round(Tf,1)
   print "Current humidity"
   print round(Hf,1)
#   print T
   datetimeWrite = (time.strftime("%Y-%m-%d ") + time.strftime(" %H:%M:%S"))
   print datetimeWrite
   ##
   ##
   slaveid = 3
   reg1,reg2, reg3, reg4 = modtk()
   room ="Main Room"
   dev = 0.75
   ess = 75.0
  # sql = ("""INSERT INTO modbus2sql (datetime,slaveid, high_temp, low_temp, voltage, current, room_temp, room_humi) VALUES (%s,%s,%s,%s,%s,%s,%s,%s)""",(datetimeWrite,slaveid, reg1, reg2, reg3, reg4, T,H))
   sql = ("""INSERT INTO Dev (Seq, Vollage, Ampair, Dev,  High_Temp, Low_Temp, Ess, Check_Time) VALUES (%s,%s,%s,%s,%s,%s,%s,%s)""",('',reg3, reg4, dev, reg1, reg2, ess, datetimeWrite))
   try:
       print "Writing to database..."
       cur.execute(*sql)
       db.commit()
       print "Write Complete"
   except:
       db.rollback()
       print "Failed writing to database"

   cur.close()
   db.close()
   break

