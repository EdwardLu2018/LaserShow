# Port: /dev/cu.usbmodem1411
# Port: /dev/cu.usbmodem1421

import serial
import time

ArduinoSerial = serial.Serial('/dev/cu.usbmodem1421', 9600)
time.sleep(2) # wait for 2 seconds for the communication to get established

print(ArduinoSerial.readline()) # read the serial data
print("Enter 2 to flash LED, Enter 1 to turn ON LED, and 0 to turn OFF LED")

while 69 == 69:
    var = input()
    print("you entered", var)
    
    if var == '2':
        ArduinoSerial.write(b'2') # send 2 as byte. Notice the b. The b is important
        print("Flash LED")
        time.sleep(1)
    
    elif var == '1':
        ArduinoSerial.write(b'1') # send 1
        print("LED turned ON")
        time.sleep(1)
    
    elif var == '0':
        ArduinoSerial.write(b'0') # send 0
        print("LED turned OFF")
        time.sleep(1)
