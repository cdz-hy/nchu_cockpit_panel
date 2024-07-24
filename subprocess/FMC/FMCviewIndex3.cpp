#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>

char origin_3[5] = {};
char dest_3[5] = {};

void draw_frame_3(double side, double center_x, double center_y) {
	double width = side * 650 / 685;
	double height = side * 540 / 685;
	double x = center_x - width / 2;
	double y = center_y - height / 2;
	setfillcolor(BLACK);
	ege_fillrect(x, y, width, height);
}

void draw_topic_3(double side, double center_x, double center_y) {
	double single = side / 67.0 * 5.7;
	double height = side * 0.035 * 2;
	double wide = side * 0.035 * 2;
	double x = center_x - single * 3;
	double y = center_y - side * 210 / 685;
	setcolor(EGEARGB(255, 32, 220, 224));
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//�趨����
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	ege_drawtext("DEP/ARR  INDEX", center_x, y);
}

void draw_line1_upper_3(double side, double center_x, double center_y) {
	double single = side / 67.0 * 5.7;
	double height = side * 0.035 * 2 / 2;
	double wide = side * 0.035 * 2 / 2;
	double x = center_x - single * 4;
	double y = center_y - side * 210 / 685 + single * 0.7;
	setcolor(EGEARGB(255, 32, 220, 224));
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//�趨����
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	ege_drawtext("A C T   F P L N", center_x, y);
}

void draw_line1_3(double side, double center_x, double center_y) {
	setcolor(WHITE);
	setbkmode(true);
	double single = side / 67.0;
	
	double wide = side * 0.035 * 1.5;
	double height = side * 0.035 * 1.5;
	double y = center_y - single * 14.6;
	double x = center_x - single * 24.4;
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//�趨����
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	ege_drawtext("<DEP", x, y);
	ege_drawtext(origin_3, center_x, y);
	x = x + single * 49;
	ege_drawtext("ARR>", x, y);
}

void draw_line2_3(double side, double center_x, double center_y) {
	setcolor(WHITE);
	double single = side / 67.0;
	double wide = side * 0.035 * 1.5;
	double height = side * 0.035 * 1.5;
	double y = center_y - single * 7.6;
	double x = center_x - single * 24.4;
	
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//�趨����
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	
	ege_drawtext(dest_3, center_x, y);
	x = x + single * 49;
	ege_drawtext("ARR>", x, y);
}

void draw_inputBox_3(double side, double center_x, double center_y) {
	setlinewidth(side * 0.0005);
	double single = side / 67.0;
	setcolor(EGEARGB(255, 32, 220, 224));
	double y = center_y + single * 23.3;
	double x1 = center_x - single * 24.4;
	double x2 = center_x + single * 24.4;
	double height = side * 0.035 * 1.8;
	double wide = side * 0.035 * 1.8;
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//�趨����
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	ege_drawtext("[", x1, y);
	ege_drawtext("]", x2, y);
	
	setcolor(WHITE);
	
}

void getScanner_3(char * origin, char * dest) {
	strcpy_s(origin_3, origin);
	strcpy_s(dest_3, dest);
}

void draw_INDEX_panel_3(double side, double center_x, double center_y) {
	draw_frame_3(side, center_x, center_y);
	draw_topic_3(side, center_x, center_y);
	draw_line1_upper_3(side, center_x, center_y);
	draw_line1_3(side, center_x, center_y);
	draw_line2_3(side, center_x, center_y);
	draw_inputBox_3(side, center_x, center_y);
}
