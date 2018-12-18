import serial
import time
import math

ArduinoSerial = serial.Serial('/dev/cu.usbmodem1421', 9600)
time.sleep(2) # wait for 2 seconds for the communication to get established

xoffset = 0
yoffset = 0
scalar = 11
x = 0
y = 0
t = 0

ptList = []

#print(ArduinoSerial.readline())

def getValFromByte(b):
    b = str(b)
    return int(b[2:-5])
    
print(ArduinoSerial.readline())
xoffset = getValFromByte(str(ArduinoSerial.readline()))
yoffset = getValFromByte(str(ArduinoSerial.readline()))

def mathifyEq(eq):
    for i in range(len(eq) - 1, -1, -1):
        if eq[i:].startswith("pi") or eq[i:].startswith("cos") or \
           eq[i:].startswith("sin"):
            eq = eq[:i] + "math." + eq[i:]
    return eq

equation = input()
time.sleep(5)
while t < 2*math.pi:
    realEq = mathifyEq(equation)
    x = int(scalar*(math.cos(t) * eval(realEq)) + xoffset)
    y = int(scalar*(math.sin(t) * eval(realEq)) + yoffset)
    t += 0.1
    ptList += [(x,y)]

l = len(ptList)
lByte = l.encode()
ArduinoSerial.write(lByte)
for pt in ptList:
    ArduinoSerial.write(str(pt[0]).encode())
    ArduinoSerial.write(str(pt[1]).encode())
# strX = str(x).encode()
# strY = str(y).encode()
# print(strX, strY)
# ArduinoSerial.write(strX)
# time.sleep(2)
# ArduinoSerial.write(strY)
# time.sleep(2)
