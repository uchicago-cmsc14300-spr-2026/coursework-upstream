#ifndef _HTBL_H
#define _HTBL_H

#include "hw6.h"


/* bucket: linked list of hash table entries */

typedef struct bucket bucket;
struct bucket {
  // key data
  board b;
  unsigned int depth;

  // value data
  int score;
  move m;

  // hash table management data
  unsigned long long int hash; 
  bucket *next;
};

// make a new linked list cell with the specified fields
bucket *bucket_cons(board bd, unsigned int depth, int score,
                    move m, unsigned long long int hash, bucket *b);

// does the linked list entry match a sought-for key?
// short-circuit the comparison if the hash values do not match
int bucket_match(board bd, unsigned int depth,
                 unsigned long long int hash, bucket *b);

// free an entire linked list
void bucket_free(bucket *b);


/* hash table struct and operations */

struct hash_table {
  bucket **buckets;
  unsigned int n_buckets, occupancy;
};
typedef struct hash_table htbl;

// make a new hash table with the specified array length
htbl *htbl_new(unsigned int sz);

// add an entry with the specified characteristics to the hash table
// grow the size of the hash table if occupancy exceeds 50%
// behavior of the hash table is undefined if there is already an entry
// with the same key
void htbl_insert(board bd, unsigned int depth, int score,
                 move m, htbl *t);

// look for an entry in the hash table with the specified key
// return false if no matching entry found
// return true and provide values via the out-parameters if match found
int htbl_get(board bd, unsigned int depth, int *score,
             move *m, htbl *t);

// deallocate the hash table and its contents
void htbl_free(htbl *t);

#endif /* _HTBL_H */
