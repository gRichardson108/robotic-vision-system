import numpy as np
import cv2

cap = cv2.VideoCapture('../testData/vtest.avi')
kernel = np.ones((2,2), np.uint8)
fgbg = cv2.createBackgroundSubtractorKNN(detectShadows=True)
while(1):
    ret, frame = cap.read()
    fgmask = fgbg.apply(frame)
    cv2.imshow('regular',frame)
    fgmask = cv2.morphologyEx(fgmask, cv2.MORPH_OPEN, kernel, iterations=4)
    cv2.imshow('frame',fgmask)
    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break
cap.release()
cv2.destroyAllWindows()
