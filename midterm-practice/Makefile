.PHONY: clean

practice: practice.h practice.c
	clang -Wall -o practice practice.c

solutions: practice.h practice-sample-solutions.c
	clang -Wall -o solutions practice-sample-solutions.c

clean:
	rm -f a.out practice solutions

