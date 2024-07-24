#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>

void draw_frame_1(double side, double center_x, double center_y) {
	double width = side * 650 / 685;
	double height = side * 540 / 685;
	double x = center_x - width / 2;
	double y = center_y - height / 2;
	setfillcolor(BLACK);
	ege_fillrect(x, y, width, height);
}

void draw_topic_1(double side, double center_x, double center_y) {
	double height = side * 0.035 * 2;
	double wide = side * 0.035 * 2;
	double x = center_x;
	double y = center_y - side * 210 / 685;
	setcolor(EGEARGB(255, 32, 220, 224));
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	ege_drawtext("INDEX", x, y);
	
	x = center_x + side * 0.3;
	ege_drawtext("1/1", x, y);
}

void draw_line1(double side, double center_x, double center_y, double gap) {
	setcolor(WHITE);
	double single = side / 67.0;
	double y = center_y - single * 14.6;
	double x = center_x - single * 24.4;
	
	//x = center_x - single * 26.1;
	double height = side * 0.035 * 1.5;
	double wide = side * 0.035 * 1.5;
	
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	ege_drawtext("<STATUS", x, y);
	x = center_x + single * 21;
	ege_drawtext("ROUTE MENU>", x, y);
}

void draw_line2(double side, double center_x, double center_y, double gap) {
	setcolor(WHITE);
	double single = side / 67.0;
	double y = center_y - single * 7.6;
	double x = center_x + single * 23;
	double height = side * 0.035 * 1.5;
	double wide = side * 0.035 * 1.5;
	
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	
	ege_drawtext("DATABASE>", x, y);
}

void draw_line3(double side, double center_x, double center_y, double gap) {
	setcolor(WHITE);
	double single = side / 67.0;
	double y = center_y - single * 0.7;
	double x = center_x - single * 24.4;
	double height = side * 0.035 * 1.5;
	double wide = side * 0.035 * 1.5;
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	
	//ege_drawtext("<STATUS", x, y);
	x = center_x + single * 21;
	//ege_drawtext("ROUTE MENU>", x, y);
}

void draw_line4(double side, double center_x, double center_y, double gap) {
	setcolor(WHITE);
	double single = side / 67.0;
	double y = center_y + single * 6.3;
	double x = center_x - single * 24.4;
	double height = side * 0.035 * 1.5;
	double wide = side * 0.035 * 1.5;
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	
	//ege_drawtext("<STATUS", x, y);
	x = center_x + single * 21;
	//ege_drawtext("ROUTE MENU>", x, y);
}

void draw_line5(double side, double center_x, double center_y, double gap) {
	setcolor(WHITE);
	double single = side / 67.0;
	double y = center_y + single * 13.2;
	double x = center_x + single * 22.3;
	double height = side * 0.035 * 1.5;
	double wide = side * 0.035 * 1.5;
	
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	ege_drawtext("ARR DATA>", x, y);
}

void draw_line6(double side, double center_x, double center_y, double gap) {
	setcolor(WHITE);
	double single = side / 67.0;
	double y = center_y + single * 20.2;
	double x = center_x + single * 22.3;
	double height = side * 0.035 * 1.5;
	double wide = side * 0.035 * 1.5;
	
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	
	ege_drawtext("ARR DATA>", x, y);
	
}

void draw_inputBox(double side, double center_x, double center_y, double gap) {
	double single = side / 67.0;
	setcolor(EGEARGB(255, 32, 220, 224));
	double y = center_y + single * 23.3;
	double x1 = center_x - single * 24.4;
	double x2 = center_x + single * 24.4;
	double height = side * 0.035 * 1.5;
	double wide = side * 0.035 * 1.5;
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	ege_drawtext("[", x1, y);
	ege_drawtext("]", x2, y);
}

void draw_INDEX_panel_1(double side, double center_x, double center_y) {
	double gap = side * 30 / 685;
	draw_frame_1(side, center_x, center_y);
	draw_topic_1(side, center_x, center_y);
	draw_line1(side, center_x, center_y, gap);
	draw_line2(side, center_x, center_y, gap);
	//draw_line3(side, center_x, center_y, gap);
	//draw_line4(side, center_x, center_y, gap);
	draw_line5(side, center_x, center_y, gap);
	//draw_line6(side, center_x, center_y, gap);
	draw_inputBox(side, center_x, center_y, gap);
}
