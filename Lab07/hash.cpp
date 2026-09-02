#include <iostream>
#include <iomanip>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include "hash.h"

#define doubleu 31;
// *typically 64*
// ULONG_MAX = 1.8e19
// UINT_MAX = 4.2Billion



size_t Hash::multiplication_hash(size_t value){
	// W = 2^w
	// M = 2^p
	// a = prime.
	// Given key `value`, return:
	// FLOOR( (a*value % W)/2^(w-p) )
	//unsigned long long S = 4294967296;
	//unsigned long long num = S * value;
	float A = 0.6180339887498949; // ~1 - sqrt(5);
	size_t w = doubleu;
	size_t mask = ((1 << w) -1);
	size_t numerator = size_t(value * A) & mask;
	return numerator >> (w-13);
}

long Hash::hash(long value){
	double A = 0.6180339887498949;
	long w = 31; // 32 is too damn much.
	int p = 29;
	int mask = (1 << w) - 1;
	int numerator = int(value*A) & mask;
	return numerator >> (w-p);
}
