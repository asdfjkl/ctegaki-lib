#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "distance.h"
#include "xml.h"

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
    // printf("initial stroke map\n");
    // print_smap(sm);

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

/*
 *
 *
 */

int get_first_assigned_idx(smap sm) {    
   int i=0;
   while(i<sm.length && sm.m[i] == -1) {
     i++;
   }
   return i; 
}

int get_last_assigned_idx(smap sm) {
    int i=sm.length-1;
    while(i>=0 && sm.m[i] == -1) {
        i--;
    } 
    return i;
}

int has_unassigned_idx(smap sm) {
    for(int i=0;i<sm.length;i++) {
        if(sm.m[i] == -1) {
            return true;
        }
    }
    return false;
}

/*
 * complete an initialized map w.r.t. to
 * the provided distance measure
 */
smap complete_map(smap sm, kanji larger, kanji smaller,
        int (*dist) (kanji, int, kanji, int, int)) {
    
    if(!has_unassigned_idx(sm)) { return sm; }
    
    int fst = get_first_assigned_idx(sm);
    for(int i=0;i<fst;i++) {
        sm.m[i] = sm.m[fst];
    }
    
    int lst = get_last_assigned_idx(sm);
    for(int i=lst+1;i<sm.length;i++) {
        sm.m[i] = sm.m[lst];
    }
    
    // print_smap(sm);
    for(int i=0;i<sm.length;i++) {
        if(i+1 < sm.length && sm.m[i+1] == -1) {
            // we have a situation like this:
            //   i       i+1   i+2   ...  i+n 
            //   start   -1    ?     -1   stop

            int start = i;
            int stop = i+1;
            while(stop<sm.length && sm.m[stop] == -1) {
                stop++;
            }
            int div = start;
            int max_dist = 1000000;
            for(int j=start;j<stop;j++) {
                // printf("j ist: %i\n",j);
                int d_ab = dist(smaller,sm.m[start],larger,start,j);
                int d_bc = dist(smaller,sm.m[stop],larger,j+1,stop);
                if(d_ab + d_bc < max_dist) {
                    div = j;
                    max_dist = d_ab + d_bc;
                }
            }
            for(int j=start;j<=div;j++) {
                sm.m[j] = sm.m[start];
            }
            for(int j=div+1;j<stop;j++) {
                sm.m[j] = sm.m[stop];
            }
        } 
    }
    return sm;
}

void test_cases() {
    
        kanji k2;
        kanji k21;
        kanji k22;
        kanji k23;
        
        read_xml_file("k2.xml",&k2);
        read_xml_file("k21.xml",&k21);
        read_xml_file("k22.xml",&k22);
        read_xml_file("k23.xml",&k23);
        
        /* skip feature extraction for these 
         * specially prepared kanji
         */
        printf("k2:\n");
        print_kanji(k2);
        printf("k21:\n");
        print_kanji(k21);
        printf("k22:\n");
        print_kanji(k22);
        printf("k23:\n");
        print_kanji(k23);
        
        /* initialize with endpoint distance
         * and complete with endpoint distance
         */
        printf("endpoint initi + endpoint completion\n");
        
        int (*p_endpoint) (kanji, int, kanji, int);
        p_endpoint = endpoint;
        int (*p_endpoint_conc) (kanji, int, kanji, int, int);
        p_endpoint_conc = endpoint_conc;
        
        smap k21_k2_init = get_initial_map(k21,k2,p_endpoint);
        printf("k21 vs k2 init:\n");
        print_smap(k21_k2_init);
        // should give
        // 0  1  2 3 
        // 0 -1 -1 1         
        smap k21_k2_comp = complete_map(k21_k2_init, k21, k2, p_endpoint_conc);
        printf("k21 vs k2 completed:\n");
        print_smap(k21_k2_comp);
        // should give
        // 0 1 2 3 
        // 0 0 1 1   
                
        smap k22_k2_init = get_initial_map(k22,k2,p_endpoint);
        printf("k22 vs k2 init:\n");
        print_smap(k22_k2_init);
        // should give
        // 0  1  2 3 
        // 0 -1 -1 1
        smap k22_k2_comp = complete_map(k22_k2_init, k22, k2, p_endpoint_conc);
        printf("k22 vs k2 completed:\n");
        print_smap(k22_k2_comp);
        // should give
        // 0 1 2 3 
        // 0 0 0 1   
        
        smap k23_k2_init = get_initial_map(k23,k2,p_endpoint);
        printf("k23 vs k2 init:\n");
        print_smap(k23_k2_init);
        // should give
        // 0  1  2 3 
        // 0 -1 -1 1   
        smap k23_k2_comp = complete_map(k23_k2_init, k23, k2, p_endpoint_conc);
        printf("k23 vs k2 completed:\n");
        print_smap(k23_k2_comp);
        // should give
        // 0  1  2 3 
        // 0  1  1 1
        
        /* initialize with initial distance 
         * and complete with whole distance
         */
        printf("initial + whole completion\n");

        int (*p_initial) (kanji, int, kanji, int);
        p_initial = initial;
        int (*p_whole) (kanji, int, kanji, int, int);
        p_whole = whole;
        
        k21_k2_init = get_initial_map(k21,k2,p_initial);
        printf("k21 vs k2 init:\n");
        print_smap(k21_k2_init);
        // should give
        // 0  1  2 3 
        // 0 -1 -1 1 
        k21_k2_comp = complete_map(k21_k2_init, k21, k2, p_whole);
        printf("k21 vs k2 completed:\n");
        print_smap(k21_k2_comp);
        // should give
        // 0  1  2 3 
        // 0  0  1 1 
        
        k22_k2_init = get_initial_map(k22,k2,p_initial);
        printf("k22 vs k2 init:\n");
        print_smap(k22_k2_init);
        // should give
        // 0  1  2 3 
        // 0 -1 -1 1 
        k22_k2_comp = complete_map(k22_k2_init, k22, k2, p_whole);
        printf("k22 vs k2 completed:\n");
        print_smap(k22_k2_comp);
        // should give
        // 0  1  2 3 
        // 0  0  0 1 
        
        k23_k2_init = get_initial_map(k23,k2,p_initial);
        printf("k23 vs k2 init:\n");
        print_smap(k23_k2_init);
        // should give
        // 0  1  2 3 
        // 0 -1 -1 1 
        k23_k2_comp = complete_map(k23_k2_init, k23, k2, p_whole);
        printf("k23 vs k2 completed:\n");
        print_smap(k23_k2_comp);
        // should give
        // 0  1  2 3 
        // 0  1  1 1 

    
}

int compute_weight(smap sm, kanji larger, kanji smaller, 
        int (*dist) (kanji, int, kanji, int, int)) {
    return 42;
}