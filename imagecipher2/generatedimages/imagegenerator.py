from PIL import Image
import sys

"""
basicFilename = "image.png";

for i in range(2, 300, 10):
	im = Image.new("RGBA", (i, i))
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
"""

basicFilename = "image.png";

im = Image.new("RGBA", (2, 4))
data = [];
for j in range(0, 8):
		data.append(tuple([66, 244, 125, 255]))

im.putdata(data)
im.save(str(2) + "x" + str(4) + basicFilename, "PNG")



im = Image.new("RGBA", (3, 3))
data = [];
for j in range(0, 9):
		data.append(tuple([66, 244, 125, 255]))

im.putdata(data)
im.save(str(3) + "x" + str(3) + basicFilename, "PNG")