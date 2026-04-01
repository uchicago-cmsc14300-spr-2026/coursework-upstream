.PHONY: clean

phase1: hw1.h hw1.c test_hw1_phase1.c
	clang -Wall -o test_hw1_phase1 hw1.c test_hw1_phase1.c -lcriterion -lm

phase2: hw1.h hw1.c test_hw1_phase2.c
	clang -Wall -o test_hw1_phase2 hw1.c test_hw1_phase2.c -lcriterion -lm

clean:
	rm -f a.out test_hw1_phase[12]

