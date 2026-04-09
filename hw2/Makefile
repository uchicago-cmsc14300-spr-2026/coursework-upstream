.PHONY: clean

phase1: hw2.h hw2.c test_hw2_phase1.c
	clang -Wall -o test_hw2_phase1 hw2.c test_hw2_phase1.c -lcriterion -lm

phase2: hw2.h hw2.c test_hw2_phase2.c
	clang -Wall -o test_hw2_phase2 hw2.c test_hw2_phase2.c -lcriterion -lm

clean:
	rm -f a.out test_hw2_phase[12]

