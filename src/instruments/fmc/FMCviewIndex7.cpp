#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>

char input_7[64] = {};//{"ZBAA"};

char left1_7[7] = {};//{ "CDY11D" };
char left2_7[7] = {};//{ "CDY11D" };
char left3_7[7] = {};//{ "CDY11D" };
char left4_7[7] = {};//{ "CDY11D" };
char left5_7[7] = {};//{ "CDY11D" };
char left6_7[7] = {};//{ "CDY11D" };

char right1_7[7] = {};//{ "RW01" };
char right2_7[7] = {};//{ "RW18L" };
char right3_7[7] = {};//{ "RW18R" };
char right4_7[7] = {};//{ "RW19" };
char right5_7[7] = {};//{ "RW36R" };
char right6_7[7] = {};//{ "RW36L" };
boolean button_clicked_7 = true;

struct rountpoint
{
	char rountpoints[10][7];
};

rountpoint FMC_rountpoints;

void draw_frame_7(double side, double center_x, double center_y) {
	double width = side * 650 / 685;
	double height = side * 540 / 685;
	double x = center_x - width / 2;
	double y = center_y - height / 2;
	setfillcolor(BLACK);
	ege_fillrect(x, y, width, height);
}

void draw_topic_7(double side, double center_x, double center_y) {
	double single = side / 67.0 * 5.7;
	double height = side * 0.035 * 2;
	double wide = side * 0.035 * 2;
	double x = center_x - single * 3;
	double y = center_y - side * 210 / 685;
	setcolor(EGEARGB(255, 32, 220, 224));
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	ege_drawtext("ACT FPLN", x, y);
	
	x = center_x + side * 0.3;
	ege_drawtext("2/2", x, y);
}

void draw_line1_upper_7(double side, double center_x, double center_y) {
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
	ege_drawtext("V I A", x, y);
	
	x += single * 8.2;
	ege_drawtext("T O", x, y);
}

void draw_line1_7(double side, double center_x, double center_y) {
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
	
	ege_drawtext(left1_7, x, y);
	if (strlen(right1_7) == 4) {
		x = center_x + single * 25;
		ege_drawtext(right1_7, x, y);
	}
	else if (strlen(right1_7) == 5) {
		x = center_x + single * 25 - wide / 3;
		ege_drawtext(right1_7, x, y);
	}
	else if (strlen(right1_7) == 6) {
		x = center_x + single * 25 - wide / 2;
		ege_drawtext(right1_7, x, y);
	}
}

void draw_line2_7(double side, double center_x, double center_y) {
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
	
	ege_drawtext(left2_7, x, y);
	if (strlen(right2_7) == 4) {
		x = center_x + single * 25;
		ege_drawtext(right2_7, x, y);
	}
	else if (strlen(right2_7) == 5) {
		x = center_x + single * 25 - wide / 3;
		ege_drawtext(right2_7, x, y);
	}
	else if (strlen(right2_7) == 6) {
		x = center_x + single * 25 - wide / 2;
		ege_drawtext(right2_7, x, y);
	}
}

void draw_line3_7(double side, double center_x, double center_y) {
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
	
	ege_drawtext(left3_7, x, y);
	if (strlen(right3_7) == 4) {
		x = center_x + single * 25;
		ege_drawtext(right3_7, x, y);
	}
	else if (strlen(right3_7) == 5) {
		x = center_x + single * 25 - wide / 3;
		ege_drawtext(right3_7, x, y);
	}
	else if (strlen(right3_7) == 6) {
		x = center_x + single * 25 - wide / 2;
		ege_drawtext(right3_7, x, y);
	}
}

void draw_line4_7(double side, double center_x, double center_y) {
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
	
	ege_drawtext(left4_7, x, y);
	if (strlen(right4_7) == 4) {
		x = center_x + single * 25;
		ege_drawtext(right4_7, x, y);
	}
	else if (strlen(right4_7) == 5) {
		x = center_x + single * 25 - wide / 3;
		ege_drawtext(right4_7, x, y);
	}
	else if (strlen(right4_7) == 6) {
		x = center_x + single * 25 - wide / 2;
		ege_drawtext(right4_7, x, y);
	}
}

void draw_line5_7(double side, double center_x, double center_y) {
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
	ege_drawtext(left5_7, x, y);
	if (strlen(right5_7) == 4) {
		x = center_x + single * 25;
		ege_drawtext(right5_7, x, y);
	}
	else if (strlen(right5_7) == 5) {
		x = center_x + single * 25 - wide / 3;
		ege_drawtext(right5_7, x, y);
	}
	else if (strlen(right5_7) == 6) {
		x = center_x + single * 25 - wide / 2;
		ege_drawtext(right5_7, x, y);
	}
}

void draw_line6_upper_7(double side, double center_x, double center_y) {
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

void draw_line6_7(double side, double center_x, double center_y) {
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
	if (strlen(left1_7) != 0) {
		ege_drawtext("<CANCEL MOD", x, y);
	}
	x = center_x + single * 25;
	ege_drawtext("VNAV>", x, y);
}

void draw_input_7Box_7(double side, double center_x, double center_y) {
	setlinewidth(side * 0.0005);
	double single = side / 67.0;
	setcolor(EGEARGB(255, 32, 220, 224));
	double y = center_y + single * 23.3;
	double x1 = center_x - single * 24.4;
	double x2 = center_x + single * 24.4;
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
	if (!button_clicked_7) {
		setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
		ege_drawtext("NAV  DATA  OUT  OF  DATE", center_x, y);
	}
	else {
		if (!strlen(input_7) == 0) {
			height = side * 0.035 * 1.8 * 0.8;
			wide = side * 0.035 * 1.8 / 2;
			setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
			for (int i = 0; i < strlen(input_7); i++) {
				outtextxy(x1 + single * 2 + wide * i, y, input_7[i]);
			}
		}
	}
}

void FMC_Scanner_panel_7(char* information, int FMC_keyword) {
	
	strcpy_s(input_7, 64, information);
	if (FMC_keyword == 1)
	{
		strcpy_s(left1_7, input_7);
		strcpy_s(FMC_rountpoints.rountpoints[0], left1_7);
		return;
	}
	else if (FMC_keyword == 2)
	{
		strcpy_s(right1_7, input_7);
		strcpy_s(FMC_rountpoints.rountpoints[1], right1_7);
		return;
	}
	else if (FMC_keyword == 3)
	{
		strcpy_s(left2_7, input_7);
		strcpy_s(FMC_rountpoints.rountpoints[2], left2_7);
		return;
	}
	else if (FMC_keyword == 4)
	{
		strcpy_s(right2_7, input_7);
		strcpy_s(FMC_rountpoints.rountpoints[3], right2_7);
		return;
	}
	else if (FMC_keyword == 5)
	{
		strcpy_s(left3_7, input_7);
		strcpy_s(FMC_rountpoints.rountpoints[4], left3_7);
		return;
	}
	else if (FMC_keyword == 6)
	{
		strcpy_s(right3_7, input_7);
		strcpy_s(FMC_rountpoints.rountpoints[5], right3_7);
		return;
	}
	else if (FMC_keyword == 7)
	{
		strcpy_s(left4_7, input_7);
		strcpy_s(FMC_rountpoints.rountpoints[6], left4_7);
		return;
	}
	else if (FMC_keyword == 8)
	{
		strcpy_s(right4_7, input_7);
		strcpy_s(FMC_rountpoints.rountpoints[7], right4_7);
		return;
	}
	else if (FMC_keyword == 9)
	{
		strcpy_s(left5_7, input_7);
		strcpy_s(FMC_rountpoints.rountpoints[8], left5_7);
		return;
	}
	else if (FMC_keyword == 10)
	{
		strcpy_s(right5_7, input_7);
		strcpy_s(FMC_rountpoints.rountpoints[9], right5_7);
		return;
	}
}

rountpoint FMC_getpointsinformation()
{
	return FMC_rountpoints;
}

void draw_FPLN_panel_7(double side, double center_x, double center_y) {
	double gap = side * 30 / 685;
	draw_frame_7(side, center_x, center_y);
	draw_topic_7(side, center_x, center_y);
	draw_line1_upper_7(side, center_x, center_y);
	draw_line1_7(side, center_x, center_y);
	draw_line2_7(side, center_x, center_y);
	draw_line3_7(side, center_x, center_y);
	draw_line4_7(side, center_x, center_y);
	draw_line5_7(side, center_x, center_y);
	draw_line6_upper_7(side, center_x, center_y);
	draw_line6_7(side, center_x, center_y);
	draw_input_7Box_7(side, center_x, center_y);
}
