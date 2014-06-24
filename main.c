#include<stdio.h>
#include "ezxml.h"
#include "xml.h"
#include "binary.h"
#include "kanji.h"
#include "kanjis.h"
#include "globals.h"
#include "normalize.h"
#include <wchar.h>
#include <locale.h>
#include "distance.h"
#include "strokemap.h"
#include "recognizer.h"
#include "tinydir.h"

int main() {
    tinydir_dir dir;
    int i;
    tinydir_open_sorted(&dir, "./test_data");

    kanji unknown;

    setlocale(LC_ALL, "de_DE.UTF-8");
    
    kanjis data = init("data.dat");
    for(int i=0;i<1000;i++) {
       wprintf(L"%lc ", data.arr[i].kji);
    }

    
    read_xml_file("./test_data/004.xml", &unknown);
    printf("\nloaded: ");
    wprintf(L"%lc ", unknown.kji);
    printf("unknown:\n");
    print_kanji(unknown);

    moment(unknown);
    printf("moment normalization applied to unknown:\n");
    print_kanji(unknown);
    kanji ex_unknown = extract_features(unknown, INTERVAL);
    printf("after feature-extraction:\n");
    print_kanji(ex_unknown);
    printf("\nrecognized:\n ");
    wchar_t *res = recognize(extract_features(unknown, INTERVAL), data);
    for (int i = 0; i < 10; i++) {
        wprintf(L"%lc ", res[i]);
    }
    printf("\n");
    
/*
    for (i = 0; i < dir.n_files; i++) {
        tinydir_file file;
        tinydir_readfile_n(&dir, &file, i);

        printf("%s\n", file.name);
        if (!file.is_dir) {
            
            char *filename = (char*) malloc(strlen("./test_data/")+strlen(file.name)+1);//+1 for the zero-terminator
            strcpy(filename, "./test_data/");
            strcat(filename, file.name);
            read_xml_file(filename, &unknown);
            printf("loaded: ");
            wprintf(L"%lc ", unknown.kji);

            printf("recognized: ");
            moment(unknown);
            wchar_t *res = recognize(extract_features(unknown, INTERVAL), data);
            for (int i = 0; i < 10; i++) {
                wprintf(L"%lc ", res[i]);
            }
            printf("\n");

        }
    }
*/
tinydir_close(&dir);
    

    



    
        
       // load kanji from xml
       // load datafile
    
       // perform recognition and show result
    
        /*
    
        setlocale(LC_ALL, "de_DE.UTF-8");
        kanjis test2 = init("data.dat");
        wprintf(L"read from disk : %lc ", test2.arr[0].kji);
        printf("\n");
        kanji k_test;
        read_xml_file("4e86.xml", &k_test);
        wprintf(L"to rec : %lc ", k_test.kji);
        printf("\n");
        wchar_t *res = recognize(k_test, test2);
        for(int i=0;i<10;i++) {
            wprintf(L"char : %lc ", res[i]);
        // printf("\n");
        }
    
    
	char test[] = "abc";
	char test1[]  = "cd";
	kanji k;
	read_xml_file("4e86.xml", &k);
        kanji ek = extract_features(k,INTERVAL);
        // print_kanji(k);
        // printf("dist00 %i 01 %i 10 %i\n",endpoint(k,0,k,0),endpoint(k,0,k,1),endpoint(k,1,k,0));
        
        test_cases();
        /*
        kanji k1;
        kanji k2;
        read_xml_file("7272.xml",&k1);
        read_xml_file("8868.xml",&k2);
        kanji ek1 = extract_features(k1,INTERVAL);
        kanji ek2 = extract_features(k2,INTERVAL);
                printf("start map test:\n");

        print_kanji(ek);
        print_kanji(ek1);
        print_kanji(ek2);
        
        int (*p_initial) (kanji, int, kanji, int);
        p_initial = initial;
        int (*p_whole) (kanji, int, kanji, int, int);
        p_whole = whole;
        smap sm1_i = get_initial_map(ek1,ek,p_initial);
        smap sm1_c = complete_map(sm1_i,ek1,ek,p_whole);
        print_smap(sm1_i);
        print_smap(sm1_c);

        smap sm2_i = get_initial_map(ek2,ek,p_initial);
        smap sm2_c = complete_map(sm2_i,ek2,ek,p_whole);
        print_smap(sm2_i);
        print_smap(sm2_c);   
        
        smap sm3_i = get_initial_map(ek1,ek2,p_initial);
        smap sm3_c = complete_map(sm3_i,ek1,ek2,p_whole);
        print_smap(sm3_i);
        print_smap(sm3_c);   
        
        
        
        // printf("read from disk:\n");
        // print_kanji(k);
        // moment(k);
        printf("normalized:\n");
        // print_kanji(k);
	setlocale(LC_ALL, "de_DE.UTF-8");
        wprintf(L"read from xml the wchar: %lc \n", k.kji);
        // kanji ka[1] = { k }; 
	// int j = write_bin_file(ka, "data");
	// printf("hex: %s, %i\n",test, k.xy[0][0].x);
	printf("finished loading from xml\n");
	// print_kanji(k);
	kanjis kjs;
	kjs.count = 1;
	kjs.arr = (kanji*) malloc(kjs.count * sizeof(kanji));
	kjs.arr[0] = k;
	write_bin_file(kjs,"data.dat");
	printf("wrote file to disk\n");
	kanjis l = read_bin_file("data.dat");
        wprintf(L"read from binary the wchar: %lc \n", l.arr[0].kji);
	printf("read following file from disk:\n");
        
	// print_kanji(l.arr[0]);
    kanji tep = l.arr[0];
    int ep0 = endpoint(tep,0,tep,0);
    int ep1 = endpoint(tep,0,tep,1);
    int ep2 = endpoint(tep,1,tep,0);
    printf("endpoint: 00: %i   01: %i   10: %i \n",ep0,ep1,ep2);
    // int ww = whole(tep,1,tep,0,1);
    // printf("whole whole: %i\n",ww);
        printf("extract features:\n");
        kanji e = extract_features(l.arr[0], INTERVAL);
        // print_kanji(e);
        kjs.arr[0] = e;
        write_bin_file(kjs,"data.dat");
        wprintf(L"last wchar: %lc \n", kjs.arr[0].kji);
        
        struct point p0;
        p0.x = 0;
        p0.y = 1;
        struct point ps[1];;
        ps[0] = p0;
        kanji testkji;
        testkji.c_strokes = 0;
        // test_add_stroke();
        // add_stroke(&testkji,ps,1);
        // print_kanji(testkji);
        // test_add_stroke();
        testWhole();
 
        */
        
	return 0;
}
