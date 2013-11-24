#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include "math_ext.h"

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
        // (to allocate buffer with appropriate size)
        int c_points = 0;
        for(int i=0;i<k.c_strokes;i++) {
                for(int j=0;j<k.c_points[i];j++) {
 			c_points++;
                }
        }
	return (c_points * sizeof(point)) + 
                ((k.c_strokes +1) * sizeof(int)) +  // for #strokes and #points
                (sizeof(wchar_t));                  // for kanji itself
}

// caller has to ensure that buffer is of appropriate length
void serialize_kanji(kanji k, char* buffer) {
	// first write no of strokes, then wchar, then for each
	// stroke, write number of points, then all points
	// for that stroke
	// i.e. to ensure we can desiralize to struct of type
	// kanji in reverse order
	int seeker = 0;
	memcpy(&buffer[seeker], &(k.c_strokes), sizeof(int));
	seeker += sizeof(int);
        memcpy(&buffer[seeker], &(k.kji), sizeof(wchar_t));
        seeker += sizeof(wchar_t);
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

float stroke_dist(kanji k, int i) {
    float dist = 0.f;
    for(int j=0;j<k.c_points[i];j++) {
        if(j>0) {
                dist += euclid(k.xy[i][j-1].x,k.xy[i][j-1].y,
                                k.xy[i][j].x,k.xy[i][j].y);
        }
    }
    return dist;
}


/*
 * determine best fitting interval distance
 */
float best_interval_size(float dist, float interval) {
    
	float no_of_fps = dist / interval;
	int lower = (int) no_of_fps;
	int higher = lower + 1;

	float lowDif = dist / ((float) lower);
	float highDif = dist / ((float) higher);

	if(abs(lowDif-interval) < abs(highDif-interval)) {
                return lowDif; 
        } else { 
            return highDif;
        }    
}

			


/* count points that will be extracted
 * i : stroke index 
 * no : 
 * 
 */
int count_extract_points(kanji k, int i, float interval) {
    if(k.c_points[i]==0) { return 0; }
    int cnt = 1; // otherwise always include first point
    int j = 0;
    float dist = 0.f;
    while(j < k.c_points[i]) {
	if(j>0) {
                float distPoints = euclid(k.xy[i][j-1].x, k.xy[i][j-1].y,
                            k.xy[i][j].x,k.xy[i][j].y);	
                dist += distPoints;
	}
        if(dist >= interval && j>1) {
                dist = 0.f;
		cnt++;
	}
        j++;
    }
    if(cnt == 1) { cnt++; } // always add at least start + end
    // if remaining dist from previous to last point 
    // is at least 3/4 of interval, add last point
    if(dist > (0.75f * interval)) {
        cnt++;
    }
    return cnt;
}


/*
 * creates a _deep_ copy of the kanji consisting
 * of the extracted features of the input kanji
 */
kanji extract_features(kanji k, float interval) {
    kanji e;
    e.c_strokes = k.c_strokes;
    e.kji = k.kji;
    e.c_points = (int*) malloc(e.c_strokes*sizeof(int));
    point** temp = (point**) malloc(e.c_strokes * sizeof(point*));
    for(int i=0;i<k.c_strokes;i++) {

        float dist = stroke_dist(k, i);

        float best_interv = best_interval_size(dist, interval);
        printf("optimal interval: %f\n",best_interv);
        int cnt = count_extract_points(k, i, best_interv);
        e.c_points[i] = cnt;
        printf("cnt: %i",cnt);
        // printf("cnt: %i\n",cnt);
        // reserve space for new kanji
        temp[i] = (point*) malloc(e.c_points[i] * sizeof(point*));
	// add points at intervals
        
        if(k.c_points[i]>0) {
            temp[i][0].x = k.xy[i][0].x;  // always include first point
            temp[i][0].y = k.xy[i][0].y;
                int l = 0;
                int idx = 1;
                float dist = 0.f;
                while(l < k.c_points[i]) {
                if(l>0) {
                    float distPoints = euclid(k.xy[i][l-1].x, k.xy[i][l-1].y,
                                k.xy[i][l].x,k.xy[i][l].y);	
                    dist += distPoints;
                }
                if(dist >= interval && l>1) {
                    temp[i][idx].x = k.xy[i][l-1].x;
                    temp[i][idx].y = k.xy[i][l-1].y;
                    dist = 0.f;
                    idx++;
                }
                l++;
                }
        }
        int last_idx_of_i = k.c_points[i]-1;
        // always add at least start + end
        if(cnt == 1) {
            temp[i][1].x = k.xy[i][last_idx_of_i].x;
            temp[i][1].y = k.xy[i][last_idx_of_i].y;
        } 
        // if remaining dist from previous to last point 
        // is at least 3/4 of interval, add last point
        if(dist > (0.75f * interval)) {
            temp[i][cnt-1].x = k.xy[i][last_idx_of_i].x;
            temp[i][cnt-1].y = k.xy[i][last_idx_of_i].y;
        }
    }
    e.xy = temp;
    return e;
}