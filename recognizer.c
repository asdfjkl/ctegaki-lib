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
    
}   

wchar_t* recognize(kanji unknown, kanjis data) {
    
    result best_100[100];

    // coarse recognition with endpoints
    int (*p_endpoint) (kanji, int, kanji, int);
    p_endpoint = endpoint;
    int (*p_endpoint_conc) (kanji, int, kanji, int, int);
    p_endpoint_conc = endpoint_conc;    
    
    for(int i=0;i<data.count;i++) {
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
        smap sm_comp_ep = complete_map(sm_init_ep, larger, smaller, p_endpoint_conc);
        int weight_i = compute_weight(sm_comp_ep, larger, smaller, p_endpoint_conc);
        insert_into(best_100, 100, weight_i, data.arr[i]);
    }
    
    // fine recognition with initialization by 
    // init-dist and completion by whole-dist
    result best_10[10];
    
    int (*p_initial) (kanji, int, kanji, int);
    p_initial = initial;
    int (*p_whole) (kanji, int, kanji, int, int);
    p_whole = whole;
    for(int i=0;i<100;i++) {
        
        kanji larger;
        kanji smaller;
        if(unknown.c_strokes >= best_100[i].k.c_strokes) {
            larger = unknown;
            smaller = best_100[i].k;
        } else {
            larger = best_100[i].k;
            smaller = unknown;
        }
        smap sm_init_wh = get_initial_map(larger, smaller, p_initial);
        smap sm_comp_wh = complete_map(sm_init_wh, larger, smaller, p_whole);
        int weight_i = compute_weight(sm_comp_wh, larger, smaller, p_whole);
        insert_into(best_10, 10, weight_i, best_100[i].k);        
    }
    
    wchar_t matching_kjis[10];
    for(int i=0;i<10;i++) {
        matching_kjis[i] = best_10[i].k.kji;
    }
    
    return matching_kjis;
}
