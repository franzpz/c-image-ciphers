from PIL import Image
import sys

basicFilename = "image.png";

for i in range(2, 300, 10):
	im = Image.new("RGB", (i, i))
	data = [];
	for j in range(0, i*i):
		if (i%2) == 0:
			data.append(tuple([66, 244, 125]))
		elif (i%5) == 0:
			data.append(tuple([66, 75, 244]))
		elif (i%3) == 0:
			data.append(tuple([244, 66, 89]))
		else:
			data.append(tuple([13, 34, 45]))

	im.putdata(data)
	im.save(str(i) + "x" + str(i) + basicFilename, "PNG")