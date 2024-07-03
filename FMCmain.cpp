#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>
#include "FMCviewIndex1.h"
#include "FMCviewIndex2.h"
#include "FMCviewIndex3.h"
#include "FMCviewIndex4.h"
#include "FMCviewIndex5.h"
#include "FMCviewIndex6.h"
#include "FMCviewIndex7.h"
#include "FMCviewIndex8.h"
#include "FMCviewIndex9.h"
#include "G_variable.h"

void draw_RouteTable_up(double center_x, double center_y, double side);
void draw_RouteTable_down(double center_x, double center_y, double side);
void draw_RouteTable_bigScrew2(double screw_x, double screw_y, double screw_r, double angle);
void draw_RouteTable_bigScrew(double screw_x, double screw_y, double screw_r, double angle);
void draw_RouteTable_smallScrew(double screw_x, double screw_y, double screw_r, double angle);
void draw_RouteTable_Side_Button(double center_x, double center_y, double side);
void draw_RouteTable_down1(double center_x, double center_y, double side);
void draw_RouteTable_down1_button(double center_x, double center_y, double side);
void draw_RouteTable_down2(double center_x, double center_y, double side);
void draw_RouteTable_down2_circle(double center_x, double center_y, double side);
void draw_RouteTable_down2_square(double center_x, double center_y, double side);
void draw_RouteTable_down2_square_poly(double center_x, double center_y, double side);

int FMC_mode = 0;
int FMC_mouse_x;
int FMC_mouse_y;
int FMC_mouse_real_x;
int FMC_mouse_real_y;
double FMC_origin_center_x_down1;
double FMC_origin_center_y_down1;
double FMC_origin_center_x_down2;
double FMC_origin_center_y_down2;
double FMC_origin_center_x_up;
double FMC_origin_center_y_up;
char inputment[64];
char FMC_button_mode = 0;
extern int MainPanelLight;

char FMC_routepoints[12][7];

char FMC_lastroutepoints[12][7];

struct FMC_buttoninformation {
	double FMC_button_x;
	double FMC_button_y;
	char FMC_button_information[64];
};

// 上半部分的表
void draw_RouteTable_up(double center_x, double center_y, double side) {//side传的是竖高
	//参数设定
	double single = side / 67;
	double length = single * 92;//横长
	double width = single * 67;// 竖宽

	ege_enable_aa(false);// 关闭抗锯齿
	setcolor(EGEARGB(0xff, 0x1b, 0x20, 0x25));//接下来画外框1的线条
	setlinewidth(4);
	ege_point points1[5] = {
		center_x - length / 2,center_y - width / 2,//左上
		center_x - length / 2,center_y + width / 2,//左下
		center_x + length / 2,center_y + width / 2,//右下
		center_x + length / 2,center_y - width / 2,//右上
		center_x - length / 2,center_y - width / 2//左上
	};
	ege_drawpoly(5, points1);

	setcolor(EGEARGB(0xff, 0x1b, 0x20, 0x25));//接下来画外框2的线条
	setlinewidth(4);
	ege_point points2[22] = {

		center_x - single * 33,center_y - single * 28.5,//1

		//加入曲线拟合点——左上角弧线点
		center_x - single * 35.9,center_y - single * 27.5,
		center_x - single * 36.5,center_y - single * 26,
		center_x - single * 37,center_y - single * 25,

		center_x - single * 38,center_y - single * 24.5,//2
		center_x - single * 38,center_y + single * 26.5,//3

		//加入曲线拟合点——左下角弧线点
		center_x - single * 36,center_y + single * 27.5,
		center_x - single * 35.5,center_y + single * 28.5,
		center_x - single * 35.4,center_y + single * 29,

		center_x - single * 33,center_y + single * 30.5,//4
		center_x + single * 33,center_y + single * 30.5,//5

		//加入曲线拟合点——右下角弧线点
		center_x + single * 35,center_y + single * 30.5,
		center_x + single * 36,center_y + single * 28.5,
		center_x + single * 37.5,center_y + single * 27,

		center_x + single * 38,center_y + single * 26.5,//6
		center_x + single * 38,center_y - single * 24.5,//7

		//加入曲线拟合点——右上角弧线点
		center_x + single * 37.6,center_y - single * 25.6,
		center_x + single * 36.5,center_y - single * 27,
		center_x + single * 33.4,center_y - single * 28,

		center_x + single * 33,center_y - single * 28.5,//8
		center_x - single * 33,center_y - single * 28.5,//1
		center_x - single * 33,center_y - single * 28.5//1
	};
	ege_bezier(22, points2);

	setfillcolor(EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(center_x - single * 33, center_y - single * 30.5, EGEARGB(0xff, 0x1b, 0x20, 0x25));//1定位点向上的点
	floodfill(center_x - single * 42, center_y - single * 24.5, EGEARGB(0xff, 0x1b, 0x20, 0x25));//2定位点向左的点
	floodfill(center_x - single * 42, center_y + single * 26.5, EGEARGB(0xff, 0x1b, 0x20, 0x25));//3定位点向左的点
	floodfill(center_x + single * 42, center_y + single * 26.5, EGEARGB(0xff, 0x1b, 0x20, 0x25));//6定位点向右的点
	floodfill(center_x + single * 42, center_y - single * 24.5, EGEARGB(0xff, 0x1b, 0x20, 0x25));//7定位点向右的点
	floodfill(center_x + single * 33, center_y - single * 30.5, EGEARGB(0xff, 0x1b, 0x20, 0x25));//8定位点向上的点


	setcolor(EGEARGB(0xff, 0x1b, 0x20, 0x25));//接下来画外框3的线条
	setlinewidth(4);
	ege_point points3[22] = {

		center_x - single * 27,center_y - single * 24.5,//1

		//加入曲线拟合点——左上角弧线点
		center_x - single * 29.5,center_y - single * 24.5,
		center_x - single * 30.5,center_y - single * 23,
		center_x - single * 31.5,center_y - single * 22,

		center_x - single * 32,center_y - single * 21.5,//2
		center_x - single * 32,center_y + single * 23.5,//3

		//加入曲线拟合点——左下角弧线点
		center_x - single * 30.5,center_y + single * 24,
		center_x - single * 29.5,center_y + single * 25.5,
		center_x - single * 28,center_y + single * 26,

		center_x - single * 27,center_y + single * 26.5,//4
		center_x + single * 27,center_y + single * 26.5,//5

		//加入曲线拟合点——右下角弧线点
		center_x + single * 28,center_y + single * 26,
		center_x + single * 29.5,center_y + single * 25,
		center_x + single * 31,center_y + single * 24,

		center_x + single * 32,center_y + single * 23.5,//6
		center_x + single * 32,center_y - single * 21.5,//7

		//加入曲线拟合点——右上角弧线点
		center_x + single * 31.5,center_y - single * 22.6,
		center_x + single * 29,center_y - single * 23.8,
		center_x + single * 27.2,center_y - single * 24,

		center_x + single * 27,center_y - single * 24.5,//8
		center_x - single * 27,center_y - single * 24.5,//1
		center_x - single * 27,center_y - single * 24.5//1

	};
	ege_bezier(22, points3);

	setfillcolor(EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	floodfill(center_x - single * 26, center_y - single * 26.5, EGEARGB(0xff, 0x1b, 0x20, 0x25));//1定位点向上的点
	//floodfill(center_x - single * 34.5, center_y - single * 21.5, EGEARGB(0xff, 0x1b, 0x20, 0x25));//2定位点向左的点
	//floodfill(center_x - single * 31, center_y + single * 21.5, EGEARGB(0xff, 0x1b, 0x20, 0x25));//3定位点向左的点
	floodfill(center_x - single * 26, center_y + single * 28.5, EGEARGB(0xff, 0x1b, 0x20, 0x25));//4定位点向下的点
	floodfill(center_x + single * 26, center_y + single * 28.5, EGEARGB(0xff, 0x1b, 0x20, 0x25));//5定位点向下的点
	//floodfill(center_x + single * 34.5, center_y + single * 23.5, EGEARGB(0xff, 0x1b, 0x20, 0x25));//6定位点向右的点
	//floodfill(center_x + single * 34.5, center_y - single * 23.5, EGEARGB(0xff, 0x1b, 0x20, 0x25));//7定位点向右的点
	floodfill(center_x + single * 26, center_y - single * 26.5, EGEARGB(0xff, 0x1b, 0x20, 0x25));//8定位点向上的点

	ege_enable_aa(true);
	setlinewidth(6);
	setcolor(EGEARGB(0xff, 0x1b, 0x20, 0x25));//接下来画外框1的线条
	ege_bezier(22, points2);
	setcolor(EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	ege_bezier(22, points3);

	// 左上角小螺丝
	draw_RouteTable_smallScrew(center_x - single * 43, center_y - single * 31, side / 46.1538461538, 0);
	// 左上角大螺丝
	draw_RouteTable_bigScrew(center_x - single * 43.5, center_y - single * 25, side / 30, 90);
	// 左下角小螺丝
	draw_RouteTable_smallScrew(center_x - single * 43, center_y + single * 31, side / 46.1538461538, 0);
	// 右上角小螺丝
	draw_RouteTable_smallScrew(center_x + single * 43, center_y - single * 31, side / 46.1538461538, 0);
	// 右上角大螺丝
	draw_RouteTable_bigScrew(center_x + single * 43.5, center_y - single * 25, side / 30, 90);
	// 右下角小螺丝
	draw_RouteTable_smallScrew(center_x + single * 43.5, center_y + single * 28, side / 46.1538461538, 0);

	// 左边小按钮
	draw_RouteTable_Side_Button(center_x - single * 42, center_y - single * 15, side / 13.33333333);
	draw_RouteTable_Side_Button(center_x - single * 42, center_y - single * 8, side / 13.33333333);
	draw_RouteTable_Side_Button(center_x - single * 42, center_y - single * 1, side / 13.33333333);
	draw_RouteTable_Side_Button(center_x - single * 42, center_y + single * 6, side / 13.33333333);
	draw_RouteTable_Side_Button(center_x - single * 42, center_y + single * 13, side / 13.33333333);
	draw_RouteTable_Side_Button(center_x - single * 42, center_y + single * 20, side / 13.33333333);
	setcolor(EGEARGB(0XFF,0X50,0X50,0X50));
	setlinewidth(side / 200);
	ege_line(center_x - single * 38.5, center_y - single * 15, center_x - single * 37, center_y - single * 15);//1
	ege_line(center_x - single * 37, center_y - single * 15, center_x - single * 31.6, center_y - single * 14.6);
	ege_line(center_x - single * 38.5, center_y - single * 8, center_x - single * 37, center_y - single * 8);//2
	ege_line(center_x - single * 37, center_y - single * 8, center_x - single * 31.6, center_y - single * 7.7);
	ege_line(center_x - single * 38.5, center_y - single * 1, center_x - single * 37, center_y - single * 1);//3
	ege_line(center_x - single * 37, center_y - single * 1, center_x - single * 31.6, center_y - single * 0.7);
	ege_line(center_x - single * 38.5, center_y + single * 6, center_x - single * 37, center_y + single * 6);//4
	ege_line(center_x - single * 37, center_y + single * 6, center_x - single * 31.6, center_y + single * 6.3);
	ege_line(center_x - single * 38.5, center_y + single * 13, center_x - single * 37, center_y + single * 13);//5
	ege_line(center_x - single * 37, center_y + single * 13, center_x - single * 31.6, center_y + single * 13.2);
	ege_line(center_x - single * 38.5, center_y + single * 20, center_x - single * 37, center_y + single * 20);//6
	ege_line(center_x - single * 37, center_y + single * 20, center_x - single * 31.6, center_y + single * 20.2);

	setcolor(EGEARGB(MainPanelLight, 124, 124, 128));
	setlinewidth(side / 200);
	ege_line(center_x - single * 38.5, center_y - single * 15, center_x - single * 37, center_y - single * 15);//1
	ege_line(center_x - single * 37, center_y - single * 15, center_x - single * 31.6, center_y - single * 14.6);
	ege_line(center_x - single * 38.5, center_y - single * 8, center_x - single * 37, center_y - single * 8);//2
	ege_line(center_x - single * 37, center_y - single * 8, center_x - single * 31.6, center_y - single * 7.7);
	ege_line(center_x - single * 38.5, center_y - single * 1, center_x - single * 37, center_y - single * 1);//3
	ege_line(center_x - single * 37, center_y - single * 1, center_x - single * 31.6, center_y - single * 0.7);
	ege_line(center_x - single * 38.5, center_y + single * 6, center_x - single * 37, center_y + single * 6);//4
	ege_line(center_x - single * 37, center_y + single * 6, center_x - single * 31.6, center_y + single * 6.3);
	ege_line(center_x - single * 38.5, center_y + single * 13, center_x - single * 37, center_y + single * 13);//5
	ege_line(center_x - single * 37, center_y + single * 13, center_x - single * 31.6, center_y + single * 13.2);
	ege_line(center_x - single * 38.5, center_y + single * 20, center_x - single * 37, center_y + single * 20);//6
	ege_line(center_x - single * 37, center_y + single * 20, center_x - single * 31.6, center_y + single * 20.2);

	// 右边小按钮
	draw_RouteTable_Side_Button(center_x + single * 42, center_y - single * 15, side / 13.33333333);
	draw_RouteTable_Side_Button(center_x + single * 42, center_y - single * 8, side / 13.33333333);
	draw_RouteTable_Side_Button(center_x + single * 42, center_y - single * 1, side / 13.33333333);
	draw_RouteTable_Side_Button(center_x + single * 42, center_y + single * 6, side / 13.33333333);
	draw_RouteTable_Side_Button(center_x + single * 42, center_y + single * 13, side / 13.33333333);
	draw_RouteTable_Side_Button(center_x + single * 42, center_y + single * 20, side / 13.33333333);

	setcolor(EGEARGB(0XFF,0X50,0X50,0X50));
	setlinewidth(side / 200);
	ege_line(center_x + single * 38.5, center_y - single * 15, center_x + single * 37, center_y - single * 15);//1
	ege_line(center_x + single * 37, center_y - single * 15, center_x + single * 31.6, center_y - single * 14.6);
	ege_line(center_x + single * 38.5, center_y - single * 8, center_x + single * 37, center_y - single * 8);//2
	ege_line(center_x + single * 37, center_y - single * 8, center_x + single * 31.6, center_y - single * 7.7);
	ege_line(center_x + single * 38.5, center_y - single * 1, center_x + single * 37, center_y - single * 1);//3
	ege_line(center_x + single * 37, center_y - single * 1, center_x + single * 31.6, center_y - single * 0.7);
	ege_line(center_x + single * 38.5, center_y + single * 6, center_x + single * 37, center_y + single * 6);//4
	ege_line(center_x + single * 37, center_y + single * 6, center_x + single * 31.6, center_y + single * 6.3);
	ege_line(center_x + single * 38.5, center_y + single * 13, center_x + single * 37, center_y + single * 13);//5
	ege_line(center_x + single * 37, center_y + single * 13, center_x + single * 31.6, center_y + single * 13.2);
	ege_line(center_x + single * 38.5, center_y + single * 20, center_x + single * 37, center_y + single * 20);//6
	ege_line(center_x + single * 37, center_y + single * 20, center_x + single * 31.6, center_y + single * 20.2);
	
	setcolor(EGEARGB(MainPanelLight, 124, 124, 128));
	setlinewidth(side / 200);
	ege_line(center_x + single * 38.5, center_y - single * 15, center_x + single * 37, center_y - single * 15);//1
	ege_line(center_x + single * 37, center_y - single * 15, center_x + single * 31.6, center_y - single * 14.6);
	ege_line(center_x + single * 38.5, center_y - single * 8, center_x + single * 37, center_y - single * 8);//2
	ege_line(center_x + single * 37, center_y - single * 8, center_x + single * 31.6, center_y - single * 7.7);
	ege_line(center_x + single * 38.5, center_y - single * 1, center_x + single * 37, center_y - single * 1);//3
	ege_line(center_x + single * 37, center_y - single * 1, center_x + single * 31.6, center_y - single * 0.7);
	ege_line(center_x + single * 38.5, center_y + single * 6, center_x + single * 37, center_y + single * 6);//4
	ege_line(center_x + single * 37, center_y + single * 6, center_x + single * 31.6, center_y + single * 6.3);
	ege_line(center_x + single * 38.5, center_y + single * 13, center_x + single * 37, center_y + single * 13);//5
	ege_line(center_x + single * 37, center_y + single * 13, center_x + single * 31.6, center_y + single * 13.2);
	ege_line(center_x + single * 38.5, center_y + single * 20, center_x + single * 37, center_y + single * 20);//6
	ege_line(center_x + single * 37, center_y + single * 20, center_x + single * 31.6, center_y + single * 20.2);
}

// 下半部分的表
void draw_RouteTable_down(double center_x, double center_y, double side) {//side传的是竖高
	draw_RouteTable_down2(center_x, center_y, side);
	draw_RouteTable_down1(center_x, center_y - side / 3.5, side);
}

// 表上的十字旋钮
void draw_RouteTable_smallScrew(double screw_x, double screw_y, double screw_r, double angle) {

	setfillcolor(EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	ege_fillellipse(screw_x - screw_r, screw_y - screw_r, 2 * screw_r, 2 * screw_r);

	setcolor(BLACK);
	setlinewidth(screw_r / 7.5);
	ege_ellipse(screw_x - screw_r, screw_y - screw_r, 2 * screw_r, 2 * screw_r);

	// 绘制中间螺丝
	angle = -angle;
	angle = angle * PI / 180;

	double x01 = -screw_r * 0.7, y01 = -screw_r * 0.15;
	double x02 = -screw_r * 0.7, y02 = +screw_r * 0.15;
	double x03 = +screw_r * 0.7, y03 = +screw_r * 0.15;
	double x04 = +screw_r * 0.7, y04 = -screw_r * 0.15;

	setfillcolor(BLACK);
	ege_point polypoints1[4] = {
		{x01 * cos(angle) - y01 * sin(angle) + screw_x,x01 * sin(angle) + y01 * cos(angle) + screw_y},// 左上
		{x02 * cos(angle) - y02 * sin(angle) + screw_x,x02 * sin(angle) + y02 * cos(angle) + screw_y},// 右上
		{x03 * cos(angle) - y03 * sin(angle) + screw_x,x03 * sin(angle) + y03 * cos(angle) + screw_y},// 右下
		{x04 * cos(angle) - y04 * sin(angle) + screw_x,x04 * sin(angle) + y04 * cos(angle) + screw_y} // 左下
	};
	ege_fillpoly(4, polypoints1);


	double x11 = -screw_r * 0.15, y11 = -screw_r * 0.7;
	double x12 = -screw_r * 0.15, y12 = +screw_r * 0.7;
	double x13 = +screw_r * 0.15, y13 = +screw_r * 0.7;
	double x14 = +screw_r * 0.15, y14 = -screw_r * 0.7;

	ege_point polypoints2[4] = {
		{x11 * cos(angle) - y11 * sin(angle) + screw_x,x11 * sin(angle) + y11 * cos(angle) + screw_y},// 左上
		{x12 * cos(angle) - y12 * sin(angle) + screw_x,x12 * sin(angle) + y12 * cos(angle) + screw_y},// 右上
		{x13 * cos(angle) - y13 * sin(angle) + screw_x,x13 * sin(angle) + y13 * cos(angle) + screw_y},// 右下
		{x14 * cos(angle) - y14 * sin(angle) + screw_x,x14 * sin(angle) + y14 * cos(angle) + screw_y} // 左下
	};
	ege_fillpoly(4, polypoints2);


	// 螺丝中间菱形
	double x21 = -screw_r * 0.4, y21 = 0;
	double x22 = 0, y22 = +screw_r * 0.4;
	double x23 = +screw_r * 0.4, y23 = 0;
	double x24 = 0, y24 = -screw_r * 0.4;
	setcolor(BLACK);
	setfillcolor(BLACK);
	ege_point polypoints5[5] = {
		{x21 * cos(angle) - y21 * sin(angle) + screw_x,x21 * sin(angle) + y21 * cos(angle) + screw_y},// 上
		{x22 * cos(angle) - y22 * sin(angle) + screw_x,x22 * sin(angle) + y22 * cos(angle) + screw_y},// 右
		{x23 * cos(angle) - y23 * sin(angle) + screw_x,x23 * sin(angle) + y23 * cos(angle) + screw_y},// 下
		{x24 * cos(angle) - y24 * sin(angle) + screw_x,x24 * sin(angle) + y24 * cos(angle) + screw_y},//左
		{x21 * cos(angle) - y21 * sin(angle) + screw_x,x21 * sin(angle) + y21 * cos(angle) + screw_y}
	};
	ege_fillpoly(5, polypoints5);


}

// 表上的一字旋钮
void draw_RouteTable_bigScrew(double screw_x, double screw_y, double screw_r, double angle) {

	setfillcolor(EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	ege_fillellipse(screw_x - screw_r, screw_y - screw_r, 2 * screw_r, 2 * screw_r);

	setcolor(BLACK);
	setlinewidth(screw_r / 7.5);
	ege_ellipse(screw_x - screw_r, screw_y - screw_r, 2 * screw_r, 2 * screw_r);

	// 绘制中间螺丝
	angle = -angle;
	angle = angle * PI / 180;

	double x01 = -screw_r * 1, y01 = -screw_r * 0.15;
	double x02 = -screw_r * 1, y02 = +screw_r * 0.15;
	double x03 = +screw_r * 1, y03 = +screw_r * 0.15;
	double x04 = +screw_r * 1, y04 = -screw_r * 0.15;

	setfillcolor(BLACK);
	ege_point polypoints1[4] = {
		{x01 * cos(angle) - y01 * sin(angle) + screw_x,x01 * sin(angle) + y01 * cos(angle) + screw_y},// 左上
		{x02 * cos(angle) - y02 * sin(angle) + screw_x,x02 * sin(angle) + y02 * cos(angle) + screw_y},// 右上
		{x03 * cos(angle) - y03 * sin(angle) + screw_x,x03 * sin(angle) + y03 * cos(angle) + screw_y},// 右下
		{x04 * cos(angle) - y04 * sin(angle) + screw_x,x04 * sin(angle) + y04 * cos(angle) + screw_y} // 左下
	};
	ege_fillpoly(4, polypoints1);

}

// 表上的一字旋钮——靠下的
void draw_RouteTable_bigScrew2(double screw_x, double screw_y, double screw_r, double angle) {

	setfillcolor(EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	ege_fillellipse(screw_x - screw_r, screw_y - screw_r, 2 * screw_r, 2 * screw_r);

	setcolor(BLACK);
	setlinewidth(screw_r / 7.5);
	ege_ellipse(screw_x - screw_r / 1.2, screw_y - screw_r / 1.2, 1.6 * screw_r, 1.6 * screw_r);

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

extern char FMCFileName[20];

// 上半部分旁边的按钮
void draw_RouteTable_Side_Button(double center_x, double center_y, double side) {
	setfillcolor(BLACK);
	double single = side / 4.5;
	double width = single * 4.5;
	double length = single * 6;
	mousepos(&FMC_mouse_x, &FMC_mouse_y);
	FMC_mouse_real_x = FMC_mouse_x;
	FMC_mouse_real_y = FMC_mouse_y;
	
	ege_fillrect(center_x - length / 2, center_y - width / 2, length, width);
	setlinewidth(side / 7.5);
	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_line(center_x - single * 2, center_y, center_x + single * 2, center_y);
	setcolor(EGEARGB(MainPanelLight, 136, 97, 67));//橙色
	ege_line(center_x - single * 2, center_y, center_x + single * 2, center_y);

	if (FMC_mouse_real_x >= center_x - length / 2 && FMC_mouse_real_x <= center_x + length / 2 && FMC_mouse_real_y >= center_y - width / 2 && FMC_mouse_real_y <= center_y + width / 2) {
		if (GetAsyncKeyState(0x02) & 0x0001) 
		{
			if (FMC_mode == 0)
			{
				if (fabs(center_x - FMC_origin_center_x_up - single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 15) < 0.0001)
				{
					FMC_mode = 7;
				}
			}
			if (FMC_mode == 1)
			{
				if (fabs(center_x - FMC_origin_center_x_up + single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 15) < 0.0001)
				{
					FMC_button_mode = 1;
				}
				else if (fabs(center_x - FMC_origin_center_x_up - single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 15) < 0.0001)
				{
					FMC_button_mode = 2;
				}
				else if (fabs(center_x - FMC_origin_center_x_up - single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 1) < 0.0001)
				{
					FMC_button_mode = 5;
				}
				else if (fabs(center_x - FMC_origin_center_x_up + single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up - single * 4.5 * 13.33333333 / 67 * 20) < 0.0001)
				{
					FMC_mode = 7;
				}
			}
			if (FMC_mode == 2)
			{
				if (fabs(center_x - FMC_origin_center_x_up + single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 15) < 0.0001 && is_empty_6())
				{
					FMC_mode = 3;
				}
				else if (fabs(center_x - FMC_origin_center_x_up + single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 15) < 0.0001 && !is_empty_6())
				{
					FMC_mode = 5;
				}
			}
			if (FMC_mode == 3)
			{
				if (fabs(center_x - FMC_origin_center_x_up - single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 15) < 0.0001)
				{
					getScanner_4(1);
					FMC_mode = 4;
				}
				else if (fabs(center_x - FMC_origin_center_x_up - single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 8) < 0.0001) 
				{
					getScanner_4(2);
					FMC_mode = 4;
				}
				else if (fabs(center_x - FMC_origin_center_x_up - single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 1) < 0.0001)
				{
					getScanner_4(3);
					FMC_mode = 4;
				}
				else if (fabs(center_x - FMC_origin_center_x_up - single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up - single * 4.5 * 13.33333333 / 67 * 6) < 0.0001)
				{
					getScanner_4(4);
					FMC_mode = 4;
				}
				else if (fabs(center_x - FMC_origin_center_x_up - single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up - single * 4.5 * 13.33333333 / 67 * 13) < 0.0001)
				{
					getScanner_4(5);
					FMC_mode = 4;
				}
				else if (fabs(center_x - FMC_origin_center_x_up - single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up - single * 4.5 * 13.33333333 / 67 * 20) < 0.0001)
				{
					getScanner_4(6);
					FMC_mode = 4;
				}
			}
			if (FMC_mode == 4) 
			{
				if (fabs(center_x - FMC_origin_center_x_up + single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 15) < 0.0001)
				{
					getScanner_5_left(1);
					FMC_mode = 5;
				}
				else if (fabs(center_x - FMC_origin_center_x_up + single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 8) < 0.0001)
				{
					getScanner_5_left(2);
					FMC_mode = 5;
				}
				else if (fabs(center_x - FMC_origin_center_x_up + single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 1) < 0.0001)
				{
					getScanner_5_left(3);
					FMC_mode = 5;
				}
				else if (fabs(center_x - FMC_origin_center_x_up + single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up - single * 4.5 * 13.33333333 / 67 * 6) < 0.0001)
				{
					getScanner_5_left(4);
					FMC_mode = 5;
				}
				else if (fabs(center_x - FMC_origin_center_x_up + single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up - single * 4.5 * 13.33333333 / 67 * 13) < 0.0001)
				{
					getScanner_5_left(5);
					FMC_mode = 5;
				}
				else if (fabs(center_x - FMC_origin_center_x_up + single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up - single * 4.5 * 13.33333333 / 67 * 20) < 0.0001)
				{
					FMC_mode = 3;
					cancelright();
				}
				else if (fabs(center_x - FMC_origin_center_x_up - single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up - single * 4.5 * 13.33333333 / 67 * 20) < 0.0001)
				{
					FMC_mode = 1;
				}
			}
			if (FMC_mode == 5)
			{
				if (fabs(center_x - FMC_origin_center_x_up + single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up - single * 4.5 * 13.33333333 / 67 * 20) < 0.0001)
				{
					FMC_mode = 4;
					cancelleft();
				}
				else if (fabs(center_x - FMC_origin_center_x_up - single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up - single * 4.5 * 13.33333333 / 67 * 20) < 0.0001)
				{
					FMC_mode = 1;
				}
			}
			if (FMC_mode == 6)
			{
				if (fabs(center_x - FMC_origin_center_x_up + single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 15) < 0.0001)
				{
					FMC_button_mode = 1;
				}
				else if (fabs(center_x - FMC_origin_center_x_up + single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 8) < 0.0001)
				{
					FMC_button_mode = 3;
				}
				else if (fabs(center_x - FMC_origin_center_x_up + single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 1) < 0.0001)
				{
					FMC_button_mode = 5;
				}
				else if (fabs(center_x - FMC_origin_center_x_up + single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up - single * 4.5 * 13.33333333 / 67 * 6) < 0.0001)
				{
					FMC_button_mode = 7;
				}
				else if (fabs(center_x - FMC_origin_center_x_up + single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up - single * 4.5 * 13.33333333 / 67 * 13) < 0.0001)
				{
					FMC_button_mode = 9;
				}
				else if (fabs(center_x - FMC_origin_center_x_up - single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 15) < 0.0001)
				{
					FMC_button_mode = 2;
				}
				else if (fabs(center_x - FMC_origin_center_x_up - single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 8) < 0.0001)
				{
					FMC_button_mode = 4;
				}
				else if (fabs(center_x - FMC_origin_center_x_up - single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 1) < 0.0001)
				{
					FMC_button_mode = 6;
				}
				else if (fabs(center_x - FMC_origin_center_x_up - single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up - single * 4.5 * 13.33333333 / 67 * 6) < 0.0001)
				{
					FMC_button_mode = 8;
				}
				else if (fabs(center_x - FMC_origin_center_x_up - single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up - single * 4.5 * 13.33333333 / 67 * 13) < 0.0001)
				{
					FMC_button_mode = 10;
				}
			}
			if (FMC_mode == 7)
			{
				if (fabs(center_x - FMC_origin_center_x_up + single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 8) < 0.0001)
				{
					FMC_mode = 8;
				}
			}
			if (FMC_mode == 8)
			{
				if (fabs(center_x - FMC_origin_center_x_up + single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up - single * 4.5 * 13.33333333 / 67 * 13) < 0.0001)
				{
					FMC_mode = 1;
				}
				else if (fabs(center_x - FMC_origin_center_x_up - single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up - single * 4.5 * 13.33333333 / 67 * 13) < 0.0001)
				{
					FMC_mode = 7;
				}
				else if (fabs(center_x - FMC_origin_center_x_up + single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 15) < 0.0001)
				{
					strcpy(FMCFileName,getinformation_9(1));
				}
				else if (fabs(center_x - FMC_origin_center_x_up + single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 8) < 0.0001)
				{
					strcpy(FMCFileName,getinformation_9(3));
				}
				else if (fabs(center_x - FMC_origin_center_x_up + single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 1) < 0.0001)
				{
					strcpy(FMCFileName,getinformation_9(5));
				}
				else if (fabs(center_x - FMC_origin_center_x_up + single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up - single * 4.5 * 13.33333333 / 67 * 6) < 0.0001)
				{
					strcpy(FMCFileName,getinformation_9(7));
				}
				else if (fabs(center_x - FMC_origin_center_x_up - single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 15) < 0.0001)
				{
					strcpy(FMCFileName,getinformation_9(2));
				}
				else if (fabs(center_x - FMC_origin_center_x_up - single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 8) < 0.0001)
				{
					strcpy(FMCFileName,getinformation_9(4));
				}
				else if (fabs(center_x - FMC_origin_center_x_up - single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up + single * 4.5 * 13.33333333 / 67 * 1) < 0.0001)
				{
					strcpy(FMCFileName,getinformation_9(6));
				}
				else if (fabs(center_x - FMC_origin_center_x_up - single * 4.5 * 13.33333333 / 67 * 42) < 0.0001 && fabs(center_y - FMC_origin_center_y_up - single * 4.5 * 13.33333333 / 67 * 6) < 0.0001)
				{
					strcpy(FMCFileName,getinformation_9(8));
				}
			}
			/*draw_RouteTable_Side_Button(center_x - single * 42, center_y - single * 15, side / 13.33333333);
				draw_RouteTable_Side_Button(center_x - single * 42, center_y - single * 8, side / 13.33333333);
				draw_RouteTable_Side_Button(center_x - single * 42, center_y - single * 1, side / 13.33333333);
				draw_RouteTable_Side_Button(center_x - single * 42, center_y + single * 6, side / 13.33333333);
				draw_RouteTable_Side_Button(center_x - single * 42, center_y + single * 13, side / 13.33333333);
				draw_RouteTable_Side_Button(center_x - single * 42, center_y + single * 20, side / 13.33333333);*/
				//ege_rectangle(FMC_origin_center_x_up - single * 4.5 * 13.33333333 / 67 * 42 - length / 2, FMC_origin_center_y_up - single * 4.5 * 13.33333333 / 67 * 15 - width / 2, length, width);
				/*draw_RouteTable_Side_Button(center_x + single * 42, center_y - single * 15, side / 13.33333333);
				draw_RouteTable_Side_Button(center_x + single * 42, center_y - single * 8, side / 13.33333333);
				draw_RouteTable_Side_Button(center_x + single * 42, center_y - single * 1, side / 13.33333333);
				draw_RouteTable_Side_Button(center_x + single * 42, center_y + single * 6, side / 13.33333333);
				draw_RouteTable_Side_Button(center_x + single * 42, center_y + single * 13, side / 13.33333333);
				draw_RouteTable_Side_Button(center_x + single * 42, center_y + single * 20, side / 13.33333333);*/
		}
	}

	if (FMC_mouse_real_x >= center_x - length / 2 && FMC_mouse_real_x <= center_x + length / 2 && FMC_mouse_real_y >= center_y - width / 2 && FMC_mouse_real_y <= center_y + width / 2) {
		setcolor(WHITE);
		setlinewidth(1.5);
		ege_rectangle(center_x - length / 2 - side * 0.005, center_y - width / 2 - side * 0.005, length + side * 0.01, width + side * 0.01);
	}
}

// 下半部分的最上一层
void draw_RouteTable_down1(double center_x, double center_y, double side) {

	// 这里的center是这个表盘部件的中心
	double single = side / 67;

	setfillcolor(EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	setcolor(EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	ege_point points1[14] = {
		center_x - single * 34,center_y - single * 19,//1点
		center_x - single * 38,center_y - single * 15,//2点
		center_x - single * 38,center_y + single * 15,//3点
		center_x - single * 34,center_y + single * 19,//4点
		center_x - single * 16,center_y + single * 19,//5点
		center_x - single * 12,center_y + single * 15,//6点
		center_x - single * 12,center_y + single * 5,//7点
		center_x - single * 11,center_y + single * 2,//8点
		center_x - single * 8,center_y + single * 1,//9点
		center_x + single * 34,center_y + single * 1,//10点
		center_x + single * 38,center_y - single * 3,//11点
		center_x + single * 38,center_y - single * 15,//12点
		center_x + single * 34,center_y - single * 19,//13点
		center_x - single * 34,center_y - single * 19//1点
	};
	ege_fillpoly(14, points1);
	ege_drawpoly(14, points1);

	// 这是对这块部分的四周的圆滑处理
	ege_fillellipse(center_x - single * 38.4, center_y - single * 19.4, single * 7.4, single * 7.4);
	ege_fillellipse(center_x - single * 38.2, center_y + single * 12, single * 7, single * 7);
	ege_fillellipse(center_x - single * 19, center_y + single * 12, single * 7, single * 7);
	ege_fillellipse(center_x + single * 31.4, center_y - single * 19.4, single * 7, single * 7);//右上
	ege_fillellipse(center_x + single * 31.2, center_y - single * 6, single * 7, single * 7);//右下
	setlinewidth(6);
	ege_point points2[4] = {
		center_x - single * 12.5,center_y + single * 5.5,//7点
		center_x - single * 11,center_y + single * 2,//
		center_x - single * 11,center_y + single * 2,//
		center_x - single * 7,center_y + single * 0.5//9点
	};
	ege_bezier(4, points2);

	// 下面的坐标的坐标系是以右为x的正半轴，下为y的正半轴
	draw_RouteTable_down1_button(center_x - single * 31, center_y - single * 13.5, single * 70);//(1,1)
	draw_RouteTable_down1_button(center_x - single * 31, center_y - single * 4.9, single * 70);//(1,2)
	draw_RouteTable_down1_button(center_x - single * 31, center_y + single * 3.7, single * 70);//(1,3)
	draw_RouteTable_down1_button(center_x - single * 31, center_y + single * 12.3, single * 70);//(1,4)
	draw_RouteTable_down1_button(center_x - single * 19, center_y - single * 13.5, single * 70);//(2,1)
	draw_RouteTable_down1_button(center_x - single * 19, center_y - single * 4.9, single * 70);//(2,2)
	draw_RouteTable_down1_button(center_x - single * 19, center_y + single * 3.7, single * 70);//(2,3)
	draw_RouteTable_down1_button(center_x - single * 19, center_y + single * 12.3, single * 70);//(2,4)
	draw_RouteTable_down1_button(center_x - single * 7, center_y - single * 13.5, single * 70);//(3,1)
	draw_RouteTable_down1_button(center_x - single * 7, center_y - single * 4.9, single * 70);//(3,2)
	draw_RouteTable_down1_button(center_x + single * 5, center_y - single * 13.5, single * 70);//(4,1)
	draw_RouteTable_down1_button(center_x + single * 5, center_y - single * 4.9, single * 70);//(4,2)
	draw_RouteTable_down1_button(center_x + single * 17, center_y - single * 13.5, single * 70);//(5,1)
	draw_RouteTable_down1_button(center_x + single * 17, center_y - single * 4.9, single * 70);//(5,2)
	setfillcolor(BLACK);
	ege_fillrect(center_x + single * 26, center_y - single * 6.5, single * 10, single * 5);//最右
	mousepos(&FMC_mouse_x, &FMC_mouse_y);
	FMC_mouse_real_x = FMC_mouse_x;
	FMC_mouse_real_y = FMC_mouse_y;
	setcolor(WHITE);
	setlinewidth(side*0.001);
	setfillcolor(BLACK);
	if (FMC_mode == 5)
	{
		if (is_empty_6())
			setfillcolor(EGEARGB(0xff, 0x48, 0xF2, 0xF4));
	}
	if (FMC_mouse_real_x >= center_x + single * 26 && FMC_mouse_real_x <= center_x + single * 26 + single * 10 && FMC_mouse_real_y >= center_y - single * 6.5 && FMC_mouse_real_y <= center_y - single * 6.5 + single * 5)
	{
		if (FMC_mode == 5)
		{
			if (GetAsyncKeyState(0x02) & 0x0001)
			{
				getinformation_6(true);
				setfillcolor(BLACK);
			}
		}
		ege_rectangle(center_x + single * 26 - side * 0.005, center_y - single * 6.5 - side * 0.005, single * 10 + side * 0.01, single * 5 + side * 0.01);
	}
	ege_fillrect(center_x + single * 28, center_y - single * 9, single * 6, single);
	setfillcolor(BLACK);
	ege_fillellipse(center_x + single * 31, center_y - single * 16, single * 4, single * 4);

	setbkmode(TRANSPARENT);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setfont(single * 3, 0, "黑体");
	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_drawtext("INIT", center_x - single * 31, center_y - single * 14.2);//(1,1) 移0.7 移1.5
	ege_drawtext("REF", center_x - single * 31, center_y - single * 12);//
	ege_drawtext("DIR", center_x - single * 31, center_y - single * 5.6);//(1,2)
	ege_drawtext("INTC", center_x - single * 31, center_y - single * 3.4);
	ege_drawtext("FIX", center_x - single * 31, center_y + single * 3.8);//(1.3)
	ege_drawtext("PREV", center_x - single * 31, center_y + single * 11.6);//(1,4)
	ege_drawtext("PAGE", center_x - single * 31, center_y + single * 13.8);
	ege_drawtext("RTE", center_x - single * 19, center_y - single * 13.4);//(2,1)
	ege_drawtext("LEGS", center_x - single * 19, center_y - single * 4.8);//(2,2)
	ege_drawtext("NAV", center_x - single * 19, center_y + single * 3);//(2,3)
	ege_drawtext("RAD", center_x - single * 19, center_y + single * 5.2);
	ege_drawtext("NEXT", center_x - single * 19, center_y + single * 11.6);//(2,4)
	ege_drawtext("PAGE", center_x - single * 19, center_y + single * 13.8);
	ege_drawtext("CLB", center_x - single * 7, center_y - single * 13.4);//(3,1)
	ege_drawtext("DEP", center_x - single * 7, center_y - single * 5.5);//(3,2)
	ege_drawtext("ARR", center_x - single * 7, center_y - single * 3.4);
	ege_drawtext("CRZ", center_x + single * 5, center_y - single * 13.4);//(4,1)
	ege_drawtext("HOLD", center_x + single * 5, center_y - single * 4.8);//(4,2)
	ege_drawtext("DES", center_x + single * 17, center_y - single * 13.4);//(5,1)
	ege_drawtext("PROG", center_x + single * 17, center_y - single * 4.8);//(5,2)
	ege_drawtext("EXEC", center_x + single * 31, center_y - single * 3.8);
	setfont(single * 2.5, 0, "黑体");
	ege_drawtext("B", center_x + single * 25, center_y - single * 17);
	ege_drawtext("R", center_x + single * 25, center_y - single * 15);
	ege_drawtext("T", center_x + single * 25, center_y - single * 13);
	
	setfont(single * 3, 0, "黑体");
	setcolor(EGEARGB(MainPanelLight, 136, 97, 67));
	ege_drawtext("INIT", center_x - single * 31, center_y - single * 14.2);//(1,1) 移0.7 移1.5
	ege_drawtext("REF", center_x - single * 31, center_y - single * 12);//
	ege_drawtext("DIR", center_x - single * 31, center_y - single * 5.6);//(1,2)
	ege_drawtext("INTC", center_x - single * 31, center_y - single * 3.4);
	ege_drawtext("FIX", center_x - single * 31, center_y + single * 3.8);//(1.3)
	ege_drawtext("PREV", center_x - single * 31, center_y + single * 11.6);//(1,4)
	ege_drawtext("PAGE", center_x - single * 31, center_y + single * 13.8);
	ege_drawtext("RTE", center_x - single * 19, center_y - single * 13.4);//(2,1)
	ege_drawtext("LEGS", center_x - single * 19, center_y - single * 4.8);//(2,2)
	ege_drawtext("NAV", center_x - single * 19, center_y + single * 3);//(2,3)
	ege_drawtext("RAD", center_x - single * 19, center_y + single * 5.2);
	ege_drawtext("NEXT", center_x - single * 19, center_y + single * 11.6);//(2,4)
	ege_drawtext("PAGE", center_x - single * 19, center_y + single * 13.8);
	ege_drawtext("CLB", center_x - single * 7, center_y - single * 13.4);//(3,1)
	ege_drawtext("DEP", center_x - single * 7, center_y - single * 5.5);//(3,2)
	ege_drawtext("ARR", center_x - single * 7, center_y - single * 3.4);
	ege_drawtext("CRZ", center_x + single * 5, center_y - single * 13.4);//(4,1)
	ege_drawtext("HOLD", center_x + single * 5, center_y - single * 4.8);//(4,2)
	ege_drawtext("DES", center_x + single * 17, center_y - single * 13.4);//(5,1)
	ege_drawtext("PROG", center_x + single * 17, center_y - single * 4.8);//(5,2)
	ege_drawtext("EXEC", center_x + single * 31, center_y - single * 3.8);
	setfont(single * 2.5, 0, "黑体");
	ege_drawtext("B", center_x + single * 25, center_y - single * 17);
	ege_drawtext("R", center_x + single * 25, center_y - single * 15);
	ege_drawtext("T", center_x + single * 25, center_y - single * 13);



}

// 下半部分的最上一层的按钮
void draw_RouteTable_down1_button(double center_x, double center_y, double side) {

	double single = side / 67;
	double length = single * 10;
	double width = single * 7;

	mousepos(&FMC_mouse_x, &FMC_mouse_y);
	FMC_mouse_real_x = FMC_mouse_x;
	FMC_mouse_real_y = FMC_mouse_y;

	if (FMC_mouse_real_x >= center_x - length / 2 && FMC_mouse_real_x <= center_x + length / 2 && FMC_mouse_real_y >= center_y - width / 2 && FMC_mouse_real_y <= center_y + width / 2)
	{
		if (GetAsyncKeyState(0x02) & 0x0001)
		{
			if (fabs(center_x - FMC_origin_center_x_down1 + single * 31 * 67 / 70) < 0.001 && fabs(center_y - FMC_origin_center_y_down1 + single * 13.5 * 67 / 70) < 0.001)
			{
				FMC_mode = 0;
			}
			else if (fabs(center_x - FMC_origin_center_x_down1 + single * 19 * 67 / 70) < 0.001 && fabs(center_y - FMC_origin_center_y_down1 + single * 13.5 * 67 / 70) < 0.001)
			{
				FMC_mode = 1;
			}
			else if (fabs(center_x - FMC_origin_center_x_down1 + single * 7 * 67 / 70 ) < 0.001&& fabs(center_y - FMC_origin_center_y_down1 + single * 4.9 * 67 / 70) < 0.001)
			{
				FMC_mode = 2;
			}
			else if (fabs(center_x - FMC_origin_center_x_down1 + single * 19 * 67 / 70) < 0.001 && fabs(center_y - FMC_origin_center_y_down1 - single * 12.3 * 67 / 70) < 0.001 && is_empty_2())
			{
				FMC_mode = 6;
			}
		}
	}


	if (FMC_mouse_real_x >= center_x - length / 2 && FMC_mouse_real_x <= center_x + length / 2 && FMC_mouse_real_y >= center_y - width / 2 && FMC_mouse_real_y <= center_y + width / 2)
	{
		setcolor(WHITE);
		setlinewidth(1.5);
		ege_rectangle(center_x - length / 2 - side * 0.005, center_y - width / 2 - side * 0.005, length + side * 0.01, width + side * 0.01);
	}

	setfillcolor(BLACK);
	ege_fillrect(center_x - length / 2, center_y - width / 2, length, width);
}

// 下半部分的最下一层
void draw_RouteTable_down2(double center_x, double center_y, double side) {

	double single = side / 67;

	setfillcolor(EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	ege_fillrect(center_x - single * 46, center_y + single * 28, single * 92, single * 10);

	setfillcolor(EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	setcolor(EGEARGB(0XFF, 0X1A, 0X1F, 0X23));

	ege_point points1[25] = {//40,38.5
		center_x - single * 37, center_y - single * 38.5,//1
		center_x - single * 40,center_y - single * 35.5,//2
		center_x - single * 40,center_y - single * 17.5,//3
		center_x - single * 40.5,center_y - single * 15,//4
		center_x - single * 42,center_y - single * 14.5,//5
		center_x - single * 44,center_y - single * 12.5,//6
		center_x - single * 44,center_y + single * 22.5,//7
		center_x - single * 43,center_y + single * 23.5,//8
		center_x - single * 41,center_y + single * 26.5,//9
		center_x - single * 40,center_y + single * 28.5,//10
		center_x - single * 40,center_y + single * 36.5,//11
		center_x - single * 38,center_y + single * 38.5,//12

		center_x + single * 38,center_y + single * 38.5,//13
		center_x + single * 40,center_y + single * 36.5,//14
		center_x + single * 40,center_y + single * 28.5,//15
		center_x + single * 41,center_y + single * 26.5,//16
		center_x + single * 43,center_y + single * 23.5,//17
		center_x + single * 44,center_y + single * 22.5,//18
		center_x + single * 44,center_y - single * 12.5,//19
		center_x + single * 42,center_y - single * 14.5,//20
		center_x + single * 40.5,center_y - single * 15,//21
		center_x + single * 40,center_y - single * 17.5,//22
		center_x + single * 40,center_y - single * 35.5,//23
		center_x + single * 37, center_y - single * 38.5,//24

		center_x - single * 37, center_y - single * 38.5//1
	};
	ege_fillpoly(25, points1);
	ege_drawpoly(25, points1);

	// 这是对这块部分的四周的圆滑处理
	ege_fillellipse(center_x - single * 40, center_y - single * 38.5, single * 5.2, single * 5.2);//左上角圆
	ege_fillellipse(center_x + single * 35, center_y - single * 38.5, single * 5, single * 5);//左上角圆
	ege_fillellipse(center_x - single * 44, center_y - single * 14.5, single * 3.5, single * 3.5);//左中间圆偏上
	ege_fillellipse(center_x + single * 40.5, center_y - single * 14.5, single * 3.5, single * 3.5);//右中间圆偏上
	ege_fillellipse(center_x - single * 44.1, center_y + single * 15, single * 5, single * 5);//左中间圆偏下
	ege_fillellipse(center_x + single * 39.1, center_y + single * 15, single * 5, single * 5);//右中间圆偏下
	ege_fillellipse(center_x - single * 40, center_y + single * 35, single * 3.5, single * 3.5);//左下角圆
	ege_fillellipse(center_x + single * 36.5, center_y + single * 35, single * 3.5, single * 3.5);//右下角圆
	setlinewidth(side / 75);
	ege_point points2[4] = {// 左中弧线
		center_x - single * 39,center_y - single * 18,//3
		center_x - single * 40.5,center_y - single * 15,//4
		center_x - single * 40.5,center_y - single * 15,//4
		center_x - single * 43,center_y - single * 14//5
	};
	ege_bezier(4, points2);
	ege_point points3[4] = {//右中弧线
		center_x + single * 39,center_y - single * 18,//3
		center_x + single * 40.5,center_y - single * 15,//4
		center_x + single * 40.5,center_y - single * 15,//4
		center_x + single * 43,center_y - single * 14//5
	};
	ege_bezier(4, points3);

	draw_RouteTable_down2_circle(center_x - single * 33.7, center_y + single * 5, single * 3.6);//(1,1)
	draw_RouteTable_down2_circle(center_x - single * 33.7, center_y + single * 14, single * 3.6);//(1,2)
	draw_RouteTable_down2_circle(center_x - single * 33.7, center_y + single * 23, single * 3.6);//(1,3)
	draw_RouteTable_down2_circle(center_x - single * 33.7, center_y + single * 32, single * 3.6);//(1,4)
	draw_RouteTable_down2_circle(center_x - single * 24.6, center_y + single * 5, single * 3.6);//(2,1)
	draw_RouteTable_down2_circle(center_x - single * 24.6, center_y + single * 14, single * 3.6);//(2,2)
	draw_RouteTable_down2_circle(center_x - single * 24.6, center_y + single * 23, single * 3.6);//(2,3)
	draw_RouteTable_down2_circle(center_x - single * 24.6, center_y + single * 32, single * 3.6);//(2,4)
	draw_RouteTable_down2_circle(center_x - single * 15.5, center_y + single * 5, single * 3.6);//(3,1)
	draw_RouteTable_down2_circle(center_x - single * 15.5, center_y + single * 14, single * 3.6);//(3,2)
	draw_RouteTable_down2_circle(center_x - single * 15.5, center_y + single * 23, single * 3.6);//(3,3)
	draw_RouteTable_down2_circle(center_x - single * 15.5, center_y + single * 32, single * 3.6);//(3,4)

	setbkmode(TRANSPARENT);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setfont(single * 5, 0, "黑体");
	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_drawtext("1", center_x - single * 33.5, center_y + single * 5.1);
	ege_drawtext("4", center_x - single * 33.6, center_y + single * 14.2);
	ege_drawtext("7", center_x - single * 33.6, center_y + single * 23.2);
	ege_drawtext(".", center_x - single * 33.1, center_y + single * 30.8);
	ege_drawtext("2", center_x - single * 24.4, center_y + single * 5.1);
	ege_drawtext("5", center_x - single * 24.4, center_y + single * 14.2);
	ege_drawtext("8", center_x - single * 24.4, center_y + single * 23.2);
	ege_drawtext("0", center_x - single * 24.4, center_y + single * 32.2);
	ege_drawtext("3", center_x - single * 15.3, center_y + single * 5.1);
	ege_drawtext("6", center_x - single * 15.3, center_y + single * 14.2);
	ege_drawtext("9", center_x - single * 15.3, center_y + single * 23.2);
	setfont(single * 4, 0, "黑体");
	ege_drawtext("+", center_x - single * 16.3, center_y + single * 31.5);
	ege_drawtext("/", center_x - single * 15, center_y + single * 32.4);
	ege_drawtext("-", center_x - single * 14, center_y + single * 33.4);
	
	setfont(single * 5, 0, "黑体");
	setcolor(EGEARGB(MainPanelLight, 136, 97, 67));
	ege_drawtext("1", center_x - single * 33.5, center_y + single * 5.1);
	ege_drawtext("4", center_x - single * 33.6, center_y + single * 14.2);
	ege_drawtext("7", center_x - single * 33.6, center_y + single * 23.2);
	ege_drawtext(".", center_x - single * 33.1, center_y + single * 30.8);
	ege_drawtext("2", center_x - single * 24.4, center_y + single * 5.1);
	ege_drawtext("5", center_x - single * 24.4, center_y + single * 14.2);
	ege_drawtext("8", center_x - single * 24.4, center_y + single * 23.2);
	ege_drawtext("0", center_x - single * 24.4, center_y + single * 32.2);
	ege_drawtext("3", center_x - single * 15.3, center_y + single * 5.1);
	ege_drawtext("6", center_x - single * 15.3, center_y + single * 14.2);
	ege_drawtext("9", center_x - single * 15.3, center_y + single * 23.2);
	setfont(single * 4, 0, "黑体");
	ege_drawtext("+", center_x - single * 16.3, center_y + single * 31.5);
	ege_drawtext("/", center_x - single * 15, center_y + single * 32.4);
	ege_drawtext("-", center_x - single * 14, center_y + single * 33.4);

	draw_RouteTable_down2_square(center_x - single * 4.8, center_y - single * 13, single * 7);//(1,1)
	draw_RouteTable_down2_square(center_x - single * 4.8, center_y - single * 4.1, single * 7);//(1,2)
	draw_RouteTable_down2_square(center_x - single * 4.8, center_y + single * 4.7, single * 7);//(1,3)
	draw_RouteTable_down2_square(center_x - single * 4.8, center_y + single * 14, single * 7);//(1,4)
	draw_RouteTable_down2_square(center_x - single * 4.8, center_y + single * 23, single * 7);//(1,5)
	draw_RouteTable_down2_square(center_x - single * 4.8, center_y + single * 32, single * 7);//(1,6)
	draw_RouteTable_down2_square(center_x + single * 5.2, center_y - single * 13, single * 7);//(2,1)
	draw_RouteTable_down2_square(center_x + single * 5.2, center_y - single * 4.1, single * 7);//(2,2)
	draw_RouteTable_down2_square(center_x + single * 5.2, center_y + single * 4.7, single * 7);//(2,3)
	draw_RouteTable_down2_square(center_x + single * 5.2, center_y + single * 14, single * 7);//(2,4)
	draw_RouteTable_down2_square(center_x + single * 5.2, center_y + single * 23, single * 7);//(2,5)
	draw_RouteTable_down2_square(center_x + single * 5.2, center_y + single * 32, single * 7);//(2,6)
	draw_RouteTable_down2_square(center_x + single * 15.2, center_y - single * 13, single * 7);//(3,1)
	draw_RouteTable_down2_square(center_x + single * 15.2, center_y - single * 4.1, single * 7);//(3,2)
	draw_RouteTable_down2_square(center_x + single * 15.2, center_y + single * 4.7, single * 7);//(3,3)
	draw_RouteTable_down2_square(center_x + single * 15.2, center_y + single * 14, single * 7);//(3,4)
	draw_RouteTable_down2_square(center_x + single * 15.2, center_y + single * 23, single * 7);//(3,5)
	draw_RouteTable_down2_square(center_x + single * 15.2, center_y + single * 32, single * 7);//(3,6)
	draw_RouteTable_down2_square(center_x + single * 24.8, center_y - single * 13, single * 7);//(4,1)
	draw_RouteTable_down2_square(center_x + single * 24.8, center_y - single * 4.1, single * 7);//(4,2)
	draw_RouteTable_down2_square(center_x + single * 24.8, center_y + single * 4.7, single * 7);//(4,3)
	draw_RouteTable_down2_square(center_x + single * 24.8, center_y + single * 14, single * 7);//(4,4)
	draw_RouteTable_down2_square(center_x + single * 24.8, center_y + single * 23, single * 7);//(4,5)
	draw_RouteTable_down2_square(center_x + single * 24.8, center_y + single * 32, single * 7);//(4,6)
	draw_RouteTable_down2_square(center_x + single * 34.4, center_y - single * 13, single * 7);//(5,1)
	draw_RouteTable_down2_square(center_x + single * 34.4, center_y - single * 4.1, single * 7);//(5,2)
	draw_RouteTable_down2_square(center_x + single * 34.4, center_y + single * 4.7, single * 7);//(5,3)
	draw_RouteTable_down2_square(center_x + single * 34.4, center_y + single * 14, single * 7);//(5,4)
	draw_RouteTable_down2_square(center_x + single * 34.4, center_y + single * 23, single * 7);//(5,5)
	draw_RouteTable_down2_square(center_x + single * 34.4, center_y + single * 32, single * 7);//(5,6)

	setbkmode(TRANSPARENT);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	setfont(single * 5, 0, "黑体");
	ege_drawtext("A", center_x - single * 4.8, center_y - single * 12.9);
	ege_drawtext("F", center_x - single * 4.8, center_y - single * 4);
	ege_drawtext("K", center_x - single * 4.8, center_y + single * 4.8);
	ege_drawtext("P", center_x - single * 4.8, center_y + single * 14.1);
	ege_drawtext("U", center_x - single * 4.8, center_y + single * 23.1);
	ege_drawtext("Z", center_x - single * 4.8, center_y + single * 32.1);
	ege_drawtext("B", center_x + single * 5.2, center_y - single * 12.9);
	ege_drawtext("G", center_x + single * 5.2, center_y - single * 4);
	ege_drawtext("L", center_x + single * 5.2, center_y + single * 4.8);
	ege_drawtext("Q", center_x + single * 5.2, center_y + single * 14.1);
	ege_drawtext("V", center_x + single * 5.2, center_y + single * 23.1);
	ege_drawtext("", center_x + single * 5.2, center_y + single * 32.1);
	ege_drawtext("C", center_x + single * 15.2, center_y - single * 12.9);
	ege_drawtext("H", center_x + single * 15.2, center_y - single * 4);
	ege_drawtext("M", center_x + single * 15.2, center_y + single * 4.8);
	ege_drawtext("R", center_x + single * 15.2, center_y + single * 14.1);
	ege_drawtext("W", center_x + single * 15.2, center_y + single * 23.1);
	setfont(single * 3, 0, "黑体");
	ege_drawtext("DEL", center_x + single * 15.2, center_y + single * 32.1);
	setfont(single * 5, 0, "黑体");
	ege_drawtext("D", center_x + single * 24.8, center_y - single * 12.9);
	ege_drawtext("I", center_x + single * 24.8, center_y - single * 4);
	ege_drawtext("N", center_x + single * 24.8, center_y + single * 4.8);
	ege_drawtext("S", center_x + single * 24.8, center_y + single * 14.1);
	ege_drawtext("X", center_x + single * 24.8, center_y + single * 23.1);
	ege_drawtext("/", center_x + single * 24.8, center_y + single * 32.1);
	ege_drawtext("E", center_x + single * 34.4, center_y - single * 12.9);
	ege_drawtext("J", center_x + single * 34.4, center_y - single * 4);
	ege_drawtext("O", center_x + single * 34.4, center_y + single * 4.8);
	ege_drawtext("T", center_x + single * 34.4, center_y + single * 14.1);
	ege_drawtext("Y", center_x + single * 34.4, center_y + single * 23.1);
	setfont(single * 3, 0, "黑体");
	ege_drawtext("CLR", center_x + single * 34.4, center_y + single * 32.1);
	
	setfont(single * 5, 0, "黑体");
	setcolor(EGEARGB(MainPanelLight, 136, 97, 67));
	ege_drawtext("A", center_x - single * 4.8, center_y - single * 12.9);
	ege_drawtext("F", center_x - single * 4.8, center_y - single * 4);
	ege_drawtext("K", center_x - single * 4.8, center_y + single * 4.8);
	ege_drawtext("P", center_x - single * 4.8, center_y + single * 14.1);
	ege_drawtext("U", center_x - single * 4.8, center_y + single * 23.1);
	ege_drawtext("Z", center_x - single * 4.8, center_y + single * 32.1);
	ege_drawtext("B", center_x + single * 5.2, center_y - single * 12.9);
	ege_drawtext("G", center_x + single * 5.2, center_y - single * 4);
	ege_drawtext("L", center_x + single * 5.2, center_y + single * 4.8);
	ege_drawtext("Q", center_x + single * 5.2, center_y + single * 14.1);
	ege_drawtext("V", center_x + single * 5.2, center_y + single * 23.1);
	ege_drawtext("", center_x + single * 5.2, center_y + single * 32.1);
	ege_drawtext("C", center_x + single * 15.2, center_y - single * 12.9);
	ege_drawtext("H", center_x + single * 15.2, center_y - single * 4);
	ege_drawtext("M", center_x + single * 15.2, center_y + single * 4.8);
	ege_drawtext("R", center_x + single * 15.2, center_y + single * 14.1);
	ege_drawtext("W", center_x + single * 15.2, center_y + single * 23.1);
	setfont(single * 3, 0, "黑体");
	ege_drawtext("DEL", center_x + single * 15.2, center_y + single * 32.1);
	setfont(single * 5, 0, "黑体");
	ege_drawtext("D", center_x + single * 24.8, center_y - single * 12.9);
	ege_drawtext("I", center_x + single * 24.8, center_y - single * 4);
	ege_drawtext("N", center_x + single * 24.8, center_y + single * 4.8);
	ege_drawtext("S", center_x + single * 24.8, center_y + single * 14.1);
	ege_drawtext("X", center_x + single * 24.8, center_y + single * 23.1);
	ege_drawtext("/", center_x + single * 24.8, center_y + single * 32.1);
	ege_drawtext("E", center_x + single * 34.4, center_y - single * 12.9);
	ege_drawtext("J", center_x + single * 34.4, center_y - single * 4);
	ege_drawtext("O", center_x + single * 34.4, center_y + single * 4.8);
	ege_drawtext("T", center_x + single * 34.4, center_y + single * 14.1);
	ege_drawtext("Y", center_x + single * 34.4, center_y + single * 23.1);
	setfont(single * 3, 0, "黑体");
	ege_drawtext("CLR", center_x + single * 34.4, center_y + single * 32.1);
	draw_RouteTable_down2_square_poly(center_x + single * 15.2, center_y + single * 23, single * 2.5);
	draw_RouteTable_down2_square_poly(center_x + single * 24.8, center_y + single * 4.7, single * 2.5);
	draw_RouteTable_down2_square_poly(center_x + single * 24.8, center_y + single * 14, single * 2.5);
	draw_RouteTable_down2_square_poly(center_x + single * 34.4, center_y - single * 13, single * 2.5);

	setfillcolor(EGEARGB(0xff, 25, 22, 12));
	ege_fillellipse(center_x - single * 42.5, center_y - single * 13, single * 3, single * 3);
	ege_fillellipse(center_x + single * 40, center_y - single * 13, single * 3, single * 3);
	setfillcolor(BLACK);
	ege_fillellipse(center_x - single * 42.5, center_y + single * 19, single * 3, single * 3);
	ege_fillellipse(center_x + single * 40, center_y + single * 19, single * 3, single * 3);
	ege_fillrect(center_x - single * 42.2, center_y - single * 8, single * 2.5, single * 24);
	ege_fillrect(center_x + single * 40, center_y - single * 8, single * 2.5, single * 24);

	setcolor(EGEARGB(50, 177, 177, 179));
	setfont(single * 2.5, 0, "黑体");
	ege_drawtext("D", center_x - single * 41, center_y - single * 6);
	ege_drawtext("S", center_x - single * 41, center_y - single * 3.5);
	ege_drawtext("P", center_x - single * 41, center_y - single * 1);
	ege_drawtext("Y", center_x - single * 41, center_y + single * 1.5);

	ege_drawtext("F", center_x - single * 41, center_y + single * 6);
	ege_drawtext("A", center_x - single * 41, center_y + single * 8.5);
	ege_drawtext("I", center_x - single * 41, center_y + single * 11);
	ege_drawtext("L", center_x - single * 41, center_y + single * 13.5);

	ege_drawtext("M", center_x + single * 41.4, center_y - single * 5);
	ege_drawtext("S", center_x + single * 41.4, center_y - single * 2.5);
	ege_drawtext("G", center_x + single * 41.4, center_y);

	ege_drawtext("O", center_x + single * 41.4, center_y + single * 5);
	ege_drawtext("F", center_x + single * 41.4, center_y + single * 7.5);
	ege_drawtext("S", center_x + single * 41.4, center_y + single * 10);
	ege_drawtext("T", center_x + single * 41.4, center_y + single * 12.5);

	setfillcolor(EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	double left_x = center_x - single * 46.5, left_y = center_y - single * 31;
	ege_point points4[7] = {
		left_x,left_y,//1
		left_x,left_y + single * 3,//2
		left_x + single * 2.4,left_y + single * 3,//3
		left_x + single * 2.4,left_y + single * 14,//4
		left_x + single * 6,left_y + single * 14,//5
		left_x + single * 6,left_y,//6
		left_x,left_y
	};
	ege_fillpoly(7, points4);

	double right_x = center_x + single * 46.5, right_y = center_y - single * 31;
	ege_point points5[7] = {
		right_x, right_y,//1
		right_x, right_y + single * 3,//2
		right_x - single * 2.4, right_y + single * 3,//3
		right_x - single * 2.4, right_y + single * 14,//4
		right_x - single * 6, right_y + single * 14,//5
		right_x - single * 6, right_y,//6
		right_x, right_y
	};
	ege_fillpoly(7, points5);

	draw_RouteTable_bigScrew2(center_x - single * 43.4, center_y - single * 34, single * 2.5, 90);
	draw_RouteTable_bigScrew2(center_x + single * 43.4, center_y - single * 34, single * 2.5, 90);

	setfillcolor(EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	ege_fillrect(center_x - single * 46, center_y - single * 26, single * 1.6, single * 48);
	ege_fillrect(center_x + single * 44.5, center_y - single * 26, single * 1.6, single * 48);

	draw_RouteTable_bigScrew2(center_x - single * 43.8, center_y + single * 28, single * 3, 90);
	draw_RouteTable_bigScrew2(center_x + single * 43.8, center_y + single * 28, single * 3, 90);
}

// 下半部分的最下一层的圆形
void draw_RouteTable_down2_circle(double center_x, double center_y, double side) {
	setfillcolor(BLACK);
	ege_fillellipse(center_x - side, center_y - side, side * 2, side * 2);
	
	if (FMC_mouse_real_x >= center_x - side / 2 && FMC_mouse_real_x <= center_x + side / 2 && FMC_mouse_real_y >= center_y - side / 2 && FMC_mouse_real_y <= center_y + side / 2)
	{
		setcolor(WHITE);
		setlinewidth(1.5);
		ege_ellipse(center_x - side, center_y - side, side * 2 + side * 0.01, side * 2 + side * 0.01);
	}
}


// 下半部分的最下一层的正方形
void draw_RouteTable_down2_square(double center_x, double center_y, double side) {
	setfillcolor(BLACK);
	ege_fillrect(center_x - side / 2, center_y - side / 2, side, side);

	mousepos(&FMC_mouse_x, &FMC_mouse_y);
	FMC_mouse_real_x = FMC_mouse_x;
	FMC_mouse_real_y = FMC_mouse_y;

	if (FMC_mouse_real_x >= center_x - side / 2 && FMC_mouse_real_x <= center_x + side / 2 && FMC_mouse_real_y >= center_y - side / 2 && FMC_mouse_real_y <= center_y + side / 2)
	{
		setcolor(WHITE);
		setlinewidth(1.5);
		ege_rectangle(center_x - side / 2 - side * 0.005, center_y - side / 2 - side * 0.005, side + side * 0.01, side + side * 0.01);
	}
}

// 下半部分的最下一层的正方形中间的线框
void draw_RouteTable_down2_square_poly(double center_x, double center_y, double side) {
	setlinewidth(side / 11.1940298);
	setcolor(EGEARGB(0XFF,0X50,0X50,0X50));
	ege_point points1[5] = {
		center_x - side,center_y - side,
		center_x - side,center_y + side,
		center_x + side,center_y + side,
		center_x + side,center_y - side,
		center_x - side,center_y - side
	};
	ege_drawpoly(5, points1);
	
	setcolor(EGEARGB(MainPanelLight, 136, 97, 67));
	ege_point points[5] = {
		center_x - side,center_y - side,
		center_x - side,center_y + side,
		center_x + side,center_y + side,
		center_x + side,center_y - side,
		center_x - side,center_y - side
	};
	ege_drawpoly(5, points);
}

void FMC_Scanner(FMC_buttoninformation *FMC_letterbutton, double side)
{
	double single = side / 67 * 7;
	mousepos(&FMC_mouse_x, &FMC_mouse_y);
	FMC_mouse_real_x = FMC_mouse_x;
	FMC_mouse_real_y = FMC_mouse_y;
	
	for (int i = 0; i < 42; i++)
	{
		double button_x = FMC_letterbutton[i].FMC_button_x;
		double button_y = FMC_letterbutton[i].FMC_button_y;
		//ege_rectangle(button_x - single / 2, button_y - single / 2, single, single);
		if (FMC_mouse_real_x >= button_x - single / 2 && FMC_mouse_real_x <= button_x + single / 2 && FMC_mouse_real_y >= button_y - single / 2 && FMC_mouse_real_y <= button_y + single / 2)
		{
			if ((i <= 16 || (i >= 18 && i <= 28) || (i >= 30 && i <= 42)) && GetAsyncKeyState(0x02) & 0x0001)
			{
				strcat_s(inputment, 64, FMC_letterbutton[i].FMC_button_information);
			}
			else if (i == 17 && GetAsyncKeyState(0x02) & 0x0001)
			{
				if (inputment[0] != '\0')
				{
					inputment[strlen(inputment) - 1] = '\0';
				}
			}
			else if (i == 29 && GetAsyncKeyState(0x02) & 0x0001)
			{
				strcpy_s(inputment, 64, "");
			}
		}
	}
	if (FMC_mode == 1)
		FMC_Scanner_panel_2(inputment, FMC_button_mode);
	else if (FMC_mode == 6)
		FMC_Scanner_panel_7(inputment, FMC_button_mode);
	if (FMC_button_mode != 0)
	{
		strcpy_s(inputment, 64, "");
		FMC_button_mode = 0;
	}
	//ege_drawtext(inputment, 400, 400);
}


void draw_FMC(double center_x, double center_y, double side) {
	FMC_origin_center_x_down1 = center_x;
	FMC_origin_center_y_down1 = center_y - side / 3.5;
	FMC_origin_center_x_down2 = center_x;
	FMC_origin_center_y_down2 = center_y;
	FMC_origin_center_x_up = center_x;
	FMC_origin_center_y_up = center_y - side * 1.055;
	double single = side / 67;
	FMC_buttoninformation FMC_letterbutton[42] = {
		{center_x - single * 4.8, center_y - single * 13, "A"},//(1,1)
		{center_x - single * 4.8, center_y - single * 4.1, "F"},//(1,2)
		{center_x - single * 4.8, center_y + single * 4.7, "K"},//(1,3)
		{center_x - single * 4.8, center_y + single * 14, "P"},//(1,4)
		{center_x - single * 4.8, center_y + single * 23, "U"},//(1,5)
		{center_x - single * 4.8, center_y + single * 32, "Z"},//(1,6)
		{center_x + single * 5.2, center_y - single * 13, "B"},//(2,1)
		{center_x + single * 5.2, center_y - single * 4.1, "G"},//(2,2)
		{center_x + single * 5.2, center_y + single * 4.7, "L"},//(2,3)
		{center_x + single * 5.2, center_y + single * 14, "Q"},//(2,4)
		{center_x + single * 5.2, center_y + single * 23, "V"},//(2,5)
		{center_x + single * 5.2, center_y + single * 32, "\0" },//(2,6)
		{center_x + single * 15.2, center_y - single * 13, "C"},//(3,1)
		{center_x + single * 15.2, center_y - single * 4.1, "H"},//(3,2)
		{center_x + single * 15.2, center_y + single * 4.7, "M"},//(3,3)
		{center_x + single * 15.2, center_y + single * 14, "R"},//(3,4)
		{center_x + single * 15.2, center_y + single * 23, "W"},//(3,5)
		{center_x + single * 15.2, center_y + single * 32, "DEL"},//(3,6)
		{center_x + single * 24.8, center_y - single * 13, "D"},//(4,1)
		{center_x + single * 24.8, center_y - single * 4.1, "I"},//(4,2)
		{center_x + single * 24.8, center_y + single * 4.7, "N"},//(4,3)
		{center_x + single * 24.8, center_y + single * 14, "S"},//(4,4)
		{center_x + single * 24.8, center_y + single * 23, "X"},//(4,5)
		{ center_x + single * 24.8, center_y + single * 32, "/"},//(4,6)
		{ center_x + single * 34.4, center_y - single * 13, "E"},//(5,1)
		{center_x + single * 34.4, center_y - single * 4.1, "J"},//(5,2)
		{center_x + single * 34.4, center_y + single * 4.7, "O"},//(5,3)
		{center_x + single * 34.4, center_y + single * 14, "T"},//(5,4)
		{center_x + single * 34.4, center_y + single * 23, "Y"},//(5,5)
		{center_x + single * 34.4, center_y + single * 32, "CLR"},//(5,6)
		{center_x - single * 33.7, center_y + single * 5, "1"},//(1,1)
		{center_x - single * 33.7, center_y + single * 14, "4"},//(1,2)
		{center_x - single * 33.7, center_y + single * 23, "7" },//(1,3)
		{center_x - single * 33.7, center_y + single * 32, "."},//(1,4)
		{center_x - single * 24.6, center_y + single * 5, "2" },//(2,1)
		{center_x - single * 24.6, center_y + single * 14, "5" },//(2,2)
		{center_x - single * 24.6, center_y + single * 23, "8" },//(2,3)
		{center_x - single * 24.6, center_y + single * 32, "0" },//(2,4)
		{center_x - single * 15.5, center_y + single * 5, "3" },//(3,1)
		{center_x - single * 15.5, center_y + single * 14, "6" },//(3,2)
		{center_x - single * 15.5, center_y + single * 23, "9" },//(3,3)
		{center_x - single * 15.5, center_y + single * 32, "+" },//(3,4)
	};

	//side是宽，中心点的坐标是对于下半部分而言的
	if (FMC_mode == 0) 
	{
		draw_INDEX_panel_1(side, center_x, center_y - side * 1.055);
	}
	else if (FMC_mode == 1)
	{
		draw_INDEX_panel_2(side, center_x, center_y - side * 1.055);
	}
	else if (FMC_mode == 2)
	{
		draw_INDEX_panel_3(side, center_x, center_y - side * 1.055);
	}
	else if (FMC_mode == 3)
	{
		draw_INDEX_panel_4(side, center_x, center_y - side * 1.055);
	}
	else if (FMC_mode == 4)
	{
		draw_INDEX_panel_5(side, center_x, center_y - side * 1.055);
	}
	else if (FMC_mode == 5)
	{
		draw_DEPART1_panel_6(side, center_x, center_y - side * 1.055);
	}
	else if (FMC_mode == 6)
	{
		draw_FPLN_panel_7(side, center_x, center_y - side * 1.055);
	}
	else if (FMC_mode == 7)
	{
		draw_ROUTE_MENU(side, center_x, center_y - side * 1.055);
	}
	else if (FMC_mode == 8)
	{
		draw_CO_ROUTE_LIST(side, center_x, center_y - side * 1.055);
	}
	draw_RouteTable_up(center_x, center_y - side * 1.055, side);
	
	draw_RouteTable_down(center_x, center_y, side);

	FMC_Scanner(FMC_letterbutton, side);
	
	for (int i = 0; i < 12; i++) {
		if (i > 0 && i < 11) {
			strcpy(FMC_routepoints[i], FMC_getpointsinformation().rountpoints[i - 1]);
		}
		else if (i == 0){
			strcpy(FMC_routepoints[i], getorigin());
		}
		else if (i == 11) {
			strcpy(FMC_routepoints[i], getdest());
		}
		//strcpy(FMC_routepoints[i], FMC_getpointsinformation().rountpoints[i]);
//		printf("%s ",FMC_routepoints[i]);
	}
//	printf("\n");
	
	
	extern vector<WAYPOINT> route;
	
	for (int i = 0; i < 12; i++) {
		if (strcmp(FMC_lastroutepoints[i],FMC_routepoints[i]) != 0) {
			
			route.clear();
			
			for(int i = 0;i < 12;i ++){
				if(strlen(FMC_routepoints[i]) > 2){
					
					for(auto it : airports){
						if(!strcmp(it.name, FMC_routepoints[i])){
							route.push_back(it);
							break;
						}
					}
					
					for(auto it : VORs){
						if(!strcmp(it.name, FMC_routepoints[i])){
							route.push_back(it);
							break;
						}
					}
					
					for(auto it : waypoints){
						if(!strcmp(it.name, FMC_routepoints[i])){
							route.push_back(it);
							break;
						}
					}
					
				}
			}
			
			
			break;
		}
	}
	
	for (int i = 0; i < 12; i++) {
		strcpy(FMC_lastroutepoints[i], FMC_routepoints[i]);
	}

	
	
}

