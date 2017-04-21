import serial

class SerialCommunicator:
    class __SerialCommunicator:
        def __init__(self, devicepath, baud = 9600):
            self.ser = serial.Serial(devicePath, baud)

        def write(self, data):
            self.ser.write(data)

        def is_open(self):
            return self.ser.is_open()
    
    instance = None
    def __init__(self, devicepath, baud = 9600):
        if not SerialCommunicator.instance:
            SerialCommunicator.instance = SerialCommunicator.__SerialCommunicator(devicepath, baud)
        
    def __getattr__(self, name):
        return getattr(self.instance, name)
