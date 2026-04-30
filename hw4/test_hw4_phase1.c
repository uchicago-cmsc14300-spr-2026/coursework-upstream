#include <criterion/criterion.h>
#include <stdio.h>
#include <string.h>
#include "hw4.h"

// ======== tests

Test(hw4_cons, cons_00, .timeout=2)
{
  str_list *strings = cons("XYZ",NULL);
  cr_assert(strings);
  str_list_free(strings);
}

Test(hw4_str_list_free, str_list_free_00, .timeout=2)
{
  str_list *strings = cons("XYZ",NULL);
  str_list_free(strings);
  cr_assert(1==1);
}
  
Test(hw4_str_list_len, str_list_len_00, .timeout=2)
{
  str_list *strings = cons("XYZ",NULL);
  cr_assert(str_list_len(strings)==1);
  str_list_free(strings);
}

Test(hw4_str_arr_to_list, str_arr_to_list_00, .timeout=2)
{
  char *arr[] = {"XYZ"};
  str_list *strings = str_arr_to_list(arr,1);
  cr_assert(!strcmp(strings->first,"XYZ") && !strings->rest);
  str_list_free(strings);
}

Test(hw4_str_list_to_arr, str_list_to_arr_00, .timeout=2)
{
  unsigned int n;
  str_list *strings = cons("XYZ",NULL);
  char **arr = str_list_to_arr(strings,&n);
  cr_assert(!strcmp(arr[0],"XYZ") && n==1);
  str_list_free(strings);
}

Test(hw4_str_list_count_vowels, str_list_count_vowels_00, .timeout=2)
{
  str_list *strings = cons("ABCDE",NULL);
  cr_assert(str_list_count_vowels(strings)==2);
  str_list_free(strings);
}

Test(hw4_str_list_remove_vowels, str_list_remove_vowels_00, .timeout=2)
{
  str_list *listA = cons("ABC",NULL);
  str_list *listB = str_list_remove_vowels(listA);
  cr_assert(!strcmp(listB->first,"BC") && listB->rest==NULL);
  str_list_free(listB);
  str_list_free(listA);
}

Test(hw4_split_at, split_at_00, .timeout=2)
{
  str_list *strings = split_at("a,bb,c",',');
  cr_assert(str_list_len(strings)==3 &&
	    !strcmp(strings->first,"a") &&
	    !strcmp(strings->rest->first,"bb") &&
	    !strcmp(strings->rest->rest->first,"c"));
  str_list_free(strings);
}

Test(hw4_explode, explode_00, .timeout=2)
{
  str_list *strings = explode("PQR");
  cr_assert(str_list_len(strings)==3 &&
	    !strcmp(strings->first,"P") &&
	    !strcmp(strings->rest->first,"Q") &&
	    !strcmp(strings->rest->rest->first,"R"));
  str_list_free(strings);  
}
