#ifndef __HW3_H__
#define __HW3_H__

struct fraction {
  int num;
  int denom;
};
typedef struct fraction frac;

// build a new heap-allocated `frac` given the numerator and the denominator
// make sure the result is _canonicalized_ in the following sense:
// - the fraction is reduced, e.g. 3/6 is reduced to 1/2
// - if negative, the numerator is negative and the denominator positive, and
// - 0 is specifically represented as 0/1
// if denom is 0, print a message to stderr and exit(1)
frac *frac_new(int num, int denom);

// the results of the following arithmetic operators must all be
// canonicalized as described above

// compute the reciprocal of q and return a new heap-allocated result
// GIGO if q is 0
frac *frac_recip(const frac *q);

// negate q and return a new heap-allocated result
frac *frac_neg(const frac *q);

// add q to r and return a new heap-allocated result
frac *frac_add(const frac *q, const frac *r);

// subtract r from q and return a new heap-allocated result
frac *frac_sub(const frac *q, const frac *r);

// multiply q by r and return a new heap-allocated result
frac *frac_mult(const frac *q, const frac *r);

// divide q by r and return a new heap-allocated result
// GIGO if r is 0
frac *frac_div(const frac *q, const frac *r);

// raise q to the given power and return a new heap-allocated result
frac *frac_raise(const frac *q, const unsigned int power);

// return a floating-point approximate value of q
double frac_approx(const frac *q);

// compare q and r for equality
// do not assume both q and r are in canonical form
int frac_eq(const frac *q, const frac *r);

// return true if q<r, false otherwise
// do not assume both q and r are in canonical form
int frac_lt(const frac *q, const frac *r);

// return true if q>r, false otherwise
// do not assume both q and r are in canonical form
int frac_gt(const frac *q, const frac *r);

// return a new heap-allocated array of the given interval divided into n parts
// include both endpoints in the result, so the length is n+1
// ex: linspace(1/1,2/1,2) -> [1.0,1.5,2.0]
// ex: linspace(1/1,2/1,4) -> [1.0,1.25,1.5,1.75,2.0]
// GIGO if n is not at least 2
// GIGO if q>=r
double *linspace(const frac *q, const frac *r, const unsigned int n);

// return the sum of an array of fracs
frac *frac_sum(const frac *arr, const unsigned int len);

// build a new heap-allocated string of the form "2/5"
char *frac_tos(frac *r);

#endif
