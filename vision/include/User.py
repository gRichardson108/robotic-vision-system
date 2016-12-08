from SimpleCV import *
from matplotlib import pyplot
from math import degrees, pi
from numpy import arctan2

def getBoundingBoxFromUser(cam, display):
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

