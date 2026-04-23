#include <criterion/criterion.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "hw3.h"

// ======== constants

const double TOL = 0.01;
// TOL is an abbreviation for "tolerance"

// ======== helper functions

int within(double epsilon, double a, double b)
{
  return fabs(a-b)<=epsilon;
}

int __phase1_frac_eq(frac *a, int num, int denom)
{
  return a->num==num && a->denom==denom;
}

// ======== tests

Test(hw3_frac_new, frac_new_00, .timeout=2)
{
  frac *f = frac_new(2,3);
  cr_assert(__phase1_frac_eq(f,2,3));
  free(f);
}

Test(hw3_frac_new, frac_new_01, .timeout=2)
{
  frac *f = frac_new(6,9);
  cr_assert(__phase1_frac_eq(f,2,3));
  free(f);
}

Test(hw3_frac_recip, frac_recip_00, .timeout=2)
{
  frac *f = frac_new(2,3);
  frac *r = frac_recip(f);
  cr_assert(__phase1_frac_eq(r,3,2));
  free(r);
  free(f);
}

Test(hw3_frac_neg, frac_neg_00, .timeout=2)
{
  frac *f = frac_new(2,3);
  frac *n = frac_neg(f);
  cr_assert(__phase1_frac_eq(n,-2,3));
  free(n);
  free(f);
}

Test(hw3_frac_add, frac_add_00, .timeout=2)
{
  frac *f = frac_new(2,3);
  frac *g = frac_add(f,f);
  cr_assert(__phase1_frac_eq(g,4,3));
  free(g);
  free(f);
}

Test(hw3_frac_sub, frac_sub_00, .timeout=2)
{
  frac *f = frac_new(3,4);
  frac *g = frac_new(1,4);
  frac *s = frac_sub(f,g);
  cr_assert(__phase1_frac_eq(s,1,2));
  free(s);
  free(g);
  free(f);
}

Test(hw3_frac_mult, frac_mult_00, .timeout=2)
{
  frac *f = frac_new(3,4);
  frac *g = frac_new(1,4);
  frac *p = frac_mult(f,g);
  cr_assert(__phase1_frac_eq(p,3,16));
  free(p);
  free(g);
  free(f);
}

Test(hw3_frac_div, frac_div_00, .timeout=2)
{
  frac *f = frac_new(3,4);
  frac *g = frac_new(2,1);
  frac *d = frac_div(f,g);
  cr_assert(__phase1_frac_eq(d,3,8));
  free(d);
  free(g);
  free(f);
}

Test(hw3_frac_raise, frac_raise_00, .timeout=2)
{
  frac *f = frac_new(1,2);
  frac *r = frac_raise(f,4);
  cr_assert(__phase1_frac_eq(r,1,16));
  free(r);
  free(f);
}

Test(hw3_frac_approx, frac_approx_00, .timeout=2)
{
  frac *f = frac_new(1,2);
  cr_assert(within(TOL,frac_approx(f),0.5));
  free(f);
}

Test(hw3_frac_eq, frac_eq_00, .timeout=2)
{
  frac *f = frac_new(1,2);
  cr_assert(frac_eq(f,f));
  free(f);
}

Test(hw3_frac_lt, frac_lt_00, .timeout=2)
{
  frac *f = frac_new(1,2);
  frac *g = frac_new(2,3);
  cr_assert(frac_lt(f,g));
  free(g);
  free(f);
}

Test(hw3_frac_gt, frac_gt_00, .timeout=2)
{
  frac *f = frac_new(1,2);
  frac *g = frac_new(2,3);
  cr_assert(frac_gt(g,f));
  free(g);
  free(f);
}

Test(hw3_linspace, linspace_00, .timeout=2)
{
  frac *f = frac_new(1,1);
  frac *g = frac_new(2,1);
  double *s = linspace(f,g,2);
  cr_assert(within(TOL,s[0],1));
  cr_assert(within(TOL,s[1],1.5));
  cr_assert(within(TOL,s[2],2));
  free(s);
  free(g);
  free(f);
}

Test(hw3_frac_sum, frac_sum_00, .timeout=2)
{
  frac arr[2];
  arr[0].num   = 1;
  arr[0].denom = 2;
  arr[1].num   = 1;
  arr[1].denom = 3;
  frac *s = frac_sum(arr,2);
  cr_assert(__phase1_frac_eq(s,5,6));
  free(s);
}

Test(hw3_frac_tos, frac_tos_00, .timeout=2)
{
  frac *f = frac_new(1,3);
  char *s = frac_tos(f);
  cr_assert(!strcmp(s,"1/3"));
  free(s);
  free(f);
}
