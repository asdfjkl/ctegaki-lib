#include<stdio.h>
#include "ezxml.h"
#include "xml.h"
#include "binary.h"
#include "kanji.h"


int main()
{
	char test[] = "abc";
	char test1[]  = "cd";
	kanji k;
	read_xml_file("4e86.xml", &k, test);
	// kanji ka[1] = { k }; 
	// int j = write_bin_file(ka, "data");
	// printf("hex: %s, %i\n",test, k.xy[0][0].x);
	printf("loaded\n");
	print_kanji(&k);
	size_t buf_len = get_size(&k);
	char* buffer = (char *)malloc(buf_len);
	printf("serializing...\n");
	serialize_kanji(&k, buffer);
	// printf("%s\n",*buffer);
	printf("done, buf_len: %i\n",buf_len);
	FILE* fp = fopen("data.dat", "wb+");
	if(fp == NULL) { 
		printf ("error opening file\n"); 
		return 1;
	}
	// todo: some error handling when writing to file
	fwrite(buffer, buf_len, 1, fp);
	// don't forget to take out the garbage
	printf("wrote buffer to file\n");
	fclose(fp);
	// free(buffer);
	return 0;
}
