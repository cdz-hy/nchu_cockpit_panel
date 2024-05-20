# include <stdio.h>
# include <graphics.h>
# include <math.h>

extern double rotationangle;//罗盘上数字和刻度线旋转的角度
extern double pointrotationangle;//罗盘指针旋转的角度
extern int course;//罗盘指定的航向

//画罗盘的框架
void draw_compass_frame(double compass_x, double compass_y, double side)
{
	double compass_r = side * 30.5 / 96;//罗盘的半径

	ege_enable_aa(false);
	setcolor(EGEARGB(0Xff, 0X12, 0X14, 0X13));//罗盘外框线的颜色
	setlinewidth(2);//罗盘外框线的宽度
	ege_arc(compass_x - compass_r, compass_y - compass_r, 2 * compass_r, 2 * compass_r, -35.0, -110.0);//罗盘的弧线部分
	ege_line(compass_x - compass_r * sin(55 * PI / 180), compass_y - compass_r * cos(55 * PI / 180), compass_x + compass_r * sin(55 * PI / 180), compass_y - compass_r * cos(55 * PI / 180));//罗盘的直线部分
	setfillcolor(EGEARGB(0Xff, 0X12, 0X14, 0X13));//罗盘内部填充颜色
	floodfill(compass_x, compass_y - compass_r * cos(55 * PI / 180) - 10, EGEARGB(0Xff, 0X12, 0X14, 0X13));//填充罗盘内部

	ege_enable_aa(true);
}

//画航向指示
void draw_course_indication(double compass_x, double compass_y, double side)
{
	double compass_r = side * 30.5 / 96;//罗盘的半径
	setcolor(EGEARGB(0x99, 0xff, 0xff, 0xff));//设置线条颜色
	setlinewidth(compass_r * 0.01);//设置线条宽度

	ege_point triangle[4];//点类型结构体保存三角形个点坐标

	//第一个点
	triangle[0].x = compass_x;
	triangle[0].y = compass_y - compass_r;

	//第二个点
	triangle[1].x = compass_x - side * 2 / 96;
	triangle[1].y = compass_y - compass_r - side * 3 / 96;

	//第三个点
	triangle[2].x = compass_x + side * 2 / 96;
	triangle[2].y = compass_y - compass_r - side * 3 / 96;

	//首尾相接，第一个点
	triangle[3].x = compass_x;
	triangle[3].y = compass_y - compass_r;

	ege_drawpoly(4, triangle);//画三角形，指示当前航向
}

//画刻度
void draw_scale(double compass_x, double compass_y, double side)
{
	double compass_r = side * 30.5 / 96;//罗盘的半径
	setcolor(EGEARGB(0x99, 0xff, 0xff, 0xff));//设置线条颜色
	setlinewidth(compass_r * 0.01);//设置线条宽度
	//长刻度
	for (double i = 0; i < 360; i += 10)
	{
		double scaleAngle = rotationangle + i;
		double rad = scaleAngle * PI / 180.0;
		double scalePosX = compass_x + 0.96 * compass_r * sin(rad);
		double scalePosY = compass_y - 0.96 * compass_r * cos(rad);
		if (scalePosX >= compass_x - compass_r * sin(60 * PI / 180) && scalePosX <= compass_x + compass_r * sin(60 * PI / 180) && scalePosY <= compass_y - compass_r * cos(60 * PI / 180) && scalePosY >= compass_y - compass_r) //判断文字是否在输出区域内，在区域内则输出，不在区域内则不输出
		{
			ege_line(compass_x + compass_r * sin(rad), compass_y - compass_r * cos(rad), compass_x + 0.96 * compass_r * sin(rad), compass_y - 0.96 * compass_r * cos(rad));
		}
	}
	//短刻度
	for (double i = 5; i < 360; i += 10)
	{
		double scaleAngle = rotationangle + i;
		double rad = scaleAngle * PI / 180.0;
		double scalePosX = compass_x + 0.975 * compass_r * sin(rad);
		double scalePosY = compass_y - 0.975 * compass_r * cos(rad);
		if (scalePosX >= compass_x - compass_r * sin(60 * PI / 180) && scalePosX <= compass_x + compass_r * sin(60 * PI / 180) && scalePosY <= compass_y - compass_r * cos(60 * PI / 180) && scalePosY >= compass_y - compass_r) //判断文字是否在输出区域内，在区域内则输出，不在区域内则不输出
		{
			ege_line(compass_x + compass_r * sin(rad), compass_y - compass_r * cos(rad), compass_x + 0.975 * compass_r * sin(rad), compass_y - 0.975 * compass_r * cos(rad));
		}
	}
}

//画旋转的文字
void draw_compass_text(double compass_x, double compass_y, double side)
{
	double compass_r = side * 30.5 / 96;//罗盘的半径
	for (int i = 0; i < 360; i += 30) //循环输出表上的刻度值
	{
		double textAngle = rotationangle + i;
		double rad = textAngle * PI / 180.0;
		double textPosX = compass_x + 0.9 * compass_r * sin(rad);
		double textPosY = compass_y - 0.9 * compass_r * cos(rad);

		//设置文字的格式
		LOGFONTW font;
		setcolor(EGEARGB(0x99, 0xff, 0xff, 0xff));
		setfont(compass_r * 0.13, 0, "Leelawadee");
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		getfont(&font);
		font.lfEscapement = -textAngle * 10;
		font.lfWeight = 500;
		setfont(&font);
#if 0
		xyprintf(compass_x + 0.8 * compass_r * cos(rad), compass_y - 0.8 * compass_r * sin(rad), "%d", i);
#endif
		if (textPosX >= compass_x - compass_r * sin(60 * PI / 180) && textPosX <= compass_x + compass_r * sin(60 * PI / 180) && textPosY <= compass_y - compass_r * cos(60 * PI / 180) && textPosY >= compass_y - compass_r) //判断文字是否在输出区域内，在区域内则输出，不在区域内则不输出
		{
			char strBuffer[64];
			sprintf_s(strBuffer, "%d", i / 10);
			ege_drawtext(strBuffer, textPosX, textPosY);
		}
		setfillcolor(BLACK);
		ege_fillrect(compass_x - compass_r, compass_y - compass_r * cos(55 * PI / 180), compass_r * 2, compass_r * cos(55 * PI / 180) - compass_r * cos(64 * PI / 180));//遮盖部分
	}
}

//画指针
void draw_compass_point(double compass_x, double compass_y, double side) {
	double compass_r = side * 30.5 / 96;//罗盘的半径
	setcolor(EGEARGB(0x99, 0xff, 0xff, 0xff));//设置线条颜色
	setlinewidth(compass_r * 0.01);//设置线条宽度
	ege_line(compass_x + compass_r * cos(55 * PI / 180) * sin(pointrotationangle * PI / 180), compass_y - compass_r * cos(55 * PI / 180) * cos(pointrotationangle * PI / 180), compass_x + compass_r * sin(pointrotationangle * PI / 180), compass_y - compass_r * cos(pointrotationangle * PI / 180));//竖线部分
	ege_line(-side / 96 * cos(pointrotationangle * PI / 180) + compass_r * 0.7 * sin(pointrotationangle * PI / 180) + compass_x, -compass_r * 0.7 * cos(pointrotationangle * PI / 180) - side / 96 * sin(pointrotationangle * PI / 180) + compass_y, side / 96 * cos(pointrotationangle * PI / 180) + compass_r * 0.7 * sin(pointrotationangle * PI / 180) + compass_x, -compass_r * 0.7 * cos(pointrotationangle * PI / 180) + side / 96 * sin(pointrotationangle * PI / 180) + compass_y);
}

//画选定航向
void draw_course(double compass_x, double compass_y, double side) {
	double compass_r = side * 30.5 / 96;//罗盘的半径

	//设置文字的格式
	LOGFONTW font;
	setcolor(EGEARGB(0x99, 0xDE, 0x58, 0xC5));
	setfont(compass_r * 0.13, 0, "Leelawadee");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font);
	font.lfEscapement = 0;
	font.lfWeight = 500;
	setfont(&font);

	char strBuffer[64];
	sprintf_s(strBuffer, "%03d", course);
	ege_drawtext(strBuffer, compass_x - compass_r * 0.23, compass_y - compass_r * 0.63);

	//设置文字的格式
	setcolor(EGEARGB(0x99, 0xDE, 0x58, 0xC5));
	setfont(compass_r * 0.1, 0, "Leelawadee");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font);
	font.lfEscapement = 0;
	font.lfWeight = 500;
	setfont(&font);

	ege_drawtext("H", compass_x - compass_r * 0.1, compass_y - compass_r * 0.625);
}

//画MAG
void draw_MAG(double compass_x, double compass_y, double side) {
	double compass_r = side * 30.5 / 96;//罗盘的半径

	//设置文字的格式
	LOGFONTW font;
	setcolor(GREEN);
	setcolor(EGEARGB(0x99, 0x75, 0xf9, 0x4d));
	setfont(compass_r * 0.1, 0, "Leelawadee");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font);
	font.lfEscapement = 0;
	font.lfWeight = 500;
	setfont(&font);

	ege_drawtext("MAG", compass_x + compass_r * 0.35, compass_y - compass_r * 0.62);//画出MAG
}

//画整个罗盘
void draw_PFD_compass(double compass_x, double compass_y, double side)
{
	draw_compass_frame(compass_x, compass_y, side);

	draw_course_indication(compass_x, compass_y, side);

	draw_scale(compass_x, compass_y, side);

	draw_compass_point(compass_x, compass_y, side);

	draw_course(compass_x, compass_y, side);

	draw_MAG(compass_x, compass_y, side);

	draw_compass_text(compass_x, compass_y, side);
}
