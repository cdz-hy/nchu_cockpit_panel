#include<graphics.h>
#include <stdio.h>
#include <math.h>







extern double backGroundLight ;
extern double AFDSFLOODLight ;
extern int MainPanelLight;
int rightPanel_mouse_x = 0, rightPanel_mouse_y = 0;
int rightPanel_speed_is_down = 0;
int rightPanel_mouse_y_cur = 0, rightPanel_mouse_x_cur = 0;

void draw_Light_contral_1(double rightPanel_x, double rightPanel_y, double side) {
	double Ulength = side / 130;
	double Linewidth = Ulength;
	double righttop_R1 = Ulength * 12;






	int x, y;
	mousepos(&x, &y);

	ege_enable_aa(false);


	setcolor(EGEARGB(0XFF, 0X16, 0X18, 0X1C));
	int Framenum = 61;
	ege_point FramePloypoints[61] = {
		{rightPanel_x - Ulength * 57,rightPanel_y - Ulength * 41},
		{rightPanel_x - Ulength * 57,rightPanel_y - Ulength * 41.5},
		{rightPanel_x - Ulength * 56.5,rightPanel_y - Ulength * 42},
		{rightPanel_x - Ulength * 56,rightPanel_y - Ulength * 42},

		{rightPanel_x + Ulength * 56,rightPanel_y - Ulength * 42},
		{rightPanel_x + Ulength * 56,rightPanel_y - Ulength * 42},
		{rightPanel_x + Ulength * 56,rightPanel_y - Ulength * 42},

		{rightPanel_x + Ulength * 56.5,rightPanel_y - Ulength * 42},
		{rightPanel_x + Ulength * 57,rightPanel_y - Ulength * 41.5},
		{rightPanel_x + Ulength * 57,rightPanel_y - Ulength * 41},

		{rightPanel_x + Ulength * 57,rightPanel_y - Ulength * 31},
		{rightPanel_x + Ulength * 57,rightPanel_y - Ulength * 31},
		{rightPanel_x + Ulength * 57,rightPanel_y - Ulength * 31},

		{rightPanel_x + Ulength * 57,rightPanel_y - Ulength * 27},
		{rightPanel_x + Ulength * 60.5,rightPanel_y - Ulength * 25},
		{rightPanel_x + Ulength * 64,rightPanel_y - Ulength * 25},

		{rightPanel_x + Ulength * 64.5,rightPanel_y - Ulength * 25},
		{rightPanel_x + Ulength * 65,rightPanel_y - Ulength * 24.5},
		{rightPanel_x + Ulength * 65,rightPanel_y - Ulength * 24},

		{rightPanel_x + Ulength * 65,rightPanel_y + Ulength * 24},
		{rightPanel_x + Ulength * 65,rightPanel_y + Ulength * 24},
		{rightPanel_x + Ulength * 65,rightPanel_y + Ulength * 24},

		{rightPanel_x + Ulength * 65,rightPanel_y + Ulength * 24.5},
		{rightPanel_x + Ulength * 64.5,rightPanel_y + Ulength * 25},
		{rightPanel_x + Ulength * 64,rightPanel_y + Ulength * 25},

		{rightPanel_x + Ulength * 60.5,rightPanel_y + Ulength * 25},
		{rightPanel_x + Ulength * 57,rightPanel_y + Ulength * 27},
		{rightPanel_x + Ulength * 57,rightPanel_y + Ulength * 31},

		{rightPanel_x + Ulength * 57,rightPanel_y + Ulength * 41},
		{rightPanel_x + Ulength * 57,rightPanel_y + Ulength * 41},
		{rightPanel_x + Ulength * 57,rightPanel_y + Ulength * 41},

		{rightPanel_x + Ulength * 57,rightPanel_y + Ulength * 41.5},
		{rightPanel_x + Ulength * 56.5,rightPanel_y + Ulength * 42},
		{rightPanel_x + Ulength * 56,rightPanel_y + Ulength * 42},

		{rightPanel_x - Ulength * 56,rightPanel_y + Ulength * 42},
		{rightPanel_x - Ulength * 56,rightPanel_y + Ulength * 42},
		{rightPanel_x - Ulength * 56,rightPanel_y + Ulength * 42},

		{rightPanel_x - Ulength * 56.5,rightPanel_y + Ulength * 42},
		{rightPanel_x - Ulength * 57,rightPanel_y + Ulength * 41.5},
		{rightPanel_x - Ulength * 57,rightPanel_y + Ulength * 41},

		{rightPanel_x - Ulength * 57,rightPanel_y + Ulength * 31},
		{rightPanel_x - Ulength * 57,rightPanel_y + Ulength * 31},
		{rightPanel_x - Ulength * 57,rightPanel_y + Ulength * 31},

		{rightPanel_x - Ulength * 57,rightPanel_y + Ulength * 27},
		{rightPanel_x - Ulength * 60.5,rightPanel_y + Ulength * 25},
		{rightPanel_x - Ulength * 64,rightPanel_y + Ulength * 25},

		{rightPanel_x - Ulength * 64.5,rightPanel_y + Ulength * 25},
		{rightPanel_x - Ulength * 65,rightPanel_y + Ulength * 24.5},
		{rightPanel_x - Ulength * 65,rightPanel_y + Ulength * 24},

		{rightPanel_x - Ulength * 65,rightPanel_y - Ulength * 24},
		{rightPanel_x - Ulength * 65,rightPanel_y - Ulength * 24},
		{rightPanel_x - Ulength * 65,rightPanel_y - Ulength * 24},

		{rightPanel_x - Ulength * 65,rightPanel_y - Ulength * 24.5},
		{rightPanel_x - Ulength * 64.5,rightPanel_y - Ulength * 25},
		{rightPanel_x - Ulength * 64,rightPanel_y - Ulength * 25},

		{rightPanel_x - Ulength * 60.5,rightPanel_y - Ulength * 25},
		{rightPanel_x - Ulength * 57,rightPanel_y - Ulength * 27},
		{rightPanel_x - Ulength * 57,rightPanel_y - Ulength * 31},

		{rightPanel_x - Ulength * 57,rightPanel_y - Ulength * 41},
		{rightPanel_x - Ulength * 57,rightPanel_y - Ulength * 41},
		{rightPanel_x - Ulength * 57,rightPanel_y - Ulength * 41},


	};
	ege_bezier(Framenum, FramePloypoints);
	setfillcolor(EGEARGB(0XFF, 0X16, 0X18, 0X1C));
	floodfill(rightPanel_x, rightPanel_y, EGEARGB(0XFF, 0X16, 0X18, 0X1C));

	ege_enable_aa(true);
	setcolor(EGEARGB(0XFF, 0X16, 0X18, 0X1C));
	setlinewidth(Linewidth / 7 * 4);
	int Framenum_1 = 61;
	ege_point FramePloypoints_1[61] = {
		{rightPanel_x - Ulength * 57,rightPanel_y - Ulength * 41},
		{rightPanel_x - Ulength * 57,rightPanel_y - Ulength * 41.5},
		{rightPanel_x - Ulength * 56.5,rightPanel_y - Ulength * 42},
		{rightPanel_x - Ulength * 56,rightPanel_y - Ulength * 42},

		{rightPanel_x + Ulength * 56,rightPanel_y - Ulength * 42},
		{rightPanel_x + Ulength * 56,rightPanel_y - Ulength * 42},
		{rightPanel_x + Ulength * 56,rightPanel_y - Ulength * 42},

		{rightPanel_x + Ulength * 56.5,rightPanel_y - Ulength * 42},
		{rightPanel_x + Ulength * 57,rightPanel_y - Ulength * 41.5},
		{rightPanel_x + Ulength * 57,rightPanel_y - Ulength * 41},

		{rightPanel_x + Ulength * 57,rightPanel_y - Ulength * 31},
		{rightPanel_x + Ulength * 57,rightPanel_y - Ulength * 31},
		{rightPanel_x + Ulength * 57,rightPanel_y - Ulength * 31},

		{rightPanel_x + Ulength * 57,rightPanel_y - Ulength * 27},
		{rightPanel_x + Ulength * 60.5,rightPanel_y - Ulength * 25},
		{rightPanel_x + Ulength * 64,rightPanel_y - Ulength * 25},

		{rightPanel_x + Ulength * 64.5,rightPanel_y - Ulength * 25},
		{rightPanel_x + Ulength * 65,rightPanel_y - Ulength * 24.5},
		{rightPanel_x + Ulength * 65,rightPanel_y - Ulength * 24},

		{rightPanel_x + Ulength * 65,rightPanel_y + Ulength * 24},
		{rightPanel_x + Ulength * 65,rightPanel_y + Ulength * 24},
		{rightPanel_x + Ulength * 65,rightPanel_y + Ulength * 24},

		{rightPanel_x + Ulength * 65,rightPanel_y + Ulength * 24.5},
		{rightPanel_x + Ulength * 64.5,rightPanel_y + Ulength * 25},
		{rightPanel_x + Ulength * 64,rightPanel_y + Ulength * 25},

		{rightPanel_x + Ulength * 60.5,rightPanel_y + Ulength * 25},
		{rightPanel_x + Ulength * 57,rightPanel_y + Ulength * 27},
		{rightPanel_x + Ulength * 57,rightPanel_y + Ulength * 31},

		{rightPanel_x + Ulength * 57,rightPanel_y + Ulength * 41},
		{rightPanel_x + Ulength * 57,rightPanel_y + Ulength * 41},
		{rightPanel_x + Ulength * 57,rightPanel_y + Ulength * 41},

		{rightPanel_x + Ulength * 57,rightPanel_y + Ulength * 41.5},
		{rightPanel_x + Ulength * 56.5,rightPanel_y + Ulength * 42},
		{rightPanel_x + Ulength * 56,rightPanel_y + Ulength * 42},

		{rightPanel_x - Ulength * 56,rightPanel_y + Ulength * 42},
		{rightPanel_x - Ulength * 56,rightPanel_y + Ulength * 42},
		{rightPanel_x - Ulength * 56,rightPanel_y + Ulength * 42},

		{rightPanel_x - Ulength * 56.5,rightPanel_y + Ulength * 42},
		{rightPanel_x - Ulength * 57,rightPanel_y + Ulength * 41.5},
		{rightPanel_x - Ulength * 57,rightPanel_y + Ulength * 41},

		{rightPanel_x - Ulength * 57,rightPanel_y + Ulength * 31},
		{rightPanel_x - Ulength * 57,rightPanel_y + Ulength * 31},
		{rightPanel_x - Ulength * 57,rightPanel_y + Ulength * 31},

		{rightPanel_x - Ulength * 57,rightPanel_y + Ulength * 27},
		{rightPanel_x - Ulength * 60.5,rightPanel_y + Ulength * 25},
		{rightPanel_x - Ulength * 64,rightPanel_y + Ulength * 25},

		{rightPanel_x - Ulength * 64.5,rightPanel_y + Ulength * 25},
		{rightPanel_x - Ulength * 65,rightPanel_y + Ulength * 24.5},
		{rightPanel_x - Ulength * 65,rightPanel_y + Ulength * 24},

		{rightPanel_x - Ulength * 65,rightPanel_y - Ulength * 24},
		{rightPanel_x - Ulength * 65,rightPanel_y - Ulength * 24},
		{rightPanel_x - Ulength * 65,rightPanel_y - Ulength * 24},

		{rightPanel_x - Ulength * 65,rightPanel_y - Ulength * 24.5},
		{rightPanel_x - Ulength * 64.5,rightPanel_y - Ulength * 25},
		{rightPanel_x - Ulength * 64,rightPanel_y - Ulength * 25},

		{rightPanel_x - Ulength * 60.5,rightPanel_y - Ulength * 25},
		{rightPanel_x - Ulength * 57,rightPanel_y - Ulength * 27},
		{rightPanel_x - Ulength * 57,rightPanel_y - Ulength * 31},

		{rightPanel_x - Ulength * 57,rightPanel_y - Ulength * 41},
		{rightPanel_x - Ulength * 57,rightPanel_y - Ulength * 41},
		{rightPanel_x - Ulength * 57,rightPanel_y - Ulength * 41},


	};
	ege_bezier(Framenum_1, FramePloypoints_1);




	setfillcolor(EGEARGB(0XFF, 0X3A, 0X3A, 0X38));
	int MainpanelLightcontralNums = 18;
	ege_point MainpanelLightcontralPloy[18] = {
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos(0 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(0 * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos(20 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(20 * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos(40 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(40 * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos(60 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(60 * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos(80 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(80 * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos(100 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(100 * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos(120 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(120 * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos(140 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(140 * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos(160 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(160 * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos(180 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(180 * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos(200 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(200 * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos(220 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(220 * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos(240 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(240 * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos(260 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(260 * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos(280 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(280 * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos(300 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(300 * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos(320 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(320 * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos(340 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(340 * PI / 180)},
	};
	ege_fillpoly(MainpanelLightcontralNums, MainpanelLightcontralPloy);

	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_arc(rightPanel_x + Ulength * 33 - righttop_R1, rightPanel_y - Ulength * 21 - righttop_R1, Ulength * 28, Ulength * 28, 180, 60);
	ege_arc(rightPanel_x + Ulength * 33 - righttop_R1, rightPanel_y - Ulength * 21 - righttop_R1, Ulength * 28, Ulength * 28, 305, 55);
	LOGFONTW font;
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font);
	font.lfEscapement = 300;
	font.lfWeight = 500;
	setfont(&font);
	setbkmode(1);


	ege_drawtext("B", rightPanel_x + Ulength * 42 - righttop_R1, rightPanel_y - Ulength * 18.8 - righttop_R1);
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_drawtext("B", rightPanel_x + Ulength * 42 - righttop_R1, rightPanel_y - Ulength * 18.8 - righttop_R1);

	LOGFONTW font1;
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font1);
	font1.lfEscapement = 200;
	font1.lfWeight = 500;
	setfont(&font1);
	setbkmode(1);

	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_drawtext("R", rightPanel_x + Ulength * 45 - righttop_R1, rightPanel_y - Ulength * 19.8 - righttop_R1);
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_drawtext("R", rightPanel_x + Ulength * 45 - righttop_R1, rightPanel_y - Ulength * 19.8 - righttop_R1);


	LOGFONTW font2;
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font2);
	font2.lfEscapement = 100;
	font2.lfWeight = 500;
	setfont(&font2);
	setbkmode(1);

	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_drawtext("I", rightPanel_x + Ulength * 47 - righttop_R1, rightPanel_y - Ulength * 20 - righttop_R1);
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_drawtext("I", rightPanel_x + Ulength * 47 - righttop_R1, rightPanel_y - Ulength * 20 - righttop_R1);

	LOGFONTW font3;
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font3);
	font3.lfEscapement = 0;
	font3.lfWeight = 500;
	setfont(&font3);
	setbkmode(1);

	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_drawtext("G", rightPanel_x + Ulength * 49 - righttop_R1, rightPanel_y - Ulength * 20.5 - righttop_R1);
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_drawtext("G", rightPanel_x + Ulength * 49 - righttop_R1, rightPanel_y - Ulength * 20.5 - righttop_R1);

	LOGFONTW font4;
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font4);
	font4.lfEscapement = -200;
	font4.lfWeight = 500;
	setfont(&font4);
	setbkmode(1);

	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_drawtext("H", rightPanel_x + Ulength * 52 - righttop_R1, rightPanel_y - Ulength * 19.2 - righttop_R1);
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_drawtext("H", rightPanel_x + Ulength * 52 - righttop_R1, rightPanel_y - Ulength * 19.2 - righttop_R1);
	LOGFONTW font5;
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font5);
	font5.lfEscapement = -400;
	font5.lfWeight = 500;
	setfont(&font5);
	setbkmode(1);

	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_drawtext("T", rightPanel_x + Ulength * 53.9 - righttop_R1, rightPanel_y - Ulength * 17.9 - righttop_R1);
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_drawtext("T", rightPanel_x + Ulength * 53.9 - righttop_R1, rightPanel_y - Ulength * 17.9 - righttop_R1);




	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_arc(rightPanel_x + Ulength * 33 - righttop_R1, rightPanel_y - Ulength * 21 - righttop_R1, Ulength * 28, Ulength * 28, 180, 60);
	ege_arc(rightPanel_x + Ulength * 33 - righttop_R1, rightPanel_y - Ulength * 21 - righttop_R1, Ulength * 28, Ulength * 28, 305, 55);




	setfillcolor(EGEARGB(0XFF, 0X3A, 0X3A, 0X38));
	int MainpanelLightcontralNums_1 = 18;
	ege_point MainpanelLightcontralPloy_1[18] = {
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos(0 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(0 * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos(20 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(20 * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos(40 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(40 * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos(60 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(60 * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos(80 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(80 * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos(100 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(100 * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos(120 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(120 * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos(140 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(140 * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos(160 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(160 * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos(180 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(180 * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos(200 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(200 * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos(220 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(220 * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos(240 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(240 * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos(260 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(260 * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos(280 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(280 * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos(300 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(300 * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos(320 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(320 * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos(340 * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin(340 * PI / 180)},
	};
	ege_fillpoly(MainpanelLightcontralNums_1, MainpanelLightcontralPloy_1);

	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_arc(rightPanel_x - Ulength * 37 - righttop_R1, rightPanel_y - Ulength * 21 - righttop_R1, Ulength * 28, Ulength * 28, 180, 60);
	ege_arc(rightPanel_x - Ulength * 37 - righttop_R1, rightPanel_y - Ulength * 21 - righttop_R1, Ulength * 28, Ulength * 28, 305, 55);
	LOGFONTW font6;
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font6);
	font6.lfEscapement = 300;
	font6.lfWeight = 500;
	setfont(&font6);
	setbkmode(1);


	ege_drawtext("B", rightPanel_x - Ulength * 28 - righttop_R1, rightPanel_y - Ulength * 18.8 - righttop_R1);
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_drawtext("B", rightPanel_x - Ulength * 28 - righttop_R1, rightPanel_y - Ulength * 18.8 - righttop_R1);

	LOGFONTW font7;
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font7);
	font7.lfEscapement = 200;
	font7.lfWeight = 500;
	setfont(&font7);
	setbkmode(1);

	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_drawtext("R", rightPanel_x - Ulength * 25 - righttop_R1, rightPanel_y - Ulength * 19.8 - righttop_R1);
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_drawtext("R", rightPanel_x - Ulength * 25 - righttop_R1, rightPanel_y - Ulength * 19.8 - righttop_R1);


	LOGFONTW font8;
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font8);
	font8.lfEscapement = 100;
	font8.lfWeight = 500;
	setfont(&font8);
	setbkmode(1);

	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_drawtext("I", rightPanel_x - Ulength * 23 - righttop_R1, rightPanel_y - Ulength * 20 - righttop_R1);
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_drawtext("I", rightPanel_x - Ulength * 23 - righttop_R1, rightPanel_y - Ulength * 20 - righttop_R1);

	LOGFONTW font9;
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font9);
	font9.lfEscapement = 0;
	font9.lfWeight = 500;
	setfont(&font9);
	setbkmode(1);

	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_drawtext("G", rightPanel_x - Ulength * 21 - righttop_R1, rightPanel_y - Ulength * 20.5 - righttop_R1);
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_drawtext("G", rightPanel_x - Ulength * 21 - righttop_R1, rightPanel_y - Ulength * 20.5 - righttop_R1);

	LOGFONTW font10;
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font10);
	font10.lfEscapement = -200;
	font10.lfWeight = 500;
	setfont(&font10);
	setbkmode(1);

	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_drawtext("H", rightPanel_x - Ulength * 18 - righttop_R1, rightPanel_y - Ulength * 19.2 - righttop_R1);
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_drawtext("H", rightPanel_x - Ulength * 18 - righttop_R1, rightPanel_y - Ulength * 19.2 - righttop_R1);
	LOGFONTW font11;
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font11);
	font11.lfEscapement = -400;
	font11.lfWeight = 500;
	setfont(&font11);
	setbkmode(1);

	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_drawtext("T", rightPanel_x - Ulength * 16.1 - righttop_R1, rightPanel_y - Ulength * 17.9 - righttop_R1);
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_drawtext("T", rightPanel_x - Ulength * 16.1 - righttop_R1, rightPanel_y - Ulength * 17.9 - righttop_R1);




	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_arc(rightPanel_x - Ulength * 37 - righttop_R1, rightPanel_y - Ulength * 21 - righttop_R1, Ulength * 28, Ulength * 28, 180, 60);
	ege_arc(rightPanel_x - Ulength * 37 - righttop_R1, rightPanel_y - Ulength * 21 - righttop_R1, Ulength * 28, Ulength * 28, 305, 55);


	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	setlinewidth(Linewidth / 7 * 4);
	setfont(Ulength * 6, Ulength * 2.5, "Bahnschrift");

	ege_line(rightPanel_x - Ulength * 35 - righttop_R1 * cos(-50 * PI / 180), rightPanel_y - Ulength * 18 - righttop_R1 * sin(-50 * PI / 180),
		rightPanel_x - Ulength * 35 - (righttop_R1 + Ulength * 3) * cos((-50) * PI / 180), rightPanel_y - Ulength * 18 - (righttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_line(rightPanel_x - Ulength * 35 - (righttop_R1 + Ulength * 3) * cos((-50) * PI / 180), rightPanel_y - Ulength * 18 - (righttop_R1 + Ulength * 3) * sin(-50 * PI / 180),
		rightPanel_x - Ulength * 38 - (righttop_R1 + Ulength * 3) * cos((-50) * PI / 180), rightPanel_y - Ulength * 18 - (righttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("OFF", rightPanel_x - Ulength * 43 - (righttop_R1 + Ulength * 3) * cos((-50) * PI / 180), rightPanel_y - Ulength * 17 - (righttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("BACKGROUND", rightPanel_x - Ulength * 26 - (righttop_R1 + Ulength * 3) * cos((-50) * PI / 180), rightPanel_y - Ulength * 50 - (righttop_R1 + Ulength * 3) * sin(-50 * PI / 180));



	ege_line(rightPanel_x + Ulength * 35 - righttop_R1 * cos(-50 * PI / 180), rightPanel_y - Ulength * 18 - righttop_R1 * sin(-50 * PI / 180),
		rightPanel_x + Ulength * 35 - (righttop_R1 + Ulength * 3) * cos((-50) * PI / 180), rightPanel_y - Ulength * 18 - (righttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_line(rightPanel_x + Ulength * 35 - (righttop_R1 + Ulength * 3) * cos((-50) * PI / 180), rightPanel_y - Ulength * 18 - (righttop_R1 + Ulength * 3) * sin(-50 * PI / 180),
		rightPanel_x + Ulength * 32 - (righttop_R1 + Ulength * 3) * cos((-50) * PI / 180), rightPanel_y - Ulength * 18 - (righttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("OFF", rightPanel_x + Ulength * 27 - (righttop_R1 + Ulength * 3) * cos((-50) * PI / 180), rightPanel_y - Ulength * 17 - (righttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("AFDS FLOOD", rightPanel_x + Ulength * 46 - (righttop_R1 + Ulength * 3) * cos((-50) * PI / 180), rightPanel_y - Ulength * 50 - (righttop_R1 + Ulength * 3) * sin(-50 * PI / 180));




	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));

	setlinewidth(Linewidth / 7 * 4);
	setfont(Ulength * 6, Ulength * 2.5, "Bahnschrift");
	ege_line(rightPanel_x - Ulength * 35 - righttop_R1 * cos(-50 * PI / 180), rightPanel_y - Ulength * 18 - righttop_R1 * sin(-50 * PI / 180),
		rightPanel_x - Ulength * 35 - (righttop_R1 + Ulength * 3) * cos((-50) * PI / 180), rightPanel_y - Ulength * 18 - (righttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_line(rightPanel_x - Ulength * 35 - (righttop_R1 + Ulength * 3) * cos((-50) * PI / 180), rightPanel_y - Ulength * 18 - (righttop_R1 + Ulength * 3) * sin(-50 * PI / 180),
		rightPanel_x - Ulength * 38 - (righttop_R1 + Ulength * 3) * cos((-50) * PI / 180), rightPanel_y - Ulength * 18 - (righttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("OFF", rightPanel_x - Ulength * 43 - (righttop_R1 + Ulength * 3) * cos((-50) * PI / 180), rightPanel_y - Ulength * 17 - (righttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("BACKGROUND", rightPanel_x - Ulength * 26 - (righttop_R1 + Ulength * 3) * cos((-50) * PI / 180), rightPanel_y - Ulength * 50 - (righttop_R1 + Ulength * 3) * sin(-50 * PI / 180));



	ege_line(rightPanel_x + Ulength * 35 - righttop_R1 * cos(-50 * PI / 180), rightPanel_y - Ulength * 18 - righttop_R1 * sin(-50 * PI / 180),
		rightPanel_x + Ulength * 35 - (righttop_R1 + Ulength * 3) * cos((-50) * PI / 180), rightPanel_y - Ulength * 18 - (righttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_line(rightPanel_x + Ulength * 35 - (righttop_R1 + Ulength * 3) * cos((-50) * PI / 180), rightPanel_y - Ulength * 18 - (righttop_R1 + Ulength * 3) * sin(-50 * PI / 180),
		rightPanel_x + Ulength * 32 - (righttop_R1 + Ulength * 3) * cos((-50) * PI / 180), rightPanel_y - Ulength * 18 - (righttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("OFF", rightPanel_x + Ulength * 27 - (righttop_R1 + Ulength * 3) * cos((-50) * PI / 180), rightPanel_y - Ulength * 17 - (righttop_R1 + Ulength * 3) * sin(-50 * PI / 180));
	ege_drawtext("AFDS FLOOD", rightPanel_x + Ulength * 46 - (righttop_R1 + Ulength * 3) * cos((-50) * PI / 180), rightPanel_y - Ulength * 50 - (righttop_R1 + Ulength * 3) * sin(-50 * PI / 180));






	ege_enable_aa(false);
	setcolor(EGEARGB(0XFF, 0X4E, 0X4F, 0X4E));
	setlinewidth(Linewidth / 2);
	int backGroundLightnum = 25;
	ege_point backGroundLightPloypoints[25] = {
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos((-40 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-40 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos((-20 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-20 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos((-20 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-20 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos((-20 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-20 + backGroundLight) * PI / 180)},

		{rightPanel_x - Ulength * 35 - (Ulength * 9) * cos((30 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 9) * cos((30 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 9) * cos((30 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + backGroundLight) * PI / 180)},

		{rightPanel_x - Ulength * 35 - (Ulength * 13) * cos((110 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 13) * cos((110 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 13) * cos((110 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + backGroundLight) * PI / 180)},


		{rightPanel_x - Ulength * 35 - (Ulength * 13.5) * cos((110 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13.5) * sin((110 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 14.5) * cos((114 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14.5) * sin((114 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 14.5) * cos((120 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14.5) * sin((120 + backGroundLight) * PI / 180)},

		{rightPanel_x - Ulength * 35 - (Ulength * 14) * cos((167 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14) * sin((167 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 14) * cos((167 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14) * sin((167 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 14) * cos((167 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14) * sin((167 + backGroundLight) * PI / 180)},


		{rightPanel_x - Ulength * 35 - (Ulength * 14) * cos((173 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14) * sin((173 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 13.5) * cos((176 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13.5) * sin((176 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 13) * cos((178 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13) * sin((178 + backGroundLight) * PI / 180)},


		{rightPanel_x - Ulength * 35 - (Ulength * 8.5) * cos((265 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 8.5) * cos((265 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 8.5) * cos((265 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + backGroundLight) * PI / 180)},

		{rightPanel_x - Ulength * 35 - righttop_R1 * cos((-40 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-40 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos((-40 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-40 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos((-40 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-40 + backGroundLight) * PI / 180)},


	};
	setfillcolor(EGEARGB(0XFF, 0X4E, 0X4F, 0X4E));
	ege_bezier(backGroundLightnum, backGroundLightPloypoints);
	floodfill(rightPanel_x - Ulength * 35, rightPanel_y - Ulength * 18, EGEARGB(0XFF, 0X4E, 0X4F, 0X4E));


	ege_enable_aa(true);


	setcolor(EGEARGB(0XFF, 0X4E, 0X4F, 0X4E));
	setlinewidth(Linewidth / 7 * 4);
	int backGroundLightnum_1 = 25;
	ege_point backGroundLightPloypoints_1[25] = {
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos((-40 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-40 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos((-20 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-20 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos((-20 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-20 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos((-20 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-20 + backGroundLight) * PI / 180)},

		{rightPanel_x - Ulength * 35 - (Ulength * 9) * cos((30 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 9) * cos((30 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 9) * cos((30 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + backGroundLight) * PI / 180)},

		{rightPanel_x - Ulength * 35 - (Ulength * 13) * cos((110 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 13) * cos((110 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 13) * cos((110 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + backGroundLight) * PI / 180)},


		{rightPanel_x - Ulength * 35 - (Ulength * 13.5) * cos((110 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13.5) * sin((110 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 14.5) * cos((114 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14.5) * sin((114 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 14.5) * cos((120 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14.5) * sin((120 + backGroundLight) * PI / 180)},

		{rightPanel_x - Ulength * 35 - (Ulength * 14) * cos((167 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14) * sin((167 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 14) * cos((167 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14) * sin((167 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 14) * cos((167 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14) * sin((167 + backGroundLight) * PI / 180)},


		{rightPanel_x - Ulength * 35 - (Ulength * 14) * cos((173 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14) * sin((173 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 13.5) * cos((176 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13.5) * sin((176 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 13) * cos((178 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13) * sin((178 + backGroundLight) * PI / 180)},


		{rightPanel_x - Ulength * 35 - (Ulength * 8.5) * cos((265 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 8.5) * cos((265 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 8.5) * cos((265 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + backGroundLight) * PI / 180)},

		{rightPanel_x - Ulength * 35 - righttop_R1 * cos((-40 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-40 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos((-40 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-40 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - righttop_R1 * cos((-40 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-40 + backGroundLight) * PI / 180)},


	};

	ege_bezier(backGroundLightnum_1, backGroundLightPloypoints_1);


	int backGroundLightnum_2 = 4;
	ege_point backGroundLightPloypoints_2[4] = {
		{rightPanel_x - Ulength * 35 - (Ulength * 9) * cos((30 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 13) * cos((110 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 13) * cos((178 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13) * sin((178 + backGroundLight) * PI / 180)},
		{rightPanel_x - Ulength * 35 - (Ulength * 8.5) * cos((265 + backGroundLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + backGroundLight) * PI / 180)}
	};

	setfillcolor(EGEARGB(0XFF, 0X36, 0X36, 0X36));
	ege_setpattern_lineargradient(rightPanel_x - Ulength * 35 - (Ulength * 13) * cos((110 + backGroundLight) * PI / 180), rightPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + backGroundLight) * PI / 180), EGEARGB(0XFF, 0X30, 0X30, 0X30),
		rightPanel_x - Ulength * 35 - (Ulength * 8.5) * cos((265 + backGroundLight) * PI / 180), rightPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + backGroundLight) * PI / 180), EGEARGB(0XFF, 0X4E, 0X4F, 0X4E));
	ege_fillpoly(backGroundLightnum_2, backGroundLightPloypoints_2);
	ege_setpattern_none();

	setcolor(EGEARGB(0X20, 0X8D, 0X8F, 0X8B));
	ege_line(rightPanel_x - Ulength * 35 - (Ulength * 9) * cos((30 + backGroundLight) * PI / 180), rightPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + backGroundLight) * PI / 180),
		rightPanel_x - Ulength * 35 - (Ulength * 8.5) * cos((265 + backGroundLight) * PI / 180), rightPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + backGroundLight) * PI / 180));
	ege_line(rightPanel_x - Ulength * 35 - (Ulength * 14.5) * cos((120 + backGroundLight) * PI / 180), rightPanel_y - Ulength * 18 - (Ulength * 14.5) * sin((120 + backGroundLight) * PI / 180),
		rightPanel_x - Ulength * 35 - (Ulength * 14) * cos((167 + backGroundLight) * PI / 180), rightPanel_y - Ulength * 18 - (Ulength * 14) * sin((167 + backGroundLight) * PI / 180));



	setcolor(EGEARGB(0XFF, 0X20, 0X20, 0X20));
	setlinewidth(Linewidth / 7 * 4);
	ege_line(rightPanel_x - Ulength * 35 - (Ulength * 2) * cos((110 + backGroundLight) * PI / 180), rightPanel_y - Ulength * 18 - (Ulength * 2) * sin((110 + backGroundLight) * PI / 180),
		rightPanel_x - Ulength * 35 - (Ulength * 2) * cos((175 + backGroundLight) * PI / 180), rightPanel_y - Ulength * 18 - (Ulength * 2) * sin((175 + backGroundLight) * PI / 180));
	ege_line(rightPanel_x - Ulength * 35 - (Ulength * 2) * cos((110 + backGroundLight) * PI / 180), rightPanel_y - Ulength * 18 - (Ulength * 2) * sin((110 + backGroundLight) * PI / 180),
		rightPanel_x - Ulength * 35 - righttop_R1 * cos((-25 + backGroundLight) * PI / 180), rightPanel_y - Ulength * 18 - righttop_R1 * sin((-25 + backGroundLight) * PI / 180));
	ege_line(rightPanel_x - Ulength * 35 - (Ulength * 2) * cos((175 + backGroundLight) * PI / 180), rightPanel_y - Ulength * 18 - (Ulength * 2) * sin((175 + backGroundLight) * PI / 180),
		rightPanel_x - Ulength * 35 - righttop_R1 * cos((-35 + backGroundLight) * PI / 180), rightPanel_y - Ulength * 18 - righttop_R1 * sin((-35 + backGroundLight) * PI / 180));
	setcolor(EGEARGB(0XFF, 0X40, 0X41, 0X42));
	setlinewidth(Linewidth * 1.5);
	ege_line(rightPanel_x - Ulength * 35 - (Ulength * 1.5) * cos((142 + backGroundLight) * PI / 180), rightPanel_y - Ulength * 18 - (Ulength * 1.5) * sin((142 + backGroundLight) * PI / 180),
		rightPanel_x - Ulength * 35 - righttop_R1 * cos((-30 + backGroundLight) * PI / 180), rightPanel_y - Ulength * 18 - righttop_R1 * sin((-30 + backGroundLight) * PI / 180));
	setlinewidth(Linewidth / 7 * 4);








	ege_enable_aa(false);
	setcolor(EGEARGB(0XFF, 0X4E, 0X4F, 0X4E));
	setlinewidth(Linewidth / 2);
	int AFDSFLOODLightnum = 25;
	ege_point AFDSFLOODLightPloypoints[25] = {
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos((-40 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-40 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos((-20 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-20 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos((-20 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-20 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos((-20 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-20 + AFDSFLOODLight) * PI / 180)},

		{rightPanel_x + Ulength * 35 - (Ulength * 9) * cos((30 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 9) * cos((30 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 9) * cos((30 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + AFDSFLOODLight) * PI / 180)},

		{rightPanel_x + Ulength * 35 - (Ulength * 13) * cos((110 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 13) * cos((110 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 13) * cos((110 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + AFDSFLOODLight) * PI / 180)},


		{rightPanel_x + Ulength * 35 - (Ulength * 13.5) * cos((110 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13.5) * sin((110 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 14.5) * cos((114 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14.5) * sin((114 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 14.5) * cos((120 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14.5) * sin((120 + AFDSFLOODLight) * PI / 180)},

		{rightPanel_x + Ulength * 35 - (Ulength * 14) * cos((167 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14) * sin((167 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 14) * cos((167 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14) * sin((167 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 14) * cos((167 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14) * sin((167 + AFDSFLOODLight) * PI / 180)},


		{rightPanel_x + Ulength * 35 - (Ulength * 14) * cos((173 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14) * sin((173 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 13.5) * cos((176 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13.5) * sin((176 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 13) * cos((178 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13) * sin((178 + AFDSFLOODLight) * PI / 180)},


		{rightPanel_x + Ulength * 35 - (Ulength * 8.5) * cos((265 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 8.5) * cos((265 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 8.5) * cos((265 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + AFDSFLOODLight) * PI / 180)},

		{rightPanel_x + Ulength * 35 - righttop_R1 * cos((-40 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-40 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos((-40 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-40 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos((-40 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-40 + AFDSFLOODLight) * PI / 180)},


	};
	setfillcolor(EGEARGB(0XFF, 0X4E, 0X4F, 0X4E));
	ege_bezier(AFDSFLOODLightnum, AFDSFLOODLightPloypoints);
	floodfill(rightPanel_x + Ulength * 35, rightPanel_y - Ulength * 18, EGEARGB(0XFF, 0X4E, 0X4F, 0X4E));


	ege_enable_aa(true);


	setcolor(EGEARGB(0XFF, 0X4E, 0X4F, 0X4E));
	setlinewidth(Linewidth / 7 * 4);
	int AFDSFLOODLightnum_1 = 25;
	ege_point AFDSFLOODLightPloypoints_1[25] = {
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos((-40 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-40 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos((-20 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-20 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos((-20 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-20 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos((-20 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-20 + AFDSFLOODLight) * PI / 180)},

		{rightPanel_x + Ulength * 35 - (Ulength * 9) * cos((30 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 9) * cos((30 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 9) * cos((30 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + AFDSFLOODLight) * PI / 180)},

		{rightPanel_x + Ulength * 35 - (Ulength * 13) * cos((110 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 13) * cos((110 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 13) * cos((110 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + AFDSFLOODLight) * PI / 180)},


		{rightPanel_x + Ulength * 35 - (Ulength * 13.5) * cos((110 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13.5) * sin((110 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 14.5) * cos((114 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14.5) * sin((114 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 14.5) * cos((120 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14.5) * sin((120 + AFDSFLOODLight) * PI / 180)},

		{rightPanel_x + Ulength * 35 - (Ulength * 14) * cos((167 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14) * sin((167 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 14) * cos((167 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14) * sin((167 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 14) * cos((167 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14) * sin((167 + AFDSFLOODLight) * PI / 180)},


		{rightPanel_x + Ulength * 35 - (Ulength * 14) * cos((173 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 14) * sin((173 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 13.5) * cos((176 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13.5) * sin((176 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 13) * cos((178 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13) * sin((178 + AFDSFLOODLight) * PI / 180)},


		{rightPanel_x + Ulength * 35 - (Ulength * 8.5) * cos((265 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 8.5) * cos((265 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 8.5) * cos((265 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + AFDSFLOODLight) * PI / 180)},

		{rightPanel_x + Ulength * 35 - righttop_R1 * cos((-40 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-40 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos((-40 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-40 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - righttop_R1 * cos((-40 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - righttop_R1 * sin((-40 + AFDSFLOODLight) * PI / 180)},


	};

	ege_bezier(AFDSFLOODLightnum_1, AFDSFLOODLightPloypoints_1);


	int AFDSFLOODLightnum_2 = 4;
	ege_point AFDSFLOODLightPloypoints_2[4] = {
		{rightPanel_x + Ulength * 35 - (Ulength * 9) * cos((30 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 13) * cos((110 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 13) * cos((178 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 13) * sin((178 + AFDSFLOODLight) * PI / 180)},
		{rightPanel_x + Ulength * 35 - (Ulength * 8.5) * cos((265 + AFDSFLOODLight) * PI / 180),rightPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + AFDSFLOODLight) * PI / 180)}
	};

	setfillcolor(EGEARGB(0XFF, 0X36, 0X36, 0X36));
	ege_setpattern_lineargradient(rightPanel_x + Ulength * 35 - (Ulength * 13) * cos((110 + AFDSFLOODLight) * PI / 180), rightPanel_y - Ulength * 18 - (Ulength * 13) * sin((110 + AFDSFLOODLight) * PI / 180), EGEARGB(0XFF, 0X30, 0X30, 0X30),
		rightPanel_x + Ulength * 35 - (Ulength * 8.5) * cos((265 + AFDSFLOODLight) * PI / 180), rightPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + AFDSFLOODLight) * PI / 180), EGEARGB(0XFF, 0X4E, 0X4F, 0X4E));
	ege_fillpoly(AFDSFLOODLightnum_2, AFDSFLOODLightPloypoints_2);
	ege_setpattern_none();

	setcolor(EGEARGB(0X20, 0X8D, 0X8F, 0X8B));
	ege_line(rightPanel_x + Ulength * 35 - (Ulength * 9) * cos((30 + AFDSFLOODLight) * PI / 180), rightPanel_y - Ulength * 18 - (Ulength * 9) * sin((30 + AFDSFLOODLight) * PI / 180),
		rightPanel_x + Ulength * 35 - (Ulength * 8.5) * cos((265 + AFDSFLOODLight) * PI / 180), rightPanel_y - Ulength * 18 - (Ulength * 8.5) * sin((265 + AFDSFLOODLight) * PI / 180));
	ege_line(rightPanel_x + Ulength * 35 - (Ulength * 14.5) * cos((120 + AFDSFLOODLight) * PI / 180), rightPanel_y - Ulength * 18 - (Ulength * 14.5) * sin((120 + AFDSFLOODLight) * PI / 180),
		rightPanel_x + Ulength * 35 - (Ulength * 14) * cos((167 + AFDSFLOODLight) * PI / 180), rightPanel_y - Ulength * 18 - (Ulength * 14) * sin((167 + AFDSFLOODLight) * PI / 180));



	setcolor(EGEARGB(0XFF, 0X20, 0X20, 0X20));
	setlinewidth(Linewidth / 7 * 4);
	ege_line(rightPanel_x + Ulength * 35 - (Ulength * 2) * cos((110 + AFDSFLOODLight) * PI / 180), rightPanel_y - Ulength * 18 - (Ulength * 2) * sin((110 + AFDSFLOODLight) * PI / 180),
		rightPanel_x + Ulength * 35 - (Ulength * 2) * cos((175 + AFDSFLOODLight) * PI / 180), rightPanel_y - Ulength * 18 - (Ulength * 2) * sin((175 + AFDSFLOODLight) * PI / 180));
	ege_line(rightPanel_x + Ulength * 35 - (Ulength * 2) * cos((110 + AFDSFLOODLight) * PI / 180), rightPanel_y - Ulength * 18 - (Ulength * 2) * sin((110 + AFDSFLOODLight) * PI / 180),
		rightPanel_x + Ulength * 35 - righttop_R1 * cos((-25 + AFDSFLOODLight) * PI / 180), rightPanel_y - Ulength * 18 - righttop_R1 * sin((-25 + AFDSFLOODLight) * PI / 180));
	ege_line(rightPanel_x + Ulength * 35 - (Ulength * 2) * cos((175 + AFDSFLOODLight) * PI / 180), rightPanel_y - Ulength * 18 - (Ulength * 2) * sin((175 + AFDSFLOODLight) * PI / 180),
		rightPanel_x + Ulength * 35 - righttop_R1 * cos((-35 + AFDSFLOODLight) * PI / 180), rightPanel_y - Ulength * 18 - righttop_R1 * sin((-35 + AFDSFLOODLight) * PI / 180));
	setcolor(EGEARGB(0XFF, 0X40, 0X41, 0X42));
	setlinewidth(Linewidth * 1.5);
	ege_line(rightPanel_x + Ulength * 35 - (Ulength * 1.5) * cos((142 + AFDSFLOODLight) * PI / 180), rightPanel_y - Ulength * 18 - (Ulength * 1.5) * sin((142 + AFDSFLOODLight) * PI / 180),
		rightPanel_x + Ulength * 35 - righttop_R1 * cos((-30 + AFDSFLOODLight) * PI / 180), rightPanel_y - Ulength * 18 - righttop_R1 * sin((-30 + AFDSFLOODLight) * PI / 180));
	setlinewidth(Linewidth / 7 * 4);


	if (GetAsyncKeyState(0x04) & 0x8000) {
		if (rightPanel_speed_is_down == 0) {
			rightPanel_speed_is_down = 1;
			mousepos(&rightPanel_mouse_x, &rightPanel_mouse_y);
			rightPanel_mouse_x_cur = rightPanel_mouse_x;
			rightPanel_mouse_y_cur = rightPanel_mouse_y;
		}
		if (rightPanel_speed_is_down == 1) {
			if ((rightPanel_mouse_x_cur >= rightPanel_x - Ulength * 35 - righttop_R1)
				&& (rightPanel_mouse_x_cur <= rightPanel_x - Ulength * 35 + righttop_R1)
				&& (rightPanel_mouse_y_cur >= rightPanel_y - Ulength * 18 - righttop_R1)
				&& (rightPanel_mouse_y_cur <= rightPanel_y - Ulength * 18 + righttop_R1)) {


				mousepos(&rightPanel_mouse_x, &rightPanel_mouse_y);
				if (rightPanel_mouse_y > rightPanel_mouse_y_cur) {
					if (backGroundLight < 260) {
						backGroundLight += (rightPanel_mouse_y - rightPanel_mouse_y_cur) / 70;
						
					}
					else if (backGroundLight >= 260) {
						backGroundLight = 260;
						
					}
				}
				else {
					if (backGroundLight > -20) {
						backGroundLight += (rightPanel_mouse_y - rightPanel_mouse_y_cur) / 70;
						
					}
					else if (backGroundLight <= -20) {
						backGroundLight = -20;
						
					}
				}
			}
		}

	}
	else if (rightPanel_speed_is_down == 1) {
		rightPanel_speed_is_down = 0;
	}

	if (GetAsyncKeyState(0x04) & 0x8000) {
		if (rightPanel_speed_is_down == 0) {
			rightPanel_speed_is_down = 1;
			mousepos(&rightPanel_mouse_x, &rightPanel_mouse_y);
			rightPanel_mouse_x_cur = rightPanel_mouse_x;
			rightPanel_mouse_y_cur = rightPanel_mouse_y;
		}
		if (rightPanel_speed_is_down == 1) {
			if ((rightPanel_mouse_x_cur >= rightPanel_x + Ulength * 35 - righttop_R1)
				&& (rightPanel_mouse_x_cur <= rightPanel_x + Ulength * 35 + righttop_R1)
				&& (rightPanel_mouse_y_cur >= rightPanel_y - Ulength * 18 - righttop_R1)
				&& (rightPanel_mouse_y_cur <= rightPanel_y - Ulength * 18 + righttop_R1)) {


				mousepos(&rightPanel_mouse_x, &rightPanel_mouse_y);
				if (rightPanel_mouse_y > rightPanel_mouse_y_cur) {
					if (AFDSFLOODLight < 260) {
						AFDSFLOODLight += (rightPanel_mouse_y - rightPanel_mouse_y_cur) / 70;

					}
					else if (AFDSFLOODLight >= 260) {
						AFDSFLOODLight = 260;

					}
				}
				else {
					if (AFDSFLOODLight > -20) {
						AFDSFLOODLight += (rightPanel_mouse_y - rightPanel_mouse_y_cur) / 70;

					}
					else if (AFDSFLOODLight <= -20) {
						AFDSFLOODLight = -20;

					}
				}
			}
		}

	}
	else if (rightPanel_speed_is_down == 1) {
		rightPanel_speed_is_down = 0;
	}



}