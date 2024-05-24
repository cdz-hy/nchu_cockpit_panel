#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>

extern double altitude;

//绘制STD

void draw_PFD_alt_STD(double side, double center_x, double center_y) {
	char STD[3] = { 'S','T','D' };
	double xSTD = center_x - 3.0 / 96.0 * side;
	double ySTD = center_y + 34.0 / 96.0 * side;
	
	double height = 16.0 / 3.0 / 96.0 * side;
	double wide = 8.0 / 3.0 / 96.0 * side;
	
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	setcolor(GREEN);
	for (int i = 0; i < 3;i++) {
		outtextxy(xSTD + i * side * 0.025, ySTD, STD[i]);
	}
	setcolor(WHITE);
}

//绘制横线及主显示器示数

void draw_PFD_alt_linesAndNum(double side, double center_x, double center_y) {
	
	setcolor(WHITE);
	//定出粗线的x坐标
	double x1 = center_x - 6.0 / 96.0 * side;
	double x2 = center_x - 3.0 / 96.0 * side;
	
	//定出细线的x坐标
	double x3 = center_x - 5.5 / 96.0 * side;
	double x4 = center_x - 3.5 / 96.0 * side;
	
	double ten = fmod(altitude, 100);
	
	double data4 = altitude - ten;
	int datas[8] = {};
	setlinewidth(side * 0.005);
	
	//计算出来了每条线的数据
	for (int i = 0;i < 8;i++) {
		datas[i] = (int)data4 + 100 * (i - 3);
	}
	int hun[8] = {};
	for (int i = 0;i < 8;i++) {
		hun[i] = datas[i] % 1000;
		hun[i] = hun[i] / 100;
	}
	char num[10] = { '0','1','2','3','4','5','6','7','8','9' };
	
	
	//计算出每条线之间的间隔
	double gap = 67.0 / 96.0 * side / 8.0;
	
	//计算数字相关参数
	double num_height = side * 0.055 * 1.15 * 0.7;
	double num_width = side * 2.5 / 96.0 * 0.85 * 0.7;
	
	//画线
	
	for (int i = 0;i < 8;i++) {
		
		double y = center_y - 33.5 / 96 * side + ten / 100 * gap + i * gap;//底部坐标 + 偏移坐标 + 循环坐标
		
		
		if (fmod(datas[7 - i], 500) == 0) {
			setlinewidth(side * 0.005);
			ege_line(x1, y, x2, y);
		}
		else
		{
			setlinewidth(side * 0.003);
			ege_line(x3, y, x4, y);
		}
		if (fmod(datas[7 - i], 1000) == 0) {
			setlinewidth(side * 0.002);
			ege_line(x2, y + num_height / 1.8, center_x + 6.0 / 96.0 * side, y + num_height / 1.8);
			ege_line(x2, y - num_height / 1.8, center_x + 6.0 / 96.0 * side, y - num_height / 1.8);
		}
	}
	
	
	//画00
	
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setfont(num_height, num_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	for (int i = 0;i < 8;i++) {
		double y = center_y - 33.5 / 96 * side + ten / 100 * gap + i * gap;//底部坐标 + 偏移坐标 + 循环坐标
		double x = center_x + 4.5 / 96 * side;
		int h = datas[i] / 100;
		
		ege_drawtext("0", x, y);
		x = x - num_width;
		ege_drawtext("0", x, y);
	}
	
	
	//画百位
	for (int i = 0;i < 8;i++) {
		double y = center_y - 33.5 / 96 * side + ten / 100 * gap + i * gap;//底部坐标 + 偏移坐标 + 循环坐标
		double x = center_x + 4.5 / 96 * side;
		x = x - 2 * num_width;
		
		char nums[64] = {};
		
		
		if (hun[7 - i] >= 0) {
			sprintf_s(nums, "%d", hun[7 - i]);
			ege_drawtext(nums, x, y);
		}
		else {
			sprintf_s(nums, "%d", -hun[7 - i]);
			ege_drawtext(nums, x, y);
			x = x - num_width;
			if (datas[7 - i] > -1000) {
				ege_drawtext("-", x, y);
			}
		}
		
	}
	//计算千位数字
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setfont(num_height * 1.2, num_width * 1.2, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	
	int thousand[8] = {};
	for (int i = 0;i < 8;i++) {
		thousand[i] = datas[i] % 10000;
		thousand[i] = thousand[i] / 1000;
	}
	
	for (int i = 0;i < 8;i++) {
		double y = center_y - 33.5 / 96 * side + ten / 100 * gap + i * gap;//底部坐标 + 偏移坐标 + 循环坐标
		double x = center_x + 4.5 / 96 * side;
		x = x - 3 * num_width * 1.05;
		
		char nums[64] = {};
		sprintf_s(nums, "%d", thousand[7 - i]);
		
		if (datas[7 - i] <= -1000 || datas[7 - i] >= 1000) {
			if (thousand[7 - i] >= 0) {
				ege_drawtext(nums, x, y);
			}
			else {
				sprintf_s(nums, "%d", -thousand[7 - i]);
				ege_drawtext(nums, x, y);
				x = x - num_width;
				if (datas[7 - i] <= -1000 && datas[7 - i] > -10000) {
					ege_drawtext("-", x, y);
				}
			}
		}
	}
	
	//计算万位
	int tenthousand[8] = {};
	for (int i = 0;i < 8;i++) {
		tenthousand[i] = datas[i] % 100000;
		tenthousand[i] = tenthousand[i] / 10000;
	}
	
	for (int i = 0;i < 8;i++) {
		double y = center_y - 33.5 / 96 * side + ten / 100 * gap + i * gap;//底部坐标 + 偏移坐标 + 循环坐标
		double x = center_x + 4.5 / 96 * side;
		x = x - 4 * num_width * 1.05;
		
		char nums[64] = {};
		sprintf_s(nums, "%d", tenthousand[7 - i]);
		
		if (datas[7 - i] <= -10000 || datas[7 - i] >= 10000) {
			if (thousand[7 - i] >= 0) {
				ege_drawtext(nums, x, y);
			}
			else {
				sprintf_s(nums, "%d", -tenthousand[7 - i]);
				ege_drawtext(nums, x, y);
				x = x - num_width;
				if (datas[7 - i] <= -1000 && datas[7 - i] > -10000) {
					ege_drawtext("-", x, y);
				}
			}
		}
	}
}

//绘制主显示的遮挡

void draw_PFD_alt_mainShadow(double side, double center_x, double center_y) {
	double num_height = side * 0.055 * 1.15 * 0.8;
	double frame_wide = side * 12 / 96;//底框的宽度
	double frame_height = side * 67 / 96;//底框的长度
	
	//左上角的坐标
	double frame_x = center_x + 29.0 / 96.0 * side - 29.0 / 96.0 * side - 5.5 / 96.0 * side;
	double frame_y = center_y - 33.5 / 96.0 * side;
	setfillcolor(BLACK);
	ege_fillrect(frame_x, frame_y + frame_height, frame_wide, num_height);
	ege_fillrect(frame_x, frame_y - num_height, frame_wide, num_height);
}

//滚轮的遮挡

void draw_PFD_alt10_shadow(double side, double center_x, double center_y) {
	setfillcolor(BLACK);
	double x = center_x + 7.0 / 96.0 * side;
	double y = center_y - side * 0.0335 - side * 0.0705 - side * 0.055 * 0.6;
	double wide = side * 2.5 / 96.0 * 0.85 * 2;
	double height = side * 0.055 * 1.6;
	ege_fillrect(x, y, wide, height);
	
	y = center_y + side * 0.049;
	ege_fillrect(x, y, wide, height);
}

//滚轮个位十位同步运动

void draw_PFD_alt10(double side, double center_x, double center_y) {
	
	double y = center_y - side * 0.0305;
	double x = center_x;
	
	double height = altitude;
	
	double number_height = side * 0.055 * 1.15;
	double number_width = side * 2.5 / 96.0 * 0.85;
	
	
	char num[] = { '6','8','0','2','4','6','8','0','2' };
	char zeros[] = { '0','0','0','0','0','0','0','0','0' };
	double usefulHeight10 = fmod(height, 100);//得到 （十 + 个）
	double uesfulHeight1 = fmod(height, 20);//得到个位
	
	
	int num2 = usefulHeight10 / 20 + 1;//准确的十位;
	int num1 = num2 - 1;//百位数 - 1；
	int num3 = num2 + 1;//百位数 + 1；
	int num0 = num2 - 2;
	int num4 = num3 + 1;
	
	//用于存储暂时有使用需求的数字
	char nums[5] = {};
	//将有用的字符存入；
	nums[0] = num[num0 + 1];
	nums[1] = num[num1 + 1];
	nums[2] = num[num2 + 1];
	nums[3] = num[num3 + 1];
	nums[4] = num[num4 + 1];
	//计算精细化坐标（加入十位和个位数字进行处理）
	double y_100 = uesfulHeight1 / 20.0 * number_height * 0.6 + y;
	//设定字体
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setfont(number_height, number_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	
	//将背景颜色设置成透明
	
	setbkmode(1);
	for (int i = 0;i < 5;i++) {
		outtextxy(x + 7.0 / 96.0 * side, y_100 + number_height * 0.6 * -(i - 2), nums[i]);
		outtextxy(x + 7.0 / 96.0 * side + number_width, y_100 + number_height * 0.6 * -(i - 2), zeros[i]);
	}
}

//百位

void draw_PFD_alt100(double side, double center_x, double center_y) {
	double y = center_y - side * 0.0305;
	double number_height = side * 0.055 * 1.15;
	double number_width = side * 2.5 / 96.0 * 0.85;
	double hun = fmod(altitude, 1000);
	
	hun = hun / 100;
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setfont(number_height, number_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	char num[12] = { '9','0','1','2','3','4','5','6','7','8','9','0' };
	
	outtextxy(center_x + number_width * 2.3, y, num[(int)hun + 1]);
}

//千位

void draw_PFD_alt1000(double side, double center_x, double center_y) {
	double y = center_y - side * 0.0345;
	double number_height = side * 0.055 * 1.3;
	double number_width = side * 2.5 / 96.0 * 0.85 * 1.3;
	double thousand = fmod(altitude, 10000);
	
	thousand = thousand / 1000;
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setfont(number_height, number_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	
	char num[12] = { '9','0','1','2','3','4','5','6','7','8','9','0' };
	
	outtextxy(center_x + number_width * 0.8, y, num[(int)thousand + 1]);
}

//绘制线框
//通过观察发现，上下两侧有阴影，后期考虑加入；

void draw_PFD_alt_wireframe(double side, double center_x, double center_y) {
	setcolor(WHITE);
	ege_enable_aa(true);
	setlinewidth(0.004 * side);
	
	double x1 = center_x + 31.5 / 96.0 * side - 29.0 / 96.0 * side - 5.5 / 96.0 * side;
	double y1 = center_y;
	
	double x2 = x1 + 1.7 / 96.0 * side;
	double y2 = center_y + 2 / 96.0 * side;
	
	double x3 = x2;
	double y3 = center_y - 2 / 96.0 * side;
	
	
	ege_point points[3]{
		{x1,y1},
		{x2,y2},
		{x3,y3}
	};
	
	ege_fillpoly(3, points);
	ege_line(x1, y1 - side * 0.001, x2 + side * 0.001, y2 - side * 0.001);
	ege_line(x1, y1 + side * 0.001, x3 + side * 0.001, y3 + side * 0.001);
	
	setcolor(WHITE);
	
	setfillcolor(BLACK);
	
	
	double x4 = x3;
	double y4 = center_y - 4.5 / 96.0 * side;
	
	double wide = 13.0 / 96.0 * side;
	double height = 9 / 96.0 * side;
	
	ege_fillrect(x4, y4, wide, height);
	
	ege_line(x3, y3 + side * 0.003, x4, y4 - side * 0.001);
	
	double x5 = x3;
	double y5 = center_y + 4.5 / 96.0 * side;
	
	ege_line(x2, y2 - side * 0.003, x5, y5 + side * 0.001);
	
	double x6 = x5 + wide;
	double y6 = y5;
	
	ege_line(x5, y5, x6, y6);
	
	double x7 = x5 + wide;
	double y7 = y4;
	
	ege_line(x4, y4, x7, y7);
	
	ege_line(x6, y6, x7, y7);
}

//绘制底盘

void draw_PFD_alt_frame(double side, double center_x, double center_y) {//画底盘
	double frame_wide = side * 12 / 96;//底框的宽度
	double frame_height = side * 67 / 96;//底框的长度
	
	//左上角的坐标
	double frame_x = center_x + 29.0 / 96.0 * side - 29.0 / 96.0 * side - 5.5 / 96.0 * side;
	double frame_y = center_y - 33.5 / 96.0 * side;
	
	setfillcolor(EGEARGB(0Xff, 0X12, 0X14, 0X13));
	//setfillcolor(WHITE);
	ege_fillrect(frame_x, frame_y, frame_wide, frame_height);
}

//绘制万位的斜线

void draw_PFD_alt_greenLines(double side, double center_x, double center_y) {
	double x_re = center_x - 0.15 / 96 * side;
	double y_re = center_y - side * 2 / 96;
	double wide = side * 2 / 96;
	double lenth = side * 4 / 96;
	ege_rect rect{
		x_re,y_re,wide,lenth
	};
	setfillcolor(GREEN);
	ege_fillrect(x_re, y_re, wide, lenth);
	
	//画出斜线
	double x0 = x_re;
	double x1 = x_re + wide / 4;
	double x2 = x_re + 2 * wide / 4;
	double x3 = x_re + 3 * wide / 4;
	double x4 = x_re + wide;
	
	double y0 = y_re;
	double y1 = y_re + lenth * 1.0 / 6.0;
	double y2 = y_re + lenth * 2.0 / 6.0;
	double y3 = y_re + lenth * 3.0 / 6.0;
	double y4 = y_re + lenth * 4.0 / 6.0;
	double y5 = y_re + lenth * 5.0 / 6.0;
	double y6 = y_re + lenth;
	
	setcolor(BLACK);
	setlinewidth(side * 0.002);
	//ege_line(x1, y0, x0, y1);
	
	ege_line(x1, y0, x0, y1);
	ege_line(x2, y0, x0, y2);
	ege_line(x3, y0, x0, y3);
	
	ege_line(x4, y0, x0, y4);
	ege_line(x4, y1, x0, y5);
	ege_line(x4, y2, x0, y6);
	
	ege_line(x4, y3, x1, y6);
	ege_line(x4, y4, x2, y6);
	ege_line(x4, y5, x3, y6);
}

//绘制万位数字

void draw_PFD_alt10000(double side, double center_x, double center_y) {
	double y = center_y - side * 0.0345;
	double number_height = side * 0.055 * 1.3;
	double number_width = side * 2.5 / 96.0 * 0.85 * 1.3;
	double tenThousand = fmod(altitude, 100000);
	
	tenThousand = tenThousand / 10000;
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setfont(number_height, number_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	
	char num[12] = { '9','0','1','2','3','4','5','6','7','8','9','0' };
	
	outtextxy(center_x - number_width * 0.25, y, num[(int)tenThousand + 1]);
}

//绘制主函数

void draw_PFD_alt( double center_x, double center_y, double side) {
	
	
	draw_PFD_alt_frame(side, center_x, center_y);//画底盘
	draw_PFD_alt_linesAndNum(side, center_x, center_y);//画线和数字
	draw_PFD_alt_mainShadow(side, center_x, center_y);
	
	draw_PFD_alt_wireframe(side, center_x, center_y);//画线框
	draw_PFD_alt10(side, center_x, center_y);
	draw_PFD_alt10_shadow(side, center_x, center_y);
	
	draw_PFD_alt_STD(side, center_x, center_y);
	draw_PFD_alt100(side, center_x, center_y);
	draw_PFD_alt1000(side, center_x, center_y);
	if (altitude < 10000) {
		draw_PFD_alt_greenLines(side, center_x, center_y);
	}
	else {
		draw_PFD_alt10000(side, center_x, center_y);
	}
}
