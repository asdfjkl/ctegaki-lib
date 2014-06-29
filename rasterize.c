#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "kanji.h"
#include "math_ext.h"
#include "globals.h"
#include "distance.h"

void reverse_stroke(point *stroke,int offset,int upto) {
    point *temp = (point*) malloc((upto-offset)*sizeof(point));
    for(int i=offset;i<=upto;i++) {
        point ti;
        ti.x = stroke[i].x;
        ti.y = stroke[i].y;
        temp[i-offset] = ti;
    }
    for(int i=offset;i<=upto;i++) {
        stroke[i].x = temp[upto-i].x;
        stroke[i].y = temp[upto-i].y;
    }
    free(temp);
}

// test case for reverse_stroke
void test_rev_stroke() {
    point p1;
    point p2;
    point p3;
    point p4;
    point p5;
    p1.x = 1;
    p1.y = 1;
    p2.x = 2;
    p2.y = 2;
    p3.x = 3;
    p3.y = 3;
    p4.x = 4;
    p4.y = 4;
    p5.x = 5;
    p5.y = 5;
    point *arr = (point*) malloc(sizeof(point)*5);
    arr[0] = p1;
    arr[1] = p2;
    arr[2] = p3;
    arr[3] = p4;
    arr[4] = p5;
    for(int i=0;i<5;i++) {
        printf("(%i,%i) ",arr[i].x,arr[i].y);
    }
    printf("\n");
    reverse_stroke(arr,1,4);
    
    for(int i=0;i<5;i++) {
        printf("(%i,%i) ",arr[i].x,arr[i].y);
    }
    printf("\n");
}



// Bresenham's line algorithm
// if simulate is true, just returns
// the number of points that the algorithm
// would generate
// if simulate is false, creates a list of 
// points between src, and dest, and stores them
// in *line beginning at offset
int plot2d(point src, point dest, bool simulate, int offset, point *stroke) {
    int cnt = 0;
    int stroke_idx = offset;
    
    int x0 = src.x;
    int x1 = dest.x;
    int y0 = src.y;
    int y1 = dest.y;
    bool steep = abs(y1 - y0) > abs(x1 - x0);
    // in our case we have to make sure that Bresenham's algo
    // does not reverse the stroke direction - if points are
    // added from dest to src, then reverse at the end
    bool reverse = false;
    int pos = direction(src, dest);
    if ( (pos == RUP && steep) ||
            (pos == LDWN && !steep) || pos == LUP || pos == L || pos == UP) {
        reverse = true;
    }
    if (steep) {
        int temp = x0;
        x0 = y0;
        y0 = temp;
        temp = x1;
        x1 = y1;
        y1 = temp;
    }
    if (x0 > x1) {
        int temp = x0;
        x0 = x1;
        x1 = temp;
        temp = y0;
        y0 = y1;
        y1 = temp;
    }
    int deltax = x1 - x0;
    int deltay = abs(y1 - y0);
    int error = deltax / 2;
    int ystep;
    int y = y0;
    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }
    // TStroke rast = new TStroke();
    for (int x = x0; x <= x1; x++) {
        if (steep) {
            cnt++;
            if(!simulate) {
                point p;
                p.x = y;
                p.y = x;
                // printf("stroke_idx, steep:%i\n",stroke_idx);
                stroke[stroke_idx] = p;
                stroke_idx++;
            }
        } else {
            cnt++;
            if(!simulate) {
                point p;
                p.x = x;
                p.y = y;
                // printf("stroke_idx, else:%i\n",stroke_idx);
                stroke[stroke_idx] = p;
                stroke_idx++;
            }
        }
        error = error - deltay;
        if (error < 0) {
            y = y + ystep;
            error = error + deltax;
        }
    }
    if(!simulate && reverse) {
      // reverse_stroke expects: stroke, from(incl), to(incl).
      // cnt was increased after adding the point, so it's one ahead
      //  printf("reversee\n");
      reverse_stroke(stroke,offset,offset+cnt-1);
    }
    return cnt;
}

// expects a kanji with some strokes
// fills between each two points of a stroke
// intermediate "filler" points using
// bresenhams line algo to increase the
// resolution
kanji raster(kanji k) {
    // print_kanji(k);
    kanji k_raster;
    k_raster.kji = k.kji;
    k_raster.c_strokes = 0;
    k_raster.c_points = 0;
    k_raster.xy = 0;
    for(int i=0;i<k.c_strokes;i++) {
        // plot_dists_i stores in i how many points will exist 
        // between stroke_i[j], stroke_i[j-1]
        int *plot_dists_i = (int*) malloc(sizeof(int)*k.c_points[i]);
        int new_size_of_i = 0;
        point *stroke_i = k.xy[i];
        // for each two consecutive points, count how many points
        // will be needed, store that into plot_dists_i
        // count overall points, and store them in new_size_of_i
        for(int j=0;j<k.c_points[i]-1;j++) {
            point *dummy;            
            int cnt_j_jplus1 = plot2d(stroke_i[j],stroke_i[j+1],true,0,dummy);
            if(j==0) {              
                plot_dists_i[j] = cnt_j_jplus1;    
            } else {
                plot_dists_i[j] = plot_dists_i[j-1] + cnt_j_jplus1;
            }
            new_size_of_i += cnt_j_jplus1;
        }
        // 
        // printf("looped, new_size: %i\n",new_size_of_i);
        point *new_stroke = (point*) malloc(sizeof(point) * new_size_of_i);
        // printf("ok\n");
        for(int j=0;j<k.c_points[i]-1;j++) {
            if(j==0) {
               // printf("calling plot2d: plot_dists_i[j]=%i\n",0);
               plot2d(stroke_i[j],stroke_i[j+1],false,0,new_stroke);
            } else {
               // printf("calling plot2d: plot_dists_i[j]=%i\n",plot_dists_i[j-1]);
               plot2d(stroke_i[j],stroke_i[j+1],false,plot_dists_i[j-1],new_stroke);
            }
        }
        // printf("add stroke\n");
        add_stroke(&k_raster,new_stroke,new_size_of_i);
    }
    // print_kanji(k_raster);
    return k_raster;
}

void test_plot2d() {
    
    point p0;
    point p1;
    point p2;
    point p3;
    p0.x = p0.y = 0;
    p1.x = 0; p1.y = 20;
    p2.x = 20; p2.y = 0;
    p3.x = 20; p3.y = 20;
    int numbers = -1;
    point *strokes;
    numbers = plot2d(p3, p2, true, 0, strokes);
    printf("numbers needed:%i\n",numbers);
    strokes = (point*) malloc(sizeof(point) *numbers);
    numbers = plot2d(p2,p3,false,0,strokes);
    for(int i=0;i<numbers;i++) {
        printf("(%i,%i) ",strokes[i].x,strokes[i].y);
    }
    printf("\n");
}