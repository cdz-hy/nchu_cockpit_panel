#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>

#define AI_x 400
#define AI_y 400
#define AI_r 200
#define Background_color EGEARGB(0xff,0x1b,0x20,0x25)
#define Frame_color EGEARGB(0xff,0x53,0x52,0x56)    

//定义横滚角 (弧度制)
double rollAngle = 0;

//定义俯仰角 (弧度制)
double pitchAngle = 0;

void draw_attitude_indicator_frame(){
	
	//绘制边框阴影 
	
	setfillcolor(EGEARGB(0xff,0x1e,0x1f,0x10));
	ege_fillrect(AI_x-1.3*AI_r,AI_y-1.54*AI_r,2.7*AI_r,0.04*AI_r);
	ege_fillrect(AI_x+1.5*AI_r,AI_y-1.4*AI_r,0.04*AI_r,2.7*AI_r);
	ege_fillellipse(AI_x-1.42*AI_r,AI_y-1.54*AI_r,0.2*AI_r,0.2*AI_r);
	ege_fillellipse(AI_x+1.34*AI_r,AI_y+1.2*AI_r,0.2*AI_r,0.2*AI_r);
	
	//绘制边框（底座）
	
	setfillcolor(Frame_color);
	ege_fillrect(AI_x-1.5*AI_r,AI_y-1.5*AI_r,3*AI_r,3*AI_r);
	
	setfillcolor(Background_color);
	ege_fillrect(AI_x-1.5*AI_r,AI_y-1.5*AI_r,0.1*AI_r,0.1*AI_r);
	ege_fillrect(AI_x-1.5*AI_r,AI_y+1.4*AI_r,0.1*AI_r,0.1*AI_r);
	ege_fillrect(AI_x+1.4*AI_r,AI_y-1.5*AI_r,0.1*AI_r,0.1*AI_r);
	ege_fillrect(AI_x+1.4*AI_r,AI_y+1.4*AI_r,0.1*AI_r,0.1*AI_r);
	
	
	setfillcolor(Frame_color);
	ege_fillellipse(AI_x-1.5*AI_r,AI_y-1.5*AI_r,0.2*AI_r,0.2*AI_r);
	ege_fillellipse(AI_x-1.5*AI_r,AI_y+1.3*AI_r,0.2*AI_r,0.2*AI_r);
	ege_fillellipse(AI_x+1.3*AI_r,AI_y-1.5*AI_r,0.2*AI_r,0.2*AI_r);
	ege_fillellipse(AI_x+1.3*AI_r,AI_y+1.3*AI_r,0.2*AI_r,0.2*AI_r);
	
	//绘制边框阴影 (右上角圆)
	
	setcolor(EGEARGB(0xff,0x1e,0x1f,0x10));
	setlinewidth(0.08*AI_r);
	ege_arc(AI_x+1.3*AI_r,AI_y-1.5*AI_r,0.2*AI_r,0.2*AI_r,2,-94);
	ege_fillellipse(AI_x+1.3*AI_r,AI_y-1.5*AI_r,0.2*AI_r,0.2*AI_r);
	
}


void draw_attitude_indicator_background(){
	
	//绘制指示背景	 
	
	
//	//背景初版解决方案：用一个半圆和圆相互遮盖 
//	if(pitchAngle >= 0){
//		
//		setfillcolor(EGEARGB(0xff,0x84,0xa8,0xa8));
//		ege_fillellipse(AI_x - AI_r,AI_y - AI_r,2 * AI_r,2 * AI_r);
//		
//		//10度显示为为5分之1的r距离,即1度50分之1 
//		
//		setfillcolor(EGEARGB(0xff,0x08,0x0a,0x0b));
//		ege_fillpie(AI_x - AI_r - AI_r / 50 * 360 * (pitchAngle / 2 / PI) * sin(rollAngle),
//			AI_y - AI_r + AI_r / 50 * 360 * (pitchAngle / 2 / PI) * cos(rollAngle),
//			2 * AI_r,2 * AI_r,0 + 360 * (rollAngle / 2 / PI),180);
//		
//	}
//	else{
//		
//		setfillcolor(EGEARGB(0xff,0x08,0x0a,0x0b));
//		ege_fillellipse(AI_x - AI_r,AI_y - AI_r,2 * AI_r,2 * AI_r);
//		
////		setfillcolor(EGEARGB(0xff,0x8f,0xc5,0xcb));
//		setfillcolor(EGEARGB(0xff,0x84,0xa8,0xa8));
//		ege_fillpie(AI_x - AI_r - AI_r / 50 * 360 * (pitchAngle / 2 / PI) * sin(rollAngle),
//			AI_y - AI_r + AI_r / 50 * 360 * (pitchAngle / 2 / PI) * cos(rollAngle),
//			2 * AI_r,2 * AI_r,-180 + 360 * (rollAngle / 2 / PI),180);
//		
//	}
	
	//背景改进版解决方案：在旋转坐标系的基础上，用一个半椭圆和圆相互遮盖 
	
//	//没加坐标系变换版
//	if(pitchAngle >= 0){
//		
//		//10度显示为为5分之1的r距离,即1度50分之1 
//		
//		//画天空
//		setfillcolor(EGEARGB(0xff,0x84,0xa8,0xa8));
//		ege_fillellipse(AI_x - AI_r,AI_y - AI_r,2 * AI_r,2 * AI_r);
//		
//		//画地面
//		setfillcolor(EGEARGB(0xff,0x08,0x0a,0x0b));
//		ege_fillpie(AI_x - AI_r,AI_y - AI_r + 2 * (360 * pitchAngle / 2 / PI * 0.02 * AI_r),2 * AI_r,2 * AI_r - 2 * (360 * pitchAngle / 2 / PI * 0.02 * AI_r),0,180);
//		
//	}
//	else{
//		
//		//画地面
//		setfillcolor(EGEARGB(0xff,0x08,0x0a,0x0b));
//		ege_fillellipse(AI_x - AI_r,AI_y - AI_r,2 * AI_r,2 * AI_r);
//		
//		//画天空
//		setfillcolor(EGEARGB(0xff,0x84,0xa8,0xa8));
//		ege_fillpie(AI_x - AI_r,AI_y - AI_r,2 * AI_r,2 * AI_r + 2 * (360 * pitchAngle / 2 / PI * 0.02 * AI_r),-180,180);//此处因为pitchAngle小于0，所以应该用+！
//		
//	}
	
	
	//加坐标系变换版
	if(pitchAngle >= 0){
		
		//10度显示为为5分之1的r距离,即1度50分之1 
		
		//画天空
		setfillcolor(EGEARGB(0xff,0x84,0xa8,0xa8));
		ege_fillellipse(AI_x - AI_r,AI_y - AI_r,2 * AI_r,2 * AI_r);
		
		//画地面
		ege_transform_matrix m;
		ege_get_transform(&m);
		ege_transform_translate(AI_x,AI_y);
		ege_transform_rotate(360 * rollAngle / 2 / PI);
		setfillcolor(EGEARGB(0xff,0x08,0x0a,0x0b));
		if(2 * AI_r - 2 * (360 * pitchAngle / 2 / PI * 0.02 * AI_r) > 0)
			ege_fillpie(-AI_r,-AI_r + 2 * (360 * pitchAngle / 2 / PI * 0.02 * AI_r),2 * AI_r,2 * AI_r - 2 * (360 * pitchAngle / 2 / PI * 0.02 * AI_r),0,180);
		ege_set_transform(&m);
		
	}
	else{
		
		//画地面
		setfillcolor(EGEARGB(0xff,0x08,0x0a,0x0b));
		ege_fillellipse(AI_x - AI_r,AI_y - AI_r,2 * AI_r,2 * AI_r);
		
		//画天空
		ege_transform_matrix m;
		ege_get_transform(&m);
		ege_transform_translate(AI_x,AI_y);
		ege_transform_rotate(360 * rollAngle / 2 / PI);
		setfillcolor(EGEARGB(0xff,0x84,0xa8,0xa8));
		if(2 * AI_r + 2 * (360 * pitchAngle / 2 / PI * 0.02 * AI_r) > 0)
			ege_fillpie(-AI_r,-AI_r,2 * AI_r,2 * AI_r + 2 * (360 * pitchAngle / 2 / PI * 0.02 * AI_r),-180,180);
		ege_set_transform(&m);
		
	}
	
	
	
	
	//俯仰角刻度
	
	setcolor(WHITE);
	setlinewidth(0.018 * AI_r);
	double AI_line_lx;
	double AI_line_ly;
	double AI_line_rx;
	double AI_line_ry;
	double AI_circle_x;
	double AI_circle_y;
	
	
	//+5度
	setfillcolor(WHITE);
	AI_circle_x = - (AI_y - 0.1 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x - 0.03 * AI_r;
	AI_circle_y = (AI_y - 0.1 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + AI_y - 0.03 * AI_r;
	if(sqrt((AI_x - AI_circle_x) * (AI_x - AI_circle_x) + (AI_y - AI_circle_y) * (AI_y - AI_circle_y)) < 1.4 * AI_r)
		ege_fillellipse(AI_circle_x,AI_circle_y,0.06 * AI_r,0.06 * AI_r);//原坐标： (AI_x - 0.03 * AI_r,AI_y - 0.13 * AI_r,0.06 * AI_r,0.06 * AI_r)
	
	//+15度
	setfillcolor(WHITE);
	AI_circle_x = - (AI_y - 0.3 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x - 0.03 * AI_r;
	AI_circle_y = (AI_y - 0.3 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + AI_y - 0.03 * AI_r;
	if(sqrt((AI_x - AI_circle_x) * (AI_x - AI_circle_x) + (AI_y - AI_circle_y) * (AI_y - AI_circle_y)) < 1.4 * AI_r)
		ege_fillellipse(AI_circle_x,AI_circle_y,0.06 * AI_r,0.06 * AI_r);
	
	//-5度
	setfillcolor(WHITE);
	AI_circle_x = - (AI_y + 0.1 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x - 0.03 * AI_r;
	AI_circle_y = (AI_y + 0.1 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + AI_y - 0.03 * AI_r;
	if(sqrt((AI_x - AI_circle_x) * (AI_x - AI_circle_x) + (AI_y - AI_circle_y) * (AI_y - AI_circle_y)) < 1.4 * AI_r)
		ege_fillellipse(AI_circle_x,AI_circle_y,0.06 * AI_r,0.06 * AI_r);
	
	//-15度
	setfillcolor(WHITE);
	AI_circle_x = - (AI_y + 0.3 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x - 0.03 * AI_r;
	AI_circle_y = (AI_y + 0.3 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + AI_y - 0.03 * AI_r;
	if(sqrt((AI_x - AI_circle_x) * (AI_x - AI_circle_x) + (AI_y - AI_circle_y) * (AI_y - AI_circle_y)) < 1.4 * AI_r)
		ege_fillellipse(AI_circle_x,AI_circle_y,0.06 * AI_r,0.06 * AI_r);
	
	
	//+10度 
	AI_line_lx = (AI_x - 0.3 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 0.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y - 0.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.3 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.3 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 0.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y - 0.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.3 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);	
	
	//+20度
	AI_line_lx = (AI_x - 0.45 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 0.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y - 0.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.45 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.45 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 0.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y - 0.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.45 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);
	
	//+30度
	AI_line_lx = (AI_x - 0.56 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 0.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y - 0.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.56 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.56 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 0.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y - 0.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.56 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);
	
	//+40度
	AI_line_lx = (AI_x - 0.56 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 0.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y - 0.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.56 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.56 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 0.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y - 0.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.56 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);
	
	//+50度 
	AI_line_lx = (AI_x - 0.3 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 1 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y - 1 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.3 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.3 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 1 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y - 1 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.3 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);
	
	//+60度
	AI_line_lx = (AI_x - 0.56 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 1.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y - 1.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.56 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.56 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 1.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y - 1.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.56 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);
	
	//+70度 
	AI_line_lx = (AI_x - 0.3 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 1.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y - 1.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.3 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.3 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 1.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y - 1.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.3 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);
	
	//+80度
	AI_line_lx = (AI_x - 0.56 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 1.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y - 1.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.56 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.56 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 1.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y - 1.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.56 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);
	
	//+90度 
	AI_line_lx = (AI_x - 0.3 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 1.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y - 1.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.3 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.3 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 1.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y - 1.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.3 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);
	
	
	//-10度 
	AI_line_lx = (AI_x - 0.3 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 0.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y + 0.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.3 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.3 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 0.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y + 0.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.3 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);
	
	//-20度
	AI_line_lx = (AI_x - 0.45 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 0.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y + 0.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.45 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.45 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 0.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y + 0.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.45 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);
	
	//-30度
	AI_line_lx = (AI_x - 0.56 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 0.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y + 0.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.56 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.56 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 0.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y + 0.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.56 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);
	
	//-40度
	AI_line_lx = (AI_x - 0.56 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 0.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y + 0.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.56 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.56 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 0.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y + 0.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.56 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);
	
	//-50度 
	AI_line_lx = (AI_x - 0.3 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 1 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y + 1 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.3 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.3 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 1 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y + 1 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.3 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);
	
	//-60度
	AI_line_lx = (AI_x - 0.56 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 1.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y + 1.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.56 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.56 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 1.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y + 1.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.56 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);
	
	//-70度 
	AI_line_lx = (AI_x - 0.3 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 1.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y + 1.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.3 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.3 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 1.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y + 1.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.3 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);
	
	//-80度
	AI_line_lx = (AI_x - 0.56 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 1.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y + 1.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.56 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.56 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 1.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y + 1.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.56 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);
	
	//-90度 
	AI_line_lx = (AI_x - 0.3 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 1.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y + 1.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.3 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.3 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 1.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y + 1.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.3 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);
	
	
	//绘制指示背景上下的遮盖
	
	//上面的 
	setfillcolor(EGEARGB(0xff,0x73,0x92,0x93));
	ege_point attitude_indicator_points8[3] = {{(AI_x - 0.95 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 0.65 * AI_r - AI_y) * sin(rollAngle) + AI_x,
		(AI_y - 0.65 * AI_r - AI_y) * cos(rollAngle) + (AI_x - 0.95 * AI_r - AI_x) * sin(rollAngle) + AI_y},
		{AI_x + 1.1 * AI_r * sin(rollAngle),AI_y - 1.1 * AI_r + 1.1 * AI_r * (1 - cos(rollAngle))},
		{(AI_x + 0.95 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 0.65 * AI_r - AI_y) * sin(rollAngle) + AI_x,
			(AI_y - 0.65 * AI_r - AI_y) * cos(rollAngle) + (AI_x + 0.95 * AI_r - AI_x) * sin(rollAngle) + AI_y}};
	ege_fillpoly(3,attitude_indicator_points8);
	
	//上面的横滚指针
	setfillcolor(WHITE);
	
//		//原始坐标 
//	double AI_Triangle_1x = AI_x;
//	double AI_Triangle_1y = AI_y - AI_r;
//	double AI_Triangle_2x = AI_x - 0.06 * AI_r;
//	double AI_Triangle_2y = AI_y - (1 - 0.125) * AI_r;
//	double AI_Triangle_3x = AI_x + 0.06 * AI_r;
//	double AI_Triangle_3y = AI_y - (1 - 0.125) * AI_r;
	
	double AI_Triangle_1x = -(AI_y - AI_r - AI_y) * sin(rollAngle) + AI_x;
	double AI_Triangle_1y = (AI_y - AI_r - AI_y) * cos(rollAngle) + AI_y;
	double AI_Triangle_2x = (AI_x - 0.06 * AI_r - AI_x) * cos(rollAngle) - (AI_y - (1 - 0.125) * AI_r - AI_y) * sin(rollAngle) + AI_x;
	double AI_Triangle_2y = (AI_y - (1 - 0.125) * AI_r - AI_y) * cos(rollAngle) + (AI_x - 0.06 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	double AI_Triangle_3x = (AI_x + 0.06 * AI_r - AI_x) * cos(rollAngle) - (AI_y - (1 - 0.125) * AI_r - AI_y) * sin(rollAngle) + AI_x;
	double AI_Triangle_3y = (AI_y - (1 - 0.125) * AI_r - AI_y) * cos(rollAngle) + (AI_x + 0.06 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	
	ege_point attitude_indicator_points9[3] = {
		{AI_Triangle_1x,AI_Triangle_1y},
		{AI_Triangle_2x,AI_Triangle_2y},
		{AI_Triangle_3x,AI_Triangle_3y}
	};
	ege_fillpoly(3,attitude_indicator_points9);
	
	
	
	//下面的 
	setfillcolor(BLACK);
	ege_fillpie(AI_x - 0.7 * AI_r,AI_y + 0.4 * AI_r,1.4 * AI_r,0.6 * AI_r,0,180);
	
	//制造背景边上的阴影 
	
	setcolor(EGEARGB(0x7f,0x00,0x00,0x00));
	setlinewidth(0.05*AI_r);
	ege_ellipse(AI_x - AI_r,AI_y - AI_r,2 * AI_r,2 * AI_r);
	
	//绘制背景俯仰角度标线 
	
//	ege_line(); 
	
	//绘制飞机标志
	
	//实机版本 
	//	setcolor(EGEARGB(0xff,0xc4,0x9a,0x61));
	//	setlinewidth(0.02*AI_r);
	//	
	//	ege_line(AI_x + 0.25 * AI_r,AI_y + 0.075 * AI_r,
	//	AI_x + 0.45 * AI_r,AI_y + 0.01 * AI_r);
	//	ege_line(AI_x + 0.45 * AI_r,AI_y + 0.01 * AI_r,
	//	AI_x + 0.8 * AI_r,AI_y + 0.01 * AI_r);
	//	
	//	ege_line(AI_x - 0.25 * AI_r,AI_y + 0.075 * AI_r,
	//	AI_x - 0.45 * AI_r,AI_y + 0.01 * AI_r);
	//	ege_line(AI_x - 0.45 * AI_r,AI_y + 0.01 * AI_r,
	//	AI_x - 0.8 * AI_r,AI_y + 0.01 * AI_r);
	//	
	//	setfillcolor(YELLOW);
	//	ege_point attitude_indicator_points1[3] = {{AI_x,AI_y},{AI_x + 0.5 * AI_r,AI_y + 0.15 * AI_r},
	//	{AI_x - 0.5 * AI_r,AI_y + 0.15 * AI_r}};	
	//	ege_fillpoly(3,attitude_indicator_points1);
	//	
	//	setfillcolor(EGEARGB(0xaf,0xc1,0x9d,0x7b));
	//	ege_point attitude_indicator_points2[4] = {{AI_x,AI_y},{AI_x + 0.5 * AI_r,AI_y + 0.15 * AI_r},
	//	{AI_x,AI_y + 0.05 * AI_r},
	//	{AI_x - 0.5 * AI_r,AI_y + 0.15 * AI_r}};	
	//	ege_fillpoly(4,attitude_indicator_points2);
	
	//X-Plane上的版本 
	
//		setcolor(EGEARGB(0xff,0xa4,0x8f,0x2a));//黄色
	setcolor(EGEARGB(0xff,0x66,0x29,0x14));//红色 
	setlinewidth(0.02*AI_r);
	ege_line(AI_x - 0.2 * AI_r,AI_y + 0.08 * AI_r,AI_x - 0.2 * AI_r,AI_y + 0.13 * AI_r);
	ege_line(AI_x + 0.2 * AI_r,AI_y + 0.08 * AI_r,AI_x + 0.2 * AI_r,AI_y + 0.13 * AI_r);		
	
	
//		setcolor(EGEARGB(0xff,0xed,0xd3,0x14));//黄色
	setcolor(EGEARGB(0xff,0x66,0x29,0x14));//红色 
	setlinewidth(0.008*AI_r);
	ege_line(AI_x - 0.35 * AI_r,AI_y,AI_x - AI_r,AI_y);
	ege_line(AI_x + 0.35 * AI_r,AI_y,AI_x + AI_r,AI_y);		
	
//		setfillcolor(EGEARGB(0xff,0xed,0xd3,0x14));//黄色
	setfillcolor(EGEARGB(0xff,0xad,0x25,0x2c));//红色 
	ege_point attitude_indicator_points2[3] = {{AI_x - 0.18 * AI_r,AI_y + 0.06 * AI_r},
		{AI_x - 0.24 * AI_r,AI_y + 0.08 * AI_r},
		{AI_x - 0.365 * AI_r,AI_y - 0.008 * AI_r}};	
	ege_fillpoly(3,attitude_indicator_points2);
	ege_point attitude_indicator_points3[3] = {{AI_x + 0.18 * AI_r,AI_y + 0.06 * AI_r},
		{AI_x + 0.24 * AI_r,AI_y + 0.08 * AI_r},
		{AI_x + 0.365 * AI_r,AI_y - 0.008 * AI_r}};	
	ege_fillpoly(3,attitude_indicator_points3);
	
	
	ege_point attitude_indicator_points1[3] = {{AI_x,AI_y},{AI_x + 0.35 * AI_r,AI_y + 0.1 * AI_r},
		{AI_x - 0.35 * AI_r,AI_y + 0.1 * AI_r}};	
	ege_fillpoly(3,attitude_indicator_points1);
	
	
	
	//绘制边框（负责遮盖的圆） 
	
	setcolor(Frame_color);
	setlinewidth(0.5*AI_r);
	ege_ellipse(AI_x-1.25*AI_r,AI_y-1.25*AI_r,2.5*AI_r,2.5*AI_r);
	
	
	//绘制背景周围黑边
	
	setcolor(EGEARGB(0xff,0x1b,0x1c,0x1d)); 
	setlinewidth(0.4*AI_r);
	ege_arc(AI_x - 1.2 * AI_r,AI_y - 1.2 * AI_r,2.4 * AI_r,2.4 * AI_r,-20,-140);
	setlinewidth(0.1*AI_r);
	ege_arc(AI_x - 1.05 * AI_r,AI_y - 1.05 * AI_r,2.1 * AI_r,2.1 * AI_r,-20,220);
	ege_arc(AI_x - 1.326 * AI_r,AI_y -0.4 * AI_r,2.652 * AI_r,1.45 * AI_r,9,162);
	
	setfillcolor(EGEARGB(0xff,0x1b,0x1c,0x1d)); 
	ege_fillrect(AI_x - 1.316 * AI_r,AI_y - 0.48 * AI_r,
		0.3 * AI_r,1.04 * AI_r);
	ege_fillrect(AI_x + 1.016 * AI_r,AI_y - 0.48 * AI_r,
		0.3 * AI_r,1.04 * AI_r);
	
	floodfill(AI_x - 0.9 * AI_r,AI_y + 0.8 * AI_r,EGEARGB(0xff,0x1b,0x1c,0x1d));
	floodfill(AI_x + 0.9 * AI_r,AI_y + 0.8 * AI_r,EGEARGB(0xff,0x1b,0x1c,0x1d));
	
}


void draw_attitude_indicator_index_mark(){
	
	//绘制边框横滚角度标线 
	
	for(int i = -90;i <= 90; i++ ){
		
		//普通白线 
		
		setcolor(WHITE);
		setlinewidth(0.013*AI_r);
		
		if(i == 10||i == 20||i == 60||i == -10||i == -20||i == -60){
			ege_line(AI_x + 1.18 * AI_r * sin(i * PI / 180),AI_y - 1.18 * AI_r + 1.18 * AI_r * (1 - cos(i * PI / 180)),
				AI_x + 1.01 * AI_r * sin(i * PI / 180),AI_y - 1.01 * AI_r +  1.01 * AI_r * (1 - cos(i * PI / 180)));
		}
		
		if(i == -30||i == 30){
			ege_line(AI_x + 1.25* AI_r * sin(i * PI / 180),AI_y - 1.25 * AI_r + 1.25 * AI_r * (1 - cos(i * PI / 180)),
				AI_x + 1.01 * AI_r * sin(i * PI / 180),AI_y - 1.01 * AI_r +  1.01 * AI_r * (1 - cos(i * PI / 180)));
		}
	}
	
	//下滑道偏离指示器 
	
	setcolor(WHITE);
	setlinewidth(0.0105 * AI_r);
	ege_line(AI_x - 1.30 * AI_r,AI_y + 0.06 * AI_r,AI_x - 1.01 * AI_r,AI_y + 0.06 * AI_r);
	
	setfillcolor(WHITE);
	ege_fillellipse(AI_x - 1.12 * AI_r,AI_y - (0.4 - 0.06) * AI_r,0.056 * AI_r,0.056 * AI_r);
	ege_fillellipse(AI_x - 1.12 * AI_r,AI_y - (0.2 - 0.06) * AI_r,0.056 * AI_r,0.056 * AI_r);
	ege_fillellipse(AI_x - 1.12 * AI_r,AI_y + (0.2 - 0.056 + 0.06) * AI_r,0.056 * AI_r,0.056 * AI_r);
	ege_fillellipse(AI_x - 1.12 * AI_r,AI_y + (0.4 - 0.056 + 0.06) * AI_r,0.056 * AI_r,0.056 * AI_r);
	
	
	//特殊箭头 
	
	setfillcolor(WHITE);
	ege_point attitude_indicator_points5[3] = {{AI_x ,AI_y - 1.01 * AI_r},
		{AI_x - 0.06 * AI_r,AI_y -1.25  * AI_r},
		{AI_x + 0.06 * AI_r,AI_y - 1.25 * AI_r}
	};
	ege_fillpoly(3,attitude_indicator_points5);
	
	setfillcolor(WHITE);
	ege_point attitude_indicator_points6[3] = {
		{-(AI_y - 1.01 * AI_r - AI_y) * 0.707106 + AI_x, (AI_y - 1.01 * AI_r - AI_y) * 0.707106 + AI_y},
		{(AI_x - 0.06 * AI_r - AI_x) * 0.707106 - (AI_y - 1.25  * AI_r - AI_y) * 0.707106 + AI_x, (AI_y - 1.25  * AI_r - AI_y) * 0.707106 + (AI_x - 0.06 * AI_r - AI_x) * 0.707106 + AI_y},
		{(AI_x + 0.06 * AI_r - AI_x) * 0.707106 - (AI_y - 1.25  * AI_r - AI_y) * 0.707106 + AI_x, (AI_y - 1.25  * AI_r - AI_y) * 0.707106 + (AI_x + 0.06 * AI_r - AI_x) * 0.707106 + AI_y}
	};
	ege_fillpoly(3,attitude_indicator_points6);
	
	setfillcolor(WHITE);
	ege_point attitude_indicator_points7[3] = {
		{-(AI_y - 1.01 * AI_r - AI_y) * -0.707106 + AI_x, (AI_y - 1.01 * AI_r - AI_y) * 0.707106 + AI_y},
		{(AI_x - 0.06 * AI_r - AI_x) * 0.707106 - (AI_y - 1.25  * AI_r - AI_y) * -0.707106 + AI_x, (AI_y - 1.25  * AI_r - AI_y) * 0.707106 + (AI_x - 0.06 * AI_r - AI_x) * -0.707106 + AI_y},
		{(AI_x + 0.06 * AI_r - AI_x) * 0.707106 - (AI_y - 1.25  * AI_r - AI_y) * -0.707106 + AI_x, (AI_y - 1.25  * AI_r - AI_y) * 0.707106 + (AI_x + 0.06 * AI_r - AI_x) * -0.707106 + AI_y}
	};
	ege_fillpoly(3,attitude_indicator_points7);
	
	
}


int main(){
	initgraph(800,800,INIT_RENDERMANUAL);
	setrendermode(RENDER_MANUAL);
	setbkcolor(Background_color); 
	ege_enable_aa(true);
	
	for(;is_run();delay_fps(60),cleardevice()){
		
		//绘制背景 
		
		draw_attitude_indicator_frame();
		
		draw_attitude_indicator_background();
		
		draw_attitude_indicator_index_mark();
		
//		setfillcolor(WHITE);
//		ege_point attitude_indicator_points5[3] = {{AI_x ,AI_y - 1.01 * AI_r},
//		{AI_x - 0.06 * AI_r,AI_y -1.25  * AI_r},
//		{AI_x + 0.06 * AI_r,AI_y - 1.25 * AI_r}};
//		ege_fillpoly(3,attitude_indicator_points5);
		
		
		//键盘模拟操作测试 
		
		if(GetAsyncKeyState(0x41) & 0x8000)
			rollAngle-=0.02;
		if(GetAsyncKeyState(0x44) & 0x8000)
			rollAngle+=0.02;
		if(GetAsyncKeyState(0x57) & 0x8000)
			pitchAngle+=0.02;
		if(GetAsyncKeyState(0x53) & 0x8000)
			pitchAngle-=0.02;
		
//		if(GetAsyncKeyState(0x42) & 0x0001)
//			resizewindow(1000,1000);
//		if(GetAsyncKeyState(0x43) & 0x0001)
//			resizewindow(800,800);
		
	}
	
	
	
	
	getch();
	return 0;
}

//void draw_attitude_indicator(){
//	
//}
//
//void draw_frame(double frame_x,double frame_y,double frame_r){
//	
//}
//
//void draw_screw(double screw_x,double screw_y,double screw_r){
//	
//}
