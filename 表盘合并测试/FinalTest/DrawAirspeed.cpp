#include<graphics.h>
#include<math.h>
#include<Windows.h>
#include "DrawScrew.h"
#include "DrawLight.h"

extern double airSpeed;

double commandbug_angle = 0;
double knob_angle = 0;

extern int G_light;

int mouse_x_cur = 0, mouse_y_cur = 0, mouse_x = 0, mouse_y = 0;
int airspeed_is_down = 0;

double small_pointer_angle1 = 0;
double small_pointer_angle2 = 0;
double small_pointer_angle3 = 0;

double airspeed_is_down1 = 0;
int mouse_x1 = 0, mouse_y1 = 0, mouse_x_cur1 = 0, mouse_y_cur1 = 0;
double airspeed_is_down2 = 0;
int mouse_x2 = 0, mouse_y2 = 0, mouse_x_cur2 = 0, mouse_y_cur2 = 0;
double airspeed_is_down3 = 0;
int mouse_x3 = 0, mouse_y3 = 0, mouse_x_cur3 = 0, mouse_y_cur3 = 0;

double pos_x1 = 0, pos_y1 = 0;
double pos_x2 = 0, pos_y2 = 0;
double pos_x3 = 0, pos_y3 = 0;

extern double vmo_speed;

double down_angle = 0;
double vmo_poiner_angle = 0;

double pos_1 = 0;
double pos_2 = 0;
double pos_3 = 0;

double pointer_angle = 0;
double pointer_angle_cur = 0;


// 坐标转换函数
double coordinateX (double width, double x);
double coordinateY (double height, double y);

// 外表框绘制函数
void draw_airspeed_frame(double center_x, double center_y, double side);

// 小刻度绘制函数
void airspeed_indicator_draw_scale_small(double r, double scale_length1, double scale_length2, double degree, double line_width, double width, double height, double airspeed_x, double airspeed_y);

// 下层刻度与文字绘制
void airspeed_indicator_draw_scale_down(double airspeed_x, double airspeed_y, double airspeed_r, double side, double width, double height);
void airspeed_indicator_draw_text_down(double airspeed_x, double airspeed_y, double airspeed_r, double side, double width, double height);

// 上层刻度与文字绘制
void airspeed_indicator_draw_scale_up(double airspeed_x, double airspeed_y, double airspeed_r, double side, double width, double height,double x,double y);
void airspeed_indicator_draw_text_up(double airspeed_x, double airspeed_y, double airspeed_r, double side, double width, double height);

// Vmo指针绘制
void airspeed_indicator_draw_Vmo(double airspeed_x, double airspeed_y, double airspeed_r, double side, double width, double height,double vmo_poiner_angle);

// 指针绘制函数
void airspeed_indicator_draw_pointer(double airspeed_x, double airspeed_y, double airspeed_r, double side, double width, double height);

// 绘制commandBug指针
void airspeed_indicator_draw_commandbug_pointer(double airspeed_x, double airspeed_y, double airspeed_r, double side, double width, double height, double angle);

// 绘制旋钮
void airspeed_indicator_draw_knob(double airspeed_x, double airspeed_y, double airspeed_r, double side, double width, double height, double angle);

// 螺丝绘制
void draw_screw(double screw_x, double screw_y, double screw_r, double angle);
void airspeed_indicator_draw_screw(double airspeed_x, double airspeed_y, double airspeed_r, double side, double width, double height);

// 旋钮鼠标交互
void airspeed_indicator_msg(double airspeed_x, double airspeed_y, double airspeed_r, double side, double width, double height);

// 绘制三个小指示指针 
void draw_airspeed_three_pointer(double airspeed_x, double airspeed_y, double airspeed_r, double side, double width, double height,double small_pointer_angle1, double small_pointer_angle2, double small_pointer_angle3);

// 调节亮度
void draw_light(double x, double y, double r);

void draw_airspeed(double airspeed_x0, double airspeed_y0, double airspeed_r00) {
	
	double airspeed_r0 = airspeed_r00 / 52 * 25 * 13 / 14;
	
	airspeed_y0 = -airspeed_y0;
	airspeed_x0 -= getwidth() / 2;
	airspeed_y0 += getheight() / 2;
	
	int width0 = getwidth();
	int height0 = getheight();
	const int width = width0;
	const int height = height0;
	
	const double airspeed_x = airspeed_x0;
	const double airspeed_y = airspeed_y0;
	const double airspeed_r = airspeed_r0;
	const double side = airspeed_r / 25 * 52.0;
	
#define Background_color EGEARGB(0xff,0x1b,0x20,0x25)
#define Frame_color EGEARGB(0xff,0x27,0x2b,0x34)
	
	// 获取当前指针转的角度
	pointer_angle_cur = pointer_angle;
	
	if (vmo_speed >= 0 && vmo_speed < 3) {
		down_angle = -(3 - vmo_speed) * 45 - 2 * 27 + (187.5 - pointer_angle_cur);
	}
	else if (vmo_speed >= 3 && vmo_speed <= 5) {
		down_angle = -(5 - vmo_speed) * 27 + (-(pointer_angle_cur - 90) - (-205));
	}
	else if (vmo_speed > 5) {
		down_angle = (vmo_speed - 5) * 27 + (205 + 90 - pointer_angle_cur);
	}
	
	// 外表框绘制
	draw_airspeed_frame(coordinateX(width, airspeed_x), coordinateY(height, airspeed_y), side);
	
	// 下层刻度与文字绘制
	airspeed_indicator_draw_scale_down(airspeed_x, airspeed_y, airspeed_r, side, width, height);
	airspeed_indicator_draw_text_down(airspeed_x, airspeed_y, airspeed_r, side, width, height);
	
	// 上层刻度与文字绘制
	airspeed_indicator_draw_scale_up(airspeed_x, airspeed_y, airspeed_r, side, width, height,coordinateX(width,airspeed_x), coordinateY(height,airspeed_y));
	airspeed_indicator_draw_text_up(airspeed_x, airspeed_y, airspeed_r, side, width, height);
	
	// Vmo指针绘制
	airspeed_indicator_draw_Vmo(airspeed_x, airspeed_y, airspeed_r, side, width, height,vmo_poiner_angle);
	
	// 指针绘制
	airspeed_indicator_draw_pointer(airspeed_x, airspeed_y, airspeed_r, side, width, height);
	
	// CommandBug指针绘制
	airspeed_indicator_draw_commandbug_pointer(airspeed_x, airspeed_y, airspeed_r, side, width, height, commandbug_angle);
	
	// 螺丝绘制
	airspeed_indicator_draw_screw(airspeed_x, airspeed_y, airspeed_r, side, width, height);
	
	// 旋钮绘制
	airspeed_indicator_draw_knob(airspeed_x, airspeed_y, airspeed_r, side, width, height, knob_angle);
	
	// 三个小指示指针
	draw_airspeed_three_pointer(airspeed_x, airspeed_y, airspeed_r, side, width, height,small_pointer_angle1,small_pointer_angle2, small_pointer_angle3);
	
	// 表盘光照
	draw_light(coordinateX(width,airspeed_x), coordinateY(height,airspeed_y), airspeed_r);
	
	// 旋钮鼠标交互
	airspeed_indicator_msg(airspeed_x, airspeed_y, airspeed_r, side, width, height);
	
}


double coordinateX(double width, double x) {
	return width / 2 + x;
}

double coordinateY(double height, double y) {
	return height / 2 - y;
}

void draw_airspeed_frame(double center_x, double center_y, double side) {
	double lefttop_x = center_x - side / 2.0;
	double lefttop_y = center_y - side / 2.0;
	double R = side / 52.0 * 25;
	double R1 = side / 2;
	
	setcolor(EGEARGB(0X4F, 0X00, 0X00, 0X00));
	setlinewidth(5);
	int RCDI_num_points_frame_edge = 16;
	ege_point RCDI_polypoints_frame_edge[16] = { {lefttop_x + side / 26 * 3,lefttop_y - side / 26},{lefttop_x - side / 26 ,lefttop_y + side / 26 * 3},
		
		{lefttop_x - side / 26 ,lefttop_y + side / 26 * 3},{lefttop_x - side / 26 ,lefttop_y + side / 26 * 3},
		
		{lefttop_x - side / 26,lefttop_y + side - side / 26 * 3},{lefttop_x - side / 26,lefttop_y + side - side / 26 * 3},
		
		{lefttop_x - side / 26,lefttop_y + side - side / 26 * 3},{lefttop_x + side / 26 * 3,lefttop_y + side + side / 26},
		
		{lefttop_x + side / 26 * 3,lefttop_y + side + side / 26},{lefttop_x + side / 26 * 3,lefttop_y + side + side / 26},
		
		{lefttop_x + side - side / 26 * 3,lefttop_y + side + side / 26},{lefttop_x + side - side / 26 * 3,lefttop_y + side + side / 26},
		
		{lefttop_x + side - side / 26 * 3,lefttop_y + side + side / 26},{lefttop_x + side + side / 26,lefttop_y + side - side / 26 * 3},
		
		{lefttop_x + side + side / 26,lefttop_y + side - side / 26 * 3},{lefttop_x + side + side / 26,lefttop_y + side - side / 26 * 3}
		
	};
	ege_bezier(RCDI_num_points_frame_edge, RCDI_polypoints_frame_edge);
	
	int num_points2 = 4;
	ege_point polypoints2[4] = {
		//{lefttop_x - side / 26 + side / 250,lefttop_y + side / 26 * 3 - side / 250} ,
		{lefttop_x + side / 26 * 3 + side / 250,lefttop_y - side / 26 - side / 250},
		{lefttop_x + side - side / 26 * 3 + side / 250,lefttop_y - side / 26 - side / 250},
		{lefttop_x + side + side / 26 + side / 250,lefttop_y + side / 26 * 3 - side / 250} ,
		{lefttop_x + side + side / 26 + side / 250,lefttop_y + side - side / 26 * 3 - side / 250}
	};
	
	ege_setpattern_lineargradient(lefttop_x + side / 26 * 3 + side / 250, lefttop_y - side / 26 - side / 250, EGEARGB(0X6F, 0XFF, 0XFF, 0XFF),
		lefttop_x + side + side / 26 + side / 250, lefttop_y + side - side / 26 * 3 - side / 250, EGEARGB(0X2F, 0XFF, 0XFF, 0XFF));
	ege_fillpoly(num_points2, polypoints2);
	ege_setpattern_none();
	
	
	// 边框颜色
	int num_points3 = 8;
	ege_point polypoints3[8] = {
		{lefttop_x - side / 26 ,lefttop_y + side / 26 * 3},
		{lefttop_x + side / 26 * 3,lefttop_y - side / 26},
		{lefttop_x + side - side / 26 * 3,lefttop_y - side / 26},
		{lefttop_x + side + side / 26,lefttop_y + side / 26 * 3},
		{lefttop_x + side + side / 26,lefttop_y + side - side / 26 * 3},
		{lefttop_x + side - side / 26 * 3,lefttop_y + side + side / 26},
		{lefttop_x + side / 26 * 3,lefttop_y + side + side / 26},
		{lefttop_x - side / 26,lefttop_y + side - side / 26 * 3}
	};
	ege_setpattern_lineargradient(lefttop_x + side + side / 26, lefttop_y + side / 26 * 3, EGEARGB(0XFF, 0X1F, 0X23, 0X2C),
		lefttop_x - side / 26, lefttop_y + side - side / 26 * 3, EGEARGB(0XFF, 0X17, 0X1A, 0X20));
	ege_fillpoly(num_points3, polypoints3);
	ege_setpattern_none();
	
	// 周边圆环凸起的一部分 
	ege_setpattern_lineargradient(lefttop_x - side / 52 + side + side / 26, lefttop_y - side / 52, EGEARGB(0XFF, 0X14, 0X1A, 0X20),
		lefttop_x - side / 52, lefttop_y - side / 52 + side + side / 26, EGEARGB(0XFF, 0X14, 0X1A, 0X20));
	ege_fillellipse(lefttop_x - side / 52 + side * 1.0 / 340, lefttop_y - side / 52 - side * 1.0 / 340, side + side / 24, side + side / 26);
	
	ege_setpattern_lineargradient(lefttop_x - side / 52 + side + side / 26, lefttop_y - side / 52, EGEARGB(0XFF, 0X17, 0X1A, 0X20),
		lefttop_x - side / 52, lefttop_y - side / 52 + side + side / 26, EGEARGB(0XFF, 0X1F, 0X23, 0X2C));
	ege_fillellipse(lefttop_x - side / 52, lefttop_y - side / 52, side + side / 26, side + side / 26);
	ege_setpattern_none();
	
	//表盘黑色
	ege_setpattern_lineargradient(center_x + R1 * cos(PI / 4) * 1.1, center_y - R1 * sin(PI / 4) * 1.1, EGEARGB(0XFF, 0X00, 0X00, 0X00),
		center_x - R1 * cos(PI / 4), center_y + R1 * sin(PI / 4), EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillellipse(lefttop_x + side * 1.0 / 97.1428571, lefttop_y + side * 1.0 / 97.1428571, side / 1.02, side / 1.02);
	ege_setpattern_none();
	
	// 表盘颜色
	ege_setpattern_lineargradient(center_x + R * cos(PI / 4), center_y - R * sin(PI / 4), EGEARGB(0XFF, 0X15, 0X15, 0X15),
		center_x - R * cos(PI / 4), center_y + R * sin(PI / 4), EGEARGB(0XFF, 0X10, 0X10, 0X10));
	ege_fillellipse(lefttop_x + side / 52, lefttop_y + side / 52, side - side / 26, side - side / 26);
	ege_setpattern_none();
}

void airspeed_indicator_draw_scale_small(double r, double scale_length1, double scale_length2, double degree, double line_width,double width, double height,double airspeed_x,double airspeed_y) {
	setfillcolor(WHITE);
	setlinewidth(line_width);
	ege_line(coordinateX(width,(airspeed_x + r * scale_length1 * cos(degree))), coordinateY(height,(airspeed_y + r * scale_length1 * sin(degree))),
		coordinateX(width,(airspeed_x + r * scale_length2 * cos(degree))), coordinateY(height,(airspeed_y + r * scale_length2 * sin(degree))));
}

void airspeed_indicator_draw_scale_down(double airspeed_x, double airspeed_y, double airspeed_r, double side, double width, double height) {
	double text_angle = down_angle;
	double scale_angle = down_angle;
	setcolor(EGERGB(177, 177, 178));
	double scale_angle1 = (scale_angle / 27) * 26.5;
	
	for (double i = -180 - 7.5; i >= -180 - 7.5 - 27 * 4; i -= 27) {
		airspeed_indicator_draw_scale_small(airspeed_r, 0.97, 0.86, PI * (i + scale_angle) / 180, side / 170, width, height, airspeed_x, airspeed_y);
	}
	for (double i = -180 - 7.5; i >= -180 - 7.5 - 5.4 * 20; i -= 5.4) {
		airspeed_indicator_draw_scale_small(airspeed_r, 0.97, 0.90, PI * (i + scale_angle) / 180, side / 226.666666667,width, height, airspeed_x, airspeed_y);
	}
	// 点绘制
	for (double i = -180 -3; i >= -180 -3 - 5.4 * 20; i -= 5.4 * 5) {
		ege_setpattern_lineargradient(
			coordinateX(width,airspeed_x + airspeed_r * 0.88 * cos((i + scale_angle1) * PI / 180)),
			coordinateY(height, airspeed_y + airspeed_r * 0.88 * sin((i + scale_angle1) * PI / 180)),
			EGERGB(177, 177, 177),
			coordinateX(width, airspeed_x + airspeed_r * 0.88 * cos((i + scale_angle1) * PI / 180)) + airspeed_r / 37.5,
			coordinateY(height, airspeed_y + airspeed_r * 0.88 * sin((i + scale_angle1) * PI / 180)) + airspeed_r / 37.5,
			EGERGB(177, 177, 177)
			);
		ege_fillellipse(coordinateX(width, airspeed_x + airspeed_r * 0.88 * cos((i + scale_angle1) * PI / 180)),
			coordinateY(height, airspeed_y + airspeed_r * 0.88 * sin((i + scale_angle1) * PI / 180)), airspeed_r / 37.5, airspeed_r / 37.5);
	}
	
}

void airspeed_indicator_draw_text_down(double airspeed_x, double airspeed_y, double airspeed_r, double side, double width, double height) {
	
	double text_angle = down_angle;
	// 每旋转28度大概字体旋转300度
	// 每旋转50度大概mach旋转400度
	double text_angle0 = (text_angle / 28) * 300;
	double text_angle1 = (text_angle / 50) * 400;
	
	//设置字体格式等
	
	setcolor(EGERGB(177, 177, 177));
	setbkmode(TRANSPARENT);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	
	LOGFONTW AI_font;
	setfont(side / 7.72727272727, 0, "黑体");
	getfont(&AI_font);
	AI_font.lfEscapement = -1000 + text_angle0;
	AI_font.lfWeight = 0;
	setfont(&AI_font);
	ege_drawtext("9", (coordinateX(width, airspeed_x + airspeed_r * 0.80 * cos((-215 - 28 * 3 + text_angle) * PI / 180))),
		(coordinateY(height, airspeed_y + airspeed_r * 0.80 * sin((-215 - 28 * 3 + text_angle) * PI / 180))));
	
	getfont(&AI_font);
	AI_font.lfEscapement = -800 + text_angle0;
	AI_font.lfWeight = 0;
	setfont(&AI_font);
	ege_drawtext("8", (coordinateX(width, airspeed_x + airspeed_r * 0.78 * cos((-210 - 28 * 2 - 1 + text_angle) * PI / 180))),
		(coordinateY(height, airspeed_y + airspeed_r * 0.78 * sin((-210 - 28 * 2 - 1 + text_angle) * PI / 180))));
	
	getfont(&AI_font);
	AI_font.lfEscapement = -500 + text_angle0;
	AI_font.lfWeight = 0;
	setfont(&AI_font);
	ege_drawtext("7", (coordinateX(width, airspeed_x + airspeed_r * 0.77 * cos((-213 - 28 * 1 + text_angle) * PI / 180))),
		(coordinateY(height, airspeed_y + airspeed_r * 0.77 * sin((-213 - 28 * 1 + text_angle) * PI / 180))));
	
	getfont(&AI_font);
	AI_font.lfEscapement = -300 + text_angle0;
	AI_font.lfWeight = 0;
	setfont(&AI_font);
	ege_drawtext("6", (coordinateX(width, airspeed_x + airspeed_r * 0.79 * cos((-213 + text_angle) * PI / 180))),
		(coordinateY(height, airspeed_y + airspeed_r * 0.79 * sin((-213 + text_angle) * PI / 180))));
	
	getfont(&AI_font);
	AI_font.lfEscapement = -100 + text_angle0;
	AI_font.lfWeight = 0;
	setfont(&AI_font);
	ege_drawtext("5", (coordinateX(width, airspeed_x + airspeed_r * 0.77 * cos((-187 + text_angle) * PI / 180))),
		(coordinateY(height, airspeed_y + airspeed_r * 0.77 * sin((-187 + text_angle) * PI / 180))));
	
	setfont(side / 19.4285714286, side / 34, "黑体");
	getfont(&AI_font);
	AI_font.lfEscapement = 100 + text_angle0;
	AI_font.lfWeight = 2;
	setfont(&AI_font);
	ege_drawtext("MACH", (coordinateX(width, airspeed_x + airspeed_r * 0.85 * cos((-173 + text_angle) * PI / 180))),
		(coordinateY(height, airspeed_y + airspeed_r * 0.85 * sin((-173 + text_angle) * PI / 180))));
}

void airspeed_indicator_draw_scale_up(double airspeed_x, double airspeed_y, double airspeed_r, double side, double width, double height,double center_x, double center_y) {
	
	double lefttop_x = center_x - side / 2.0;
	double lefttop_y = center_y - side / 2.0;
	double R = side / 52.0 * 25;
	double R1 = side / 2;
	
	// 扇形遮盖
	setfillcolor(BLACK);
	ege_fillpie(coordinateX(width,airspeed_x + airspeed_r * 1.45 * cos(135 * PI / 180)),
		coordinateY(height,airspeed_y + airspeed_r * 1.36 * sin(133.5 * PI / 180)), side * 0.97, side * 0.95, -125, 230);
	// 扇形遮盖打上的阴影
	ege_setpattern_lineargradient(center_x + R * cos(PI / 4), center_y - R * sin(PI / 4), EGEARGB(0XFF, 0X15, 0X15, 0X15),
		center_x - R * cos(PI / 4), center_y + R * sin(PI / 4), EGEARGB(0XFF, 0X10, 0X10, 0X10));
	ege_fillpie(coordinateX(width,airspeed_x + airspeed_r * 1.45 * cos(135 * PI / 180)),
		coordinateY(height,airspeed_y + airspeed_r * 1.36 * sin(133.5 * PI / 180)), side * 0.97, side * 0.95, -125, 230);
	ege_setpattern_none();
	
	setcolor(EGERGB(177, 177, 178));
	airspeed_indicator_draw_scale_small(airspeed_r, 0.97, 0.85, PI * 107 / 180, side / 226.666666667, width, height, airspeed_x, airspeed_y);
	for (int i = 90; i >= 90 - 150; i -= 15) {
		airspeed_indicator_draw_scale_small(airspeed_r, 0.97, 0.78, PI * i / 180, side / 170, width, height, airspeed_x, airspeed_y);
	}
	for (double i = 90; i >= 90 - 15 * 4; i -= 7.5) {
		airspeed_indicator_draw_scale_small(airspeed_r, 0.97, 0.85, PI * i / 180, side / 170, width, height, airspeed_x, airspeed_y);
	}
	for (double i = 30; i >= 30 - 90; i -= 3) {
		airspeed_indicator_draw_scale_small(airspeed_r, 0.97, 0.85, PI * i / 180, side / 226.666666667, width, height, airspeed_x, airspeed_y);
	}
	for (int i = -60; i >= -60 - 30; i -= 10) {
		airspeed_indicator_draw_scale_small(airspeed_r, 0.97, 0.78, PI * i / 180, side / 170, width, height, airspeed_x, airspeed_y);
	}
	for (double i = -60; i >= -60 - 40; i -= 5) {
		airspeed_indicator_draw_scale_small(airspeed_r, 0.97, 0.85, PI * i / 180, side / 170, width, height, airspeed_x, airspeed_y);
	}
	airspeed_indicator_draw_scale_small(airspeed_r, 0.97, 0.55, PI * -100 / 180, side / 170, width, height, airspeed_x, airspeed_y);
	for (double i = -100; i >= -100 - 35 * 2; i -= 35) {
		airspeed_indicator_draw_scale_small(airspeed_r, 0.7, 0.55, PI * i / 180, side / 170, width, height, airspeed_x, airspeed_y);
	}
	for (double i = -100; i >= -100 - 35 * 2; i -= 7) {
		airspeed_indicator_draw_scale_small(airspeed_r, 0.7, 0.62, PI * i / 180, side / 170, width, height, airspeed_x, airspeed_y);
	}
	for (double i = -170; i >= -170 - 25 * 2; i -= 25) {
		airspeed_indicator_draw_scale_small(airspeed_r, 0.7, 0.55, PI * i / 180, side / 170, width, height, airspeed_x, airspeed_y);
	}
	for (double i = -170; i >= -170 - 25 * 2 - 10; i -= 5) {
		airspeed_indicator_draw_scale_small(airspeed_r, 0.7, 0.62, PI * i / 180, side / 226.666666667, width, height, airspeed_x, airspeed_y);
	}
	
}

void airspeed_indicator_draw_text_up(double airspeed_x, double airspeed_y, double airspeed_r, double side, double width, double height) {
	setcolor(EGERGB(177, 177, 177));
	setbkmode(TRANSPARENT);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setfont(side / 17.894736842105, 0, "黑体");
	outtextxy((coordinateX(width, airspeed_x + airspeed_r * 0.80 * cos(107 * PI / 180))),
		(coordinateY(height, airspeed_y + airspeed_r * 0.80 * sin(107 * PI / 180))), "0");
	setfont(side / 11.3333333333, 0, "黑体");
	outtextxy((coordinateX(width, airspeed_x + airspeed_r * 0.68 * cos(90 * PI / 180))),
		(coordinateY(height, airspeed_y + airspeed_r * 0.68 * sin(90 * PI / 180))), "60");
	outtextxy((coordinateX(width, airspeed_x + airspeed_r * 0.68 * cos(60 * PI / 180))),
		(coordinateY(height, airspeed_y + airspeed_r * 0.68 * sin(60 * PI / 180))), "80");
	outtextxy((coordinateX(width, airspeed_x + airspeed_r * 0.62 * cos(33 * PI / 180))),
		(coordinateY(height, airspeed_y + airspeed_r * 0.62 * sin(33 * PI / 180))), "100");
	outtextxy((coordinateX(width, airspeed_x + airspeed_r * 0.61 * cos(0 * PI / 180))),
		(coordinateY(height, airspeed_y + airspeed_r * 0.61 * sin(0 * PI / 180))), "120");
	outtextxy((coordinateX(width, airspeed_x + airspeed_r * 0.62 * cos(-33 * PI / 180))),
		(coordinateY(height, airspeed_y + airspeed_r * 0.62 * sin(-33 * PI / 180))), "140");
	outtextxy((coordinateX(width, airspeed_x + airspeed_r * 0.68 * cos(-61 * PI / 180))),
		(coordinateY(height, airspeed_y + airspeed_r * 0.68 * sin(-61 * PI / 180))), "160");
	setfont(side / 13.6, 0, "黑体");
	outtextxy((coordinateX(width, airspeed_x + airspeed_r * 0.48 * cos(-100 * PI / 180))),
		(coordinateY(height, airspeed_y + airspeed_r * 0.48 * sin(-100 * PI / 180))), "200");
	outtextxy((coordinateX(width, airspeed_x + airspeed_r * 0.45 * cos(-136 * PI / 180))),
		(coordinateY(height, airspeed_y + airspeed_r * 0.45 * sin(-136 * PI / 180))), "250");
	outtextxy((coordinateX(width, airspeed_x + airspeed_r * 0.42 * cos(-170 * PI / 180))),
		(coordinateY(height, airspeed_y + airspeed_r * 0.42 * sin(-170 * PI / 180))), "300");
	outtextxy((coordinateX(width, airspeed_x + airspeed_r * 0.43 * cos(-197 * PI / 180))),
		(coordinateY(height, airspeed_y + airspeed_r * 0.43 * sin(-197 * PI / 180))), "350");
	outtextxy((coordinateX(width, airspeed_x + airspeed_r * 0.44 * cos(-223 * PI / 180))),
		(coordinateY(height, airspeed_y + airspeed_r * 0.44 * sin(-223 * PI / 180))), "400");
	setfont(side / 11.3333333333, 0, "黑体");
	outtextxy((coordinateX(width, airspeed_x + airspeed_r * 0.18 * cos(-76 * PI / 180))),
		(coordinateY(height, airspeed_y + airspeed_r * 0.18 * sin(-76 * PI / 180))), "KNOTS");
	setfont(side / 22.6666666667, side / 34, "黑体", 230, 0, 1, false, false, false);
	outtextxy((coordinateX(width, airspeed_x + airspeed_r * 0.93 * cos(-240 * PI / 180))),
		(coordinateY(height, airspeed_y + airspeed_r * 0.93 * sin(-240 * PI / 180))), "M");
	outtextxy((coordinateX(width, airspeed_x + airspeed_r * 0.86 * cos(-239.5 * PI / 180))),
		(coordinateY(height, airspeed_y + airspeed_r * 0.86 * sin(-239.5 * PI / 180))), "A");
	outtextxy((coordinateX(width, airspeed_x + airspeed_r * 0.79 * cos(-239 * PI / 180))),
		(coordinateY(height, airspeed_y + airspeed_r * 0.79 * sin(-239 * PI / 180))), "C");
	outtextxy((coordinateX(width, airspeed_x + airspeed_r * 0.72 * cos(-238.2 * PI / 180))),
		(coordinateY(height, airspeed_y + airspeed_r * 0.72 * sin(-238.2 * PI / 180))), "H");
	
}

void airspeed_indicator_draw_Vmo(double airspeed_x, double airspeed_y, double airspeed_r, double side, double width, double height,double angle) {
	angle = -angle;
	angle = angle * PI / 180;
	
	double x01 = airspeed_r * 0.72 * cos(141 * PI / 180), y01 = airspeed_r * 0.72 * sin(141 * PI / 180);
	double x02 = airspeed_r * 0.63 * cos(141.5 * PI / 180), y02 = airspeed_r * 0.63 * sin(141.5 * PI / 180);
	double x03 = airspeed_r * 0.63 * cos(144 * PI / 180), y03 = airspeed_r * 0.63 * sin(144 * PI / 180);
	double x04 = airspeed_r * 0.53 * cos(147 * PI / 180), y04 = airspeed_r * 0.53 * sin(147 * PI / 180);
	double x05 = airspeed_r * 0.53 * cos(151 * PI / 180), y05 = airspeed_r * 0.53 * sin(151 * PI / 180);
	double x06 = airspeed_r * 0.72 * cos(151 * PI / 180), y06 = airspeed_r * 0.72 * sin(151 * PI / 180);
	ege_setpattern_lineargradient(
		coordinateX(width, x01 * cos(angle) - y01 * sin(angle) + airspeed_x),
		coordinateY(height, x01 * sin(angle) + y01 * cos(angle) + airspeed_y),
		EGERGB(177, 177, 177),
		coordinateX(width, x05 * cos(angle) - y05 * sin(angle) + airspeed_x),
		coordinateY(height, x05 * sin(angle) + y05 * cos(angle) + airspeed_y),
		EGERGB(177, 177, 177)
		);
	ege_point polypoints[6] = {
		coordinateX(width,x01 * cos(angle) - y01 * sin(angle) + airspeed_x),coordinateY(height, x01 * sin(angle) + y01 * cos(angle) + airspeed_y),
		coordinateX(width,x02 * cos(angle) - y02 * sin(angle) + airspeed_x),coordinateY(height, x02 * sin(angle) + y02 * cos(angle) + airspeed_y),
		coordinateX(width,x03 * cos(angle) - y03 * sin(angle) + airspeed_x),coordinateY(height, x03 * sin(angle) + y03 * cos(angle) + airspeed_y),
		coordinateX(width,x04 * cos(angle) - y04 * sin(angle) + airspeed_x),coordinateY(height, x04 * sin(angle) + y04 * cos(angle) + airspeed_y),
		coordinateX(width,x05 * cos(angle) - y05 * sin(angle) + airspeed_x),coordinateY(height, x05 * sin(angle) + y05 * cos(angle) + airspeed_y),
		coordinateX(width,x06 * cos(angle) - y06 * sin(angle) + airspeed_x),coordinateY(height, x06 * sin(angle) + y06 * cos(angle) + airspeed_y)
	};
	ege_fillpoly(6, polypoints);
	
	
	double x = airspeed_r * 0.72 * cos(141 * PI / 180), y = airspeed_r * 0.72 * sin(141 * PI / 180);
	double xx = airspeed_r * 0.53 * cos(151 * PI / 180), yy = airspeed_r * 0.53 * sin(151 * PI / 180);
	
	double x11 = airspeed_r * 0.72 * cos(148 * PI / 180), y11 = airspeed_r * 0.72 * sin(148 * PI / 180);
	double x12 = airspeed_r * 0.72 * cos(151 * PI / 180), y12 = airspeed_r * 0.72 * sin(151 * PI / 180);
	double x13 = airspeed_r * 0.64 * cos(141.5 * PI / 180), y13 = airspeed_r * 0.64 * sin(141.5 * PI / 180);
	double x14 = airspeed_r * 0.67 * cos(141.5 * PI / 180), y14 = airspeed_r * 0.67 * sin(141.5 * PI / 180);
	
	ege_setpattern_lineargradient(
		coordinateX(width, x * cos(angle) - y * sin(angle) + airspeed_x), coordinateY(height, x * sin(angle) + y * cos(angle) + airspeed_y),
		EGERGB(220, 20, 60),
		coordinateX(width, xx * cos(angle) - yy * sin(angle) + airspeed_x), coordinateY(height, xx * sin(angle) + yy * cos(angle) + airspeed_y),
		EGERGB(220, 20, 60)
		);
	
	ege_point polypoints1[4] = {
		coordinateX(width,x11 * cos(angle) - y11 * sin(angle) + airspeed_x),coordinateY(height, x11 * sin(angle) + y11 * cos(angle) + airspeed_y),
		coordinateX(width,x12 * cos(angle) - y12 * sin(angle) + airspeed_x),coordinateY(height, x12 * sin(angle) + y12 * cos(angle) + airspeed_y),
		coordinateX(width,x13 * cos(angle) - y13 * sin(angle) + airspeed_x),coordinateY(height, x13 * sin(angle) + y13 * cos(angle) + airspeed_y),
		coordinateX(width,x14 * cos(angle) - y14 * sin(angle) + airspeed_x),coordinateY(height, x14 * sin(angle) + y14 * cos(angle) + airspeed_y)
	};
	ege_fillpoly(4, polypoints1);
	
	
	double x21 = airspeed_r * 0.69 * cos(151 * PI / 180), y21 = airspeed_r * 0.69 * sin(151 * PI / 180);
	double x22 = airspeed_r * 0.66 * cos(151 * PI / 180), y22 = airspeed_r * 0.66 * sin(151 * PI / 180);
	double x23 = airspeed_r * 0.60 * cos(144.5 * PI / 180), y23 = airspeed_r * 0.60 * sin(144.5 * PI / 180);
	double x24 = airspeed_r * 0.63 * cos(144 * PI / 180), y24 = airspeed_r * 0.63 * sin(144 * PI / 180);
	
	ege_point polypoints2[4] = {
		coordinateX(width,x21 * cos(angle) - y21 * sin(angle) + airspeed_x),coordinateY(height, x21 * sin(angle) + y21 * cos(angle) + airspeed_y),
		coordinateX(width,x22 * cos(angle) - y22 * sin(angle) + airspeed_x),coordinateY(height, x22 * sin(angle) + y22 * cos(angle) + airspeed_y),
		coordinateX(width,x23 * cos(angle) - y23 * sin(angle) + airspeed_x),coordinateY(height, x23 * sin(angle) + y23 * cos(angle) + airspeed_y),
		coordinateX(width,x24 * cos(angle) - y24 * sin(angle) + airspeed_x),coordinateY(height, x24 * sin(angle) + y24 * cos(angle) + airspeed_y)
	};
	ege_fillpoly(4, polypoints2);
	
	
	double x31 = airspeed_r * 0.62 * cos(151 * PI / 180), y31 = airspeed_r * 0.62 * sin(151 * PI / 180);
	double x32 = airspeed_r * 0.59 * cos(151 * PI / 180), y32 = airspeed_r * 0.59 * sin(151 * PI / 180);
	double x33 = airspeed_r * 0.55 * cos(146 * PI / 180), y33 = airspeed_r * 0.55 * sin(146 * PI / 180);
	double x34 = airspeed_r * 0.577 * cos(145.2 * PI / 180), y34 = airspeed_r * 0.577 * sin(145.2 * PI / 180);
	
	ege_point polypoints3[4] = {
		coordinateX(width,x31 * cos(angle) - y31 * sin(angle) + airspeed_x),coordinateY(height, x31 * sin(angle) + y31 * cos(angle) + airspeed_y),
		coordinateX(width,x32 * cos(angle) - y32 * sin(angle) + airspeed_x),coordinateY(height, x32 * sin(angle) + y32 * cos(angle) + airspeed_y),
		coordinateX(width,x33 * cos(angle) - y33 * sin(angle) + airspeed_x),coordinateY(height, x33 * sin(angle) + y33 * cos(angle) + airspeed_y),
		coordinateX(width,x34 * cos(angle) - y34 * sin(angle) + airspeed_x),coordinateY(height, x34 * sin(angle) + y34 * cos(angle) + airspeed_y)
	};
	ege_fillpoly(4, polypoints3);
	
}

void airspeed_indicator_draw_pointer(double airspeed_x, double airspeed_y, double airspeed_r, double side, double width, double height) {
	setcolor(EGERGB(177, 177, 178));
	double angle = 0;
	if (airSpeed <= 60) {
		angle = airSpeed * 17 / 60;
	}
	else if (airSpeed >= 60 && airSpeed <= 160) {
		angle = 17 + (airSpeed - 60) * 150 / 100;
	}
	else if (airSpeed >= 160 && airSpeed <= 200) {
		angle = 17 + 150 + (airSpeed - 160) * 40 / 40;
	}
	else if (airSpeed >= 200 && airSpeed <= 300) {
		angle = 17 + 150 + 40 + (airSpeed - 200) * 70 / 100;
	}
	else if (airSpeed >= 300 && airSpeed <= 400) {
		angle = 17 + 150 + 40 + 70 + (airSpeed - 300) * 50 / 100;
	}
	pointer_angle = angle;
	// 逆时针旋转，angle正负改变
	angle = -angle;
	angle = angle * PI / 180;
	
	// 上面白色的（动）
	double x01 = airspeed_r * 0.88 * cos(108 * PI / 180), y01 = airspeed_r * 0.88 * sin(108 * PI / 180);
	double x02 = airspeed_r * 0.88 * cos(107 * PI / 180), y02 = airspeed_r * 0.88 * sin(107 * PI / 180);
	double x03 = airspeed_r * 0.35 * cos(104 * PI / 180), y03 = airspeed_r * 0.35 * sin(104 * PI / 180);
	double x04 = airspeed_r * 0.27 * cos(93 * PI / 180), y04 = airspeed_r * 0.27 * sin(93 * PI / 180);
	double x05 = airspeed_r * 0.12 * cos(68 * PI / 180), y05 = airspeed_r * 0.12 * sin(68 * PI / 180);
	double x06 = airspeed_r * 0.1 * cos(136 * PI / 180), y06 = airspeed_r * 0.1 * sin(136 * PI / 180);
	double x07 = airspeed_r * 0.27 * cos(120 * PI / 180), y07 = airspeed_r * 0.27 * sin(120 * PI / 180);
	double x08 = airspeed_r * 0.35 * cos(112 * PI / 180), y08 = airspeed_r * 0.35 * sin(112 * PI / 180);
	double x09 = airspeed_r * 0.70 * cos(110 * PI / 180), y09 = airspeed_r * 0.70 * sin(110 * PI / 180);
	
	ege_setpattern_lineargradient(
		coordinateX(width, x01 * cos(angle) - y01 * sin(angle) + airspeed_x),
		coordinateY(height, x01 * sin(angle) + y01 * cos(angle) + airspeed_y),
		EGERGB(177, 177, 178),
		coordinateX(width, x06 * cos(angle) - y06 * sin(angle) + airspeed_x),
		coordinateY(height, x06 * sin(angle) + y06 * cos(angle) + airspeed_y),
		EGERGB(177, 177, 178)
		);
	ege_point polypoints[9] = {
		coordinateX(width, x01 * cos(angle) - y01 * sin(angle) + airspeed_x),coordinateY(height, x01 * sin(angle) + y01 * cos(angle) + airspeed_y),
		coordinateX(width, x02 * cos(angle) - y02 * sin(angle) + airspeed_x),coordinateY(height, x02 * sin(angle) + y02 * cos(angle) + airspeed_y),
		coordinateX(width, x03 * cos(angle) - y03 * sin(angle) + airspeed_x),coordinateY(height, x03 * sin(angle) + y03 * cos(angle) + airspeed_y),
		coordinateX(width, x04 * cos(angle) - y04 * sin(angle) + airspeed_x),coordinateY(height, x04 * sin(angle) + y04 * cos(angle) + airspeed_y),
		coordinateX(width, x05 * cos(angle) - y05 * sin(angle) + airspeed_x),coordinateY(height, x05 * sin(angle) + y05 * cos(angle) + airspeed_y),
		coordinateX(width, x06 * cos(angle) - y06 * sin(angle) + airspeed_x),coordinateY(height, x06 * sin(angle) + y06 * cos(angle) + airspeed_y),
		coordinateX(width, x07 * cos(angle) - y07 * sin(angle) + airspeed_x),coordinateY(height, x07 * sin(angle) + y07 * cos(angle) + airspeed_y),
		coordinateX(width, x08 * cos(angle) - y08 * sin(angle) + airspeed_x),coordinateY(height, x08 * sin(angle) + y08 * cos(angle) + airspeed_y),
		coordinateX(width, x09 * cos(angle) - y09 * sin(angle) + airspeed_x),coordinateY(height, x09 * sin(angle) + y09 * cos(angle) + airspeed_y)
	};
	ege_fillpoly(9, polypoints);
	
	// 指针肚绘制(动)
	setcolor(EGERGB(177, 177, 179));
	double x11 = airspeed_r * 0.88 * cos(108 * PI / 180), y11 = airspeed_r * 0.88 * sin(108 * PI / 180);
	double x12 = airspeed_r * 0.79 * cos(111 * PI / 180), y12 = airspeed_r * 0.79 * sin(111 * PI / 180);
	double x13 = airspeed_r * 0.67 * cos(108 * PI / 180), y13 = airspeed_r * 0.67 * sin(108 * PI / 180);
	double x14 = airspeed_r * 0.88 * cos(108 * PI / 180), y14 = airspeed_r * 0.88 * sin(108 * PI / 180);
	double x15 = airspeed_r * 0.78 * cos(109 * PI / 180), y15 = airspeed_r * 0.78 * sin(109 * PI / 180);
	setlinewidth(2.5);
	ege_setpattern_none();
	ege_point polypoints2[4] = {
		coordinateX(width, x11 * cos(angle) - y11 * sin(angle) + airspeed_x),coordinateY(height, x11 * sin(angle) + y11 * cos(angle) + airspeed_y),
		coordinateX(width, x12 * cos(angle) - y12 * sin(angle) + airspeed_x),coordinateY(height, x12 * sin(angle) + y12 * cos(angle) + airspeed_y),
		coordinateX(width, x13 * cos(angle) - y13 * sin(angle) + airspeed_x),coordinateY(height, x13 * sin(angle) + y13 * cos(angle) + airspeed_y),
		coordinateX(width, x14 * cos(angle) - y14 * sin(angle) + airspeed_x),coordinateY(height, x14 * sin(angle) + y14 * cos(angle) + airspeed_y)
	};
	ege_drawcurve(4, polypoints2);
	setfillcolor(EGERGB(177, 177, 179));
	floodfill(coordinateX(width, x15 * cos(angle) - y15 * sin(angle) + airspeed_x),
		coordinateY(height, x15 * sin(angle) + y15 * cos(angle) + airspeed_y), EGERGB(177, 177, 179));
	
	
	// 下面黑色指针绘制（动）
	double x21 = airspeed_r * 0.12 * cos(68 * PI / 180), y21 = airspeed_r * 0.12 * sin(68 * PI / 180);
	double x22 = airspeed_r * 0.335 * cos(-57 * PI / 180), y22 = airspeed_r * 0.335 * sin(-57 * PI / 180);
	double x23 = airspeed_r * 0.33 * cos(-78 * PI / 180), y23 = airspeed_r * 0.33 * sin(-78 * PI / 180);
	double x24 = airspeed_r * 0.10 * cos(136 * PI / 180), y24 = airspeed_r * 0.10 * sin(136 * PI / 180);
	ege_setpattern_lineargradient(
		coordinateX(width, x21 * cos(angle) - y21 * sin(angle) + airspeed_x),
		coordinateY(height, x21 * sin(angle) + y21 * cos(angle) + airspeed_y),
		BLACK,
		coordinateX(width, x23 * cos(angle) - y23 * sin(angle) + airspeed_x),
		coordinateY(height, x23 * sin(angle) + y23 * cos(angle) + airspeed_y),
		BLACK
		);
	ege_point polypoints1[4] = {
		coordinateX(width, x21 * cos(angle) - y21 * sin(angle) + airspeed_x),coordinateY(height, x21 * sin(angle) + y21 * cos(angle) + airspeed_y),
		coordinateX(width, x22 * cos(angle) - y22 * sin(angle) + airspeed_x),coordinateY(height, x22 * sin(angle) + y22 * cos(angle) + airspeed_y),
		coordinateX(width, x23 * cos(angle) - y23 * sin(angle) + airspeed_x),coordinateY(height, x23 * sin(angle) + y23 * cos(angle) + airspeed_y),
		coordinateX(width, x24 * cos(angle) - y24 * sin(angle) + airspeed_x),coordinateY(height, x24 * sin(angle) + y24 * cos(angle) + airspeed_y)
	};
	ege_fillpoly(4, polypoints1);
	
	
	// 下面黑色圆球
	double x31 = airspeed_r * 0.334 * cos(-55.5 * PI / 180), y31 = airspeed_r * 0.334 * sin(-55.5 * PI / 180);
	double x32 = airspeed_r * 0.38 * cos(-60 * PI / 180), y32 = airspeed_r * 0.38 * sin(-60 * PI / 180);
	double x33 = airspeed_r * 0.39 * cos(-69 * PI / 180), y33 = airspeed_r * 0.39 * sin(-69 * PI / 180);
	double x34 = airspeed_r * 0.376 * cos(-74 * PI / 180), y34 = airspeed_r * 0.376 * sin(-74 * PI / 180);
	double x35 = airspeed_r * 0.33 * cos(-78 * PI / 180), y35 = airspeed_r * 0.33 * sin(-78 * PI / 180);
	double x36 = airspeed_r * 0.37 * cos(-69 * PI / 180), y36 = airspeed_r * 0.37 * sin(-69 * PI / 180);
	ege_setpattern_none();
	setlinewidth(4);
	setcolor(EGERGB(1, 1, 1));
	ege_point polypoints3[6] = {
		coordinateX(width, x31 * cos(angle) - y31 * sin(angle) + airspeed_x),coordinateY(height, x31 * sin(angle) + y31 * cos(angle) + airspeed_y),
		coordinateX(width, x32 * cos(angle) - y32 * sin(angle) + airspeed_x),coordinateY(height, x32 * sin(angle) + y32 * cos(angle) + airspeed_y),
		coordinateX(width, x33 * cos(angle) - y33 * sin(angle) + airspeed_x),coordinateY(height, x33 * sin(angle) + y33 * cos(angle) + airspeed_y),
		coordinateX(width, x34 * cos(angle) - y34 * sin(angle) + airspeed_x),coordinateY(height, x34 * sin(angle) + y34 * cos(angle) + airspeed_y),
		coordinateX(width, x35 * cos(angle) - y35 * sin(angle) + airspeed_x),coordinateY(height, x35 * sin(angle) + y35 * cos(angle) + airspeed_y),
		coordinateX(width, x31 * cos(angle) - y31 * sin(angle) + airspeed_x),coordinateY(height, x31 * sin(angle) + y31 * cos(angle) + airspeed_y)
	};
	ege_drawcurve(6, polypoints3);
	setfillcolor(EGERGB(1, 1, 1));
	floodfill(coordinateX(width, x36 * cos(angle) - y36 * sin(angle) + airspeed_x),
		coordinateY(height, x36 * sin(angle) + y36 * cos(angle) + airspeed_y), EGERGB(1, 1, 1));
	
	
}

void airspeed_indicator_draw_commandbug_pointer(double airspeed_x, double airspeed_y, double airspeed_r, double side, double width, double height, double angle) {
	
	angle = -angle;
	angle = angle * PI / 180;
	
	//commandBug指针上半部分长方形(动态)
	setcolor(EGERGB(203, 114, 25));
	double x01 = airspeed_r * 0.93 * cos(-67.5 * PI / 180), y01 = airspeed_r * 0.93 * sin(-67.5 * PI / 180);
	double x02 = airspeed_r * 0.845 * cos(-67.5 * PI / 180), y02 = airspeed_r * 0.845 * sin(-67.5 * PI / 180);
	double x03 = airspeed_r * 0.845 * cos(-65 * PI / 180), y03 = airspeed_r * 0.845 * sin(-65 * PI / 180);
	double x04 = airspeed_r * 0.93 * cos(-65 * PI / 180), y04 = airspeed_r * 0.93 * sin(-65 * PI / 180);
	
	ege_setpattern_lineargradient(
		coordinateX(width, x02 * cos(angle) - y02 * sin(angle) + airspeed_x),
		coordinateY(height, x02 * sin(angle) + y02 * cos(angle) + airspeed_y),
		EGERGB(203, 114, 25),
		coordinateX(width, x04 * cos(angle) - y04 * sin(angle) + airspeed_x),
		coordinateY(height, x04 * sin(angle) + y04 * cos(angle) + airspeed_y),
		EGERGB(203, 114, 25)
		);
	ege_point polypoints1[4] = {
		coordinateX(width, x01 * cos(angle) - y01 * sin(angle) + airspeed_x),coordinateY(height, x01 * sin(angle) + y01 * cos(angle) + airspeed_y),
		coordinateX(width, x02 * cos(angle) - y02 * sin(angle) + airspeed_x),coordinateY(height, x02 * sin(angle) + y02 * cos(angle) + airspeed_y),
		coordinateX(width, x03 * cos(angle) - y03 * sin(angle) + airspeed_x),coordinateY(height, x03 * sin(angle) + y03 * cos(angle) + airspeed_y),
		coordinateX(width, x04 * cos(angle) - y04 * sin(angle) + airspeed_x),coordinateY(height, x04 * sin(angle) + y04 * cos(angle) + airspeed_y)
	};
	ege_fillpoly(4, polypoints1);
	
	// commandBug指针下面的弧线的部分（动态）
	double x11 = airspeed_r * 0.93 * cos(-67.3 * PI / 180), y11 = airspeed_r * 0.93 * sin(-67.3 * PI / 180);
	double x12 = airspeed_r * 0.98 * cos(-68.5 * PI / 180), y12 = airspeed_r * 0.98 * sin(-68.5 * PI / 180);
	double x13 = airspeed_r * 1.01 * cos(-74 * PI / 180), y13 = airspeed_r * 1.01 * sin(-74 * PI / 180);
	double x14 = airspeed_r * 1.02 * cos(-74 * PI / 180), y14 = airspeed_r * 1.02 * sin(-74 * PI / 180);
	double x15 = airspeed_r * 1.02 * cos(-66 * PI / 180), y15 = airspeed_r * 1.02 * sin(-66 * PI / 180);
	double x16 = airspeed_r * 1.02 * cos(-59 * PI / 180), y16 = airspeed_r * 1.02 * sin(-59 * PI / 180);
	double x17 = airspeed_r * 1.01 * cos(-59 * PI / 180), y17 = airspeed_r * 1.01 * sin(-59 * PI / 180);
	double x18 = airspeed_r * 0.98 * cos(-64 * PI / 180), y18 = airspeed_r * 0.98 * sin(-64 * PI / 180);
	double x19 = airspeed_r * 0.93 * cos(-65.2 * PI / 180), y19 = airspeed_r * 0.93 * sin(-65.2 * PI / 180);
	double x110 = airspeed_r * 0.96 * cos(-66 * PI / 180), y110 = airspeed_r * 0.96 * sin(-66 * PI / 180);
	ege_setpattern_none();
	ege_point polypoints2[10] = {
		coordinateX(width, x11 * cos(angle) - y11 * sin(angle) + airspeed_x),coordinateY(height, x11 * sin(angle) + y11 * cos(angle) + airspeed_y),
		coordinateX(width, x12 * cos(angle) - y12 * sin(angle) + airspeed_x),coordinateY(height, x12 * sin(angle) + y12 * cos(angle) + airspeed_y),
		coordinateX(width, x13 * cos(angle) - y13 * sin(angle) + airspeed_x),coordinateY(height, x13 * sin(angle) + y13 * cos(angle) + airspeed_y),
		coordinateX(width, x14 * cos(angle) - y14 * sin(angle) + airspeed_x),coordinateY(height, x14 * sin(angle) + y14 * cos(angle) + airspeed_y),
		coordinateX(width, x15 * cos(angle) - y15 * sin(angle) + airspeed_x),coordinateY(height, x15 * sin(angle) + y15 * cos(angle) + airspeed_y),
		coordinateX(width, x16 * cos(angle) - y16 * sin(angle) + airspeed_x),coordinateY(height, x16 * sin(angle) + y16 * cos(angle) + airspeed_y),
		coordinateX(width, x17 * cos(angle) - y17 * sin(angle) + airspeed_x),coordinateY(height, x17 * sin(angle) + y17 * cos(angle) + airspeed_y),
		coordinateX(width, x18 * cos(angle) - y18 * sin(angle) + airspeed_x),coordinateY(height, x18 * sin(angle) + y18 * cos(angle) + airspeed_y),
		coordinateX(width, x19 * cos(angle) - y19 * sin(angle) + airspeed_x),coordinateY(height, x19 * sin(angle) + y19 * cos(angle) + airspeed_y),
		coordinateX(width, x11 * cos(angle) - y11 * sin(angle) + airspeed_x),coordinateY(height, x11 * sin(angle) + y11 * cos(angle) + airspeed_y)
	};
	setlinewidth(4);
	setfillcolor(EGERGB(203, 114, 25));
	ege_drawcurve(10, polypoints2);
	floodfill(coordinateX(width, x110 * cos(angle) - y110 * sin(angle) + airspeed_x),
		coordinateY(height, x110 * sin(angle) + y110 * cos(angle) + airspeed_y), EGERGB(203, 114, 25));
	
	
	// 黑色线（动态）
	double x21 = airspeed_r * 1.03 * cos(-66 * PI / 180), y21 = airspeed_r * 1.03 * sin(-66 * PI / 180);
	double x22 = airspeed_r * 0.99 * cos(-66 * PI / 180), y22 = airspeed_r * 0.99 * sin(-66 * PI / 180);
	setcolor(BLACK);
	setlinewidth(side / 220);
	ege_line(
		coordinateX(width, x21 * cos(angle) - y21 * sin(angle) + airspeed_x),
		coordinateY(height, x21 * sin(angle) + y21 * cos(angle) + airspeed_y),
		coordinateX(width, x22 * cos(angle) - y22 * sin(angle) + airspeed_x),
		coordinateY(height, x22 * sin(angle) + y22 * cos(angle) + airspeed_y));
	
	
}

void airspeed_indicator_draw_knob(double airspeed_x, double airspeed_y, double airspeed_r, double side, double width, double height, double angle) {
	
	angle = -angle;
	angle = angle * PI / 180;
	
	for (int i = 0; i < 9; i++) {
		
		ege_setpattern_lineargradient(
			coordinateX(width, airspeed_x + airspeed_r * 1.23 * (1 + i * 1.0 / 120) * cos(-145 * PI / 180)),
			coordinateY(height, airspeed_y + airspeed_r * 1.23 * (1 + i * 1.0 / 120) * sin(-145 * PI / 180)),
			BLACK,
			coordinateX(width, airspeed_x + airspeed_r * 1.23 * (1 + i * 1.0 / 120) * cos(-145 * PI / 180) + airspeed_r / 3.2),
			coordinateY(height, airspeed_y + airspeed_r * 1.23 * (1 + i * 1.0 / 120) * sin(-145 * PI / 180) - airspeed_r / 3.2),
			BLACK
			);
		
		ege_fillellipse(
			coordinateX(width, airspeed_x + airspeed_r * 1.23 * (1 + i * 1.0 / 120) * cos(-145 * PI / 180)),
			coordinateY(height, airspeed_y + airspeed_r * 1.23 * (1 + i * 1.0 / 120) * sin(-145 * PI / 180)),
			airspeed_r / 3.2,
			airspeed_r / 3.2
			);
	}
	
	ege_setpattern_lineargradient(
		coordinateX(width, airspeed_x + airspeed_r * 1.23 * (1 + 8.5 * 1.0 / 120) * cos(-145 * PI / 180)),
		coordinateY(height, airspeed_y + airspeed_r * 1.23 * (1 + 8.5 * 1.0 / 120) * sin(-145 * PI / 180)),
		EGEARGB(200, 255, 255, 255),
		coordinateX(width, airspeed_x + airspeed_r * 1.23 * (1 + 8.5 * 1.0 / 120) * cos(-145 * PI / 180) + airspeed_r / 3.2),
		coordinateY(height, airspeed_y + airspeed_r * 1.23 * (1 + 8.5 * 1.0 / 120) * sin(-145 * PI / 180) - airspeed_r / 3.2),
		BLACK
		);
	
	ege_fillellipse(
		coordinateX(width, airspeed_x + airspeed_r * 1.23 * (1 + 8.5 * 1.0 / 120) * cos(-145 * PI / 180)),
		coordinateY(height, airspeed_y + airspeed_r * 1.23 * (1 + 8.5 * 1.0 / 120) * sin(-145 * PI / 180)),
		airspeed_r / 3.2,
		airspeed_r / 3.2
		);
	
	ege_setpattern_lineargradient(
		coordinateX(width, airspeed_x + airspeed_r * 1.23 * (1 + 9 * 1.0 / 120) * cos(-145 * PI / 180)),
		coordinateY(height, airspeed_y + airspeed_r * 1.23 * (1 + 9 * 1.0 / 120) * sin(-145 * PI / 180)),
		BLACK,
		coordinateX(width, airspeed_x + airspeed_r * 1.23 * (1 + 9 * 1.0 / 120) * cos(-145 * PI / 180) + airspeed_r / 3.2),
		coordinateY(height, airspeed_y + airspeed_r * 1.23 * (1 + 9 * 1.0 / 120) * sin(-145 * PI / 180) - airspeed_r / 3.2),
		BLACK
		);
	
	ege_fillellipse(
		coordinateX(width, airspeed_x + airspeed_r * 1.23 * (1 + 9 * 1.0 / 120) * cos(-145 * PI / 180)),
		coordinateY(height, airspeed_y + airspeed_r * 1.23 * (1 + 9 * 1.0 / 120) * sin(-145 * PI / 180)),
		airspeed_r / 3.2,
		airspeed_r / 3.2
		);
	
	// 橙色的（动态的）
	double x0 = airspeed_x + airspeed_r * 1.23 * (1 + 9 * 1.0 / 120) * cos(-145 * PI / 180) + airspeed_r / 3.2 / 2,
	y0 = airspeed_y + airspeed_r * 1.23 * (1 + 9 * 1.0 / 120) * sin(-145 * PI / 180) - airspeed_r / 3.2 / 2;//绕的中心点的坐标
	
	double x01 = airspeed_x + airspeed_r * 1.34 * cos(-139.5 * PI / 180) - x0,
	y01 = airspeed_y + airspeed_r * 1.34 * sin(-139.5 * PI / 180) - y0;
	double x02 = airspeed_x + airspeed_r * 1.33 * cos(-138.3 * PI / 180) - x0,
	y02 = airspeed_y + airspeed_r * 1.33 * sin(-138.3 * PI / 180) - y0;
	double x03 = airspeed_x + airspeed_r * 1.22 * cos(-135 * PI / 180) - x0,
	y03 = airspeed_y + airspeed_r * 1.22 * sin(-135 * PI / 180) - y0;
	double x04 = airspeed_x + airspeed_r * 1.335 * cos(-132.5 * PI / 180) - x0,
	y04 = airspeed_y + airspeed_r * 1.335 * sin(-132.5 * PI / 180) - y0;
	double x05 = airspeed_x + airspeed_r * 1.355 * cos(-132 * PI / 180) - x0,
	y05 = airspeed_y + airspeed_r * 1.355 * sin(-132 * PI / 180) - y0;
	double x06 = airspeed_x + airspeed_r * 1.373 * cos(-134 * PI / 180) - x0,
	y06 = airspeed_y + airspeed_r * 1.373 * sin(-134 * PI / 180) - y0;
	double x07 = airspeed_x + airspeed_r * 1.37 * cos(-137 * PI / 180) - x0,
	y07 = airspeed_y + airspeed_r * 1.37 * sin(-137 * PI / 180) - y0;
	// 这是取得定位画图点
	double x08 = airspeed_x + airspeed_r * 1.30 * cos(-135.3 * PI / 180) - x0,
	y08 = airspeed_y + airspeed_r * 1.30 * sin(-135.3 * PI / 180) - y0;
	setcolor(EGERGB(203, 114, 25));
	setlinewidth(3);
	setfillcolor(EGERGB(203, 114, 25));
	ege_setpattern_none();
	ege_point polypoints[8] = {
		coordinateX(width, x01 * cos(angle) - y01 * sin(angle) + x0),coordinateY(height,x01 * sin(angle) + y01 * cos(angle) + y0),
		coordinateX(width, x02 * cos(angle) - y02 * sin(angle) + x0),coordinateY(height,x02 * sin(angle) + y02 * cos(angle) + y0),
		coordinateX(width, x03 * cos(angle) - y03 * sin(angle) + x0),coordinateY(height,x03 * sin(angle) + y03 * cos(angle) + y0),
		coordinateX(width, x04 * cos(angle) - y04 * sin(angle) + x0),coordinateY(height,x04 * sin(angle) + y04 * cos(angle) + y0),
		coordinateX(width, x05 * cos(angle) - y05 * sin(angle) + x0),coordinateY(height,x05 * sin(angle) + y05 * cos(angle) + y0),
		coordinateX(width, x06 * cos(angle) - y06 * sin(angle) + x0),coordinateY(height,x06 * sin(angle) + y06 * cos(angle) + y0),
		coordinateX(width, x07 * cos(angle) - y07 * sin(angle) + x0),coordinateY(height,x07 * sin(angle) + y07 * cos(angle) + y0),
		coordinateX(width, x01 * cos(angle) - y01 * sin(angle) + x0),coordinateY(height,x01 * sin(angle) + y01 * cos(angle) + y0)
	};
	ege_drawcurve(8, polypoints);
	floodfill(
		coordinateX(width, x08 * cos(angle) - y08 * sin(angle) + x0),
		coordinateY(height, x08 * sin(angle) + y08 * cos(angle) + y0), EGERGB(203, 114, 25)
		);
	
	setcolor(EGERGB(177, 177, 177));
	int x, y;
	mousepos(&x, &y);
	if ((x >= coordinateX(width, airspeed_x + airspeed_r * 1.23 * (1 + 9 * 1.0 / 120) * cos(-145 * PI / 180))) && (x <= coordinateX(width, airspeed_x + airspeed_r * 1.23 * (1 + 9 * 1.0 / 120) * cos(-145 * PI / 180)) + airspeed_r / 3.2)
		&& (y >= coordinateY(height, airspeed_y + airspeed_r * 1.23 * (1 + 9 * 1.0 / 120) * sin(-145 * PI / 180))) && (y <= coordinateY(height, airspeed_y + airspeed_r * 1.23 * (1 + 9 * 1.0 / 120) * sin(-145 * PI / 180)) + airspeed_r / 3.2)) {
		ege_point polypoints1[4]{// 左侧弧线
			{coordinateX(width, airspeed_x + airspeed_r * 1.21 * (1 + 9 * 1.0 / 120) * cos(-139 * PI / 180)),
				coordinateY(height, airspeed_y + airspeed_r * 1.21 * (1 + 9 * 1.0 / 120) * sin(-139 * PI / 180))},//1
			{coordinateX(width, airspeed_x + airspeed_r * 1.25 * (1 + 9 * 1.0 / 120) * cos(-138 * PI / 180)),
				coordinateY(height, airspeed_y + airspeed_r * 1.25 * (1 + 9 * 1.0 / 120) * sin(-138 * PI / 180))},//2
			{coordinateX(width, airspeed_x + airspeed_r * 1.27 * (1 + 9 * 1.0 / 120) * cos(-138 * PI / 180)),
				coordinateY(height, airspeed_y + airspeed_r * 1.27 * (1 + 9 * 1.0 / 120) * sin(-138 * PI / 180))},//3
			{coordinateX(width, airspeed_x + airspeed_r * 1.285 * (1 + 9 * 1.0 / 120) * cos(-134.5 * PI / 180)),
				coordinateY(height, airspeed_y + airspeed_r * 1.285 * (1 + 9 * 1.0 / 120) * sin(-134.5 * PI / 180))}//4
		};
		ege_bezier(4, polypoints1);
		
		ege_line(
			coordinateX(width, airspeed_x + airspeed_r * 1.285 * (1 + 9 * 1.0 / 120) * cos(-134.5 * PI / 180)),
			coordinateY(height, airspeed_y + airspeed_r * 1.285 * (1 + 9 * 1.0 / 120) * sin(-134.5 * PI / 180)),
			coordinateX(width, airspeed_x + airspeed_r * 1.3 * (1 + 9 * 1.0 / 120) * cos(-136 * PI / 180)),
			coordinateY(height, airspeed_y + airspeed_r * 1.3 * (1 + 9 * 1.0 / 120) * sin(-136 * PI / 180))
			);
		ege_line(
			coordinateX(width, airspeed_x + airspeed_r * 1.285 * (1 + 9 * 1.0 / 120) * cos(-134.5 * PI / 180)),
			coordinateY(height, airspeed_y + airspeed_r * 1.285 * (1 + 9 * 1.0 / 120) * sin(-134.5 * PI / 180)),
			coordinateX(width, airspeed_x + airspeed_r * 1.245 * (1 + 9 * 1.0 / 120) * cos(-135.2 * PI / 180)),
			coordinateY(height, airspeed_y + airspeed_r * 1.245 * (1 + 9 * 1.0 / 120) * sin(-135.2 * PI / 180))
			);
		
		
		ege_point polypoints2[4]{// 右侧弧线
			{coordinateX(width, airspeed_x + airspeed_r * 1.13 * (1 + 9 * 1.0 / 120) * cos(-136 * PI / 180)),
				coordinateY(height, airspeed_y + airspeed_r * 1.13 * (1 + 9 * 1.0 / 120) * sin(-136 * PI / 180))},//1
			{coordinateX(width, airspeed_x + airspeed_r * 1.15 * (1 + 9 * 1.0 / 120) * cos(-133 * PI / 180)),
				coordinateY(height, airspeed_y + airspeed_r * 1.15 * (1 + 9 * 1.0 / 120) * sin(-133 * PI / 180))},//2
			{coordinateX(width, airspeed_x + airspeed_r * 1.2 * (1 + 9 * 1.0 / 120) * cos(-132 * PI / 180)),
				coordinateY(height, airspeed_y + airspeed_r * 1.2 * (1 + 9 * 1.0 / 120) * sin(-132 * PI / 180))},//3
			{coordinateX(width, airspeed_x + airspeed_r * 1.24 * (1 + 9 * 1.0 / 120) * cos(-132 * PI / 180)),
				coordinateY(height, airspeed_y + airspeed_r * 1.24 * (1 + 9 * 1.0 / 120) * sin(-132 * PI / 180))}//4
		};
		ege_bezier(4, polypoints2);
		
		ege_line(
			coordinateX(width, airspeed_x + airspeed_r * 1.24 * (1 + 9 * 1.0 / 120) * cos(-132 * PI / 180)),
			coordinateY(height, airspeed_y + airspeed_r * 1.24 * (1 + 9 * 1.0 / 120) * sin(-132 * PI / 180)),
			coordinateX(width, airspeed_x + airspeed_r * 1.215 * (1 + 9 * 1.0 / 120) * cos(-133.5 * PI / 180)),
			coordinateY(height, airspeed_y + airspeed_r * 1.215 * (1 + 9 * 1.0 / 120) * sin(-133.5 * PI / 180))
			);
		ege_line(
			coordinateX(width, airspeed_x + airspeed_r * 1.24 * (1 + 9 * 1.0 / 120) * cos(-132 * PI / 180)),
			coordinateY(height, airspeed_y + airspeed_r * 1.24 * (1 + 9 * 1.0 / 120) * sin(-132 * PI / 180)),
			coordinateX(width, airspeed_x + airspeed_r * 1.19 * (1 + 9 * 1.0 / 120) * cos(-131.2 * PI / 180)),
			coordinateY(height, airspeed_y + airspeed_r * 1.19 * (1 + 9 * 1.0 / 120) * sin(-131.2 * PI / 180))
			);
	}
}

void airspeed_indicator_draw_screw(double airspeed_x, double airspeed_y, double airspeed_r, double side, double width, double height) {
	draw_screw(coordinateX(width, airspeed_x + airspeed_r * 1.5 * cos(45 * PI / 180)), coordinateY(height, airspeed_y + airspeed_r * 1.5 * sin(45 * PI / 180)), side / 28.3333333333, 0);
	
	draw_screw(coordinateX(width, airspeed_x + airspeed_r * 1.5 * cos(135 * PI / 180)), coordinateY(height, airspeed_y + airspeed_r * 1.5 * sin(135 * PI / 180)), side / 28.3333333333, 0);
	
	draw_screw(coordinateX(width, airspeed_x + airspeed_r * 1.5 * cos(225 * PI / 180)), coordinateY(height, airspeed_y + airspeed_r * 1.5 * sin(225 * PI / 180)), side / 28.3333333333, 0);
	
	draw_screw(coordinateX(width, airspeed_x + airspeed_r * 1.5 * cos(315 * PI / 180)), coordinateY(height, airspeed_y + airspeed_r * 1.5 * sin(315 * PI / 180)), side / 28.3333333333, 0);
}


void draw_airspeed_three_pointer(double airspeed_x, double airspeed_y, double airspeed_r, double side, double width, double height,double small_pointer_angle1, double small_pointer_angle2, double small_pointer_angle3) {
	
	small_pointer_angle1 = -small_pointer_angle1;
	small_pointer_angle1 = small_pointer_angle1 * PI / 180;
	
	small_pointer_angle2 = -small_pointer_angle2;
	small_pointer_angle2 = small_pointer_angle2 * PI / 180;
	
	small_pointer_angle3 = -small_pointer_angle3;
	small_pointer_angle3 = small_pointer_angle3 * PI / 180;
	
	// 上 (动态)
	double x01 = airspeed_r * 0.95 * cos(0 * PI / 180), y01 = airspeed_r * 0.95 * sin(0 * PI / 180);
	double x02 = airspeed_r * 1.03 * cos(2.8 * PI / 180), y02 = airspeed_r * 1.03 * sin(2.8 * PI / 180);
	double x03 = airspeed_r * 1.12 * cos(2.4 * PI / 180), y03 = airspeed_r * 1.12 * sin(2.4 * PI / 180);
	double x04 = airspeed_r * 1.12 * cos(-2.4 * PI / 180), y04 = airspeed_r * 1.12 * sin(-2.4 * PI / 180);
	double x05 = airspeed_r * 1.03 * cos(-2.8 * PI / 180), y05 = airspeed_r * 1.03 * sin(-2.8 * PI / 180);
	
	ege_setpattern_lineargradient(
		coordinateX(width,x01 * cos(small_pointer_angle1) - y01 * sin(small_pointer_angle1) + airspeed_x), coordinateY(height, x01 * sin(small_pointer_angle1) + y01 * cos(small_pointer_angle1) + airspeed_y),
		EGERGB(35, 43, 52),
		coordinateX(width, x04 * cos(small_pointer_angle1) - y04 * sin(small_pointer_angle1) + airspeed_x), coordinateY(height, x04 * sin(small_pointer_angle1) + y04 * cos(small_pointer_angle1) + airspeed_y),
		EGERGB(35, 43, 52)
		);
	ege_point polypoints1[5] = {
		coordinateX(width,x01 * cos(small_pointer_angle1) - y01 * sin(small_pointer_angle1) + airspeed_x),coordinateY(height,x01 * sin(small_pointer_angle1) + y01 * cos(small_pointer_angle1) + airspeed_y),
		coordinateX(width,x02 * cos(small_pointer_angle1) - y02 * sin(small_pointer_angle1) + airspeed_x),coordinateY(height,x02 * sin(small_pointer_angle1) + y02 * cos(small_pointer_angle1) + airspeed_y),
		coordinateX(width,x03 * cos(small_pointer_angle1) - y03 * sin(small_pointer_angle1) + airspeed_x),coordinateY(height,x03 * sin(small_pointer_angle1) + y03 * cos(small_pointer_angle1) + airspeed_y),
		coordinateX(width,x04 * cos(small_pointer_angle1) - y04 * sin(small_pointer_angle1) + airspeed_x),coordinateY(height,x04 * sin(small_pointer_angle1) + y04 * cos(small_pointer_angle1) + airspeed_y),
		coordinateX(width,x05 * cos(small_pointer_angle1) - y05 * sin(small_pointer_angle1) + airspeed_x),coordinateY(height,x05 * sin(small_pointer_angle1) + y05 * cos(small_pointer_angle1) + airspeed_y)
	};
	ege_fillpoly(5, polypoints1);
	pos_1 = small_pointer_angle1;
	
	// 中（动态
	double x11 = airspeed_r * 0.95 * cos((-60) * PI / 180), y11 = airspeed_r * 0.95 * sin((-60) * PI / 180);
	double x12 = airspeed_r * 1.03 * cos((2.8 - 60) * PI / 180), y12 = airspeed_r * 1.03 * sin((2.8 - 60) * PI / 180);
	double x13 = airspeed_r * 1.12 * cos((2.4 - 60) * PI / 180), y13 = airspeed_r * 1.12 * sin((2.4 - 60) * PI / 180);
	double x14 = airspeed_r * 1.12 * cos((-2.4 - 60) * PI / 180), y14 = airspeed_r * 1.12 * sin((-2.4 - 60) * PI / 180);
	double x15 = airspeed_r * 1.03 * cos((-2.8 - 60) * PI / 180), y15 = airspeed_r * 1.03 * sin((-2.8 - 60) * PI / 180);
	
	ege_setpattern_lineargradient(
		coordinateX(width, x11 * cos(small_pointer_angle2) - y11 * sin(small_pointer_angle2) + airspeed_x), coordinateY(height, x11 * sin(small_pointer_angle2) + y11 * cos(small_pointer_angle2) + airspeed_y),
		EGERGB(35, 43, 52),
		coordinateX(width, x14 * cos(small_pointer_angle2) - y14 * sin(small_pointer_angle2) + airspeed_x), coordinateY(height, x14 * sin(small_pointer_angle2) + y14 * cos(small_pointer_angle2) + airspeed_y),
		EGERGB(35, 43, 52)
		);
	ege_point polypoints2[5] = {
		coordinateX(width,x11 * cos(small_pointer_angle2) - y11 * sin(small_pointer_angle2) + airspeed_x),coordinateY(height,x11 * sin(small_pointer_angle2) + y11 * cos(small_pointer_angle2) + airspeed_y),
		coordinateX(width,x12 * cos(small_pointer_angle2) - y12 * sin(small_pointer_angle2) + airspeed_x),coordinateY(height,x12 * sin(small_pointer_angle2) + y12 * cos(small_pointer_angle2) + airspeed_y),
		coordinateX(width,x13 * cos(small_pointer_angle2) - y13 * sin(small_pointer_angle2) + airspeed_x),coordinateY(height,x13 * sin(small_pointer_angle2) + y13 * cos(small_pointer_angle2) + airspeed_y),
		coordinateX(width,x14 * cos(small_pointer_angle2) - y14 * sin(small_pointer_angle2) + airspeed_x),coordinateY(height,x14 * sin(small_pointer_angle2) + y14 * cos(small_pointer_angle2) + airspeed_y),
		coordinateX(width,x15 * cos(small_pointer_angle2) - y15 * sin(small_pointer_angle2) + airspeed_x),coordinateY(height,x15 * sin(small_pointer_angle2) + y15 * cos(small_pointer_angle2) + airspeed_y)
	};
	ege_fillpoly(5, polypoints2);
	pos_2 = small_pointer_angle2 + 60;
	
	// 下（动态）
	double x21 = airspeed_r * 0.95 * cos((-100) * PI / 180), y21 = airspeed_r * 0.95 * sin((-100) * PI / 180);
	double x22 = airspeed_r * 1.03 * cos((2.8 - 100) * PI / 180), y22 = airspeed_r * 1.03 * sin((2.8 - 100) * PI / 180);
	double x23 = airspeed_r * 1.12 * cos((2.4 - 100) * PI / 180), y23 = airspeed_r * 1.12 * sin((2.4 - 100) * PI / 180);
	double x24 = airspeed_r * 1.12 * cos((-2.4 - 100) * PI / 180), y24 = airspeed_r * 1.12 * sin((-2.4 - 100) * PI / 180);
	double x25 = airspeed_r * 1.03 * cos((-2.8 - 100) * PI / 180), y25 = airspeed_r * 1.03 * sin((-2.8 - 100) * PI / 180);
	
	ege_setpattern_lineargradient(
		coordinateX(width, x21 * cos(small_pointer_angle3) - y21 * sin(small_pointer_angle3) + airspeed_x), coordinateY(height, x21 * sin(small_pointer_angle3) + y21 * cos(small_pointer_angle3) + airspeed_y),
		EGERGB(35, 43, 52),
		coordinateX(width, x24 * cos(small_pointer_angle3) - y24 * sin(small_pointer_angle3) + airspeed_x), coordinateY(height, x24 * sin(small_pointer_angle3) + y24 * cos(small_pointer_angle3) + airspeed_y),
		EGERGB(35, 43, 52)
		);
	ege_point polypoints3[5] = {
		coordinateX(width,x21 * cos(small_pointer_angle3) - y21 * sin(small_pointer_angle3) + airspeed_x),coordinateY(height,x21 * sin(small_pointer_angle3) + y21 * cos(small_pointer_angle3) + airspeed_y),
		coordinateX(width,x22 * cos(small_pointer_angle3) - y22 * sin(small_pointer_angle3) + airspeed_x),coordinateY(height,x22 * sin(small_pointer_angle3) + y22 * cos(small_pointer_angle3) + airspeed_y),
		coordinateX(width,x23 * cos(small_pointer_angle3) - y23 * sin(small_pointer_angle3) + airspeed_x),coordinateY(height,x23 * sin(small_pointer_angle3) + y23 * cos(small_pointer_angle3) + airspeed_y),
		coordinateX(width,x24 * cos(small_pointer_angle3) - y24 * sin(small_pointer_angle3) + airspeed_x),coordinateY(height,x24 * sin(small_pointer_angle3) + y24 * cos(small_pointer_angle3) + airspeed_y),
		coordinateX(width,x25 * cos(small_pointer_angle3) - y25 * sin(small_pointer_angle3) + airspeed_x),coordinateY(height,x25 * sin(small_pointer_angle3) + y25 * cos(small_pointer_angle3) + airspeed_y)
	};
	ege_fillpoly(5, polypoints3);
	pos_3 = small_pointer_angle3 + 100;
}

void airspeed_indicator_msg(double airspeed_x, double airspeed_y, double airspeed_r, double side, double width, double height)
{
	
	if (GetAsyncKeyState(0x02) & 0x8000) {
		if (airspeed_is_down == 0) {
			airspeed_is_down = 1;
			mousepos(&mouse_x, &mouse_y);
			mouse_x_cur = mouse_x;
			mouse_y_cur = mouse_y;
		}
		if (airspeed_is_down == 1) {
			if ((mouse_x_cur >= coordinateX(width,airspeed_x + airspeed_r * 1.23 * (1 + 9 * 1.0 / 120) * cos(-145 * PI / 180))) && (mouse_x_cur <= coordinateX(width,airspeed_x + airspeed_r * 1.23 * (1 + 9 * 1.0 / 120) * cos(-145 * PI / 180)) + airspeed_r / 3.2)
				&& (mouse_y_cur >= coordinateY(height,airspeed_y + airspeed_r * 1.23 * (1 + 9 * 1.0 / 120) * sin(-145 * PI / 180))) && (mouse_y_cur <= coordinateY(height,airspeed_y + airspeed_r * 1.23 * (1 + 9 * 1.0 / 120) * sin(-145 * PI / 180)) + airspeed_r / 3.2)) {
				
				mousepos(&mouse_x, &mouse_y);
				if (mouse_y > mouse_y_cur) {
					knob_angle -= (mouse_y - mouse_y_cur) / 70;
					commandbug_angle -= (mouse_y - mouse_y_cur) / 70;
				}
				else {
					knob_angle -= (mouse_y - mouse_y_cur) / 70;
					commandbug_angle -= (mouse_y - mouse_y_cur) / 70;
				}
			}
		}
		
	}
	else if (airspeed_is_down == 1) {
		airspeed_is_down = 0;
	}
	
	// 上小指针
	if (GetAsyncKeyState(0x02) & 0x8000) {
		if (airspeed_is_down1 == 0) {
			airspeed_is_down1 = 1;
			mousepos(&mouse_x1, &mouse_y1);
			mouse_x_cur1 = mouse_x1;
			mouse_y_cur1 = mouse_y1;
		}
		if (airspeed_is_down1 == 1) {
			double cita1 = coordinateY(height,mouse_y_cur1) - coordinateY(height,airspeed_y);
			double cita2 = coordinateX(width,mouse_x_cur1) - coordinateX(width,airspeed_x);
			double cita3 = atan(cita1 / cita2);
			if (4 >= fabs(cita3 - pos_1) && mouse_x_cur1 >= coordinateX(width,airspeed_x)) {
				if (mouse_y1 > mouse_y_cur1) {
					small_pointer_angle1 += (mouse_y1 - mouse_y_cur1) / 0.4;
				}
				else {
					small_pointer_angle1 += (mouse_y1 - mouse_y_cur1) / 0.4;
				}
			}
		}
		
	}
	else if (airspeed_is_down1 == 1) {
		airspeed_is_down1 = 0;
	}
	
	// 中小指针
	if (GetAsyncKeyState(0x02) & 0x8000) {
		if (airspeed_is_down2 == 0) {
			airspeed_is_down2 = 1;
			mousepos(&mouse_x2, &mouse_y2);
			mouse_x_cur2 = mouse_x2;
			mouse_y_cur2 = mouse_y2;
		}
		if (airspeed_is_down2 == 1) {
			double cita1 = coordinateY(height, mouse_y_cur1) - coordinateY(height, airspeed_y);
			double cita2 = coordinateX(width, mouse_x_cur1) - coordinateX(width, airspeed_x);
			double cita3 = atan(cita1 / cita2);
			if (10 >= fabs(cita3 - pos_2)) {
				mousepos(&mouse_x2, &mouse_y2);
				if (mouse_y2 > mouse_y_cur2) {
					small_pointer_angle2 += (mouse_y2 - mouse_y_cur2) / 0.4;
				}
				else {
					small_pointer_angle2 += (mouse_y2 - mouse_y_cur2) / 0.4;
				}
			}
		}
		
	}
	else if (airspeed_is_down2 == 1) {
		airspeed_is_down2 = 0;
	}
	
	// 下小指针
	if (GetAsyncKeyState(0x02) & 0x8000) {
		if (airspeed_is_down3 == 0) {
			airspeed_is_down3 = 1;
			mousepos(&mouse_x3, &mouse_y3);
			mouse_x_cur3 = mouse_x3;
			mouse_y_cur3 = mouse_y3;
		}
		if (airspeed_is_down3 == 1) {
			double cita1 = coordinateY(height, mouse_y_cur1) - coordinateY(height, airspeed_y);
			double cita2 = coordinateX(width, mouse_x_cur1) - coordinateX(width, airspeed_x);
			double cita3 = atan(cita1 / cita2);
			if (10 >= fabs(cita3 - pos_3)) {
				mousepos(&mouse_x3, &mouse_y3);
				if (mouse_y3 > mouse_y_cur3) {
					small_pointer_angle3 -= (mouse_y3 - mouse_y_cur3) / 0.4;
				}
				else {
					small_pointer_angle3 -= (mouse_y3 - mouse_y_cur3) / 0.4;
				}
			}
		}
		
	}
	else if (airspeed_is_down3 == 1) {
		airspeed_is_down3 = 0;
	}
}

