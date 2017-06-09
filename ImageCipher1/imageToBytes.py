from PIL import Image
import sys

filename = str(sys.argv[1])
image = Image.open(filename)
pix = image.load()

x = 0
y = 0

imagePixelValues = list()

for y in range(0, image.size[1]):
	for x in range(0, image.size[0]):
		imagePixelValues.append(pix[x,y][0])
		imagePixelValues.append(pix[x,y][1])
		imagePixelValues.append(pix[x,y][2])

print "size of image"
print len(imagePixelValues)
print imagePixelValues

thefile = open(filename + 'bytes.txt', 'w')

for val in imagePixelValues:
  thefile.write("%d " % val)

thefile.close();