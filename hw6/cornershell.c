#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "hw6.h"
#include "locations.h"
#include "htbl.h"
#include "strategy.h"

char *piece_str(piece_t p)
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

void board_show_labels(board b)
{
  printf("  abcdefgh\n");
  char str[] = {0,0,0};
  for (int rank=8; rank>=1; rank--) {
    printf("%c ",'0'+rank);
    for (int file='a'; file<='h'; file++) {
      str[0] = file;
      str[1] = '0'+rank;
      loc_t loc = str_loc(str);
      piece_t p = piece_at(b,loc);
      if ((file+rank)%2==0) // dark squares
	if (shadow_realm(loc))
      	  printf("\033[48;5;243m%s\033[0m",piece_str(p)); // dark gray, 256 colors
	else
          printf("\033[48;5;27m%s\033[0m",piece_str(p)); // blue, 256 colors
      else // light squares
	if (shadow_realm(loc))
	  printf("\033[48;5;251m%s\033[0m",piece_str(p)); // light gray, 256 colors
	else
	  printf("\033[48;5;195m%s\033[0m",piece_str(p)); // light blue, 256 colors
  }
    printf(" %c\n",'0'+rank);
  }
  printf("  abcdefgh\n");
}


int isfile(char c)
{
  return 'a'<=c && c<='h';
}

int isrank(char c)
{
  return '1'<=c && c<='8';
}

int is_move_cmd(char *canon)
{
  int n = strlen(canon);
  if (n==4) {
    return isfile(canon[0]) &&
      isrank(canon[1]) &&
      isfile(canon[2]) &&
      isrank(canon[3]);
  }
  else
    return 0;
}

// remove all spaces and make all characters lowercase
// ex: turns "B1   C6  " into "b1c6"
char *canonicalize(char *line)
{
  int n = strlen(line);
  char *canon = malloc(n+1);
  int j=0;
  for (int i=0; i<n; ++i) {
    if (isnumber(line[i]))
      canon[j++]=line[i];
    else if (isalpha(line[i]))
      canon[j++]=tolower(line[i]);
  }
  canon[j]='\0';
  return canon;
}

void prompt(color_t turn)
{
  
  printf("* To move, type, for example, \x1B[3ma2 b3\x1B[0m.\n");
  printf("* To quit, type \x1B[3mq.\x1B[0m\n");
  printf("-> %s's turn\n",turn==COLOR_white?"White":"Black");
  printf(" > ");
}

int handle_victory(board b)
{
  color_t g = winner(b);
  if (g != COLOR_none)
    printf(">>>VICTORY<<<\n");
  if (g==COLOR_white)
    printf("White wins!\n");
  else if (g==COLOR_black)
    printf("Black wins!\n");
  return g;
}

void black_turn(board *b, htbl *ht, int(*heuristic)(board))
{
  move m = {0, 0};

  printf("(analyzing...)\n");

  int score = minimax(ht, heuristic, *b, 5, &m);
  (void)score; // suppresses compiler warning
  if (m.src == 0 && m.dst == 0) {
    fprintf(stderr, "minimax did not return a move\n");
    exit(1);
  }
  
  char *ssrc = loc_str(m.src), *sdst = loc_str(m.dst);
  printf("Black chooses %s %s\n",ssrc, sdst);
  free(ssrc);
  free(sdst);
  if (!perform_move(b, m)) {
    fprintf(stderr,"The computer player chose an illegal move.\n");
    exit(1);
  }
  board_show_labels(*b);
}

int bucket_size(bucket *b)
{
  int sz=0;
  for (;b;b=b->next)
    ++sz;
  return sz;   
}

int htbl_num_entries(htbl *ht)
{
  int c = 0;
  for (int i=0; i<ht->n_buckets; i++)
    c += bucket_size(ht->buckets[i]);
  return c;
}

int main(int argc, char *argv[])
{
  htbl *ht = htbl_new(1000000);
  char *line = NULL;
  size_t size = 0;
  ssize_t nread;
  
  board b = board_new();
  move m;
  
  int(*heuristic)(board) = &base_heuristic;
  if (argc>1 && tolower(argv[1][0]=='c')) {
    printf("(using custom_heuristic)\n");
    heuristic = &custom_heuristic;
  } else {
    printf("(using base_heuristic)\n");
  }
  
  printf("Welcome to Corner Case! It's kind of like chess!\n");

  board_show_labels(b);
  prompt(b.whose_turn);
  
  while ((nread = getline(&line, &size, stdin)) != -1) {
    char *canon = canonicalize(line);

    if (!strcmp(canon,"q"))
      exit(0);
    
    if (is_move_cmd(canon)) {
      
      m.dst = str_loc(canon + 2);
      canon[2] = 0;
      m.src = str_loc(canon);
      
      if (!perform_move(&b, m)) {
        printf("That move cannot be made. Please try again.\n>> ");
        continue;
      }
      board_show_labels(b);
    } else {
      printf("Unrecognized command. Please try again.\n>> ");
      continue;
    }
    
    if (handle_victory(b))
      exit(0);
    
    black_turn(&b, ht, heuristic);
    if (handle_victory(b))
      exit(0);    
    
    prompt(b.whose_turn);
  }
  
  free(line);
  return 0;  
}
