from PIL import Image
import sys

filename = str(sys.argv[1])
width = int(sys.argv[2])
height = int(sys.argv[3])

array = []

mode = "RGB"
if mode == "RGB":
	valuesPerPixel = 3

if mode == "RGBA":
	valuesPerPixel = 4
	""", array[(i*valuesPerPixel+3)]"""

with open(filename) as f:
    array = [[int(x) for x in line.split()] for line in f][0]

print len(array)
"""print array"""

data = [];

for i in range(0, len(array)/valuesPerPixel):
    data.append(tuple([array[i*valuesPerPixel], array[(i*valuesPerPixel)+1], array[(i*valuesPerPixel+2)] ]))   

print len(data)
"""print data"""

newFile = filename + ".png"

im = Image.new("RGB", (width, height))
im.putdata(data)
im.save(newFile, "PNG")

print "created " + newFile
