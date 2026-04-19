#include <criterion/criterion.h>
#include <stdio.h>
#include "hw2.h"

// ======== tests

Test(hw2_count_color, count_color00, .timeout=2)
{
  rgb colors[] = {0X000000, 0XF00000, 0XF00000};
  cr_assert(count_color(0XF00000, colors, 3)==2);
}

Test(hw2_count_color, count_color01, .timeout=2)
{
  rgb colors[] = {0X000000, 0XFFFFFF, 0XFF0000, 0X00FF00, 0X0000FF};
  cr_assert(count_color(0XFFFF00, colors, 5)==0);
}

Test(hw2_count_color, count_color02, .timeout=2)
{
  rgb colors[] = {0X000000, 0XFFFFFF, 0XFF0000, 0X00FF00, 0X0000FF};
  cr_assert(count_color(0XFF0000, colors, 5)==1);
}

Test(hw2_count_color, count_color03, .timeout=2)
{
  rgb colors[] = {0X000000, 0XFFFFFF, 0XFF0000, 0X00FF00, 0X0000FF};
  cr_assert(count_color(0X0000FF, colors, 5)==1);
}

Test(hw2_count_color, count_color04, .timeout=2)
{
  rgb colors[] = {0X000000, 0XFFFFFF, 0XFF0000, 0X00FF00, 0X0000FF};
  cr_assert(count_color(0XFF0000, colors, 5)==1);
}

Test(hw2_count_color, count_color05, .timeout=2)
{
  rgb colors[] = {0X000000, 0XFFFFFF, 0XFF0000, 0XFFFFFF, 0X0000FF};
  cr_assert(count_color(0XFFFFFF, colors, 5)==2);
}

Test(hw2_count_color, count_color06, .timeout=2)
{
  rgb colors[] = {0X000000, 0XFFFFFF, 0X000000, 0X00FF00, 0X000000};
  cr_assert(count_color(0X000000, colors, 5)==3);
}

Test(hw2_count_color, count_color07, .timeout=2)
{
  rgb colors[] = {0XFF00FF, 0XFF00FF, 0XFF00FF, 0X00FF00, 0XFF00FF};
  cr_assert(count_color(0XFF00FF, colors, 5)==4);
}

Test(hw2_count_color, count_color08, .timeout=2)
{
  rgb colors[] = {0XFF00FF, 0XFF00FF, 0XFF00FF, 0XFF00FF, 0XFF00FF};
  cr_assert(count_color(0XFF00FF, colors, 5)==5);
}


Test(hw2_negate_colors, negate_colors00, .timeout=2)
{
  rgb colors[]  = {0XFF00FF, 0X00FF00};
  rgb negated[] = {0X00FF00, 0XFF00FF};
  negate_colors(colors,2);
  cr_assert(colors[0]==negated[0] && colors[1]==negated[1]);      
}

Test(hw2_negate_colors, negate_colors01, .timeout=2)
{
  rgb colors[]  = {0X732AB4};
  rgb negated[] = {0X8CD54B};
  negate_colors(colors,1);
  cr_assert(colors[0]==negated[0]);
}

Test(hw2_negate_colors, negate_colors02, .timeout=2)
{
  rgb colors[]  = {0XC64B20, 0XA913E4, 0X17645F};
  rgb negated[] = {0X39B4DF, 0X56EC1B, 0XE89BA0};
  negate_colors(colors,3);
  cr_assert(colors[0]==negated[0] && colors[1]==negated[1] &&
            colors[2]==negated[2]);
}

Test(hw2_negate_colors, negate_colors03, .timeout=2)
{
  rgb colors[]  = {0X7910AE, 0X927D19, 0X07229D, 0XFEA0D6};
  rgb negated[] = {0X86EF51, 0X6D82E6, 0XF8DD62, 0X015F29};
  negate_colors(colors,4);
  cr_assert(colors[0]==negated[0] && colors[1]==negated[1] &&
            colors[2]==negated[2] && colors[3]==negated[3]);
}


Test(hw2_stretch, stretch00, .timeout=2)
{
  rgb colors[] = {0, 0XF0F0F0};
  rgb *s = stretch(colors, 2);
  cr_assert(s[0]==0 && s[1]==0 && s[2]==0XF0F0F0 && s[3]==0XF0F0F0);
  free(s);
}

Test(hw2_stretch, stretch01, .timeout=2)
{
  rgb colors[] = {0xA713D1};
  rgb *s = stretch(colors, 1);
  cr_assert(s[0]==0xA713D1 && s[1]==0xA713D1);
  free(s);
}

Test(hw2_stretch, stretch02, .timeout=2)
{
  rgb colors[] = {0X961A44, 0X213384, 0XAA0DFE};
  rgb *s = stretch(colors, 3);
  cr_assert(s[0]==0X961A44 && s[1]==0X961A44 && s[2]==0X213384 &&
            s[3]==0X213384 && s[4]==0XAA0DFE && s[5]==0XAA0DFE);
  free(s);
}

Test(hw2_stretch, stretch03, .timeout=2)
{
  rgb colors[] = {0X961A44, 0X213384, 0XAA0DFE, 0X94F7E6};
  rgb *s = stretch(colors, 4);
  cr_assert(s[0]==0X961A44 && s[1]==0X961A44 && s[2]==0X213384 &&
            s[3]==0X213384 && s[4]==0XAA0DFE && s[5]==0XAA0DFE &&
            s[6]==0X94F7E6 && s[7]==0X94F7E6);
  free(s);
}

Test(hw2_stretch, stretch04, .timeout=2)
{
  rgb colors[] = {0X961A44, 0X213384, 0XAA0DFE, 0X94F7E6, 0X9E6F2C};
  rgb *s = stretch(colors, 5);
  cr_assert(s[0]==0X961A44 && s[1]==0X961A44 && s[2]==0X213384 &&
            s[3]==0X213384 && s[4]==0XAA0DFE && s[5]==0XAA0DFE &&
            s[6]==0X94F7E6 && s[7]==0X94F7E6 && s[8]==0X9E6F2C &&
            s[9]==0X9E6F2C);
  free(s);
}


Test(hw2_min_blue, min_blue00, .timeout=2)
{
  rgb colors[] = {0XFFEEBB, 0XFFDDAA};
  cr_assert(min_blue(colors,2)==0XAA);
}

Test(hw2_min_blue, min_blue01, .timeout=2)
{
  rgb colors[] = {0XAB00C9, 0X610024, 0X7A00B4, 0X23001A, 0X7B0023};
  cr_assert(min_blue(colors,5)==0X1A);
}

Test(hw2_min_blue, min_blue02, .timeout=2)
{
  rgb colors[] = {0XABFF19, 0X61FF24, 0X7AFFB4, 0X23FF1A, 0X7BFF23};
  cr_assert(min_blue(colors,5)==0X19);
}

Test(hw2_min_blue, min_blue03, .timeout=2)
{
  rgb colors[] = {0XAB00C9, 0X61FF14, 0X7A00B4, 0X23001A, 0X7B00F3};
  cr_assert(min_blue(colors,5)==0X14);
}

Test(hw2_min_blue, min_blue04, .timeout=2)
{
  rgb colors[] = {0XAB6E11, 0X611224, 0X7A86B4, 0X23871A, 0X7B2223};
  cr_assert(min_blue(colors,5)==0X11);
}

Test(hw2_min_blue, min_blue05, .timeout=2)
{
  rgb colors[] = {0XAB00C9, 0X610724, 0X7A1910, 0X230D1A, 0X7B1A23};
  cr_assert(min_blue(colors,5)==0X10);
}

Test(hw2_min_blue, min_blue06, .timeout=2)
{
  rgb colors[] = {0XAB7323, 0X619723, 0X7A2223, 0X239723, 0X7B8F23};
  cr_assert(min_blue(colors,5)==0X23);
}

Test(hw2_min_blue, min_blue07, .timeout=2)
{
  rgb colors[] = {0XAB00C9, 0XAB1824, 0X7A00B4, 0X23001A, 0X7B001A};
  cr_assert(min_blue(colors,5)==0X1A);
}


Test(hw2_connect_rgb_arrays, connect_rgb_arrays00, .timeout=2)
{
  rgb colors1[] = {0, 0X0000BB};
  rgb colors2[] = {0XFF0000};
  rgb *c = connect_rgb_arrays(colors1,2,colors2,1);
  cr_assert(c[0]==0 &&
	    c[1]==0X0000BB &&
	    c[2]==0XFF0000);
  free(c);
}

Test(hw2_connect_rgb_arrays, connect_rgb_arrays01, .timeout=2)
{
  rgb colors1[] = {0XA9B623};
  rgb colors2[] = {0X148296};
  rgb *c = connect_rgb_arrays(colors1,1,colors2,1);
  cr_assert(c[0]==0XA9B623 &&
            c[1]==0X148296);
  free(c);
}

Test(hw2_connect_rgb_arrays, connect_rgb_arrays02, .timeout=2)
{
  rgb colors1[] = {0X912C34};
  rgb colors2[] = {0XA601CB, 0X22341A};
  rgb *c = connect_rgb_arrays(colors1,1,colors2,2);
  cr_assert(c[0]==0X912C34 &&
      c[1]==0XA601CB &&
      c[2]==0X22341A);
  free(c);
}

Test(hw2_connect_rgb_arrays, connect_rgb_arrays03, .timeout=2)
{
  rgb colors1[] = {0X994328, 0X221827, 0X16A409};
  rgb colors2[] = {0XA49BCD, 0X1664A8, 0X9193AB, 0X774A8B};
  rgb *c = connect_rgb_arrays(colors1,3,colors2,4);
  cr_assert(c[0]==0X994328 &&
            c[1]==0X221827 &&
            c[2]==0X16A409 &&
            c[3]==0XA49BCD &&
            c[4]==0X1664A8 &&
            c[5]==0X9193AB &&
            c[6]==0X774A8B);
  free(c);
}

Test(hw2_connect_rgb_arrays, connect_rgb_arrays04, .timeout=2)
{
  rgb colors1[] = {0X994328, 0X221827, 0X16A409, 0XA49BCD};
  rgb colors2[] = {0X1664A8, 0X9193AB, 0X774A8B};
  rgb *c = connect_rgb_arrays(colors1,4,colors2,3);
  cr_assert(c[0]==0X994328 &&
            c[1]==0X221827 &&
            c[2]==0X16A409 &&
            c[3]==0XA49BCD &&
            c[4]==0X1664A8 &&
            c[5]==0X9193AB &&
            c[6]==0X774A8B);
  free(c);
}

Test(hw2_connect_rgb_arrays, connect_rgb_arrays05, .timeout=2)
{
  rgb colors1[] = {0X994328, 0X221827, 0X16A409, 0XA49BCD};
  rgb colors2[] = {0X1664A8, 0X9193AB, 0X774A8B, 0X97338E};
  rgb *c = connect_rgb_arrays(colors1,4,colors2,4);
  cr_assert(c[0]==0X994328 &&
            c[1]==0X221827 &&
            c[2]==0X16A409 &&
            c[3]==0XA49BCD &&
            c[4]==0X1664A8 &&
            c[5]==0X9193AB &&
            c[6]==0X774A8B &&
            c[7]==0X97338E);
  free(c);
}


Test(hw2_sift_up, sift_up00, .timeout=2)
{
  timestamp dates[] = {20250401000000, 20250101000000, 20250201000000};
  sift_up(dates, 1);
  cr_assert(dates[0]==20250101000000 &&
	    dates[1]==20250401000000 &&
	    dates[2]==20250201000000);
}

Test(hw2_sift_up, sift_up01, .timeout=2)
{
  timestamp dates[] = {20250201000000, 20250301000000, 20250201000000};
  sift_up(dates, 1);
  cr_assert(dates[0]==20250201000000 &&
      dates[1]==20250301000000 &&
      dates[2]==20250201000000);
}

Test(hw2_sift_up, sift_up02, .timeout=2)
{
  timestamp dates[] = {20250201000000, 20250203000000, 20250301000000,
    20250204000000, 20250205000000, 20250302000000, 20250303000000,
    20250202000000};
  sift_up(dates, 7);
  cr_assert(dates[0]==20250201000000 &&
            dates[1]==20250202000000 &&
            dates[2]==20250301000000 &&
            dates[3]==20250203000000 &&
            dates[4]==20250205000000 &&
            dates[5]==20250302000000 &&
            dates[6]==20250303000000 &&
            dates[7]==20250204000000);
}

Test(hw2_sift_up, sift_up03, .timeout=2)
{
  timestamp dates[] = {20250202000000, 20250203000000, 20250301000000,
    20250204000000, 20250205000000, 20250302000000, 20250303000000,
    20250201000000};
  sift_up(dates, 7);
  cr_assert(dates[0]==20250201000000 &&
            dates[1]==20250202000000 &&
            dates[2]==20250301000000 &&
            dates[3]==20250203000000 &&
            dates[4]==20250205000000 &&
            dates[5]==20250302000000 &&
            dates[6]==20250303000000 &&
            dates[7]==20250204000000);
}


Test(hw2_sift_down, sift_down00, .timeout=2)
{
  timestamp dates[] = {20250201000000, 20250202000000, 20250301000000,
    20250203000000, 20250204000000, 20250302000000, 20250303000000,
    20250205000000};
  sift_down(dates, 0, 8);
  cr_assert(dates[0]==20250201000000 &&
            dates[1]==20250202000000 &&
            dates[2]==20250301000000 &&
            dates[3]==20250203000000 &&
            dates[4]==20250204000000 &&
            dates[5]==20250302000000 &&
            dates[6]==20250303000000 &&
            dates[7]==20250205000000);
}

Test(hw2_sift_down, sift_down01, .timeout=2)
{
  timestamp dates[] = {20250202000000, 20250201000000, 20250301000000,
    20250203000000, 20250204000000, 20250302000000, 20250303000000,
    20250205000000};
  sift_down(dates, 0, 8);
  cr_assert(dates[0]==20250201000000 &&
            dates[1]==20250202000000 &&
            dates[2]==20250301000000 &&
            dates[3]==20250203000000 &&
            dates[4]==20250204000000 &&
            dates[5]==20250302000000 &&
            dates[6]==20250303000000 &&
            dates[7]==20250205000000);
}

Test(hw2_sift_down, sift_down02, .timeout=2)
{
  timestamp dates[] = {20250202000000, 20250301000000, 20250201000000,
    20250302000000, 20250303000000, 20250203000000, 20250204000000,
    20250305000000};
  sift_down(dates, 0, 8);
  cr_assert(dates[0]==20250201000000 &&
            dates[1]==20250301000000 &&
            dates[2]==20250202000000 &&
            dates[3]==20250302000000 &&
            dates[4]==20250303000000 &&
            dates[5]==20250203000000 &&
            dates[6]==20250204000000 &&
            dates[7]==20250305000000);
}

Test(hw2_sift_down, sift_down03, .timeout=2)
{
  timestamp dates[] = {20250203000000, 20250201000000, 20250301000000,
    20250202000000, 20250204000000, 20250302000000, 20250303000000,
    20250205000000};
  sift_down(dates, 0, 8);
  cr_assert(dates[0]==20250201000000 &&
            dates[1]==20250202000000 &&
            dates[2]==20250301000000 &&
            dates[3]==20250203000000 &&
            dates[4]==20250204000000 &&
            dates[5]==20250302000000 &&
            dates[6]==20250303000000 &&
            dates[7]==20250205000000);
}

Test(hw2_sift_down, sift_down04, .timeout=2)
{
  timestamp dates[] = {20250205000000, 20250201000000, 20250301000000,
    20250202000000, 20250204000000, 20250302000000, 20250303000000,
    20250203000000};
  sift_down(dates, 0, 8);
  cr_assert(dates[0]==20250201000000 &&
            dates[1]==20250202000000 &&
            dates[2]==20250301000000 &&
            dates[3]==20250203000000 &&
            dates[4]==20250204000000 &&
            dates[5]==20250302000000 &&
            dates[6]==20250303000000 &&
            dates[7]==20250205000000);
}

Test(hw2_sift_down, sift_down05, .timeout=2)
{
  timestamp dates[] = {20250201000000, 20250202000000, 20250301000000,
    20250203000000, 20250204000000, 20250302000000, 20250303000000,
    20250205000000};
  sift_down(dates, 1, 8);
  cr_assert(dates[0]==20250201000000 &&
            dates[1]==20250202000000 &&
            dates[2]==20250301000000 &&
            dates[3]==20250203000000 &&
            dates[4]==20250204000000 &&
            dates[5]==20250302000000 &&
            dates[6]==20250303000000 &&
            dates[7]==20250205000000);
}

Test(hw2_sift_down, sift_down06, .timeout=2)
{
  timestamp dates[] = {20250201000000, 20250203000000, 20250301000000,
    20250202000000, 20250204000000, 20250302000000, 20250303000000,
    20250205000000};
  sift_down(dates, 1, 8);
  cr_assert(dates[0]==20250201000000 &&
            dates[1]==20250202000000 &&
            dates[2]==20250301000000 &&
            dates[3]==20250203000000 &&
            dates[4]==20250204000000 &&
            dates[5]==20250302000000 &&
            dates[6]==20250303000000 &&
            dates[7]==20250205000000);
}

Test(hw2_sift_down, sift_down07, .timeout=2)
{
  timestamp dates[] = {20250201000000, 20250203000000, 20250301000000,
    20250204000000, 20250202000000, 20250302000000, 20250303000000,
    20250205000000};
  sift_down(dates, 1, 8);
  cr_assert(dates[0]==20250201000000 &&
            dates[1]==20250202000000 &&
            dates[2]==20250301000000 &&
            dates[3]==20250204000000 &&
            dates[4]==20250203000000 &&
            dates[5]==20250302000000 &&
            dates[6]==20250303000000 &&
            dates[7]==20250205000000);
}

Test(hw2_sift_down, sift_down08, .timeout=2)
{
  timestamp dates[] = {20250201000000, 20250206000000, 20250301000000,
    20250203000000, 20250204000000, 20250302000000, 20250303000000,
    20250205000000};
  sift_down(dates, 1, 8);
  cr_assert(dates[0]==20250201000000 &&
            dates[1]==20250203000000 &&
            dates[2]==20250301000000 &&
            dates[3]==20250205000000 &&
            dates[4]==20250204000000 &&
            dates[5]==20250302000000 &&
            dates[6]==20250303000000 &&
            dates[7]==20250206000000);
}

Test(hw2_sift_down, sift_down09, .timeout=2)
{
  timestamp dates[] = {20250201000000, 20250206000000, 20250301000000,
    20250203000000, 20250204000000, 20250302000000, 20250303000000,
    20250205000000, 20250210000000, 20250211000000, 20250212000000,
    20250310000000, 20250311000000, 20250312000000, 20250313000000,
    20250220000000};
  sift_down(dates, 1, 16);
  cr_assert(dates[0]==20250201000000 &&
            dates[1]==20250203000000 &&
            dates[2]==20250301000000 &&
            dates[3]==20250205000000 &&
            dates[4]==20250204000000 &&
            dates[5]==20250302000000 &&
            dates[6]==20250303000000 &&
            dates[7]==20250206000000 &&
            dates[8]==20250210000000 &&
            dates[9]==20250211000000 &&
            dates[10]==20250212000000 &&
            dates[11]==20250310000000 &&
            dates[12]==20250311000000 &&
            dates[13]==20250312000000 &&
            dates[14]==20250313000000 &&
            dates[15]==20250220000000);
}


Test(hw2_heapsort_dates, heapsort_dates00, .timeout=2)
{
  timestamp dates[] = {20200101000000, 20180101000000, 20140101000000};
  heapsort_dates(dates,3);
  cr_assert(dates[0]==20140101000000 &&
	    dates[1]==20180101000000 &&
	    dates[2]==20200101000000);
}

Test(hw2_heapsort_dates, heapsort_dates01, .timeout=2)
{
  timestamp dates[] = {20240314000000};
  heapsort_dates(dates,1);
  cr_assert(dates[0]==20240314000000);
}

Test(hw2_heapsort_dates, heapsort_dates02, .timeout=2)
{
  timestamp dates[] = {20240314000000, 20230404000000};
  heapsort_dates(dates,2);
  cr_assert(dates[0]==20230404000000 &&
            dates[1]==20240314000000);
}

Test(hw2_heapsort_dates, heapsort_dates03, .timeout=2)
{
  timestamp dates[] = {20250506123456, 20211231081005, 20230706001500,
                      20221008231024};
  heapsort_dates(dates,4);
  cr_assert(dates[0]==20211231081005 &&
            dates[1]==20221008231024 &&
            dates[2]==20230706001500 &&
            dates[3]==20250506123456);
}

Test(hw2_heapsort_dates, heapsort_dates04, .timeout=2)
{
  timestamp dates[] = {20210203040506, 20220304050607, 20230405060708,
                      20240506070809, 20250607080910, 20260708091011,
                      20270809101112, 20280910111213};
  heapsort_dates(dates,8);
  cr_assert(dates[0]==20210203040506 &&
            dates[1]==20220304050607 &&
            dates[2]==20230405060708 &&
            dates[3]==20240506070809 &&
            dates[4]==20250607080910 &&
            dates[5]==20260708091011 &&
            dates[6]==20270809101112 &&
            dates[7]==20280910111213);
}

Test(hw2_heapsort_dates, heapsort_dates05, .timeout=2)
{
  timestamp dates[] = {20280910111213, 20270809101112, 20260708091011,
    20250607080910, 20240506070809, 20230405060708,
    20220304050607, 20210203040506};
  heapsort_dates(dates,8);
  cr_assert(dates[0]==20210203040506 &&
            dates[1]==20220304050607 &&
            dates[2]==20230405060708 &&
            dates[3]==20240506070809 &&
            dates[4]==20250607080910 &&
            dates[5]==20260708091011 &&
            dates[6]==20270809101112 &&
            dates[7]==20280910111213);
}

Test(hw2_heapsort_dates, heapsort_dates06, .timeout=2)
{
  timestamp dates[] = {20220304050607, 20260708091011, 20280910111213,
                      20230405060708, 20240506070809, 20250607080910,
                      20210203040506, 20270809101112};
  heapsort_dates(dates,8);
  cr_assert(dates[0]==20210203040506 &&
            dates[1]==20220304050607 &&
            dates[2]==20230405060708 &&
            dates[3]==20240506070809 &&
            dates[4]==20250607080910 &&
            dates[5]==20260708091011 &&
            dates[6]==20270809101112 &&
            dates[7]==20280910111213);
}

Test(hw2_heapsort_dates, heapsort_dates07, .timeout=2)
{
  timestamp dates[] = {20220304050607, 20260708091011, 20280910111213,
                      20230405060708, 20240506070809, 20230405060708,
                      20210203040506, 20230405060708};
  heapsort_dates(dates,8);
  cr_assert(dates[0]==20210203040506 &&
            dates[1]==20220304050607 &&
            dates[2]==20230405060708 &&
            dates[3]==20230405060708 &&
            dates[4]==20230405060708 &&
            dates[5]==20240506070809 &&
            dates[6]==20260708091011 &&
            dates[7]==20280910111213);
}

Test(hw2_heapsort_dates, heapsort_dates08, .timeout=2)
{
  timestamp dates[] = {20220304050607, 20220304050607, 20220304050607,
                      20220304050607, 20220304050607, 20220304050607,
                      20220304050607, 20220304050607};
  heapsort_dates(dates,8);
  cr_assert(dates[0]==20220304050607 &&
            dates[1]==20220304050607 &&
            dates[2]==20220304050607 &&
            dates[3]==20220304050607 &&
            dates[4]==20220304050607 &&
            dates[5]==20220304050607 &&
            dates[6]==20220304050607 &&
            dates[7]==20220304050607);
}


Test(hw2_distinct_dates, distinct_dates00, .timeout=2)
{
  timestamp dates[] = {20240101000000, 20240101000000};
  int n;
  timestamp *ds = distinct_dates(dates,2,&n);
  cr_assert(n==1 && ds[0]==20240101000000);
  free(ds);
}

Test(hw2_distinct_dates, distinct_dates01, .timeout=2)
{
  timestamp dates[] = {20160812231907};
  int n;
  timestamp *ds = distinct_dates(dates,1,&n);
  cr_assert(n==1 && ds[0]==20160812231907);
  free(ds);
}

Test(hw2_distinct_dates, distinct_dates02, .timeout=2)
{
  timestamp dates[] = {20180403221417, 20120618081203};
  int n;
  timestamp *ds = distinct_dates(dates,2,&n);
  cr_assert(n==2 && ds[0]==20120618081203 && ds[1]==20180403221417);
  free(ds);
}

Test(hw2_distinct_dates, distinct_dates03, .timeout=2)
{
  timestamp dates[] = {20180403221417, 20120618081203, 20201201031824};
  int n;
  timestamp *ds = distinct_dates(dates,3,&n);
  cr_assert(n==3 && ds[0]==20120618081203 && ds[1]==20180403221417 &&
            dates[2]==20201201031824);
  free(ds);
}

Test(hw2_distinct_dates, distinct_dates04, .timeout=2)
{
  timestamp dates[] = {20120618081203, 20120618081203, 20201201031824};
  int n;
  timestamp *ds = distinct_dates(dates,3,&n);
  cr_assert(n==2 && ds[0]==20120618081203 && ds[1]==20201201031824);
  free(ds);
}

Test(hw2_distinct_dates, distinct_dates05, .timeout=2)
{
  timestamp dates[] = {20180403221417, 20120618081203, 20180403221417};
  int n;
  timestamp *ds = distinct_dates(dates,3,&n);
  cr_assert(n==2 && ds[0]==20120618081203 && ds[1]==20180403221417);
            
}

Test(hw2_distinct_dates, distinct_dates06, .timeout=2)
{
  timestamp dates[] = {20180403221417, 20120618081203, 20120618081203};
  int n;
  timestamp *ds = distinct_dates(dates,3,&n);
  cr_assert(n==2 && ds[0]==20120618081203 && ds[1]==20180403221417);
  free(ds);
}

Test(hw2_distinct_dates, distinct_dates07, .timeout=2)
{
  timestamp dates[] = {20180403221417, 20180403221417, 20180403221417};
  int n;
  timestamp *ds = distinct_dates(dates,3,&n);
  cr_assert(n==1 && ds[0]==20180403221417);
  free(ds);
}

// helper function for these tests
int grading_days_match(timestamp* actual, timestamp* expect, unsigned int len) {
  unsigned int i;
  for (i = 0; i < len; i++) {
    if (actual[i] / 1000000 != expect[i]) {
      return 0;
    }
    if ((actual[i] % 100 > 59) ||
        ((actual[i] / 100) % 100 > 59) ||
        ((actual[i] / 10000) % 100 > 23)) {
      return 0;
    }
  }
  return 1;
}

Test(hw2_weekdays, weekdays00, .timeout=2)
{
  int n;
  timestamp *w = weekdays(20250416123456, 20250423123456, &n);
  timestamp expect[] = {20250416, 20250417, 20250418, 20250421, 20250422,
                      20250423};
  cr_assert(n==6 && grading_days_match(w, expect, 6));
  free(w);
}

Test(hw2_weekdays, weekdays01, .timeout=2)
{
  int n;
  timestamp *w = weekdays(20230517123456, 20230513123456, &n);
  cr_assert(n==0);
  (void)w; // nonsense operation to silence compiler warning
}

Test(hw2_weekdays, weekdays02, .timeout=2)
{
  int n;
  timestamp *w = weekdays(20230520123456, 20230521123456, &n);
  cr_assert(n==0);
  (void)w; // nonsense operation to silence compiler warning
}

Test(hw2_weekdays, weekdays03, .timeout=2)
{
  int n;
  timestamp *w = weekdays(20230521123456, 20230527123456, &n);
  timestamp expect[] = {20230522, 20230523, 20230524, 20230525, 20230526};
  cr_assert(n==5 && grading_days_match(w, expect, 5));
  free(w);
}

Test(hw2_weekdays, weekdays04, .timeout=2)
{
  int n;
  timestamp *w = weekdays(20230520123456, 20230528123456, &n);
  timestamp expect[] = {20230522, 20230523, 20230524, 20230525, 20230526};
  cr_assert(n==5 && grading_days_match(w, expect, 5));
  free(w);
}

Test(hw2_weekdays, weekdays05, .timeout=2)
{
  int n;
  timestamp *w = weekdays(20230522123456, 20230526123456, &n);
  timestamp expect[] = {20230522, 20230523, 20230524, 20230525, 20230526};
  cr_assert(n==5 && grading_days_match(w, expect, 5));
  free(w);
}

Test(hw2_weekdays, weekdays06, .timeout=2)
{
  int n;
  timestamp *w = weekdays(20230523123456, 20230525123456, &n);
  timestamp expect[] = {20230523, 20230524, 20230525};
  cr_assert(n==3 && grading_days_match(w, expect, 3));
  free(w);
}

Test(hw2_weekdays, weekdays07, .timeout=2)
{
  int n;
  timestamp *w = weekdays(20180201234507, 20180228234507, &n);
  timestamp expect[] = {20180201, 20180202, 20180205, 20180206, 20180207,
                      20180208, 20180209, 20180212, 20180213, 20180214,
                      20180215, 20180216, 20180219, 20180220, 20180221,
                      20180222, 20180223, 20180226, 20180227, 20180228};
  cr_assert(n==20 && grading_days_match(w, expect, 20));
  free(w);
}


Test(hw2_mondays, mondays00, .timeout=2)
{
  int n;
  timestamp *w = mondays(20250416123456, 20250423123456, &n);
  timestamp expect[] = {20250421};
  cr_assert(n==1 && grading_days_match(w, expect, 1));
  free(w);
}

Test(hw2_mondays, mondays01, .timeout=2)
{
  int n;
  timestamp *w = mondays(20230517123456, 20230518123456, &n);
  cr_assert(n==0);
  (void)w; // nonsense operation to silence compiler warning
}

Test(hw2_mondays, mondays02, .timeout=2)
{
  int n;
  timestamp *w = mondays(20230501123456, 20230531123456, &n);
  timestamp expect[] = {20230501,20230508,20230515,20230522,20230529};
  cr_assert(n==5 && grading_days_match(w, expect, 5));
  free(w);
}

Test(hw2_mondays, mondays03, .timeout=2)
{
  int n;
  timestamp *w = mondays(20230522123456, 20230522123456, &n);
  timestamp expect[] = {20230522};
  cr_assert(n==1 && grading_days_match(w, expect, 1));
  free(w);
}

Test(hw2_mondays, mondays04, .timeout=2)
{
  int n;
  timestamp *w = mondays(20180201234507, 20180228234507, &n);
  timestamp expect[] = {20180205,20180212,20180219,20180226};
  cr_assert(n==4 && grading_days_match(w, expect, 4));
  free(w);
}

Test(hw2_primes, primes00, .timeout=2)
{
  int n;
  unsigned int a[] = {1,2,3,4,5,6,7,8,9,99};
  unsigned int *np = primes(a,10,&n);
  cr_assert(n==4 &&
	    np[0]==2 &&
	    np[1]==3 &&
	    np[2]==5 &&
	    np[3]==7);
    free(np);
}

Test(hw2_primes, primes01, .timeout=2)
{
  int n;
  unsigned int a[] = {3};
  unsigned int *np = primes(a,1,&n);
  cr_assert(n==1 &&
	    np[0]==3);
  free(np);
}

Test(hw2_primes, primes02, .timeout=2)
{
  int n;
  unsigned int a[] = {24};
  unsigned int *np = primes(a,1,&n);
  cr_assert(n==0);
  (void)np; // nonsense operation to silence compiler warning
}

Test(hw2_primes, primes03, .timeout=2)
{
  int n;
  unsigned int a[] = {2,3,5,7,11,13,17,19,23,29};
  unsigned int *np = primes(a,10,&n);
  cr_assert(n==10 &&
	    np[0]==2 &&
            np[1]==3 &&
	    np[2]==5 &&
	    np[3]==7 &&
	    np[4]==11 &&
	    np[5]==13 &&
	    np[6]==17 &&
	    np[7]==19 &&
	    np[8]==23 &&
	    np[9]==29);
  free(np);
}

Test(hw2_primes, primes04, .timeout=2)
{
  int n;
  unsigned int a[] = {4,9,15,21,25,28};
  unsigned int *np = primes(a,6,&n);
  cr_assert(n==0);
  (void)np; // nonsense operation to silence compiler warning
}

