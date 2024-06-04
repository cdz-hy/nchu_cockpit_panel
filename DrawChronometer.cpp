# include <stdio.h>
# include <graphics.h>
# include <math.h>

extern int hour1;
extern int minute1;
extern int month1;
extern int date1;
extern int hour2;
extern int minute2;
extern int month2;
extern int date2;
int times = 0;
int state = 0;
int timestate = 0;
int mod = -1;
int minute3 = 0;
int seconds = 0;
int setstate = 0;

//画计时器的外框
void draw_ChronometerFrame(double center_x, double center_y, double side)
{
	double chronometer_r = side * 43 / 108;

	//外框第一层
	setfillcolor(EGEARGB(0xff, 0x13, 0x15, 0x18));
	ege_point chronometerframe1[9];

	chronometerframe1[0].x = center_x - side * 54 / 108;
	chronometerframe1[0].y = center_y - side * 37.5 / 108;

	chronometerframe1[1].x = center_x - side * 37.5 / 108;
	chronometerframe1[1].y = center_y - side * 54 / 108;

	chronometerframe1[2].x = center_x + side * 37.5 / 108;
	chronometerframe1[2].y = center_y - side * 54 / 108;

	chronometerframe1[3].x = center_x + side * 54 / 108;
	chronometerframe1[3].y = center_y - side * 37.5 / 108;

	chronometerframe1[4].x = center_x + side * 54 / 108;
	chronometerframe1[4].y = center_y + side * 37.5 / 108;

	chronometerframe1[5].x = center_x + side * 37.5 / 108;
	chronometerframe1[5].y = center_y + side * 54 / 108;

	chronometerframe1[6].x = center_x - side * 37.5 / 108;
	chronometerframe1[6].y = center_y + side * 54 / 108;

	chronometerframe1[7].x = center_x - side * 54 / 108;
	chronometerframe1[7].y = center_y + side * 37.5 / 108;

	chronometerframe1[8].x = center_x - side * 54 / 108;
	chronometerframe1[8].y = center_y - side * 37.5 / 108;

	ege_fillpoly(9, chronometerframe1);

	//外框第二层
	ege_setpattern_lineargradient(center_x - chronometer_r, center_y - chronometer_r, EGEARGB(0xff, 0x1C, 0x1E, 0x20), center_x + chronometer_r, center_y + chronometer_r, EGEARGB(0xff, 0x02, 0x03, 0x03));
	ege_point chronometerframe2[9];

	chronometerframe2[0].x = center_x - side * 43 / 108;
	chronometerframe2[0].y = center_y - side * 26.5 / 108;

	chronometerframe2[1].x = center_x - side * 26.5 / 108;
	chronometerframe2[1].y = center_y - side * 43 / 108;

	chronometerframe2[2].x = center_x + side * 26.5 / 108;
	chronometerframe2[2].y = center_y - side * 43 / 108;

	chronometerframe2[3].x = center_x + side * 43 / 108;
	chronometerframe2[3].y = center_y - side * 26.5 / 108;

	chronometerframe2[4].x = center_x + side * 43 / 108;
	chronometerframe2[4].y = center_y + side * 26.5 / 108;

	chronometerframe2[5].x = center_x + side * 26.5 / 108;
	chronometerframe2[5].y = center_y + side * 43 / 108;

	chronometerframe2[6].x = center_x - side * 26.5 / 108;
	chronometerframe2[6].y = center_y + side * 43 / 108;

	chronometerframe2[7].x = center_x - side * 43 / 108;
	chronometerframe2[7].y = center_y + side * 26.5 / 108;

	chronometerframe2[8].x = center_x - side * 43 / 108;
	chronometerframe2[8].y = center_y - side * 26.5 / 108;

	ege_fillpoly(9, chronometerframe2);
	ege_setpattern_none();

	//外框最内层
	setfillcolor(BLACK);
	ege_point chronometerframe3[9];
	chronometerframe3[0].x = center_x - side * 42 / 108;
	chronometerframe3[0].y = center_y - side * 25.5 / 108;

	chronometerframe3[1].x = center_x - side * 25.5 / 108;
	chronometerframe3[1].y = center_y - side * 42 / 108;

	chronometerframe3[2].x = center_x + side * 25.5 / 108;
	chronometerframe3[2].y = center_y - side * 42 / 108;

	chronometerframe3[3].x = center_x + side * 42 / 108;
	chronometerframe3[3].y = center_y - side * 25.5 / 108;

	chronometerframe3[4].x = center_x + side * 42 / 108;
	chronometerframe3[4].y = center_y + side * 25.5 / 108;

	chronometerframe3[5].x = center_x + side * 25.5 / 108;
	chronometerframe3[5].y = center_y + side * 42 / 108;

	chronometerframe3[6].x = center_x - side * 25.5 / 108;
	chronometerframe3[6].y = center_y + side * 42 / 108;

	chronometerframe3[7].x = center_x - side * 42 / 108;
	chronometerframe3[7].y = center_y + side * 25.5 / 108;

	chronometerframe3[8].x = center_x - side * 42 / 108;
	chronometerframe3[8].y = center_y - side * 25.5 / 108;

	ege_fillpoly(9, chronometerframe3);
}

//画几个按钮
void draw_Chronometer_buttons(double center_x, double center_y, double side)
{
	//按钮1的偏转角度
	double Rad1 = -45 * PI / 180;
	//按钮1的阴影效果
	setfillcolor(EGEARGB(0xff, 0x1C, 0x1E, 0x20));
	ege_point button1shadow[5];

	button1shadow[0].x = -8 * side / 108 * cos(Rad1) - (-61.5 * side / 108) * sin(Rad1) + center_x;
	button1shadow[0].y = -61.5 * side / 108 * cos(Rad1) - 8 * side / 108 * sin(Rad1) + center_y;

	button1shadow[1].x = -8 * side / 108 * cos(Rad1) - (-51) * side / 108 * sin(Rad1) + center_x;
	button1shadow[1].y = -51 * side / 108 * cos(Rad1) - 8 * side / 108 * sin(Rad1) + center_y;

	button1shadow[2].x = 7.5 * side / 108 * cos(Rad1) - (-51 * side / 108) * sin(Rad1) + center_x;
	button1shadow[2].y = -51 * side / 108 * cos(Rad1) + 7.5 * side / 108 * sin(Rad1) + center_y;

	button1shadow[3].x = 7.5 * side / 108 * cos(Rad1) - (-61 * side / 108) * sin(Rad1) + center_x;
	button1shadow[3].y = -61 * side / 108 * cos(Rad1) + 7.5 * side / 108 * sin(Rad1) + center_y;

	button1shadow[4].x = -8 * side / 108 * cos(Rad1) - (-61.5 * side / 108) * sin(Rad1) + center_x;
	button1shadow[4].y = -61.5 * side / 108 * cos(Rad1) - 8 * side / 108 * sin(Rad1) + center_y;

	ege_fillpoly(5, button1shadow);

	//左上角的按钮
	setfillcolor(BLACK);
	ege_point button1[5];

	button1[0].x = -7.5 * side / 108 * cos(Rad1) - (-61.5 * side / 108) * sin(Rad1) + center_x;
	button1[0].y = -61.5 * side / 108 * cos(Rad1) - 7.5 * side / 108 * sin(Rad1) + center_y;

	button1[1].x = -7.5 * side / 108 * cos(Rad1) - (-51.5) * side / 108 * sin(Rad1) + center_x;
	button1[1].y = -51.5 * side / 108 * cos(Rad1) - 7.5 * side / 108 * sin(Rad1) + center_y;

	button1[2].x = 7.5 * side / 108 * cos(Rad1) - (-51.5 * side / 108) * sin(Rad1) + center_x;
	button1[2].y = -51.5 * side / 108 * cos(Rad1) + 7.5 * side / 108 * sin(Rad1) + center_y;

	button1[3].x = 7.5 * side / 108 * cos(Rad1) - (-61.5 * side / 108) * sin(Rad1) + center_x;
	button1[3].y = -61.5 * side / 108 * cos(Rad1) + 7.5 * side / 108 * sin(Rad1) + center_y;

	button1[4].x = -7.5 * side / 108 * cos(Rad1) - (-61.5 * side / 108) * sin(Rad1) + center_x;
	button1[4].y = -61.5 * side / 108 * cos(Rad1) - 7.5 * side / 108 * sin(Rad1) + center_y;

	ege_fillpoly(5, button1);

	//按钮2，3的偏转角度
	double Rad2 = 45 * PI / 180;
	//按钮2，3的阴影效果


	//右上角的按钮
	setfillcolor(BLACK);
	ege_point button2[5];

	button2[0].x = -15.5 * side / 108 * cos(Rad2) - (-59.5 * side / 108) * sin(Rad2) + center_x;
	button2[0].y = -59.5 * side / 108 * cos(Rad2) - 15.5 * side / 108 * sin(Rad2) + center_y;

	button2[1].x = -1.5 * side / 108 * cos(Rad2) - (-59.5 * side / 108) * sin(Rad2) + center_x;
	button2[1].y = -59.5 * side / 108 * cos(Rad2) - 1.5 * side / 108 * sin(Rad2) + center_y;

	button2[2].x = -1.5 * side / 108 * cos(Rad2) - (-50.5 * side / 108) * sin(Rad2) + center_x;
	button2[2].y = -50.5 * side / 108 * cos(Rad2) - 1.5 * side / 108 * sin(Rad2) + center_y;

	button2[3].x = -15.5 * side / 108 * cos(Rad2) - (-50.5 * side / 108) * sin(Rad2) + center_x;
	button2[3].y = -50.5 * side / 108 * cos(Rad2) - 15.5 * side / 108 * sin(Rad2) + center_y;

	button2[4].x = -15.5 * side / 108 * cos(Rad2) - (-59.5 * side / 108) * sin(Rad2) + center_x;
	button2[4].y = -59.5 * side / 108 * cos(Rad2) - 15.5 * side / 108 * sin(Rad2) + center_y;

	ege_fillpoly(5, button2);

	ege_point button3[5];

	button3[0].x = 15.5 * side / 108 * cos(Rad2) - (-59.5 * side / 108) * sin(Rad2) + center_x;
	button3[0].y = -59.5 * side / 108 * cos(Rad2) + 15.5 * side / 108 * sin(Rad2) + center_y;

	button3[1].x = 1.5 * side / 108 * cos(Rad2) - (-59.5 * side / 108) * sin(Rad2) + center_x;
	button3[1].y = -59.5 * side / 108 * cos(Rad2) + 1.5 * side / 108 * sin(Rad2) + center_y;

	button3[2].x = 1.5 * side / 108 * cos(Rad2) - (-50.5 * side / 108) * sin(Rad2) + center_x;
	button3[2].y = -50.5 * side / 108 * cos(Rad2) + 1.5 * side / 108 * sin(Rad2) + center_y;

	button3[3].x = 15.5 * side / 108 * cos(Rad2) - (-50.5 * side / 108) * sin(Rad2) + center_x;
	button3[3].y = -50.5 * side / 108 * cos(Rad2) + 15.5 * side / 108 * sin(Rad2) + center_y;

	button3[4].x = 15.5 * side / 108 * cos(Rad2) - (-59.5 * side / 108) * sin(Rad2) + center_x;
	button3[4].y = -59.5 * side / 108 * cos(Rad2) + 15.5 * side / 108 * sin(Rad2) + center_y;

	ege_fillpoly(5, button3);

	//按钮4，5的偏转角度
	Rad2 = 135 * PI / 180;
	//按钮4，5的阴影效果


	//右下角的按钮
	setfillcolor(BLACK);
	//ege_point button2[5];

	button2[0].x = -15.5 * side / 108 * cos(Rad2) - (-59.5 * side / 108) * sin(Rad2) + center_x;
	button2[0].y = -59.5 * side / 108 * cos(Rad2) - 15.5 * side / 108 * sin(Rad2) + center_y;

	button2[1].x = -1.5 * side / 108 * cos(Rad2) - (-59.5 * side / 108) * sin(Rad2) + center_x;
	button2[1].y = -59.5 * side / 108 * cos(Rad2) - 1.5 * side / 108 * sin(Rad2) + center_y;

	button2[2].x = -1.5 * side / 108 * cos(Rad2) - (-50.5 * side / 108) * sin(Rad2) + center_x;
	button2[2].y = -50.5 * side / 108 * cos(Rad2) - 1.5 * side / 108 * sin(Rad2) + center_y;

	button2[3].x = -15.5 * side / 108 * cos(Rad2) - (-50.5 * side / 108) * sin(Rad2) + center_x;
	button2[3].y = -50.5 * side / 108 * cos(Rad2) - 15.5 * side / 108 * sin(Rad2) + center_y;

	button2[4].x = -15.5 * side / 108 * cos(Rad2) - (-59.5 * side / 108) * sin(Rad2) + center_x;
	button2[4].y = -59.5 * side / 108 * cos(Rad2) - 15.5 * side / 108 * sin(Rad2) + center_y;

	ege_fillpoly(5, button2);

	//ege_point button3[5];

	button3[0].x = 15.5 * side / 108 * cos(Rad2) - (-59.5 * side / 108) * sin(Rad2) + center_x;
	button3[0].y = -59.5 * side / 108 * cos(Rad2) + 15.5 * side / 108 * sin(Rad2) + center_y;

	button3[1].x = 1.5 * side / 108 * cos(Rad2) - (-59.5 * side / 108) * sin(Rad2) + center_x;
	button3[1].y = -59.5 * side / 108 * cos(Rad2) + 1.5 * side / 108 * sin(Rad2) + center_y;

	button3[2].x = 1.5 * side / 108 * cos(Rad2) - (-50.5 * side / 108) * sin(Rad2) + center_x;
	button3[2].y = -50.5 * side / 108 * cos(Rad2) + 1.5 * side / 108 * sin(Rad2) + center_y;

	button3[3].x = 15.5 * side / 108 * cos(Rad2) - (-50.5 * side / 108) * sin(Rad2) + center_x;
	button3[3].y = -50.5 * side / 108 * cos(Rad2) + 15.5 * side / 108 * sin(Rad2) + center_y;

	button3[4].x = 15.5 * side / 108 * cos(Rad2) - (-59.5 * side / 108) * sin(Rad2) + center_x;
	button3[4].y = -59.5 * side / 108 * cos(Rad2) + 15.5 * side / 108 * sin(Rad2) + center_y;

	ege_fillpoly(5, button3);

	//按钮6，7的偏转角度
	Rad2 = 225 * PI / 180;
	//按钮6，7的阴影效果


	//右上角的按钮
	setfillcolor(BLACK);
	//ege_point button2[5];

	button2[0].x = -15.5 * side / 108 * cos(Rad2) - (-59.5 * side / 108) * sin(Rad2) + center_x;
	button2[0].y = -59.5 * side / 108 * cos(Rad2) - 15.5 * side / 108 * sin(Rad2) + center_y;

	button2[1].x = -1.5 * side / 108 * cos(Rad2) - (-59.5 * side / 108) * sin(Rad2) + center_x;
	button2[1].y = -59.5 * side / 108 * cos(Rad2) - 1.5 * side / 108 * sin(Rad2) + center_y;

	button2[2].x = -1.5 * side / 108 * cos(Rad2) - (-50.5 * side / 108) * sin(Rad2) + center_x;
	button2[2].y = -50.5 * side / 108 * cos(Rad2) - 1.5 * side / 108 * sin(Rad2) + center_y;

	button2[3].x = -15.5 * side / 108 * cos(Rad2) - (-50.5 * side / 108) * sin(Rad2) + center_x;
	button2[3].y = -50.5 * side / 108 * cos(Rad2) - 15.5 * side / 108 * sin(Rad2) + center_y;

	button2[4].x = -15.5 * side / 108 * cos(Rad2) - (-59.5 * side / 108) * sin(Rad2) + center_x;
	button2[4].y = -59.5 * side / 108 * cos(Rad2) - 15.5 * side / 108 * sin(Rad2) + center_y;

	ege_fillpoly(5, button2);

	//ege_point button3[5];

	button3[0].x = 15.5 * side / 108 * cos(Rad2) - (-59.5 * side / 108) * sin(Rad2) + center_x;
	button3[0].y = -59.5 * side / 108 * cos(Rad2) + 15.5 * side / 108 * sin(Rad2) + center_y;

	button3[1].x = 1.5 * side / 108 * cos(Rad2) - (-59.5 * side / 108) * sin(Rad2) + center_x;
	button3[1].y = -59.5 * side / 108 * cos(Rad2) + 1.5 * side / 108 * sin(Rad2) + center_y;

	button3[2].x = 1.5 * side / 108 * cos(Rad2) - (-50.5 * side / 108) * sin(Rad2) + center_x;
	button3[2].y = -50.5 * side / 108 * cos(Rad2) + 1.5 * side / 108 * sin(Rad2) + center_y;

	button3[3].x = 15.5 * side / 108 * cos(Rad2) - (-50.5 * side / 108) * sin(Rad2) + center_x;
	button3[3].y = -50.5 * side / 108 * cos(Rad2) + 15.5 * side / 108 * sin(Rad2) + center_y;

	button3[4].x = 15.5 * side / 108 * cos(Rad2) - (-59.5 * side / 108) * sin(Rad2) + center_x;
	button3[4].y = -59.5 * side / 108 * cos(Rad2) + 15.5 * side / 108 * sin(Rad2) + center_y;

	ege_fillpoly(5, button3);
}

//画刻度
void draw_Chronometer_Scale(double center_x, double center_y, double side)
{
	double r = 36 * side / 108;

	//短刻度
	for (int i = 6; i < 360; i += 6)
	{
		if (i % 30 != 0)
		{
			setlinewidth(r * 0.018);//设置线宽
			setcolor(EGEARGB(0x99, 0xff, 0xff, 0xff));//设置线的颜色
			double rad = i * PI / 180;
			ege_line(r * 1.03 * sin(rad) + center_x, -r * 1.03 * cos(rad) + center_y, r * 0.92 * sin(rad) + center_x, -r * 0.92 * cos(rad) + center_y);
		}
	}

	//长刻度
	for (int i = 0; i < 360; i += 30)
	{
		setlinewidth(r * 0.02);//设置线宽
		setcolor(EGEARGB(0xaa, 0xff, 0xff, 0xff));//设置线的颜色
		double rad = i * PI / 180;
		ege_line(r * 1.1 * sin(rad) + center_x, -r * 1.1 * cos(rad) + center_y, r * 0.92 * sin(rad) + center_x, -r * 0.92 * cos(rad) + center_y);
	}

	//刻度值
	for (int i = 0; i <= 360; i += 60)
	{
		//double textAngle = i;
		double rad = i * PI / 180.0;
		double textPosX = center_x + 0.78 * r * sin(rad);
		double textPosY = center_y - 0.78 * r * cos(rad);

		LOGFONT font;
		setfont(side * 0.07, side * 0.037, "黑体");
		setcolor(EGEARGB(0x99, 0x99, 0x99, 0x99));
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		getfont(&font);
		font.lfWeight = 550;
		setfont(&font);

		char strBuffer[64];
		sprintf_s(strBuffer, "%d", i / 6);
		setbkmode(1);
		if (i != 0)
			outtextxy(textPosX, textPosY, strBuffer);
	}
}

//画中间的时间显示
void draw_Chronometer_time(double center_x, double center_y, double side)
{
	if (timestate == 0 && mod == -1)
	{
		if (times == 0) {
			LOGFONTW font;
			setfont(side * 0.17, side * 0.06, "DigifaceWide");
			setcolor(EGEARGB(0x99, 0x99, 0x99, 0x99));
			font.lfWidth = side * 0.05;
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			getfont(&font);
			font.lfWeight = 550;
			setfont(&font);
			//int hour = 1;
			char stringbuffer[64];
			sprintf_s(stringbuffer, "%d", hour1);
			if (hour1 >= 10)
				outtextxy(center_x - side * 9 / 108, center_y - side * 10 / 108, stringbuffer);
			else
				outtextxy(center_x - side * 5 / 108, center_y - side * 10 / 108, stringbuffer);

			setfont(side * 0.17, side * 0.06, "Leelawadee");
			setcolor(EGEARGB(0x99, 0x99, 0x99, 0x99));
			font.lfWidth = side * 0.05;
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			getfont(&font);
			font.lfWeight = 550;
			setfont(&font);
			outtextxy(center_x, center_y - side * 10.5 / 108, ":");

			setfont(side * 0.04, side * 0.06, "Leelawadee");
			setcolor(EGEARGB(0xff, 0x99, 0x99, 0x99));
			font.lfWidth = side * 0.05;
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			getfont(&font);
			font.lfWeight = 550;
			setfont(&font);
			ege_drawtext("MAN", center_x + side * 27 / 108, center_y - side * 33 / 108);

			setfont(side * 0.17, side * 0.06, "DigifaceWide");
			setcolor(EGEARGB(0x99, 0x99, 0x99, 0x99));
			font.lfWidth = side * 0.05;
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			getfont(&font);
			font.lfWeight = 550;
			setfont(&font);
			//int minute = 59;
			sprintf_s(stringbuffer, "%02d", minute1);
			outtextxy(center_x + side * 9 / 108, center_y - side * 10 / 108, stringbuffer);
		}
		else if (times == 1)
		{
			LOGFONTW font;
			setfont(side * 0.17, side * 0.06, "DigifaceWide");
			setcolor(EGEARGB(0x99, 0x99, 0x99, 0x99));
			font.lfWidth = side * 0.05;
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			getfont(&font);
			font.lfWeight = 550;
			setfont(&font);
			char stringbuffer[64];
			sprintf_s(stringbuffer, "%d", month1);
			if (month1 >= 10)
				outtextxy(center_x - side * 9 / 108, center_y - side * 10 / 108, stringbuffer);
			else
				outtextxy(center_x - side * 4 / 108, center_y - side * 10 / 108, stringbuffer);

			setfont(side * 0.17, side * 0.06, "DigifaceWide");
			setcolor(EGEARGB(0x99, 0x99, 0x99, 0x99));
			font.lfWidth = side * 0.05;
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			getfont(&font);
			font.lfWeight = 550;
			setfont(&font);
			sprintf_s(stringbuffer, "%d", date1);
			if (date1 >= 10)
				outtextxy(center_x + side * 9 / 108, center_y - side * 10 / 108, stringbuffer);
			else
				outtextxy(center_x + side * 4 / 108, center_y - side * 10 / 108, stringbuffer);

			setfont(side * 0.04, side * 0.06, "Leelawadee");
			setcolor(EGEARGB(0xff, 0x99, 0x99, 0x99));
			font.lfWidth = side * 0.05;
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			getfont(&font);
			font.lfWeight = 550;
			setfont(&font);
			ege_drawtext("MAN", center_x + side * 27 / 108, center_y - side * 33 / 108);
		}
		else if (times == 2)
		{
			LOGFONTW font;
			setfont(side * 0.17, side * 0.06, "DigifaceWide");
			setcolor(EGEARGB(0x99, 0x99, 0x99, 0x99));
			font.lfWidth = side * 0.05;
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			getfont(&font);
			font.lfWeight = 550;
			setfont(&font);
			char stringbuffer[64];
			sprintf_s(stringbuffer, "%d", hour2);
			if (hour2 >= 10)
				outtextxy(center_x - side * 9 / 108, center_y - side * 10 / 108, stringbuffer);
			else
				outtextxy(center_x - side * 5 / 108, center_y - side * 10 / 108, stringbuffer);

			setfont(side * 0.17, side * 0.06, "Leelawadee");
			setcolor(EGEARGB(0x99, 0x99, 0x99, 0x99));
			font.lfWidth = side * 0.05;
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			getfont(&font);
			font.lfWeight = 550;
			setfont(&font);
			outtextxy(center_x, center_y - side * 10.5 / 108, ":");

			setfont(side * 0.04, side * 0.06, "Leelawadee");
			setcolor(EGEARGB(0xff, 0x99, 0x99, 0x99));
			font.lfWidth = side * 0.05;
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			getfont(&font);
			font.lfWeight = 550;
			setfont(&font);
			ege_drawtext("UTC", center_x + side * 27 / 108, center_y - side * 33 / 108);

			setfont(side * 0.17, side * 0.06, "DigifaceWide");
			setcolor(EGEARGB(0x99, 0x99, 0x99, 0x99));
			font.lfWidth = side * 0.05;
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			getfont(&font);
			font.lfWeight = 550;
			setfont(&font);
			sprintf_s(stringbuffer, "%02d", minute2);
			outtextxy(center_x + side * 9 / 108, center_y - side * 10 / 108, stringbuffer);
		}
		else if (times == 3)
		{
			LOGFONTW font;
			setfont(side * 0.17, side * 0.06, "DigifaceWide");
			setcolor(EGEARGB(0x99, 0x99, 0x99, 0x99));
			font.lfWidth = side * 0.05;
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			getfont(&font);
			font.lfWeight = 550;
			setfont(&font);
			char stringbuffer[64];
			sprintf_s(stringbuffer, "%d", month2);
			if (month2 >= 10)
				outtextxy(center_x - side * 9 / 108, center_y - side * 10 / 108, stringbuffer);
			else
				outtextxy(center_x - side * 5 / 108, center_y - side * 10 / 108, stringbuffer);

			setfont(side * 0.17, side * 0.06, "DigifaceWide");
			setcolor(EGEARGB(0x99, 0x99, 0x99, 0x99));
			font.lfWidth = side * 0.05;
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			getfont(&font);
			font.lfWeight = 550;
			setfont(&font);
			sprintf_s(stringbuffer, "%d", date2);
			if (date2 >= 10)
				outtextxy(center_x + side * 9 / 108, center_y - side * 10 / 108, stringbuffer);
			else
				outtextxy(center_x + side * 4 / 108, center_y - side * 10 / 108, stringbuffer);

			setfont(side * 0.04, side * 0.06, "Leelawadee");
			setcolor(EGEARGB(0xff, 0x99, 0x99, 0x99));
			font.lfWidth = side * 0.05;
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			getfont(&font);
			font.lfWeight = 550;
			setfont(&font);
			ege_drawtext("UTC", center_x + side * 27 / 108, center_y - side * 33 / 108);
		}
	}
}

//画文字
void draw_Chronometer_text(double center_x, double center_y, double side)
{
	if (timestate == 0 && mod == -1)
	{
		LOGFONTW font;
		setfont(side * 0.07, 0, "Leelawadee");
		setcolor(EGEARGB(0xff, 0x8F, 0x64, 0x42));
		font.lfWidth = side * 0.05;
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		getfont(&font);
		font.lfWeight = 550;
		setfont(&font);
		//左上角的文字
		ege_drawtext("CHR", center_x - side * 28 / 108, center_y - side * 48 / 108);
		//右上角的文字
		ege_drawtext("TIME/DATE", center_x + side * 9 / 108, center_y - side * 48 / 108);
		ege_drawtext("SET", center_x + side * 49 / 108, center_y - side * 20 / 108);
		//左下角的文字
		ege_drawtext("ET", center_x - side * 49 / 108, center_y + side * 21 / 108);
		ege_drawtext("RESET", center_x - side * 15.5 / 108, center_y + side * 49 / 108);
		//右下角的文字
		ege_drawtext("+", center_x + side * 48 / 108, center_y + side * 23 / 108);
		ege_drawtext("-", center_x + side * 24 / 108, center_y + side * 49 / 108);

		if (times == 0)
		{
			setfont(side * 0.06, 0, "Leelawadee");
			setcolor(EGEARGB(0xff, 0x99, 0x99, 0x99));
			font.lfWidth = side * 0.05;
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			getfont(&font);
			font.lfWeight = 550;
			setfont(&font);
			ege_drawtext("TIME", center_x, center_y - side * 18 / 108);
		}
		else if (times == 1)
		{
			setfont(side * 0.06, 0, "Leelawadee");
			setcolor(EGEARGB(0xff, 0x99, 0x99, 0x99));
			font.lfWidth = side * 0.05;
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			getfont(&font);
			font.lfWeight = 550;
			setfont(&font);
			ege_drawtext("DATE", center_x, center_y - side * 18 / 108);
		}
		else if (times == 2)
		{
			setfont(side * 0.06, 0, "Leelawadee");
			setcolor(EGEARGB(0xff, 0x99, 0x99, 0x99));
			font.lfWidth = side * 0.05;
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			getfont(&font);
			font.lfWeight = 550;
			setfont(&font);
			ege_drawtext("TIME", center_x, center_y - side * 18 / 108);
		}
		else if (times == 3)
		{
			setfont(side * 0.06, 0, "Leelawadee");
			setcolor(EGEARGB(0xff, 0x99, 0x99, 0x99));
			font.lfWidth = side * 0.05;
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			getfont(&font);
			font.lfWeight = 550;
			setfont(&font);
			ege_drawtext("DATE", center_x, center_y - side * 18 / 108);
		}
	}
	else
	{
		LOGFONTW font;
		setfont(side * 0.07, 0, "Leelawadee");
		setcolor(EGEARGB(0xff, 0x8F, 0x64, 0x42));
		font.lfWidth = side * 0.05;
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		getfont(&font);
		font.lfWeight = 550;
		setfont(&font);
		//左上角的文字
		ege_drawtext("CHR", center_x - side * 28 / 108, center_y - side * 48 / 108);
		//右上角的文字
		ege_drawtext("TIME/DATE", center_x + side * 9 / 108, center_y - side * 48 / 108);
		ege_drawtext("SET", center_x + side * 49 / 108, center_y - side * 20 / 108);
		//左下角的文字
		ege_drawtext("ET", center_x - side * 49 / 108, center_y + side * 21 / 108);
		ege_drawtext("RESET", center_x - side * 15.5 / 108, center_y + side * 49 / 108);
		//右下角的文字
		ege_drawtext("+", center_x + side * 48 / 108, center_y + side * 23 / 108);
		ege_drawtext("-", center_x + side * 24 / 108, center_y + side * 49 / 108);


		setfont(side * 0.06, 0, "Leelawadee");
		setcolor(EGEARGB(0xff, 0x99, 0x99, 0x99));
		font.lfWidth = side * 0.05;
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		getfont(&font);
		font.lfWeight = 550;
		setfont(&font);
		ege_drawtext("ET", center_x, center_y - side * 18 / 108);
	}
}

//检测鼠标是否在某区域内按下
void check_mouse(double center_x, double center_y, double side)
{
	int mouse_x;
	int mouse_y;
	mousepos(&mouse_x, &mouse_y);
	int mouse_x_real = mouse_x;
	int mouse_y_real = mouse_y;

	//判断鼠标位置
	if (mouse_x_real >= center_x + side * 25 / 108 && mouse_x_real <= center_x + side * 40 / 108 && mouse_y_real <= center_y - side * 35 / 108 && mouse_y_real >= center_y - side * 50 / 108)
	{
		double Rad2 = 45 * PI / 180;
		setfillcolor(BLACK);
		ege_point button2[5];

		button2[0].x = -15.8 * side / 108 * cos(Rad2) - (-59.8 * side / 108) * sin(Rad2) + center_x;
		button2[0].y = -59.8 * side / 108 * cos(Rad2) - 15.8 * side / 108 * sin(Rad2) + center_y;

		button2[1].x = -1.2 * side / 108 * cos(Rad2) - (-59.8 * side / 108) * sin(Rad2) + center_x;
		button2[1].y = -59.8 * side / 108 * cos(Rad2) - 1.2 * side / 108 * sin(Rad2) + center_y;

		button2[2].x = -1.2 * side / 108 * cos(Rad2) - (-50.2 * side / 108) * sin(Rad2) + center_x;
		button2[2].y = -50.2 * side / 108 * cos(Rad2) - 1.2 * side / 108 * sin(Rad2) + center_y;

		button2[3].x = -15.8 * side / 108 * cos(Rad2) - (-50.2 * side / 108) * sin(Rad2) + center_x;
		button2[3].y = -50.2 * side / 108 * cos(Rad2) - 15.8 * side / 108 * sin(Rad2) + center_y;

		button2[4].x = -15.8 * side / 108 * cos(Rad2) - (-59.8 * side / 108) * sin(Rad2) + center_x;
		button2[4].y = -59.8 * side / 108 * cos(Rad2) - 15.8 * side / 108 * sin(Rad2) + center_y;

		setlinewidth(side * 0.001);

		ege_drawpoly(5, button2);
	}

	//判断鼠标是否点击
	if (GetAsyncKeyState(0x04) & 0x8000 && state == 0) {
		mousepos(&mouse_x, &mouse_y);
		mouse_x_real = mouse_x;
		mouse_y_real = mouse_y;

		if (mouse_x_real >= center_x + side * 25 / 108 && mouse_x_real <= center_x + side * 40 / 108 && mouse_y_real <= center_y - side * 35 / 108 && mouse_y_real >= center_y - side * 50 / 108)
		{
			if (times < 3) {
				times++;
				state = 1;
			}
			else if (times == 3) {
				times = 0;
				state = 1;
			}
		}
	}
}

//计时模式
void timing(double center_x, double center_y, double side)
{
	static int timess;
	static double moretime;
	static double a;
	static double angle;
	int mouse_x;
	int mouse_y;
	mousepos(&mouse_x, &mouse_y);
	int mouse_x_real = mouse_x;
	int mouse_y_real = mouse_y;
	mousepos(&mouse_x, &mouse_y);
	mouse_x_real = mouse_x;
	mouse_y_real = mouse_y;

	if (timess != times)
	{
		timess = times;
		mod = -1;
		return;
	}

	if (mod != -1) {
		if (mod == 0) {
			minute3 = 0;
			a = fclock();

			if (a - moretime <= 59)
				seconds = a - moretime;
			else
			{
				while (a - moretime >= 60)
				{
					a -= 60;
					minute3++;
				}
				seconds = a - moretime;
			}

			angle = (a - moretime) * 6 * PI / 180;

			ege_point point[4];

			point[0].x = -0.25 * side / 108 * cos(angle) - (-15 * side / 108 * sin(angle)) + center_x;
			point[0].y = -15 * side / 108 * cos(angle) - 0.25 * side / 108 * sin(angle) + center_y;

			point[1].x = 0.25 * side / 108 * cos(angle) - (-15 * side / 108 * sin(angle)) + center_x;
			point[1].y = -15 * side / 108 * cos(angle) + 0.25 * side / 108 * sin(angle) + center_y;

			point[2].x = 1 * side / 108 * cos(angle) - (-30 * side / 108 * sin(angle)) + center_x;
			point[2].y = -30 * side / 108 * cos(angle) + 1 * side / 108 * sin(angle) + center_y;

			point[3].x = -1 * side / 108 * cos(angle) - (-30 * side / 108 * sin(angle)) + center_x;
			point[3].y = -30 * side / 108 * cos(angle) - 1 * side / 108 * sin(angle) + center_y;

			setfillcolor(WHITE);
			ege_fillpoly(4, point);
		}

		LOGFONTW font;
		setfont(side * 0.17, side * 0.06, "DigifaceWide");
		setcolor(EGEARGB(0x99, 0x99, 0x99, 0x99));
		font.lfWidth = side * 0.05;
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		getfont(&font);
		font.lfWeight = 550;
		setfont(&font);
		char str[64];
		sprintf_s(str, "%d", minute3);

		if (minute3 >= 10)
			outtextxy(center_x - side * 9 / 108, center_y - side * 10 / 108, str);
		else
			outtextxy(center_x - side * 5 / 108, center_y - side * 10 / 108, str);

		setfont(side * 0.17, side * 0.06, "Leelawadee");
		setcolor(EGEARGB(0x99, 0x99, 0x99, 0x99));
		font.lfWidth = side * 0.05;
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		getfont(&font);
		font.lfWeight = 550;
		setfont(&font);
		outtextxy(center_x, center_y - side * 10.5 / 108, ":");

		setfont(side * 0.17, side * 0.06, "DigifaceWide");
		setcolor(EGEARGB(0x99, 0x99, 0x99, 0x99));
		font.lfWidth = side * 0.05;
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		getfont(&font);
		font.lfWeight = 550;
		setfont(&font);
		sprintf_s(str, "%02d", seconds);
		outtextxy(center_x + side * 9 / 108, center_y - side * 10 / 108, str);

		ege_point point[4];

		point[0].x = -0.25 * side / 108 * cos(angle) - (-15 * side / 108 * sin(angle)) + center_x;
		point[0].y = -15 * side / 108 * cos(angle) - 0.25 * side / 108 * sin(angle) + center_y;

		point[1].x = 0.25 * side / 108 * cos(angle) - (-15 * side / 108 * sin(angle)) + center_x;
		point[1].y = -15 * side / 108 * cos(angle) + 0.25 * side / 108 * sin(angle) + center_y;

		point[2].x = 1 * side / 108 * cos(angle) - (-30 * side / 108 * sin(angle)) + center_x;
		point[2].y = -30 * side / 108 * cos(angle) + 1 * side / 108 * sin(angle) + center_y;

		point[3].x = -1 * side / 108 * cos(angle) - (-30 * side / 108 * sin(angle)) + center_x;
		point[3].y = -30 * side / 108 * cos(angle) - 1 * side / 108 * sin(angle) + center_y;

		setfillcolor(WHITE);
		ege_fillpoly(4, point);
	}
	else if (mod == -1 && timestate == 1 && (minute3 == 0 && seconds == 0))
	{
		seconds = 0;
		minute3 = 0;
		LOGFONTW font;
		setfont(side * 0.17, side * 0.06, "DigifaceWide");
		setcolor(EGEARGB(0x99, 0x99, 0x99, 0x99));
		font.lfWidth = side * 0.05;
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		getfont(&font);
		font.lfWeight = 550;
		setfont(&font);
		char str[64];
		sprintf_s(str, "%d", minute3);

		if (minute3 >= 10)
			outtextxy(center_x - side * 9 / 108, center_y - side * 10 / 108, str);
		else
			outtextxy(center_x - side * 5 / 108, center_y - side * 10 / 108, str);

		setfont(side * 0.17, side * 0.06, "Leelawadee");
		setcolor(EGEARGB(0x99, 0x99, 0x99, 0x99));
		font.lfWidth = side * 0.05;
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		getfont(&font);
		font.lfWeight = 550;
		setfont(&font);
		outtextxy(center_x, center_y - side * 10.5 / 108, ":");

		setfont(side * 0.17, side * 0.06, "DigifaceWide");
		setcolor(EGEARGB(0x99, 0x99, 0x99, 0x99));
		font.lfWidth = side * 0.05;
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		getfont(&font);
		font.lfWeight = 550;
		setfont(&font);
		sprintf_s(str, "%02d", seconds);
		outtextxy(center_x + side * 9 / 108, center_y - side * 10 / 108, str);
	}



	if (mouse_x_real <= center_x - side * 30 / 108 && mouse_x_real >= center_x - side * 50 / 108 && mouse_y_real <= center_y - side * 25 / 108 && mouse_y_real >= center_y - side * 50 / 108)
	{
		double Rad1 = -45 * PI / 180;
		ege_point button1[5];

		button1[0].x = -7.8 * side / 108 * cos(Rad1) - (-61.8 * side / 108) * sin(Rad1) + center_x;
		button1[0].y = -61.8 * side / 108 * cos(Rad1) - 7.8 * side / 108 * sin(Rad1) + center_y;

		button1[1].x = -7.8 * side / 108 * cos(Rad1) - (-51.2) * side / 108 * sin(Rad1) + center_x;
		button1[1].y = -51.2 * side / 108 * cos(Rad1) - 7.8 * side / 108 * sin(Rad1) + center_y;

		button1[2].x = 7.8 * side / 108 * cos(Rad1) - (-51.2 * side / 108) * sin(Rad1) + center_x;
		button1[2].y = -51.2 * side / 108 * cos(Rad1) + 7.8 * side / 108 * sin(Rad1) + center_y;

		button1[3].x = 7.8 * side / 108 * cos(Rad1) - (-61.8 * side / 108) * sin(Rad1) + center_x;
		button1[3].y = -61.8 * side / 108 * cos(Rad1) + 7.8 * side / 108 * sin(Rad1) + center_y;

		button1[4].x = -7.8 * side / 108 * cos(Rad1) - (-61.8 * side / 108) * sin(Rad1) + center_x;
		button1[4].y = -61.8 * side / 108 * cos(Rad1) - 7.8 * side / 108 * sin(Rad1) + center_y;

		setlinewidth(side * 0.001);

		ege_drawpoly(5, button1);
	}

	if (GetAsyncKeyState(0x04) & 0x8000 && timestate == 0)
	{
		if (mouse_x_real <= center_x - side * 30 / 108 && mouse_x_real >= center_x - side * 50 / 108 && mouse_y_real <= center_y - side * 25 / 108 && mouse_y_real >= center_y - side * 50 / 108)
		{
			if (mod < 1)
				mod++;
			else if (mod == 1)
			{
				mod = -1;
				seconds = 0;
				minute3 = 0;
			}
			timestate = 1;
			moretime = fclock();
		}
	}
	timess = times;
}

//画精密计时器
void draw_Chronometer(double center_x, double center_y, double side)
{
	draw_ChronometerFrame(center_x, center_y, side);

	draw_Chronometer_buttons(center_x, center_y, side);

	draw_Chronometer_Scale(center_x, center_y, side);

	draw_Chronometer_time(center_x, center_y, side);

	timing(center_x, center_y, side);

	draw_Chronometer_text(center_x, center_y, side);

	check_mouse(center_x, center_y, side);

	//判断状态是否发生变化
	if (!(GetAsyncKeyState(0x04) & 0x8000)) {
		state = 0;
		timestate = 0;
	}
}