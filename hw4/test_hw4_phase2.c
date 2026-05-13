#include <criterion/criterion.h>
#include <stdio.h>
#include <string.h>
#include "hw4.h"

// ======== helpers

// p2c and p2f are phase2_cons and phase2_free, respectively

// these are used in the tests so that any errors in cons/free in the
// student's code doesn't cause failures when *other* functions are
// being tested

void MISSOURI(char *label, str_list *strings)
{
  printf("+++%s:\t",label);
  for (;strings;strings=strings->rest)
    printf("\"%s\":",strings->first);
  printf("NULL\n");
}

void KANSAS(char *label, char *arr[], int len)
{
  printf("###%s:\t",label);
  for (int i=0; i<len; i++)
    printf("\"%s\":",arr[i]);
  printf("NULL\n");
}

str_list *p2c(char *s, str_list *ss)
{
  str_list *strings = malloc(sizeof(str_list));
  if (!strings) {
    fprintf(stderr,"(p2c) malloc failure (not expected)\n");
    exit(1);
  }
  strings->first = strdup(s);
  strings->rest = ss;
  return strings;
}

// singleton list constructor
str_list *p2cs(char *s)
{
  return p2c(s,NULL);
}

void p2f(str_list *ss)
{
  if (ss) {
    p2f(ss->rest);
    free(ss->first);
    free(ss);
  }
}

int str_list_same(str_list *list1, str_list *list2)
{
  if (!list1 && !list2)
    return 1;
  else if (!list1 || !list2)
    return 0;
  //fprintf(stderr,"(str_list_same) comparing |%s| and |%s|\n",list1->first,list2->first);
  if (!strcmp(list1->first,list2->first)) 
    return str_list_same(list1->rest,list2->rest);
  else
    return 0;
}

int str_arr_same(char *arr1[], char *arr2[], int len)
{
  for (int i=0; i<len; i++)
    if (strcmp(arr1[i],arr2[i]))
      return 0;
  return 1;
}

// ======== tests

Test(hw4_cons, cons_00, .timeout=2)
{
  str_list *strings = cons("XYZ",NULL);
  cr_assert(strings);
  p2f(strings);
}

Test(hw4_cons, cons_01, .timeout=2)
{
  str_list *strings = cons("",NULL);
  cr_assert(strings);
  p2f(strings);
}

Test(hw4_cons, cons_02, .timeout=2)
{
  str_list *strings = cons("",cons("x",NULL));
  cr_assert(strings);
  p2f(strings);
}

Test(hw4_str_list_free, str_list_free_00, .timeout=2)
{
  // note: free functions are not really testable in Criterion, other
  // than to check that they don't crash
  str_list *strings = p2cs("XYZ");
  str_list_free(strings);
  cr_assert(1==1);
}
  
Test(hw4_str_list_len, str_list_len_00, .timeout=2)
{
  str_list *strings = p2cs("XYZ");
  cr_assert(str_list_len(strings)==1);
  p2f(strings);
}

Test(hw4_str_list_len, str_list_len_01, .timeout=2)
{
  str_list *strings = NULL;
  cr_assert(str_list_len(strings)==0);
  p2f(strings);
}

Test(hw4_str_list_len, str_list_len_02, .timeout=2)
{
  str_list *strings = p2c("a",p2c("a",p2c("a",p2c("a",NULL))));
  cr_assert(str_list_len(strings)==4);
  p2f(strings);
}

Test(hw4_str_arr_to_list, str_arr_to_list_00, .timeout=2)
{
  char *arr[] = {"XYZ"};
  str_list *strings = str_arr_to_list(arr,1);
  str_list *expected = p2cs("XYZ");
  cr_assert(str_list_same(strings,expected));
  p2f(expected);
  p2f(strings);
}

Test(hw4_str_arr_to_list, str_arr_to_list_01, .timeout=2)
{
  char *arr[] = {"XYZ","ABC","D"};
  str_list *strings = str_arr_to_list(arr,3);
  str_list *expected = p2c("XYZ",p2c("ABC",p2c("D",NULL)));
  cr_assert(str_list_same(strings,expected));
  p2f(expected);
  p2f(strings);
}

Test(hw4_str_arr_to_list, str_arr_to_list_02, .timeout=2)
{
  char *arr[] = {"x","x","x","x","x"};
  str_list *strings = str_arr_to_list(arr,5);
  str_list *expected = p2c("x",p2c("x",p2c("x",p2c("x",p2c("x",NULL)))));
  cr_assert(str_list_same(strings,expected));
  p2f(expected);
  p2f(strings);
}

Test(hw4_str_list_to_arr, str_list_to_arr_00, .timeout=2)
{
  unsigned int n;
  str_list *strings = p2cs("XYZ");
  char **arr = str_list_to_arr(strings,&n);
  char *expected[] = {"XYZ"};
  cr_assert(n==1 && str_arr_same(arr,expected,1));
  p2f(strings);
}

Test(hw4_str_list_to_arr, str_list_to_arr_01, .timeout=2)
{
  unsigned int n;
  str_list *strings = p2c("a",p2c("b",p2c("c",p2c("d",p2c("e",NULL)))));
  char **arr = str_list_to_arr(strings,&n);
  char *expected[] = {"a","b","c","d","e"};
  cr_assert(n==5);
  cr_assert(str_arr_same(arr,expected,5));
  p2f(strings);
}

Test(hw4_str_list_to_arr, str_list_to_arr_02, .timeout=2)
{
  unsigned int n;
  str_list *strings = p2c("a",p2c("b",p2c("c",p2c("d",p2c("ee",NULL)))));
  char **arr = str_list_to_arr(strings,&n);
  char *expected[] = {"a","b","c","d","ee"};
  cr_assert(n==5 && str_arr_same(arr,expected,5));
  p2f(strings);
}

Test(hw4_str_list_count_vowels, str_list_count_vowels_00, .timeout=2)
{
  str_list *strings = p2cs("ABCDE");
  cr_assert(str_list_count_vowels(strings)==2);
  p2f(strings);
}

Test(hw4_str_list_count_vowels, str_list_count_vowels_01, .timeout=2)
{
  str_list *strings = p2cs("abcde");
  cr_assert(str_list_count_vowels(strings)==2);
  p2f(strings);
}

Test(hw4_str_list_count_vowels, str_list_count_vowels_02, .timeout=2)
{
  str_list *strings = p2cs("AbCde");
  cr_assert(str_list_count_vowels(strings)==2);
  p2f(strings);
}

Test(hw4_str_list_count_vowels, str_list_count_vowels_03, .timeout=2)
{
  cr_assert(str_list_count_vowels(NULL)==0);
}

Test(hw4_str_list_count_vowels, str_list_count_vowels_04, .timeout=2)
{
  str_list *strings = p2c("a",p2c("b",p2c("c",p2c("d",NULL))));
  cr_assert(str_list_count_vowels(strings)==1);
  p2f(strings);
}

Test(hw4_str_list_count_vowels, str_list_count_vowels_05, .timeout=2)
{
  str_list *strings = p2c("AB",p2c("CD",p2c("ef",NULL)));
  cr_assert(str_list_count_vowels(strings)==2);
  p2f(strings);
}

Test(hw4_str_list_remove_vowels, str_list_remove_vowels_00, .timeout=2)
{
  str_list *listA = p2cs("ABC");
  str_list *listB = str_list_remove_vowels(listA);
  str_list *expected = p2cs("BC");
  cr_assert(str_list_same(listB,expected));
  p2f(expected);
  p2f(listB);
  p2f(listA);
}

Test(hw4_str_list_remove_vowels, str_list_remove_vowels_01, .timeout=2)
{
  str_list *listA = p2cs("PQR");
  str_list *listB = str_list_remove_vowels(listA);
  str_list *expected = p2cs("PQR");
  cr_assert(str_list_same(listB,expected));
  p2f(expected);
  p2f(listB);
  p2f(listA);
}

Test(hw4_str_list_remove_vowels, str_list_remove_vowels_02, .timeout=2)
{
  str_list *listA = p2c("works",p2c("in",p2c("theory",NULL)));
  str_list *listB = str_list_remove_vowels(listA);
  str_list *expected = p2c("wrks",p2c("n",p2c("thr",NULL)));
  cr_assert(str_list_same(listB,expected));
  p2f(expected);
  p2f(listB);
  p2f(listA);
}

Test(hw4_str_list_remove_vowels, str_list_remove_vowels_03, .timeout=2)
{
  str_list *listA = p2c("aaa",p2c("bbb",p2c("XYZ",NULL)));
  str_list *listB = str_list_remove_vowels(listA);
  str_list *expected = p2c("",p2c("bbb",p2c("XZ",NULL)));
  cr_assert(str_list_same(listB,expected));
  p2f(expected);
  p2f(listB);
  p2f(listA);
}

Test(hw4_str_list_remove_vowels, str_list_remove_vowels_04, .timeout=2)
{
  str_list *listA = p2c("???",p2c("A:E:O:U:Y:I",NULL));
  str_list *listB = str_list_remove_vowels(listA);
  str_list *expected = p2c("???",p2c(":::::",NULL));
  cr_assert(str_list_same(listB,expected));
  p2f(expected);
  p2f(listB);
  p2f(listA);
}

Test(hw4_str_list_remove_vowels, str_list_remove_vowels_05, .timeout=2)
{
  str_list *listA = p2cs("(aeiouyAEIOUY)");
  str_list *listB = str_list_remove_vowels(listA);
  str_list *expected = p2cs("()");
  cr_assert(str_list_same(listB,expected));
  p2f(expected);
  p2f(listB);
  p2f(listA);
}

Test(hw4_split_at, split_at_00, .timeout=2)
{
  str_list *strings = split_at("a,bb,c",',');
  str_list *expected = p2c("a",p2c("bb",p2c("c",NULL)));
  cr_assert(str_list_same(strings,expected));
  p2f(expected);
  p2f(strings);
}

Test(hw4_split_at, split_at_01, .timeout=2)
{
  str_list *strings = split_at("a,bb,c",'x');
  str_list *expected = p2cs("a,bb,c");
  cr_assert(str_list_same(strings,expected));
  p2f(expected);
  p2f(strings);
}

Test(hw4_split_at, split_at_02, .timeout=2)
{
  str_list *strings = split_at(",a,bb,c",',');
  str_list *expected = p2c("",p2c("a",p2c("bb",p2c("c",NULL))));
  cr_assert(str_list_same(strings,expected));
  p2f(expected);
  p2f(strings);
}

Test(hw4_split_at, split_at_03, .timeout=2)
{
  // we decided to allow either of two answers for this test:
  // - the empty list
  // - the list containing ""
  str_list *strings = split_at("",'/');
  str_list *expected = p2cs("");
  cr_assert(!strings || str_list_same(strings,expected));
  p2f(expected);
  p2f(strings);
}

Test(hw4_split_at, split_at_04, .timeout=2)
{
  str_list *strings = split_at("x//y",'/');
  str_list *expected = p2c("x",p2c("",p2c("y",NULL)));
  cr_assert(str_list_same(strings,expected));
  p2f(expected);
  p2f(strings);
}

Test(hw4_split_at, split_at_05, .timeout=2)
{
  str_list *strings = split_at("x//y",'x');
  str_list *expected = p2c("",p2c("//y",NULL));
  cr_assert(str_list_same(strings,expected));
  p2f(expected);
  p2f(strings);
}

Test(hw4_split_at, split_at_06, .timeout=2)
{
  str_list *strings = split_at("x//y",'x');
  str_list *expected = p2c("",p2c("//y",NULL));
  cr_assert(str_list_same(strings,expected));
  p2f(expected);
  p2f(strings);
}

Test(hw4_split_at, split_at_07, .timeout=2)
{
  str_list *strings = split_at("///",'/');
  str_list *expected = p2c("",p2c("",p2c("",p2c("",NULL))));
  cr_assert(str_list_same(strings,expected));
  p2f(expected);
  p2f(strings);
}

Test(hw4_split_at, split_at_08, .timeout=2)
{
  str_list *strings = split_at("a&/b&&/c",'/');
  str_list *expected = p2c("a&",p2c("b&&",p2cs("c")));
  cr_assert(str_list_same(strings,expected));
  p2f(expected);
  p2f(strings);
}

Test(hw4_split_at, split_at_09, .timeout=2)
{
  str_list *strings = split_at("a&/b&&/c",'&');
  str_list *expected = p2c("a",p2c("/b",p2c("",p2cs("/c"))));
  cr_assert(str_list_same(strings,expected));
  p2f(expected);
  p2f(strings);
}

Test(hw4_explode, explode_00, .timeout=2)
{
  str_list *strings = explode("PQR");
  str_list *expected = p2c("P",p2c("Q",p2c("R",NULL)));
  cr_assert(str_list_same(strings,expected));
  p2f(expected);
  p2f(strings);
}

Test(hw4_explode, explode_01, .timeout=2)
{
  str_list *strings = explode("");
  cr_assert(!strings);
}

Test(hw4_explode, explode_02, .timeout=2)
{
  str_list *strings = explode("abcde");
  str_list *expected = p2c("a",p2c("b",p2c("c",p2c("d",p2cs("e")))));
  cr_assert(str_list_same(strings,expected));
  p2f(expected);
  p2f(strings);
}
