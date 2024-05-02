#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include "DrawFrame.h"
#include "DrawLight.h"

extern double angle;
extern double RMI_point_angle_1;
extern double RMI_point_angle_2;

void draw_text(double RMI_x, double RMI_y, double RMI_side) {
	for (int i = 0; i < 360; i += 30) {
		int textAngle = angle + i;
		double rad = textAngle * PI / 180.0;
		double textPosX = RMI_x + 0.55 * RMI_side/2 * cos(rad);
		double textPosY = RMI_y + 0.55 * RMI_side/2 * sin(rad);
		
		LOGFONTW font;
		setfont(RMI_side/2 * 0.2, 0, "Leelawadee");
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		setcolor(EGEARGB(0xff, 0xef, 0xef, 0xef));
		getfont(&font);
		font.lfEscapement = 2700 - textAngle * 10;
		font.lfWeight = 550;
		setfont(&font);
#if 0
		xyprintf(textPosX = RMI_x + 0.8 * RMI_side * cos(rad), RMI_y - 0.8 * RMI_side/2 * sin(rad), "%d", i);
#endif
		char strBuffer[64];
		sprintf_s(strBuffer, "%d", i / 10);
		ege_drawtext(strBuffer, textPosX, textPosY);
	}
}


void draw_RMI(double RMI_x, double RMI_y, double RMI_side) {
	
	double RMI_r = RMI_side / 28 * 13;
	double R = RMI_r / 52 * 38;
	double triangle_R = RMI_r / 52 * 46;
	double length_1 = RMI_r / 52 * 8;//长刻度
	double length_2 = RMI_r / 52 * 6;//中刻度
	double length_3 = RMI_r / 52 * 4;//短刻度
	double triangle_height = RMI_r / 52 * 4;
	//double angle = 0;
	double side2 = RMI_side * 13 / 14;
	double lefttop_x = RMI_x - side2 / 2.0;
	double lefttop_y = RMI_y - side2 / 2.0;
	double R2 = side2 / 52.0 * 21;//表盘半径
	double R1 = side2 / 52.0 * 22;//表盘阴影半径
	
	setcolor(EGEARGB(0X4F, 0X00, 0X00, 0X00));
	setlinewidth(5);
	int RCDI_frame_edge_pointsNum = 16;
	ege_point RCDI_frame_edge_polyPoints[16] = { {lefttop_x + side2 / 26 * 3,lefttop_y - side2 / 26},{lefttop_x - side2 / 26 ,lefttop_y + side2 / 26 * 3},
		
		{lefttop_x - side2 / 26 ,lefttop_y + side2 / 26 * 3},{lefttop_x - side2 / 26 ,lefttop_y + side2 / 26 * 3},
		
		{lefttop_x - side2 / 26,lefttop_y + side2 - side2 / 26 * 3},{lefttop_x - side2 / 26,lefttop_y + side2 - side2 / 26 * 3},
		
		{lefttop_x - side2 / 26,lefttop_y + side2 - side2 / 26 * 3},{lefttop_x + side2 / 26 * 3,lefttop_y + side2 + side2 / 26},
		
		
		{lefttop_x + side2 / 26 * 3,lefttop_y + side2 + side2 / 26},{lefttop_x + side2 / 26 * 3,lefttop_y + side2 + side2 / 26},
		
		{lefttop_x + side2 - side2 / 26 * 3,lefttop_y + side2 + side2 / 26},{lefttop_x + side2 - side2 / 26 * 3,lefttop_y + side2 + side2 / 26},
		
		{lefttop_x + side2 - side2 / 26 * 3,lefttop_y + side2 + side2 / 26},{lefttop_x + side2 + side2 / 26,lefttop_y + side2 - side2 / 26 * 3},
		
		{lefttop_x + side2 + side2 / 26,lefttop_y + side2 - side2 / 26 * 3},{lefttop_x + side2 + side2 / 26,lefttop_y + side2 - side2 / 26 * 3}
		
		
	};
	ege_bezier(RCDI_frame_edge_pointsNum, RCDI_frame_edge_polyPoints);
	
	
	int num_points2 = 4;
	ege_point polypoints2[4] = {
		{lefttop_x + side2 / 26 * 3 + side2 / 250,lefttop_y - side2 / 26 - side2 / 250},
		{lefttop_x + side2 - side2 / 26 * 3 + side2 / 250,lefttop_y - side2 / 26 - side2 / 250},
		{lefttop_x + side2 + side2 / 26 + side2 / 250,lefttop_y + side2 / 26 * 3 - side2 / 250} ,
		{lefttop_x + side2 + side2 / 26 + side2 / 250,lefttop_y + side2 - side2 / 26 * 3 - side2 / 250}
	};
	
	ege_setpattern_lineargradient(lefttop_x + side2 / 26 * 3 + side2 / 250, lefttop_y - side2 / 26 - side2 / 250, EGEARGB(0X6F, 0XFF, 0XFF, 0XFF),
		lefttop_x + side2 + side2 / 26 + side2 / 250, lefttop_y + side2 - side2 / 26 * 3 - side2 / 250, EGEARGB(0X2F, 0XFF, 0XFF, 0XFF));
	ege_fillpoly(num_points2, polypoints2);
	ege_setpattern_none();
	
	
	// 边框颜色
	int num_points3 = 8;
	ege_point polypoints3[8] = {
		{lefttop_x - side2 / 26 ,lefttop_y + side2 / 26 * 3},
		{lefttop_x + side2 / 26 * 3,lefttop_y - side2 / 26},
		{lefttop_x + side2 - side2 / 26 * 3,lefttop_y - side2 / 26},
		{lefttop_x + side2 + side2 / 26,lefttop_y + side2 / 26 * 3},
		{lefttop_x + side2 + side2 / 26,lefttop_y + side2 - side2 / 26 * 3},
		{lefttop_x + side2 - side2 / 26 * 3,lefttop_y + side2 + side2 / 26},
		{lefttop_x + side2 / 26 * 3,lefttop_y + side2 + side2 / 26},
		{lefttop_x - side2 / 26,lefttop_y + side2 - side2 / 26 * 3}
	};
	ege_setpattern_lineargradient(lefttop_x + side2 + side2 / 26, lefttop_y + side2 / 26 * 3, EGEARGB(0XFF, 0X1F, 0X23, 0X2C),
		lefttop_x - side2 / 26, lefttop_y + side2 - side2 / 26 * 3, EGEARGB(0XFF, 0X17, 0X1A, 0X20));
	ege_fillpoly(num_points3, polypoints3);
	ege_setpattern_none();
	
	
	
	ege_enable_aa(false);
	setcolor(BLACK);
	
	int left_pointsNum = 10;
	ege_point left_ploypoints[10] = {
		{lefttop_x - side2 / 26 + side2 / 52 * 2,lefttop_y + side2 - side2 / 26 * 3},
		{lefttop_x - side2 / 26 + side2 / 52 * 5,lefttop_y + side2 - side2 / 52 * 2},
		{lefttop_x - side2 / 26 + side2 / 52 * 9,lefttop_y + side2 },
		{lefttop_x - side2 / 26 + side2 / 52 * 10,lefttop_y + side2 - side2 / 26 * 3 },
		
		{lefttop_x - side2 / 26 + side2 / 52 * 8,lefttop_y + side2 - side2 / 26 * 6},
		{lefttop_x - side2 / 26 + side2 / 52 * 6,lefttop_y + side2 - side2 / 26 * 7},
		{lefttop_x - side2 / 26 + side2 / 52 * 4,lefttop_y + side2 - side2 / 26 * 7},
		
		{lefttop_x - side2 / 26 + side2 / 52 * 1,lefttop_y + side2 - side2 / 26 * 5},
		{lefttop_x - side2 / 26 + side2 / 52 * 3,lefttop_y + side2 - side2 / 26 * 3},
		{lefttop_x - side2 / 26 + side2 / 52 * 2,lefttop_y + side2 - side2 / 26 * 3}
		
	};
	ege_bezier(left_pointsNum, left_ploypoints);
	setfillcolor(BLACK);
	floodfill(lefttop_x - side2 / 26 + side2 / 52 * 3, lefttop_y + side2 - side2 / 52 * 7,BLACK);
	
	int right_pointsNum = 10;
	ege_point right_ploypoints[10] = {
		{lefttop_x -  side2 / 26 - side2 / 52 * 6 + side2,lefttop_y + side2 - side2 / 26 * 3},
		{lefttop_x - side2 / 26 - side2 / 52 * 6 + side2 / 52 * 1 + side2,lefttop_y + side2 },
		{lefttop_x - side2 / 26 - side2 / 52 * 6 + side2 / 52 * 5 + side2,lefttop_y + side2 - side2 / 52 * 2},
		{lefttop_x - side2 / 26 - side2 / 52 * 6 + side2 / 52 * 8 + side2,lefttop_y + side2 - side2 / 26 * 3 },
		
		{lefttop_x - side2 / 26 - side2 / 52 * 6 + side2 / 52 * 8 + side2,lefttop_y + side2 - side2 / 26 * 3 },
		{lefttop_x - side2 / 26 - side2 / 52 * 6 + side2 / 52 * 10 + side2,lefttop_y + side2 - side2 / 26 * 8 },
		{lefttop_x - side2 / 26 - side2 / 52 * 6 + side2 / 52 * 7 + side2,lefttop_y + side2 - side2 / 26 * 7 },
		
		{lefttop_x - side2 / 26 - side2 / 52 * 8 + side2 / 52 * 7 + side2,lefttop_y + side2 - side2 / 26 * 7 },
		{lefttop_x - side2 / 26 - side2 / 52 * 13 + side2 / 52 * 7 + side2,lefttop_y + side2 - side2 / 26 * 5 },
		{lefttop_x - side2 / 26 - side2 / 52 * 6 + side2,lefttop_y + side2 - side2 / 26 * 3},
		
	};
	ege_bezier(right_pointsNum, right_ploypoints);
	setfillcolor(BLACK);
	floodfill(lefttop_x - side2 / 26 - side2 / 52 * 5 + side2, lefttop_y + side2 - side2 / 26 * 4 , BLACK);
	ege_enable_aa(true);
	setcolor(BLACK);
	
	int left_pointsNum_1= 10;
	ege_point left_ploypoints_1[10] = {
		{lefttop_x - side2 / 26 + side2 / 52 * 2,lefttop_y + side2 - side2 / 26 * 3},
		{lefttop_x - side2 / 26 + side2 / 52 * 5,lefttop_y + side2 - side2 / 52 * 2},
		{lefttop_x - side2 / 26 + side2 / 52 * 9,lefttop_y + side2 },
		{lefttop_x - side2 / 26 + side2 / 52 * 10,lefttop_y + side2 - side2 / 26 * 3 },
		
		{lefttop_x - side2 / 26 + side2 / 52 * 8,lefttop_y + side2 - side2 / 26 * 6},
		{lefttop_x - side2 / 26 + side2 / 52 * 6,lefttop_y + side2 - side2 / 26 * 7},
		{lefttop_x - side2 / 26 + side2 / 52 * 4,lefttop_y + side2 - side2 / 26 * 7},
		
		{lefttop_x - side2 / 26 + side2 / 52 * 1,lefttop_y + side2 - side2 / 26 * 5},
		{lefttop_x - side2 / 26 + side2 / 52 * 3,lefttop_y + side2 - side2 / 26 * 3},
		{lefttop_x - side2 / 26 + side2 / 52 * 2,lefttop_y + side2 - side2 / 26 * 3}
		
	};
	ege_bezier(left_pointsNum_1, left_ploypoints_1);
	
	int right_pointsNum_1 = 10;
	ege_point right_ploypoints_1[10] = {
		{lefttop_x - side2 / 26 * 4 + side2,lefttop_y + side2 - side2 / 26 * 3},
		{lefttop_x - side2 / 26 * 4 + side2 / 52 * 1 + side2,lefttop_y + side2 },
		{lefttop_x - side2 / 26 * 4 + side2 / 52 * 5 + side2,lefttop_y + side2 - side2 / 52 * 2},
		{lefttop_x - side2 / 26 * 4 + side2 / 52 * 8 + side2,lefttop_y + side2 - side2 / 26 * 3 },
		
		{lefttop_x - side2 / 26 * 4 + side2 / 52 * 8 + side2,lefttop_y + side2 - side2 / 26 * 3 },
		{lefttop_x - side2 / 26 * 4 + side2 / 52 * 10 + side2,lefttop_y + side2 - side2 / 26 * 8 },
		{lefttop_x - side2 / 26 * 4 + side2 / 52 * 7 + side2,lefttop_y + side2 - side2 / 26 * 7 },
		
		{lefttop_x - side2 / 26 * 5 + side2 / 52 * 7 + side2,lefttop_y + side2 - side2 / 26 * 7 },
		{lefttop_x - side2 / 26 - side2 / 52 * 13 + side2 / 52 * 7 + side2,lefttop_y + side2 - side2 / 26 * 5 },
		{lefttop_x - side2 / 26 * 4 + side2,lefttop_y + side2 - side2 / 26 * 3},
		
	};
	ege_bezier(right_pointsNum_1, right_ploypoints_1);
	setcolor(EGEARGB(0XFF, 0X60, 0X60, 0X60));
	setlinewidth(side2 / 520 * 2);
	ege_line(lefttop_x - side2 / 26 * 3.5 + side2, lefttop_y + side2 - side2 / 26 * 3 , lefttop_x - side2 / 26 * 2.5 + side2, lefttop_y + side2 - side2 / 26 * 5);
	ege_line(lefttop_x - side2 / 26 * 2.8 + side2, lefttop_y + side2 - side2 / 26 * 5.5, lefttop_x - side2 / 26 * 2.5 + side2, lefttop_y + side2 - side2 / 26 * 5);
	ege_line(lefttop_x - side2 / 26 * 2.8 + side2, lefttop_y + side2 - side2 / 26 * 5.5, lefttop_x - side2 / 26 * 1 + side2, lefttop_y + side2 - side2 / 26 * 6);
	
	
	ege_line(lefttop_x - side2 / 26 * 2.5 + side2, lefttop_y + side2 - side2 / 26 * 2, lefttop_x - side2 / 26 * 1.5 + side2, lefttop_y + side2 - side2 / 26 * 4);
	ege_line(lefttop_x - side2 / 26 * 1 + side2, lefttop_y + side2 - side2 / 26 * 3.7, lefttop_x - side2 / 26 * 1.5 + side2, lefttop_y + side2 - side2 / 26 * 4);
	ege_line(lefttop_x - side2 / 26 * 1 + side2, lefttop_y + side2 - side2 / 26 * 3.7, lefttop_x - side2 / 26 * 1 + side2, lefttop_y + side2 - side2 / 26 * 6);
	
	int num = 7;
	ege_point polypoints[7] = {
		{lefttop_x - side2 / 26 + side2 / 52 * 6.1, lefttop_y + side2 - side2 / 52 * 2.5},
		{lefttop_x - side2 / 26 + side2 / 52 * 8, lefttop_y + side2 - side2 / 52 * 3.5},
		{lefttop_x - side2 / 26 + side2 / 52 * 6.5, lefttop_y + side2 - side2 / 52 * 8.5},
		{lefttop_x - side2 / 26 + side2 / 52 * 7.5, lefttop_y + side2 - side2 / 52 * 9},
		{lefttop_x - side2 / 26 + side2 / 52 * 4.5, lefttop_y + side2 - side2 / 52 * 11},
		{lefttop_x - side2 / 26 + side2 / 52 * 3.5, lefttop_y + side2 - side2 / 52 * 7.5},
		{lefttop_x - side2 / 26 + side2 / 52 * 4.5, lefttop_y + side2 - side2 / 52 * 8}
	};
	setfillcolor(EGEARGB(0XFF, 0X60, 0X60, 0X60));
	ege_fillpoly(num, polypoints);

	
	// 表盘阴影
	ege_setpattern_lineargradient(RMI_x + R1 * cos(PI / 4), RMI_y - R1 * sin(PI / 4), EGEARGB(0XFF, 0X00, 0X00, 0X00),
		RMI_x - R1 * cos(PI / 4), RMI_y + R1 * sin(PI / 4), EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillellipse(lefttop_x + side2 / 52 * 2, lefttop_y + side2 / 52 * 2, side2 - side2 / 26 * 2, side2 - side2 / 26 * 2);
	ege_setpattern_none();
	
	// 表盘颜色
	ege_setpattern_lineargradient(RMI_x + R2 * cos(PI / 4), RMI_y - R2 * sin(PI / 4), EGEARGB(0XFF, 0X15, 0X15, 0X15),
		RMI_x - R2 * cos(PI / 4), RMI_y + R2 * sin(PI / 4), EGEARGB(0XFF, 0X10, 0X10, 0X10));
	
	ege_fillellipse(lefttop_x + side2 / 52 * 3, lefttop_y + side2 / 52 * 3, side2 - side2 / 26 * 3, side2 - side2 / 26 * 3);
	ege_setpattern_none();
	
	draw_text(RMI_x, RMI_y, RMI_side);
	
	setcolor(WHITE);
	setlinewidth(0.005 * RMI_side);
	for (int i = 0; i <= 360; i+=30) {
		ege_line(RMI_x - R * cos((i + angle) * PI / 180), RMI_y - R * sin((i + angle) * PI / 180),
			RMI_x - (R + length_1) * cos((i + angle) * PI / 180), RMI_y - (R + length_1) * sin((i + angle) * PI / 180));
	}
	for (int i = 5; i < 360; i += 10) {
		ege_line(RMI_x - R * cos((i + angle) * PI / 180), RMI_y - R * sin((i + angle) * PI / 180),
			RMI_x - (R + length_3) * cos((i + angle) * PI / 180), RMI_y - (R + length_3) * sin((i + angle) * PI / 180));
	}
	for (int i = 10; i <= 360; i += 10) {
		ege_line(RMI_x - R * cos((i + angle) * PI / 180), RMI_y - R * sin((i + angle) * PI / 180),
			RMI_x - (R + length_2) * cos((i + angle) * PI / 180), RMI_y - (R + length_2) * sin((i + angle) * PI / 180));
	}
	
	setcolor(EGEARGB(0XFF, 0X80, 0X80, 0X80));
	ege_line(RMI_x - (R - RMI_side / 520 * 3) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 3) * sin(RMI_point_angle_1 * PI / 180),
		RMI_x - (R - RMI_side / 520 * 33) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 33) * sin(RMI_point_angle_1 * PI / 180));
	ege_line(RMI_x - (R - RMI_side / 520 * 63) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 63) * sin(RMI_point_angle_1 * PI / 180),
		RMI_x - (R - RMI_side / 520 * 93) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 93) * sin(RMI_point_angle_1 * PI / 180));
	ege_line(RMI_x - (R - RMI_side / 520 * 123) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 123) * sin(RMI_point_angle_1 * PI / 180),
		RMI_x - (R - RMI_side / 520 * 153) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 153) * sin(RMI_point_angle_1 * PI / 180));
	ege_line(RMI_x - (R - RMI_side / 520 * 183) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 183) * sin(RMI_point_angle_1 * PI / 180),
		RMI_x - (R - RMI_side / 520 * 213) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 213) * sin(RMI_point_angle_1 * PI / 180));
	ege_line(RMI_x - (R - RMI_side / 520 * 243) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 243) * sin(RMI_point_angle_1 * PI / 180),
		RMI_x - (R - RMI_side / 520 * 273) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 273) * sin(RMI_point_angle_1 * PI / 180));
	ege_line(RMI_x - (R - RMI_side / 520 * 303) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 303) * sin(RMI_point_angle_1 * PI / 180),
		RMI_x - (R - RMI_side / 520 * 333) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 333) * sin(RMI_point_angle_1 * PI / 180));
	
	
	
	
	ege_line((-R + RMI_side / 520 * 83) * cos(RMI_point_angle_2 * PI / 180) - (-RMI_side / 104 * 3) * sin(RMI_point_angle_2 * PI / 180) + RMI_x,
		(-RMI_side / 104 * 3) * cos(RMI_point_angle_2 * PI / 180) + (-R + RMI_side / 520 * 83) * sin(RMI_point_angle_2 * PI / 180) + RMI_y,
		(-R + RMI_side / 520 * 263) * cos(RMI_point_angle_2 * PI / 180) - (-RMI_side / 104 * 3) * sin(RMI_point_angle_2 * PI / 180) + RMI_x,
		(-RMI_side / 104 * 3) * cos(RMI_point_angle_2 * PI / 180) + (-R + RMI_side / 520 * 263) * sin(RMI_point_angle_2 * PI / 180) + RMI_y);
	ege_line( ( - R + RMI_side / 520 * 83) * cos(RMI_point_angle_2 * PI / 180) - (RMI_side / 104 * 3) * sin(RMI_point_angle_2 * PI / 180) + RMI_x,
		( RMI_side / 104 * 3) * cos(RMI_point_angle_2* PI / 180) + (-R + RMI_side / 520 * 83) * sin(RMI_point_angle_2 * PI / 180) + RMI_y,
		( - R + RMI_side / 520 * 263) * cos(RMI_point_angle_2* PI / 180) -(RMI_side / 104 * 3) * sin(RMI_point_angle_2 * PI / 180) + RMI_x,
		(RMI_side / 104 * 3) * cos(RMI_point_angle_2* PI / 180) + (-R + RMI_side / 520 * 263) * sin(RMI_point_angle_2 * PI / 180) + RMI_y);

	
	
	for (int j = -45; j < 46; j += 45) {
		setfillcolor(EGEARGB(0XFF, 0XFF, 0XFF, 0XFF));
		int num_points = 3;
		ege_point ploypoints[3] = {
			{RMI_x - (triangle_R - triangle_height) * cos(j * PI / 180),RMI_y - (triangle_R - triangle_height) * sin(j * PI / 180)},
			{RMI_x - triangle_R * cos((j - 2) * PI / 180),RMI_y - triangle_R * sin((j - 2) * PI / 180)},
			{RMI_x - triangle_R * cos((j + 2) * PI / 180),RMI_y - triangle_R * sin((j + 2) * PI / 180)}
		};
		ege_fillpoly(num_points, ploypoints);
		
	}
	for (int j = 135; j < 226; j += 45) {
		setfillcolor(EGEARGB(0XFF, 0XFF, 0XFF, 0XFF));
		int num_points = 3;
		ege_point ploypoints[3] = {
			{RMI_x - (triangle_R - triangle_height) * cos(j * PI / 180),RMI_y - (triangle_R - triangle_height) * sin(j * PI / 180)},
			{RMI_x - triangle_R * cos((j - 2) * PI / 180),RMI_y - triangle_R * sin((j - 2) * PI / 180)},
			{RMI_x - triangle_R * cos((j + 2) * PI / 180),RMI_y - triangle_R * sin((j + 2) * PI / 180)}
		};
		ege_fillpoly(num_points, ploypoints);
	}
	setfillcolor(EGEARGB(0XFF, 0XFF, 0XFF, 0XFF));
	int num_points_1 = 5;
	ege_point ploypoints_1 [5] = {
		{RMI_x , RMI_y - triangle_R + triangle_height},
		{RMI_x - (triangle_R - triangle_height / 2) * cos(88 * PI / 180),RMI_y - (triangle_R - triangle_height / 2) * sin(88 * PI / 180)},
		{RMI_x - (triangle_R - triangle_height / 2) * cos(88 * PI / 180),RMI_y - (triangle_R - triangle_height / 2) * sin(88 * PI / 180) - side2 / 520 * 10},
		{RMI_x - (triangle_R - triangle_height / 2) * cos(92 * PI / 180),RMI_y - (triangle_R - triangle_height / 2) * sin(92 * PI / 180) - side2 / 520 * 10},
		{RMI_x - (triangle_R - triangle_height / 2) * cos(92 * PI / 180),RMI_y - (triangle_R - triangle_height / 2) * sin(92 * PI / 180)}
	};
	ege_fillpoly(num_points_1, ploypoints_1);
	
	int num_points_2 = 5;
	ege_point ploypoints_2[5] = {
		{RMI_x , RMI_y + triangle_R - triangle_height},
		{RMI_x - (triangle_R - triangle_height / 2) * cos(88 * PI / 180),RMI_y - (triangle_R - triangle_height / 2) * sin(272 * PI / 180)},
		{RMI_x - (triangle_R - triangle_height / 2) * cos(88 * PI / 180),RMI_y - (triangle_R - triangle_height / 2) * sin(272 * PI / 180) + side2 / 520 * 10},
		{RMI_x - (triangle_R - triangle_height / 2) * cos(92 * PI / 180),RMI_y - (triangle_R - triangle_height / 2) * sin(268 * PI / 180) + side2 / 520 * 10},
		{RMI_x - (triangle_R - triangle_height / 2) * cos(92 * PI / 180),RMI_y - (triangle_R - triangle_height / 2) * sin(268 * PI / 180)}
	};
	ege_fillpoly(num_points_1, ploypoints_2);
	
	setfillcolor(EGEARGB(0XFF, 0X20, 0X20, 0X20));
	ege_fillellipse(RMI_x - RMI_side / 104 * 5, RMI_y - RMI_side / 104 * 5, RMI_side / 52 * 5, RMI_side / 52 * 5);
	setfillcolor(BLACK);
	ege_fillellipse(RMI_x - RMI_side / 104 * 3, RMI_y - RMI_side / 104 * 3, RMI_side / 52 * 3, RMI_side / 52 * 3);
	setfillcolor(EGEARGB(0XFF, 0X20, 0X20, 0X20));
	ege_fillellipse(RMI_x - RMI_side / 416 * 11, RMI_y - RMI_side / 416 * 11, RMI_side / 208 * 11, RMI_side / 208 * 11);
	
	setfillcolor(EGEARGB(0XFF, 0X80, 0X80, 0X80));
	int num_points_3 = 6;
	ege_point ploypoints_3[6] = {
		{ ( - R + RMI_side / 520 * 263) * cos(RMI_point_angle_2 * PI / 180) - (-RMI_side / 208 * 7) * sin(RMI_point_angle_2 * PI / 180) + RMI_x ,
			( - RMI_side / 208 * 7)* cos(RMI_point_angle_2 * PI / 180) + (-R + RMI_side / 520 * 263) * sin(RMI_point_angle_2 * PI / 180) + RMI_y},
		{( - R + RMI_side / 520 * 288) * cos(RMI_point_angle_2 * PI / 180) - (-RMI_side / 208 * 2) * sin(RMI_point_angle_2 * PI / 180) + RMI_x,
			( - RMI_side / 208 * 2) * cos(RMI_point_angle_2 * PI / 180) + (-R + RMI_side / 520 * 288) * sin(RMI_point_angle_2 * PI / 180) + RMI_y },
		{ ( - R + RMI_side / 520 * 343) * cos(RMI_point_angle_2 * PI / 180) - ( - RMI_side / 416) * sin(RMI_point_angle_2 * PI / 180) + RMI_x,
			(-RMI_side / 416)* cos(RMI_point_angle_2 * PI / 180) + (-R + RMI_side / 520 * 343) * sin(RMI_point_angle_2 * PI / 180) + RMI_y},
		{ (-R + RMI_side / 520 * 343) * cos(RMI_point_angle_2 * PI / 180) - (RMI_side / 416) * sin(RMI_point_angle_2 * PI / 180) + RMI_x,
			(RMI_side / 416) * cos(RMI_point_angle_2 * PI / 180) + (-R + RMI_side / 520 * 343) * sin(RMI_point_angle_2 * PI / 180) + RMI_y},
		{(-R + RMI_side / 520 * 288) * cos(RMI_point_angle_2 * PI / 180) - (RMI_side / 208 * 2) * sin(RMI_point_angle_2 * PI / 180) + RMI_x,
			(RMI_side / 208 * 2) * cos(RMI_point_angle_2 * PI / 180) + (-R + RMI_side / 520 * 288) * sin(RMI_point_angle_2 * PI / 180) + RMI_y },
		{ (-R + RMI_side / 520 * 263) * cos(RMI_point_angle_2 * PI / 180) - (RMI_side / 208 * 7) * sin(RMI_point_angle_2 * PI / 180) + RMI_x ,
			(RMI_side / 208 * 7) * cos(RMI_point_angle_2 * PI / 180) + (-R + RMI_side / 520 * 263) * sin(RMI_point_angle_2 * PI / 180) + RMI_y}
	};
	ege_fillpoly(num_points_3, ploypoints_3);
	
	int num_points_4 = 6;
	ege_point ploypoints_4[6] = {
		{ (-R + RMI_side / 520 * 263) * cos(RMI_point_angle_1 * PI / 180) - (-RMI_side / 208 * 3) * sin(RMI_point_angle_1 * PI / 180) + RMI_x ,
			(-RMI_side / 208 * 3) * cos(RMI_point_angle_1 * PI / 180) + (-R + RMI_side / 520 * 263) * sin(RMI_point_angle_1 * PI / 180) + RMI_y},
		{(-R + RMI_side / 520 * 288) * cos(RMI_point_angle_1 * PI / 180) - (-RMI_side / 208 ) * sin(RMI_point_angle_1 * PI / 180) + RMI_x,
			(-RMI_side / 208) * cos(RMI_point_angle_1 * PI / 180) + (-R + RMI_side / 520 * 288) * sin(RMI_point_angle_1 * PI / 180) + RMI_y },
		{ (-R + RMI_side / 520 * 343) * cos(RMI_point_angle_1 * PI / 180) - (-RMI_side / 416) * sin(RMI_point_angle_1 * PI / 180) + RMI_x,
			(-RMI_side / 416) * cos(RMI_point_angle_1 * PI / 180) + (-R + RMI_side / 520 * 343) * sin(RMI_point_angle_1 * PI / 180) + RMI_y},
		{ (-R + RMI_side / 520 * 343) * cos(RMI_point_angle_1 * PI / 180) - (RMI_side / 416) * sin(RMI_point_angle_1 * PI / 180) + RMI_x,
			(RMI_side / 416) * cos(RMI_point_angle_1 * PI / 180) + (-R + RMI_side / 520 * 343) * sin(RMI_point_angle_1 * PI / 180) + RMI_y},
		{(-R + RMI_side / 520 * 288) * cos(RMI_point_angle_1 * PI / 180) - (RMI_side / 208 ) * sin(RMI_point_angle_1 * PI / 180) + RMI_x,
			(RMI_side / 208) * cos(RMI_point_angle_1 * PI / 180) + (-R + RMI_side / 520 * 288) * sin(RMI_point_angle_1 * PI / 180) + RMI_y },
		{ (-R + RMI_side / 520 * 263) * cos(RMI_point_angle_1 * PI / 180) - (RMI_side / 208 * 3) * sin(RMI_point_angle_1 * PI / 180) + RMI_x ,
			(RMI_side / 208 * 3) * cos(RMI_point_angle_1 * PI / 180) + (-R + RMI_side / 520 * 263) * sin(RMI_point_angle_1 * PI / 180) + RMI_y}
		
		
	};
	ege_fillpoly(num_points_4, ploypoints_4);
	
	
	//光照效果
	draw_light(RMI_x, RMI_y, RMI_r * 13 / 14);
	
}


