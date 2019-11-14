#!/usr/bin/env python
# -*- coding: utf_8 -*-
import serial
 
import modbus_tk
import modbus_tk.defines as cst
from modbus_tk import modbus_rtu
 
#PORT = 1
PORT = "/dev/ttyAMA0"

def main():
    """main"""
    logger = modbus_tk.utils.create_logger("console")
#    abc = modbus_tk.utils.ConsoleHandler

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

        #htemp = 'high temp' + reg1
        print (reg1)
       # print'VOLTAGE: ',reg3
       # print'CURRENT: ',reg4
        #####
    except modbus_tk.modbus.ModbusError as exc:
        logger.error("%s- Code=%d", exc, exc.get_exception_code())

if __name__ == "__main__":
    main()


