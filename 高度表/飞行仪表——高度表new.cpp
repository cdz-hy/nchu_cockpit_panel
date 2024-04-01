#include <graphics.h>
#include <stdio.h>
#include<math.h>

#define WIDTH 1500
#define LENTH 1000
#define alt_indicator_r 600//半径
double alt_indicator_x = 600;
double alt_indicator_y = 400;

struct alt_pointer {
	//中心圆的相关参数
	double r = alt_indicator_r * 0.01;//半径
	double circle_x = alt_indicator_x - r;//椭圆矩形左上角x；
	double circle_y = alt_indicator_y - r;//椭圆矩形左上角y；
	double w = 2 * r;
	double h = w;

	//指针杆的相关参数(线段)
	double pointer_r = alt_indicator_r * 0.35;
	
	//针头的相关参数
	
	//首先是每个点的坐标；
	double point_x1 = alt_indicator_x + alt_indicator_r * 0.35;
	double point_y1 = alt_indicator_y;

	//double 
}alt_pointer;


struct alt_indicator_scale {
	
	double R = 0.5 * alt_indicator_r;

	//刻度相关参数

	double r_outer = R - (R / 24);
	double small_r_inner = R * 376 / 434;
	double large_r_inner = R * 331 / 434;
	double small_r_outer = r_outer;
	double large_r_outer = r_outer;
	
	double number_r = R * 251 / 365;
	double number_height = R / 4.5;
	double number_width = R / 9;

	//100的参数

	double height_100 = number_height / 2;
	double width_100 = number_width / 2;
	double x_100 = alt_indicator_x - large_r_inner * sin(PI / 12) - 0.05 * R;
	double y_100 = alt_indicator_y - large_r_inner * cos(PI / 12);
	
	//FT的参数

	double FT_height = height_100;
	double FT_width = width_100;
	double FT_x = alt_indicator_x + large_r_inner * sin(PI / 12) + 0.05 * R;
	double FT_y = alt_indicator_y - large_r_inner * cos(PI / 12);


	//字符ALT参数

	double ALT_height = R / 6;
	double ALT_width = R / 15;
	
	//下小行字参数

	double small_words_height = R / 9;
	double small_words_width = R / 25;

}alt_indicator_Scale;


struct alt_indicator_frames {
	double large_frame_height = alt_indicator_Scale.R * 0.4;
	double large_frame_width = 1.2 * alt_indicator_Scale.R;
	double large_frame_x = alt_indicator_x - 0.5 * large_frame_width;
	double large_frame_y = alt_indicator_y - 0.5 * alt_indicator_Scale.R;
	double small_frame_height = alt_indicator_Scale.R * 0.18;
	double small_frame_width = alt_indicator_Scale.R * 0.4;
	double small_frame_y = alt_indicator_y + 0.35 * alt_indicator_Scale.R;
	double small_frame_x1 = alt_indicator_x - 0.6 * alt_indicator_Scale.R;
	double small_frame_x2 = alt_indicator_x + 0.6 * alt_indicator_Scale.R - small_frame_width;
}alt_indicator_Frames;

//画背景

void draw_frame(double frame_x, double frame_y, double frame_side) {//画整个表外框

	double frame_lefttop_x = frame_x - frame_side / 2.0;
	double frame_lefttop_y = frame_y - frame_side / 2.0;
	double R = frame_side / 52.0 * 25; //表盘的半径
	double R1 = frame_side / 2; //表盘阴影的半径

	int num_points1 = 8;

	// 设置外八边形各点
	ege_point frame_polypoints1[8] = {
		{frame_lefttop_x  ,frame_lefttop_y + frame_side / 26 * 2},
		{frame_lefttop_x + frame_side / 26 * 4,frame_lefttop_y - frame_side / 13},
		{frame_lefttop_x + frame_side - frame_side / 26 * 2,frame_lefttop_y - frame_side / 13},
		{frame_lefttop_x + frame_side + frame_side / 13,frame_lefttop_y + frame_side / 26 * 2},
		{frame_lefttop_x + frame_side + frame_side / 13,frame_lefttop_y + frame_side - frame_side / 26 * 4},
		{frame_lefttop_x + frame_side - frame_side / 26 * 2,frame_lefttop_y + frame_side },
		{frame_lefttop_x + frame_side / 26 * 4,frame_lefttop_y + frame_side },
		{frame_lefttop_x ,frame_lefttop_y + frame_side - frame_side / 26 * 4}
	};

	// 左上角到右下角渐变色函数
	ege_setpattern_lineargradient(frame_lefttop_x + frame_side / 52, frame_lefttop_y + frame_side / 52, EGEARGB(0XFF, 0x63, 0x62, 0x66),
		frame_lefttop_x + frame_side + frame_side / 52, frame_lefttop_y + frame_side + frame_side / 52, EGEARGB(0XFF, 0x53, 0x52, 0x56));
	ege_fillpoly(num_points1, frame_polypoints1);

	int num_points2 = 5;
	ege_point frame_polypoints2[5] = {
		{frame_lefttop_x - frame_side / 26 + frame_side / 250,frame_lefttop_y + frame_side / 26 * 3 - frame_side / 250} ,
		{frame_lefttop_x + frame_side / 26 * 3 + frame_side / 250,frame_lefttop_y - frame_side / 26 - frame_side / 250},
		{frame_lefttop_x + frame_side - frame_side / 26 * 3 + frame_side / 250,frame_lefttop_y - frame_side / 26 - frame_side / 250},
		{frame_lefttop_x + frame_side + frame_side / 26 + frame_side / 250,frame_lefttop_y + frame_side / 26 * 3 - frame_side / 250} ,
		{frame_lefttop_x + frame_side + frame_side / 26 + frame_side / 250,frame_lefttop_y + frame_side - frame_side / 26 * 3 - frame_side / 250}
	};

	ege_setpattern_lineargradient(frame_lefttop_x + frame_side / 26 * 3 + frame_side / 250, frame_lefttop_y - frame_side / 26 - frame_side / 250, EGEARGB(0XBF, 0XFF, 0XFF, 0XFF),
		frame_lefttop_x + frame_side + frame_side / 26 + frame_side / 250, frame_lefttop_y + frame_side - frame_side / 26 * 3 - frame_side / 250, EGEARGB(0X22, 0XFF, 0XFF, 0XFF));
	ege_fillpoly(num_points2, frame_polypoints2);

	// 边框颜色
	int num_points3 = 8;
	ege_point frame_polypoints3[8] = {
		{frame_lefttop_x - frame_side / 26 ,frame_lefttop_y + frame_side / 26 * 3},
		{frame_lefttop_x + frame_side / 26 * 3,frame_lefttop_y - frame_side / 26},
		{frame_lefttop_x + frame_side - frame_side / 26 * 3,frame_lefttop_y - frame_side / 26},
		{frame_lefttop_x + frame_side + frame_side / 26,frame_lefttop_y + frame_side / 26 * 3},
		{frame_lefttop_x + frame_side + frame_side / 26,frame_lefttop_y + frame_side - frame_side / 26 * 3},
		{frame_lefttop_x + frame_side - frame_side / 26 * 3,frame_lefttop_y + frame_side + frame_side / 26},
		{frame_lefttop_x + frame_side / 26 * 3,frame_lefttop_y + frame_side + frame_side / 26},
		{frame_lefttop_x - frame_side / 26,frame_lefttop_y + frame_side - frame_side / 26 * 3}
	};
	ege_setpattern_lineargradient(frame_lefttop_x, frame_lefttop_y, EGEARGB(0xFF, 0x73, 0x72, 0x76),
		frame_lefttop_x + frame_side, frame_lefttop_y + frame_side, EGEARGB(0XFF, 0X33, 0X32, 0X36));
	ege_fillpoly(num_points3, frame_polypoints3);

	// 表盘阴影
	ege_setpattern_lineargradient(frame_x - R1 * cos(PI / 4), frame_y - R1 * sin(PI / 4), EGEARGB(0XFF, 0X00, 0X00, 0X00),
		frame_x + R1 * cos(PI / 4), frame_y + R1 * sin(PI / 4), EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillellipse(frame_lefttop_x, frame_lefttop_y, frame_side, frame_side);

	// 表盘颜色
	ege_setpattern_lineargradient(frame_x - R * cos(PI / 4), frame_y - R * sin(PI / 4), EGEARGB(0XFF, 0X35, 0X35, 0X35),
		frame_x + R * cos(PI / 4), frame_y + R * sin(PI / 4), EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillellipse(frame_lefttop_x + frame_side / 52, frame_lefttop_y + frame_side / 52, frame_side - frame_side / 26, frame_side - frame_side / 26);

}

//画刻度

void alt_indicator_draw_scale() {
	setcolor(WHITE);
	setlinewidth(alt_indicator_r / 150);
	//setlinewidth(alt_indicator_r * 3 / 240);
	for (int i = 0; i < 10; i++) {//大刻度
		ege_line(alt_indicator_x + (alt_indicator_Scale.large_r_inner) * cos(PI / 2 + i * PI / 5), alt_indicator_y + alt_indicator_Scale.large_r_inner * sin(PI / 2 + i * PI / 5),
			alt_indicator_x + alt_indicator_Scale.large_r_outer * cos(PI / 2 + i * PI / 5), alt_indicator_y + alt_indicator_Scale.large_r_outer * sin(PI / 2 + i * PI / 5));
	}
	
	for (int i = 0; i < 50; i++) {//小刻度
		ege_line(alt_indicator_x + (alt_indicator_Scale.small_r_inner) * cos(PI / 2 + i * PI / 25), alt_indicator_y + alt_indicator_Scale.small_r_inner * sin(PI / 2 + i * PI / 25),
			alt_indicator_x + alt_indicator_Scale.small_r_outer * cos(PI / 2 + i * PI / 25), alt_indicator_y + alt_indicator_Scale.small_r_outer * sin(PI / 2 + i * PI / 25));
	}
}

//画刻度上的数字

void alt_indicator_draw_numbers() {
	settextjustify(CENTER_TEXT, CENTER_TEXT);//设定对齐方式；
	char num[10] = { '0','I','2','3','4','5','6','7','8','9' };
	setbkmode(TRANSPARENT);//设置文字背景色为透明;
	setfont(alt_indicator_Scale.number_height, alt_indicator_Scale.number_width, "爱奇艺黑体", 0, 0, 0, 0, 0, 0);//设定字体
	for (int i = 1;i <= 9;i++) {
		outtextxy(alt_indicator_x + (alt_indicator_Scale.number_r) * cos(i * PI / 5 - PI / 2), alt_indicator_y + alt_indicator_Scale.number_r * sin(i * PI / 5 - PI / 2), num[i]);
	}//绘制数字；
}

//画字符

void alt_indicator_draw_words() {
	settextjustify(CENTER_TEXT, CENTER_TEXT);//设定对齐方式；
	char ALT[4] = "ALT";
	char MB[3] = "MB";
	char INHG[6] = "IN HG";
	setbkmode(TRANSPARENT);//设置文字背景色为透明;
	
	//setfont(alt_indicator_Scale.small_words_height, alt_indicator_Scale.small_words_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	//outtextxy(alt_indicator_x - (alt_indicator_Scale.R * 2 / 5), alt_indicator_y + (alt_indicator_Scale.R * 2 / 15) + alt_indicator_r * 0.05, MB);
	//outtextxy(alt_indicator_x + (alt_indicator_Scale.R * 2 / 5), alt_indicator_y + (alt_indicator_Scale.R * 2 / 15) + alt_indicator_r * 0.05, INHG);
	
	//绘制100
	setfont(alt_indicator_Scale.height_100 ,alt_indicator_Scale.width_100 ,"爱奇艺黑体" ,150,150,100,false,false,false);
	outtextxy(alt_indicator_Scale.x_100, alt_indicator_Scale.y_100,"I00");

	//绘制FT
	setfont(alt_indicator_Scale.FT_height, alt_indicator_Scale.FT_width, "Calibri", -150, -150, 100, false, false, false);
	outtextxy(alt_indicator_Scale.FT_x, alt_indicator_Scale.FT_y, "FT");

	//绘制ALT
	setfont(alt_indicator_Scale.ALT_height, alt_indicator_Scale.ALT_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	outtextxy(alt_indicator_x + alt_indicator_r * 50 / 434, alt_indicator_y, ALT);
}//画英文字母

//画内部框

void alt_indicator_draw_innerframes() {
	ege_enable_aa(true);
	ege_rectangle(alt_indicator_Frames.large_frame_x,
		alt_indicator_Frames.large_frame_y,
		alt_indicator_Frames.large_frame_width,
		alt_indicator_Frames.large_frame_height);
	//setcolor(BLACK);
	ege_rectangle(alt_indicator_Frames.small_frame_x1,
		alt_indicator_Frames.small_frame_y,
		alt_indicator_Frames.small_frame_width,
		alt_indicator_Frames.small_frame_height);
	ege_rectangle(alt_indicator_Frames.small_frame_x2,
		alt_indicator_Frames.small_frame_y,
		alt_indicator_Frames.small_frame_width,
		alt_indicator_Frames.small_frame_height);

}//画内部框

//画指针

void alt_indicator_draw_pointer() {
	
	ege_setpattern_none();//取消渐变填充
	
	//绘制中心圆
	setfillcolor(WHITE);
	ege_fillellipse(alt_pointer.circle_x, alt_pointer.circle_y, alt_pointer.w, alt_pointer.h);

	//绘制针杆（线段）
	setlinewidth(alt_indicator_r / 100);
	ege_line(alt_indicator_x, alt_indicator_y , alt_pointer.circle_x + alt_pointer.pointer_r, alt_indicator_y);

	//绘制针头（六边形）

}

int main() {

	initgraph(WIDTH, LENTH);//设置背景色为白色；
	setbkcolor(WHITE);
	draw_frame(alt_indicator_x, alt_indicator_y, alt_indicator_r); //画表盘；
	alt_indicator_draw_scale(); //画刻度
	alt_indicator_draw_numbers();//画数字
	alt_indicator_draw_words();//画英语字体
	//alt_indicator_draw_innerframes();//画内部框
	alt_indicator_draw_pointer();//画指针；
	getch();
	closegraph;

	return 0;
}


