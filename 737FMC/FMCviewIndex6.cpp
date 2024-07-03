#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>
#include "FMCviewIndex2.h"

char origin_6[5] = {};// { "ZBAA" };
char left1_6[7] = {};
char left2_6[7] = {};//{ "CDY11D" };
char left3_6[7] = {};//{ "CDY11D" };
char left4_6[7] = {};//{ "CDY11D" };
char left5_6[7] = {};//{ "CDY11D" };
char left6_6[7] = {};//{ "CDY11D" };


char right1_6[7] = {};
char right2_6[7] = {};//{ "RW18L" };
char right3_6[7] = {};//{ "RW18R" };
char right4_6[7] = {};//{ "RW19" };
char right5_6[7] = {};//{ "RW36R" };
char right6_6[7] = {};//{ "RW36L" };

char input_6[64] = {};//{"ZBAA"};
boolean button_clicked_6 = false;
boolean empty_6 = false;

void draw_frame_6(double side, double center_x, double center_y) {
	double width = side * 650 / 685;
	double height = side * 540 / 685;
	double x = center_x - width / 2;
	double y = center_y - height / 2;
	setfillcolor(BLACK);
	ege_fillrect(x, y, width, height);
}

void draw_topic_6(double side, double center_x, double center_y) {
	double single = side / 67.0 * 5.7;
	double height = side * 0.035 * 2;
	double wide = side * 0.035 * 2;
	double x = center_x - single * 2.7;
	double y = center_y - side * 210 / 685;
	setcolor(EGEARGB(255, 32, 220, 224));
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	ege_drawtext(origin_6, x - wide * 1.5, y);
	ege_drawtext("DEPART", x + wide * 1.5, y);
	
	x = center_x + side * 0.3;
	ege_drawtext("1/1", x, y);
}

void draw_line1_upper_6(double side, double center_x, double center_y) {
	double single = side / 67.0 * 5.7;
	double height = side * 0.035 * 2 / 2;
	double wide = side * 0.035 * 2 / 2;
	double x = center_x - single * 4;
	double y = center_y - side * 210 / 685 + single * 0.7;
	setcolor(EGEARGB(255, 32, 220, 224));
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	ege_drawtext("S I D S", x, y);
	ege_drawtext("A C T   F P L N", center_x, y);
	x += single * 8.2;
	ege_drawtext("R W Y S", x, y);
	
}

void draw_line1_6(double side, double center_x, double center_y) {
	setcolor(WHITE);
	setbkmode(true);
	double single = side / 67.0;
	
	double height = side * 0.035 * 1.5;
	double wide = side * 0.035 * 1.5;
	double y = center_y - single * 14.6;
	double x = center_x - single * 24.4;
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	ege_drawtext("<SEL>", center_x + single * 16, y);
	ege_drawtext("<SEL>", x + single * 10, y);
	ege_drawtext(left1_6, x, y);
	if (strlen(right1_6) == 4) {
		x = center_x + single * 25;
		ege_drawtext(right1_6, x, y);
	}
	else if (strlen(right1_6) == 5) {
		x = center_x + single * 25 - wide / 3;
		ege_drawtext(right1_6, x, y);
	}
	else if (strlen(right1_6) == 6) {
		x = center_x + single * 25 - wide / 2;
		ege_drawtext(right1_6, x, y);
	}
}

void draw_line2_upper_6(double side, double center_x, double center_y) {
	double single = side / 67.0 * 5.7;
	double height = side * 0.035 * 2 / 2;
	double wide = side * 0.035 * 2 / 2;
	double x = center_x - single * 3.8;
	double y = center_y - single * 2;
	setcolor(EGEARGB(255, 32, 220, 224));
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	ege_drawtext("T R A N S", x, y);
}

void draw_line2_6(double side, double center_x, double center_y) {
	setcolor(WHITE);
	double single = side / 67.0;
	double height = side * 0.035 * 1.5;
	double wide = side * 0.035 * 1.5;
	double y = center_y - single * 7.6;
	double x = center_x - single * 24.4;
	
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	
	ege_drawtext(left2_6, x, y);
	if (strlen(right2_6) == 4) {
		x = center_x + single * 25;
		ege_drawtext(right2_6, x, y);
	}
	else if (strlen(right2_6) == 5) {
		x = center_x + single * 25 - wide / 3;
		ege_drawtext(right2_6, x, y);
	}
	else if (strlen(right2_6) == 6) {
		x = center_x + single * 25 - wide / 2;
		ege_drawtext(right2_6, x, y);
	}
}

void draw_line3_6(double side, double center_x, double center_y) {
	setcolor(WHITE);
	double single = side / 67.0;
	
	double height = side * 0.035 * 1.5;
	double wide = side * 0.035 * 1.5;
	double y = center_y - single * 0.7;
	double x = center_x - single * 24.4;
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	
	ege_drawtext(left3_6, x, y);
	if (strlen(right3_6) == 4) {
		x = center_x + single * 25;
		ege_drawtext(right3_6, x, y);
	}
	else if (strlen(right3_6) == 5) {
		x = center_x + single * 25 - wide / 3;
		ege_drawtext(right3_6, x, y);
	}
	else if (strlen(right3_6) == 6) {
		x = center_x + single * 25 - wide / 2;
		ege_drawtext(right3_6, x, y);
	}
}

void draw_line4_6(double side, double center_x, double center_y) {
	setcolor(WHITE);
	double single = side / 67.0;
	double y = center_y + single * 6.3;
	double x = center_x - single * 24.4;
	double height = side * 0.035 * 1.5;
	double wide = side * 0.035 * 1.5;
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	
	ege_drawtext(left4_6, x, y);
	if (strlen(right4_6) == 4) {
		x = center_x + single * 25;
		ege_drawtext(right4_6, x, y);
	}
	else if (strlen(right4_6) == 5) {
		x = center_x + single * 25 - wide / 3;
		ege_drawtext(right4_6, x, y);
	}
	else if (strlen(right4_6) == 6) {
		x = center_x + single * 25 - wide / 2;
		ege_drawtext(right4_6, x, y);
	}
}

void draw_line5_6(double side, double center_x, double center_y) {
	setcolor(WHITE);
	double single = side / 67.0;
	double y = center_y + single * 13.2;
	double x = center_x - single * 24.4;
	double height = side * 0.035 * 1.5;
	double wide = side * 0.035 * 1.5;
	
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	ege_drawtext(left5_6, x, y);
	if (strlen(right5_6) == 4) {
		x = center_x + single * 25;
		ege_drawtext(right5_6, x, y);
	}
	else if (strlen(right5_6) == 5) {
		x = center_x + single * 25 - wide / 3;
		ege_drawtext(right5_6, x, y);
	}
	else if (strlen(right5_6) == 6) {
		x = center_x + single * 25 - wide / 2;
		ege_drawtext(right5_6, x, y);
	}
}

void draw_line6_upper_6(double side, double center_x, double center_y) {
	double single = side / 67.0 * 5.7;
	double height = side * 0.035 * 2 / 2;
	double wide = side * 0.035 * 2 / 2;
	double x = center_x;
	double y = center_y + single * 2.9;
	setcolor(EGEARGB(255, 32, 220, 224));
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	ege_drawtext("——————————————————————————————————", x, y);
}

void draw_line6_6(double side, double center_x, double center_y) {
	setcolor(WHITE);
	double single = side / 67.0;
	double y = center_y + single * 20.2;
	double x = center_x - single * 20.3;
	double height = side * 0.035 * 1.5;
	double wide = side * 0.035 * 1.5;
	
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	
	ege_drawtext("<CANCEL MOD", x, y);
	x = center_x + single * 25;
	ege_drawtext("FPLN>", x, y);
}

void draw_input_Box_6(double side, double center_x, double center_y) {
	setlinewidth(side * 0.0005);
	double single = side / 67.0;
	setcolor(EGEARGB(255, 32, 220, 224));
	double y = center_y + single * 23.3;
	double x1 = center_x - single * 29;
	double x2 = center_x + single * 29;
	double height = side * 0.035 * 1.8;
	double wide = side * 0.035 * 1.8;
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	ege_drawtext("[", x1, y);
	ege_drawtext("]", x2, y);
	
	setcolor(WHITE);
	//绘制输入框的输入值
	if (!strlen(input_6) == 0) {
		height = side * 0.035 * 1.8 * 0.8;
		wide = side * 0.035 * 1.8 / 2;
		setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
		y = y - height / 2;
		for (int i = 0; i < strlen(input_6); i++) {
			outtextxy(x1 + single * 0.2 + wide * i, y, input_6[i]);
		}
	}
}

void getScanner_6(char* left1, char* right1)
{
	strcpy_s(left1_6, left1);
	strcpy_s(right1_6, right1);
}

void getinformation_6(boolean state)
{
	empty_6 = state;
	if (state)
		FMC_getinformation(left1_6);
	else
		return;
}

boolean is_empty_6()
{
	if (strlen(left1_6) == 0 && strlen(right1_6) == 0 || !empty_6)
		return true;
	else
		return false;
}

void cancelright()
{
	strcpy(right1_6, "");
	empty_6 = false;
}

void cancelleft()
{
	strcpy(left1_6, "");
	empty_6 = false;
}

void draw_DEPART1_panel_6(double side, double center_x, double center_y) {
	double gap = side * 30 / 685;
	draw_frame_6(side, center_x, center_y);
	draw_topic_6(side, center_x, center_y);
	draw_line1_upper_6(side, center_x, center_y);
	draw_line1_6(side, center_x, center_y);
	
	draw_line2_upper_6(side, center_x, center_y);
	draw_line2_6(side, center_x, center_y);
	
	draw_line3_6(side, center_x, center_y);
	
	draw_line4_6(side, center_x, center_y);
	
	draw_line5_6(side, center_x, center_y);
	draw_line6_upper_6(side, center_x, center_y);
	
	draw_line6_6(side, center_x, center_y);
	draw_input_Box_6(side, center_x, center_y);
}

