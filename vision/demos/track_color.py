import cv2
import numpy as np

cap = cv2.VideoCapture(0)

while(1):

    # Take each frame
    _, frame = cap.read()

    # Convert BGR to HSV
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Define color ranges we want in HSV, can get in python shell passing BGR

    # blue
    lower_blue = np.array([110,100,100])
    upper_blue = np.array([130,255,255])
    # green
    lower_green = np.array([50,100,100])
    upper_green = np.array([70,255,255])
    # red
    lower_red = np.array([0,0,255])
    upper_red = np.array([10,255,255])

    # Threshold the HSV image to get blue colors and green colors and red
    blue_mask = cv2.inRange(hsv, lower_blue, upper_blue)
    green_mask = cv2.inRange(hsv, lower_green, upper_green)
    red_mask = cv2.inRange(hsv, lower_red, upper_red)
    mask = blue_mask + green_mask + red_mask

    # Bitwise-AND mask and original image
    res = cv2.bitwise_and(frame,frame, mask= mask)

    # Draw contours
    (contours, _) = cv2.findContours(mask,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
    cv2.drawContours(frame, contours, -1, (0,255,0), 3)

    # Real image with contours
    cv2.imshow('frame',frame)
    # Threshold image, which is used in calculation
    cv2.imshow('mask',mask)
    # Final result filtering on colors of interest
    cv2.imshow('res',res)

    # Hit escape on window to end program...kinda buggy
    if cv2.waitKey(5) == 27:
        cv2.destroyAllWindows()
