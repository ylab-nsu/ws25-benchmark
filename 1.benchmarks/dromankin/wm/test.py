import matplotlib.pyplot as plt
import numpy as np
import sys

CONST = int(sys.argv[1])
file = open("out3.txt", "r")
file2 = open("banana_out3.txt", "r")
x = []
y = []
y2 = []
buf = []
min_val = 0
count = 1;
c = 0

for line in file:
	buf.append(float(line))
	c += 1
	if c == CONST:
		min_val = min(buf)
		y.append(min_val)
		x.append(count)
		count += 1000000
		c = 0
		buf = []
buf = []
c = 0
min_val = 0
for line in file2:
	buf.append(float(line))
	c += 1
	if c == CONST:
		min_val = min(buf)
		y2.append(min_val)
		c = 0

		buf = []


plt.figure().set_figwidth(15)
plt.plot(x, y, 'ro-', label='lichee')
plt.plot(x, y2, 'go-', label='banana')
plt.title("c.nop", fontsize = 20)
plt.grid(True)
plt.ylabel('time(s)', fontsize = 15)
plt.xlabel('operations', fontsize = 15)

plt.ylim([0, 1])
plt.legend()
plt.savefig('out_cnop.png')
file.close()
file2.close()
