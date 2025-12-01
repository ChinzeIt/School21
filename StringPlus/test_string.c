#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

START_TEST(s21_strlen_test) {
  char *test1 = "Hello scho\0ol 21!";
  ck_assert_int_eq(strlen(test1), s21_strlen(test1));
  char *test2 = "123456789";
  ck_assert_int_eq(strlen(test2), s21_strlen(test2));
  char *test3 = " ";
  ck_assert_int_eq(strlen(test3), s21_strlen(test3));
  char *test4 = "";
  ck_assert_int_eq(strlen(test4), s21_strlen(test4));
  char *test5 = "hel\0lo";
  ck_assert_int_eq(strlen(test5), s21_strlen(test5));
  char *test6 = "h";
  ck_assert_int_eq(strlen(test6), s21_strlen(test6));
  char *test7 = "Hello\nWorld";
  ck_assert_int_eq(strlen(test7), s21_strlen(test7));
  char *test8 = "\0";
  ck_assert_int_eq(strlen(test8), s21_strlen(test8));
}
END_TEST

START_TEST(s21_strchr_test) {
  char *test1 = "Hello school 21!";
  int n1 = 'l';
  ck_assert_ptr_eq(strchr(test1, n1), s21_strchr(test1, n1));
  char *test2 = "";
  int n2 = 'b';
  ck_assert_ptr_eq(strchr(test2, n2), s21_strchr(test2, n2));
  char *test3 = "Hello school 21!";
  int n3 = 'v';
  ck_assert_ptr_eq(strchr(test3, n3), s21_strchr(test1, n3));
  char *test4 = "Hello sc\0hool 21!";
  int n4 = '\0';
  ck_assert_ptr_eq(strchr(test4, n4), s21_strchr(test4, n4));
  char *test5 = "   ";
  int n5 = ' ';
  ck_assert_ptr_eq(strchr(test5, n5), s21_strchr(test5, n5));
  char *test6 = "12458@#74^";
  int n6 = '^';
  ck_assert_ptr_eq(strchr(test6, n6), s21_strchr(test6, n6));
  char *test7 = "hello school 21!";
  int n7 = 'H';
  ck_assert_ptr_eq(strchr(test7, n7), s21_strchr(test7, n7));
}
END_TEST

START_TEST(s21_strrchr_test) {
  char *test1 = "Hello school 21!";
  int n1 = 'l';
  ck_assert_ptr_eq(strrchr(test1, n1), s21_strrchr(test1, n1));
  char *test2 = "";
  int n2 = 'b';
  ck_assert_ptr_eq(strrchr(test2, n2), s21_strrchr(test2, n2));
  char *test3 = "Hello school 21!";
  int n3 = 'v';
  ck_assert_ptr_eq(strrchr(test3, n3), s21_strrchr(test1, n3));
  char *test4 = "Hello sc\0hool 21!";
  int n4 = '\0';
  ck_assert_ptr_eq(strrchr(test4, n4), s21_strrchr(test4, n4));
  char *test5 = "   ";
  int n5 = ' ';
  ck_assert_ptr_eq(strrchr(test5, n5), s21_strrchr(test5, n5));
  char *test6 = "12458@#74^";
  int n6 = '^';
  ck_assert_ptr_eq(strrchr(test6, n6), s21_strrchr(test6, n6));
  char *test7 = "Hello school 21!";
  int n7 = 'H';
  ck_assert_ptr_eq(strrchr(test7, n7), s21_strrchr(test7, n7));
  char *test8 = "Hello school 21!";
  int n8 = '!';
  ck_assert_ptr_eq(strrchr(test8, n8), s21_strrchr(test8, n8));
}
END_TEST

START_TEST(s21_strncmp_test) {
  char *test1 = "Hello school 21!";
  char *test11 = "Hello school 21!";
  size_t n1 = 5;
  ck_assert_int_eq(strncmp(test1, test11, n1), s21_strncmp(test1, test11, n1));
  char *test2 = "Hello school 21!";
  char *test22 = "Hello sghool 21!";
  size_t n2 = 16;
  ck_assert_int_eq(strncmp(test2, test22, n2), s21_strncmp(test2, test22, n2));
  char *test3 = "Hello school 21!";
  char *test33 = "Hella school 21!";
  size_t n3 = 16;
  ck_assert_int_eq(strncmp(test3, test33, n3), s21_strncmp(test3, test33, n3));
  char *test4 = "";
  char *test44 = "";
  size_t n4 = 16;
  ck_assert_int_eq(strncmp(test4, test44, n4), s21_strncmp(test4, test44, n4));
  char *test5 = "he";
  char *test55 = "Hello school 21!";
  size_t n5 = 7;
  ck_assert_int_eq(strncmp(test5, test55, n5), s21_strncmp(test5, test55, n5));
  char *test8 = "Hello";
  char *test88 = "Hel";
  size_t n8 = -2;
  ck_assert_int_eq(strncmp(test8, test88, n8), s21_strncmp(test8, test88, n8));
}
END_TEST

START_TEST(s21_strstr_test) {
  char *test1 = "Hello school 21!";
  char *test11 = "lo";
  ck_assert_ptr_eq(strstr(test1, test11), s21_strstr(test1, test11));
  char *test2 = "H";
  char *test22 = "lo";
  ck_assert_ptr_eq(strstr(test2, test22), s21_strstr(test2, test22));
  char *test3 = "Hello school 21!";
  char *test33 = "";
  ck_assert_ptr_eq(strstr(test3, test33), s21_strstr(test3, test33));
  char *test4 = "Hello school 21!";
  char *test44 = "bye";
  ck_assert_ptr_eq(strstr(test4, test44), s21_strstr(test4, test44));
  char *test5 = "";
  char *test55 = "aba";
  ck_assert_ptr_eq(strstr(test5, test55), s21_strstr(test5, test55));
  char *test6 = "Hello";
  char *test66 = "Hello";
  ck_assert_ptr_eq(strstr(test6, test66), s21_strstr(test6, test66));
  char *test7 = "ololo";
  char *test77 = "lo";
  ck_assert_ptr_eq(strstr(test7, test77), s21_strstr(test7, test77));
  char *test8 = "hello school 21!";
  char *test88 = "H";
  ck_assert_ptr_eq(strstr(test8, test88), s21_strstr(test8, test88));
}
END_TEST

START_TEST(s21_strpbrk_test) {
  char *test1 = "Hello school 21!";
  char *test11 = "aot";
  ck_assert_ptr_eq(strpbrk(test1, test11), s21_strpbrk(test1, test11));
  char *test2 = "Hello school 21!";
  char *test22 = "gxp";
  ck_assert_ptr_eq(strpbrk(test2, test22), s21_strpbrk(test2, test22));
  char *test3 = "";
  char *test33 = "gxp";
  ck_assert_ptr_eq(strpbrk(test3, test33), s21_strpbrk(test3, test33));
  char *test4 = "Hello school 21!";
  char *test44 = "";
  ck_assert_ptr_eq(strpbrk(test4, test44), s21_strpbrk(test4, test44));
  char *test5 = "hello";
  char *test55 = "h";
  ck_assert_ptr_eq(strpbrk(test5, test55), s21_strpbrk(test5, test55));
  char *test6 = "ololo";
  char *test66 = "lo";
  ck_assert_ptr_eq(strpbrk(test6, test66), s21_strpbrk(test6, test66));
  char *test7 = "hello";
  char *test77 = "H";
  ck_assert_ptr_eq(strpbrk(test7, test77), s21_strpbrk(test7, test77));
}
END_TEST

START_TEST(s21_strncat_test) {
  char dest1[20] = "Hello ";
  char s21_dest1[20] = "Hello ";
  char *test1 = "school 21";
  size_t n1 = 9;
  ck_assert_str_eq(strncat(dest1, test1, n1),
                   s21_strncat(s21_dest1, test1, n1));
  char dest2[20] = "Hello ";
  char s21_dest2[20] = "Hello ";
  char *test2 = "school 21\0World";
  size_t n2 = 15;
  ck_assert_str_eq(strncat(dest2, test2, n2),
                   s21_strncat(s21_dest2, test2, n2));
  char dest3[20] = "Hello ";
  char s21_dest3[20] = "Hello ";
  char *test3 = "school 21";
  size_t n3 = 6;
  ck_assert_str_eq(strncat(dest3, test3, n3),
                   s21_strncat(s21_dest3, test3, n3));
  char dest4[20] = "Hello ";
  char s21_dest4[20] = "Hello ";
  char *test4 = "";
  size_t n4 = 9;
  ck_assert_str_eq(strncat(dest4, test4, n4),
                   s21_strncat(s21_dest4, test4, n4));
  char dest5[20] = "";
  char s21_dest5[20] = "";
  char *test5 = "";
  size_t n5 = 0;
  ck_assert_str_eq(strncat(dest5, test5, n5),
                   s21_strncat(s21_dest5, test5, n5));
  char dest6[20] = "";
  char s21_dest6[20] = "";
  char *test6 = "HELLO";
  size_t n6 = 5;
  ck_assert_str_eq(strncat(dest6, test6, n6),
                   s21_strncat(s21_dest6, test6, n6));
}
END_TEST

START_TEST(s21_memchr_test) {
  char *test1 = "Hello school 21!";
  int c1 = 's';
  size_t n1 = 16;
  ck_assert_ptr_eq(memchr(test1, c1, n1), s21_memchr(test1, c1, n1));
  char *test2 = "Hello";
  int c2 = '1';
  size_t n2 = 5;
  ck_assert_ptr_eq(memchr(test2, c2, n2), s21_memchr(test2, c2, n2));
  char *test3 = "Hello school 21!";
  int c3 = 'k';
  size_t n3 = 16;
  ck_assert_ptr_eq(memchr(test3, c3, n3), s21_memchr(test3, c3, n3));
  char *test4 = "Hello sc\0hool 21!";
  int c4 = 'h';
  size_t n4 = 16;
  ck_assert_ptr_eq(memchr(test4, c4, n4), s21_memchr(test4, c4, n4));
  char *test5 = "";
  int c5 = 'h';
  size_t n5 = 0;
  ck_assert_ptr_eq(memchr(test5, c5, n5), s21_memchr(test5, c5, n5));
  char *test6 = "   ";
  int c6 = 'h';
  size_t n6 = 2;
  ck_assert_ptr_eq(memchr(test6, c6, n6), s21_memchr(test6, c6, n6));
  char *test7 = "1245794&$458#";
  int c7 = '&';
  size_t n7 = 12;
  ck_assert_ptr_eq(memchr(test7, c7, n7), s21_memchr(test7, c7, n7));
  char *test8 = "hello school 21!";
  int c8 = '&';
  size_t n8 = 12;
  ck_assert_ptr_eq(memchr(test8, c8, n8), s21_memchr(test8, c8, n8));
}
END_TEST

START_TEST(s21_memset_test) {
  char test1[10] = "fggfg";
  int c1 = 'A';
  size_t n1 = 9;
  ck_assert_str_eq(memset(test1, c1, n1), s21_memset(test1, c1, n1));
  char test2[] = "ghgh";
  int c2 = '0';
  size_t n2 = 2;
  ck_assert_str_eq(memset(test2, c2, n2), s21_memset(test2, c2, n2));
  char test3[] = "Hello, World!";
  int c3 = 'H';
  size_t n3 = 5;
  ck_assert_str_eq(memset(test3, c3, n3), s21_memset(test3, c3, n3));
  char test4[] = "Supernova, Void, Galaxy, Oxygen";
  int c4 = 'W';
  size_t n4 = 9;
  ck_assert_str_eq(memset(test4, c4, n4), s21_memset(test4, c4, n4));
  char test5[] = "Supernova, Void, Galaxy, Oxygen";
  int c5 = '1';
  size_t n5 = 5;
  ck_assert_str_eq(memset(test5, c5, n5), s21_memset(test5, c5, n5));
}
END_TEST

START_TEST(s21_memcpy_test) {
  char dest1[10] = "aaa";
  char *test1 = "bbb";
  size_t n1 = 2;
  ck_assert_str_eq(memcpy(dest1, test1, n1), s21_memcpy(dest1, test1, n1));
  char dest2[30] = "Hello shcool 21!";
  char *test2 = "World";
  size_t n2 = 5;
  ck_assert_str_eq(memcpy(dest2, test2, n2), s21_memcpy(dest2, test2, n2));
  char dest3[30] = "Hello shcool 21!";
  char *test3 = "Hello world\0";
  size_t n3 = 12;
  ck_assert_str_eq(memcpy(dest3, test3, n3), s21_memcpy(dest3, test3, n3));
  char dest4[30] = "Hello shcool 21!";
  char *test4 = "Hello\nworld\0";
  size_t n4 = 12;
  ck_assert_str_eq(memcpy(dest4, test4, n4), s21_memcpy(dest4, test4, n4));
  char dest5[30] = "Hello shcool 21!";
  char *test5 = "11111111";
  size_t n5 = 5;
  ck_assert_str_eq(memcpy(dest5, test5, n5), s21_memcpy(dest5, test5, n5));
}
END_TEST

START_TEST(s21_memcmp_test) {
  char *test1 = "Hello school 21!";
  char *test11 = "Hello school 21!";
  size_t n1 = 5;
  ck_assert_int_eq(memcmp(test1, test11, n1), s21_memcmp(test1, test11, n1));
  char *test2 = "Hello school 21!";
  char *test22 = "Hello sghool 21!";
  size_t n2 = 0;
  ck_assert_int_eq(memcmp(test2, test22, n2), s21_memcmp(test2, test22, n2));
  char *test3 = "Hello school 21!";
  char *test33 = "Hello sghool 21!";
  size_t n3 = 16;
  ck_assert_int_eq(memcmp(test3, test33, n3), s21_memcmp(test3, test33, n3));
  char *test4 = "";
  char *test44 = "";
  size_t n4 = 0;
  ck_assert_int_eq(memcmp(test4, test44, n4), s21_memcmp(test4, test44, n4));
  char *test5 = "he";
  char *test55 = "Hello school 21!";
  size_t n5 = 2;
  ck_assert_int_eq(memcmp(test5, test55, n5), s21_memcmp(test5, test55, n5));
}
END_TEST

START_TEST(s21_strcspn_test) {
  char *test1 = "Hello school 21!";
  char *test11 = "bye";
  ck_assert_int_eq(strcspn(test1, test11), s21_strcspn(test1, test11));
  char *test2 = "Hello school 21!";
  char *test22 = "sc";
  ck_assert_int_eq(strcspn(test2, test22), s21_strcspn(test2, test22));
  char *test3 = "Hello school 21!";
  char *test33 = "He";
  ck_assert_int_eq(strcspn(test3, test33), s21_strcspn(test3, test33));
  char *test4 = "Hello school 21!";
  char *test44 = "!";
  ck_assert_int_eq(strcspn(test4, test44), s21_strcspn(test4, test44));
  char *test5 = "Hello, school 21!";
  char *test55 = "H,";
  ck_assert_int_eq(strcspn(test5, test55), s21_strcspn(test5, test55));
  char *test6 = "!!!!";
  char *test66 = "!";
  ck_assert_int_eq(strcspn(test6, test66), s21_strcspn(test6, test66));
  char *test7 = "";
  char *test77 = "He";
  ck_assert_int_eq(strcspn(test7, test77), s21_strcspn(test7, test77));
  char *test8 = "Hello school 21!";
  char *test88 = "";
  ck_assert_int_eq(strcspn(test8, test88), s21_strcspn(test8, test88));
  char *test9 = "Hello, sch\0ool 21!";
  char *test99 = "\0";
  ck_assert_int_eq(strcspn(test9, test99), s21_strcspn(test9, test99));
}
END_TEST

START_TEST(s21_strncpy_test) {
  char dest1[10] = "";
  char s21_dest1[10] = "";
  char *test1 = "Hello";
  size_t n1 = 5;
  ck_assert_str_eq(strncpy(dest1, test1, n1),
                   s21_strncpy(s21_dest1, test1, n1));
  char dest2[20] = "";
  char s21_dest2[20] = "";
  char *test2 = "Hello";
  size_t n2 = 10;
  ck_assert_str_eq(strncpy(dest2, test2, n2),
                   s21_strncpy(s21_dest2, test2, n2));
  char dest3[10] = "gh";
  char s21_dest3[10] = "gh";
  char *test3 = "";
  size_t n3 = 5;
  ck_assert_str_eq(strncpy(dest3, test3, n3),
                   s21_strncpy(s21_dest3, test3, n3));
  char dest4[10] = "";
  char s21_dest4[10] = "";
  char *test4 = "Hello";
  size_t n4 = 0;
  ck_assert_str_eq(strncpy(dest4, test4, n4),
                   s21_strncpy(s21_dest4, test4, n4));
  char dest5[10] = "";
  char s21_dest5[10] = "";
  char *test5 = "Hello";
  size_t n5 = 3;
  ck_assert_str_eq(strncpy(dest5, test5, n5),
                   s21_strncpy(s21_dest5, test5, n5));
  char dest6[30] = "";
  char s21_dest6[30] = "";
  char *test6 = "Hello\0school 21!";
  size_t n6 = 7;
  ck_assert_str_eq(strncpy(dest6, test6, n6),
                   s21_strncpy(s21_dest6, test6, n6));
}
END_TEST

START_TEST(s21_strtok_test) {
  char test1[] = {"Hello +school-21!"};
  char *del1 = " +-";
  char *strtok_result_1 = strtok(test1, del1);
  char *s21_strtok_result_1 = s21_strtok(test1, del1);
  while (s21_strtok_result_1 != S21_NULL) {
    ck_assert_str_eq(strtok_result_1, s21_strtok_result_1);
    strtok_result_1 = strtok(NULL, del1);
    s21_strtok_result_1 = s21_strtok(S21_NULL, del1);
  }

  char test2[] = {"Hello"};
  char *del2 = " +-";
  char *strtok_result_2 = strtok(test2, del2);
  char *s21_strtok_result_2 = s21_strtok(test2, del2);
  while (s21_strtok_result_2 != S21_NULL) {
    ck_assert_str_eq(strtok_result_2, s21_strtok_result_2);
    strtok_result_2 = strtok(NULL, del2);
    s21_strtok_result_2 = s21_strtok(S21_NULL, del2);
  }

  char test3[] = {"Hello. school. 21!! Oxygen,. Oasis,. Void, Galaxy"};
  char *del3 = "He";
  char *strtok_result_3 = strtok(test3, del3);
  char *s21_strtok_result_3 = s21_strtok(test3, del3);
  while (s21_strtok_result_3 != S21_NULL) {
    ck_assert_str_eq(strtok_result_3, s21_strtok_result_3);
    strtok_result_3 = strtok(NULL, del3);
    s21_strtok_result_3 = s21_strtok(S21_NULL, del3);
  }

  char test4[] = {"He"};
  char *del4 = "He";
  char *strtok_result_4 = strtok(test4, del4);
  char *s21_strtok_result_4 = s21_strtok(test4, del4);
  while (s21_strtok_result_4 != S21_NULL) {
    ck_assert_str_eq(strtok_result_4, s21_strtok_result_4);
    strtok_result_4 = strtok(NULL, del4);
    s21_strtok_result_4 = s21_strtok(S21_NULL, del4);
  }

  char test5[] = {"GHG\0HGH"};
  char *del5 = "G";
  char *strtok_result_5 = strtok(test5, del5);
  char *s21_strtok_result_5 = s21_strtok(test5, del5);
  while (s21_strtok_result_5 != S21_NULL) {
    ck_assert_str_eq(strtok_result_5, s21_strtok_result_5);
    strtok_result_5 = strtok(NULL, del5);
    s21_strtok_result_5 = s21_strtok(S21_NULL, del5);
  }
}
END_TEST

START_TEST(s21_strerror_test) {
  for (int i = -5; i < 120; i++) {
    char *s21_err = s21_strerror(i);
    char *err = strerror(i);
    ck_assert_str_eq(s21_err, err);
  }
}
END_TEST

START_TEST(s21_sprint_test_prozent) {
  char buff_1[1024];
  char s21_buff_1[1024];
  sprintf(buff_1, "%%");
  s21_sprintf(s21_buff_1, "%%");
  ck_assert_str_eq(buff_1, s21_buff_1);
}
END_TEST

START_TEST(s21_sprintf_test_c) {
  char buff_1[1024];
  char s21_buff_1[1024];
  sprintf(buff_1, "%10c %-10c %c %c %c %-7c", 'k', 'k', 67, '8', ' ', 't');
  s21_sprintf(s21_buff_1, "%10c %-10c %c %c %c %-7c", 'k', 'k', 67, '8', ' ',
              't');
  ck_assert_str_eq(buff_1, s21_buff_1);
}
END_TEST

START_TEST(s21_sprintf_test_d_polozhitelnoe) {
  char buff_1[1024];
  char s21_buff_1[1024];
  sprintf(buff_1, "%d %0d %7d %.3d %7.3d %.d %hd %ld", 7, 2, 45, 12, 85, 4,
          124678, 12345678901);
  s21_sprintf(s21_buff_1, "%d %0d %7d %.3d %7.3d %.d %hd %ld", 7, 2, 45, 12, 85,
              4, 124678, 12345678901);
  ck_assert_str_eq(buff_1, s21_buff_1);

  char buff_2[1024];
  char s21_buff_2[1024];
  sprintf(buff_2, "% d % 0d % 7d % .3d % 7.3d % .d % hd % ld", 7, 2, 45, 12, 85,
          4, 124678, 12345678901);
  s21_sprintf(s21_buff_2, "% d % 0d % 7d % .3d % 7.3d % .d % hd % ld", 7, 2, 45,
              12, 85, 4, 124678, 12345678901);
  ck_assert_str_eq(buff_2, s21_buff_2);

  char buff_3[1024];
  char s21_buff_3[1024];
  sprintf(buff_3, "%-d % -7d %-.3d % -7.3d %-.d % -hd % -ld", 7, 45, 12, 85, 4,
          124678, 12345678901);
  s21_sprintf(s21_buff_3, "%-d % -7d %-.3d % -7.3d %-.d % -hd % -ld", 7, 45, 12,
              85, 4, 124678, 12345678901);
  ck_assert_str_eq(buff_3, s21_buff_3);

  char buff_4[1024];
  char s21_buff_4[1024];
  sprintf(buff_4, "%+-d %+0d %+-7d %+.3d %+-7.3d %+.d %+hd %+ld", 7, 2, 45, 12,
          85, 4, 124678, 12345678901);
  s21_sprintf(s21_buff_4, "%+-d %+0d %+-7d %+.3d %+-7.3d %+.d %+hd %+ld", 7, 2,
              45, 12, 85, 4, 124678, 12345678901);
  ck_assert_str_eq(buff_4, s21_buff_4);
}
END_TEST

START_TEST(s21_sprintf_test_d_otrizatelnoe) {
  char buff_1[1024];
  char s21_buff_1[1024];
  sprintf(buff_1, "%d %0d %7d %.3d %7.3d %.d %hd %ld", -7, -2, -45, -12, -85,
          -4, -124678, -12345678901);
  s21_sprintf(s21_buff_1, "%d %0d %7d %.3d %7.3d %.d %hd %ld", -7, -2, -45, -12,
              -85, -4, -124678, -12345678901);
  ck_assert_str_eq(buff_1, s21_buff_1);

  char buff_2[1024];
  char s21_buff_2[1024];
  sprintf(buff_2, "% d % 0d % 7d % .3d % 7.3d % .d % hd % ld", -7, -2, -45, -12,
          -85, -4, -124678, -12345678901);
  s21_sprintf(s21_buff_2, "% d % 0d % 7d % .3d % 7.3d % .d % hd % ld", -7, -2,
              -45, -12, -85, -4, -124678, -12345678901);
  ck_assert_str_eq(buff_2, s21_buff_2);

  char buff_3[1024];
  char s21_buff_3[1024];
  sprintf(buff_3, "% -d % -7d % -.3d %-7.3d % -.d %-hd % -ld", -7, -45, -12,
          -85, -4, -124678, -12345678901);
  s21_sprintf(s21_buff_3, "% -d % -7d % -.3d %-7.3d % -.d %-hd % -ld", -7, -45,
              -12, -85, -4, -124678, -12345678901);
  ck_assert_str_eq(buff_3, s21_buff_3);

  char buff_4[1024];
  char s21_buff_4[1024];
  sprintf(buff_4, "%+-d %+-7d %+-.3d %+-7.3d %+-.d %+-hd %+-ld", -7, -45, -12,
          -85, -4, -124678, -12345678901);
  s21_sprintf(s21_buff_4, "%+-d %+-7d %+-.3d %+-7.3d %+-.d %+-hd %+-ld", -7,
              -45, -12, -85, -4, -124678, -12345678901);
  ck_assert_str_eq(buff_4, s21_buff_4);
}
END_TEST

START_TEST(s21_sprintf_test_d_null) {
  char buff_1[1024];
  char s21_buff_1[1024];
  sprintf(buff_1, "%d % 0d %7d % .3d %7.3d % .d %hd", 0, 0, 0, 0, 0, 0, 0);
  s21_sprintf(s21_buff_1, "%d % 0d %7d % .3d %7.3d % .d %hd", 0, 0, 0, 0, 0, 0,
              0);
  ck_assert_str_eq(buff_1, s21_buff_1);

  char buff_4[1024];
  char s21_buff_4[1024];
  sprintf(buff_4, "%-d % -7d %+-.3d % -7.3d %+-.d %+-hd", 0, 0, 0, 0, 0, 0);
  s21_sprintf(s21_buff_4, "%-d % -7d %+-.3d % -7.3d %+-.d %+-hd", 0, 0, 0, 0, 0,
              0);
  ck_assert_str_eq(buff_4, s21_buff_4);
}
END_TEST

START_TEST(s21_sprintf_test_f_polozhitelnoe) {
  char buff_1[1024];
  char s21_buff_1[1024];
  sprintf(buff_1, "%f %0f %.3f %7f %7.5f %.f", 5.7, 47.3, 45.7454578545887455,
          14.3, 458775848.554215879542695, 451.78454);
  s21_sprintf(s21_buff_1, "%f %0f %.3f %7f %7.5f %.f", 5.7, 47.3,
              45.7454578545887455, 14.3, 458775848.554215879542695, 451.78454);
  ck_assert_str_eq(buff_1, s21_buff_1);

  char buff_2[1024];
  char s21_buff_2[1024];
  sprintf(buff_2, "% f % 0f % .3f % 7f % 7.5f % .f", 5.7, 47.3,
          45.7454578545887455, 14.3, 458775848.554215879542695, 451.78454);
  s21_sprintf(s21_buff_2, "% f % 0f % .3f % 7f % 7.5f % .f", 5.7, 47.3,
              45.7454578545887455, 14.3, 458775848.554215879542695, 451.78454);
  ck_assert_str_eq(buff_2, s21_buff_2);

  char buff_3[1024];
  char s21_buff_3[1024];
  sprintf(buff_3, "% -f %-.3f % -7f %-7.5f % -.f", 5.7, 47.3,
          45.7454578545887455, 458775848.554215879542695, 451.78454);
  s21_sprintf(s21_buff_3, "% -f %-.3f % -7f %-7.5f % -.f", 5.7, 47.3,
              45.7454578545887455, 458775848.554215879542695, 451.78454);
  ck_assert_str_eq(buff_3, s21_buff_3);

  char buff_4[1024];
  char s21_buff_4[1024];
  sprintf(buff_4, "%+-f %+-.3f %+-7f %+-7.5f %+-.f", 5.7, 47.3,
          0.7454578545887455, 458775848.554215879542695, 451.78454);
  s21_sprintf(s21_buff_4, "%+-f %+-.3f %+-7f %+-7.5f %+-.f", 5.7, 47.3,
              0.7454578545887455, 458775848.554215879542695, 451.78454);
  ck_assert_str_eq(buff_4, s21_buff_4);
}
END_TEST

START_TEST(s21_sprintf_test_f_otrizatelnoe) {
  char buff_1[1024];
  char s21_buff_1[1024];
  sprintf(buff_1, "%f %0f %.3f %7f %7.5f %.f", -5.7, -47.3,
          -45.7454578545887455, -14.3, -458775848.554215879542695, -451.78454);
  s21_sprintf(s21_buff_1, "%f %0f %.3f %7f %7.5f %.f", -5.7, -47.3,
              -45.7454578545887455, -14.3, -458775848.554215879542695,
              -451.78454);
  ck_assert_str_eq(buff_1, s21_buff_1);

  char buff_2[1024];
  char s21_buff_2[1024];
  sprintf(buff_2, "% f % 0f % .3f % 7f % 7.5f % .f", -5.7, -47.3,
          -45.7454578545887455, -14.3, -458775848.554215879542695, -451.78454);
  s21_sprintf(s21_buff_2, "% f % 0f % .3f % 7f % 7.5f % .f", -5.7, -47.3,
              -45.7454578545887455, -14.3, -458775848.554215879542695,
              -451.78454);
  ck_assert_str_eq(buff_2, s21_buff_2);

  char buff_3[1024];
  char s21_buff_3[1024];
  sprintf(buff_3, "% -f %-.3f % -7f %-7.5f % -.f", -5.7, -45.7454578545887455,
          -14.3, -458775848.554215879542695, -451.78454);
  s21_sprintf(s21_buff_3, "% -f %-.3f % -7f %-7.5f % -.f", -5.7,
              -45.7454578545887455, -14.3, -458775848.554215879542695,
              -451.78454);
  ck_assert_str_eq(buff_3, s21_buff_3);

  char buff_4[1024];
  char s21_buff_4[1024];
  sprintf(buff_4, "%+f %+.3f %+-7f %+7.5f %+-.f", -5.7, -47.3,
          -45.7454578545887455, -458775848.554215879542695, -451.78454);
  s21_sprintf(s21_buff_4, "%+f %+.3f %+-7f %+7.5f %+-.f", -5.7, -47.3,
              -45.7454578545887455, -458775848.554215879542695, -451.78454);
  ck_assert_str_eq(buff_4, s21_buff_4);
}
END_TEST

START_TEST(s21_sprintf_test_f_with_null) {
  char buff_1[1024];
  char s21_buff_1[1024];
  sprintf(buff_1, "%f %0f %.3f %7f %7.5f %.f", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
  s21_sprintf(s21_buff_1, "%f %0f %.3f %7f %7.5f %.f", 0.0, 0.0, 0.0, 0.0, 0.0,
              0.0);
  ck_assert_str_eq(buff_1, s21_buff_1);

  char buff_2[1024];
  char s21_buff_2[1024];
  sprintf(buff_2, "% f % .3f %+7f % 7.5f % .f", 0.0, 0.0, 0.0, 0.0, 0.0);
  s21_sprintf(s21_buff_2, "% f % .3f %+7f % 7.5f % .f", 0.0, 0.0, 0.0, 0.0,
              0.0);
  ck_assert_str_eq(buff_2, s21_buff_2);
}
END_TEST

START_TEST(s21_sprint_test_s) {
  char buff_1[1024];
  char s21_buff_1[1024];
  char *test1 = "Hello school 21!";
  sprintf(buff_1, "%s", test1);
  s21_sprintf(s21_buff_1, "%s", test1);
  ck_assert_str_eq(buff_1, s21_buff_1);

  char buff_2[1024];
  char s21_buff_2[1024];
  char *test2 = "Hello school 21!";
  sprintf(buff_2, "%7.4s", test2);
  s21_sprintf(s21_buff_2, "%7.4s", test2);
  ck_assert_str_eq(buff_2, s21_buff_2);

  char buff_3[1024];
  char s21_buff_3[1024];
  char *test3 = "Hello school 21!";
  sprintf(buff_3, "%-7.4s", test3);
  s21_sprintf(s21_buff_3, "%-7.4s", test3);
  ck_assert_str_eq(buff_3, s21_buff_3);

  char buff_4[1024];
  char s21_buff_4[1024];
  char *test4 = "";
  sprintf(buff_4, "%s", test4);
  s21_sprintf(s21_buff_4, "%s", test4);
  ck_assert_str_eq(buff_4, s21_buff_4);

  char buff_5[1024];
  char s21_buff_5[1024];
  char *test5 = "14579621458";
  sprintf(buff_5, "%3s", test5);
  s21_sprintf(s21_buff_5, "%3s", test5);
  ck_assert_str_eq(buff_5, s21_buff_5);
}
END_TEST

START_TEST(s21_sprint_test_u_pol) {
  char buff_1[1024];
  char s21_buff_1[1024];
  sprintf(buff_1, "%u %0u %.3u %4u %4.3u %hu %lu", (unsigned int)45,
          (unsigned int)48, (unsigned int)78, (unsigned int)2, (unsigned int)7,
          (unsigned int)487, (unsigned long)1234567891);
  s21_sprintf(s21_buff_1, "%u %0u %.3u %4u %4.3u %hu %lu", (unsigned int)45,
              (unsigned int)48, (unsigned int)78, (unsigned int)2,
              (unsigned int)7, (unsigned int)487, (unsigned long)1234567891);
  ck_assert_str_eq(buff_1, s21_buff_1);

  char buff_3[1024];
  char s21_buff_3[1024];
  sprintf(buff_3, "%-u %-.3u %4u %-4.3u %-hu %-lu", (unsigned int)45,
          (unsigned int)78, (unsigned int)2, (unsigned int)7, (unsigned int)487,
          (unsigned long)1234567891);
  s21_sprintf(s21_buff_3, "%-u %-.3u %4u %-4.3u %-hu %-lu", (unsigned int)45,
              (unsigned int)78, (unsigned int)2, (unsigned int)7,
              (unsigned int)487, (unsigned long)1234567891);
  ck_assert_str_eq(buff_3, s21_buff_3);
}
END_TEST

START_TEST(s21_sprintf_test_null) {
  char buff_1[1024];
  char s21_buff_1[1024];
  sprintf(buff_1, "%u %0u %.3u %4u %4.3u %hu", 0, 0, 0, 0, 0, 0);
  s21_sprintf(s21_buff_1, "%u %0u %.3u %4u %4.3u %hu", 0, 0, 0, 0, 0, 0);
  ck_assert_str_eq(buff_1, s21_buff_1);

  char buff_2[1024];
  char s21_buff_2[1024];
  sprintf(buff_2, "%-u %-.3u %-4u %-4.3u %-hu", 0, 0, 0, 0, 0);
  s21_sprintf(s21_buff_2, "%-u %-.3u %-4u %-4.3u %-hu", 0, 0, 0, 0, 0);
  ck_assert_str_eq(buff_2, s21_buff_2);
}
END_TEST

START_TEST(s21_sscanf_test) {
  const char *input1 = "A";
  char result0;
  char result00;
  int matched1 = sscanf(input1, "%c", &result0);
  int matched11 = s21_sscanf(input1, "%c", &result00);
  ck_assert_int_eq(matched1, matched11);
  ck_assert_int_eq(result0, result00);

  const char *input2 = "vvv";
  char result1;
  char result11;
  char result2;
  char result22;
  char result3;
  char result33;
  int matched2 = sscanf(input2, "%c%c%c", &result1, &result2, &result3);
  int matched22 = s21_sscanf(input2, "%c%c%c", &result11, &result22, &result33);
  ck_assert_int_eq(matched2, matched22);
  ck_assert_int_eq(result1, result11);
  ck_assert_int_eq(result2, result22);
  ck_assert_int_eq(result3, result33);

  const char *input4 = "-123";
  int result4;
  int result44;
  int matched4 = sscanf(input4, "%d", &result4);
  int matched44 = s21_sscanf(input4, "%d", &result44);
  ck_assert_int_eq(matched4, matched44);
  ck_assert_int_eq(result4, result44);

  const char *input5 = "-123.45";
  double result5;
  int matched5 = s21_sscanf(input5, "%f", &result5);
  ck_assert_int_eq(matched5, 1);
  ck_assert_double_eq(result5, -123.45);

  const char *input6 = "hello";
  char result6[100];
  char result66[100];
  int matched6 = sscanf(input6, "%s", result6);
  int matched66 = s21_sscanf(input6, "%s", result66);
  ck_assert_int_eq(matched6, matched66);
  ck_assert_str_eq(result6, result66);

  const char *input7 = "1234";
  int matched7 = s21_sscanf(input7, "");
  ck_assert_int_eq(matched7, 0);

  const char *input8 = "%";
  char result8;
  int matched8 = s21_sscanf(input8, "%%", &result8);
  ck_assert_int_eq(matched8, 1);
}
END_TEST

START_TEST(s21_to_upper_test) {
  char test1[] = "hello school 21!";
  char expected1[] = "HELLO SCHOOL 21!";
  char *s21_test1 = s21_to_upper(test1);
  if (s21_test1) {
    ck_assert_str_eq(expected1, s21_test1);
    free(s21_test1);
  }

  char test2[] = "Hello SchooL 21!";
  char expected2[] = "HELLO SCHOOL 21!";
  char *s21_test2 = s21_to_upper(test2);
  if (s21_test2) {
    ck_assert_str_eq(expected2, s21_test2);
    free(s21_test2);
  }

  char test3[] = "HELLO SCHOOL 21!";
  char expected3[] = "HELLO SCHOOL 21!";
  char *s21_test3 = s21_to_upper(test3);
  if (s21_test3) {
    ck_assert_str_eq(expected3, s21_test3);
    free(s21_test3);
  }

  char test4[] = "\0";
  char expected4[] = "\0";
  char *s21_test4 = s21_to_upper(test4);
  if (s21_test4) {
    ck_assert_str_eq(expected4, s21_test4);
    free(s21_test4);
  }

  char test5[] = "";
  char expected5[] = "";
  char *s21_test5 = s21_to_upper(test5);
  if (s21_test5) {
    ck_assert_str_eq(expected5, s21_test5);
    free(s21_test5);
  }
}
END_TEST

START_TEST(s21_to_lower_test) {
  char test1[] = "HELLO SCHOOL 21!";
  char expected1[] = "hello school 21!";
  char *s21_test1 = s21_to_lower(test1);
  if (s21_test1) {
    ck_assert_str_eq(expected1, s21_test1);
    free(s21_test1);
  }

  char test2[] = "HELlo ScHoOl 21!";
  char expected2[] = "hello school 21!";
  char *s21_test2 = s21_to_lower(test2);
  if (s21_test2) {
    ck_assert_str_eq(expected2, s21_test2);
    free(s21_test2);
  }

  char test3[] = "hello school 21!";
  char expected3[] = "hello school 21!";
  char *s21_test3 = s21_to_lower(test3);
  if (s21_test3) {
    ck_assert_str_eq(expected3, s21_test3);
    free(s21_test3);
  }

  char test4[] = "";
  char expected4[] = "";
  char *s21_test4 = s21_to_lower(test4);
  if (s21_test4) {
    ck_assert_str_eq(expected4, s21_test4);
    free(s21_test4);
  }

  char test5[] = "123456789";
  char expected5[] = "123456789";
  char *s21_test5 = s21_to_lower(test5);
  if (s21_test5) {
    ck_assert_str_eq(expected5, s21_test5);
    free(s21_test5);
  }
}
END_TEST

START_TEST(s21_insert_test) {
  char *test1 = "Hello 21!";
  char *str1 = "school ";
  char *expected1 = "Hello school 21!";
  char *s21_test1 = s21_insert(test1, str1, 6);
  if (s21_test1) {
    ck_assert_str_eq(expected1, s21_test1);
    free(s21_test1);
  }

  char *test2 = "Hello 21!";
  char *str2 = "school ";
  char *expected2 = S21_NULL;
  char *s21_test2 = s21_insert(test2, str2, -2);
  if (s21_test2) {
    ck_assert_str_eq(expected2, s21_test2);
    free(s21_test2);
  }

  char *test3 = "Hello \n\0";
  char *str3 = "school 21!";
  char *expected3 = "Hello school 21!\n";
  char *s21_test3 = s21_insert(test3, str3, 6);
  if (s21_test3) {
    ck_assert_str_eq(expected3, s21_test3);
    free(s21_test3);
  }

  char *test4 = "";
  char *str4 = "school 21!";
  char *expected4 = "school 21!";
  char *s21_test4 = s21_insert(test4, str4, 0);
  if (s21_test4) {
    ck_assert_str_eq(expected4, s21_test4);
    free(s21_test4);
  }

  char *test5 = "Hello";
  char *str5 = "";
  char *expected5 = "Hello";
  char *s21_test5 = s21_insert(test5, str5, 0);
  if (s21_test5) {
    ck_assert_str_eq(expected5, s21_test5);
    free(s21_test5);
  }

  char *test6 = "Hello";
  char *str6 = "";
  char *expected6 = S21_NULL;
  char *s21_test6 = s21_insert(test6, str6, 6);
  if (s21_test6) {
    ck_assert_str_eq(expected6, s21_test6);
    free(s21_test6);
  }

  char *test7 = "Hello";
  char *str7 = " school 21!";
  char *expected7 = "Hello school 21!";
  char *s21_test7 = s21_insert(test7, str7, 5);
  if (s21_test7) {
    ck_assert_str_eq(expected7, s21_test7);
    free(s21_test7);
  }

  char *test8 = "";
  char *str8 = "";
  char *expected8 = S21_NULL;
  char *s21_test8 = s21_insert(test8, str8, 0);
  if (s21_test8) {
    ck_assert_str_eq(expected8, s21_test8);
    free(s21_test8);
  }
}
END_TEST

START_TEST(s21_trim_test) {
  char *str1 = "!!!Hello school 21!!!";
  char *trim_chars1 = "!";
  char *expected1 = "Hello school 21";
  char *s21_trim1 = s21_trim(str1, trim_chars1);
  if (s21_trim1) {
    ck_assert_str_eq(expected1, s21_trim1);
    free(s21_trim1);
  }

  char *str2 = "Hello";
  char *trim_chars2 = "!+^";
  char *expected2 = "Hello";
  char *s21_trim2 = s21_trim(str2, trim_chars2);
  if (s21_trim2) {
    ck_assert_str_eq(expected2, s21_trim2);
    free(s21_trim2);
  }

  char *str3 = "";
  char *trim_chars3 = "";
  char *expected3 = "";
  char *s21_trim3 = s21_trim(str3, trim_chars3);
  if (s21_trim3) {
    ck_assert_str_eq(expected3, s21_trim3);
    free(s21_trim3);
  }

  char *str4 = "";
  char *trim_chars4 = "+-^5";
  char *expected4 = "";
  char *s21_trim4 = s21_trim(str4, trim_chars4);
  if (s21_trim4) {
    ck_assert_str_eq(expected4, s21_trim4);
    free(s21_trim4);
  }

  char *str5 = "hehehe";
  char *trim_chars5 = "";
  char *expected5 = "hehehe";
  char *s21_trim5 = s21_trim(str5, trim_chars5);
  if (s21_trim5) {
    ck_assert_str_eq(expected5, s21_trim5);
    free(s21_trim5);
  }

  char *str6 = "hehehe";
  char *trim_chars6 = "hehehe";
  char *expected6 = "";
  char *s21_trim6 = s21_trim(str6, trim_chars6);
  if (s21_trim6) {
    ck_assert_str_eq(expected6, s21_trim6);
    free(s21_trim6);
  }

  char *str7 = "            hehehe";
  char *trim_chars7 = S21_NULL;
  char *expected7 = "hehehe";
  char *s21_trim7 = s21_trim(str7, trim_chars7);
  if (s21_trim7) {
    ck_assert_str_eq(expected7, s21_trim7);
    free(s21_trim7);
  }

  char *str8 = S21_NULL;
  char *trim_chars8 = S21_NULL;
  char *expected8 = S21_NULL;
  char *s21_trim8 = s21_trim(str8, trim_chars8);
  if (s21_trim8) {
    ck_assert_str_eq(expected8, s21_trim8);
    free(s21_trim8);
  }

  char *str9 = "  !Hello !!";
  char *trim_chars9 = " !";
  char *expected9 = "Hello";
  char *s21_trim9 = s21_trim(str9, trim_chars9);
  if (s21_trim9) {
    ck_assert_str_eq(expected9, s21_trim9);
    free(s21_trim9);
  }
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, s21_strlen_test);
  tcase_add_test(tc1_1, s21_strchr_test);
  tcase_add_test(tc1_1, s21_strrchr_test);
  tcase_add_test(tc1_1, s21_strncmp_test);
  tcase_add_test(tc1_1, s21_strstr_test);
  tcase_add_test(tc1_1, s21_strpbrk_test);
  tcase_add_test(tc1_1, s21_strncat_test);
  tcase_add_test(tc1_1, s21_memchr_test);
  tcase_add_test(tc1_1, s21_memset_test);
  tcase_add_test(tc1_1, s21_memcpy_test);
  tcase_add_test(tc1_1, s21_memcmp_test);
  tcase_add_test(tc1_1, s21_strcspn_test);
  tcase_add_test(tc1_1, s21_strncpy_test);
  tcase_add_test(tc1_1, s21_strtok_test);
  tcase_add_test(tc1_1, s21_strerror_test);
  tcase_add_test(tc1_1, s21_sprint_test_prozent);
  tcase_add_test(tc1_1, s21_sprintf_test_c);
  tcase_add_test(tc1_1, s21_sprintf_test_d_polozhitelnoe);
  tcase_add_test(tc1_1, s21_sprintf_test_d_otrizatelnoe);
  tcase_add_test(tc1_1, s21_sprintf_test_d_null);
  tcase_add_test(tc1_1, s21_sprintf_test_f_polozhitelnoe);
  tcase_add_test(tc1_1, s21_sprintf_test_f_otrizatelnoe);
  tcase_add_test(tc1_1, s21_sprintf_test_f_with_null);
  tcase_add_test(tc1_1, s21_sprint_test_s);
  tcase_add_test(tc1_1, s21_sprint_test_u_pol);
  tcase_add_test(tc1_1, s21_sprintf_test_null);
  tcase_add_test(tc1_1, s21_sscanf_test);
  tcase_add_test(tc1_1, s21_to_upper_test);
  tcase_add_test(tc1_1, s21_to_lower_test);
  tcase_add_test(tc1_1, s21_insert_test);
  tcase_add_test(tc1_1, s21_trim_test);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
