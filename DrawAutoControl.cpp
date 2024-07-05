#include<graphics.h>
#include <stdio.h>
#include <math.h>


#include "G_variable.h"
int AT_1 = 0;
extern int choicetransformAT;

int longPanel_mouse_x = 0, longPanel_mouse_y = 0;
int longPanel_speed_is_down = 0;
int longPanel_mouse_y_cur = 0, longPanel_mouse_x_cur = 0;

void datatransform_back() {
	if (AT == 1) {
		altitude_bk_mode = 1;
	} 
	else if (AT == 0) {
		altitude_bk_mode = 0;
	}
	if (FD_1_1 == 1 && SPEED_1 == 0 && HDGSEL_1 == 0 && ALTHLD_1 == 0 && VS_1 == 0) {
		autopilot_bk_mode = 132;
	}
	else if (FD_1_1 == 0 && SPEED_1 == 0 && HDGSEL_1 == 0 && ALTHLD_1 == 0 && VS_1 == 0) {
		autopilot_bk_mode = 164;
	}
	else if (FD_1_1 == 0 && SPEED_1 == 1 && HDGSEL_1 == 0 && ALTHLD_1 == 0 && VS_1 == 0) {
		autopilot_bk_mode = 165;
	}
	else if (FD_1_1 == 0 && SPEED_1 == 0 && HDGSEL_1 == 1 && ALTHLD_1 == 0 && VS_1 == 0) {
		autopilot_bk_mode = 162;
	}
	else if (FD_1_1 == 0 && SPEED_1 == 0 && HDGSEL_1 == 0 && ALTHLD_1 == 1 && VS_1 == 0) {
		autopilot_bk_mode = 16388;
	}
	else if (FD_1_1 == 0 && SPEED_1 == 0 && HDGSEL_1 == 0 && ALTHLD_1 == 0 && VS_1 == 1) {
		autopilot_bk_mode = 52;
	}
	else if (FD_1_1 == 0 && SPEED_1 == 1 && HDGSEL_1 == 1 && ALTHLD_1 == 0 && VS_1 == 0) {
		autopilot_bk_mode = 163;
	}
	else if (FD_1_1 == 0 && SPEED_1 == 0 && HDGSEL_1 == 1 && ALTHLD_1 == 1 && VS_1 == 0) {
		autopilot_bk_mode = 16386;
	}
	else if (FD_1_1 == 0 && SPEED_1 == 1 && HDGSEL_1 == 0 && ALTHLD_1 == 1 && VS_1 == 0) {
		autopilot_bk_mode = 16389;
	}
	else if (FD_1_1 == 0 && SPEED_1 == 1 && HDGSEL_1 == 1 && ALTHLD_1 == 1 && VS_1 == 0) {
		autopilot_bk_mode = 16387;
	}
	else if (FD_1_1 == 0 && SPEED_1 == 1 && HDGSEL_1 == 1 && ALTHLD_1 == 0 && VS_1 == 1) {
		autopilot_bk_mode = 51;
	}

	if (CMDA_1 == 0 && FD_1_1 == 0) {
		flight_director_bk_mode = 1;
	}
	else if (CMDA_1 == 1 && FD_1_1 == 0) {
		flight_director_bk_mode = 0;
	}
}

void datatransform() {
	if (altitude_mode == 1) {
		AT = 1;
	}
	else {
		AT = 0;
	}
	if (autopilot_mode == 132) {
		FD_1 = 1;
		SPEED = 0;
		HDGSEL = 0;
		ALTHLD = 0;
		VS = 0;
	}
	else if (autopilot_mode == 164) {
		FD_1 = 0;
		SPEED = 0;
		HDGSEL = 0;
		ALTHLD = 0;
		VS = 0;
	}
	else if (autopilot_mode == 165) {
		FD_1 = 0;
		SPEED = 1;
		HDGSEL = 0;
		ALTHLD = 0;
		VS = 0;
	}
	else if (autopilot_mode == 162) {
		FD_1 = 0;
		SPEED = 0;
		HDGSEL = 1;
		ALTHLD = 0;
		VS = 0;
	}
	else if (autopilot_mode == 16388) {
		FD_1 = 0;
		SPEED = 0;
		HDGSEL = 0;
		ALTHLD = 1;
		VS = 0;
	}
	else if (autopilot_mode == 52) {
		FD_1 = 0;
		SPEED = 0;
		HDGSEL = 0;
		ALTHLD = 0;
		VS = 1;
	}
	else if (autopilot_mode == 163) {
		FD_1 = 0;
		SPEED = 1;
		HDGSEL = 1;
		ALTHLD = 0;
		VS = 0;
	}
	else if (autopilot_mode == 16386) {
		FD_1 = 0;
		SPEED = 0;
		HDGSEL = 1;
		ALTHLD = 1;
		VS = 0;
	}
	else if (autopilot_mode == 16389) {
		FD_1 = 0;
		SPEED = 1;
		HDGSEL = 0;
		ALTHLD = 1;
		VS = 0;
	}
	else if (autopilot_mode == 16387) {
		FD_1 = 0;
		SPEED = 1;
		HDGSEL = 1;
		ALTHLD = 1;
		VS = 0;
	}
	else if (autopilot_mode == 51) {
		FD_1 = 0;
		SPEED = 1;
		HDGSEL = 1;
		ALTHLD = 0;
		VS = 1;
	}
	if (flight_director_mode == 1) {
		FD_1 = 0;
		CMDA = 0;
	}
	else if (flight_director_mode == 2) {
		FD_1 = 0;
		CMDA = 1;
	}
}

void button_green_light(double center_x, double center_y, double side) {
	//小正方形的边长
	double side0 = side / 100.0;

	//先计算左上角的坐标
	double x = center_x - side0 * 8;
	double y = center_y - side0 * 2;
	setfillcolor(GREEN);
	for (int i = 0; i < 16; i += 2) {
		ege_fillrect(x + side0 * i, y, side0, side0);
	}
	for (int i = -1; i < 17; i += 2) {
		ege_fillrect(x + side0 * i, y + side0, side0, side0);
	}
	for (int i = 0; i < 16; i += 2) {
		ege_fillrect(x + side0 * i, y + side0 * 2, side0, side0);
	}
	for (int i = -1; i < 17; i += 2) {
		ege_fillrect(x + side0 * i, y + side0 * 3, side0, side0);
	}
}

void draw_auto_control(double center_x, double center_y, double side) {
	datatransform();

	SPEED_1 = SPEED;
	FD_1_1 = FD_1;
	HDGSEL_1 = HDGSEL;
	ALTHLD_1 = ALTHLD;
	VS_1 = VS;
	CMDA_1 = CMDA;

	double Ulength = side / 366;
	double Linewidth = Ulength;

	int x, y;
	mousepos(&x, &y);

	double Topknob_R1 = Ulength * 8;
	double Topknob_R2 = Ulength * 6.5;

	ege_enable_aa(false);

	setcolor(EGEARGB(0XFF, 0X1B, 0X1E, 0X21));
	int Framenum = 61;
	ege_point FramePloypoints[61] = {
		{center_x - Ulength * 175,center_y - Ulength * 27},
		{center_x - Ulength * 175,center_y - Ulength * 27.5},
		{center_x - Ulength * 174.5,center_y - Ulength * 28},
		{center_x - Ulength * 174,center_y - Ulength * 28},

		{center_x + Ulength * 174,center_y - Ulength * 28},
		{center_x + Ulength * 174,center_y - Ulength * 28},
		{center_x + Ulength * 174,center_y - Ulength * 28},

		{center_x + Ulength * 174.5,center_y - Ulength * 28},
		{center_x + Ulength * 175,center_y - Ulength * 27.5},
		{center_x + Ulength * 175,center_y - Ulength * 27},

		{center_x + Ulength * 175,center_y - Ulength * 22},
		{center_x + Ulength * 175,center_y - Ulength * 22},
		{center_x + Ulength * 175,center_y - Ulength * 22},

		{center_x + Ulength * 175,center_y - Ulength * 18},
		{center_x + Ulength * 178.5,center_y - Ulength * 16},
		{center_x + Ulength * 182,center_y - Ulength * 16},

		{center_x + Ulength * 182.5,center_y - Ulength * 16},
		{center_x + Ulength * 183,center_y - Ulength * 15.5},
		{center_x + Ulength * 183,center_y - Ulength * 15},

		{center_x + Ulength * 183,center_y + Ulength * 15},
		{center_x + Ulength * 183,center_y + Ulength * 15},
		{center_x + Ulength * 183,center_y + Ulength * 15},

		{center_x + Ulength * 183,center_y + Ulength * 15.5},
		{center_x + Ulength * 182.5,center_y + Ulength * 16},
		{center_x + Ulength * 182,center_y + Ulength * 16},

		{center_x + Ulength * 178.5,center_y + Ulength * 16},
		{center_x + Ulength * 175,center_y + Ulength * 18},
		{center_x + Ulength * 175,center_y + Ulength * 22},

		{center_x + Ulength * 175,center_y + Ulength * 27},
		{center_x + Ulength * 175,center_y + Ulength * 27},
		{center_x + Ulength * 175,center_y + Ulength * 27},

		{center_x + Ulength * 175,center_y + Ulength * 27.5},
		{center_x + Ulength * 174.5,center_y + Ulength * 28},
		{center_x + Ulength * 174,center_y + Ulength * 28},

		{center_x - Ulength * 174,center_y + Ulength * 28},
		{center_x - Ulength * 174,center_y + Ulength * 28},
		{center_x - Ulength * 174,center_y + Ulength * 28},

		{center_x - Ulength * 174.5,center_y + Ulength * 28},
		{center_x - Ulength * 175,center_y + Ulength * 27.5},
		{center_x - Ulength * 175,center_y + Ulength * 27},

		{center_x - Ulength * 175,center_y + Ulength * 22},
		{center_x - Ulength * 175,center_y + Ulength * 22},
		{center_x - Ulength * 175,center_y + Ulength * 22},

		{center_x - Ulength * 175,center_y + Ulength * 18},
		{center_x - Ulength * 178.5,center_y + Ulength * 16},
		{center_x - Ulength * 182,center_y + Ulength * 16},

		{center_x - Ulength * 182.5,center_y + Ulength * 16},
		{center_x - Ulength * 183,center_y + Ulength * 15.5},
		{center_x - Ulength * 183,center_y + Ulength * 15},

		{center_x - Ulength * 183,center_y - Ulength * 15},
		{center_x - Ulength * 183,center_y - Ulength * 15},
		{center_x - Ulength * 183,center_y - Ulength * 15},

		{center_x - Ulength * 183,center_y - Ulength * 15.5},
		{center_x - Ulength * 182.5,center_y - Ulength * 16},
		{center_x - Ulength * 182,center_y - Ulength * 16},

		{center_x - Ulength * 178.5,center_y - Ulength * 16},
		{center_x - Ulength * 175,center_y - Ulength * 18},
		{center_x - Ulength * 175,center_y - Ulength * 22},

		{center_x - Ulength * 175,center_y - Ulength * 27},
		{center_x - Ulength * 175,center_y - Ulength * 27},
		{center_x - Ulength * 175,center_y - Ulength * 27},


	};
	ege_bezier(Framenum, FramePloypoints);
	setfillcolor(EGEARGB(0XFF, 0X1B, 0X1E, 0X21));
	floodfill(center_x, center_y, EGEARGB(0XFF, 0X1B, 0X1E, 0X21));
	floodfill(center_x - 170 * Ulength, center_y - 24 * Ulength, EGEARGB(0XFF, 0X1B, 0X1E, 0X21));
	floodfill(center_x + 170 * Ulength, center_y - 24 * Ulength, EGEARGB(0XFF, 0X1B, 0X1E, 0X21));
	floodfill(center_x - 170 * Ulength, center_y + 24 * Ulength, EGEARGB(0XFF, 0X1B, 0X1E, 0X21));
	floodfill(center_x + 170 * Ulength, center_y + 24 * Ulength, EGEARGB(0XFF, 0X1B, 0X1E, 0X21));

	ege_enable_aa(true);
	setcolor(EGEARGB(0XFF, 0X10, 0X10, 0X10));
	setlinewidth(Linewidth / 7 * 4);
	int Framenum_1 = 61;
	ege_point FramePloypoints_1[61] = {
		{center_x - Ulength * 175,center_y - Ulength * 27},
		{center_x - Ulength * 175,center_y - Ulength * 27.5},
		{center_x - Ulength * 174.5,center_y - Ulength * 28},
		{center_x - Ulength * 174,center_y - Ulength * 28},

		{center_x + Ulength * 174,center_y - Ulength * 28},
		{center_x + Ulength * 174,center_y - Ulength * 28},
		{center_x + Ulength * 174,center_y - Ulength * 28},

		{center_x + Ulength * 174.5,center_y - Ulength * 28},
		{center_x + Ulength * 175,center_y - Ulength * 27.5},
		{center_x + Ulength * 175,center_y - Ulength * 27},

		{center_x + Ulength * 175,center_y - Ulength * 22},
		{center_x + Ulength * 175,center_y - Ulength * 22},
		{center_x + Ulength * 175,center_y - Ulength * 22},

		{center_x + Ulength * 175,center_y - Ulength * 18},
		{center_x + Ulength * 178.5,center_y - Ulength * 16},
		{center_x + Ulength * 182,center_y - Ulength * 16},

		{center_x + Ulength * 182.5,center_y - Ulength * 16},
		{center_x + Ulength * 183,center_y - Ulength * 15.5},
		{center_x + Ulength * 183,center_y - Ulength * 15},

		{center_x + Ulength * 183,center_y + Ulength * 15},
		{center_x + Ulength * 183,center_y + Ulength * 15},
		{center_x + Ulength * 183,center_y + Ulength * 15},

		{center_x + Ulength * 183,center_y + Ulength * 15.5},
		{center_x + Ulength * 182.5,center_y + Ulength * 16},
		{center_x + Ulength * 182,center_y + Ulength * 16},

		{center_x + Ulength * 178.5,center_y + Ulength * 16},
		{center_x + Ulength * 175,center_y + Ulength * 18},
		{center_x + Ulength * 175,center_y + Ulength * 22},

		{center_x + Ulength * 175,center_y + Ulength * 27},
		{center_x + Ulength * 175,center_y + Ulength * 27},
		{center_x + Ulength * 175,center_y + Ulength * 27},

		{center_x + Ulength * 175,center_y + Ulength * 27.5},
		{center_x + Ulength * 174.5,center_y + Ulength * 28},
		{center_x + Ulength * 174,center_y + Ulength * 28},

		{center_x - Ulength * 174,center_y + Ulength * 28},
		{center_x - Ulength * 174,center_y + Ulength * 28},
		{center_x - Ulength * 174,center_y + Ulength * 28},

		{center_x - Ulength * 174.5,center_y + Ulength * 28},
		{center_x - Ulength * 175,center_y + Ulength * 27.5},
		{center_x - Ulength * 175,center_y + Ulength * 27},

		{center_x - Ulength * 175,center_y + Ulength * 22},
		{center_x - Ulength * 175,center_y + Ulength * 22},
		{center_x - Ulength * 175,center_y + Ulength * 22},

		{center_x - Ulength * 175,center_y + Ulength * 18},
		{center_x - Ulength * 178.5,center_y + Ulength * 16},
		{center_x - Ulength * 182,center_y + Ulength * 16},

		{center_x - Ulength * 182.5,center_y + Ulength * 16},
		{center_x - Ulength * 183,center_y + Ulength * 15.5},
		{center_x - Ulength * 183,center_y + Ulength * 15},

		{center_x - Ulength * 183,center_y - Ulength * 15},
		{center_x - Ulength * 183,center_y - Ulength * 15},
		{center_x - Ulength * 183,center_y - Ulength * 15},

		{center_x - Ulength * 183,center_y - Ulength * 15.5},
		{center_x - Ulength * 182.5,center_y - Ulength * 16},
		{center_x - Ulength * 182,center_y - Ulength * 16},

		{center_x - Ulength * 178.5,center_y - Ulength * 16},
		{center_x - Ulength * 175,center_y - Ulength * 18},
		{center_x - Ulength * 175,center_y - Ulength * 22},

		{center_x - Ulength * 175,center_y - Ulength * 27},
		{center_x - Ulength * 175,center_y - Ulength * 27},
		{center_x - Ulength * 175,center_y - Ulength * 27},

	};
	ege_bezier(Framenum_1, FramePloypoints_1);

	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_arc(center_x - 166 * Ulength, center_y - 8 * Ulength, 16 * Ulength, 16 * Ulength, 120, 120);
	ege_arc(center_x - 166 * Ulength, center_y - 8 * Ulength, 16 * Ulength, 16 * Ulength, 300, 120);
	ege_line(center_x - 158 * Ulength, center_y, center_x - 155 * Ulength, center_y - 7 * Ulength);
	ege_line(center_x - 155 * Ulength, center_y - 9 * Ulength, center_x - 155 * Ulength, center_y - 7 * Ulength);


	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_arc(center_x - 166 * Ulength, center_y - 8 * Ulength, 16 * Ulength, 16 * Ulength, 125, 110);
	ege_arc(center_x - 166 * Ulength, center_y - 8 * Ulength, 16 * Ulength, 16 * Ulength, 305, 110);
	ege_line(center_x - 158 * Ulength, center_y, center_x - 155 * Ulength, center_y - 7 * Ulength);
	ege_line(center_x - 155 * Ulength, center_y - 9 * Ulength, center_x - 155 * Ulength, center_y - 7 * Ulength);

	setfillcolor(EGEARGB(0XFF, 0X95, 0X88, 0X70));
	ege_fillellipse(center_x - 164 * Ulength, center_y - 6 * Ulength, 12 * Ulength, 12 * Ulength);

	int num_1 = 4;
	ege_point numploy_1[4] = {
		{center_x - 158 * Ulength ,center_y - 6 * Ulength},
		{center_x - 158 * Ulength ,center_y + 6 * Ulength},
		{center_x - 165 * Ulength ,center_y + 6 * Ulength},
		{center_x - 165 * Ulength ,center_y - 6 * Ulength},

	};
	ege_fillpoly(num_1, numploy_1);


	setcolor(EGEARGB(0X30, 0X50, 0X50, 0X50));
	for (int i = 0; i < 360; i += 10) {
		ege_line(center_x - 158 * Ulength - (6 * Ulength) * cos((i + COURSE_1) * PI / 180), center_y - (6 * Ulength) * sin((i + COURSE_1) * PI / 180),
			center_x - 165 * Ulength - (6 * Ulength) * cos((i + COURSE_1) * PI / 180), center_y - (6 * Ulength) * sin((i + COURSE_1) * PI / 180));
	}


	setfillcolor(EGEARGB(0XFF, 0X49, 0X48, 0X46));
	ege_fillellipse(center_x - 171 * Ulength, center_y - 6 * Ulength, 12 * Ulength, 12 * Ulength);

	setcolor(EGEARGB(0XFF, 0X39, 0X38, 0X36));
	ege_ellipse(center_x - 170.5 * Ulength, center_y - 5.5 * Ulength, 11 * Ulength, 11 * Ulength);

	setcolor(EGEARGB(0XFF, 0X6C, 0X56, 0X2A));
	setlinewidth(Linewidth * 1.2);
	ege_line(center_x - 165 * Ulength - (5 * Ulength) * cos((0 + COURSE_1) * PI / 180), center_y - (5 * Ulength) * sin((0 + COURSE_1) * PI / 180),
		center_x - 165 * Ulength - (5 * Ulength) * cos((180 + COURSE_1) * PI / 180), center_y - (5 * Ulength) * sin((180 + COURSE_1) * PI / 180));
	ege_line(center_x - 165 * Ulength - (4 * Ulength) * cos((70 + COURSE_1) * PI / 180), center_y - (4 * Ulength) * sin((70 + COURSE_1) * PI / 180),
		center_x - 165 * Ulength - (4 * Ulength) * cos((290 + COURSE_1) * PI / 180), center_y - (4 * Ulength) * sin((290 + COURSE_1) * PI / 180));

	setcolor(EGEARGB(0XFF, 0X6A, 0X48, 0X27));
	setlinewidth(Linewidth * 4 / 6);
	ege_line(center_x - 165 * Ulength - (4.7 * Ulength) * cos((0 + COURSE_1) * PI / 180), center_y - (4.7 * Ulength) * sin((0 + COURSE_1) * PI / 180),
		center_x - 165 * Ulength - (4.7 * Ulength) * cos((180 + COURSE_1) * PI / 180), center_y - (4.7 * Ulength) * sin((180 + COURSE_1) * PI / 180));
	ege_line(center_x - 165 * Ulength - (3.3 * Ulength) * cos((65 + COURSE_1) * PI / 180), center_y - (3.3 * Ulength) * sin((65 + COURSE_1) * PI / 180),
		center_x - 165 * Ulength - (3.3 * Ulength) * cos((295 + COURSE_1) * PI / 180), center_y - (3.3 * Ulength) * sin((295 + COURSE_1) * PI / 180));


	if (GetAsyncKeyState(0x04) & 0x8000) {
		if (longPanel_speed_is_down == 0) {
			longPanel_speed_is_down = 1;
			mousepos(&longPanel_mouse_x, &longPanel_mouse_y);
			longPanel_mouse_x_cur = longPanel_mouse_x;
			longPanel_mouse_y_cur = longPanel_mouse_y;
		}
		if (longPanel_speed_is_down == 1) {
			if ((longPanel_mouse_x_cur >= center_x - 171 * Ulength)
				&& (longPanel_mouse_x_cur <= center_x - 152 * Ulength)
				&& (longPanel_mouse_y_cur >= center_y - 6 * Ulength)
				&& (longPanel_mouse_y_cur <= center_y + 6 * Ulength)) {


				mousepos(&longPanel_mouse_x, &longPanel_mouse_y);
				if (longPanel_mouse_y > longPanel_mouse_y_cur) {

					COURSE_1 += (longPanel_mouse_y - longPanel_mouse_y_cur) / 70;
					if (COURSE_1NUM + change_COURSE_1NUM < 360 && COURSE_1NUM + change_COURSE_1NUM>0) {
						change_COURSE_1NUM += (int)((longPanel_mouse_y - longPanel_mouse_y_cur) / 70);
					}
					else if (COURSE_1NUM + change_COURSE_1NUM >= 360) {
						change_COURSE_1NUM = 1 - COURSE_1NUM;

					}
					else if (COURSE_1NUM + change_COURSE_1NUM <= 0) {
						change_COURSE_1NUM = 359 - COURSE_1NUM;

					}

				}
				else {
					COURSE_1 += (longPanel_mouse_y - longPanel_mouse_y_cur) / 70;
					if (COURSE_1NUM + change_COURSE_1NUM < 360 && COURSE_1NUM + change_COURSE_1NUM>0) {
						change_COURSE_1NUM += (int)((longPanel_mouse_y - longPanel_mouse_y_cur) / 70);
					}
					else if (COURSE_1NUM + change_COURSE_1NUM >= 360) {
						change_COURSE_1NUM = 1 - COURSE_1NUM;

					}
					else if (COURSE_1NUM + change_COURSE_1NUM <= 0) {
						change_COURSE_1NUM = 359 - COURSE_1NUM;

					}
				}
			}
		}

	}
	else if (longPanel_speed_is_down == 1) {
		longPanel_speed_is_down = 0;
	}



	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_rectangle(center_x - 149 * Ulength, center_y + 10 * Ulength, Ulength * 7, Ulength * 11);
	setfont(Ulength * 4, Ulength * 2.5, "Bahnschrift");
	ege_drawtext("F/D", center_x - Ulength * 145, center_y + 5 * Ulength);
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	ege_drawtext("ON", center_x - Ulength * 145.5, center_y + 8.5 * Ulength);
	ege_drawtext("OFF", center_x - Ulength * 145.5, center_y + 24.5 * Ulength);

	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_rectangle(center_x - 149 * Ulength, center_y + 10 * Ulength, Ulength * 7, Ulength * 11);
	setfont(Ulength * 4, Ulength * 2.5, "Bahnschrift");
	ege_drawtext("F/D", center_x - Ulength * 145, center_y + 5 * Ulength);
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	ege_drawtext("ON", center_x - Ulength * 145.5, center_y + 8.5 * Ulength);
	ege_drawtext("OFF", center_x - Ulength * 145.5, center_y + 24.5 * Ulength);




	ege_enable_aa(false);
	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	setlinewidth(Linewidth / 3);
	setcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	int FDnums_1 = 13;
	ege_point FDploypoints_1[13] = {
		{center_x - Ulength * 147,center_y + 13 * Ulength},
		{center_x - Ulength * 146,center_y + 11 * Ulength},
		{center_x - Ulength * 144,center_y + 11 * Ulength},
		{center_x - Ulength * 143,center_y + 13 * Ulength},

		{center_x - Ulength * 143,center_y + 18 * Ulength},
		{center_x - Ulength * 143,center_y + 18 * Ulength},
		{center_x - Ulength * 143,center_y + 18 * Ulength},

		{center_x - Ulength * 144,center_y + 20 * Ulength},
		{center_x - Ulength * 146,center_y + 20 * Ulength},
		{center_x - Ulength * 147,center_y + 18 * Ulength},

		{center_x - Ulength * 147,center_y + 13 * Ulength},
		{center_x - Ulength * 147,center_y + 13 * Ulength},
		{center_x - Ulength * 147,center_y + 13 * Ulength},

	};
	ege_bezier(FDnums_1, FDploypoints_1);

	floodfill(center_x - Ulength * 147, center_y + 16 * Ulength, EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_enable_aa(true);

	if (FD_1 == 0) {
		setfillcolor(EGEARGB(0XFF, 0X4B, 0X4B, 0X49));

		for (int i = 0; i <= 60; i++) {
			ege_fillellipse(center_x - Ulength * (147 + 0.025 * i), center_y + (13 - i * 0.1) * Ulength, Ulength * (3 + i * 0.015), Ulength * (3 + i * 0.015));
		}
		setlinewidth(Linewidth / 5);
		setcolor(EGEARGB(0X8F, 0X20, 0X20, 0X20));
		ege_ellipse(center_x - Ulength * (147 + 0.025 * 60), center_y + (13 - 60 * 0.1) * Ulength, Ulength * (3 + 60 * 0.015), Ulength * (3 + 60 * 0.015));

	}
	if (FD_1 == 1) {
		setfillcolor(EGEARGB(0XFF, 0X4B, 0X4B, 0X49));

		for (int i = 0; i <= 60; i++) {
			ege_fillellipse(center_x - Ulength * (147 + 0.025 * i), center_y + (13 + i * 0.1) * Ulength, Ulength * (3 + i * 0.015), Ulength * (3 + i * 0.015));
		}
		setlinewidth(Linewidth / 5);
		setcolor(EGEARGB(0X8F, 0X20, 0X20, 0X20));
		ege_ellipse(center_x - Ulength * (147 + 0.025 * 60), center_y + (13 + 60 * 0.1) * Ulength, Ulength * (3 + 60 * 0.015), Ulength * (3 + 60 * 0.015));

	}
	if (x > center_x - Ulength * 147 && x < center_x - Ulength * 143 && y>center_y + 12 * Ulength && y <= center_y + 15 * Ulength) {
		ege_rectangle(center_x - Ulength * 147, center_y + 12 * Ulength, Ulength * 4, Ulength * 3);

		if (GetAsyncKeyState(0x02) & 0x0001 && FD_1 > 0) {
			FD_1_1--;

		}
	}
	if (x > center_x - Ulength * 147 && x < center_x - Ulength * 143 && y>center_y + 15 * Ulength && y <= center_y + 19 * Ulength) {
		ege_rectangle(center_x - Ulength * 147, center_y + 15 * Ulength, Ulength * 4, Ulength * 4);

		if (GetAsyncKeyState(0x02) & 0x0001 && FD_1 < 1) {
			FD_1_1++;

		}
	}

	setfillcolor(EGEARGB(0XFF, 0X26, 0X2B, 0X2C));
	ege_fillellipse(center_x - Ulength * 148.5, center_y - 6.5 * Ulength, 7 * Ulength, 7 * Ulength);
	ege_fillrect(center_x - Ulength * 166, center_y - 23 * Ulength, Ulength * 24, Ulength * 13);



	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillellipse(center_x - Ulength * 148, center_y - 6 * Ulength, 6 * Ulength, 6 * Ulength);
	ege_fillrect(center_x - Ulength * 165, center_y - 22 * Ulength, Ulength * 22, Ulength * 11);


	setfillcolor(EGEARGB(0XFF, 0X15, 0X15, 0X15));
	ege_fillrect(center_x - Ulength * 164, center_y - 21.5 * Ulength, Ulength * 20, Ulength * 10);

	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillrect(center_x - Ulength * 163, center_y - 21 * Ulength, Ulength * 18, Ulength * 9);

	if (FD_1 == 0) {
		setcolor(EGEARGB(0XFF, 0X0D, 0X9B, 0X12));
		setfont(Ulength * 4, Ulength * 2.5, "Bahnschrift");
		ege_drawtext("MA", center_x - Ulength * 145, center_y - 2.5 * Ulength);

	}

	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	setfont(Ulength * 10, Ulength * 2.5, "DigifaceWide");
	char nums_1[64];//左上上
	sprintf_s(nums_1, "%03d", COURSE_1NUM + change_COURSE_1NUM);
	ege_drawtext(nums_1, center_x - Ulength * 154, center_y - 16 * Ulength);

	setlinewidth(Linewidth / 7 * 4);
	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	setfont(Ulength * 4, Ulength * 2.5, "Bahnschrift");
	ege_drawtext("COURSE", center_x - Ulength * 155, center_y - 24.5 * Ulength);
	ege_drawtext("A/T", center_x - Ulength * 130, center_y - 24.5 * Ulength);
	ege_drawtext("ARM", center_x - Ulength * 130, center_y - 21.5 * Ulength);
	ege_drawtext("OFF", center_x - Ulength * 129.5, center_y - 0 * Ulength);
	ege_arc(center_x - Ulength * 136, center_y - 15 * Ulength, Ulength * 13, Ulength * 13, 125, 110);
	ege_arc(center_x - Ulength * 136, center_y - 15 * Ulength, Ulength * 13, Ulength * 13, 305, 110);


	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_drawtext("COURSE", center_x - Ulength * 155, center_y - 24.5 * Ulength);
	ege_drawtext("A/T", center_x - Ulength * 130, center_y - 24.5 * Ulength);
	ege_drawtext("ARM", center_x - Ulength * 130, center_y - 21.5 * Ulength);
	ege_drawtext("OFF", center_x - Ulength * 129.5, center_y - 0 * Ulength);
	ege_arc(center_x - Ulength * 136, center_y - 15 * Ulength, Ulength * 13, Ulength * 13, 125, 110);
	ege_arc(center_x - Ulength * 136, center_y - 15 * Ulength, Ulength * 13, Ulength * 13, 305, 110);


	if (AT == 0&&AT_1==0)
		setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	else if (AT == 1||AT_1==1)
		setfillcolor(GREEN);

	ege_fillellipse(center_x - Ulength * 133, center_y - 20 * Ulength, Ulength * 6, Ulength * 2);
	ege_fillellipse(center_x - Ulength * 132.5, center_y - 14 * Ulength, Ulength * 6, Ulength * 10);



	if (AT == 0) {
		setfillcolor(EGEARGB(0XFF, 0X4B, 0X4B, 0X49));

		for (int i = 0; i <= 60; i++) {
			ege_fillellipse(center_x - Ulength * (131 + 0.025 * i), center_y - (11 - i * 0.15) * Ulength, Ulength * (3 + i * 0.03), Ulength * (3 + i * 0.03));
		}
		setlinewidth(Linewidth / 5);
		setcolor(EGEARGB(0X8F, 0X20, 0X20, 0X20));
		ege_ellipse(center_x - Ulength * (131 + 0.025 * 60), center_y - (11 - 60 * 0.15) * Ulength, Ulength * (3 + 60 * 0.03), Ulength * (3 + 60 * 0.03));

	}
	if (AT == 1) {
		setfillcolor(EGEARGB(0XFF, 0X4B, 0X4B, 0X49));

		for (int i = 0; i <= 60; i++) {
			ege_fillellipse(center_x - Ulength * (131 + 0.025 * i), center_y - (11 + i * 0.15) * Ulength, Ulength * (3 + i * 0.03), Ulength * (3 + i * 0.03));
		}
		setlinewidth(Linewidth / 5);
		setcolor(EGEARGB(0X8F, 0X20, 0X20, 0X20));
		ege_ellipse(center_x - Ulength * (131 + 0.025 * 60), center_y - (11 + 60 * 0.15) * Ulength, Ulength * (3 + 60 * 0.03), Ulength * (3 + 60 * 0.03));

	}

	if (x > center_x - Ulength * 132.5 && x < center_x - Ulength * 126.5 && y>center_y - 14 * Ulength && y <= center_y - 9 * Ulength) {
		ege_rectangle(center_x - Ulength * 132.5, center_y - 14 * Ulength, Ulength * 6, Ulength * 5);

		if (GetAsyncKeyState(0x02) & 0x0001 && AT < 1) {
			AT_1++;

		}
	}
	if (x > center_x - Ulength * 132.5 && x < center_x - Ulength * 126.5 && y>center_y - 9 * Ulength && y <= center_y - 4 * Ulength) {
		ege_rectangle(center_x - Ulength * 132.5, center_y - 9 * Ulength, Ulength * 6, Ulength * 5);

		if (GetAsyncKeyState(0x02) & 0x0001 && AT > 0) {
			AT_1--;

		}
	}



	setfillcolor(BLACK);
	ege_fillrect(center_x - Ulength * 138, center_y + 10.5 * Ulength, Ulength * 16, Ulength * 16);
	ege_fillrect(center_x - Ulength * 119, center_y + 10.5 * Ulength, Ulength * 16, Ulength * 16);
	ege_fillrect(center_x - Ulength * 70, center_y + 10.5 * Ulength, Ulength * 16, Ulength * 16);

	setfillcolor(EGEARGB(0XFF, 0X40, 0X40, 0X40));
	ege_fillrect(center_x - Ulength * 137, center_y + 11.5 * Ulength, Ulength * 14, Ulength * 14);
	ege_fillrect(center_x - Ulength * 118, center_y + 11.5 * Ulength, Ulength * 14, Ulength * 14);
	ege_fillrect(center_x - Ulength * 69, center_y + 11.5 * Ulength, Ulength * 14, Ulength * 14);

	setfillcolor(BLACK);
	ege_fillrect(center_x - Ulength * 136.5, center_y + 12 * Ulength, Ulength * 13, Ulength * 13);
	ege_fillrect(center_x - Ulength * 117.5, center_y + 12 * Ulength, Ulength * 13, Ulength * 13);
	ege_fillrect(center_x - Ulength * 68.5, center_y + 12 * Ulength, Ulength * 13, Ulength * 13);

	if (x > center_x - Ulength * 136.5 && x < center_x - Ulength * 123.5 && y>center_y + 12 * Ulength && y <= center_y + 25 * Ulength) {


		if (GetAsyncKeyState(0x02) & 0x0001) {
			setfillcolor(BLACK);
			ege_fillrect(center_x - Ulength * 137, center_y + 11.5 * Ulength, Ulength * 14, Ulength * 14);
			if (N1 == 0) {
				N1 = 1;
			}
			else if (N1 == 1) {
				N1 = 0;
			}
		}

	}

	if (x > center_x - Ulength * 117.5 && x < center_x - Ulength * 104.5 && y>center_y + 12 * Ulength && y <= center_y + 25 * Ulength) {


		if (GetAsyncKeyState(0x02) & 0x0001) {
			setfillcolor(BLACK);
			ege_fillrect(center_x - Ulength * 118, center_y + 11.5 * Ulength, Ulength * 14, Ulength * 14);

			if (SPEED == 0) {
				SPEED_1 = 1;
			}
			else if (SPEED == 1) {
				SPEED_1 = 0;
			}
		}

	}

	if (x > center_x - Ulength * 68.5 && x < center_x - Ulength * 55.5 && y>center_y + 12 * Ulength && y <= center_y + 25 * Ulength) {


		if (GetAsyncKeyState(0x02) & 0x0001) {
			setfillcolor(BLACK);
			ege_fillrect(center_x - Ulength * 69, center_y + 11.5 * Ulength, Ulength * 14, Ulength * 14);
			if (LVLCHG == 0) {
				LVLCHG = 1;
			}
			else if (LVLCHG == 1) {
				LVLCHG = 0;
			}
		}

	}



	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	setlinewidth(Linewidth / 5);
	ege_line(center_x - Ulength * 138, center_y + 10.5 * Ulength, center_x - Ulength * 122, center_y + 10.5 * Ulength);
	ege_line(center_x - Ulength * 119, center_y + 10.5 * Ulength, center_x - Ulength * 103, center_y + 10.5 * Ulength);
	ege_line(center_x - Ulength * 70, center_y + 10.5 * Ulength, center_x - Ulength * 54, center_y + 10.5 * Ulength);
	setlinewidth(Linewidth * 4 / 7);
	setfont(Ulength * 4.5, Ulength * 2.5, "Bahnschrift");
	ege_drawtext("N1", center_x - Ulength * 130, center_y + 16.5 * Ulength);
	ege_drawtext("SPEED", center_x - Ulength * 111, center_y + 16.5 * Ulength);
	ege_drawtext("IAS/MACH", center_x - Ulength * 96, center_y - 25 * Ulength);
	setfont(Ulength * 4, Ulength * 2.5, "Bahnschrift");
	ege_drawtext("C/O", center_x - Ulength * 103, center_y - 7.3 * Ulength);
	ege_drawtext("SPD", center_x - Ulength * 60, center_y + 1 * Ulength);
	ege_drawtext("INTV", center_x - Ulength * 60, center_y + 3.7 * Ulength);
	ege_drawtext("LVL CHG", center_x - Ulength * 61.8, center_y + 16.5 * Ulength);
	setfont(Ulength * 4.5, Ulength * 2.5, "Bahnschrift");
	ege_ellipse(center_x - Ulength * 109, center_y - 6.5 * Ulength, 12 * Ulength, 12 * Ulength);
	ege_ellipse(center_x - Ulength * 76, center_y - 6.5 * Ulength, 12 * Ulength, 12 * Ulength);
	ege_ellipse(center_x - Ulength * 95, center_y - 2.5 * Ulength, 17 * Ulength, 17 * Ulength);
	ege_line(center_x - Ulength * 97.5, center_y - 5 * Ulength, center_x - Ulength * 95.5, center_y - 6.5 * Ulength);
	ege_line(center_x - Ulength * 95.5, center_y - 6.5 * Ulength, center_x - Ulength * 95.5, center_y - 9.5 * Ulength);
	ege_line(center_x - Ulength * 86.5, center_y - 3.5 * Ulength, center_x - Ulength * 86.5, center_y - 9.5 * Ulength);
	ege_line(center_x - Ulength * 96, center_y + 7.5 * Ulength, center_x - Ulength * 102, center_y + 9.5 * Ulength);
	ege_line(center_x - Ulength * 77, center_y + 7.5 * Ulength, center_x - Ulength * 71, center_y + 9.5 * Ulength);



	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));

	setfont(Ulength * 4, Ulength * 2.5, "Bahnschrift");
	ege_drawtext("C/O", center_x - Ulength * 103, center_y - 7.3 * Ulength);
	ege_drawtext("SPD", center_x - Ulength * 60, center_y + 1 * Ulength);
	ege_drawtext("INTV", center_x - Ulength * 60, center_y + 3.7 * Ulength);
	ege_drawtext("LVL CHG", center_x - Ulength * 61.8, center_y + 16.5 * Ulength);
	setfont(Ulength * 4.5, Ulength * 2.5, "Bahnschrift");
	ege_ellipse(center_x - Ulength * 109, center_y - 6.5 * Ulength, 12 * Ulength, 12 * Ulength);
	ege_ellipse(center_x - Ulength * 76, center_y - 6.5 * Ulength, 12 * Ulength, 12 * Ulength);
	ege_ellipse(center_x - Ulength * 95, center_y - 2.5 * Ulength, 17 * Ulength, 17 * Ulength);
	ege_drawtext("N1", center_x - Ulength * 130, center_y + 16.5 * Ulength);
	ege_drawtext("SPEED", center_x - Ulength * 111, center_y + 16.5 * Ulength);
	if (SPEED == 1 && AT == 1) {
		button_green_light(center_x - Ulength * 111, center_y + 22 * Ulength, side * 0.16);
	}
	ege_drawtext("IAS/MACH", center_x - Ulength * 96, center_y - 25 * Ulength);
	ege_line(center_x - Ulength * 97.5, center_y - 5 * Ulength, center_x - Ulength * 95.5, center_y - 6.5 * Ulength);
	ege_line(center_x - Ulength * 95.5, center_y - 6.5 * Ulength, center_x - Ulength * 95.5, center_y - 9.5 * Ulength);
	ege_line(center_x - Ulength * 86.5, center_y - 3.5 * Ulength, center_x - Ulength * 86.5, center_y - 9.5 * Ulength);
	ege_line(center_x - Ulength * 96, center_y + 7.5 * Ulength, center_x - Ulength * 102, center_y + 9.5 * Ulength);
	ege_line(center_x - Ulength * 77, center_y + 7.5 * Ulength, center_x - Ulength * 71, center_y + 9.5 * Ulength);





	setfillcolor(EGEARGB(0XFF, 0X26, 0X2B, 0X2C));

	ege_fillrect(center_x - Ulength * 116, center_y - 23 * Ulength, Ulength * 43, Ulength * 13);



	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));

	ege_fillrect(center_x - Ulength * 115, center_y - 22 * Ulength, Ulength * 41, Ulength * 11);
	ege_fillellipse(center_x - Ulength * 106, center_y - 3.5 * Ulength, 6 * Ulength, 6 * Ulength);
	ege_fillellipse(center_x - Ulength * 73, center_y - 3.5 * Ulength, 6 * Ulength, 6 * Ulength);

	setfillcolor(EGEARGB(0XFF, 0X15, 0X15, 0X15));
	ege_fillrect(center_x - Ulength * 114, center_y - 21.5 * Ulength, Ulength * 39, Ulength * 10);
	ege_fillellipse(center_x - Ulength * 105.5, center_y - 3 * Ulength, 5 * Ulength, 5 * Ulength);
	ege_fillellipse(center_x - Ulength * 72.5, center_y - 3 * Ulength, 5 * Ulength, 5 * Ulength);

	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillrect(center_x - Ulength * 113, center_y - 21 * Ulength, Ulength * 37, Ulength * 9);

	if (x > center_x - Ulength * 106 && x < center_x - Ulength * 100 && y>center_y - 3.5 * Ulength && y <= center_y + 2.5 * Ulength) {


		if (GetAsyncKeyState(0x02) & 0x0001) {
			setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
			ege_fillellipse(center_x - Ulength * 106.5, center_y - 4 * Ulength, 7 * Ulength, 7 * Ulength);
			if (CO == 0) {
				CO = 1;
			}
			else if (CO == 1) {
				CO = 0;
			}
		}

	}
	if (x > center_x - Ulength * 73 && x < center_x - Ulength * 67 && y>center_y - 3.5 * Ulength && y <= center_y + 2.5 * Ulength) {


		if (GetAsyncKeyState(0x02) & 0x0001) {
			setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
			ege_fillellipse(center_x - Ulength * 73.5, center_y - 4 * Ulength, 7 * Ulength, 7 * Ulength);
			if (SPDINTV == 0) {
				SPDINTV = 1;
			}
			else if (SPDINTV == 1) {
				SPDINTV = 0;
			}
		}

	}

	//1显示左边，0显示右边
	if (CO == 0) {


		setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
		setfont(Ulength * 10, Ulength * 2.5, "DigifaceWide");
		char nums_2[64];//右
		sprintf_s(nums_2, "%03d", CO_2 + CO_2_change);
		ege_drawtext(nums_2, center_x - Ulength * 84, center_y - 16 * Ulength);


	}
	if (CO == 1) {

		setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
		setfont(Ulength * 10, Ulength * 2.5, "DigifaceWide");
		char nums_2[64];//左
		ege_drawtext(".", center_x - Ulength * 110, center_y - 16 * Ulength);
		sprintf_s(nums_2, "%d", CO_1 + CO_1_change);
		ege_drawtext(nums_2, center_x - Ulength * 103, center_y - 16 * Ulength);

	}

	setfillcolor(EGEARGB(0XFF, 0X95, 0X88, 0X70));

	ege_fillellipse(center_x - Ulength * 93, center_y - 0.5 * Ulength, 13 * Ulength, 13 * Ulength);

	setcolor(EGEARGB(0X30, 0X50, 0X50, 0X50));
	for (int i = 0; i < 360; i += 10) {
		ege_line(center_x - 88.5 * Ulength - (6.5 * Ulength) * cos((i + INSMACHangle) * PI / 180), center_y + 6 * Ulength - (6.5 * Ulength) * sin((i + INSMACHangle) * PI / 180),
			center_x - 86 * Ulength - (6.5 * Ulength) * cos((i + INSMACHangle) * PI / 180), center_y + 6 * Ulength - (6.5 * Ulength) * sin((i + INSMACHangle) * PI / 180));
	}


	setfillcolor(EGEARGB(0XFF, 0X49, 0X48, 0X46));
	ege_fillellipse(center_x - 95 * Ulength, center_y - 0.5 * Ulength, 13 * Ulength, 13 * Ulength);

	setcolor(EGEARGB(0XFF, 0X39, 0X38, 0X36));
	ege_ellipse(center_x - 94.5 * Ulength, center_y - 0 * Ulength, 12 * Ulength, 12 * Ulength);



	if (GetAsyncKeyState(0x04) & 0x8000) {
		if (longPanel_speed_is_down == 0) {
			longPanel_speed_is_down = 1;
			mousepos(&longPanel_mouse_x, &longPanel_mouse_y);
			longPanel_mouse_x_cur = longPanel_mouse_x;
			longPanel_mouse_y_cur = longPanel_mouse_y;
		}
		if (longPanel_speed_is_down == 1) {
			if ((longPanel_mouse_x_cur >= center_x - 95 * Ulength)
				&& (longPanel_mouse_x_cur <= center_x - 82 * Ulength)
				&& (longPanel_mouse_y_cur >= center_y - 0.5 * Ulength)
				&& (longPanel_mouse_y_cur <= center_y + 12.5 * Ulength)) {


				mousepos(&longPanel_mouse_x, &longPanel_mouse_y);
				if (longPanel_mouse_y > longPanel_mouse_y_cur) {

					INSMACHangle += (longPanel_mouse_y - longPanel_mouse_y_cur) / 70;
					if (CO == 0) {
						if (CO_2 + CO_2_change < 392 && CO_2 + CO_2_change >= 0) {
							CO_2_change += (int)((longPanel_mouse_y - longPanel_mouse_y_cur) / 70);
							CO_1_change = (int)((CO_2 + CO_2_change) / 392.0 * 61) - CO_1;
						}
						else if (CO_2 + CO_2_change >= 392) {
							CO_2_change = 392 - CO_2;

						}
						else if (CO_2 + CO_2_change < 0) {
							CO_2_change = -CO_2;

						}
					}
					if (CO == 1) {
						if (CO_2 + CO_2_change < 538 && CO_2 + CO_2_change >= 0) {
							CO_2_change += (int)((longPanel_mouse_y - longPanel_mouse_y_cur) / 70);
							CO_1_change = (int)((CO_2 + CO_2_change) / 538.0 * 84) - CO_1;
						}
						else if (CO_2 + CO_2_change >= 538) {
							CO_2_change = 538 - CO_2;

						}
						else if (CO_2 + CO_2_change < 0) {
							CO_2_change = -CO_2;

						}
					}

				}
				else {
					INSMACHangle += (longPanel_mouse_y - longPanel_mouse_y_cur) / 70;
					if (CO == 0) {
						if (CO_2 + CO_2_change < 392 && CO_2 + CO_2_change >= 0) {
							CO_2_change += (int)((longPanel_mouse_y - longPanel_mouse_y_cur) / 70);
							CO_1_change = (int)((CO_2 + CO_2_change) / 392.0 * 61) - CO_1;
						}
						else if (CO_2 + CO_2_change >= 392) {
							CO_2_change = 392 - CO_2;

						}
						else if (CO_2 + CO_2_change < 0) {
							CO_2_change = -CO_2;

						}
					}
					if (CO == 1) {
						if (CO_2 + CO_2_change < 538 && CO_2 + CO_2_change >= 0) {
							CO_2_change += (int)((longPanel_mouse_y - longPanel_mouse_y_cur) / 70);
							CO_1_change = (int)((CO_2 + CO_2_change) / 538.0 * 84) - CO_1;
						}
						else if (CO_2 + CO_2_change >= 538) {
							CO_2_change = 538 - CO_2;

						}
						else if (CO_2 + CO_2_change < 0) {
							CO_2_change = -CO_2;

						}
					}
				}
			}
		}

	}
	else if (longPanel_speed_is_down == 1) {
		longPanel_speed_is_down = 0;
	}



	setfillcolor(BLACK);

	ege_fillrect(center_x - Ulength * 70, center_y - 27 * Ulength, Ulength * 16, Ulength * 16);
	ege_fillrect(center_x - Ulength * 20, center_y - 27 * Ulength, Ulength * 16, Ulength * 16);
	ege_fillrect(center_x - Ulength * 20, center_y - 9.5 * Ulength, Ulength * 16, Ulength * 16);
	ege_fillrect(center_x - Ulength * 20, center_y + 10.5 * Ulength, Ulength * 16, Ulength * 16);
	ege_fillrect(center_x - Ulength * 45, center_y + 10.5 * Ulength, Ulength * 16, Ulength * 16);
	ege_fillrect(center_x + Ulength * 15, center_y + 10.5 * Ulength, Ulength * 16, Ulength * 16);
	ege_fillrect(center_x + Ulength * 35, center_y + 10.5 * Ulength, Ulength * 16, Ulength * 16);


	setfillcolor(EGEARGB(0XFF, 0X40, 0X40, 0X40));

	ege_fillrect(center_x - Ulength * 69, center_y - 26 * Ulength, Ulength * 14, Ulength * 14);
	ege_fillrect(center_x - Ulength * 19, center_y - 26 * Ulength, Ulength * 14, Ulength * 14);
	ege_fillrect(center_x - Ulength * 19, center_y - 8.5 * Ulength, Ulength * 14, Ulength * 14);
	ege_fillrect(center_x - Ulength * 19, center_y + 11.5 * Ulength, Ulength * 14, Ulength * 14);
	ege_fillrect(center_x - Ulength * 44, center_y + 11.5 * Ulength, Ulength * 14, Ulength * 14);
	ege_fillrect(center_x + Ulength * 16, center_y + 11.5 * Ulength, Ulength * 14, Ulength * 14);
	ege_fillrect(center_x + Ulength * 36, center_y + 11.5 * Ulength, Ulength * 14, Ulength * 14);

	setfillcolor(BLACK);

	ege_fillrect(center_x - Ulength * 68.5, center_y - 25.5 * Ulength, Ulength * 13, Ulength * 13);
	ege_fillrect(center_x - Ulength * 18.5, center_y - 25.5 * Ulength, Ulength * 13, Ulength * 13);
	ege_fillrect(center_x - Ulength * 18.5, center_y - 8 * Ulength, Ulength * 13, Ulength * 13);
	ege_fillrect(center_x - Ulength * 18.5, center_y + 12 * Ulength, Ulength * 13, Ulength * 13);
	ege_fillrect(center_x - Ulength * 43.5, center_y + 12 * Ulength, Ulength * 13, Ulength * 13);
	ege_fillrect(center_x + Ulength * 16.5, center_y + 12 * Ulength, Ulength * 13, Ulength * 13);
	ege_fillrect(center_x + Ulength * 36.5, center_y + 12 * Ulength, Ulength * 13, Ulength * 13);

	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	setlinewidth(Linewidth / 5);
	ege_line(center_x - Ulength * 70, center_y - 27 * Ulength, center_x - Ulength * 54, center_y - 27 * Ulength);
	ege_line(center_x - Ulength * 20, center_y - 27 * Ulength, center_x - Ulength * 4, center_y - 27 * Ulength);
	ege_line(center_x - Ulength * 20, center_y - 9.5 * Ulength, center_x - Ulength * 4, center_y - 9.5 * Ulength);
	ege_line(center_x - Ulength * 20, center_y + 10.5 * Ulength, center_x - Ulength * 4, center_y + 10.5 * Ulength);
	ege_line(center_x - Ulength * 45, center_y + 10.5 * Ulength, center_x - Ulength * 29, center_y + 10.5 * Ulength);
	ege_line(center_x + Ulength * 15, center_y + 10.5 * Ulength, center_x + Ulength * 31, center_y + 10.5 * Ulength);
	ege_line(center_x + Ulength * 35, center_y + 10.5 * Ulength, center_x + Ulength * 51, center_y + 10.5 * Ulength);
	setlinewidth(Linewidth * 4 / 7);
	if (x > center_x + Ulength * 16 && x < center_x + Ulength * 30 && y>center_y + 12 * Ulength && y <= center_y + 25 * Ulength) {

		if (GetAsyncKeyState(0x02) & 0x0001) {
			setfillcolor(BLACK);
			ege_fillrect(center_x + Ulength * 15.5, center_y + 11 * Ulength, Ulength * 15, Ulength * 15);

			if (ALTHLD == 0) {
				ALTHLD_1 = 1;
			}
			else if (ALTHLD == 1) {
				ALTHLD_1 = 0;
			}
		}
	}
	if (x > center_x + Ulength * 36 && x < center_x + Ulength * 50 && y>center_y + 12 * Ulength && y <= center_y + 25 * Ulength) {

		if (GetAsyncKeyState(0x02) & 0x0001) {
			setfillcolor(BLACK);
			ege_fillrect(center_x + Ulength * 35.5, center_y + 11 * Ulength, Ulength * 15, Ulength * 15);

			if (VS == 0) {
				VS_1 = 1;
			}
			else if (VS == 1) {
				VS_1 = 0;
			}
		}
	}

	if (x > center_x - Ulength * 70 && x < center_x - Ulength * 54 && y>center_y - 26 * Ulength && y <= center_y - 10 * Ulength) {

		if (GetAsyncKeyState(0x02) & 0x0001) {
			setfillcolor(BLACK);
			ege_fillrect(center_x - Ulength * 70.5, center_y - 27.5 * Ulength, Ulength * 17, Ulength * 17);

			if (VNAV == 0) {
				VNAV = 1;
			}
			else if (VNAV == 1) {
				VNAV = 0;
			}
		}
	}
	if (x > center_x - Ulength * 20 && x < center_x - Ulength * 4 && y>center_y - 26 * Ulength && y <= center_y - 10 * Ulength) {

		if (GetAsyncKeyState(0x02) & 0x0001) {
			setfillcolor(BLACK);
			ege_fillrect(center_x - Ulength * 20.5, center_y - 27.5 * Ulength, Ulength * 17, Ulength * 17);

			if (LNAV == 0) {
				LNAV = 1;
			}
			else if (LNAV == 1) {
				LNAV = 0;
			}
		}
	}
	if (x > center_x - Ulength * 20 && x < center_x - Ulength * 4 && y>center_y - 8 * Ulength && y <= center_y + 5 * Ulength) {

		if (GetAsyncKeyState(0x02) & 0x0001) {
			setfillcolor(BLACK);
			ege_fillrect(center_x - Ulength * 20.5, center_y - 9.5 * Ulength, Ulength * 17, Ulength * 17);

			if (VORLOC == 0) {
				VORLOC = 1;
			}
			else if (VORLOC == 1) {
				VORLOC = 0;
			}
		}
	}
	if (x > center_x - Ulength * 20 && x < center_x - Ulength * 4 && y>center_y + 12 * Ulength && y <= center_y + 25 * Ulength) {

		if (GetAsyncKeyState(0x02) & 0x0001) {
			setfillcolor(BLACK);
			ege_fillrect(center_x - Ulength * 20.5, center_y + 10.5 * Ulength, Ulength * 17, Ulength * 17);

			if (APP == 0) {
				APP = 1;
			}
			else if (APP == 1) {
				APP = 0;
			}
		}
	}

	if (x > center_x - Ulength * 45 && x < center_x - Ulength * 4 && y>center_y + 12 * Ulength && y <= center_y + 25 * Ulength) {

		if (GetAsyncKeyState(0x02) & 0x0001) {
			setfillcolor(BLACK);
			ege_fillrect(center_x - Ulength * 45.5, center_y + 10.5 * Ulength, Ulength * 17, Ulength * 17);

			if (HDGSEL == 0) {
				HDGSEL_1 = 1;
			}
			else if (HDGSEL == 1) {
				HDGSEL_1 = 0;
			}
		}
	}


	setfont(Ulength * 4, Ulength * 2.5, "Bahnschrift");
	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_drawtext("VNAV", center_x - Ulength * 62, center_y - 21.5 * Ulength);
	ege_drawtext("LNAV", center_x - Ulength * 12, center_y - 21.5 * Ulength);
	ege_drawtext("APP", center_x - Ulength * 12, center_y + 16.5 * Ulength);
	ege_drawtext("HEADING", center_x - Ulength * 36, center_y - 25 * Ulength);
	ege_drawtext("ALTITUDE", center_x + Ulength * 24, center_y - 25 * Ulength);
	ege_drawtext("VERT SPEED", center_x + Ulength * 76, center_y - 25 * Ulength);
	ege_drawtext("V/S", center_x + Ulength * 43, center_y + 16.5 * Ulength);

	setfont(Ulength * 3.5, Ulength * 2.5, "Bahnschrift");
	ege_drawtext("VOR LOC", center_x - Ulength * 12, center_y - 3.5 * Ulength);
	ege_drawtext("HDG SEL", center_x - Ulength * 37, center_y + 16.5 * Ulength);
	ege_drawtext("ALT HLD", center_x + Ulength * 23, center_y + 16.5 * Ulength);

	setfont(Ulength * 4, Ulength * 2.5, "Bahnschrift");
	ege_line(center_x - 36.5 * Ulength, center_y + 1 * Ulength, center_x - 36.5 * Ulength, center_y - 9 * Ulength);
	ege_line(center_x - 36.5 * Ulength, center_y + 1 * Ulength,
		center_x - 36.5 * Ulength - (15 * Ulength) * cos(30 * PI / 180), center_y - (15 * Ulength) * sin(30 * PI / 180));
	ege_line(center_x - 36.5 * Ulength, center_y + 1 * Ulength,
		center_x - 36.5 * Ulength - (14 * Ulength) * cos(150 * PI / 180), center_y - (14 * Ulength) * sin(150 * PI / 180));
	ege_line(center_x - 36.5 * Ulength, center_y + 1 * Ulength,
		center_x - 36.5 * Ulength - (11 * Ulength) * cos(120 * PI / 180), center_y - (11 * Ulength) * sin(120 * PI / 180));
	ege_line(center_x - 36.5 * Ulength, center_y + 1 * Ulength,
		center_x - 36.5 * Ulength - (11 * Ulength) * cos(60 * PI / 180), center_y - (11 * Ulength) * sin(60 * PI / 180));


	ege_drawtext("10", center_x - 36.5 * Ulength - (16.5 * Ulength) * cos(30 * PI / 180), center_y - (16.5 * Ulength) * sin(30 * PI / 180));
	ege_drawtext("30", center_x - 36.5 * Ulength - (16 * Ulength) * cos(150 * PI / 180), center_y - (16 * Ulength) * sin(150 * PI / 180));


	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_drawtext("VNAV", center_x - Ulength * 62, center_y - 21.5 * Ulength);
	ege_drawtext("LNAV", center_x - Ulength * 12, center_y - 21.5 * Ulength);
	ege_drawtext("APP", center_x - Ulength * 12, center_y + 16.5 * Ulength);
	ege_drawtext("HEADING", center_x - Ulength * 36, center_y - 25 * Ulength);
	ege_drawtext("ALTITUDE", center_x + Ulength * 24, center_y - 25 * Ulength);
	ege_drawtext("VERT SPEED", center_x + Ulength * 76, center_y - 25 * Ulength);
	ege_drawtext("V/S", center_x + Ulength * 43, center_y + 16.5 * Ulength);
	if (VS == 1 || VS_1 == 1) {
		button_green_light(center_x + 43 * Ulength, center_y + 22 * Ulength, side * 0.16);
	}
	setfont(Ulength * 3.5, Ulength * 2.5, "Bahnschrift");
	ege_drawtext("VOR LOC", center_x - Ulength * 12, center_y - 3.5 * Ulength);
	ege_drawtext("HDG SEL", center_x - Ulength * 37, center_y + 16.5 * Ulength);
	if (HDGSEL == 1 || HDGSEL_1 == 1) {
		button_green_light(center_x - Ulength * 37, center_y + 22 * Ulength, side * 0.16);
	}
	ege_drawtext("ALT HLD", center_x + Ulength * 23, center_y + 16.5 * Ulength);
	if (ALTHLD == 1 || ALTHLD_1 == 1) {
		button_green_light(center_x + 23 * Ulength, center_y + 22 * Ulength, side * 0.16);
	}
	setfont(Ulength * 4, Ulength * 2.5, "Bahnschrift");
	ege_line(center_x - 36.5 * Ulength, center_y + 1 * Ulength, center_x - 36.5 * Ulength, center_y - 9 * Ulength);
	ege_line(center_x - 36.5 * Ulength, center_y + 1 * Ulength,
		center_x - 36.5 * Ulength - (15 * Ulength) * cos(30 * PI / 180), center_y - (15 * Ulength) * sin(30 * PI / 180));
	ege_line(center_x - 36.5 * Ulength, center_y + 1 * Ulength,
		center_x - 36.5 * Ulength - (14 * Ulength) * cos(150 * PI / 180), center_y - (14 * Ulength) * sin(150 * PI / 180));
	ege_line(center_x - 36.5 * Ulength, center_y + 1 * Ulength,
		center_x - 36.5 * Ulength - (11 * Ulength) * cos(120 * PI / 180), center_y - (11 * Ulength) * sin(120 * PI / 180));
	ege_line(center_x - 36.5 * Ulength, center_y + 1 * Ulength,
		center_x - 36.5 * Ulength - (11 * Ulength) * cos(60 * PI / 180), center_y - (11 * Ulength) * sin(60 * PI / 180));


	ege_drawtext("10", center_x - 36.5 * Ulength - (16.5 * Ulength) * cos(30 * PI / 180), center_y - (16.5 * Ulength) * sin(30 * PI / 180));
	ege_drawtext("30", center_x - 36.5 * Ulength - (16 * Ulength) * cos(150 * PI / 180), center_y - (16 * Ulength) * sin(150 * PI / 180));


	setfillcolor(EGEARGB(0XFF, 0X26, 0X2B, 0X2C));

	ege_fillrect(center_x - Ulength * 49, center_y - 23 * Ulength, Ulength * 24, Ulength * 13);



	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));

	ege_fillrect(center_x - Ulength * 48, center_y - 22 * Ulength, Ulength * 22, Ulength * 11);


	setfillcolor(EGEARGB(0XFF, 0X15, 0X15, 0X15));
	ege_fillrect(center_x - Ulength * 47, center_y - 21.5 * Ulength, Ulength * 20, Ulength * 10);

	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillrect(center_x - Ulength * 46, center_y - 21 * Ulength, Ulength * 18, Ulength * 9);



	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	setfont(Ulength * 10, Ulength * 2.5, "DigifaceWide");
	char nums_3[64];//左上上
	sprintf_s(nums_3, "%03d", HEADING + HEADING_1_change);
	ege_drawtext(nums_3, center_x - Ulength * 37, center_y - 16 * Ulength);



	int centerTopknobnum_4 = 12;//中间旋钮最底层
	ege_point centerTopknobploypoints_4[12] = {
		{center_x - 36.5 * Ulength - Topknob_R1 * cos(HEADING_2 * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin(HEADING_2 * PI / 180)},
		{center_x - 36.5 * Ulength - Topknob_R1 * cos((HEADING_2 + 30) * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + 30) * PI / 180)},
		{center_x - 36.5 * Ulength - Topknob_R1 * cos((HEADING_2 + 60) * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + 60) * PI / 180)},
		{center_x - 36.5 * Ulength - Topknob_R1 * cos((HEADING_2 + 90) * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + 90) * PI / 180)},
		{center_x - 36.5 * Ulength - Topknob_R1 * cos((HEADING_2 + 120) * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + 120) * PI / 180)},
		{center_x - 36.5 * Ulength - Topknob_R1 * cos((HEADING_2 + 150) * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + 150) * PI / 180)},
		{center_x - 36.5 * Ulength - Topknob_R1 * cos((HEADING_2 + 180) * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + 180) * PI / 180)},
		{center_x - 36.5 * Ulength - Topknob_R1 * cos((HEADING_2 + 210) * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + 210) * PI / 180)},
		{center_x - 36.5 * Ulength - Topknob_R1 * cos((HEADING_2 + 240) * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + 240) * PI / 180)},
		{center_x - 36.5 * Ulength - Topknob_R1 * cos((HEADING_2 + 270) * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + 270) * PI / 180)},
		{center_x - 36.5 * Ulength - Topknob_R1 * cos((HEADING_2 + 300) * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + 300) * PI / 180)},
		{center_x - 36.5 * Ulength - Topknob_R1 * cos((HEADING_2 + 330) * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + 330) * PI / 180)},

	};
	ege_setpattern_lineargradient(center_x - 35.5 * Ulength - Topknob_R1, center_y + 2 * Ulength - Topknob_R1, EGEARGB(0XFF, 0X10, 0X10, 0X10),
		center_x - 37.5 * Ulength + Topknob_R1, center_y + 0.8 * Ulength + Topknob_R1, EGEARGB(0XFF, 0X7D, 0X7F, 0X7B));
	ege_fillpoly(centerTopknobnum_4, centerTopknobploypoints_4);
	ege_setpattern_none();

	setcolor(EGEARGB(0X2F, 0X50, 0X50, 0X50));
	for (int i = 0; i < 360; i += 30) {
		ege_line(center_x - 36.5 * Ulength - Topknob_R1 * cos((HEADING_2 + i) * PI / 180), center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + i) * PI / 180),
			center_x - 38 * Ulength - Topknob_R1 * cos((HEADING_2 + i) * PI / 180), center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + i) * PI / 180));
	}
	setlinewidth(Linewidth * 3);
	setcolor(EGEARGB(0XFF, 0X3A, 0X35, 0X2F));
	ege_line(center_x - 36.5 * Ulength, center_y + 1 * Ulength,
		center_x - 36.5 * Ulength - (Topknob_R1 - Ulength / 3) * cos(HEADING_2 * PI / 180), center_y + 1 * Ulength - (Topknob_R1 - Ulength / 3) * sin(HEADING_2 * PI / 180));
	setlinewidth(Linewidth * 1.1);
	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_line(center_x - 36.5 * Ulength, center_y + 1 * Ulength,
		center_x - 36.5 * Ulength - (Topknob_R1 - Ulength / 3) * cos(HEADING_2 * PI / 180), center_y + 1 * Ulength - (Topknob_R1 - Ulength / 3) * sin(HEADING_2 * PI / 180));

	setlinewidth(Linewidth * 1.1);
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_line(center_x - 36.5 * Ulength, center_y + 1 * Ulength,
		center_x - 36.5 * Ulength - (Topknob_R1 - Ulength / 3) * cos(HEADING_2 * PI / 180), center_y + 1 * Ulength - (Topknob_R1 - Ulength / 3) * sin(HEADING_2 * PI / 180));

	setlinewidth(Linewidth / 2);
	int centerTopknobnum_3 = 12;//中间旋钮倒数第二层
	ege_point centerTopknobploypoints_3[12] = {
		{center_x - 38 * Ulength - Topknob_R1 * cos(HEADING_2 * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin(HEADING_2 * PI / 180)},
		{center_x - 38 * Ulength - Topknob_R1 * cos((HEADING_2 + 30) * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + 30) * PI / 180)},
		{center_x - 38 * Ulength - Topknob_R1 * cos((HEADING_2 + 60) * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + 60) * PI / 180)},
		{center_x - 38 * Ulength - Topknob_R1 * cos((HEADING_2 + 90) * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + 90) * PI / 180)},
		{center_x - 38 * Ulength - Topknob_R1 * cos((HEADING_2 + 120) * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + 120) * PI / 180)},
		{center_x - 38 * Ulength - Topknob_R1 * cos((HEADING_2 + 150) * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + 150) * PI / 180)},
		{center_x - 38 * Ulength - Topknob_R1 * cos((HEADING_2 + 180) * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + 180) * PI / 180)},
		{center_x - 38 * Ulength - Topknob_R1 * cos((HEADING_2 + 210) * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + 210) * PI / 180)},
		{center_x - 38 * Ulength - Topknob_R1 * cos((HEADING_2 + 240) * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + 240) * PI / 180)},
		{center_x - 38 * Ulength - Topknob_R1 * cos((HEADING_2 + 270) * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + 270) * PI / 180)},
		{center_x - 38 * Ulength - Topknob_R1 * cos((HEADING_2 + 300) * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + 300) * PI / 180)},
		{center_x - 38 * Ulength - Topknob_R1 * cos((HEADING_2 + 330) * PI / 180) ,center_y + 1 * Ulength - Topknob_R1 * sin((HEADING_2 + 330) * PI / 180)},

	};
	ege_setpattern_lineargradient(center_x - 37 * Ulength - Topknob_R1, center_y + 2 * Ulength - Topknob_R1, EGEARGB(0XFF, 0X6B, 0X6B, 0X69),
		center_x - 39 * Ulength + Topknob_R1, center_y + 0 * Ulength + Topknob_R1, EGEARGB(0XFF, 0X3D, 0X3C, 0X39));
	ege_fillpoly(centerTopknobnum_3, centerTopknobploypoints_3);
	ege_setpattern_none();
	setlinewidth(Linewidth * 3);
	setcolor(EGEARGB(0XFF, 0X3A, 0X35, 0X2F));
	ege_line(center_x - 38 * Ulength, center_y + 1 * Ulength,
		center_x - 38 * Ulength - (Topknob_R1 - Ulength / 2) * cos(HEADING_2 * PI / 180), center_y + 1 * Ulength - (Topknob_R1 - Ulength / 2) * sin(HEADING_2 * PI / 180));

	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	setlinewidth(Linewidth * 1.1);

	ege_line(center_x - 38 * Ulength, center_y + 1 * Ulength,
		center_x - 38 * Ulength - (Topknob_R1 - Ulength / 2) * cos(HEADING_2 * PI / 180), center_y + 1 * Ulength - (Topknob_R1 - Ulength / 2) * sin(HEADING_2 * PI / 180));

	setlinewidth(Linewidth * 1.1);
	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_line(center_x - 38 * Ulength, center_y + 1 * Ulength,
		center_x - 38 * Ulength - (Topknob_R1 - Ulength / 2) * cos(HEADING_2 * PI / 180), center_y + 1 * Ulength - (Topknob_R1 - Ulength / 2) * sin(HEADING_2 * PI / 180));

	if (x < center_x - 36.5 * Ulength + Topknob_R1 && x> center_x - 41 * Ulength + Topknob_R1 && y > center_y + 2 * Ulength - Topknob_R1 && y < center_y + 2 * Ulength + Topknob_R1) {
		ege_rectangle(center_x - 41 * Ulength + Topknob_R1, center_y + 2 * Ulength - Topknob_R1, 5 * Ulength, 2 * Topknob_R1);
		if (GetAsyncKeyState(0x02) & 0x0001) {

			if (HEADING_2 < 150) {
				HEADING_2 += 30;
			}
		}
	}

	if (x < center_x - 51.5 * Ulength + Topknob_R1 && x> center_x - 56 * Ulength + Topknob_R1 && y > center_y + 2 * Ulength - Topknob_R1 && y < center_y + 2 * Ulength + Topknob_R1) {
		ege_rectangle(center_x - 56 * Ulength + Topknob_R1, center_y + 2 * Ulength - Topknob_R1, 5 * Ulength, 2 * Topknob_R1);
		if (GetAsyncKeyState(0x02) & 0x0001) {

			if (HEADING_2 > 0) {
				HEADING_2 -= 30;
			}
		}
	}





	setlinewidth(Linewidth / 2);

	int centerTopknobnum_2 = 12;//中间旋钮倒数第三层
	ege_point centerTopknobploypoints_2[12] = {
		{center_x - 38 * Ulength - Topknob_R2 * cos(HEADING_1 * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin(HEADING_1 * PI / 180)},
		{center_x - 38 * Ulength - Topknob_R2 * cos((HEADING_1 + 30) * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + 30) * PI / 180)},
		{center_x - 38 * Ulength - Topknob_R2 * cos((HEADING_1 + 60) * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + 60) * PI / 180)},
		{center_x - 38 * Ulength - Topknob_R2 * cos((HEADING_1 + 90) * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + 90) * PI / 180)},
		{center_x - 38 * Ulength - Topknob_R2 * cos((HEADING_1 + 120) * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + 120) * PI / 180)},
		{center_x - 38 * Ulength - Topknob_R2 * cos((HEADING_1 + 150) * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + 150) * PI / 180)},
		{center_x - 38 * Ulength - Topknob_R2 * cos((HEADING_1 + 180) * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + 180) * PI / 180)},
		{center_x - 38 * Ulength - Topknob_R2 * cos((HEADING_1 + 210) * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + 210) * PI / 180)},
		{center_x - 38 * Ulength - Topknob_R2 * cos((HEADING_1 + 240) * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + 240) * PI / 180)},
		{center_x - 38 * Ulength - Topknob_R2 * cos((HEADING_1 + 270) * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + 270) * PI / 180)},
		{center_x - 38 * Ulength - Topknob_R2 * cos((HEADING_1 + 300) * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + 300) * PI / 180)},
		{center_x - 38 * Ulength - Topknob_R2 * cos((HEADING_1 + 330) * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + 330) * PI / 180)},





	};
	ege_setpattern_lineargradient(center_x - 37 * Ulength - Topknob_R2, center_y + 2 * Ulength - Topknob_R2, EGEARGB(0XFF, 0X10, 0X10, 0X10),
		center_x - 39 * Ulength + Topknob_R2, center_y + 0 * Ulength + Topknob_R2, EGEARGB(0XFF, 0X7D, 0X7F, 0X7B));
	ege_fillpoly(centerTopknobnum_2, centerTopknobploypoints_2);
	ege_setpattern_none();

	setcolor(EGEARGB(0X2F, 0X50, 0X50, 0X50));
	for (int i = 0; i < 360; i += 30) {
		ege_line(center_x - 38 * Ulength - Topknob_R2 * cos((HEADING_1 + i) * PI / 180), center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + i) * PI / 180),
			center_x - 39 * Ulength - Topknob_R2 * cos((HEADING_1 + i) * PI / 180), center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + i) * PI / 180));
	}

	int centerTopknobnum_1 = 12;//中间旋钮倒数第四层
	ege_point centerTopknobploypoints_1[12] = {
		{center_x - 39 * Ulength - Topknob_R2 * cos(HEADING_1 * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin(HEADING_1 * PI / 180)},
		{center_x - 39 * Ulength - Topknob_R2 * cos((HEADING_1 + 30) * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + 30) * PI / 180)},
		{center_x - 39 * Ulength - Topknob_R2 * cos((HEADING_1 + 60) * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + 60) * PI / 180)},
		{center_x - 39 * Ulength - Topknob_R2 * cos((HEADING_1 + 90) * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + 90) * PI / 180)},
		{center_x - 39 * Ulength - Topknob_R2 * cos((HEADING_1 + 120) * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + 120) * PI / 180)},
		{center_x - 39 * Ulength - Topknob_R2 * cos((HEADING_1 + 150) * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + 150) * PI / 180)},
		{center_x - 39 * Ulength - Topknob_R2 * cos((HEADING_1 + 180) * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + 180) * PI / 180)},
		{center_x - 39 * Ulength - Topknob_R2 * cos((HEADING_1 + 210) * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + 210) * PI / 180)},
		{center_x - 39 * Ulength - Topknob_R2 * cos((HEADING_1 + 240) * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + 240) * PI / 180)},
		{center_x - 39 * Ulength - Topknob_R2 * cos((HEADING_1 + 270) * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + 270) * PI / 180)},
		{center_x - 39 * Ulength - Topknob_R2 * cos((HEADING_1 + 300) * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + 300) * PI / 180)},
		{center_x - 39 * Ulength - Topknob_R2 * cos((HEADING_1 + 330) * PI / 180) ,center_y + 1 * Ulength - Topknob_R2 * sin((HEADING_1 + 330) * PI / 180)},





	};
	setfillcolor(EGEARGB(0XFF, 0X58, 0X58, 0X56));
	ege_fillpoly(centerTopknobnum_1, centerTopknobploypoints_1);

	if (GetAsyncKeyState(0x04) & 0x8000) {
		if (longPanel_speed_is_down == 0) {
			longPanel_speed_is_down = 1;
			mousepos(&longPanel_mouse_x, &longPanel_mouse_y);
			longPanel_mouse_x_cur = longPanel_mouse_x;
			longPanel_mouse_y_cur = longPanel_mouse_y;
		}
		if (longPanel_speed_is_down == 1) {
			if ((longPanel_mouse_x_cur >= center_x - 39 * Ulength - Topknob_R2)
				&& (longPanel_mouse_x_cur <= center_x - 39 * Ulength + Topknob_R2)
				&& (longPanel_mouse_y_cur >= center_y + 1 * Ulength - Topknob_R2)
				&& (longPanel_mouse_y_cur <= center_y + 1 * Ulength + Topknob_R2)) {


				mousepos(&longPanel_mouse_x, &longPanel_mouse_y);
				if (longPanel_mouse_y > longPanel_mouse_y_cur) {

					HEADING_1 += (longPanel_mouse_y - longPanel_mouse_y_cur) / 70;
					if (HEADING + HEADING_1_change < 360 && HEADING + HEADING_1_change>0) {
						HEADING_1_change += (int)((longPanel_mouse_y - longPanel_mouse_y_cur) / 70);
					}
					else if (HEADING + HEADING_1_change >= 360) {
						HEADING_1_change = 1 - HEADING;
						HEADING_1 = HEADING_1_change * 2;
					}
					else if (HEADING + HEADING_1_change <= 0) {
						HEADING_1_change = 359 - HEADING;
						HEADING_1 = HEADING_1_change * 2;
					}

				}
				else {
					HEADING_1 += (longPanel_mouse_y - longPanel_mouse_y_cur) / 70;
					if (HEADING + HEADING_1_change < 360 && HEADING + HEADING_1_change>0) {
						HEADING_1_change += (int)((longPanel_mouse_y - longPanel_mouse_y_cur) / 70);
					}
					else if (HEADING + HEADING_1_change >= 360) {
						HEADING_1_change = 1 - HEADING;
					}
					else if (HEADING + HEADING_1_change <= 0) {
						HEADING_1_change = 359 - HEADING;
					}
				}
			}
		}

	}
	else if (longPanel_speed_is_down == 1) {
		longPanel_speed_is_down = 0;
	}



	setfillcolor(EGEARGB(0XFF, 0X26, 0X2B, 0X2C));
	ege_fillrect(center_x + Ulength * 3, center_y - 24 * Ulength, Ulength * 43, Ulength * 13);

	ege_fillrect(center_x + Ulength * 54, center_y - 24 * Ulength, Ulength * 43, Ulength * 13);

	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillrect(center_x + Ulength * 4, center_y - 23 * Ulength, Ulength * 41, Ulength * 11);

	ege_fillellipse(center_x + Ulength * 40, center_y - 3.5 * Ulength, 6 * Ulength, 6 * Ulength);

	ege_fillrect(center_x + Ulength * 55, center_y - 23 * Ulength, Ulength * 41, Ulength * 11);

	setfillcolor(EGEARGB(0XFF, 0X15, 0X15, 0X15));
	ege_fillrect(center_x + Ulength * 5, center_y - 22.5 * Ulength, Ulength * 39, Ulength * 10);

	ege_fillellipse(center_x + Ulength * 40.5, center_y - 3 * Ulength, 5 * Ulength, 5 * Ulength);

	ege_fillrect(center_x + Ulength * 56, center_y - 22.5 * Ulength, Ulength * 39, Ulength * 10);

	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillrect(center_x + Ulength * 6, center_y - 22 * Ulength, Ulength * 37, Ulength * 9);

	ege_fillrect(center_x + Ulength * 57, center_y - 22 * Ulength, Ulength * 37, Ulength * 9);

	if (x > center_x + Ulength * 40 && x < center_x + Ulength * 45 && y>center_y - 3.5 * Ulength && y <= center_y + 2.5 * Ulength) {


		if (GetAsyncKeyState(0x02) & 0x0001) {
			setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
			ege_fillellipse(center_x + Ulength * 39.5, center_y - 4 * Ulength, 7 * Ulength, 7 * Ulength);
			if (ALTINTV == 0) {
				ALTINTV = 1;
			}
			else if (ALTINTV == 1) {
				ALTINTV = 0;
			}
		}

	}

	setlinewidth(Linewidth * 4 / 7);
	setfont(Ulength * 4, Ulength * 2.5, "Bahnschrift");
	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_ellipse(center_x + Ulength * 16, center_y - 9 * Ulength, 17 * Ulength, 17 * Ulength);
	ege_ellipse(center_x + Ulength * 36, center_y - 7 * Ulength, 13 * Ulength, 13 * Ulength);
	ege_drawtext("ALT", center_x + Ulength * 53, center_y + 2 * Ulength);
	ege_drawtext("INTV", center_x + Ulength * 53, center_y + 5 * Ulength);
	ege_drawtext("A/P ENGAGE", center_x + Ulength * 120, center_y - 26 * Ulength);
	ege_drawtext("A", center_x + Ulength * 108, center_y - 24 * Ulength);
	ege_drawtext("B", center_x + Ulength * 132, center_y - 24 * Ulength);
	ege_line(center_x + Ulength * 130, center_y - 27 * Ulength, center_x + Ulength * 134, center_y - 27 * Ulength);
	ege_line(center_x + Ulength * 110, center_y - 27 * Ulength, center_x + Ulength * 106, center_y - 27 * Ulength);
	ege_line(center_x + Ulength * 138, center_y - 25 * Ulength, center_x + Ulength * 134, center_y - 27 * Ulength);
	ege_line(center_x + Ulength * 102, center_y - 25 * Ulength, center_x + Ulength * 106, center_y - 27 * Ulength);



	ege_line(center_x + Ulength * 24.5, center_y - 9 * Ulength, center_x + Ulength * 24.5, center_y - 11 * Ulength);

	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_ellipse(center_x + Ulength * 16, center_y - 9 * Ulength, 17 * Ulength, 17 * Ulength);
	ege_ellipse(center_x + Ulength * 36, center_y - 7 * Ulength, 13 * Ulength, 13 * Ulength);
	ege_drawtext("ALT", center_x + Ulength * 53, center_y + 2 * Ulength);
	ege_drawtext("INTV", center_x + Ulength * 53, center_y + 5 * Ulength);
	ege_drawtext("A/P ENGAGE", center_x + Ulength * 120, center_y - 26 * Ulength);
	ege_drawtext("A", center_x + Ulength * 108, center_y - 24 * Ulength);
	ege_drawtext("B", center_x + Ulength * 132, center_y - 24 * Ulength);
	ege_line(center_x + Ulength * 130, center_y - 27 * Ulength, center_x + Ulength * 134, center_y - 27 * Ulength);
	ege_line(center_x + Ulength * 110, center_y - 27 * Ulength, center_x + Ulength * 106, center_y - 27 * Ulength);
	ege_line(center_x + Ulength * 138, center_y - 25 * Ulength, center_x + Ulength * 134, center_y - 27 * Ulength);
	ege_line(center_x + Ulength * 102, center_y - 25 * Ulength, center_x + Ulength * 106, center_y - 27 * Ulength);

	ege_line(center_x + Ulength * 24.5, center_y - 9 * Ulength, center_x + Ulength * 24.5, center_y - 11 * Ulength);



	setlinewidth(Linewidth / 2);

	int ALTITUDEknobnum_2 = 12;//中间旋钮倒数第三层
	ege_point ALTITUDEknobploypoints_2[12] = {
		{center_x + 25 * Ulength - Topknob_R2 * cos(ALTITUDEangle * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin(ALTITUDEangle * PI / 180)},
		{center_x + 25 * Ulength - Topknob_R2 * cos((ALTITUDEangle + 30) * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + 30) * PI / 180)},
		{center_x + 25 * Ulength - Topknob_R2 * cos((ALTITUDEangle + 60) * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + 60) * PI / 180)},
		{center_x + 25 * Ulength - Topknob_R2 * cos((ALTITUDEangle + 90) * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + 90) * PI / 180)},
		{center_x + 25 * Ulength - Topknob_R2 * cos((ALTITUDEangle + 120) * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + 120) * PI / 180)},
		{center_x + 25 * Ulength - Topknob_R2 * cos((ALTITUDEangle + 150) * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + 150) * PI / 180)},
		{center_x + 25 * Ulength - Topknob_R2 * cos((ALTITUDEangle + 180) * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + 180) * PI / 180)},
		{center_x + 25 * Ulength - Topknob_R2 * cos((ALTITUDEangle + 210) * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + 210) * PI / 180)},
		{center_x + 25 * Ulength - Topknob_R2 * cos((ALTITUDEangle + 240) * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + 240) * PI / 180)},
		{center_x + 25 * Ulength - Topknob_R2 * cos((ALTITUDEangle + 270) * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + 270) * PI / 180)},
		{center_x + 25 * Ulength - Topknob_R2 * cos((ALTITUDEangle + 300) * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + 300) * PI / 180)},
		{center_x + 25 * Ulength - Topknob_R2 * cos((ALTITUDEangle + 330) * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + 330) * PI / 180)},





	};
	ege_setpattern_lineargradient(center_x + 24 * Ulength - Topknob_R2, center_y + 1 * Ulength - Topknob_R2, EGEARGB(0XFF, 0X10, 0X10, 0X10),
		center_x + 26 * Ulength + Topknob_R2, center_y - 1 * Ulength + Topknob_R2, EGEARGB(0XFF, 0X7D, 0X7F, 0X7B));
	ege_fillpoly(ALTITUDEknobnum_2, ALTITUDEknobploypoints_2);
	ege_setpattern_none();

	setcolor(EGEARGB(0X2F, 0X50, 0X50, 0X50));
	for (int i = 0; i < 360; i += 30) {
		ege_line(center_x + 25 * Ulength - Topknob_R2 * cos((ALTITUDEangle + i) * PI / 180), center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + i) * PI / 180),
			center_x + 26 * Ulength - Topknob_R2 * cos((ALTITUDEangle + i) * PI / 180), center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + i) * PI / 180));
	}

	int ALTITUDEknobnum_1 = 12;//中间旋钮倒数第四层
	ege_point ALTITUDEknobploypoints_1[12] = {
		{center_x + 26 * Ulength - Topknob_R2 * cos(ALTITUDEangle * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin(ALTITUDEangle * PI / 180)},
		{center_x + 26 * Ulength - Topknob_R2 * cos((ALTITUDEangle + 30) * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + 30) * PI / 180)},
		{center_x + 26 * Ulength - Topknob_R2 * cos((ALTITUDEangle + 60) * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + 60) * PI / 180)},
		{center_x + 26 * Ulength - Topknob_R2 * cos((ALTITUDEangle + 90) * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + 90) * PI / 180)},
		{center_x + 26 * Ulength - Topknob_R2 * cos((ALTITUDEangle + 120) * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + 120) * PI / 180)},
		{center_x + 26 * Ulength - Topknob_R2 * cos((ALTITUDEangle + 150) * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + 150) * PI / 180)},
		{center_x + 26 * Ulength - Topknob_R2 * cos((ALTITUDEangle + 180) * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + 180) * PI / 180)},
		{center_x + 26 * Ulength - Topknob_R2 * cos((ALTITUDEangle + 210) * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + 210) * PI / 180)},
		{center_x + 26 * Ulength - Topknob_R2 * cos((ALTITUDEangle + 240) * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + 240) * PI / 180)},
		{center_x + 26 * Ulength - Topknob_R2 * cos((ALTITUDEangle + 270) * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + 270) * PI / 180)},
		{center_x + 26 * Ulength - Topknob_R2 * cos((ALTITUDEangle + 300) * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + 300) * PI / 180)},
		{center_x + 26 * Ulength - Topknob_R2 * cos((ALTITUDEangle + 330) * PI / 180) ,center_y + 0 * Ulength - Topknob_R2 * sin((ALTITUDEangle + 330) * PI / 180)},





	};
	setfillcolor(EGEARGB(0XFF, 0X58, 0X58, 0X56));
	ege_fillpoly(ALTITUDEknobnum_1, ALTITUDEknobploypoints_1);

	if (GetAsyncKeyState(0x04) & 0x8000) {
		if (longPanel_speed_is_down == 0) {
			longPanel_speed_is_down = 1;
			mousepos(&longPanel_mouse_x, &longPanel_mouse_y);
			longPanel_mouse_x_cur = longPanel_mouse_x;
			longPanel_mouse_y_cur = longPanel_mouse_y;
		}
		if (longPanel_speed_is_down == 1) {
			if ((longPanel_mouse_x_cur >= center_x + 26 * Ulength - Topknob_R2)
				&& (longPanel_mouse_x_cur <= center_x + 26 * Ulength + Topknob_R2)
				&& (longPanel_mouse_y_cur >= center_y + 0 * Ulength - Topknob_R2)
				&& (longPanel_mouse_y_cur <= center_y + 0 * Ulength + Topknob_R2)) {


				mousepos(&longPanel_mouse_x, &longPanel_mouse_y);
				if (longPanel_mouse_y > longPanel_mouse_y_cur) {

					ALTITUDEangle += (longPanel_mouse_y - longPanel_mouse_y_cur) / 70;
					if (ALTITUDE + ALTITUDE_change <= 100000 && ALTITUDE + ALTITUDE_change >= -1000) {
						ALTITUDE_change += ((int)(((longPanel_mouse_y - longPanel_mouse_y_cur) / 70))) * 100;
					}
					else if (ALTITUDE + ALTITUDE_change > 100000) {
						ALTITUDE_change = 100000 - ALTITUDE;

					}
					else if (ALTITUDE + ALTITUDE_change < -1000) {
						ALTITUDE_change = -1000 - ALTITUDE;

					}

				}
				else {
					ALTITUDEangle += (longPanel_mouse_y - longPanel_mouse_y_cur) / 70;
					if (ALTITUDE + ALTITUDE_change <= 100000 && ALTITUDE + ALTITUDE_change >= -1000) {
						ALTITUDE_change += ((int)(((longPanel_mouse_y - longPanel_mouse_y_cur) / 70))) * 100;
					}
					else if (ALTITUDE + ALTITUDE_change > 100000) {
						ALTITUDE_change = 100000 - ALTITUDE;

					}
					else if (ALTITUDE + ALTITUDE_change < -1000) {
						ALTITUDE_change = -1000 - ALTITUDE;

					}
				}
			}
		}

	}
	else if (longPanel_speed_is_down == 1) {
		longPanel_speed_is_down = 0;
	}

	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	setfont(Ulength * 10, Ulength * 2.5, "DigifaceWide");
	char nums_4[64];//ALTITUDE
	sprintf_s(nums_4, "%d", ALTITUDE + ALTITUDE_change);
	ege_drawtext(nums_4, center_x + Ulength * 26, center_y - 16 * Ulength);




	char nums_5[64];//VERTSPEED
	sprintf_s(nums_5, "%d", VERTSPEED + VERTSPEED_change);
	ege_drawtext(nums_5, center_x + Ulength * 80, center_y - 16 * Ulength);


	setfillcolor(BLACK);
	ege_fillrect(center_x + Ulength * 102, center_y - 23 * Ulength, Ulength * 16, Ulength * 16);
	ege_fillrect(center_x + Ulength * 102, center_y - 3 * Ulength, Ulength * 16, Ulength * 16);
	ege_fillrect(center_x + Ulength * 123, center_y - 23 * Ulength, Ulength * 16, Ulength * 16);
	ege_fillrect(center_x + Ulength * 123, center_y - 3 * Ulength, Ulength * 16, Ulength * 16);


	setfillcolor(EGEARGB(0XFF, 0X40, 0X40, 0X40));
	ege_fillrect(center_x + Ulength * 103, center_y - 22 * Ulength, Ulength * 14, Ulength * 14);
	ege_fillrect(center_x + Ulength * 124, center_y - 22 * Ulength, Ulength * 14, Ulength * 14);
	ege_fillrect(center_x + Ulength * 103, center_y - 2 * Ulength, Ulength * 14, Ulength * 14);
	ege_fillrect(center_x + Ulength * 124, center_y - 2 * Ulength, Ulength * 14, Ulength * 14);


	setfillcolor(BLACK);
	ege_fillrect(center_x + Ulength * 103.5, center_y - 21.5 * Ulength, Ulength * 13, Ulength * 13);
	ege_fillrect(center_x + Ulength * 124.5, center_y - 21.5 * Ulength, Ulength * 13, Ulength * 13);
	ege_fillrect(center_x + Ulength * 103.5, center_y - 1.5 * Ulength, Ulength * 13, Ulength * 13);
	ege_fillrect(center_x + Ulength * 124.5, center_y - 1.5 * Ulength, Ulength * 13, Ulength * 13);

	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	setlinewidth(Linewidth / 5);
	ege_line(center_x + Ulength * 102, center_y - 23 * Ulength, center_x + Ulength * 118, center_y - 23 * Ulength);
	ege_line(center_x + Ulength * 123, center_y - 23 * Ulength, center_x + Ulength * 139, center_y - 23 * Ulength);
	ege_line(center_x + Ulength * 102, center_y - 3 * Ulength, center_x + Ulength * 118, center_y - 3 * Ulength);
	ege_line(center_x + Ulength * 123, center_y - 3 * Ulength, center_x + Ulength * 139, center_y - 3 * Ulength);




	if (x > center_x + Ulength * 124 && x < center_x + Ulength * 140 && y>center_y - 22 * Ulength && y <= center_y - 8 * Ulength) {

		if (GetAsyncKeyState(0x02) & 0x0001) {
			setfillcolor(BLACK);
			ege_fillrect(center_x + Ulength * 122.5, center_y - 23.5 * Ulength, Ulength * 17, Ulength * 17);

			if (CMDB == 0) {
				CMDB = 1;
			}
			else if (CMDB == 1) {
				CMDB = 0;
			}
		}
	}
	if (x > center_x + Ulength * 104 && x < center_x + Ulength * 117 && y>center_y - 22 * Ulength && y <= center_y - 8 * Ulength) {

		if (GetAsyncKeyState(0x02) & 0x0001) {
			setfillcolor(BLACK);
			ege_fillrect(center_x + Ulength * 102.5, center_y - 23.5 * Ulength, Ulength * 17, Ulength * 17);

			if (CMDA == 0) {
				CMDA = 1;
			}
			else if (CMDA == 1) {
				CMDA = 0;
			}
		}
	}
	if (x > center_x + Ulength * 124 && x < center_x + Ulength * 140 && y>center_y - 2 * Ulength && y <= center_y + 12 * Ulength) {

		if (GetAsyncKeyState(0x02) & 0x0001) {
			setfillcolor(BLACK);
			ege_fillrect(center_x + Ulength * 122.5, center_y - 3.5 * Ulength, Ulength * 17, Ulength * 17);

			if (CWSB == 0) {
				CWSB = 1;
			}
			else if (CWSB == 1) {
				CWSB = 0;
			}
		}
	}
	if (x > center_x + Ulength * 104 && x < center_x + Ulength * 117 && y>center_y - 2 * Ulength && y <= center_y + 12 * Ulength) {

		if (GetAsyncKeyState(0x02) & 0x0001) {
			setfillcolor(BLACK);
			ege_fillrect(center_x + Ulength * 102.5, center_y - 3.5 * Ulength, Ulength * 17, Ulength * 17);

			if (CWSA == 0) {
				CWSA = 1;
			}
			else if (CWSA == 1) {
				CWSA = 0;
			}
		}
	}
	setlinewidth(Linewidth * 4 / 7);
	setfont(Ulength * 4, Ulength * 2.5, "Bahnschrift");

	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_drawtext("CMD", center_x + Ulength * 110, center_y - 18 * Ulength);
	if (CMDA == 1 || CMDA_1 == 1) {
		button_green_light(center_x + 110 * Ulength, center_y - 11.5 * Ulength, side * 0.16);
	}
	ege_drawtext("CMD", center_x + Ulength * 131, center_y - 18 * Ulength);
	ege_drawtext("CWS", center_x + Ulength * 110, center_y + 3 * Ulength);
	ege_drawtext("CWS", center_x + Ulength * 131, center_y + 3 * Ulength);
	ege_drawtext("DISENGAGE", center_x + Ulength * 120.5, center_y + 16 * Ulength);
	ege_line(center_x + Ulength * 110.5, center_y + 15 * Ulength, center_x + Ulength * 101.5, center_y + 15 * Ulength);
	ege_line(center_x + Ulength * 130.5, center_y + 15 * Ulength, center_x + Ulength * 139.5, center_y + 15 * Ulength);
	ege_line(center_x + Ulength * 139.5, center_y + 26 * Ulength, center_x + Ulength * 139.5, center_y + 15 * Ulength);
	ege_line(center_x + Ulength * 101.5, center_y + 26 * Ulength, center_x + Ulength * 101.5, center_y + 15 * Ulength);

	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_drawtext("CMD", center_x + Ulength * 110, center_y - 18 * Ulength);
	ege_drawtext("CMD", center_x + Ulength * 131, center_y - 18 * Ulength);
	ege_drawtext("CWS", center_x + Ulength * 110, center_y + 3 * Ulength);
	ege_drawtext("CWS", center_x + Ulength * 131, center_y + 3 * Ulength);
	ege_drawtext("DISENGAGE", center_x + Ulength * 120.5, center_y + 16 * Ulength);
	ege_line(center_x + Ulength * 110.5, center_y + 15 * Ulength, center_x + Ulength * 101.5, center_y + 15 * Ulength);
	ege_line(center_x + Ulength * 130.5, center_y + 15 * Ulength, center_x + Ulength * 139.5, center_y + 15 * Ulength);
	ege_line(center_x + Ulength * 139.5, center_y + 26 * Ulength, center_x + Ulength * 139.5, center_y + 15 * Ulength);
	ege_line(center_x + Ulength * 101.5, center_y + 26 * Ulength, center_x + Ulength * 101.5, center_y + 15 * Ulength);



	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_arc(center_x + 150 * Ulength, center_y - 8 * Ulength, 16 * Ulength, 16 * Ulength, 120, 120);
	ege_arc(center_x + 150 * Ulength, center_y - 8 * Ulength, 16 * Ulength, 16 * Ulength, 300, 120);
	ege_line(center_x + 158 * Ulength, center_y, center_x + 155 * Ulength, center_y - 7 * Ulength);
	ege_line(center_x + 155 * Ulength, center_y - 9 * Ulength, center_x + 155 * Ulength, center_y - 7 * Ulength);


	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_arc(center_x + 150 * Ulength, center_y - 8 * Ulength, 16 * Ulength, 16 * Ulength, 125, 110);
	ege_arc(center_x + 150 * Ulength, center_y - 8 * Ulength, 16 * Ulength, 16 * Ulength, 305, 110);
	ege_line(center_x + 158 * Ulength, center_y, center_x + 155 * Ulength, center_y - 7 * Ulength);
	ege_line(center_x + 155 * Ulength, center_y - 9 * Ulength, center_x + 155 * Ulength, center_y - 7 * Ulength);

	setfillcolor(EGEARGB(0XFF, 0X95, 0X88, 0X70));
	ege_fillellipse(center_x + 152 * Ulength, center_y - 6 * Ulength, 12 * Ulength, 12 * Ulength);

	int num_6 = 4;
	ege_point numploy_6[4] = {
		{center_x + 158 * Ulength ,center_y - 6 * Ulength},
		{center_x + 158 * Ulength ,center_y + 6 * Ulength},
		{center_x + 165 * Ulength ,center_y + 6 * Ulength},
		{center_x + 165 * Ulength ,center_y - 6 * Ulength},

	};
	ege_fillpoly(num_6, numploy_6);


	setcolor(EGEARGB(0X30, 0X50, 0X50, 0X50));
	for (int i = 0; i < 360; i += 10) {
		ege_line(center_x + 158 * Ulength - (6 * Ulength) * cos((i + COURSE_2) * PI / 180), center_y - (6 * Ulength) * sin((i + COURSE_2) * PI / 180),
			center_x + 165 * Ulength - (6 * Ulength) * cos((i + COURSE_2) * PI / 180), center_y - (6 * Ulength) * sin((i + COURSE_2) * PI / 180));
	}


	setfillcolor(EGEARGB(0XFF, 0X49, 0X48, 0X46));
	ege_fillellipse(center_x + 159 * Ulength, center_y - 6 * Ulength, 12 * Ulength, 12 * Ulength);

	setcolor(EGEARGB(0XFF, 0X39, 0X38, 0X36));
	ege_ellipse(center_x + 159.5 * Ulength, center_y - 5.5 * Ulength, 11 * Ulength, 11 * Ulength);

	setcolor(EGEARGB(0XFF, 0X6C, 0X56, 0X2A));
	setlinewidth(Linewidth * 1.2);
	ege_line(center_x + 165 * Ulength - (5 * Ulength) * cos((0 + COURSE_2) * PI / 180), center_y - (5 * Ulength) * sin((0 + COURSE_2) * PI / 180),
		center_x + 165 * Ulength - (5 * Ulength) * cos((180 + COURSE_2) * PI / 180), center_y - (5 * Ulength) * sin((180 + COURSE_2) * PI / 180));
	ege_line(center_x + 165 * Ulength - (4 * Ulength) * cos((70 + COURSE_2) * PI / 180), center_y - (4 * Ulength) * sin((70 + COURSE_2) * PI / 180),
		center_x + 165 * Ulength - (4 * Ulength) * cos((290 + COURSE_2) * PI / 180), center_y - (4 * Ulength) * sin((290 + COURSE_2) * PI / 180));

	setcolor(EGEARGB(0XFF, 0X6A, 0X48, 0X27));
	setlinewidth(Linewidth * 4 / 6);
	ege_line(center_x + 165 * Ulength - (4.7 * Ulength) * cos((0 + COURSE_2) * PI / 180), center_y - (4.7 * Ulength) * sin((0 + COURSE_2) * PI / 180),
		center_x + 165 * Ulength - (4.7 * Ulength) * cos((180 + COURSE_2) * PI / 180), center_y - (4.7 * Ulength) * sin((180 + COURSE_2) * PI / 180));
	ege_line(center_x + 165 * Ulength - (3.3 * Ulength) * cos((65 + COURSE_2) * PI / 180), center_y - (3.3 * Ulength) * sin((65 + COURSE_2) * PI / 180),
		center_x + 165 * Ulength - (3.3 * Ulength) * cos((295 + COURSE_2) * PI / 180), center_y - (3.3 * Ulength) * sin((295 + COURSE_2) * PI / 180));


	if (GetAsyncKeyState(0x04) & 0x8000) {
		if (longPanel_speed_is_down == 0) {
			longPanel_speed_is_down = 1;
			mousepos(&longPanel_mouse_x, &longPanel_mouse_y);
			longPanel_mouse_x_cur = longPanel_mouse_x;
			longPanel_mouse_y_cur = longPanel_mouse_y;
		}
		if (longPanel_speed_is_down == 1) {
			if ((longPanel_mouse_x_cur <= center_x + 171 * Ulength)
				&& (longPanel_mouse_x_cur >= center_x + 152 * Ulength)
				&& (longPanel_mouse_y_cur >= center_y - 6 * Ulength)
				&& (longPanel_mouse_y_cur <= center_y + 6 * Ulength)) {


				mousepos(&longPanel_mouse_x, &longPanel_mouse_y);
				if (longPanel_mouse_y > longPanel_mouse_y_cur) {

					COURSE_2 += (longPanel_mouse_y - longPanel_mouse_y_cur) / 70;
					if (COURSE_2NUM + change_COURSE_2NUM < 360 && COURSE_2NUM + change_COURSE_2NUM>0) {
						change_COURSE_2NUM += (int)((longPanel_mouse_y - longPanel_mouse_y_cur) / 70);
					}
					else if (COURSE_2NUM + change_COURSE_2NUM >= 360) {
						change_COURSE_2NUM = 1 - COURSE_2NUM;

					}
					else if (COURSE_2NUM + change_COURSE_2NUM <= 0) {
						change_COURSE_2NUM = 359 - COURSE_2NUM;

					}

				}
				else {
					COURSE_2 += (longPanel_mouse_y - longPanel_mouse_y_cur) / 70;
					if (COURSE_2NUM + change_COURSE_2NUM < 360 && COURSE_2NUM + change_COURSE_2NUM>0) {
						change_COURSE_2NUM += (int)((longPanel_mouse_y - longPanel_mouse_y_cur) / 70);
					}
					else if (COURSE_2NUM + change_COURSE_2NUM >= 360) {
						change_COURSE_2NUM = 1 - COURSE_2NUM;

					}
					else if (COURSE_2NUM + change_COURSE_2NUM <= 0) {
						change_COURSE_2NUM = 359 - COURSE_2NUM;

					}
				}
			}
		}

	}
	else if (longPanel_speed_is_down == 1) {
		longPanel_speed_is_down = 0;
	}

	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_rectangle(center_x + 141.5 * Ulength, center_y + 10 * Ulength, Ulength * 7, Ulength * 11);
	setfont(Ulength * 4, Ulength * 2.5, "Bahnschrift");
	ege_drawtext("F/D", center_x + Ulength * 145, center_y + 5 * Ulength);
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	ege_drawtext("ON", center_x + Ulength * 145.5, center_y + 8.5 * Ulength);
	ege_drawtext("OFF", center_x + Ulength * 145.5, center_y + 24.5 * Ulength);

	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_rectangle(center_x + 141.5 * Ulength, center_y + 10 * Ulength, Ulength * 7, Ulength * 11);
	setfont(Ulength * 4, Ulength * 2.5, "Bahnschrift");
	ege_drawtext("F/D", center_x + Ulength * 145, center_y + 5 * Ulength);
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	ege_drawtext("ON", center_x + Ulength * 145.5, center_y + 8.5 * Ulength);
	ege_drawtext("OFF", center_x + Ulength * 145.5, center_y + 24.5 * Ulength);




	ege_enable_aa(false);
	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	setlinewidth(Linewidth / 3);
	setcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	int FDnums_2 = 13;
	ege_point FDploypoints_2[13] = {
		{center_x + Ulength * 147,center_y + 13 * Ulength},
		{center_x + Ulength * 146,center_y + 11 * Ulength},
		{center_x + Ulength * 144,center_y + 11 * Ulength},
		{center_x + Ulength * 143,center_y + 13 * Ulength},

		{center_x + Ulength * 143,center_y + 18 * Ulength},
		{center_x + Ulength * 143,center_y + 18 * Ulength},
		{center_x + Ulength * 143,center_y + 18 * Ulength},

		{center_x + Ulength * 144,center_y + 20 * Ulength},
		{center_x + Ulength * 146,center_y + 20 * Ulength},
		{center_x + Ulength * 147,center_y + 18 * Ulength},

		{center_x + Ulength * 147,center_y + 13 * Ulength},
		{center_x + Ulength * 147,center_y + 13 * Ulength},
		{center_x + Ulength * 147,center_y + 13 * Ulength},

	};
	ege_bezier(FDnums_2, FDploypoints_2);

	floodfill(center_x + Ulength * 146, center_y + 16 * Ulength, EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_enable_aa(true);
	if (FD_2 == 0) {
		setfillcolor(EGEARGB(0XFF, 0X4B, 0X4B, 0X49));

		for (int i = 0; i <= 60; i++) {
			ege_fillellipse(center_x + Ulength * (144 + 0.025 * i), center_y + (13 - i * 0.1) * Ulength, Ulength * (3 + i * 0.015), Ulength * (3 + i * 0.015));
		}
		setlinewidth(Linewidth / 5);
		setcolor(EGEARGB(0X8F, 0X20, 0X20, 0X20));
		ege_ellipse(center_x + Ulength * (144 + 0.025 * 60), center_y + (13 - 60 * 0.1) * Ulength, Ulength * (3 + 60 * 0.015), Ulength * (3 + 60 * 0.015));

	}
	if (FD_2 == 1) {
		setfillcolor(EGEARGB(0XFF, 0X4B, 0X4B, 0X49));

		for (int i = 0; i <= 60; i++) {
			ege_fillellipse(center_x + Ulength * (144 + 0.025 * i), center_y + (13 + i * 0.1) * Ulength, Ulength * (3 + i * 0.015), Ulength * (3 + i * 0.015));
		}
		setlinewidth(Linewidth / 5);
		setcolor(EGEARGB(0X8F, 0X20, 0X20, 0X20));
		ege_ellipse(center_x + Ulength * (144 + 0.025 * 60), center_y + (13 + 60 * 0.1) * Ulength, Ulength * (3 + 60 * 0.015), Ulength * (3 + 60 * 0.015));

	}
	if (x < center_x + Ulength * 147 && x > center_x + Ulength * 143 && y > center_y + 12 * Ulength && y <= center_y + 15 * Ulength) {
		ege_rectangle(center_x + Ulength * 144, center_y + 12 * Ulength, Ulength * 4, Ulength * 3);

		if (GetAsyncKeyState(0x02) & 0x0001 && FD_2 > 0) {
			FD_2--;

		}
	}
	if (x < center_x + Ulength * 147 && x > center_x + Ulength * 143 && y > center_y + 15 * Ulength && y <= center_y + 19 * Ulength) {
		ege_rectangle(center_x + Ulength * 144, center_y + 15 * Ulength, Ulength * 4, Ulength * 4);

		if (GetAsyncKeyState(0x02) & 0x0001 && FD_2 < 1) {
			FD_2++;

		}
	}
	setfillcolor(EGEARGB(0XFF, 0X26, 0X2B, 0X2C));
	ege_fillellipse(center_x + Ulength * 141.2, center_y - 6.5 * Ulength, 7 * Ulength, 7 * Ulength);
	ege_fillrect(center_x + Ulength * 144, center_y - 23 * Ulength, Ulength * 24, Ulength * 13);



	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillellipse(center_x + Ulength * 141.7, center_y - 6 * Ulength, 6 * Ulength, 6 * Ulength);
	ege_fillrect(center_x + Ulength * 145, center_y - 22 * Ulength, Ulength * 22, Ulength * 11);


	setfillcolor(EGEARGB(0XFF, 0X15, 0X15, 0X15));
	ege_fillrect(center_x + Ulength * 146, center_y - 21.5 * Ulength, Ulength * 20, Ulength * 10);

	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillrect(center_x + Ulength * 147, center_y - 21 * Ulength, Ulength * 18, Ulength * 9);

	if (FD_2 == 0) {
		setcolor(EGEARGB(0XFF, 0X0D, 0X9B, 0X12));
		setfont(Ulength * 4, Ulength * 2.5, "Bahnschrift");
		ege_drawtext("MA", center_x + Ulength * 145, center_y - 2.5 * Ulength);

	}

	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	setfont(Ulength * 10, Ulength * 2.5, "DigifaceWide");
	char nums_7[64];//左上上
	sprintf_s(nums_7, "%03d", COURSE_2NUM + change_COURSE_2NUM);
	ege_drawtext(nums_7, center_x + Ulength * 156, center_y - 16 * Ulength);


	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	ege_line(center_x + Ulength * 53, center_y + 18 * Ulength, center_x + Ulength * 76, center_y + 18 * Ulength);
	ege_line(center_x + Ulength * 78, center_y + 26 * Ulength, center_x + Ulength * 78, center_y + 23 * Ulength);
	ege_line(center_x + Ulength * 78, center_y + 26 * Ulength, center_x + Ulength * 90, center_y + 26 * Ulength);
	ege_line(center_x + Ulength * 90, center_y + 23 * Ulength, center_x + Ulength * 90, center_y + 26 * Ulength);
	ege_line(center_x + Ulength * 90, center_y - 5 * Ulength, center_x + Ulength * 90, center_y - 8 * Ulength);
	ege_line(center_x + Ulength * 78, center_y - 8 * Ulength, center_x + Ulength * 90, center_y - 8 * Ulength);
	ege_line(center_x + Ulength * 78, center_y - 8 * Ulength, center_x + Ulength * 78, center_y - 5 * Ulength);
	ege_line(center_x + Ulength * 84, center_y - 8 * Ulength, center_x + Ulength * 84, center_y - 11 * Ulength);
	ege_line(center_x + Ulength * 97, center_y + 9 * Ulength, center_x + Ulength * 92, center_y + 9 * Ulength);
	ege_line(center_x + Ulength * 94.5, center_y + 10 * Ulength, center_x + Ulength * 94.5, center_y + 15 * Ulength);
	ege_line(center_x + Ulength * 94.5, center_y + 8 * Ulength, center_x + Ulength * 94.5, center_y + 3 * Ulength);
	setfont(Ulength * 4, Ulength * 2.5, "Bahnschrift");
	ege_drawtext("UP", center_x + Ulength * 94.5, center_y + 21 * Ulength);
	ege_drawtext("DN", center_x + Ulength * 94.5, center_y - 2 * Ulength);

	setcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	ege_line(center_x + Ulength * 53, center_y + 18 * Ulength, center_x + Ulength * 76, center_y + 18 * Ulength);
	ege_line(center_x + Ulength * 78, center_y + 26 * Ulength, center_x + Ulength * 78, center_y + 23 * Ulength);
	ege_line(center_x + Ulength * 78, center_y + 26 * Ulength, center_x + Ulength * 90, center_y + 26 * Ulength);
	ege_line(center_x + Ulength * 90, center_y + 23 * Ulength, center_x + Ulength * 90, center_y + 26 * Ulength);
	ege_line(center_x + Ulength * 90, center_y - 5 * Ulength, center_x + Ulength * 90, center_y - 8 * Ulength);
	ege_line(center_x + Ulength * 78, center_y - 8 * Ulength, center_x + Ulength * 90, center_y - 8 * Ulength);
	ege_line(center_x + Ulength * 78, center_y - 8 * Ulength, center_x + Ulength * 78, center_y - 5 * Ulength);
	ege_line(center_x + Ulength * 84, center_y - 8 * Ulength, center_x + Ulength * 84, center_y - 11 * Ulength);
	ege_line(center_x + Ulength * 97, center_y + 9 * Ulength, center_x + Ulength * 92, center_y + 9 * Ulength);
	ege_line(center_x + Ulength * 94.5, center_y + 10 * Ulength, center_x + Ulength * 94.5, center_y + 15 * Ulength);
	ege_line(center_x + Ulength * 94.5, center_y + 8 * Ulength, center_x + Ulength * 94.5, center_y + 3 * Ulength);

	setfillcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	int nums_9 = 3;
	ege_point numspoly_9[3] = {
		{center_x + Ulength * 93, center_y + 3 * Ulength},
		{center_x + Ulength * 96, center_y + 3 * Ulength},
		{center_x + Ulength * 94.5, center_y + 0 * Ulength},
	};
	ege_fillpoly(nums_9, numspoly_9);
	int nums_10 = 3;
	ege_point numspoly_10[3] = {
		{ center_x + Ulength * 93, center_y + 15 * Ulength},
		{ center_x + Ulength * 96, center_y + 15 * Ulength},
		{ center_x + Ulength * 94.5, center_y + 18 * Ulength},
	};
	ege_fillpoly(nums_10, numspoly_10);
	setfillcolor(EGEARGB(MainPanelLight, 0XB2, 0X7E, 0X50));
	int nums_11 = 3;
	ege_point numspoly_11[3] = {
		{center_x + Ulength * 93, center_y + 3 * Ulength},
		{center_x + Ulength * 96, center_y + 3 * Ulength},
		{center_x + Ulength * 94.5, center_y + 0 * Ulength},
	};
	ege_fillpoly(nums_11, numspoly_11);
	int nums_12 = 3;
	ege_point numspoly_12[3] = {
		{ center_x + Ulength * 93, center_y + 15 * Ulength},
		{ center_x + Ulength * 96, center_y + 15 * Ulength},
		{ center_x + Ulength * 94.5, center_y + 18 * Ulength},
	};
	ege_fillpoly(nums_12, numspoly_12);

	setfillcolor(EGEARGB(0XFF, 0X67, 0X66, 0X63));
	ege_fillrect(center_x + Ulength * 79, center_y - 4 * Ulength, 10 * Ulength, 26 * Ulength);
	setcolor(BLACK);
	setlinewidth(Linewidth);
	ege_rectangle(center_x + Ulength * 79, center_y - 4 * Ulength, 10 * Ulength, 26 * Ulength);

	setlinewidth(Linewidth / 10);
	for (int i = 0; i <= 26; i++) {
		ege_line(center_x + Ulength * 79, center_y - 4 * Ulength + i * Ulength, center_x + Ulength * 89, center_y - 4 * Ulength + i * Ulength);
	}
	for (int i = 0; i <= 6; i++) {
		ege_line(center_x + Ulength * 79, center_y - 4 * Ulength + i * (Ulength * 4), center_x + Ulength * 89, center_y - 4 * Ulength + i * (Ulength * 4));
	}

	if (GetAsyncKeyState(0x04) & 0x8000) {
		if (longPanel_speed_is_down == 0) {
			longPanel_speed_is_down = 1;
			mousepos(&longPanel_mouse_x, &longPanel_mouse_y);
			longPanel_mouse_x_cur = longPanel_mouse_x;
			longPanel_mouse_y_cur = longPanel_mouse_y;
		}
		if (longPanel_speed_is_down == 1) {
			if ((longPanel_mouse_x_cur >= center_x + Ulength * 79)
				&& (longPanel_mouse_x_cur <= center_x + Ulength * 89)
				&& (longPanel_mouse_y_cur >= center_y - 4 * Ulength)
				&& (longPanel_mouse_y_cur <= center_y + 22 * Ulength)) {


				mousepos(&longPanel_mouse_x, &longPanel_mouse_y);
				if (longPanel_mouse_y > longPanel_mouse_y_cur) {

					VERTSPEEDangle += (longPanel_mouse_y - longPanel_mouse_y_cur) / 70;
					if (VERTSPEED + VERTSPEED_change <= 5000 && VERTSPEED + VERTSPEED_change >= -5000) {
						VERTSPEED_change += ((int)((longPanel_mouse_y - longPanel_mouse_y_cur) / 70)) * 100;
					}
					else if (VERTSPEED + VERTSPEED_change > 5000) {
						VERTSPEED_change = 5000 - VERTSPEED;

					}
					else if (VERTSPEED + VERTSPEED_change < -5000) {
						VERTSPEED_change = -5000 - VERTSPEED;

					}

				}
				else {
					VERTSPEEDangle += (longPanel_mouse_y - longPanel_mouse_y_cur) / 70;
					if (VERTSPEED + VERTSPEED_change <= 5000 && VERTSPEED + VERTSPEED_change >= -5000) {
						VERTSPEED_change += ((int)((longPanel_mouse_y - longPanel_mouse_y_cur) / 70)) * 100;
					}
					else if (VERTSPEED + VERTSPEED_change > 5000) {
						VERTSPEED_change = 5000 - VERTSPEED;

					}
					else if (VERTSPEED + VERTSPEED_change < -5000) {
						VERTSPEED_change = -5000 - VERTSPEED;

					}
				}
			}
		}

	}
	else if (longPanel_speed_is_down == 1) {
		longPanel_speed_is_down = 0;
	}

	if (VS_1 != VS || SPEED_1 != SPEED || HDGSEL_1 != HDGSEL || ALTHLD_1 != ALTHLD || FD_1 != FD_1_1) {
		choicetransfromAUTO = 1;
	}
	else {
		choicetransfromAUTO = 0;
	}

	if (choicetransfromAUTO == 1)
		datatransform_back();
}