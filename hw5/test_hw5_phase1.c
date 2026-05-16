#include <criterion/criterion.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "locations.h"
#include "hw5.h"

// ======== tests

Test(hw5_board_empty, board_empty_00, .timeout=2)
{
  board b = board_empty();
  cr_assert(b.white_envoy==0 &&
	    b.white_queen==0 &&
	    b.white_bishop==0 &&
	    b.white_knight==0 &&
	    b.white_sentry==0 &&
	    b.black_envoy==0 &&
	    b.black_queen==0 &&
	    b.black_bishop==0 &&
	    b.black_knight==0 &&
	    b.black_sentry==0);
}

Test(hw5_board_new, board_empty_00, .timeout=2)
{
  board b = board_new();
  cr_assert(b.white_envoy==LOC_c1 &&
	    b.whose_turn==COLOR_white);
}

Test(hw5_file, file_00, .timeout=2)
{
  cr_assert(file(LOC_c1)=='c');
}

Test(hw5_rank, rank_00, .timeout=2)
{
  cr_assert(rank(LOC_c1)==1);
}

Test(hw5_loc_str, loc_str_00, .timeout=2)
{
  cr_assert(!strcmp("a2",loc_str(LOC_a2)));
}

Test(hw5_str_loc, str_loc_00, .timeout=2)
{
  cr_assert(LOC_b4==str_loc("b4"));
}

Test(hw5_char_piece, char_piece_00, .timeout=2)
{
  cr_assert(char_piece('B')==PIECE_bb);
}

Test(hw5_pieces_white, pieces_white_00, .timeout=2)
{
  board b = board_empty();
  cr_assert(!pieces_white(b));
}

Test(hw5_pieces_black, pieces_black_00, .timeout=2)
{
  board b = board_empty();
  cr_assert(!pieces_black(b));
}

Test(hw5_pieces_all, pieces_all_00, .timeout=2)
{
  board b = board_empty();
  cr_assert(!pieces_all(b));
}

Test(hw5_is_white, is_white_00, .timeout=2)
{
  cr_assert(is_white(PIECE_ws));
}

Test(hw5_is_black, is_black_00, .timeout=2)
{
  cr_assert(is_black(PIECE_bs));
}

Test(hw5_is_occupied, is_occupied_00, .timeout=2)
{
  board b = board_empty();
  cr_assert(!is_occupied(b,LOC_g8));
}

Test(hw5_is_unoccupied, is_unoccupied_00, .timeout=2)
{
  board b = board_empty();
  cr_assert(is_unoccupied(b,LOC_g8));
}

Test(hw5_shadow_realm, shadow_realm_00, .timeout=2)
{
  cr_assert(!shadow_realm(LOC_h8));
}

Test(hw5_border, border_00, .timeout=2)
{
  cr_assert(border(LOC_h8));
}

Test(hw5_piece_at, piece_at_00, .timeout=2)
{
  board b = board_empty();
  cr_assert(piece_at(b,LOC_b2)==PIECE_none);
}

Test(hw5_color_at, color_at_00, .timeout=2)
{
  board b = board_empty();
  cr_assert(color_at(b,LOC_b2)==COLOR_none);
}

Test(hw5_put_piece, put_piece_00, .timeout=2)
{
  board b = board_empty();
  put_piece(&b,LOC_a2,PIECE_wq);
  cr_assert(b.white_queen==LOC_a2);
}

Test(hw5_unconditionally_put_piece, unconditionally_put_piece_00, .timeout=2)
{
  board b = board_empty();
  unconditionally_put_piece(&b,LOC_a2,PIECE_wq);
  cr_assert(b.white_queen==LOC_a2);
}

Test(hw5_bishop_moves, bishop_moves_00, .timeout=2)
{
  board b = board_empty();
  b.whose_turn = COLOR_white;
  put_piece(&b,LOC_a1,PIECE_wb);
  cr_assert(bishop_moves(b,LOC_a1));
}

Test(hw5_sentry_moves, sentry_moves_00, .timeout=2)
{
  board b = board_empty();
  b.whose_turn = COLOR_white;
  put_piece(&b,LOC_a1,PIECE_ws);
  cr_assert(sentry_moves(b,LOC_a1));
}

Test(hw5_queen_moves, queen_moves_00, .timeout=2)
{
  board b = board_empty();
  b.whose_turn = COLOR_white;
  put_piece(&b,LOC_a1,PIECE_wq);
  cr_assert(queen_moves(b,LOC_a1));
}

Test(hw5_winner, winner_00, .timeout=2)
{
  board b = board_new();
  cr_assert(winner(b)==COLOR_none);
}

