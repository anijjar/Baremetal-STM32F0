# This file will connect to a COM port and communicate with the STM

import serial

data = "" # Contain data from STM

if __name__ == "__main__":
    ser = serial.Serial(port='COM4', baudrate=9600, timeout=0, stopbits=serial.STOPBITS_ONE)  # open serial port
    ser.close()             # close port because idk how to do it when the script gets killed.
    ser.open()
    print(ser.is_open)
    while(1):
        # Wait until there is data
        if(ser.in_waiting > 0):
            # Record the data till carraige return or new line is entered
            data = ser.readline()
            # Decode and print
            print(data.decode('Ascii'))
            # Send a response
            ser.write(b"Pollo\r\n")