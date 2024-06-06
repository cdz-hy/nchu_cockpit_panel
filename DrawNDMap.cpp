#include<stdio.h>
#include<graphics.h>
#include<math.h>

extern double rotationangle;//表盘刻度的旋转角度
extern double ndtoprotationangle;//顶部三角形的偏转角度
double realrotationangle2 = 0;//实际的旋转角度
extern int ndcourse;
extern double course2;

//画刻度盘上的弧线
void draw_acr(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径

	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽

	ege_arc(center_x - r, center_y - r, r * 2, r * 2, -40.0, -100.0);
}

//画刻度
void draw_map_scale(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径

	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽

	//短刻度
	for (int i = 5; i < 360; i += 10)
	{
		double scaleAngle = realrotationangle2 + i;
		double rad = scaleAngle * PI / 180.0;
		double scalePosX = center_x + 0.975 * r * sin(rad);
		double scalePosY = center_y - 0.975 * r * cos(rad);

		if (scalePosX >= center_x - r * sin(55 * PI / 180) && scalePosX <= center_x + r * sin(55 * PI / 180) && scalePosY <= center_y - r * cos(55 * PI / 180) && scalePosY >= center_y - r) //判断文字是否在输出区域内，在区域内则输出，不在区域内则不输出
			ege_line(center_x + r * sin(rad), center_y - r * cos(rad), center_x + 0.975 * r * sin(rad), center_y - 0.975 * r * cos(rad));
	}

	//长刻度
	for (int i = 0; i < 360; i += 10)
	{
		double scaleAngle = realrotationangle2 + i;
		double rad = scaleAngle * PI / 180.0;
		double scalePosX = center_x + 0.975 * r * sin(rad);
		double scalePosY = center_y - 0.975 * r * cos(rad);

		if (scalePosX >= center_x - r * sin(55 * PI / 180) && scalePosX <= center_x + r * sin(55 * PI / 180) && scalePosY <= center_y - r * cos(55 * PI / 180) && scalePosY >= center_y - r) //判断文字是否在输出区域内，在区域内则输出，不在区域内则不输出
			ege_line(center_x + r * sin(rad), center_y - r * cos(rad), center_x + 0.96 * r * sin(rad), center_y - 0.96 * r * cos(rad));
	}
}

//画刻度值
void draw_ndtext(double center_x, double center_y, double side) {
	double r = side * 71 / 104;//表盘的半径

	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽

	for (int i = 0; i < 360; i += 30) //循环输出表上的刻度值
	{
		double textAngle = realrotationangle2 + i;
		double rad = textAngle * PI / 180.0;
		double textPosX = center_x + 0.92 * r * sin(rad);
		double textPosY = center_y - 0.92 * r * cos(rad);

		//设置文字的格式
		LOGFONTW font;
		setcolor(EGEARGB(0x99, 0xff, 0xff, 0xff));
		setfont(r * 0.09, 0, "Leelawadee");
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		getfont(&font);
		font.lfEscapement = -textAngle * 10;
		font.lfWeight = 500;
		setfont(&font);
#if 0
		xyprintf(compass_x + 0.8 * compass_r * cos(rad), compass_y - 0.8 * compass_r * sin(rad), "%d", i);
#endif
		if (textPosX >= center_x - r * sin(50 * PI / 180) && textPosX <= center_x + r * sin(55 * PI / 180) && textPosY <= center_y - r * cos(55 * PI / 180) && textPosY >= center_y - r) //判断文字是否在输出区域内，在区域内则输出，不在区域内则不输出
		{
			char strBuffer[64];
			sprintf_s(strBuffer, "%d", i / 10);
			ege_drawtext(strBuffer, textPosX, textPosY);
		}
	}
}

//画指向航向的固定指针
void draw_ndpoint(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径

	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽

	//画出指针
	ege_line(center_x, center_y, center_x, center_y - r - 3 * side / 104);
	ege_line(center_x - r * 0.02, center_y - r / 4, center_x + r * 0.02, center_y - r / 4);
	ege_line(center_x - r * 0.02, center_y - r / 2, center_x + r * 0.02, center_y - r / 2);
	ege_line(center_x - r * 0.02, center_y - r * 3 / 4, center_x + r * 0.02, center_y - r * 3 / 4);
}

//画表中间的一个三角形
void draw_ndcenterangle(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径

	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽

	//画表中间的一个三角形
	ege_point centerangle[4];

	centerangle[0].x = center_x;
	centerangle[0].y = center_y;

	centerangle[1].x = center_x - side * 3.5 / 104;
	centerangle[1].y = center_y + side * 8 / 104;

	centerangle[2].x = center_x + side * 3.5 / 104;
	centerangle[2].y = center_y + side * 8 / 104;

	centerangle[3].x = center_x;
	centerangle[3].y = center_y;

	ege_drawpoly(4, centerangle);
}

//画顶部会移动的三角形
void draw_ndtoptriangle(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径

	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽

	double rad = (ndtoprotationangle + realrotationangle2) * PI / 180;//将旋转角度化成弧度制

	if ((ndtoprotationangle + realrotationangle2) > 310 || (ndtoprotationangle + realrotationangle2) < 50) {
		//画顶部会移动的三角形
		ege_point toptriangle[4];

		toptriangle[0].x = r * sin(rad) + center_x;
		toptriangle[0].y = -r * cos(rad) + center_y;

		toptriangle[1].x = -side * 2 / 104 * cos(rad) + (r + side * 3 / 104) * sin(rad) + center_x;
		toptriangle[1].y = (-r - side * 3 / 104) * cos(rad) - side * 2 / 104 * sin(rad) + center_y;

		toptriangle[2].x = side * 2 / 104 * cos(rad) + (r + side * 3 / 104) * sin(rad) + center_x;
		toptriangle[2].y = (-r - side * 3 / 104) * cos(rad) + side * 2 / 104 * sin(rad) + center_y;

		toptriangle[3].x = r * sin(rad) + center_x;
		toptriangle[3].y = -r * cos(rad) + center_y;

		ege_drawpoly(4, toptriangle);
	}
}

//画顶部不闭合的矩形
void draw_ndtoprectangle(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径

	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽

	//画顶部不闭合的矩形
	ege_point toprectangle[4];

	toprectangle[0].x = center_x - 6.5 * side / 104;
	toprectangle[0].y = center_y - r - 9 * side / 104;

	toprectangle[1].x = center_x - 6.5 * side / 104;
	toprectangle[1].y = center_y - r - 3 * side / 104;

	toprectangle[2].x = center_x + 6.5 * side / 104;
	toprectangle[2].y = center_y - r - 3 * side / 104;

	toprectangle[3].x = center_x + 6.5 * side / 104;
	toprectangle[3].y = center_y - r - 9 * side / 104;

	ege_drawpoly(4, toprectangle);
}

//画顶部显示的文字内容
void draw_ndtoptext(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径

	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽

	//顶部中间的数字显示
	LOGFONTW font;
	setfont(r * 0.09, 0, "Leelawadee");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font);
	font.lfEscapement = 0;
	font.lfWeight = 550;
	setfont(&font);

	char stringBuffer[64];
	ndcourse = rotationangle;
	sprintf_s(stringBuffer, "%03d", ndcourse);
	ege_drawtext(stringBuffer, center_x, center_y - r - side * 6 / 104);

	//顶部左边的字母显示
	setfont(r * 0.07, 0, "Leelawadee");
	setcolor(EGEARGB(0x99, 0x75, 0xf9, 0x4d));
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font);
	font.lfEscapement = 0;
	font.lfWeight = 550;
	setfont(&font);
	ege_drawtext("TRK", center_x - side * 11 / 104, center_y - r - side * 6 / 104);

	//顶部右边的字母显示
	setfont(r * 0.07, 0, "Leelawadee");
	setcolor(EGEARGB(0x99, 0x75, 0xf9, 0x4d));
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font);
	font.lfEscapement = 0;
	font.lfWeight = 550;
	setfont(&font);
	ege_drawtext("MAG", center_x + side * 12 / 104, center_y - r - side * 6 / 104);
}

//画选定的航向
void draw_ndcourse(double compass_x, double compass_y, double side)
{
	double compass_r = side * 71 / 104;//表盘的半径

	//画指示标志
	setcolor(EGEARGB(0x99, 0xDE, 0x58, 0xC5));
	setlinewidth(compass_r * 0.007);
	ege_point graphics[22];

	double rad = (course2 + realrotationangle2) * PI / 180;

	if ((course2 + realrotationangle2) > 310 || (course2 + realrotationangle2) < 50) {
		graphics[0].x = -compass_r * sin(0.5 * PI / 180) * cos(rad) - (-compass_r * cos(0.5 * PI / 180) * sin(rad)) + compass_x;
		graphics[0].y = -compass_r * cos(0.5 * PI / 180) * cos(rad) - compass_r * sin(0.5 * PI / 180) * sin(rad) + compass_y;

		graphics[1].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.2 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 0.75 / 96) * sin(rad)) + compass_x;
		graphics[1].y = (-compass_r * cos(0.5 * PI / 180) - side * 0.75 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.2 / 96) * sin(rad) + compass_y;

		graphics[2].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.2 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 0.75 / 96) * sin(rad)) + compass_x;
		graphics[2].y = (-compass_r * cos(0.5 * PI / 180) - side * 0.75 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.2 / 96) * sin(rad) + compass_y;

		graphics[3].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.4 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[3].y = (-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.4 / 96) * sin(rad) + compass_y;

		graphics[4].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.6 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[4].y = (-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.6 / 96) * sin(rad) + compass_y;

		graphics[5].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.6 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[5].y = (-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.6 / 96) * sin(rad) + compass_y;

		graphics[6].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[6].y = (-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[7].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 0.7 / 96) * sin(rad)) + compass_x;
		graphics[7].y = (-compass_r * cos(0.5 * PI / 180) - side * 0.7 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[8].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 0.7 / 96) * sin(rad)) + compass_x;
		graphics[8].y = (-compass_r * cos(0.5 * PI / 180) - side * 0.7 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[9].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) + side * 0.1 / 96) * sin(rad)) + compass_x;
		graphics[9].y = (-compass_r * cos(0.5 * PI / 180) + side * 0.1 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[10].x = compass_r * sin(rad) + compass_x;
		graphics[10].y = -compass_r * cos(rad) + compass_y;

		graphics[11].x = compass_r * sin(rad) + compass_x;
		graphics[11].y = -compass_r * cos(rad) + compass_y;

		graphics[12].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) + side * 0.1 / 96) * sin(rad)) + compass_x;
		graphics[12].y = (-compass_r * cos(-0.5 * PI / 180) + side * 0.1 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[13].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 0.7 / 96) * sin(rad)) + compass_x;
		graphics[13].y = (-compass_r * cos(-0.5 * PI / 180) - side * 0.7 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[14].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 0.7 / 96) * sin(rad)) + compass_x;
		graphics[14].y = (-compass_r * cos(-0.5 * PI / 180) - side * 0.7 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[15].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[15].y = (-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[16].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.6 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[16].y = (-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.6 / 96) * sin(rad) + compass_y;

		graphics[17].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.6 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[17].y = (-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.6 / 96) * sin(rad) + compass_y;

		graphics[18].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.4 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[18].y = (-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.4 / 96) * sin(rad) + compass_y;

		graphics[19].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.2 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 0.75 / 96) * sin(rad)) + compass_x;
		graphics[19].y = (-compass_r * cos(-0.5 * PI / 180) - side * 0.75 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.2 / 96) * sin(rad) + compass_y;

		graphics[20].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.2 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 0.75 / 96) * sin(rad)) + compass_x;
		graphics[20].y = (-compass_r * cos(-0.5 * PI / 180) - side * 0.75 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.2 / 96) * sin(rad) + compass_y;

		graphics[21].x = (-compass_r * sin(-0.5 * PI / 180)) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180)) * sin(rad)) + compass_x;
		graphics[21].y = (-compass_r * cos(-0.5 * PI / 180)) * cos(rad) - (compass_r * sin(-0.5 * PI / 180)) * sin(rad) + compass_y;

		ege_bezier(22, graphics);
	}
}

//画MAP模式下的NP表
void draw_ND_map(double center_x, double center_y, double side)
{
	realrotationangle2 = 360 - rotationangle;

	draw_acr(center_x, center_y, side);

	draw_map_scale(center_x, center_y, side);

	draw_ndtext(center_x, center_y, side);

	draw_ndpoint(center_x, center_y, side);

	draw_ndcourse(center_x, center_y, side);

	draw_ndcenterangle(center_x, center_y, side);

	draw_ndtoptriangle(center_x, center_y, side);

	draw_ndtoprectangle(center_x, center_y, side);

	draw_ndtoptext(center_x, center_y, side);
}
