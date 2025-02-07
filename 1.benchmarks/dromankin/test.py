import matplotlib.pyplot as plt
import numpy as np
import sys

CONST = int(sys.argv[1])
file = open("out3_fmadd.txt", "r")
file2 = open("banana_out3_fmadd.txt", "r")
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
plt.plot(x, y, 'r', label='lichee')
plt.plot(x, y2, color = 'g', label='banana')
plt.title("fmadd", fontsize = 20)
plt.grid(True)
plt.ylabel('time(s)', fontsize = 15)
plt.xlabel('cycle iterations', fontsize = 15)

plt.ylim([0, 1])
plt.legend()
plt.savefig('out_fmadd.png')
file.close()
file2.close()



file = open("out3_fmsub.txt", "r")
file2 = open("banana_out3_fmsub.txt", "r")
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
plt.plot(x, y, 'r', label='lichee')
plt.plot(x, y2, color = 'g', label='banana')
plt.title("fmsub", fontsize = 20)
plt.grid(True)
plt.ylabel('time(s)', fontsize = 15)
plt.xlabel('cycle iterations', fontsize = 15)

plt.ylim([0, 1])
plt.legend()
plt.savefig('out_fmsub.png')
file.close()
file2.close()


file = open("out3_fmadd_asm.txt", "r")
file2 = open("banana_out3_fmadd_asm.txt", "r")
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
plt.plot(x, y, 'r', label='lichee')
plt.plot(x, y2, color = 'g', label='banana')
plt.title("fmadd(asm)", fontsize = 20)
plt.grid(True)
plt.ylabel('time(s)', fontsize = 15)
plt.xlabel('cycle iterations', fontsize = 15)

plt.ylim([0, 1])
plt.legend()
plt.savefig('out_fmadd_asm.png')
file.close()
file2.close()

file = open("out3_fmsub_asm.txt", "r")
file2 = open("banana_out3_fmsub_asm.txt", "r")
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
plt.plot(x, y, 'r', label='lichee')
plt.plot(x, y2, color = 'g', label='banana')
plt.title("fmsub(asm)", fontsize = 20)
plt.grid(True)
plt.ylabel('time(s)', fontsize = 15)
plt.xlabel('cycle iterations', fontsize = 15)

plt.ylim([0, 1])
plt.legend()
plt.savefig('out_fmsub_asm.png')
file.close()
file2.close()


