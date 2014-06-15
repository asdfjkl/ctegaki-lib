/* 
 * File:   recognizer.h
 * Author: user
 *
 * Created on 15. Juni 2014, 14:53
 */

#ifndef RECOGNIZER_H
#define	RECOGNIZER_H

kanjis init(char filename[]);
wchar_t recognize(kanji unknown, kanjis data);

#ifdef	__cplusplus
extern "C" {
#endif

    
#ifdef	__cplusplus
}
#endif

#endif	/* RECOGNIZER_H */

