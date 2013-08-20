#include "math.h"

int abs(int x) {
    if(x<0) { 
        return -x;
    } else { 
        return x;
    }
}

int manhatten(int x0, int y0, int x1, int y1) {
    int xdist = abs(x1-x0);
    int ydist = abs(y1-y0);
    
}

float euclid(int x0, int y0, int x1, int y1) {
    int xdist = abs(x1-x0);
    int ydist = abs(y1-y0);
    return sqrtf((float) (xdist*xdist) + (float) (ydist*ydist));
}
