#include <stdio.h>
#include <graphics.h>
#include <math.h>

void draw_screw(double screw_x, double screw_y, double screw_r, double angle) {
	
	ege_setpattern_lineargradient(
		screw_x - screw_r, screw_y - screw_r, EGEARGB(200, 255, 255, 255),
		screw_x + screw_r, screw_y + screw_r, EGEARGB(0xff, 0x1b, 0x20, 0x25)
		);
	ege_fillellipse(
		screw_x - screw_r * 0.97, screw_y - screw_r * 1.03, 2 * screw_r * 1, 2 * screw_r * 1
		);
	
	
	ege_setpattern_lineargradient(
		screw_x - screw_r, screw_y - screw_r, EGEARGB(200, 0, 0, 0),
		screw_x + screw_r, screw_y + screw_r, EGEARGB(0xff, 0x1b, 0x20, 0x25)
		);
	ege_fillellipse(
		screw_x - screw_r * 1.03, screw_y - screw_r * 0.97, 2 * screw_r * 1, 2 * screw_r * 1
		);
	
	// 倒数第二层
	ege_setpattern_lineargradient(
		screw_x - screw_r, screw_y - screw_r, EGEARGB(0XFF, 0X1F, 0X23, 0X2C),
		screw_x + screw_r, screw_y + screw_r, EGEARGB(0XFF, 0X17, 0X1A, 0X24)
		);
	ege_fillellipse(
		screw_x - screw_r, screw_y - screw_r, 2 * screw_r, 2 * screw_r
		);
	
	// 绘制中间螺丝
	angle = -angle;
	angle = angle * PI / 180;
	
	double x01 = -screw_r * 0.7, y01 = -screw_r * 0.2;
	double x02 = -screw_r * 0.7, y02 = +screw_r * 0.2;
	double x03 = +screw_r * 0.7, y03 = +screw_r * 0.2;
	double x04 = +screw_r * 0.7, y04 = -screw_r * 0.2;
	
	ege_setpattern_lineargradient(
		x01 * cos(angle) - y01 * sin(angle) + screw_x, x01 * sin(angle) + y01 * cos(angle) + screw_y, BLACK,
		x03 * cos(angle) - y03 * sin(angle) + screw_x, x03 * sin(angle) + y03 * cos(angle) + screw_y, BLACK
		);
	ege_point polypoints1[4] = {
		{x01 * cos(angle) - y01 * sin(angle) + screw_x,x01 * sin(angle) + y01 * cos(angle) + screw_y},// 左上
		{x02 * cos(angle) - y02 * sin(angle) + screw_x,x02 * sin(angle) + y02 * cos(angle) + screw_y},// 右上
		{x03 * cos(angle) - y03 * sin(angle) + screw_x,x03 * sin(angle) + y03 * cos(angle) + screw_y},// 右下
		{x04 * cos(angle) - y04 * sin(angle) + screw_x,x04 * sin(angle) + y04 * cos(angle) + screw_y} // 左下
	};
	ege_fillpoly(4, polypoints1);
	
	
	double x11 = -screw_r * 0.2, y11 = -screw_r * 0.7;
	double x12 = -screw_r * 0.2, y12 = +screw_r * 0.7;
	double x13 = +screw_r * 0.2, y13 = +screw_r * 0.7;
	double x14 = +screw_r * 0.2, y14 = -screw_r * 0.7;
	
	ege_setpattern_lineargradient(
		x11 * cos(angle) - y11 * sin(angle) + screw_x, x11 * sin(angle) + y11 * cos(angle) + screw_y, BLACK,
		x13 * cos(angle) - y13 * sin(angle) + screw_x, x13 * sin(angle) + y13 * cos(angle) + screw_y, BLACK
		);
	ege_point polypoints2[4] = {
		{x11 * cos(angle) - y11 * sin(angle) + screw_x,x11 * sin(angle) + y11 * cos(angle) + screw_y},// 左上
		{x12 * cos(angle) - y12 * sin(angle) + screw_x,x12 * sin(angle) + y12 * cos(angle) + screw_y},// 右上
		{x13 * cos(angle) - y13 * sin(angle) + screw_x,x13 * sin(angle) + y13 * cos(angle) + screw_y},// 右下
		{x14 * cos(angle) - y14 * sin(angle) + screw_x,x14 * sin(angle) + y14 * cos(angle) + screw_y} // 左下
	};
	ege_fillpoly(4, polypoints2);
	
	
	// 螺丝中间菱形
	double x21 = -screw_r * 0.53, y21 = 0;
	double x22 = 0, y22 = +screw_r * 0.53;
	double x23 = +screw_r * 0.53, y23 = 0;
	double x24 = 0, y24 = -screw_r * 0.53;
	setcolor(BLACK);
	ege_setpattern_lineargradient(
		x21 * cos(angle) - y21 * sin(angle) + screw_x, x21 * sin(angle) + y21 * cos(angle) + screw_y, BLACK,
		x23 * cos(angle) - y23 * sin(angle) + screw_x, x23 * sin(angle) + y23 * cos(angle) + screw_y, BLACK
		);
	ege_point polypoints5[5] = {
		{x21 * cos(angle) - y21 * sin(angle) + screw_x,x21 * sin(angle) + y21 * cos(angle) + screw_y},// 上
		{x22 * cos(angle) - y22 * sin(angle) + screw_x,x22 * sin(angle) + y22 * cos(angle) + screw_y},// 右
		{x23 * cos(angle) - y23 * sin(angle) + screw_x,x23 * sin(angle) + y23 * cos(angle) + screw_y},// 下
		{x24 * cos(angle) - y24 * sin(angle) + screw_x,x24 * sin(angle) + y24 * cos(angle) + screw_y},//左
		{x21 * cos(angle) - y21 * sin(angle) + screw_x,x21 * sin(angle) + y21 * cos(angle) + screw_y}
	};
	ege_fillpoly(5, polypoints5);
}
