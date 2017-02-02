from SimpleCV import *
from matplotlib import pyplot
from math import degrees, pi
from numpy import arctan2

def foo(image):
    return image.meanColor()

def camshift():
    cam = Camera()
    img = cam.getImage()
    histogram = img.hueHistogram()
    print histogram
    pyplot.plot(histogram)
    pyplot.show()
    center_point = (img.width/2, img.height/2)
    circleLayer = DrawingLayer((img.width,img.height))
    circleLayer.circle(center_point, 10)
    d = Display(img.size())
    bb1 = getBBFromUser(cam,d)
    print "Bounding Box Selected"
    fs1=[]
    while True:
        try:
            img1 = cam.getImage()
            fs1 = img1.track("camshift",fs1,img,bb1,num_frames=5, nframes=60, lower=(120, 40, 40), upper=(180, 200, 200))
            coordset = fs1[-1]
            angleLayer = DrawingLayer((img.width, img.height))
            angleLayer.lines([center_point, (coordset.x, coordset.y)])
            angleLayer.lines([(0, img.height/2), (img.width, img.height/2)])
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
        except KeyboardInterrupt:
            print "\nTracked frames: ",
            print fs1.trackLength()
            print fs1.processTrack(foo)
            break

def getBBFromUser(cam, d):
    p1 = None
    p2 = None
    img = cam.getImage()
    while d.isNotDone():
        try:
            img = cam.getImage()
            img.save(d)
            dwn = d.leftButtonDownPosition()
            up = d.leftButtonUpPosition()

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
    print xmin,ymin,xmax,ymax
    return (xmin,ymin,xmax-xmin,ymax-ymin)

camshift()
