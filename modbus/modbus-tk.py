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
        master = modbus_rtu.RtuMaster(
            serial.Serial(port=PORT, baudrate=9600, bytesize=8, parity='N', stopbits=1, xonxoff=0)
        )
        master.set_timeout(5.0)
        master.set_verbose(True)
        logger.info("connected")

        #Name table # Command # Address
        #State      # 0x04    # 0x0000
        #High Temp  # 0x04    # 0x0002
        #Cool Temp  # 0x04    # 0x0004
        #Voltage    # 0x04    # 0x0006
        #Current    # 0x04    # 0x0008
        #################################################################
        #logger.info(master.execute(1, cst.READ_HOLDING_REGISTERS, 1, 1))
        #send some queries
                       #logger.info(master.execute(1, cst.READ_COILS, 0, 10))
        #logger.info(master.execute(1, cst.READ_DISCRETE_INPUTS, 0, 8))
        #
        #Command 0X04=READ_INPUT_REGISTERS; slave addr = 1;
        #The Data Address of the first register requested 0x0000 =0;
        #total number of registers requested=5 ( read 5 registers)
        #


        logger.info(master.execute(3, cst.READ_INPUT_REGISTERS, 2, 8 , data_format='>ffff'))



        #logger.info(master.execute(1, cst.WRITE_SINGLE_COIL, 7, output_value=1))
        #logger.info(master.execute(1, cst.WRITE_SINGLE_REGISTER, 100, output_value=54))
        #logger.info(master.execute(1, cst.WRITE_MULTIPLE_COILS, 0, output_value=[1, 1, 0, 1, 1, 0, 1, 1]))
        #logger.info(master.execute(1, cst.WRITE_MULTIPLE_REGISTERS, 100, output_value=xrange(12))) 

#        print('abc= ', self.format(record))
#reg1 = master.execute(3, cst.READ_INPUT_REGISTERS, 2, 2, data_format = '>f')
#reg2 = master.execute(3, cst.READ_INPUT_REGISTERS, 4, 2, data_format = '>f')
#reg3 = master.execute(3, cst.READ_INPUT_REGISTERS, 6, 2, data_format = '>f')
#reg4 = master.execute(3, cst.READ_INPUT_REGISTERS, 8, 2, data_format = '>f')
#print'HIGH TEMP: ',reg1
#print'LOW TEMP: ',reg2
#print'VOLTAGE: ',reg3
#print'CURRENT: ',reg4



    except modbus_tk.modbus.ModbusError as exc:
        logger.error("%s- Code=%d", exc, exc.get_exception_code())

if __name__ == "__main__":
    main()

