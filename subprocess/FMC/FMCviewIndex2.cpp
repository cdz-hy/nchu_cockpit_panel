#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "FMCviewIndex3.h"

char origin[5] = {};// { 'Z', 'B', 'A', 'A' };
char dest[5] = {};//{'Z','S','S','S'};
char co_route[9] = {};//{"ZBAA"};
char fly_no[7] = {};//{"5020"};
char via[7] = {};//{"LADI8H"};
char to[6] = {};//{"LADIX"};
char input[64] = {};//{"ZBAA"};
boolean button_clicked = true;

void draw_frame_2(double side, double center_x, double center_y) {
	double width = side * 650 / 685;
	double height = side * 540 / 685;
	double x = center_x - width / 2;
	double y = center_y - height / 2;
	setfillcolor(BLACK);
	ege_fillrect(x, y, width, height);
}

void draw_topic_2(double side, double center_x, double center_y) {
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
	ege_drawtext("1/1", x, y);
}

void draw_line1_upper(double side, double center_x, double center_y) {
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
	ege_drawtext("O R I G I N", x, y);
	
	x += single * 8.2;
	ege_drawtext("D E S T", x, y);
}

void draw_line1(double side, double center_x, double center_y, char str1[], char str2[]) {
	setcolor(WHITE);
	setlinewidth(side * 0.001);
	setbkmode(true);
	double single = side / 67.0;
	
	double wide = side * 0.035 * 1.5 / 2;
	double height = side * 0.035 * 1.5 * 0.8;
	double y = center_y - single * 14.6;
	double x = center_x - single * 24.4 - 2 * wide;
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	if (strlen(origin) == 0) {
		for (int i = 0; i < 4; i++) {
			ege_rectangle(x + wide * i, y, wide, wide);
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			outtextxy(x + wide * i, y, origin[i]);
		}
	}
	x = center_x + single * 21 + single * 1.8;
	if (strlen(dest) == 0) {
		for (int i = 0; i < 4; i++) {
			ege_rectangle(x - single * 0.7 + wide * i, y, wide, wide);
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			outtextxy(x + wide * i, y, dest[i]);
		}
	}
	
}

void draw_line2_upper(double side, double center_x, double center_y) {
	double single = side / 67.0 * 5.7;
	double height = side * 0.035 * 2 / 2;
	double wide = side * 0.035 * 2 / 2;
	double x = center_x - single * 3.8;
	double y = center_y - single * 1.7;
	setcolor(EGEARGB(255, 32, 220, 224));
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	ege_drawtext("C O   R O U T E", x, y);
}

void draw_line2(double side, double center_x, double center_y) {
	setcolor(WHITE);
	double single = side / 67.0;
	double wide = side * 0.035 * 1.5 / 2;
	double height = side * 0.035 * 1.5 * 0.8;
	double y = center_y - single * 7.6 - height / 2;
	double x = center_x - single * 24.4 - 2 * wide;
	
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	
	if (strlen(co_route) == 0) {
		y = center_y - single * 7.6;
		x = x + wide * 4;
		ege_drawtext("--------------", x, y);
	}
	else {
		/*y = center_y - single * 7.6;
		x = x + wide * 4;
		ege_drawtext("--------------", x, y);*/
		y = center_y - single * 7.6 + height / 2;
		x = x + wide * 2;
		for (int i = 0; i < 4; i++) {
			outtextxy(x + wide * i, y, co_route[i]);
		}
	}
}

void draw_line3_upper(double side, double center_x, double center_y) {
	double single = side / 67.0 * 5.7;
	double height = side * 0.035 * 2 / 2;
	double wide = side * 0.035 * 2 / 2;
	double x = center_x + single * 3.8;
	double y = center_y - single * 0.5;
	setcolor(EGEARGB(255, 32, 220, 224));
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	ege_drawtext("F L Y   N O", x, y);
}

void draw_line3(double side, double center_x, double center_y) {
	setcolor(WHITE);
	double single = side / 67.0;
	double y = center_y - single * 0.7;
	double x = center_x - single * 24.4;
	double height = side * 0.035 * 1.5;
	double wide = side * 0.035 * 1.5;
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	
	
	if (strlen(fly_no) == 0) {
		y = center_y - single * 0.7;
		x = center_x + single * 21;
		ege_drawtext("--------------", x, y);
	}
	else {
		for (int i = 0; i < 5; i++) {
			height = side * 0.035 * 1.5 * 0.8;
			wide = side * 0.035 * 1.5 / 2;
			y = center_y - single * 0.7;
			x = center_x + single * 21;
			
			setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
			outtextxy(x + wide * i, y, fly_no[i]);
			//ege_drawtext("--------------", x, y);
		}
	}
}

void draw_line4_upper(double side, double center_x, double center_y) {
	double single = side / 67.0 * 5.7;
	double height = side * 0.035 * 2 / 2;
	double wide = side * 0.035 * 2 / 2;
	double x = center_x + single * 3.8;
	double y = center_y - single * 0.5;
	setcolor(EGEARGB(255, 32, 220, 224));
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	//ege_drawtext("F L Y   N O", x, y);
}

void draw_line4(double side, double center_x, double center_y) {
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
	
	//ege_drawtext("<STATUS", x, y);
	x = center_x + single * 21;
	//ege_drawtext("ROUTE MENU>", x, y);
}

void draw_line5_upper(double side, double center_x, double center_y) {
	double single = side / 67.0 * 5.7;
	double height = side * 0.035 * 2 / 2;
	double wide = side * 0.035 * 2 / 2;
	double x = center_x - single * 4.3;
	double y = center_y + single * 1.9;
	setcolor(EGEARGB(255, 32, 220, 224));
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	ege_drawtext("V I A", x, y);
	
	x = center_x + single * 4.3;
	ege_drawtext("T O", x, y);
}

void draw_line5(double side, double center_x, double center_y) {
	setcolor(WHITE);
	double single = side / 67.0;
	double y = center_y + single * 13.2;
	double x = center_x - single * 22.3;
	double height = side * 0.035 * 1.5;
	double wide = side * 0.035 * 1.5;
	
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	//ege_drawtext("ARR DATA>", x, y);
	
	if (strlen(via) == 0) {
		for (int i = 0; i < 4; i++) {
			ege_drawtext("--------------", x, y);
		}
	}
	else {
		height = side * 0.035 * 1.5 * 0.8;
		wide = side * 0.035 * 1.5 / 2;
		y = center_y + single * 13.2 - height / 2;
		x = center_x - single * 21 - wide * 4;
		setcolor(EGEARGB(0xff, 0xFD, 0x00, 0xFD));
		setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
		
		for (int i = 0; i < strlen(via); i++) {
			outtextxy(x + wide * i, y, via[i]);
		}
		setcolor(WHITE);
	}
	
	x = center_x + single * 21 + single * 1.8;
	if (strlen(to) == 0) {
		for (int i = 0; i < 4; i++) {
			ege_drawtext("--------------", x, y);
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			height = side * 0.035 * 1.5 * 0.8;
			wide = side * 0.035 * 1.5 / 2;
			y = center_y + single * 13.2 - height / 2;
			x = center_x + single * 21;
			setcolor(EGEARGB(0xff, 0xFD, 0x00, 0xFD));
			setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
			
			for (int i = 0; i < strlen(to); i++) {
				outtextxy(x + wide * i, y, to[i]);
			}
			setcolor(WHITE);
		}
	}
}

void draw_line6_upper(double side, double center_x, double center_y) {
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
	ege_drawtext("----------------------------------------------------------------", x, y);
}

void draw_line6(double side, double center_x, double center_y) {
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
	ege_drawtext("<ROUTE MENU", x, y);
	x = center_x + single * 24.8;
	ege_drawtext("VNAV>", x, y);
	
}

void draw_inputBox(double side, double center_x, double center_y) {
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
	if (!button_clicked) {
		setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
		ege_drawtext("NAV  DATA  OUT  OF  DATE", center_x, y);
	}
	else {
		if (!strlen(input) == 0) {
			height = side * 0.035 * 1.8 * 0.8;
			wide = side * 0.035 * 1.8 / 2;
			setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
			for (int i = 0; i < strlen(input); i++) {
				outtextxy(x1 + single * 2 + wide * i, y, input[i]);
			}
		}
	}
}

void FMC_Scanner_panel_2(char* information, int FMC_keyword) {
	
	strcpy_s(input, 64, information);
	if (FMC_keyword == 1)
	{
		if (strlen(input) <= 5) {
			strcpy_s(origin, input);
			strcpy_s(input, "");
		}
		return;
	}
	else if (FMC_keyword == 2)
	{
		if (strlen(input) <= 5) {
			strcpy_s(dest, input);
			strcpy_s(input, "");
		}
		return;
	}
	else if (FMC_keyword == 5)
	{
		if (strlen(input) <= 7) {
			strcpy_s(fly_no, input);
			strcpy_s(input, "");
		}
		return;
	}
}

void FMC_getinformation(char* is_via)
{
	strcpy_s(via, is_via);
	strcpy_s(to, "LADIX");
}

boolean is_empty_2()
{
	if (strlen(via) != 0 && strlen(to) != 0)
		return true;
	else
		return false;
}

char* getorigin() {
	return origin;
}

char* getdest() {
	return dest;
}


void draw_INDEX_panel_2(double side, double center_x, double center_y) {
	double gap = side * 30 / 685;
	draw_frame_2(side, center_x, center_y);
	draw_topic_2(side, center_x, center_y);
	draw_line1_upper(side, center_x, center_y);
	draw_line1(side, center_x, center_y, origin, dest);
	draw_line2_upper(side, center_x, center_y);
	draw_line2(side, center_x, center_y);
	draw_line3_upper(side, center_x, center_y);
	draw_line3(side, center_x, center_y);
	draw_line4_upper(side, center_x, center_y);
	draw_line4(side, center_x, center_y);
	draw_line5_upper(side, center_x, center_y);
	draw_line5(side, center_x, center_y);
	draw_line6_upper(side, center_x, center_y);
	draw_line6(side, center_x, center_y);
	draw_inputBox(side, center_x, center_y);
	getScanner_3(origin, dest);
}
