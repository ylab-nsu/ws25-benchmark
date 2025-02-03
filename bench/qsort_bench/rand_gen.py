#!/usr/bin/env python3
import random

ARRAY_SIZE = 1000000
filename = "random_data.h"

with open(filename, "w") as f:
    f.write("// This header file is auto-generated\n")
    f.write("#ifndef RANDOM_DATA_H\n")
    f.write("#define RANDOM_DATA_H\n\n")
    f.write("#define BASE_ARRAY_SIZE {}\n\n".format(ARRAY_SIZE))
    f.write("static const int base_array[BASE_ARRAY_SIZE] = {\n")

    for i in range(ARRAY_SIZE):
        if i % 10 == 0:
            f.write("    ")
        f.write("{:d}".format(random.randint(-1000000, 1000000)))
        if i != ARRAY_SIZE - 1:
            f.write(", ")
        if i % 10 == 9:
            f.write("\n")
    f.write("\n};\n\n")
    f.write("#endif // RANDOM_DATA_H\n")
