#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

struct point {
	uint8_t x;
	uint8_t y;
};

struct kanji {
	point **xy;
	int c_strokes;
	int *c_points;
};

void print_kanji(kanji k) {
	for(int i=0;i<k.c_strokes;i++) {
		printf("new stroke\n");
		for(int j=0;j<k.c_points[i];j++) {
			printf("x: %i, y: %i\n",k.xy[i][j].x,k.xy[i][j].y);
		}
	}
}

size_t get_size(kanji k) {
        // count no of all points in kanji
        // and allocate buffer with appropriate size
        int c_points = 0;
        for(int i=0;i<k.c_strokes;i++) {
                for(int j=0;j<k.c_points[i];j++) {
 			c_points++;
                }
        }
	return (c_points * sizeof(point)) + ((k.c_strokes +1) * sizeof(int));
}

// caller has to ensure that buffer is of appropriate length
void serialize_kanji(kanji k, char* buffer) {
	// first write no of strokes, then for each
	// stroke, write number of points, then all points
	// for that stroke
	// i.e. to ensure we can desiralize to struct of type
	// kanji in reverse order
	int seeker = 0;
	memcpy(&buffer[seeker], &(k.c_strokes), sizeof(int));
	seeker += sizeof(int);
	for(int i=0;i<k.c_strokes;i++) {
		memcpy(&buffer[seeker], &(k.c_points[i]), sizeof(int));
		seeker += sizeof(int);
		for(int j=0;j<k.c_points[i];j++) {
			memcpy(&buffer[seeker], &(k.xy[i][j]), sizeof(point));
			seeker += sizeof(point);
		}

	}
}

void transform_kanji(kanji k, int add_x, int add_y) {
    for(int i=0;i<k.c_strokes;i++) {
            for(int j=0;j<k.c_points[i];j++) {
                    k.xy[i][j].x = k.xy[i][j].x + add_x;
                    k.xy[i][j].y = k.xy[i][j].y + add_y;
            }
    }
}
