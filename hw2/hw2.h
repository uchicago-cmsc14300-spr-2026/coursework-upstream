#include <stdint.h>

typedef uint64_t timestamp;
typedef uint32_t rgb;

// count the occurrences of the given color in array
// GIGO if array is NULL or if len is incorrect
int count_color(rgb c, rgb *colors, int len);

// negate all the colors in the array
// do not build an array; modify the array given
// GIGO if array is NULL or if len is incorrect
void negate_colors(rgb *colors, int len);

// return new array of twice the length, with each color appearing twice
// GIGO if arr is NULL or if len is incorrect
rgb *stretch(rgb *colors, int len);

// return the minimum blue component of any color in array
// GIGO if array is NULL or len is not positive
uint8_t min_blue(rgb *arr, int len);

// build new array that is all the colors in a followed by all the colors in b
// GIGO if a or b is NULL or either length incorrect
rgb *connect_rgb_arrays(rgb *a, int alen, rgb *b, int blen);

// sift up min-heap operation
// GIGO if array is NULL or pos is outside the array
void sift_up(timestamp *dates, int pos);

// sift down min-heap operation
// GIGO if array is NULL, if pos is outside the array, or len is incorrect
void sift_down(timestamp *dates, int pos, int len);

// in-place heapsort of timestamp array ascending
// perform in-place heapsort using sift operations
// GIGO if array is NULL or len is incorrect
void heapsort_dates(timestamp *dates, int len);

// return an array of the distinct dates in an array of dates
// assume no particular order for array argument
// the return value must be in ascending order
// GIGO if dates is NULL or len is incorrect
timestamp *distinct_dates(timestamp *dates, int len, int *outlen);

// build array of dates of weekdays from start to end inclusive
// the time part of each timestamp must be valid but is unconstrained
// return NULL and set outlen to 0 if there are no weekdays between dates
// return NULL and set outlen to 0 if end date before start date
timestamp *weekdays(timestamp start_incl, timestamp end_incl, int *outlen);

// build array of dates of Mondays from start to end inclusive
// the time part of each timestamp must be valid but is unconstrained
// return NULL and set outlen to 0 if there are no weekends between dates
// return NULL and set outlen to 0 if end date before start date
timestamp *mondays(timestamp start_incl, timestamp end_incl, int *outlen);

// construct new array, keeping all the primes in the argument array
// report length in count
// if no primes, return NULL and set count to 0
// GIGO if a is NULL or len is incorrect
unsigned int *primes(unsigned int *a, int len, int *count);
