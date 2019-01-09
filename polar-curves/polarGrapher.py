import serial
import time
import math
import struct 

ArduinoSerial = serial.Serial('/dev/cu.usbmodem1421', 9600)
time.sleep(2) # wait for 2 seconds for the communication to get established

print(ArduinoSerial.readline())

xoffset = 0
yoffset = 0
scalar = 11
x = 0
y = 0
t = 0

ptList = []

def mathifyEq(eq):
    for i in range(len(eq) - 1, -1, -1):
        if eq[i:].startswith("pi") or eq[i:].startswith("cos") or \
           eq[i:].startswith("sin"):
            eq = eq[:i] + "math." + eq[i:]
    return eq

xoffset = int(ArduinoSerial.readline().decode())
print(xoffset)
yoffset = int(ArduinoSerial.readline().decode())
print(yoffset)

equation = input()
while t < 2*math.pi:
    realEq = mathifyEq(equation)
    x = int(scalar*(math.cos(t) * eval(realEq)) + xoffset)
    y = int(scalar*(math.sin(t) * eval(realEq)) + yoffset)
    t += 0.1
    ptList += [(x,y)]

print(ptList)

ArduinoSerial.write(struct.pack("BBB", 1, 2, 3))

# l = len(ptList)
# for pt in ptList:
#     ArduinoSerial.write(str(pt[0]).encode())
#     ArduinoSerial.write(str(pt[1]).encode())
# strX = str(x).encode()
# strY = str(y).encode()
# print(strX, strY)
# ArduinoSerial.write(strX)
# time.sleep(2)
# ArduinoSerial.write(strY)
# time.sleep(2)
