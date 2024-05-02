#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>

#include "DrawScrew.h"

#define Background_color EGEARGB(0xff,0x1b,0x20,0x25)
#define Frame_color1 EGEARGB(0xff,0x24,0x28,0x33)	//EGEARGB(0xff,0x53,0x52,0x56)   // 0xff,0x39,0x39,0x40
#define Frame_color2 EGEARGB(0xff,0x1f,0x23,0x2e)	//24，28，33	//0xff,0x2f,0x2f,0x32

//函数声明
void draw_attitude_indicator_frame(double AI_x, double AI_y, double AI_r);
void draw_attitude_indicator_background(double AI_x, double AI_y, double AI_r);
void draw_attitude_indicator_index_mark(double AI_x, double AI_y, double AI_r);
void draw_slip_indicator(double AI_x, double AI_y, double AI_r);
void draw_botton_and_screw(double AI_x, double AI_y, double AI_r);
void darw_AI_light(double AI_x, double AI_y, double AI_r);

//引用全局变量
extern double pitchAngle;
extern double rollAngle;
extern double sideSlipAngle;
extern double headingIndication;
extern double glideIndication;

extern int G_light;

void draw_AI(double AI_x, double AI_y, double AI_side ){
	
	double AI_r = AI_side / 3;
	
	draw_attitude_indicator_frame(AI_x, AI_y, AI_r);
	
	draw_attitude_indicator_background(AI_x, AI_y, AI_r);
	
	draw_attitude_indicator_index_mark(AI_x, AI_y, AI_r);
	
	draw_slip_indicator(AI_x, AI_y, AI_r);
	
	draw_botton_and_screw(AI_x, AI_y, AI_r);
	
	darw_AI_light(AI_x, AI_y, AI_r);
	
}


void draw_attitude_indicator_frame(double AI_x, double AI_y, double AI_r){
	
	//绘制边框阴影 
	
	setfillcolor(BLACK);
	ege_fillrect(AI_x-1.3*AI_r,AI_y-1.64*AI_r,2.7*AI_r,0.04*AI_r);
	ege_fillrect(AI_x+1.5*AI_r,AI_y-1.5*AI_r,0.04*AI_r,2.9*AI_r);
	ege_fillellipse(AI_x-1.42*AI_r,AI_y-1.64*AI_r,0.2*AI_r,0.2*AI_r);
	ege_fillellipse(AI_x+1.34*AI_r,AI_y+1.3*AI_r,0.2*AI_r,0.2*AI_r);
	
	
	//绘制边框（底座）
	
	//边框长3.2*r 宽3.0*r 
	ege_setpattern_lineargradient(AI_x,AI_y-1.6*AI_r,Frame_color1,AI_x,AI_y+1.6*AI_r,Frame_color2);
	ege_fillrect(AI_x-1.5*AI_r,AI_y-1.6*AI_r,3*AI_r,3.2*AI_r);
	ege_setpattern_none();
	
	//遮盖四个角，并画圆形成圆角
	setfillcolor(Background_color);
	ege_fillrect(AI_x-1.5*AI_r,AI_y-1.6*AI_r,0.1*AI_r,0.1*AI_r);
	ege_fillrect(AI_x-1.5*AI_r,AI_y+1.5*AI_r,0.1*AI_r,0.1*AI_r);
	ege_fillrect(AI_x+1.4*AI_r,AI_y-1.6*AI_r,0.1*AI_r,0.1*AI_r);
	ege_fillrect(AI_x+1.4*AI_r,AI_y+1.5*AI_r,0.1*AI_r,0.1*AI_r);
	
	ege_setpattern_lineargradient(AI_x,AI_y-1.6*AI_r,Frame_color1,AI_x,AI_y+1.6*AI_r,Frame_color2);
	ege_fillellipse(AI_x-1.5*AI_r,AI_y-1.6*AI_r,0.2*AI_r,0.2*AI_r);
	ege_fillellipse(AI_x-1.5*AI_r,AI_y+1.4*AI_r,0.2*AI_r,0.2*AI_r);
	ege_fillellipse(AI_x+1.3*AI_r,AI_y-1.6*AI_r,0.2*AI_r,0.2*AI_r);
	ege_fillellipse(AI_x+1.3*AI_r,AI_y+1.4*AI_r,0.2*AI_r,0.2*AI_r);
	ege_setpattern_none();
	
	//绘制边框阴影 (右上角圆)
	
	setcolor(BLACK);
	setlinewidth(0.08*AI_r);
	ege_arc(AI_x+1.3*AI_r,AI_y-1.6*AI_r,0.2*AI_r,0.2*AI_r,2,-94);
	
	ege_setpattern_lineargradient(AI_x,AI_y-1.6*AI_r,Frame_color1,AI_x,AI_y+1.6*AI_r,Frame_color2);
	ege_fillellipse(AI_x+1.3*AI_r,AI_y-1.6*AI_r,0.2*AI_r,0.2*AI_r);
	ege_setpattern_none();
	
}


void draw_attitude_indicator_background(double AI_x, double AI_y, double AI_r){
	
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
		setfillcolor(EGEARGB(0xff,0x66,0x92,0x96));	//原EGEARGB(0xff,0x84,0xa8,0xa8)
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
		setfillcolor(EGEARGB(0xff,0x66,0x92,0x96));	//原EGEARGB(0xff,0x84,0xa8,0xa8)
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
	AI_line_lx = (AI_x - 0.46 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 0.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y - 0.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.46 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.46 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 0.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y - 0.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.46 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);
	
	
	
	//设置字体格式等
	setcolor(WHITE);
//	setfont(1 * AI_r,1 * AI_r,"微软雅黑");
	setbkmode(TRANSPARENT);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	LOGFONTW AI_font;
	setfont(0.16 * AI_r,0.08 * AI_r,"Bahnschrift");
	getfont(&AI_font);
//	strcpy(AI_font.lfFaceName,"微软雅黑");
//	AI_font.lfWidth = 0.08 * AI_r;
//	AI_font.lfHeight = 0.15 * AI_r;
	AI_font.lfEscapement = -10 * 360 * rollAngle / 2 / PI;
	AI_font.lfWeight = 2.5 * AI_r;
	setfont(&AI_font);
	double AI_gear_x;
	double AI_gear_y;
	
	
	//+20刻度
	AI_gear_x = (- 0.55 * AI_r) * cos(rollAngle) - (- 0.38 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * sin(rollAngle) + AI_x;
	AI_gear_y = (- 0.55 * AI_r) * sin(rollAngle) + (- 0.38 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * cos(rollAngle) + AI_y;
	if(sqrt((AI_gear_x - AI_x) * (AI_gear_x - AI_x) + (AI_gear_y - AI_y) * (AI_gear_y - AI_y)) < 1.2 * AI_r) 
		ege_drawtext("20", AI_gear_x, AI_gear_y);
	AI_gear_x = (0.55 * AI_r) * cos(rollAngle) - (- 0.38 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * sin(rollAngle) + AI_x;
	AI_gear_y = (0.55 * AI_r) * sin(rollAngle) + (- 0.38 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * cos(rollAngle) + AI_y;
	if(sqrt((AI_gear_x - AI_x) * (AI_gear_x - AI_x) + (AI_gear_y - AI_y) * (AI_gear_y - AI_y)) < 1.2 * AI_r) 
		ege_drawtext("20", AI_gear_x, AI_gear_y);
	
	//+40刻度
	AI_gear_x = (- 0.55 * AI_r) * cos(rollAngle) - (- 0.78 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * sin(rollAngle) + AI_x;
	AI_gear_y = (- 0.55 * AI_r) * sin(rollAngle) + (- 0.78 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * cos(rollAngle) + AI_y;
	if(sqrt((AI_gear_x - AI_x) * (AI_gear_x - AI_x) + (AI_gear_y - AI_y) * (AI_gear_y - AI_y)) < 1.2 * AI_r) 
		ege_drawtext("40", AI_gear_x, AI_gear_y);
	AI_gear_x = (0.55 * AI_r) * cos(rollAngle) - (- 0.78 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * sin(rollAngle) + AI_x;
	AI_gear_y = (0.55 * AI_r) * sin(rollAngle) + (- 0.78 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * cos(rollAngle) + AI_y;
	if(sqrt((AI_gear_x - AI_x) * (AI_gear_x - AI_x) + (AI_gear_y - AI_y) * (AI_gear_y - AI_y)) < 1.2 * AI_r) 
		ege_drawtext("40", AI_gear_x, AI_gear_y);
	
	//+60刻度
	AI_gear_x = (- 0.55 * AI_r) * cos(rollAngle) - (- 1.18 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * sin(rollAngle) + AI_x;
	AI_gear_y = (- 0.55 * AI_r) * sin(rollAngle) + (- 1.18 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * cos(rollAngle) + AI_y;
	if(sqrt((AI_gear_x - AI_x) * (AI_gear_x - AI_x) + (AI_gear_y - AI_y) * (AI_gear_y - AI_y)) < 1.2 * AI_r) 
		ege_drawtext("60", AI_gear_x, AI_gear_y);
	AI_gear_x = (0.55 * AI_r) * cos(rollAngle) - (- 1.18 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * sin(rollAngle) + AI_x;
	AI_gear_y = (0.55 * AI_r) * sin(rollAngle) + (- 1.18 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * cos(rollAngle) + AI_y;
	if(sqrt((AI_gear_x - AI_x) * (AI_gear_x - AI_x) + (AI_gear_y - AI_y) * (AI_gear_y - AI_y)) < 1.2 * AI_r) 
		ege_drawtext("60", AI_gear_x, AI_gear_y);
	
	//+80刻度
	AI_gear_x = (- 0.55 * AI_r) * cos(rollAngle) - (- 1.58 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * sin(rollAngle) + AI_x;
	AI_gear_y = (- 0.55 * AI_r) * sin(rollAngle) + (- 1.58 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * cos(rollAngle) + AI_y;
	if(sqrt((AI_gear_x - AI_x) * (AI_gear_x - AI_x) + (AI_gear_y - AI_y) * (AI_gear_y - AI_y)) < 1.2 * AI_r) 
		ege_drawtext("80", AI_gear_x, AI_gear_y);
	AI_gear_x = (0.55 * AI_r) * cos(rollAngle) - (- 1.58 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * sin(rollAngle) + AI_x;
	AI_gear_y = (0.55 * AI_r) * sin(rollAngle) + (- 1.58 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * cos(rollAngle) + AI_y;
	if(sqrt((AI_gear_x - AI_x) * (AI_gear_x - AI_x) + (AI_gear_y - AI_y) * (AI_gear_y - AI_y)) < 1.2 * AI_r) 
		ege_drawtext("80", AI_gear_x, AI_gear_y);
	
	//-20刻度
	AI_gear_x = (- 0.55 * AI_r) * cos(rollAngle) - (0.42 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * sin(rollAngle) + AI_x;
	AI_gear_y = (- 0.55 * AI_r) * sin(rollAngle) + (0.42 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * cos(rollAngle) + AI_y;
	if(sqrt((AI_gear_x - AI_x) * (AI_gear_x - AI_x) + (AI_gear_y - AI_y) * (AI_gear_y - AI_y)) < 1.2 * AI_r) 
		ege_drawtext("20", AI_gear_x, AI_gear_y);
	AI_gear_x = (0.55 * AI_r) * cos(rollAngle) - (0.42 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * sin(rollAngle) + AI_x;
	AI_gear_y = (0.55 * AI_r) * sin(rollAngle) + (0.42 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * cos(rollAngle) + AI_y;
	if(sqrt((AI_gear_x - AI_x) * (AI_gear_x - AI_x) + (AI_gear_y - AI_y) * (AI_gear_y - AI_y)) < 1.2 * AI_r) 
		ege_drawtext("20", AI_gear_x, AI_gear_y);
	
	//-40刻度
	AI_gear_x = (- 0.55 * AI_r) * cos(rollAngle) - (0.82 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * sin(rollAngle) + AI_x;
	AI_gear_y = (- 0.55 * AI_r) * sin(rollAngle) + (0.82 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * cos(rollAngle) + AI_y;
	if(sqrt((AI_gear_x - AI_x) * (AI_gear_x - AI_x) + (AI_gear_y - AI_y) * (AI_gear_y - AI_y)) < 1.2 * AI_r) 
		ege_drawtext("40", AI_gear_x, AI_gear_y);
	AI_gear_x = (0.55 * AI_r) * cos(rollAngle) - (0.82 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * sin(rollAngle) + AI_x;
	AI_gear_y = (0.55 * AI_r) * sin(rollAngle) + (0.82 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * cos(rollAngle) + AI_y;
	if(sqrt((AI_gear_x - AI_x) * (AI_gear_x - AI_x) + (AI_gear_y - AI_y) * (AI_gear_y - AI_y)) < 1.2 * AI_r) 
		ege_drawtext("40", AI_gear_x, AI_gear_y);
	
	//-60刻度
	AI_gear_x = (- 0.55 * AI_r) * cos(rollAngle) - (1.22 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * sin(rollAngle) + AI_x;
	AI_gear_y = (- 0.55 * AI_r) * sin(rollAngle) + (1.22 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * cos(rollAngle) + AI_y;
	if(sqrt((AI_gear_x - AI_x) * (AI_gear_x - AI_x) + (AI_gear_y - AI_y) * (AI_gear_y - AI_y)) < 1.2 * AI_r) 
		ege_drawtext("60", AI_gear_x, AI_gear_y);
	AI_gear_x = (0.55 * AI_r) * cos(rollAngle) - (1.22 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * sin(rollAngle) + AI_x;
	AI_gear_y = (0.55 * AI_r) * sin(rollAngle) + (1.22 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * cos(rollAngle) + AI_y;
	if(sqrt((AI_gear_x - AI_x) * (AI_gear_x - AI_x) + (AI_gear_y - AI_y) * (AI_gear_y - AI_y)) < 1.2 * AI_r) 
		ege_drawtext("60", AI_gear_x, AI_gear_y);
	
	//-80刻度
	AI_gear_x = (- 0.55 * AI_r) * cos(rollAngle) - (1.62 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * sin(rollAngle) + AI_x;
	AI_gear_y = (- 0.55 * AI_r) * sin(rollAngle) + (1.62 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * cos(rollAngle) + AI_y;
	if(sqrt((AI_gear_x - AI_x) * (AI_gear_x - AI_x) + (AI_gear_y - AI_y) * (AI_gear_y - AI_y)) < 1.2 * AI_r) 
		ege_drawtext("80", AI_gear_x, AI_gear_y);
	AI_gear_x = (0.55 * AI_r) * cos(rollAngle) - (1.62 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * sin(rollAngle) + AI_x;
	AI_gear_y = (0.55 * AI_r) * sin(rollAngle) + (1.62 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r)) * cos(rollAngle) + AI_y;
	if(sqrt((AI_gear_x - AI_x) * (AI_gear_x - AI_x) + (AI_gear_y - AI_y) * (AI_gear_y - AI_y)) < 1.2 * AI_r) 
		ege_drawtext("80", AI_gear_x, AI_gear_y);
	
	
	
	//+30度
	AI_line_lx = (AI_x - 0.60 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 0.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y - 0.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.60 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.60 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 0.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y - 0.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.60 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);
	
	//+40度
	AI_line_lx = (AI_x - 0.46 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 0.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y - 0.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.46 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.46 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 0.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y - 0.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.46 * AI_r - AI_x) * sin(rollAngle) + AI_y;
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
	AI_line_lx = (AI_x - 0.46 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 1.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y - 1.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.46 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.46 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 1.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y - 1.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.46 * AI_r - AI_x) * sin(rollAngle) + AI_y;
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
	AI_line_lx = (AI_x - 0.46 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 1.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y - 1.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.46 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.46 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 1.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y - 1.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.46 * AI_r - AI_x) * sin(rollAngle) + AI_y;
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
	AI_line_lx = (AI_x - 0.46 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 0.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y + 0.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.46 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.46 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 0.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y + 0.4 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.46 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);
	
	//-30度
	AI_line_lx = (AI_x - 0.60 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 0.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y + 0.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.60 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.60 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 0.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y + 0.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.60 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);
	
	//-40度
	AI_line_lx = (AI_x - 0.46 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 0.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y + 0.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.46 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.46 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 0.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y + 0.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.46 * AI_r - AI_x) * sin(rollAngle) + AI_y;
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
	AI_line_lx = (AI_x - 0.46 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 1.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y + 1.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.46 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.46 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 1.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y + 1.2 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.46 * AI_r - AI_x) * sin(rollAngle) + AI_y;
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
	AI_line_lx = (AI_x - 0.46 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 1.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y + 1.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.46 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.46 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 1.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y + 1.6 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.46 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);
	
	//-90度 
	AI_line_lx = (AI_x - 0.3 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 1.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ly = (AI_y + 1.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x - 0.3 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	AI_line_rx = (AI_x + 0.3 * AI_r - AI_x) * cos(rollAngle) - (AI_y + 1.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * sin(rollAngle) + AI_x;
	AI_line_ry = (AI_y + 1.8 * AI_r + (360 * pitchAngle / 2 / PI * 0.02 * AI_r) - AI_y) * cos(rollAngle) + (AI_x + 0.3 * AI_r - AI_x) * sin(rollAngle) + AI_y;
	if(sqrt((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly)) < 1.4 * AI_r)
		ege_line(AI_line_lx,AI_line_ly,AI_line_rx,AI_line_ry);
	
	
	//背景的立体效果（周围渐渐变黑）(也用了旋转坐标系)
	
	ege_transform_matrix m;
	ege_get_transform(&m);
	ege_transform_translate(AI_x,AI_y);
	ege_transform_rotate(360 * rollAngle / 2 / PI);
	
	ege_setpattern_lineargradient(-1.3 * AI_r, 0, EGEARGB(0xff,0x00,0x00,0x00), - 0.5 * AI_r, 0, EGEARGB(0x00,0x00,0x00,0x00));
	ege_fillrect(-1.2 * AI_r, -0.8 * AI_r, 0.69 * AI_r, 1.63 * AI_r);
	
	ege_setpattern_lineargradient(1.3 * AI_r, 0, EGEARGB(0xff,0x00,0x00,0x00), 0.5 * AI_r, 0, EGEARGB(0x00,0x00,0x00,0x00));
	ege_fillrect(0.51 * AI_r, -0.8 * AI_r, 0.69 * AI_r, 1.63 * AI_r);
	
	ege_set_transform(&m);
	ege_setpattern_none();
	
	
	//绘制指示背景上下的遮盖
	
	//上面的 
	setfillcolor(EGEARGB(0xff,0x5c,0x8a,0x86));
	ege_point AI_points8[3] = {{(AI_x - 0.95 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 0.65 * AI_r - AI_y) * sin(rollAngle) + AI_x,
		(AI_y - 0.65 * AI_r - AI_y) * cos(rollAngle) + (AI_x - 0.95 * AI_r - AI_x) * sin(rollAngle) + AI_y},
		{AI_x + 1.1 * AI_r * sin(rollAngle),AI_y - 1.1 * AI_r + 1.1 * AI_r * (1 - cos(rollAngle))},
		{(AI_x + 0.95 * AI_r - AI_x) * cos(rollAngle) - (AI_y - 0.65 * AI_r - AI_y) * sin(rollAngle) + AI_x,
			(AI_y - 0.65 * AI_r - AI_y) * cos(rollAngle) + (AI_x + 0.95 * AI_r - AI_x) * sin(rollAngle) + AI_y}};
	ege_fillpoly(3,AI_points8);
	
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
	
	ege_point AI_points9[3] = {
		{AI_Triangle_1x,AI_Triangle_1y},
		{AI_Triangle_2x,AI_Triangle_2y},
		{AI_Triangle_3x,AI_Triangle_3y}
	};
	ege_fillpoly(3,AI_points9);
	
	
	
	//下面的 
	setfillcolor(BLACK);
	ege_fillpie(AI_x - 0.7 * AI_r,AI_y + 0.4 * AI_r,1.4 * AI_r,0.6 * AI_r,0,180);
	
	//航向偏离指示
	setcolor(WHITE);
	setlinewidth(0.02 * AI_r);
	ege_line(AI_x, AI_y + 0.71 * AI_r, AI_x, AI_y + 0.88 * AI_r);
	setfillcolor(WHITE);
	ege_fillellipse(AI_x - 0.35 * AI_r, AI_y + 0.74 * AI_r, 0.07 * AI_r, 0.07 * AI_r);
	ege_fillellipse(AI_x + (0.35 - 0.035 * 2) * AI_r, AI_y + 0.74 * AI_r, 0.07 * AI_r, 0.07 * AI_r);
	
	//绘制指示箭头
	ege_point ege_points26[3]{
		{AI_x + headingIndication * 0.315 * AI_r, AI_y + 0.80 * AI_r},
		{AI_x - 0.1 * AI_r + headingIndication * 0.315 * AI_r, AI_y + 1 * AI_r},
		{AI_x + 0.1 * AI_r + headingIndication * 0.315 * AI_r, AI_y + 1 * AI_r},
	};
	ege_fillpoly(3,ege_points26);
	
	
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
	//	ege_point AI_points1[3] = {{AI_x,AI_y},{AI_x + 0.5 * AI_r,AI_y + 0.15 * AI_r},
	//	{AI_x - 0.5 * AI_r,AI_y + 0.15 * AI_r}};	
	//	ege_fillpoly(3,AI_points1);
	//	
	//	setfillcolor(EGEARGB(0xaf,0xc1,0x9d,0x7b));
	//	ege_point AI_points2[4] = {{AI_x,AI_y},{AI_x + 0.5 * AI_r,AI_y + 0.15 * AI_r},
	//	{AI_x,AI_y + 0.05 * AI_r},
	//	{AI_x - 0.5 * AI_r,AI_y + 0.15 * AI_r}};	
	//	ege_fillpoly(4,AI_points2);
	
	//AI_x-Plane上的版本 
	
	//机身下的线
		//红色正常版	
	setcolor(EGEARGB(0xff,0x66,0x29,0x14));//红色 
	setlinewidth(0.02*AI_r);
	ege_line(AI_x - 0.19 * AI_r,AI_y + 0.08 * AI_r,AI_x - 0.19 * AI_r,AI_y + 0.12 * AI_r);
	ege_line(AI_x + 0.19 * AI_r,AI_y + 0.08 * AI_r,AI_x + 0.19 * AI_r,AI_y + 0.12 * AI_r);	
		//黄色作为光照效果遮盖
	setcolor(EGEARGB(G_light,0xa4,0x8f,0x2a));//黄色
	setlinewidth(0.02*AI_r);
	ege_line(AI_x - 0.19 * AI_r,AI_y + 0.08 * AI_r,AI_x - 0.19 * AI_r,AI_y + 0.12 * AI_r);
	ege_line(AI_x + 0.19 * AI_r,AI_y + 0.08 * AI_r,AI_x + 0.19 * AI_r,AI_y + 0.12 * AI_r);
	
	//两侧的线
	
		//红色正常版
	setcolor(EGEARGB(0xff,0x66,0x29,0x14));//红色 
	setlinewidth(0.008*AI_r);
	ege_line(AI_x - 0.308 * AI_r,AI_y,AI_x - AI_r,AI_y);
	ege_line(AI_x + 0.308 * AI_r,AI_y,AI_x + AI_r,AI_y);
		//黄色作为光照效果遮盖
	setcolor(EGEARGB(G_light,0xed,0xd3,0x14));//黄色
	setlinewidth(0.008*AI_r);
	ege_line(AI_x - 0.308 * AI_r,AI_y,AI_x - AI_r,AI_y);
	ege_line(AI_x + 0.308 * AI_r,AI_y,AI_x + AI_r,AI_y);
	
	//连接处
		
		//红色正常版
	setfillcolor(EGEARGB(0xff,0xad,0x25,0x2c));//红色
	ege_point AI_points2[3] = {{AI_x - 0.15 * AI_r,AI_y + 0.04 * AI_r},
		{AI_x - 0.23 * AI_r,AI_y + 0.07 * AI_r},
		{AI_x - 0.316 * AI_r,AI_y - 0.008 * AI_r}};	
	ege_fillpoly(3,AI_points2);
	ege_point AI_points3[3] = {{AI_x + 0.15 * AI_r,AI_y + 0.04 * AI_r},
		{AI_x + 0.23 * AI_r,AI_y + 0.07 * AI_r},
		{AI_x + 0.316 * AI_r,AI_y - 0.008 * AI_r}};	
	ege_fillpoly(3,AI_points3);
		//黄色作为光照效果遮盖
	setfillcolor(EGEARGB(G_light,0xed,0xd3,0x14));//黄色
	ege_fillpoly(3,AI_points2);
	ege_fillpoly(3,AI_points3);
	
	
	//连接处阴影
	ege_setpattern_lineargradient(AI_x - 0.22 * AI_r,AI_y + 0.16 * AI_r, EGEARGB(0xff,0x00,0x00,0x00) , AI_x - 0.316 * AI_r,AI_y - 0.012 * AI_r, EGEARGB(0x00,0x00,0x00,0x00)); 
	ege_fillpoly(3,AI_points2);
	ege_setpattern_lineargradient(AI_x + 0.22 * AI_r,AI_y + 0.16 * AI_r, EGEARGB(0xff,0x00,0x00,0x00) , AI_x + 0.316 * AI_r,AI_y - 0.012 * AI_r, EGEARGB(0x00,0x00,0x00,0x00));
	ege_fillpoly(3,AI_points3);
	ege_setpattern_none();
	
	//机身
		//红色正常版
	setfillcolor(EGEARGB(0xff,0xad,0x25,0x2c));//红色 
	ege_point AI_points1[3] = {
		{AI_x,AI_y - 0.02 * AI_r},
		{AI_x + 0.33 * AI_r,AI_y + 0.09 * AI_r},
		{AI_x - 0.33 * AI_r,AI_y + 0.09 * AI_r}
	};	
	ege_fillpoly(3,AI_points1);
		//黄色作为光照效果遮盖
	setfillcolor(EGEARGB(G_light,0xed,0xd3,0x14));//黄色
	ege_fillpoly(3,AI_points1);
	
	
	
//	//绘制边框（负责遮盖的圆）（初版，无法渐变）
//	
//	setcolor(Frame_color2);
//	setlinewidth(0.5*AI_r);
//	ege_ellipse(AI_x-1.25*AI_r,AI_y-1.25*AI_r,2.5*AI_r,2.5*AI_r);
	
	
	//绘制边框（负责遮盖的多边形） 
	
	//四周的矩形
	ege_setpattern_lineargradient(AI_x,AI_y-1.6*AI_r,Frame_color1,AI_x,AI_y+1.6*AI_r,Frame_color2);
	ege_fillrect(AI_x - 1.45 * AI_r, AI_y - 1.55 * AI_r, 0.4 * AI_r, 3.1 * AI_r);
	ege_fillrect(AI_x - 1.45 * AI_r, AI_y + 1.03 * AI_r, 2.9 * AI_r, 0.5 * AI_r);
	ege_fillrect(AI_x + 1.05 * AI_r, AI_y - 1.55 * AI_r, 0.4 * AI_r, 3.1 * AI_r);
	ege_fillrect(AI_x - 1.45 * AI_r, AI_y - 1.55 * AI_r, 2.9 * AI_r, 0.5 * AI_r);
	
	//四周的三角形
	ege_point AI_points4[3]{
		{AI_x, AI_y - 1.05 * AI_r},
		{AI_x + 1.3 * AI_r, AI_y - 0.7 * AI_r},
		{AI_x + 1.3 * AI_r, AI_y - 1.05 * AI_r}
	};
	ege_point AI_points5[3]{
		{AI_x, AI_y + 1.05 * AI_r},
		{AI_x + 1.3 * AI_r, AI_y + 0.7 * AI_r},
		{AI_x + 1.3 * AI_r, AI_y + 1.05 * AI_r}
	};
	ege_point AI_points6[3]{
		{AI_x, AI_y - 1.05 * AI_r},
		{AI_x - 1.3 * AI_r, AI_y - 0.7 * AI_r},
		{AI_x - 1.3 * AI_r, AI_y - 1.05 * AI_r}
	};
	ege_point AI_points7[3]{
		{AI_x, AI_y + 1.05 * AI_r},
		{AI_x - 1.3 * AI_r, AI_y + 0.7 * AI_r},
		{AI_x - 1.3 * AI_r, AI_y + 1.05 * AI_r}
	};
	ege_fillpoly(3,AI_points4);
	ege_fillpoly(3,AI_points5);
	ege_fillpoly(3,AI_points6);
	ege_fillpoly(3,AI_points7);
	ege_setpattern_none();
	
	
	//绘制背景周围黑边
	
	ege_enable_aa(false);
	
	setcolor(EGEARGB(0xff,0x12,0x12,0x11)); 
	setlinewidth(0.35*AI_r);
	ege_arc(AI_x - 1.2 * AI_r,AI_y - 1.2 * AI_r,2.4 * AI_r,2.4 * AI_r,-20,-140);
	setlinewidth(0.05*AI_r);
	ege_arc(AI_x - 1.05 * AI_r,AI_y - 1.05 * AI_r,2.1 * AI_r,2.1 * AI_r,-20,220);
	ege_arc(AI_x - 1.326 * AI_r,AI_y -0.4 * AI_r,2.652 * AI_r,1.45 * AI_r,9,162);
	
	setfillcolor(EGEARGB(0xff,0x12,0x12,0x11)); 
	ege_fillrect(AI_x - 1.316 * AI_r,AI_y - 0.48 * AI_r,
		0.3 * AI_r,1.04 * AI_r);
	ege_fillrect(AI_x + 1.016 * AI_r,AI_y - 0.48 * AI_r,
		0.3 * AI_r,1.04 * AI_r);
	
	floodfill(AI_x - 1 * AI_r,AI_y + 0.55 * AI_r,EGEARGB(0xff,0x12,0x12,0x11));
	floodfill(AI_x + 1 * AI_r,AI_y + 0.55 * AI_r,EGEARGB(0xff,0x12,0x12,0x11));
	
	ege_enable_aa(true);
	
	setcolor(EGEARGB(0xff,0x12,0x12,0x11)); 
	setlinewidth(0.4*AI_r);
	ege_arc(AI_x - 1.2 * AI_r,AI_y - 1.2 * AI_r,2.4 * AI_r,2.4 * AI_r,-20,-140);
	setlinewidth(0.1*AI_r);
	ege_arc(AI_x - 1.05 * AI_r,AI_y - 1.05 * AI_r,2.1 * AI_r,2.1 * AI_r,-20,220);
	ege_arc(AI_x - 1.326 * AI_r,AI_y -0.4 * AI_r,2.652 * AI_r,1.45 * AI_r,9,162);
	
	
}


void draw_attitude_indicator_index_mark(double AI_x, double AI_y, double AI_r){
	
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
	
	//指示的箭头
	setfillcolor(WHITE);
	ege_point ege_points25[3]{
		{AI_x - 1.30 * AI_r , AI_y - 0.04 * AI_r - glideIndication * 0.188 * AI_r},
		{AI_x - 1.30 * AI_r , AI_y + 0.16 * AI_r - glideIndication * 0.188 * AI_r},
		{AI_x - 1.08 * AI_r , AI_y + 0.06 * AI_r - glideIndication * 0.188 * AI_r},
	};
	ege_fillpoly(3,ege_points25);
	
	
	//特殊箭头 
	
	setfillcolor(WHITE);
	ege_point AI_points10[3] = {{AI_x ,AI_y - 1.01 * AI_r},
		{AI_x - 0.06 * AI_r,AI_y -1.25  * AI_r},
		{AI_x + 0.06 * AI_r,AI_y - 1.25 * AI_r}
	};
	ege_fillpoly(3,AI_points10);
	
	setfillcolor(WHITE);
	ege_point AI_points11[3] = {
		{-(AI_y - 1.01 * AI_r - AI_y) * 0.707106 + AI_x, (AI_y - 1.01 * AI_r - AI_y) * 0.707106 + AI_y},
		{(AI_x - 0.06 * AI_r - AI_x) * 0.707106 - (AI_y - 1.25  * AI_r - AI_y) * 0.707106 + AI_x, (AI_y - 1.25  * AI_r - AI_y) * 0.707106 + (AI_x - 0.06 * AI_r - AI_x) * 0.707106 + AI_y},
		{(AI_x + 0.06 * AI_r - AI_x) * 0.707106 - (AI_y - 1.25  * AI_r - AI_y) * 0.707106 + AI_x, (AI_y - 1.25  * AI_r - AI_y) * 0.707106 + (AI_x + 0.06 * AI_r - AI_x) * 0.707106 + AI_y}
	};
	ege_fillpoly(3,AI_points11);
	
	setfillcolor(WHITE);
	ege_point AI_points7[3] = {
		{-(AI_y - 1.01 * AI_r - AI_y) * -0.707106 + AI_x, (AI_y - 1.01 * AI_r - AI_y) * 0.707106 + AI_y},
		{(AI_x - 0.06 * AI_r - AI_x) * 0.707106 - (AI_y - 1.25  * AI_r - AI_y) * -0.707106 + AI_x, (AI_y - 1.25  * AI_r - AI_y) * 0.707106 + (AI_x - 0.06 * AI_r - AI_x) * -0.707106 + AI_y},
		{(AI_x + 0.06 * AI_r - AI_x) * 0.707106 - (AI_y - 1.25  * AI_r - AI_y) * -0.707106 + AI_x, (AI_y - 1.25  * AI_r - AI_y) * 0.707106 + (AI_x + 0.06 * AI_r - AI_x) * -0.707106 + AI_y}
	};
	ege_fillpoly(3,AI_points7);
	
	
}


void draw_slip_indicator(double AI_x, double AI_y, double AI_r){
	
	//绘制侧滑指示的底盘
	
		// 上边缘
	ege_point AI_points13[4] = {
		{AI_x + 0.37 * AI_r, AI_y + 1.16 * AI_r},
		{AI_x + 0.20 * AI_r, AI_y + 1.20  * AI_r},
		{AI_x - 0.20 * AI_r, AI_y + 1.20  * AI_r},
		{AI_x - 0.37 * AI_r, AI_y + 1.16 * AI_r},
	};	
		//下边缘
	ege_point AI_points14[4] = {
		{AI_x + 0.37 * AI_r, AI_y + 1.44 * AI_r},
		{AI_x + 0.20 * AI_r, AI_y + 1.50 * AI_r},
		{AI_x - 0.20 * AI_r, AI_y + 1.50 * AI_r},
		{AI_x - 0.37 * AI_r, AI_y + 1.44 * AI_r},
	};
		//右边缘
	ege_point AI_points15[4] = {
		{AI_x + 0.365 * AI_r, AI_y + 1.15 * AI_r},
		{AI_x + 0.37 * AI_r, AI_y + 1.22 * AI_r},
		{AI_x + 0.37 * AI_r, AI_y + 1.38 * AI_r},
		{AI_x + 0.365 * AI_r, AI_y + 1.443 * AI_r},
	};
		//左边缘
	ege_point AI_points16[4] = {
		{AI_x - 0.365 * AI_r, AI_y + 1.15 * AI_r},
		{AI_x - 0.37 * AI_r, AI_y + 1.22 * AI_r},
		{AI_x - 0.37 * AI_r, AI_y + 1.38 * AI_r},
		{AI_x - 0.365 * AI_r, AI_y + 1.443 * AI_r},
	};
		//上下分界
	ege_point AI_points17[4] = {
		{AI_x + 0.37 * AI_r, AI_y + 1.29 * AI_r},
		{AI_x + 0.20 * AI_r, AI_y + 1.33  * AI_r},
		{AI_x - 0.20 * AI_r, AI_y + 1.33  * AI_r},
		{AI_x - 0.37 * AI_r, AI_y + 1.29 * AI_r},
	};
	
	
		//填充下半部分(黄)	用多边形近似覆盖
	
	ege_point AI_points26[8] = {
		{AI_x - 0.37 * AI_r, AI_y + 1.25 * AI_r},
		{AI_x - 0.37 * AI_r, AI_y + 1.44 * AI_r},
		{AI_x - 0.20 * AI_r, AI_y + 1.475 * AI_r},
		{AI_x - 0.10 * AI_r, AI_y + 1.485 * AI_r},
		{AI_x + 0.10 * AI_r, AI_y + 1.485 * AI_r},
		{AI_x + 0.20 * AI_r, AI_y + 1.475 * AI_r},
		{AI_x + 0.37 * AI_r, AI_y + 1.44 * AI_r},
		{AI_x + 0.37 * AI_r, AI_y + 1.25 * AI_r},
	};
	setfillcolor(EGEARGB(0xff,0xb5,0xac,0x46));
	ege_fillpoly(8,AI_points26);
	
		//随光照变化
	setfillcolor(EGEARGB(G_light,0x8b,0x9c,0x52));
	ege_fillpoly(8,AI_points26);
	
		//填充上半部分(黑)	同样用多边形近似覆盖
	ege_point AI_points27[13] = {
		{AI_x - 0.10 * AI_r, AI_y + 1.19 * AI_r},
		{AI_x - 0.20 * AI_r, AI_y + 1.18 * AI_r},
		{AI_x - 0.37 * AI_r, AI_y + 1.16 * AI_r},
		{AI_x - 0.37 * AI_r, AI_y + 1.16 * AI_r},
		{AI_x - 0.37 * AI_r, AI_y + 1.29 * AI_r},
		{AI_x - 0.20 * AI_r, AI_y + 1.31 * AI_r},
		{AI_x - 0.10 * AI_r, AI_y + 1.32 * AI_r},
		{AI_x + 0.10 * AI_r, AI_y + 1.32 * AI_r},
		{AI_x + 0.20 * AI_r, AI_y + 1.31 * AI_r},
		{AI_x + 0.37 * AI_r, AI_y + 1.29 * AI_r},
		{AI_x + 0.37 * AI_r, AI_y + 1.16 * AI_r},
		{AI_x + 0.20 * AI_r, AI_y + 1.18 * AI_r},
		{AI_x + 0.10 * AI_r, AI_y + 1.19 * AI_r},
	};
	setfillcolor(BLACK);
	ege_fillpoly(13,AI_points27);
	
	
		//绘制指示器边界
	setlinewidth(0.021 * AI_r);
	setcolor(BLACK);
	ege_bezier(4,AI_points13);
	setcolor(Frame_color2);
	ege_bezier(4,AI_points14);
	ege_bezier(4,AI_points15);
	ege_bezier(4,AI_points16);
	
	//分界白线
	ege_point AI_points18[4] = {
		{AI_x + 0.355 * AI_r, AI_y + 1.285 * AI_r},
		{AI_x + 0.185 * AI_r, AI_y + 1.325 * AI_r},
		{AI_x - 0.185 * AI_r, AI_y + 1.325 * AI_r},
		{AI_x - 0.355 * AI_r, AI_y + 1.285 * AI_r},
	};
	setcolor(WHITE);
	setlinewidth(0.015 * AI_r);
	ege_bezier(4,AI_points18);
	
	
	
	//绘制指示圆球
	setfillcolor(EGEARGB(0xff,0xff,0xe5,0x9e));
		//此处暂时当作左右各45度各0.29*AI_r
	ege_point AI_points21{AI_x  + 0.90 * (sideSlipAngle / PI * 360) / 45 * 0.29 * AI_r, AI_y + 1.385 * AI_r - 0.15 * fabs(sideSlipAngle / PI * 360) / 45 * 0.29 * AI_r};
	ege_setpattern_ellipsegradient(AI_points21, EGEARGB(0xff,0xff,0xe5,0x9e) , AI_x - 0.08 * AI_r + (sideSlipAngle / PI * 360) / 45 * 0.29 * AI_r, AI_y + 1.32 * AI_r - fabs(0.11 * (sideSlipAngle / PI * 360) / 45 * 0.29 * AI_r) , 0.17 * AI_r, 0.17 * AI_r, BLACK);
	ege_fillellipse(AI_x - 0.065 * AI_r + (sideSlipAngle / PI * 360) / 45 * 0.29 * AI_r, AI_y + 1.34 * AI_r - 0.08 * fabs(sideSlipAngle / PI * 360) / 45 * 0.29 * AI_r, 0.13 * AI_r, 0.13 * AI_r);
		
		//随光照变化
	ege_setpattern_ellipsegradient(AI_points21, EGEARGB((int)(1.0 * G_light / 1.5),0xa6,0x60,0x44) , AI_x - 0.08 * AI_r + (sideSlipAngle / PI * 360) / 45 * 0.29 * AI_r, AI_y + 1.32 * AI_r - fabs(0.11 * (sideSlipAngle / PI * 360) / 45 * 0.29 * AI_r) , 0.17 * AI_r, 0.17 * AI_r, EGEARGB((int)(1.0 * G_light / 1.5),0x00,0x00,0x00));
	ege_fillellipse(AI_x - 0.065 * AI_r + (sideSlipAngle / PI * 360) / 45 * 0.29 * AI_r, AI_y + 1.34 * AI_r - 0.08 * fabs(sideSlipAngle / PI * 360) / 45 * 0.29 * AI_r, 0.13 * AI_r, 0.13 * AI_r);
	ege_setpattern_none();
	
	
	//指示中心的两条线
	ege_point AI_points19[4] = {
		{AI_x - 0.075 * AI_r, AI_y + 1.3 * AI_r},
		{AI_x - 0.08 * AI_r, AI_y + 1.3 * AI_r},
		{AI_x - 0.08 * AI_r, AI_y + 1.48 * AI_r},
		{AI_x - 0.075 * AI_r, AI_y + 1.48 * AI_r},
	};
	ege_point AI_points20[4] = {
		{AI_x + 0.075 * AI_r, AI_y + 1.3 * AI_r},
		{AI_x + 0.08 * AI_r, AI_y + 1.3 * AI_r},
		{AI_x + 0.08 * AI_r, AI_y + 1.48 * AI_r},
		{AI_x + 0.075 * AI_r, AI_y + 1.48 * AI_r},
	};
	setcolor(BLACK);
	ege_bezier(4,AI_points19);
	ege_bezier(4,AI_points20);
	
	
	//整个指示仪的阴影
	ege_point AI_points22{AI_x, AI_y + 1 * AI_r};
	ege_setpattern_ellipsegradient(AI_points21, EGEARGB(0x00,0x00,0x00,0x0) , AI_x - 0.8 * AI_r, AI_y + 0.2 * AI_r ,1.6 * AI_r, 1.6 * AI_r, EGEARGB(0xff,0x00,0x00,0x00));
	ege_point AI_points23[8] = {
		{AI_x - 0.37 * AI_r, AI_y + 1.25 * AI_r},
		{AI_x - 0.37 * AI_r, AI_y + 1.44 * AI_r},
		{AI_x - 0.20 * AI_r, AI_y + 1.48 * AI_r},
		{AI_x - 0.10 * AI_r, AI_y + 1.49 * AI_r},
		{AI_x + 0.10 * AI_r, AI_y + 1.49 * AI_r},
		{AI_x + 0.20 * AI_r, AI_y + 1.48 * AI_r},
		{AI_x + 0.37 * AI_r, AI_y + 1.44 * AI_r},
		{AI_x + 0.37 * AI_r, AI_y + 1.25 * AI_r},
	};
	ege_fillpoly(8,AI_points23);
//	ege_fillrect( AI_x - 0.38 * AI_r, AI_y + 1.25 * AI_r ,0.76 * AI_r, 0.23 * AI_r);
	
	
}


void darw_AI_light(double AI_x, double AI_y, double AI_r){
	
	//光照效果
	
	ege_point point_tmp = {AI_x, AI_y};
	ege_setpattern_ellipsegradient(point_tmp, EGEARGB(0x00,0x00,0x00,0x00), AI_x - 1.4 * AI_r, AI_y - 1.4 * AI_r, 2.8 * AI_r, 2.8 * AI_r, EGEARGB(G_light / 5,0xff,0x87,0x10));
	ege_fillpie(AI_x - 1.25 * AI_r, AI_y - 1.4 * AI_r, 2.5 * AI_r, 2 * AI_r, -150, 120);
	ege_fillpie(AI_x - 1.25 * AI_r, AI_y - 0.9 * AI_r, 2.5 * AI_r, 2 * AI_r, 60, 60);
	ege_setpattern_ellipsegradient(point_tmp, EGEARGB(0x00,0x00,0x00,0x00), AI_x - 1.4 * AI_r, AI_y - 1.4 * AI_r, 2.8 * AI_r, 2.8 * AI_r, EGEARGB(G_light / 7,0xff,0x87,0x10));
	ege_fillpie(AI_x - 1.25 * AI_r, AI_y - 1.4 * AI_r, 2.5 * AI_r, 2 * AI_r, -180, 180);
	ege_fillpie(AI_x - 1.25 * AI_r, AI_y - 0.9 * AI_r, 2.5 * AI_r, 2 * AI_r, 30, 120);
	
//	ege_setpattern_lineargradient(AI_x, AI_y, EGEARGB(G_light / 5,0xff,0x87,0x10), AI_x - 1.2 * AI_r, AI_y, EGEARGB(0x00,0x00,0x00,0x00));
//	ege_fillrect(AI_x - 0.8 * AI_r, AI_y - 1.1 * AI_r, 0.8 * AI_r, 2 * AI_r);
//	
////	ege_setpattern_lineargradient(AI_x, AI_y, EGEARGB(G_light / 5,0xff,0x87,0x10), AI_x + 1.2 * AI_r, AI_y, EGEARGB(0x00,0x00,0x00,0x00));
//	ege_fillrect(AI_x , AI_y - 1.1 * AI_r, 0.8 * AI_r, 2 * AI_r);
//	ege_setpattern_none();
	
	ege_setpattern_ellipsegradient(point_tmp, EGEARGB(0x00,0x00,0x00,0x00), AI_x - AI_r, AI_y - AI_r, 2 * AI_r, 2 * AI_r, EGEARGB(G_light / 6,0xd9,0x6c,0x21)); // EGEARGB(G_light / 4,0xb5,0x5e,0x51)
	ege_fillellipse(AI_x - AI_r, AI_y - AI_r, 2 * AI_r, 2 * AI_r);	
	ege_setpattern_none();
	
}


void draw_botton_and_screw(double AI_x, double AI_y, double AI_r){
	
	//周围螺丝
	draw_screw(AI_x - 1.36 * AI_r , AI_y + 1.46 * AI_r, 0.09 * AI_r , 50);
	draw_screw(AI_x + 1.36 * AI_r , AI_y + 1.46 * AI_r, 0.09 * AI_r , 40);
	draw_screw(AI_x + 1.36 * AI_r , AI_y - 1.46 * AI_r, 0.09 * AI_r , 80);
	draw_screw(AI_x - 1.36 * AI_r , AI_y - 1.46 * AI_r, 0.09 * AI_r , 15);
	
	
	
	//按钮底座
	ege_setpattern_lineargradient(AI_x - 1.50 * AI_r ,AI_y + 0.9 * AI_r, EGEARGB(0xff,0x18,0x19,0x20),AI_x - 0.7 * AI_r ,AI_y + 1.5 * AI_r, BLACK);
	ege_fillellipse(AI_x - 1.42 * AI_r ,AI_y + 0.9 * AI_r , 0.47 * AI_r, 0.45 * AI_r);
	ege_setpattern_none();
	
	
	//绘制按钮顶部
	setfillcolor(BLACK);
	ege_fillellipse(AI_x - 1.40 * AI_r ,AI_y + 1.10 * AI_r , 0.3 * AI_r, 0.3 * AI_r);
	ege_setpattern_lineargradient(AI_x - 1.40 * AI_r ,AI_y + 1.40 * AI_r, BLACK,AI_x - 0.8 * AI_r ,AI_y + 0.8 * AI_r, EGEARGB(0xff,0x2e,0x26,0x1e));
	for(double i = 0;i - (0.04 * AI_r) <= 0.001 ;i += 0.001 * AI_r){
		ege_fillellipse(AI_x - 1.40 * AI_r + i ,AI_y + 1.10 * AI_r - 1.5 * i, 0.31 * AI_r, 0.31 * AI_r);
	}
	ege_setpattern_lineargradient(AI_x - 1.40 * AI_r ,AI_y + 1.40 * AI_r, BLACK,AI_x - 1 * AI_r ,AI_y + 1 * AI_r, EGEARGB(0xff,0x66,0x58,0x45));
	ege_fillellipse(AI_x - 1.41 * AI_r ,AI_y + 1.09 * AI_r , 0.325 * AI_r, 0.325 * AI_r);
	ege_setpattern_none();
	setfillcolor(BLACK);
	ege_fillellipse(AI_x - 1.40 * AI_r ,AI_y + 1.10 * AI_r , 0.31 * AI_r, 0.31 * AI_r);
	
	
}




