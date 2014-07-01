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
    printf("\nStrokes: %i\n",k.c_strokes);
	for(int i=0;i<k.c_strokes;i++) {
		printf("Stroke[%i]: ",i);
		for(int j=0;j<k.c_points[i];j++) {
			printf("(%i,%i) ",k.xy[i][j].x,k.xy[i][j].y);
		}
        printf("\n");
	}
    printf("\n");
}

void add_stroke(kanji* k, point* ps, int len) {
    
    
    // printf("sizeof ps: %i\n",sizeof(ps));
    // printf("sizeof point: %i\n",sizeof(point));
    
    
    
    // printf("reallocating c_points... \n");

    // increase c_points by one and store length of ps[] in there
    (*k).c_points = (int*) realloc((*k).c_points, ((*k).c_strokes + 1) * sizeof(int));    
    (*k).c_points[(*k).c_strokes] = len;
    
    // printf("c_points at 0: %i\n",(*k).c_points[0]);
    

    // printf("increasing 2d array... \n");
    for(int i=0;i<k->c_strokes;i++) {
        // printf("address of *k.xy[%i]: %i\n",i,k->xy[i]);
    }

    // increase 2dim array by adding one more space for pointer
    (*k).xy = (point**) realloc((*k).xy,((*k).c_strokes + 1) * sizeof (point*));
    // printf("after realloc of 2d array... \n");

    for(int i=0;i<k->c_strokes+1;i++) {
        // printf("address of *k.xy[%i]: %i\n",i,k->xy[i]);
    }


    // insert new array at end
    (*k).xy[(*k).c_strokes] = ps;
    
    // printf("k.xy @0 x,y %i,%i and at 1x,y: %i,%i\n",(*k).xy[0][0].x,(*k).xy[0][0].y,
     //         (*k).xy[0][1].x, (*k).xy[0][1].y);
    
    // we have one more stroke in that kanji
    (*k).c_strokes++;
    
    // print_kanji((*k));
    
}
 
    
/*
    for (xml_stroke = ezxml_child(xml_kanji, "stroke"); xml_stroke; xml_stroke = xml_stroke->next) {
        int points = count_children(xml_stroke, (char*) "point");
        temp[i] = (point*) malloc(points * sizeof (point));
        (*k).c_points[i] = points;
        int j = 0;
        for (xml_point = ezxml_child(xml_stroke, "point"); xml_point; xml_point = xml_point->next) {
            point p;
            p.x = atoi(ezxml_attr(xml_point, "x"));
            p.y = atoi(ezxml_attr(xml_point, "y"));
            temp[i][j] = p;
            j++;
        }
        i++;
    }
*/


void test_add_stroke() {
    
    point p1;
    p1.x = 1;
    p1.y = 2;
    
    printf("size of p1: %i\n", sizeof(p1));
    
    point p2;
    p2.x = 3;
    p2.y = 4;
    
    printf("size of p2: %i\n", sizeof(p2));
    
    point ps[2];
    ps[0] = p1;
    ps[1] = p2;
    
    printf("size of ps: %i\n", sizeof(ps));
    
    point p3;
    p3.x = 5;
    p3.y = 6;
    
    point p4;
    p4.x = 7;
    p4.y = 8;
    
    point p5;
    p5.x = 9;
    p5.y = 10;
    
    point ps1[] = { p3, p4, p5 };

    kanji k;
    k.c_strokes = 0;
    k.c_points = 0;
    k.xy = 0;
    
    printf("old kanji: \n");
    print_kanji(k);
    add_stroke(&k,ps,2);
    add_stroke(&k,ps,2);
    printf("new kanji: \n");
    print_kanji(k);
    add_stroke(&k,ps1,3);
    print_kanji(k);
    add_stroke(&k,ps,2);
    print_kanji(k);
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
                // dist = euclid(k.xy[i][j-1].x, k.xy[i][j-1].y,
                //                k.xy[i][j].x,k.xy[i][j].y);
                dist = dist - interval;           
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
        // printf("optimal interval: %f for stroke %i\n",best_interv, i);
        int cnt = count_extract_points(k, i, best_interv);
        e.c_points[i] = cnt;
        // printf("cnt: %i",cnt);
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
                    // printf("old point: (%i,%i) ",k.xy[i][l-1].x, k.xy[i][l-1].y);
                    // printf("current point: (%i,%i) ",k.xy[i][l].x, k.xy[i][l].y);
                    // printf("dist: %f \n",dist);
                }
                // printf("dist >= interval: %i with dist: %f, interval: %f \n", dist>=best_interv, dist, best_interv);
                if(dist >= best_interv && l>1) {
                    
                   // printf("added point: (%i,%i)\n ",k.xy[i][l-1].x, k.xy[i][l-1].y);
                    
                    temp[i][idx].x = k.xy[i][l-1].x;
                    temp[i][idx].y = k.xy[i][l-1].y;
                    // we added the previous (l-1) point, such that always
                    // distance between two extracted points <= best_interv
                    // holds. Thus we don't set dist to zero, but to "d(l,l-1)" 
                    
                    // dist = euclid(k.xy[i][l-1].x, k.xy[i][l-1].y,
                    //            k.xy[i][l].x,k.xy[i][l].y);
                    dist = dist - best_interv;
                            
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
        // printf("above was: %i\n\n",i);
    }
    e.xy = temp;
    return e;
}

