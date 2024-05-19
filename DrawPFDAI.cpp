#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>

#define Background_color EGEARGB(0xff,0x1b,0x20,0x25)
#define Frame_color1 EGEARGB(0xff,0x24,0x28,0x33)	//EGEARGB(0xff,0x53,0x52,0x56)   // 0xff,0x39,0x39,0x40
#define Frame_color2 EGEARGB(0xff,0x1f,0x23,0x2e)	//24，28，33	//0xff,0x2f,0x2f,0x32

//函数声明

void draw_PFD_AI_background();
void draw_PFD_AI_gear();

//引用全局变量
double pitchAngle = 0;
double rollAngle = 0;
double sideSlipAngle = 0;
double headingIndication = 0;
double glideIndication = 0;

int G_light = 0;

double AI_x = 0;
double AI_y = 0;
double AI_side = 0;

//注意，这里的side并不是真正的边长，而只是PFD的高，PFD并非严格正方形
void draw_PFD_AI(double x, double y, double side){
	
	AI_x = x;
	AI_y = y;
	AI_side = side / 4;//即一半的边长
	
	draw_PFD_AI_background();
	
	draw_PFD_AI_gear();
	
	if (GetAsyncKeyState(0x41) & 0x8000)
		rollAngle -= 0.002;
	if (GetAsyncKeyState(0x44) & 0x8000)
		rollAngle += 0.002;
	if (GetAsyncKeyState(0x57) & 0x8000)
		pitchAngle += 0.002;
	if (GetAsyncKeyState(0x53) & 0x8000)
		pitchAngle -= 0.002;
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
	
	
}


void draw_PFD_AI_gear(){
	
	//需要被遮盖的背景圆的半径
	double AI_r = sqrt(2) * AI_side;
	
	//俯仰角刻度
	
	setcolor(WHITE);
	setlinewidth(0.012 * AI_side);
	double AI_line_lx;
	double AI_line_ly;
	double AI_line_rx;
	double AI_line_ry;
	double AI_circle_x;
	double AI_circle_y;
	
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
	
	
	
	//绘制上方固定的蓝色遮挡
	setcolor(EGEARGB(0xff,0x10,0x86,0xcf));
	setlinewidth(0.4 * AI_side);
	ege_arc(AI_x - 1.23 * AI_side, AI_y - 1 * AI_side, 2.46 * AI_side, 2.3 * AI_side, -150, 120);
	ege_arc(AI_x - 1.23 * AI_side, AI_y - 1.2 * AI_side, 2.46 * AI_side, 2.3 * AI_side, -150, 120);
	
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
