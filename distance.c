#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "math_ext.h"
#include "kanji.h"
#include "globals.h"

// returns the direction between two points
// direction is coded by an int (see globals.h)
int direction(point a, point b) {

    if (b.x > a.x) { // b is right of a 
        if (b.y > a.y) { // b is below of a
            return RDWN;
        }
        if (b.y < a.y) { // b is above of a
            return RUP;
        }
        if (b.y == a.y) {
            return R;
        }
    }
    if (b.x < a.x) { // b is left of a
        if (b.y > a.y) { // b is below of a
            return LDWN;
        }
        if (b.y < a.y) { // b is above of a
            return LUP;
        }
        if (b.y == a.y) {
            return L;
        }
    }
    if (b.x == a.x) { // same on x
        if (b.y > a.y) { // b is below of a
            return DWN;
        }
        if (b.y < a.y) { // b is above of a
            return UP;
        }
        if (b.y == a.y) {
            return ID;
        }
    }
    return ID;
}


// int min(int a, int b) { return (a < b) ? a : b; }

int endpoint(kanji a, int idx_a, kanji b, int idx_b) {
    
    int d_xs = abs(a.xy[idx_a][0].x - b.xy[idx_b][0].x);
    int d_ys = abs(a.xy[idx_a][0].y - b.xy[idx_b][0].y);
    
    int last_a = a.c_points[idx_a]-1;
    int last_b = b.c_points[idx_b]-1;
    
    int d_xe = abs(a.xy[idx_a][last_a].x - b.xy[idx_b][last_b].x);
    int d_ye = abs(a.xy[idx_a][last_a].y - b.xy[idx_b][last_b].y);
    
    return ((d_xs + d_ys + d_xe + d_ye)/2);
    
}

int endpoint_conc(kanji a, int idx_a, kanji b, int begin, int end) {
    
    int d_xs = abs(a.xy[idx_a][0].x - b.xy[begin][0].x);
    int d_ys = abs(a.xy[idx_a][0].y - b.xy[begin][0].y);
    
    int last_a = a.c_points[idx_a]-1;
    int last_b = b.c_points[end]-1;
    
    int d_xe = abs(a.xy[idx_a][last_a].x - b.xy[end][last_b].x);
    int d_ye = abs(a.xy[idx_a][last_a].y - b.xy[end][last_b].y);
    
    return ((d_xs + d_ys + d_xe + d_ye)/2);
    
}

int initial(kanji a, int idx_a, kanji b, int idx_b) {
		
    int m = a.c_points[idx_a];
    int n = b.c_points[idx_b];
	if(m < n) {
		int temp = n;
		n = m;
		m = temp;
	}
	int dist = 0;
	for(int i=0;i<n;i++) {
		dist += (abs(a.xy[idx_a][i].x - b.xy[idx_b][i].x) +
                 abs(a.xy[idx_a][i].y - b.xy[idx_b][i].y));
	}
	return dist * (m*10/n);		
}

int tau_of_i(int i, int m, int n) {
    return (((m)/(n))*(i));
}

/*
 * parameters: 
 * a.xy[idx_a] is the first stroke
 * the second stroke is the concatenation of 
 *   b.xy[begin], b.xy[begin+1] ... , b.xy[begin+j]
 * len0 = len_b
 * len1 = len_a
 * 
 * expects that kanji a and kanji b are not empty, i.e.
 * contain at least one valid stroke
 */
int whole(kanji a, int idx_a, kanji b, int begin, int end) {

    int dist = 0;
    
    // total length (number of points) of the combined stroke of b
    int len_b = 0;
    for (int i = begin; i <= end; i++) {
        len_b += b.c_points[i];
    }
    
    // length of the single stroke of a
    int len_a = a.c_points[idx_a];
    
    if (len_b <= len_a) {
        // The combined stroke of b has less points than the single stroke of a
        // printf("combined smaller than single\n");
        int i = begin;
        int j = 0;
        int combined_index = 0; // virtual index of the combined stroke
        // b.xy[i][j] corresponds to the combined_index' position of the combined stroke
        while (i <= end) {
            // tau calculates the index of b, to which the current
            // virtual index of the combined stroke is mapped to
            int tau = tau_of_i(combined_index, len_a, len_b);
            dist += abs(a.xy[idx_a][tau].x - b.xy[i][j].x);
            dist += abs(a.xy[idx_a][tau].y - b.xy[i][j].y);
            combined_index++;
            // if we haven't reached the end of the i's stroke, go to the next point
            // otherwise jump to the next stroke, and choose the zero's point
            if (j < b.c_points[i] - 1) {
                j++;
            } else {
                i++;
                j = 0;
            }
        }
    } else {
        // The single stroke of a has less points than the combined stroke of b
        // printf("combined larger than single\n");
        
        // k holds the index of the smaller stroke
        for (int k = 0; k < len_a; k++) {
            // k is mapped to the tau's index of the combined stroke of b
            int tau = tau_of_i(k, len_b, len_a);
            // convert the combined index tau to array position of b
            // by decreasing tau. At the end [j][tau] corresponds to
            // the tau's position (current value of tau) of the combined index
            int j = 0;
            // as long as tau is not a valid point
            while(tau > b.c_points[begin+j] -1 ) {
                // decrease tau by the number of points on the begin+j's stroke
                tau -= b.c_points[begin+j];
                // go to the next stroke
                j++;
            }
            dist += abs(a.xy[idx_a][k].x - b.xy[begin+j][tau].x);
            dist += abs(a.xy[idx_a][k].y - b.xy[begin+j][tau].y);
        }
    }
    return (dist * 10) / (min(len_b, len_a));
}


int whole_delta(kanji a, int idx_a, kanji b, int begin, int end) {

    int dist = 0;
    
    // total length (number of points) of the combined stroke of b
    int len_b = 0;
    for (int i = begin; i <= end; i++) {
        len_b += b.c_points[i];
    }
    
    // length of the single stroke of a
    int len_a = a.c_points[idx_a];
    point last_of_a;
    point last_of_b;
    last_of_a.x = last_of_a.y = 0;
    last_of_b.x = last_of_b.y = 0;
    
    if (len_b <= len_a) {
        // The combined stroke of b has less points than the single stroke of a
        // printf("combined smaller than single\n");
        int i = begin;
        int j = 0;
        int combined_index = 0; // virtual index of the combined stroke
        // b.xy[i][j] corresponds to the combined_index' position of the combined stroke
        while (i <= end) {
            // tau calculates the index of b, to which the current
            // virtual index of the combined stroke is mapped to
            int tau = tau_of_i(combined_index, len_a, len_b);
            
            int delta_x_a = a.xy[idx_a][tau].x - last_of_a.x;
            int delta_y_a = a.xy[idx_a][tau].y - last_of_a.y;
            
            int delta_x_b = b.xy[i][j].x - last_of_b.x;
            int delta_y_b = b.xy[i][j].y - last_of_b.y;
            
            dist += (abs(delta_x_a - delta_x_b) + abs(delta_y_a - delta_y_b));
            
            last_of_a.x = a.xy[idx_a][tau].x;
            last_of_a.y = a.xy[idx_a][tau].y;
            last_of_b.x = b.xy[i][j].x;
            last_of_b.y = b.xy[i][j].y;
            
            combined_index++;
            // if we haven't reached the end of the i's stroke, go to the next point
            // otherwise jump to the next stroke, and choose the zero's point
            if (j < b.c_points[i] - 1) {
                j++;
            } else {
                i++;
                j = 0;
            }
        }
    } else {
        // The single stroke of a has less points than the combined stroke of b
        // printf("combined larger than single\n");
        
        // k holds the index of the smaller stroke
        for (int k = 0; k < len_a; k++) {
            // k is mapped to the tau's index of the combined stroke of b
            int tau = tau_of_i(k, len_b, len_a);
            // convert the combined index tau to array position of b
            // by decreasing tau. At the end [j][tau] corresponds to
            // the tau's position (current value of tau) of the combined index
            int j = 0;
            // as long as tau is not a valid point
            while(tau > b.c_points[begin+j] -1 ) {
                // decrease tau by the number of points on the begin+j's stroke
                tau -= b.c_points[begin+j];
                // go to the next stroke
                j++;
            }
            int delta_x_a = a.xy[idx_a][k].x - last_of_a.x;
            int delta_y_a = a.xy[idx_a][k].y - last_of_a.y;
            
            int delta_x_b = b.xy[begin+j][tau].x - last_of_b.x;
            int delta_y_b = b.xy[begin+j][tau].y - last_of_b.y;
            
            dist += (abs(delta_x_a - delta_x_b) + abs(delta_y_a - delta_y_b));
            
            last_of_a.x = a.xy[idx_a][k].x;
            last_of_a.y = a.xy[idx_a][k].y;
            last_of_b.x = b.xy[begin+j][tau].x;
            last_of_b.y = b.xy[begin+j][tau].y;
            
        }
    }
    return (dist * 10) / (min(len_b, len_a));
}



/*
 * todo: implement whole_whole mit direction
 */

/*
 * test cases for the distance calculation whole()
 *
 */
void testWhole() {

    kanji combined;
    combined.c_strokes = 0;
    combined.c_points = 0;
    combined.xy = 0;

    point p0;
    p0.x = 0;
    p0.y = 0;
    
    point p1;
    p1.x = 1;
    p1.y = 1;
    
    point p2;
    p2.x = 2;
    p2.y = 2;
    
    point p3;
    p3.x = 3;
    p3.y = 3;
    
    point p4;
    p4.x = 4;
    p4.y = 4;
    
    point p5;
    p5.x = 5;
    p5.y = 5;
    
    point p6;
    p6.x = 6;
    p6.y = 6;
    
    point p7;
    p7.x = 7;
    p7.y = 7;
    
    point p8;
    p8.x = 8;
    p8.y = 8;
    
    point p9;
    p9.x = 9;
    p9.y = 9;
    
    point p10;
    p10.x = 10;
    p10.y = 10;
    
    point p11;
    p11.x = 11;
    p11.y = 11;
    
    point p12;
    p12.x = 12;
    p12.y = 12;
    
    point p13;
    p13.x = 13;
    p13.y = 13;
    
    point p14;
    p14.x = 14;
    p14.y = 14;
    
    point p15;
    p15.x = 15;
    p15.y = 15;

    point p16;
    p16.x = 16;
    p16.y = 16;
    
    point zero[] = { p0, p1, p2, p3, p4 };            
    point one[] = { p0, p1, p2, p3 };
    point two[] = { p0, p1, p2, p3, p4, p5, p6 };
    
    add_stroke(&combined, zero, 5);
    add_stroke(&combined, one, 4);
    add_stroke(&combined, two, 7);
    
    kanji l4;
    l4.c_strokes = 0;
    l4.c_points = 0;
    l4.xy = 0;
    add_stroke(&l4,one,4);
    
    point six[] = { p0, p1, p2, p3, p4, p5 };
    kanji l6;
    l6.c_strokes = 0;
    l6.c_points = 0;
    l6.xy = 0;
    add_stroke(&l6,six,6);
    
    printf("\nGnerated combined, l4, l6:");
    print_kanji(combined);
    print_kanji(l4);
    print_kanji(l6);
    
    point ten[] = { p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 };
    kanji l10;
    l10.c_strokes = 0;
    l10.c_points = 0;
    l10.xy = 0;
    add_stroke(&l10,ten,10);
    
    point twelve[] = { p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 };
    kanji l12;
    l12.c_strokes = 0;
    l12.c_points = 0;
    l12.xy = 0;
    add_stroke(&l12,twelve,12);
    
    point sevten[] = {p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13,p14,p15,p16 };
    kanji l17;
    l17.c_strokes = 0;
    l17.c_points = 0;
    l17.xy = 0;
    add_stroke(&l17,sevten,17);
    
   
    printf("begin=0, end =1, l4\n");
    int res = whole(l4, 0, combined, 0, 1);
    printf("res: %i\n",res);
        
    printf("begin=0, end = 1, l10\n");
    res = whole(l10, 0, combined, 0, 1);
    printf("res: %i\n",res);
        
    printf("begin=0, end = 2, l12\n");
    res = whole(l12, 0, combined, 0, 2);
    printf("res: %i\n",res);
        
    printf("begin=0, end = 2, l17\n");
    res = whole(l17, 0, combined, 0, 2);
    printf("res: %i\n",res);
    
    printf("begin=1, end = 2, l6\n");
    res = whole(l6, 0, combined, 1, 2);
    printf("res: %i\n",res);
    
    printf("begin=1, end = 2, l12\n");
    res = whole(l12, 0, combined, 1, 2);
    printf("res: %i\n",res);
 
}

