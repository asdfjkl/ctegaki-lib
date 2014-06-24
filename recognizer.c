#include "kanji.h"
#include "kanjis.h"
#include "binary.h"
#include <wchar.h>
#include "distance.h"
#include "strokemap.h"

struct result {
    kanji k;
    int weight;
};
    
kanjis init(char filename[]) {
    kanjis kjs = read_bin_file(filename);
    return kjs;
}

void insert_into(result rs[], int len, int weight, kanji k) {
    int i=0;
    while(weight >= rs[i].weight && i < len) {
        i++;
    }
    for(int j=len-1;j>i;j--) {
        rs[j] = rs[j-1];
    }
    // printf("i: %i\n",i);
    rs[i].k = k;
    rs[i].weight = weight;
}   

wchar_t* recognize(kanji unknown, kanjis data) {
    
    kanji dummy_k;
    dummy_k.c_strokes = 0;
    result best_100[100];
    result dummy;
    dummy.weight = 100000;
    dummy.k = dummy_k;
    for(int i=0;i<100;i++) {
        best_100[i] = dummy;
    }

    // coarse recognition with endpoints
    int (*p_endpoint) (kanji, int, kanji, int);
    p_endpoint = endpoint;
    int (*p_endpoint_conc) (kanji, int, kanji, int, int);
    p_endpoint_conc = endpoint_conc;    
            wchar_t hirag_ri = L'\u308a';

    for(int i=0;i<data.count;i++) {
       //if(data.arr[i].kji == unknown.kji || data.arr[i].kji == hirag_ri) {
        {
        printf("unknown:\n");
            print_kanji(unknown);
            printf("from data-set:\n");
            print_kanji(data.arr[i]);
            
        kanji larger;
        kanji smaller;
        if(unknown.c_strokes >= data.arr[i].c_strokes) {
            larger = unknown;
            smaller = data.arr[i];
        } else {
            larger = data.arr[i];
            smaller = unknown;
        }
        smap sm_init_ep = get_initial_map(larger, smaller, p_endpoint);
                            print_smap(sm_init_ep);

        smap sm_comp_ep = complete_map(sm_init_ep, larger, smaller, p_endpoint_conc);
                    print_smap(sm_comp_ep);

        int weight_i = compute_weight(sm_comp_ep, larger, smaller, p_endpoint_conc);
        weight_i = (10 * larger.c_strokes * weight_i)/(smaller.c_strokes);
        		// return ((largeX.length*10)/(smallX.length))*weight;

        
        wprintf(L"\n coarse weight: %i for %lc ", weight_i, data.arr[i].kji);
        if(true) {
                    insert_into(best_100, 100, weight_i, data.arr[i]);
         // wprintf(L"\n %lc ", data.arr[i].kji);
        // print_smap(sm_comp_ep);
        // printf("weight: %i\n",weight_i);
        }
    }
    }
    // fine recognition with initialization by 
    // init-dist and completion by whole-dist
    dummy.weight = 100000;
    dummy.k = dummy_k;
    result best_10[10];
    for(int i=0;i<10;i++) {
        best_10[i] = dummy;
    }

    int (*p_initial) (kanji, int, kanji, int);
    p_initial = initial;
    int (*p_whole) (kanji, int, kanji, int, int);
    p_whole = whole;
    for (int i = 0; i < 100; i++) {
        // skip the inserted dummy kanji
        // which has zero strokes
        // skip "smaller" kanji 
        if (best_100[i].k.c_strokes > 0) { // && best_100[i].k.kji == unknown.kji) {
            if(best_100[i].k.kji == unknown.kji ) {
                printf("within best 100\n");
            }            
            kanji larger;
            kanji smaller;
            if (unknown.c_strokes >= best_100[i].k.c_strokes) {
                larger = unknown;
                smaller = best_100[i].k;
            } else {
                larger = best_100[i].k;
                smaller = unknown;
            }
            smap sm_init_wh = get_initial_map(larger, smaller, p_initial);
               //                 print_smap(sm_init_wh);

            smap sm_comp_wh = complete_map(sm_init_wh, larger, smaller, p_whole);
            // print_smap(sm_comp_wh);
            int weight_i = compute_weight1(sm_comp_wh, larger, smaller, p_whole);
 
            wprintf(L"\n fine weight: %i for %lc ", weight_i, best_100[i].k.kji);
            if(weight_i < 1000) {
               //  wprintf(L"\n BEST %lc ", best_100[i].k);

            }
            insert_into(best_10, 10, weight_i, best_100[i].k);
        }
    }
    
    static wchar_t matching_kjis[10];
    for(int i=0;i<10;i++) {
        matching_kjis[i] = best_10[i].k.kji;
        // printf("w: %i", best_10[i].weight);
    }
    // printf("\n");
    return matching_kjis;
}
