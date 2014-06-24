#include "math.h"

int abs(int x) {
    if(x<0) { 
        return -x;
    } else { 
        return x;
    }
}

int max(int a, int b) {
    if(a < b) {
        return b;
    } else {
        return a;
    }
}

int min(int a, int b) {
    if(a < b) {
        return a;
    } else {
        return b;
    }
}


int manhatten(int x0, int y0, int x1, int y1) {
    int xdist = abs(x1-x0);
    int ydist = abs(y1-y0);
    return xdist + ydist;
}

float euclid(int x0, int y0, int x1, int y1) {
    int xdist = abs(x1-x0);
    int ydist = abs(y1-y0);
    return sqrtf((float) (xdist*xdist) + (float) (ydist*ydist));
}
