#include<stdio.h>
#include "ezxml.h"
#include "xml.h"
#include "binary.h"
#include "kanji.h"
#include "kanjis.h";
#include "globals.h";
#include "normalize.h";

int main()
{
	char test[] = "abc";
	char test1[]  = "cd";
	kanji k;
	read_xml_file("4e86.xml", &k);
	// kanji ka[1] = { k }; 
	// int j = write_bin_file(ka, "data");
	// printf("hex: %s, %i\n",test, k.xy[0][0].x);
	printf("loaded from xml\n");
	print_kanji(k);
	kanjis kjs;
	kjs.count = 1;
	kjs.arr = (kanji*) malloc(kjs.count * sizeof(kanji));
	kjs.arr[0] = k;
	write_bin_file(kjs,"data.dat");
	printf("wrote file to disk\n");
	kanjis l = read_bin_file("data.dat");
	printf("read following file from disk:\n");
	print_kanji(l.arr[0]);
        printf("extract features:\n");
        kanji e = extract_features(l.arr[0], INTERVAL);
        print_kanji(e);
        moment(k);
        printf("moment normalization:\n");
        print_kanji(k);
        kjs.arr[0] = e;
        write_bin_file(kjs,"data.dat");
	return 0;
}
