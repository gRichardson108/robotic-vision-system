import serial
import time

ser = serial.Serial("/dev/ttyACM0")

for x in range(0, 180):
	coordString = "<" + str(x) + "," + str(0) + ">\n"
	print x
	ser.write(coordString)
	print coordString
	time.sleep(.2)
