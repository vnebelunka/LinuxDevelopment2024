/**
 * @file binsearch.h
 * @author massia (massia@my.msu.ru)
 * @brief header file for binsearch game
 * @version 0.1
 * @date 2024-12-08
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef BINSEARCH_H
#define BINSEARCH_H

/**
 * @brief translate string of romanian number to decimal integer
 * @param number as romanian number. must be in interval [1, 100]
 * @return integer == romanian number.
 * @note returns -1 if number not in interval [1, 100]
 */
int fromRoman(const char *number);

/**
 * @brief translate decimal integer number to romanian
 *
 * @param number number to translate. must be in [1, 100]
 * @return const char* string representing romanian number
 * @note if number not in [1, 100] than undefined behavior
 */
const char *toRoman(int number);

/**
 * @brief playing "find number" game using binsearch with optional roman
 * interface. By asking questions about number, finds it using binsearch
 * algorithm number must be in interaval [1, 100]
 * @param roman boolean flag for roman interface
 */
void binsearch(int roman);

#endif
