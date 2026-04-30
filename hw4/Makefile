.PHONY: clean

phase1: hw4.h hw4.c test_hw4_phase1.c
	clang -Wall -o test_hw4_phase1 hw4.c test_hw4_phase1.c -lcriterion -lm

phase2: hw4.h hw4.c test_hw4_phase2.c
	clang -Wall -o test_hw4_phase2 hw4.c test_hw4_phase2.c -lcriterion -lm

clean:
	rm -f a.out test_hw4_phase[12]

