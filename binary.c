#include <stdlib.h>
#include <stdio.h>
#include "kanji.h"

int write_bin_file(kanji k[], char filename[]){

	FILE* data = fopen(filename, "wb");
	if(data == NULL) {
		printf("Error opening file: %s\n", filename);
		return 1;
	}
	int length = sizeof(k) / sizeof(k[0]);
	printf("length %i k: %i, k0: %i\n",length,sizeof(k), sizeof(k[0]) );
	fwrite(k, sizeof(struct kanji), 1, data);
	fclose(data);

	return 0;
}
