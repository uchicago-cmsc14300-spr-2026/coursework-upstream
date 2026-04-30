#ifndef __HW4_H__
#define __HW4_H__

struct str_list {
  char *first;
  struct str_list *rest;
};
typedef struct str_list str_list;

// *not graded* write a string array display function for testing
void str_arr_show(char *strings[], unsigned int len);

// *not graded* write a string list display function for testing
void str_list_show(str_list *strings);

// write a constructor for string lists
// *important* strdup `first` when building new list
str_list *cons(char *first, str_list *rest);

// free the string list and all pointed-to strings
void str_list_free(str_list *strings);

// count the number of strings in the list
unsigned int str_list_len(str_list *strings);

// convert an array of strings to a string list
// *important* strings should not be shared; duplicate them
str_list *str_arr_to_list(char *strings[], unsigned int len);

// convert a string list to an array of strings
// *important* strings should not be shared; duplicate them
char **str_list_to_arr(str_list *strings, unsigned int *outlen);

// count the vowels in the string list
// treat uppercase and lowercase a, e, i, o, u, and y as vowels
// (even though in context y is not always a vowel)
unsigned int str_list_count_vowels(str_list *strings);

// build a new strings list whose strings are stripped of a, e, i, o, u, y
// (uppercase or lowercase)
// the returned list must be *all new* (new list, new strings)
str_list *str_list_remove_vowels(str_list *strings);

// split the given string at the given separator
// *forbidden!* the built-in function `strtok` does too much
//   of the heavy lifting this function requires, so do not
//   use it in you code
// for example: split_at("A/B/CC/D") --> ["A","B","CC","D"]
// for example: split_at("A/B//D") --> ["A","B","","D"]
// for example: split_at("A/B/CC/") --> ["A","B","CC",""]
// for example: split_at("/B/CC/") --> ["","B","CC",""]
// for example: split_at("//") --> ["","",""]
str_list *split_at(char *s, char sep);

// given a string, build a list of strings of length 1
// for example: explode("Chicago") --> ["C","h","i","c","a","g","o"]
str_list *explode(char *s);

#endif
