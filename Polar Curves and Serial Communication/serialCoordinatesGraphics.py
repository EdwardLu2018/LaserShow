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
    data.removedPts = []
    data.port = "/dev/cu.usbmodem1421"
    data.baudRate = 9600
    data.isSendingData = False

def mousePressed(event, data):
    if len(data.points) <= 1 or data.points[0] != data.points[-1]:
        x = event.x/data.cellSize
        y = event.y/data.cellSize
        for r in range(data.rows):
            for c in range(data.cols):
                if isClose(x, c) and isClose(y, r) and \
                   round(x)-data.half != data.half and \
                   data.half-round(y) != data.half:
                        data.removedPts = []
                        data.points += [[round(x)-data.half, 
                                         data.half-round(y)]]
    removeUnneedPts(data)

def removeUnneedPts(data):
    if len(data.points) >= 2:
        if data.points[-1] == data.points[-2]:
            data.points.pop()
    if len(data.points) >= 3:
        x0 = data.points[-1][0]
        y0 = data.points[-1][1]
        x1 = data.points[-2][0]
        y1 = data.points[-2][1]
        x2 = data.points[-3][0]
        y2 = data.points[-3][1]
        if (y0 == y1 == y2 and (x0 < x1 < x2 or x0 > x1 > x2)) or \
           (x0 == x1 == x2 and (y0 < y1 < y2 or y0 > y1 > y2)) or \
           (x0-x1 != 0 and x1-x2 != 0 and x0-x2 != 0 and \
            y0-y1 != 0 and y1-y2 != 0 and y0-y2 != 0 and \
           (y0-y1)/(x0-x1) == (y1-y2)/(x1-x2) == (y0-y2)/(x0-x2) ):
            data.points.remove(data.points[-2])

def isClose(pt1, pt2):
    return abs(pt1 - pt2) <= .25

def keyPressed(event, data):
    if event.keysym == "z":
        if len(data.points) > 0:
            data.removedPts += [data.points.pop()]
    elif event.keysym == "y":
        if len(data.removedPts) > 0:
            data.points += [data.removedPts.pop()]
    elif event.keysym == "x":
        data.points = []
    elif event.keysym == "u":
        sendDataPoints(data)

    if 0 < len(data.points) <= 1 or \
       (len(data.points) >= 2 and data.points[0] != data.points[-1]):
        if data.points[-1][0] > -10 and event.keysym == "Left":
            data.points += [[data.points[-1][0]-1, data.points[-1][1]]]
        elif data.points[-1][0] < 10 and event.keysym == "Right":
            data.points += [[data.points[-1][0]+1, data.points[-1][1]]]
        elif data.points[-1][1] < 10 and event.keysym == "Up":
            data.points += [[data.points[-1][0], data.points[-1][1]+1]]
        elif data.points[-1][1] > -10 and event.keysym == "Down":
            data.points += [[data.points[-1][0], data.points[-1][1]-1]]
    removeUnneedPts(data)

def sendDataPoints(data):
    if len(data.points) > 0:
        try:
            ArduinoSerial = serial.Serial(data.port, data.baudRate)
            time.sleep(2)
            print("Serial communication established!")
            print("Sending inputs to Arduino...")
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
    else:
        print("Not enough data points! Please add more.")

def redrawAll(canvas, data):
    for r in range(data.rows):
        for c in range(data.cols):
            left = c*data.cellSize
            right = r*data.cellSize
            canvas.create_rectangle((left, right), 
                                    (left+data.cellSize, right+data.cellSize))
    canvas.create_line((data.half*data.cellSize, 0), 
                       (data.half*data.cellSize, data.height-5), 
                       width=3, arrow=BOTH)
    canvas.create_line((0, data.half*data.cellSize), 
                       (data.width-5, data.half*data.cellSize),
                       width=3, arrow=BOTH)

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
                           width=3, fill="green yellow", arrow=LAST)

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
    # create the root
    root = Tk()
    root.resizable(width=False, height=False) # prevents resizing window
    init(data)
    # create the title
    title = Label(root, text="Laser Show!", font="Times 20 bold")
    title.pack(side=TOP, fill=BOTH, expand=YES)
    # create the canvas
    canvas = Canvas(root, width=data.width, height=data.height)
    canvas.configure(bd=0, highlightthickness=0)
    canvas.pack(side=TOP, padx=(8,5), pady=(0,5))
    # set up events
    root.bind("<Button-1>", lambda event:
                            mousePressedWrapper(event, canvas, data))
    root.bind("<Key>", lambda event:
                            keyPressedWrapper(event, canvas, data))
    redrawAll(canvas, data)
    # and launch the app
    root.mainloop()  # blocks until window is closed
    print("Application Closed.")

run(600, 600)