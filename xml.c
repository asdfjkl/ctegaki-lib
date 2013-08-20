#include<stdio.h>
#include "ezxml.h"
#include "kanji.h"
#include <stdint.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

int count_children(ezxml_t node, char name[]) 
{
	int i=0;
	ezxml_t child;
	for(child = ezxml_child(node, name); child; child = child->next) {
		i++;
	}
	return i;
}

void read_xml_file(char filename[], kanji* k) {

    ezxml_t xml_kanji = ezxml_parse_file(filename), xml_stroke, xml_point;

    int strokes = count_children(xml_kanji, (char*) "stroke");
    point **temp;
    temp = (point**) malloc(strokes * sizeof (point*));

    int i = 0;
    (*k).c_strokes = strokes;
    (*k).c_points = (int*) malloc(strokes * sizeof (int));

    for (xml_stroke = ezxml_child(xml_kanji, "stroke"); xml_stroke; xml_stroke = xml_stroke->next) {
        int points = count_children(xml_stroke, (char*) "point");
        temp[i] = (point*) malloc(points * sizeof (point));
        (*k).c_points[i] = points;
        int j = 0;
        for (xml_point = ezxml_child(xml_stroke, "point"); xml_point; xml_point = xml_point->next) {
            point p;
            p.x = atoi(ezxml_attr(xml_point, "x"));
            p.y = atoi(ezxml_attr(xml_point, "y"));
            temp[i][j] = p;
            j++;
        }
        i++;
    }

    for (xml_stroke = ezxml_child(xml_kanji, "unicode"); xml_stroke; xml_stroke = xml_stroke->next) {
        char* utf_hex = xml_stroke->txt;
        wchar_t wc = strtol(utf_hex, NULL, 16);
        (*k).kji = wc;
        // setlocale(LC_ALL, "de_DE.UTF-8");
        // wprintf(L"saved wchar: %lc \n", (*k).kji);
        /* 
        printf("utf8: %s\n",utf_hex);
        wchar_t b = '\u4e86';
        wprintf(L"char: %lc\n",b);
        //char f[] = "0444";
        //printf(strcat("\u",f));
        wchar_t *wstr = L"\u4F60\u597D";
        wchar_t wc = strtol("4e86", NULL, 16);
              
        setlocale(LC_ALL, "de_DE.UTF-8");
        wprintf(L"char2: %lc \n", wc);
         */
    }
    ezxml_free(xml_kanji);
    (*k).xy = temp;
    // utf_hex = "abcdefg";
    // print_kanji(k);
}
