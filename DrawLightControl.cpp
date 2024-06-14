
#include<graphics.h>
#include <stdio.h>
#include <math.h>

extern double OUTBDangle;
extern double INBDangle;
extern double LOWERangle;
extern double LOWERangle_1;
extern double INBDangle_1;
extern double UPPERangle;
extern double Brightangle;
extern double changecolor;
extern int MainPanelLight;

int leftPanel_mouse_x = 0, leftPanel_mouse_y = 0;
int leftPanel_speed_is_down = 0;
int leftPanel_mouse_y_cur = 0, leftPanel_mouse_x_cur = 0;

void draw_Light_contral(double leftPanel_x, double leftPanel_y, double side) {
	double Ulength = side / 130;
	double Linewidth = Ulength;
	double lefttop_R1 = Ulength * 12;
	double Lowknob_R1 = 9 * Ulength;
	double Lowknob_R2 = 7 * Ulength;
	double Lowknob_R3 = 6 * Ulength;
	int x, y;
	mousepos(&x, &y);
	
	
	
	
	ege_enable_aa(false);
	
	
	setcolor(EGEARGB(0XFF, 0X1B, 0X1E, 0X21));
	int Framenum = 61;
	ege_point FramePloypoints[61] = {
		{leftPanel_x - Ulength * 57,leftPanel_y - Ulength * 41},
		{leftPanel_x - Ulength * 57,leftPanel_y - Ulength * 41.5},
		{leftPanel_x - Ulength * 56.5,leftPanel_y - Ulength * 42},
		{leftPanel_x - Ulength * 56,leftPanel_y - Ulength * 42},
		
		{leftPanel_x + Ulength * 56,leftPanel_y - Ulength * 42},
		{leftPanel_x + Ulength * 56,leftPanel_y - Ulength * 42},
		{leftPanel_x + Ulength * 56,leftPanel_y - Ulength * 42},
		
		{leftPanel_x + Ulength * 56.5,leftPanel_y - Ulength * 42},
		{leftPanel_x + Ulength * 57,leftPanel_y - Ulength * 41.5},
		{leftPanel_x + Ulength * 57,leftPanel_y - Ulength * 41},
		
		{leftPanel_x + Ulength * 57,leftPanel_y - Ulength * 31},
		{leftPanel_x + Ulength * 57,leftPanel_y - Ulength * 31},
		{leftPanel_x + Ulength * 57,leftPanel_y - Ulength * 31},
		
		{leftPanel_x + Ulength * 57,leftPanel_y - Ulength * 27},
		{leftPanel_x + Ulength * 60.5,leftPanel_y - Ulength * 25},
		{leftPanel_x + Ulength * 64,leftPanel_y - Ulength * 25},
		
		{leftPanel_x + Ulength * 64.5,leftPanel_y - Ulength * 25},
		{leftPanel_x + Ulength * 65,leftPanel_y - Ulength * 24.5},
		{leftPanel_x + Ulength * 65,leftPanel_y - Ulength * 24},
		
		{leftPanel_x + Ulength * 65,leftPanel_y + Ulength * 24},
		{leftPanel_x + Ulength * 65,leftPanel_y + Ulength * 24},
		{leftPanel_x + Ulength * 65,leftPanel_y + Ulength * 24},
		
		{leftPanel_x + Ulength * 65,leftPanel_y + Ulength * 24.5},
		{leftPanel_x + Ulength * 64.5,leftPanel_y + Ulength * 25},
		{leftPanel_x + Ulength * 64,leftPanel_y + Ulength * 25},
		
		{leftPanel_x + Ulength * 60.5,leftPanel_y + Ulength * 25},
		{leftPanel_x + Ulength * 57,leftPanel_y + Ulength * 27},
		{leftPanel_x + Ulength * 57,leftPanel_y + Ulength * 31},
		
		{leftPanel_x + Ulength * 57,leftPanel_y + Ulength * 41},
		{leftPanel_x + Ulength * 57,leftPanel_y + Ulength * 41},
		{leftPanel_x + Ulength * 57,leftPanel_y + Ulength * 41},
		
		{leftPanel_x + Ulength * 57,leftPanel_y + Ulength * 41.5},
		{leftPanel_x + Ulength * 56.5,leftPanel_y + Ulength * 42},
		{leftPanel_x + Ulength * 56,leftPanel_y + Ulength * 42},
		
		{leftPanel_x - Ulength * 56,leftPanel_y + Ulength * 42},
		{leftPanel_x - Ulength * 56,leftPanel_y + Ulength * 42},
		{leftPanel_x - Ulength * 56,leftPanel_y + Ulength * 42},
		
		{leftPanel_x - Ulength * 56.5,leftPanel_y + Ulength * 42},
		{leftPanel_x - Ulength * 57,leftPanel_y + Ulength * 41.5},
		{leftPanel_x - Ulength * 57,leftPanel_y + Ulength * 41},
		
		{leftPanel_x - Ulength * 57,leftPanel_y + Ulength * 31},
		{leftPanel_x - Ulength * 57,leftPanel_y + Ulength * 31},
		{leftPanel_x - Ulength * 57,leftPanel_y + Ulength * 31},
		
		{leftPanel_x - Ulength * 57,leftPanel_y + Ulength * 27},
		{leftPanel_x - Ulength * 60.5,leftPanel_y + Ulength * 25},
		{leftPanel_x - Ulength * 64,leftPanel_y + Ulength * 25},
		
		{leftPanel_x - Ulength * 64.5,leftPanel_y + Ulength * 25},
		{leftPanel_x - Ulength * 65,leftPanel_y + Ulength * 24.5},
		{leftPanel_x - Ulength * 65,leftPanel_y + Ulength * 24},
		
		{leftPanel_x - Ulength * 65,leftPanel_y - Ulength * 24},
		{leftPanel_x - Ulength * 65,leftPanel_y - Ulength * 24},
		{leftPanel_x - Ulength * 65,leftPanel_y - Ulength * 24},
		
		{leftPanel_x - Ulength * 65,leftPanel_y - Ulength * 24.5},
		{leftPanel_x - Ulength * 64.5,leftPanel_y - Ulength * 25},
		{leftPanel_x - Ulength * 64,leftPanel_y - Ulength * 25},
		
		{leftPanel_x - Ulength * 60.5,leftPanel_y - Ulength * 25},
		{leftPanel_x - Ulength * 57,leftPanel_y - Ulength * 27},
		{leftPanel_x - Ulength * 57,leftPanel_y - Ulength * 31},
		
		{leftPanel_x - Ulength * 57,leftPanel_y - Ulength * 41},
		{leftPanel_x - Ulength * 57,leftPanel_y - Ulength * 41},
		{leftPanel_x - Ulength * 57,leftPanel_y - Ulength * 41},
		
		
	};
	ege_bezier(Framenum, FramePloypoints);
	setfillcolor(EGEARGB(0XFF, 0X1B, 0X1E, 0X21));
	floodfill(leftPanel_x, leftPanel_y, EGEARGB(0XFF, 0X1B, 0X1E, 0X21));
	
	ege_enable_aa(true);
	setcolor(EGEARGB(0XFF, 0X10, 0X10, 0X10));
	setlinewidth(Linewidth / 7 * 4);
	int Framenum_1 = 61;
	ege_point FramePloypoints_1[61] = {
		{leftPanel_x - Ulength * 57,leftPanel_y - Ulength * 41},
		{leftPanel_x - Ulength * 57,leftPanel_y - Ulength * 41.5},
		{leftPanel_x - Ulength * 56.5,leftPanel_y - Ulength * 42},
		{leftPanel_x - Ulength * 56,leftPanel_y - Ulength * 42},
		
		{leftPanel_x + Ulength * 56,leftPanel_y - Ulength * 42},
		{leftPanel_x + Ulength * 56,leftPanel_y - Ulength * 42},
		{leftPanel_x + Ulength * 56,leftPanel_y - Ulength * 42},
		
		{leftPanel_x + Ulength * 56.5,leftPanel_y - Ulength * 42},
		{leftPanel_x + Ulength * 57,leftPanel_y - Ulength * 41.5},
		{leftPanel_x + Ulength * 57,leftPanel_y - Ulength * 41},
		
		{leftPanel_x + Ulength * 57,leftPanel_y - Ulength * 31},
		{leftPanel_x + Ulength * 57,leftPanel_y - Ulength * 31},
		{leftPanel_x + Ulength * 57,leftPanel_y - Ulength * 31},
		
		{leftPanel_x + Ulength * 57,leftPanel_y - Ulength * 27},
		{leftPanel_x + Ulength * 60.5,leftPanel_y - Ulength * 25},
		{leftPanel_x + Ulength * 64,leftPanel_y - Ulength * 25},
		
		{leftPanel_x + Ulength * 64.5,leftPanel_y - Ulength * 25},
		{leftPanel_x + Ulength * 65,leftPanel_y - Ulength * 24.5},
		{leftPanel_x + Ulength * 65,leftPanel_y - Ulength * 24},
		
		{leftPanel_x + Ulength * 65,leftPanel_y + Ulength * 24},
		{leftPanel_x + Ulength * 65,leftPanel_y + Ulength * 24},
		{leftPanel_x + Ulength * 65,leftPanel_y + Ulength * 24},
		
		{leftPanel_x + Ulength * 65,leftPanel_y + Ulength * 24.5},
		{leftPanel_x + Ulength * 64.5,leftPanel_y + Ulength * 25},
		{leftPanel_x + Ulength * 64,leftPanel_y + Ulength * 25},
		
		{leftPanel_x + Ulength * 60.5,leftPanel_y + Ulength * 25},
		{leftPanel_x + Ulength * 57,leftPanel_y + Ulength * 27},
		{leftPanel_x + Ulength * 57,leftPanel_y + Ulength * 31},
		
		{leftPanel_x + Ulength * 57,leftPanel_y + Ulength * 41},
		{leftPanel_x + Ulength * 57,leftPanel_y + Ulength * 41},
		{leftPanel_x + Ulength * 57,leftPanel_y + Ulength * 41},
		
		{leftPanel_x + Ulength * 57,leftPanel_y + Ulength * 41.5},
		{leftPanel_x + Ulength * 56.5,leftPanel_y + Ulength * 42},
		{leftPanel_x + Ulength * 56,leftPanel_y + Ulength * 42},
		
		{leftPanel_x - Ulength * 56,leftPanel_y + Ulength * 42},
		{leftPanel_x - Ulength * 56,leftPanel_y + Ulength * 42},
		{leftPanel_x - Ulength * 56,leftPanel_y + Ulength * 42},
		
		{leftPanel_x - Ulength * 56.5,leftPanel_y + Ulength * 42},
		{leftPanel_x - Ulength * 57,leftPanel_y + Ulength * 41.5},
		{leftPanel_x - Ulength * 57,leftPanel_y + Ulength * 41},
		
		{leftPanel_x - Ulength * 57,leftPanel_y + Ulength * 31},
		{leftPanel_x - Ulength * 57,leftPanel_y + Ulength * 31},
		{leftPanel_x - Ulength * 57,leftPanel_y + Ulength * 31},
		
		{leftPanel_x - Ulength * 57,leftPanel_y + Ulength * 27},
		{leftPanel_x - Ulength * 60.5,leftPanel_y + Ulength * 25},
		{leftPanel_x - Ulength * 64,leftPanel_y + Ulength * 25},
		
		{leftPanel_x - Ulength * 64.5,leftPanel_y + Ulength * 25},
		{leftPanel_x - Ulength * 65,leftPanel_y + Ulength * 24.5},
		{leftPanel_x - Ulength * 65,leftPanel_y + Ulength * 24},
		
		{leftPanel_x - Ulength * 65,leftPanel_y - Ulength * 24},
		{leftPanel_x - Ulength * 65,leftPanel_y - Ulength * 24},
		{leftPanel_x - Ulength * 65,leftPanel_y - Ulength * 24},
		
		{leftPanel_x - Ulength * 65,leftPanel_y - Ulength * 24.5},
		{leftPanel_x - Ulength * 64.5,leftPanel_y - Ulength * 25},
		{leftPanel_x - Ulength * 64,leftPanel_y - Ulength * 25},
		
		{leftPanel_x - Ulength * 60.5,leftPanel_y - Ulength * 25},
		{leftPanel_x - Ulength * 57,leftPanel_y - Ulength * 27},
		{leftPanel_x - Ulength * 57,leftPanel_y - Ulength * 31},
		
		{leftPanel_x - Ulength * 57,leftPanel_y - Ulength * 41},
		{leftPanel_x - Ulength * 57,leftPanel_y - Ulength * 41},
		{leftPanel_x - Ulength * 57,leftPanel_y - Ulength * 41},
		
		
	};
	ege_bezier(Framenum_1, FramePloypoints_1);
	//左上底座
	setfillcolor(EGEARGB(0XFF, 0X3A, 0X3A, 0X38));
	int MainpanelLightcontralNums = 18;
	ege_point MainpanelLightcontralPloy[18] = {
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos(0 * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin(0 * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos(20 * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin(20 * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos(40 * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin(40 * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos(60 * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin(60 * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos(80 * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin(80 * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos(100 * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin(100 * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos(120 * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin(120 * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos(140 * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin(140 * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos(160 * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin(160 * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos(180 * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin(180 * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos(200 * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin(200 * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos(220 * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin(220 * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos(240 * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin(240 * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos(260 * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin(260 * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos(280 * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin(280 * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos(300 * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin(300 * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos(320 * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin(320 * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos(340 * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin(340 * PI / 180)},
	};
	ege_fillpoly(MainpanelLightcontralNums, MainpanelLightcontralPloy);
	
	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_arc(leftPanel_x - Ulength * 37 - lefttop_R1, leftPanel_y - Ulength * 21 - lefttop_R1, Ulength * 28, Ulength * 28, 180, 60);
	ege_arc(leftPanel_x - Ulength * 37 - lefttop_R1, leftPanel_y - Ulength * 21 - lefttop_R1, Ulength * 28, Ulength * 28, 305, 55);
	LOGFONTW font;
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font);
	font.lfEscapement = 300;
	font.lfWeight = 500;
	setfont(&font);
	setbkmode(1);
	
	
	ege_drawtext("B", leftPanel_x - Ulength * 28 - lefttop_R1, leftPanel_y - Ulength * 18.8 - lefttop_R1);
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_drawtext("B", leftPanel_x - Ulength * 28 - lefttop_R1, leftPanel_y - Ulength * 18.8 - lefttop_R1);
	
	LOGFONTW font1;
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font1);
	font1.lfEscapement = 200;
	font1.lfWeight = 500;
	setfont(&font1);
	setbkmode(1);
	
	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_drawtext("R", leftPanel_x - Ulength * 25 - lefttop_R1, leftPanel_y - Ulength * 19.8 - lefttop_R1);
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_drawtext("R", leftPanel_x - Ulength * 25 - lefttop_R1, leftPanel_y - Ulength * 19.8 - lefttop_R1);
	
	
	LOGFONTW font2;
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font2);
	font2.lfEscapement = 100;
	font2.lfWeight = 500;
	setfont(&font2);
	setbkmode(1);
	
	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_drawtext("I", leftPanel_x - Ulength * 23 - lefttop_R1, leftPanel_y - Ulength * 20 - lefttop_R1);
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_drawtext("I", leftPanel_x - Ulength * 23 - lefttop_R1, leftPanel_y - Ulength * 20 - lefttop_R1);
	
	LOGFONTW font3;
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font3);
	font3.lfEscapement = 0;
	font3.lfWeight = 500;
	setfont(&font3);
	setbkmode(1);
	
	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_drawtext("G", leftPanel_x - Ulength * 21 - lefttop_R1, leftPanel_y - Ulength * 20.5 - lefttop_R1);
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_drawtext("G", leftPanel_x - Ulength * 21 - lefttop_R1, leftPanel_y - Ulength * 20.5 - lefttop_R1);
	
	LOGFONTW font4;
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font4);
	font4.lfEscapement = -200;
	font4.lfWeight = 500;
	setfont(&font4);
	setbkmode(1);
	
	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_drawtext("H", leftPanel_x - Ulength * 18 - lefttop_R1, leftPanel_y - Ulength * 19.2 - lefttop_R1);
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_drawtext("H", leftPanel_x - Ulength * 18 - lefttop_R1, leftPanel_y - Ulength * 19.2 - lefttop_R1);
	LOGFONTW font5;
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font5);
	font5.lfEscapement = -400;
	font5.lfWeight = 500;
	setfont(&font5);
	setbkmode(1);
	
	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_drawtext("T", leftPanel_x - Ulength * 16.1 - lefttop_R1, leftPanel_y - Ulength * 17.9 - lefttop_R1);
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_drawtext("T", leftPanel_x - Ulength * 16.1 - lefttop_R1, leftPanel_y - Ulength * 17.9 - lefttop_R1);
	
	
	
	
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_arc(leftPanel_x - Ulength * 37 - lefttop_R1, leftPanel_y - Ulength * 21 - lefttop_R1, Ulength * 28, Ulength * 28, 180, 60);
	ege_arc(leftPanel_x - Ulength * 37 - lefttop_R1, leftPanel_y - Ulength * 21 - lefttop_R1, Ulength * 28, Ulength * 28, 305, 55);
	
	
	int OUTBDnum = 12;//左下旋钮
	ege_point OUTBDpoints[12] = {
		{leftPanel_x - 35 * Ulength - Lowknob_R1 * cos(OUTBDangle * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin(OUTBDangle * PI / 180)},
		{leftPanel_x - 35 * Ulength - Lowknob_R1 * cos((OUTBDangle + 30) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((OUTBDangle + 30) * PI / 180)},
		{leftPanel_x - 35 * Ulength - Lowknob_R1 * cos((OUTBDangle + 60) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((OUTBDangle + 60) * PI / 180)},
		{leftPanel_x - 35 * Ulength - Lowknob_R1 * cos((OUTBDangle + 90) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((OUTBDangle + 90) * PI / 180)},
		{leftPanel_x - 35 * Ulength - Lowknob_R1 * cos((OUTBDangle + 120) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((OUTBDangle + 120) * PI / 180)},
		{leftPanel_x - 35 * Ulength - Lowknob_R1 * cos((OUTBDangle + 150) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((OUTBDangle + 150) * PI / 180)},
		{leftPanel_x - 35 * Ulength - Lowknob_R1 * cos((OUTBDangle + 180) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((OUTBDangle + 180) * PI / 180)},
		{leftPanel_x - 35 * Ulength - Lowknob_R1 * cos((OUTBDangle + 210) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((OUTBDangle + 210) * PI / 180)},
		{leftPanel_x - 35 * Ulength - Lowknob_R1 * cos((OUTBDangle + 240) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((OUTBDangle + 240) * PI / 180)},
		{leftPanel_x - 35 * Ulength - Lowknob_R1 * cos((OUTBDangle + 270) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((OUTBDangle + 270) * PI / 180)},
		{leftPanel_x - 35 * Ulength - Lowknob_R1 * cos((OUTBDangle + 300) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((OUTBDangle + 300) * PI / 180)},
		{leftPanel_x - 35 * Ulength - Lowknob_R1 * cos((OUTBDangle + 330) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((OUTBDangle + 330) * PI / 180)},
	};
	setfillcolor(EGEARGB(0XFF, 0X58, 0X58, 0X56));
	ege_setpattern_lineargradient(leftPanel_x - 35 * Ulength, leftPanel_y + 23 * Ulength - Lowknob_R1, EGEARGB(0XFF, 0X40, 0X40, 0X40),
		leftPanel_x - 35 * Ulength, leftPanel_y + 23 * Ulength + Lowknob_R1, EGEARGB(0XFF, 0X8D, 0X8F, 0X8B));
	ege_fillpoly(OUTBDnum, OUTBDpoints);
	ege_setpattern_none();
	
	setcolor(EGEARGB(0X2F, 0X50, 0X50, 0X50));
	for (int i = 0; i < 360; i += 30) {
		ege_line(leftPanel_x - 35 * Ulength - Lowknob_R1 * cos((OUTBDangle + i) * PI / 180), leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((OUTBDangle + i) * PI / 180),
			leftPanel_x - 36.7 * Ulength - Lowknob_R2 * cos((OUTBDangle + i) * PI / 180), leftPanel_y + 23 * Ulength - Lowknob_R2 * sin((OUTBDangle + i) * PI / 180));
	}
	
	
	int OUTBDnum_1 = 12;
	ege_point OUTBDploy_1[12] = {
		{leftPanel_x  - 36.7 * Ulength - Lowknob_R2 * cos(OUTBDangle * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R2 * sin(OUTBDangle * PI / 180)},
		{leftPanel_x  - 36.7 * Ulength - Lowknob_R2 * cos((OUTBDangle + 30) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R2 * sin((OUTBDangle + 30) * PI / 180)},
		{leftPanel_x  - 36.7 * Ulength - Lowknob_R2 * cos((OUTBDangle + 60) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R2 * sin((OUTBDangle + 60) * PI / 180)},
		{leftPanel_x  - 36.7 * Ulength - Lowknob_R2 * cos((OUTBDangle + 90) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R2 * sin((OUTBDangle + 90) * PI / 180)},
		{leftPanel_x  - 36.7 * Ulength - Lowknob_R2 * cos((OUTBDangle + 120) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R2 * sin((OUTBDangle + 120) * PI / 180)},
		{leftPanel_x  - 36.7 * Ulength - Lowknob_R2 * cos((OUTBDangle + 150) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R2 * sin((OUTBDangle + 150) * PI / 180)},
		{leftPanel_x  - 36.7 * Ulength - Lowknob_R2 * cos((OUTBDangle + 180) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R2 * sin((OUTBDangle + 180) * PI / 180)},
		{leftPanel_x  - 36.7 * Ulength - Lowknob_R2 * cos((OUTBDangle + 210) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R2 * sin((OUTBDangle + 210) * PI / 180)},
		{leftPanel_x  - 36.7 * Ulength - Lowknob_R2 * cos((OUTBDangle + 240) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R2 * sin((OUTBDangle + 240) * PI / 180)},
		{leftPanel_x  - 36.7 * Ulength - Lowknob_R2 * cos((OUTBDangle + 270) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R2 * sin((OUTBDangle + 270) * PI / 180)},
		{leftPanel_x  - 36.7 * Ulength - Lowknob_R2 * cos((OUTBDangle + 300) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R2 * sin((OUTBDangle + 300) * PI / 180)},
		{leftPanel_x  - 36.7 * Ulength - Lowknob_R2 * cos((OUTBDangle + 330) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R2 * sin((OUTBDangle + 330) * PI / 180)},
	};
	
	setfillcolor(EGEARGB(0XFF, 0X3A, 0X3A, 0X38));
	ege_fillpoly(OUTBDnum_1, OUTBDploy_1);
	
	
	setcolor(EGEARGB(0XFF, 0X20, 0X20, 0X20));
	setlinewidth(Linewidth / 7 * 4);
	
	ege_line(leftPanel_x - 36.7 * Ulength - (Ulength * 1) * cos((90 + OUTBDangle) * PI / 180), leftPanel_y + 23 * Ulength - (Ulength * 1) * sin((90 + OUTBDangle) * PI / 180),
		leftPanel_x - 35 * Ulength - Lowknob_R1 * cos((OUTBDangle + 7) * PI / 180), leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((OUTBDangle + 7) * PI / 180));
	ege_line(leftPanel_x - 36.7 * Ulength - (Ulength * 1) * cos((-90 + OUTBDangle) * PI / 180), leftPanel_y + 23 * Ulength - (Ulength * 1) * sin((-90 + OUTBDangle) * PI / 180),
		leftPanel_x - 35 * Ulength - Lowknob_R1 * cos((OUTBDangle - 7) * PI / 180), leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((OUTBDangle - 7) * PI / 180));
	setcolor(EGEARGB(0XFF, 0X40, 0X41, 0X42));
	setlinewidth(Linewidth * 1.5);
	ege_line(leftPanel_x - 36.7 * Ulength, leftPanel_y + 23 * Ulength,
		leftPanel_x - 35 * Ulength - Lowknob_R1 * cos(OUTBDangle * PI / 180), leftPanel_y + 23 * Ulength - Lowknob_R1 * sin(OUTBDangle * PI / 180));
	setcolor(EGEARGB(0XFF, 0X20, 0X20, 0X20));
	setlinewidth(Linewidth / 7 * 4);
	ege_line(leftPanel_x - 36.7 * Ulength - (Ulength * 1) * cos((90 + OUTBDangle) * PI / 180), leftPanel_y + 23 * Ulength - (Ulength * 1) * sin((90 + OUTBDangle) * PI / 180),
		leftPanel_x - 36.7 * Ulength - (Ulength * 1) * cos((-90 + OUTBDangle) * PI / 180), leftPanel_y + 23 * Ulength - (Ulength * 1) * sin((-90 + OUTBDangle) * PI / 180));
	
	setlinewidth(Linewidth / 7 * 4);
	
	
	
	
	int INBDnum = 12;//中下旋钮
	ege_point INBDpoints[12] = {
		{leftPanel_x - 1 * Ulength - Lowknob_R1 * cos(INBDangle * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin(INBDangle * PI / 180)},
		{leftPanel_x - 1 * Ulength - Lowknob_R1 * cos((INBDangle + 30) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + 30) * PI / 180)},
		{leftPanel_x - 1 * Ulength - Lowknob_R1 * cos((INBDangle + 60) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + 60) * PI / 180)},
		{leftPanel_x - 1 * Ulength - Lowknob_R1 * cos((INBDangle + 90) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + 90) * PI / 180)},
		{leftPanel_x - 1 * Ulength - Lowknob_R1 * cos((INBDangle + 120) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + 120) * PI / 180)},
		{leftPanel_x - 1 * Ulength - Lowknob_R1 * cos((INBDangle + 150) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + 150) * PI / 180)},
		{leftPanel_x - 1 * Ulength - Lowknob_R1 * cos((INBDangle + 180) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + 180) * PI / 180)},
		{leftPanel_x - 1 * Ulength - Lowknob_R1 * cos((INBDangle + 210) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + 210) * PI / 180)},
		{leftPanel_x - 1 * Ulength - Lowknob_R1 * cos((INBDangle + 240) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + 240) * PI / 180)},
		{leftPanel_x - 1 * Ulength - Lowknob_R1 * cos((INBDangle + 270) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + 270) * PI / 180)},
		{leftPanel_x - 1 * Ulength - Lowknob_R1 * cos((INBDangle + 300) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + 300) * PI / 180)},
		{leftPanel_x - 1 * Ulength - Lowknob_R1 * cos((INBDangle + 330) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + 330) * PI / 180)},
	};
	setfillcolor(EGEARGB(0XFF, 0X58, 0X58, 0X56));
	ege_setpattern_lineargradient(leftPanel_x - 1 * Ulength, leftPanel_y + 23 * Ulength - Lowknob_R1, EGEARGB(0XFF, 0X40, 0X40, 0X40),
		leftPanel_x - 1 * Ulength, leftPanel_y + 23 * Ulength + Lowknob_R1, EGEARGB(0XFF, 0X8D, 0X8F, 0X8B));
	ege_fillpoly(INBDnum, INBDpoints);
	ege_setpattern_none();
	
	setcolor(EGEARGB(0X2F, 0X50, 0X50, 0X50));
	for (int i = 0; i < 360; i += 30) {
		ege_line(leftPanel_x - 1 * Ulength - Lowknob_R1 * cos((INBDangle + i) * PI / 180), leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + i) * PI / 180),
			leftPanel_x - 2 * Ulength - Lowknob_R1 * cos((INBDangle + i) * PI / 180), leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + i) * PI / 180));
	}
	
	
	int INBDnum_1 = 12;//中下旋钮
	ege_point INBDpoints_1[12] = {
		{leftPanel_x - 2 * Ulength - Lowknob_R1 * cos(INBDangle * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin(INBDangle * PI / 180)},
		{leftPanel_x - 2 * Ulength - Lowknob_R1 * cos((INBDangle + 30) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + 30) * PI / 180)},
		{leftPanel_x - 2 * Ulength - Lowknob_R1 * cos((INBDangle + 60) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + 60) * PI / 180)},
		{leftPanel_x - 2 * Ulength - Lowknob_R1 * cos((INBDangle + 90) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + 90) * PI / 180)},
		{leftPanel_x - 2 * Ulength - Lowknob_R1 * cos((INBDangle + 120) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + 120) * PI / 180)},
		{leftPanel_x - 2 * Ulength - Lowknob_R1 * cos((INBDangle + 150) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + 150) * PI / 180)},
		{leftPanel_x - 2 * Ulength - Lowknob_R1 * cos((INBDangle + 180) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + 180) * PI / 180)},
		{leftPanel_x - 2 * Ulength - Lowknob_R1 * cos((INBDangle + 210) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + 210) * PI / 180)},
		{leftPanel_x - 2 * Ulength - Lowknob_R1 * cos((INBDangle + 240) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + 240) * PI / 180)},
		{leftPanel_x - 2 * Ulength - Lowknob_R1 * cos((INBDangle + 270) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + 270) * PI / 180)},
		{leftPanel_x - 2 * Ulength - Lowknob_R1 * cos((INBDangle + 300) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + 300) * PI / 180)},
		{leftPanel_x - 2 * Ulength - Lowknob_R1 * cos((INBDangle + 330) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((INBDangle + 330) * PI / 180)},
	};
	setfillcolor(EGEARGB(0XFF, 0X3A, 0X3A, 0X38));
	ege_fillpoly(INBDnum_1, INBDpoints_1);
	
	
	
	int INBDnum_2 = 12;
	ege_point INBDpoints_2[12] = {
		{leftPanel_x - 2 * Ulength - Lowknob_R3 * cos(INBDangle_1 * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin(INBDangle_1 * PI / 180)},
		{leftPanel_x - 2 * Ulength - Lowknob_R3 * cos((INBDangle_1 + 30) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + 30) * PI / 180)},
		{leftPanel_x - 2 * Ulength - Lowknob_R3 * cos((INBDangle_1 + 60) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + 60) * PI / 180)},
		{leftPanel_x - 2 * Ulength - Lowknob_R3 * cos((INBDangle_1 + 90) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + 90) * PI / 180)},
		{leftPanel_x - 2 * Ulength - Lowknob_R3 * cos((INBDangle_1 + 120) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + 120) * PI / 180)},
		{leftPanel_x - 2 * Ulength - Lowknob_R3 * cos((INBDangle_1 + 150) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + 150) * PI / 180)},
		{leftPanel_x - 2 * Ulength - Lowknob_R3 * cos((INBDangle_1 + 180) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + 180) * PI / 180)},
		{leftPanel_x - 2 * Ulength - Lowknob_R3 * cos((INBDangle_1 + 210) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + 210) * PI / 180)},
		{leftPanel_x - 2 * Ulength - Lowknob_R3 * cos((INBDangle_1 + 240) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + 240) * PI / 180)},
		{leftPanel_x - 2 * Ulength - Lowknob_R3 * cos((INBDangle_1 + 270) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + 270) * PI / 180)},
		{leftPanel_x - 2 * Ulength - Lowknob_R3 * cos((INBDangle_1 + 300) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + 300) * PI / 180)},
		{leftPanel_x - 2 * Ulength - Lowknob_R3 * cos((INBDangle_1 + 330) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + 330) * PI / 180)},
	};
	setfillcolor(EGEARGB(0XFF, 0X58, 0X58, 0X56));
	ege_setpattern_lineargradient(leftPanel_x - 2 * Ulength, leftPanel_y + 23 * Ulength - Lowknob_R3, EGEARGB(0XFF, 0X40, 0X40, 0X40),
		leftPanel_x - 2 * Ulength, leftPanel_y + 23 * Ulength + Lowknob_R3, EGEARGB(0XFF, 0X8D, 0X8F, 0X8B));
	ege_fillpoly(INBDnum_2, INBDpoints_2);
	ege_setpattern_none();
	
	setcolor(EGEARGB(0X2F, 0X40, 0X40, 0X40));
	for (int i = 0; i < 360; i += 30) {
		ege_line(leftPanel_x - 2 * Ulength - Lowknob_R3 * cos((INBDangle_1 + i) * PI / 180), leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + i) * PI / 180),
			leftPanel_x - 3 * Ulength - Lowknob_R3 * cos((INBDangle_1 + i) * PI / 180), leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + i) * PI / 180));
	}
	
	
	int INBDnum_3 = 12;//中下旋钮
	ege_point INBDpoints_3[12] = {
		{leftPanel_x - 3 * Ulength - Lowknob_R3 * cos(INBDangle_1 * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin(INBDangle_1 * PI / 180)},
		{leftPanel_x - 3 * Ulength - Lowknob_R3 * cos((INBDangle_1 + 30) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + 30) * PI / 180)},
		{leftPanel_x - 3 * Ulength - Lowknob_R3 * cos((INBDangle_1 + 60) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + 60) * PI / 180)},
		{leftPanel_x - 3 * Ulength - Lowknob_R3 * cos((INBDangle_1 + 90) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + 90) * PI / 180)},
		{leftPanel_x - 3 * Ulength - Lowknob_R3 * cos((INBDangle_1 + 120) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + 120) * PI / 180)},
		{leftPanel_x - 3 * Ulength - Lowknob_R3 * cos((INBDangle_1 + 150) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + 150) * PI / 180)},
		{leftPanel_x - 3 * Ulength - Lowknob_R3 * cos((INBDangle_1 + 180) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + 180) * PI / 180)},
		{leftPanel_x - 3 * Ulength - Lowknob_R3 * cos((INBDangle_1 + 210) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + 210) * PI / 180)},
		{leftPanel_x - 3 * Ulength - Lowknob_R3 * cos((INBDangle_1 + 240) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + 240) * PI / 180)},
		{leftPanel_x - 3 * Ulength - Lowknob_R3 * cos((INBDangle_1 + 270) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + 270) * PI / 180)},
		{leftPanel_x - 3 * Ulength - Lowknob_R3 * cos((INBDangle_1 + 300) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + 300) * PI / 180)},
		{leftPanel_x - 3 * Ulength - Lowknob_R3 * cos((INBDangle_1 + 330) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + 330) * PI / 180)},
	};
	setfillcolor(EGEARGB(0XFF, 0X3A, 0X3A, 0X38));
	ege_fillpoly(INBDnum_3, INBDpoints_3);
	
	setlinewidth(Linewidth / 7);
	
	setcolor(EGEARGB(0X2F, 0X00, 0X00, 0X00));
	for (int i = 0; i < 360; i += 30) {
		ege_line(leftPanel_x - 3 * Ulength - Lowknob_R3 * cos((INBDangle_1 + i) * PI / 180), leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + i) * PI / 180),
			leftPanel_x - 3 * Ulength - Lowknob_R3 * cos((INBDangle_1 + 30 + i) * PI / 180), leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((INBDangle_1 + i + 30) * PI / 180));
		
	}
	
	setcolor(EGEARGB(0XFF, 0X20, 0X20, 0X20));
	setlinewidth(Linewidth / 7 * 4);
	ege_line(leftPanel_x - 4 * Ulength, leftPanel_y + 23 * Ulength,
		leftPanel_x - 2 * Ulength, leftPanel_y + 23 * Ulength);
	ege_line(leftPanel_x - 4 * Ulength, leftPanel_y + 23 * Ulength,
		leftPanel_x - 4 * Ulength, leftPanel_y + 23 * Ulength - Lowknob_R3);
	ege_line(leftPanel_x - 2 * Ulength, leftPanel_y + 23 * Ulength,
		leftPanel_x - 2 * Ulength, leftPanel_y + 23 * Ulength - Lowknob_R3);
	setcolor(EGEARGB(0XFF, 0X40, 0X41, 0X42));
	setlinewidth(Linewidth * 1.5);
	ege_line(leftPanel_x - 3 * Ulength, leftPanel_y + 22.5 * Ulength,
		leftPanel_x - 3 * Ulength, leftPanel_y + 23 * Ulength - Lowknob_R3);
	setlinewidth(Linewidth / 7 * 4);
	
	
	
	
	
	int LOWERnum = 12;//右下旋钮
	ege_point LOWERpoints[12] = {
		{leftPanel_x + 32 * Ulength - Lowknob_R1 * cos(LOWERangle * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin(LOWERangle * PI / 180)},
		{leftPanel_x + 32 * Ulength - Lowknob_R1 * cos((LOWERangle + 30) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + 30) * PI / 180)},
		{leftPanel_x + 32 * Ulength - Lowknob_R1 * cos((LOWERangle + 60) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + 60) * PI / 180)},
		{leftPanel_x + 32 * Ulength - Lowknob_R1 * cos((LOWERangle + 90) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + 90) * PI / 180)},
		{leftPanel_x + 32 * Ulength - Lowknob_R1 * cos((LOWERangle + 120) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + 120) * PI / 180)},
		{leftPanel_x + 32 * Ulength - Lowknob_R1 * cos((LOWERangle + 150) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + 150) * PI / 180)},
		{leftPanel_x + 32 * Ulength - Lowknob_R1 * cos((LOWERangle + 180) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + 180) * PI / 180)},
		{leftPanel_x + 32 * Ulength - Lowknob_R1 * cos((LOWERangle + 210) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + 210) * PI / 180)},
		{leftPanel_x + 32 * Ulength - Lowknob_R1 * cos((LOWERangle + 240) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + 240) * PI / 180)},
		{leftPanel_x + 32 * Ulength - Lowknob_R1 * cos((LOWERangle + 270) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + 270) * PI / 180)},
		{leftPanel_x + 32 * Ulength - Lowknob_R1 * cos((LOWERangle + 300) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + 300) * PI / 180)},
		{leftPanel_x + 32 * Ulength - Lowknob_R1 * cos((LOWERangle + 330) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + 330) * PI / 180)},
	};
	setfillcolor(EGEARGB(0XFF, 0X58, 0X58, 0X56));
	ege_setpattern_lineargradient(leftPanel_x + 32 * Ulength, leftPanel_y + 23 * Ulength - Lowknob_R1, EGEARGB(0XFF, 0X40, 0X40, 0X40),
		leftPanel_x + 32 * Ulength, leftPanel_y + 23 * Ulength + Lowknob_R1, EGEARGB(0XFF, 0X8D, 0X8F, 0X8B));
	ege_fillpoly(LOWERnum, LOWERpoints);
	ege_setpattern_none();
	
	setcolor(EGEARGB(0X2F, 0X50, 0X50, 0X50));
	for (int i = 0; i < 360; i += 30) {
		ege_line(leftPanel_x + 32 * Ulength - Lowknob_R1 * cos((LOWERangle + i) * PI / 180), leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + i) * PI / 180),
			leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((LOWERangle + i) * PI / 180), leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + i) * PI / 180));
	}
	
	
	int LOWERnum_1 = 12;//右下旋钮
	ege_point LOWERpoints_1[12] = {
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos(LOWERangle * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin(LOWERangle * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((LOWERangle + 30) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + 30) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((LOWERangle + 60) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + 60) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((LOWERangle + 90) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + 90) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((LOWERangle + 120) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + 120) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((LOWERangle + 150) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + 150) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((LOWERangle + 180) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + 180) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((LOWERangle + 210) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + 210) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((LOWERangle + 240) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + 240) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((LOWERangle + 270) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + 270) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((LOWERangle + 300) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + 300) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((LOWERangle + 330) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R1 * sin((LOWERangle + 330) * PI / 180)},
	};
	setfillcolor(EGEARGB(0XFF, 0X3A, 0X3A, 0X38));
	ege_fillpoly(LOWERnum_1, LOWERpoints_1);
	
	
	
	int LOWERnum_2 = 12;
	ege_point LOWERpoints_2[12] = {
		{leftPanel_x + 31 * Ulength - Lowknob_R3 * cos(LOWERangle_1 * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin(LOWERangle_1 * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + 30) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + 30) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + 60) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + 60) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + 90) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + 90) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + 120) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + 120) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + 150) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + 150) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + 180) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + 180) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + 210) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + 210) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + 240) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + 240) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + 270) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + 270) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + 300) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + 300) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + 330) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + 330) * PI / 180)},
	};
	setfillcolor(EGEARGB(0XFF, 0X58, 0X58, 0X56));
	ege_setpattern_lineargradient(leftPanel_x + 31 * Ulength, leftPanel_y + 23 * Ulength - Lowknob_R3, EGEARGB(0XFF, 0X40, 0X40, 0X40),
		leftPanel_x + 31 * Ulength, leftPanel_y + 23 * Ulength + Lowknob_R3, EGEARGB(0XFF, 0X8D, 0X8F, 0X8B));
	ege_fillpoly(LOWERnum_2, LOWERpoints_2);
	ege_setpattern_none();
	
	setcolor(EGEARGB(0X2F, 0X50, 0X50, 0X50));
	for (int i = 0; i < 360; i += 30) {
		ege_line(leftPanel_x + 31 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + i) * PI / 180), leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + i) * PI / 180),
			leftPanel_x + 30 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + i) * PI / 180), leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + i) * PI / 180));
	}
	
	
	
	
	
	int LOWERnum_3 = 12;//旋钮右下
	ege_point LOWERpoints_3[12] = {
		{leftPanel_x + 30 * Ulength - Lowknob_R3 * cos(LOWERangle_1 * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin(LOWERangle_1 * PI / 180)},
		{leftPanel_x + 30 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + 30) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + 30) * PI / 180)},
		{leftPanel_x + 30 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + 60) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + 60) * PI / 180)},
		{leftPanel_x + 30 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + 90) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + 90) * PI / 180)},
		{leftPanel_x + 30 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + 120) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + 120) * PI / 180)},
		{leftPanel_x + 30 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + 150) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + 150) * PI / 180)},
		{leftPanel_x + 30 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + 180) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + 180) * PI / 180)},
		{leftPanel_x + 30 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + 210) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + 210) * PI / 180)},
		{leftPanel_x + 30 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + 240) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + 240) * PI / 180)},
		{leftPanel_x + 30 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + 270) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + 270) * PI / 180)},
		{leftPanel_x + 30 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + 300) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + 300) * PI / 180)},
		{leftPanel_x + 30 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + 330) * PI / 180) , leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + 330) * PI / 180)},
	};
	setfillcolor(EGEARGB(0XFF, 0X3A, 0X3A, 0X38));
	ege_fillpoly(LOWERnum_3, LOWERpoints_3);
	
	
	
	setlinewidth(Linewidth / 7);
	
	setcolor(EGEARGB(0X2F, 0X00, 0X00, 0X00));
	for (int i = 0; i < 360; i += 30) {
		ege_line(leftPanel_x + 30 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + i) * PI / 180), leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + i) * PI / 180),
			leftPanel_x + 30 * Ulength - Lowknob_R3 * cos((LOWERangle_1 + 30 + i) * PI / 180), leftPanel_y + 23 * Ulength - Lowknob_R3 * sin((LOWERangle_1 + i + 30) * PI / 180));
		
	}
	
	setcolor(EGEARGB(0XFF, 0X20, 0X20, 0X20));
	setlinewidth(Linewidth / 7 * 4);
	ege_line(leftPanel_x + 31 * Ulength, leftPanel_y + 23 * Ulength,
		leftPanel_x + 29 * Ulength, leftPanel_y + 23 * Ulength);
	ege_line(leftPanel_x + 31 * Ulength, leftPanel_y + 23 * Ulength,
		leftPanel_x + 31 * Ulength, leftPanel_y + 23 * Ulength - Lowknob_R3);
	ege_line(leftPanel_x + 29 * Ulength, leftPanel_y + 23 * Ulength,
		leftPanel_x + 29 * Ulength, leftPanel_y + 23 * Ulength - Lowknob_R3);
	setcolor(EGEARGB(0XFF, 0X40, 0X41, 0X42));
	setlinewidth(Linewidth * 1.5);
	ege_line(leftPanel_x + 30 * Ulength, leftPanel_y + 22.5 * Ulength,
		leftPanel_x + 30 * Ulength, leftPanel_y + 23 * Ulength - Lowknob_R3);
	setlinewidth(Linewidth / 7 * 4);
	
	
	
	int UPPERnum = 12;//右上旋钮
	ege_point UPPERpoints[12] = {
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos(UPPERangle * PI / 180) , leftPanel_y - 18 * Ulength - Lowknob_R1 * sin(UPPERangle * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((UPPERangle + 30) * PI / 180) , leftPanel_y - 18 * Ulength - Lowknob_R1 * sin((UPPERangle + 30) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((UPPERangle + 60) * PI / 180) , leftPanel_y - 18 * Ulength - Lowknob_R1 * sin((UPPERangle + 60) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((UPPERangle + 90) * PI / 180) , leftPanel_y - 18 * Ulength - Lowknob_R1 * sin((UPPERangle + 90) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((UPPERangle + 120) * PI / 180) , leftPanel_y - 18 * Ulength - Lowknob_R1 * sin((UPPERangle + 120) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((UPPERangle + 150) * PI / 180) , leftPanel_y - 18 * Ulength - Lowknob_R1 * sin((UPPERangle + 150) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((UPPERangle + 180) * PI / 180) , leftPanel_y - 18 * Ulength - Lowknob_R1 * sin((UPPERangle + 180) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((UPPERangle + 210) * PI / 180) , leftPanel_y - 18 * Ulength - Lowknob_R1 * sin((UPPERangle + 210) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((UPPERangle + 240) * PI / 180) , leftPanel_y - 18 * Ulength - Lowknob_R1 * sin((UPPERangle + 240) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((UPPERangle + 270) * PI / 180) , leftPanel_y - 18 * Ulength - Lowknob_R1 * sin((UPPERangle + 270) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((UPPERangle + 300) * PI / 180) , leftPanel_y - 18 * Ulength - Lowknob_R1 * sin((UPPERangle + 300) * PI / 180)},
		{leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((UPPERangle + 330) * PI / 180) , leftPanel_y - 18 * Ulength - Lowknob_R1 * sin((UPPERangle + 330) * PI / 180)},
	};
	setfillcolor(EGEARGB(0XFF, 0X58, 0X58, 0X56));
	ege_setpattern_lineargradient(leftPanel_x + 31 * Ulength, leftPanel_y - 18 * Ulength - Lowknob_R1, EGEARGB(0XFF, 0X40, 0X40, 0X40),
		leftPanel_x + 31 * Ulength, leftPanel_y - 18 * Ulength + Lowknob_R1, EGEARGB(0XFF, 0X8D, 0X8F, 0X8B));
	ege_fillpoly(UPPERnum, UPPERpoints);
	ege_setpattern_none();
	
	setcolor(EGEARGB(0X2F, 0X50, 0X50, 0X50));
	for (int i = 0; i < 360; i += 30) {
		ege_line(leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((UPPERangle + i) * PI / 180), leftPanel_y - 18 * Ulength - Lowknob_R1 * sin((UPPERangle + i) * PI / 180),
			leftPanel_x + 30 * Ulength - Lowknob_R2 * cos((UPPERangle + i) * PI / 180), leftPanel_y - 18.5 * Ulength - Lowknob_R2 * sin((UPPERangle + i) * PI / 180));
	}
	
	int UPPERnum_1 = 12;
	ege_point UPPERploy_1[12] = {
		{leftPanel_x + 30 * Ulength - Lowknob_R2 * cos(UPPERangle * PI / 180) , leftPanel_y - 18.5 * Ulength - Lowknob_R2 * sin(UPPERangle * PI / 180)},
		{leftPanel_x + 30 * Ulength - Lowknob_R2 * cos((UPPERangle + 30) * PI / 180) , leftPanel_y - 18.5 * Ulength - Lowknob_R2 * sin((UPPERangle + 30) * PI / 180)},
		{leftPanel_x + 30 * Ulength - Lowknob_R2 * cos((UPPERangle + 60) * PI / 180) , leftPanel_y - 18.5 * Ulength - Lowknob_R2 * sin((UPPERangle + 60) * PI / 180)},
		{leftPanel_x + 30 * Ulength - Lowknob_R2 * cos((UPPERangle + 90) * PI / 180) , leftPanel_y - 18.5 * Ulength - Lowknob_R2 * sin((UPPERangle + 90) * PI / 180)},
		{leftPanel_x + 30 * Ulength - Lowknob_R2 * cos((UPPERangle + 120) * PI / 180) , leftPanel_y - 18.5 * Ulength - Lowknob_R2 * sin((UPPERangle + 120) * PI / 180)},
		{leftPanel_x + 30 * Ulength - Lowknob_R2 * cos((UPPERangle + 150) * PI / 180) , leftPanel_y - 18.5 * Ulength - Lowknob_R2 * sin((UPPERangle + 150) * PI / 180)},
		{leftPanel_x + 30 * Ulength - Lowknob_R2 * cos((UPPERangle + 180) * PI / 180) , leftPanel_y - 18.5 * Ulength - Lowknob_R2 * sin((UPPERangle + 180) * PI / 180)},
		{leftPanel_x + 30 * Ulength - Lowknob_R2 * cos((UPPERangle + 210) * PI / 180) , leftPanel_y - 18.5 * Ulength - Lowknob_R2 * sin((UPPERangle + 210) * PI / 180)},
		{leftPanel_x + 30 * Ulength - Lowknob_R2 * cos((UPPERangle + 240) * PI / 180) , leftPanel_y - 18.5 * Ulength - Lowknob_R2 * sin((UPPERangle + 240) * PI / 180)},
		{leftPanel_x + 30 * Ulength - Lowknob_R2 * cos((UPPERangle + 270) * PI / 180) , leftPanel_y - 18.5 * Ulength - Lowknob_R2 * sin((UPPERangle + 270) * PI / 180)},
		{leftPanel_x + 30 * Ulength - Lowknob_R2 * cos((UPPERangle + 300) * PI / 180) , leftPanel_y - 18.5 * Ulength - Lowknob_R2 * sin((UPPERangle + 300) * PI / 180)},
		{leftPanel_x + 30 * Ulength - Lowknob_R2 * cos((UPPERangle + 330) * PI / 180) , leftPanel_y - 18.5 * Ulength - Lowknob_R2 * sin((UPPERangle + 330) * PI / 180)},
	};
	
	setfillcolor(EGEARGB(0XFF, 0X3A, 0X3A, 0X38));
	ege_fillpoly(UPPERnum_1, UPPERploy_1);
	
	
	setcolor(EGEARGB(0XFF, 0X20, 0X20, 0X20));
	setlinewidth(Linewidth / 7 * 4);
	
	ege_line(leftPanel_x + 30 * Ulength - (Ulength * 1) * cos((90 + UPPERangle) * PI / 180), leftPanel_y - 18 * Ulength - (Ulength * 1) * sin((90 + UPPERangle) * PI / 180),
		leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((UPPERangle + 7) * PI / 180), leftPanel_y - 18.5 * Ulength - Lowknob_R1 * sin((UPPERangle + 7) * PI / 180));
	ege_line(leftPanel_x + 30 * Ulength - (Ulength * 1) * cos((-90 + UPPERangle) * PI / 180), leftPanel_y - 18 * Ulength - (Ulength * 1) * sin((-90 + UPPERangle) * PI / 180),
		leftPanel_x + 31 * Ulength - Lowknob_R1 * cos((UPPERangle - 7) * PI / 180), leftPanel_y - 18.5 * Ulength - Lowknob_R1 * sin((UPPERangle - 7) * PI / 180));
	setcolor(EGEARGB(0XFF, 0X40, 0X41, 0X42));
	setlinewidth(Linewidth * 1.5);
	ege_line(leftPanel_x + 30 * Ulength, leftPanel_y - 18 * Ulength,
		leftPanel_x + 31 * Ulength - Lowknob_R1 * cos(UPPERangle * PI / 180), leftPanel_y - 18.5 * Ulength - Lowknob_R1 * sin(UPPERangle * PI / 180));
	setcolor(EGEARGB(0XFF, 0X20, 0X20, 0X20));
	setlinewidth(Linewidth / 7 * 4);
	ege_line(leftPanel_x + 30 * Ulength - (Ulength * 1) * cos((90 + UPPERangle) * PI / 180), leftPanel_y - 18 * Ulength - (Ulength * 1) * sin((90 + UPPERangle) * PI / 180),
		leftPanel_x + 30 * Ulength - (Ulength * 1) * cos((-90 + UPPERangle) * PI / 180), leftPanel_y - 18 * Ulength - (Ulength * 1) * sin((-90 + UPPERangle) * PI / 180));
	
	setlinewidth(Linewidth / 7 * 4);
	
	
	
	
	
	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	setlinewidth(Linewidth / 7 * 4);
	setfont(Ulength * 6, Ulength * 2.5, "Bahnschrift");
	
	ege_line(leftPanel_x - Ulength * 35 - lefttop_R1 * cos(-50 * PI / 180), leftPanel_y - Ulength * 18 - lefttop_R1 * sin(-50 * PI / 180),
		leftPanel_x - Ulength * 35 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 18 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_line(leftPanel_x - Ulength * 35 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 18 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180),
		leftPanel_x - Ulength * 38 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 18 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("OFF", leftPanel_x - Ulength * 43 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 17 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("OUTBD DU", leftPanel_x - Ulength * 27 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 6 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("BRT", leftPanel_x - Ulength * 25 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 1 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("INBD DU", leftPanel_x + Ulength * 9 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 6 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("BRT", leftPanel_x + Ulength * 9 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 1 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("LOWER DU", leftPanel_x + Ulength * 42 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 6 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("BRT", leftPanel_x + Ulength * 42 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 1 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("UPPER DU", leftPanel_x + Ulength * 42 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 46 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("BRT", leftPanel_x + Ulength * 42 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 41 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("MAIN PANEL", leftPanel_x - Ulength * 26 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 50 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	
	
	
	
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	
	setlinewidth(Linewidth / 7 * 4);
	setfont(Ulength * 6, Ulength * 2.5, "Bahnschrift");
	ege_line(leftPanel_x - Ulength * 35 - lefttop_R1 * cos(-50 * PI / 180), leftPanel_y - Ulength * 18 - lefttop_R1 * sin(-50 * PI / 180),
		leftPanel_x - Ulength * 35 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 18 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_line(leftPanel_x - Ulength * 35 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 18 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180),
		leftPanel_x - Ulength * 38 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 18 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("OFF", leftPanel_x - Ulength * 43 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 17 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("OUTBD DU" , leftPanel_x - Ulength * 27 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 6 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("BRT", leftPanel_x - Ulength * 25 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 1 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("INBD DU", leftPanel_x + Ulength * 9 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 6 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("BRT", leftPanel_x + Ulength * 9 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 1 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("LOWER DU", leftPanel_x + Ulength * 42 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 6 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("BRT", leftPanel_x + Ulength * 42 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 1 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("UPPER DU", leftPanel_x + Ulength * 42 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 46 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("BRT", leftPanel_x + Ulength * 42 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 41 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("MAIN PANEL", leftPanel_x - Ulength * 26 - (lefttop_R1 + Ulength * 3) * cos((-50) * PI / 180), leftPanel_y - Ulength * 50 - (lefttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	
	
	
	ege_enable_aa(false);
	setcolor(EGEARGB(0XFF, 0X4E, 0X4F, 0X4E));
	setlinewidth(Linewidth / 2);
	int Brightnum = 25;
	ege_point BrightPloypoints[25] = {
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos((-40 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin((-40 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos((-20 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin((-20 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos((-20 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin((-20 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos((-20 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin((-20 + Brightangle) * PI / 180)},
		
		{leftPanel_x - Ulength * 35 - (Ulength * 9) * cos((30 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 9) * cos((30 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 9) * cos((30 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + Brightangle) * PI / 180)},
		
		{leftPanel_x - Ulength * 35 - (Ulength * 13) * cos((110 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 13) * cos((110 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 13) * cos((110 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + Brightangle) * PI / 180)},
		
		
		{leftPanel_x - Ulength * 35 - (Ulength * 13.5) * cos((110 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 13.5) * sin((110 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 14.5) * cos((114 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 14.5) * sin((114 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 14.5) * cos((120 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 14.5) * sin((120 + Brightangle) * PI / 180)},
		
		{leftPanel_x - Ulength * 35 - (Ulength * 14) * cos((167 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 14) * sin((167 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 14) * cos((167 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 14) * sin((167 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 14) * cos((167 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 14) * sin((167 + Brightangle) * PI / 180)},
		
		
		{leftPanel_x - Ulength * 35 - (Ulength * 14) * cos((173 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 14) * sin((173 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 13.5) * cos((176 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 13.5) * sin((176 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 13) * cos((178 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 13) * sin((178 + Brightangle) * PI / 180)},
		
		
		{leftPanel_x - Ulength * 35 - (Ulength * 8.5) * cos((265 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 8.5) * cos((265 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 8.5) * cos((265 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + Brightangle) * PI / 180)},
		
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos((-40 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin((-40 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos((-40 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin((-40 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos((-40 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin((-40 + Brightangle) * PI / 180)},
		
		
	};
	setfillcolor(EGEARGB(0XFF, 0X4E, 0X4F, 0X4E));
	ege_bezier(Brightnum, BrightPloypoints);
	floodfill(leftPanel_x - Ulength * 35, leftPanel_y - Ulength * 18, EGEARGB(0XFF, 0X4E, 0X4F, 0X4E));
	
	
	ege_enable_aa(true);
	
	
	setcolor(EGEARGB(0XFF, 0X4E, 0X4F, 0X4E));
	setlinewidth(Linewidth / 7 * 4);
	int Brightnum_1 = 25;
	ege_point BrightPloypoints_1[25] = {
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos((-40 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin((-40 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos((-20 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin((-20 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos((-20 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin((-20 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos((-20 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin((-20 + Brightangle) * PI / 180)},
		
		{leftPanel_x - Ulength * 35 - (Ulength * 9) * cos((30 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 9) * cos((30 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 9) * cos((30 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + Brightangle) * PI / 180)},
		
		{leftPanel_x - Ulength * 35 - (Ulength * 13) * cos((110 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 13) * cos((110 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 13) * cos((110 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + Brightangle) * PI / 180)},
		
		
		{leftPanel_x - Ulength * 35 - (Ulength * 13.5) * cos((110 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 13.5) * sin((110 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 14.5) * cos((114 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 14.5) * sin((114 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 14.5) * cos((120 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 14.5) * sin((120 + Brightangle) * PI / 180)},
		
		{leftPanel_x - Ulength * 35 - (Ulength * 14) * cos((167 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 14) * sin((167 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 14) * cos((167 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 14) * sin((167 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 14) * cos((167 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 14) * sin((167 + Brightangle) * PI / 180)},
		
		
		{leftPanel_x - Ulength * 35 - (Ulength * 14) * cos((173 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 14) * sin((173 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 13.5) * cos((176 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 13.5) * sin((176 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 13) * cos((178 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 13) * sin((178 + Brightangle) * PI / 180)},
		
		
		{leftPanel_x - Ulength * 35 - (Ulength * 8.5) * cos((265 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 8.5) * cos((265 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 8.5) * cos((265 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + Brightangle) * PI / 180)},
		
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos((-40 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin((-40 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos((-40 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin((-40 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - lefttop_R1 * cos((-40 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - lefttop_R1 * sin((-40 + Brightangle) * PI / 180)},
		
		
	};
	
	ege_bezier(Brightnum_1, BrightPloypoints_1);
	
	
	int Brightnum_2 = 4;
	ege_point BrightPloypoints_2[4] = {
		{leftPanel_x - Ulength * 35 - (Ulength * 9) * cos((30 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 13) * cos((110 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 13) * cos((178 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 13) * sin((178 + Brightangle) * PI / 180)},
		{leftPanel_x - Ulength * 35 - (Ulength * 8.5) * cos((265 + Brightangle) * PI / 180),leftPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + Brightangle) * PI / 180)}
	};
	
	setfillcolor(EGEARGB(0XFF, 0X36, 0X36, 0X36));
	ege_setpattern_lineargradient(leftPanel_x - Ulength * 35 - (Ulength * 13) * cos((110 + Brightangle) * PI / 180), leftPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + Brightangle) * PI / 180), EGEARGB(0XFF, 0X30, 0X30, 0X30),
		leftPanel_x - Ulength * 35 - (Ulength * 8.5) * cos((265 + Brightangle) * PI / 180), leftPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + Brightangle) * PI / 180), EGEARGB(0XFF, 0X4E, 0X4F, 0X4E));
	ege_fillpoly(Brightnum_2,BrightPloypoints_2);
	ege_setpattern_none();
	
	setcolor(EGEARGB(0X20, 0X8D, 0X8F, 0X8B));
	ege_line(leftPanel_x - Ulength * 35 - (Ulength * 9) * cos((30 + Brightangle) * PI / 180), leftPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + Brightangle) * PI / 180),
		leftPanel_x - Ulength * 35 - (Ulength * 8.5) * cos((265 + Brightangle) * PI / 180), leftPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + Brightangle) * PI / 180));
	ege_line(leftPanel_x - Ulength * 35 - (Ulength * 14.5) * cos((120 + Brightangle) * PI / 180), leftPanel_y - Ulength * 18 - (Ulength * 14.5) * sin((120 + Brightangle) * PI / 180),
		leftPanel_x - Ulength * 35 - (Ulength * 14) * cos((167 + Brightangle) * PI / 180), leftPanel_y - Ulength * 18 - (Ulength * 14) * sin((167 + Brightangle) * PI / 180));
	
	
	
	setcolor(EGEARGB(0XFF, 0X20, 0X20, 0X20));
	setlinewidth(Linewidth / 7 * 4);
	ege_line(leftPanel_x - Ulength * 35 - (Ulength * 2) * cos((110 + Brightangle) * PI / 180), leftPanel_y - Ulength * 18 - (Ulength * 2) * sin((110 + Brightangle) * PI / 180),
		leftPanel_x - Ulength * 35 - (Ulength * 2) * cos((175 + Brightangle) * PI / 180), leftPanel_y - Ulength * 18 - (Ulength * 2) * sin((175 + Brightangle) * PI / 180));
	ege_line(leftPanel_x - Ulength * 35 - (Ulength * 2) * cos((110 + Brightangle) * PI / 180), leftPanel_y - Ulength * 18 - (Ulength * 2) * sin((110 + Brightangle) * PI / 180),
		leftPanel_x - Ulength * 35 - lefttop_R1 * cos((-25 + Brightangle) * PI / 180), leftPanel_y - Ulength * 18 - lefttop_R1 * sin((-25 + Brightangle) * PI / 180));
	ege_line(leftPanel_x - Ulength * 35 - (Ulength * 2) * cos((175 + Brightangle) * PI / 180), leftPanel_y - Ulength * 18 - (Ulength * 2) * sin((175 + Brightangle) * PI / 180),
		leftPanel_x - Ulength * 35 - lefttop_R1 * cos((-35 + Brightangle) * PI / 180), leftPanel_y - Ulength * 18 - lefttop_R1 * sin((-35 + Brightangle) * PI / 180));
	setcolor(EGEARGB(0XFF, 0X40, 0X41, 0X42));
	setlinewidth(Linewidth * 1.5);
	ege_line(leftPanel_x - Ulength * 35 - (Ulength * 1.5) * cos((142 + Brightangle) * PI / 180), leftPanel_y - Ulength * 18 - (Ulength * 1.5) * sin((142 + Brightangle) * PI / 180),
		leftPanel_x - Ulength * 35 - lefttop_R1 * cos((-30 + Brightangle) * PI / 180), leftPanel_y - Ulength * 18 - lefttop_R1 * sin((-30 + Brightangle) * PI / 180));
	setlinewidth(Linewidth / 7 * 4);
	
	
	
	
	
	if (GetAsyncKeyState(0x04) & 0x8000) {
		if (leftPanel_speed_is_down == 0) {
			leftPanel_speed_is_down = 1;
			mousepos(&leftPanel_mouse_x, &leftPanel_mouse_y);
			leftPanel_mouse_x_cur = leftPanel_mouse_x;
			leftPanel_mouse_y_cur = leftPanel_mouse_y;
		}
		if (leftPanel_speed_is_down == 1) {
			if ((leftPanel_mouse_x_cur >= leftPanel_x - Ulength * 35 - lefttop_R1)
				&& (leftPanel_mouse_x_cur <= leftPanel_x - Ulength * 35 + lefttop_R1)
				&& (leftPanel_mouse_y_cur >= leftPanel_y - Ulength * 18 - lefttop_R1)
				&& (leftPanel_mouse_y_cur <= leftPanel_y - Ulength * 18 + lefttop_R1)) {
				
				
				mousepos(&leftPanel_mouse_x, &leftPanel_mouse_y);
				if (leftPanel_mouse_y > leftPanel_mouse_y_cur) {
					if (Brightangle < 255) {
						Brightangle += (leftPanel_mouse_y - leftPanel_mouse_y_cur) / 70;
//						MainPanelLight += (leftPanel_mouse_y - leftPanel_mouse_y_cur) / 100;
						if(Brightangle >= 255){
							Brightangle = 255;
						}
//						MainPanelLight = (Brightangle + 20 ) * 255.0 / 280 - 255;
					}
//					else if (Brightangle >= 260) {
//						Brightangle = 260;
//						MainPanelLight = 255;
//					}
				}
				else {
					if (Brightangle > -20) {
						Brightangle += (leftPanel_mouse_y - leftPanel_mouse_y_cur) / 70;
//						MainPanelLight += (leftPanel_mouse_y - leftPanel_mouse_y_cur) / 100;
						if(Brightangle <= -20){
							Brightangle -20;
						}
//						MainPanelLight = (Brightangle + 20 ) * 255.0 / 280 - 255;
					}
//					else if (Brightangle <= -20) {
//						Brightangle = -20;
//						MainPanelLight = 0;
//						MainPanelLight = (Brightangle + 20 ) * 255.0 / 280 - 255;
//						
//					}
				}
				
				
			}
		}
		
	}
	else if (leftPanel_speed_is_down == 1) {
		leftPanel_speed_is_down = 0;
	}
	
	
	MainPanelLight = fabs((Brightangle + 20 ) * 255.0 / 280 - 255);
	
	if( MainPanelLight >= 255){
		MainPanelLight = 255;
	}
	else if(MainPanelLight <= 0){
		MainPanelLight = 0;
	}
	
	MainPanelLight = -MainPanelLight;
	
	//INBD
	if (GetAsyncKeyState(0x04) & 0x8000) {
		if (leftPanel_speed_is_down == 0) {
			leftPanel_speed_is_down = 1;
			mousepos(&leftPanel_mouse_x, &leftPanel_mouse_y);
			leftPanel_mouse_x_cur = leftPanel_mouse_x;
			leftPanel_mouse_y_cur = leftPanel_mouse_y;
		}
		if (leftPanel_speed_is_down == 1) {
			if ((leftPanel_mouse_x_cur >= leftPanel_x - 1 * Ulength - Lowknob_R1)
				&& (leftPanel_mouse_x_cur <= leftPanel_x - 1 * Ulength + Lowknob_R1)
				&& (leftPanel_mouse_y_cur >= leftPanel_y + 23 * Ulength - Lowknob_R1)
				&& (leftPanel_mouse_y_cur <= leftPanel_y + 23 * Ulength + Lowknob_R1)) {
				
				
				mousepos(&leftPanel_mouse_x, &leftPanel_mouse_y);
				if (leftPanel_mouse_y > leftPanel_mouse_y_cur) {
					if (INBDangle < 255) {
						INBDangle += (leftPanel_mouse_y - leftPanel_mouse_y_cur) / 70;//一共255度；
						if (INBDangle >= 255)
							INBDangle = 255;
					}
				}
				else {
					if (INBDangle > 0) {
						INBDangle += (leftPanel_mouse_y - leftPanel_mouse_y_cur) / 70;
						if (INBDangle <= 0) 
							INBDangle = 0;
					}
				}
			}
		}
		
	}
	else if (leftPanel_speed_is_down == 1) {
		leftPanel_speed_is_down = 0;
	}
	
	//LOWER
	if (GetAsyncKeyState(0x04) & 0x8000) {
		if (leftPanel_speed_is_down == 0) {
			leftPanel_speed_is_down = 1;
			mousepos(&leftPanel_mouse_x, &leftPanel_mouse_y);
			leftPanel_mouse_x_cur = leftPanel_mouse_x;
			leftPanel_mouse_y_cur = leftPanel_mouse_y;
		}
		if (leftPanel_speed_is_down == 1) {
			if ((leftPanel_mouse_x_cur >= leftPanel_x + 32 * Ulength - Lowknob_R1)
				&& (leftPanel_mouse_x_cur <= leftPanel_x + 32 * Ulength + Lowknob_R1)
				&& (leftPanel_mouse_y_cur >= leftPanel_y + 23 * Ulength - Lowknob_R1)
				&& (leftPanel_mouse_y_cur <= leftPanel_y + 23 * Ulength + Lowknob_R1)) {
				
				
				mousepos(&leftPanel_mouse_x, &leftPanel_mouse_y);
				if (leftPanel_mouse_y > leftPanel_mouse_y_cur) {
					if (LOWERangle < 255) {
						LOWERangle += (leftPanel_mouse_y - leftPanel_mouse_y_cur) / 70;//一共255度；
						
					}
					else if (LOWERangle >= 255) {
						LOWERangle = 255;
						
					}
				}
				else {
					if (LOWERangle > 0) {
						LOWERangle += (leftPanel_mouse_y - leftPanel_mouse_y_cur) / 70;
						
					}
					else if (LOWERangle <= 0) {
						LOWERangle = 0;
						
					}
				}
			}
		}
		
	}
	else if (leftPanel_speed_is_down == 1) {
		leftPanel_speed_is_down = 0;
	}
	
	//OUTBD
	if (GetAsyncKeyState(0x04) & 0x8000) {
		if (leftPanel_speed_is_down == 0) {
			leftPanel_speed_is_down = 1;
			mousepos(&leftPanel_mouse_x, &leftPanel_mouse_y);
			leftPanel_mouse_x_cur = leftPanel_mouse_x;
			leftPanel_mouse_y_cur = leftPanel_mouse_y;
		}
		if (leftPanel_speed_is_down == 1) {
			if ((leftPanel_mouse_x_cur >= leftPanel_x - 35 * Ulength - Lowknob_R1)
				&& (leftPanel_mouse_x_cur <= leftPanel_x - 35 * Ulength + Lowknob_R1)
				&& (leftPanel_mouse_y_cur >= leftPanel_y + 23 * Ulength - Lowknob_R1)
				&& (leftPanel_mouse_y_cur <= leftPanel_y + 23 * Ulength + Lowknob_R1)) {
				
				
				mousepos(&leftPanel_mouse_x, &leftPanel_mouse_y);
				if (leftPanel_mouse_y > leftPanel_mouse_y_cur) {
					if (OUTBDangle < 255) {
						OUTBDangle += (leftPanel_mouse_y - leftPanel_mouse_y_cur) / 70;//一共255度；
						if(OUTBDangle > 255)
							OUTBDangle = 255;
					}
//					else if (OUTBDangle >= 255) {
//						OUTBDangle = 255;
//						
//					}
				}
				else {
					if (OUTBDangle > 0) {
						OUTBDangle += (leftPanel_mouse_y - leftPanel_mouse_y_cur) / 70;
						if(OUTBDangle <= 0)
							OUTBDangle = 0;
					}
//					else if (OUTBDangle <= 0) {
//						OUTBDangle = 0;
//						
//					}
				}
			}
		}
		
	}
	else if (leftPanel_speed_is_down == 1) {
		leftPanel_speed_is_down = 0;
	}
	//UPPER
	if (GetAsyncKeyState(0x04) & 0x8000) {
		if (leftPanel_speed_is_down == 0) {
			leftPanel_speed_is_down = 1;
			mousepos(&leftPanel_mouse_x, &leftPanel_mouse_y);
			leftPanel_mouse_x_cur = leftPanel_mouse_x;
			leftPanel_mouse_y_cur = leftPanel_mouse_y;
		}
		if (leftPanel_speed_is_down == 1) {
			if ((leftPanel_mouse_x_cur >= leftPanel_x + 31 * Ulength - Lowknob_R1)
				&& (leftPanel_mouse_x_cur <= leftPanel_x + 31 * Ulength + Lowknob_R1)
				&& (leftPanel_mouse_y_cur >= leftPanel_y - 18 * Ulength - Lowknob_R1)
				&& (leftPanel_mouse_y_cur <= leftPanel_y - 18 * Ulength + Lowknob_R1)) {
				
				
				mousepos(&leftPanel_mouse_x, &leftPanel_mouse_y);
				if (leftPanel_mouse_y > leftPanel_mouse_y_cur) {
					if (UPPERangle < 255) {
						UPPERangle += (leftPanel_mouse_y - leftPanel_mouse_y_cur) / 70;//一共255度；
						if(UPPERangle >=255)
							UPPERangle = 255;
					}
				}
				else {
					if (UPPERangle > 0) {
						UPPERangle += (leftPanel_mouse_y - leftPanel_mouse_y_cur) / 70;
						if(UPPERangle <= 0)
							UPPERangle = 0;
					}
				}
			}
		}
		
	}
	else if (leftPanel_speed_is_down == 1) {
		leftPanel_speed_is_down = 0;
	}
	
	
	
	
	
}




//===================================================================================//



extern double MainpanelDU;
extern double LOWERDU;
extern int MainPanelLight;
extern int MainpanelDU_gear;
extern int LOWERDU_gear;

void draw_TopContral(double topContral_x, double topContral_y, double side) {
	double Ulength = side / 130;
	double knob_R1 = 12 * Ulength;
	double linewidth = Ulength;
	
	
	int x, y;
	mousepos(&x, &y);
	
	ege_enable_aa(false);
	setcolor(EGEARGB(0XFF, 0X1B, 0X1E, 0X21));
	int frame_TopContral = 28;
	ege_point frame_TopContralploy[28] = {
		{topContral_x - 65 * Ulength , topContral_y - 30.5 * Ulength},
		{topContral_x - 65 * Ulength , topContral_y - 31.5* Ulength},
		{topContral_x - 64 * Ulength , topContral_y - 32.5 * Ulength},
		{topContral_x - 63 * Ulength , topContral_y - 32.5 * Ulength},
		
		{topContral_x - 25 * Ulength , topContral_y - 37.5 * Ulength},
		{topContral_x - 25 * Ulength , topContral_y - 37.5 * Ulength},
		{topContral_x - 25 * Ulength , topContral_y - 37.5 * Ulength},
		
		{topContral_x + 63 * Ulength , topContral_y - 37.5 * Ulength},
		{topContral_x + 63 * Ulength , topContral_y - 37.5 * Ulength},
		{topContral_x + 63 * Ulength , topContral_y - 37.5 * Ulength},
		
		{topContral_x + 64 * Ulength , topContral_y - 37.5 * Ulength},
		{topContral_x + 65 * Ulength , topContral_y - 36.5 * Ulength},
		{topContral_x + 65 * Ulength , topContral_y - 35.5 * Ulength},
		
		
		{topContral_x + 65 * Ulength , topContral_y + 30.5 * Ulength},
		{topContral_x + 65 * Ulength , topContral_y + 30.5 * Ulength},
		{topContral_x + 65 * Ulength , topContral_y + 30.5 * Ulength},
		
		
		{topContral_x + 65 * Ulength , topContral_y + 31.5 * Ulength},
		{topContral_x + 64 * Ulength , topContral_y + 32.5 * Ulength},
		{topContral_x + 63 * Ulength , topContral_y + 32.5 * Ulength},
		
		{topContral_x - 63 * Ulength , topContral_y + 32.5 * Ulength},
		{topContral_x - 63 * Ulength , topContral_y + 32.5 * Ulength},
		{topContral_x - 63 * Ulength , topContral_y + 32.5 * Ulength},
		
		{topContral_x - 64 * Ulength , topContral_y + 32.5 * Ulength},
		{topContral_x - 65 * Ulength , topContral_y + 31.5 * Ulength},
		{topContral_x - 65 * Ulength , topContral_y + 30.5 * Ulength},
		
		{topContral_x - 65 * Ulength , topContral_y - 30.5 * Ulength},
		{topContral_x - 65 * Ulength , topContral_y - 30.5 * Ulength},
		{topContral_x - 65 * Ulength , topContral_y - 30.5 * Ulength}
		
	};
	ege_bezier(frame_TopContral, frame_TopContralploy);
	
	setfillcolor(EGEARGB(0XFF, 0X1B, 0X1E, 0X21));
	floodfill(topContral_x - 64 * Ulength, topContral_y - 30.5 * Ulength, EGEARGB(0XFF, 0X1B, 0X1E, 0X21));
	floodfill(topContral_x + 64 * Ulength, topContral_y - 36.5 * Ulength, EGEARGB(0XFF, 0X1B, 0X1E, 0X21));
	floodfill(topContral_x - 64 * Ulength, topContral_y + 30.5 * Ulength, EGEARGB(0XFF, 0X1B, 0X1E, 0X21));
	floodfill(topContral_x + 64 * Ulength, topContral_y + 30.5 * Ulength, EGEARGB(0XFF, 0X1B, 0X1E, 0X21));
	floodfill(topContral_x , topContral_y, EGEARGB(0XFF, 0X1B, 0X1E, 0X21));
	
	ege_enable_aa(true);
	setlinewidth(linewidth / 7 * 4);
	
	setcolor(EGEARGB(0XFF, 0X10, 0X10, 0X10));
	int frame_TopContral_1 = 28;
	ege_point frame_TopContralploy_1[28] = {
		{topContral_x - 65 * Ulength , topContral_y - 30.5 * Ulength},
		{topContral_x - 65 * Ulength , topContral_y - 31.5 * Ulength},
		{topContral_x - 64 * Ulength , topContral_y - 32.5 * Ulength},
		{topContral_x - 63 * Ulength , topContral_y - 32.5 * Ulength},
		
		{topContral_x - 25 * Ulength , topContral_y - 37.5 * Ulength},
		{topContral_x - 25 * Ulength , topContral_y - 37.5 * Ulength},
		{topContral_x - 25 * Ulength , topContral_y - 37.5 * Ulength},
		
		{topContral_x + 63 * Ulength , topContral_y - 37.5 * Ulength},
		{topContral_x + 63 * Ulength , topContral_y - 37.5 * Ulength},
		{topContral_x + 63 * Ulength , topContral_y - 37.5 * Ulength},
		
		{topContral_x + 64 * Ulength , topContral_y - 37.5 * Ulength},
		{topContral_x + 65 * Ulength , topContral_y - 36.5 * Ulength},
		{topContral_x + 65 * Ulength , topContral_y - 35.5 * Ulength},
		
		
		{topContral_x + 65 * Ulength , topContral_y + 30.5 * Ulength},
		{topContral_x + 65 * Ulength , topContral_y + 30.5 * Ulength},
		{topContral_x + 65 * Ulength , topContral_y + 30.5 * Ulength},
		
		
		{topContral_x + 65 * Ulength , topContral_y + 31.5 * Ulength},
		{topContral_x + 64 * Ulength , topContral_y + 32.5 * Ulength},
		{topContral_x + 63 * Ulength , topContral_y + 32.5 * Ulength},
		
		{topContral_x - 63 * Ulength , topContral_y + 32.5 * Ulength},
		{topContral_x - 63 * Ulength , topContral_y + 32.5 * Ulength},
		{topContral_x - 63 * Ulength , topContral_y + 32.5 * Ulength},
		
		{topContral_x - 64 * Ulength , topContral_y + 32.5 * Ulength},
		{topContral_x - 65 * Ulength , topContral_y + 31.5 * Ulength},
		{topContral_x - 65 * Ulength , topContral_y + 30.5 * Ulength},
		
		{topContral_x - 65 * Ulength , topContral_y - 30.5 * Ulength},
		{topContral_x - 65 * Ulength , topContral_y - 30.5 * Ulength},
		{topContral_x - 65 * Ulength , topContral_y - 30.5 * Ulength}
		
	};
	ege_bezier(frame_TopContral_1, frame_TopContralploy_1);
	
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	for (int i = 45; i <= 225; i += 45) {
		ege_line(topContral_x - 30 * Ulength, topContral_y + 2 * Ulength, topContral_x - 30 * Ulength - (knob_R1 + Ulength * 3) * cos(i * PI / 180), topContral_y + 2 * Ulength - (knob_R1 + Ulength * 3) * sin(i * PI / 180));
	}
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	for (int i = 45; i <= 225; i += 45) {
		ege_line(topContral_x - 30 * Ulength, topContral_y + 2 * Ulength, topContral_x - 30 * Ulength - (knob_R1 + Ulength * 3) * cos(i * PI / 180), topContral_y + 2 * Ulength - (knob_R1 + Ulength * 3) * sin(i * PI / 180));
	}
	
	
	setfillcolor(EGEARGB(0XFF, 0X3A, 0X3A, 0X38));
	int MainpanelDUnums = 18;
	ege_point MainpanelDUpoly[18] = {
		{topContral_x - 30 * Ulength - knob_R1 * cos(0 * PI / 180),topContral_y + 2 * Ulength  - knob_R1 * sin(0 * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos(20 * PI / 180),topContral_y + 2 * Ulength  - knob_R1 * sin(20 * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos(40 * PI / 180),topContral_y + 2 * Ulength  - knob_R1 * sin(40 * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos(60 * PI / 180),topContral_y + 2 * Ulength  - knob_R1 * sin(60 * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos(80 * PI / 180),topContral_y + 2 * Ulength  - knob_R1 * sin(80 * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos(100 * PI / 180),topContral_y + 2 * Ulength  - knob_R1 * sin(100 * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos(120 * PI / 180),topContral_y + 2 * Ulength  - knob_R1 * sin(120 * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos(140 * PI / 180),topContral_y + 2 * Ulength  - knob_R1 * sin(140 * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos(160 * PI / 180),topContral_y + 2 * Ulength  - knob_R1 * sin(160 * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos(180 * PI / 180),topContral_y + 2 * Ulength  - knob_R1 * sin(180 * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos(200 * PI / 180),topContral_y + 2 * Ulength  - knob_R1 * sin(200 * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos(220 * PI / 180),topContral_y + 2 * Ulength  - knob_R1 * sin(220 * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos(240 * PI / 180),topContral_y + 2 * Ulength  - knob_R1 * sin(240 * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos(260 * PI / 180),topContral_y + 2 * Ulength  - knob_R1 * sin(260 * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos(280 * PI / 180),topContral_y + 2 * Ulength  - knob_R1 * sin(280 * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos(300 * PI / 180),topContral_y + 2 * Ulength  - knob_R1 * sin(300 * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos(320 * PI / 180),topContral_y + 2 * Ulength  - knob_R1 * sin(320 * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos(340 * PI / 180),topContral_y + 2 * Ulength  - knob_R1 * sin(340 * PI / 180)},
	};
	ege_fillpoly(MainpanelDUnums, MainpanelDUpoly);
	
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	for (int i = 45; i <= 135; i += 45) {
		ege_line(topContral_x + 30 * Ulength, topContral_y + 2 * Ulength, topContral_x + 30 * Ulength - (knob_R1 + Ulength * 3) * cos(i * PI / 180), topContral_y + 2 * Ulength - (knob_R1 + Ulength * 3) * sin(i * PI / 180));
	}
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	for (int i = 45; i <= 135; i += 45) {
		ege_line(topContral_x + 30 * Ulength, topContral_y + 2 * Ulength, topContral_x + 30 * Ulength - (knob_R1 + Ulength * 3) * cos(i * PI / 180), topContral_y + 2 * Ulength - (knob_R1 + Ulength * 3) * sin(i * PI / 180));
	}
	
	
	int LOWERDUnums = 18;
	ege_point LOWERDUploys[18] = {
		{topContral_x + 30 * Ulength - knob_R1 * cos(0 * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin(0 * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos(20 * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin(20 * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos(40 * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin(40 * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos(60 * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin(60 * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos(80 * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin(80 * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos(100 * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin(100 * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos(120 * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin(120 * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos(140 * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin(140 * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos(160 * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin(160 * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos(180 * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin(180 * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos(200 * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin(200 * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos(220 * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin(220 * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos(240 * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin(240 * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos(260 * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin(260 * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos(280 * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin(280 * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos(300 * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin(300 * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos(320 * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin(320 * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos(340 * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin(340 * PI / 180)},
	};
	ege_fillpoly(LOWERDUnums, LOWERDUploys);
	
	
	setfont(Ulength * 6, Ulength * 3, "Bahnschrift");
	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_drawtext("MAIN PANEL DUs" , topContral_x - 29 * Ulength, topContral_y - 26 * Ulength);
	ege_drawtext("LOWER DU", topContral_x + 30 * Ulength, topContral_y - 26 * Ulength);
	ege_drawtext("NORM", topContral_x - 30 * Ulength, topContral_y - 15 * Ulength);
	ege_drawtext("NORM", topContral_x + 31 * Ulength, topContral_y - 15 * Ulength);
	ege_drawtext("OUTBD", topContral_x - 49 * Ulength, topContral_y - 10 * Ulength);
	ege_drawtext("PFD", topContral_x - 48 * Ulength, topContral_y - 5 * Ulength);
	ege_drawtext("ND", topContral_x + 45 * Ulength, topContral_y - 10 * Ulength);
	ege_drawtext("ENG", topContral_x + 15 * Ulength, topContral_y - 10 * Ulength);
	ege_drawtext("PRI", topContral_x + 14 * Ulength, topContral_y - 5 * Ulength);
	ege_drawtext("ENG", topContral_x - 13 * Ulength, topContral_y - 10 * Ulength);
	ege_drawtext("PRI", topContral_x - 14 * Ulength, topContral_y - 5 * Ulength);
	ege_drawtext("PFD", topContral_x - 9 * Ulength, topContral_y + 2.5 * Ulength);
	ege_drawtext("MFD", topContral_x - 14 * Ulength, topContral_y + 15 * Ulength);
	ege_drawtext("INBD", topContral_x - 2 * Ulength, topContral_y + 12 * Ulength);
	ege_line(topContral_x - 30 * Ulength - (knob_R1 + Ulength * 19) * cos(135 * PI / 180), topContral_y + 2 * Ulength - (knob_R1 + Ulength * 19) * sin(135 * PI / 180),
		topContral_x - 30 * Ulength - (knob_R1 + Ulength * 10) * cos(135 * PI / 180), topContral_y + 2 * Ulength - (knob_R1 + Ulength * 10) * sin(135 * PI / 180));
	ege_line(topContral_x - 30 * Ulength - (knob_R1 + Ulength * 19) * cos(225 * PI / 180), topContral_y + 2 * Ulength - (knob_R1 + Ulength * 19) * sin(225 * PI / 180),
		topContral_x - 30 * Ulength - (knob_R1 + Ulength * 10) * cos(225 * PI / 180), topContral_y + 2 * Ulength - (knob_R1 + Ulength * 10) * sin(225 * PI / 180));
	ege_arc(topContral_x - 30 * Ulength - knob_R1 - Ulength * 17, topContral_y + 2 * Ulength - knob_R1 - Ulength * 17
		, (knob_R1 + Ulength * 16) * 2, (knob_R1 + Ulength * 16) * 2, -42, 57);
	ege_arc(topContral_x - 30 * Ulength - knob_R1 - Ulength * 17, topContral_y + 2 * Ulength - knob_R1 - Ulength * 17
		, (knob_R1 + Ulength * 16) * 2, (knob_R1 + Ulength * 16) * 2, 27, 18);
	
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_drawtext("MAIN PANEL DUs", topContral_x - 29 * Ulength, topContral_y - 26 * Ulength);
	ege_drawtext("LOWER DU", topContral_x + 30 * Ulength, topContral_y - 26 * Ulength);
	ege_drawtext("NORM", topContral_x - 30 * Ulength, topContral_y - 15 * Ulength);
	ege_drawtext("NORM", topContral_x + 31 * Ulength, topContral_y - 15 * Ulength);
	ege_drawtext("OUTBD", topContral_x - 49 * Ulength, topContral_y - 10 * Ulength);
	ege_drawtext("PFD", topContral_x - 48 * Ulength, topContral_y - 5 * Ulength);
	ege_drawtext("ND", topContral_x + 45 * Ulength, topContral_y - 10 * Ulength);
	ege_drawtext("ENG", topContral_x + 15 * Ulength, topContral_y - 10 * Ulength);
	ege_drawtext("PRI", topContral_x + 14 * Ulength, topContral_y - 5 * Ulength);
	ege_drawtext("ENG", topContral_x - 13 * Ulength, topContral_y - 10 * Ulength);
	ege_drawtext("PRI", topContral_x - 14 * Ulength, topContral_y - 5 * Ulength);
	ege_drawtext("PFD", topContral_x - 9 * Ulength, topContral_y + 2.5 * Ulength);
	ege_drawtext("MFD", topContral_x - 14 * Ulength, topContral_y + 15 * Ulength);
	ege_drawtext("INBD", topContral_x - 2 * Ulength, topContral_y + 12 * Ulength);
	ege_line(topContral_x - 30 * Ulength - (knob_R1 + Ulength * 19) * cos(135 * PI / 180), topContral_y + 2 * Ulength - (knob_R1 + Ulength * 19) * sin(135 * PI / 180),
		topContral_x - 30 * Ulength - (knob_R1 + Ulength * 10) * cos(135 * PI / 180), topContral_y + 2 * Ulength - (knob_R1 + Ulength * 10) * sin(135 * PI / 180));
	ege_line(topContral_x - 30 * Ulength - (knob_R1 + Ulength * 19) * cos(225 * PI / 180), topContral_y + 2 * Ulength - (knob_R1 + Ulength * 19) * sin(225 * PI / 180),
		topContral_x - 30 * Ulength - (knob_R1 + Ulength * 10) * cos(225 * PI / 180), topContral_y + 2 * Ulength - (knob_R1 + Ulength * 10) * sin(225 * PI / 180));
	ege_arc(topContral_x - 30 * Ulength - knob_R1 - Ulength * 17, topContral_y + 2 * Ulength - knob_R1 - Ulength * 17
		, (knob_R1 + Ulength * 16) * 2, (knob_R1 + Ulength * 16) * 2, -42, 57);
	ege_arc(topContral_x - 30 * Ulength - knob_R1 - Ulength * 17, topContral_y + 2 * Ulength - knob_R1 - Ulength * 17
		, (knob_R1 + Ulength * 16) * 2, (knob_R1 + Ulength * 16) * 2, 27, 18);
	
	
	
	ege_enable_aa(false);
	setcolor(EGEARGB(0XFF, 0X4E, 0X4F, 0X4E));
	setlinewidth(linewidth / 2);
	int MainpanelDUnum = 25;
	ege_point MainpanelDUPloypoints[25] = {
		{topContral_x - 30 * Ulength - knob_R1 * cos((-40 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-40 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos((-20 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-20 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos((-20 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-20 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos((-20 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-20 + MainpanelDU) * PI / 180)},
		
		{topContral_x - 30 * Ulength - (Ulength * 9) * cos((30 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 9) * sin((30 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 9) * cos((30 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 9) * sin((30 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 9) * cos((30 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 9) * sin((30 + MainpanelDU) * PI / 180)},
		
		{topContral_x - 30 * Ulength - (Ulength * 13) * cos((110 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13) * sin((110 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 13) * cos((110 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13) * sin((110 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 13) * cos((110 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13) * sin((110 + MainpanelDU) * PI / 180)},
		
		
		{topContral_x - 30 * Ulength - (Ulength * 13.5) * cos((110 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13.5) * sin((110 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 14.5) * cos((114 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14.5) * sin((114 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 14.5) * cos((120 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14.5) * sin((120 + MainpanelDU) * PI / 180)},
		
		{topContral_x - 30 * Ulength - (Ulength * 14) * cos((167 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14) * sin((167 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 14) * cos((167 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14) * sin((167 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 14) * cos((167 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14) * sin((167 + MainpanelDU) * PI / 180)},
		
		
		{topContral_x - 30 * Ulength - (Ulength * 14) * cos((173 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14) * sin((173 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 13.5) * cos((176 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13.5) * sin((176 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 13) * cos((178 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13) * sin((178 + MainpanelDU) * PI / 180)},
		
		
		{topContral_x - 30 * Ulength - (Ulength * 8.5) * cos((265 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 8.5) * sin((265 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 8.5) * cos((265 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 8.5) * sin((265 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 8.5) * cos((265 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 8.5) * sin((265 + MainpanelDU) * PI / 180)},
		
		{topContral_x - 30 * Ulength - knob_R1 * cos((-40 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-40 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos((-40 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-40 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos((-40 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-40 + MainpanelDU) * PI / 180)},
		
		
	};
	setfillcolor(EGEARGB(0XFF, 0X4E, 0X4F, 0X4E));
	ege_bezier(MainpanelDUnum, MainpanelDUPloypoints);
	floodfill(topContral_x - 30 * Ulength, topContral_y + 2 * Ulength, EGEARGB(0XFF, 0X4E, 0X4F, 0X4E));
	
	
	
	int LOWERDUnum = 25;
	ege_point LOWERDUPloypoints[25] = {
		{topContral_x + 30 * Ulength - knob_R1 * cos((-40 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-40 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos((-20 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-20 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos((-20 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-20 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos((-20 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-20 + LOWERDU) * PI / 180)},
		
		{topContral_x + 30 * Ulength - (Ulength * 9) * cos((30 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 9) * sin((30 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 9) * cos((30 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 9) * sin((30 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 9) * cos((30 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 9) * sin((30 + LOWERDU) * PI / 180)},
		
		{topContral_x + 30 * Ulength - (Ulength * 13) * cos((110 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13) * sin((110 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 13) * cos((110 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13) * sin((110 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 13) * cos((110 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13) * sin((110 + LOWERDU) * PI / 180)},
		
		
		{topContral_x + 30 * Ulength - (Ulength * 13.5) * cos((110 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13.5) * sin((110 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 14.5) * cos((114 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14.5) * sin((114 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 14.5) * cos((120 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14.5) * sin((120 + LOWERDU) * PI / 180)},
		
		{topContral_x + 30 * Ulength - (Ulength * 14) * cos((167 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14) * sin((167 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 14) * cos((167 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14) * sin((167 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 14) * cos((167 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14) * sin((167 + LOWERDU) * PI / 180)},
		
		
		{topContral_x + 30 * Ulength - (Ulength * 14) * cos((173 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14) * sin((173 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 13.5) * cos((176 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13.5) * sin((176 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 13) * cos((178 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13) * sin((178 + LOWERDU) * PI / 180)},
		
		
		{topContral_x + 30 * Ulength - (Ulength * 8.5) * cos((265 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 8.5) * sin((265 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 8.5) * cos((265 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 8.5) * sin((265 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 8.5) * cos((265 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 8.5) * sin((265 + LOWERDU) * PI / 180)},
		
		{topContral_x + 30 * Ulength - knob_R1 * cos((-40 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-40 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos((-40 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-40 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos((-40 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-40 + LOWERDU) * PI / 180)},
		
		
	};
	setfillcolor(EGEARGB(0XFF, 0X4E, 0X4F, 0X4E));
	ege_bezier(LOWERDUnum, LOWERDUPloypoints);
	floodfill(topContral_x + 30 * Ulength, topContral_y + 2 * Ulength, EGEARGB(0XFF, 0X4E, 0X4F, 0X4E));
	
	
	ege_enable_aa(true);
	
	
	setcolor(EGEARGB(0XFF, 0X4E, 0X4F, 0X4E));
	setlinewidth(linewidth / 7 * 4);
	int MainpanelDUnum_1 = 25;
	ege_point MainpanelDUPloypoints_1[25] = {
		{topContral_x - 30 * Ulength - knob_R1 * cos((-40 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-40 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos((-20 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-20 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos((-20 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-20 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos((-20 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-20 + MainpanelDU) * PI / 180)},
		
		{topContral_x - 30 * Ulength - (Ulength * 9) * cos((30 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 9) * sin((30 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 9) * cos((30 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 9) * sin((30 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 9) * cos((30 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 9) * sin((30 + MainpanelDU) * PI / 180)},
		
		{topContral_x - 30 * Ulength - (Ulength * 13) * cos((110 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13) * sin((110 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 13) * cos((110 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13) * sin((110 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 13) * cos((110 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13) * sin((110 + MainpanelDU) * PI / 180)},
		
		
		{topContral_x - 30 * Ulength - (Ulength * 13.5) * cos((110 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13.5) * sin((110 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 14.5) * cos((114 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14.5) * sin((114 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 14.5) * cos((120 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14.5) * sin((120 + MainpanelDU) * PI / 180)},
		
		{topContral_x - 30 * Ulength - (Ulength * 14) * cos((167 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14) * sin((167 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 14) * cos((167 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14) * sin((167 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 14) * cos((167 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14) * sin((167 + MainpanelDU) * PI / 180)},
		
		
		{topContral_x - 30 * Ulength - (Ulength * 14) * cos((173 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14) * sin((173 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 13.5) * cos((176 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13.5) * sin((176 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 13) * cos((178 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13) * sin((178 + MainpanelDU) * PI / 180)},
		
		
		{topContral_x - 30 * Ulength - (Ulength * 8.5) * cos((265 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 8.5) * sin((265 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 8.5) * cos((265 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 8.5) * sin((265 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 8.5) * cos((265 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 8.5) * sin((265 + MainpanelDU) * PI / 180)},
		
		{topContral_x - 30 * Ulength - knob_R1 * cos((-40 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-40 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos((-40 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-40 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - knob_R1 * cos((-40 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-40 + MainpanelDU) * PI / 180)},
		
		
	};
	
	ege_bezier(MainpanelDUnum_1, MainpanelDUPloypoints_1);
	
	
	
	int LOWERDUnum_1 = 25;
	ege_point LOWERDUPloypoints_1[25] = {
		{topContral_x + 30 * Ulength - knob_R1 * cos((-40 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-40 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos((-20 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-20 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos((-20 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-20 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos((-20 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-20 + LOWERDU) * PI / 180)},
		
		{topContral_x + 30 * Ulength - (Ulength * 9) * cos((30 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 9) * sin((30 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 9) * cos((30 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 9) * sin((30 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 9) * cos((30 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 9) * sin((30 + LOWERDU) * PI / 180)},
		
		{topContral_x + 30 * Ulength - (Ulength * 13) * cos((110 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13) * sin((110 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 13) * cos((110 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13) * sin((110 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 13) * cos((110 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13) * sin((110 + LOWERDU) * PI / 180)},
		
		
		{topContral_x + 30 * Ulength - (Ulength * 13.5) * cos((110 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13.5) * sin((110 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 14.5) * cos((114 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14.5) * sin((114 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 14.5) * cos((120 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14.5) * sin((120 + LOWERDU) * PI / 180)},
		
		{topContral_x + 30 * Ulength - (Ulength * 14) * cos((167 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14) * sin((167 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 14) * cos((167 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14) * sin((167 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 14) * cos((167 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14) * sin((167 + LOWERDU) * PI / 180)},
		
		
		{topContral_x + 30 * Ulength - (Ulength * 14) * cos((173 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 14) * sin((173 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 13.5) * cos((176 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13.5) * sin((176 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 13) * cos((178 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13) * sin((178 + LOWERDU) * PI / 180)},
		
		
		{topContral_x + 30 * Ulength - (Ulength * 8.5) * cos((265 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 8.5) * sin((265 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 8.5) * cos((265 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 8.5) * sin((265 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 8.5) * cos((265 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 8.5) * sin((265 + LOWERDU) * PI / 180)},
		
		{topContral_x + 30 * Ulength - knob_R1 * cos((-40 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-40 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos((-40 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-40 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - knob_R1 * cos((-40 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - knob_R1 * sin((-40 + LOWERDU) * PI / 180)},
		
		
	};
	
	ege_bezier(LOWERDUnum_1, LOWERDUPloypoints_1);
	
	
	int LOWERDUnum_2 = 4;
	ege_point LOWERDUPloypoints_2[4] = {
		{topContral_x + 30 * Ulength - (Ulength * 9) * cos((30 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 9) * sin((30 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 13) * cos((110 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13) * sin((110 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 13) * cos((178 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13) * sin((178 + LOWERDU) * PI / 180)},
		{topContral_x + 30 * Ulength - (Ulength * 8.5) * cos((265 + LOWERDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 8.5) * sin((265 + LOWERDU) * PI / 180)}
	};
	
	setfillcolor(EGEARGB(0XFF, 0X36, 0X36, 0X36));
	ege_setpattern_lineargradient(topContral_x + 30 * Ulength - (Ulength * 13) * cos((110 + LOWERDU) * PI / 180), topContral_y + 2 * Ulength - (Ulength * 13) * sin((110 + LOWERDU) * PI / 180), EGEARGB(0XFF, 0X30, 0X30, 0X30),
		topContral_x + 30 * Ulength - (Ulength * 8.5) * cos((265 + LOWERDU) * PI / 180), topContral_y + 2 * Ulength - (Ulength * 8.5) * sin((265 + LOWERDU) * PI / 180), EGEARGB(0XFF, 0X4E, 0X4F, 0X4E));
	ege_fillpoly(LOWERDUnum_2, LOWERDUPloypoints_2);
	ege_setpattern_none();
	
	
	
	
	int MainpanelDUnum_2 = 4;
	ege_point MainpanelDUPloypoints_2[4] = {
		{topContral_x - 30 * Ulength - (Ulength * 9) * cos((30 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 9) * sin((30 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 13) * cos((110 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13) * sin((110 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 13) * cos((178 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 13) * sin((178 + MainpanelDU) * PI / 180)},
		{topContral_x - 30 * Ulength - (Ulength * 8.5) * cos((265 + MainpanelDU) * PI / 180),topContral_y + 2 * Ulength - (Ulength * 8.5) * sin((265 + MainpanelDU) * PI / 180)}
	};
	
	setfillcolor(EGEARGB(0XFF, 0X36, 0X36, 0X36));
	ege_setpattern_lineargradient(topContral_x - 30 * Ulength - (Ulength * 13) * cos((110 + MainpanelDU) * PI / 180), topContral_y + 2 * Ulength - (Ulength * 13) * sin((110 + MainpanelDU) * PI / 180), EGEARGB(0XFF, 0X30, 0X30, 0X30),
		topContral_x - 30 * Ulength - (Ulength * 8.5) * cos((265 + MainpanelDU) * PI / 180), topContral_y + 2 * Ulength - (Ulength * 8.5) * sin((265 + MainpanelDU) * PI / 180), EGEARGB(0XFF, 0X4E, 0X4F, 0X4E));
	ege_fillpoly(MainpanelDUnum_2, MainpanelDUPloypoints_2);
	ege_setpattern_none();
	
	
	
	setcolor(EGEARGB(0X20, 0X8D, 0X8F, 0X8B));
	ege_line(topContral_x - 30 * Ulength - (Ulength * 9) * cos((30 + MainpanelDU) * PI / 180), topContral_y + 2 * Ulength - (Ulength * 9) * sin((30 + MainpanelDU) * PI / 180),
		topContral_x - 30 * Ulength - (Ulength * 8.5) * cos((265 + MainpanelDU) * PI / 180), topContral_y + 2 * Ulength - (Ulength * 8.5) * sin((265 + MainpanelDU) * PI / 180));
	ege_line(topContral_x - 30 * Ulength - (Ulength * 14.5) * cos((120 + MainpanelDU) * PI / 180), topContral_y + 2 * Ulength - (Ulength * 14.5) * sin((120 + MainpanelDU) * PI / 180),
		topContral_x - 30 * Ulength - (Ulength * 14) * cos((167 + MainpanelDU) * PI / 180), topContral_y + 2 * Ulength - (Ulength * 14) * sin((167 + MainpanelDU) * PI / 180));
	
	
	ege_line(topContral_x + 30 * Ulength - (Ulength * 9) * cos((30 + LOWERDU) * PI / 180), topContral_y + 2 * Ulength - (Ulength * 9) * sin((30 + LOWERDU) * PI / 180),
		topContral_x + 30 * Ulength - (Ulength * 8.5) * cos((265 + LOWERDU) * PI / 180), topContral_y + 2 * Ulength - (Ulength * 8.5) * sin((265 + LOWERDU) * PI / 180));
	ege_line(topContral_x + 30 * Ulength - (Ulength * 14.5) * cos((120 + LOWERDU) * PI / 180), topContral_y + 2 * Ulength - (Ulength * 14.5) * sin((120 + LOWERDU) * PI / 180),
		topContral_x + 30 * Ulength - (Ulength * 14) * cos((167 + LOWERDU) * PI / 180), topContral_y + 2 * Ulength - (Ulength * 14) * sin((167 + LOWERDU) * PI / 180));
	
	
	
	
	
	setcolor(EGEARGB(0XFF, 0X20, 0X20, 0X20));
	setlinewidth(linewidth / 7 * 4);
	
	ege_line(topContral_x + 30 * Ulength - (Ulength * 2) * cos((110 + LOWERDU) * PI / 180), topContral_y + 2 * Ulength - (Ulength * 2) * sin((110 + LOWERDU) * PI / 180),
		topContral_x + 30 * Ulength - (Ulength * 2) * cos((175 + LOWERDU) * PI / 180), topContral_y + 2 * Ulength - (Ulength * 2) * sin((175 + LOWERDU) * PI / 180));
	ege_line(topContral_x + 30 * Ulength - (Ulength * 2) * cos((110 + LOWERDU) * PI / 180), topContral_y + 2 * Ulength - (Ulength * 2) * sin((110 + LOWERDU) * PI / 180),
		topContral_x + 30 * Ulength - knob_R1 * cos((-25 + LOWERDU) * PI / 180), topContral_y + 2 * Ulength - knob_R1 * sin((-25 + LOWERDU) * PI / 180));
	ege_line(topContral_x + 30 * Ulength - (Ulength * 2) * cos((175 + LOWERDU) * PI / 180), topContral_y + 2 * Ulength - (Ulength * 2) * sin((175 + LOWERDU) * PI / 180),
		topContral_x + 30 * Ulength - knob_R1 * cos((-35 + LOWERDU) * PI / 180), topContral_y + 2 * Ulength - knob_R1 * sin((-35 + LOWERDU) * PI / 180));
	
	
	
	ege_line(topContral_x - 30 * Ulength - (Ulength * 2) * cos((110 + MainpanelDU) * PI / 180), topContral_y + 2 * Ulength - (Ulength * 2) * sin((110 + MainpanelDU) * PI / 180),
		topContral_x - 30 * Ulength - (Ulength * 2) * cos((175 + MainpanelDU) * PI / 180), topContral_y + 2 * Ulength - (Ulength * 2) * sin((175 + MainpanelDU) * PI / 180));
	ege_line(topContral_x - 30 * Ulength - (Ulength * 2) * cos((110 + MainpanelDU) * PI / 180), topContral_y + 2 * Ulength - (Ulength * 2) * sin((110 + MainpanelDU) * PI / 180),
		topContral_x - 30 * Ulength - knob_R1 * cos((-25 + MainpanelDU) * PI / 180), topContral_y + 2 * Ulength - knob_R1 * sin((-25 + MainpanelDU) * PI / 180));
	ege_line(topContral_x - 30 * Ulength - (Ulength * 2) * cos((175 + MainpanelDU) * PI / 180), topContral_y + 2 * Ulength - (Ulength * 2) * sin((175 + MainpanelDU) * PI / 180),
		topContral_x - 30 * Ulength - knob_R1 * cos((-35 + MainpanelDU) * PI / 180), topContral_y + 2 * Ulength - knob_R1 * sin((-35 + MainpanelDU) * PI / 180));
	
	setcolor(EGEARGB(0XFF, 0X40, 0X41, 0X42));
	setlinewidth(linewidth * 1.5);
	
	ege_line(topContral_x + 30 * Ulength - (Ulength * 1.5) * cos((142 + LOWERDU) * PI / 180), topContral_y + 2 * Ulength - (Ulength * 1.5) * sin((142 + LOWERDU) * PI / 180),
		topContral_x + 30 * Ulength - knob_R1 * cos((-30 + LOWERDU) * PI / 180), topContral_y + 2 * Ulength - knob_R1 * sin((-30 + LOWERDU) * PI / 180));
	
	
	ege_line(topContral_x - 30 * Ulength - (Ulength * 1.5) * cos((142 + MainpanelDU) * PI / 180), topContral_y + 2 * Ulength - (Ulength * 1.5) * sin((142 + MainpanelDU) * PI / 180),
		topContral_x - 30 * Ulength - knob_R1 * cos((-30 + MainpanelDU) * PI / 180), topContral_y + 2 * Ulength - knob_R1 * sin((-30 + MainpanelDU) * PI / 180));
	
	setlinewidth(linewidth / 7 * 4);
	
	
	
	
	
	if (x > topContral_x - 30 * Ulength - knob_R1 && x< topContral_x - 30 * Ulength  && y>topContral_y + 2 * Ulength - knob_R1 && y < topContral_y + 2 * Ulength + knob_R1) {
		
		if (GetAsyncKeyState(0x02) & 0x0001) {
			
			if (MainpanelDU > 75&& MainpanelDU_gear>0) {
				MainpanelDU -= 45;
				MainpanelDU_gear--;
			}
			else {
				MainpanelDU_gear = 0;
				MainpanelDU = 75;
			}
			
		}
	}
	if (x < topContral_x - 30 * Ulength + knob_R1 && x> topContral_x - 30 * Ulength && y>topContral_y + 2 * Ulength - knob_R1 && y < topContral_y + 2 * Ulength + knob_R1) {
		
		if (GetAsyncKeyState(0x02) & 0x0001) {
			
			if (MainpanelDU < 255 && MainpanelDU_gear < 4) {
				MainpanelDU += 45;
				MainpanelDU_gear++;
			}
			else {
				MainpanelDU_gear = 4;
				MainpanelDU = 255;
			}
			
		}
	}
	
	if (x > topContral_x + 30 * Ulength - knob_R1 && x< topContral_x + 30 * Ulength && y>topContral_y + 2 * Ulength - knob_R1 && y < topContral_y + 2 * Ulength + knob_R1) {
		
		if (GetAsyncKeyState(0x02) & 0x0001) {
			
			if (LOWERDU > 75 && LOWERDU_gear > 0) {
				LOWERDU -= 45;
				LOWERDU_gear--;
			}
			else {
				LOWERDU_gear = 0;
				LOWERDU = 75;
			}
			
		}
	}
	if (x < topContral_x + 30 * Ulength + knob_R1 && x> topContral_x + 30 * Ulength && y > topContral_y + 2 * Ulength - knob_R1 && y < topContral_y + 2 * Ulength + knob_R1) {
		
		if (GetAsyncKeyState(0x02) & 0x0001) {
			
			if (LOWERDU < 165 && LOWERDU_gear < 2) {
				LOWERDU += 45;
				LOWERDU_gear++;
			}
			else {
				LOWERDU_gear = 2;
				LOWERDU = 165;
			}
			
		}
	}
	
	
}
