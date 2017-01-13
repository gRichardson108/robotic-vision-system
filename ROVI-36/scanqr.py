import cv2
import zbar
from PIL import Image

# Init
cv2.namedWindow("#feed")
cap = cv2.VideoCapture(0)

scanner = zbar.ImageScanner()
scanner.parse_config('enable')

# Capture frames
while True:
    ret, output = cap.read()
    if not ret:
      continue
    gray = cv2.cvtColor(output, cv2.COLOR_BGR2GRAY, dstCn=0)
    pil = Image.fromarray(gray)
    width, height = pil.size
    raw = pil.tobytes()
    image = zbar.Image(width, height, 'Y800', raw)
    scanner.scan(image)

    # Track & output data
    for symbol in image:
        print 'decoded', symbol.type, 'symbol', '"%s"' % symbol.data
        loc = symbol.location
        cv2.rectangle(output, (loc[0][0], loc[0][1]), (loc[2][0], loc[2][1]), (255,0,0), 2)

    cv2.imshow("#feed", output)

    # Press q to quit
    keypress = cv2.waitKey(1) & 0xFF
    if keypress == ord('q'):
        break

# Cleanup
cap.release()
cv2.destroyAllWindows()
