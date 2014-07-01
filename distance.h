/* 
 * File:   distance.h
 * Author: user
 *
 * Created on 24. November 2013, 18:43
 */

#include "kanji.h"


#ifndef DISTANCE_H
#define	DISTANCE_H

int direction(point a, point b);

int endpoint(kanji a, int idx_a, kanji b, int idx_b);

int endpoint_conc(kanji a, int idx_a, kanji b, int begin, int end);

int initial(kanji a, int idx_a, kanji b, int idx_b);

int whole(kanji a, int idx_a, kanji b, int begin, int end);

int whole_delta(kanji a, int idx_a, kanji b, int begin, int end);

void testWhole();

#ifdef	__cplusplus
extern "C" {
#endif    
#ifdef	__cplusplus
}
#endif

#endif	/* DISTANCE_H */