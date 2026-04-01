#include <criterion/criterion.h>
#include <math.h>
#include <stdio.h>
#include "hw1.h"

// ======== constants

const double TOLERANCE = 0.001;
// We will use this for testing near-equality of floating-point
// numbers.

// ======== helper functions

int within(double epsilon, double a, double b)
{
  return fabs(a-b)<=epsilon;
}

// ======== tests

// (you can add additional tests as you see fit)

// -- warm-up problems

Test(hw1_sphere, sphere_contains_seg00)
{
  cr_assert(sphere_contains_seg(0.0,0.0,0.0,1.0,
				0.1,0.1,0.1,
				0.2,0.2,0.2));
}

Test(hw1_sphere, sphere_contains_seg01)
{
  cr_assert(!sphere_contains_seg(0.0,0.0,0.0,1.0,
				 0.1,0.1,0.1,
				 0.2,0.2,22.2));
}

Test(hw1_sphere, sphere_contains_sphere00)
{
  cr_assert(sphere_contains_sphere(0.0,0.0,0.0,1.0,
				   0.0,0.0,0.0,0.9));
}

// --- bit exercises

Test(hw1_bits, count_ones00)
{
  cr_assert(count_ones(3)==2);
}

Test(hw1_bits, count_zeroes00)
{
  cr_assert(count_zeroes(3)==30);
}

Test(hw1_bits, bits_differ00)
{
  cr_assert(bits_differ(1,3)==1);
}

// --- timestamp

Test(hw1_timestamp, valid_timestamp00)
{
  cr_assert(valid_timestamp(20250401175332));
}

Test(hw1_timestamp, day_before00)
{
  cr_assert(day_before(20251019123456)==20251018123456);
}

Test(hw1_timestamp, day_after00)
{
  cr_assert(day_after(20251019123456)==20251020123456);
}

Test(hw1_timestamp, earlier00)
{
  cr_assert(earlier(20250101121212,20250201121212));
}

Test(hw1_timestamp, later00)
{
  cr_assert(later(20250101121212,20240508123212));
}

// --- rgb

Test(hw1_rgb, rgb_negate00)
{
  cr_assert(rgb_negate(0X00FF11FF)==0X0000EE00);
}

Test(hw1_rgb, rgb_luminance00)
{
  cr_assert(within(TOLERANCE,rgb_luminance(0),0.0));
}

Test(hw1_rgb, rgb_grayscale00)
{
  cr_assert(rgb_grayscale(0)==0);
}
