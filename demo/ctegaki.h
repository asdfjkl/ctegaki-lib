/* 
 * File:   main.h
 * Author: user
 *
 * Created on 13. September 2014, 17:52
 */

#ifndef CTEGAKI_H
#define	CTEGAKI_H

#include "kanji.h"
#include "kanjis.h"
#include <wchar.h>
#include <locale.h>

wchar_t* recognize_kanji(kanji unknown, kanjis dataset);
kanjis load_data(char* filename);

#endif	/* MAIN_H */

