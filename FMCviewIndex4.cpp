#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>
#include "FMCviewIndex5.h"

char origin_4[5] = {};// { "ZBAA" };
char left1_4[7] = { "CDY11D" };//{ "CDY11D" };
char left2_4[7] = { "CDY11D" };//{ "CDY11D" };
char left3_4[7] = { "CDY11D" };//{ "CDY11D" };
char left4_4[7] = { "CDY11D" };//{ "CDY11D" };
char left5_4[7] = { "CDY11D" };//{ "CDY11D" };
char left6_4[7] = { "CDY11D" };//{ "CDY11D" };

char right1_4[7] = { "RW01" };//{ "RW01" };
char right2_4[7] = { "RW18L" };//{ "RW18L" };
char right3_4[7] = { "RW18R" };//{ "RW18R" };
char right4_4[7] = { "RW19" };//{ "RW19" };
char right5_4[7] = { "RW36R" };//{ "RW36R" };
char right6_4[7] = { "RW36L" };//{ "RW36L" };

char input_4[64] = {};//{"ZBAA"};
boolean button_clicked_4 = false;

void draw_frame_4(double side, double center_x, double center_y) {
	double width = side * 650 / 685;
	double height = side * 540 / 685;
	double x = center_x - width / 2;
	double y = center_y - height / 2;
	setfillcolor(BLACK);
	ege_fillrect(x, y, width, height);
}

void draw_topic_4(double side, double center_x, double center_y) {
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
	ege_drawtext(origin_4, x - wide * 1.5, y);
	ege_drawtext("DEPART", x + wide * 1.5, y);

	x = center_x + side * 0.3;
	ege_drawtext("1/1", x, y);
}

void draw_line1_upper_4(double side, double center_x, double center_y) {
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

void draw_line1_4(double side, double center_x, double center_y) {
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

	ege_drawtext(left1_4, x, y);
	if (strlen(right1_4) == 4) {
		x = center_x + single * 25;
		ege_drawtext(right1_4, x, y);
	}
	else if (strlen(right1_4) == 5) {
		x = center_x + single * 25 - wide / 3;
		ege_drawtext(right1_4, x, y);
	}
	else if (strlen(right1_4) == 6) {
		x = center_x + single * 25 - wide / 2;
		ege_drawtext(right1_4, x, y);
	}
}

void draw_line2_4(double side, double center_x, double center_y) {
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

	ege_drawtext(left2_4, x, y);
	if (strlen(right2_4) == 4) {
		x = center_x + single * 25;
		ege_drawtext(right2_4, x, y);
	}
	else if (strlen(right2_4) == 5) {
		x = center_x + single * 25 - wide / 3;
		ege_drawtext(right2_4, x, y);
	}
	else if (strlen(right2_4) == 6) {
		x = center_x + single * 25 - wide / 2;
		ege_drawtext(right2_4, x, y);
	}
}

void draw_line3_4(double side, double center_x, double center_y) {
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

	ege_drawtext(left3_4, x, y);
	if (strlen(right3_4) == 4) {
		x = center_x + single * 25;
		ege_drawtext(right3_4, x, y);
	}
	else if (strlen(right3_4) == 5) {
		x = center_x + single * 25 - wide / 3;
		ege_drawtext(right3_4, x, y);
	}
	else if (strlen(right3_4) == 6) {
		x = center_x + single * 25 - wide / 2;
		ege_drawtext(right3_4, x, y);
	}
}

void draw_line4_4(double side, double center_x, double center_y) {
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

	ege_drawtext(left4_4, x, y);
	if (strlen(right4_4) == 4) {
		x = center_x + single * 25;
		ege_drawtext(right4_4, x, y);
	}
	else if (strlen(right4_4) == 5) {
		x = center_x + single * 25 - wide / 3;
		ege_drawtext(right4_4, x, y);
	}
	else if (strlen(right4_4) == 6) {
		x = center_x + single * 25 - wide / 2;
		ege_drawtext(right4_4, x, y);
	}
}

void draw_line5_4(double side, double center_x, double center_y) {
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
	ege_drawtext(left5_4, x, y);
	if (strlen(right5_4) == 4) {
		x = center_x + single * 25;
		ege_drawtext(right5_4, x, y);
	}
	else if (strlen(right5_4) == 5) {
		x = center_x + single * 25 - wide / 3;
		ege_drawtext(right5_4, x, y);
	}
	else if (strlen(right5_4) == 6) {
		x = center_x + single * 25 - wide / 2;
		ege_drawtext(right5_4, x, y);
	}
}

void draw_line6_upper_4(double side, double center_x, double center_y) {
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

void draw_line6_4(double side, double center_x, double center_y) {
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

	ege_drawtext("<DEP/ARR IDX", x, y);
	x = center_x + single * 25;
	ege_drawtext("FPLN>", x, y);
}

void draw_inputBox_4(double side, double center_x, double center_y) {
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
	if (!strlen(input_4) == 0) {
		height = side * 0.035 * 1.8 * 0.8;
		wide = side * 0.035 * 1.8 / 2;
		setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
		y = y - height / 2;
		for (int i = 0; i < strlen(input_4); i++) {
			outtextxy(x1 + single * 0.2 + wide * i, y, input_4[i]);
		}
	}
}

void getScanner_4(int site)
{
	if (site == 1)
	{
		getScanner_5_right(right1_4);
	}
	else if (site == 2)
	{
		getScanner_5_right(right2_4);
	}
	else if (site == 3)
	{
		getScanner_5_right(right3_4);
	}
	else if (site == 4)
	{
		getScanner_5_right(right4_4);
	}
	else if (site == 5)
	{
		getScanner_5_right(right5_4);
	}
	else if (site == 6)
	{
		getScanner_5_right(right6_4);
	}
}

void draw_INDEX_panel_4(double side, double center_x, double center_y) {
	double gap = side * 30 / 685;
	draw_frame_4(side, center_x, center_y);
	draw_topic_4(side, center_x, center_y);
	draw_line1_upper_4(side, center_x, center_y);
	draw_line1_4(side, center_x, center_y);

	draw_line2_4(side, center_x, center_y);

	draw_line3_4(side, center_x, center_y);

	draw_line4_4(side, center_x, center_y);

	draw_line5_4(side, center_x, center_y);
	draw_line6_upper_4(side, center_x, center_y);

	draw_line6_4(side, center_x, center_y);
	draw_inputBox_4(side, center_x, center_y);
}
