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

Test(hw1_sphere, sphere_contains_seg02)
{
  cr_assert(sphere_contains_seg(0.0,0.0,0.0,1.0,
				0.1,-0.1,0.1,
				0.2,0.2,-0.2));
}

Test(hw1_sphere, sphere_contains_seg03)
{
  cr_assert(sphere_contains_seg(0.0,0.0,0.0,1.0,
				-0.1,-0.1,-0.1,
				0.2,-0.2,-0.2));
}

Test(hw1_sphere, sphere_contains_seg04)
{
  cr_assert(sphere_contains_seg(0.0,0.0,0.0,1.0,
			        0.0,0.0,0.0,
				0.0,0.0,-0.5));
}

Test(hw1_sphere, sphere_contains_seg05)
{
  cr_assert(!sphere_contains_seg(0.0,0.0,0.0,1.0,
				 0.0,0.0,0.0,
				 0.0,1.0,1.0));
}

Test(hw1_sphere, sphere_contains_seg06)
{
  cr_assert(sphere_contains_seg(1.0,1.0,1.0,10.0,
				0.0,0.0,0.0,
			        -2.0,-2.0,-2.0));
}

Test(hw1_sphere, sphere_contains_seg07)
{
  cr_assert(sphere_contains_seg(-10.0,-10.0,-10.0,100.0,
				0.0,0.0,0.0,
			        -2.0,-2.0,-2.0));
}

Test(hw1_sphere, sphere_contains_seg08)
{
  cr_assert(sphere_contains_seg(-10.0,-10.0,-10.0,100.0,
				1.0,1.0,1.0,
			        2.0,2.0,2.0));
}

Test(hw1_sphere, sphere_contains_seg09)
{
  cr_assert(!sphere_contains_seg(-10.0,-10.0,-10.0,100.0,
				 1.0,1.0,1.0,
				 2.0,2.0,2111.0));
}

Test(hw1_sphere, sphere_contains_sphere00)
{
  cr_assert(sphere_contains_sphere(0.0,0.0,0.0,1.0,
				   0.0,0.0,0.0,0.9));
}

Test(hw1_sphere, sphere_contains_sphere01)
{
  cr_assert(sphere_contains_sphere(0.0,0.0,0.0,1.0,
				   0.1,0.1,0.1,0.1));
}

Test(hw1_sphere, sphere_contains_sphere02)
{
  cr_assert(!sphere_contains_sphere(0.0,0.0,0.0,1.0,
				    0.1,0.1,0.1,1.1));
}

Test(hw1_sphere, sphere_contains_sphere03)
{
  cr_assert(sphere_contains_sphere(0.0,0.0,0.0,1.0,
				   0.0,0.0,0.9,0.001));
}

Test(hw1_sphere, sphere_contains_sphere04)
{
  cr_assert(!sphere_contains_sphere(0.0,0.0,0.0,1.0,
				    9.0,9.0,9.0,0.1));
}

Test(hw1_sphere, sphere_contains_sphere05)
{
  cr_assert(!sphere_contains_sphere(1.0,1.0,1.0,1.0,
				    9.0,9.0,9.0,0.1));
}

Test(hw1_sphere, sphere_contains_sphere06)
{
  cr_assert(!sphere_contains_sphere(1.0,1.0,1.0,1.0,
				    9.0,9.0,9.0,0.1));
}

Test(hw1_sphere, sphere_contains_sphere07)
{
  cr_assert(!sphere_contains_sphere(1.0,1.0,1.0,1.0,
				    1.1,1.1,1.1,1.0));
}

Test(hw1_sphere, sphere_contains_sphere08)
{
  cr_assert(sphere_contains_sphere(-1.0,-1.0,-1.0,1.0,
				   -0.9,-0.9,-0.9,0.01));
}

Test(hw1_sphere, sphere_contains_sphere09)
{
  cr_assert(!sphere_contains_sphere(-1.0,1.0,1.0,1.0,
				    1.1,1.1,1.1,1.0));
}

// --- bit exercises

Test(hw1_bits, count_ones00)
{
  cr_assert(count_ones(3)==2);
}

Test(hw1_bits, count_ones01)
{
  cr_assert(count_ones(0XFFFFFFFF)==32);
}

Test(hw1_bits, count_ones02)
{
  cr_assert(count_ones(0X0)==0);
}

Test(hw1_bits, count_ones03)
{
  cr_assert(count_ones(0XAAAAAAAA)==16);
}

Test(hw1_bits, count_ones04)
{
  cr_assert(count_ones(0XF00F0FF0)==16);
}

Test(hw1_bits, count_ones05)
{
  cr_assert(count_ones(0X11111111)==8);
}

Test(hw1_bits, count_ones06)
{
  cr_assert(count_ones(0X10011001)==4);
}

Test(hw1_bits, count_zeroes00)
{
  cr_assert(count_zeroes(3)==30);
}

Test(hw1_bits, count_zeroes01)
{
  cr_assert(count_zeroes(0XFFFFFFFF)==0);
}

Test(hw1_bits, count_zeroes02)
{
  cr_assert(count_zeroes(0X0)==32);
}

Test(hw1_bits, count_zeroes03)
{
  cr_assert(count_zeroes(0XAAAAAAAA)==16);
}

Test(hw1_bits, count_zeroes04)
{
  cr_assert(count_zeroes(0XF00F0FF0)==16);
}

Test(hw1_bits, count_zeroes05)
{
  cr_assert(count_zeroes(0X11111111)==24);
}

Test(hw1_bits, count_zeroes06)
{
  cr_assert(count_zeroes(0X10011001)==28);
}

Test(hw1_bits, bits_differ00)
{
  cr_assert(bits_differ(1,3)==1);
}

Test(hw1_bits, bits_differ01)
{
  cr_assert(bits_differ(0,0)==0);
}

Test(hw1_bits, bits_differ02)
{
  cr_assert(bits_differ(0XFFFFFFFF,0XFFFFFFFF)==0);
}

Test(hw1_bits, bits_differ03)
{
  cr_assert(bits_differ(0XFFFFFFFF,0)==32);
}

Test(hw1_bits, bits_differ04)
{
  cr_assert(bits_differ(0,0XFFFFFFFF)==32);
}

Test(hw1_bits, bits_differ05)
{
  cr_assert(bits_differ(0XFFFFFFFF,0XFFFF0000)==16);
}

Test(hw1_bits, bits_differ06)
{
  cr_assert(bits_differ(0XFFFF0000,0XFFFFFFFF)==16);
}

Test(hw1_bits, bits_differ07)
{
  cr_assert(bits_differ(0XFFFF0000,0X0000FFFF)==32);
}

Test(hw1_bits, bits_differ08)
{
  cr_assert(bits_differ(0XAABBCCDD,0X0000CCDD)==10);
}

// --- timestamp

Test(hw1_timestamp, valid_timestamp00)
{
  cr_assert(valid_timestamp(20250401175332));
}

Test(hw1_timestamp, valid_timestamp01)
{
  cr_assert(valid_timestamp(19921201232021));
}

Test(hw1_timestamp, valid_timestamp02)
{
  cr_assert(valid_timestamp(20000229050607));
}

Test(hw1_timestamp, valid_timestamp03)
{
  cr_assert(!valid_timestamp(20250431175332));
}

Test(hw1_timestamp, valid_timestamp04)
{
  cr_assert(!valid_timestamp(20250421275332));
}

Test(hw1_timestamp, valid_timestamp05)
{
  cr_assert(!valid_timestamp(20250421179332));
}

Test(hw1_timestamp, valid_timestamp06)
{
  cr_assert(!valid_timestamp(20250421170382));
}

Test(hw1_timestamp, day_before00)
{
  cr_assert(day_before(20251019123456)==20251018123456);
}

Test(hw1_timestamp, day_before01)
{
  cr_assert(day_before(20250101112233)==20241231112233);
}

Test(hw1_timestamp, day_before02)
{
  cr_assert(day_before(20250201032211)==20250131032211);
}

Test(hw1_timestamp, day_before03)
{
  cr_assert(day_before(20040301213141)==20040229213141);
}

Test(hw1_timestamp, day_before04)
{
  cr_assert(day_before(20050301233445)==20050228233445);
}

Test(hw1_timestamp, day_before05)
{
  cr_assert(day_before(20050611001122)==20050610001122);
}

Test(hw1_timestamp, day_before06)
{
  cr_assert(day_before(20050922001122)==20050921001122);
}

Test(hw1_timestamp, day_after00)
{
  cr_assert(day_after(20251019123456)==20251020123456);
}

Test(hw1_timestamp, day_after01)
{
  cr_assert(day_after(20251231112356)==20260101112356);
}

Test(hw1_timestamp, day_after02)
{
  cr_assert(day_after(20250131112356)==20250201112356);
}

Test(hw1_timestamp, day_after03)
{
  cr_assert(day_after(20250130112356)==20250131112356);
}

Test(hw1_timestamp, day_after04)
{
  cr_assert(day_after(20040228220033)==20040229220033);
}

Test(hw1_timestamp, day_after05)
{
  cr_assert(day_after(20050228220055)==20050301220055);
}

Test(hw1_timestamp, day_after06)
{
  cr_assert(day_after(20151122232425)==20151123232425);
}

Test(hw1_timestamp, earlier00)
{
  cr_assert(earlier(20250101121212,20250201121212));
}

Test(hw1_timestamp, earlier01)
{
  cr_assert(earlier(20250101121212,20260101000000));
}

Test(hw1_timestamp, earlier02)
{
  cr_assert(earlier(20250101121212,20250101121213));
}

Test(hw1_timestamp, earlier03)
{
  cr_assert(earlier(20250101121212,20250101121312));
}

Test(hw1_timestamp, earlier04)
{
  cr_assert(earlier(20250101121212,20250101131212));
}

Test(hw1_timestamp, earlier05)
{
  cr_assert(earlier(20250101121212,20250102000000));
}

Test(hw1_timestamp, earlier06)
{
  cr_assert(!earlier(20250101121212,20250101121212));
}

Test(hw1_timestamp, earlier07)
{
  cr_assert(!earlier(20250101121212,20240101121212));
}

Test(hw1_timestamp, later00)
{
  cr_assert(later(20250101121212,20240508123212));
}

Test(hw1_timestamp, later01)
{
  cr_assert(later(20250101121212,20240508123212));
}

Test(hw1_timestamp, later02)
{
  cr_assert(later(20250131121212,20250112234543));
}

Test(hw1_timestamp, later03)
{
  cr_assert(later(20250331121212,20250101234543));
}

Test(hw1_timestamp, later04)
{
  cr_assert(later(20250331121212,20250330121212));
}

Test(hw1_timestamp, later05)
{
  cr_assert(later(20250331121212,20250331121211));
}

Test(hw1_timestamp, later06)
{
  cr_assert(later(20250331121212,20250331121112));
}

Test(hw1_timestamp, later07)
{
  cr_assert(!later(20250331121212,20250331121212));
}

// --- rgb

Test(hw1_rgb, rgb_negate00)
{
  cr_assert(rgb_negate(0X00FF11FF)==0X0000EE00);
}

Test(hw1_rgb, rgb_negate01)
{
  cr_assert(rgb_negate(0X000FF00F)==0X00F00FF0);
}

Test(hw1_rgb, rgb_negate02)
{
  cr_assert(rgb_negate(0X00123456)==0X00EDCBA9);
}

Test(hw1_rgb, rgb_negate03)
{
  cr_assert(rgb_negate(0X00EDCBA9)==0X00123456);
}

Test(hw1_rgb, rgb_negate04)
{
  cr_assert(rgb_negate(0X00A1B1C1)==0X005E4E3E);
}

Test(hw1_rgb, rgb_negate05)
{
  cr_assert(rgb_negate(0)==0X00FFFFFF);
}

Test(hw1_rgb, rgb_negate06)
{
  cr_assert(rgb_negate(0X00FFFFFF)==0);
}

Test(hw1_rgb, rgb_luminance00)
{
  cr_assert(within(TOLERANCE,rgb_luminance(0),0.0));
}

Test(hw1_rgb, luminance01)
{
  cr_assert(within(TOLERANCE,rgb_luminance(0X000A0000),2.0));
}

Test(hw1_rgb, luminance02)
{
  cr_assert(within(TOLERANCE,rgb_luminance(0X00000A00),7.0));
}

Test(hw1_rgb, luminance03)
{
  cr_assert(within(TOLERANCE,rgb_luminance(0X000000A0),11.0));
}

Test(hw1_rgb, luminance04)
{
  cr_assert(within(TOLERANCE,rgb_luminance(0X00A11000),45.0));
}

Test(hw1_rgb, luminance05)
{
  cr_assert(within(TOLERANCE,rgb_luminance(0X001000FF),21.0));
}

Test(hw1_rgb, luminance06)
{
  cr_assert(within(TOLERANCE,rgb_luminance(0X0010FF10),186.0));
}

Test(hw1_rgb, luminance07)
{
  cr_assert(within(TOLERANCE,rgb_luminance(0X00AA00AA),48.0));
}

Test(hw1_rgb, rgb_grayscale00)
{
  cr_assert(rgb_grayscale(0)==0);
}

Test(hw1_rgb, rgb_grayscale01)
{
  cr_assert(rgb_grayscale(0X000A0000)==0X00020202);
}

Test(hw1_rgb, rgb_grayscale02)
{
  cr_assert(rgb_grayscale(0X00000A00)==0X00070707);
}

Test(hw1_rgb, rgb_grayscale03)
{
  cr_assert(rgb_grayscale(0X000000A0)==0X000B0B0B);
}

Test(hw1_rgb, rgb_grayscale04)
{
  cr_assert(rgb_grayscale(0X000B0BB0)==0X00161616);
}

