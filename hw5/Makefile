.PHONY: clean

phase1: hw5.h hw5.c test_hw5_phase1.c
	clang -Wall -o test_hw5_phase1 hw5.c test_hw5_phase1.c -lcriterion -lm

phase2: hw5.h hw5.c test_hw5_phase2.c
	clang -Wall -o test_hw5_phase2 hw5.c test_hw5_phase2.c -lcriterion -lm

clean:
	rm -f a.out test_hw5_phase[12]

