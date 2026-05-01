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

frac stack_frac(int num, int denom)
{
  frac *f = frac_new(num,denom);
  frac result;
  result.num = f->num;
  result.denom = f->denom;
  free(f);
  return result;
}

// ======== tests

Test(hw3_frac_new, frac_new_0, .timeout=2)
{
  frac *f = frac_new(1,3);
  cr_assert(f->num==1 && f->denom==3);
  free(f);
}

Test(hw3_frac_new, frac_new_1, .timeout=2)
{
  frac *f = frac_new(8,20);
  cr_assert(f->num==2 && f->denom==5);
  free(f);
}

Test(hw3_frac_new, frac_new_2, .timeout=2)
{
  frac *f = frac_new(0,1);
  cr_assert(f->num==0 && f->denom==1);
  free(f);
}

Test(hw3_frac_new, frac_new_3, .timeout=2)
{
  frac *f = frac_new(0,22);
  cr_assert(f->num==0 && f->denom==1);
  free(f);
}

Test(hw3_frac_new, frac_new_4, .timeout=2)
{
  frac *f = frac_new(-1,-3);
  cr_assert(f->num==1 && f->denom==3);
  free(f);
}

Test(hw3_frac_new, frac_new_5, .timeout=2)
{
  frac *f = frac_new(-3,4);
  cr_assert(f->num==-3 && f->denom==4);
  free(f);
}

Test(hw3_frac_new, frac_new_6, .timeout=2)
{
  frac *f = frac_new(5,-8);
  cr_assert(f->num==-5 && f->denom==8);
  free(f);
}

Test(hw3_frac_new, frac_new_7, .timeout=2)
{
  frac *f = frac_new(50,80);
  cr_assert(f->num==5 && f->denom==8);
  free(f);
}

Test(hw3_frac_new, frac_new_8, .timeout=2)
{
  frac *f = frac_new(333,36363);
  cr_assert(f->num==111 && f->denom==12121);
  free(f);
}

Test(hw3_frac_new, frac_new_9, .timeout=2)
{
  frac *f = frac_new(777,111);
  cr_assert(f->num==7 && f->denom==1);
  free(f);
}

Test(hw3_frac_new, frac_new_10, .timeout=2)
{
  frac *f = frac_new(1234,4321);
  cr_assert(f->num==1234 && f->denom==4321);
  free(f);
}

Test(hw3_frac_recip, frac_recip_0, .timeout=2)
{
  frac *f1 = frac_new(1,3);
  frac *f2 = frac_recip(f1);
  cr_assert(f2->num==3 && f2->denom==1);
  free(f2);
  free(f1);
}

Test(hw3_frac_recip, frac_recip_1, .timeout=2)
{
  frac *f1 = frac_new(8,20);
  frac *f2 = frac_recip(f1);
  cr_assert(f2->num==5 && f2->denom==2);
  free(f2);
  free(f1);
}

Test(hw3_frac_recip, frac_recip_2, .timeout=2)
{
  frac *f1 = frac_new(20,1);
  frac *f2 = frac_recip(f1);
  cr_assert(f2->num==1 && f2->denom==20);
  free(f2);
  free(f1);
}

Test(hw3_frac_recip, frac_recip_3, .timeout=2)
{
  frac *f1 = frac_new(30,22);
  frac *f2 = frac_recip(f1);
  cr_assert(f2->num==11 && f2->denom==15);
  free(f2);
  free(f1);
}

Test(hw3_frac_recip, frac_recip_4, .timeout=2)
{
  frac *f1 = frac_new(-1,-3);
  frac *f2 = frac_recip(f1);
  cr_assert(f2->num==3 && f2->denom==1);
  free(f2);
  free(f1);
}

Test(hw3_frac_recip, frac_recip_5, .timeout=2)
{
  frac *f1 = frac_new(-3,4);
  frac *f2 = frac_recip(f1);
  cr_assert(f2->num==-4 && f2->denom==3);
  free(f2);
  free(f1);
}

Test(hw3_frac_recip, frac_recip_6, .timeout=2)
{
  frac *f1 = frac_new(5,-8);
  frac *f2 = frac_recip(f1);
  cr_assert(f2->num==-8 && f2->denom==5);
  free(f2);
  free(f1);
}

Test(hw3_frac_recip, frac_recip_7, .timeout=2)
{
  frac *f1 = frac_new(50,80);
  frac *f2 = frac_recip(f1);
  cr_assert(f2->num==8 && f2->denom==5);
  free(f2);
  free(f1);
}

Test(hw3_frac_recip, frac_recip_8, .timeout=2)
{
  frac *f1 = frac_new(333,36363);
  frac *f2 = frac_recip(f1);
  cr_assert(f2->num==12121 && f2->denom==111);
  free(f2);
  free(f1);
}

Test(hw3_frac_recip, frac_recip_9, .timeout=2)
{
  frac *f1 = frac_new(777,111);
  frac *f2 = frac_recip(f1);
  cr_assert(f2->num==1 && f2->denom==7);
  free(f2);
  free(f1);
}

Test(hw3_frac_recip, frac_recip_10, .timeout=2)
{
  frac *f1 = frac_new(1234,4321);
  frac *f2 = frac_recip(f1);
  cr_assert(f2->num==4321 && f2->denom==1234);
  free(f2);
  free(f1);
}

Test(hw3_frac_neg, frac_neg_0, .timeout=2)
{
  frac *f1 = frac_new(1,3);
  frac *f2 = frac_neg(f1);
  cr_assert(f2->num==-1 && f2->denom==3);
  free(f2);
  free(f1);
}

Test(hw3_frac_neg, frac_neg_1, .timeout=2)
{
  frac *f1 = frac_new(8,20);
  frac *f2 = frac_neg(f1);
  cr_assert(f2->num==-2 && f2->denom==5);
  free(f2);
  free(f1);
}

Test(hw3_frac_neg, frac_neg_2, .timeout=2)
{
  frac *f1 = frac_new(20,1);
  frac *f2 = frac_neg(f1);
  cr_assert(f2->num==-20 && f2->denom==1);
  free(f2);
  free(f1);
}

Test(hw3_frac_neg, frac_neg_3, .timeout=2)
{
  frac *f1 = frac_new(30,22);
  frac *f2 = frac_neg(f1);
  cr_assert(f2->num==-15 && f2->denom==11);
  free(f2);
  free(f1);
}

Test(hw3_frac_neg, frac_neg_4, .timeout=2)
{
  frac *f1 = frac_new(-1,-3);
  frac *f2 = frac_neg(f1);
  cr_assert(f2->num==-1 && f2->denom==3);
  free(f2);
  free(f1);
}

Test(hw3_frac_neg, frac_neg_5, .timeout=2)
{
  frac *f1 = frac_new(-3,4);
  frac *f2 = frac_neg(f1);
  cr_assert(f2->num==3 && f2->denom==4);
  free(f2);
  free(f1);
}

Test(hw3_frac_neg, frac_neg_6, .timeout=2)
{
  frac *f1 = frac_new(5,-8);
  frac *f2 = frac_neg(f1);
  cr_assert(f2->num==5 && f2->denom==8);
  free(f2);
  free(f1);
}

Test(hw3_frac_neg, frac_neg_7, .timeout=2)
{
  frac *f1 = frac_new(50,80);
  frac *f2 = frac_neg(f1);
  cr_assert(f2->num==-5 && f2->denom==8);
  free(f2);
  free(f1);
}

Test(hw3_frac_neg, frac_neg_8, .timeout=2)
{
  frac *f1 = frac_new(333,36363);
  frac *f2 = frac_neg(f1);
  cr_assert(f2->num==-111 && f2->denom==12121);
  free(f2);
  free(f1);
}

Test(hw3_frac_neg, frac_neg_9, .timeout=2)
{
  frac *f1 = frac_new(777,111);
  frac *f2 = frac_neg(f1);
  cr_assert(f2->num==-7 && f2->denom==1);
  free(f2);
  free(f1);
}

Test(hw3_frac_neg, frac_neg_10, .timeout=2)
{
  frac *f1 = frac_new(1234,4321);
  frac *f2 = frac_neg(f1);
  cr_assert(f2->num==-1234 && f2->denom==4321);
  free(f2);
  free(f1);
}

Test(hw3_frac_neg, frac_neg_11, .timeout=2)
{
  frac *f1 = frac_new(0,1);
  frac *f2 = frac_neg(f1);
  cr_assert(f2->num==0 && f2->denom==1);
  free(f2);
  free(f1);
}

Test(hw3_frac_add, frac_add_0, .timeout=2)
{
  frac *f1 = frac_new(1,2);
  frac *f2 = frac_new(1,3);
  frac *f3 = frac_add(f1,f2);
  cr_assert(f3->num==5 && f3->denom==6);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_add, frac_add_1, .timeout=2)
{
  frac *f1 = frac_new(11,22);
  frac *f2 = frac_new(333,666);
  frac *f3 = frac_add(f1,f2);
  cr_assert(f3->num==1 && f3->denom==1);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_add, frac_add_2, .timeout=2)
{
  frac *f1 = frac_new(1,3);
  frac *f2 = frac_new(7,8);
  frac *f3 = frac_add(f1,f2);
  cr_assert(f3->num==29 && f3->denom==24);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_add, frac_add_3, .timeout=2)
{
  frac *f1 = frac_new(77,8);
  frac *f2 = frac_new(88,7);
  frac *f3 = frac_add(f1,f2);
  cr_assert(f3->num==1243 && f3->denom==56);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_add, frac_add_4, .timeout=2)
{
  frac *f1 = frac_new(-1,2);
  frac *f2 = frac_new(-3,-4);
  frac *f3 = frac_add(f1,f2);
  cr_assert(f3->num==1 && f3->denom==4);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_add, frac_add_5, .timeout=2)
{
  frac *f1 = frac_new(11,2);
  frac *f2 = frac_new(-33,4);
  frac *f3 = frac_add(f1,f2);
  cr_assert(f3->num==-11 && f3->denom==4);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_add, frac_add_6, .timeout=2)
{
  frac *f1 = frac_new(0,5);
  frac *f2 = frac_new(9,5);
  frac *f3 = frac_add(f1,f2);
  cr_assert(f3->num==9 && f3->denom==5);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_add, frac_add_7, .timeout=2)
{
  frac *f1 = frac_new(99,-22);
  frac *f2 = frac_new(22,333);
  frac *f3 = frac_add(f1,f2);
  cr_assert(f3->num==-2953 && f3->denom==666);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_add, frac_add_8, .timeout=2)
{
  frac *f1 = frac_new(12,23);
  frac *f2 = frac_new(34,56);
  frac *f3 = frac_add(f1,f2);
  cr_assert(f3->num==727 && f3->denom==644);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_add, frac_add_9, .timeout=2)
{
  frac *f1 = frac_new(-12,54);
  frac *f2 = frac_new(-98,76);
  frac *f3 = frac_add(f1,f2);
  cr_assert(f3->num==-517 && f3->denom==342);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_add, frac_add_10, .timeout=2)
{
  frac *f1 = frac_new(1234,4567);
  frac *f2 = frac_new(7865,4332);
  frac *f3 = frac_add(f1,f2);
  cr_assert(f3->num==41265143 && f3->denom==19784244);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_sub, frac_sub_0, .timeout=2)
{
  frac *f1 = frac_new(1,2);
  frac *f2 = frac_new(1,3);
  frac *f3 = frac_sub(f1,f2);
  cr_assert(f3->num==1 && f3->denom==6);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_sub, frac_sub_1, .timeout=2)
{
  frac *f1 = frac_new(11,22);
  frac *f2 = frac_new(333,666);
  frac *f3 = frac_sub(f1,f2);
  cr_assert(f3->num==0 && f3->denom==1);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_sub, frac_sub_2, .timeout=2)
{
  frac *f1 = frac_new(1,3);
  frac *f2 = frac_new(7,8);
  frac *f3 = frac_sub(f1,f2);
  cr_assert(f3->num==-13 && f3->denom==24);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_sub, frac_sub_3, .timeout=2)
{
  frac *f1 = frac_new(77,8);
  frac *f2 = frac_new(88,7);
  frac *f3 = frac_sub(f1,f2);
  cr_assert(f3->num==-165 && f3->denom==56);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_sub, frac_sub_4, .timeout=2)
{
  frac *f1 = frac_new(-1,2);
  frac *f2 = frac_new(-3,-4);
  frac *f3 = frac_sub(f1,f2);
  cr_assert(f3->num==-5 && f3->denom==4);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_sub, frac_sub_5, .timeout=2)
{
  frac *f1 = frac_new(11,2);
  frac *f2 = frac_new(-33,4);
  frac *f3 = frac_sub(f1,f2);
  cr_assert(f3->num==55 && f3->denom==4);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_sub, frac_sub_6, .timeout=2)
{
  frac *f1 = frac_new(0,5);
  frac *f2 = frac_new(9,5);
  frac *f3 = frac_sub(f1,f2);
  cr_assert(f3->num==-9 && f3->denom==5);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_sub, frac_sub_7, .timeout=2)
{
  frac *f1 = frac_new(99,-22);
  frac *f2 = frac_new(22,333);
  frac *f3 = frac_sub(f1,f2);
  cr_assert(f3->num==-3041 && f3->denom==666);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_sub, frac_sub_8, .timeout=2)
{
  frac *f1 = frac_new(12,23);
  frac *f2 = frac_new(34,56);
  frac *f3 = frac_sub(f1,f2);
  cr_assert(f3->num==-55 && f3->denom==644);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_sub, frac_sub_9, .timeout=2)
{
  frac *f1 = frac_new(-12,54);
  frac *f2 = frac_new(-98,76);
  frac *f3 = frac_sub(f1,f2);
  cr_assert(f3->num==365 && f3->denom==342);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_sub, frac_sub_10, .timeout=2)
{
  frac *f1 = frac_new(1234,4567);
  frac *f2 = frac_new(7865,4332);
  frac *f3 = frac_sub(f1,f2);
  cr_assert(f3->num==-30573767 && f3->denom==19784244);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_mult, frac_mult_0, .timeout=2)
{
  frac *f1 = frac_new(1,2);
  frac *f2 = frac_new(1,3);
  frac *f3 = frac_mult(f1,f2);
  cr_assert(f3->num==1 && f3->denom==6);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_mult, frac_mult_1, .timeout=2)
{
  frac *f1 = frac_new(11,22);
  frac *f2 = frac_new(333,666);
  frac *f3 = frac_mult(f1,f2);
  cr_assert(f3->num==1 && f3->denom==4);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_mult, frac_mult_2, .timeout=2)
{
  frac *f1 = frac_new(1,3);
  frac *f2 = frac_new(7,8);
  frac *f3 = frac_mult(f1,f2);
  cr_assert(f3->num==7 && f3->denom==24);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_mult, frac_mult_3, .timeout=2)
{
  frac *f1 = frac_new(77,8);
  frac *f2 = frac_new(88,7);
  frac *f3 = frac_mult(f1,f2);
  cr_assert(f3->num==121 && f3->denom==1);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_mult, frac_mult_4, .timeout=2)
{
  frac *f1 = frac_new(-1,2);
  frac *f2 = frac_new(-3,-4);
  frac *f3 = frac_mult(f1,f2);
  cr_assert(f3->num==-3 && f3->denom==8);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_mult, frac_mult_5, .timeout=2)
{
  frac *f1 = frac_new(11,2);
  frac *f2 = frac_new(-33,4);
  frac *f3 = frac_mult(f1,f2);
  cr_assert(f3->num==-363 && f3->denom==8);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_mult, frac_mult_6, .timeout=2)
{
  frac *f1 = frac_new(0,5);
  frac *f2 = frac_new(9,5);
  frac *f3 = frac_mult(f1,f2);
  cr_assert(f3->num==0 && f3->denom==1);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_mult, frac_mult_7, .timeout=2)
{
  frac *f1 = frac_new(99,-22);
  frac *f2 = frac_new(22,333);
  frac *f3 = frac_mult(f1,f2);
  cr_assert(f3->num==-11 && f3->denom==37);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_mult, frac_mult_8, .timeout=2)
{
  frac *f1 = frac_new(12,23);
  frac *f2 = frac_new(34,56);
  frac *f3 = frac_mult(f1,f2);
  cr_assert(f3->num==51 && f3->denom==161);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_mult, frac_mult_9, .timeout=2)
{
  frac *f1 = frac_new(-12,54);
  frac *f2 = frac_new(-98,76);
  frac *f3 = frac_mult(f1,f2);
  cr_assert(f3->num==49 && f3->denom==171);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_mult, frac_mult_10, .timeout=2)
{
  frac *f1 = frac_new(1234,4567);
  frac *f2 = frac_new(7865,4332);
  frac *f3 = frac_mult(f1,f2);
  cr_assert(f3->num==4852705 && f3->denom==9892122);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_div, frac_div_0, .timeout=2)
{
  frac *f1 = frac_new(1,2);
  frac *f2 = frac_new(1,3);
  frac *f3 = frac_div(f1,f2);
  cr_assert(f3->num==3 && f3->denom==2);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_div, frac_div_1, .timeout=2)
{
  frac *f1 = frac_new(11,22);
  frac *f2 = frac_new(333,666);
  frac *f3 = frac_div(f1,f2);
  cr_assert(f3->num==1 && f3->denom==1);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_div, frac_div_2, .timeout=2)
{
  frac *f1 = frac_new(1,3);
  frac *f2 = frac_new(7,8);
  frac *f3 = frac_div(f1,f2);
  cr_assert(f3->num==8 && f3->denom==21);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_div, frac_div_3, .timeout=2)
{
  frac *f1 = frac_new(77,8);
  frac *f2 = frac_new(88,7);
  frac *f3 = frac_div(f1,f2);
  cr_assert(f3->num==49 && f3->denom==64);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_div, frac_div_4, .timeout=2)
{
  frac *f1 = frac_new(-1,2);
  frac *f2 = frac_new(-3,-4);
  frac *f3 = frac_div(f1,f2);
  cr_assert(f3->num==-2 && f3->denom==3);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_div, frac_div_5, .timeout=2)
{
  frac *f1 = frac_new(11,2);
  frac *f2 = frac_new(-33,4);
  frac *f3 = frac_div(f1,f2);
  cr_assert(f3->num==-2 && f3->denom==3);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_div, frac_div_6, .timeout=2)
{
  frac *f1 = frac_new(0,5);
  frac *f2 = frac_new(9,5);
  frac *f3 = frac_div(f1,f2);
  cr_assert(f3->num==0 && f3->denom==1);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_div, frac_div_7, .timeout=2)
{
  frac *f1 = frac_new(99,-22);
  frac *f2 = frac_new(22,333);
  frac *f3 = frac_div(f1,f2);
  cr_assert(f3->num==-2997 && f3->denom==44);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_div, frac_div_8, .timeout=2)
{
  frac *f1 = frac_new(12,23);
  frac *f2 = frac_new(34,56);
  frac *f3 = frac_div(f1,f2);
  cr_assert(f3->num==336 && f3->denom==391);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_div, frac_div_9, .timeout=2)
{
  frac *f1 = frac_new(-12,54);
  frac *f2 = frac_new(-98,76);
  frac *f3 = frac_div(f1,f2);
  cr_assert(f3->num==76 && f3->denom==441);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_div, frac_div_10, .timeout=2)
{
  frac *f1 = frac_new(1234,4567);
  frac *f2 = frac_new(7865,4332);
  frac *f3 = frac_div(f1,f2);
  cr_assert(f3->num==5345688 && f3->denom==35919455);
  free(f3);
  free(f2);
  free(f1);
}

Test(hw3_frac_raise, frac_raise_0, .timeout=2)
{
  frac *f1 = frac_new(1,2);
  unsigned int n = 0;
  frac *f2 = frac_raise(f1,n);
  cr_assert(f2->num==1 && f2->denom==1);
  free(f1);
}

Test(hw3_frac_raise, frac_raise_1, .timeout=2)
{
  frac *f1 = frac_new(1,2);
  unsigned int n = 1;
  frac *f2 = frac_raise(f1,n);
  cr_assert(f2->num==1 && f2->denom==2);
  free(f1);
}

Test(hw3_frac_raise, frac_raise_2, .timeout=2)
{
  frac *f1 = frac_new(1,2);
  unsigned int n = 2;
  frac *f2 = frac_raise(f1,n);
  cr_assert(f2->num==1 && f2->denom==4);
  free(f1);
}

Test(hw3_frac_raise, frac_raise_3, .timeout=2)
{
  frac *f1 = frac_new(1,2);
  unsigned int n = 3;
  frac *f2 = frac_raise(f1,n);
  cr_assert(f2->num==1 && f2->denom==8);
  free(f1);
}

Test(hw3_frac_raise, frac_raise_4, .timeout=2)
{
  frac *f1 = frac_new(2,3);
  unsigned int n = 4;
  frac *f2 = frac_raise(f1,n);
  cr_assert(f2->num==16 && f2->denom==81);
  free(f1);
}

Test(hw3_frac_raise, frac_raise_5, .timeout=2)
{
  frac *f1 = frac_new(-1,2);
  unsigned int n = 0;
  frac *f2 = frac_raise(f1,n);
  cr_assert(f2->num==1 && f2->denom==1);
  free(f1);
}

Test(hw3_frac_raise, frac_raise_6, .timeout=2)
{
  frac *f1 = frac_new(-1,2);
  unsigned int n = 1;
  frac *f2 = frac_raise(f1,n);
  cr_assert(f2->num==-1 && f2->denom==2);
  free(f1);
}

Test(hw3_frac_raise, frac_raise_7, .timeout=2)
{
  frac *f1 = frac_new(-1,2);
  unsigned int n = 2;
  frac *f2 = frac_raise(f1,n);
  cr_assert(f2->num==1 && f2->denom==4);
  free(f1);
}

Test(hw3_frac_raise, frac_raise_8, .timeout=2)
{
  frac *f1 = frac_new(-1,2);
  unsigned int n = 3;
  frac *f2 = frac_raise(f1,n);
  cr_assert(f2->num==-1 && f2->denom==8);
  free(f1);
}

Test(hw3_frac_raise, frac_raise_9, .timeout=2)
{
  frac *f1 = frac_new(-2,3);
  unsigned int n = 4;
  frac *f2 = frac_raise(f1,n);
  cr_assert(f2->num==16 && f2->denom==81);
  free(f1);
}

Test(hw3_frac_raise, frac_raise_10, .timeout=2)
{
  frac *f1 = frac_new(33,44);
  unsigned int n = 2;
  frac *f2 = frac_raise(f1,n);
  cr_assert(f2->num==9 && f2->denom==16);
  free(f1);
}

Test(hw3_frac_raise, frac_raise_11, .timeout=2)
{
  frac *f1 = frac_new(22,55);
  unsigned int n = 4;
  frac *f2 = frac_raise(f1,n);
  cr_assert(f2->num==16 && f2->denom==625);
  free(f1);
}

Test(hw3_frac_raise, frac_raise_12, .timeout=2)
{
  frac *f1 = frac_new(35,56);
  unsigned int n = 3;
  frac *f2 = frac_raise(f1,n);
  cr_assert(f2->num==125 && f2->denom==512);
  free(f1);
}

Test(hw3_frac_raise, frac_raise_13, .timeout=2)
{
  frac *f1 = frac_new(-99,88);
  unsigned int n = 2;
  frac *f2 = frac_raise(f1,n);
  cr_assert(f2->num==81 && f2->denom==64);
  free(f1);
}

Test(hw3_frac_eq, frac_eq_0, .timeout=2)
{
  frac *f1 = frac_new(1,2);
  frac *f2 = frac_new(1,3);
  cr_assert(!frac_eq(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_eq, frac_eq_1, .timeout=2)
{
  frac *f1 = frac_new(1,2);
  frac *f2 = frac_new(2,3);
  cr_assert(!frac_eq(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_eq, frac_eq_2, .timeout=2)
{
  frac *f1 = frac_new(1,3);
  frac *f2 = frac_new(2,6);
  cr_assert(frac_eq(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_eq, frac_eq_3, .timeout=2)
{
  frac *f1 = frac_new(7,8);
  frac *f2 = frac_new(3,8);
  cr_assert(!frac_eq(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_eq, frac_eq_4, .timeout=2)
{
  frac *f1 = frac_new(11,22);
  frac *f2 = frac_new(2,3);
  cr_assert(!frac_eq(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_eq, frac_eq_5, .timeout=2)
{
  frac *f1 = frac_new(-1,2);
  frac *f2 = frac_new(1,-2);
  cr_assert(frac_eq(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_eq, frac_eq_6, .timeout=2)
{
  frac *f1 = frac_new(1,2);
  frac *f2 = frac_new(-10,-20);
  cr_assert(frac_eq(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_eq, frac_eq_7, .timeout=2)
{
  frac *f1 = frac_new(0,1);
  frac *f2 = frac_new(0,2);
  cr_assert(frac_eq(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_eq, frac_eq_8, .timeout=2)
{
  frac *f1 = frac_new(10,20);
  frac *f2 = frac_new(30,40);
  cr_assert(!frac_eq(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_eq, frac_eq_9, .timeout=2)
{
  frac *f1 = frac_new(10,20);
  frac *f2 = frac_new(30,41);
  cr_assert(!frac_eq(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_eq, frac_eq_10, .timeout=2)
{
  frac *f1 = frac_new(22,321);
  frac *f2 = frac_new(234,543);
  cr_assert(!frac_eq(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_eq, frac_eq_11, .timeout=2)
{
  frac *f1 = frac_new(349,5984);
  frac *f2 = frac_new(-21,234);
  cr_assert(!frac_eq(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_lt, frac_lt_0, .timeout=2)
{
  frac *f1 = frac_new(1,2);
  frac *f2 = frac_new(1,3);
  cr_assert(!frac_lt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_lt, frac_lt_1, .timeout=2)
{
  frac *f1 = frac_new(1,2);
  frac *f2 = frac_new(2,3);
  cr_assert(frac_lt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_lt, frac_lt_2, .timeout=2)
{
  frac *f1 = frac_new(1,3);
  frac *f2 = frac_new(2,6);
  cr_assert(!frac_lt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_lt, frac_lt_3, .timeout=2)
{
  frac *f1 = frac_new(7,8);
  frac *f2 = frac_new(3,8);
  cr_assert(!frac_lt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_lt, frac_lt_4, .timeout=2)
{
  frac *f1 = frac_new(11,22);
  frac *f2 = frac_new(2,3);
  cr_assert(frac_lt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_lt, frac_lt_5, .timeout=2)
{
  frac *f1 = frac_new(-1,2);
  frac *f2 = frac_new(1,-2);
  cr_assert(!frac_lt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_lt, frac_lt_6, .timeout=2)
{
  frac *f1 = frac_new(1,2);
  frac *f2 = frac_new(-10,-20);
  cr_assert(!frac_lt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_lt, frac_lt_7, .timeout=2)
{
  frac *f1 = frac_new(0,1);
  frac *f2 = frac_new(0,2);
  cr_assert(!frac_lt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_lt, frac_lt_8, .timeout=2)
{
  frac *f1 = frac_new(10,20);
  frac *f2 = frac_new(30,40);
  cr_assert(frac_lt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_lt, frac_lt_9, .timeout=2)
{
  frac *f1 = frac_new(10,20);
  frac *f2 = frac_new(30,41);
  cr_assert(frac_lt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_lt, frac_lt_10, .timeout=2)
{
  frac *f1 = frac_new(22,321);
  frac *f2 = frac_new(234,543);
  cr_assert(frac_lt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_lt, frac_lt_11, .timeout=2)
{
  frac *f1 = frac_new(349,5984);
  frac *f2 = frac_new(-21,234);
  cr_assert(!frac_lt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_gt, frac_gt_0, .timeout=2)
{
  frac *f1 = frac_new(1,2);
  frac *f2 = frac_new(1,3);
  cr_assert(frac_gt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_gt, frac_gt_1, .timeout=2)
{
  frac *f1 = frac_new(1,2);
  frac *f2 = frac_new(2,3);
  cr_assert(!frac_gt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_gt, frac_gt_2, .timeout=2)
{
  frac *f1 = frac_new(1,3);
  frac *f2 = frac_new(2,6);
  cr_assert(!frac_gt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_gt, frac_gt_3, .timeout=2)
{
  frac *f1 = frac_new(7,8);
  frac *f2 = frac_new(3,8);
  cr_assert(frac_gt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_gt, frac_gt_4, .timeout=2)
{
  frac *f1 = frac_new(11,22);
  frac *f2 = frac_new(2,3);
  cr_assert(!frac_gt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_gt, frac_gt_5, .timeout=2)
{
  frac *f1 = frac_new(-1,2);
  frac *f2 = frac_new(1,-2);
  cr_assert(!frac_gt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_gt, frac_gt_6, .timeout=2)
{
  frac *f1 = frac_new(1,2);
  frac *f2 = frac_new(-10,-20);
  cr_assert(!frac_gt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_gt, frac_gt_7, .timeout=2)
{
  frac *f1 = frac_new(0,1);
  frac *f2 = frac_new(0,2);
  cr_assert(!frac_gt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_gt, frac_gt_8, .timeout=2)
{
  frac *f1 = frac_new(10,20);
  frac *f2 = frac_new(30,40);
  cr_assert(!frac_gt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_gt, frac_gt_9, .timeout=2)
{
  frac *f1 = frac_new(10,20);
  frac *f2 = frac_new(30,41);
  cr_assert(!frac_gt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_gt, frac_gt_10, .timeout=2)
{
  frac *f1 = frac_new(22,321);
  frac *f2 = frac_new(234,543);
  cr_assert(!frac_gt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_gt, frac_gt_11, .timeout=2)
{
  frac *f1 = frac_new(349,5984);
  frac *f2 = frac_new(-21,234);
  cr_assert(frac_gt(f1,f2));
  free(f2);
  free(f1);
}

Test(hw3_frac_approx, frac_approx_0, .timeout=2)
{
  frac *f1 = frac_new(1,2);
  cr_assert(within(TOL,frac_approx(f1),0.5));
  free(f1);
}

Test(hw3_frac_approx, frac_approx_1, .timeout=2)
{
  frac *f1 = frac_new(1,3);
  cr_assert(within(TOL,frac_approx(f1),0.3333333333333333));
  free(f1);
}

Test(hw3_frac_approx, frac_approx_2, .timeout=2)
{
  frac *f1 = frac_new(7,8);
  cr_assert(within(TOL,frac_approx(f1),0.875));
  free(f1);
}

Test(hw3_frac_approx, frac_approx_3, .timeout=2)
{
  frac *f1 = frac_new(8,12);
  cr_assert(within(TOL,frac_approx(f1),0.6666666666666666));
  free(f1);
}

Test(hw3_frac_approx, frac_approx_4, .timeout=2)
{
  frac *f1 = frac_new(-1,23);
  cr_assert(within(TOL,frac_approx(f1),-0.043478260869565216));
  free(f1);
}

Test(hw3_frac_approx, frac_approx_5, .timeout=2)
{
  frac *f1 = frac_new(2,-34);
  cr_assert(within(TOL,frac_approx(f1),-0.058823529411764705));
  free(f1);
}

Test(hw3_frac_approx, frac_approx_6, .timeout=2)
{
  frac *f1 = frac_new(22,33);
  cr_assert(within(TOL,frac_approx(f1),0.6666666666666666));
  free(f1);
}

Test(hw3_frac_approx, frac_approx_7, .timeout=2)
{
  frac *f1 = frac_new(324,432);
  cr_assert(within(TOL,frac_approx(f1),0.75));
  free(f1);
}

Test(hw3_frac_approx, frac_approx_8, .timeout=2)
{
  frac *f1 = frac_new(12345,54322);
  cr_assert(within(TOL,frac_approx(f1),0.22725599204742095));
  free(f1);
}

Test(hw3_frac_tos, frac_tos_0, .timeout=2)
{
  frac *f1 = frac_new(1,2);
  char *s = frac_tos(f1);
  cr_assert(!strcmp(s,"1/2"));
  free(s);
  free(f1);
}

Test(hw3_frac_tos, frac_tos_1, .timeout=2)
{
  frac *f1 = frac_new(1,3);
  char *s = frac_tos(f1);
  cr_assert(!strcmp(s,"1/3"));
  free(s);
  free(f1);
}

Test(hw3_frac_tos, frac_tos_2, .timeout=2)
{
  frac *f1 = frac_new(7,8);
  char *s = frac_tos(f1);
  cr_assert(!strcmp(s,"7/8"));
  free(s);
  free(f1);
}

Test(hw3_frac_tos, frac_tos_3, .timeout=2)
{
  frac *f1 = frac_new(8,12);
  char *s = frac_tos(f1);
  cr_assert(!strcmp(s,"2/3"));
  free(s);
  free(f1);
}

Test(hw3_frac_tos, frac_tos_4, .timeout=2)
{
  frac *f1 = frac_new(-1,23);
  char *s = frac_tos(f1);
  cr_assert(!strcmp(s,"-1/23"));
  free(s);
  free(f1);
}

Test(hw3_frac_tos, frac_tos_5, .timeout=2)
{
  frac *f1 = frac_new(2,-34);
  char *s = frac_tos(f1);
  cr_assert(!strcmp(s,"-1/17"));
  free(s);
  free(f1);
}

Test(hw3_frac_tos, frac_tos_6, .timeout=2)
{
  frac *f1 = frac_new(22,33);
  char *s = frac_tos(f1);
  cr_assert(!strcmp(s,"2/3"));
  free(s);
  free(f1);
}

Test(hw3_frac_tos, frac_tos_7, .timeout=2)
{
  frac *f1 = frac_new(324,432);
  char *s = frac_tos(f1);
  cr_assert(!strcmp(s,"3/4"));
  free(s);
  free(f1);
}

Test(hw3_frac_tos, frac_tos_8, .timeout=2)
{
  frac *f1 = frac_new(12345,54322);
  char *s = frac_tos(f1);
  cr_assert(!strcmp(s,"12345/54322"));
  free(s);
  free(f1);
}

Test(hw3_linspace, linspace_0, .timeout=2)
{
  frac *f1 = frac_new(1,1);
  frac *f2 = frac_new(2,1);
  double *s = linspace(f1,f2,2);
  double arr[] = {1.0,1.5,2.0};
  for (int i=0; i<2+1; i++) {
    cr_assert(within(TOL,s[i],arr[i]));
  }
  free(s);
  free(f2);
  free(f1);
}

Test(hw3_linspace, linspace_1, .timeout=2)
{
  frac *f1 = frac_new(1,1);
  frac *f2 = frac_new(2,1);
  double *s = linspace(f1,f2,3);
  double arr[] = {1.0,1.3333333333333333,1.6666666666666665,2.0};
  for (int i=0; i<3+1; i++) {
    cr_assert(within(TOL,s[i],arr[i]));
  }
  free(s);
  free(f2);
  free(f1);
}

Test(hw3_linspace, linspace_2, .timeout=2)
{
  frac *f1 = frac_new(1,1);
  frac *f2 = frac_new(2,1);
  double *s = linspace(f1,f2,4);
  double arr[] = {1.0,1.25,1.5,1.75,2.0};
  for (int i=0; i<4+1; i++) {
    cr_assert(within(TOL,s[i],arr[i]));
  }
  free(s);
  free(f2);
  free(f1);
}

Test(hw3_linspace, linspace_3, .timeout=2)
{
  frac *f1 = frac_new(1,1);
  frac *f2 = frac_new(2,1);
  double *s = linspace(f1,f2,5);
  double arr[] = {1.0,1.2,1.4,1.5999999999999999,1.7999999999999998,2.0};
  for (int i=0; i<5+1; i++) {
    cr_assert(within(TOL,s[i],arr[i]));
  }
  free(s);
  free(f2);
  free(f1);
}

Test(hw3_linspace, linspace_4, .timeout=2)
{
  frac *f1 = frac_new(1,2);
  frac *f2 = frac_new(7,8);
  double *s = linspace(f1,f2,6);
  double arr[] = {0.5,0.5625,0.625,0.6875,0.75,0.8125,0.875};
  for (int i=0; i<6+1; i++) {
    cr_assert(within(TOL,s[i],arr[i]));
  }
  free(s);
  free(f2);
  free(f1);
}

Test(hw3_linspace, linspace_5, .timeout=2)
{
  frac *f1 = frac_new(0,1);
  frac *f2 = frac_new(8,9);
  double *s = linspace(f1,f2,11);
  double arr[] = {0.0,0.0808080808080808,0.1616161616161616,0.2424242424242424,0.3232323232323232,0.404040404040404,0.48484848484848475,0.5656565656565655,0.6464646464646463,0.7272727272727271,0.8080808080808078,0.8888888888888888};
  for (int i=0; i<11+1; i++) {
    cr_assert(within(TOL,s[i],arr[i]));
  }
  free(s);
  free(f2);
  free(f1);
}

Test(hw3_linspace, linspace_6, .timeout=2)
{
  frac *f1 = frac_new(1,2);
  frac *f2 = frac_new(3,4);
  double *s = linspace(f1,f2,5);
  double arr[] = {0.5,0.55,0.6000000000000001,0.6500000000000001,0.7000000000000002,0.75};
  for (int i=0; i<5+1; i++) {
    cr_assert(within(TOL,s[i],arr[i]));
  }
  free(s);
  free(f2);
  free(f1);
}

Test(hw3_linspace, linspace_7, .timeout=2)
{
  frac *f1 = frac_new(-1,2);
  frac *f2 = frac_new(5,6);
  double *s = linspace(f1,f2,10);
  double arr[] = {-0.5,-0.36666666666666664,-0.23333333333333328,-0.09999999999999992,0.03333333333333344,0.1666666666666668,0.30000000000000016,0.4333333333333335,0.5666666666666669,0.7000000000000002,0.8333333333333334};
  for (int i=0; i<10+1; i++) {
    cr_assert(within(TOL,s[i],arr[i]));
  }
  free(s);
  free(f2);
  free(f1);
}

Test(hw3_frac_sum, frac_sum_0, .timeout=2)
{
  frac arr[] = {
  };
  frac *s = frac_sum(arr,0);
  cr_assert(s->num==0 && s->denom==1);
  free(s);
}

Test(hw3_frac_sum, frac_sum_1, .timeout=2)
{
  frac arr[] = {
    stack_frac(6,77)
  };
  frac *s = frac_sum(arr,1);
  cr_assert(s->num==6 && s->denom==77);
  free(s);
}

Test(hw3_frac_sum, frac_sum_2, .timeout=2)
{
  frac arr[] = {
    stack_frac(1,2),
    stack_frac(2,3)
  };
  frac *s = frac_sum(arr,2);
  cr_assert(s->num==7 && s->denom==6);
  free(s);
}

Test(hw3_frac_sum, frac_sum_3, .timeout=2)
{
  frac arr[] = {
    stack_frac(1,2),
    stack_frac(2,3),
    stack_frac(11,1),
    stack_frac(9,88)
  };
  frac *s = frac_sum(arr,4);
  cr_assert(s->num==3239 && s->denom==264);
  free(s);
}

Test(hw3_frac_sum, frac_sum_4, .timeout=2)
{
  frac arr[] = {
    stack_frac(0,1),
    stack_frac(2,3),
    stack_frac(0,1),
    stack_frac(0,1),
    stack_frac(0,1)
  };
  frac *s = frac_sum(arr,5);
  cr_assert(s->num==2 && s->denom==3);
  free(s);
}

Test(hw3_frac_sum, frac_sum_5, .timeout=2)
{
  frac arr[] = {
    stack_frac(-1,2),
    stack_frac(-1,3),
    stack_frac(-1,4),
    stack_frac(-1,5)
  };
  frac *s = frac_sum(arr,4);
  cr_assert(s->num==-77 && s->denom==60);
  free(s);
}

Test(hw3_frac_sum, frac_sum_6, .timeout=2)
{
  frac arr[] = {
    stack_frac(41,152),
    stack_frac(263,329),
    stack_frac(1234,5667)
  };
  frac *s = frac_sum(arr,3);
  cr_assert(s->num==364696027 && s->denom==283395336);
  free(s);
}

