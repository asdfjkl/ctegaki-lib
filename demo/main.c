#include "ctegaki.h"
#include <wchar.h>
#include <locale.h>

int main() {
	setlocale(LC_ALL, "en_US.UTF-8");
	kanjis data = load_data("data.dat");
	kanji k;
	point p00;
	point p01;
	point p11;
	point p10;

	p00.x = 0;
	p00.y = 0;
	// point stroke1[] = { p00, p00, p00  };
        point* stroke1 = (point*) malloc(3*sizeof(point));
	stroke1[0] = p00;
	stroke1[1] = p00;
	stroke1[1] = p00;
	printf("ok");
	printf("\n");

	add_stroke(&k,stroke1,3);
	printf("ok");
	printf("\n");
	wchar_t *results = recognize_kanji(k,data);
	for(int i=0;i<2;i++) { 
		wprintf(L"%lc ",results[i]);
	}
	printf("\n");
}
