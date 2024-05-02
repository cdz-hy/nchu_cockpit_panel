#include <stdio.h>
#include <graphics.h>
#include <math.h>

extern int G_light;

void draw_light(double x, double y, double r){
	
	//光照效果
	ege_point point_tmp = {x, y};
	ege_setpattern_ellipsegradient(point_tmp, EGEARGB(0x00,0x00,0x00,0x00), x - r, y - r, 2 * r, 2 * r, EGEARGB(G_light / 6,0xd9,0x6c,0x21)); // EGEARGB(G_light / 4,0xb5,0x5e,0x51)
	ege_fillellipse(x - r, y - r, 2 * r, 2 * r);	
	ege_setpattern_none();
	
}
