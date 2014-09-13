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

wchar_t* recognize_kanji(kanji unknown, kanjis dataset) {
        kanji rastered = raster(unknown);
        moment(rastered);
        kanji rastered_moment = raster(rastered);
        kanji features = extract_features(rastered_moment, INTERVAL);
        return recognize(features, dataset);
}

kanjis load_data(char* filename) {
        kanjis data = init("data.dat");
        return data;
}
