#include <stdlib.h>
#include <stdio.h>
#include "kanji.h"
#include "kanjis.h"

int write_bin_file(kanjis kjs, char filename[]){
	FILE* data = fopen(filename, "wb+");
	if(data == NULL) {
		printf("Error opening file: %s\n", filename);
		exit(1);
	}
	// number of all kanjis
	fwrite(&kjs.count, sizeof(int), 1, data);
	for(int i=0;i<kjs.count;i++) {	
		size_t buf_len = get_size(kjs.arr[i]);
		char* buffer = (char *)malloc(buf_len);
		serialize_kanji(kjs.arr[i],buffer);
		fwrite(buffer, buf_len, 1, data);
		free(buffer);
	}
	fclose(data);
	return 0;
}

kanjis read_bin_file(char filename[]) {
	kanjis kjs;
	FILE* data = fopen(filename, "rb");
	if(data == NULL) {
		printf("Error opening file: %s\n", filename);
		exit(1);
	}
	int all = 0;
	fread(&all,sizeof(int),1,data);
	kjs.count = all;
	kjs.arr = (kanji*) malloc(kjs.count * sizeof(kanji));
	for(int l=0;l<kjs.count;l++) {
		int m = 0;
		kanji k;
		fread(&m,sizeof(int),1,data);
		printf("size: %i\n",m);
		k.c_strokes = m;
		k.c_points = (int*) malloc(k.c_strokes*sizeof(int));
		point** temp = (point**) malloc(k.c_strokes * sizeof(point*));
        	for(int i=0;i<k.c_strokes;i++) {
			fread(&(k.c_points[i]),sizeof(int),1,data);
			temp[i] = (point*) malloc(k.c_points[i] * sizeof(point*));
			for(int j=0;j<k.c_points[i];j++) {
				point p;
				fread(&p,sizeof(point),1,data);
				temp[i][j] = p; 
			}
		}
		k.xy = temp;
		kjs.arr[l] = k;
	}
	fclose(data);
	return kjs;
} 
