
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

void draw_EICAS(double Oilcenterx, double Oilcentery, double side) {
	
	setfillcolor(BLACK);
	ege_fillrect(Oilcenterx - side / 1.9, Oilcentery - side / 1.9, 1.1 * side, 1.1 * side);
	
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	
	double Ulength = side / 84;
	double R = Ulength * 7.5;
	double linewidth_1 = Ulength / 3;
	double linelength = Ulength * 1.5;
	
	
	setlinewidth(linewidth_1 );
	setcolor(EGEARGB(0XFF, 0X80, 0X80, 0X80));
	
	
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
	
	char num_2[64];//左上下左
sprintf_s(num_2, "%.2f", FuelFlowSpeed);
ege_drawtext(num_2, Oilcenterx - Ulength * 26.5, Oilcentery + Ulength * 7.2);

char num_7[64];//左上下右
sprintf_s(num_7, "%.2f", FuelFlowSpeed_1);

ege_drawtext(num_7, Oilcenterx - Ulength * 3.5, Oilcentery + Ulength * 7.2);
	
	
	if (fanSpeed > 100) {
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
	
	setcolor(EGEARGB(0XFF, 0X2A, 0X21, 0X28));
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
	
	setcolor(EGEARGB(0XFF, 0X07, 0X9F, 0X9B));
	setfont(Ulength * 2.8, 0, "Calibri");
	ege_drawtext("ENG 1", Oilcenterx + Ulength * 16, Oilcentery - Ulength * 36.8);
	ege_drawtext("ENG 2", Oilcenterx + Ulength * 33, Oilcentery - Ulength * 36.8);
	
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
	setcolor(EGEARGB(0XFF, 0X07, 0X9F, 0XAB));
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
	setcolor(EGEARGB(0XFF, 0X80, 0X80, 0X80));
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
	ege_drawtext(num_6, Oilcenterx + Ulength * 21.5, Oilcentery + Ulength * 39.5);
	
	
	setcolor(EGEARGB(0XFF, 0X7F, 0X06, 0X03));
	ege_line(Oilcenterx - Ulength * 28.5 - R, Oilcentery - Ulength * 21.75 - R, Oilcenterx - Ulength * 30.5 - R, Oilcentery - Ulength * 22.75 - R);
	
	ege_line(Oilcenterx - Ulength * 5.5 - R, Oilcentery - Ulength * 21.75 - R, Oilcenterx - Ulength * 7.5 - R, Oilcentery - Ulength * 22.75 - R);
	
	ege_line(Oilcenterx - Ulength * 28.5 - R, Oilcentery - Ulength * 7 - R, Oilcenterx - Ulength * 30.5 - R, Oilcentery - Ulength * 7.75 - R);
	
	ege_line(Oilcenterx - Ulength * 5.5 - R, Oilcentery - Ulength * 7 - R, Oilcenterx - Ulength * 7.5 - R, Oilcentery - Ulength * 7.75 - R);
	
	setcolor(EGEARGB(0XFF, 0X89, 0X4A, 0X03));
	
	ege_line(Oilcenterx - Ulength * 29 - R, Oilcentery - Ulength * 6.4 - R, Oilcenterx - Ulength * 30 - R, Oilcentery - Ulength * 6.7 - R);
	
	ege_line(Oilcenterx - Ulength * 6 - R, Oilcentery - Ulength * 6.4 - R, Oilcenterx - Ulength * 7 - R, Oilcentery - Ulength * 6.7 - R);
	
	
	
	setcolor(EGEARGB(0XFF, 0X1F, 0X77, 0X0B));
	ege_line(Oilcenterx - Ulength * 29 - R, Oilcentery - Ulength * 22 - R, Oilcenterx - Ulength * 30 - R, Oilcentery - Ulength * 22.5 - R);
	ege_line(Oilcenterx - Ulength * 30 - R, Oilcentery - Ulength * 22.5 - R, Oilcenterx - Ulength * 31 - R, Oilcentery - Ulength * 24 - R);
	ege_line(Oilcenterx - Ulength * 30 - R, Oilcentery - Ulength * 22.5 - R, Oilcenterx - Ulength * 31.5 - R, Oilcentery - Ulength * 22 - R);
	
	ege_line(Oilcenterx - Ulength * 6 - R, Oilcentery - Ulength * 22 - R, Oilcenterx - Ulength * 7 - R, Oilcentery - Ulength * 22.5 - R);
	ege_line(Oilcenterx - Ulength * 7 - R, Oilcentery - Ulength * 22.5 - R, Oilcenterx - Ulength * 8 - R, Oilcentery - Ulength * 24 - R);
	ege_line(Oilcenterx - Ulength * 7 - R, Oilcentery - Ulength * 22.5 - R, Oilcenterx - Ulength * 8.5 - R, Oilcentery - Ulength * 22 - R);
	
	
	draw_PFD_frame(Oilcenterx, Oilcentery, side);
	
}
