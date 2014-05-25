#include <stdint.h>
#include <stdlib.h>
#include<stdio.h>
#include "distance.h"

struct smap {
    int *m;
    int length;
};

void print_smap(smap sm) {
    printf("\nStrokemap:\n");
    for(int i=0;i<sm.length;i++) {
        printf("%i ",i);
    }
    printf("\n");
    for(int i=0;i<sm.length;i++) {
        printf("%i ",sm.m[i]);
    }
    printf("\n");
}

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
 *  the smallest distance. distance is a function 
 *  pointer to a stroke distance function
 */

smap make_by_dist(kanji larger, kanji smaller, 
        int (*dist) (kanji, int, kanji, int)) {
    
    int len_large = larger.c_strokes;
     
    // create map of size larger and
    // set each image as unassigned (-1)
    smap sm = make_smap(len_large);
    for(int i=0;i<sm.length;i++) {
        sm.m[i] = -1;
    }
    // to track those strokes of larger kanji
    // which haven't been fixed yet - initially all
    bool* rem_large = (bool*) malloc(sizeof(bool) * len_large);
    for(int i=0;i<len_large;i++) {
        rem_large[i] = true;
    }
    
    // for each stroke of the smaller kanji:
    // find -- among the unassigned of the larger --
    // the stroke, that minimizes the distance
    // then set that stroke as assigned

    for(int i=0;i<smaller.c_strokes;i++) {
        int min_dist = 1000000;
        int min_j = -1;
        for(int j=0;j<len_large;j++) {
            if(rem_large[j] != false) {  // if the larger stroke has not 
                                         // been assigned yet, check, otherwise
                                         // skip
                int dist_ij = dist(larger,j,smaller,i);
                if(dist_ij < min_dist) {
                    min_dist = dist_ij;
                    min_j = j;
                }
            }
        }
        if(min_j != -1) {  // a minimum was actually found
                           // should always happen
            rem_large[min_j] = false;
            sm.m[min_j] = i;
        }
    }
    free(rem_large);
    return sm;
}

smap get_initial_map(kanji larger, kanji smaller,
        int (*dist) (kanji, int, kanji, int)) {
    // first initalize, then optimize the
    // initial assignment
    smap sm = make_by_dist(larger, smaller, dist);
    printf("initial stroke map\n");
    print_smap(sm);

    // optimize the assignment by iterating
    // several times. Here set to 3
    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < sm.length; i++) {
            if (sm.m[i] != -1) {
                int i_mapi = dist(larger, i, smaller, sm.m[i]);
                for (int j = 0; j < sm.length; j++) {
                    if (sm.m[i] != -1) {
                        if (sm.m[j] != -1) {
                            int j_mapj = dist(larger, j, smaller, sm.m[j]);
                            int i_mapj = dist(larger, j, smaller, sm.m[i]);
                            int j_mapi = dist(larger, i, smaller, sm.m[j]);
                            if (j_mapi + i_mapj < i_mapi + j_mapj) {
                                // switch
                                int mapj = sm.m[j];
                                sm.m[j] = sm.m[i];
                                sm.m[i] = mapj;
                                i_mapi = i_mapj;
                            }
                        } else { // consider switching just i and j
                            int i_mapj = dist(larger, j, smaller, sm.m[i]);
                            if (i_mapj < i_mapi) { // switch
                                sm.m[j] = sm.m[i];
                                sm.m[i] = -1;
                                i_mapi = i_mapj;
                            }
                        }
                    }
                }
            }
        }
    }
    return sm;
}