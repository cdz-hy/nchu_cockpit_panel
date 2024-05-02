#include<graphics.h>
#include<math.h>
#include<Windows.h>
#include "DrawScrew.h"
#include "DrawFrame.h"
#include "DrawLight.h"


extern double MILLIBARS_data;
extern double INGH_data;
extern double altitude;

double angle_knob = 0;
//画背景（表底座）

double alt_angle_knob = 0;
double alt_angle_triangle = -PI / 2;
double alt_angle_BARO = 0;
double alt_is_down = 0;
int alt_mouse_x = 0;
int alt_mouse_y = 0;
int alt_mouse_x_cur = 0;
int alt_mouse_y_cur = 0;

double alignment = 0;//校准量

//画刻度

void alt_indicator_draw_scale(double x, double y, double side) {
	setcolor(WHITE);
	setlinewidth(side / 150);
	double R = side * 0.5;
	double r_outer = R - (R / 24);
	double small_r_inner = R * 376 / 434;
	double large_r_inner = R * 331 / 434;
	double small_r_outer = r_outer;
	double large_r_outer = r_outer;
	
	double number_r = R * 251 / 365;
	double number_height = R / 4;
	double number_width = R / 9;
	
	for (int i = 0; i < 10; i++) {//大刻度
		ege_line(x + (large_r_inner)*cos(PI / 2 + i * PI / 5), y + large_r_inner * sin(PI / 2 + i * PI / 5),
			x + large_r_outer * cos(PI / 2 + i * PI / 5), y + large_r_outer * sin(PI / 2 + i * PI / 5));
	}
	
	for (int i = 0; i < 50; i++) {//小刻度
		ege_line(x + (small_r_inner)*cos(PI / 2 + i * PI / 25), y + small_r_inner * sin(PI / 2 + i * PI / 25),
			x + small_r_outer * cos(PI / 2 + i * PI / 25), y + small_r_outer * sin(PI / 2 + i * PI / 25));
	}
}

//画刻度上的数字

void alt_indicator_draw_numbers(double x, double y, double side) {
	double R = 0.5 * side;
	
	//刻度相关参数
	
	double r_outer = R - (R / 24);
	double small_r_inner = R * 376 / 434;
	double large_r_inner = R * 331 / 434;
	double small_r_outer = r_outer;
	double large_r_outer = r_outer;
	
	double number_r = R * 251 / 365;
	double number_height = R / 4;
	double number_width = R / 9;
	
	settextjustify(CENTER_TEXT, CENTER_TEXT);//设定对齐方式；
	char num[10] = { '0','I','2','3','4','5','6','7','8','9' };
	setbkmode(TRANSPARENT);//设置文字背景色为透明;
	setfont(number_height, number_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	for (int i = 1;i <= 9;i++) {
		outtextxy(x + (number_r)*cos(i * PI / 5 - PI / 2), y + number_r * sin(i * PI / 5 - PI / 2), num[i]);
	}//绘制数字；
}

//画英语字符及“00”

void alt_indicator_draw_words(double x, double y, double side) {
	double R = 0.5 * side;
	//刻度相关参数
	
	double r_outer = R - (R / 24);
	double small_r_inner = R * 376 / 434;
	double large_r_inner = R * 331 / 434;
	double small_r_outer = r_outer;
	double large_r_outer = r_outer;
	
	double number_r = R * 251 / 365;
	double number_height = R / 4 * 1.2;
	double number_width = R / 9;
	//100的参数
	
	double height_100 = number_height / 2;
	double width_100 = number_width / 2;
	double x_100 = x - large_r_inner * sin(PI / 12) - 0.05 * R;
	double y_100 = y - large_r_inner * cos(PI / 12);
	
	//FT的参数
	
	double FT_height = height_100;
	double FT_width = width_100;
	double FT_x = x + large_r_inner * sin(PI / 12) + 0.05 * R;
	double FT_y = y - large_r_inner * cos(PI / 12);
	
	
	//字符ALT参数
	
	double ALT_height = R / 6;
	double ALT_width = R / 15;
	
	
	//MILLIBARS
	double MILLIBARS_height = R / 11;
	double MILLIBARS_width = R / 22;
	
	//INGH的相关参数；
	double INGH_height = R / 10;
	double INGH_width = R / 20;
	
	settextjustify(CENTER_TEXT, CENTER_TEXT);//设定对齐方式；
	char ALT[4] = "ALT";
	char MB[3] = "MB";
	char I_N[3] = "IN";
	char HG[3] = "HG";
	char MILLIBARS[10] = "MILLIBARS";
	char zero[3] = "00";
	setbkmode(TRANSPARENT);//设置文字背景色为透明;
	
	//绘制100
	setfont(height_100, width_100, "Calibri", 150, 150, 100, false, false, false);
	outtextxy(x_100, y_100, "I00");
	
	//绘制FT
	setfont(FT_height, FT_width, "Leelawadee", -150, -150, 100, false, false, false);
	outtextxy(FT_x, FT_y, "FT");
	
	//绘制ALT
	setfont(ALT_height, ALT_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	outtextxy(x + side * 12 / 80, y, ALT);
	
	//绘制MILLIBARS
	setfont(MILLIBARS_height, MILLIBARS_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	outtextxy(x + side * 0.1, y - side * 0.1, MILLIBARS);
	
	//绘制INGH
	setfont(INGH_height, INGH_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	outtextxy(x + side * 0.03, y + side * 0.22, I_N);
	outtextxy(x + side * 0.17, y + side * 0.22, HG);
	
	//绘制00
	setfont(number_height, number_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	outtextxy(x - side * 0.0001, y, zero);
}//画英文字母

//画内部框

void alt_indicator_draw_innerframes(double x, double y, double side) {
	double x1 = x - 0.415 * side;
	double y1 = y - 0.065 * side;
	
	ege_setpattern_none();//取消渐变填充
	
	
	setcolor(WHITE);
	ege_enable_aa(true);
	setlinewidth(side / 300);
	ege_rectangle(x1, y1, 0.4957 * side, 0.13 * side);
}//画内部框

//画指针

void alt_indicator_draw_pointer(double height, double x, double y, double side) {
	double alt_angle; // 定义指针初始角度
	//通过高度求角度；
	double num = fmod(height + alignment, 1000);
	double angle = 2 * PI * num / 1000 - PI / 2;
	alt_angle = angle;
	
	
	//半径
	double r = side * 0.008;
	//中心两点
	float x01 = x + r * cos(alt_angle + PI / 2);
	float y01 = y + r * sin(alt_angle + PI / 2);
	
	float x02 = x - r * cos(alt_angle + PI / 2);
	float y02 = y - r * sin(alt_angle + PI / 2);
	
	//杆与指针的连接点
	float x_collect1 = x + side * 0.315 * cos(alt_angle + PI * 0.007);
	float y_collect1 = y + side * 0.315 * sin(alt_angle + PI * 0.007);
	
	float x_collect2 = x + side * 0.315 * cos(alt_angle - PI * 0.007);
	float y_collect2 = y + side * 0.315 * sin(alt_angle - PI * 0.007);
	
	
	//远心点
	float x2 = x + side * 0.365 * cos(alt_angle);
	float y2 = y + side * 0.365 * sin(alt_angle);
	
	//近心偏点
	float x3 = x + side * 0.325 * cos(alt_angle + PI * 0.013);
	float y3 = y + side * 0.325 * sin(alt_angle + PI * 0.013);
	
	float x4 = x + side * 0.325 * cos(alt_angle - PI * 0.013);
	float y4 = y + side * 0.325 * sin(alt_angle - PI * 0.013);
	
	//远心偏点
	float x5 = x + side * 0.335 * cos(alt_angle + PI * 0.013);
	float y5 = y + side * 0.335 * sin(alt_angle + PI * 0.013);
	
	float x6 = x + side * 0.335 * cos(alt_angle - PI * 0.013);
	float y6 = y + side * 0.335 * sin(alt_angle - PI * 0.013);
	
	ege_point point[9] = {
		{x01 , y01},
		{x_collect1 , y_collect1},
		{x3 , y3},
		{x5 , y5},
		{x2 , y2},
		{x6 , y6},
		{x4 , y4},
		{x_collect2 ,y_collect2},
		{x02 , y02},
	};
	
	
	ege_setpattern_none();//取消渐变填充
	ege_enable_aa(true);
	
	//绘制中心圆
	setfillcolor(WHITE);
	ege_fillellipse(x - side * 0.008, y - side * 0.008, side * 0.016, side * 0.016);
	
	//绘制指针（多边形）
	ege_fillpoly(9, point);
	
}

//绘底面用阴影(打底)

void alt_shadow(double x, double y, double side) {
	//首先需要注意的是在只有百位可以显示在最上层
	//ege_setpattern_none();//取消渐变填充
	ege_setpattern_lineargradient(x + side * cos(PI / 4), y - side * sin(PI / 4), EGEARGB(0XFF, 0X15, 0X15, 0X15),
		x - side * cos(PI / 4), y + side * sin(PI / 4), EGEARGB(0XFF, 0X10, 0X10, 0X10));
	
	ege_enable_aa(true);
	//绘制一个矩形
	float x1 = x - (side * 0.18);
	float y1 = y - (side * 0.125);
	float wide = side * 0.1;
	float height = side * 0.25;
	setfillcolor(BLACK);
	ege_fillrect(x1, y1, wide, height);
	ege_setpattern_none();//取消渐变填充
	
}

//绘制主显示的数字(百位)；

void draw_MainDigitalDisplay100(double height, double x, double y, double side) {
	height += alignment;
	double R = 0.5 * side;
	
	//刻度相关参数
	
	double r_outer = R - (R / 24);
	double small_r_inner = R * 376 / 434;
	double large_r_inner = R * 331 / 434;
	double small_r_outer = r_outer;
	double large_r_outer = r_outer;
	
	double number_r = R * 251 / 365;
	double number_height = R / 4 * 1.2;
	double number_width = R / 9;
	
	char num[12] = { '9','0','I','2','3','4','5','6','7','8','9','0' };
	double usefulHeight100 = fmod(height, 1000);//得到的是百位及其以下的数字
	double uesfulHeight10 = fmod(height, 100);//得到的是十位及其以下的数字
	int num1 = usefulHeight100 / 100;//准确的百位数;
	int num2 = num1 - 1;//百位数 - 1；
	int num3 = num1 + 1;//百位数 + 1；
	
	//用于存储暂时有使用需求的数字
	char nums[3] = {};
	//将有用的字符存入；
	nums[0] = num[num2 + 1];
	nums[1] = num[num1 + 1];
	nums[2] = num[num3 + 1];
	//计算精细化坐标（加入十位和个位数字进行处理）
	double y_100 = uesfulHeight10 / 100 * number_height * 0.7 + y;
	//设定字体
	setfont(number_height, number_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	
	for (int i = 0;i < 3;i++) {
		outtextxy(x - side * 0.13, y_100 + number_height * 0.7 * -(i - 1), nums[i]);
	}
}

//绘制主显示的数字(千位)；

void draw_MainDigitalDisplay1000(double height, double x, double y, double side) {
	height += alignment;
	double R = 0.5 * side;
	
	//刻度相关参数
	
	double r_outer = R - (R / 24);
	double small_r_inner = R * 376 / 434;
	double large_r_inner = R * 331 / 434;
	double small_r_outer = r_outer;
	double large_r_outer = r_outer;
	
	double number_r = R * 251 / 365;
	double number_height = R / 4 * 1.2;
	double number_width = R / 9;
	
	setcolor(WHITE);
	char num[12] = { '9','0','I','2','3','4','5','6','7','8','9','0' };
	double usefulHeight1000 = fmod(height, 10000);//得到的是千位及其以下的数字
	double usefulHeight100 = fmod(height, 1000);//得到的是百位及其以下的数字
	setfillcolor(WHITE);
	int num1 = usefulHeight1000 / 1000;//准确的千位位数;
	int num2 = num1 - 1;//千位数 - 1；
	int num3 = num1 + 1;//千位数 + 1；
	//用于存储暂时有使用需求的数字
	char nums[3] = {};
	//将有用的字符存入；
	nums[0] = num[num2 + 1];
	nums[1] = num[num1 + 1];
	nums[2] = num[num3 + 1];
	
	//计算精细化坐标（加入十位和个位数字进行处理）
	double y_100 = (usefulHeight100 - 900) / 100 * number_height * 0.7 + y;
	//设定字体
	setfont(number_height, number_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	for (int i = 0;i < 3;i++) {
		if (usefulHeight100 > 900) {
			outtextxy(x - side * 0.25, y_100 + number_height * 0.7 * -(i - 1), nums[i]);
		}
		else {
			outtextxy(x - side * 0.25, y + number_height * 0.7 * -(i - 1), nums[i]);
		}
		
	}
}

//绘制主显示的数字（万位）

void draw_MainDigitalDisplay10000(double height, double x, double y, double side) {
	height += alignment;
	double R = 0.5 * side;
	
	//刻度相关参数
	
	double r_outer = R - (R / 24);
	double small_r_inner = R * 376 / 434;
	double large_r_inner = R * 331 / 434;
	double small_r_outer = r_outer;
	double large_r_outer = r_outer;
	
	double number_r = R * 251 / 365;
	double number_height = R / 4 * 1.2;
	double number_width = R / 9;
	
	char num[12] = { '9','0','I','2','3','4','5','6','7','8','9','0' };
	double usefulHeight10000 = fmod(height, 100000);//得到最高位万位及其以下数字
	double usefulHeight1000 = fmod(height, 10000);//得到的是千位及其以下的数字
	
	int num1 = usefulHeight10000 / 10000;//准确的万位位数;
	int num2 = num1 - 1;//万位数 - 1；
	int num3 = num1 + 1;//万位数 + 1；
	
	//用于存储暂时有使用需求的数字
	char nums[3] = {};
	//将有用的字符存入；
	nums[0] = num[num2 + 1];
	nums[1] = num[num1 + 1];
	nums[2] = num[num3 + 1];
	
	//计算精细化坐标（加入十位和个位数字进行处理）double y_100 = -(usefulHeight100 - 900)  / 100 * number_height + y;
	double y_1000 = (usefulHeight1000 - 9900) / 100 * number_height * 0.7 + y;
	//设定字体
	setfont(number_height, number_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	for (int i = 0;i < 3;i++) {
		
		if (usefulHeight1000 > 9900) {
			outtextxy(x - side * 0.35, y_1000 + number_height * 0.7 * -(i - 1), nums[i]);
		}
		else {
			outtextxy(x - side * 0.35, y + number_height * 0.7 * -(i - 1), nums[i]);
		}
	}
}

//绘制主显示用遮挡（百位用）

void alt_shadow100(double x, double y, double side) {
	//使用渐变填充
	ege_setpattern_lineargradient(x + side * cos(PI / 4), y - side * sin(PI / 4), EGEARGB(0XFF, 0X15, 0X15, 0X15),
		x - side * cos(PI / 4), y + side * sin(PI / 4), EGEARGB(0XFF, 0X10, 0X10, 0X10));
	
	float x1 = x - (side * 0.181);
	float y1 = y - (side * 0.35);
	float wide = side * 0.11;
	float height = side * 0.27;
	ege_fillrect(x1, y1, wide, height);
	
	float x2 = x1;
	float y2 = y + (side * 0.08);
	ege_fillrect(x2, y2, wide, height);
	ege_setpattern_none();
}

//绘制主显示用遮挡（千位用）

void alt_shadow1000(double x, double y, double side) {
	//使用渐变填充
	ege_setpattern_lineargradient(x + side * cos(PI / 4), y - side * sin(PI / 4), EGEARGB(0XFF, 0X15, 0X15, 0X15),
		x - side * cos(PI / 4), y + side * sin(PI / 4), EGEARGB(0XFF, 0X10, 0X10, 0X10));
	
	float x1 = x - side * 0.28;
	float y1 = y - side * 0.35;
	float wide = side * 0.1;
	float height = side * 0.285;
	ege_fillrect(x1, y1, wide, height);
	
	float x2 = x1;
	float y2 = y + (side * 0.065);
	ege_fillrect(x2, y2, wide, height);
	ege_setpattern_none();
}

//绘制主显示用遮挡（万位用）

void alt_shadow10000(double x, double y, double side) {
	//使用渐变填充
	ege_setpattern_lineargradient(x + side * cos(PI / 4), y - side * sin(PI / 4), EGEARGB(0XFF, 0X15, 0X15, 0X15),
		x - side * cos(PI / 4), y + side * sin(PI / 4), EGEARGB(0XFF, 0X10, 0X10, 0X10));
	
	float x1 = x - side * 0.4;
	float y1 = y - side * 0.3;
	float wide = side * 0.1;
	float height = side * 0.235;
	ege_fillrect(x1, y1, wide, height);
	
	float x2 = x1;
	float y2 = y + (side * 0.065);
	ege_fillrect(x2, y2, wide, height);
	ege_setpattern_none();
}

//绘制MILLIBARS的数字千位（1000）

void alt_MILLIBARSDisplay1000(double x, double y, double side) {
	double R = 0.5 * side;
	
	//刻度相关参数
	
	double r_outer = R - (R / 24);
	double small_r_inner = R * 376 / 434;
	double large_r_inner = R * 331 / 434;
	double small_r_outer = r_outer;
	double large_r_outer = r_outer;
	
	double number_r = R * 251 / 365;
	double number_height = R / 4;
	double number_width = R / 9;
	
	setcolor(WHITE);
	char num[12] = { '9','0','I','2','3','4','5','6','7','8','9','0' };
	double useful1000 = fmod(MILLIBARS_data, 10000);//得到的是千位及其以下的数字
	double useful100 = fmod(MILLIBARS_data, 1000);//得到的是百位及其以下的数字
	setfillcolor(WHITE);
	int num1 = useful1000 / 1000;//准确的千位位数;
	int num2 = num1 - 1;//千位数 - 1；
	int num3 = num1 + 1;//千位数 + 1；
	//用于存储暂时有使用需求的数字
	char nums[3] = {};
	//将有用的字符存入；
	nums[0] = num[num2 + 1];
	nums[1] = num[num1 + 1];
	nums[2] = num[num3 + 1];
	
	//计算精细化坐标（加入十位和个位数字进行处理）
	double y_100 = (useful100 - 999) / 1 * number_height * 0.9 + y - side * 0.15;
	setbkmode(OPAQUE);
	//设定字体
	setfont(number_height * 0.9, number_width * 0.9, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	for (int i = 0;i < 3;i++) {
		if (useful100 > 999) {
			outtextxy(x + side * 0.032, y_100 + number_height * -(i - 1) * 0.9, nums[i]);
		}
		else {
			outtextxy(x + side * 0.032, y - side * 0.15 + number_height * -(i - 1) * 0.9, nums[i]);
		}
		
	}
	
}

//绘制MILLIBARS的数字百位（100）

void alt_MILLIBARSDisplay100(double x, double y, double side) {
	double R = 0.5 * side;
	
	//刻度相关参数
	
	double r_outer = R - (R / 24);
	double small_r_inner = R * 376 / 434;
	double large_r_inner = R * 331 / 434;
	double small_r_outer = r_outer;
	double large_r_outer = r_outer;
	
	double number_r = R * 251 / 365;
	double number_height = R / 4;
	double number_width = R / 9;
	
	setcolor(WHITE);
	char num[12] = { '9','0','I','2','3','4','5','6','7','8','9','0' };
	double useful100 = fmod(MILLIBARS_data, 1000);//得到的是百位及其以下的数字
	double useful10 = fmod(MILLIBARS_data, 100);//得到的是十位及其以下的数字
	setfillcolor(WHITE);
	int num1 = useful100 / 100;//准确的百位数;
	int num2 = num1 - 1;//百位数 - 1；
	int num3 = num1 + 1;//百位数 + 1；
	//用于存储暂时有使用需求的数字
	char nums[3] = {};
	//将有用的字符存入；
	nums[0] = num[num2 + 1];
	nums[1] = num[num1 + 1];
	nums[2] = num[num3 + 1];
	
	//计算精细化坐标（加入十位和个位数字进行处理）
	double y_100 = (useful10 - 99) / 1 * number_height * 0.9 + y - side * 0.15;
	//设定字体
	setfont(number_height * 0.9, number_width * 0.9, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	for (int i = 0;i < 3;i++) {
		if (useful10 > 99) {
			outtextxy(x + side * 0.032 + number_width * 0.9, y_100 + number_height * 0.9 * -(i - 1), nums[i]);
		}
		else {
			outtextxy(x + side * 0.032 + number_width * 0.9, y - side * 0.15 + number_height * 0.9 * -(i - 1), nums[i]);
		}
	}
	
}

//绘制MILLIBARS的数字十位（10）

void alt_MILLIBARSDisplay10(double x, double y, double side) {
	
	double R = 0.5 * side;
	
	//刻度相关参数
	
	double r_outer = R - (R / 24);
	double small_r_inner = R * 376 / 434;
	double large_r_inner = R * 331 / 434;
	double small_r_outer = r_outer;
	double large_r_outer = r_outer;
	
	double number_r = R * 251 / 365;
	double number_height = R / 4;
	double number_width = R / 9;
	
	setcolor(WHITE);
	char num[12] = { '9','0','I','2','3','4','5','6','7','8','9','0' };
	double useful10 = fmod(MILLIBARS_data, 100);//得到的是百位及其以下的数字
	double useful1 = fmod(MILLIBARS_data, 10);//得到的是十位及其以下的数字
	setfillcolor(WHITE);
	int num1 = useful10 / 10;//准确的百位数;
	int num2 = num1 - 1;//千位数 - 1；
	int num3 = num1 + 1;//千位数 + 1；
	//用于存储暂时有使用需求的数字
	char nums[3] = {};
	//将有用的字符存入；
	nums[0] = num[num2 + 1];
	nums[1] = num[num1 + 1];
	nums[2] = num[num3 + 1];
	
	//计算精细化坐标（加入十位和个位数字进行处理）
	double y_100 = (useful1 - 9) / 1 * number_height * 0.9 + y - side * 0.15;
	//设定字体
	setfont(number_height * 0.9, number_width * 0.9, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	for (int i = 0;i < 3;i++) {
		if (useful1 > 9) {
			outtextxy(x + side * 0.032 + 2 * number_width * 0.9, y_100 + number_height * -(i - 1) * 0.9, nums[i]);
		}
		else {
			outtextxy(x + side * 0.032 + 2 * number_width * 0.9, y - side * 0.15 + number_height * -(i - 1) * 0.9, nums[i]);
		}
	}
}

//绘制MILLIBARS的数字个位（1）

void alt_MILLIBARSDisplay1(double x, double y, double side) {
	double R = 0.5 * side;
	
	//刻度相关参数
	
	double r_outer = R - (R / 24);
	double small_r_inner = R * 376 / 434;
	double large_r_inner = R * 331 / 434;
	double small_r_outer = r_outer;
	double large_r_outer = r_outer;
	
	double number_r = R * 251 / 365;
	double number_height = R / 4;
	double number_width = R / 9;
	
	setcolor(WHITE);
	char num[12] = { '9','0','I','2','3','4','5','6','7','8','9','0' };
	double useful1 = fmod(MILLIBARS_data, 10);//得到的是千位及其以下的数字
	double useful01 = fmod(MILLIBARS_data, 1);//得到的是百位及其以下的数字
	setfillcolor(WHITE);
	int num1 = useful1 / 1;//准确的千位位数;
	int num2 = num1 - 1;//千位数 - 1；
	int num3 = num1 + 1;//千位数 + 1；
	//用于存储暂时有使用需求的数字
	char nums[3] = {};
	//将有用的字符存入；
	nums[0] = num[num2 + 1];
	nums[1] = num[num1 + 1];
	nums[2] = num[num3 + 1];
	
	//计算精细化坐标（加入十位和个位数字进行处理）
	double y_100 = useful01 / 1 * number_height * 0.9 + y - side * 0.15;
	//设定字体
	setfont(number_height * 0.9, number_width * 0.9, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	for (int i = 0;i < 3;i++) {
		outtextxy(x + side * 0.032 + 3 * number_width * 0.9, y_100 + number_height * -(i - 1) * 0.9, nums[i]);
	}
}

//绘制INGH的数字千位（1000）

void alt_INGHDisplay1000(double x, double y, double side) {
	double data = INGH_data * 100;
	double R = 0.5 * side;
	
	//刻度相关参数
	
	double r_outer = R - (R / 24);
	double small_r_inner = R * 376 / 434;
	double large_r_inner = R * 331 / 434;
	double small_r_outer = r_outer;
	double large_r_outer = r_outer;
	
	double number_r = R * 251 / 365;
	double number_height = R / 4;
	double number_width = R / 9;
	
	setcolor(WHITE);
	char num[12] = { '9','0','I','2','3','4','5','6','7','8','9','0' };
	double useful1000 = fmod(data, 10000);//得到的是千位及其以下的数字
	double useful100 = fmod(data, 1000);//得到的是百位及其以下的数字
	setfillcolor(WHITE);
	int num1 = useful1000 / 1000;//准确的千位位数;
	int num2 = num1 - 1;//千位数 - 1；
	int num3 = num1 + 1;//千位数 + 1；
	//用于存储暂时有使用需求的数字
	char nums[3] = {};
	//将有用的字符存入；
	nums[0] = num[num2 + 1];
	nums[1] = num[num1 + 1];
	nums[2] = num[num3 + 1];
	
	//计算精细化坐标（加入十位和个位数字进行处理）
	double y_100 = (useful100 - 999) / 1 * number_height * 0.9 + y + side * 0.17;
	//设定字体
	setfont(number_height * 0.9, number_width * 0.9, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	for (int i = 0;i < 3;i++) {
		if (useful100 > 999) {
			outtextxy(x + side * 0.032, y_100 + number_height * -(i - 1) * 0.9, nums[i]);
		}
		else {
			outtextxy(x + side * 0.032, y + side * 0.17 + number_height * -(i - 1) * 0.9, nums[i]);
		}
		
	}
	
}

//绘制INGH的数字百位（100）

void alt_INGHDisplay100(double x, double y, double side) {
	double data = INGH_data * 100;
	double R = 0.5 * side;
	
	//刻度相关参数
	
	double r_outer = R - (R / 24);
	double small_r_inner = R * 376 / 434;
	double large_r_inner = R * 331 / 434;
	double small_r_outer = r_outer;
	double large_r_outer = r_outer;
	
	double number_r = R * 251 / 365;
	double number_height = R / 4;
	double number_width = R / 9;
	
	setcolor(WHITE);
	char num[12] = { '9','0','I','2','3','4','5','6','7','8','9','0' };
	double useful100 = fmod(data, 1000);//得到的是百位及其以下的数字
	double useful10 = fmod(data, 100);//得到的是十位及其以下的数字
	setfillcolor(WHITE);
	int num1 = useful100 / 100;//准确的百位数;
	int num2 = num1 - 1;//百位数 - 1；
	int num3 = num1 + 1;//百位数 + 1；
	//用于存储暂时有使用需求的数字
	char nums[3] = {};
	//将有用的字符存入；
	nums[0] = num[num2 + 1];
	nums[1] = num[num1 + 1];
	nums[2] = num[num3 + 1];
	
	//计算精细化坐标（加入十位和个位数字进行处理）
	double y_100 = (useful10 - 99) / 1 * number_height * 0.9 + y + side * 0.17;
	//设定字体
	setfont(number_height * 0.9, number_width * 0.9, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	for (int i = 0;i < 3;i++) {
		if (useful10 > 99) {
			outtextxy(x + side * 0.032 + number_width * 0.9, y_100 + number_height * 0.9 * -(i - 1), nums[i]);
		}
		else {
			outtextxy(x + side * 0.032 + number_width * 0.9, y + side * 0.17 + number_height * 0.9 * -(i - 1), nums[i]);
		}
		
	}
	
}

//绘制INGH的数字十位（10）

void alt_INGHDisplay10(double x, double y, double side) {
	double data = INGH_data * 100;
	double R = 0.5 * side;
	
	//刻度相关参数
	
	double r_outer = R - (R / 24);
	double small_r_inner = R * 376 / 434;
	double large_r_inner = R * 331 / 434;
	double small_r_outer = r_outer;
	double large_r_outer = r_outer;
	
	double number_r = R * 251 / 365;
	double number_height = R / 4;
	double number_width = R / 9;
	
	setcolor(WHITE);
	char num[12] = { '9','0','I','2','3','4','5','6','7','8','9','0' };
	double useful10 = fmod(data, 100);//得到的是百位及其以下的数字
	double useful1 = fmod(data, 10);//得到的是十位及其以下的数字
	setfillcolor(WHITE);
	int num1 = useful10 / 10;//准确的百位数;
	int num2 = num1 - 1;//千位数 - 1；
	int num3 = num1 + 1;//千位数 + 1；
	//用于存储暂时有使用需求的数字
	char nums[3] = {};
	//将有用的字符存入；
	nums[0] = num[num2 + 1];
	nums[1] = num[num1 + 1];
	nums[2] = num[num3 + 1];
	
	//计算精细化坐标（加入十位和个位数字进行处理）
	double y_100 = (useful1 - 9) / 1 * number_height * 0.9 + y + side * 0.17;
	//设定字体
	setfont(number_height * 0.9, number_width * 0.9, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	for (int i = 0;i < 3;i++) {
		if (useful1 > 9) {
			outtextxy(x + side * 0.032 + 2 * number_width * 0.9, y_100 + number_height * -(i - 1) * 0.9, nums[i]);
		}
		else {
			outtextxy(x + side * 0.032 + 2 * number_width * 0.9, y + side * 0.17 + number_height * -(i - 1) * 0.9, nums[i]);
		}
		
	}
	
}

//绘制INGH的数字个位（1）

void alt_INGHDisplay1(double x, double y, double side) {
	double data = INGH_data * 100;
	double R = 0.5 * side;
	
	//刻度相关参数
	
	double r_outer = R - (R / 24);
	double small_r_inner = R * 376 / 434;
	double large_r_inner = R * 331 / 434;
	double small_r_outer = r_outer;
	double large_r_outer = r_outer;
	
	double number_r = R * 251 / 365;
	double number_height = R / 4;
	double number_width = R / 9;
	
	setcolor(WHITE);
	char num[12] = { '9','0','I','2','3','4','5','6','7','8','9','0' };
	double useful1 = fmod(data, 10);//得到的是千位及其以下的数字
	double useful01 = fmod(data, 1);//得到的是百位及其以下的数字
	setfillcolor(WHITE);
	int num1 = useful1 / 1;//准确的千位位数;
	int num2 = num1 - 1;//千位数 - 1；
	int num3 = num1 + 1;//千位数 + 1；
	//用于存储暂时有使用需求的数字
	char nums[3] = {};
	//将有用的字符存入；
	nums[0] = num[num2 + 1];
	nums[1] = num[num1 + 1];
	nums[2] = num[num3 + 1];
	
	//计算精细化坐标（加入十位和个位数字进行处理）
	double y_100 = useful01 / 1 * number_height * 0.9 + y + side * 0.17;
	//设定字体
	setfont(number_height * 0.9, number_width * 0.9, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	for (int i = 0;i < 3;i++) {
		outtextxy(x + side * 0.032 + 3 * number_width * 0.9, y_100 + number_height * -(i - 1) * 0.9, nums[i]);
	}
	
}

//绘制副显示器的遮挡

void alt_shadow_MILLIBARS(double x, double y, double side) {
	ege_setpattern_lineargradient(x + side * cos(PI / 4), y - side * sin(PI / 4), EGEARGB(0XFF, 0X15, 0X15, 0X15),
		x - side * cos(PI / 4), y + side * sin(PI / 4), EGEARGB(0XFF, 0X10, 0X10, 0X10));
	
	//setfillcolor(BLACK);//调试用
	
	double x1 = x + side * 0.002;
	double y1 = y - side * 0.432;
	double lenth = side * 0.207;
	double wide = side * 0.247;
	ege_fillrect(x1, y1, lenth, wide);
	double y2 = y - side * 0.11;
	double wide2 = side * 0.24;
	ege_fillrect(x1, y2, lenth, wide2);
	
	double y3 = y + side * 0.21;
	ege_fillrect(x1, y3, lenth, wide);
	ege_setpattern_none();
}

//绘制几个点

void draw_dots(double x, double y, double side) {
	//相当于画一个填充圆
	ege_setpattern_none();
	setfillcolor(WHITE);
	
	//主显示的点
	
	ege_fillellipse(x - side * 0.2, y + side * 0.035, side * 0.023, side * 0.023);
	
	double x1 = x + side * 0.105;
	double y1 = y + side * 0.18;
	
	double x2 = x + side * 0.095;
	double y2 = y + side * 0.2;
	
	double x3 = x + side * 0.115;
	double y3 = y + side * 0.2;
	
	ege_point points[3]{
		{x1,y1},
		{x2,y2},
		{x3,y3},
	};
	setfillcolor(LIGHTGRAY);
	//INGH的三角形
	ege_fillpoly(3, points);
}

//绘制所有装饰片

void draw_decoration(double x, double y, double side) {
	
	setlinewidth(side / 250);
	
	
	double x1 = x - (side / 2) * cos(PI * 13 / 100);
	double y1 = y - (side / 2) * sin(PI * 13 / 100);
	
	double x2 = x - (side / 2) * cos(PI * 16 / 100);
	double y2 = y - (side / 2) * sin(PI * 16 / 100);
	
	double x3 = x - (side / 2) * cos(PI * 20 / 100);
	double y3 = y - (side / 2) * sin(PI * 20 / 100);
	
	double x4 = x - (side / 2) * cos(PI * 24 / 100);
	double y4 = y - (side / 2) * sin(PI * 24 / 100);
	
	double x5 = x - (side / 2) * cos(PI * 28 / 100);
	double y5 = y - (side / 2) * sin(PI * 28 / 100);
	
	double x6 = x - (side / 2) * cos(PI * 32 / 100);
	double y6 = y - (side / 2) * sin(PI * 32 / 100);
	
	double x7 = x - (side / 2) * cos(PI * 37 / 100);
	double y7 = y - (side / 2) * sin(PI * 37 / 100);
	
	//左下点
	
	double x8 = x - side / 2 * 1.05;
	double y8 = y - side * 0.25;
	
	//左上点
	
	double x9 = x - side / 2 * 1.05;
	double y9 = y - side * 0.38;
	
	double x10 = x - side * 0.38;
	double y10 = y - side / 2 * 1.05;
	
	double x11 = x - side * 0.25;
	double y11 = y - side / 2 * 1.05;
	
	ege_point point[7]{
		{x1,y1},
		{x2,y2},
		{x3,y3},
		{x4,y4},
		{x5,y5},
		{x6,y6},
		{x7,y7}
	};
	
	setcolor(BLACK);
	
	setfillcolor(EGEARGB(0xff, 0x20, 0x20, 0x20));
	
	ege_enable_aa(false);
	ege_bezier(7, point);
	ege_line(x1, y1, x8, y8);
	ege_line(x8, y8, x9, y9);
	ege_line(x9, y9, x10, y10);
	ege_line(x10, y10, x11, y11);
	ege_line(x11, y11, x7, y7);
	floodfill((x1 + x9) / 2, (y1 + y9) / 2, BLACK);
	
	x1 = x + (side / 2) * cos(PI * 13 / 100);
	y1 = y - (side / 2) * sin(PI * 13 / 100);
	
	x2 = x + (side / 2) * cos(PI * 16 / 100);
	y2 = y - (side / 2) * sin(PI * 16 / 100);
	
	x3 = x + (side / 2) * cos(PI * 20 / 100);
	y3 = y - (side / 2) * sin(PI * 20 / 100);
	
	x4 = x + (side / 2) * cos(PI * 24 / 100);
	y4 = y - (side / 2) * sin(PI * 24 / 100);
	
	x5 = x + (side / 2) * cos(PI * 28 / 100);
	y5 = y - (side / 2) * sin(PI * 28 / 100);
	
	x6 = x + (side / 2) * cos(PI * 32 / 100);
	y6 = y - (side / 2) * sin(PI * 32 / 100);
	
	x7 = x + (side / 2) * cos(PI * 37 / 100);
	y7 = y - (side / 2) * sin(PI * 37 / 100);
	
	//左下点
	
	x8 = x + side / 2 * 1.05;
	y8 = y - side * 0.25;
	
	//左上点
	
	x9 = x + side / 2 * 1.05;
	y9 = y - side * 0.38;
	
	x10 = x + side * 0.38;
	y10 = y - side / 2 * 1.05;
	
	x11 = x + side * 0.25;
	y11 = y - side / 2 * 1.05;
	
	ege_point points[7]{
		{x1,y1},
		{x2,y2},
		{x3,y3},
		{x4,y4},
		{x5,y5},
		{x6,y6},
		{x7,y7}
	};
	setcolor(BLACK);
	setfillcolor(EGEARGB(0xff, 0x20, 0x20, 0x20));
	ege_bezier(7, points);
	
	ege_line(x1, y1, x8, y8);
	ege_line(x8, y8, x9, y9);
	ege_line(x9, y9, x10, y10);
	ege_line(x10, y10, x11, y11);
	ege_line(x11, y11, x7, y7);
	floodfill((x1 + x9) / 2, (y1 + y9) / 2, BLACK);
	
	ege_enable_aa(true);
	
	//表盘外螺丝
	draw_screw(x - side * 0.5, y - side * 0.5, 0.04 * side, PI / 1);
	draw_screw(x + side * 0.5, y + side * 0.5, 0.04 * side, PI / 2);
	draw_screw(x - side * 0.5, y + side * 0.5, 0.04 * side, PI / 3);
	draw_screw(x + side * 0.5, y - side * 0.5, 0.04 * side, PI / 4);
	
	//表盘上靠下的螺丝；
	
	draw_screw(x - side * 0.47, y - side * 0.32, 0.045 * side, PI / 3);
	draw_screw(x + side * 0.47, y - side * 0.32, 0.045 * side, PI / 4);
	
	//表盘上的螺丝；
	draw_screw(x - side * 0.33, y - side * 0.47, 0.045 * side, PI / 7);
	draw_screw(x + side * 0.33, y - side * 0.47, 0.045 * side, PI / 2);
	
}

//绘制旋钮

void alt_draw_knob(double x, double y, double side) {
	double x1 = x + side * 0.5 * 0.67;
	double y1 = y + side * 0.5 * 0.67;
	
	double r = side * 0.15;
	ege_setpattern_none();
	setfillcolor(EGEARGB(255, 19, 19, 20));
	for (int i = 0;i < 10; i++) {
		if (i == 9) {
			setfillcolor(EGEARGB(255, 29, 29, 31));
		}
		ege_fillellipse(x1 + i * side * 0.005, y1 + i * side * 0.005, r, r);
	}
	
	double x2 = x - side * 0.5 * 0.95;
	setfillcolor(EGEARGB(255, 19, 19, 20));
	for (int i = 0;i < 10; i++) {
		if (i == 9) {
			setfillcolor(EGEARGB(255, 29, 29, 31));
		}
		ege_fillellipse(x2 + i * side * 0.005, y1 + i * side * 0.005, r, r);
	}
	
	//寻找中心坐标
	double x_center = x1 + 9 * side * 0.005 + 0.5 * r;
	double y_center = y1 + 9 * side * 0.005 + 0.5 * r;
	
	//三角形的绘制
	double trianglex1 = x_center + 0.5 * r * cos(alt_angle_knob) * 0.8;
	double triangley1 = y_center + 0.5 * r * sin(alt_angle_knob) * 0.8;
	
	double trianglex2 = x_center + 0.5 * r * cos(alt_angle_knob + 2 * PI / 3) * 0.8;
	double triangley2 = y_center + 0.5 * r * sin(alt_angle_knob + 2 * PI / 3) * 0.8;
	
	double trianglex3 = x_center + 0.5 * r * cos(alt_angle_knob + 4 * PI / 3) * 0.8;
	double triangley3 = y_center + 0.5 * r * sin(alt_angle_knob + 4 * PI / 3) * 0.8;
	
	ege_point points1[3]{
		{trianglex1,triangley1},
		{trianglex2,triangley2},
		{trianglex3,triangley3}
	};
	setfillcolor(RED);
	ege_fillpoly(3, points1);
	
	double x2_center = x2 + 9 * side * 0.005 + 0.5 * r;
	double y2_center = y1 + 9 * side * 0.005 + 0.5 * r;
	int alt_x_mouse;
	int alt_y_mouse;
	
	mousepos(&alt_x_mouse, &alt_y_mouse);
	setcolor(WHITE);
	setlinewidth(side * 0.0001);
	if (((alt_x_mouse - x_center) * (alt_x_mouse - x_center) + (alt_y_mouse - y_center) * (alt_y_mouse - y_center) <= r / 2 * r / 2)) {
		ege_ellipse(x_center - r / 2, y_center - r / 2, r, r);
	}
	else if (((alt_x_mouse - x2_center) * (alt_x_mouse - x2_center) + (alt_y_mouse - y2_center) * (alt_y_mouse - y2_center) <= r / 2 * r / 2)) {
		ege_ellipse(x2_center - r / 2, y2_center - r / 2, r, r);
	}
	mouse_msg msgRecord = { 0 };
	
	char BARO[5] = "BARO";
	double x_BARO = x2_center - r / 2 * cos(alt_angle_BARO);
	double y_BARO = y2_center - r / 2 * cos(alt_angle_BARO);
	
	//用于BARO
	
	double angle = alt_angle_BARO * 180 / PI;
	setfont(r / 4, r / 4, "黑体", angle, 0, 1000, 0, 0, 0);
	ege_enable_aa(true);
	LOGFONTW font;
	setfont(r / 2 * 0.7, r / 2 * 0.7, "Leelawadee", -angle * 10, 0, 1000, 0, 0, 0);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font);
	char stringbuffer[64] = "BARO";
	ege_drawtext(stringbuffer, x2_center, y2_center);
}

//绘制显示小三角

void alt_draw_triangle(double x, double y, double side) {
	setfillcolor(RED);
	
	double x1 = x + side / 2 * cos(alt_angle_triangle) * 0.85;
	double y1 = y + side / 2 * sin(alt_angle_triangle) * 0.85;
	
	double x2 = x + side / 2 * cos(alt_angle_triangle + PI / 50) * 0.97;
	double y2 = y + side / 2 * sin(alt_angle_triangle + PI / 50) * 0.97;
	
	double x3 = x + side / 2 * cos(alt_angle_triangle - PI / 50) * 0.97;
	double y3 = y + side / 2 * sin(alt_angle_triangle - PI / 50) * 0.97;
	
	ege_point points[3]{
		{x1,y1},
		{x2,y2},
		{x3,y3}
	};
	ege_fillpoly(3, points);
	
}

//接收鼠标信息

void alt_indicator_msg(double x, double y, double side)
{
	double r = side * 0.15;
	double x1 = x + side * 0.5 * 0.67;
	double y1 = y + side * 0.5 * 0.67;
	double x2 = x - side * 0.5 * 0.95;
	//寻找旋钮的中心坐标
	double x_center = x1 + 9 * side * 0.005 + 0.5 * r;
	double y_center = y1 + 9 * side * 0.005 + 0.5 * r;
	double x2_center = x2 + 9 * side * 0.005 + 0.5 * r;
	double y2_center = y1 + 9 * side * 0.005 + 0.5 * r;
	
	setcolor(WHITE);
	if (GetAsyncKeyState(0x02) & 0x8000) {
		if (alt_is_down == 0) {
			alt_is_down = 1;
			mousepos(&alt_mouse_x_cur, &alt_mouse_y_cur);
			alt_mouse_x = alt_mouse_x_cur;
			alt_mouse_y = alt_mouse_y_cur;
		}
		if (alt_is_down == 1) {
			if (((alt_mouse_x - x_center) * (alt_mouse_x - x_center) + (alt_mouse_y - y_center) * (alt_mouse_y - y_center) <= r / 2 * r / 2)) {
				mousepos(&alt_mouse_x_cur, &alt_mouse_y_cur);
				if (alt_mouse_y > alt_mouse_y_cur) {
					alt_angle_triangle -= (double)(alt_mouse_y - alt_mouse_y_cur) / (70 * 180 / PI);
					alt_angle_knob -= (double)(alt_mouse_y - alt_mouse_y_cur) / (70 * 180 / PI);
				}
				else if (alt_mouse_y < alt_mouse_y_cur) {
					alt_angle_triangle -= (double)(alt_mouse_y - alt_mouse_y_cur) / (70 * 180 / PI);
					alt_angle_knob -= (double)(alt_mouse_y - alt_mouse_y_cur) / (70 * 180 / PI);
				}
			}
			else if (((alt_mouse_x - x2_center) * (alt_mouse_x - x2_center) + (alt_mouse_y - y2_center) * (alt_mouse_y - y2_center) <= r / 2 * r / 2)) {
				mousepos(&alt_mouse_x_cur, &alt_mouse_y_cur);
				if (alt_mouse_y > alt_mouse_y_cur) {
					alignment += (double)(alt_mouse_y - alt_mouse_y_cur) / 10;
					alt_angle_BARO += (double)(alt_mouse_y - alt_mouse_y_cur) / (70 * 180 / PI);
				}
				else if (alt_mouse_y < alt_mouse_y_cur) {
					alignment += (double)(alt_mouse_y - alt_mouse_y_cur) / 10;
					alt_angle_BARO += (double)(alt_mouse_y - alt_mouse_y_cur) / (70 * 180 / PI);
				}
			}
		}
	}
	else if (alt_is_down == 1) {
		alt_is_down = 0;
	}
}

//绘制的主函数

void draw_alt(double x, double y, double side) {
	side = side * 13 / 14;
	double height;
	if (altitude > 0) {
		height = altitude;
	}
	else {
		height = 100000 + altitude;
	}
	draw_frame(x, y, side); //画表盘；
	
	draw_MainDigitalDisplay1000(height, x, y, side);//绘制主显示器的数字（千位）
	alt_shadow1000(x, y, side);//绘制主显示用遮挡（千位用）
	draw_MainDigitalDisplay10000(height, x, y, side);//绘制主显示器的数字（万位）
	alt_shadow10000(x, y, side);//绘制主显示用遮挡（万位用）
	
	
	alt_MILLIBARSDisplay1000(x, y, side);//用于MILLIBARS表的1000位置
	alt_MILLIBARSDisplay100(x, y, side);//用于MILLIBARS表的100位置
	alt_MILLIBARSDisplay10(x, y, side);//用于MILLIBARS表的10位置
	alt_MILLIBARSDisplay1(x, y, side);//用于MILLIBARS表的1位置
	
	alt_INGHDisplay1000(x, y, side);//用于MILLIBARS表的1000位置
	alt_INGHDisplay100(x, y, side);//用于MILLIBARS表的100位置
	alt_INGHDisplay10(x, y, side);//用于MILLIBARS表的10位置
	alt_INGHDisplay1(x, y, side);//用于MILLIBARS表的1位置
	
	
	alt_shadow_MILLIBARS(x, y, side);//用于MILLIBARS表的遮挡
	
	alt_indicator_draw_scale(x, y, side); //画刻度
	alt_indicator_draw_numbers(x, y, side);//画刻度数字
	
	alt_indicator_draw_innerframes(x, y, side);//画内部框
	
	alt_shadow(x, y, side);//百位底层遮挡
	draw_MainDigitalDisplay100(height, x, y, side);//绘制主显示器的数字（百位）
	alt_shadow100(x, y, side);//绘制主显示用遮挡（百位用）
	alt_indicator_draw_words(x, y, side);//画英语字体
	draw_dots(x, y, side);//绘制几个点（装饰）
	alt_indicator_draw_pointer(height, x, y, side);//画指针；
	
	draw_decoration(x, y, side);//绘制螺丝和装饰片	
	
	alt_draw_knob(x, y, side);//绘制旋钮
	
	alt_draw_triangle(x, y, side);//绘制小三角
	
	alt_indicator_msg(x, y, side);//获取鼠标消息
	
	draw_light(x, y, side / 2);//光照效果
}
