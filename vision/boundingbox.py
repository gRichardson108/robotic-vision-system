# import the necessary packages
from scipy.spatial import distance as dist
import imutils
from imutils import perspective
from imutils import contours
import argparse
import numpy as np
import cv2

def compute_box(cnt):
    # compute the rotated bounding box of the contour, then
    # draw the contours
    box = cv2.minAreaRect(cnt)                                                  # returns a box structure
    box = cv2.cv.BoxPoints(box) if imutils.is_cv2() else cv2.boxPoints(box)     # takes a box structure to get points
    box = np.array(box, dtype="int")                                            # creates array of coord points
    return box

def order_box_points(pts):
        # sort the points based on their x-coordinates
        xSorted = pts[np.argsort(pts[:, 0]), :]

        # grab the left-most and right-most points from the sorted
        # x-cooroodinate points
        leftMost = xSorted[:2, :]
        rightMost = xSorted[2:, :]

        # now, sort the left-most coordinates according to their
        # y-coordinates so we can grab the top-left and bottom-left
        # points, respectively
        leftMost = leftMost[np.argsort(leftMost[:, 1]), :]
        (tl, bl) = leftMost

        # now that we have the top-left coordinate, use it as an
        # anchor to calculate the Euclidean distance between the
        # top-left and right-most points; by the Pythagorean
        # theorem, the point with the largest distance will be
        # our bottom-right point
        D = dist.cdist(tl[np.newaxis], rightMost, "euclidean")[0]
        (br, tr) = rightMost[np.argsort(D)[::-1], :]

        # return the coordinates in top-left, top-right,
        # bottom-right, and bottom-left order
        return np.array([tl, tr, br, bl], dtype="float32")

def print_box_coords(box):
    # print out the re-ordered coordinates of object
    print(box.astype("int"))
    print("")