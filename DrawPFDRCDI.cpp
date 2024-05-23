#include<graphics.h>
#include <stdio.h>
double calPointery(double verticalRate, double Ulength);
extern double verticalRate;
void draw_PFD_RCDI(double RCDI_x,double RCDI_y,double RCDI_side) {

	double Ulength = RCDI_side / 96;
	double big_width = Ulength / 3;
	double small_width = Ulength / 5;
	double Pointer_y;

	setfont(0,0,"Calibri");
	
	//表盘
	int RCDI_frame_pointsNum = 10;
	ege_point RCDI_frame_ployPoint[10]{
		{RCDI_x - Ulength * 4 , RCDI_y - Ulength * 23 },
		{RCDI_x  , RCDI_y - Ulength * 23},
		{RCDI_x + Ulength * 4 , RCDI_y - Ulength * 12.5},
		{RCDI_x + Ulength * 4 , RCDI_y + Ulength * 12.5},
		{RCDI_x  , RCDI_y + Ulength * 23},
		{RCDI_x - Ulength * 4 , RCDI_y + Ulength * 23},
		{RCDI_x - Ulength * 4 , RCDI_y + Ulength * 7.5},
		{RCDI_x - Ulength * 2 , RCDI_y + Ulength * 6},
		{RCDI_x - Ulength * 2 , RCDI_y - Ulength * 6},
		{RCDI_x - Ulength * 4 , RCDI_y - Ulength * 7.5},
	};
	setfillcolor(EGEARGB(0XFF,0X11,0X12,0X11));
	ege_fillpoly(RCDI_frame_pointsNum, RCDI_frame_ployPoint);

	//刻度
	setcolor(EGEARGB(0XFF, 0X75, 0X75, 0X75));

	setlinewidth(big_width);
	ege_line(RCDI_x - 2 * Ulength, RCDI_y, RCDI_x - 1 * Ulength, RCDI_y);

	ege_line(RCDI_x - 2 * Ulength, RCDI_y - 9 * Ulength, RCDI_x - 1 * Ulength, RCDI_y - 9 * Ulength);
	ege_line(RCDI_x - 2 * Ulength, RCDI_y + 9 * Ulength, RCDI_x - 1 * Ulength, RCDI_y + 9 * Ulength);
	ege_line(RCDI_x - 2 * Ulength, RCDI_y - 17 * Ulength, RCDI_x - 1 * Ulength, RCDI_y - 17 * Ulength);
	ege_line(RCDI_x - 2 * Ulength, RCDI_y + 17 * Ulength, RCDI_x - 1 * Ulength, RCDI_y + 17 * Ulength);
	ege_line(RCDI_x - 2 * Ulength, RCDI_y - 21 * Ulength, RCDI_x - 1 * Ulength, RCDI_y - 21 * Ulength);
	ege_line(RCDI_x - 2 * Ulength, RCDI_y + 21 * Ulength, RCDI_x - 1 * Ulength, RCDI_y + 21 * Ulength);

	setlinewidth(small_width);
	ege_line(RCDI_x - 2 * Ulength, RCDI_y - 4.5 * Ulength, RCDI_x - 1 * Ulength, RCDI_y - 4.5 * Ulength);
	ege_line(RCDI_x - 2 * Ulength, RCDI_y + 4.5 * Ulength, RCDI_x - 1 * Ulength, RCDI_y + 4.5 * Ulength);
	ege_line(RCDI_x - 2 * Ulength, RCDI_y - 19 * Ulength, RCDI_x - 1 * Ulength, RCDI_y - 19 * Ulength);
	ege_line(RCDI_x - 2 * Ulength, RCDI_y + 19 * Ulength, RCDI_x - 1 * Ulength, RCDI_y + 19 * Ulength);



	//绘制数字
	setbkmode(TRANSPARENT);
	setcolor(EGEARGB(0XFF, 0X6D,0X6E,0X6D));
	setfont(25,3, "Calibri");
	ege_drawtext("6",RCDI_x - 3.8 * Ulength, RCDI_y - 22.1 * Ulength);
	ege_drawtext("6",RCDI_x - 3.8 * Ulength, RCDI_y + 19.8 * Ulength);
	ege_drawtext("2",RCDI_x - 3.8 * Ulength, RCDI_y - 18.4 * Ulength);
	ege_drawtext("2",RCDI_x - 3.8 * Ulength, RCDI_y + 15.8 * Ulength);
	ege_drawtext("1",RCDI_x - 3.8 * Ulength, RCDI_y - 10.2 * Ulength);
	ege_drawtext("1",RCDI_x - 3.8 * Ulength, RCDI_y + 7.8 * Ulength);

	
	setfont(30, 3, "Calibri");
	if (verticalRate >= 400 && verticalRate <= 9999) 
	{
		char num[64];
		sprintf_s(num, "%.0f", verticalRate);
		ege_drawtext(num, RCDI_x - 4.5 * Ulength, RCDI_y - 26 * Ulength);

	}
	else if (verticalRate > 9999)
	{
		ege_drawtext("9999", RCDI_x - 4.5 * Ulength, RCDI_y - 26 * Ulength);
	}
	else if (verticalRate <= -400 && verticalRate >= -9999)
	{
		char num[64];
		sprintf_s(num, "%.0f", -verticalRate);
		ege_drawtext(num, RCDI_x - 4.5 * Ulength, RCDI_y + 23 * Ulength);
	}
	else if (verticalRate < -9999) 
	{
		ege_drawtext("9999", RCDI_x - 4.5 * Ulength, RCDI_y + 23 * Ulength);
	}



	//绘制指针
	Pointer_y = calPointery(verticalRate/1000,Ulength);
	setcolor(EGEARGB(0XFF, 0X75, 0X75, 0X75));
	setlinewidth(big_width);
	ege_line(RCDI_x + Ulength * 4, RCDI_y, RCDI_x - Ulength * 2, RCDI_y - Pointer_y);

}
double calPointery(double verticalRates,double Ulength) {
	if (verticalRates >= 0 && verticalRates <= 1) {
		return 9 * Ulength * verticalRates;
	}
	else if (verticalRates > 1 && verticalRates <= 2) {
		verticalRates = verticalRates - 1;
		return 9 * Ulength + verticalRates * 8 * Ulength;
	}
	else if (verticalRates > 2 && verticalRates <= 6) {
		verticalRates = verticalRates - 2;
		return 17 * Ulength + verticalRates * Ulength;
	}
	else if (verticalRates > 6) {
		return 21 * Ulength;
	}
	else if(verticalRates<0 && verticalRates >= -1){
		return 9 * Ulength * verticalRates;

	}
	else if (verticalRates < -1 && verticalRates >= -2) {
		verticalRates = verticalRates + 1;
		return - 9 * Ulength + verticalRates * 8 * Ulength;
	}
	else if (verticalRates < -2 && verticalRates >= -6) {
		verticalRates = verticalRates + 2;
		return - 17 * Ulength + verticalRates * Ulength;
	}
	else {
		return -21 * Ulength;
	}

}
//void draw_PFD_frame(double frame_x,double frame_y , double frame_side) {
//	double Ulength = frame_side / 113;
//
//
//
//	int num_frame_1 = 25;
//	ege_point frame_1_ploypoints[25]{
//		{frame_x - 49.5 * Ulength , frame_y - },
//
//
//
//
//
//
//
//
//
//	};
//}
