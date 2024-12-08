/**
 * @file binsearch.c
 * @author massia(massia@my.msu.ru)
 * @brief src realization of binsearch game
 * @version 0.1
 * @date 2024-12-08
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "binsearch.h"
#include <argp.h>
#include <libgen.h>
#include <libintl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief global table for roman-normal number translation from 1 to 100.
 *
 */
static const char *table[] = {
    "I",       "II",     "III",     "IV",       "V",      "VI",      "VII",
    "VIII",    "IX",     "X",       "XI",       "XII",    "XIII",    "XIV",
    "XV",      "XVI",    "XVII",    "XVIII",    "XIX",    "XX",      "XXI",
    "XXII",    "XXIII",  "XXIV",    "XXV",      "XXVI",   "XXVII",   "XXVIII",
    "XXIX",    "XXX",    "XXXI",    "XXXII",    "XXXIII", "XXXIV",   "XXXV",
    "XXXVI",   "XXXVII", "XXXVIII", "XXXIX",    "XL",     "XLI",     "XLII",
    "XLIII",   "XLIV",   "XLV",     "XLVI",     "XLVII",  "XLVIII",  "XLIX",
    "L",       "LI",     "LII",     "LIII",     "LIV",    "LV",      "LVI",
    "LVII",    "LVIII",  "LIX",     "LX",       "LXI",    "LXII",    "LXIII",
    "LXIV",    "LXV",    "LXVI",    "LXVII",    "LXVIII", "LXIX",    "LXX",
    "LXXI",    "LXXII",  "LXXIII",  "LXXIV",    "LXXV",   "LXXVI",   "LXXVII",
    "LXXVIII", "LXXIX",  "LXXX",    "LXXXI",    "LXXXII", "LXXXIII", "LXXXIV",
    "LXXXV",   "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC",      "XCI",
    "XCII",    "XCIII",  "XCIV",    "XCV",      "XCVI",   "XCVII",   "XCVIII",
    "XCIX",    "C"};

const char *toRoman(int number) { return table[number - 1]; }

int fromRoman(const char *number) {
  for (int i = 0; i < 100; ++i) {
    if (strcmp(table[i], number) == 0) {
      return i + 1;
    }
  }
  return -1;
}

void binsearch(int roman) {
  int low = 1, high = 100;
  char ans[10];
  while (high - low > 1) {
    int mid = (low + high) / 2;
    if (!roman) {
      printf(gettext("number is greater than %d?\n"), mid);
    } else {
      printf(gettext("number is greater than %s?\n"), toRoman(mid));
    }
    if (scanf("%s", ans) != 1) {
      exit(1);
    }
    if (strcmp(ans, gettext("yes")) == 0) {
      low = mid;
    } else if (strcmp(ans, gettext("no")) == 0) {
      high = mid;
    } else {
      printf(gettext("unknown command. Valiable answers: yes/no.\n"));
    }
  }
  if (!roman) {
    printf(gettext("number is greater than %d?\n"), low);
  } else {
    printf(gettext("number is greater than %s?\n"), toRoman(low));
  }
  scanf("%s", ans);
  if (strcmp(ans, gettext("yes")) == 0) {
    if (!roman) {
      printf(gettext("answer is %d!\n"), high);
    } else {
      printf(gettext("answer is %s!\n"), toRoman(high));
    }
  } else if (strcmp(ans, gettext("no")) == 0) {
    if (!roman) {
      printf(gettext("answer is %d!\n"), low);
    } else {
      printf(gettext("answer is %s!\n"), toRoman(low));
    }
  } else {
    printf(gettext("unknown command. Valiable answers: yes/no.\n"));
  }
}
