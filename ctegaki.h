/* 
 * File:   main.h
 * Author: user
 *
 * Created on 13. September 2014, 17:52
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include<stdio.h>
#include "ezxml.h"
#include "xml.h"
#include "binary.h"
#include "kanji.h"
#include "kanjis.h"
#include "globals.h"
#include "normalize.h"
#include <wchar.h>
#include <locale.h>
#include "distance.h"
#include "strokemap.h"
#include "rasterize.h"
#include "recognizer.h"
#include "tinydir.h"

extern wchar_t* recognize_kanji(kanji unknown, kanjis dataset);
extern kanjis load_data(char* filename);


#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

