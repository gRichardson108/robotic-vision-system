from vehicle_counter import VehicleCounter
shape = (100,100)
boundingBox = ((20,20),(80,80))

x = VehicleCounter(shape, boundingBox)

outsideRect1 = ((0,0), (10,10))
outsideRect2 = ((5,5), (10,90))
outsideRect3 = ((90,2), (100,40))
outsideRect4 = ((90,90), (100,100))

insideRect = ((50,50), (60,60))
crossRect = ((0,0), (50,50))

rectlist = [outsideRect1, outsideRect2, outsideRect3, outsideRect4, insideRect, crossRect]

for i in range(len(rectlist)):
	print(x.check_rect_overlap(rectlist[i], boundingBox))
