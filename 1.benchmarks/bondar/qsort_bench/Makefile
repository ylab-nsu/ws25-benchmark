gen_data:
	python3 rand_gen.py

sort_mcpy:
	gcc -O0 -o sort sort_memcpy_with_offset.c

sort_mcpy_gprof: 
	gcc -pg -o sort sort_memcpy_with_offset.c

sort_xor: 
	gcc -O0 -o sort sort_memcpy_xor.c

sort_xor_gprof: 
	gcc -pg -o sort sort_memcpy_xor.c

clean:
	rm sort gmon.out