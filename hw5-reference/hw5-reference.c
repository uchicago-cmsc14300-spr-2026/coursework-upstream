#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include "hw5.h"
#include "locations.h"

// HW5 reference implementation
// CMSC 14300, May 2026, Adam Shaw

// The following vector list data structure will be used in
// calculating moves.

typedef struct vector_list vector_list;
struct vector_list {
  int8_t df;
  int8_t dr;
  vector_list *next;
};

move_list *move_list_cons(loc_t src, loc_t dst, move_list *next)
{
  move_list *ms = malloc(sizeof(move_list));
  ms->m.src  = src;
  ms->m.dst  = dst;
  ms->next = next;
  return ms;
}

void move_list_free(move_list *moves)
{
  if (moves) {
    move_list_free(moves->next);
    free(moves);
  }
}

vector_list *vector_list_cons(int8_t df, int8_t dr, vector_list *next)
{
  vector_list *v = malloc(sizeof(vector_list));
  v->df = df;
  v->dr = dr;
  v->next = next;
  return v;
}

void vector_list_free(vector_list *vs)
{
  if (vs) {
    vector_list_free(vs->next);
    free(vs);
  }
}

// add df and dr to the file and rank of the loc
// if the new location is off the board, return LOC_off
loc_t loc_plus(loc_t loc, int df, int dr)
{
  char newfile = file(loc) + df;
  int  newrank = rank(loc) + dr;
  if ('a'<=newfile && newfile<='h' && 1<=newrank && newrank<=8) {
    uint8_t offset = ((newrank-1)*8) + (newfile-'a');
    loc_t r = 0X01;
    return (r<<offset);
  }
  else
    return LOC_off;
}

// travel_along generalizes piece movement
// pre: expected piece is at the start location
//      GIGO if that piece is not the expected piece
move_list *travel_along(board b,
			loc_t start,
			vector_list *vecs, // vectors to travel along
			int chain, // keep going after one move along vector?
			int shadow_off_limits, // false for knights
			int border_only) // true for sentries
{
  color_t protagonist = color_at(b,start);
  if (protagonist==COLOR_none)
    return NULL;
  move_list *moves = NULL;
  color_t antagonist = (protagonist==COLOR_white)?COLOR_black:COLOR_white;
  while (vecs) {
    int8_t df  = vecs->df;
    int8_t dr  = vecs->dr;
    int active = 1;
    loc_t newloc = start;
    while (active) {
      newloc = loc_plus(newloc,df,dr);
      if (newloc==LOC_off ||
	  (shadow_off_limits && shadow_realm(newloc)) ||
	  (border_only && !border(newloc))) {
	active = 0;
      }
      else {
	color_t color = color_at(b,newloc);
	if (color==COLOR_none || color==antagonist)
	  moves = move_list_cons(start, newloc, moves);
	if (color==protagonist || color==antagonist || !chain)
	  active = 0;
      }
    }
    vecs = vecs->next;
  }
  return moves;
}

vector_list *bishop_vectors = NULL;
vector_list *queen_vectors  = NULL;
vector_list *knight_vectors = NULL;
vector_list *sentry_vectors = NULL;
// NOTE: envoy vectors are not needed, same as queen vectors

// list_v builds a list of vectors from a variable number of arguments
// the number of vector-component arguments is given in the first argument len
// uses a C technique called varargs (used by, for example, printf)
// ex: list_v(4,1,1,-1,-1) would produce the list [(1,1),(-1,-1)]
vector_list *list_v(int len, ...)
{
  va_list args;
  va_start(args,len);

  int tmp[len];

  // build array of args
  for (int i=0; i<len; i++)
    tmp[i] = va_arg(args,int);

  va_end(args);
  
  // build list from last pair of items backwards to first
  vector_list *vs = NULL;
  for (int i=len-1; i>=0; i-=2)
    vs = vector_list_cons(tmp[i-1],tmp[i],vs);

  return vs;
}

board board_empty()
{
  board b = {0}; // initializes all fields to 0
  return b;
}

board board_new()
{
  board b = {0};
  b.white_envoy  = LOC_c1;
  b.white_queen  = LOC_c2;
  b.white_bishop = LOC_c3 | LOC_c4;
  b.white_knight = LOC_b1;
  b.white_sentry = LOC_a1;
  b.black_envoy  = LOC_h6;
  b.black_queen  = LOC_g6;
  b.black_bishop = LOC_e6 | LOC_f6;
  b.black_knight = LOC_h7;
  b.black_sentry = LOC_h8;
  b.whose_turn   = COLOR_white;
  return b;
}

// return the file 'a' through 'h' given location
char file(loc_t loc)
{
  loc_t mask = 0XFF;
  loc_t t1   = loc;
  for (int i=0; i<8; i++) {
    uint8_t t2 = t1&mask;
    if (t2) {
      for (int j=0; j<8; j++) {
	if (0X01&t2)
	  return 'a'+j;
	t2>>=1;
      }
    }
    t1>>=8;
  }
  fprintf(stderr,"(file) bug? %016llX\n",loc);
  return 'X';
}

// return the rank 1 through 8 given location
int rank(loc_t loc)
{
  loc_t mask = 0XFF;
  for (int i=1; i<=8; i++) {
    if (loc&mask)
      return i;
    mask<<=8;
  }
  fprintf(stderr,"(rank) BUG\n");
  return 0;
}

// return a string of the form "b3"
char *loc_str(loc_t loc)
{
  char *s = malloc(3);
  s[0] = file(loc);
  s[1] = '0'+rank(loc);
  s[2] = '\0';
  return s;
}

// from a string of the form "b3", return the location
loc_t str_loc(char *s)
{
  char file = s[0];
  char rank = s[1];
  int offset = ((rank-'1')*8) + (file-'a');
  loc_t t = 0X01;
  return (t<<offset);
}

// for 'e', 'b', 'q', 'k', 's', return corresponding white piece
// for 'E', 'B', 'Q', 'K', 'S', return corresponding black piece
// return PIECE_none for any other char
piece_t char_piece(char p)
{
  switch (p) {
  case 'e':
    return PIECE_we;
  case 'E':
    return PIECE_be;
  case 'b':
    return PIECE_wb;
  case 'B':
    return PIECE_bb;
  case 'q':
    return PIECE_wq;
  case 'Q':
    return PIECE_bq;
  case 'k':
    return PIECE_wk;
  case 'K':
    return PIECE_bk;
  case 's':
    return PIECE_ws;
  case 'S':
    return PIECE_bs;
  }
  fprintf(stderr,"(char_piece) unrecognized piece %c\n", p);
  return PIECE_none;
}

uint64_t pieces_white(board b)
{
  return (b.white_envoy |
	  b.white_queen |
	  b.white_bishop |
	  b.white_knight |
	  b.white_sentry);
}

uint64_t pieces_black(board b)
{
  return (b.black_envoy |
	  b.black_queen |
	  b.black_bishop |
	  b.black_knight |
	  b.black_sentry);
}

uint64_t pieces_all(board b)
{
  return pieces_white(b)|pieces_black(b);
}

int is_occupied(board b, loc_t loc)
{
  // NOTE: we can't just return loc&pieces_all(b)
  //   because that 64-bit result is narrowed to an int,
  //   dropping the higher 32 bits! (tricky bug!)
  return loc&pieces_all(b)?1:0;
}

int is_unoccupied(board b, loc_t loc)
{
  return !is_occupied(b,loc);
}

int shadow_realm(loc_t loc)
{
  return loc!=LOC_off && file(loc)>='d' && rank(loc)<=5;
}

int border(loc_t loc) // for sentries
{
  char f = file(loc);
  int  r = rank(loc);
  if (f=='a' || r==8)
    return 1;
  if (r==1 && f<='c')
    return 1;
  if (f=='h' && r>=6)
    return 1;
  return 0;
}

piece_t piece_at(board b, loc_t loc)
{
  if (loc&b.white_envoy)
    return PIECE_we;
  if (loc&b.white_queen)
    return PIECE_wq;
  if (loc&b.white_bishop)
    return PIECE_wb;
  if (loc&b.white_knight)
    return PIECE_wk;
  if (loc&b.white_sentry)
    return PIECE_ws;
  if (loc&b.black_envoy)
    return PIECE_be;
  if (loc&b.black_queen)
    return PIECE_bq;
  if (loc&b.black_bishop)
    return PIECE_bb;
  if (loc&b.black_knight)
    return PIECE_bk;
  if (loc&b.black_sentry)
    return PIECE_bs;
  return PIECE_none;
}

int is_white(piece_t p)
{
  switch (p) {
  case PIECE_we:
  case PIECE_wq:
  case PIECE_wb:
  case PIECE_wk:
  case PIECE_ws: return 1;
  }
  return 0;
}

int is_black(piece_t p)
{
  switch (p) {
  case PIECE_be:
  case PIECE_bq:
  case PIECE_bb:
  case PIECE_bk:
  case PIECE_bs: return 1;
  }
  return 0;
}

color_t color_at(board b, loc_t loc)
{
  piece_t p = piece_at(b,loc);
  if (p==PIECE_none)
    return COLOR_none;
  else if (is_white(p))
    return COLOR_white;
  else
    return COLOR_black;
}

// pre: space must be unoccupied
void put_piece(board *b, loc_t loc, piece_t piece)
{
  if (is_occupied(*b,loc)) {
    fprintf(stderr, "(put_piece) location already occupied\n");
    exit(1);
  }
  if (piece==PIECE_we)
    b->white_envoy |= loc;
  if (piece==PIECE_wq)
    b->white_queen |= loc;
  if (piece==PIECE_wb)
    b->white_bishop |= loc;
  if (piece==PIECE_wk)
    b->white_knight |= loc;
  if (piece==PIECE_ws)
    b->white_sentry |= loc;
  if (piece==PIECE_be)
    b->black_envoy |= loc;
  if (piece==PIECE_bq)
    b->black_queen |= loc;
  if (piece==PIECE_bb)
    b->black_bishop |= loc;
  if (piece==PIECE_bk)
    b->black_knight |= loc;
  if (piece==PIECE_bs)
    b->black_sentry |= loc;
  return;
}

void remove_piece(board *b, loc_t loc)
{
  piece_t piece = piece_at(*b,loc);
  if (piece==PIECE_none) {
    fprintf(stderr,"(remove_piece) BUG\n");
    exit(1);
  }
  if (piece==PIECE_we)
    b->white_envoy &= ~loc;
  if (piece==PIECE_wq)
    b->white_queen &= ~loc;
  if (piece==PIECE_wb)
    b->white_bishop &= ~loc;
  if (piece==PIECE_wk)
    b->white_knight &= ~loc;
  if (piece==PIECE_ws)
    b->white_sentry &= ~loc;
  if (piece==PIECE_be)
    b->black_envoy &= ~loc;
  if (piece==PIECE_bq)
    b->black_queen &= ~loc;
  if (piece==PIECE_bb)
    b->black_bishop &= ~loc;
  if (piece==PIECE_bk)
    b->black_knight &= ~loc;
  if (piece==PIECE_bs)
    b->black_sentry &= ~loc;
  return;  
}

void unconditionally_put_piece(board *b, loc_t loc, piece_t piece)
{
  if (is_occupied(*b,loc))
    remove_piece(b,loc);
  put_piece(b,loc,piece);
}

move_list *bishop_moves(board b, loc_t loc)
{
  if (!bishop_vectors) // init. bishop vectors if not yet init.
    bishop_vectors = list_v(8,1,1,-1,-1,1,-1,-1,1);
  return travel_along(b,loc,bishop_vectors,1,1,0);
}

move_list *queen_moves(board b, loc_t loc)
{
  if (!queen_vectors) // init. queen vectors if not yet init.
    queen_vectors =
      list_v(16,1,1,-1,-1,1,-1,-1,1,1,0,0,1,0,-1,-1,0);
  return travel_along(b,loc,queen_vectors,1,1,0);
}

move_list *sentry_moves(board b, loc_t loc)
{
  if (!sentry_vectors)  // init. sentry vectors if not yet init.
    sentry_vectors = list_v(8,1,0,0,1,-1,0,0,-1);
  return travel_along(b,loc,sentry_vectors,1,0,1);
}

void move_list_show(char *label, move_list *ms)
{
  printf("%s ",label);
  putchar('[');
  while (ms) {
    char *src_str = loc_str(ms->m.src);
    char *dst_str = loc_str(ms->m.dst);
    printf("%s->%s",src_str,dst_str);
    if (ms->next)
      putchar(',');
    free(src_str);
    free(dst_str);
    ms = ms->next;
  }
  putchar(']');
  putchar('\n');
}

char *piece_unicode(piece_t p)
{
  switch (p) {
  case PIECE_we:   return "♙";
  case PIECE_wq:   return "♕";
  case PIECE_wb:   return "♗";
  case PIECE_wk:   return "♘";
  case PIECE_ws:   return "♖";
  case PIECE_be:   return "♟";
  case PIECE_bq:   return "♛";
  case PIECE_bb:   return "♝";
  case PIECE_bk:   return "♞";
  case PIECE_bs:   return "♜";
  case PIECE_none: return " ";
  }
  fprintf(stderr,"(piece_char) bad piece\n");
  exit(1);
}

void board_show(board b)
{
  char str[] = {0,0,0};
  for (int rank=8; rank>=1; rank--) {
    for (int file='a'; file<='h'; file++) {
      str[0] = file;
      str[1] = '0'+rank;
      loc_t loc = str_loc(str);
      piece_t p = piece_at(b,loc);
      if ((file+rank)%2==0)
	printf("\033[48;5;244m%s\033[0m",piece_unicode(p));
      else
	printf("\033[48;5;250m%s\033[0m",piece_unicode(p));
  }
    putchar('\n');
  }
}

color_t winner(board b)
{
  if (!b.black_envoy || piece_at(b,LOC_h6)==PIECE_we)
    return COLOR_white;
  else if (!b.white_envoy || piece_at(b,LOC_c1)==PIECE_be)
    return COLOR_black;
  else
    return COLOR_none;  
}

