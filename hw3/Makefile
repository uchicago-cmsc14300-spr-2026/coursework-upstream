.PHONY: clean

phase1: hw3.h hw3.c test_hw3_phase1.c
	clang -Wall -o test_hw3_phase1 hw3.c test_hw3_phase1.c -lcriterion -lm

phase2: hw3.h hw3.c test_hw3_phase2.c
	clang -Wall -o test_hw3_phase2 hw3.c test_hw3_phase2.c -lcriterion -lm

clean:
	rm -f a.out test_hw3_phase[12]

