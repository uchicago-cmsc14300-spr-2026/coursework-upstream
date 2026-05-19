.PHONY: clean

phase1: hw6.h hw6.c locations.h strategy.h strategy.c htbl.h htbl.c test_hw6_phase1.c
	clang -Wall -o test_hw6_phase1 hw6.c htbl.c strategy.c test_hw6_phase1.c -lcriterion -lm

phase2: hw6.h hw6.c locations.h strategy.h strategy.c htbl.h htbl.c test_hw6_phase2.c
	clang -Wall -o test_hw6_phase2 hw6.c htbl.c strategy.c test_hw6_phase2.c -lcriterion -lm

cornercase: hw6.h hw6.c locations.h htbl.h htbl.c strategy.h strategy.c cornershell.c
	clang -Wall -g -o cornercase hw6.c htbl.c strategy.c cornershell.c -lm

clean:
	rm -rf a.out test_hw6_phase[12] cornercase cornercase.dSYM

