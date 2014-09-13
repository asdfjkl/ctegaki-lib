#include <stdint.h>
#include <stdlib.h>

#ifndef _KANJI_H_
#define _KANJI_H_

struct point {
	uint8_t x;
	uint8_t y;
};

struct kanji {
        wchar_t kji;
	point **xy;
	int c_strokes;
	int *c_points;
};

void add_stroke(kanji* k, point* ps, int len);

void free_kanji(kanji k);

void test_add_stroke(); 

void print_kanji(kanji k);

size_t get_size(kanji k);

void serialize_kanji(kanji k, char* buffer);

void transform_kanji(kanji k, int add_x, int add_y);

kanji extract_features(kanji k, float interval);

#endif 
