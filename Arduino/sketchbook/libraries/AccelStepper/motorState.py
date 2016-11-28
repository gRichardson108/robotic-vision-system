from nanpy import ArduinoApi
from nanpy import SerialManager
from nanpy import Stepper

#Establish connection
connection = SerialManager()
a = ArduinoApi(connection = connection)
