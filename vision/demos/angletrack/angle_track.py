from SimpleCV import *
from matplotlib import pyplot
from math import degrees, pi
from numpy import arctan2
import serial


def foo(image):
    return image.meanColor()

def camshift():
    ser = serial.Serial("/dev/ttyACM0")
    print ser.name

    lastTime = time.time()
    cam = Camera()
    img = cam.getImage()
    center_point = (img.width/2, 9*img.height/10)
    circleLayer = DrawingLayer((img.width,img.height))
    circleLayer.circle(center_point, 10, Color.GOLD, 1, True)
    d = Display(img.size())
    selectionHue = False
    while selectionHue == False:
        bb1 = getBoundingBoxFromUser(cam,d)
        print "Bounding Box Selected"
        img = cam.getImage()
        selectedRegion = img.regionSelect(bb1[0],bb1[1],bb1[2]+bb1[0], bb1[3]+bb1[2])
        selectionHue = getHueValue(selectedRegion)

    selectedRegion.save("region-select.png")    

    minHue = np.maximum(selectionHue - 10, 0)
    maxHue = np.minimum(selectionHue + 10, 180)#openCV does hue from 0 to 180
    print "SelectionHue: " + str(selectionHue) + " minHue: " + str(minHue) + " maxHue: " + str(maxHue)
    
    fs1=[]
    while d.isNotDone():
        try:
            reset = d.mouseRight
            if (reset):
                print "Resetting bounding box"
                selectionHue = False
                while selectionHue == False:
                    bb1 = getBoundingBoxFromUser(cam,d)
                    print "Bounding Box Selected"
                    img = cam.getImage()
                    selectedRegion = img.regionSelect(bb1[0],bb1[1],bb1[2]+bb1[0], bb1[3]+bb1[2])
                    selectionHue = getHueValue(selectedRegion)

                selectedRegion.save("region-select.png")

                minHue = np.maximum(selectionHue - 10, 0)
                maxHue = np.minimum(selectionHue + 10, 180)#openCV does hue from 0 to 180
                print "SelectionHue: " + str(selectionHue) + " minHue: " + str(minHue) + " maxHue: " + str(maxHue)
     
            
            img1 = cam.getImage()
            fs1 = img1.track("camshift",fs1,img,bb1,num_frames=5, nframes=60, lower=(minHue, 40, 20), upper=(maxHue, 255, 255))
            coordset = fs1[-1]
            angleLayer = DrawingLayer((img.width, img.height))
            angleLayer.lines([center_point, (coordset.x, coordset.y)], Color.RED, True, -1, 2)
            angleLayer.lines([(0, center_point[1]), (img.width, center_point[1])], Color.MAROON, True, -1, 2)
            angle = degrees(arctan2(coordset.x - center_point[0], coordset.y - center_point[1]) - pi/2.0) % 360
            
            fs1.drawBB()
            #fs1.drawPath()
            fs1.draw()
            fs1.showCoordinates()
            fs1.showSizeRatio()
            img1.addDrawingLayer(circleLayer)
            img1.addDrawingLayer(angleLayer)
            img1.applyLayers()
            img1.drawText("Angle: " + str(angle))
            img1.show()


            currentTime = time.time() - lastTime
            if (currentTime > .05):
                coordString = "<" + str(coordset.x - center_point[0]) + ", " + str(coordset.y - center_point[1]) + ", 0>\n"
                ser.write(coordString)
                lastTime = time.time()
                currentTime = lastTime
                
        except KeyboardInterrupt:
            print "\nTracked frames: ",
            print fs1.trackLength()
            print fs1.processTrack(foo)
            ser.close()
            break
        except Exception:
            if (ser.is_open):
                ser.close()

def showCroppedImage():
    cam = Camera(1)
    img = cam.getImage()
    d = Display(img.size())
    img.show()
    img = selectImageByBox(img, d)
    img.show()
    
def getBoundingBoxFromUser(cam, display):
    p1 = None
    p2 = None
    img = cam.getImage()
    while display.isNotDone():
        try:
            img = cam.getImage()
            img.save(display)
            dwn = display.leftButtonDownPosition()
            up = display.leftButtonUpPosition()

            if dwn:
                p1 = dwn
            if up:
                p2 = up
                break

            time.sleep(0.05)
        except KeyboardInterrupt:
            break
    print p1,p2
    if not p1 or not p2:
        return None

    xmax = np.max((p1[0],p2[0]))
    xmin = np.min((p1[0],p2[0]))
    ymax = np.max((p1[1],p2[1]))
    ymin = np.min((p1[1],p2[1]))
    return (xmin,ymin,xmax-xmin,ymax-ymin)

def selectImageByBox(image, display):
    p1 = None
    p2 = None
    while display.isNotDone():
        try:
            image.save(display)
            dwn = display.leftButtonDownPosition()
            up = display.leftButtonUpPosition()

            if dwn:
                p1 = dwn
            if up:
                p2 = up
                break

            time.sleep(0.05)
        except KeyboardInterrupt:
            break
    print p1,p2
    if not p1 or not p2:
        return None

    xmax = np.max((p1[0],p2[0]))
    xmin = np.min((p1[0],p2[0]))
    ymax = np.max((p1[1],p2[1]))
    ymin = np.min((p1[1],p2[1]))
    return image.regionSelect(xmin, ymin, xmax, ymax)

def getHueValue(image):
    peaks = image.huePeaks()
    print(peaks)
    if (len(peaks) >= 1):
        peaks = sorted(peaks, key=lambda p: p[1], reverse=True)
        print(peaks)
        return peaks[0][0]
    else: 
        return False

camshift()
#showCroppedImage()