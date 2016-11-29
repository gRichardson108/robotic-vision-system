import cv2

def gray_image(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    return cv2.GaussianBlur(gray, (7, 7), 0)

def edge_image(image):
    edged = cv2.Canny(image, 50, 100)
    edged = cv2.dilate(edged, None, iterations=1)
    return cv2.erode(edged, None, iterations=1)