
#include<graphics.h>
#include<math.h>
#include<Windows.h>
#include "DrawScrew.h"
#include "G_variable.h"


extern int alert_pullup;
extern int alert_beloGS;
extern int alert_ALT;
extern int alert_MDA;
extern int alert_autoPilot;

int showsomedata = 0;


void draw_back(double center_x, double center_y, double unitLength) {
	
	
	setfont(0,0,"微软雅黑");
	
	setcolor(BLACK);
	setlinewidth(unitLength / 10);
	ege_line(center_x - unitLength * 24, center_y - unitLength * 14, center_x - unitLength * 5, center_y - unitLength * 16);
	ege_line(center_x + unitLength * 5, center_y - unitLength * 16, center_x - unitLength * 5, center_y - unitLength * 16);
	
	ege_line(center_x + unitLength * 5, center_y - unitLength * 16, center_x  + unitLength * 24, center_y - unitLength * 20);
	
	ege_line(center_x + unitLength * 5, center_y + unitLength * 24, center_x + unitLength * 5, center_y - unitLength * 16);
	ege_line(center_x - unitLength * 5, center_y + unitLength * 24, center_x - unitLength * 5, center_y - unitLength * 16);
	setcolor(EGEARGB(0X20, 0XFF, 0XFF, 0XFF));
	setlinewidth(unitLength / 20);
	
	ege_line(center_x - unitLength * 24, center_y - unitLength * 14 - unitLength / 20, center_x - unitLength * 5, center_y - unitLength * 16 - unitLength / 20);
	ege_line(center_x + unitLength * 5, center_y - unitLength * 16 - unitLength / 20, center_x - unitLength * 5, center_y - unitLength * 16 - unitLength / 20);
	
	ege_line(center_x + unitLength * 5, center_y - unitLength * 16 - unitLength / 20, center_x + unitLength * 24, center_y - unitLength * 20);
	
	ege_line(center_x + unitLength * 5 + unitLength / 20, center_y + unitLength * 24, center_x + unitLength * 5 + unitLength / 20, center_y - unitLength * 16);
	ege_line(center_x - unitLength * 5 - unitLength / 20, center_y + unitLength * 24, center_x - unitLength * 5 - unitLength / 20, center_y - unitLength * 16);
	
	//阴影
	setfillcolor(BLACK);
	//右2
	ege_fillrect(center_x + unitLength * 5 + unitLength / 20 * 2, center_y - unitLength * 10 - unitLength / 20 * 11, unitLength * 2.46, unitLength * 2.7);
	ege_fillrect(center_x + unitLength * 5 + unitLength / 20 * 2, center_y - unitLength * 13 - unitLength / 20 * 11, unitLength * 2.46, unitLength * 2.7);
	//左1
	ege_fillrect(center_x - unitLength * 13 + unitLength / 20 * 2, center_y - unitLength * 10 - unitLength / 20 * 11, unitLength * 2.46, unitLength * 2.7);
	//左二小矩形
	ege_fillrect(center_x - unitLength * 9 + unitLength / 20 * 3, center_y - unitLength * 9.7 - unitLength / 20 * 7, unitLength * 2.4, unitLength * 1.4);
	ege_fillrect(center_x - unitLength * 9 + unitLength / 20 * 3, center_y - unitLength * 8.6 - unitLength / 20 * 7, unitLength * 2.4, unitLength * 1.4);
	
	
	
	
	//主体
	setfillcolor(EGEARGB(0XFF, 0X32, 0X15, 0X04));
	//右2
	ege_fillrect(center_x + unitLength * 5 + unitLength / 20 * 5, center_y - unitLength * 10 - unitLength / 20 * 4, unitLength * 2.16, unitLength * 2.1);
	ege_fillrect(center_x + unitLength * 5 + unitLength / 20 * 5, center_y - unitLength * 13 - unitLength / 20 * 4, unitLength * 2.16, unitLength * 2.1);
	//左1
	ege_fillrect(center_x - unitLength * 13 + unitLength / 20 * 5, center_y - unitLength * 10 - unitLength / 20 * 4, unitLength * 2.16, unitLength * 2.1);
	//左二小矩形
	setfillcolor(EGEARGB(0XFF, 0X11, 0X12, 0X14));
	ege_fillrect(center_x - unitLength * 9 + unitLength / 20 * 5, center_y - unitLength * 9.7 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);
	ege_fillrect(center_x - unitLength * 9 + unitLength / 20 * 5, center_y - unitLength * 8.6 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);
	
	
	
	//右小矩形方阵
	ege_enable_aa(false);
	setcolor(EGEARGB(0XFF, 0X22, 0X27, 0X2D));
	int right_pointNums = 25;
	ege_point right_ploypoints[25] = {
		{center_x + unitLength * 8.2, center_y - unitLength * 13.2 - unitLength / 20 * 4},{center_x + unitLength * 8.3, center_y - unitLength * 13.6 - unitLength / 20 * 4},
		{center_x + unitLength * 8.4, center_y - unitLength * 13.7 - unitLength / 20 * 4},{center_x + unitLength * 8.6, center_y - unitLength * 13.8 - unitLength / 20 * 4},
		
		{center_x + unitLength * 14.1, center_y - unitLength * 13.8 - unitLength / 20 * 4},{center_x + unitLength * 14.1, center_y - unitLength * 13.8 - unitLength / 20 * 4},
		{center_x + unitLength * 14.1, center_y - unitLength * 13.8 - unitLength / 20 * 4},
		
		{center_x + unitLength * 14.3, center_y - unitLength * 13.7 - unitLength / 20 * 4},{center_x + unitLength * 14.4, center_y - unitLength * 13.6 - unitLength / 20 * 4},
		{center_x + unitLength * 14.5, center_y - unitLength * 13.2 - unitLength / 20 * 4},
		
		{center_x + unitLength * 14.5, center_y - unitLength * 8.4 - unitLength / 20 * 4},{center_x + unitLength * 14.5, center_y - unitLength * 8.4 - unitLength / 20 * 4},
		{center_x + unitLength * 14.5, center_y - unitLength * 8.4 - unitLength / 20 * 4},
		
		{center_x + unitLength * 14.4, center_y - unitLength * 8 - unitLength / 20 * 4},{center_x + unitLength * 14.3, center_y - unitLength * 7.9 - unitLength / 20 * 4},
		{center_x + unitLength * 14.1, center_y - unitLength * 7.8 - unitLength / 20 * 4},
		
		{center_x + unitLength * 8.6, center_y - unitLength * 7.8 - unitLength / 20 * 4},{center_x + unitLength * 8.6, center_y - unitLength * 7.8 - unitLength / 20 * 4},
		{center_x + unitLength * 8.6, center_y - unitLength * 7.8 - unitLength / 20 * 4},
		
		{center_x + unitLength * 8.4, center_y - unitLength * 7.9 - unitLength / 20 * 4},{center_x + unitLength * 8.3, center_y - unitLength * 8 - unitLength / 20 * 4},
		{center_x + unitLength * 8.2, center_y - unitLength * 8.4 - unitLength / 20 * 4},
		
		{center_x + unitLength * 8.2, center_y - unitLength * 13.2 - unitLength / 20 * 4},{center_x + unitLength * 8.2, center_y - unitLength * 13.2 - unitLength / 20 * 4},
		{center_x + unitLength * 8.2, center_y - unitLength * 13.2 - unitLength / 20 * 4},
		
	};
	setfillcolor(EGEARGB(0XFF, 0X22, 0X27, 0X2D));
	ege_bezier(right_pointNums, right_ploypoints);
	floodfill(center_x + unitLength * 10.2, center_y - unitLength * 10.4 - unitLength / 20 * 4, EGEARGB(0XFF, 0X22, 0X27, 0X2D));
	
	setcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	int right_pointNums_top = 25;
	ege_point right_ploypoints_top[25] = {
		{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},{center_x + unitLength * 9.8, center_y - unitLength * 15.8 - unitLength / 20 * 4},
		{center_x + unitLength * 9.9, center_y - unitLength * 15.9 - unitLength / 20 * 4},{center_x + unitLength * 10.1, center_y - unitLength * 16 - unitLength / 20 * 4},
		
		{center_x + unitLength * 12.6, center_y - unitLength * 16 - unitLength / 20 * 4},{center_x + unitLength * 12.6, center_y - unitLength * 16 - unitLength / 20 * 4},
		{center_x + unitLength * 12.6, center_y - unitLength * 16 - unitLength / 20 * 4},
		
		{center_x + unitLength * 12.8, center_y - unitLength * 15.9 - unitLength / 20 * 4},{center_x + unitLength * 12.9, center_y - unitLength * 15.8 - unitLength / 20 * 4},
		{center_x + unitLength * 13, center_y - unitLength * 15.4 - unitLength / 20 * 4},
		
		{center_x + unitLength * 13, center_y - unitLength * 14.7 - unitLength / 20 * 4},{center_x + unitLength * 13, center_y - unitLength * 14.7 - unitLength / 20 * 4},
		{center_x + unitLength * 13, center_y - unitLength * 14.7 - unitLength / 20 * 4},
		
		{center_x + unitLength * 12.9, center_y - unitLength * 14.3 - unitLength / 20 * 4},{center_x + unitLength * 12.8, center_y - unitLength * 14.2 - unitLength / 20 * 4},
		{center_x + unitLength * 12.6, center_y - unitLength * 14.1 - unitLength / 20 * 4},
		
		{center_x + unitLength * 9.9, center_y - unitLength * 14.1 - unitLength / 20 * 4},{center_x + unitLength * 9.9, center_y - unitLength * 14.1 - unitLength / 20 * 4},
		{center_x + unitLength * 9.9, center_y - unitLength * 14.1 - unitLength / 20 * 4},
		
		{center_x + unitLength * 9.9, center_y - unitLength * 14.2 - unitLength / 20 * 4},{center_x + unitLength * 9.8, center_y - unitLength * 14.3 - unitLength / 20 * 4},
		{center_x + unitLength * 9.7, center_y - unitLength * 14.7 - unitLength / 20 * 4},
		
		{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},
		{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},
		
	};
	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_bezier(right_pointNums_top, right_ploypoints_top);
	floodfill(center_x + unitLength * 11.2, center_y - unitLength * 14.4 - unitLength / 20 * 4, EGEARGB(0XFF, 0X00, 0X00, 0X00));
	
	
	int center_pointNums_top = 25;
	ege_point center_ploypoints_top[25] = {
		{center_x - unitLength * 3.9, center_y - unitLength * 12.7 - unitLength / 20 * 4},{center_x - unitLength * 3.8, center_y - unitLength * 13.1 - unitLength / 20 * 4},
		{center_x - unitLength * 3.7, center_y - unitLength * 13.2 - unitLength / 20 * 4},{center_x - unitLength * 3.5, center_y - unitLength * 13.3 - unitLength / 20 * 4},
		
		{center_x + unitLength * 3.1, center_y - unitLength * 13.3 - unitLength / 20 * 4},{center_x + unitLength * 3.1, center_y - unitLength * 13.3 - unitLength / 20 * 4},
		{center_x + unitLength * 3.1, center_y - unitLength * 13.3 - unitLength / 20 * 4},
		
		{center_x + unitLength * 3.3, center_y - unitLength * 13.2 - unitLength / 20 * 4},{center_x + unitLength * 3.4, center_y - unitLength * 13.1 - unitLength / 20 * 4},
		{center_x + unitLength * 3.5, center_y - unitLength * 12.7 - unitLength / 20 * 4},
		
		{center_x + unitLength * 3.5, center_y - unitLength * 12.7 - unitLength / 20 * 4},{center_x + unitLength * 3.5, center_y - unitLength * 12.7 - unitLength / 20 * 4},
		{center_x + unitLength * 3.5, center_y - unitLength * 12.7 - unitLength / 20 * 4},
		
		{center_x + unitLength * 3.4, center_y - unitLength * 12.3 - unitLength / 20 * 4},{center_x + unitLength * 3.3, center_y - unitLength * 12.2 - unitLength / 20 * 4},
		{center_x + unitLength * 3.1, center_y - unitLength * 12.1 - unitLength / 20 * 4},
		
		{center_x - unitLength * 3.5, center_y - unitLength * 12.1 - unitLength / 20 * 4},{center_x - unitLength * 3.5, center_y - unitLength * 12.1 - unitLength / 20 * 4},
		{center_x - unitLength * 3.5, center_y - unitLength * 12.1 - unitLength / 20 * 4},
		
		{center_x - unitLength * 3.7, center_y - unitLength * 12.2 - unitLength / 20 * 4},{center_x - unitLength * 3.8, center_y - unitLength * 12.3 - unitLength / 20 * 4},
		{center_x - unitLength * 3.9, center_y - unitLength * 12.7 - unitLength / 20 * 4},
		
		{center_x - unitLength * 3.9, center_y - unitLength * 12.7 - unitLength / 20 * 4},{center_x - unitLength * 3.9, center_y - unitLength * 12.7 - unitLength / 20 * 4},
		{center_x - unitLength * 3.9, center_y - unitLength * 12.7 - unitLength / 20 * 4}
		
	};
	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_bezier(center_pointNums_top, center_ploypoints_top);
	floodfill(center_x - unitLength * 1.8, center_y - unitLength * 13.2 - unitLength / 20 * 4, EGEARGB(0XFF, 0X00, 0X00, 0X00));
	
	
	setcolor(EGEARGB(0XFF, 0X10, 0X10, 0X10));
	int pointsNum_center = 13;
	ege_point ploypoints_center[13] = {
		{center_x + unitLength * 4 + unitLength / 20 * 2, center_y - unitLength * 9.5 - unitLength / 20 * 11},
		{center_x + unitLength * 5 + unitLength / 20 * 2, center_y - unitLength * 10 - unitLength / 20 * 11},
		{center_x + unitLength * 5 + unitLength / 20 * 2, center_y - unitLength * 10.5 - unitLength / 20 * 11},
		{center_x + unitLength * 4 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20 * 11},
		
		{center_x - unitLength * 4.2 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20 * 11},
		{center_x - unitLength * 4.2 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20 * 11},
		{center_x - unitLength * 4.2 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20 * 11},
		
		{center_x - unitLength * 5.2 + unitLength / 20 * 2, center_y - unitLength * 10.5 - unitLength / 20 * 11},
		{center_x - unitLength * 5.2 + unitLength / 20 * 2, center_y - unitLength * 10 - unitLength / 20 * 11},
		{center_x - unitLength * 4.2 + unitLength / 20 * 2, center_y - unitLength * 9.5 - unitLength / 20 * 11},
		
		{center_x + unitLength * 4 + unitLength / 20 * 2, center_y - unitLength * 9.5 - unitLength / 20 * 11},
		{center_x + unitLength * 4 + unitLength / 20 * 2, center_y - unitLength * 9.5 - unitLength / 20 * 11},
		{center_x + unitLength * 4 + unitLength / 20 * 2, center_y - unitLength * 9.5 - unitLength / 20 * 11}
		
		
	};
	setfillcolor(EGEARGB(0XFF, 0X10, 0X10, 0X10));
	
	ege_bezier(pointsNum_center, ploypoints_center);
	floodfill(center_x - unitLength * 3.2 + unitLength / 20 * 2, center_y - unitLength * 10 - unitLength / 20 * 11, EGEARGB(0XFF, 0X10, 0X10, 0X10));
	
	
	
	ege_enable_aa(true);
	
	
	setcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	int right_pointNums_1 = 25;
	ege_point right_ploypoints_1[25] = {
		{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},{center_x + unitLength * 9.8, center_y - unitLength * 15.8 - unitLength / 20 * 4},
		{center_x + unitLength * 9.9, center_y - unitLength * 15.9 - unitLength / 20 * 4},{center_x + unitLength * 10.1, center_y - unitLength * 16 - unitLength / 20 * 4},
		
		{center_x + unitLength * 12.6, center_y - unitLength * 16 - unitLength / 20 * 4},{center_x + unitLength * 12.6, center_y - unitLength * 16 - unitLength / 20 * 4},
		{center_x + unitLength * 12.6, center_y - unitLength * 16 - unitLength / 20 * 4},
		
		{center_x + unitLength * 12.8, center_y - unitLength * 15.9 - unitLength / 20 * 4},{center_x + unitLength * 12.9, center_y - unitLength * 15.8 - unitLength / 20 * 4},
		{center_x + unitLength * 13, center_y - unitLength * 15.4 - unitLength / 20 * 4},
		
		{center_x + unitLength * 13, center_y - unitLength * 14.7 - unitLength / 20 * 4},{center_x + unitLength * 13, center_y - unitLength * 14.7 - unitLength / 20 * 4},
		{center_x + unitLength * 13, center_y - unitLength * 14.7 - unitLength / 20 * 4},
		
		{center_x + unitLength * 12.9, center_y - unitLength * 14.3 - unitLength / 20 * 4},{center_x + unitLength * 12.8, center_y - unitLength * 14.2 - unitLength / 20 * 4},
		{center_x + unitLength * 12.6, center_y - unitLength * 14.1 - unitLength / 20 * 4},
		
		{center_x + unitLength * 9.9, center_y - unitLength * 14.1 - unitLength / 20 * 4},{center_x + unitLength * 9.9, center_y - unitLength * 14.1 - unitLength / 20 * 4},
		{center_x + unitLength * 9.9, center_y - unitLength * 14.1 - unitLength / 20 * 4},
		
		{center_x + unitLength * 9.9, center_y - unitLength * 14.2 - unitLength / 20 * 4},{center_x + unitLength * 9.8, center_y - unitLength * 14.3 - unitLength / 20 * 4},
		{center_x + unitLength * 9.7, center_y - unitLength * 14.7 - unitLength / 20 * 4},
		
		{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},
		{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},
		
		
	};
	ege_bezier(right_pointNums_1, right_ploypoints_1);
	
	setcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	int right_pointNums_top_1 = 25;
	ege_point right_ploypoints_top_1[25] = {
		{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},{center_x + unitLength * 9.8, center_y - unitLength * 15.8 - unitLength / 20 * 4},
		{center_x + unitLength * 9.9, center_y - unitLength * 15.9 - unitLength / 20 * 4},{center_x + unitLength * 10.1, center_y - unitLength * 16 - unitLength / 20 * 4},
		
		{center_x + unitLength * 12.6, center_y - unitLength * 16 - unitLength / 20 * 4},{center_x + unitLength * 12.6, center_y - unitLength * 16 - unitLength / 20 * 4},
		{center_x + unitLength * 12.6, center_y - unitLength * 16 - unitLength / 20 * 4},
		
		{center_x + unitLength * 12.8, center_y - unitLength * 15.9 - unitLength / 20 * 4},{center_x + unitLength * 12.9, center_y - unitLength * 15.8 - unitLength / 20 * 4},
		{center_x + unitLength * 13, center_y - unitLength * 15.4 - unitLength / 20 * 4},
		
		{center_x + unitLength * 13, center_y - unitLength * 14.7 - unitLength / 20 * 4},{center_x + unitLength * 13, center_y - unitLength * 14.7 - unitLength / 20 * 4},
		{center_x + unitLength * 13, center_y - unitLength * 14.7 - unitLength / 20 * 4},
		
		{center_x + unitLength * 12.9, center_y - unitLength * 14.3 - unitLength / 20 * 4},{center_x + unitLength * 12.8, center_y - unitLength * 14.2 - unitLength / 20 * 4},
		{center_x + unitLength * 12.6, center_y - unitLength * 14.1 - unitLength / 20 * 4},
		
		{center_x + unitLength * 9.9, center_y - unitLength * 14.1 - unitLength / 20 * 4},{center_x + unitLength * 9.9, center_y - unitLength * 14.1 - unitLength / 20 * 4},
		{center_x + unitLength * 9.9, center_y - unitLength * 14.1 - unitLength / 20 * 4},
		
		{center_x + unitLength * 9.9, center_y - unitLength * 14.2 - unitLength / 20 * 4},{center_x + unitLength * 9.8, center_y - unitLength * 14.3 - unitLength / 20 * 4},
		{center_x + unitLength * 9.7, center_y - unitLength * 14.7 - unitLength / 20 * 4},
		
		{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},
		{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},
		
	};
	
	ege_bezier(right_pointNums_top_1, right_ploypoints_top_1);
	
	
	setcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	int pointsNum_center_1 = 13;
	ege_point ploypoints_center_1[13] = {
		{center_x + unitLength * 4 + unitLength / 20 * 2, center_y - unitLength * 9.5 - unitLength / 20 * 11},
		{center_x + unitLength * 5 + unitLength / 20 * 2, center_y - unitLength * 10 - unitLength / 20 * 11},
		{center_x + unitLength * 5 + unitLength / 20 * 2, center_y - unitLength * 10.5 - unitLength / 20 * 11},
		{center_x + unitLength * 4 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20 * 11},
		
		{center_x - unitLength * 4.2 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20 * 11},
		{center_x - unitLength * 4.2 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20 * 11},
		{center_x - unitLength * 4.2 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20 * 11},
		
		{center_x - unitLength * 5.2 + unitLength / 20 * 2, center_y - unitLength * 10.5 - unitLength / 20 * 11},
		{center_x - unitLength * 5.2 + unitLength / 20 * 2, center_y - unitLength * 10 - unitLength / 20 * 11},
		{center_x - unitLength * 4.2 + unitLength / 20 * 2, center_y - unitLength * 9.5 - unitLength / 20 * 11},
		
		{center_x + unitLength * 4 + unitLength / 20 * 2, center_y - unitLength * 9.5 - unitLength / 20 * 11},
		{center_x + unitLength * 4 + unitLength / 20 * 2, center_y - unitLength * 9.5 - unitLength / 20 * 11},
		{center_x + unitLength * 4 + unitLength / 20 * 2, center_y - unitLength * 9.5 - unitLength / 20 * 11}
		
		
	};
	ege_bezier(pointsNum_center_1, ploypoints_center_1);
	
	
	int center_pointNums_top_1 = 25;
	ege_point center_ploypoints_top_1[25] = {
		{center_x - unitLength * 3.9, center_y - unitLength * 12.7 - unitLength / 20 * 4},{center_x - unitLength * 3.8, center_y - unitLength * 13.1 - unitLength / 20 * 4},
		{center_x - unitLength * 3.7, center_y - unitLength * 13.2 - unitLength / 20 * 4},{center_x - unitLength * 3.5, center_y - unitLength * 13.3 - unitLength / 20 * 4},
		
		{center_x + unitLength * 3.1, center_y - unitLength * 13.3 - unitLength / 20 * 4},{center_x + unitLength * 3.1, center_y - unitLength * 13.3 - unitLength / 20 * 4},
		{center_x + unitLength * 3.1, center_y - unitLength * 13.3 - unitLength / 20 * 4},
		
		{center_x + unitLength * 3.3, center_y - unitLength * 13.2 - unitLength / 20 * 4},{center_x + unitLength * 3.4, center_y - unitLength * 13.1 - unitLength / 20 * 4},
		{center_x + unitLength * 3.5, center_y - unitLength * 12.7 - unitLength / 20 * 4},
		
		{center_x + unitLength * 3.5, center_y - unitLength * 12.7 - unitLength / 20 * 4},{center_x + unitLength * 3.5, center_y - unitLength * 12.7 - unitLength / 20 * 4},
		{center_x + unitLength * 3.5, center_y - unitLength * 12.7 - unitLength / 20 * 4},
		
		{center_x + unitLength * 3.4, center_y - unitLength * 12.3 - unitLength / 20 * 4},{center_x + unitLength * 3.3, center_y - unitLength * 12.2 - unitLength / 20 * 4},
		{center_x + unitLength * 3.1, center_y - unitLength * 12.1 - unitLength / 20 * 4},
		
		{center_x - unitLength * 3.5, center_y - unitLength * 12.1 - unitLength / 20 * 4},{center_x - unitLength * 3.5, center_y - unitLength * 12.1 - unitLength / 20 * 4},
		{center_x - unitLength * 3.5, center_y - unitLength * 12.1 - unitLength / 20 * 4},
		
		{center_x - unitLength * 3.7, center_y - unitLength * 12.2 - unitLength / 20 * 4},{center_x - unitLength * 3.8, center_y - unitLength * 12.3 - unitLength / 20 * 4},
		{center_x - unitLength * 3.9, center_y - unitLength * 12.7 - unitLength / 20 * 4},
		
		{center_x - unitLength * 3.9, center_y - unitLength * 12.7 - unitLength / 20 * 4},{center_x - unitLength * 3.9, center_y - unitLength * 12.7 - unitLength / 20 * 4},
		{center_x - unitLength * 3.9, center_y - unitLength * 12.7 - unitLength / 20 * 4}
		
	};
	
	ege_bezier(center_pointNums_top_1, center_ploypoints_top_1);
	
	
	setfillcolor(EGEARGB(0XFF, 0X32, 0X15, 0X04));
	ege_fillrect(center_x - unitLength * 3.6 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20 * 7, unitLength * 2.16 / 2.2, unitLength * 2.1 / 2);
	ege_fillrect(center_x - unitLength * 3.6 + unitLength / 20 * 2.2 + unitLength * 2.16 / 2.2, center_y - unitLength * 11 - unitLength / 20 * 7, unitLength * 2.16 / 2.2, unitLength * 2.1 / 2);
	ege_fillrect(center_x - unitLength * 3.6 + unitLength / 20 * 2.4 + unitLength * 2.16 / 2.2 * 2, center_y - unitLength * 11 - unitLength / 20 * 7, unitLength * 2.16 / 2.2, unitLength * 2.1 / 2);
	ege_fillrect(center_x - unitLength * 3.6 + unitLength / 20 * 2.6 + unitLength * 2.16 / 2.2 * 3, center_y - unitLength * 11 - unitLength / 20 * 7, unitLength * 2.16 / 2.2, unitLength * 2.1 / 2);
	ege_fillrect(center_x - unitLength * 3.6 + unitLength / 20 * 2.8 + unitLength * 2.16 / 2.2 * 4, center_y - unitLength * 11 - unitLength / 20 * 7, unitLength * 2.16 / 2.2, unitLength * 2.1 / 2);
	ege_fillrect(center_x - unitLength * 3.6 + unitLength / 20 * 3 + unitLength * 2.16 / 2.2 * 5, center_y - unitLength * 11 - unitLength / 20 * 7, unitLength * 2.16 / 2.2, unitLength * 2.1 / 2);
	ege_fillrect(center_x - unitLength * 3.6 + unitLength / 20 * 3.2 + unitLength * 2.16 / 2.2 * 6, center_y - unitLength * 11 - unitLength / 20 * 7, unitLength * 2.16 / 2.2, unitLength * 2.1 / 2);
	
	
	setcolor(EGEARGB(0XFF, 0X4A, 0X51, 0X52));
	setfont(unitLength * 0.55, unitLength * 0.18, "微软雅黑", 0, 0, unitLength, 0, 0, 0);
	xyprintf(center_x - unitLength * 3 + unitLength / 20, center_y - unitLength * 10.7 - unitLength / 20 * 7, "MON");
	xyprintf(center_x - unitLength * 3 + unitLength / 20, center_y - unitLength * 10.7, "PWR");
	xyprintf(center_x - unitLength * 2 + unitLength / 20, center_y - unitLength * 10.7 - unitLength / 20 * 2, "HOG");
	xyprintf(center_x - unitLength * 1 + unitLength / 20, center_y - unitLength * 10.7 - unitLength / 20 * 2, "PLLCH");
	xyprintf(center_x + unitLength / 20 * 3, center_y - unitLength * 10.7 - unitLength / 20 * 2, "ROLL");
	xyprintf(center_x + unitLength * 1 + unitLength / 20, center_y - unitLength * 10.7 - unitLength / 20 * 2, "GS");
	xyprintf(center_x + unitLength * 2 + unitLength / 20, center_y - unitLength * 10.7 - unitLength / 20 * 2, "LGC");
	xyprintf(center_x + unitLength * 3 + unitLength / 20, center_y - unitLength * 10.7 - unitLength / 20 * 2, "ALT");
	
	
	
	draw_screw2(center_x + unitLength * 8.7, center_y - unitLength * 12.6 - unitLength / 20 * 4, unitLength / 3, 0);
	draw_screw2(center_x + unitLength * 8.7, center_y - unitLength * 9 - unitLength / 20 * 4, unitLength / 3, 0);
	draw_screw2(center_x + unitLength * 14, center_y - unitLength * 12.6 - unitLength / 20 * 4, unitLength / 3, 0);
	draw_screw2(center_x + unitLength * 14, center_y - unitLength * 9 - unitLength / 20 * 4, unitLength / 3, 0);
	draw_screw2(center_x - unitLength * 4 + unitLength / 20 * 2, center_y - unitLength * 11 + unitLength / 20 * 3, unitLength / 4, 0);
	draw_screw2(center_x - unitLength * 2.3 + unitLength / 20 * 3.2 + unitLength * 2.16 / 2.2 * 6, center_y - unitLength * 11 + unitLength / 20 * 3, unitLength / 4, 0);
	
	
	setfillcolor(EGEARGB(0XFF, 0X60, 0X60, 0X60));
	ege_fillellipse(center_x - unitLength * 4.8 + unitLength / 20 * 3, center_y - unitLength * 11 - unitLength / 20 * 2, unitLength / 3, unitLength / 3);
	ege_fillellipse(center_x + unitLength * 4.2 + unitLength / 20 * 3, center_y - unitLength * 11 - unitLength / 20 * 2, unitLength / 3, unitLength / 3);
	
	
	
	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillellipse(center_x - unitLength * 4.8 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20, unitLength / 3, unitLength / 3);
	ege_fillellipse(center_x + unitLength * 4.2 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20, unitLength / 3, unitLength / 3);
	
	
	
	setfillcolor(BLACK);
	ege_fillrect(center_x + unitLength * 9.1, center_y - unitLength * 13.7 - unitLength / 20 * 4, unitLength * 2.14 * 2.1, unitLength * 5.6);
	
	setfillcolor(EGEARGB(0XFF, 0X11, 0X12, 0X14));
	ege_fillrect(center_x + unitLength * 9.2, center_y - unitLength * 9.2 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);
	ege_fillrect(center_x + unitLength * 9.2, center_y - unitLength * 10.3 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);
	ege_fillrect(center_x + unitLength * 9.2, center_y - unitLength * 11.4 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);
	ege_fillrect(center_x + unitLength * 9.2, center_y - unitLength * 12.5 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);
	ege_fillrect(center_x + unitLength * 9.2, center_y - unitLength * 13.6 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);
	
	ege_fillrect(center_x + unitLength * 11.44, center_y - unitLength * 9.2 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);
	ege_fillrect(center_x + unitLength * 11.44, center_y - unitLength * 10.3 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);
	ege_fillrect(center_x + unitLength * 11.44, center_y - unitLength * 11.4 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);
	ege_fillrect(center_x + unitLength * 11.44, center_y - unitLength * 12.5 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);
	ege_fillrect(center_x + unitLength * 11.44, center_y - unitLength * 13.6 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);
	
	
	
	if (alert_ALT == 1) {
		setfillcolor(EGEARGB(0X40, 0X72, 0X55, 0X34));
		ege_fillrect(center_x + unitLength * 5 + unitLength / 20 * 5, center_y - unitLength * 10 - unitLength / 20 * 4, unitLength * 2.16, unitLength * 2.1);
	}
	else {
		setfillcolor(EGEARGB(0XFF, 0X32, 0X15, 0X04));
		ege_fillrect(center_x + unitLength * 5 + unitLength / 20 * 5, center_y - unitLength * 10 - unitLength / 20 * 4, unitLength * 2.16, unitLength * 2.1);
	}
	if (alert_MDA == 1) {
		setfillcolor(EGEARGB(0X40, 0X72, 0X55, 0X34));
		ege_fillrect(center_x + unitLength * 5 + unitLength / 20 * 5, center_y - unitLength * 13 - unitLength / 20 * 4, unitLength * 2.16, unitLength * 2.1);
		
	}
	else {
		setfillcolor(EGEARGB(0XFF, 0X32, 0X15, 0X04));
		ege_fillrect(center_x + unitLength * 5 + unitLength / 20 * 5, center_y - unitLength * 13 - unitLength / 20 * 4, unitLength * 2.16, unitLength * 2.1);
	}
	if (alert_autoPilot == 1) {
		//        setfillcolor(EGEARGB(0X40, 0X72, 0X55, 0X34));
		setfillcolor(EGEARGB(0XFF, 0X4d, 0X07, 0X07));
		ege_fillrect(center_x - unitLength * 13 + unitLength / 20 * 5, center_y - unitLength * 10 - unitLength / 20 * 4, unitLength * 2.16, unitLength * 2.1);
	}
	else {
		//        setfillcolor(EGEARGB(0XFF, 0X32, 0X15, 0X04));
		setfillcolor(EGEARGB(0XFF, 0X38, 0X05, 0X05));
		ege_fillrect(center_x - unitLength * 13 + unitLength / 20 * 5, center_y - unitLength * 10 - unitLength / 20 * 4, unitLength * 2.16, unitLength * 2.1);
	}
	
	setcolor(BLACK);
	setbkmode(TRANSPARENT);
	setfont(unitLength * 1, unitLength * 0.38, "微软雅黑", 0, 0, unitLength, 0, 0, 0);
	xyprintf(center_x + unitLength * 6.3 + unitLength / 20 * 3, center_y - unitLength * 10 + unitLength / 20 * 15, "ALT");
	xyprintf(center_x + unitLength * 6.3 + unitLength / 20 * 3, center_y - unitLength * 13 + unitLength / 20 * 15, "MDA");
	setcolor(EGEARGB(0XFF, 0X80, 0X80, 0X80));
	setfont(unitLength * 0.8, unitLength * 0.3, "微软雅黑", 0, 0, unitLength, 0, 0, 0);
	xyprintf(center_x - unitLength * 11.9 + unitLength / 20 * 6, center_y - unitLength * 9.5 - unitLength / 20 * 4, "AUTO");
	xyprintf(center_x - unitLength * 11.9 + unitLength / 20 * 6, center_y - unitLength * 9.5 + unitLength / 20 * 11, "PILOT");
	setfont(unitLength * 0.35, unitLength * 0.15, "微软雅黑", 0, 0, unitLength, 0, 0, 0);
	xyprintf(center_x - unitLength * 11.7 + unitLength / 20 * 2, center_y - unitLength * 8.5 + unitLength / 20 * 4, "DISENGAGE");
	
	setcolor(EGEARGB(0XFF, 0X4A, 0X51, 0X52));
	setfont(unitLength * 0.8, unitLength * 0.25, "微软雅黑", 0, 0, unitLength, 0, 0, 0);
	xyprintf(center_x - unitLength * 0.2, center_y - unitLength * 12.8 - unitLength / 20 * 2, "INSTRUMENT COMPARATOR");
	xyprintf(center_x + unitLength * 11.3, center_y - unitLength * 15 - unitLength / 20 * 12, "APD");
	xyprintf(center_x + unitLength * 10.3, center_y - unitLength * 15 + unitLength / 20 * 2, "F/D");
	xyprintf(center_x + unitLength * 12.5, center_y - unitLength * 15 + unitLength / 20 * 2, "A/P");
	
	if (alert_pullup == 1) {
		setcolor(WHITE);
		setfont(unitLength * 0.8, unitLength * 0.25, "微软雅黑", 0, 0, unitLength, 0, 0, 0);
		xyprintf(center_x - unitLength * 7.5 - unitLength / 20 * 2, center_y - unitLength * 9 - unitLength / 20 * 4, "PULL UP");
	}
	else {
		setcolor(BLACK);
		setfont(unitLength * 0.8, unitLength * 0.25, "微软雅黑", 0, 0, unitLength, 0, 0, 0);
		xyprintf(center_x - unitLength * 7.5 - unitLength / 20 * 2, center_y - unitLength * 9.3 - unitLength / 20 * 4, "PULL UP");
	}
	if (alert_beloGS == 1) {
		setcolor(EGEARGB(0XFF, 0X9D, 0X42, 0X0E));
		setfont(unitLength * 0.6, unitLength * 0.20, "微软雅黑", 0, 0, unitLength, 0, 0, 0);
		xyprintf(center_x - unitLength * 7.5 - unitLength / 20 * 5, center_y - unitLength * 8.2 - unitLength / 20 * 6, "BELO G/S");
		setfont(unitLength * 0.6, unitLength * 0.15, "微软雅黑", 0, 0, unitLength, 0, 0, 0);
		xyprintf(center_x - unitLength * 7.8, center_y - unitLength * 7.7 - unitLength / 20 * 6, "P-INHIBIT");
	}
	else {
		setcolor(BLACK);
		setfont(unitLength * 0.6, unitLength * 0.20, "微软雅黑", 0, 0, unitLength, 0, 0, 0);
		xyprintf(center_x - unitLength * 7.5 - unitLength / 20 * 5, center_y - unitLength * 8.2 - unitLength / 20 * 6, "BELO G/S");
		setfont(unitLength * 0.6, unitLength * 0.15, "微软雅黑", 0, 0, unitLength, 0, 0, 0);
		xyprintf(center_x - unitLength * 7.8, center_y - unitLength * 7.7 - unitLength / 20 * 6, "P-INHIBIT");
	}
	
	setfillcolor(EGEARGB(0X50, 0X60, 0X60, 0X60));
	ege_fillrect(center_x - unitLength * 4.2 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20 * 13, unitLength * 2.16 / 2.2 * 8.4, unitLength * 2.1 * 0.8);
}
void draw_Background_2(double Background_2_x , double Background_2_y , double side){
	double Ulength = 0.01 * side;
	double linewidth = Ulength;
	setlinewidth(linewidth / 2);
	setcolor(BLACK);
	
	
	setfillcolor(EGEARGB(0xff, 0x3B, 0x39, 0X38));
	int num_7 = 4;
	ege_point polynums_7[4] = {
		{Background_2_x + Ulength * 785 , Background_2_y + Ulength * 248},
		{Background_2_x + Ulength * 785 , Background_2_y - Ulength * 127.5},
		{Background_2_x - Ulength * 175 , Background_2_y - Ulength * 127.5},
		{Background_2_x - Ulength * 175 , Background_2_y + Ulength * 248},
	};
	ege_fillpoly(num_7,polynums_7);
	
	int num_12 = 5;
	ege_point ploynums_12[5]={
		{Background_2_x - Ulength * 140 , Background_2_y - Ulength * 69},
		
		{Background_2_x - Ulength * 150 , Background_2_y + Ulength * 69},
		{Background_2_x - Ulength * 144 , Background_2_y + Ulength * 69},
		{Background_2_x - Ulength * 140 , Background_2_y + Ulength * 60},
		{Background_2_x - Ulength * 130 , Background_2_y - Ulength * 69}
		
	};
	setfillcolor(EGEARGB(0XFF, 0X17, 0X17, 0X17));
	ege_fillpoly(num_12, ploynums_12);
	int num_13 = 4;
	ege_point ploynums_13[4]={
		
		{Background_2_x - Ulength * 150 , Background_2_y + Ulength * 69},
		{Background_2_x - Ulength * 144 , Background_2_y + Ulength * 69},
	    {Background_2_x - Ulength * 130 , Background_2_y + Ulength * 100},
		{Background_2_x - Ulength * 145 , Background_2_y + Ulength * 130},
		
	};
	setfillcolor(EGEARGB(0XFF, 0X17, 0X17, 0X17));
	ege_fillpoly(num_13, ploynums_13);
	
	int num_14 = 4;
	ege_point ploynums_14[4]={
		
		{Background_2_x - Ulength * 150 , Background_2_y + Ulength * 69},
		{Background_2_x + Ulength * 774 , Background_2_y + Ulength * 69},
		{Background_2_x + Ulength * 770 , Background_2_y + Ulength * 250},
		{Background_2_x - Ulength * 145 , Background_2_y + Ulength * 250},
		
	};
	setfillcolor(EGEARGB(0XFF, 0X17, 0X17, 0X17));
	ege_fillpoly(num_14, ploynums_14);
	
	setfillcolor(EGEARGB(0xff, 0x14, 0x17, 0x19));
	int num_6 = 6;
	ege_point ploynums_6[6] = {
		{Background_2_x - Ulength * 140 , Background_2_y + Ulength * 60},
		{Background_2_x + Ulength * 774 , Background_2_y + Ulength * 60},
		{Background_2_x + Ulength * 766 , Background_2_y - Ulength * 123},
		{Background_2_x + Ulength * 540 , Background_2_y - Ulength * 173},
		{Background_2_x + Ulength * 145 , Background_2_y - Ulength * 173},
		{Background_2_x - Ulength * 130 , Background_2_y - Ulength * 127.5},
	};
	ege_fillpoly(num_6, ploynums_6);
	
	
	ege_line(Background_2_x - Ulength * 58 , Background_2_y - Ulength * 93.5 , Background_2_x - Ulength * 58 , Background_2_y - Ulength * 62 );
	setlinewidth(linewidth);
	ege_line(Background_2_x - Ulength * 58 , Background_2_y - Ulength * 62.6 , Background_2_x + Ulength * 194 , Background_2_y - Ulength * 62.6);
	setlinewidth(linewidth / 2);
	ege_line(Background_2_x + Ulength * 194 , Background_2_y - Ulength * 115 , Background_2_x + Ulength * 194 , Background_2_y - Ulength * 62);
	ege_line(Background_2_x + Ulength * 194 , Background_2_y - Ulength * 115 , Background_2_x + Ulength * 102 , Background_2_y - Ulength * 115);
	ege_line(Background_2_x - Ulength * 132 , Background_2_y - Ulength * 90, Background_2_x - Ulength * 140 , Background_2_y + Ulength * 60);
	ege_line(Background_2_x - Ulength * 58 , Background_2_y + Ulength * 60, Background_2_x - Ulength * 140 , Background_2_y + Ulength * 60);
	int num_1 = 4;
	ege_point ploynums_1[4] = {
		{Background_2_x - Ulength * 140 , Background_2_y + Ulength * 60},
		{Background_2_x - Ulength * 143 , Background_2_y + Ulength * 64},
		{Background_2_x + Ulength * 778 , Background_2_y + Ulength * 64},
		{Background_2_x + Ulength * 773 , Background_2_y + Ulength * 60}
	};
	ege_setpattern_lineargradient(Background_2_x - Ulength * 100 , Background_2_y + Ulength * 60, EGEARGB(0XFF, 0X00, 0X00, 0X00),
		Background_2_x - Ulength * 100 , Background_2_y + Ulength * 64, EGEARGB(0XFF, 0X20, 0X20, 0X20));
	ege_fillpoly(num_1, ploynums_1);
	ege_setpattern_none();
	
	
	
	int num_2 = 4;
	ege_point ploynums_2[4] = {
		{Background_2_x - Ulength * 143 , Background_2_y + Ulength * 64},
		{Background_2_x - Ulength * 144 , Background_2_y + Ulength * 66},
		{Background_2_x + Ulength * 780 , Background_2_y + Ulength * 66},
		{Background_2_x + Ulength * 778 , Background_2_y + Ulength * 64}
	};
	//setfillcolor(EGEARGB(0X60,0X60,0X60,0X60));
	ege_setpattern_lineargradient(Background_2_x - Ulength * 100 , Background_2_y + Ulength * 64, EGEARGB(0XFF, 0X20, 0X20, 0X20),
		Background_2_x - Ulength * 100 , Background_2_y + Ulength * 66, EGEARGB(0X60, 0X50, 0X50, 0X50));
	ege_fillpoly(num_2, ploynums_2);
	ege_setpattern_none();
	
	int num_3 = 4;
	ege_point ploynums_3[4] = {
		{Background_2_x - Ulength * 144 , Background_2_y + Ulength * 66},
		{Background_2_x - Ulength * 144 , Background_2_y + Ulength * 68},
		{Background_2_x + Ulength * 779 , Background_2_y + Ulength * 68},
		{Background_2_x + Ulength * 780 , Background_2_y + Ulength * 66}
	};
	
	ege_setpattern_lineargradient(Background_2_x - Ulength * 100 , Background_2_y + Ulength * 66, EGEARGB(0X60, 0X50, 0X50, 0X50),
		Background_2_x - Ulength * 100 , Background_2_y + Ulength * 68, EGEARGB(0XFF, 0X19, 0X1A, 0X1E));
	ege_fillpoly(num_3, ploynums_3);
	ege_setpattern_none();
	
	
	int num_4 = 4;
	ege_point ploynums_4[4] = {
		{Background_2_x - Ulength * 144 , Background_2_y + Ulength * 68},
		{Background_2_x - Ulength * 140 , Background_2_y + Ulength * 79},
		{Background_2_x + Ulength * 773 , Background_2_y + Ulength * 79},
		{Background_2_x + Ulength * 779 , Background_2_y + Ulength * 68}
	};
	
	setfillcolor(EGEARGB(0XFF, 0X18, 0X19, 0X1B));
	ege_fillpoly(num_4, ploynums_4);
	
	
	int num_5 = 4;
	ege_point ploynums_5[4] = {
		{Background_2_x - Ulength * 140 , Background_2_y + Ulength * 79},
		{Background_2_x - Ulength * 150 , Background_2_y + Ulength * 130},
		{Background_2_x + Ulength * 155 , Background_2_y + Ulength * 130},
		{Background_2_x + Ulength * 155 , Background_2_y + Ulength * 79}
	};
	
	setfillcolor(EGEARGB(0XFF, 0X10, 0X10, 0X10));
	ege_fillpoly(num_5, ploynums_5);
	int num_11 = 4;
	ege_point ploynums_11[4]={
		{Background_2_x + Ulength * 773 , Background_2_y + Ulength * 79},
		{Background_2_x + Ulength * 778 , Background_2_y + Ulength * 130},
		{Background_2_x + Ulength * 460 , Background_2_y + Ulength * 130},
		{Background_2_x + Ulength * 460 , Background_2_y + Ulength * 79},
		
	};
	setfillcolor(EGEARGB(0XFF, 0X10, 0X10, 0X10));
	ege_fillpoly(num_11, ploynums_11);
	
	
	setcolor(BLACK);
	ege_line(Background_2_x + Ulength * 387 , Background_2_y + Ulength * 60,
		Background_2_x + Ulength * 387 , Background_2_y - Ulength * 117);
	ege_line(Background_2_x + Ulength * 258 , Background_2_y + Ulength * 60,
		Background_2_x + Ulength * 258 , Background_2_y - Ulength * 117);
	ege_line(Background_2_x + Ulength * 423 , Background_2_y + Ulength * 60,
		Background_2_x + Ulength * 423 , Background_2_y - Ulength * 117);
	ege_line(Background_2_x + Ulength * 671 , Background_2_y + Ulength * 60,
		Background_2_x + Ulength * 671 , Background_2_y - Ulength * 102);
	ege_line(Background_2_x + Ulength * 750 , Background_2_y + Ulength * 60,
		Background_2_x + Ulength * 742 , Background_2_y - Ulength * 88);
	
	
	draw_screw2(Background_2_x - Ulength * 130 , Background_2_y + Ulength * 56,Ulength * 3.5,0);
	draw_screw2(Background_2_x - Ulength * 64 , Background_2_y + Ulength * 56,Ulength * 3.5,0);
	draw_screw2(Background_2_x - Ulength * 64 , Background_2_y - Ulength * 85,Ulength * 3.5,0);
	draw_screw2(Background_2_x - Ulength * 63 , Background_2_y - Ulength * 50,Ulength * 2.5,0);
	draw_screw2(Background_2_x - Ulength * 63 , Background_2_y - Ulength * 8,Ulength * 2.5,0);
	draw_screw2(Background_2_x - Ulength * 107 , Background_2_y - Ulength * 50,Ulength * 2.5,0);
	draw_screw2(Background_2_x - Ulength * 107 , Background_2_y - Ulength * 8,Ulength * 2.5,0);
	draw_screw2(Background_2_x - Ulength * 54 , Background_2_y - Ulength * 67,Ulength * 3.5,0);
	draw_screw2(Background_2_x + Ulength * 20 , Background_2_y - Ulength * 95,Ulength * 3.5,0);
	draw_screw2(Background_2_x + Ulength * 125 , Background_2_y - Ulength * 85,Ulength * 2.5,0);
	draw_screw2(Background_2_x + Ulength * 125 , Background_2_y - Ulength * 105,Ulength * 2.5,0);
	draw_screw2(Background_2_x + Ulength * 190 , Background_2_y - Ulength * 70,Ulength * 2.5,0);
	draw_screw2(Background_2_x + Ulength * 200 , Background_2_y - Ulength * 55,Ulength * 2.5,0);
	draw_screw2(Background_2_x + Ulength * 252 , Background_2_y - Ulength * 55,Ulength * 2.5,0);
	draw_screw2(Background_2_x + Ulength * 200 , Background_2_y - Ulength * 3,Ulength * 2.5,0);
	draw_screw2(Background_2_x + Ulength * 252 , Background_2_y - Ulength * 3,Ulength * 2.5,0);
	draw_screw2(Background_2_x + Ulength * 200 , Background_2_y + Ulength * 55,Ulength * 3.5,0);
	draw_screw2(Background_2_x + Ulength * 252 , Background_2_y + Ulength * 55,Ulength * 3.5,0);
	draw_screw2(Background_2_x + Ulength * 262 , Background_2_y - Ulength * 65,Ulength * 2.5,0);
	draw_screw2(Background_2_x + Ulength * 332 , Background_2_y - Ulength * 65,Ulength * 2.5,0);
	draw_screw2(Background_2_x + Ulength * 347 , Background_2_y - Ulength * 77,Ulength * 2.5,0);
	draw_screw2(Background_2_x + Ulength * 380 , Background_2_y - Ulength * 110,Ulength * 2.5,0);
	draw_screw2(Background_2_x + Ulength * 433 , Background_2_y - Ulength * 68,Ulength * 3.5,0);
	draw_screw2(Background_2_x + Ulength * 428 , Background_2_y - Ulength * 85,Ulength * 2.5,0);
	draw_screw2(Background_2_x + Ulength * 465 , Background_2_y - Ulength * 80,Ulength * 2.5,0);
	draw_screw2(Background_2_x + Ulength * 465 , Background_2_y - Ulength * 102,Ulength * 2.5,0);
	draw_screw2(Background_2_x - Ulength * 135 , Background_2_y + Ulength * 90,Ulength * 3.5,0);
	draw_screw2(Background_2_x - Ulength * 142 , Background_2_y + Ulength * 125,Ulength * 3.5,0);
	draw_screw2(Background_2_x - Ulength * 19 , Background_2_y + Ulength * 85,Ulength * 3,0);
	draw_screw2(Background_2_x - Ulength * 19 , Background_2_y + Ulength * 122,Ulength * 3,0);
	draw_screw2(Background_2_x - Ulength * 26 , Background_2_y + Ulength * 85,Ulength * 3,0);
	draw_screw2(Background_2_x - Ulength * 26 , Background_2_y + Ulength * 122,Ulength * 3,0);
	draw_screw2(Background_2_x + Ulength * 48 , Background_2_y + Ulength * 85,Ulength * 3,0);
	draw_screw2(Background_2_x + Ulength * 48 , Background_2_y + Ulength * 122,Ulength * 3,0);
	draw_screw2(Background_2_x + Ulength * 54 , Background_2_y + Ulength * 85,Ulength * 3,0);
	draw_screw2(Background_2_x + Ulength * 54 , Background_2_y + Ulength * 122,Ulength * 3,0);
	draw_screw2(Background_2_x + Ulength * 122 , Background_2_y + Ulength * 85,Ulength * 3,0);
	draw_screw2(Background_2_x + Ulength * 122 , Background_2_y + Ulength * 122,Ulength * 3,0);
	draw_screw2(Background_2_x + Ulength * 745 , Background_2_y + Ulength * 56,Ulength * 3.5,0);
	draw_screw2(Background_2_x + Ulength * 680 , Background_2_y + Ulength * 56,Ulength * 3.5,0);
	draw_screw2(Background_2_x + Ulength * 735 , Background_2_y - Ulength * 80,Ulength * 3.5,0);
	draw_screw2(Background_2_x + Ulength * 680 , Background_2_y - Ulength * 95,Ulength * 3.5,0);
	draw_screw2(Background_2_x + Ulength * 660 , Background_2_y - Ulength * 75,Ulength * 3.5,0);
	draw_screw2(Background_2_x + Ulength * 603 , Background_2_y - Ulength * 98,Ulength * 2.5,0);
	draw_screw2(Background_2_x + Ulength * 603 , Background_2_y - Ulength * 68,Ulength * 2.5,0);
	draw_screw2(Background_2_x + Ulength * 716 , Background_2_y + Ulength * 85,Ulength * 3,0);
	draw_screw2(Background_2_x + Ulength * 660 , Background_2_y + Ulength * 85,Ulength * 3,0);
	draw_screw2(Background_2_x + Ulength * 716 , Background_2_y + Ulength * 125,Ulength * 3,0);
	draw_screw2(Background_2_x + Ulength * 660 , Background_2_y + Ulength * 125,Ulength * 3,0);
	draw_screw2(Background_2_x + Ulength * 582 , Background_2_y + Ulength * 85,Ulength * 3,0);
	draw_screw2(Background_2_x + Ulength * 582 , Background_2_y + Ulength * 125,Ulength * 3,0);
	draw_screw2(Background_2_x + Ulength * 588 , Background_2_y + Ulength * 85,Ulength * 3,0);
	draw_screw2(Background_2_x + Ulength * 588 , Background_2_y + Ulength * 125,Ulength * 3,0);
	draw_screw2(Background_2_x + Ulength * 508 , Background_2_y + Ulength * 85,Ulength * 3,0);
	draw_screw2(Background_2_x + Ulength * 508 , Background_2_y + Ulength * 125,Ulength * 3,0);
	
	
	
	int num_21 = 4;
	ege_point ploynums_21[4] = {
		{Background_2_x - Ulength * 150 , Background_2_y + Ulength * 130},
		{Background_2_x - Ulength * 153 , Background_2_y + Ulength * 134},
		{Background_2_x + Ulength * 783 , Background_2_y + Ulength * 134},
		{Background_2_x + Ulength * 778 , Background_2_y + Ulength * 130}
	};
	ege_setpattern_lineargradient(Background_2_x - Ulength * 100 , Background_2_y + Ulength * 130, EGEARGB(0XFF, 0X00, 0X00, 0X00),
		Background_2_x - Ulength * 100 , Background_2_y + Ulength * 134, EGEARGB(0XFF, 0X20, 0X20, 0X20));
	ege_fillpoly(num_21, ploynums_21);
	ege_setpattern_none();
	
	
	
	int num_22 = 4;
	ege_point ploynums_22[4] = {
		{Background_2_x - Ulength * 153 , Background_2_y + Ulength * 134},
		{Background_2_x - Ulength * 154 , Background_2_y + Ulength * 136},
		{Background_2_x + Ulength * 785 , Background_2_y + Ulength * 136},
		{Background_2_x + Ulength * 783 , Background_2_y + Ulength * 134}
	};
	//setfillcolor(EGEARGB(0X60,0X60,0X60,0X60));
	ege_setpattern_lineargradient(Background_2_x - Ulength * 100 , Background_2_y + Ulength * 134, EGEARGB(0XFF, 0X20, 0X20, 0X20),
		Background_2_x - Ulength * 100 , Background_2_y + Ulength * 136, EGEARGB(0X60, 0X50, 0X50, 0X50));
	ege_fillpoly(num_22, ploynums_22);
	ege_setpattern_none();
	
	int num_23 = 4;
	ege_point ploynums_23[4] = {
		{Background_2_x - Ulength * 154 , Background_2_y + Ulength * 136},
		{Background_2_x - Ulength * 154 , Background_2_y + Ulength * 138},
		{Background_2_x + Ulength * 784 , Background_2_y + Ulength * 138},
		{Background_2_x + Ulength * 785 , Background_2_y + Ulength * 136}
	};
	
	ege_setpattern_lineargradient(Background_2_x - Ulength * 100 , Background_2_y + Ulength * 136, EGEARGB(0X60, 0X50, 0X50, 0X50),
		Background_2_x - Ulength * 100 , Background_2_y + Ulength * 138, EGEARGB(0XFF, 0X19, 0X1A, 0X1E));
	ege_fillpoly(num_23, ploynums_23);
	ege_setpattern_none();
	
	
	int num_24 = 4;
	ege_point ploynums_24[4] = {
		{Background_2_x - Ulength * 154 , Background_2_y + Ulength * 138},
		{Background_2_x - Ulength * 150 , Background_2_y + Ulength * 149},
		{Background_2_x + Ulength * 778 , Background_2_y + Ulength * 149},
		{Background_2_x + Ulength * 784 , Background_2_y + Ulength * 138}
	};
	
	setfillcolor(EGEARGB(0XFF, 0X18, 0X19, 0X1B));
	ege_fillpoly(num_24, ploynums_24);
	setcolor(EGEARGB(0XF0, 0X00, 0X00, 0X00));
	setlinewidth(Ulength * 10);
	ege_line(Background_2_x + Ulength * 110 , Background_2_y - Ulength * 173,
		Background_2_x - Ulength * 220 , Background_2_y - Ulength * 126);
	
		setlinewidth(Ulength * 2);
	ege_line(Background_2_x + Ulength * 108 , Background_2_y - Ulength * 174.8,
		Background_2_x + Ulength * 130 , Background_2_y - Ulength * 177.3);
	ege_line(Background_2_x - Ulength * 316 , Background_2_y - Ulength * 365,
		Background_2_x - Ulength * 212 , Background_2_y - Ulength * 126);
	setlinewidth(Ulength * 3);
	ege_line(Background_2_x + Ulength * 518 , Background_2_y - Ulength * 176.7,
		Background_2_x + Ulength * 130 , Background_2_y - Ulength * 176.9);
	ege_line(Background_2_x + Ulength * 518 , Background_2_y - Ulength * 176.7,
		Background_2_x + Ulength * 575 , Background_2_y - Ulength * 169.5);
	
	
	setcolor(EGEARGB(0XF0, 0X62, 0X64, 0X56));
	ege_line(Background_2_x + Ulength * 289 , Background_2_y - Ulength * 352,
		Background_2_x + Ulength * 297 , Background_2_y - Ulength * 178);
	
	
	ege_line(Background_2_x + Ulength * 372 , Background_2_y - Ulength * 352,
		Background_2_x + Ulength * 362 , Background_2_y - Ulength * 178);
	
	setcolor(EGEARGB(0XF0, 0X30, 0X30, 0X30));
	setlinewidth(Ulength * 4);
	ege_line(Background_2_x + Ulength * 282 , Background_2_y - Ulength * 418,
		Background_2_x + Ulength * 283 , Background_2_y - Ulength * 354);
	ege_line(Background_2_x + Ulength * 385 , Background_2_y - Ulength * 418,
		Background_2_x + Ulength * 385 , Background_2_y - Ulength * 354);
	
	if(GetAsyncKeyState(0x65) & 0x0001){
		if(showsomedata==0){
			showsomedata = 1;
		}else if(showsomedata==1){
			showsomedata = 0;
		}
	}
	if(showsomedata==1){
		setcolor(EGEARGB(0XFF, 0XBF, 0XBF, 0XBF));
		setfont(Ulength * 6, Ulength * 2.5, "DigifaceWide");
		char nums_20[64];//起落架在第一个
		sprintf_s(nums_20, "%d", stateLandingGear);
		ege_drawtext("LandingGear:",Background_2_x - Ulength * 20 , Background_2_y - Ulength * 90);
		ege_drawtext(nums_20, Background_2_x + Ulength * 10 , Background_2_y - Ulength * 90);
		char nums_21[64];//刹车在第二个
		sprintf_s(nums_21, "%d", statebrake);
		ege_drawtext("brake:",Background_2_x - Ulength * 20 , Background_2_y - Ulength * 85);
		ege_drawtext(nums_21, Background_2_x - Ulength * 4 , Background_2_y - Ulength * 85);
		char nums_22[64];//油门
		sprintf_s(nums_22, "%.2f", accelerator_change+accelerator);
		ege_drawtext("accelerator:",Background_2_x - Ulength * 20 , Background_2_y - Ulength * 80);
		ege_drawtext(nums_22, Background_2_x + Ulength * 10 , Background_2_y - Ulength * 80);
		char nums_23[64];//襟翼
		sprintf_s(nums_23, "%.3f", gearFlaps + Flapschange);
		ege_drawtext("FlapsGear:",Background_2_x - Ulength * 20 , Background_2_y - Ulength * 75);
		ege_drawtext(nums_23, Background_2_x + Ulength * 5 , Background_2_y - Ulength * 75);
	}
	
	
}