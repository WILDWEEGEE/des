#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "des.h"

static unsigned char ip_first[] = {
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7
};

/*
 * First permutation
 */
static void des_ip_first(unsigned char *current)
{
	unsigned char prev[8];
	unsigned char swap;
	int i;

	memcpy(&prev, current, sizeof(prev));
	for (i = 0; i < 64; ++i) {
		/* swap the two bits using the matrice ip_first */
		swap = prev[BYTE_POS(ip_first[i] - 1)] & (1 << (BIT_POS(ip_first[i] - 1)));
		swap >>= BIT_POS(ip_first[i] - 1);
		swap <<= BIT_POS(i);
		current[BYTE_POS(i)] &= ~(1 << BIT_POS(i));
		current[BYTE_POS(i)] |= swap;
	}
}

static unsigned char ip_second[] = {
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25
};

/*
 * Second permutation
 */
static void des_ip_second(unsigned char *current)
{
	unsigned char prev[8];
	unsigned char swap;
	int i;

	memcpy(&prev, current, sizeof(prev));
	for (i = 0; i < 64; ++i) {
		/* swap the two bits using the matrice ip_second */
		swap = prev[BYTE_POS(ip_second[i] - 1)] & (1 << BIT_POS(ip_second[i] - 1));
		swap >>= BIT_POS(ip_second[i] - 1);
		swap <<= BIT_POS(i);
		current[BYTE_POS(i)] &= ~(1 << BIT_POS(i));
		current[BYTE_POS(i)] |= swap;
	}
}

static unsigned char exp_right[] = {
	32, 1, 2, 3, 4, 5,
	4, 5, 6, 7, 8, 9,
	8, 9, 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32, 1
};

/*
 * Block expansion
 */
static void des_exp(unsigned char block[4], unsigned char exp[6])
{
	unsigned char swap;
	int i;

	for (i = 0; i < 48; ++i) {
		/* swap the two bits using the matrice exp_right */
		swap = block[BYTE_POS(exp_right[i] - 1)] & (1 << BIT_POS(exp_right[i] - 1));
		swap >>= BIT_POS(exp_right[i] - 1);
		swap <<= BIT_POS(i);
		exp[BYTE_POS(i)] &= ~(1 << BIT_POS(i));
		exp[BYTE_POS(i)] |= swap;
	}
}

/*
 * Main entry
 */
void des_cipher_block(unsigned char *block)
{
	unsigned char right[6];

	des_ip_first(block);
	memcpy(right, &block[4], 4 * sizeof(unsigned char));
	des_exp(block, right);
	des_ip_second(block);
	exit(1);
}
