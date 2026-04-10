// hw1.h, CS143, Spring 2026

#ifndef __HW1_H__
#define __HW1_H__

#include <stdint.h>
#include <math.h>

typedef unsigned char byte;
typedef uint64_t timestamp; // decimal number: YYYYMMDDHHMMSS
typedef uint32_t rgb;       // four bytes: [unused] [r] [g] [b]

// ======== warm-up problems

// A sphere is represented by a center (cx, cy, cz) and a radius.
// A line segment (in three dimensions) is represented by
// its two endpoints a and b.
// Return true if the sphere strictly contains the line segment.
// GIGO if radius is nonpositive.
int sphere_contains_seg(double cx, double cy, double cz, double r,
			double ax, double ay, double az,
			double bx, double by, double bz);

// Return true if s2 is contained strictly within s1.
// GIGO if either radius is nonpositive.
int sphere_contains_sphere(double s1x, double s1y, double s1z, double r1,
			   double s2x, double s2y, double s2z, double r2);

// ======== bit exercises

// Count the bits set to 1 in n.
byte count_ones(uint32_t n);

// Count the bits set to 0 in n.
byte count_zeroes(uint32_t n);

// Count the number of bits that differ, by position, in m and n.
byte bits_differ(uint32_t m, uint32_t n);

// ======== timestamp

// A timestamp is a year, month, day, hour, minute, second
// representation of a moment in time as an integer of the form
// YYYYMMDDHHMMSS.

// By convention, January is month 1 up to December month 12.

// Hours go from 00 to 23, military style; minutes and seconds from 00
// to 59.

// For example, March 26, 2024 at 4:07:23PM is 20240326160723 as a
// timestamp.

// Verify that the timestamp is legitimate. For example, January the
// 49th (of any year) is not a legitimate timestamp, nor is any
// timestamp at 27 o'clock. Yes, the code must check for leap
// years. Helper functions recommended.
// GIGO if the date is prior to the 20th century.
int valid_timestamp(timestamp t);

// Return the timestamp 24 hours before the given moment.
// GIGO if the date is prior to the 20th century.
// GIGO if the date is not valid.
timestamp day_before(timestamp t);

// Return the timestamp 24 hours after the given moment.
// GIGO if the date is prior to the 20th century.
// GIGO if the date is not valid.
timestamp day_after(timestamp t);

// Return true if t1 is an earlier timestamp than t2.
// GIGO if either date is prior to the 20th century.
// GIGO if either date is not valid.
int earlier(timestamp t1, timestamp t2);

// Return true if t1 is a later timestamp than t2.
// GIGO if either date is prior to the 20th century.
// GIGO if either date is not valid.
int later(timestamp t1, timestamp t2);

// ======== rgb

// a "packed rgb" contains 0 in the highest byte, red in the
// second-highest byte, green in the third-highest byte, and blue in
// the lowest byte. For example, the color (255,254,2) is represented
// as 00000000 11111111 11111110 00000010 as a packed rgb. We use four
// bytes, even though one of them is not used, because there is no
// three-byte integer type.

// The negation of a color (r,g,b) is (255-r,255-g,255-b).
// When negating, do not change the 0 byte before r,g,b.
rgb rgb_negate(rgb c);

// The luminance (a measure of brightness) of an RGB color
// is 0.2126R + 0.7152G + 0.0722B. Higher luminance corresponds
// to greater brightness.
// To ensure the results of computing luminance are consistent with
// our tests, compute the _floor_ of the linear combination
// given above.
// Note that this means the luminance of (255,255,255) is 254.0, even
// though that seems wrong.
double rgb_luminance(rgb c);

// The grayscale of a color is (m,m,m) where m is the luminance of the
// color. For example, since the luminance of (11,22,100) is 25.0, the
// grayscale counterpart is (25,25,25).
rgb rgb_grayscale(rgb c);

#endif
