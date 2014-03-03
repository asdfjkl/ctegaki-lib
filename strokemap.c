#include <stdint.h>
#include <stdlib.h>
#include "distance.h"

struct smap {
    int *m;
    int length;
};

smap make_smap(int len) {
    smap sm;
    sm.m = (int*) malloc(sizeof(int) * len);
    for(int i=0;i<len;i++) {
        sm.m[i] = -1;
    }
    sm.length = len;
    return sm;
}

/* 
 *  Initialize a stroke map by mapping each stroke
 *  from the larger (i.e. more strokes) kanji to
 *  the stroke of the smaller kanji, that yields
 *  the smallest _initial_ distance
 */
smap make_by_initial(kanji larger, kanji smaller) {
    smap sm = make_smap(larger.c_strokes);
    for(int i=0;i<larger.c_strokes;i++) {
        int best_idx = -1;
        int best_val = 1000000;
        for(int j=0;j<smaller.c_strokes;j++) {
            int dist = initial(larger, i, smaller, j);
            if(dist <= best_val) {
                best_val = dist;
                best_idx = j;
            }
        }
        sm.m[i] = best_idx;
    }
    return sm;
}

/* 
 *  Initialize a stroke map by mapping each stroke
 *  from the larger (i.e. more strokes) kanji to
 *  the stroke of the smaller kanji, that yields
 *  the smallest _endpoint_ distance
 */
smap make_by_endpoint(kanji larger, kanji smaller) {
    smap sm = make_smap(larger.c_strokes);
    for(int i=0;i<larger.c_strokes;i++) {
        int best_idx = -1;
        int best_val = 1000000;
        for(int j=0;j<smaller.c_strokes;j++) {
            int dist = endpoint(larger, i, smaller, j);
            if(dist <= best_val) {
                best_val = dist;
                best_idx = j;
            }
        }
        sm.m[i] = best_idx;
    }
    return sm;
}