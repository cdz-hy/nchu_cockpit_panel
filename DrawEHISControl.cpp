#include<graphics.h>
#include <stdio.h>
#include <math.h>

extern double LeftTopAngle_1;//RST上层
extern double LeftTopAngle_2;//RST下层
extern double rightTopAngle_1;//STD上层
extern double rightTopAngle_2;//STD下层
extern double leftLowAngle;//CTR
extern double rightLowAngle;//TFC
extern double changecolor;
extern int FPV;
extern int MTRS;
extern int RST;
extern int STD;
extern int CTR;
extern int TFC;
extern int WXR;
extern int STA;
extern int WPT;
extern int ARPT;
extern int DATA;
extern int POS;
extern int TERR;
extern int VOR1;
extern int VOR2;
extern int ChangeLight;
int knob_mouse_x = 0, knob_mouse_y = 0;
int knob_speed_is_down = 0;
int knob_mouse_y_cur = 0, knob_mouse_x_cur = 0;
void draw_EHIS_control(double EHIScontrol_x, double EHIScontrol_y, double side) {

	int x, y;
	mousepos(&x, &y);
	

	double Ulength = side / 140;
	double linewidth = Ulength;
	double Topknob_R1 = Ulength * 12;
	double Topknob_R2 = Ulength * 9;
	double Topknob_R3 = Ulength * 6;
	double Topknob_R4 = Ulength * 6.5;//左上旋钮按钮
	double Topknob_R5 = Ulength * 6.5;//右上旋钮按钮



	double Lowknob_R1 = Ulength * 9;
	double Lowknob_R2 = Ulength * 7.5;
	double Lowknob_R3 = Ulength * 4.5;
	double Lowknob_R4 = Ulength * 5;//左下旋钮按钮
	double Lowknob_R5 = Ulength * 5;//右下旋钮按钮


	setcolor(EGEARGB(0XFF, 0X18, 0X1C, 0X20));
	setlinewidth(linewidth);

	int KnobPanelFramePointNum = 25;
	ege_point KnobPanelFrameploypoints[25]{
		{EHIScontrol_x - 65 * Ulength , EHIScontrol_y - 38 * Ulength},
		{EHIScontrol_x - 68 * Ulength , EHIScontrol_y - 38 * Ulength},
		{EHIScontrol_x - 70 * Ulength , EHIScontrol_y - 36 * Ulength},
		{EHIScontrol_x - 70 * Ulength , EHIScontrol_y - 33 * Ulength},

		{EHIScontrol_x - 70 * Ulength , EHIScontrol_y + 33 * Ulength},
		{EHIScontrol_x - 70 * Ulength , EHIScontrol_y + 33 * Ulength},
		{EHIScontrol_x - 70 * Ulength , EHIScontrol_y + 33 * Ulength},

		{EHIScontrol_x - 70 * Ulength , EHIScontrol_y + 36 * Ulength},
		{EHIScontrol_x - 68 * Ulength , EHIScontrol_y + 38 * Ulength},
		{EHIScontrol_x - 65 * Ulength , EHIScontrol_y + 38 * Ulength},

		{EHIScontrol_x + 65 * Ulength , EHIScontrol_y + 38 * Ulength},
		{EHIScontrol_x + 65 * Ulength , EHIScontrol_y + 38 * Ulength},
		{EHIScontrol_x + 65 * Ulength , EHIScontrol_y + 38 * Ulength},

		{EHIScontrol_x + 68 * Ulength , EHIScontrol_y + 38 * Ulength},
		{EHIScontrol_x + 70 * Ulength , EHIScontrol_y + 36 * Ulength},
		{EHIScontrol_x + 70 * Ulength , EHIScontrol_y + 33 * Ulength},

		{EHIScontrol_x + 70 * Ulength , EHIScontrol_y - 33 * Ulength},
		{EHIScontrol_x + 70 * Ulength , EHIScontrol_y - 33 * Ulength},
		{EHIScontrol_x + 70 * Ulength , EHIScontrol_y - 33 * Ulength},

		{EHIScontrol_x + 70 * Ulength , EHIScontrol_y - 36 * Ulength},
		{EHIScontrol_x + 68 * Ulength , EHIScontrol_y - 38 * Ulength},
		{EHIScontrol_x + 65 * Ulength , EHIScontrol_y - 38 * Ulength},

		{EHIScontrol_x - 65 * Ulength , EHIScontrol_y - 38 * Ulength},
		{EHIScontrol_x - 65 * Ulength , EHIScontrol_y - 38 * Ulength},
		{EHIScontrol_x - 65 * Ulength , EHIScontrol_y - 38 * Ulength},

	};
	ege_bezier(KnobPanelFramePointNum, KnobPanelFrameploypoints);
	setfillcolor(EGEARGB(0XFF, 0X18, 0X1C, 0X20));
	floodfill(EHIScontrol_x - 64 * Ulength, EHIScontrol_y - 37 * Ulength, EGEARGB(0XFF, 0X18, 0X1C, 0X20));
	floodfill(EHIScontrol_x + 64 * Ulength, EHIScontrol_y - 37 * Ulength, EGEARGB(0XFF, 0X18, 0X1C, 0X20));
	floodfill(EHIScontrol_x - 64 * Ulength, EHIScontrol_y + 37 * Ulength, EGEARGB(0XFF, 0X18, 0X1C, 0X20));
	floodfill(EHIScontrol_x + 64 * Ulength, EHIScontrol_y + 37 * Ulength, EGEARGB(0XFF, 0X18, 0X1C, 0X20));


	setcolor(EGEARGB(0X1F, 0X50, 0X50, 0X50));
	setlinewidth(linewidth / 2);
	int Framelightnum = 16;
	ege_point Framelightploypoints[16] = {

		{EHIScontrol_x + 65 * Ulength , EHIScontrol_y + 38 * Ulength},
		{EHIScontrol_x + 68 * Ulength , EHIScontrol_y + 38 * Ulength},
		{EHIScontrol_x + 70 * Ulength , EHIScontrol_y + 36 * Ulength},
		{EHIScontrol_x + 70 * Ulength , EHIScontrol_y + 33 * Ulength},

		{EHIScontrol_x + 70 * Ulength , EHIScontrol_y - 33 * Ulength},
		{EHIScontrol_x + 70 * Ulength , EHIScontrol_y - 33 * Ulength},
		{EHIScontrol_x + 70 * Ulength , EHIScontrol_y - 33 * Ulength},

		{EHIScontrol_x + 70 * Ulength , EHIScontrol_y - 36 * Ulength},
		{EHIScontrol_x + 68 * Ulength , EHIScontrol_y - 38 * Ulength},
		{EHIScontrol_x + 65 * Ulength , EHIScontrol_y - 38 * Ulength},

		{EHIScontrol_x - 65 * Ulength , EHIScontrol_y - 38 * Ulength},
		{EHIScontrol_x - 65 * Ulength , EHIScontrol_y - 38 * Ulength},
		{EHIScontrol_x - 65 * Ulength , EHIScontrol_y - 38 * Ulength},

		{EHIScontrol_x - 68 * Ulength , EHIScontrol_y - 38 * Ulength},
		{EHIScontrol_x - 70 * Ulength , EHIScontrol_y - 36 * Ulength},
		{EHIScontrol_x - 70 * Ulength , EHIScontrol_y - 33 * Ulength},

	};
	ege_bezier(Framelightnum, Framelightploypoints);

	setcolor(EGEARGB(0X1F, 0X00, 0X00, 0X00));
	setlinewidth(linewidth / 2);

	int Frameshadenum = 10;
	ege_point Frameshadeploypoints[10]{
		{EHIScontrol_x - 70 * Ulength , EHIScontrol_y - 33 * Ulength},
		{EHIScontrol_x - 70 * Ulength , EHIScontrol_y + 33 * Ulength},
		{EHIScontrol_x - 70 * Ulength , EHIScontrol_y + 33 * Ulength},
		{EHIScontrol_x - 70 * Ulength , EHIScontrol_y + 33 * Ulength},

		{EHIScontrol_x - 70 * Ulength , EHIScontrol_y + 36 * Ulength},
		{EHIScontrol_x - 68 * Ulength , EHIScontrol_y + 38 * Ulength},
		{EHIScontrol_x - 65 * Ulength , EHIScontrol_y + 38 * Ulength},

		{EHIScontrol_x + 65 * Ulength , EHIScontrol_y + 38 * Ulength},
		{EHIScontrol_x + 65 * Ulength , EHIScontrol_y + 38 * Ulength},
		{EHIScontrol_x + 65 * Ulength , EHIScontrol_y + 38 * Ulength},

	};

	ege_bezier(Frameshadenum, Frameshadeploypoints);



	if (changecolor == 1) {

		setcolor(EGEARGB(ChangeLight, 0XB2, 0X7E, 0X50));
	}
	else {
		setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	}
	setfont(Ulength * 5, Ulength * 2, "Bahnschrift");
	ege_line(EHIScontrol_x - 43.5 * Ulength, EHIScontrol_y - 15 * Ulength,
		EHIScontrol_x - 43.5 * Ulength - (Topknob_R1 + 1.5 * Ulength) * cos(55 * PI / 180), EHIScontrol_y - 15 * Ulength - (Topknob_R1 + 1.5 * Ulength) * sin(55 * PI / 180));
	ege_line(EHIScontrol_x - 43.5 * Ulength , EHIScontrol_y - 15 * Ulength ,
		EHIScontrol_x - 43.5 * Ulength - (Topknob_R1 + 1.5 * Ulength) * cos(125 * PI / 180), EHIScontrol_y - 15 * Ulength - (Topknob_R1 + 1.5 * Ulength) * sin(125 * PI / 180));
	ege_drawtext("RADIO",EHIScontrol_x - 63 * Ulength, EHIScontrol_y - 30 * Ulength);
	ege_drawtext("MINS",EHIScontrol_x - 49 * Ulength, EHIScontrol_y - 33 * Ulength);
	ege_drawtext("BARO",EHIScontrol_x - 36 * Ulength, EHIScontrol_y - 30 * Ulength);



	int LeftTopknobnum_4 = 12;//左上旋钮最底层
	ege_point LeftTopknobploypoints_4[12] = {
		{EHIScontrol_x - 43.5 * Ulength - Topknob_R1 * cos(LeftTopAngle_2 * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin(LeftTopAngle_2 * PI / 180)},
		{EHIScontrol_x - 43.5 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + 30) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + 30) * PI / 180)},
		{EHIScontrol_x - 43.5 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + 60) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + 60) * PI / 180)},
		{EHIScontrol_x - 43.5 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + 90) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + 90) * PI / 180)},
		{EHIScontrol_x - 43.5 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + 120) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + 120) * PI / 180)},
		{EHIScontrol_x - 43.5 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + 150) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + 150) * PI / 180)},
		{EHIScontrol_x - 43.5 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + 180) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + 180) * PI / 180)},
		{EHIScontrol_x - 43.5 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + 210) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + 210) * PI / 180)},
		{EHIScontrol_x - 43.5 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + 240) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + 240) * PI / 180)},
		{EHIScontrol_x - 43.5 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + 270) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + 270) * PI / 180)},
		{EHIScontrol_x - 43.5 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + 300) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + 300) * PI / 180)},
		{EHIScontrol_x - 43.5 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + 330) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + 330) * PI / 180)},

	};
	ege_setpattern_lineargradient(EHIScontrol_x - 42.5 * Ulength - Topknob_R2, EHIScontrol_y - 14 * Ulength - Topknob_R2, EGEARGB(0XFF, 0X10, 0X10, 0X10),
		EHIScontrol_x - 44.5 * Ulength + Topknob_R2, EHIScontrol_y - 15.2 * Ulength + Topknob_R2, EGEARGB(0XFF, 0X7D, 0X7F, 0X7B));
	ege_fillpoly(LeftTopknobnum_4, LeftTopknobploypoints_4);
	ege_setpattern_none();

	setcolor(EGEARGB(0X2F, 0X50, 0X50, 0X50));
	for (int i = 0; i < 360; i += 30) {
		ege_line(EHIScontrol_x - 43.5 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + i) * PI / 180), EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + i) * PI / 180),
			EHIScontrol_x - 45 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + i) * PI / 180), EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + i) * PI / 180));
	}
	setlinewidth(linewidth * 3);
	setcolor(EGEARGB(0XFF, 0X3A, 0X35, 0X2F));
	ege_line(EHIScontrol_x - 43.5 * Ulength, EHIScontrol_y - 15 * Ulength ,
		EHIScontrol_x - 43.5 * Ulength - (Topknob_R1 - Ulength / 3) * cos(LeftTopAngle_2 * PI / 180), EHIScontrol_y - 15 * Ulength - (Topknob_R1 - Ulength / 3) * sin(LeftTopAngle_2 * PI / 180));

	setlinewidth(linewidth * 1.1);
	setcolor(EGEARGB(0XFF, 0XB2, 0X7E, 0X50));
	ege_line(EHIScontrol_x - 43.5 * Ulength, EHIScontrol_y - 15 * Ulength,
		EHIScontrol_x - 43.5 * Ulength - (Topknob_R1 - Ulength / 3) * cos(LeftTopAngle_2 * PI / 180), EHIScontrol_y - 15 * Ulength - (Topknob_R1 - Ulength / 3) * sin(LeftTopAngle_2 * PI / 180));

	setlinewidth(linewidth / 2);
	int LeftTopknobnum_3 = 12;//左上旋钮倒数第二层
	ege_point LeftTopknobploypoints_3[12] = {
		{EHIScontrol_x - 45 * Ulength - Topknob_R1 * cos(LeftTopAngle_2 * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin(LeftTopAngle_2 * PI / 180)},
		{EHIScontrol_x - 45 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + 30) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + 30) * PI / 180)},
		{EHIScontrol_x - 45 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + 60) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + 60) * PI / 180)},
		{EHIScontrol_x - 45 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + 90) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + 90) * PI / 180)},
		{EHIScontrol_x - 45 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + 120) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + 120) * PI / 180)},
		{EHIScontrol_x - 45 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + 150) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + 150) * PI / 180)},
		{EHIScontrol_x - 45 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + 180) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + 180) * PI / 180)},
		{EHIScontrol_x - 45 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + 210) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + 210) * PI / 180)},
		{EHIScontrol_x - 45 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + 240) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + 240) * PI / 180)},
		{EHIScontrol_x - 45 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + 270) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + 270) * PI / 180)},
		{EHIScontrol_x - 45 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + 300) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + 300) * PI / 180)},
		{EHIScontrol_x - 45 * Ulength - Topknob_R1 * cos((LeftTopAngle_2 + 330) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((LeftTopAngle_2 + 330) * PI / 180)},

	};
	ege_setpattern_lineargradient(EHIScontrol_x - 44 * Ulength - Topknob_R1, EHIScontrol_y - 14 * Ulength - Topknob_R1, EGEARGB(0XFF, 0X6B, 0X6B, 0X69),
		EHIScontrol_x - 46 * Ulength + Topknob_R1, EHIScontrol_y - 16 * Ulength + Topknob_R1, EGEARGB(0XFF, 0X3D, 0X3C, 0X39));
	ege_fillpoly(LeftTopknobnum_3, LeftTopknobploypoints_3);
	ege_setpattern_none();
	setlinewidth(linewidth * 3);
	setcolor(EGEARGB(0XFF, 0X3A, 0X35, 0X2F));
	ege_line(EHIScontrol_x - 45 * Ulength, EHIScontrol_y - 15 * Ulength ,
		EHIScontrol_x - 45 * Ulength - (Topknob_R1 - Ulength/2) * cos(LeftTopAngle_2 * PI / 180), EHIScontrol_y - 15 * Ulength - (Topknob_R1 - Ulength/2) * sin(LeftTopAngle_2 * PI / 180));
	


	setlinewidth(linewidth * 1.1);
	setcolor(EGEARGB(0XFF, 0XB2, 0X7E, 0X50));
	ege_line(EHIScontrol_x - 45 * Ulength, EHIScontrol_y - 15 * Ulength,
		EHIScontrol_x - 45 * Ulength - (Topknob_R1 - Ulength / 2) * cos(LeftTopAngle_2 * PI / 180), EHIScontrol_y - 15 * Ulength - (Topknob_R1 - Ulength / 2) * sin(LeftTopAngle_2 * PI / 180));

	if (x < EHIScontrol_x - 43.5 * Ulength + Topknob_R1 && x> EHIScontrol_x - 48 * Ulength + Topknob_R1 && y>EHIScontrol_y - 15 * Ulength - Topknob_R1 && y < EHIScontrol_y - 15 * Ulength + Topknob_R1) {
		
		if (GetAsyncKeyState(0x04) & 0x0001) {
			
			if (LeftTopAngle_2 == 125) {
				LeftTopAngle_2 = 55;
				
			}
			else {
				LeftTopAngle_2 = 125;
			}


		}
	}


	if (x > EHIScontrol_x + 20.5 * Ulength + Topknob_R1 && x< EHIScontrol_x + 25 * Ulength + Topknob_R1 && y > EHIScontrol_y - 15 * Ulength - Topknob_R1 && y < EHIScontrol_y - 15 * Ulength + Topknob_R1) {
		if (GetAsyncKeyState(0x04) & 0x0001) {

			if (rightTopAngle_2 == 125) {
				rightTopAngle_2 = 55;

			}
			else{
				rightTopAngle_2 = 125;
			}


		}
	}


	setlinewidth(linewidth / 2);

	int LeftTopknobnum_2 = 12;//左上旋钮倒数第三层
	ege_point LeftTopknobploypoints_2[12] = {
		{EHIScontrol_x - 45 * Ulength - Topknob_R2 * cos(LeftTopAngle_1 * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin(LeftTopAngle_1 * PI / 180)},
		{EHIScontrol_x - 45 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + 30) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + 30) * PI / 180)},
		{EHIScontrol_x - 45 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + 60) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + 60) * PI / 180)},
		{EHIScontrol_x - 45 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + 90) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + 90) * PI / 180)},
		{EHIScontrol_x - 45 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + 120) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + 120) * PI / 180)},
		{EHIScontrol_x - 45 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + 150) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + 150) * PI / 180)},
		{EHIScontrol_x - 45 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + 180) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + 180) * PI / 180)},
		{EHIScontrol_x - 45 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + 210) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + 210) * PI / 180)},
		{EHIScontrol_x - 45 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + 240) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + 240) * PI / 180)},
		{EHIScontrol_x - 45 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + 270) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + 270) * PI / 180)},
		{EHIScontrol_x - 45 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + 300) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + 300) * PI / 180)},
		{EHIScontrol_x - 45 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + 330) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + 330) * PI / 180)},





	};
	ege_setpattern_lineargradient(EHIScontrol_x - 44 * Ulength - Topknob_R2, EHIScontrol_y - 14 * Ulength - Topknob_R2, EGEARGB(0XFF, 0X10, 0X10, 0X10),
		EHIScontrol_x - 46 * Ulength + Topknob_R2, EHIScontrol_y - 16 * Ulength + Topknob_R2, EGEARGB(0XFF, 0X7D, 0X7F, 0X7B));
	ege_fillpoly(LeftTopknobnum_2, LeftTopknobploypoints_2);
	ege_setpattern_none();

	setcolor(EGEARGB(0X2F, 0X50, 0X50, 0X50));
	for (int i = 0; i < 360; i += 30) {
		ege_line(EHIScontrol_x - 45 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + i) * PI / 180), EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + i) * PI / 180),
			EHIScontrol_x - 47 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + i) * PI / 180), EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + i) * PI / 180));
	}

	int LeftTopknobnum_1 = 12;//左上旋钮倒数第四层
	ege_point LeftTopknobploypoints_1[12] = {
		{EHIScontrol_x - 47 * Ulength - Topknob_R2 * cos(LeftTopAngle_1 * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin(LeftTopAngle_1 * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + 30) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + 30) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + 60) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + 60) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + 90) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + 90) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + 120) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + 120) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + 150) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + 150) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + 180) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + 180) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + 210) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + 210) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + 240) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + 240) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + 270) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + 270) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + 300) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + 300) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R2 * cos((LeftTopAngle_1 + 330) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((LeftTopAngle_1 + 330) * PI / 180)},





	};
	setfillcolor(EGEARGB(0XFF, 0X58, 0X58, 0X56));
	ege_fillpoly(LeftTopknobnum_1, LeftTopknobploypoints_1);


	if (x > EHIScontrol_x - 47 * Ulength - Topknob_R3 && x< EHIScontrol_x - 47 * Ulength + Topknob_R3 && y>EHIScontrol_y - 15 * Ulength - Topknob_R3 && y < EHIScontrol_y - 15 * Ulength + Topknob_R3) {

		if (GetAsyncKeyState(0x04) & 0x0001) {

			if (RST == 0) {
				Topknob_R4 = 7.5;
				RST = 1;
			}
			if (RST == 1) {
				Topknob_R4 = 7.5;
				RST = 0;
			}

		}
	}

	int LeftTopknobnum_6 = 12;//左上旋钮第二层
	ege_point LeftTopknobploypoints_6[12] = {
		{EHIScontrol_x - 47 * Ulength - Topknob_R4 * cos(LeftTopAngle_1 * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R4 * sin(LeftTopAngle_1 * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R4 * cos((LeftTopAngle_1 + 30) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R4 * sin((LeftTopAngle_1 + 30) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R4 * cos((LeftTopAngle_1 + 60) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R4 * sin((LeftTopAngle_1 + 60) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R4 * cos((LeftTopAngle_1 + 90) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R4 * sin((LeftTopAngle_1 + 90) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R4 * cos((LeftTopAngle_1 + 120) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R4 * sin((LeftTopAngle_1 + 120) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R4 * cos((LeftTopAngle_1 + 150) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R4 * sin((LeftTopAngle_1 + 150) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R4 * cos((LeftTopAngle_1 + 180) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R4 * sin((LeftTopAngle_1 + 180) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R4 * cos((LeftTopAngle_1 + 210) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R4 * sin((LeftTopAngle_1 + 210) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R4 * cos((LeftTopAngle_1 + 240) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R4 * sin((LeftTopAngle_1 + 240) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R4 * cos((LeftTopAngle_1 + 270) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R4 * sin((LeftTopAngle_1 + 270) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R4 * cos((LeftTopAngle_1 + 300) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R4 * sin((LeftTopAngle_1 + 300) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R4 * cos((LeftTopAngle_1 + 330) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R4 * sin((LeftTopAngle_1 + 330) * PI / 180)},





	};
	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillpoly(LeftTopknobnum_6, LeftTopknobploypoints_6);

	int LeftTopknobnum_5 = 12;//左上旋钮最顶层
	ege_point LeftTopknobploypoints_5[12] = {
		{EHIScontrol_x - 47 * Ulength - Topknob_R3 * cos(LeftTopAngle_1 * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin(LeftTopAngle_1 * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R3 * cos((LeftTopAngle_1 + 30) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin((LeftTopAngle_1 + 30) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R3 * cos((LeftTopAngle_1 + 60) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin((LeftTopAngle_1 + 60) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R3 * cos((LeftTopAngle_1 + 90) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin((LeftTopAngle_1 + 90) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R3 * cos((LeftTopAngle_1 + 120) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin((LeftTopAngle_1 + 120) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R3 * cos((LeftTopAngle_1 + 150) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin((LeftTopAngle_1 + 150) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R3 * cos((LeftTopAngle_1 + 180) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin((LeftTopAngle_1 + 180) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R3 * cos((LeftTopAngle_1 + 210) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin((LeftTopAngle_1 + 210) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R3 * cos((LeftTopAngle_1 + 240) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin((LeftTopAngle_1 + 240) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R3 * cos((LeftTopAngle_1 + 270) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin((LeftTopAngle_1 + 270) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R3 * cos((LeftTopAngle_1 + 300) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin((LeftTopAngle_1 + 300) * PI / 180)},
		{EHIScontrol_x - 47 * Ulength - Topknob_R3 * cos((LeftTopAngle_1 + 330) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin((LeftTopAngle_1 + 330) * PI / 180)},





	};
	setfillcolor(EGEARGB(0XFF, 0X11, 0X11, 0X11));
	ege_fillpoly(LeftTopknobnum_5, LeftTopknobploypoints_5);

	setbkmode(TRANSPARENT);
	setcolor(EGEARGB(0XFF, 0X60, 0X60, 0X60));
	setfont(Ulength * 6, Ulength * 2, "Bahnschrift");
	xyprintf(EHIScontrol_x - 44.5 * Ulength - Topknob_R3, EHIScontrol_y - 12 * Ulength - Topknob_R3, "RST");


	if (changecolor == 1) {

		setcolor(EGEARGB(ChangeLight, 0XB2, 0X7E, 0X50));
	}
	else {
		setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	}
	setfont(Ulength * 5, Ulength * 2, "Bahnschrift");
	ege_line(EHIScontrol_x + 43.5 * Ulength, EHIScontrol_y - 15 * Ulength,
		EHIScontrol_x + 43.5 * Ulength - (Topknob_R1 + 1.5 * Ulength) * cos(55 * PI / 180), EHIScontrol_y - 15 * Ulength - (Topknob_R1 + 1.5 * Ulength) * sin(55 * PI / 180));
	ege_line(EHIScontrol_x + 43.5 * Ulength, EHIScontrol_y - 15 * Ulength,
		EHIScontrol_x + 43.5 * Ulength - (Topknob_R1 + 1.5 * Ulength) * cos(125 * PI / 180), EHIScontrol_y - 15 * Ulength - (Topknob_R1 + 1.5 * Ulength) * sin(125 * PI / 180));
	ege_drawtext("HPA",EHIScontrol_x + 51 * Ulength, EHIScontrol_y - 30 * Ulength);
	ege_drawtext("BARO",EHIScontrol_x + 38 * Ulength, EHIScontrol_y - 33 * Ulength);
	ege_drawtext("IN",EHIScontrol_x + 31 * Ulength, EHIScontrol_y - 30 * Ulength);



	int rightTopknobnum_4 = 12;//右上旋钮最底层
	ege_point rightTopknobploypoints_4[12] = {
		{EHIScontrol_x + 43.5 * Ulength - Topknob_R1 * cos(rightTopAngle_2 * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin(rightTopAngle_2 * PI / 180)},
		{EHIScontrol_x + 43.5 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + 30) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + 30) * PI / 180)},
		{EHIScontrol_x + 43.5 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + 60) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + 60) * PI / 180)},
		{EHIScontrol_x + 43.5 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + 90) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + 90) * PI / 180)},
		{EHIScontrol_x + 43.5 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + 120) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + 120) * PI / 180)},
		{EHIScontrol_x + 43.5 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + 150) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + 150) * PI / 180)},
		{EHIScontrol_x + 43.5 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + 180) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + 180) * PI / 180)},
		{EHIScontrol_x + 43.5 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + 210) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + 210) * PI / 180)},
		{EHIScontrol_x + 43.5 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + 240) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + 240) * PI / 180)},
		{EHIScontrol_x + 43.5 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + 270) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + 270) * PI / 180)},
		{EHIScontrol_x + 43.5 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + 300) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + 300) * PI / 180)},
		{EHIScontrol_x + 43.5 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + 330) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + 330) * PI / 180)},

	};
	ege_setpattern_lineargradient(EHIScontrol_x + 42.5 * Ulength + Topknob_R2, EHIScontrol_y - 14 * Ulength - Topknob_R2, EGEARGB(0XFF, 0X10, 0X10, 0X10),
		EHIScontrol_x + 44.5 * Ulength - Topknob_R2, EHIScontrol_y - 15.2 * Ulength + Topknob_R2, EGEARGB(0XFF, 0X7D, 0X7F, 0X7B));
	ege_fillpoly(rightTopknobnum_4, rightTopknobploypoints_4);
	ege_setpattern_none();

	setcolor(EGEARGB(0X2F, 0X50, 0X50, 0X50));
	for (int i = 0; i < 360; i += 30) {
		ege_line(EHIScontrol_x + 43.5 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + i) * PI / 180), EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + i) * PI / 180),
			EHIScontrol_x + 45 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + i) * PI / 180), EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + i) * PI / 180));
	}
	setlinewidth(linewidth * 3);
	setcolor(EGEARGB(0XFF, 0X3A, 0X35, 0X2F));
	ege_line(EHIScontrol_x + 43.5 * Ulength, EHIScontrol_y - 15 * Ulength,
		EHIScontrol_x + 43.5 * Ulength - (Topknob_R1 - Ulength / 3) * cos(rightTopAngle_2 * PI / 180), EHIScontrol_y - 15 * Ulength - (Topknob_R1 - Ulength / 3) * sin(rightTopAngle_2 * PI / 180));

	setlinewidth(linewidth * 1.1);
	setcolor(EGEARGB(0XFF, 0XB2, 0X7E, 0X50));
	ege_line(EHIScontrol_x + 43.5 * Ulength, EHIScontrol_y - 15 * Ulength,
		EHIScontrol_x + 43.5 * Ulength - (Topknob_R1 - Ulength / 3) * cos(rightTopAngle_2 * PI / 180), EHIScontrol_y - 15 * Ulength - (Topknob_R1 - Ulength / 3) * sin(rightTopAngle_2 * PI / 180));

	setlinewidth(linewidth / 2);

	int rightTopknobnum_3 = 12;//右上旋钮倒数第二层
	ege_point rightTopknobploypoints_3[12] = {
		{EHIScontrol_x + 45 * Ulength - Topknob_R1 * cos(rightTopAngle_2 * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin(rightTopAngle_2 * PI / 180)},
		{EHIScontrol_x + 45 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + 30) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + 30) * PI / 180)},
		{EHIScontrol_x + 45 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + 60) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + 60) * PI / 180)},
		{EHIScontrol_x + 45 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + 90) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + 90) * PI / 180)},
		{EHIScontrol_x + 45 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + 120) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + 120) * PI / 180)},
		{EHIScontrol_x + 45 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + 150) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + 150) * PI / 180)},
		{EHIScontrol_x + 45 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + 180) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + 180) * PI / 180)},
		{EHIScontrol_x + 45 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + 210) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + 210) * PI / 180)},
		{EHIScontrol_x + 45 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + 240) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + 240) * PI / 180)},
		{EHIScontrol_x + 45 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + 270) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + 270) * PI / 180)},
		{EHIScontrol_x + 45 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + 300) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + 300) * PI / 180)},
		{EHIScontrol_x + 45 * Ulength - Topknob_R1 * cos((rightTopAngle_2 + 330) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R1 * sin((rightTopAngle_2 + 330) * PI / 180)},

	};
	ege_setpattern_lineargradient(EHIScontrol_x + 46 * Ulength - Topknob_R1, EHIScontrol_y - 16 * Ulength + Topknob_R1, EGEARGB(0XFF, 0X3D, 0X3C, 0X39),
		EHIScontrol_x + 44 * Ulength + Topknob_R1, EHIScontrol_y - 14 * Ulength - Topknob_R1, EGEARGB(0XFF, 0X6B, 0X6B, 0X69));
	ege_fillpoly(rightTopknobnum_3, rightTopknobploypoints_3);
	ege_setpattern_none();

	setlinewidth(linewidth * 3);
	setcolor(EGEARGB(0XFF, 0X3A, 0X35, 0X2F));
	ege_line(EHIScontrol_x + 45 * Ulength, EHIScontrol_y - 15 * Ulength,
		EHIScontrol_x + 45 * Ulength - (Topknob_R1 - Ulength / 4) * cos(rightTopAngle_2 * PI / 180), EHIScontrol_y - 15 * Ulength - (Topknob_R1 - Ulength / 4) * sin(rightTopAngle_2 * PI / 180));

	setlinewidth(linewidth * 1.1);
	setcolor(EGEARGB(0XFF, 0XB2, 0X7E, 0X50));
	ege_line(EHIScontrol_x + 45 * Ulength, EHIScontrol_y - 15 * Ulength,
		EHIScontrol_x + 45 * Ulength - (Topknob_R1 - Ulength / 4) * cos(rightTopAngle_2 * PI / 180), EHIScontrol_y - 15 * Ulength - (Topknob_R1 - Ulength / 4) * sin(rightTopAngle_2 * PI / 180));

	setlinewidth(linewidth / 2);

	int rightTopknobnum_2 = 12;//右上旋钮倒数第三层
	ege_point rightTopknobploypoints_2[12] = {
		{EHIScontrol_x + 45 * Ulength - Topknob_R2 * cos(rightTopAngle_1 * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin(rightTopAngle_1 * PI / 180)},
		{EHIScontrol_x + 45 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + 30) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + 30) * PI / 180)},
		{EHIScontrol_x + 45 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + 60) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + 60) * PI / 180)},
		{EHIScontrol_x + 45 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + 90) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + 90) * PI / 180)},
		{EHIScontrol_x + 45 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + 120) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + 120) * PI / 180)},
		{EHIScontrol_x + 45 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + 150) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + 150) * PI / 180)},
		{EHIScontrol_x + 45 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + 180) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + 180) * PI / 180)},
		{EHIScontrol_x + 45 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + 210) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + 210) * PI / 180)},
		{EHIScontrol_x + 45 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + 240) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + 240) * PI / 180)},
		{EHIScontrol_x + 45 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + 270) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + 270) * PI / 180)},
		{EHIScontrol_x + 45 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + 300) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + 300) * PI / 180)},
		{EHIScontrol_x + 45 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + 330) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + 330) * PI / 180)},





	};
	ege_setpattern_lineargradient(EHIScontrol_x + 46 * Ulength + Topknob_R2, EHIScontrol_y - 14 * Ulength - Topknob_R2, EGEARGB(0XFF, 0X10, 0X10, 0X10),
		EHIScontrol_x + 44 * Ulength - Topknob_R2, EHIScontrol_y - 16 * Ulength + Topknob_R2, EGEARGB(0XFF, 0X7D, 0X7F, 0X7B));
	ege_fillpoly(rightTopknobnum_2, rightTopknobploypoints_2);
	ege_setpattern_none();

	setcolor(EGEARGB(0X2F, 0X50, 0X50, 0X50));
	for (int i = 0; i < 360; i += 30) {
		ege_line(EHIScontrol_x + 45 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + i) * PI / 180), EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + i) * PI / 180),
			EHIScontrol_x + 47 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + i) * PI / 180), EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + i) * PI / 180));
	}

	int rightTopknobnum_1 = 12;//右上旋钮倒数第四层
	ege_point rightTopknobploypoints_1[12] = {
		{EHIScontrol_x + 47 * Ulength - Topknob_R2 * cos(rightTopAngle_1 * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin(rightTopAngle_1 * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + 30) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + 30) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + 60) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + 60) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + 90) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + 90) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + 120) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + 120) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + 150) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + 150) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + 180) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + 180) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + 210) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + 210) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + 240) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + 240) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + 270) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + 270) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + 300) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + 300) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R2 * cos((rightTopAngle_1 + 330) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R2 * sin((rightTopAngle_1 + 330) * PI / 180)},



	};
	setfillcolor(EGEARGB(0XFF, 0X58, 0X58, 0X56));
	ege_fillpoly(rightTopknobnum_1, rightTopknobploypoints_1);


	if (x < EHIScontrol_x + 47 * Ulength + Topknob_R3 && x > EHIScontrol_x + 47 * Ulength - Topknob_R3 && y>EHIScontrol_y - 15 * Ulength - Topknob_R3 && y < EHIScontrol_y - 15 * Ulength + Topknob_R3) {

		if (GetAsyncKeyState(0x04) & 0x0001) {

			if (STD == 0) {
				Topknob_R5 = 7.5;
				STD = 1;
			}
			if (STD == 1) {
				Topknob_R5 = 7.5;
				STD = 0;
			}

		}
	}

	int rightTopknobnum_6 = 12;//右上旋钮第二层
	ege_point rightTopknobploypoints_6[12] = {
		{EHIScontrol_x + 47 * Ulength - Topknob_R5 * cos(rightTopAngle_1 * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R5 * sin(rightTopAngle_1 * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R5 * cos((rightTopAngle_1 + 30) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R5 * sin((rightTopAngle_1 + 30) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R5 * cos((rightTopAngle_1 + 60) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R5 * sin((rightTopAngle_1 + 60) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R5 * cos((rightTopAngle_1 + 90) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R5 * sin((rightTopAngle_1 + 90) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R5 * cos((rightTopAngle_1 + 120) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R5 * sin((rightTopAngle_1 + 120) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R5 * cos((rightTopAngle_1 + 150) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R5 * sin((rightTopAngle_1 + 150) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R5 * cos((rightTopAngle_1 + 180) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R5 * sin((rightTopAngle_1 + 180) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R5 * cos((rightTopAngle_1 + 210) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R5 * sin((rightTopAngle_1 + 210) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R5 * cos((rightTopAngle_1 + 240) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R5 * sin((rightTopAngle_1 + 240) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R5 * cos((rightTopAngle_1 + 270) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R5 * sin((rightTopAngle_1 + 270) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R5 * cos((rightTopAngle_1 + 300) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R5 * sin((rightTopAngle_1 + 300) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R5 * cos((rightTopAngle_1 + 330) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R5 * sin((rightTopAngle_1 + 330) * PI / 180)},

	};
	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillpoly(rightTopknobnum_6, rightTopknobploypoints_6);

	int rightTopknobnum_5 = 12;//右上旋钮最顶层
	ege_point rightTopknobploypoints_5[12] = {
		{EHIScontrol_x + 47 * Ulength - Topknob_R3 * cos(rightTopAngle_1 * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin(rightTopAngle_1 * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R3 * cos((rightTopAngle_1 + 30) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin((rightTopAngle_1 + 30) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R3 * cos((rightTopAngle_1 + 60) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin((rightTopAngle_1 + 60) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R3 * cos((rightTopAngle_1 + 90) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin((rightTopAngle_1 + 90) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R3 * cos((rightTopAngle_1 + 120) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin((rightTopAngle_1 + 120) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R3 * cos((rightTopAngle_1 + 150) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin((rightTopAngle_1 + 150) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R3 * cos((rightTopAngle_1 + 180) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin((rightTopAngle_1 + 180) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R3 * cos((rightTopAngle_1 + 210) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin((rightTopAngle_1 + 210) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R3 * cos((rightTopAngle_1 + 240) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin((rightTopAngle_1 + 240) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R3 * cos((rightTopAngle_1 + 270) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin((rightTopAngle_1 + 270) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R3 * cos((rightTopAngle_1 + 300) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin((rightTopAngle_1 + 300) * PI / 180)},
		{EHIScontrol_x + 47 * Ulength - Topknob_R3 * cos((rightTopAngle_1 + 330) * PI / 180) ,EHIScontrol_y - 15 * Ulength - Topknob_R3 * sin((rightTopAngle_1 + 330) * PI / 180)},

	};
	setfillcolor(EGEARGB(0XFF, 0X11, 0X11, 0X11));
	ege_fillpoly(rightTopknobnum_5, rightTopknobploypoints_5);



	setbkmode(TRANSPARENT);
	setcolor(EGEARGB(0XFF, 0X60, 0X60, 0X60));
	setfont(Ulength * 6, Ulength * 2, "Bahnschrift");
	xyprintf(EHIScontrol_x + 50.5 * Ulength - Topknob_R3, EHIScontrol_y - 12 * Ulength - Topknob_R3, "STD");

	if (x > EHIScontrol_x - 17.5 * Ulength - Lowknob_R1 && x< EHIScontrol_x - 17.5 * Ulength - Lowknob_R4 && y > EHIScontrol_y + 11 * Ulength - Lowknob_R1 && y < EHIScontrol_y + 11 * Ulength + Lowknob_R1) {
		
		if (GetAsyncKeyState(0x04) & 0x0001) {
			if (leftLowAngle == 110) {
				leftLowAngle -= 30;
			}
			else if(leftLowAngle>55){
				leftLowAngle -= 25;
			}

		}
	}
	if (x < EHIScontrol_x - 17.5 * Ulength + Lowknob_R1 && x> EHIScontrol_x - 17.5 * Ulength + Lowknob_R4 && y > EHIScontrol_y + 11 * Ulength - Lowknob_R1 && y < EHIScontrol_y + 11 * Ulength + Lowknob_R1) {
		
		if (GetAsyncKeyState(0x04) & 0x0001) {
			if (leftLowAngle == 80) {
				leftLowAngle += 30;
			}
			else if (leftLowAngle < 135) {
				leftLowAngle += 25;
			}

		}
	}

	if (changecolor == 1) {

		setcolor(EGEARGB(ChangeLight, 0XB2, 0X7E, 0X50));
	}
	else {
		setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	}
	setfont(Ulength * 5, Ulength * 1.7, "Bahnschrift");
	ege_line(EHIScontrol_x - 17.5 * Ulength, EHIScontrol_y + 11 * Ulength,
		EHIScontrol_x - 17.5 * Ulength - (Lowknob_R1 + 1.5 * Ulength) * cos(55 * PI / 180), EHIScontrol_y + 11 * Ulength - (Lowknob_R1 + 1.5 * Ulength) * sin(55 * PI / 180));
	ege_line(EHIScontrol_x - 17.5 * Ulength, EHIScontrol_y + 11 * Ulength,
		EHIScontrol_x - 17.5 * Ulength - (Lowknob_R1 + 1.5 * Ulength) * cos(80 * PI / 180), EHIScontrol_y + 11 * Ulength - (Lowknob_R1 + 1.5 * Ulength) * sin(80 * PI / 180));
	ege_line(EHIScontrol_x - 17.5 * Ulength, EHIScontrol_y + 11 * Ulength,
		EHIScontrol_x - 17.5 * Ulength - (Lowknob_R1 + 1.5 * Ulength) * cos(110 * PI / 180), EHIScontrol_y + 11 * Ulength - (Lowknob_R1 + 1.5 * Ulength) * sin(115 * PI / 180));
	ege_line(EHIScontrol_x - 17.5 * Ulength, EHIScontrol_y + 11 * Ulength,
		EHIScontrol_x - 17.5 * Ulength - (Lowknob_R1 + 1.5 * Ulength) * cos(135 * PI / 180), EHIScontrol_y + 11 * Ulength - (Lowknob_R1 + 1.5 * Ulength) * sin(135 * PI / 180));
	
	ege_drawtext("APP",EHIScontrol_x - 31.5 * Ulength, EHIScontrol_y - 0.5 * Ulength);
	ege_drawtext("VOR",EHIScontrol_x - 25 * Ulength, EHIScontrol_y - 4 * Ulength);
	ege_drawtext("MAP", EHIScontrol_x - 16 * Ulength, EHIScontrol_y - 4 * Ulength);
	ege_drawtext("PLN",EHIScontrol_x - 10 * Ulength, EHIScontrol_y - 0 * Ulength);

	int leftLowknobnum_2 = 12;//左下旋钮
	ege_point leftLowknobploypoints_2[12] = {
		{EHIScontrol_x - 17.5 * Ulength - Lowknob_R1 * cos(leftLowAngle * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin(leftLowAngle * PI / 180)},
		{EHIScontrol_x - 17.5 * Ulength - Lowknob_R1 * cos((leftLowAngle + 30) * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((leftLowAngle + 30) * PI / 180)},
		{EHIScontrol_x - 17.5 * Ulength - Lowknob_R1 * cos((leftLowAngle + 60) * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((leftLowAngle + 60) * PI / 180)},
		{EHIScontrol_x - 17.5 * Ulength - Lowknob_R1 * cos((leftLowAngle + 90) * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((leftLowAngle + 90) * PI / 180)},
		{EHIScontrol_x - 17.5 * Ulength - Lowknob_R1 * cos((leftLowAngle + 120) * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((leftLowAngle + 120) * PI / 180)},
		{EHIScontrol_x - 17.5 * Ulength - Lowknob_R1 * cos((leftLowAngle + 150) * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((leftLowAngle + 150) * PI / 180)},
		{EHIScontrol_x - 17.5 * Ulength - Lowknob_R1 * cos((leftLowAngle + 180) * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((leftLowAngle + 180) * PI / 180)},
		{EHIScontrol_x - 17.5 * Ulength - Lowknob_R1 * cos((leftLowAngle + 210) * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((leftLowAngle + 210) * PI / 180)},
		{EHIScontrol_x - 17.5 * Ulength - Lowknob_R1 * cos((leftLowAngle + 240) * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((leftLowAngle + 240) * PI / 180)},
		{EHIScontrol_x - 17.5 * Ulength - Lowknob_R1 * cos((leftLowAngle + 270) * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((leftLowAngle + 270) * PI / 180)},
		{EHIScontrol_x - 17.5 * Ulength - Lowknob_R1 * cos((leftLowAngle + 300) * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((leftLowAngle + 300) * PI / 180)},
		{EHIScontrol_x - 17.5 * Ulength - Lowknob_R1 * cos((leftLowAngle + 330) * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((leftLowAngle + 330) * PI / 180)},
	};

	setfillcolor(EGEARGB(0XFF, 0X58, 0X58, 0X56));
	ege_setpattern_lineargradient(EHIScontrol_x - 17.5 * Ulength, EHIScontrol_y + 11 * Ulength - Lowknob_R1, EGEARGB(0XFF, 0X20, 0X20, 0X20),
		EHIScontrol_x - 17.5 * Ulength, EHIScontrol_y + 11 * Ulength + Lowknob_R1, EGEARGB(0XFF, 0X7D, 0X7F, 0X7B));
	ege_fillpoly(leftLowknobnum_2, leftLowknobploypoints_2);
	ege_setpattern_none();
	setcolor(EGEARGB(0X1F, 0X50, 0X50, 0X50));
	for (int i = 0; i < 360; i += 30) {
		ege_line(EHIScontrol_x - 17.5 * Ulength - Lowknob_R1 * cos((leftLowAngle + i) * PI / 180), EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((leftLowAngle + i) * PI / 180),
			EHIScontrol_x - 18 * Ulength - Lowknob_R2 * cos((leftLowAngle + i) * PI / 180), EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((leftLowAngle + i) * PI / 180));
	}
	


	int leftLowknobnum_1 = 12;
	ege_point leftLowknobploypoints_1[12] = {
		{EHIScontrol_x - 18 * Ulength - Lowknob_R2 * cos(leftLowAngle * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin(leftLowAngle * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R2 * cos((leftLowAngle + 30) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((leftLowAngle + 30) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R2 * cos((leftLowAngle + 60) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((leftLowAngle + 60) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R2 * cos((leftLowAngle + 90) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((leftLowAngle + 90) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R2 * cos((leftLowAngle + 120) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((leftLowAngle + 120) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R2 * cos((leftLowAngle + 150) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((leftLowAngle + 150) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R2 * cos((leftLowAngle + 180) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((leftLowAngle + 180) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R2 * cos((leftLowAngle + 210) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((leftLowAngle + 210) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R2 * cos((leftLowAngle + 240) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((leftLowAngle + 240) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R2 * cos((leftLowAngle + 270) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((leftLowAngle + 270) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R2 * cos((leftLowAngle + 300) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((leftLowAngle + 300) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R2 * cos((leftLowAngle + 330) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((leftLowAngle + 330) * PI / 180)},
	};

	setfillcolor(EGEARGB(0XFF, 0X58, 0X58, 0X56));
	ege_fillpoly(leftLowknobnum_1, leftLowknobploypoints_1);
	setlinewidth(linewidth * 2.5);
	setcolor(EGEARGB(0XFF, 0X2A, 0X25, 0X1F));
	ege_line(EHIScontrol_x - 18 * Ulength, EHIScontrol_y + 11 * Ulength,
		EHIScontrol_x - 17.5 * Ulength - (Lowknob_R1 - Ulength / 3) * cos(leftLowAngle  * PI / 180), EHIScontrol_y + 11 * Ulength - (Lowknob_R1 - Ulength / 3) * sin(leftLowAngle  * PI / 180));

	setlinewidth(linewidth * 1);
	setcolor(EGEARGB(0XFF, 0XB2, 0X7E, 0X50));
	ege_line(EHIScontrol_x - 18 * Ulength, EHIScontrol_y + 11 * Ulength,
		EHIScontrol_x - 17.5 * Ulength - (Lowknob_R1 - Ulength / 3) * cos(leftLowAngle  * PI / 180), EHIScontrol_y + 11 * Ulength - (Lowknob_R1 - Ulength / 3) * sin(leftLowAngle * PI / 180));

	setlinewidth(linewidth / 4);

	setcolor(EGEARGB(0X3F, 0X58, 0X58, 0X56));
	ege_line(EHIScontrol_x - 18 * Ulength - Lowknob_R2 * cos(leftLowAngle * PI / 180), EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin(leftLowAngle * PI / 180),
		EHIScontrol_x - 18 * Ulength - Lowknob_R2 * cos((leftLowAngle + 30) * PI / 180), EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((leftLowAngle + 30) * PI / 180));
	setlinewidth(linewidth / 2);

	if (x < EHIScontrol_x - 18 * Ulength + Lowknob_R3 && x > EHIScontrol_x - 18 * Ulength - Lowknob_R3 && y > EHIScontrol_y + 12 * Ulength - Lowknob_R3 && y < EHIScontrol_y + 12 * Ulength + Lowknob_R3) {

		if (GetAsyncKeyState(0x04) & 0x0001) {

			if (CTR == 0) {
				Lowknob_R4 = 6;
				CTR = 1;
			}
			if (CTR == 1) {
				Lowknob_R4 = 6;
				CTR = 0;
			}

		}
	}

	int leftLowknobnum_3 = 12;
	ege_point leftLowknobploypoints_3[12] = {
		{EHIScontrol_x - 18 * Ulength - Lowknob_R4 * cos(leftLowAngle * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R4 * sin(leftLowAngle * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R4 * cos((leftLowAngle + 30) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R4 * sin((leftLowAngle + 30) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R4 * cos((leftLowAngle + 60) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R4 * sin((leftLowAngle + 60) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R4 * cos((leftLowAngle + 90) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R4 * sin((leftLowAngle + 90) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R4 * cos((leftLowAngle + 120) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R4 * sin((leftLowAngle + 120) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R4 * cos((leftLowAngle + 150) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R4 * sin((leftLowAngle + 150) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R4 * cos((leftLowAngle + 180) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R4 * sin((leftLowAngle + 180) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R4 * cos((leftLowAngle + 210) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R4 * sin((leftLowAngle + 210) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R4 * cos((leftLowAngle + 240) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R4 * sin((leftLowAngle + 240) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R4 * cos((leftLowAngle + 270) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R4 * sin((leftLowAngle + 270) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R4 * cos((leftLowAngle + 300) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R4 * sin((leftLowAngle + 300) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R4 * cos((leftLowAngle + 330) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R4 * sin((leftLowAngle + 330) * PI / 180)},
	};

	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillpoly(leftLowknobnum_3, leftLowknobploypoints_3);


	int leftLowknobnum_4 = 12;
	ege_point leftLowknobploypoints_4[12] = {
		{EHIScontrol_x - 18 * Ulength - Lowknob_R3 * cos(leftLowAngle * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin(leftLowAngle * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R3 * cos((leftLowAngle + 30) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin((leftLowAngle + 30) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R3 * cos((leftLowAngle + 60) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin((leftLowAngle + 60) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R3 * cos((leftLowAngle + 90) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin((leftLowAngle + 90) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R3 * cos((leftLowAngle + 120) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin((leftLowAngle + 120) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R3 * cos((leftLowAngle + 150) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin((leftLowAngle + 150) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R3 * cos((leftLowAngle + 180) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin((leftLowAngle + 180) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R3 * cos((leftLowAngle + 210) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin((leftLowAngle + 210) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R3 * cos((leftLowAngle + 240) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin((leftLowAngle + 240) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R3 * cos((leftLowAngle + 270) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin((leftLowAngle + 270) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R3 * cos((leftLowAngle + 300) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin((leftLowAngle + 300) * PI / 180)},
		{EHIScontrol_x - 18 * Ulength - Lowknob_R3 * cos((leftLowAngle + 330) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin((leftLowAngle + 330) * PI / 180)},
	};

	setfillcolor(EGEARGB(0XFF, 0X11, 0X11, 0X11));
	ege_fillpoly(leftLowknobnum_4, leftLowknobploypoints_4);
	setcolor(EGEARGB(0XFF, 0X60, 0X60, 0X60));
	setfont(Ulength * 5, Ulength * 2, "Bahnschrift");
	xyprintf(EHIScontrol_x - 16.5 * Ulength - Lowknob_R3, EHIScontrol_y + 14 * Ulength - Lowknob_R3, "CTR");


	if (changecolor == 1) {

		setcolor(EGEARGB(ChangeLight, 0XB2, 0X7E, 0X50));
	}
	else {
		setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	}
	setfont(Ulength * 5, Ulength * 2, "Bahnschrift");
	for (int i = 0; i <= 210; i += 30) {
		ege_line(EHIScontrol_x + 17.5 * Ulength, EHIScontrol_y + 11 * Ulength,
			EHIScontrol_x + 17.5 * Ulength - (Lowknob_R1 + Ulength * 2) * cos(i * PI / 180), EHIScontrol_y + 11 * Ulength - (Lowknob_R1 + Ulength * 2) * sin(i * PI / 180));
	}

	ege_drawtext("5",EHIScontrol_x + 3 * Ulength, EHIScontrol_y + 9 * Ulength);
	ege_drawtext("10",EHIScontrol_x + 3 * Ulength, EHIScontrol_y + 3 * Ulength);
	ege_drawtext("20",EHIScontrol_x + 7 * Ulength, EHIScontrol_y - 2 * Ulength);
	ege_drawtext("40",EHIScontrol_x + 14 * Ulength, EHIScontrol_y - 4 * Ulength);
	ege_drawtext("80",EHIScontrol_x + 21 * Ulength, EHIScontrol_y - 2.5 * Ulength);
	ege_drawtext("160",EHIScontrol_x + 26.5 * Ulength, EHIScontrol_y + 2.5 * Ulength);
	ege_drawtext("320",EHIScontrol_x + 28 * Ulength, EHIScontrol_y + 9 * Ulength);
	ege_drawtext("640",EHIScontrol_x + 27 * Ulength, EHIScontrol_y + 15 * Ulength);


	if (x > EHIScontrol_x + 17.5 * Ulength - Lowknob_R1 && x< EHIScontrol_x + 17.5 * Ulength - Lowknob_R4 && y > EHIScontrol_y + 11 * Ulength - Lowknob_R1 && y < EHIScontrol_y + 11 * Ulength + Lowknob_R1) {
		
		if (GetAsyncKeyState(0x04) & 0x0001) {
			if (rightLowAngle > 0) {
				rightLowAngle -= 30;
			}
		}
	}
	if (x < EHIScontrol_x + 17.5 * Ulength + Lowknob_R1 && x> EHIScontrol_x + 17.5 * Ulength + Lowknob_R4 && y > EHIScontrol_y + 11 * Ulength - Lowknob_R1 && y < EHIScontrol_y + 11 * Ulength + Lowknob_R1) {
	
		if (GetAsyncKeyState(0x04) & 0x0001) {
			if (rightLowAngle < 210) {
				rightLowAngle += 30;
			}

		}
	}

	int rightLowknobnum_2 = 12;//右下旋钮
	ege_point rightLowknobploypoints_2[12] = {
		{EHIScontrol_x + 17.5 * Ulength - Lowknob_R1 * cos(rightLowAngle * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin(rightLowAngle * PI / 180)},
		{EHIScontrol_x + 17.5 * Ulength - Lowknob_R1 * cos((rightLowAngle + 30) * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((rightLowAngle + 30) * PI / 180)},
		{EHIScontrol_x + 17.5 * Ulength - Lowknob_R1 * cos((rightLowAngle + 60) * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((rightLowAngle + 60) * PI / 180)},
		{EHIScontrol_x + 17.5 * Ulength - Lowknob_R1 * cos((rightLowAngle + 90) * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((rightLowAngle + 90) * PI / 180)},
		{EHIScontrol_x + 17.5 * Ulength - Lowknob_R1 * cos((rightLowAngle + 120) * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((rightLowAngle + 120) * PI / 180)},
		{EHIScontrol_x + 17.5 * Ulength - Lowknob_R1 * cos((rightLowAngle + 150) * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((rightLowAngle + 150) * PI / 180)},
		{EHIScontrol_x + 17.5 * Ulength - Lowknob_R1 * cos((rightLowAngle + 180) * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((rightLowAngle + 180) * PI / 180)},
		{EHIScontrol_x + 17.5 * Ulength - Lowknob_R1 * cos((rightLowAngle + 210) * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((rightLowAngle + 210) * PI / 180)},
		{EHIScontrol_x + 17.5 * Ulength - Lowknob_R1 * cos((rightLowAngle + 240) * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((rightLowAngle + 240) * PI / 180)},
		{EHIScontrol_x + 17.5 * Ulength - Lowknob_R1 * cos((rightLowAngle + 270) * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((rightLowAngle + 270) * PI / 180)},
		{EHIScontrol_x + 17.5 * Ulength - Lowknob_R1 * cos((rightLowAngle + 300) * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((rightLowAngle + 300) * PI / 180)},
		{EHIScontrol_x + 17.5 * Ulength - Lowknob_R1 * cos((rightLowAngle + 330) * PI / 180) , EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((rightLowAngle + 330) * PI / 180)},
	};

	setfillcolor(EGEARGB(0XFF, 0X58, 0X58, 0X56));
	ege_setpattern_lineargradient(EHIScontrol_x + 17.5 * Ulength, EHIScontrol_y + 11 * Ulength - Lowknob_R1, EGEARGB(0XFF, 0X20, 0X20, 0X20),
		EHIScontrol_x + 17.5 * Ulength, EHIScontrol_y + 11 * Ulength + Lowknob_R1, EGEARGB(0XFF, 0X7D, 0X7F, 0X7B));
	ege_fillpoly(rightLowknobnum_2, rightLowknobploypoints_2);
	ege_setpattern_none();
	setcolor(EGEARGB(0X1F, 0X50, 0X50, 0X50));
	for (int i = 0; i < 360; i += 30) {
		ege_line(EHIScontrol_x + 17.5 * Ulength - Lowknob_R1 * cos((rightLowAngle + i) * PI / 180), EHIScontrol_y + 11 * Ulength - Lowknob_R1 * sin((rightLowAngle + i) * PI / 180),
			EHIScontrol_x + 18 * Ulength - Lowknob_R2 * cos((rightLowAngle + i) * PI / 180), EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((rightLowAngle + i) * PI / 180));
	}
	
	int rightLowknobnum_1 = 12;
	ege_point rightLowknobploypoints_1[12] = {
		{EHIScontrol_x + 18 * Ulength - Lowknob_R2 * cos(rightLowAngle * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin(rightLowAngle * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R2 * cos((rightLowAngle + 30) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((rightLowAngle + 30) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R2 * cos((rightLowAngle + 60) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((rightLowAngle + 60) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R2 * cos((rightLowAngle + 90) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((rightLowAngle + 90) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R2 * cos((rightLowAngle + 120) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((rightLowAngle + 120) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R2 * cos((rightLowAngle + 150) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((rightLowAngle + 150) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R2 * cos((rightLowAngle + 180) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((rightLowAngle + 180) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R2 * cos((rightLowAngle + 210) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((rightLowAngle + 210) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R2 * cos((rightLowAngle + 240) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((rightLowAngle + 240) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R2 * cos((rightLowAngle + 270) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((rightLowAngle + 270) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R2 * cos((rightLowAngle + 300) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((rightLowAngle + 300) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R2 * cos((rightLowAngle + 330) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((rightLowAngle + 330) * PI / 180)},
	};

	setfillcolor(EGEARGB(0XFF, 0X58, 0X58, 0X56));
	ege_fillpoly(rightLowknobnum_1, rightLowknobploypoints_1);

	setlinewidth(linewidth * 2.5);
	setcolor(EGEARGB(0XFF, 0X2A, 0X25, 0X1F));
	ege_line(EHIScontrol_x + 18 * Ulength, EHIScontrol_y + 11 * Ulength,
		EHIScontrol_x + 17.5 * Ulength - (Lowknob_R1 - Ulength / 3) * cos(rightLowAngle  * PI / 180), EHIScontrol_y + 11 * Ulength - (Lowknob_R1 - Ulength / 3) * sin(rightLowAngle  * PI / 180));

	setlinewidth(linewidth * 1);
	setcolor(EGEARGB(0XFF, 0XB2, 0X7E, 0X50));
	ege_line(EHIScontrol_x + 18 * Ulength, EHIScontrol_y + 11 * Ulength,
		EHIScontrol_x + 17.5 * Ulength - (Lowknob_R1 - Ulength / 3) * cos(rightLowAngle  * PI / 180), EHIScontrol_y + 11 * Ulength - (Lowknob_R1 - Ulength / 3) * sin(rightLowAngle  * PI / 180));

	setlinewidth(linewidth / 4);

	setcolor(EGEARGB(0X3F, 0X58, 0X58, 0X56));
	ege_line(EHIScontrol_x + 18 * Ulength - Lowknob_R2 * cos((rightLowAngle + 30) * PI / 180), EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin((rightLowAngle + 30) * PI / 180),
		EHIScontrol_x + 18 * Ulength - Lowknob_R2 * cos(rightLowAngle * PI / 180), EHIScontrol_y + 12 * Ulength - Lowknob_R2 * sin(rightLowAngle  * PI / 180));
	setlinewidth(linewidth / 2);

	if (x < EHIScontrol_x + 18 * Ulength + Lowknob_R3 && x > EHIScontrol_x + 18 * Ulength - Lowknob_R3 && y > EHIScontrol_y + 12 * Ulength - Lowknob_R3 && y < EHIScontrol_y + 12 * Ulength + Lowknob_R3) {

		if (GetAsyncKeyState(0x04) & 0x0001) {

			if (TFC == 0) {
				Lowknob_R5 = 6;
				TFC = 1;
			}
			if (TFC == 1) {
				Lowknob_R5 = 6;
				TFC = 0;
			}

		}
	}


	int rightLowknobnum_3 = 12;
	ege_point rightLowknobploypoints_3[12] = {
		{EHIScontrol_x + 18 * Ulength - Lowknob_R5 * cos(rightLowAngle * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R5 * sin(rightLowAngle * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R5 * cos((rightLowAngle + 30) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R5 * sin((rightLowAngle + 30) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R5 * cos((rightLowAngle + 60) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R5 * sin((rightLowAngle + 60) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R5 * cos((rightLowAngle + 90) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R5 * sin((rightLowAngle + 90) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R5 * cos((rightLowAngle + 120) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R5 * sin((rightLowAngle + 120) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R5 * cos((rightLowAngle + 150) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R5 * sin((rightLowAngle + 150) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R5 * cos((rightLowAngle + 180) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R5 * sin((rightLowAngle + 180) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R5 * cos((rightLowAngle + 210) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R5 * sin((rightLowAngle + 210) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R5 * cos((rightLowAngle + 240) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R5 * sin((rightLowAngle + 240) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R5 * cos((rightLowAngle + 270) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R5 * sin((rightLowAngle + 270) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R5 * cos((rightLowAngle + 300) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R5 * sin((rightLowAngle + 300) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R5 * cos((rightLowAngle + 330) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R5 * sin((rightLowAngle + 330) * PI / 180)},
	};

	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillpoly(rightLowknobnum_3, rightLowknobploypoints_3);


	int rightLowknobnum_4 = 12;
	ege_point rightLowknobploypoints_4[12] = {
		{EHIScontrol_x + 18 * Ulength - Lowknob_R3 * cos(rightLowAngle * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin(rightLowAngle * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R3 * cos((rightLowAngle + 30) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin((rightLowAngle + 30) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R3 * cos((rightLowAngle + 60) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin((rightLowAngle + 60) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R3 * cos((rightLowAngle + 90) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin((rightLowAngle + 90) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R3 * cos((rightLowAngle + 120) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin((rightLowAngle + 120) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R3 * cos((rightLowAngle + 150) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin((rightLowAngle + 150) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R3 * cos((rightLowAngle + 180) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin((rightLowAngle + 180) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R3 * cos((rightLowAngle + 210) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin((rightLowAngle + 210) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R3 * cos((rightLowAngle + 240) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin((rightLowAngle + 240) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R3 * cos((rightLowAngle + 270) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin((rightLowAngle + 270) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R3 * cos((rightLowAngle + 300) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin((rightLowAngle + 300) * PI / 180)},
		{EHIScontrol_x + 18 * Ulength - Lowknob_R3 * cos((rightLowAngle + 330) * PI / 180) , EHIScontrol_y + 12 * Ulength - Lowknob_R3 * sin((rightLowAngle + 330) * PI / 180)},
	};

	setfillcolor(EGEARGB(0XFF, 0X11, 0X11, 0X11));
	ege_fillpoly(rightLowknobnum_4, rightLowknobploypoints_4);
	setcolor(EGEARGB(0XFF, 0X60, 0X60, 0X60));
	setfont(Ulength * 5, Ulength * 2, "Bahnschrift");
	xyprintf(EHIScontrol_x + 19.5 * Ulength - Lowknob_R3, EHIScontrol_y + 14 * Ulength - Lowknob_R3, "TFC");

	

	int ii = 0;
	int jj = 0;
	if (x > EHIScontrol_x - 18 * Ulength && x < EHIScontrol_x - 8 * Ulength &&
		y > EHIScontrol_y - Ulength * 27 && y < EHIScontrol_y - Ulength * 17) {
		
		if (GetAsyncKeyState(0x04) & 0x0001) {

			if (FPV == 0) {
				ii = 1;
				FPV = 1;
			}
			if (FPV == 1) {
				ii = 1;
				FPV = 0;
			}

		}
	}

	
	if (x < EHIScontrol_x + 18 * Ulength && x > EHIScontrol_x + 8 * Ulength &&
		y > EHIScontrol_y - Ulength * 27 && y < EHIScontrol_y - Ulength * 17) {
		
		if (GetAsyncKeyState(0x04) & 0x0001) {

			if (MTRS == 0) {
				jj = 1;
				MTRS = 1;
			}
			if (MTRS == 1) {
				jj = 1;
				MTRS = 0;
			}

		}
	}

	//最上面左边的按钮
	setfillcolor(EGEARGB(0XFF, 0X40, 0X40, 0X40));
	ege_fillellipse(EHIScontrol_x - 18 * Ulength, EHIScontrol_y - Ulength * 27, Ulength * 10.2, Ulength * 10.2);
	ege_fillellipse(EHIScontrol_x + 8 * Ulength, EHIScontrol_y - Ulength * 27, Ulength * 10.2, Ulength * 10.2);
	//最上面右边的按钮
	setfillcolor(EGEARGB(0XFF, 0X18, 0X18, 0X18));
	ege_fillellipse(EHIScontrol_x - (18 + ii) * Ulength, EHIScontrol_y - Ulength * 27, Ulength * (10 + 2 * ii), Ulength * (10 + 2 * ii));
	ege_fillellipse(EHIScontrol_x + (8 - jj) * Ulength, EHIScontrol_y - Ulength * 27, Ulength * (10 + 2 * jj), Ulength * (10 + 2 * jj));





	//最底下的按钮，从左到右
	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillrect(EHIScontrol_x - 59.2 * Ulength, EHIScontrol_y + 22.2 * Ulength, Ulength * 11, Ulength * 11);
	ege_fillrect(EHIScontrol_x - 41.2 * Ulength, EHIScontrol_y + 22.2 * Ulength, Ulength * 11, Ulength * 11);
	ege_fillrect(EHIScontrol_x - 23.2 * Ulength, EHIScontrol_y + 22.2 * Ulength, Ulength * 11, Ulength * 11);
	ege_fillrect(EHIScontrol_x - 5.2 * Ulength, EHIScontrol_y + 22.2 * Ulength, Ulength * 11, Ulength * 11);
	ege_fillrect(EHIScontrol_x + 12.8 * Ulength, EHIScontrol_y + 22.2 * Ulength, Ulength * 11, Ulength * 11);
	ege_fillrect(EHIScontrol_x + 30.8 * Ulength, EHIScontrol_y + 22.2 * Ulength, Ulength * 11, Ulength * 11);
	ege_fillrect(EHIScontrol_x + 48.8 * Ulength, EHIScontrol_y + 22.2 * Ulength, Ulength * 11, Ulength * 11);

	setfillcolor(EGEARGB(0XFF, 0X40, 0X40, 0X40));
	ege_fillrect(EHIScontrol_x - 58.8 * Ulength, EHIScontrol_y + 21.8 * Ulength, Ulength * 11, Ulength * 11);
	ege_fillrect(EHIScontrol_x - 40.8 * Ulength, EHIScontrol_y + 21.8 * Ulength, Ulength * 11, Ulength * 11);
	ege_fillrect(EHIScontrol_x - 22.8 * Ulength, EHIScontrol_y + 21.8 * Ulength, Ulength * 11, Ulength * 11);
	ege_fillrect(EHIScontrol_x - 4.8 * Ulength, EHIScontrol_y + 21.8 * Ulength, Ulength * 11, Ulength * 11);
	ege_fillrect(EHIScontrol_x + 13.2 * Ulength, EHIScontrol_y + 21.8 * Ulength, Ulength * 11, Ulength * 11);
	ege_fillrect(EHIScontrol_x + 31.2 * Ulength, EHIScontrol_y + 21.8 * Ulength, Ulength * 11, Ulength * 11);
	ege_fillrect(EHIScontrol_x + 49.2 * Ulength, EHIScontrol_y + 21.8 * Ulength, Ulength * 11, Ulength * 11);



	setfillcolor(EGEARGB(0XFF, 0X18, 0X18, 0X18));
	ege_fillrect(EHIScontrol_x - 59 * Ulength, EHIScontrol_y + 22 * Ulength, Ulength * 11, Ulength * 11);
	ege_fillrect(EHIScontrol_x - 41 * Ulength, EHIScontrol_y + 22 * Ulength, Ulength * 11, Ulength * 11);
	ege_fillrect(EHIScontrol_x - 23 * Ulength, EHIScontrol_y + 22 * Ulength, Ulength * 11, Ulength * 11);
	ege_fillrect(EHIScontrol_x - 5 * Ulength, EHIScontrol_y + 22 * Ulength, Ulength * 11, Ulength * 11);
	ege_fillrect(EHIScontrol_x + 13 * Ulength, EHIScontrol_y + 22 * Ulength, Ulength * 11, Ulength * 11);
	ege_fillrect(EHIScontrol_x + 31 * Ulength, EHIScontrol_y + 22 * Ulength, Ulength * 11, Ulength * 11);
	ege_fillrect(EHIScontrol_x + 49 * Ulength, EHIScontrol_y + 22 * Ulength, Ulength * 11, Ulength * 11);




	if (changecolor == 1) {

		setcolor(EGEARGB(ChangeLight, 0XB2, 0X7E, 0X50));
	}
	else {
		setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	}
	ege_ellipse(EHIScontrol_x - 20 * Ulength, EHIScontrol_y - Ulength * 29, Ulength * 14, Ulength * 14);
	ege_ellipse(EHIScontrol_x + 6 * Ulength, EHIScontrol_y - Ulength * 29, Ulength * 14, Ulength * 14);
	setfont(Ulength * 5, Ulength * 2, "Bahnschrift");
	ege_drawtext("FPV",EHIScontrol_x - 17 * Ulength, EHIScontrol_y - Ulength * 34);
	ege_drawtext("MTRS",EHIScontrol_x + 8 * Ulength, EHIScontrol_y - Ulength * 34);
	setfont(Ulength * 5, Ulength * 2, "Bahnschrift");
	ege_drawtext("WXR",EHIScontrol_x - 58 * Ulength, EHIScontrol_y + 26 * Ulength);
	ege_drawtext("STA",EHIScontrol_x - 40 * Ulength, EHIScontrol_y + 26 * Ulength);
	ege_drawtext("WPT",EHIScontrol_x - 22 * Ulength, EHIScontrol_y + 26 * Ulength);
	ege_drawtext("ARPT",EHIScontrol_x - 5 * Ulength, EHIScontrol_y + 26 * Ulength);
	ege_drawtext("DATA",EHIScontrol_x + 13 * Ulength, EHIScontrol_y + 26 * Ulength);
	ege_drawtext("POS",EHIScontrol_x + 32 * Ulength, EHIScontrol_y + 26 * Ulength);
	ege_drawtext("TERR",EHIScontrol_x + 49 * Ulength, EHIScontrol_y + 26 * Ulength);







	int VOR1nums = 13;
	ege_point VOR1ploypoints[13] = {
		{EHIScontrol_x - Ulength * 61,EHIScontrol_y + 2 * Ulength},
		{EHIScontrol_x - Ulength * 58,EHIScontrol_y - 2 * Ulength},
		{EHIScontrol_x - Ulength * 54,EHIScontrol_y - 2 * Ulength},
		{EHIScontrol_x - Ulength * 51,EHIScontrol_y + 2 * Ulength},

		{EHIScontrol_x - Ulength * 51,EHIScontrol_y + 11 * Ulength},
		{EHIScontrol_x - Ulength * 51,EHIScontrol_y + 11 * Ulength},
		{EHIScontrol_x - Ulength * 51,EHIScontrol_y + 11 * Ulength},

		{EHIScontrol_x - Ulength * 54,EHIScontrol_y + 15 * Ulength},
		{EHIScontrol_x - Ulength * 58,EHIScontrol_y + 15 * Ulength},
		{EHIScontrol_x - Ulength * 61,EHIScontrol_y + 11 * Ulength},

		{EHIScontrol_x - Ulength * 61,EHIScontrol_y + 2 * Ulength},
		{EHIScontrol_x - Ulength * 61,EHIScontrol_y + 2 * Ulength},
		{EHIScontrol_x - Ulength * 61,EHIScontrol_y + 2 * Ulength},

	};
	ege_bezier(VOR1nums, VOR1ploypoints);
	ege_drawtext("VOR 1",EHIScontrol_x - Ulength * 62, EHIScontrol_y - 5 * Ulength);
	ege_drawtext("OFF",EHIScontrol_x - Ulength * 51, EHIScontrol_y + 5 * Ulength);

	int VOR2nums = 13;
	ege_point VOR2ploypoints[13] = {
		{EHIScontrol_x + Ulength * 61,EHIScontrol_y + 2 * Ulength},
		{EHIScontrol_x + Ulength * 58,EHIScontrol_y - 2 * Ulength},
		{EHIScontrol_x + Ulength * 54,EHIScontrol_y - 2 * Ulength},
		{EHIScontrol_x + Ulength * 51,EHIScontrol_y + 2 * Ulength},

		{EHIScontrol_x + Ulength * 51,EHIScontrol_y + 11 * Ulength},
		{EHIScontrol_x + Ulength * 51,EHIScontrol_y + 11 * Ulength},
		{EHIScontrol_x + Ulength * 51,EHIScontrol_y + 11 * Ulength},

		{EHIScontrol_x + Ulength * 54,EHIScontrol_y + 15 * Ulength},
		{EHIScontrol_x + Ulength * 58,EHIScontrol_y + 15 * Ulength},
		{EHIScontrol_x + Ulength * 61,EHIScontrol_y + 11 * Ulength},

		{EHIScontrol_x + Ulength * 61,EHIScontrol_y + 2 * Ulength},
		{EHIScontrol_x + Ulength * 61,EHIScontrol_y + 2 * Ulength},
		{EHIScontrol_x + Ulength * 61,EHIScontrol_y + 2 * Ulength},

	};
	ege_bezier(VOR2nums, VOR2ploypoints);
	ege_drawtext("VOR 2",EHIScontrol_x + Ulength * 53, EHIScontrol_y - 5 * Ulength);
	ege_drawtext("OFF",EHIScontrol_x + Ulength * 42, EHIScontrol_y + 5 * Ulength);

	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	setlinewidth(linewidth / 3);
	setcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	int VOR1nums_1 = 13;
	ege_point VOR1ploypoints_1[13] = {
		{EHIScontrol_x - Ulength * 58,EHIScontrol_y + 4 * Ulength},
		{EHIScontrol_x - Ulength * 57,EHIScontrol_y + 2 * Ulength},
		{EHIScontrol_x - Ulength * 55,EHIScontrol_y + 2 * Ulength},
		{EHIScontrol_x - Ulength * 54,EHIScontrol_y + 4 * Ulength},

		{EHIScontrol_x - Ulength * 54,EHIScontrol_y + 9 * Ulength},
		{EHIScontrol_x - Ulength * 54,EHIScontrol_y + 9 * Ulength},
		{EHIScontrol_x - Ulength * 54,EHIScontrol_y + 9 * Ulength},

		{EHIScontrol_x - Ulength * 55,EHIScontrol_y + 11 * Ulength},
		{EHIScontrol_x - Ulength * 57,EHIScontrol_y + 11 * Ulength},
		{EHIScontrol_x - Ulength * 58,EHIScontrol_y + 9 * Ulength},

		{EHIScontrol_x - Ulength * 58,EHIScontrol_y + 4 * Ulength},
		{EHIScontrol_x - Ulength * 58,EHIScontrol_y + 4 * Ulength},
		{EHIScontrol_x - Ulength * 58,EHIScontrol_y + 4 * Ulength},

	};
	ege_bezier(VOR1nums_1, VOR1ploypoints_1);

	floodfill(EHIScontrol_x - Ulength * 57, EHIScontrol_y + 7 * Ulength, EGEARGB(0XFF, 0X00, 0X00, 0X00));

	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	setlinewidth(linewidth / 3);
	setcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	int VOR2nums_1 = 13;
	ege_point VOR2ploypoints_1[13] = {
		{EHIScontrol_x + Ulength * 58,EHIScontrol_y + 4 * Ulength},
		{EHIScontrol_x + Ulength * 57,EHIScontrol_y + 2 * Ulength},
		{EHIScontrol_x + Ulength * 55,EHIScontrol_y + 2 * Ulength},
		{EHIScontrol_x + Ulength * 54,EHIScontrol_y + 4 * Ulength},

		{EHIScontrol_x + Ulength * 54,EHIScontrol_y + 9 * Ulength},
		{EHIScontrol_x + Ulength * 54,EHIScontrol_y + 9 * Ulength},
		{EHIScontrol_x + Ulength * 54,EHIScontrol_y + 9 * Ulength},

		{EHIScontrol_x + Ulength * 55,EHIScontrol_y + 11 * Ulength},
		{EHIScontrol_x + Ulength * 57,EHIScontrol_y + 11 * Ulength},
		{EHIScontrol_x + Ulength * 58,EHIScontrol_y + 9 * Ulength},

		{EHIScontrol_x + Ulength * 58,EHIScontrol_y + 4 * Ulength},
		{EHIScontrol_x + Ulength * 58,EHIScontrol_y + 4 * Ulength},
		{EHIScontrol_x + Ulength * 58,EHIScontrol_y + 4 * Ulength},

	};
	ege_bezier(VOR2nums_1, VOR2ploypoints_1);

	floodfill(EHIScontrol_x + Ulength * 57, EHIScontrol_y + 7 * Ulength, EGEARGB(0XFF, 0X00, 0X00, 0X00));

	setfillcolor(EGEARGB(0XFF, 0X40, 0X40, 0X40));
	ege_fillrect(EHIScontrol_x - Ulength * 64.8, EHIScontrol_y + 12.8 * Ulength, Ulength * 13, Ulength * 8);
	ege_fillrect(EHIScontrol_x + Ulength * 52.2, EHIScontrol_y + 12.8 * Ulength, Ulength * 13, Ulength * 8);

	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillrect(EHIScontrol_x - Ulength * 65.2, EHIScontrol_y + 13.2 * Ulength, Ulength * 13, Ulength * 8);
	ege_fillrect(EHIScontrol_x + Ulength * 51.8, EHIScontrol_y + 13.2 * Ulength, Ulength * 13, Ulength * 8);


	setfillcolor(EGEARGB(0XFF, 0X29, 0X2D, 0X2F));
	ege_fillrect(EHIScontrol_x - Ulength * 65, EHIScontrol_y + 13 * Ulength, Ulength * 13, Ulength * 8);
	ege_fillrect(EHIScontrol_x + Ulength * 52, EHIScontrol_y + 13 * Ulength, Ulength * 13, Ulength * 8);

	setcolor(EGEARGB(0XFF, 0X60, 0X60, 0X60));
	setfont(Ulength * 5, Ulength * 2.5, "Bahnschrift");
	xyprintf(EHIScontrol_x - Ulength * 63, EHIScontrol_y + 14 * Ulength, "INOP");
	xyprintf(EHIScontrol_x + Ulength * 54, EHIScontrol_y + 14 * Ulength,"INOP");


	if (VOR1 == 0) {
		setfillcolor(EGEARGB(0XFF, 0X4B, 0X4B, 0X49));

		for (int i = 0; i <= 60; i++) {
			ege_fillellipse(EHIScontrol_x - Ulength * (57 + 0.025 * i), EHIScontrol_y + (4 - i * 0.1) * Ulength, Ulength * (3 + i * 0.015), Ulength * (3 + i * 0.015));
		}
		setlinewidth(linewidth / 5);
		setcolor(EGEARGB(0X8F, 0X20, 0X20, 0X20));
		ege_ellipse(EHIScontrol_x - Ulength * (57 + 0.025 * 60), EHIScontrol_y + (4 - 60 * 0.1) * Ulength, Ulength* (3 + 60 * 0.015), Ulength* (3 + 60 * 0.015));
		ege_line(EHIScontrol_x - Ulength * (57 + 0.025 * 60), EHIScontrol_y + (0.8) * Ulength,
			EHIScontrol_x - Ulength * 57 , EHIScontrol_y + 6  * Ulength);
		ege_line(EHIScontrol_x - Ulength * (53 + 0.025 * 60), EHIScontrol_y + (0.5) * Ulength,
			EHIScontrol_x - Ulength * 54, EHIScontrol_y + 6 * Ulength);
	}
	if (VOR1 == 1) {
		setfillcolor(EGEARGB(0XFF, 0X4B, 0X4B, 0X49));
		ege_fillellipse(EHIScontrol_x - Ulength * 58, EHIScontrol_y + 4 * Ulength, Ulength * 4, Ulength * 4);

	}
	if (VOR1 == 2) {
		setfillcolor(EGEARGB(0XFF, 0X4B, 0X4B, 0X49));

		for (int i = 0; i <= 60; i++) {
			ege_fillellipse(EHIScontrol_x - Ulength * (57 + 0.025 * i), EHIScontrol_y + (5 + i * 0.1) * Ulength, Ulength * (3 + i * 0.015), Ulength * (3 + i * 0.015));
		}
		setlinewidth(linewidth / 5);
		setcolor(EGEARGB(0X8F, 0X20, 0X20, 0X20));
		ege_ellipse(EHIScontrol_x - Ulength * (57 + 0.025 * 60), EHIScontrol_y + (5 + 60 * 0.1) * Ulength, Ulength * (3 + 60 * 0.015), Ulength * (3 + 60 * 0.015));
		ege_line(EHIScontrol_x - Ulength * (57.3 + 0.025 * 60), EHIScontrol_y + 14.2 * Ulength,
			EHIScontrol_x - Ulength * 57, EHIScontrol_y + 6 * Ulength);
		ege_line(EHIScontrol_x - Ulength * (53 + 0.025 * 60), EHIScontrol_y + 13.5 * Ulength,
			EHIScontrol_x - Ulength * 54, EHIScontrol_y + 7 * Ulength);
	}



	if (VOR2 == 0) {
		setfillcolor(EGEARGB(0XFF, 0X4B, 0X4B, 0X49));

		for (int i = 0; i <= 60; i++) {
			ege_fillellipse(EHIScontrol_x + Ulength * (54 + 0.025 * i), EHIScontrol_y + (4 - i * 0.1) * Ulength, Ulength * (3 + i * 0.015), Ulength * (3 + i * 0.015));
		}
		setlinewidth(linewidth / 5);
		setcolor(EGEARGB(0X8F, 0X20, 0X20, 0X20));
		ege_ellipse(EHIScontrol_x + Ulength * (54 + 0.025 * 60), EHIScontrol_y + (4 - 60 * 0.1) * Ulength, Ulength * (3 + 60 * 0.015), Ulength * (3 + 60 * 0.015));
		ege_line(EHIScontrol_x + Ulength * (58 + 0.025 * 60), EHIScontrol_y + (0.8) * Ulength,
			EHIScontrol_x + Ulength * 57, EHIScontrol_y + 6 * Ulength);
		ege_line(EHIScontrol_x + Ulength * (53 + 0.025 * 60), EHIScontrol_y + (0.5) * Ulength,
			EHIScontrol_x + Ulength * 54, EHIScontrol_y + 6 * Ulength);
	}
	if (VOR2 == 1) {
		setfillcolor(EGEARGB(0XFF, 0X4B, 0X4B, 0X49));
		ege_fillellipse(EHIScontrol_x + Ulength * 54, EHIScontrol_y + 4 * Ulength, Ulength * 4, Ulength * 4);

	}

	if (VOR2 == 2) {
		setfillcolor(EGEARGB(0XFF, 0X4B, 0X4B, 0X49));

		for (int i = 0; i <= 60; i++) {
			ege_fillellipse(EHIScontrol_x + Ulength * (54 + 0.025 * i), EHIScontrol_y + (5 + i * 0.1) * Ulength, Ulength * (3 + i * 0.015), Ulength * (3 + i * 0.015));
		}
		setlinewidth(linewidth / 5);
		setcolor(EGEARGB(0X8F, 0X20, 0X20, 0X20));
		ege_ellipse(EHIScontrol_x + Ulength * (54 + 0.025 * 60), EHIScontrol_y + (5 + 60 * 0.1) * Ulength, Ulength * (3 + 60 * 0.015), Ulength * (3 + 60 * 0.015));
		ege_line(EHIScontrol_x + Ulength * (58.3 + 0.025 * 60), EHIScontrol_y + 13.5 * Ulength,
			EHIScontrol_x + Ulength * 57, EHIScontrol_y + 6 * Ulength);
		ege_line(EHIScontrol_x + Ulength * (54 + 0.025 * 60), EHIScontrol_y + 13.5 * Ulength,
			EHIScontrol_x + Ulength * 54, EHIScontrol_y + 7 * Ulength);
	}
	setcolor(EGEARGB(0XFF, 0X50, 0X50, 0X50));
	if (x> EHIScontrol_x - Ulength * 58 && x < EHIScontrol_x - Ulength * 54 && y>EHIScontrol_y + 3 * Ulength&&y<= EHIScontrol_y + 6 * Ulength) {
		ege_rectangle(EHIScontrol_x - Ulength * 58, EHIScontrol_y + 3 * Ulength, Ulength * 4, Ulength * 3);

		if (GetAsyncKeyState(0x04) & 0x0001 && VOR1>0) {
			VOR1--;

		}
	}
	if (x > EHIScontrol_x - Ulength * 58 && x < EHIScontrol_x - Ulength * 54 && y>EHIScontrol_y + 6 * Ulength && y <= EHIScontrol_y + 10 * Ulength) {
		ege_rectangle(EHIScontrol_x - Ulength * 58, EHIScontrol_y + 6 * Ulength, Ulength * 4, Ulength * 4);

		if (GetAsyncKeyState(0x04) & 0x0001 && VOR1 < 2) {
			VOR1++;

		}
	}



	if (x < EHIScontrol_x + Ulength * 58 && x > EHIScontrol_x + Ulength * 54 && y>EHIScontrol_y + 3 * Ulength && y <= EHIScontrol_y + 6 * Ulength) {
		ege_rectangle(EHIScontrol_x + Ulength * 54, EHIScontrol_y + 3 * Ulength, Ulength * 4, Ulength * 3);

		if (GetAsyncKeyState(0x04) & 0x0001 && VOR2 > 0) {
			VOR2--;

		}
	}
	if (x < EHIScontrol_x + Ulength * 58 && x > EHIScontrol_x + Ulength * 54 && y>EHIScontrol_y + 6 * Ulength && y <= EHIScontrol_y + 10 * Ulength) {
		ege_rectangle(EHIScontrol_x + Ulength * 54, EHIScontrol_y + 6 * Ulength, Ulength * 4, Ulength * 4);

		if (GetAsyncKeyState(0x04) & 0x0001 && VOR2 < 2) {
			VOR2++;

		}
	}

	
	
		if (x > EHIScontrol_x - 59 * Ulength && x< EHIScontrol_x - 48 * Ulength && y>EHIScontrol_y + 22 * Ulength && y < EHIScontrol_y + 33 * Ulength) {
			setcolor(EGEARGB(0XFF, 0X40, 0X40, 0X40));
			setlinewidth(linewidth / 2);
			ege_rectangle(EHIScontrol_x - 59 * Ulength, EHIScontrol_y + 22 * Ulength, Ulength * 11, Ulength * 11);
			if (GetAsyncKeyState(0x04) & 0x0001 ) {
				setlinewidth(linewidth);
				setcolor(EGEARGB(0XFF, 0X10, 0X10, 0X10));
				ege_rectangle(EHIScontrol_x - 59 * Ulength, EHIScontrol_y + 22 * Ulength, Ulength * 11, Ulength * 11);
				if (WXR == 0) {
					WXR = 1;
				}
				if (WXR == 1) {
					WXR = 0;
				}

			}
	}
		if (x > EHIScontrol_x - 41 * Ulength && x< EHIScontrol_x - 30 * Ulength && y>EHIScontrol_y + 22 * Ulength && y < EHIScontrol_y + 33 * Ulength) {
			setcolor(EGEARGB(0XFF, 0X40, 0X40, 0X40));
			setlinewidth(linewidth / 2);
			ege_rectangle(EHIScontrol_x - 41 * Ulength, EHIScontrol_y + 22 * Ulength, Ulength * 11, Ulength * 11);
			if (GetAsyncKeyState(0x04) & 0x0001) {
				setlinewidth(linewidth);
				setcolor(EGEARGB(0XFF, 0X10, 0X10, 0X10));
				ege_rectangle(EHIScontrol_x - 41 * Ulength, EHIScontrol_y + 22 * Ulength, Ulength * 11, Ulength * 11);
				if (STA == 0) {
					STA = 1;
				}
				if (STA == 1) {
					STA = 0;
				}

			}
		}
		if (x > EHIScontrol_x - 23 * Ulength && x< EHIScontrol_x - 12 * Ulength && y>EHIScontrol_y + 22 * Ulength && y < EHIScontrol_y + 33 * Ulength) {
			setcolor(EGEARGB(0XFF, 0X40, 0X40, 0X40));
			setlinewidth(linewidth / 2);
			ege_rectangle(EHIScontrol_x - 23 * Ulength, EHIScontrol_y + 22 * Ulength, Ulength * 11, Ulength * 11);
			if (GetAsyncKeyState(0x04) & 0x0001) {
				setlinewidth(linewidth);
				setcolor(EGEARGB(0XFF, 0X10, 0X10, 0X10));
				ege_rectangle(EHIScontrol_x - 23 * Ulength, EHIScontrol_y + 22 * Ulength, Ulength * 11, Ulength * 11);
				if (WPT == 0) {
					WPT = 1;
				}
				if (WPT == 1) {
					WPT = 0;
				}

			}
		}
		if (x > EHIScontrol_x - 5 * Ulength && x< EHIScontrol_x + 6 * Ulength && y>EHIScontrol_y + 22 * Ulength && y < EHIScontrol_y + 33 * Ulength) {
			setcolor(EGEARGB(0XFF, 0X40, 0X40, 0X40));
			setlinewidth(linewidth / 2);
			ege_rectangle(EHIScontrol_x - 5 * Ulength, EHIScontrol_y + 22 * Ulength, Ulength * 11, Ulength * 11);
			if (GetAsyncKeyState(0x04) & 0x0001) {
				setlinewidth(linewidth);
				setcolor(EGEARGB(0XFF, 0X10, 0X10, 0X10));
				ege_rectangle(EHIScontrol_x - 5 * Ulength, EHIScontrol_y + 22 * Ulength, Ulength * 11, Ulength * 11);
				if (ARPT == 0) {
					ARPT = 1;
				}
				if (ARPT == 1) {
					ARPT = 0;
				}

			}
		}
		if (x > EHIScontrol_x + 13 * Ulength && x< EHIScontrol_x + 24 * Ulength && y>EHIScontrol_y + 22 * Ulength && y < EHIScontrol_y + 33 * Ulength) {
			setcolor(EGEARGB(0XFF, 0X40, 0X40, 0X40));
			setlinewidth(linewidth / 2);
			ege_rectangle(EHIScontrol_x + 13 * Ulength, EHIScontrol_y + 22 * Ulength, Ulength * 11, Ulength * 11);
			if (GetAsyncKeyState(0x04) & 0x0001) {
				setlinewidth(linewidth);
				setcolor(EGEARGB(0XFF, 0X10, 0X10, 0X10));
				ege_rectangle(EHIScontrol_x + 13 * Ulength, EHIScontrol_y + 22 * Ulength, Ulength * 11, Ulength * 11);
				if (DATA == 0) {
					DATA = 1;
				}
				if (DATA == 1) {
					DATA = 0;
				}

			}
		}
		if (x > EHIScontrol_x + 31 * Ulength && x< EHIScontrol_x + 42 * Ulength && y>EHIScontrol_y + 22 * Ulength && y < EHIScontrol_y + 33 * Ulength) {
			setcolor(EGEARGB(0XFF, 0X40, 0X40, 0X40));
			setlinewidth(linewidth / 2);
			ege_rectangle(EHIScontrol_x + 31 * Ulength, EHIScontrol_y + 22 * Ulength, Ulength * 11, Ulength * 11);
			if (GetAsyncKeyState(0x04) & 0x0001) {
				setlinewidth(linewidth);
				setcolor(EGEARGB(0XFF, 0X10, 0X10, 0X10));
				ege_rectangle(EHIScontrol_x + 31 * Ulength, EHIScontrol_y + 22 * Ulength, Ulength * 11, Ulength * 11);
				if (POS == 0) {
					POS = 1;
				}
				if (POS == 1) {
					POS = 0;
				}

			}
		}
		if (x > EHIScontrol_x + 49 * Ulength && x< EHIScontrol_x + 61 * Ulength && y>EHIScontrol_y + 22 * Ulength && y < EHIScontrol_y + 33 * Ulength) {
			setcolor(EGEARGB(0XFF, 0X40, 0X40, 0X40));
			setlinewidth(linewidth / 2);
			ege_rectangle(EHIScontrol_x + 49 * Ulength, EHIScontrol_y + 22 * Ulength, Ulength * 11, Ulength * 11);
			if (GetAsyncKeyState(0x04) & 0x0001) {
				setlinewidth(linewidth);
				setcolor(EGEARGB(0XFF, 0X10, 0X10, 0X10));
				ege_rectangle(EHIScontrol_x + 49 * Ulength, EHIScontrol_y + 22 * Ulength, Ulength * 11, Ulength * 11);
				if (TERR == 0) {
					TERR = 1;
				}
				if (TERR == 1) {
					TERR = 0;
				}

			}
		}
		if (GetAsyncKeyState(0x04) & 0x8000) {
			if (knob_speed_is_down == 0) {
				knob_speed_is_down = 1;
				mousepos(&knob_mouse_x, &knob_mouse_y);
				knob_mouse_x_cur = knob_mouse_x;
				knob_mouse_y_cur = knob_mouse_y;
			}
			if (knob_speed_is_down == 1) {
				if ((knob_mouse_x_cur >= EHIScontrol_x - 45 * Ulength - Topknob_R2)
					&& (knob_mouse_x_cur <= EHIScontrol_x - 45 * Ulength + Topknob_R2)
					&& (knob_mouse_y_cur >= EHIScontrol_y - 15 * Ulength - Topknob_R2)
					&& (knob_mouse_y_cur <= EHIScontrol_y - 15 * Ulength + Topknob_R2)) {


					mousepos(&knob_mouse_x, &knob_mouse_y);
					if (knob_mouse_y < knob_mouse_y_cur) {
						LeftTopAngle_1 += (knob_mouse_y - knob_mouse_y_cur) / 70;

					}
					else {
						LeftTopAngle_1 += (knob_mouse_y - knob_mouse_y_cur) / 70;

					}
				}
			}
			
		}
		else if (knob_speed_is_down == 1) {
			knob_speed_is_down = 0;
		}
		
		
		if (GetAsyncKeyState(0x04) & 0x8000) {
			if (knob_speed_is_down == 0) {
				knob_speed_is_down = 1;
				mousepos(&knob_mouse_x, &knob_mouse_y);
				knob_mouse_x_cur = knob_mouse_x;
				knob_mouse_y_cur = knob_mouse_y;
			}
			if (knob_speed_is_down == 1) {
				if ((knob_mouse_x_cur >= EHIScontrol_x + 45 * Ulength - Topknob_R2)
					&& (knob_mouse_x_cur <= EHIScontrol_x + 45 * Ulength + Topknob_R2)
					&& (knob_mouse_y_cur >= EHIScontrol_y - 15 * Ulength - Topknob_R2)
					&& (knob_mouse_y_cur <= EHIScontrol_y - 15 * Ulength + Topknob_R2)) {


					mousepos(&knob_mouse_x, &knob_mouse_y);
					if (knob_mouse_y < knob_mouse_y_cur) {
						rightTopAngle_1 += (knob_mouse_y - knob_mouse_y_cur) / 70;

					}
					else {
						rightTopAngle_1 += (knob_mouse_y - knob_mouse_y_cur) / 70;

					}
				}
			}

		}
		else if (knob_speed_is_down == 1) {
			knob_speed_is_down = 0;
		}

		

}