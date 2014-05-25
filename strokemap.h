#ifndef STROKEMAP_H
#define	STROKEMAP_H

struct smap {
    int *m;
    int length;
};

void print_smap(smap sm);
smap make_smap(int len);
smap get_initial_map(kanji larger, kanji smaller,
                       int (*dist) (kanji, int, kanji, int));

#endif	/* STROKEMAP_H */

