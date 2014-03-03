/* 
 * File:   distance.h
 * Author: user
 *
 * Created on 24. November 2013, 18:43
 */

#include "kanji.h"


#ifndef DISTANCE_H
#define	DISTANCE_H

int endpoint(kanji a, int idx_a, kanji b, int idx_b);

int initial(kanji a, int idx_a, kanji b, int idx_b);

int whole(kanji a, int idx_a, kanji b, int begin, int end);

void testWhole();

#ifdef	__cplusplus
extern "C" {
#endif    
#ifdef	__cplusplus
}
#endif

#endif	/* DISTANCE_H */