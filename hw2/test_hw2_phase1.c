#include <criterion/criterion.h>
#include <stdio.h>
#include "hw2.h"

// ======== tests

Test(hw2_count_color, count_color00)
{
  rgb colors[] = {0X00000000, 0X000000AB, 0X000000AB};
  cr_assert(count_color(0X000000AB, colors, 3)==2);
}

Test(hw2_negate_colors, negate_colors00)
{
  rgb colors[]  = {0X00FF00FF, 0X0000FF00};
  rgb negated[] = {0X0000FF00, 0X00FF00FF};
  negate_colors(colors,2);
  cr_assert(colors[0]==negated[0] && colors[1]==negated[1]);      
}

Test(hw2_stretch, stretch00)
{
  rgb colors[] = {0, 0X00F0F0F0};
  rgb *s = stretch(colors, 2);
  cr_assert(s[0]==0 && s[1]==0 && s[2]==0X00F0F0F0 && s[3]==0X00F0F0F0);
}

Test(hw2_min_blue, min_blue00)
{
  rgb colors[] = {0X00FFEEBB, 0X00FFDDAA};
  cr_assert(min_blue(colors,2)==0XAA);
}

Test(hw2_connect_rgb_arrays, connect_rgb_arrays00)
{
  rgb colors1[] = {0, 0X0000BB00};
  rgb colors2[] = {0X00FF0000};
  rgb *c = connect_rgb_arrays(colors1,2,colors2,1);
  cr_assert(c[0]==0 &&
	    c[1]==0X0000BB00 &&
	    c[2]==0X00FF0000);
}

Test(hw2_sift_up, sift_up00)
{
  timestamp dates[] = {20250401000000, 20250101000000, 20250201000000};
  sift_up(dates, 1);
  cr_assert(dates[0]==20250101000000 &&
	    dates[1]==20250401000000 &&
	    dates[2]==20250201000000);
}

Test(hw2_sift_down, sift_down00)
{
  timestamp dates[] = {20290401000000, 20250101000000, 20250201000000};
  sift_down(dates, 0, 2);
  cr_assert(dates[0]==20250101000000 &&
	    dates[1]==20290401000000 &&
	    dates[2]==20250201000000);
}

Test(hw2_heapsort_dates, heapsort_dates00)
{
  timestamp dates[] = {20200101000000, 20180101000000, 20140101000000};
  heapsort_dates(dates,3);
  cr_assert(dates[0]==20140101000000 &&
	    dates[1]==20180101000000 &&
	    dates[2]==20200101000000);
}

Test(hw2_distinct_dates, distinct_dates00)
{
  timestamp dates[] = {20240101000000, 20240101000000};
  int n;
  timestamp *ds = distinct_dates(dates,2,&n);
  cr_assert(n==1 && ds[0]==20240101000000);
}

Test(hw2_weekdays, weekdays00)
{
  int n;
  timestamp *w = weekdays(20250405000000, 20250408000000, &n);
  cr_assert(n==2 &&
	    w[0]==20250407000000 &&
	    w[1]==20250408000000);
}

Test(hw2_mondays, mondays00)
{
  int n;
  timestamp *m = mondays(20250405000000, 20250408000000, &n);
  cr_assert(n==1 &&
	    m[0]==20250407000000);
}

Test(hw2_primes, primes00)
{
  int n;
  unsigned int a[] = {1,2,3,4,5,6,7,8,9,99};
  unsigned int *p = primes(a,10,&n);
  cr_assert(n==4 &&
	    p[0]==2 &&
	    p[1]==3 &&
	    p[2]==5 &&
	    p[3]==7);
}

