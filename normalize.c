#include "globals.h"
#include "kanji.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>

struct bbox{
	int x0;
	int y0;
	int x1;
	int y1;
	int width;
	int heigth;
};

bbox make_bbox(kanji k) {
    	bbox b;    
	b.x0 = MAXSIZE;
	b.x1 = 0;
	b.y0 = MAXSIZE;
	b.y1 = 0;
	for(int i=0;i<k.c_strokes;i++) {
		for(int j=0;j<k.c_points[i];j++) {
			int x = (int) k.xy[i][j].x;
			int y = (int) k.xy[i][j].y;
                  	if(x < b.x0) { b.x0 = x; }
			if(x > b.x1) { b.x1 = x; }
			if(y < b.y0) { b.y0 = y; }
			if(y > b.y1) { b.y1 = y; }	
		}
	}
        // printf("bb0 %i %i %i %i",b.x0,b.x1,b.y0,b.y1);
        b.heigth = b.y1 - b.y0;
        b.width = b.x1 - b.x0;
        return b;
}

int f_m10(kanji k) {
	int sum=0;
	for(int i=0;i<k.c_strokes;i++) {
		for(int j=0;j<k.c_points[i];j++) {
			sum += k.xy[i][j].x;
		}
	}
	return sum;
}

int f_m01(kanji k) {
	int sum=0;
	for(int i=0;i<k.c_strokes;i++) {
		for(int j=0;j<k.c_points[i];j++) {
			sum += k.xy[i][j].y;
		}
	}
	return sum;
}

int f_m00(kanji k) {
	int all_points = 0;
	for(int i=0;i<k.c_strokes;i++) {
		all_points += k.c_points[i];
	}
	return all_points;
}	
			
int f_mu20(kanji k, int xc) {
	int sum = 0;
	for(int i=0;i<k.c_strokes;i++) {
		for(int j=0;j<k.c_points[i];j++) {
			int diff = k.xy[i][j].x - xc;
			sum += (diff * diff);
		}			
	}
	return sum;
}

int f_mu02(kanji k, int yc) {
	int sum = 0;
	for(int i=0;i<k.c_strokes;i++) {
		for(int j=0;j<k.c_points[i];j++) {
			int diff = k.xy[i][j].y - yc;
			sum += (diff * diff);
		}			
	}
	return sum;
}
	
float aran(int width, int height) {
		
	float r1 = 0.;
		if(height > width) {
		r1 = ((float) width) / ((float) height);
	} else {
		r1 = ((float) height) / ((float) width);
	}	
	float r2 = (float) sqrtf(sinf((M_PI/2.) * r1));
	return r2;
}	
	
void moment_normalize(kanji k, bbox b, int new_w, int new_h) {
	float r2 = aran(b.width, b.heigth);
	// printf("r2: %f\n",r2);
		
	int aran_w = new_w;
	int aran_h = new_h;
	
        if(b.heigth > b.width) {
            	aran_w = (int) (r2 * (float) new_w); 
	} else {
		aran_h = (int) (r2 *(float) new_h);
	}		
	// printf("aran width %i and heigth %i\n", aran_w, aran_h);
	
        
	int x_offset = (new_w - aran_w)/2;
	int y_offset = (new_h - aran_h)/2; 
		
	// printf("xOffset %i and yoffset %i\n",x_offset,y_offset);
	// System.out.println("yOffset: "+yOffset);

	float m00 = (float) f_m00(k);
	float m01 = (float) f_m01(k);
	float m10 = (float) f_m10(k);
		
	// printf("m00: %f m01 %f m10 %f\n",m00,m01,m10);
		
	int xc = (int) (m10/m00);
	int yc = (int) (m01/m00);
		
	// printf("xc: %i + yc %i\n",xc,yc);
		
	int xc_ = aran_w/2;
	int yc_ = aran_h/2;
		
	// printf("xc_: %i + yc %i\n",xc_,yc_);
		
	float mu20 = (float) f_mu20(k, xc);
	float mu02 = (float) f_mu02(k, yc);

	// printf("mu20: %i mu02 %i",mu20,mu02);
				
	// System.out.println("aranWidth"+aranWidth + " rounded "+ ((float)aranWidth ));
	float alpha = ((float) aran_w) / (4 * (float) sqrtf(mu20/m00));
	float beta = ((float) aran_h) / (4 * (float) sqrtf(mu02/m00));
		
	// printf("alpha: %f beta %f",alpha,beta);
		
	for(int i=0;i<k.c_strokes;i++) {
		for(int j=0;j<k.c_points[i];j++) {
			int old_x = k.xy[i][j].x;
			int old_y = k.xy[i][j].y;
			int new_x = (int) (alpha * (old_x - xc) + xc_);
			int new_y = (int) (beta * (old_y - yc) + yc_);
			// avoid distortions
			if(new_x > MAXSIZE) new_x = MAXSIZE;
			if(new_x < 0) new_x = 0;
			if(new_y > MAXSIZE) new_y = MAXSIZE;
			if(new_y < 0) new_y = 0;
			k.xy[i][j].x = new_x;
			k.xy[i][j].y = new_y;
		}
	}		
	// transform_kanji(k,x_offset,y_offset);
}

void linear_normalize(kanji k, int s_old, int offset_x, int offset_y) {
        float old_size = (float) s_old;
        float new_size = (float) MAXSIZE - 10;
        float r = new_size/old_size;
        
        for(int i=0;i<k.c_strokes;i++) {
                for(int j=0;j<k.c_points[i];j++) {
                    int x = k.xy[i][j].x;
                    int y = k.xy[i][j].y;
                    int m = ((int) (r * (float) x)) - offset_x;
                    int n = ((int) (r * (float) y)) - offset_y;
                    k.xy[i][j].x = m;
                    k.xy[i][j].y = n;
                }
        }
        // align on new global size
        bbox b = make_bbox(k);
        int add_x = ((MAXSIZE - b.width)/2)  - b.x0;
        int add_y = ((MAXSIZE - b.heigth)/2)  - b.y0;		
        transform_kanji(k, add_x, add_y);
}

/*
	public static TFigure ln(TFigure f, int s_old, TPoint offset) {
		
		float old_size = (float) s_old;
		float new_size = (float) Globals.SIZE-10;
		float r = new_size / old_size;
		
		TFigure scaled = new TFigure();
		for(int i=0;i<f.size();i++) {
			TStroke si = f.get(i);
			TStroke sn = new TStroke();
			for(int j=0;j<si.size();j++) {
				int x = si.get(j).x;
				int y = si.get(j).y;
				
				int m = ((int) (r * (float) x)) - offset.x;
				int n = ((int) (r* (float) y)) - offset.y;
				
				sn.add(new TPoint(m,n));
			}
			scaled.add(sn);
		}
		// align on new Globals.size		
		BoundingBox bb = new BoundingBox(scaled);
		int add_x = ((Globals.SIZE - bb.width())/2)  - bb.x0;
		int add_y = ((Globals.SIZE - bb.heigth())/2)  - bb.y0;		
		return scaled.transform(add_x, add_y);
		
		
	}
*/

void linear(kanji k) {
    bbox b = make_bbox(k);
    if(b.width > b.heigth) {
        linear_normalize(k,b.width,b.x0,b.y0);
    } else {
        linear_normalize(k,b.heigth,b.x0,b.y0);
    }
}
	
void moment(kanji k) {	
	bbox b = make_bbox(k);
        // printf("b heigth: %i and width %i\n",b.heigth,b.width);
	if(	b.heigth > 3* b.width ||
		b.width > 3* b.heigth) {
           // printf("if\n");
		if(b.width > b.heigth) {
			linear_normalize(k,b.width, b.x0, b.y0);
		} else {
			linear_normalize(k,b.heigth, b.x0, b.y0);
		}
	} else {
		return moment_normalize(k, b, MAXSIZE, MAXSIZE);
	}		
}

