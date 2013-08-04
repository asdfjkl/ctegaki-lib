#include <stdint.h>

#ifndef _KANJI_H_
#define _KANJI_H_

struct point {
	uint8_t x;
	uint8_t y;
};

struct kanji {
	point **xy;
	int c_strokes;
	int *c_points;
};

void print_kanji(kanji k);

size_t get_size(kanji k);

void serialize_kanji(kanji k, char* buffer);

#endif 
