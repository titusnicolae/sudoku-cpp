from PIL import Image
from PIL import ImageFont
from PIL import ImageDraw 
from os import listdir


square = 109
w1, w2 = 10, 4
ox, oy = 0, 0

ww=[]
ct = 0
X, Y = 1400, 2100
for i in range(0,10):
  if i%3==0:
    ww.append((ct, ct+w1))
    ct+=w1
  else:
    ww.append((ct, ct+w2))
    ct+=w2
  ct+=square
W = ww[-1][1]

puzzles = [(filename, eval(''.join(open("output/"+filename).readlines()))) for filename in sorted(listdir("output")) if filename.endswith("puzzle")]

page = 0
for pp1, pp2 in [puzzles[i:i+2] for i in range(0,len(puzzles),2)]:
    ff1, ll1 = pp1
    ff2, ll2 = pp2
    img = Image.new("RGB", (X, Y), (255,255,255))
    draw = ImageDraw.Draw(img)
    font = ImageFont.truetype("/usr/share/fonts/truetype/ubuntu-font-family/Ubuntu-L.ttf", 110)
  
    ox, oy = (X-W)/2, 0
    for x1, x2 in ww:
      draw.rectangle(((ox+x1, oy), (ox+x2, oy+W)), fill="black")
      draw.rectangle(((ox, oy+x1), (ox+W, oy+x2)), fill="black")

    for a in enumerate(zip(ww, ll1)): 
      for b in enumerate(zip(ww, a[1][1])):
        i, j = a[0], b[0]
        xx = a[1][0]
        yy = b[1][0]
        if ll1[j][i]!=0:
          draw.text((ox+square/5+xx[1], oy+yy[1]-square/12), str(ll1[j][i]), (0, 0 ,0), font=font)

    ox, oy = (X-W)/2, Y-W
    for x1, x2 in ww:
      draw.rectangle(((ox+x1, oy), (ox+x2, oy+W)), fill="black")
      draw.rectangle(((ox, oy+x1), (ox+W, oy+x2)), fill="black")
  
    for a in enumerate(zip(ww, ll2)): 
      for b in enumerate(zip(ww, a[1][1])):
        i, j = a[0], b[0]
        xx = a[1][0]
        yy = b[1][0]
        if ll2[j][i]!=0:
          draw.text((ox+square/5+xx[1], oy+yy[1]-square/12), str(ll2[j][i]), (0, 0 ,0), font=font)

     
    img.save("sudoku%02d.png" % page)
    page+=1
