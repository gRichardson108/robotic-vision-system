import numpy as np
import cv2

history = 10
thresh = 8000

cap = cv2.VideoCapture(1)
kernel = np.ones((2,2), np.uint8)
fgbg = cv2.createBackgroundSubtractorKNN(history, thresh, True)
fgbg.setShadowValue(0)
blobDetectorParams = cv2.SimpleBlobDetector_Params()
detector = cv2.SimpleBlobDetector_create(blobDetectorParams)


ret, current_frame = cap.read()
previous_frame = current_frame

while(1):
    current_frame_gray = cv2.cvtColor(current_frame, cv2.COLOR_BGR2GRAY)
    previous_frame_gray = cv2.cvtColor(previous_frame, cv2.COLOR_BGR2GRAY)

    fgmask = fgbg.apply(current_frame)
    cv2.imshow('fgmask',fgmask)
    fgmask = cv2.morphologyEx(fgmask, cv2.MORPH_OPEN, kernel, iterations=4)
    fgmask = cv2.morphologyEx(fgmask, cv2.MORPH_DILATE, kernel, iterations=4)
    fgmask, contours, hierarchy = cv2.findContours(fgmask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    cv2.imshow('regular',current_frame)
    cv2.drawContours(fgmask, contours, 0, (0, 255,0), 3)
    cv2.imshow('contours', fgmask)

    #keypoints = detector.detect(fgmask)
    #im_keypoints = np.array([])
    #im_keypoints = cv2.drawKeypoints(fgmask, keypoints, im_keypoints,(0,0,255), cv2.DRAW_MATCHES_FLAGS_DEFAULT)
    #cv2.imshow("keypoints", im_keypoints)


    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break

    previous_frame = current_frame.copy()
    ret, current_frame = cap.read()
cap.release()
cv2.destroyAllWindows()
