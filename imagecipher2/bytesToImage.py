from PIL import Image
import sys

filename = str(sys.argv[1])
width = int(sys.argv[2])
height = int(sys.argv[3])

array = []

with open(filename) as f:
    array = [[int(x) for x in line.split()] for line in f][0]

print len(array)
print array

data = [];

for i in range(0, len(array)/4):
    data.append(tuple([array[i*4], array[(i*4)+1], array[(i*4+2)], array[(i*4+3)]]))

print len(data)
print data

im = Image.new("RGBA", (width, height))
im.putdata(data)
im.save(filename + ".decrypted.png", "PNG")
