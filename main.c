#include<stdio.h>
#include "ezxml.h"
#include "xml.h"
#include "binary.h"
#include "kanji.h"
#include "kanjis.h";
#include "globals.h";
#include "normalize.h";
#include <wchar.h>
#include <locale.h>
#include "distance.h"

int main()
{
	char test[] = "abc";
	char test1[]  = "cd";
	kanji k;
	read_xml_file("4e86.xml", &k);
        kanji ek = extract_features(k,INTERVAL);
        print_kanji(k);
        printf("dist00 %i 01 %i 10 %i\n",endpoint(k,0,k,0),endpoint(k,0,k,1),endpoint(k,1,k,0));
        
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
        printf("extract features:\n");
        kanji e = extract_features(l.arr[0], INTERVAL);
        // print_kanji(e);
        kjs.arr[0] = e;
        write_bin_file(kjs,"data.dat");
        wprintf(L"last wchar: %lc \n", kjs.arr[0].kji);
	return 0;
}
