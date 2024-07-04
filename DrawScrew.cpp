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

void draw_screw1(double screw_x, double screw_y, double screw_r, double angle) {
	
	ege_setpattern_lineargradient(
		screw_x - screw_r, screw_y - screw_r, EGEARGB(200, 255, 255, 255),
		screw_x + screw_r, screw_y + screw_r, EGEARGB(0xff, 0x1b, 0x20, 0x25)
		);
	ege_fillellipse(
		screw_x - screw_r * 0.98, screw_y - screw_r * 1.02, 2 * screw_r * 1, 2 * screw_r * 1
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
	
	ege_setpattern_none();
}

void draw_screw2(double screw_x, double screw_y, double screw_r, double angle) {

	
	setfillcolor(EGEARGB(200, 0, 0, 0));// 黑色圈-倒数第一层
	ege_fillellipse(
		screw_x - 1.025*screw_r, screw_y - 1.025*screw_r, 2.05 * screw_r, 2.05 * screw_r
		);
	// 底色-倒数第二层
	ege_setpattern_lineargradient(
		screw_x - screw_r, screw_y - screw_r, EGEARGB(0XFF, 0X1F, 0X23, 0X2C),
		screw_x + screw_r, screw_y + screw_r, EGEARGB(0XFF, 0X17, 0X1A, 0X24)
		);
	ege_fillellipse(
		screw_x - screw_r, screw_y - screw_r, 2 * screw_r, 2 * screw_r
		);
	ege_setpattern_none();
	
	setfillcolor(EGEARGB(255, 0, 0, 0));//黑色边（倒数第三层）
	ege_fillellipse(
		screw_x - 0.85*screw_r  , screw_y - 0.85*screw_r, 1.7 * screw_r, 1.7 * screw_r
		);
	
	ege_setpattern_lineargradient(// 最上面一层
		screw_x - 0.83 * screw_r, screw_y - 0.83 * screw_r, EGEARGB(0XFF, 0X12, 0X12, 0X12),
		screw_x + 0.83 * screw_r, screw_y + 0.83 * screw_r, EGEARGB(0XFF, 0X12, 0X12, 0X12)
		);
	ege_fillellipse(
		screw_x - 0.83 * screw_r, screw_y - 0.83 * screw_r, 1.66 * screw_r, 1.66 * screw_r
		);
	ege_setpattern_none();
	
	ege_setpattern_lineargradient(// 上面一层白色遮盖的效果
		screw_x , screw_y - 0.83 * screw_r, EGEARGB(20, 255, 255, 255),
		screw_x , screw_y + 0.83 * screw_r, EGEARGB(0, 255, 255, 255)
		);
	ege_fillellipse(
		screw_x - 0.83 * screw_r, screw_y - 0.83 * screw_r, 1.66 * screw_r, 1.66 * screw_r
		);
	ege_setpattern_none();
	
	// 绘制中间螺丝
	angle = -angle;
	angle = angle * PI / 180;
	
	double x01 = -screw_r * 0.55, y01 = -screw_r * 0.12;
	double x02 = -screw_r * 0.55, y02 = +screw_r * 0.12;
	double x03 = +screw_r * 0.55, y03 = +screw_r * 0.12;
	double x04 = +screw_r * 0.55, y04 = -screw_r * 0.12;
	
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
	
	
	double x11 = -screw_r * 0.12, y11 = -screw_r * 0.55;
	double x12 = -screw_r * 0.12, y12 = +screw_r * 0.55;
	double x13 = +screw_r * 0.12, y13 = +screw_r * 0.55;
	double x14 = +screw_r * 0.12, y14 = -screw_r * 0.55;
	
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
	double x21 = -screw_r * 0.42, y21 = 0;
	double x22 = 0, y22 = +screw_r * 0.42;
	double x23 = +screw_r * 0.42, y23 = 0;
	double x24 = 0, y24 = -screw_r * 0.42;
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

void draw_screw3(double screw_x, double screw_y, double screw_r, double angle) {
	
	
	
	setfillcolor(EGEARGB(150, 0, 0, 0));// 黑色圈-倒数第一层
	ege_fillellipse(
		screw_x- screw_r/4 * 0.5 - 1.025 * screw_r, screw_y - screw_r / 4 * 1.2 - 1.025 * screw_r, 2.05 * screw_r, 2.05 * screw_r
		);
	
	for (double i = screw_r / 4; i > 0; i--) {
		ege_setpattern_lineargradient(
			screw_x - i*0.5 - screw_r, screw_y - i*1.2 - screw_r, EGEARGB(255,11, 13, 18),
			screw_x - i*0.5 + screw_r, screw_y - i*1.2 + screw_r, EGEARGB(255, 11,13,18)
			);
		ege_fillellipse(
			screw_x - i * 0.5 -screw_r, screw_y - i * 1.2 -screw_r, 2 * screw_r, 2 * screw_r
			);
		ege_setpattern_none();
	}
	ege_setpattern_lineargradient(
		screw_x -screw_r, screw_y- screw_r, EGEARGB(255, 31, 35, 44),
		screw_x  + screw_r, screw_y  + screw_r, EGEARGB(255, 23, 26, 36)
		);
	ege_fillellipse(
		screw_x- screw_r, screw_y  - screw_r, 2 * screw_r, 2 * screw_r
		);
	ege_setpattern_none();
	
	
	// 绘制中间螺丝
	angle = -angle;
	angle = angle * PI / 180;
	
	double x01 = -screw_r * 0.55, y01 = -screw_r * 0.12;
	double x02 = -screw_r * 0.55, y02 = +screw_r * 0.12;
	double x03 = +screw_r * 0.55, y03 = +screw_r * 0.12;
	double x04 = +screw_r * 0.55, y04 = -screw_r * 0.12;
	
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
	
	
	double x11 = -screw_r * 0.12, y11 = -screw_r * 0.55;
	double x12 = -screw_r * 0.12, y12 = +screw_r * 0.55;
	double x13 = +screw_r * 0.12, y13 = +screw_r * 0.55;
	double x14 = +screw_r * 0.12, y14 = -screw_r * 0.55;
	
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
	double x21 = -screw_r * 0.42, y21 = 0;
	double x22 = 0, y22 = +screw_r * 0.42;
	double x23 = +screw_r * 0.42, y23 = 0;
	double x24 = 0, y24 = -screw_r * 0.42;
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

void draw_screw4(double screw_x, double screw_y, double screw_r, double angle) {
	
	setfillcolor(EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	ege_fillellipse(screw_x - screw_r, screw_y - screw_r, 2 * screw_r, 2 * screw_r);
	
	setcolor(BLACK);
	setlinewidth(screw_r / 7.5);
	ege_ellipse(screw_x - screw_r/1.2, screw_y - screw_r/1.2, 1.6 * screw_r, 1.6 * screw_r);
	
	// 绘制中间螺丝
	angle = -angle;
	angle = angle * PI / 180;
	
	double x01 = -screw_r * 0.8, y01 = -screw_r * 0.15;
	double x02 = -screw_r * 0.8, y02 = +screw_r * 0.15;
	double x03 = +screw_r * 0.8, y03 = +screw_r * 0.15;
	double x04 = +screw_r * 0.8, y04 = -screw_r * 0.15;
	
	setfillcolor(BLACK);
	ege_point polypoints1[4] = {
		{x01 * cos(angle) - y01 * sin(angle) + screw_x,x01 * sin(angle) + y01 * cos(angle) + screw_y},// 左上
		{x02 * cos(angle) - y02 * sin(angle) + screw_x,x02 * sin(angle) + y02 * cos(angle) + screw_y},// 右上
		{x03 * cos(angle) - y03 * sin(angle) + screw_x,x03 * sin(angle) + y03 * cos(angle) + screw_y},// 右下
		{x04 * cos(angle) - y04 * sin(angle) + screw_x,x04 * sin(angle) + y04 * cos(angle) + screw_y} // 左下
	};
	ege_fillpoly(4, polypoints1);
}

