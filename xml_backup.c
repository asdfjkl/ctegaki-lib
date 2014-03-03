#include<stdio.h>
#include "ezxml.h"
int main()
{
	int kanji[200][2];
	int i = 0;

	int8_t test = 8;
	ezxml_t f1 = ezxml_parse_file("4e86.xml"), stroke, point;
	const char *teamname;
 
	for (stroke = ezxml_child(f1, "stroke"); stroke; stroke = stroke->next) {
    	printf("new stroke\n");
    	for (point = ezxml_child(stroke, "point"); point; point = point->next) {
        	kanji[i][0] = atoi(ezxml_attr(point,"x"));
		kanji[i][1] = atoi(ezxml_attr(point,"y"));
		i++; 
                // printf("%i",i);
		// printf("%s \n", ezxml_attr(point,"x"));
    	}
	}
	ezxml_free(f1);
	for(int j = 0;j<50;j++) {
	 	printf("j: %i, x: %i, y: %i\n", j, kanji[j][0], kanji[j][1]);
	} 


	return 0;
}
