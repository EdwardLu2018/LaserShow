from tkinter import *
import time
import serial
import struct

################################################################################

def init(data):
    data.points = []
    data.rows = data.cols = 22
    data.half = data.rows//2
    data.cellSize = data.width//data.rows
    data.lastKey = ""
    data.removedPts = []
    data.port = "/dev/cu.usbmodem1421"
    # data.isSendingData = False

def mousePressed(event, data):
    x = event.x/data.cellSize
    y = event.y/data.cellSize
    for r in range(data.rows):
        for c in range(data.cols):
            if isClose(x, c) and isClose(y, r) and \
               round(x)-data.half != data.half and \
               data.half-round(y) != data.half:
                    data.removedPts = []
                    data.points += [[round(x)-data.half, data.half-round(y)]]
    removeUnneedPts(data)

def removeUnneedPts(data):
    if len(data.points) >= 2:
        if data.points[-1] == data.points[-2]:
            data.points.pop()
    if len(data.points) >= 3:
        for i in range(len(data.points)-2):
            x0 = data.points[i][0]
            y0 = data.points[i][1]
            x1 = data.points[i+1][0]
            y1 = data.points[i+1][1]
            x2 = data.points[i+2][0]
            y2 = data.points[i+2][1]
            if (y0 == y1 == y2 and (x0 < x1 < x2 or x0 > x1 > x2)) or \
               (x0 == x1 == x2 and (y0 < y1 < y2 or y0 > y1 > y2)) or \
               (x0-x1 != 0 and x1-x2 != 0 and x0-x2 and \
               (y0-y1)//(x0-x1) == (y1-y2)//(x1-x2) == (y0-y2)//(x0-x2)):
                data.points.remove(data.points[i+1])

def isClose(pt1, pt2):
    return abs(pt1 - pt2) <= .25

def keyPressed(event, data):
    if data.lastKey == "??" and event.keysym == "z":
        if len(data.points) > 0:
            data.removedPts += [data.points.pop()]
    elif data.lastKey == "??" and event.keysym == "y":
        if len(data.removedPts) > 0:
            data.points += [data.removedPts.pop()]
    elif data.lastKey == "??" and event.keysym == "u":
        sendDataPoints(data)
    else:
        data.lastKey = event.keysym

def sendDataPoints(data):
    try:
        ArduinoSerial = serial.Serial(data.port, 9600)
        time.sleep(2)
        print("Serial communication established!")
        print("Sending inputs to Arduino.")
        while True:
            for pt in data.points:
                print("...")
                ArduinoSerial.write(struct.pack(">BB", pt[0]+data.half, 
                                                       pt[1]+data.half))
                time.sleep(1)
            if len(data.points) >= 2 and data.points[0] != data.points[-1]:
                for i in range(len(data.points)-1, -1, -1):
                    pt = data.points[i]
                    print("...")
                    ArduinoSerial.write(struct.pack(">BB", pt[0]+data.half, 
                                                           pt[1]+data.half))
                    time.sleep(1)
    except:
        print("Could not find connection to Arduino. Please try again.")

def redrawAll(canvas, data):
    for r in range(data.rows):
        for c in range(data.cols):
            left = c*data.cellSize
            right = r*data.cellSize
            canvas.create_rectangle((left, right), 
                                    (left+data.cellSize, right+data.cellSize))
    canvas.create_line((data.half*data.cellSize, 0), 
                       (data.half*data.cellSize, data.height), 
                       width=3)
    canvas.create_line((0, data.half*data.cellSize), 
                       (data.width, data.half*data.cellSize),
                       width=3)

    for pt in data.points:
        radius = 3
        canvas.create_oval(((pt[0]+data.half)*data.cellSize-radius, 
                            -(pt[1]-data.half)*data.cellSize-radius), 
                           ((pt[0]+data.half)*data.cellSize+radius, 
                            -(pt[1]-data.half)*data.cellSize+radius),
                           fill="black")

    for i in range(len(data.points)-1):
        firstPt = data.points[i]
        secondPt = data.points[i+1]
        canvas.create_line(((firstPt[0]+data.half)*data.cellSize, 
                            -(firstPt[1]-data.half)*data.cellSize), 
                           ((secondPt[0]+data.half)*data.cellSize, 
                            -(secondPt[1]-data.half)*data.cellSize), 
                           width=3, fill="green yellow")

################################################################################

def run(width=300, height=300):
    def redrawAllWrapper(canvas, data):
        canvas.delete(ALL)
        canvas.create_rectangle(0, 0, data.width, data.height,
                                fill='white', width=0)
        redrawAll(canvas, data)
        canvas.update()    

    def mousePressedWrapper(event, canvas, data):
        mousePressed(event, data)
        redrawAllWrapper(canvas, data)

    def keyPressedWrapper(event, canvas, data):
        keyPressed(event, data)
        redrawAllWrapper(canvas, data)

    # Set up data and call init
    class Struct(object): pass
    data = Struct()
    data.width = width
    data.height = height
    root = Tk()
    root.resizable(width=False, height=False) # prevents resizing window
    init(data)
    # create the root and the canvas
    canvas = Canvas(root, width=data.width, height=data.height)
    canvas.configure(bd=0, highlightthickness=0)
    canvas.pack()
    # set up events
    root.bind("<Button-1>", lambda event:
                            mousePressedWrapper(event, canvas, data))
    root.bind("<Key>", lambda event:
                            keyPressedWrapper(event, canvas, data))
    root.bind("<B1-Motion>", lambda event:
                            mousePressedWrapper(event, canvas, data))
    redrawAll(canvas, data)
    # and launch the app
    root.mainloop()  # blocks until window is closed
    print("bye!")

run(600, 600)