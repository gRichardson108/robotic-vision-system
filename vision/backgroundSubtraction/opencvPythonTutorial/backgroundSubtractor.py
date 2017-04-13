import numpy as np
import cv2

cap = cv2.VideoCapture(0)
kernel = np.ones((2,2), np.uint8)
fgbg = cv2.createBackgroundSubtractorMOG2(100,200,detectShadows=True)
fgbg.setHistory(30)
blobDetector = cv2.SimpleBlobDetector_create()

ret, current_frame = cap.read()
previous_frame = current_frame

while(1):
    current_frame_gray = cv2.cvtColor(current_frame, cv2.COLOR_BGR2GRAY)
    previous_frame_gray = cv2.cvtColor(previous_frame, cv2.COLOR_BGR2GRAY)
    frame_diff = cv2.absdiff(current_frame_gray, previous_frame_gray)
    cv2.imshow('frame diff', frame_diff)

    fgmask = fgbg.apply(current_frame)
    cv2.imshow('regular',current_frame)
    fgmask = cv2.morphologyEx(fgmask, cv2.MORPH_OPEN, kernel, iterations=1)
    cv2.imshow('fgmask',fgmask)

    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break

    previous_frame = current_frame.copy()
    ret, current_frame = cap.read()
cap.release()
cv2.destroyAllWindows()
