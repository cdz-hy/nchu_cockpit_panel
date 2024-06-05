#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>

#include "DrawFrame.h"

//函数声明

void draw_PFD_AI(double AI_x, double AI_y, double AI_side );
void draw_PFD_airspeed(double center_x, double center_y, double side);
void draw_PFD_alt( double center_x, double center_y, double side);
void draw_PFD_compass(double compass_x, double compass_y, double side);
void draw_PFD_RCDI(double RCDI_x,double RCDI_y,double RCDI_side);
void draw_PFD_top(double top_x, double top_y, double side) ;
void draw_1(double x, double y, double side);



//==================================以下为绘制总表部分========================================//


void draw_PFD(double PFD_x, double PFD_y, double PFD_side){
	
	draw_PFD_AI(PFD_x, PFD_y ,PFD_side);
	
	draw_PFD_compass(PFD_x , PFD_y + 64.0 / 96 * PFD_side,PFD_side);
	
	draw_PFD_airspeed(PFD_x - 34.5 / 96 * PFD_side, PFD_y ,PFD_side);
	
	draw_PFD_alt(PFD_x + 35.0 / 96 * PFD_side, PFD_y ,PFD_side);
	
	draw_PFD_RCDI(PFD_x + 49.5 / 96 * PFD_side, PFD_y ,PFD_side);
	
	draw_PFD_frame(PFD_x + 0.06 * PFD_side, PFD_y ,PFD_side);
	
	draw_PFD_top(PFD_x, PFD_y - 41.0 / 96 * PFD_side,PFD_side);
	
	draw_1(PFD_x  + 20.0 / 96 * PFD_side, PFD_y - 31.0 / 96 * PFD_side,PFD_side);
	
}
//==========================================================================================//




//==================================以下为姿态仪部分========================================//



#define Background_color EGEARGB(0xff,0x1b,0x20,0x25)
#define Frame_color1 EGEARGB(0xff,0x24,0x28,0x33)	//EGEARGB(0xff,0x53,0x52,0x56)   // 0xff,0x39,0x39,0x40
#define Frame_color2 EGEARGB(0xff,0x1f,0x23,0x2e)	//24，28，33	//0xff,0x2f,0x2f,0x32

//函数声明

void draw_PFD_AI_background();
void draw_PFD_AI_gear();
void draw_PFD_AI_pointer();
void draw_PFD_AI_occlusion();

//引用全局变量
extern double pitchAngle;
extern double rollAngle;
extern double sideSlipAngle;
extern double headingIndication;
extern double glideIndication;


double AI_x = 0;
double AI_y = 0;
double AI_side = 0;

//注意，这里的side并不是真正的边长，而只是PFD的高，PFD并非严格正方形
void draw_PFD_AI(double x, double y, double side){
	
	AI_x = x;
	AI_y = y;
	AI_side = side / 4;//即一半的边长
	
	//绘制天空地面背景
	draw_PFD_AI_background();
	
	//绘制刻度
	draw_PFD_AI_gear();
	
	//绘制飞机指示和滚转指针
	draw_PFD_AI_pointer();
	
	//绘制周围遮挡的（黑边）
	draw_PFD_AI_occlusion();
	
//	if (GetAsyncKeyState(0x41) & 0x8000)
//		rollAngle -= 0.002;
//	if (GetAsyncKeyState(0x44) & 0x8000)
//		rollAngle += 0.002;
//	if (GetAsyncKeyState(0x57) & 0x8000)
//		pitchAngle += 0.002;
//	if (GetAsyncKeyState(0x53) & 0x8000)
//		pitchAngle -= 0.002;
	
}


void draw_PFD_AI_background(){
	
	//10度显示为为176分之74(约0.42)的side(半个边长)的距离,即1度0.042
	//10度显示为为717分之74(约0.1032)的side(高)的距离,即1度100分之1(按上面这个来)
	
	//需要被遮盖的背景圆的半径
	double AI_r = sqrt(2) * AI_side;
	
	//通过坐标系变换和遮盖实现圆角矩形的指示
	if(pitchAngle >= 0){
		
		//画天空
		setfillcolor(EGEARGB(0xff,0x10,0x86,0xcf));
		ege_fillellipse(AI_x - AI_r,AI_y - AI_r,2 * AI_r,2 * AI_r);
		
		//画地面
		ege_transform_matrix m;
		ege_get_transform(&m);
		ege_transform_translate(AI_x,AI_y);
		ege_transform_rotate(360 * rollAngle / 2 / PI);
		setfillcolor(EGEARGB(0xff,0x6e,0x33,0x07));
		setcolor(WHITE);
		setlinewidth(0.012 * AI_r);
		if(2 * AI_side - 2 * (360 * pitchAngle / 2 / PI * 0.02 * AI_r) > 0){
			ege_fillpie(-AI_r + 0.38 * (360 * pitchAngle / 2 / PI * 0.042045 * AI_side) ,-AI_r + 2 * (360 * pitchAngle / 2 / PI * 0.042045 * AI_side),2 * AI_r - 0.76 * (360 * pitchAngle / 2 / PI * 0.042045 * AI_side),2 * AI_r - 2 * (360 * pitchAngle / 2 / PI * 0.042045 * AI_side),0,180);
			//天地中间的白线
			ege_pie(-AI_r + 0.38 * (360 * pitchAngle / 2 / PI * 0.042045 * AI_side), -AI_r + 2 * (360 * pitchAngle / 2 / PI * 0.042045 * AI_side),2 * AI_r - 0.76 * (360 * pitchAngle / 2 / PI * 0.042045 * AI_side),2 * AI_r - 2 * (360 * pitchAngle / 2 / PI * 0.042045 * AI_side),0,180);
		}
		ege_set_transform(&m);
		
	}
	else{
		
		//画地面
		setfillcolor(EGEARGB(0xff,0x6e,0x33,0x07));
		ege_fillellipse(AI_x - AI_r,AI_y - AI_r,2 * AI_r,2 * AI_r);
		
		//画天空
		ege_transform_matrix m;
		ege_get_transform(&m);
		ege_transform_translate(AI_x,AI_y);
		ege_transform_rotate(360 * rollAngle / 2 / PI);
		setfillcolor(EGEARGB(0xff,0x10,0x86,0xcf));
		setcolor(WHITE);
		setlinewidth(0.012 * AI_r);
		if(2 * AI_side - 2 * (360 * pitchAngle / 2 / PI * 0.02 * AI_r) > 0){
			ege_fillpie(-AI_r - 0.38 * (360 * pitchAngle / 2 / PI * 0.042045 * AI_side), -AI_r,2 * AI_r + 0.76 * (360 * pitchAngle / 2 / PI * 0.042045 * AI_side),2 * AI_r + 2 * (360 * pitchAngle / 2 / PI * 0.042045 * AI_side),-180,180);
			//天地中间的白线
			ege_pie(-AI_r - 0.38 * (360 * pitchAngle / 2 / PI * 0.042045 * AI_side), -AI_r,2 * AI_r + 0.76 * (360 * pitchAngle / 2 / PI * 0.042045 * AI_side),2 * AI_r + 2 * (360 * pitchAngle / 2 / PI * 0.042045 * AI_side),-180,180);
		}
		ege_set_transform(&m);
		
	}
	
	
}


void draw_PFD_AI_gear(){
	
	
	//俯仰角刻度
	
	setcolor(WHITE);
	setlinewidth(0.012 * AI_side);
	double AI_line_lx;
	double AI_line_ly;
	double AI_line_rx;
	double AI_line_ry;
	double AI_circle_x;
	double AI_circle_y;
	
	
	//设置刻度字体格式等
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	LOGFONTW AI_font;
	setfont(0.12 * AI_side,0.08 * AI_side,"Bahnschrift Light");
	getfont(&AI_font);
	AI_font.lfEscapement = -10 * 360 * rollAngle / 2 / PI;
	AI_font.lfWeight = 2.2 * AI_side;
	setfont(&AI_font);
	double AI_gear_x;
	double AI_gear_y;
	
	for(double i= -90;i <= 90;i += 2.5){
		if(i == 0){
			
		}
		else if(fabs(fmod(i,10)) <= 0.001){
//			//旋转前原坐标
//			AI_line_lx = AI_x - 0.43 * AI_side;
//			AI_line_ly = AI_y - 0.042045 * i * AI_side;
//			AI_line_rx = AI_x + 0.43 * AI_side;
//			AI_line_ry = AI_y - 0.042045 * i * AI_side;
			
			AI_line_lx = (AI_x - (AI_x - 0.43 * AI_side)) * cos(rollAngle) - ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.042045  * AI_side) - AI_y) * sin(rollAngle) + AI_x;
			AI_line_ly = ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.042045  * AI_side) - AI_y) * cos(rollAngle) + (AI_x - (AI_x - 0.43 * AI_side)) * sin(rollAngle) + AI_y;
			AI_line_rx = (AI_x - (AI_x + 0.43 * AI_side)) * cos(rollAngle) - ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.042045  * AI_side) - AI_y) * sin(rollAngle) + AI_x;
			AI_line_ry = ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.042045  * AI_side) - AI_y) * cos(rollAngle) + (AI_x - (AI_x + 0.43 * AI_side)) * sin(rollAngle) + AI_y;
			
			if((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly) <= 1.5 * AI_side * 1.5 * AI_side)
				ege_line(AI_line_lx, AI_line_ly, AI_line_rx, AI_line_ry);
			
			
			//刻度示数
			AI_gear_x = (AI_x - (AI_x - 0.50 * AI_side)) * cos(rollAngle) - ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.042045  * AI_side + 0.015 * AI_side) - AI_y) * sin(rollAngle) + AI_x;
			AI_gear_y = ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.042045  * AI_side + 0.015 * AI_side) - AI_y) * cos(rollAngle) + (AI_x - (AI_x - 0.50 * AI_side)) * sin(rollAngle) + AI_y;
			if(sqrt((AI_gear_x - AI_x) * (AI_gear_x - AI_x) + (AI_gear_y - AI_y) * (AI_gear_y - AI_y)) <= 1.5 * AI_side){
				char tmp[3];
				sprintf(tmp,"%d",abs((int)i));
				ege_drawtext(tmp, AI_gear_x, AI_gear_y);
			}
			AI_gear_x = (AI_x - (AI_x + 0.495 * AI_side)) * cos(rollAngle) - ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.042045  * AI_side + 0.015 * AI_side) - AI_y) * sin(rollAngle) + AI_x;
			AI_gear_y = ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.042045  * AI_side + 0.015 * AI_side) - AI_y) * cos(rollAngle) + (AI_x - (AI_x + 0.495 * AI_side)) * sin(rollAngle) + AI_y;
			if(sqrt((AI_gear_x - AI_x) * (AI_gear_x - AI_x) + (AI_gear_y - AI_y) * (AI_gear_y - AI_y)) <= 1.5 * AI_side){
				char tmp[3];
				sprintf(tmp,"%d",abs((int)i));
				ege_drawtext(tmp, AI_gear_x, AI_gear_y);
			}
			
			
		}
		else if(fabs(fmod(i,5)) <= 0.001){
//			AI_line_lx = AI_x - 0.21 * AI_side;
//			AI_line_ly = AI_y - 0.042045 * i * AI_side;
//			AI_line_rx = AI_x + 0.21 * AI_side;
//			AI_line_ry = AI_y - 0.042045 * i * AI_side;
			
			AI_line_lx = (AI_x - (AI_x - 0.21 * AI_side)) * cos(rollAngle) - ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.042045  * AI_side) - AI_y) * sin(rollAngle) + AI_x;
			AI_line_ly = ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.042045  * AI_side) - AI_y) * cos(rollAngle) + (AI_x - (AI_x - 0.21 * AI_side)) * sin(rollAngle) + AI_y;
			AI_line_rx = (AI_x - (AI_x + 0.21 * AI_side)) * cos(rollAngle) - ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.042045  * AI_side) - AI_y) * sin(rollAngle) + AI_x;
			AI_line_ry = ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.042045  * AI_side) - AI_y) * cos(rollAngle) + (AI_x - (AI_x + 0.21 * AI_side)) * sin(rollAngle) + AI_y;
			
			if((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly) <= 1.5 * AI_side * 1.5 * AI_side)
				ege_line(AI_line_lx, AI_line_ly, AI_line_rx, AI_line_ry);
		}
		else if(fabs(fmod(i,2.5)) <= 0.001){
//			AI_line_lx = AI_x - 0.12 * AI_side;
//			AI_line_ly = AI_y + (i - (360 * pitchAngle / 2 / PI)) * 0.042045  * AI_side;
//			AI_line_rx = AI_x + 0.12 * AI_side;
//			AI_line_ry = AI_y + (i - (360 * pitchAngle / 2 / PI)) * 0.042045  * AI_side;
			
			AI_line_lx = (AI_x - (AI_x - 0.12 * AI_side)) * cos(rollAngle) - ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.042045  * AI_side) - AI_y) * sin(rollAngle) + AI_x;
			AI_line_ly = ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.042045  * AI_side) - AI_y) * cos(rollAngle) + (AI_x - (AI_x - 0.12 * AI_side)) * sin(rollAngle) + AI_y;
			AI_line_rx = (AI_x - (AI_x + 0.12 * AI_side)) * cos(rollAngle) - ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.042045  * AI_side) - AI_y) * sin(rollAngle) + AI_x;
			AI_line_ry = ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.042045  * AI_side) - AI_y) * cos(rollAngle) + (AI_x - (AI_x + 0.12 * AI_side)) * sin(rollAngle) + AI_y;
			
			if((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly) <= 1.5 * AI_side * 1.5 * AI_side)
				ege_line(AI_line_lx, AI_line_ly, AI_line_rx, AI_line_ry);
			
			
		}
	}
	
	
}



void draw_PFD_AI_pointer(){
	
	
	
	//绘制指示(飞机)标志
	
	//中间方框
	setcolor(WHITE);
	setlinewidth(0.015 * AI_side);
	ege_rectangle(AI_x - 0.04 * AI_side, AI_y - 0.04 * AI_side , 0.08 * AI_side, 0.08 * AI_side);
	
	
	//右侧
	setcolor(BLACK);
	setlinewidth(0.06 * AI_side);
	//黑线
	ege_line(AI_x + 0.38 * AI_side, AI_y, AI_x + 0.81 * AI_side, AI_y);
	ege_line(AI_x + 0.38 * AI_side, AI_y - 0.03 * AI_side, AI_x + 0.38 * AI_side, AI_y + 0.14 * AI_side);
	setcolor(WHITE);
	setlinewidth(0.015 * AI_side);
	//白线边框
	ege_line(AI_x + 0.343 * AI_side, AI_y - 0.03 * AI_side, AI_x + 0.817 * AI_side, AI_y - 0.03 * AI_side);
	ege_line(AI_x + 0.41 * AI_side, AI_y + 0.03 * AI_side, AI_x + 0.817 * AI_side, AI_y + 0.03 * AI_side);
	ege_line(AI_x + 0.343 * AI_side, AI_y + 0.14 * AI_side, AI_x + 0.410 * AI_side, AI_y + 0.14 * AI_side);
	
	ege_line(AI_x + 0.817 * AI_side, AI_y - 0.037 * AI_side, AI_x + 0.817 * AI_side, AI_y + 0.037 * AI_side);
	ege_line(AI_x + 0.343 * AI_side, AI_y - 0.037 * AI_side, AI_x + 0.343 * AI_side, AI_y + 0.147 * AI_side);
	ege_line(AI_x + 0.417 * AI_side, AI_y + 0.03 * AI_side, AI_x + 0.417 * AI_side, AI_y + 0.147 * AI_side);
	
	//左侧
	setcolor(BLACK);
	setlinewidth(0.06 * AI_side);
	//黑线
	ege_line(AI_x - 0.38 * AI_side, AI_y, AI_x - 0.81 * AI_side, AI_y);
	ege_line(AI_x - 0.38 * AI_side, AI_y - 0.03 * AI_side, AI_x - 0.38 * AI_side, AI_y + 0.14 * AI_side);
	setcolor(WHITE);
	setlinewidth(0.015 * AI_side);
	//白线边框
	ege_line(AI_x - 0.343 * AI_side, AI_y - 0.03 * AI_side, AI_x - 0.817 * AI_side, AI_y - 0.03 * AI_side);
	ege_line(AI_x - 0.41 * AI_side, AI_y + 0.03 * AI_side, AI_x - 0.817 * AI_side, AI_y + 0.03 * AI_side);
	ege_line(AI_x - 0.343 * AI_side, AI_y + 0.14 * AI_side, AI_x - 0.410 * AI_side, AI_y + 0.14 * AI_side);
	
	ege_line(AI_x - 0.817 * AI_side, AI_y - 0.037 * AI_side, AI_x - 0.817 * AI_side, AI_y + 0.037 * AI_side);
	ege_line(AI_x - 0.343 * AI_side, AI_y - 0.037 * AI_side, AI_x - 0.343 * AI_side, AI_y + 0.147 * AI_side);
	ege_line(AI_x - 0.417 * AI_side, AI_y + 0.03 * AI_side, AI_x - 0.417 * AI_side, AI_y + 0.147 * AI_side);
	
	
	
	//绘制上方固定的蓝色遮挡
	setcolor(EGEARGB(0xff,0x10,0x86,0xcf));
	setlinewidth(0.1 * AI_side);
	//原本两个椭圆弧模拟的，因为边缘的角度问题用不了
//	ege_arc(AI_x - 1.23 * AI_side, AI_y - 1 * AI_side, 2.46 * AI_side, 2.3 * AI_side, -150, 120);
//	ege_arc(AI_x - 1.23 * AI_side, AI_y - 1.2 * AI_side, 2.46 * AI_side, 2.3 * AI_side, -150, 120);
	//新版循环画多个细的椭圆弧
	for(double i = 0.5;i >= 0;i -= 0.02){
		ege_arc(AI_x - (1.05 + i) * AI_side, AI_y - (0.85 + i) * AI_side, (2.1 + 2 * i) * AI_side, (1.7 + 2 * i) * AI_side, -150, 120);
	}	
	
	//蓝色遮挡上表示横滚角的刻度
	setcolor(WHITE);
	setlinewidth(0.015 * AI_side);
	
	//旋转前坐标
	double AI_pointTmp1_x = AI_x;
	double AI_pointTmp1_y = AI_y - 0.95 * AI_side;
	double AI_pointTmp2_x = AI_x;
	double AI_pointTmp2_y = AI_y - 1.05 * AI_side;
	
	for(int i = -60; i <= 60; i += 5){
		if(i == 10 || i == -10 || i == 20 || i == -20 || i == 45 || i == -45 || i == 60 || i == -60){
			AI_pointTmp1_x = - (AI_y - 0.95 * AI_side - AI_y) * sin(1.0 * i / 360 * 2 * PI) + AI_x;
			AI_pointTmp1_y = (AI_y - 0.95 * AI_side - AI_y) * cos(1.0 * i / 360 * 2 * PI) + AI_y;
			AI_pointTmp2_x = - (AI_y - 1.05 * AI_side - AI_y) * sin(1.0 * i / 360 * 2 * PI) + AI_x;
			AI_pointTmp2_y = (AI_y - 1.05 * AI_side - AI_y) * cos(1.0 * i / 360 * 2 * PI) + AI_y;
			ege_line(AI_pointTmp1_x, AI_pointTmp1_y, AI_pointTmp2_x, AI_pointTmp2_y);
		}
	}
	
	//+-30度稍长的线
	AI_pointTmp1_x = - (AI_y - 0.95 * AI_side - AI_y) * sin(1.0 * 30 / 360 * 2 * PI) + AI_x;
	AI_pointTmp1_y = (AI_y - 0.95 * AI_side - AI_y) * cos(1.0 * 30 / 360 * 2 * PI) + AI_y;
	AI_pointTmp2_x = - (AI_y - 1.09 * AI_side - AI_y) * sin(1.0 * 30 / 360 * 2 * PI) + AI_x;
	AI_pointTmp2_y = (AI_y - 1.09 * AI_side - AI_y) * cos(1.0 * 30 / 360 * 2 * PI) + AI_y;
	ege_line(AI_pointTmp1_x, AI_pointTmp1_y, AI_pointTmp2_x, AI_pointTmp2_y);
	AI_pointTmp1_x = - (AI_y - 0.95 * AI_side - AI_y) * sin(1.0 * -30 / 360 * 2 * PI) + AI_x;
	AI_pointTmp1_y = (AI_y - 0.95 * AI_side - AI_y) * cos(1.0 * -30 / 360 * 2 * PI) + AI_y;
	AI_pointTmp2_x = - (AI_y - 1.09 * AI_side - AI_y) * sin(1.0 * -30 / 360 * 2 * PI) + AI_x;
	AI_pointTmp2_y = (AI_y - 1.09 * AI_side - AI_y) * cos(1.0 * -30 / 360 * 2 * PI) + AI_y;
	ege_line(AI_pointTmp1_x, AI_pointTmp1_y, AI_pointTmp2_x, AI_pointTmp2_y);
	
	//正上方三角形
	setfillcolor(WHITE);
	setlinewidth(0.015 * AI_side);
	ege_point AI_point1[3]{
		{AI_x, AI_y - 0.93 * AI_side},
		{AI_x - 0.05 * AI_side, AI_y - AI_side},
		{AI_x + 0.05 * AI_side, AI_y - AI_side},
	};
	ege_fillpoly(3,AI_point1);
	
	
	
	//绘制横滚角指针
	//三角形每个点的原坐标
	double AI_pointTmp3_x = AI_x ;
	double AI_pointTmp3_y = AI_y - 0.95 * AI_side ;
	double AI_pointTmp4_x = AI_x - 0.08 * AI_side ;
	double AI_pointTmp4_y = AI_y - 0.85 * AI_side ;
	double AI_pointTmp5_x = AI_x + 0.08 * AI_side ;
	double AI_pointTmp5_y = AI_y - 0.85 * AI_side ;
	
	AI_pointTmp3_x = - (AI_y - 0.95 * AI_side - AI_y) * sin(rollAngle) + AI_x;
	AI_pointTmp3_y = (AI_y - 0.95 * AI_side - AI_y) * cos(rollAngle) + AI_y;
	AI_pointTmp4_x = (AI_x - 0.08 * AI_side - AI_x) * cos(rollAngle) - (AI_y - 0.85 * AI_side - AI_y) * sin(rollAngle) + AI_x;
	AI_pointTmp4_y = (AI_y - 0.85 * AI_side - AI_y) * cos(rollAngle) + (AI_x - 0.08 * AI_side - AI_x) * sin(rollAngle) + AI_y;
	AI_pointTmp5_x = (AI_x + 0.08 * AI_side - AI_x) * cos(rollAngle) - (AI_y - 0.85 * AI_side - AI_y) * sin(rollAngle) + AI_x;
	AI_pointTmp5_y = (AI_y - 0.85 * AI_side - AI_y) * cos(rollAngle) + (AI_x + 0.08 * AI_side - AI_x) * sin(rollAngle) + AI_y;
	
	
	setcolor(WHITE);
	setlinewidth(0.015 * AI_side);
	ege_line(AI_pointTmp3_x, AI_pointTmp3_y, AI_pointTmp4_x, AI_pointTmp4_y);
	ege_line(AI_pointTmp5_x, AI_pointTmp5_y, AI_pointTmp4_x, AI_pointTmp4_y);
	ege_line(AI_pointTmp3_x, AI_pointTmp3_y, AI_pointTmp5_x, AI_pointTmp5_y);
	
	//侧滑指示的矩形原坐标
	double AI_pointTmp6_x = AI_x - 0.088 * AI_side + (sideSlipAngle / PI * 360) / 45 * 2 * 0.088 * AI_side;
	double AI_pointTmp6_y = AI_y - 0.845 * AI_side;
	double AI_pointTmp7_x = AI_x + 0.088 * AI_side + (sideSlipAngle / PI * 360) / 45 * 2 * 0.088 * AI_side;
	double AI_pointTmp7_y = AI_y - 0.845 * AI_side;
	double AI_pointTmp8_x = AI_x + 0.088 * AI_side + (sideSlipAngle / PI * 360) / 45 * 2 * 0.088 * AI_side;
	double AI_pointTmp8_y = AI_y - 0.805 * AI_side;
	double AI_pointTmp9_x = AI_x - 0.088 * AI_side + (sideSlipAngle / PI * 360) / 45 * 2 * 0.088 * AI_side;
	double AI_pointTmp9_y = AI_y - 0.805 * AI_side;
	
//	double AI_pointTmp6_x = AI_x - 0.088 * AI_side;
//	double AI_pointTmp6_y = AI_y - 0.845 * AI_side;
//	double AI_pointTmp7_x = AI_x + 0.088 * AI_side;
//	double AI_pointTmp7_y = AI_y - 0.845 * AI_side;
//	double AI_pointTmp8_x = AI_x + 0.088 * AI_side;
//	double AI_pointTmp8_y = AI_y - 0.805 * AI_side;
//	double AI_pointTmp9_x = AI_x - 0.088 * AI_side;
//	double AI_pointTmp9_y = AI_y - 0.805 * AI_side;
	
	AI_pointTmp6_x = (AI_x - 0.088 * AI_side + (sideSlipAngle / PI * 360) / 45 * 2 * 0.088 * AI_side - AI_x) * cos(rollAngle) - (AI_y - 0.845 * AI_side - AI_y) * sin(rollAngle) + AI_x; 
	AI_pointTmp6_y = (AI_x - 0.088 * AI_side + (sideSlipAngle / PI * 360) / 45 * 2 * 0.088 * AI_side - AI_x) * sin(rollAngle) + (AI_y - 0.845 * AI_side - AI_y) * cos(rollAngle) + AI_y;
	AI_pointTmp7_x = (AI_x + 0.088 * AI_side + (sideSlipAngle / PI * 360) / 45 * 2 * 0.088 * AI_side - AI_x) * cos(rollAngle) - (AI_y - 0.845 * AI_side - AI_y) * sin(rollAngle) + AI_x; 
	AI_pointTmp7_y = (AI_x + 0.088 * AI_side + (sideSlipAngle / PI * 360) / 45 * 2 * 0.088 * AI_side - AI_x) * sin(rollAngle) + (AI_y - 0.845 * AI_side - AI_y) * cos(rollAngle) + AI_y;
	AI_pointTmp8_x = (AI_x + 0.088 * AI_side + (sideSlipAngle / PI * 360) / 45 * 2 * 0.088 * AI_side - AI_x) * cos(rollAngle) - (AI_y - 0.805 * AI_side - AI_y) * sin(rollAngle) + AI_x; 
	AI_pointTmp8_y = (AI_x + 0.088 * AI_side + (sideSlipAngle / PI * 360) / 45 * 2 * 0.088 * AI_side - AI_x) * sin(rollAngle) + (AI_y - 0.805 * AI_side - AI_y) * cos(rollAngle) + AI_y;
	AI_pointTmp9_x = (AI_x - 0.088 * AI_side + (sideSlipAngle / PI * 360) / 45 * 2 * 0.088 * AI_side - AI_x) * cos(rollAngle) - (AI_y - 0.805 * AI_side - AI_y) * sin(rollAngle) + AI_x; 
	AI_pointTmp9_y = (AI_x - 0.088 * AI_side + (sideSlipAngle / PI * 360) / 45 * 2 * 0.088 * AI_side - AI_x) * sin(rollAngle) + (AI_y - 0.805 * AI_side - AI_y) * cos(rollAngle) + AI_y;
	
	
	ege_line(AI_pointTmp6_x, AI_pointTmp6_y, AI_pointTmp7_x, AI_pointTmp7_y);
	ege_line(AI_pointTmp7_x, AI_pointTmp7_y, AI_pointTmp8_x, AI_pointTmp8_y);
	ege_line(AI_pointTmp8_x, AI_pointTmp8_y, AI_pointTmp9_x, AI_pointTmp9_y);
	ege_line(AI_pointTmp9_x, AI_pointTmp9_y, AI_pointTmp6_x, AI_pointTmp6_y);
	
}


void draw_PFD_AI_occlusion(){
	
	//需要被遮盖的背景圆的半径
	double AI_r = sqrt(2) * AI_side;
	
//	//遮盖为圆角矩形
//		//利用四个矩形遮盖为矩形(较小，但是有bug)
//	setfillcolor(BLACK);
//	ege_fillrect(AI_x - AI_r, AI_y - AI_r, 2 * AI_r, AI_r - AI_side);
//	ege_fillrect(AI_x - 1.01 * AI_r, AI_y - AI_r, AI_r - AI_side + 0.01 * AI_r, 2 * AI_r);//此处因为那个扇形边框是有一定宽度的，故x多减一点
//	ege_fillrect(AI_x + AI_side, AI_y - AI_r, AI_r - AI_side + 0.01 * AI_r, 2 * AI_r);
//	ege_fillrect(AI_x - 1.01 * AI_r, AI_y + AI_side, 2 * AI_r + 0.01 * AI_r, AI_r - AI_side + 0.01 * AI_r);
	
	//利用四个矩形遮盖为矩形(正常遮盖)
	setfillcolor(BLACK);
	ege_fillrect(AI_x - 1.2 * AI_r, AI_y - 1.2 * AI_r, 2.4 * AI_r, 1.2 * AI_r - AI_side);
	ege_fillrect(AI_x - 1.2 * AI_r, AI_y + 1 * AI_side, 2.4 * AI_r, 1.2 * AI_r - AI_side);
	ege_fillrect(AI_x - 1.2 * AI_r, AI_y - 1.2 * AI_r, 1.2 * AI_r - AI_side , 2.4 * AI_r);
	ege_fillrect(AI_x + 1 * AI_side, AI_y - 1.2 * AI_r, 1.2 * AI_r - AI_side , 2.4 * AI_r);
	
	//用多个圆弧遮盖绘制为圆角
	setcolor(BLACK);
	setlinewidth(0.015 * AI_r);
	//因为线是有宽度的，所以这里不是小于AI_x - 1 * AI_side
	for(double i = 1.05 * AI_side; i >= 1.01 * AI_side; i -= 0.005 * AI_side){
		//左上角
		ege_arc(AI_x - i , AI_y - i , 0.4 * AI_side, 0.4 * AI_side, -180, 90);
		//右上角
		//因为这个点是左上角坐标，所以减0.35*side，下同
		ege_arc(AI_x + i - 0.4 * AI_side, AI_y - i , 0.4 * AI_side, 0.4 * AI_side, -90, 90);
		//右下角
		ege_arc(AI_x + i - 0.4 * AI_side, AI_y + i - 0.4 * AI_side, 0.4 * AI_side, 0.4 * AI_side, 0, 90);
		//左下角
		ege_arc(AI_x - i, AI_y + i - 0.4 * AI_side, 0.4 * AI_side, 0.4 * AI_side, 90, 90);
	}
	
}



//=========================================================================================//





//==================================以下为空速表部分========================================//



extern double airSpeed; 
extern double airSpeed_acceleration;
extern double airSpeed_mach;
extern double airSpeed_instruction;

int num_scale1 = 0;
int num_scale2 = 0;


void draw_PFD_airspeed(double center_x, double center_y, double side)
{
	if (airSpeed <= 45) {
		airSpeed = 45;
	}
	side = side / 96 * 67;
	double length = side;
	double width = side / 67 * 11.5;
	
	// 最底层灰色
	setfillcolor(EGEARGB(0xff, 12, 14, 13));
	ege_fillrect(center_x - width / 2, center_y - length / 2, width, length);
	
	// 小刻度与数字显示
	setcolor(EGEARGB(150, 177, 177, 178));
	
	setbkmode(TRANSPARENT);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setfont(side / 17.1428, 0, "黑体");
	
	setlinewidth(side / 200);
	double distance = 0;
	if (airSpeed >= 40)
		distance = -(airSpeed - 30) / 10;
	if (airSpeed < 40)
		distance = -airSpeed / 40;
	if (airSpeed <= 40) num_scale2 = 7;
	else if (airSpeed <= 100) {
		num_scale2 = (int)(airSpeed - 40) / 10 % 10 + 1 + 7;
	}
	else {
		if (airSpeed <= 450) {
			num_scale1 = (int)(airSpeed - 100) / 10 % 10 + 1 + ((int)(airSpeed / 100) % 10 - 1) * 10;
			num_scale2 = num_scale1 + 13;
		}
		else
		{
			num_scale1 = (int)(450- 100) / 10 % 10 + 1 + ((int)(450 / 100) % 10 - 1) * 10;
			num_scale2 = num_scale1 + 13;
		}
	}
	if(airSpeed >=450)
		distance = -(450 - 30) / 10;
	for (int i = num_scale1; i < num_scale2; i++) {
		if (i<=42) {
			ege_line(center_x + width / 11.5 * 3.75,
				center_y - (i + distance) * length / 67 * 5.57,
				center_x + width / 2,
				center_y - (i + distance) * length / 67 * 5.57);
		}
		else {
			
		}
		
		
		// 绘制粉色指示速度标
		setcolor(EGEARGB(150, 255, 51, 255));
		setlinewidth(side / 250);
		int pointSpeed = (int)(airSpeed_instruction - 30);
		int one_digit, ten_digit, hundred_digit, new_number;
		one_digit = pointSpeed % 10;
		hundred_digit = (int)(pointSpeed / 100) % 10;
		ten_digit = (int)(pointSpeed / 10) % 10;
		new_number = hundred_digit * 10 + ten_digit;
		if (num_scale1 + 1 <= new_number && new_number <= num_scale2 - 1) {
			double point_distance = one_digit * 1.0 / 10 * length / 67 * 5.57;
			double yy = (new_number + distance) * length / 67 * 5.57;
			ege_point points6[6] = {
				center_x + width / 2.8,center_y - yy - point_distance,// 左中尖
				center_x + width / 2,center_y - yy - point_distance - length / 67 * 1,// 左上
				center_x + width / 1.4,center_y - yy - point_distance - length / 67 * 1,// 右上
				center_x + width / 1.4,center_y - yy - point_distance + length / 67 * 1,// 右下
				center_x + width / 2,center_y - yy - point_distance + length / 67 * 1,// 左下
				center_x + width / 2.8,center_y - yy - point_distance
			};
			ege_drawpoly(6, points6);
		}
		
		setcolor(EGEARGB(150, 177, 177, 178));
		setbkmode(TRANSPARENT);
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		setfont(side / 17.1428, 0, "黑体");
		double x_bit = center_x + width / 11.5 * 1.4,
		y_bit = center_y - (i + distance) * length / 67 * 5.57;
		double x_decade = center_x - width / 11.5 * 0.5,
		y_decade = center_y - (i + distance) * length / 67 * 5.57;
		double x_hundred = center_x - width / 11.5 * 2.4,
		y_hundred = center_y - (i + distance) * length / 67 * 5.57;
		
		if ((i + 1) % 2 == 0 && i<=42)
			outtextxy(x_bit, y_bit, '0');
		if (i == 1)
			outtextxy(x_decade, y_decade, '4');
		if (i == 3)
			outtextxy(x_decade, y_decade, '6');
		if (i == 5)
			outtextxy(x_decade, y_decade, '8');
		if (i == 7) {
			outtextxy(x_decade, y_decade, '0');
			outtextxy(x_hundred, y_hundred, '1');
		}
		if (i == 9) {
			outtextxy(x_decade, y_decade, '2');
			outtextxy(x_hundred, y_hundred, '1');
		}
		if (i == 11) {
			outtextxy(x_decade, y_decade, '4');
			outtextxy(x_hundred, y_hundred, '1');
		}
		if (i == 13) {
			outtextxy(x_decade, y_decade, '6');
			outtextxy(x_hundred, y_hundred, '1');
		}
		if (i == 15) {
			outtextxy(x_decade, y_decade, '8');
			outtextxy(x_hundred, y_hundred, '1');
		}
		if (i == 17) {
			outtextxy(x_decade, y_decade, '0');
			outtextxy(x_hundred, y_hundred, '2');
		}
		if (i == 19) {
			outtextxy(x_decade, y_decade, '2');
			outtextxy(x_hundred, y_hundred, '2');
		}
		if (i == 21) {
			outtextxy(x_decade, y_decade, '4');
			outtextxy(x_hundred, y_hundred, '2');
		}
		if (i == 23) {
			outtextxy(x_decade, y_decade, '6');
			outtextxy(x_hundred, y_hundred, '2');
		}
		if (i == 25) {
			outtextxy(x_decade, y_decade, '8');
			outtextxy(x_hundred, y_hundred, '2');
		}
		if (i == 27) {
			outtextxy(x_decade, y_decade, '0');
			outtextxy(x_hundred, y_hundred, '3');
		}
		if (i == 29) {
			outtextxy(x_decade, y_decade, '2');
			outtextxy(x_hundred, y_hundred, '3');
		}
		if (i == 31) {
			outtextxy(x_decade, y_decade, '4');
			outtextxy(x_hundred, y_hundred, '3');
		}
		if (i == 33) {
			outtextxy(x_decade, y_decade, '6');
			outtextxy(x_hundred, y_hundred, '3');
		}
		if (i == 35) {
			outtextxy(x_decade, y_decade, '8');
			outtextxy(x_hundred, y_hundred, '3');
		}
		if (i == 37) {
			outtextxy(x_decade, y_decade, '0');
			outtextxy(x_hundred, y_hundred, '4');
		}
		if (i == 39) {
			outtextxy(x_decade, y_decade, '2');
			outtextxy(x_hundred, y_hundred, '4');
		}
		if (i == 41) {
			outtextxy(x_decade, y_decade, '4');
			outtextxy(x_hundred, y_hundred, '4');
		}
		setlinewidth(side / 200);
	}
	
	// 放置空速显示上下进行遮盖
	setfillcolor(EGEARGB(0xff, 0, 0, 0));
	ege_point points0[4] = {
		center_x + width / 2 , center_y + length / 2,// 3
		center_x - width / 2, center_y + length / 2 ,// 4
		center_x - width / 2, center_y + length / 2 + length / 67 * 7,// 4下面的
		center_x + width / 2 , center_y + length / 2 + length / 67 * 7// 3下面的
	};
	ege_fillpoly(4, points0);
	
	
	// 黑色底板
	setfillcolor(EGEARGB(0xff, 0, 0, 0));
	ege_point points1[7] = {
		center_x - width / 2,center_y + length / 67 * 4,// 5
		center_x - width / 2 + width / 11.5 * 8, center_y + length / 67 * 4,// 6
		center_x - width / 2 + width / 11.5 * 8,center_y + length / 67 * 1,// 7
		center_x + width / 11.5 * (9.5 - 5.75),center_y,// 8
		center_x - width / 2 + width / 11.5 * 8,center_y - length / 67 * 1,// 9
		center_x - width / 2 + width / 11.5 * 8, center_y - length / 67 * 4,// 10
		center_x - width / 2,center_y - length / 67 * 4//11
	};
	ege_fillpoly(7, points1);
	
	int int_airSpeed = (int)airSpeed;
	double double_airSpeed = airSpeed - int_airSpeed;
	setcolor(EGEARGB(150, 177, 177, 178));
	setbkmode(TRANSPARENT);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setfont(side / 15, 0, "黑体");
	
	char num12[10] = { ' ','1','2','3','4','5','6','7','8','9' };// 十位
	if (int_airSpeed >= 90) {
		num12[0] = '0';
	}
	int tens_digit = (int_airSpeed / 10) % 10;
	char num_using2 = num12[tens_digit];
	outtextxy(center_x - width / 2 + width / 11.5 * 3.8, center_y - length / 67 * 8.4 + (2) * length / 67 * 4.2, num_using2);
	
	char num13[10] = { ' ','1','2','3','4','5','6','7','8','9' };// 百位
	int hundreds_digit = (int_airSpeed / 100) % 10;
	char num_using3 = num13[hundreds_digit];
	outtextxy(center_x - width / 2 + width / 11.5 * 1.5, center_y - length / 67 * 8.4 + (2) * length / 67 * 4.2, num_using3);
	
	char num11[12] = { '9','0','1','2','3','4','5','6','7','8','9','0' };// 个位
	int ones_digit1 = int_airSpeed % 10;
	int ones_digit2 = ones_digit1 + 1;
	int ones_digit3 = ones_digit1 - 1;
	char num_using1[3] = {};
	num_using1[0] = num11[ones_digit2 + 1];
	num_using1[1] = num11[ones_digit1 + 1];
	num_using1[2] = num11[ones_digit3 + 1];
	for (int i = 0; i < 3; i++) {
		if ((center_y - length / 67 * 8.2 + (i + 1 + double_airSpeed) * length / 67 * 3.8) <= center_y + length / 67 * 3.9)
			outtextxy(center_x - width / 2 + width / 11.5 * 6.5, center_y - length / 67 * 7.4 + (i + 1 + double_airSpeed) * length / 67 * 3.7, num_using1[i]);
	}
	
	// 上下两个遮盖的灰边
	setfillcolor(EGEARGB(0xff, 12, 14, 13));
	ege_point points2[4] = {
		center_x - width / 2 + width / 11.5 * 8, center_y - length / 67 * 4,// 10
		center_x - width / 2,center_y - length / 67 * 4,// 11
		center_x - width / 2,center_y - length / 67 * 5.6,// 11上面
		center_x - width / 2 + width / 11.5 * 8, center_y - length / 67 * 5.6// 10上面
	};
	ege_fillpoly(4, points2);
	ege_point points3[4] = {
		center_x - width / 2,center_y + length / 67 * 4,// 5
		center_x - width / 2 + width / 11.5 * 8, center_y + length / 67 * 4,// 6
		center_x - width / 2 + width / 11.5 * 8, center_y + length / 67 * 6.4,// 6下面
		center_x - width / 2,center_y + length / 67 * 6.4// 5下面
	};
	ege_fillpoly(4, points3);
	
	// 白色表框显示
	setcolor(EGEARGB(150, 177, 177, 178));
	setlinewidth(side / 200);
	ege_point points4[8] = {
		center_x - width / 1.9,center_y + length / 67 * 4,// 5
		center_x - width / 2 + width / 11.5 * 8, center_y + length / 67 * 4,// 6
		center_x - width / 2 + width / 11.5 * 8,center_y + length / 67 * 1,// 7
		center_x + width / 11.5 * (9.5 - 5.75),center_y,// 8
		center_x - width / 2 + width / 11.5 * 8,center_y - length / 67 * 1,// 9
		center_x - width / 2 + width / 11.5 * 8, center_y - length / 67 * 4,// 10
		center_x - width / 1.9,center_y - length / 67 * 4,//11
		center_x - width / 1.9,center_y + length / 67 * 4// 5
	};
	ege_drawpoly(8, points4);
	
	// 绿色指针显示
	setcolor(EGEARGB(150, 76, 153, 0));
	setlinewidth(side / 200);
	if (airSpeed_acceleration > 0) {// 绿色指针向上
		if (airSpeed_acceleration <= (length / 2 - side / 60)) {
			ege_line(center_x + width / 11.5 * (9.5 - 5.75),
				center_y,
				center_x + width / 11.5 * (9.5 - 5.75),
				center_y - airSpeed_acceleration);
			if (airSpeed_acceleration >= side / 60) {
				ege_point points5[4] = {
					center_x + width / 11.5 * 2.7,// 左下
					center_y - airSpeed_acceleration,
					center_x + width / 11.5 * 4.5,// 右下
					center_y - airSpeed_acceleration,
					center_x + width / 11.5 * 3.75,// 上部定位点
					center_y - airSpeed_acceleration - side / 60,
					center_x + width / 11.5 * 2.7,
					center_y - airSpeed_acceleration
				};
				ege_drawpoly(4, points5);
			}
			
		}
		else
		{
			ege_line(center_x + width / 11.5 * (9.5 - 5.75),
				center_y,
				center_x + width / 11.5 * (9.5 - 5.75),
				center_y - length / 2 + side / 60);
			ege_point points5[4] = {
				center_x + width / 11.5 * 2.7,// 左下
				center_y - length / 2 + side / 60,
				center_x + width / 11.5 * 4.5,// 右下
				center_y - length / 2 + side / 60 ,
				center_x + width / 11.5 * 3.75,// 上部定位点
				center_y - length / 2 ,
				center_x + width / 11.5 * 2.7,
				center_y - length / 2 + side / 60
			};
			ege_drawpoly(4, points5);
		}
	}
	if (airSpeed_acceleration < 0) {// 绿色指针向下
		if (airSpeed_acceleration >= -(length / 2 - side / 60)) {
			ege_line(center_x + width / 11.5 * (9.5 - 5.75),
				center_y,
				center_x + width / 11.5 * (9.5 - 5.75),
				center_y - airSpeed_acceleration);
			if (airSpeed_acceleration <= -side / 60) {
				ege_point points5[4] = {
					center_x + width / 11.5 * 2.7,// 左上
					center_y - airSpeed_acceleration ,
					center_x + width / 11.5 * 4.5,// 右上
					center_y - airSpeed_acceleration ,
					center_x + width / 11.5 * 3.75,// 下部定位点
					center_y - airSpeed_acceleration + side / 60 ,
					center_x + width / 11.5 * 2.7,
					center_y - airSpeed_acceleration
				};
				ege_drawpoly(4, points5);
			}
			
		}
		else
		{
			ege_line(center_x + width / 11.5 * (9.5 - 5.75),
				center_y,
				center_x + width / 11.5 * (9.5 - 5.75),
				center_y + length / 2 - side / 60);
			ege_point points5[4] = {
				center_x + width / 11.5 * 2.7,// 左上
				center_y + length / 2 - side / 60,
				center_x + width / 11.5 * 4.5,// 右上
				center_y + length / 2 - side / 60,
				center_x + width / 11.5 * 3.75,// 下部定位点
				center_y + length / 2 ,
				center_x + width / 11.5 * 2.7,
				center_y + length / 2 - side / 60
			};
			ege_drawpoly(4, points5);
		}
	}
	
	// 马赫显示
	if (airSpeed_mach >= 0.4) {
		setcolor(EGEARGB(150, 177, 177, 178));
		setbkmode(TRANSPARENT);
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		setfont(side / 12, 0, "黑体");
		char str[100];
		sprintf(str, "%.3f", airSpeed_mach);
		char str0[99];
		int i;
		for (i = 1; str[i] != '\0'; i++) {
			str0[i - 1] = str[i];
		}
		str0[i - 1] = '\0';
		outtextxy(center_x - width / 18, center_y + length / 2 * 1.11, str0);
	}
	
	// 速度指示绘制
	setcolor(EGEARGB(150, 255, 51, 255));
	setbkmode(TRANSPARENT);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setfont(side / 12, 0, "黑体");
	char str[100];
	sprintf(str, "%.0f", airSpeed_instruction);
	outtextxy(center_x + width / 10, center_y - length / 2 * 1.11, str);
}



//=========================================================================================//





//==================================以下为高度表表部分========================================//



extern double altitude;
extern double indicated_number;
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
	
	setcolor(EGEARGB(200, 177, 177, 178));
	//定出粗线的x坐标
	double x1 = center_x - 6.0 / 96.0 * side;
	double x2 = center_x - 3.0 / 96.0 * side;
	
	//定出细线的x坐标
	double x3 = center_x - 5.5 / 96.0 * side;
	double x4 = center_x - 3.5 / 96.0 * side;
	
	double ten = fmod(altitude, 100);
	
	double data4 = altitude - ten;
	int datas[9] = {};
	setlinewidth(side * 0.005);
	
	//计算出来了每条线的数据
	for (int i = 0;i < 9;i++) {
		datas[i] = (int)data4 + 100 * (i - 4);
	}
	
	int hun[9] = {};
	for (int i = 0;i < 9;i++) {
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
	
	for (int i = 0;i < 9;i++) {
		
		double y = center_y - 33.5 / 96 * side + ten / 100 * gap + i * gap;//底部坐标 + 偏移坐标 + 循环坐标
		
		//绘制每个刻度左侧的横线
		
		if (fmod(datas[8 - i], 500) == 0) {
			setlinewidth(side * 0.005);
			ege_line(x1, y, x2, y);
		}
		else
		{
			setlinewidth(side * 0.003);
			ege_line(x3, y, x4, y);
		}
		
		//绘制千上下两条横线
		
		if (fmod(datas[8 - i], 1000) == 0) {
			setlinewidth(side * 0.002);
			ege_line(x2, y + num_height / 1.8, center_x + 6.0 / 96.0 * side, y + num_height / 1.8);
			ege_line(x2, y - num_height / 1.8, center_x + 6.0 / 96.0 * side, y - num_height / 1.8);
		}
	}
	
	
	//画00
	
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setfont(num_height, num_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	for (int i = 0;i < 9;i++) {
		double y = center_y - 33.5 / 96 * side + ten / 100 * gap + i * gap;//底部坐标 + 偏移坐标 + 循环坐标
		double x = center_x + 4.5 / 96 * side;
		int h = datas[i] / 100;
		if (fmod(datas[8 - i], 200) == 0) {
			ege_drawtext("0", x, y);
			x = x - num_width;
			ege_drawtext("0", x, y);
		}
	}
	
	
	//画百位
	for (int i = 0;i < 9;i++) {
		double y = center_y - 33.5 / 96 * side + ten / 100 * gap + i * gap;//底部坐标 + 偏移坐标 + 循环坐标
		double x = center_x + 4.5 / 96 * side;
		x = x - 2 * num_width;
		
		char nums[64] = {};
		
		
		if (hun[8 - i] >= 0) {
			sprintf_s(nums, "%d", hun[8 - i]);
			if (fmod(datas[8 - i], 200) == 0) {
				ege_drawtext(nums, x, y);
			}
		}
		else {
			sprintf_s(nums, "%d", -hun[8 - i]);
			if (fmod(datas[8 - i], 200) == 0) {
				ege_drawtext(nums, x, y);
			}
			x = x - num_width;
			if (datas[8 - i] > -1000) {
				if (fmod(datas[8 - i], 200) == 0) {
					ege_drawtext("-", x, y);
				}
			}
		}
		
	}
	//计算千位数字
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setfont(num_height * 1.2, num_width * 1.2, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	
	int thousand[9] = {};
	for (int i = 0;i < 9;i++) {
		thousand[i] = datas[i] % 10000;
		thousand[i] = thousand[i] / 1000;
	}
	
	for (int i = 0;i < 9;i++) {
		double y = center_y - 33.5 / 96 * side + ten / 100 * gap + i * gap;//底部坐标 + 偏移坐标 + 循环坐标
		double x = center_x + 4.5 / 96 * side;
		x = x - 3 * num_width * 1.05;
		
		char nums[64] = {};
		sprintf_s(nums, "%d", thousand[8 - i]);
		
		if (datas[8 - i] <= -1000 || datas[8 - i] >= 1000) {
			if (thousand[8 - i] >= 0) {
				if (fmod(datas[8 - i], 200) == 0) {
					ege_drawtext(nums, x, y);
				}
			}
			else {
				sprintf_s(nums, "%d", -thousand[8 - i]);
				if (fmod(datas[8 - i], 200) == 0) {
					ege_drawtext(nums, x, y);
				}
				x = x - num_width;
				if (datas[8 - i] <= -1000 && datas[8 - i] > -10000) {
					if (fmod(datas[8 - i], 200) == 0) {
						ege_drawtext("-", x, y);
					}
				}
			}
		}
	}
	
	//计算万位
	int tenthousand[9] = {};
	for (int i = 0;i < 9;i++) {
		tenthousand[i] = datas[i] % 100000;
		tenthousand[i] = tenthousand[i] / 10000;
	}
	
	for (int i = 0;i < 8;i++) {
		double y = center_y - 33.5 / 96 * side + ten / 100 * gap + i * gap;//底部坐标 + 偏移坐标 + 循环坐标
		double x = center_x + 4.5 / 96 * side;
		x = x - 4 * num_width * 1.05;
		
		char nums[64] = {};
		sprintf_s(nums, "%d", tenthousand[8 - i]);
		
		if (datas[8 - i] <= -10000 || datas[8 - i] >= 10000) {
			if (thousand[8 - i] >= 0) {
				if (fmod(datas[8 - i], 200) == 0) {
					ege_drawtext(nums, x, y);
				}
			}
			else {
				sprintf_s(nums, "%d", -tenthousand[7 - i]);
				if (fmod(datas[8 - i], 200) == 0) {
					ege_drawtext(nums, x, y);
				}
				x = x - num_width;
				if (datas[8 - i] <= -1000 && datas[8 - i] > -10000) {
					if (fmod(datas[8 - i], 200) == 0) {
						ege_drawtext("-", x, y);
					}
				}
			}
		}
	}
	
}

//绘制主显示的遮挡

void draw_PFD_alt_mainShadow(double side, double center_x, double center_y) {
	
	double num_height = side * 0.055 * 1.15 * 0.8;
	double frame_wide = side * 13.5 / 96;//底框的宽度
	double frame_height = side * 67.0 / 96;//底框的长度
	
	//左上角的坐标
	double frame_x = center_x + 29.0 / 96.0 * side - 29.0 / 96.0 * side - 6.5 / 96.0 * side;
	double frame_y = center_y - 33.5 / 96.0 * side;
	setfillcolor(BLACK);
	ege_fillrect(frame_x, frame_y + frame_height, frame_wide, num_height * 2.7);
	ege_fillrect(frame_x, frame_y - num_height * 2.7, frame_wide, num_height * 2.71);
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

void draw_PFD_alt10(double height, double side, double center_x, double center_y) {
	setcolor(EGEARGB(200, 177, 177, 178));
	double y = center_y - side * 0.0305;
	double x = center_x;
	
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

void draw_PFD_alt100(double height, double side, double center_x, double center_y) {
	setcolor(EGEARGB(200, 177, 177, 178));
	double y = center_y - side * 0.0305;
	double number_height = side * 0.055 * 1.15;
	double number_width = side * 2.5 / 96.0 * 0.85;
	double hun = fmod(height, 1000);
	
	hun = hun / 100;
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setfont(number_height, number_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	char num[12] = { '9','0','1','2','3','4','5','6','7','8','9','0' };
	
	outtextxy(center_x + number_width * 2.3, y, num[(int)hun + 1]);
}

//千位

void draw_PFD_alt1000(double height, double side, double center_x, double center_y) {
	setcolor(EGEARGB(200, 177, 177, 178));
	double y = center_y - side * 0.0345;
	double number_height = side * 0.055 * 1.3;
	double number_width = side * 2.5 / 96.0 * 0.85 * 1.3;
	double thousand = fmod(height, 10000);
	
	thousand = thousand / 1000;
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setfont(number_height, number_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	
	char num[12] = { '9','0','1','2','3','4','5','6','7','8','9','0' };
	
	outtextxy(center_x + number_width * 0.8, y, num[(int)thousand + 1]);
}

//绘制线框
//通过观察发现，上下两侧有阴影，后期考虑加入；

void draw_PFD_alt_wireframe(double side, double center_x, double center_y) {
	setcolor(EGEARGB(200, 177, 177, 178));
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


//主显示指定的高度

void draw_PFD_alt_indicatedNum(double side, double center_x, double center_y) {
	setcolor(EGEARGB(150, 255, 51, 255));
	char num[12] = { '9','0','1','2','3','4','5','6','7','8','9','0' };
	double number_height = side * 0.055 * 1.1;
	double number_width = side * 2.5 / 96.0 * 0.85;
	
	double x = center_x + 3.0 / 96.0 * side;
	double y = center_y - 33.5 / 96 * side - number_height * 0.3;
	
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setfont(number_height, number_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	double lessThan1000 = fmod(indicated_number, 1000);
	
	int LessThan1000[3] = {};
	LessThan1000[0] = lessThan1000 / 100;
	lessThan1000 -= 100 * LessThan1000[0];
	LessThan1000[1] = lessThan1000 / 10;
	lessThan1000 -= 10 * LessThan1000[1];
	LessThan1000[2] = lessThan1000 / 1;
	
	char last[4] = {};
	for (int i = 0;i < 3;i++) {
		last[i] = num[LessThan1000[i] + 1];
	}
	
	if (indicated_number < 10000) {
		//当在10000以下的时候，只显示到千
		double thousand = indicated_number / 1000;
		number_height = side * 0.055 * 1.3;
		number_width = side * 2.5 / 96.0 * 0.85 * 1.3;
		ege_drawtext(last, x, y);
		
		setfont(number_height, number_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
		char thou = num[(int)thousand + 1];
		
		char nums[64] = {};
		sprintf_s(nums, "%d", thou);
		x = center_x - 2.1 / 96.0 * side;
		y = center_y - 33.5 / 96 * side - number_height * 0.32;
		ege_drawtext("0", x, y);
	}
	else {
		//当在10000以上的时候，再向上显示
		double thousand = indicated_number / 1000;
		number_height = side * 0.055 * 1.3;
		number_width = side * 2.5 / 96.0 * 0.85 * 1.3;
		ege_drawtext(last, x, y);
		
		setfont(number_height, number_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
		char thou = num[(int)thousand + 1];
		
		char nums[64] = {};
		sprintf_s(nums, "%d", thou);
		x = center_x - 2.1 / 96.0 * side;
		y = center_y - 33.5 / 96 * side - number_height * 0.32;
		ege_drawtext("0", x, y);
		
		int tenTHOU = indicated_number / 10000;
		char TenTHOU = num[(int)tenTHOU + 1];
		setcolor(EGEARGB(150, 255, 51, 255));
		outtextxy(x - side * 4.0 / 96.0, y - side * 3.7 / 96.0, TenTHOU);
	}
}

//绘制指定的高度的线框

void draw_PFD_alt_indicatedFrame(double side, double center_x, double center_y) {
	//计算出每条线之间的间隔
	double gap = 67.0 / 96.0 * side / 8.0;
	
	double ten = fmod(altitude, 100);
	
	double data4 = altitude - ten;
	int datas[9] = {};
	setlinewidth(side * 0.005);
	
	//计算出来了每条线的数据
	for (int i = 0;i < 9;i++) {
		datas[i] = (int)data4 + 100 * (i - 4);
	}
	//依据data找到在当前界面中是否需要绘制这个紫色线框
	bool existence = false;
	int No = 0;
	for (int i = 0;i < 9;i++) {
		if (indicated_number == datas[i]) {
			existence = true;
			No = 8 - i;
		}
	}
	
	//当在当前界面存在
	if (existence) {
		//找到目标位置；
		double y = center_y - 33.5 / 96 * side + ten / 100 * gap + No * gap;//底部坐标 + 偏移坐标 + 循环坐标
		
		//设置颜色
		setcolor(EGEARGB(150, 255, 51, 255));
		
		double x = center_x - 6.3 / 96 * side;
		double y1 = y - 4.5 / 96.0 * side;
		
		double wide = 5.5 / 96.0 * side;
		double height = 9.0 / 96.0 * side;
		setlinewidth(0.004 * side);
		
		ege_line(x, y1, x + wide, y1);
		ege_line(x, y1 + height, x + wide, y1 + height);
		ege_line(x + wide, y1 - side * 0.001, x + wide, y1 + height + side * 0.001);
		ege_line(x, y1 - side * 0.001, x, y1 + height * 0.4);
		ege_line(x, y1 + height * 0.6, x, y1 + height + side * 0.001);
		ege_line(x, y1 + height * 0.4, x + side * 0.01, y + side * 0.001);
		ege_line(x, y1 + height * 0.6, x + side * 0.01, y - side * 0.001);
		//ege_rectangle(x, y1, wide, height);
	}
}

//绘制主函数

void draw_PFD_alt(double center_x, double center_y, double side) {
	double height;
	
	if (altitude < 0) {
		height = -altitude;
	}
	else
	{
		height = altitude;
	}
	
	draw_PFD_alt_frame(side, center_x, center_y);//画底盘
	
	draw_PFD_alt_linesAndNum(side, center_x, center_y);//画线和数字
	
	draw_PFD_alt_indicatedFrame(side, center_x, center_y);
	
	draw_PFD_alt_mainShadow(side, center_x, center_y);//主显示上部和下部矩形遮挡
	
	draw_PFD_alt_wireframe(side, center_x, center_y);//画固定的白色线框
	
	draw_PFD_alt10(height, side, center_x, center_y);
	
	draw_PFD_alt10_shadow(side, center_x, center_y);
	
	
	
	draw_PFD_alt_STD(side, center_x, center_y);//绘制STD
	
	draw_PFD_alt_indicatedNum(side, center_x, center_y);//绘制主显示上指定的数值
	
	draw_PFD_alt100(height, side, center_x, center_y);
	
	draw_PFD_alt1000(height, side, center_x, center_y);
	
	//主显示上的线
	
	if (altitude < 10000) {
		draw_PFD_alt_greenLines(side, center_x, center_y);
	}
	else {
		draw_PFD_alt10000(side, center_x, center_y);
	}
}



//=========================================================================================//





//==================================以下为垂直速率表部分========================================//



double calPointery(double verticalRate, double Ulength);
extern double verticalRate;
void draw_PFD_RCDI(double RCDI_x,double RCDI_y,double RCDI_side) {
	
	double Ulength = RCDI_side / 96;
	double big_width = Ulength / 3;
	double small_width = Ulength / 5;
	double Pointer_y;
	
	setfont(0,0,"Calibri");
	
	//表盘
	int RCDI_frame_pointsNum = 10;
	ege_point RCDI_frame_ployPoint[10]{
		{RCDI_x - Ulength * 4 , RCDI_y - Ulength * 23 },
		{RCDI_x  , RCDI_y - Ulength * 23},
		{RCDI_x + Ulength * 4 , RCDI_y - Ulength * 12.5},
		{RCDI_x + Ulength * 4 , RCDI_y + Ulength * 12.5},
		{RCDI_x  , RCDI_y + Ulength * 23},
		{RCDI_x - Ulength * 4 , RCDI_y + Ulength * 23},
		{RCDI_x - Ulength * 4 , RCDI_y + Ulength * 7.5},
		{RCDI_x - Ulength * 2 , RCDI_y + Ulength * 6},
		{RCDI_x - Ulength * 2 , RCDI_y - Ulength * 6},
		{RCDI_x - Ulength * 4 , RCDI_y - Ulength * 7.5},
	};
	setfillcolor(EGEARGB(0XFF,0X11,0X12,0X11));
	ege_fillpoly(RCDI_frame_pointsNum, RCDI_frame_ployPoint);
	
	//刻度
	setcolor(EGEARGB(0XFF, 0X75, 0X75, 0X75));
	
	setlinewidth(big_width);
	ege_line(RCDI_x - 2 * Ulength, RCDI_y, RCDI_x - 1 * Ulength, RCDI_y);
	
	ege_line(RCDI_x - 2 * Ulength, RCDI_y - 9 * Ulength, RCDI_x - 1 * Ulength, RCDI_y - 9 * Ulength);
	ege_line(RCDI_x - 2 * Ulength, RCDI_y + 9 * Ulength, RCDI_x - 1 * Ulength, RCDI_y + 9 * Ulength);
	ege_line(RCDI_x - 2 * Ulength, RCDI_y - 17 * Ulength, RCDI_x - 1 * Ulength, RCDI_y - 17 * Ulength);
	ege_line(RCDI_x - 2 * Ulength, RCDI_y + 17 * Ulength, RCDI_x - 1 * Ulength, RCDI_y + 17 * Ulength);
	ege_line(RCDI_x - 2 * Ulength, RCDI_y - 21 * Ulength, RCDI_x - 1 * Ulength, RCDI_y - 21 * Ulength);
	ege_line(RCDI_x - 2 * Ulength, RCDI_y + 21 * Ulength, RCDI_x - 1 * Ulength, RCDI_y + 21 * Ulength);
	
	setlinewidth(small_width);
	ege_line(RCDI_x - 2 * Ulength, RCDI_y - 4.5 * Ulength, RCDI_x - 1 * Ulength, RCDI_y - 4.5 * Ulength);
	ege_line(RCDI_x - 2 * Ulength, RCDI_y + 4.5 * Ulength, RCDI_x - 1 * Ulength, RCDI_y + 4.5 * Ulength);
	ege_line(RCDI_x - 2 * Ulength, RCDI_y - 19 * Ulength, RCDI_x - 1 * Ulength, RCDI_y - 19 * Ulength);
	ege_line(RCDI_x - 2 * Ulength, RCDI_y + 19 * Ulength, RCDI_x - 1 * Ulength, RCDI_y + 19 * Ulength);
	
	
	
	//绘制数字
	setbkmode(TRANSPARENT);
	setcolor(EGEARGB(0XFF, 0XAD,0XAE,0XAD));
	setfont(Ulength / 9 * 25,Ulength / 9 * 3, "Calibri");
	
	ege_drawtext("6", RCDI_x - 2.8 * Ulength, RCDI_y - 20.9 * Ulength);
	ege_drawtext("6", RCDI_x - 2.8 * Ulength, RCDI_y + 21 * Ulength);
	ege_drawtext("2", RCDI_x - 2.8 * Ulength, RCDI_y - 17.2 * Ulength);
	ege_drawtext("2", RCDI_x - 2.8 * Ulength, RCDI_y + 17 * Ulength);
	ege_drawtext("1", RCDI_x - 2.8 * Ulength, RCDI_y - 9 * Ulength);
	ege_drawtext("1", RCDI_x - 2.8 * Ulength, RCDI_y + 9 * Ulength);
	
	
	setfont(Ulength / 9 * 35, Ulength / 9 * 3, "Calibri");
	if (verticalRate >= 400 && verticalRate <= 9999) 
	{
		char num[64];
		sprintf_s(num, "%d", (int)verticalRate / 50 * 50);
		ege_drawtext(num, RCDI_x - 1 * Ulength, RCDI_y - 25 * Ulength);
		
	}
	else if (verticalRate > 9999)
	{
		ege_drawtext("9999", RCDI_x - 1 * Ulength, RCDI_y - 25 * Ulength);
	}
	else if (verticalRate <= -400 && verticalRate >= -9999)
	{
		char num[64];
		sprintf_s(num, "%d", (int)-verticalRate / 50 * 50);
		ege_drawtext(num, RCDI_x - 1 * Ulength, RCDI_y + 25.5 * Ulength);
	}
	else if (verticalRate < -9999) 
	{
		ege_drawtext("9999", RCDI_x - 1 * Ulength, RCDI_y + 25.5 * Ulength);
	}
	
	
	
	//绘制指针
	Pointer_y = calPointery(verticalRate/1000,Ulength);
	setcolor(EGEARGB(0XFF, 0X75, 0X75, 0X75));
	setlinewidth(big_width);
	ege_line(RCDI_x + Ulength * 4, RCDI_y, RCDI_x - Ulength * 2, RCDI_y - Pointer_y);
	
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




//=========================================================================================//





//==================================以下为航向罗盘部分========================================//



extern double rotationangle;//罗盘上数字和刻度线旋转的角度
extern double pointrotationangle;//罗盘指针旋转的角度
extern int course;//罗盘指定的航向
double realrotationangle1 = 0;//真实的旋转角度

//画罗盘的框架
void draw_compass_frame(double compass_x, double compass_y, double side)
{
	double compass_r = side * 30.5 / 96;//罗盘的半径
	
	setfillcolor(EGEARGB(0Xff, 0X12, 0X14, 0X13));//罗盘内部填充颜色
	
	//画一个置于底层的带底色的多边形来避免使用底色填充
	ege_point coverpoly[5];
	
	coverpoly[0].x = compass_x - compass_r * sin(55 * PI / 180);
	coverpoly[0].y = compass_y - compass_r * cos(55 * PI / 180);
	
	coverpoly[1].x = compass_x - compass_r * 0.5;
	coverpoly[1].y = compass_y - compass_r;
	
	coverpoly[2].x = compass_x + compass_r * 0.5;
	coverpoly[2].y = compass_y - compass_r;
	
	coverpoly[3].x = compass_x + compass_r * sin(55 * PI / 180);
	coverpoly[3].y = compass_y - compass_r * cos(55 * PI / 180);
	
	coverpoly[4].x = compass_x - compass_r * sin(55 * PI / 180);
	coverpoly[4].y = compass_y - compass_r * cos(55 * PI / 180);
	
	ege_fillpoly(5, coverpoly);
	
	//使用圆弧遮盖多余的填充部分
	for (int i = 0; i < 150; i++)
	{
		setcolor(BLACK);
		ege_arc(compass_x - compass_r, compass_y - compass_r * (1.15 - 0.001 * i), compass_r * 2, compass_r * 2, -35.0, -110.0);
	}
	
	setcolor(EGEARGB(0Xff, 0X12, 0X14, 0X13));//罗盘外框线的颜色
	setlinewidth(2);//罗盘外框线的宽度
	ege_arc(compass_x - compass_r, compass_y - compass_r, 2 * compass_r, 2 * compass_r, -35.0, -110.0);//罗盘的弧线部分
	ege_line(compass_x - compass_r * sin(55 * PI / 180), compass_y - compass_r * cos(55 * PI / 180), compass_x + compass_r * sin(55 * PI / 180), compass_y - compass_r * cos(55 * PI / 180));//罗盘的直线部分
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
		double scaleAngle = realrotationangle1 + i;
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
		double scaleAngle = realrotationangle1 + i;
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
		double textAngle = realrotationangle1 + i;
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
	realrotationangle1 = 360 - rotationangle;
	
	draw_compass_frame(compass_x, compass_y, side);
	
	draw_course_indication(compass_x, compass_y, side);
	
	draw_scale(compass_x, compass_y, side);
	
	draw_compass_point(compass_x, compass_y, side);
	
	draw_course(compass_x, compass_y, side);
	
	draw_MAG(compass_x, compass_y, side);
	
	draw_compass_text(compass_x, compass_y, side);
}



//=========================================================================================//




//===================================以下负责绘制PFD其他部件====================================//



void draw_PFD_top(double top_x, double top_y, double side) {
	double Ulength = side / 96;
	double linewidth = Ulength / 3;
	
	setfillcolor(EGEARGB(0XFF, 0X11, 0X11, 0X11));
	ege_fillrect(top_x - Ulength * 27, top_y - Ulength * 3, Ulength * 54, Ulength * 6);
	setcolor(EGEARGB(0XFF, 0X75, 0X75, 0X75));
	setlinewidth(linewidth);
	ege_line(top_x - Ulength * 8.5, top_y - Ulength * 3, top_x - Ulength * 8.5, top_y + Ulength * 3);
	ege_line(top_x + Ulength * 8.5, top_y - Ulength * 3, top_x + Ulength * 8.5, top_y + Ulength * 3);
}
void draw_1(double x, double y, double side) {
	
	extern double Anum;
	
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
	
	double angle;
	
	if (Anum == 0) {
		angle = 225;
	}
	else if (Anum > 0 && Anum <= 20) {
		angle = 225 - Anum * 9;
	}
	else if (Anum > 20) {
		angle = 45;
	}
	else if (Anum < 0 && Anum >= -5) {
		angle = 225 - Anum * 9;
	}
	else if (Anum < -5) {
		angle = 270;
	}
	
	ege_line(x, y, x - 6 * Ulength * cos(angle * PI / 180), y - 6 * Ulength * sin(angle * PI / 180));
	setfont(Ulength / 7 * 30, Ulength / 7 * 3, "Calibri");
	if (Anum >= -6 && Anum <= 22) {
		char num[64];
		sprintf_s(num, "%.1f", Anum);
		ege_drawtext(num, x - 6 * Ulength, y );
	}
	else if (Anum > 22) {
		ege_drawtext("22.0", x - 6 * Ulength, y );
	}
	else if (Anum < -6) {
		ege_drawtext("-6.0", x - 6 * Ulength, y );
	}
}



//=========================================================================================//
