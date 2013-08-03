#include<stdio.h>
#include "ezxml.h"
#include "kanji.h"
#include <stdint.h>

int count_children(ezxml_t node, char name[]) 
{
	int i=0;
	ezxml_t child;
	for(child = ezxml_child(node, name); child; child = child->next) {
		i++;
	}
	return i;
}

void read_xml_file(char filename[], kanji* k, char utf_hex[])
{
	ezxml_t xml_kanji = ezxml_parse_file("4e86.xml"), xml_stroke, xml_point;
	
	int strokes = count_children(xml_kanji, "stroke");
	point **temp;
	temp = (point**) malloc(strokes*sizeof(point*));
 	
	int i=0;
	(*k).c_strokes = strokes;
	(*k).c_points = (int*) malloc(strokes*sizeof(int));
	for (xml_stroke = ezxml_child(xml_kanji, "stroke"); xml_stroke; xml_stroke = xml_stroke->next) {
        int points = count_children(xml_stroke, "point");  
        temp[i] = (point*) malloc(points*sizeof(point));
    	(*k).c_points[i] = points;
       	int j=0;
    	for (xml_point = ezxml_child(xml_stroke, "point"); xml_point; xml_point = xml_point->next) {
			point p;
			p.x =  atoi(ezxml_attr(xml_point,"x"));
			p.y = atoi(ezxml_attr(xml_point,"y"));
			temp[i][j] = p;
    		j++; 
    	}
    	i++;
	}
	ezxml_free(xml_kanji);
	(*k).xy = temp;
	utf_hex = "abcdefg";
	// print_kanji(k);
}
