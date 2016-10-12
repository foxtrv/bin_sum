run: a.out input
	./a.out input

a.out: bin_sum.c
	gcc bin_sum.c -o a.out
