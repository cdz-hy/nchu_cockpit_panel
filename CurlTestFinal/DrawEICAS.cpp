
#include<graphics.h>
#include<math.h>
#include<stdio.h>

#include "DrawFrame.h"

extern double Oangle_1;
extern double Oangle_2;
extern double Oangle_3;
extern double Oangle_4;
extern double fanSpeed;
extern double fanSpeed_1 ;
extern double gastemp ;
extern double gastemp_1 ;
extern double FuelFlowSpeed;
extern double FuelFlowSpeed_1;
extern double Fuelrest_1;
extern double Fuelrest_2;
extern double Fuelrest_3;
extern double Fuelrest_total;
extern int TAT;


extern double UPPERangle;

void draw_EICAS(double Oilcenterx, double Oilcentery, double side) {
	
	setfillcolor(BLACK);
	ege_fillrect(Oilcenterx - side / 1.9, Oilcentery - side / 1.9, 1.1 * side, 1.1 * side);
	
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	
	double Ulength = side / 84;
	double R = Ulength * 7.5;
	double linewidth_1 = Ulength / 3;
	double linelength = Ulength * 1.5;
	
	
	setlinewidth(linewidth_1 );
	setcolor(EGEARGB(0XFF, 0XE0, 0XE0, 0XE0));
	
	
	setfillcolor(EGEARGB(0XFF, 0X3A, 0X31, 0X38));
	
	ege_rectangle(Oilcenterx - Ulength * 29, Oilcentery - Ulength * 32.5, Ulength * 11.5, Ulength * 4);
	ege_rectangle(Oilcenterx - Ulength * 6, Oilcentery - Ulength * 32.5, Ulength * 11.5, Ulength * 4);
	setfont(Ulength * 5, 0, "Calibri");
	LOGFONTA font;
	getfont(&font);
	font.lfHeight = Ulength * 5;
	font.lfWeight = Ulength * 50;
	font.lfQuality = ANTIALIASED_QUALITY;
	setfont(&font);
	char num[64];//左上上
	sprintf_s(num, "%.1f", fanSpeed);
	ege_drawtext(num ,Oilcenterx - Ulength * 23.5, Oilcentery - Ulength * 30);
	
	
	
	char nums[64];//左上上
	sprintf_s(nums, "%.1f", fanSpeed_1);
	
	
	ege_drawtext(nums ,Oilcenterx - Ulength * 0.5, Oilcentery - Ulength * 30);
	
	if (fanSpeed_1 <= 101.5 && fanSpeed_1 >= 0) {
		Oangle_3 = fanSpeed_1 / 10 * 19;
	}
	else if (fanSpeed_1 > 101.5) {
		Oangle_3 = 101.5 / 10 * 19;
	}
	else {
		Oangle_3 = 0;
	}
	
	
	
	if (fanSpeed <= 101.5 && fanSpeed >= 0) {
		Oangle_1 = fanSpeed / 10 * 19;
	}
	else if (fanSpeed > 101.5) {
		Oangle_1 = 101.5 / 10 * 19;
	}
	else {
		Oangle_1 = 0;
	}
	
	if (gastemp < 999) {
		char num_1[64];//左上中
		sprintf_s(num_1, "%.0f", gastemp);
		ege_drawtext(num_1, Oilcenterx - Ulength * 25, Oilcentery - Ulength * 15);
		
	}
	else 
	{
		char num_1[64];//左上中
		ege_drawtext("999", Oilcenterx - Ulength * 25, Oilcentery - Ulength * 15);
		
	}
	
	if (gastemp_1 < 999) {
		char nums_1[64];//左上中
		sprintf_s(nums_1, "%.0f", gastemp_1);
		
		ege_drawtext(nums_1, Oilcenterx - Ulength * 2, Oilcentery - Ulength * 15);
	}
	else
	{
		char nums_1[64];//左上中
		
		ege_drawtext("999", Oilcenterx - Ulength * 2, Oilcentery - Ulength * 15);
	}
	if (gastemp <= 950 && gastemp >= 0) {
		Oangle_2 = gastemp * 198 / 950;
	}
	else if (gastemp > 950) {
		Oangle_2 = 198;
	}
	else {
		Oangle_2 = 0;
	}
	if (gastemp_1 <= 950 && gastemp_1 >= 0) {
		Oangle_4 = gastemp_1 * 198 / 950;
	}
	else if (gastemp_1 > 950) {
		Oangle_4 = 198;
	}
	else {
		Oangle_4 = 0;
	}
	
	
	
	
	setfont(Ulength * 4, 0, "Calibri");
	getfont(&font);
	font.lfHeight = Ulength * 4.5;
	font.lfWeight = Ulength * 40;
	font.lfQuality = ANTIALIASED_QUALITY;
	setfont(&font);
	if(FuelFlowSpeed<10){
		char num_2[64];//左上下左
		sprintf_s(num_2, "%.2f", FuelFlowSpeed);
		ege_drawtext(num_2, Oilcenterx - Ulength * 26.5, Oilcentery + Ulength * 7.2);
	}
	else if(FuelFlowSpeed>=10){
		char num_2[64];
		sprintf_s(num_2, "%.1f", FuelFlowSpeed);
		ege_drawtext(num_2, Oilcenterx - Ulength * 26.5, Oilcentery + Ulength * 7.2);	
	}
	if(FuelFlowSpeed_1<10){
		char num_7[64];//左上下右
		sprintf_s(num_7, "%.2f", FuelFlowSpeed_1);
		ege_drawtext(num_7, Oilcenterx - Ulength * 3.5, Oilcentery + Ulength * 7.2);
	}
	else if(FuelFlowSpeed_1>=10){
		char num_7[64];//左上下右
		sprintf_s(num_7, "%.1f", FuelFlowSpeed_1);
		ege_drawtext(num_7, Oilcenterx - Ulength * 3.5, Oilcentery + Ulength * 7.2);
	}
	
	char num12[64];//最上TAT
	sprintf_s(num12, "%d", TAT);
	ege_drawtext(num12 ,Oilcenterx - Ulength * 23.5, Oilcentery - Ulength * 38);
	
	ege_drawtext("C" ,Oilcenterx - Ulength * 20.5, Oilcentery - Ulength * 38);
	if (fanSpeed > 101) {
		setfillcolor(EGEARGB(0X9F, 0X7F, 0X06, 0X03));
	}
	else {
		setfillcolor(EGEARGB(0XFF, 0X3A, 0X31, 0X38));
		
	}
	
	ege_fillpie(Oilcenterx - Ulength * 29 - R, Oilcentery - Ulength * 27.5 - R, 2 * R, 2 * R, 0, Oangle_1);
	ege_fillpie(Oilcenterx - Ulength * 6 - R, Oilcentery - Ulength * 27.5 - R, 2 * R, 2 * R, 0, Oangle_1);
	
	if (gastemp >= 915 && gastemp < 950) {
		setfillcolor(EGEARGB(0X9F, 0X89, 0X4A, 0X03));
	}
	else if (gastemp >= 950) {
		setfillcolor(EGEARGB(0X9F, 0X7F, 0X06, 0X03));
	}
	else {
		setfillcolor(EGEARGB(0XFF, 0X3A, 0X31, 0X38));;
	}
	
	ege_fillpie(Oilcenterx - Ulength * 29 - R, Oilcentery - Ulength * 12.5 - R, 2 * R, 2 * R, 0, Oangle_2);
	ege_fillpie(Oilcenterx - Ulength * 6 - R, Oilcentery - Ulength * 12.5 - R, 2 * R, 2 * R, 0, Oangle_2);
	
	
	
	ege_line(Oilcenterx - Ulength * 29 - R * cos((Oangle_1 - 180) * PI / 180), Oilcentery - Ulength * 27.5 - R * sin((Oangle_1 - 180) * PI / 180),
		Oilcenterx - Ulength * 29, Oilcentery - Ulength * 27.5);
	ege_line(Oilcenterx - Ulength * 6 - R * cos((Oangle_1 - 180) * PI / 180), Oilcentery - Ulength * 27.5 - R * sin((Oangle_1 - 180) * PI / 180),
		Oilcenterx - Ulength * 6, Oilcentery - Ulength * 27.5);
	
	ege_line(Oilcenterx - Ulength * 29 - R * cos((Oangle_2 - 180) * PI / 180), Oilcentery - Ulength * 12.5 - R * sin((Oangle_2 - 180) * PI / 180),
		Oilcenterx - Ulength * 29, Oilcentery - Ulength * 12.5);
	ege_line(Oilcenterx - Ulength * 6 - R * cos((Oangle_2 - 180) * PI / 180), Oilcentery - Ulength * 12.5 - R * sin((Oangle_2 - 180) * PI / 180),
		Oilcenterx - Ulength * 6, Oilcentery - Ulength * 12.5);
	
	
	
	ege_arc(Oilcenterx - Ulength * 29 - R, Oilcentery - Ulength * 27.5 - R, 2*R, 2*R, 0 , 198);
	ege_arc(Oilcenterx - Ulength * 6 - R, Oilcentery - Ulength * 27.5 - R, 2*R, 2*R, 0, 198);
	ege_arc(Oilcenterx - Ulength * 29 - R, Oilcentery - Ulength * 12.5 - R, 2*R, 2*R, 0, 198);
	ege_arc(Oilcenterx - Ulength * 6 - R, Oilcentery - Ulength * 12.5 - R, 2*R, 2*R, 0, 198);
	
	
	
	
	
	
	
	for (int i = 10; i >= -180; i -= 19) {
		ege_line(Oilcenterx - Ulength * 29 - R * cos(i * PI / 180) , Oilcentery - Ulength * 27.5  - R * sin(i * PI / 180), 
			Oilcenterx - Ulength * 29  - (R - linelength) * cos(i * PI / 180), Oilcentery - Ulength * 27.5  - (R - linelength) * sin(i * PI / 180));
	}
	for (int i = 10; i >= -180; i -= 19) {
		ege_line(Oilcenterx - Ulength * 6 - R * cos(i * PI / 180), Oilcentery - Ulength * 27.5 - R * sin(i * PI / 180),
			Oilcenterx - Ulength * 6 - (R - linelength) * cos(i * PI / 180), Oilcentery - Ulength * 27.5 - (R - linelength) * sin(i * PI / 180));
	}
	
	
	
	ege_rectangle(Oilcenterx - Ulength * 29, Oilcentery - Ulength * 17.5, Ulength * 7, Ulength * 4);
	ege_rectangle(Oilcenterx - Ulength * 6, Oilcentery - Ulength * 17.5, Ulength * 7, Ulength * 4);
	
	ege_rectangle(Oilcenterx - Ulength * 31, Oilcentery + Ulength * 5.5, Ulength * 8.5, Ulength * 3);
	ege_rectangle(Oilcenterx - Ulength * 8, Oilcentery + Ulength * 5.5, Ulength * 8.5, Ulength * 3);
	
	setcolor(EGEARGB(0XFF, 0X3A, 0X31, 0X38));
	setlinewidth(linewidth_1 * 1.5);
	ege_rectangle(Oilcenterx + Ulength * 8.5, Oilcentery - Ulength * 36, Ulength * 15, Ulength * 5);
	ege_rectangle(Oilcenterx + Ulength * 8.5, Oilcentery - Ulength * 31, Ulength * 15, Ulength * 5);
	ege_rectangle(Oilcenterx + Ulength * 8.5, Oilcentery - Ulength * 26, Ulength * 15, Ulength * 5);
	
	ege_rectangle(Oilcenterx + Ulength * 25.5, Oilcentery - Ulength * 36, Ulength * 15, Ulength * 5);
	ege_rectangle(Oilcenterx + Ulength * 25.5, Oilcentery - Ulength * 31, Ulength * 15, Ulength * 5);
	ege_rectangle(Oilcenterx + Ulength * 25.5, Oilcentery - Ulength * 26, Ulength * 15, Ulength * 5);
	
	setfillcolor(EGEARGB(0XFF, 0X2A, 0X21, 0X28));
	ege_fillrect(Oilcenterx + Ulength * 12.5, Oilcentery - Ulength * 38.2, Ulength * 6.5, Ulength * 2.2);
	ege_fillrect(Oilcenterx + Ulength * 29.5, Oilcentery - Ulength * 38.2, Ulength * 6.5, Ulength * 2.2);
	
	setcolor(EGEARGB(0XFF, 0X17, 0XAF, 0XAB));
	setfont(Ulength * 2.8, 0, "Calibri");
	ege_drawtext("ENG 1", Oilcenterx + Ulength * 16, Oilcentery - Ulength * 36.8);
	ege_drawtext("ENG 2", Oilcenterx + Ulength * 33, Oilcentery - Ulength * 36.8);
	ege_drawtext("TAT", Oilcenterx - Ulength * 34.5, Oilcentery - Ulength * 37.8);
	
	int pointnum = 22;
	ege_point ploypoint[22] = {
		{Oilcenterx + Ulength * 11 , Oilcentery + Ulength * 28.5},
		{Oilcenterx + Ulength * 11 , Oilcentery + Ulength * 28.5},
		{Oilcenterx + Ulength * 11 , Oilcentery + Ulength * 28.5},
		{Oilcenterx + Ulength * 9 , Oilcentery + Ulength * 28.5},
		
		
		{Oilcenterx + Ulength * 8.5 , Oilcentery + Ulength * 28.5},
		{Oilcenterx + Ulength * 7.5 , Oilcentery + Ulength * 29},
		{Oilcenterx + Ulength * 7.5 , Oilcentery + Ulength * 30},
		
		
		{Oilcenterx + Ulength * 7.5 , Oilcentery + Ulength * 35.5},
		{Oilcenterx + Ulength * 7.5 , Oilcentery + Ulength * 36.5},
		{Oilcenterx + Ulength * 8.5 , Oilcentery + Ulength * 37},
		
		{Oilcenterx + Ulength * 9 , Oilcentery + Ulength * 37},
		{Oilcenterx + Ulength * 39 , Oilcentery + Ulength * 37},
		{Oilcenterx + Ulength * 39 , Oilcentery + Ulength * 37},
		
		{Oilcenterx + Ulength * 40.5 , Oilcentery + Ulength * 37},
		{Oilcenterx + Ulength * 40.5 , Oilcentery + Ulength * 36.5},
		{Oilcenterx + Ulength * 40.5 , Oilcentery + Ulength * 35.5},
		
		{Oilcenterx + Ulength * 40.5 , Oilcentery + Ulength * 30},
		{Oilcenterx + Ulength * 40.5 , Oilcentery + Ulength * 29},
		{Oilcenterx + Ulength * 39.5 , Oilcentery + Ulength * 28.5},
		
		{Oilcenterx + Ulength * 39 , Oilcentery + Ulength * 28.5},
		{Oilcenterx + Ulength * 37 , Oilcentery + Ulength * 28.5},
		{Oilcenterx + Ulength * 37 , Oilcentery + Ulength * 28.5},
		
		
		
	};
	setcolor(EGEARGB(0XFF, 0X17, 0XAF, 0XBB));
	setlinewidth(linewidth_1);
	ege_line(Oilcenterx + Ulength * 24, Oilcentery + Ulength * 29, Oilcenterx + Ulength * 22, Oilcentery + Ulength * 29);
	ege_bezier(pointnum, ploypoint);
	setfont(Ulength * 3.5, 0, "Calibri");
	LOGFONTA f;
	getfont(&f);
	f.lfHeight = Ulength * 3.5;
	f.lfWeight = Ulength * 60;
	f.lfWidth = Ulength / 6 * 8;
	f.lfQuality = ANTIALIASED_QUALITY;
	setfont(&f);
	xyprintf( Oilcenterx + Ulength * 16.5, Oilcentery + Ulength * 29, "FUEL QTY");
	xyprintf(Oilcenterx + Ulength * 30.5, Oilcentery + Ulength * 29, "LBS X 1000");
	xyprintf(Oilcenterx + Ulength * 14, Oilcentery + Ulength * 40, "TOTAL");
	
	
	xyprintf(Oilcenterx - Ulength * 17, Oilcentery - Ulength * 22, "N1");
	xyprintf(Oilcenterx - Ulength * 17, Oilcentery - Ulength * 7, "EGT");
	xyprintf(Oilcenterx - Ulength * 17, Oilcentery + Ulength * 7, "FF");
	
	
	
	LOGFONTA f1;
	getfont(&f1);
	f1.lfHeight = Ulength * 5.5;
	f1.lfWeight = Ulength * 40;
	f1.lfWidth = 6;
	f1.lfQuality = ANTIALIASED_QUALITY;
	setfont(&f1);
	setcolor(EGEARGB(0XFF, 0XE0, 0XE0, 0XE0));
	char num_3[64];//      1
	sprintf_s(num_3, "%.2f", Fuelrest_1);
	ege_drawtext(num_3, Oilcenterx + Ulength * 13.5, Oilcentery + Ulength * 33);
	
	char num_4[64];//      2
	sprintf_s(num_4, "%.2f", Fuelrest_2);
	ege_drawtext(num_4, Oilcenterx + Ulength * 23, Oilcentery + Ulength * 33);
	
	char num_5[64];//      3
	sprintf_s(num_5, "%.2f", Fuelrest_3);
	ege_drawtext(num_5, Oilcenterx + Ulength * 33, Oilcentery + Ulength * 33);
	
	setfont(Ulength * 6.5, 0, "Calibri");
	char num_6[64];//      
	sprintf_s(num_6, "%.1f", Fuelrest_total);
	ege_drawtext(num_6, Oilcenterx + Ulength * 22.5, Oilcentery + Ulength * 39.5);
	
	
	setcolor(EGEARGB(0XFF, 0X8F, 0X16, 0X13));
	ege_line(Oilcenterx - Ulength * 28.5 - R, Oilcentery - Ulength * 21.75 - R, Oilcenterx - Ulength * 30.5 - R, Oilcentery - Ulength * 22.75 - R);
	
	ege_line(Oilcenterx - Ulength * 5.5 - R, Oilcentery - Ulength * 21.75 - R, Oilcenterx - Ulength * 7.5 - R, Oilcentery - Ulength * 22.75 - R);
	
	ege_line(Oilcenterx - Ulength * 28.5 - R, Oilcentery - Ulength * 7 - R, Oilcenterx - Ulength * 30.5 - R, Oilcentery - Ulength * 7.75 - R);
	
	ege_line(Oilcenterx - Ulength * 5.5 - R, Oilcentery - Ulength * 7 - R, Oilcenterx - Ulength * 7.5 - R, Oilcentery - Ulength * 7.75 - R);
	
	setcolor(EGEARGB(0XFF, 0X99, 0X5A, 0X13));
	
	ege_line(Oilcenterx - Ulength * 29 - R, Oilcentery - Ulength * 6.4 - R, Oilcenterx - Ulength * 30 - R, Oilcentery - Ulength * 6.7 - R);
	
	ege_line(Oilcenterx - Ulength * 6 - R, Oilcentery - Ulength * 6.4 - R, Oilcenterx - Ulength * 7 - R, Oilcentery - Ulength * 6.7 - R);
	
	
	
	setcolor(EGEARGB(0XFF, 0X2F, 0X87, 0X1B));
	ege_line(Oilcenterx - Ulength * 29 - R, Oilcentery - Ulength * 22 - R, Oilcenterx - Ulength * 30 - R, Oilcentery - Ulength * 22.5 - R);
	ege_line(Oilcenterx - Ulength * 30 - R, Oilcentery - Ulength * 22.5 - R, Oilcenterx - Ulength * 31 - R, Oilcentery - Ulength * 24 - R);
	ege_line(Oilcenterx - Ulength * 30 - R, Oilcentery - Ulength * 22.5 - R, Oilcenterx - Ulength * 31.5 - R, Oilcentery - Ulength * 22 - R);
	
	ege_line(Oilcenterx - Ulength * 6 - R, Oilcentery - Ulength * 22 - R, Oilcenterx - Ulength * 7 - R, Oilcentery - Ulength * 22.5 - R);
	ege_line(Oilcenterx - Ulength * 7 - R, Oilcentery - Ulength * 22.5 - R, Oilcenterx - Ulength * 8 - R, Oilcentery - Ulength * 24 - R);
	ege_line(Oilcenterx - Ulength * 7 - R, Oilcentery - Ulength * 22.5 - R, Oilcenterx - Ulength * 8.5 - R, Oilcentery - Ulength * 22 - R);
	
	
	//灯光遮盖效果
	setfillcolor(EGEARGB(255 - (int)UPPERangle, 0x00, 0x00, 0x00));
	ege_fillrect(Oilcenterx - side / 2, Oilcentery - side / 2, side ,side);
	
	
	
	draw_PFD_frame(Oilcenterx, Oilcentery, side);
	
}


extern double N21;
extern double N22;

extern double FF1;
extern double FF2;

extern double oilPress1;
extern double oilPress2;

extern double oilTemp1;
extern double oilTemp2;

extern double oilQTY1;
extern double oilQTY2;

extern double VIB1;
extern double VIB2;

void draw_LowerEICAS_frame(double x, double y, double side) {
	setfillcolor(BLACK);
	ege_fillrect(x, y, side * 1254 / 500, side * 1235 / 500);
}

void draw_LowerEICAS_lineFrames(double x, double y, double side) {
	setlinewidth(side * 0.007);
	setcolor(WHITE);
	
	//第一行两个框
	ege_rectangle(x + 229.0 / 500 * side, y + 94.0 / 500 * side, side * 169.0 / 500, side * 62.0 / 500);
	ege_rectangle(x + 567.0 / 500 * side, y + 94.0 / 500 * side, side * 169.0 / 500, side * 62.0 / 500);
	
	//第二行两个框
	ege_rectangle(x + 149.0 / 500 * side, y + 350.0 / 500 * side, side * 135.0 / 500, side * 63.0 / 500);
	ege_rectangle(x + 514.0 / 500 * side, y + 350.0 / 500 * side, side * 135.0 / 500, side * 63.0 / 500);
	
	//第三行两个框
	ege_rectangle(x + 202.0 / 500 * side, y + 503.0 / 500 * side, side * 85.0 / 500, side * 55.0 / 500);
	ege_rectangle(x + 514.0 / 500 * side, y + 503.0 / 500 * side, side * 85.0 / 500, side * 55.0 / 500);
	
	//第四行两个框
	ege_rectangle(x + 202.0 / 500 * side, y + 747.0 / 500 * side, side * 85.0 / 500, side * 55.0 / 500);
	ege_rectangle(x + 514.0 / 500 * side, y + 747.0 / 500 * side, side * 85.0 / 500, side * 55.0 / 500);
	
	//第五行两个框
	ege_rectangle(x + 222.0 / 500 * side, y + 878.0 / 500 * side, side * 63.0 / 500, side * 56.0 / 500);
	ege_rectangle(x + 515.0 / 500 * side, y + 878.0 / 500 * side, side * 63.0 / 500, side * 56.0 / 500);
	
	//第六行两个框
	ege_rectangle(x + 202.0 / 500 * side, y + 1043.0 / 500 * side, side * 86.0 / 500, side * 56.0 / 500);
	ege_rectangle(x + 516.0 / 500 * side, y + 1043.0 / 500 * side, side * 86.0 / 500, side * 56.0 / 500);
	
	
}

void draw_LowerEICAS_lines(double x, double y, double side) {
	//绘制第一组橙色小横线
	setcolor(EGEARGB(255, 0X85, 0X49, 0X06));
	ege_line(x + side * 305.0 / 500, y + side * 585.0 / 500, x + side * 313.0 / 500, y + side * 585.0 / 500);
	ege_line(x + side * 488.0 / 500, y + side * 585.0 / 500, x + side * 496.0 / 500, y + side * 585.0 / 500);
	
	//绘制第二组橙色小横线；
	ege_line(x + side * 306.0 / 500, y + side * 706.0 / 500, x + side * 313.0 / 500, y + side * 706.0 / 500);
	ege_line(x + side * 489.0 / 500, y + side * 706.0 / 500, x + side * 496.0 / 500, y + side * 706.0 / 500);
	
	//第一组竖线
	setcolor(WHITE);
	ege_line(x + side * 306.0 / 500, y + side * 456.0 / 500, x + side * 306.0 / 500, y + side * 599.0 / 500);
	ege_line(x + side * 496.0 / 500, y + side * 456.0 / 500, x + side * 496.0 / 500, y + side * 599.0 / 500);
	
	//第二组竖线
	ege_line(x + side * 306.0 / 500, y + side * 698.0 / 500, x + side * 306.0 / 500, y + side * 840.0 / 500);
	ege_line(x + side * 497.0 / 500, y + side * 698.0 / 500, x + side * 497.0 / 500, y + side * 840.0 / 500);
	
	//第三组竖线
	ege_line(x + side * 306.0 / 500, y + side * 998.0 / 500, x + side * 306.0 / 500, y + side * 1147.0 / 500);
	ege_line(x + side * 497.0 / 500, y + side * 998.0 / 500, x + side * 497.0 / 500, y + side * 1147.0 / 500);
	
	//一组白色横线
	ege_line(x + side * 306.0 / 500, y + side * 1028.0 / 500, x + side * 315.0 / 500, y + side * 1028.0 / 500);
	ege_line(x + side * 488.0 / 500, y + side * 1028.0 / 500, x + side * 497.0 / 500, y + side * 1028.0 / 500);
	
	//绘制第一组红色小横线
	setcolor(RED);
	ege_line(x + side * 295.0 / 500, y + side * 599.0 / 500, x + side * 323.0 / 500, y + side * 599.0 / 500);
	ege_line(x + side * 478.0 / 500, y + side * 599.0 / 500, x + side * 507.0 / 500, y + side * 599.0 / 500);
	
	//绘制第二组红色小横线
	ege_line(x + side * 295.0 / 500, y + side * 696.0 / 500, x + side * 323.0 / 500, y + side * 696.0 / 500);
	ege_line(x + side * 478.0 / 500, y + side * 696.0 / 500, x + side * 507.0 / 500, y + side * 696.0 / 500);
	
	//绘制最上方的红色线段；
	ege_line(x + side * 113.0 / 500, y + side * 100.0 / 500, x + side * 134.0 / 500, y + side * 112.0 / 500);
	ege_line(x + side * 450.0 / 500, y + side * 100.0 / 500, x + side * 472.0 / 500, y + side * 112.0 / 500);
}

void draw_LowerEICAS_arc(double x, double y, double side) {
	setcolor(WHITE);
	//绘制两个圆弧
	ege_arc(x + 229.0 / 500 * side - 112.0 / 500 * side,y + 169.0 / 500 * side - 112.0 / 500 * side,side * 224.0 / 500, side * 224.0 / 500,0, 210);
	ege_arc(x + 567.0 / 500 * side - 112.0 / 500 * side, y + 169.0 / 500 * side - 112.0 / 500 * side, side * 224.0 / 500, side * 224.0 / 500, 0, 210);
	
}
void draw_LowerEICAS_arcIn(double x, double y, double side) {
	setfillcolor(EGEARGB(255, 0X27, 0X22, 0X29));
	setcolor(BLACK);
	sector(x + side * 229.0 / 500, y + side * 169 / 500, - N21 * 2 - 2, 0, 112 * side / 500, 112 * side / 500);
	sector(x + side * 567.0 / 500, y + side * 169 / 500, - N22 * 2 - 2, 0, 112 * side / 500, 112 * side / 500);
}
void draw_LowerEICAS_pointer(double x, double y, double side) {
	side = side / 500;
	double r = 112 * side;
	ege_line(x + side * 229.0, y + side * 169, x + side * 229 + r * cos(N21 * 2 * PI / 180), y + side * 169 + r * sin(N21 * 2 * PI / 180));
	ege_line(x + side * 567.0, y + side * 169, x + side * 567 + r * cos(N22 * 2 * PI / 180), y + side * 169 + r * sin(N22 * 2 * PI / 180));
}

void draw_LowerEICAS_words(double x, double y, double side) {
	//绘制N2
	setbkmode(true);
	side = side / 500;
	double number_height = 25 * side * 2.2;
	double number_width = 13 * side * 2.0;
	setcolor(EGEARGB(255,0X3B,0X82,0X8F));
	setfont(number_height, number_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	outtextxy(x + side * 379, y + side * 255, 'N');
	outtextxy(x + side * 410, y + side * 268, '2');
	
	//绘制FF
	ege_drawtext("FF", x + 400 * side,y + 382 * side);
	
	//绘制OIL
	ege_drawtext("OIL", x + 400 * side, y + 513 * side);
	
	//绘制PRESS
	ege_drawtext("PRESS", x + 400 * side, y + 548 * side);
	
	//绘制OIL
	ege_drawtext("OIL", x + 400 * side, y + 753 * side);
	
	//绘制TEMP
	ege_drawtext("TEMP", x + 400 * side, y + 786 * side);
	
	//绘制OIL
	ege_drawtext("OIL", x + 366 * side, y + 905 * side);
	
	//绘制QTY
	ege_drawtext("QTY", x + 437 * side, y + 905 * side);
	
	//绘制OIL
	ege_drawtext("VIB", x + 400 * side, y + 1073 * side);
}
void draw_LowerEICAS_numbers(double x, double y, double side) {
	side = side / 500;
	double number_height = 25 * side * 2.2 * 1.5;
	double number_width = 13 * side * 2.0 * 1.5;
	setfont(number_height, number_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	
	setcolor(WHITE);
	char N21num[64];
	char N22num[64];
	sprintf_s(N21num, "%.1lf", N21);
	sprintf_s(N22num, "%.1lf", N22);
	//绘制N1
	if (N21 < 100) {
		ege_drawtext(N21num, x + side * 335, y + side * 128);
	}
	else {
		ege_drawtext(N21num, x + side * 316, y + side * 128);
	}
	if (N21 < 100) {
		ege_drawtext(N22num, x + side * 671, y + side * 128);
	}
	else {
		ege_drawtext(N22num, x + side * 652, y + side * 128);
	}
	
	//绘制FF
	char FF1num[64];
	char FF2num[64];
	sprintf_s(FF1num, "%.2lf", FF1);
	sprintf_s(FF2num, "%.2lf", FF2);
	ege_drawtext(FF1num, x + side * 217, y + side * 385);
	ege_drawtext(FF2num, x + side * 585, y + side * 385);
	
	//绘制oil temp
	char oiltempNum1[64];
	char oiltempNum2[64];
	
	sprintf_s(oiltempNum1, "%.0lf", oilTemp1);
	sprintf_s(oiltempNum2, "%.0lf", oilTemp2);
	
	if (oilTemp1 < 100) {
		ege_drawtext(oiltempNum1, x + side * 257, y + side * 777);
	}
	else {
		ege_drawtext(oiltempNum2, x + side * 243, y + side * 777);
	}
	if (oilTemp2 < 100) {
		ege_drawtext(oiltempNum2, x + side * 565, y + side * 777);
	}
	else {
		ege_drawtext(oiltempNum2, x + side * 556, y + side * 777);
	}
	
	//绘制OILQTY
	char oilqtyNum1[64];
	char oilqtyNum2[64];
	
	sprintf_s(oilqtyNum1, "%.0lf", oilQTY1);
	sprintf_s(oilqtyNum2, "%.0lf", oilQTY2);
	
	ege_drawtext(oilqtyNum1, x + side * 255, y + side * 910);
	ege_drawtext(oilqtyNum2, x + side * 548, y + side * 910);
	
	//绘制VIB
	char VIBNum1[64];
	char VIBNum2[64];
	
	sprintf_s(VIBNum1, "%.1lf", VIB1);
	sprintf_s(VIBNum2, "%.1lf", VIB2);
	
	ege_drawtext(VIBNum1, x + side * 245, y + side * 1075);
	ege_drawtext(VIBNum2, x + side * 560, y + side * 1075);
	
	//绘制OILPRESS
	char oilPRESSNum1[64];
	char oilPRESSNum2[64];
	
	sprintf_s(oilPRESSNum1, "%.0lf", oilPress1);
	sprintf_s(oilPRESSNum2, "%.0lf", oilPress2);
	if (oilPress1 >= 29 ) {
		ege_drawtext(oilPRESSNum1, x + side * 244.5, y + side * 530.5);
	}
	if (oilPress2 >= 29) {
		ege_drawtext(oilPRESSNum2, x + side * 556.5, y + side * 530.5);
	}
	
}

void draw_EICAS2(double x, double y, double side) {
	
	side /= 2.35;
	
	x = x - side * 1254 / 500 / 2;
	y = y - side * 1235 / 500 / 2;
	ege_enable_aa(true);
	draw_LowerEICAS_frame(x, y, side);//底框
	draw_LowerEICAS_lineFrames(x, y, side);//绘制矩形线框
	draw_LowerEICAS_lines(x, y, side);//绘制直线
	draw_LowerEICAS_arcIn(x, y, side);//绘制阴影区域
	draw_LowerEICAS_arc(x, y, side);//绘制圆弧
	draw_LowerEICAS_pointer(x, y, side);//绘制指针
	draw_LowerEICAS_words(x, y, side);//绘制所有的英文字母
	draw_LowerEICAS_numbers(x, y, side);//绘制所有的数字
}         
