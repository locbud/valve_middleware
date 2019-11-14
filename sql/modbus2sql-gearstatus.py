#!/usr/bin/env python
# -*- coding: utf_8 -*-
import serial
import os
import time
import datetime
import glob
import MySQLdb
from time import strftime
import Adafruit_DHT
import RPi.GPIO as GPIO
import sys
# Try to write data to NAS mysql server
db = MySQLdb.connect(host="192.168.219.253", user="Dascorporation", passwd="Das.1018", db="IoT_Smart_Valve")
cur = db.cursor()

def tempRead1():
   H, T = Adafruit_DHT.read_retry(Adafruit_DHT.DHT22, 23)
   return (str(H), str(T))

while True:
   H, T = tempRead1()
   Tf = float(T)
   Hf = float(H)
   print "Current temperature"
   print round(Tf,1)
   print "Current humidity"
   print round(Hf,1)
   datetimeWrite = (time.strftime("%Y-%m-%d ") + time.strftime(" %H:%M:%S"))
   print datetimeWrite
   ##
#   sql_select = ("""SELECT * FROM Gear_Stastus""")
#   sql = ("""UPDATE Gear_Stastus SET Room_Temp=%s WHERE Seq=1""", (T))
#   sql = ("""INSERT INTO Gear_Stastus (Seq, Gear_Name,Status, Room_Temp, Check_Time) VALUES (%s,%s,%s,%s,%s)""",('','','', T,datetimeWrite))
   try:
       print "Writing to database..."
       cur.execute("""SELECT * FROM Gear_Stastus""") 
       cur.execute("""UPDATE Gear_Stastus 
                      SET Room_Temp=%s, Check_Time=%s 
                      WHERE Seq<6
                   """, (T,datetimeWrite))
#       cur.execute ("""INSERT INTO Gear_Stastus (Seq, Gear_Name,Status, Room_Temp, Check_Time) VALUES (%s,%s,%s,%s,%s)""",('','','', T,datetimeWrite))
       db.commit()
       print "Write Complete"
   except:
       db.rollback()
       print "Failed writing to database"

   cur.close()
   db.close()
   break

