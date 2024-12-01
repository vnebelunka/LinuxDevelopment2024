/**
 * @mainpage binsearch
 * @copydetails library
 */

/**
 * @page library
 * @brief
 * # About
 *
 * Simple \"guess number\" game in interval [1, 100] with binary search.\n
 * Possible answers: yes/no for each question.
 * # Usage
 * ~~~~~~~~~~~~~~~~~~~~~
 *    binsearch [-r]
 * ~~~~~~~~~~~~~~~~~~~~~
 * # Options
 * - `-h`, `--help`
        Give this help list
 * - `-r`
        Use romanian numbers in game
 *
 * @author Mass Ilya (massia@my.msu.ru)
 * @brief src file for binsearch game
 * @version 0.1
 * @date 2024-12-01
 * @details
 * @copyright Copyright (c) 2024
 *
*/

/**
 * @file binsearch.c
 * @copydetails library
 *
 */
#include <argp.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>
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

/**
 * @brief translate number to romanian
 *
 * @param number number to translate. must be in [1, 100]
 * @return const char* string representing romanian number
 * @note returns -1 if number not in interval [1, 100]
 */
const char *toRoman(int number) { return table[number - 1]; }
int fromRoman(const char *number) {
  for (int i = 0; i < 100; ++i) {
    if (strcmp(table[i], number) == 0) {
      return i + 1;
    }
  }
  return -1;
}

/**
 * @brief playing "find number" game using binsearch with optional roman
 * interface. By asking questions about number, finds it using binsearch
 * algorithm number must be in interaval [1, 100]
 * @param roman boolean flag for roman interface
 */
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
    scanf("%s", ans);
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

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");
#ifdef TEXTDOMAINDIR
  bindtextdomain("messages", TEXTDOMAINDIR);
  textdomain("messages");
#endif

  int roman = 0;
  if (argc == 2 &&
      (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
    printf(
        gettext("Usage: binsearch [-r]\n"
                "Simple \"guess number\" game in interval [1, 100] with "
                "binary search.\n"
                "Possible answers: yes/no for each question.\n"
                "\n"
                "-h, --help                 Give this help list\n"
                "-r                         Use romanian numbers in game\n"));
    return 0;
  }

  if (argc == 2 && strcmp(argv[1], "-r") == 0) {
    roman = 1;
  }

  binsearch(roman);
}
