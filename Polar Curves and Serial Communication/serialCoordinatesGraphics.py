from tkinter import *
import time
import serial

################################################################################

def init(data):
    data.points = []
    data.rows = data.cols = 10
    data.cellSize = data.width//data.rows

def mousePressed(event, data):
    x = event.x/data.cellSize
    y = event.y/data.cellSize
    for r in range(data.rows):
        for c in range(data.cols):
            if isClose(x, c) and isClose(y, r):
                data.points += [[round(x), round(y)]]

def isClose(pt1, pt2):
    return abs(pt1 - pt2) <= .1

def keyPressed(event, data):
    # use event.char and event.keysym
    pass

def timerFired(data):
    pass

def redrawAll(canvas, data):
    for r in range(data.rows):
        for c in range(data.cols):
            left = c*data.cellSize
            right = r*data.cellSize
            canvas.create_rectangle((left, right), 
                                    (left+data.cellSize, right+data.cellSize))
    canvas.create_line((5*data.cellSize, 0), 
                       (5*data.cellSize, data.height), 
                       width=3)
    canvas.create_line((0, 5*data.cellSize), 
                       (data.width, 5*data.cellSize),
                       width=3)

    for pt in data.points:
        radius = 3
        canvas.create_oval((pt[0]*data.cellSize-radius, 
                            pt[1]*data.cellSize-radius), 
                           (pt[0]*data.cellSize+radius, 
                            pt[1]*data.cellSize+radius),
                           fill="black")

    for i in range(len(data.points)-1):
        firstPt = data.points[i]
        secondPt = data.points[i+1]
        canvas.create_line((firstPt[0]*data.cellSize, 
                            firstPt[1]*data.cellSize), 
                           (secondPt[0]*data.cellSize, 
                            secondPt[1]*data.cellSize), 
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

    # ArduinoSerial = serial.Serial('/dev/cu.usbmodem1421', 9600)
    # time.sleep(2)
    # print("Serial communication established")

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
    redrawAll(canvas, data)
    # and launch the app
    root.mainloop()  # blocks until window is closed
    print("bye!")

run(500, 500)