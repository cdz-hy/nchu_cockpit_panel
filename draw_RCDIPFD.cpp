#include<graphics.h>
#include <stdio.h>
#include <math.h>


double calPointery(double verticalRate, double Ulength);
extern double verticalRate;
void draw_Part_RCDI(double centerx,double centery,double side) {

	double Ulength = side / 96;
	double big_width = Ulength / 3;
	double small_width = Ulength / 5;
	double Pointer_y;

	//表盘
	int RCDI_frame_pointsNum = 10;
	ege_point RCDI_frame_ployPoint[10]{
		{centerx - Ulength * 4 , centery - Ulength * 23 },
		{centerx  , centery - Ulength * 23},
		{centerx + Ulength * 4 , centery - Ulength * 12.5},
		{centerx + Ulength * 4 , centery + Ulength * 12.5},
		{centerx  , centery + Ulength * 23},
		{centerx - Ulength * 4 , centery + Ulength * 23},
		{centerx - Ulength * 4 , centery + Ulength * 7.5},
		{centerx - Ulength * 2 , centery + Ulength * 6},
		{centerx - Ulength * 2 , centery - Ulength * 6},
		{centerx - Ulength * 4 , centery - Ulength * 7.5},
	};
	setfillcolor(EGEARGB(0XFF,0X11,0X12,0X11));
	ege_fillpoly(RCDI_frame_pointsNum, RCDI_frame_ployPoint);

	//刻度
	setcolor(EGEARGB(0XFF, 0X75, 0X75, 0X75));

	setlinewidth(big_width);
	ege_line(centerx - 2 * Ulength, centery, centerx - 1 * Ulength, centery);

	ege_line(centerx - 2 * Ulength, centery - 9 * Ulength, centerx - 1 * Ulength, centery - 9 * Ulength);
	ege_line(centerx - 2 * Ulength, centery + 9 * Ulength, centerx - 1 * Ulength, centery + 9 * Ulength);
	ege_line(centerx - 2 * Ulength, centery - 17 * Ulength, centerx - 1 * Ulength, centery - 17 * Ulength);
	ege_line(centerx - 2 * Ulength, centery + 17 * Ulength, centerx - 1 * Ulength, centery + 17 * Ulength);
	ege_line(centerx - 2 * Ulength, centery - 21 * Ulength, centerx - 1 * Ulength, centery - 21 * Ulength);
	ege_line(centerx - 2 * Ulength, centery + 21 * Ulength, centerx - 1 * Ulength, centery + 21 * Ulength);

	setlinewidth(small_width);
	ege_line(centerx - 2 * Ulength, centery - 4.5 * Ulength, centerx - 1 * Ulength, centery - 4.5 * Ulength);
	ege_line(centerx - 2 * Ulength, centery + 4.5 * Ulength, centerx - 1 * Ulength, centery + 4.5 * Ulength);
	ege_line(centerx - 2 * Ulength, centery - 19 * Ulength, centerx - 1 * Ulength, centery - 19 * Ulength);
	ege_line(centerx - 2 * Ulength, centery + 19 * Ulength, centerx - 1 * Ulength, centery + 19 * Ulength);



	//绘制数字
	setbkmode(TRANSPARENT);
	setcolor(EGEARGB(0XFF, 0X6D,0X6E,0X6D));
	setfont(25,3, "Calibri");
	ege_drawtext("6",centerx - 3.8 * Ulength, centery - 22.1 * Ulength);
	ege_drawtext("6",centerx - 3.8 * Ulength, centery + 19.8 * Ulength);
	ege_drawtext("2",centerx - 3.8 * Ulength, centery - 18.4 * Ulength);
	ege_drawtext("2",centerx - 3.8 * Ulength, centery + 15.8 * Ulength);
	ege_drawtext("1",centerx - 3.8 * Ulength, centery - 10.2 * Ulength);
	ege_drawtext("1",centerx - 3.8 * Ulength, centery + 7.8 * Ulength);

	
	setfont(30, 3, "Calibri");
	if (verticalRate >= 400 && verticalRate <= 9999) 
	{
		char num[64];
		sprintf_s(num, "%.0f", verticalRate);
		ege_drawtext(num, centerx - 4.5 * Ulength, centery - 26 * Ulength);

	}
	else if (verticalRate > 9999)
	{
		ege_drawtext("9999", centerx - 4.5 * Ulength, centery - 26 * Ulength);
	}
	else if (verticalRate <= -400 && verticalRate >= -9999)
	{
		char num[64];
		sprintf_s(num, "%.0f", -verticalRate);
		ege_drawtext(num, centerx - 4.5 * Ulength, centery + 23 * Ulength);
	}
	else if (verticalRate < -9999) 
	{
		ege_drawtext("9999", centerx - 4.5 * Ulength, centery + 23 * Ulength);
	}



	//绘制指针
	Pointer_y = calPointery(verticalRate/1000,Ulength);
	setcolor(EGEARGB(0XFF, 0X75, 0X75, 0X75));
	setlinewidth(big_width);
	ege_line(centerx + Ulength * 4, centery, centerx - Ulength * 2, centery - Pointer_y);

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
void draw_PFD_top(double top_x, double top_y, double side) {//显示屏
	double Ulength = side / 96;
	double linewidth = Ulength / 3;

	setfillcolor(EGEARGB(0XFF, 0X11, 0X11, 0X11));
	ege_fillrect(top_x - Ulength * 27, top_y - Ulength * 3, Ulength * 54, Ulength * 6);
	setcolor(EGEARGB(0XFF, 0X75, 0X75, 0X75));
	setlinewidth(linewidth);
	ege_line(top_x - Ulength * 8.5, top_y - Ulength * 3, top_x - Ulength * 8.5, top_y + Ulength * 3);
	ege_line(top_x + Ulength * 8.5, top_y - Ulength * 3, top_x + Ulength * 8.5, top_y + Ulength * 3);
}
void draw_1(double x, double y, double side) {//圆弧
	double Ulength = side / 96;
	double linewidth = Ulength / 3;

	setcolor(EGEARGB(0XFF, 0X75, 0X75, 0X75));
	setlinewidth(linewidth);
	ege_arc(x - 6 * Ulength, y - 6 * Ulength, 12 * Ulength, 12 * Ulength, 90, -225);

	for(int i = 90 ; i <= 270 ; i+=90)
	{
		ege_line(x - 6 * Ulength * cos(i * PI / 180), y - 6 * Ulength * sin(i * PI / 180), x - 5 * Ulength * cos(i * PI / 180), y - 5 * Ulength * sin(i * PI / 180));
	}
	for (int i = 45; i <= 135; i += 90)
	{
		ege_line(x - 6 * Ulength * cos(i * PI / 180), y - 6 * Ulength * sin(i * PI / 180), x - 5 * Ulength * cos(i * PI / 180), y - 5 * Ulength * sin(i * PI / 180));
	}
}