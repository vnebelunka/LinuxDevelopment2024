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

#include "binsearch.h"

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
