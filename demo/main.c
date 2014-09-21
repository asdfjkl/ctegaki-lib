#include "ctegaki.h"
#include <wchar.h>
#include <locale.h>
#include <stdio.h>

int main() {
	setlocale(LC_ALL, "en_US.UTF-8");
	kanjis data = load_data("data.dat");
	kanji k;
	point p1,p2,p3,p4,p5,p6;
	p1.x = 0;
	p1.y = 0;
	
	p2.x = 50;
	p2.y = 0;
	
	p3.x = 50;
	p3.y = 120;
	
	p4.x = 0;
	p4.y = 120;
	
	p5.x = 0;
	p5.y = 60;
	
	p6.x = 50;
	p6.y = 60;
        point* stroke1 = (point*) malloc(2*sizeof(point));
	stroke1[0] = p1;
	stroke1[1] = p4;
	add_stroke(&k,stroke1,2);
	point* stroke2 = (point*) malloc(3*sizeof(point));
	stroke2[0] = p1;
	stroke2[1] = p2;
	stroke2[2] = p3;
	add_stroke(&k,stroke2,3);
	point* stroke3 = (point*) malloc(2*sizeof(point));
	stroke3[0] = p5;
	stroke3[1] = p6;
	add_stroke(&k,stroke3,2);
	point* stroke4 = (point*) malloc(2*sizeof(point));
	stroke4[0] = p4;
	stroke4[1] = p3;
	add_stroke(&k,stroke4,2);

	wchar_t *results = recognize_kanji(k,data);
	for(int i=0;i<10;i++) { 
		wprintf(L"%lc ",results[i]);
	}
	printf("\n");
}
