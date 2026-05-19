#include <criterion/criterion.h>
#include <stdio.h>
#include "locations.h"
#include "hw6.h"
#include "htbl.h"
#include "strategy.h"

// ======== tests

Test(hw6_knight_moves, knight_moves_00, .timeout=2)
{
  board b = board_empty();
  b.whose_turn = COLOR_white;
  put_piece(&b,LOC_a1,PIECE_wk);
  cr_assert(knight_moves(b,LOC_a1));
}

Test(hw6_envoy_moves, envoy_moves_00, .timeout=2)
{
  board b = board_empty();
  b.whose_turn = COLOR_white;
  put_piece(&b,LOC_a1,PIECE_we);
  cr_assert(envoy_moves(b,LOC_a1));
}

Test(hw6_possible_moves, possible_moves_00, .timeout=2)
{
  board b = board_empty();
  b.whose_turn = COLOR_white;
  put_piece(&b,LOC_a1,PIECE_wq);
  cr_assert(possible_moves(b));
}

Test(hw6_perform_move, perform_move_00, .timeout=2)
{
  board b = board_empty();
  b.whose_turn = COLOR_white;
  put_piece(&b,LOC_a1,PIECE_wq);
  move m = {LOC_a1, LOC_b2};
  cr_assert(perform_move(&b,m));
}

Test(hw6_bucket_cons, bucket_cons_00, .timeout=2)
{
  move m = {1, 2};
  cr_assert(bucket_cons(board_new(), 1, 0,
                        m, 123, NULL));
}

Test(hw6_bucket_match, bucket_match_00, .timeout=2)
{
  move m = {1, 2};
  bucket *b = bucket_cons(board_new(), 1, 0,
                          m, 123, NULL);
  cr_assert(!bucket_match(board_new(), 2, 456, b));
}

Test(hw6_bucket_free, bucket_free_00, .timeout=2)
{
  bucket_free(NULL);
  cr_assert(1);  // that it didn't crash
}

Test(hw6_htbl_new, htbl_new_00, .timeout=2)
{
  cr_assert(htbl_new(10));
}

Test(hw6_htbl_insert, htbl_insert_00, .timeout=2)
{
  htbl *ht = htbl_new(10);
  move m = {1, 2};
  htbl_insert(board_new(), 1, 0,
              m, ht);
  cr_assert(1);  // that it didn't crash
}

Test(hw6_htbl_get, htbl_get_00, .timeout=2)
{
  htbl *ht = htbl_new(10);
  move m;
  int score;
  cr_assert(!htbl_get(board_new(), 1, &score,
                      &m, ht));
}

Test(hw6_htbl_free, htbl_free_00, .timeout=2)
{
  htbl *ht = htbl_new(10);
  htbl_free(ht);
  cr_assert(1);  // that it didn't crash
}

Test(hw6_base_heuristic, base_heuristic_00, .timeout=2)
{
  cr_assert(base_heuristic(board_new())==0);
}

Test(hw6_custom_heuristic, custom_heuristic_00, .timeout=2)
{
  board b = board_empty();
  b.whose_turn = COLOR_white;
  put_piece(&b,LOC_c1,PIECE_be);
  cr_assert(custom_heuristic(b)<0);
}

Test(hw6_minimax, minimax_00, .timeout=2)
{
  move m;
  cr_assert(minimax(htbl_new(10), base_heuristic,
                    board_new(), 0, &m)==0);
}
