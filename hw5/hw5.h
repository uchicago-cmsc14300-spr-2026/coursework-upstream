#ifndef __HW5_H__
#define __HW5_H__

// refer to the document "Corner Case: Rules of the Game"
// on Canvas/Ed

// ======== constants

#define COLOR_none  0
#define COLOR_white 1
#define COLOR_black 2

#define PIECE_none 0
#define PIECE_we (0+1)
#define PIECE_wq (0+2)
#define PIECE_wb (0+4)
#define PIECE_wk (0+8)
#define PIECE_ws (0+16)
#define PIECE_be (128+1)
#define PIECE_bq (128+2)
#define PIECE_bb (128+4)
#define PIECE_bk (128+8)
#define PIECE_bs (128+16)

// ======= types and data structures

typedef uint8_t  color_t;
typedef uint8_t  piece_t;
typedef uint64_t loc_t;

// this is a bitboard-like data structure 
// (see https://en.wikipedia.org/wiki/Bitboard)
// each field* is 64-bit bit vector encoding the locations of that
//   type of piece (see comment below)
// *except for whose_turn, which tracks whose turn it is
struct board {
  uint64_t white_envoy;
  uint64_t white_queen;
  uint64_t white_bishop;
  uint64_t white_knight;
  uint64_t white_sentry;
  uint64_t black_envoy;
  uint64_t black_queen;
  uint64_t black_bishop;
  uint64_t black_knight;
  uint64_t black_sentry;
  color_t  whose_turn;
};
typedef struct board board;

/* The board is mapped into 64-bit vectors like this:

  a8:56 b8:57 ... h8:63
  ... 
  a2:8  ...
  a1:0  b1:1  ... h1:7

  That is, bit 0 (least sig. bit) is a1, bit 1 is b1, bit 2 is c1,
  (...and so on up to...) bit 63 is h8.
*/

// Note: there are location constants defined for convenience in
// locations.h.
struct move {
  loc_t src;
  loc_t dst;
};
typedef struct move move;

typedef struct move_list move_list;
struct move_list {
  move m;
  move_list *next;
};

// ======== operations

// a cons-style constructor for move lists
move_list *move_list_cons(loc_t src, loc_t dst, move_list *next);

void move_list_free(move_list *moves);

// (not graded) useful for debugging
void move_list_show(char *label, move_list *ms);

// an empty board
board board_empty();

// a new board, ready to play
board board_new();

// (not graded) useful for debugging and gameplay
void board_show(board b);
  
// return the file 'a' through 'h' given a location
// NOTE: *do not enumerate every possibility*
// solutions that painstakingly check every possible case
//   will earn no credit
char file(loc_t loc);

// return the rank 1 through 8 given a location
// NOTE: *do not enumerate every possibility*
// solutions that painstakingly check every possible case
//   will earn no credit
int rank(loc_t loc);

// return a string of the form "b3"
// NOTE: *do not enumerate every possibility*
// solutions that painstakingly check every possible case
//   will earn no credit
char *loc_str(loc_t loc);

// from a string of the form "b3", return the location
loc_t str_loc(char *s);

// for 'e', 'b', 'q', 'k', 's', return corresponding white piece
// for 'E', 'B', 'Q', 'K', 'S', return corresponding black piece
// return PIECE_none for any other char
piece_t char_piece(char p);

// return a bit vector of all the white pieces
uint64_t pieces_white(board b);

// return a bit vector of all the black pieces
uint64_t pieces_black(board b);

// return a bit vector of all the pieces
uint64_t pieces_all(board b);

// return true if piece is white, false otherwise
int is_white(piece_t p);

// return true if piece is black, false otherwise
int is_black(piece_t p);

// return true if location is occupied, false otherwise
int is_occupied(board b, loc_t loc);

// return true if location is unoccupied, false otherwise
int is_unoccupied(board b, loc_t loc);

// return true if location is in the shadow realm, false otherwise
// (refer to corner case rules)
// NOTE: *do not enumerate every possibility*
int shadow_realm(loc_t loc);

// return true if location is part of sentry border, false otherwise
// (refer to corner case rules)
// NOTE: *do not enumerate every possibility*
int border(loc_t loc);

// return the piece at the location, or PIECE_none
piece_t piece_at(board b, loc_t loc);

// return the color of the piece at the location, or COLOR_none
color_t color_at(board b, loc_t loc);

// put the given piece at the given unoccupied location
// fprintf/exit if the location is occupied
void put_piece(board *b, loc_t loc, piece_t piece);

// put the given piece at the given location, occupied or not
// if location is occupied, remove the current piece from it
void unconditionally_put_piece(board *b, loc_t loc, piece_t piece);

// return the legal moves for a given bishop
// precondition: there is a bishop at the location
// precondition: the bishop's color matches whose turn
// must exclude the shadow realm (see rules)
// ERROR if the location is unoccupied
// ERROR if the location is occupied by a non-bishop
// ERROR if the bishop's color does not match whose turn
// moves can appear in any order in the result
move_list *bishop_moves(board b, loc_t loc);

// return the legal moves for a given sentry
// precondition: there is a sentry at the location
// precondition: the sentry's color matches whose turn
// must exclude the shadow realm (see rules)
// must stay on the border (see sentry rules)
// ERROR if the location is unoccupied
// ERROR if the location is occupied by a non-bishop
// ERROR if the bishop's color does not match whose turn
// moves can appear in any order in the result
move_list *sentry_moves(board b, loc_t loc);

// return the legal moves for a given queen
// precondition: there is a queen at the location
// precondition: the queen's color matches whose turn
// must exclude the shadow realm (see rules)
// ERROR if the location is unoccupied
// ERROR if the location is occupied by a non-bishop
// ERROR if the bishop's color does not match whose turn
// moves can appear in any order in the result
move_list *queen_moves(board b, loc_t loc);

// return COLOR_white, COLOR_black, or COLOR_none
// GIGO if the board is in an impossible game state (e.g., empty)
color_t winner(board b);
		       
#endif
