#include <criterion/criterion.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "locations.h"
#include "hw5.h"

// ======== helper

int p2_move_lt(move m1, move m2)
{
  if (m1.src<m2.src)
    return 1;
  else if (m1.src==m2.src && m1.dst<m2.dst)
    return 1;
  else
    return 0;
}

move_list *p2_ml_cons(loc_t src, loc_t dst, move_list *next)
{
  move_list *moves = malloc(sizeof(move_list));
  moves->m.src = src;
  moves->m.dst = dst;
  moves->next = next;
  return moves;
}

void p2_ml_free(move_list *moves)
{
  if (moves) {
    p2_ml_free(moves->next);
    free(moves);
  }
}

move_list *p2_ml_dup(move_list *moves)
{
  if (!moves)
    return NULL;
  else
    return p2_ml_cons(moves->m.src, moves->m.dst, p2_ml_dup(moves->next));
}

move_list *p2_ml_insert(move m1, move_list *moves)
{  
  if (!moves || p2_move_lt(m1,moves->m)) {
    return p2_ml_cons(m1.src, m1.dst, moves);
  } else {
    move_list *t = p2_ml_insert(m1,moves->next);
    moves->next = t;
    return moves;
  }    
}

move_list *p2_ml_sort(move_list *moves)
{
  if (!moves || !moves->next)
    return p2_ml_dup(moves);
  else
    return p2_ml_insert(moves->m, p2_ml_sort(moves->next));
}

int p2_ml_eq(move_list *moves1, move_list *moves2)
{
  if (!moves1 && !moves2)
    return 1;
  else if (!moves1 || !moves2)
    return 0;
  else
    return (moves1->m.src==moves2->m.src &&
	    moves1->m.dst==moves2->m.dst &&
	    p2_ml_eq(moves1->next,moves2->next));
}

void p2_ml_show(char *label, move_list *moves)
{
  if (label && label[0])
    printf("%s:\t",label);
  for (;moves;moves=moves->next)
    printf("(%llX,%llX):",moves->m.src,moves->m.dst);
  printf(".\n");
}

// order-insensitive move_list equality
int p2_ml_same_moves(move_list *moves1, move_list *moves2)
{
  move_list *sorted1 = p2_ml_sort(moves1);
  move_list *sorted2 = p2_ml_sort(moves2);
  //p2_ml_show("sorted1",sorted1);
  //p2_ml_show("sorted2",sorted2);
  int result = p2_ml_eq(sorted1,sorted2);
  p2_ml_free(sorted1);
  p2_ml_free(sorted2);
  return result;
}

// provide the number of moves, then locations in src/dst pairs
move_list *p2_ml(int n_locs, ...)
{
  if (n_locs==0)
    return NULL;
  move_list *moves = NULL;
  va_list args;
  move_list *curr;
  va_start(args, n_locs); // initialize the list, starting after 'count'
  for (int i=0; i<n_locs; i++) {
    loc_t src = va_arg(args, loc_t);
    loc_t dst = va_arg(args, loc_t);
    move_list *new_node = p2_ml_cons(src,dst,NULL);
    if (!moves) {
      curr  = new_node;
      moves = new_node;
    }
    else {
      curr->next = new_node;
      curr = curr->next;
    }
  }
  va_end(args);
  return moves;
}

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

Test(hw5_board_new, board_new_00, .timeout=2)
{
  board b = board_new();
  cr_assert(b.white_envoy==LOC_c1 &&
	    b.white_queen==LOC_c2 &&
	    b.white_bishop==(LOC_c3|LOC_c4) &&
	    b.white_knight==LOC_b1 &&
	    b.white_sentry==LOC_a1 &&
	    b.black_envoy==LOC_h6 &&
	    b.black_queen==LOC_g6 &&
	    b.black_bishop==(LOC_f6|LOC_e6) &&
	    b.black_knight==LOC_h7 &&
	    b.black_sentry==LOC_h8);
}

Test(hw5_board_new, board_new_01, .timeout=2)
{
  board b = board_new();
  cr_assert(b.whose_turn==COLOR_white);
}

Test(hw5_file, file_00, .timeout=2)
{
  cr_assert(file(LOC_a1)=='a');
}

Test(hw5_file, file_01, .timeout=2)
{
  cr_assert(file(LOC_b2)=='b');
}

Test(hw5_file, file_02, .timeout=2)
{
  cr_assert(file(LOC_c3)=='c');
}

Test(hw5_file, file_03, .timeout=2)
{
  cr_assert(file(LOC_d4)=='d');
}

Test(hw5_file, file_04, .timeout=2)
{
  cr_assert(file(LOC_e5)=='e');
}

Test(hw5_file, file_05, .timeout=2)
{
  cr_assert(file(LOC_f6)=='f');
}

Test(hw5_file, file_06, .timeout=2)
{
  cr_assert(file(LOC_g7)=='g');
}

Test(hw5_file, file_07, .timeout=2)
{
  cr_assert(file(LOC_h8)=='h');
}

Test(hw5_rank, rank_00, .timeout=2)
{
  cr_assert(rank(LOC_a8)==8);
}

Test(hw5_rank, rank_01, .timeout=2)
{
  cr_assert(rank(LOC_b7)==7);
}

Test(hw5_rank, rank_02, .timeout=2)
{
  cr_assert(rank(LOC_c6)==6);
}

Test(hw5_rank, rank_03, .timeout=2)
{
  cr_assert(rank(LOC_d5)==5);
}

Test(hw5_rank, rank_04, .timeout=2)
{
  cr_assert(rank(LOC_e4)==4);
}

Test(hw5_rank, rank_05, .timeout=2)
{
  cr_assert(rank(LOC_f3)==3);
}

Test(hw5_rank, rank_06, .timeout=2)
{
  cr_assert(rank(LOC_g2)==2);
}

Test(hw5_rank, rank_07, .timeout=2)
{
  cr_assert(rank(LOC_h1)==1);
}

Test(hw5_loc_str, loc_str_00, .timeout=2)
{
  cr_assert(!strcmp("a2",loc_str(LOC_a2)));
}


Test(hw5_loc_str, loc_str_01, .timeout=2)
{
  cr_assert(!strcmp("b3",loc_str(LOC_b3)));
}


Test(hw5_loc_str, loc_str_02, .timeout=2)
{
  cr_assert(!strcmp("c4",loc_str(LOC_c4)));
}


Test(hw5_loc_str, loc_str_03, .timeout=2)
{
  cr_assert(!strcmp("d5",loc_str(LOC_d5)));
}


Test(hw5_loc_str, loc_str_04, .timeout=2)
{
  cr_assert(!strcmp("e6",loc_str(LOC_e6)));
}

Test(hw5_loc_str, loc_str_05, .timeout=2)
{
  cr_assert(!strcmp("f7",loc_str(LOC_f7)));
}

Test(hw5_loc_str, loc_str_06, .timeout=2)
{
  cr_assert(!strcmp("g8",loc_str(LOC_g8)));
}

Test(hw5_loc_str, loc_str_07, .timeout=2)
{
  cr_assert(!strcmp("h1",loc_str(LOC_h1)));
}

Test(hw5_str_loc, str_loc_00, .timeout=2)
{
  cr_assert(LOC_b4==str_loc("b4"));
}

Test(hw5_str_loc, str_loc_01, .timeout=2)
{
  cr_assert(LOC_e5==str_loc("e5"));
}

Test(hw5_str_loc, str_loc_02, .timeout=2)
{
  cr_assert(LOC_f6==str_loc("f6"));
}

Test(hw5_str_loc, str_loc_03, .timeout=2)
{
  cr_assert(LOC_g7==str_loc("g7"));
}

Test(hw5_str_loc, str_loc_04, .timeout=2)
{
  cr_assert(LOC_h8==str_loc("h8"));
}

Test(hw5_str_loc, str_loc_05, .timeout=2)
{
  cr_assert(LOC_a2==str_loc("a2"));
}

Test(hw5_str_loc, str_loc_06, .timeout=2)
{
  cr_assert(LOC_b3==str_loc("b3"));
}

Test(hw5_str_loc, str_loc_07, .timeout=2)
{
  cr_assert(LOC_c4==str_loc("c4"));
}

Test(hw5_char_piece, char_piece_00, .timeout=2)
{
  cr_assert(char_piece('B')==PIECE_bb);
}

Test(hw5_char_piece, char_piece_01, .timeout=2)
{
  cr_assert(char_piece('Q')==PIECE_bq);
}

Test(hw5_char_piece, char_piece_02, .timeout=2)
{
  cr_assert(char_piece('E')==PIECE_be);
}

Test(hw5_char_piece, char_piece_03, .timeout=2)
{
  cr_assert(char_piece('S')==PIECE_bs);
}

Test(hw5_char_piece, char_piece_04, .timeout=2)
{
  cr_assert(char_piece('K')==PIECE_bk);
}

Test(hw5_char_piece, char_piece_05, .timeout=2)
{
  cr_assert(char_piece('b')==PIECE_wb);
}

Test(hw5_char_piece, char_piece_06, .timeout=2)
{
  cr_assert(char_piece('q')==PIECE_wq);
}

Test(hw5_char_piece, char_piece_07, .timeout=2)
{
  cr_assert(char_piece('k')==PIECE_wk);
}

Test(hw5_char_piece, char_piece_08, .timeout=2)
{
  cr_assert(char_piece('e')==PIECE_we);
}

Test(hw5_char_piece, char_piece_09, .timeout=2)
{
  cr_assert(char_piece('s')==PIECE_ws);
}

Test(hw5_pieces_white, pieces_white_00, .timeout=2)
{
  board b = board_empty();
  cr_assert(!pieces_white(b));
}

Test(hw5_pieces_white, pieces_white_01, .timeout=2)
{
  board b = board_new();
  loc_t expected = LOC_a1|LOC_b1|LOC_c1|LOC_c2|LOC_c3|LOC_c4;
  cr_assert(pieces_white(b)==expected);
}

Test(hw5_pieces_black, pieces_black_00, .timeout=2)
{
  board b = board_empty();
  cr_assert(!pieces_black(b));
}

Test(hw5_pieces_black, pieces_black_01, .timeout=2)
{
  board b = board_new();
  loc_t expected = LOC_h8|LOC_h7|LOC_h6|LOC_g6|LOC_f6|LOC_e6;
  cr_assert(pieces_black(b)==expected);
}

Test(hw5_pieces_all, pieces_all_00, .timeout=2)
{
  board b = board_empty();
  cr_assert(!pieces_all(b));
}

Test(hw5_pieces_all, pieces_all_01, .timeout=2)
{
  board b = board_new();
  loc_t expected = LOC_h8|LOC_h7|LOC_h6|LOC_g6|LOC_f6|LOC_e6|
                   LOC_a1|LOC_b1|LOC_c1|LOC_c2|LOC_c3|LOC_c4;
  cr_assert(pieces_all(b)==expected);
}

Test(hw5_is_white, is_white_00, .timeout=2)
{
  cr_assert(is_white(PIECE_ws));
}

Test(hw5_is_white, is_white_01, .timeout=2)
{
  cr_assert(!is_white(PIECE_bs));
}

Test(hw5_is_white, is_white_02, .timeout=2)
{
  cr_assert(!is_white(PIECE_none));
}

Test(hw5_is_black, is_black_00, .timeout=2)
{
  cr_assert(is_black(PIECE_bs));
}

Test(hw5_is_black, is_black_01, .timeout=2)
{
  cr_assert(!is_black(PIECE_ws));
}

Test(hw5_is_black, is_black_02, .timeout=2)
{
  cr_assert(!is_black(PIECE_none));
}

Test(hw5_is_occupied, is_occupied_00, .timeout=2)
{
  board b = board_empty();
  cr_assert(!is_occupied(b,LOC_g8));
}

Test(hw5_is_occupied, is_occupied_01, .timeout=2)
{
  board b = board_new();
  cr_assert(is_occupied(b,LOC_c1));
}

Test(hw5_is_occupied, is_occupied_02, .timeout=2)
{
  board b = board_new();
  cr_assert(!is_occupied(b,LOC_b2));
}

Test(hw5_is_occupied, is_occupied_03, .timeout=2)
{
  board b = board_new();
  cr_assert(is_occupied(b,LOC_h7));
}

Test(hw5_is_unoccupied, is_unoccupied_00, .timeout=2)
{
  board b = board_new();
  cr_assert(is_unoccupied(b,LOC_g8));
}

Test(hw5_is_unoccupied, is_unoccupied_01, .timeout=2)
{
  board b = board_new();
  cr_assert(!is_unoccupied(b,LOC_h8));
}

Test(hw5_is_unoccupied, is_unoccupied_02, .timeout=2)
{
  board b = board_new();
  cr_assert(is_unoccupied(b,LOC_a4));
}

Test(hw5_is_unoccupied, is_unoccupied_03, .timeout=2)
{
  board b = board_new();
  cr_assert(!is_unoccupied(b,LOC_c2));
}

Test(hw5_shadow_realm, shadow_realm_00, .timeout=2)
{
  cr_assert(!shadow_realm(LOC_h8));
}
 
Test(hw5_shadow_realm, shadow_realm_01, .timeout=2)
{
  cr_assert(shadow_realm(LOC_h1));
}

Test(hw5_shadow_realm, shadow_realm_02, .timeout=2)
{
  cr_assert(shadow_realm(LOC_d5));
}

Test(hw5_shadow_realm, shadow_realm_03, .timeout=2)
{
  cr_assert(!shadow_realm(LOC_c4) && !shadow_realm(LOC_d6));
}

Test(hw5_border, border_00, .timeout=2)
{
  cr_assert(border(LOC_h8));
}

Test(hw5_border, border_01, .timeout=2)
{
  cr_assert(border(LOC_h6) && border(LOC_c1));
}

Test(hw5_border, border_02, .timeout=2)
{
  cr_assert(border(LOC_a1));
}

Test(hw5_border, border_03, .timeout=2)
{
  cr_assert(!border(LOC_h1));
}

Test(hw5_border, border_04, .timeout=2)
{
  cr_assert(!border(LOC_b7));
}

Test(hw5_piece_at, piece_at_00, .timeout=2)
{
  board b = board_empty();
  cr_assert(piece_at(b,LOC_b2)==PIECE_none);
}

Test(hw5_piece_at, piece_at_01, .timeout=2)
{
  board b = board_new();
  cr_assert(piece_at(b,LOC_c3)==PIECE_wb);
}

Test(hw5_piece_at, piece_at_02, .timeout=2)
{
  board b = board_new();
  cr_assert(piece_at(b,LOC_h6)==PIECE_be);
}

Test(hw5_piece_at, piece_at_03, .timeout=2)
{
  board b = board_new();
  cr_assert(piece_at(b,LOC_g6)==PIECE_bq);
}

Test(hw5_piece_at, piece_at_04, .timeout=2)
{
  board b = board_new();
  cr_assert(piece_at(b,LOC_c3)==PIECE_wb);
}

Test(hw5_piece_at, piece_at_05, .timeout=2)
{
  board b = board_new();
  cr_assert(piece_at(b,LOC_f2)==PIECE_none);
}

Test(hw5_color_at, color_at_00, .timeout=2)
{
  board b = board_empty();
  cr_assert(color_at(b,LOC_b2)==COLOR_none);
}

Test(hw5_color_at, color_at_01, .timeout=2)
{
  board b = board_new();
  cr_assert(color_at(b,LOC_c4)==COLOR_white);
}

 Test(hw5_color_at, color_at_02, .timeout=2)
 {
  board b = board_new();
  cr_assert(color_at(b,LOC_c1)==COLOR_white);
}

Test(hw5_color_at, color_at_03, .timeout=2)
{
  board b = board_new();
  cr_assert(color_at(b,LOC_h6)==COLOR_black);
}

Test(hw5_color_at, color_at_04, .timeout=2)
{
  board b = board_new();
  cr_assert(color_at(b,LOC_e6)==COLOR_black);
}

 Test(hw5_color_at, color_at_05, .timeout=2)
{
  board b = board_new();
  cr_assert(color_at(b,LOC_h3)==COLOR_none);
}

Test(hw5_put_piece, put_piece_00, .timeout=2)
{
  board b = board_empty();
  put_piece(&b,LOC_a2,PIECE_wq);
  cr_assert(b.white_queen==LOC_a2);
}

Test(hw5_put_piece, put_piece_01, .timeout=2)
{
  board b = board_empty();
  put_piece(&b,LOC_a2,PIECE_wb);
  put_piece(&b,LOC_a3,PIECE_wb);
  cr_assert(b.white_bishop==(LOC_a2|LOC_a3));
}

Test(hw5_put_piece, put_piece_02, .timeout=2)
{
  board b = board_empty();
  put_piece(&b,LOC_a2,PIECE_bb);
  put_piece(&b,LOC_a3,PIECE_bb);
  cr_assert(b.black_bishop==(LOC_a2|LOC_a3));
}

Test(hw5_unconditionally_put_piece, unconditionally_put_piece_00, .timeout=2)
{
  board b = board_empty();
  unconditionally_put_piece(&b,LOC_a2,PIECE_wq);
  cr_assert(b.white_queen==LOC_a2);
}

Test(hw5_unconditionally_put_piece, unconditionally_put_piece_01, .timeout=2)
{
  board b = board_new();
  unconditionally_put_piece(&b,LOC_c1,PIECE_wq);
  cr_assert(b.white_queen==(LOC_c1|LOC_c2) && !b.white_envoy);
}

Test(hw5_unconditionally_put_piece, unconditionally_put_piece_02, .timeout=2)
{
  board b = board_new();
  unconditionally_put_piece(&b,LOC_d6,PIECE_bk);
  cr_assert(b.black_knight==(LOC_h7|LOC_d6));
}

Test(hw5_bishop_moves, bishop_moves_00, .timeout=2)
{
  board b = board_empty();
  b.whose_turn = COLOR_white;
  put_piece(&b,LOC_a1,PIECE_wb);
  cr_assert(bishop_moves(b,LOC_a1));
}

Test(hw5_bishop_moves, bishop_moves_01, .timeout=2)
{
  board b = board_new();
  move_list *moves = bishop_moves(b,LOC_c4);
  move_list *expected = p2_ml(4,
    LOC_c4,LOC_a2,
    LOC_c4,LOC_a6,
    LOC_c4,LOC_b3,
    LOC_c4,LOC_b5);
  cr_assert(p2_ml_same_moves(moves, expected));
  p2_ml_free(expected);
  p2_ml_free(moves);
}

Test(hw5_bishop_moves, bishop_moves_02, .timeout=2)
{
  board b = board_new();
  move_list *moves = bishop_moves(b,LOC_c3);
  move_list *expected = p2_ml(3,
    LOC_c3,LOC_a5,
    LOC_c3,LOC_b2,
    LOC_c3,LOC_b4);
  cr_assert(p2_ml_same_moves(moves, expected));
  p2_ml_free(expected);
  p2_ml_free(moves);
}

Test(hw5_bishop_moves, bishop_moves_03, .timeout=2)
{
  board b = board_new();
  b.white_sentry = LOC_a2;
  b.whose_turn   = COLOR_black;
  move_list *moves = bishop_moves(b,LOC_e6);
  move_list *expected = p2_ml(4,
    LOC_e6,LOC_c8,
    LOC_e6,LOC_d7,
    LOC_e6,LOC_f7,
    LOC_e6,LOC_g8);
  cr_assert(p2_ml_same_moves(moves, expected));
  p2_ml_free(expected);
  p2_ml_free(moves);
}

Test(hw5_bishop_moves, bishop_moves_04, .timeout=2)
{
  board b = board_new();
  b.white_sentry = LOC_a2;
  b.whose_turn   = COLOR_black;
  move_list *moves = bishop_moves(b,LOC_f6);
  move_list *expected = p2_ml(3,
    LOC_f6,LOC_d8,
    LOC_f6,LOC_e7,
    LOC_f6,LOC_g7);
  cr_assert(p2_ml_same_moves(moves, expected));
  p2_ml_free(expected);
  p2_ml_free(moves);
}

Test(hw5_sentry_moves, sentry_moves_00, .timeout=2)
{
  board b = board_empty();
  b.whose_turn = COLOR_white;
  put_piece(&b,LOC_a1,PIECE_ws);
  cr_assert(sentry_moves(b,LOC_a1));
}

Test(hw5_sentry_moves, sentry_moves_01, .timeout=2)
{
  board b = board_new();
  move_list *moves = sentry_moves(b,LOC_a1);
  move_list *expected = p2_ml(7,
    LOC_a1,LOC_a2,
    LOC_a1,LOC_a3,
    LOC_a1,LOC_a4,
    LOC_a1,LOC_a5,
    LOC_a1,LOC_a6,
    LOC_a1,LOC_a7,
    LOC_a1,LOC_a8);
  cr_assert(p2_ml_same_moves(moves, expected));
  p2_ml_free(expected);
  p2_ml_free(moves);
}

Test(hw5_sentry_moves, sentry_moves_02, .timeout=2)
{
  board b = board_new();
  b.white_sentry = LOC_a2;
  b.whose_turn = COLOR_black;
  move_list *moves = sentry_moves(b,LOC_h8);
  move_list *expected = p2_ml(7,
    LOC_h8,LOC_a8,
    LOC_h8,LOC_b8,
    LOC_h8,LOC_c8,
    LOC_h8,LOC_d8,
    LOC_h8,LOC_e8,
    LOC_h8,LOC_f8,
    LOC_h8,LOC_g8);
  cr_assert(p2_ml_same_moves(moves, expected));
  p2_ml_free(expected);
  p2_ml_free(moves);
}

Test(hw5_queen_moves, queen_moves_00, .timeout=2)
{
  board b = board_empty();
  b.whose_turn = COLOR_white;
  put_piece(&b,LOC_a1,PIECE_wq);
  cr_assert(queen_moves(b,LOC_a1));
}

Test(hw5_queen_moves, queen_moves_01, .timeout=2)
{
  board b = board_new();
  move_list *moves = queen_moves(b,LOC_c2);
  move_list *expected = p2_ml(4,
    LOC_c2,LOC_a2,
    LOC_c2,LOC_a4,
    LOC_c2,LOC_b2,
    LOC_c2,LOC_b3);
  cr_assert(p2_ml_same_moves(moves, expected));
  p2_ml_free(expected);
  p2_ml_free(moves);
}

Test(hw5_queen_moves, queen_moves_02, .timeout=2)
{
  board b = board_new();
  b.white_sentry = LOC_a2;
  b.whose_turn = COLOR_black;
  move_list *moves = queen_moves(b,LOC_g6);
  move_list *expected = p2_ml(4,
    LOC_g6,LOC_e8,
    LOC_g6,LOC_f7,
    LOC_g6,LOC_g7,
    LOC_g6,LOC_g8);
  cr_assert(p2_ml_same_moves(moves, expected));
  p2_ml_free(expected);
  p2_ml_free(moves);
}

Test(hw5_winner, winner_00, .timeout=2)
{
  board b = board_new();
  cr_assert(winner(b)==COLOR_none);
}

Test(hw5_winner, winner_01, .timeout=2)
{
  board b = board_new();
  b.white_envoy = 0;
  cr_assert(winner(b)==COLOR_black);
}

Test(hw5_winner, winner_02, .timeout=2)
{
  board b = board_new();
  b.black_envoy = 0;
  cr_assert(winner(b)==COLOR_white);
}

Test(hw5_winner, winner_03, .timeout=2)
{
  board b = board_new();
  unconditionally_put_piece(&b,LOC_h6,PIECE_we);  
  cr_assert(winner(b)==COLOR_white);
}

Test(hw5_winner, winner_04, .timeout=2)
{
  board b = board_new();
  unconditionally_put_piece(&b,LOC_c1,PIECE_be);  
  cr_assert(winner(b)==COLOR_black);
}

Test(hw5_winner, winner_05, .timeout=2)
{
  board b = board_new();
  b.white_queen = LOC_b3;
  cr_assert(winner(b)==COLOR_none);
}

Test(hw5_winner, winner_06, .timeout=2)
{
  board b = board_new();
  unconditionally_put_piece(&b,LOC_a1,PIECE_be);
  unconditionally_put_piece(&b,LOC_h8,PIECE_we);
  cr_assert(winner(b)==COLOR_none);
}

Test(hw5_winner, winner_07, .timeout=2)
{
  board b = board_new();
  unconditionally_put_piece(&b,LOC_a1,PIECE_be);
  unconditionally_put_piece(&b,LOC_h6,PIECE_we);
  cr_assert(winner(b)==COLOR_white);
}

Test(hw5_winner, winner_08, .timeout=2)
{
  board b = board_new();
  unconditionally_put_piece(&b,LOC_h8,PIECE_we);
  unconditionally_put_piece(&b,LOC_c1,PIECE_be);
  cr_assert(winner(b)==COLOR_black);
}

