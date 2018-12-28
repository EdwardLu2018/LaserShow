import time
import struct
import serial

ArduinoSerial = serial.Serial('/dev/cu.usbmodem1421', 9600)
time.sleep(2)

# print(ArduinoSerial.readline().decode())

def getDataPoints(numPts=3):
    inputs = []
    while len(inputs) < numPts:
        pt = input("Input a data point (-10 to 10): ")
        try:
            pt = int(pt)
            if -10 <= pt <= 10:
                inputs += [pt]
            else: 
                print("%s is not between -10 and 10!" % str(pt))
        except ValueError:
            print("%s is not an integer between -10 and 10!" % str(pt))
    return inputs

def sendToArduino(inputs):
    print("Sending inputs to Arduino")
    
    for pt in inputs:
        print("...")
        time.sleep(1)
        ArduinoSerial.write(str(pt).encode())
        time.sleep(1)
    
    print("Done!")
    
inputs = getDataPoints()
sendToArduino(inputs)