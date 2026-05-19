#ifndef __STRATEGY_H__
#define __STRATEGY_H__

#include "hw6.h"
#include "htbl.h"

// given a board, calculate a score for the current game state
// scoring method given in writeup
int base_heuristic(board b);

// come up with your own (better?) heuristic
int custom_heuristic(board b);

// choose a move per minimax analysis
// use provided heuristic
// use hash table for memoization
// limit exploration of future moves to "depth"
// return score produced by recommended move, and that move via out-parameter
int minimax(htbl *ht, int(*heuristic)(board),
            board b, unsigned int depth,
            move *m);

#endif
