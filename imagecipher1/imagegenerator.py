from PIL import Image
import sys

basicFilename = "image.jpg";

for i in range(5, 400, 10):
	im = Image.new("RGB", (i, i))
	data = [];
	for j in range(0, i*i*3):
		if (i%2) == 0:
			data.append(tuple(66, 244, 125))
		elif (i%3) == 0:
			data.append(tuple(244, 66, 89))
		elif (i%5) == 0:
			data.append(tuple(66, 75, 244))
	im.putdata(data)
	im.save(i + "x" + i + basicFilename, "JPEG")