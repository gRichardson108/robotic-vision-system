import cv2
import numpy as np

c = cv2.VideoCapture(0)
_,f = c.read()

avg = np.float32(f)
alpha=0.001
mog2 = cv2.createBackgroundSubtractorMOG2(30,500,detectShadows=True)
countdown_reset = 30
snapshot_countdown = 0 #count down frames before we save a snapshot.
_,current_frame = c.read()
previous_frame = current_frame
while(1):
    _,f = c.read()

    _,current_frame = c.read()
    cv2.accumulateWeighted(previous_frame,avg,alpha)
    res = cv2.convertScaleAbs(avg)
    current_frame_gray = cv2.cvtColor(current_frame, cv2.COLOR_BGR2GRAY)
    res_gray = cv2.cvtColor(res, cv2.COLOR_BGR2GRAY)
    frame_diff = cv2.absdiff(current_frame_gray,res_gray)
    diff_mog2 = mog2.apply(frame_diff)

    cv2.imshow('absdiff',frame_diff)
    cv2.imshow('img',f)
    cv2.imshow('avg',res)
    cv2.imshow('diff_mog2', diff_mog2)

    k = cv2.waitKey(20)

    if k == 27:
        break
    if snapshot_countdown <= 0:
        previous_frame = current_frame
        snapshot_countdown = countdown_reset
    else:
        snapshot_countdown-= 1
cv2.destroyAllWindows()
c.release()
