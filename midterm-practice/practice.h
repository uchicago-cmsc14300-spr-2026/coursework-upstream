#include <stdint.h>

// return the distance from the point (x,y) to the perimeter of the circle
// if the point is on the circle, the distance is 0
// otherwise, it should be a positive number
// GIGO if the radius is nonpositive
double dist_to(double x, double y, double cx, double cy, double r);

// retrieve the bit in position b from the 64-bit int n
// the bit in position 0 is the least significant bit
// the bit in position 63 is the most significant bit
// GIGO if b is outside the range [0,63]
int get_bit(uint8_t b, uint64_t n);

// given a 64-bit int, return the number consisting of the bits
//  at pos 1, pos 3, ..., pos 63
// the bit in position 0 is the least significant bit
// the bit in position 63 is the most significant bit
// for example, odd_bits(0XAAAAAAAAAAAAAAAA) -> 0XFFFFFFFF
// for example, odd_bits(0XAAAAAAAAAAAA0000) -> 0XFFFFFF00
uint32_t odd_bits(uint64_t n);

// return the 0-based index of the sought character in the string
// return -1 if the character does not appear
// for example, index_of("ABCDE",'C') ->  2
// for example, index_of("ABCDE",'X') -> -1
int index_of(char *s, char c);

// build a new heap-allocated string
// reverse the original tring *and* capitalize any letters in it
// for example, revcap("abC5") -> "5CBA"
// for example, revcap("xyz") -> "ZYX"
// for example, revcap("#@!") -> "!@#"
// GIGO if s is NULL
char *revcap(char *s);

// build a new heap-allocated string up to but not including the marker
// if the marker doesn't appear, return a copy of the string
// for example, until("AB/XY",'/') -> "AB"
// for example, until("AB/XY",',') -> "AB/XY"
// GIGO if s is NULL
char *until(char *s, char marker);

// build a new heap-allocated string
// insert the string s2 into string s1 at given position
// treat any position >= the length of the string as "the end"
// for example, ins("ABC","[X]",0) -> "[X]ABC"
// for example, ins("ABC","[X]",1) -> "A[X]BC"
// for example, ins("ABC","[X]",2) -> "AB[X]C"
// for example, ins("ABC","[X]",3) -> "ABC[X]"
// for example, ins("ABC","[X]",9) -> "ABC[X]"
// GIGO if s1 and/or s2 is NULL
char *ins(char *s1, char *s2, unsigned int pos); 
