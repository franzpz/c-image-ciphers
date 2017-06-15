from PIL import Image
import sys

filename = str(sys.argv[1])
image = Image.open(filename)
pix = image.load()

mode = "RGBA"

if len(sys.argv) == 3:
	mode = str(sys.argv[2]);

x = 0
y = 0

imagePixelValues = list()

for y in range(0, image.size[1]):
	for x in range(0, image.size[0]):
		imagePixelValues.append(pix[x,y][0])
		imagePixelValues.append(pix[x,y][1])
		imagePixelValues.append(pix[x,y][2])
		if(mode == "RGBA"):
			imagePixelValues.append(pix[x,y][3])

print "size of image"
print len(imagePixelValues)
"""print imagePixelValues"""

thefile = open(filename + 'bytes.txt', 'w')

for val in imagePixelValues:
  thefile.write("%d " % val)

thefile.close();

print "created file: " + thefile.name