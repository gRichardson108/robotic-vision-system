# import the necessary packages
from scipy.spatial import distance as dist
import imutils
from imutils import perspective
from imutils import contours
import argparse
import numpy as np
import cv2
from boundingbox import *
from objectdetection import *


# load our input image, convert it to grayscale, and blur it slightly
image = cv2.imread("test3.jpg")
gray = gray_image(image)


# perform edge detection, then perform a dilation + erosion to
# close gaps in between object edges
edged = edge_image(gray)

# find contours in the edge map
cnts = cv2.findContours(edged.copy(), cv2.RETR_EXTERNAL,
                        cv2.CHAIN_APPROX_SIMPLE)

cnts = cnts[0]

# sort the contours from left-to-right
# initialize the bounding box point colors
(cnts, _) = contours.sort_contours(cnts)
colors = ((0, 0, 255), (240, 0, 159), (255, 0, 0), (255, 255, 0))

# loop over the contours individually
# and draw bounding box for each contour
for (i, c) in enumerate(cnts):

    # if the contour is not sufficiently large, ignore it
    if cv2.contourArea(c) < 100:
        continue

    box = compute_box(c)                                # compute bounding box points of contour
    cv2.drawContours(image, [box], -1, (0, 255, 0), 2)  # draws the bounding box
    rect = order_box_points(box)                        # then order the points  of box

    # print coords of box
    print_box_coords(rect)

    # drawing colored circles at each edge of box
    for ((x, y), color) in zip(rect, colors):               # (x,y) matches with rect,  color matches with colors
        cv2.circle(image, (int(x), int(y)), 5, color, -1)   # draw circles filled in

    # draw the object num at the top-left corner
    cv2.putText(image, "Object #{}".format(i + 1),
                (int(rect[0][0] - 15), int(rect[0][1] - 15)),
                cv2.FONT_HERSHEY_SIMPLEX, 0.55, (255, 255, 255), 2)

    # show the image
    cv2.imshow("Image", image)
    cv2.waitKey(0)