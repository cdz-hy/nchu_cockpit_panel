#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>


//函数声明

void draw_PFD_standby_AI(double PFD_x, double PFD_y, double PFD_side);
void draw_PFD_standby_Compass(double center_x, double center_y, double side);
void draw_standy_alt(double center_x, double center_y, double side);
void draw_standy_airSpeed(double center_x, double center_y, double side);
//void draw_PFD_standby_else();
void draw_smallpfd_frame(double center_x, double center_y, double side);
void draw_PFD_standby_Compass(double center_x, double center_y, double side);
void drwa_ND_atmosphericPressure(double center_x,double center_y,double side);

//引用全局变量
extern double pitchAngle;
extern double rollAngle;
extern double sideSlipAngle;
extern double headingIndication;
extern double glideIndication;
extern double altitude;
extern double rotationangle;
extern double airSpeed;
extern double INGH_data;

//935 655 575

//注意，这里的side并不是真正的边长，而只是PFD的高，PFD并非严格正方形
void draw_PFD_standby(double PFD_x, double PFD_y, double PFD_side){
	
	//绘制备用PFD姿态仪
	draw_PFD_standby_AI(PFD_x+PFD_side/30, PFD_y+PFD_side/30, PFD_side*1.1);
//	
//	//绘制备用PFD罗盘
	draw_PFD_standby_Compass(PFD_x+PFD_side/40, PFD_y + 2.22 * PFD_side, PFD_side * 3.4);
	
	//绘制备用PFD高度
	draw_standy_alt(PFD_x + 0.94 * PFD_side, PFD_y + 0.02 * PFD_side, PFD_side / 1.7);
	
	//绘制备用PFD空速
	draw_standy_airSpeed(PFD_x - 0.8 * PFD_side, PFD_y + 0.02 * PFD_side, PFD_side / 1.65);
	
	//灯光遮盖效果
	setfillcolor(EGEARGB(0x23, 0x00, 0x00, 0x00));
	ege_fillrect(PFD_x - PFD_side * 1.2, PFD_y - PFD_side * 1.1,2.4 * PFD_side ,2.3 * PFD_side);
	
	//绘制PFD边框
	draw_smallpfd_frame(PFD_x + PFD_side/20, PFD_y +PFD_side/20, PFD_side*2.3);
	
	//绘制pfd右上角的气压指示
	drwa_ND_atmosphericPressure(PFD_x,PFD_y,PFD_side);
	
}





//========================================以下为姿态仪=================================================//


//side 935; high 655; wid 575;
//10度160; 1度16;
//1度16/655（即0.02442745 * AIhigh（高））（也即0.0488549 * AIside（一半高）（但是稍大，所以下面都按0.48处理））

void draw_PFD_standby_AI(double PFD_x, double PFD_y, double PFD_side){
	
	double AI_x = PFD_x;
	double AI_y = PFD_y;
	double AI_side = PFD_side * 935 / 655 / 2;//即一半的边长
	
	//需要被遮盖的背景圆的半径
	double AI_r = sqrt(2) * AI_side;
	
	//通过坐标系变换和遮盖实现圆角矩形的指示
	if(pitchAngle >= 0){
		
		//画天空
		setfillcolor(EGEARGB(0xff,0x03,0xb2,0xe3));
		ege_fillellipse(AI_x - AI_r,AI_y - AI_r,2 * AI_r,2 * AI_r);
		
		//画地面
		ege_transform_matrix m;
		ege_get_transform(&m);
		ege_transform_translate(AI_x,AI_y);
		ege_transform_rotate(360 * rollAngle / 2 / PI);
		setfillcolor(EGEARGB(0xff,0xa3,0x6e,0x3e));
		setcolor(WHITE);
		setlinewidth(0.012 * AI_r);
		if(2 * AI_side - 2 * (360 * pitchAngle / 2 / PI * 0.02 * AI_r) > 0){
			ege_fillpie(-AI_r + 0.38 * (360 * pitchAngle / 2 / PI * 0.048 * AI_side) ,-AI_r + 2 * (360 * pitchAngle / 2 / PI * 0.048 * AI_side),2 * AI_r - 0.76 * (360 * pitchAngle / 2 / PI * 0.048 * AI_side),2 * AI_r - 2 * (360 * pitchAngle / 2 / PI * 0.048 * AI_side),0,180);
			//天地中间的白线
			ege_pie(-AI_r + 0.38 * (360 * pitchAngle / 2 / PI * 0.048 * AI_side), -AI_r + 2 * (360 * pitchAngle / 2 / PI * 0.048 * AI_side),2 * AI_r - 0.76 * (360 * pitchAngle / 2 / PI * 0.048 * AI_side),2 * AI_r - 2 * (360 * pitchAngle / 2 / PI * 0.048 * AI_side),0,180);
		}
		ege_set_transform(&m);
		
	}
	else{
		
		//画地面
		setfillcolor(EGEARGB(0xff,0xa3,0x6e,0x3e));
		ege_fillellipse(AI_x - AI_r,AI_y - AI_r,2 * AI_r,2 * AI_r);
		
		//画天空
		ege_transform_matrix m;
		ege_get_transform(&m);
		ege_transform_translate(AI_x,AI_y);
		ege_transform_rotate(360 * rollAngle / 2 / PI);
		setfillcolor(EGEARGB(0xff,0x03,0xb2,0xe3));
		setcolor(WHITE);
		setlinewidth(0.012 * AI_r);
		if(2 * AI_side - 2 * (360 * pitchAngle / 2 / PI * 0.02 * AI_r) > 0){
			ege_fillpie(-AI_r - 0.38 * (360 * pitchAngle / 2 / PI * 0.048 * AI_side), -AI_r,2 * AI_r + 0.76 * (360 * pitchAngle / 2 / PI * 0.048 * AI_side),2 * AI_r + 2 * (360 * pitchAngle / 2 / PI * 0.048 * AI_side),-180,180);
			//天地中间的白线
			ege_pie(-AI_r - 0.38 * (360 * pitchAngle / 2 / PI * 0.048 * AI_side), -AI_r,2 * AI_r + 0.76 * (360 * pitchAngle / 2 / PI * 0.048 * AI_side),2 * AI_r + 2 * (360 * pitchAngle / 2 / PI * 0.048 * AI_side),-180,180);
		}
		ege_set_transform(&m);
		
	}
	
	
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
	setfont(0.20 * AI_side,0.08 * AI_side,"黑体");
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
//			AI_line_ly = AI_y - 0.048 * i * AI_side;
//			AI_line_rx = AI_x + 0.43 * AI_side;
//			AI_line_ry = AI_y - 0.048 * i * AI_side;
			
			AI_line_lx = (AI_x - (AI_x - 0.35 * AI_side)) * cos(rollAngle) - ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.048  * AI_side) - AI_y) * sin(rollAngle) + AI_x;
			AI_line_ly = ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.048  * AI_side) - AI_y) * cos(rollAngle) + (AI_x - (AI_x - 0.35 * AI_side)) * sin(rollAngle) + AI_y;
			AI_line_rx = (AI_x - (AI_x + 0.35 * AI_side)) * cos(rollAngle) - ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.048  * AI_side) - AI_y) * sin(rollAngle) + AI_x;
			AI_line_ry = ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.048  * AI_side) - AI_y) * cos(rollAngle) + (AI_x - (AI_x + 0.35 * AI_side)) * sin(rollAngle) + AI_y;
			
			if((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly) <= 1.5 * AI_side * 1.5 * AI_side)
				ege_line(AI_line_lx, AI_line_ly, AI_line_rx, AI_line_ry);
			
			
			//刻度示数
			AI_gear_x = (AI_x - (AI_x + 0.495 * AI_side)) * cos(rollAngle) - ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.048  * AI_side + 0.015 * AI_side) - AI_y) * sin(rollAngle) + AI_x;
			AI_gear_y = ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.048  * AI_side + 0.015 * AI_side) - AI_y) * cos(rollAngle) + (AI_x - (AI_x + 0.495 * AI_side)) * sin(rollAngle) + AI_y;
			if(sqrt((AI_gear_x - AI_x) * (AI_gear_x - AI_x) + (AI_gear_y - AI_y) * (AI_gear_y - AI_y)) <= 1.5 * AI_side){
				char tmp[3];
				sprintf(tmp,"%d",abs((int)i));
				ege_drawtext(tmp, AI_gear_x, AI_gear_y);
			}
			
			
		}
		else if(fabs(fmod(i,5)) <= 0.001){
//			AI_line_lx = AI_x - 0.21 * AI_side;
//			AI_line_ly = AI_y - 0.048 * i * AI_side;
//			AI_line_rx = AI_x + 0.21 * AI_side;
//			AI_line_ry = AI_y - 0.048 * i * AI_side;
			
			AI_line_lx = (AI_x - (AI_x - 0.21 * AI_side)) * cos(rollAngle) - ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.048  * AI_side) - AI_y) * sin(rollAngle) + AI_x;
			AI_line_ly = ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.048  * AI_side) - AI_y) * cos(rollAngle) + (AI_x - (AI_x - 0.21 * AI_side)) * sin(rollAngle) + AI_y;
			AI_line_rx = (AI_x - (AI_x + 0.21 * AI_side)) * cos(rollAngle) - ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.048  * AI_side) - AI_y) * sin(rollAngle) + AI_x;
			AI_line_ry = ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.048  * AI_side) - AI_y) * cos(rollAngle) + (AI_x - (AI_x + 0.21 * AI_side)) * sin(rollAngle) + AI_y;
			
			if((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly) <= 1.5 * AI_side * 1.5 * AI_side)
				ege_line(AI_line_lx, AI_line_ly, AI_line_rx, AI_line_ry);
		}
		else if(fabs(fmod(i,2.5)) <= 0.001){
//			AI_line_lx = AI_x - 0.12 * AI_side;
//			AI_line_ly = AI_y + (i - (360 * pitchAngle / 2 / PI)) * 0.048  * AI_side;
//			AI_line_rx = AI_x + 0.12 * AI_side;
//			AI_line_ry = AI_y + (i - (360 * pitchAngle / 2 / PI)) * 0.048  * AI_side;
			
			AI_line_lx = (AI_x - (AI_x - 0.12 * AI_side)) * cos(rollAngle) - ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.048  * AI_side) - AI_y) * sin(rollAngle) + AI_x;
			AI_line_ly = ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.048  * AI_side) - AI_y) * cos(rollAngle) + (AI_x - (AI_x - 0.12 * AI_side)) * sin(rollAngle) + AI_y;
			AI_line_rx = (AI_x - (AI_x + 0.12 * AI_side)) * cos(rollAngle) - ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.048  * AI_side) - AI_y) * sin(rollAngle) + AI_x;
			AI_line_ry = ((AI_y - (i - (360 * pitchAngle / 2 / PI)) * 0.048  * AI_side) - AI_y) * cos(rollAngle) + (AI_x - (AI_x + 0.12 * AI_side)) * sin(rollAngle) + AI_y;
			
			if((AI_x - AI_line_lx) * (AI_x - AI_line_lx) + (AI_y - AI_line_ly) * (AI_y - AI_line_ly) <= 1.5 * AI_side * 1.5 * AI_side)
				ege_line(AI_line_lx, AI_line_ly, AI_line_rx, AI_line_ry);
			
			
		}
	}
	
	
	//绘制指示(飞机)标志
	
	//中间方框
	setfillcolor(BLACK);
	ege_fillrect(AI_x - 0.03 * AI_side, AI_y - 0.04 * AI_side , 0.06 * AI_side, 0.08 * AI_side);
	setcolor(WHITE);
	setlinewidth(0.011 * AI_side);
	ege_rectangle(AI_x - 0.03 * AI_side, AI_y - 0.04 * AI_side , 0.06 * AI_side, 0.08 * AI_side);
	
	
	//右侧
	setcolor(BLACK);
	setlinewidth(0.065 * AI_side);
	//黑线
	ege_line(AI_x + 0.20 * AI_side, AI_y - 0.015 * AI_side, AI_x + 0.56 * AI_side, AI_y - 0.015 * AI_side);
	ege_line(AI_x + 0.20 * AI_side, AI_y - 0.045 * AI_side, AI_x + 0.20 * AI_side, AI_y + 0.13 * AI_side);
	
	setcolor(WHITE);
	setlinewidth(0.01 * AI_side);
	//白线边框
	ege_line(AI_x + 0.17 * AI_side, AI_y - 0.045 * AI_side, AI_x + 0.56 * AI_side, AI_y - 0.045 * AI_side);
	ege_line(AI_x + 0.23 * AI_side, AI_y + 0.02 * AI_side, AI_x + 0.56 * AI_side, AI_y + 0.02 * AI_side);
	ege_line(AI_x + 0.17 * AI_side, AI_y + 0.13 * AI_side, AI_x + 0.237 * AI_side, AI_y + 0.13 * AI_side);
	
	ege_line(AI_x + 0.56 * AI_side, AI_y - 0.045 * AI_side, AI_x + 0.56 * AI_side, AI_y + 0.02 * AI_side);
	ege_line(AI_x + 0.175 * AI_side, AI_y - 0.05 * AI_side, AI_x + 0.175 * AI_side, AI_y + 0.137 * AI_side);
	ege_line(AI_x + 0.237 * AI_side, AI_y + 0.02 * AI_side, AI_x + 0.237 * AI_side, AI_y + 0.137 * AI_side);
	
	//左侧
	setcolor(BLACK);
	setlinewidth(0.065 * AI_side);
	//黑线
	ege_line(AI_x - 0.20 * AI_side, AI_y - 0.015 * AI_side, AI_x - 0.56 * AI_side, AI_y - 0.015 * AI_side);
	ege_line(AI_x - 0.20 * AI_side, AI_y - 0.045 * AI_side, AI_x - 0.20 * AI_side, AI_y + 0.13 * AI_side);
	
	setcolor(WHITE);
	setlinewidth(0.01 * AI_side);
	//白线边框
	ege_line(AI_x - 0.17 * AI_side, AI_y - 0.045 * AI_side, AI_x - 0.56 * AI_side, AI_y - 0.045 * AI_side);
	ege_line(AI_x - 0.23 * AI_side, AI_y + 0.02 * AI_side, AI_x - 0.56 * AI_side, AI_y + 0.02 * AI_side);
	ege_line(AI_x - 0.17 * AI_side, AI_y + 0.13 * AI_side, AI_x - 0.23 * AI_side, AI_y + 0.13 * AI_side);
	
	ege_line(AI_x - 0.56 * AI_side, AI_y - 0.045 * AI_side, AI_x - 0.56 * AI_side, AI_y + 0.02 * AI_side);
	ege_line(AI_x - 0.175 * AI_side, AI_y - 0.05 * AI_side, AI_x - 0.175 * AI_side, AI_y + 0.13 * AI_side);
	ege_line(AI_x - 0.23 * AI_side, AI_y + 0.02 * AI_side, AI_x - 0.23 * AI_side, AI_y + 0.13 * AI_side);
	
	
	
	//绘制上方固定的蓝色遮挡
	setcolor(EGEARGB(0xff,0x03,0xb2,0xe3));
	setlinewidth(0.05 * AI_side);
	//原本两个椭圆弧模拟的，因为边缘的角度问题用不了
//	ege_arc(AI_x - 1.23 * AI_side, AI_y - 1 * AI_side, 2.46 * AI_side, 2.3 * AI_side, -150, 120);
//	ege_arc(AI_x - 1.23 * AI_side, AI_y - 1.2 * AI_side, 2.46 * AI_side, 2.3 * AI_side, -150, 120);
	//新版循环画多个细的椭圆弧
	for(double i = 0.5;i >= 0;i -= 0.02){
		ege_arc(AI_x - (1.05 + i) * AI_side, AI_y - (0.90 + i) * AI_side, (2.1 + 2 * i) * AI_side, (1.8 + 2 * i) * AI_side, -150, 120);
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
		if(i == 10 || i == -10 || i == 20 || i == -20 || i == 45 || i == -45){
			AI_pointTmp1_x = - (AI_y - 0.92 * AI_side - AI_y) * sin(1.0 * i / 360 * 2 * PI) + AI_x;
			AI_pointTmp1_y = (AI_y - 0.92 * AI_side - AI_y) * cos(1.0 * i / 360 * 2 * PI) + AI_y;
			AI_pointTmp2_x = - (AI_y - 1 * AI_side - AI_y) * sin(1.0 * i / 360 * 2 * PI) + AI_x;
			AI_pointTmp2_y = (AI_y - 1 * AI_side - AI_y) * cos(1.0 * i / 360 * 2 * PI) + AI_y;
			ege_line(AI_pointTmp1_x, AI_pointTmp1_y, AI_pointTmp2_x, AI_pointTmp2_y);
		}
		
	}
	
	//+-30度稍长的线
	AI_pointTmp1_x = - (AI_y - 0.90 * AI_side - AI_y) * sin(1.0 * 30 / 360 * 2 * PI) + AI_x;
	AI_pointTmp1_y = (AI_y - 0.90 * AI_side - AI_y) * cos(1.0 * 30 / 360 * 2 * PI) + AI_y;
	AI_pointTmp2_x = - (AI_y - 1.04 * AI_side - AI_y) * sin(1.0 * 30 / 360 * 2 * PI) + AI_x;
	AI_pointTmp2_y = (AI_y - 1.04 * AI_side - AI_y) * cos(1.0 * 30 / 360 * 2 * PI) + AI_y;
	ege_line(AI_pointTmp1_x, AI_pointTmp1_y, AI_pointTmp2_x, AI_pointTmp2_y);
	AI_pointTmp1_x = - (AI_y - 0.90 * AI_side - AI_y) * sin(1.0 * -30 / 360 * 2 * PI) + AI_x;
	AI_pointTmp1_y = (AI_y - 0.90 * AI_side - AI_y) * cos(1.0 * -30 / 360 * 2 * PI) + AI_y;
	AI_pointTmp2_x = - (AI_y - 1.04 * AI_side - AI_y) * sin(1.0 * -30 / 360 * 2 * PI) + AI_x;
	AI_pointTmp2_y = (AI_y - 1.04 * AI_side - AI_y) * cos(1.0 * -30 / 360 * 2 * PI) + AI_y;
	ege_line(AI_pointTmp1_x, AI_pointTmp1_y, AI_pointTmp2_x, AI_pointTmp2_y);
	
	//正上方三角形
	setfillcolor(WHITE);
	setlinewidth(0.015 * AI_side);
	ege_point AI_point1[3]{
		{AI_x, AI_y - 0.93 * AI_side},
		{AI_x - 0.06 * AI_side, AI_y - AI_side},
		{AI_x + 0.06 * AI_side, AI_y - AI_side},
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
	AI_pointTmp4_x = (AI_x - 0.04 * AI_side - AI_x) * cos(rollAngle) - (AI_y - 0.88 * AI_side - AI_y) * sin(rollAngle) + AI_x;
	AI_pointTmp4_y = (AI_y - 0.88 * AI_side - AI_y) * cos(rollAngle) + (AI_x - 0.04 * AI_side - AI_x) * sin(rollAngle) + AI_y;
	AI_pointTmp5_x = (AI_x + 0.04 * AI_side - AI_x) * cos(rollAngle) - (AI_y - 0.88 * AI_side - AI_y) * sin(rollAngle) + AI_x;
	AI_pointTmp5_y = (AI_y - 0.88 * AI_side - AI_y) * cos(rollAngle) + (AI_x + 0.04 * AI_side - AI_x) * sin(rollAngle) + AI_y;
	
	
	setcolor(WHITE);
	setlinewidth(0.02 * AI_side);
	ege_line(AI_pointTmp3_x, AI_pointTmp3_y, AI_pointTmp4_x, AI_pointTmp4_y);
	ege_line(AI_pointTmp5_x, AI_pointTmp5_y, AI_pointTmp4_x, AI_pointTmp4_y);
	ege_line(AI_pointTmp3_x, AI_pointTmp3_y, AI_pointTmp5_x, AI_pointTmp5_y);
	
	ege_point AI_stb_points[3]{
		{AI_pointTmp3_x, AI_pointTmp3_y},
		{AI_pointTmp4_x, AI_pointTmp4_y},
		{AI_pointTmp5_x, AI_pointTmp5_y},
	};
	setfillcolor(BLACK);
	ege_fillpoly(3,AI_stb_points);
	
	//利用四个矩形遮盖为矩形(正常遮盖)
	setfillcolor(BLACK);
	ege_fillrect(AI_x - 1.2 * AI_r, AI_y - 1.2 * AI_r, 2.4 * AI_r, 1.2 * AI_r - AI_side);
	ege_fillrect(AI_x - 1.2 * AI_r, AI_y + 0.92 * AI_side, 2.4 * AI_r, 1.2 * AI_r - AI_side);
	ege_fillrect(AI_x - 1.2 * AI_r, AI_y - 1.2 * AI_r, 1.32 * AI_r - AI_side , 2.4 * AI_r);
	ege_fillrect(AI_x + 0.88 * AI_side, AI_y - 1.2 * AI_r, 1.32 * AI_r - AI_side , 2.4 * AI_r);
	
	
}


//===================================================================================================//





//========================================以下为罗盘=================================================//

extern double rotationangle;
double realrotationangle4 = 0;

//画边框
void draw_PFD_Compass_frame(double center_x, double center_y, double side)
{
	double r = side * 51.2 / 126;//罗盘的半径
	
	setlinewidth(2.5);
	
	setfillcolor(EGEARGB(0xff, 0x3A, 0x3A, 0x38));
	//ege_fillrect(center_x - r + side * 23 / 126, center_y - r - side / 126, 56 * side / 126, 10 * side / 126);
	
	ege_point coverpoly[7];
	
	coverpoly[0].x = center_x - r + side * 23 / 126;
	coverpoly[0].y = center_y - r + side * 9 / 126;
	
	coverpoly[1].x = center_x - r + side * 79 / 126;
	coverpoly[1].y = center_y - r + side * 9 / 126;
	
	coverpoly[2].x = center_x - r + side * 79 / 126;
	coverpoly[2].y = center_y - r + 7.7 * side / 126;
	
	coverpoly[3].x = center_x - r + side * 66 / 126;
	coverpoly[3].y = center_y - r + 1.5 * side / 126;
	
	coverpoly[4].x = center_x;
	coverpoly[4].y = center_y - r;
	
	coverpoly[5].x = center_x - r + side * 36 / 126;
	coverpoly[5].y = center_y - r + 1.5 * side / 126;
	
	coverpoly[6].x = center_x - r + side * 23 / 126;
	coverpoly[6].y = center_y - r + 8.1 * side / 126;
	
	ege_fillpoly(7, coverpoly);
	
	for (int i = 0; i <= 5; i++)
	{
		setcolor(BLACK);
		setlinewidth(r * 0.01);
		ege_arc(center_x - r, center_y - r - r * 0.01 * i, r * 2, r * 2, -56.0, -68.0);
	}
	
	setcolor(BLACK);
	ege_arc(center_x - r, center_y - r, r * 2, r * 2, -57.0, -66.0);
}

//画刻度
void draw_PFD_scale(double compass_x, double compass_y, double side)
{
	double compass_r = side * 51.2 / 126;
	setcolor(EGEARGB(0xff, 0xff, 0xff, 0xff));//设置线条颜色
	setlinewidth(compass_r * 0.01);//设置线条宽度
	//长刻度
	for (double i = 0; i < 360; i += 10)
	{
		double scaleAngle = realrotationangle4 + i;
		double rad = scaleAngle * PI / 180.0;
		double scalePosX = compass_x + 0.96 * compass_r * sin(rad);
		double scalePosY = compass_y - 0.96 * compass_r * cos(rad);
		if (scalePosX >= compass_x - compass_r * sin(60 * PI / 180) && scalePosX <= compass_x + compass_r * sin(40 * PI / 180) && scalePosY <= compass_y - compass_r * cos(40 * PI / 180) && scalePosY >= compass_y - compass_r) //判断文字是否在输出区域内，在区域内则输出，不在区域内则不输出
		{
			ege_line(compass_x + compass_r * 0.99 * sin(rad), compass_y - compass_r * 0.99 * cos(rad), compass_x + 0.95 * compass_r * sin(rad), compass_y - 0.95 * compass_r * cos(rad));
		}
	}
	//短刻度
	for (double i = 5; i < 360; i += 10)
	{
		double scaleAngle = realrotationangle4 + i;
		double rad = scaleAngle * PI / 180.0;
		double scalePosX = compass_x + 0.975 * compass_r * sin(rad);
		double scalePosY = compass_y - 0.975 * compass_r * cos(rad);
		if (scalePosX >= compass_x - compass_r * sin(60 * PI / 180) && scalePosX <= compass_x + compass_r * sin(40 * PI / 180) && scalePosY <= compass_y - compass_r * cos(40 * PI / 180) && scalePosY >= compass_y - compass_r) //判断文字是否在输出区域内，在区域内则输出，不在区域内则不输出
		{
			ege_line(compass_x + compass_r * 0.99 * sin(rad), compass_y - compass_r * 0.99 * cos(rad), compass_x + 0.965 * compass_r * sin(rad), compass_y - 0.965 * compass_r * cos(rad));
		}
	}
}

//画旋转的文字
void draw_PFD_compass_text(double compass_x, double compass_y, double side)
{
	double compass_r = side * 51.2 / 126;//罗盘的半径
	for (int i = 0; i < 360; i += 30) //循环输出表上的刻度值
	{
		double textAngle = realrotationangle4 + i;
		double rad = textAngle * PI / 180.0;
		double textPosX = compass_x + 0.89 * compass_r * sin(rad);
		double textPosY = compass_y - 0.89 * compass_r * cos(rad);
		
		//设置文字的格式
		LOGFONTW font;
		setcolor(EGEARGB(0xff, 0xff, 0xff, 0xff));
		setfont(compass_r * 0.15, 0, "Leelawadee");
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		getfont(&font);
		font.lfEscapement = -textAngle * 10;
		font.lfWeight = 500;
		setfont(&font);
#if 0
		xyprintf(compass_x + 0.8 * compass_r * cos(rad), compass_y - 0.8 * compass_r * sin(rad), "%d", i);
#endif
		if (textPosX >= compass_x - compass_r * sin(60 * PI / 180) && textPosX <= compass_x + compass_r * sin(40 * PI / 180) && textPosY <= compass_y - compass_r * cos(40 * PI / 180) && textPosY >= compass_y - compass_r) //判断文字是否在输出区域内，在区域内则输出，不在区域内则不输出
		{
			char strBuffer[64];
			sprintf_s(strBuffer, "%d", i / 10);
			ege_drawtext(strBuffer, textPosX, textPosY);
		}
		//setfillcolor(BLACK);
		//ege_fillrect(compass_x - compass_r, compass_y - compass_r * cos(33 * PI / 180), compass_r * 2, compass_r * cos(33 * PI / 180) - compass_r * cos(44 * PI / 180));//遮盖部分
	}
	
	for (int i = 0; i < 360; i += 10) 
	{
		if (i % 30 != 0)
		{
			double textAngle = realrotationangle4 + i;
			double rad = textAngle * PI / 180.0;
			double textPosX = compass_x + 0.9 * compass_r * sin(rad);
			double textPosY = compass_y - 0.9 * compass_r * cos(rad);
			
			//设置文字的格式
			LOGFONTW font;
			setcolor(EGEARGB(0xff, 0xff, 0xff, 0xff));
			setfont(compass_r * 0.10, 0, "Leelawadee");
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			getfont(&font);
			font.lfEscapement = -textAngle * 10;
			font.lfWeight = 500;
			setfont(&font);
			
#if 0
			xyprintf(compass_x + 0.8 * compass_r * cos(rad), compass_y - 0.8 * compass_r * sin(rad), "%d", i);
#endif
			if (textPosX >= compass_x - compass_r * sin(60 * PI / 180) && textPosX <= compass_x + compass_r * sin(40 * PI / 180) && textPosY <= compass_y - compass_r * cos(40 * PI / 180) && textPosY >= compass_y - compass_r) //判断文字是否在输出区域内，在区域内则输出，不在区域内则不输出
			{
				char strBuffer[64];
				sprintf_s(strBuffer, "%d", i / 10);
				ege_drawtext(strBuffer, textPosX, textPosY);
			}
			setfillcolor(BLACK);
			ege_fillrect(compass_x - compass_r, compass_y - compass_r * cos(33 * PI / 180), compass_r * 2, compass_r * cos(33 * PI / 180) - compass_r * cos(44 * PI / 180));//遮盖部分
		}
	}
}

//画航向指示
void draw_PFD_course(double center_x, double center_y, double side)
{
	ege_point triangle[4];
	
	triangle[0].x = center_x;
	triangle[0].y = center_y - side * 48.7 / 126;
	
	triangle[1].x = center_x - side * 2.5 / 126;
	triangle[1].y = center_y - side * 52.7 / 126;
	
	triangle[2].x = center_x + side * 2.5 / 126;
	triangle[2].y = center_y - side * 52.7 / 126;
	
	triangle[3].x = center_x;
	triangle[3].y = center_y - side * 48.7 / 126;
	
	ege_drawpoly(4, triangle);
}

//画备用PFD表的罗盘
void draw_PFD_standby_Compass(double center_x, double center_y, double side)
{
	realrotationangle4 = 360 - rotationangle;
	
	draw_PFD_Compass_frame(center_x, center_y, side);
	
	draw_PFD_scale(center_x, center_y, side);
	
	draw_PFD_compass_text(center_x, center_y, side);
	
	draw_PFD_course(center_x, center_y, side);
	
	
}



//===================================================================================================//





//========================================以下为边框=================================================//



void draw_black_sign1(double x, double y, double single) {
	setfillcolor(BLACK);
	ege_point points11[9] = {
		x - (16) * single,y - (6) * single,//1
		x - (17) * single, y - (5) * single,//2
		x - (17) * single, y + (5) * single,//3
		x - (16) * single,y +(6) * single,//4
		x + (16) * single,y + (6) * single,//5
		x + (17) * single, y + (5) * single,//6
		x + (17) * single, y - (5) * single,//7
		x + (16) * single,y - (6) * single,//8
		x - (16) * single,y - (6) * single//1
	};
	ege_fillpoly(9, points11);
}

void draw_black_sign2(double x, double y, double single) {
	setfillcolor(BLACK);
	ege_point points11[9] = {
		x - (5) * single, y - (17) * single,//1
		x - (6) * single,y - (16) * single,//2
		x - (6) * single,y + (16) * single,//3
		x - (5) * single, y + (17) * single,//4
		x + (5) * single, y + (17) * single,//5
		x + (6) * single,y + (16) * single,//6
		x + (6) * single,y - (16) * single,//7
		x + (5) * single, y - (17) * single,//8
		x - (5) * single,y - (17) * single//1
	};
	ege_fillpoly(9, points11);
}

void draw_smallpfd_frame(double center_x, double center_y, double side) {
// 设置相关参数
	double single = side / 126;// side传的是黑边的长度，把除以单位一，取其单位长度，方便计算比例
	double width = single * 130;
	double length = single * 126;
	
	
	setlinewidth(side/100);// 这里是对于表盘上部阴影的处理
	setcolor(EGEARGB(0Xff, 13, 15, 17));
	ege_line(center_x - 63 * single, center_y - (63 + 21) * single,//1
		center_x - (65 + 7 + 15) * single, center_y - (60) * single);//2
	ege_line(center_x - 63 * single, center_y - (63 + 21) * single,//1
		center_x + 63 * single, center_y - (63 + 21) * single);//8
	ege_line(center_x + (65 + 7 + 15) * single, center_y - (60) * single,//7
		center_x + 63 * single, center_y - (63 + 21) * single);//8
	
	ege_enable_aa(false);// 关闭抗锯齿
	
	setcolor(EGEARGB(0xff, 0x1b, 0x20, 0x25));//接下来画外框1的线条
	setlinewidth(4);
	ege_point points1[9] = {
		center_x - 63 * single,center_y - (63 + 21) * single,//1
		center_x - (65 + 7 + 15) * single,center_y - (60) * single,//2
		center_x - (65 + 7 + 15) * single, center_y + (60) * single,//3
		center_x - 63 * single,center_y + (63 + 21) * single,//4
		center_x + 63 * single,center_y + (63 + 21) * single,//5
		center_x + (65 + 7 + 15) * single,center_y + (60) * single,//6
		center_x + (65 + 7 + 15) * single, center_y - (60) * single,//7
		center_x + 63 * single,center_y - (63 + 21) * single,//8
		center_x - 63 * single,center_y - (63 + 21) * single//1
	};
	ege_drawpoly(9,points1);
	
	setcolor(EGEARGB(0xff, 0x1b, 0x20, 0x25));//接下来画外框2的线条
	setlinewidth(4);
	ege_point points2[22] = {
		center_x - 63 * single,center_y - (63 + 5) * single,//1
		
		//加入曲线拟合点——左上角弧线点
		center_x - (63 + 4) * single,center_y - (60 + 6.3) * single,
		center_x - (63 + 4.5) * single,center_y - (60 + 4) * single,
		center_x - (63 + 6) * single,center_y - (60 + 2) * single,
		
		center_x - (65 + 7) * single,center_y - (60) * single,//2
		center_x - (65 + 7) * single, center_y + (60) * single,//3
		
		// 加入曲线拟合点——左下角弧线点
		center_x - (63 + 6) * single,center_y + (60 + 2) * single,
		center_x - (63 + 4.5) * single,center_y + (60 + 4) * single,
		center_x - (63 + 4.3) * single,center_y + (60 + 6.3) * single,
		
		center_x - 63 * single,center_y + (63 + 5) * single,//4
		center_x + 63 * single,center_y + (63 + 5) * single,//5
		
		// 加入曲线拟合点——右下角弧线点
		center_x + (63 + 1) * single,center_y + (60 + 7) * single,
		center_x + (63 + 4) * single,center_y + (60 + 4.5) * single,
		center_x + (63 + 6) * single,center_y + (60 + 3.5) * single,
		
		center_x + (65 + 7) * single,center_y + (60) * single,//6
		center_x + (65 + 7) * single, center_y - (60) * single,//7
		
		// 加入曲线拟合点——右上角弧线点
		center_x + (63 + 9) * single,center_y - (60) * single,
		center_x + (63 + 6) * single,center_y - (60 +5) * single,
		center_x +  (63+1.2) * single,center_y - (60 + 6) * single,
		
		center_x + 63 * single,center_y - (63 + 5) * single,//8
		
		center_x - 63 * single,center_y - (63 + 5) * single,//1
		center_x - 63 * single,center_y - (63 + 5) * single//1
	};
	ege_bezier(22, points2);
	
	setfillcolor(EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(center_x - 63 * single, center_y - (63 + 21 - 10) * single,EGEARGB(0xff, 0x1b, 0x20, 0x25));//1定位点向下的点
	floodfill(center_x - (65 + 7 + 15 - 10) * single, center_y - (60) * single, EGEARGB(0xff, 0x1b, 0x20, 0x25));//2定位点向右的点
	floodfill(center_x - (65 + 7 + 15 - 10) * single, center_y + (60) * single, EGEARGB(0xff, 0x1b, 0x20, 0x25));//3定位点向右的点
	floodfill(center_x - 63 * single, center_y + (63 + 21 - 10) * single, EGEARGB(0xff, 0x1b, 0x20, 0x25));//4定位点向上的点
	floodfill(center_x + 63 * single, center_y + (63 + 21 - 10) * single, EGEARGB(0xff, 0x1b, 0x20, 0x25));//5定位点向上的点
	floodfill(center_x + (65 + 7 + 15 -10) * single, center_y + (60) * single, EGEARGB(0xff, 0x1b, 0x20, 0x25));//6定位点向左的点
	floodfill(center_x + (65 + 7 + 15 - 10) * single, center_y - (60) * single, EGEARGB(0xff, 0x1b, 0x20, 0x25));//7定位点向左的点
	floodfill(center_x + 63 * single, center_y - (63 + 21 - 10) * single, EGEARGB(0xff, 0x1b, 0x20, 0x25));//8定位点向下的点
	
	
	setcolor(EGEARGB(0xff, 0x1b, 0x20, 0x25));//接下来画外框3的线条
	setlinewidth(4);
	ege_point points3[22] = {
		center_x - 58 * single,center_y - (63) * single,//1
		
		//加入曲线拟合点——左上角弧线点
		center_x - (58 + 4) * single,center_y - (56 + 6.3) * single,
		center_x - (58 + 4.5) * single,center_y - (56 + 4) * single,
		center_x - (58 + 6) * single,center_y - (56 + 2) * single,
		
		center_x - (65) * single,center_y - (56) * single,//2
		center_x - (65) * single,center_y + (52) * single,//3
		
		//加入曲线拟合点——左下角弧线点
		center_x - (58 + 4) * single,center_y + (52 + 2) * single,
		center_x - (58 + 2.5) * single,center_y + (52 + 4) * single,
		center_x - (58 + 2.3) * single,center_y + (52 + 6.3) * single,
		
		center_x - 58 * single,center_y + (59) * single,//4
		center_x + 58 * single,center_y + (59) * single,//5
		
		//加入曲线拟合点——右下角弧线点
		center_x + (58 + 1) * single,center_y + (52 + 7) * single,
		center_x + (58 + 4) * single,center_y + (52 + 4.5) * single,
		center_x + (58 + 6) * single,center_y + (52 + 3.5) * single,
		
		center_x + (65) * single, center_y + (52) * single,//6
		center_x + (65) * single, center_y - (56) * single,//7
		
		//加入曲线拟合点——右上角弧线点
		center_x + (58 + 6) * single,center_y - (56+2.5) * single,
		center_x + (58 + 5) * single,center_y - (56 + 3.5) * single,
		center_x + (58+2) * single,center_y - (56 + 6) * single,
		
		center_x + 58 * single,center_y - (63) * single,//8
		center_x - 58 * single,center_y - (63) * single,//1
		center_x - 58 * single,center_y - (63) * single//1
	};
	ege_bezier(22,points3);
	
	setfillcolor(EGEARGB(0Xff, 32, 37, 41));
	floodfill(center_x - 63 * single, center_y - (63 + 5 - 4) * single, EGEARGB(0xff, 0x1b, 0x20, 0x25));//1定位点向下的点
	floodfill(center_x - (65 + 7 - 4) * single, center_y - (60) * single, EGEARGB(0xff, 0x1b, 0x20, 0x25));//2定位点向右的点
	floodfill(center_x - (65 + 7 - 4) * single, center_y + (60) * single, EGEARGB(0xff, 0x1b, 0x20, 0x25));//3定位点向右的点
	floodfill(center_x - 63 * single, center_y + (63 + 5 - 4) * single, EGEARGB(0xff, 0x1b, 0x20, 0x25));//4定位点向上的点
	floodfill(center_x + 63 * single, center_y + (63 + 5 - 4) * single, EGEARGB(0xff, 0x1b, 0x20, 0x25));//5定位点向上的点
	floodfill(center_x + (65 + 7 - 4) * single, center_y + (60) * single, EGEARGB(0xff, 0x1b, 0x20, 0x25));//6定位点向左的点
	floodfill(center_x + (65 + 7 - 4) * single, center_y - (60) * single, EGEARGB(0xff, 0x1b, 0x20, 0x25));//7定位点向左的点
	floodfill(center_x + 63 * single, center_y - (63 + 5 - 4) * single, EGEARGB(0xff, 0x1b, 0x20, 0x25));//8定位点向下的点
	
	
	ege_enable_aa(true);
	setcolor(EGEARGB(0xff, 0x1b, 0x20, 0x25));//接下来画外框1的线条
	setlinewidth(6);
	ege_bezier(22, points2);
	ege_bezier(22, points3);
	
	
	setfillcolor(EGEARGB(0Xff, 32, 37, 41));//接下来画的一系列圆都是对于右下角圆的修补与显示立体效果
	ege_fillellipse(
		center_x + (61.4) * single, center_y + (35) * single,
		single * 9, single * 9
		);
	ege_fillellipse(
		center_x + (60.8) * single, center_y + (36) * single,
		single * 9, single * 9
		);
	ege_fillellipse(
		center_x + (59) * single, center_y + (37) * single,
		single * 9, single * 9
		);
	ege_fillellipse(
		center_x + (58) * single, center_y + (38) * single,
		single * 9, single * 9
		);
	ege_fillellipse(
		center_x + (57) * single, center_y + (38) * single,
		single * 9, single * 9
		);//从这往上是上面的
	ege_fillellipse(
		center_x + (38) * single, center_y + (51) * single,
		single * 9, single * 9
		);
	ege_fillellipse(
		center_x + (36) * single, center_y + (53) * single,
		single * 9, single * 9
		);
	ege_fillellipse(
		center_x + (35.9) * single, center_y + (53.28) * single,
		single * 9, single * 9
		);
	ege_fillellipse(
		center_x + (34) * single, center_y + (55.5) * single,
		single * 9, single * 9
		);
	ege_fillellipse(
		center_x + (33.8) * single, center_y + (56.3) * single,
		single * 9, single * 9
		);// 从这往上是下面的   
	setcolor(EGEARGB(0Xff, 32, 37, 41));//对于左下角的圆弧进行补充的贝塞尔曲线（下弧线）
	setlinewidth(single * 2);
	ege_point points5[4] = {
		center_x + (44) * single, center_y + (47.6) * single,
		center_x + (35.9) * single, center_y + (54.28) * single,
		center_x + (34.9) * single, center_y + (58) * single,
		center_x + (32.9) * single, center_y + (60) * single,
	};
	ege_bezier(4, points5);
	ege_point points6[4] = {// （上弧线）
		center_x + (66.4) * single, center_y + (35) * single,
		center_x + (63.2) * single, center_y + (36) * single,
		center_x + (62.1) * single, center_y + (37) * single,
		center_x + (55) * single, center_y + (41) * single,
	};
	ege_bezier(4, points6);
	
	setfillcolor(EGEARGB(0XFF, 32, 38, 43));//右下角大圆
	ege_fillellipse(
		center_x + (40) * single, center_y + (40) * single,
		single * 35, single * 35
		);
	
	// 这是绘制旋钮的部分
	setfillcolor(EGEARGB(0XFF, 46,47,48));
	for (double i = 0; i < single * 2.2; i = i + single / 5) {
		ege_fillellipse(
			center_x + (40) * single, center_y + (40 + i) * single,
			single * 34, single * 34
			);
	}
	setcolor(BLACK);
	setlinewidth(single / 1.2);
	ege_ellipse(
		center_x + (40) * single, center_y + (40 + single * 2.1) * single,
		single * 34, single * 34
		);
	setfillcolor(EGEARGB(0Xff, 56, 57, 59));
	ege_fillellipse(
		center_x + (40) * single, center_y + (40 + single * 2.1) * single,
		single * 34, single * 34
		);
	setlinewidth(single / 2);
	setcolor(BLACK);
	ege_ellipse(
		center_x + (44.5) * single, center_y + (45 + single * 2.1) * single,
		single * 25, single * 25
		);
	
	// 接下来绘制的是5个黑色的小图标以及他们对应的字
	draw_black_sign1(center_x - 29 * single, center_y - (76) * single, single);
	draw_black_sign1(center_x + 29 * single, center_y - (76) * single, single);
	draw_black_sign1(center_x - 29 * single, center_y + (76) * single, single);
	
	draw_black_sign2(center_x - 80 * single, center_y + (29) * single, single);
	draw_black_sign2(center_x - 80 * single, center_y - (29) * single, single);
	
//	// 文字显示
//	// 因为在小熊猫上会字体偏移所以改正
//	setbkmode(TRANSPARENT);
//	settextjustify(CENTER_TEXT, CENTER_TEXT);
//	setfont(single * 9, 0, "黑体");
//	setcolor(EGEARGB(0xff, 136, 97, 67));
//	ege_drawtext("APP", center_x - 38 * single, center_y - (80) * single);
//	ege_drawtext("HP/IN", center_x + 16 * single, center_y - (80) * single);
//	ege_drawtext("-", center_x - 84 * single, center_y + (25) * single);
//	ege_drawtext("+", center_x - 84 * single, center_y - (32) * single);
//	ege_drawtext("RST", center_x - 38 * single, center_y + (72) * single);
//	setfont(single * 8, 0, "黑体");
//	ege_drawtext("ATT", center_x - 63 * single, center_y + (71) * single);
//	ege_drawtext("RARO", center_x + 24 * single, center_y + (71) * single);
	
	// 文字显示
	setbkmode(TRANSPARENT);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setfont(single * 10, 0, "黑体");
	setcolor(EGEARGB(0xff, 136, 97, 67));
	ege_drawtext("APP", center_x - 29 * single, center_y - (75) * single);
	ege_drawtext("HP/IN", center_x + 29 * single, center_y - (75) * single);
	ege_drawtext("-", center_x - 80 * single, center_y + (29) * single);
	ege_drawtext("+", center_x - 80 * single, center_y - (29) * single);
	ege_drawtext("RST", center_x - 29 * single, center_y + (77) * single);
	setfont(single * 8, 0, "黑体");
	ege_drawtext("ATT", center_x - 53 * single, center_y + (75) * single);
	ege_drawtext("RARO", center_x + 31 * single, center_y + (75) * single);
	
	
	
}

// 绘制表盘右上角的气压指示
void drwa_ND_atmosphericPressure(double center_x,double center_y,double side){
	
	setbkmode(TRANSPARENT);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setfont(side/6, 0, "黑体");
	setcolor(EGEARGB(250, 76, 153, 0));
	char str[100];
	sprintf_s(str, "%.2f", INGH_data);
	ege_drawtext(str,center_x + side / 3.3,center_y - side / 1.1);
	ege_drawtext("IN",center_x + side / 1.66,center_y - side / 1.1);
}


//===================================================================================================//





//==========================================以下为高度表============================================//


extern double altitude;

//绘制底框

void draw_alt_standy_frame(double center_x, double center_y, double side) {
	double frame_wide = side * 63 / 96;//底框的宽度
	double frame_height = side * 331 / 96;//底框的长度
	
	double frame_x = center_x - 31.5 / 96 * side;
	double frame_y = center_y - 165.5 / 96.0 * side;
	
	setfillcolor(EGEARGB(0Xff, 59, 59, 59));
	//setfillcolor(WHITE);
	ege_fillrect(frame_x, frame_y, frame_wide, frame_height);
}

//绘制线框和黑色填充

void draw_alt_standy_wireframe(double center_x, double center_y, double side) {
	setcolor(EGEARGB(200, 177, 177, 178));
	double x = center_x + 31.5 / 96 * side - 78.0 / 96 * side;
	double y = center_y - 24.0 / 96 * side;
	
	double wide = side * 78 / 96;
	double height = side * 48 / 96;
	setlinewidth(side * 0.01);
	setfillcolor(BLACK);
	ege_fillrect(x, y, wide, height);
	ege_rectangle(x, y, wide, height);
	
}

//画其他的数字

void draw_alt_else(double center_x, double center_y, double side, double height) {
	setcolor(EGEARGB(200, 177, 177, 178));
	double y = center_y - side * 0.17;
	double x = center_x;
	double number_height = side * 2.5 / 96.0 * 2 * 6.5;
	double number_width = side * 2.5 / 96.0 * 5;
	
	double hun = fmod(height, 1000);
	hun = hun / 100;
	char num[12] = { '9','0','1','2','3','4','5','6','7','8','9','0' };
	
	outtextxy(center_x - number_width * 0.55, y, num[(int)hun + 1]);
	
	double thou = fmod(height, 10000);
	thou = thou / 1000;
	setfont(number_height * 1.2, number_width * 1.2, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	outtextxy(center_x - number_width * 2.0, y - number_height * 0.125, num[(int)thou + 1]);
	
	if (height > 9999.9) {
		double tenThou = fmod(height, 100000);
		tenThou = tenThou / 10000;
		setfont(number_height * 1.2, number_width * 1.2, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
		LOGFONTW FMC_font;
		getfont(&FMC_font);
		FMC_font.lfWeight = side * 3;
		setfont(&FMC_font);
		outtextxy(center_x - number_width * 3.25, y - number_height * 0.125, num[(int)tenThou + 1]);
	}
	else {
		double x_re = center_x - number_width * 3.25;
		double y_re = y + side * 4.5 / 96;
		double wide = number_width * 1.2 * 0.9;
		double lenth = number_height * 1.2 * 0.6;
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
		ege_enable_aa(TRUE);
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
	
}

//画十位和个位

void draw_alt_10(double center_x,double center_y,double side,double height) {
	setcolor(EGEARGB(200, 177, 177, 178));
	double y = center_y - side * 0.17;
	double x = center_x;
	double number_height = side  * 2.5 / 96.0 * 2 * 6.5;
	double number_width = side * 2.5 / 96.0 * 5;
	
	
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
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	//将背景颜色设置成透明
	
	setbkmode(1);
	//将区间进一步分段
	double judge = fmod(height, 20);
	if (judge >= 0 && judge < 7) {
		for (int i = 0;i < 3;i++) {
			outtextxy(x + 7.0 / 96.0 * side, y_100 + number_height * 0.6 * -(i - 1), nums[i + 1]);
			outtextxy(x + 7.0 / 96.0 * side + number_width, y_100 + number_height * 0.6 * -(i - 1), zeros[i + 1]);
		}
	}
	else if(judge >= 7 && judge <= 15)
	{
		for (int i = 0;i < 4;i++) {
			outtextxy(x + 7.0 / 96.0 * side, y_100 + number_height * 0.6 * -(i - 1), nums[i + 1]);
			outtextxy(x + 7.0 / 96.0 * side + number_width, y_100 + number_height * 0.6 * -(i - 1), zeros[i]);
		}
	}
	else
	{
		for (int i = 0;i < 3;i++) {
			outtextxy(x + 7.0 / 96.0 * side, y_100 + number_height * 0.6 * -(i), nums[i + 2]);
			outtextxy(x + 7.0 / 96.0 * side + number_width, y_100 + number_height * 0.6 * -(i), zeros[i]);
		}
	}
}

void draw_alt_NumShadow(double center_x, double center_y, double side) {
	double x = center_x + 31.5 / 96 * side - 78.0 / 96 * side;
	double y = center_y - 24.0 / 96 * side;
	
	double number_height = side * 2.5 / 96.0 * 2 * 6.5;
	double wide = side * 78 / 96;
	double height = side * 48 / 96;
	setfillcolor(EGEARGB(0Xff, 59, 59, 59));
	ege_fillrect(center_x - 31.5 / 96 * side, y - number_height - side * 0.005, side * 63 / 96, number_height);
	ege_fillrect(center_x - 31.5 / 96 * side, y + side * 0.005 + height, side * 63 / 96, number_height);
}

void draw_alt_lines(double center_x, double center_y, double side) {
	setcolor(EGEARGB(200, 177, 177, 178));
	
	setlinewidth(side * 0.005);
	int datas[11] = {};
	double ten = fmod(altitude, 100);
	double data5 = altitude - ten;
	
	//计算出来了每条线的数据
	for (int i = 0;i < 11;i++) {
		datas[i] = (int)data5 + 100 * (i - 5);
	}
	
	double gap = side * 331.0 / 96.0 / 10;
	double x1 = center_x - 31.0 / 96 * side;
	double x2 = center_x - 31.5 / 96 * side + side * 9.5 / 96;
	
	for (int i = 0;i < 11;i++) {
		double y = center_y - 165.5 / 96 * side + ten / 100 * gap + i * gap;//底部坐标 + 偏移坐标 + 循环坐标
		if (fmod(datas[10 - i] - 100, 200) == 0) {
			setlinewidth(side * 0.015);
			ege_line(x1, y, x2, y);
		}
	}
	
	//画数字
	settextjustify(LEFT_TEXT, TOP_TEXT);
	double number_height = side * 2.5 / 96.0 * 2 * 6.5 * 0.9;
	double number_width = side * 2.5 / 96.0 * 5 * 0.9;
	setfont(number_height, number_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	for (int i = 0;i < 11;i++) {
		double y = center_y - 165.5 / 96 * side + ten / 100 * gap + i * gap;//底部坐标 + 偏移坐标 + 循环坐标
		double x = center_x + 11.0 / 96 * side;
		int h = datas[i] / 100;
		if (datas[10 - i] == 0) {
			double x1 = center_x + 14.0 / 96 * side;
			ege_drawtext("000", x1, y);
		}
		else if (fmod(datas[10 - i], 200) == 0)
		{	
			if (datas[10 - i] < 1000 && datas[10 - i] > -1000) {
				char str[64];
				snprintf(str, sizeof(str), "%.0f", (float)datas[10 - i]);
				ege_drawtext(str, x, y);
			}
			else if (datas[10 - i] >= 1000 && datas[10 - i] <  10000)
			{
				double x1 = center_x + 8.0 / 96 * side;
				char str[64];
				snprintf(str, sizeof(str), "%.0f", (float)datas[10 - i]);
				ege_drawtext(str, x1, y);
			}
			else
			{
				double x1 = center_x + 2.5 / 96 * side;
				char str[64];
				snprintf(str, sizeof(str), "%.0f", (float)datas[10 - i]);
				ege_drawtext(str, x1, y);
			}
		}
	}
}

void draw_alt_Standy_shadow(double center_x, double center_y, double side) {
	double number_height = side * 2.5 / 96.0 * 2 * 6.5;
	double x = center_x + 31.5 / 96 * side - 78.0 / 96 * side;
	double y = center_y - 24.0 / 96 * side;
	
	setfillcolor(BLACK);
	
	y += side * 48 / 96 - side * 0.019;
	double wide = side * 78 / 96;
	double height = side * 0.02;
	
	ege_fillrect(center_x - 31.5 / 96 * side, y, side * 63 / 96, height);
	ege_fillrect(center_x - 31.5 / 96 * side, y - number_height * 1.425, side * 63 / 96, height);
	x = center_x + 31.5 / 96 * side - 78.0 / 96 * side;
	y = center_y - 24.0 / 96 * side;
	
	wide = side * 78 / 96;
	height = side * 48 / 96;
	setcolor(WHITE);
	ege_rectangle(x, y, wide, height);
	
}

void draw_standy_alt_main(double center_x, double center_y, double side) {
	double frame_wide = side * 63 / 96;//底框的宽度
	double frame_height = side * 331 / 96;//底框的长度
	
	double frame_x = center_x - 31.5 / 96 * side;
	double frame_y = center_y - 165.5 / 96.0 * side;
	setfillcolor(BLACK);
	double lenth = side * 0.5;
	ege_fillrect(frame_x, frame_y - lenth, frame_wide, lenth);
	ege_fillrect(frame_x, frame_y + frame_height, frame_wide, lenth);
}

//总绘制函数

void draw_standy_alt(double center_x, double center_y, double side) {
	double height;
	if (altitude < 0) {
		height = -altitude;
	}
	else
	{
		height = altitude;
	}
	draw_alt_standy_frame(center_x, center_y, side);//底框
	
	draw_alt_lines(center_x, center_y, side);//绘制下层表的所有刻度线
	draw_alt_standy_wireframe(center_x, center_y, side);//线框和线框下的底色
	draw_alt_10(center_x, center_y, side,height);//十位及个位
	draw_alt_else(center_x, center_y, side, height);//其他位
	draw_alt_NumShadow(center_x, center_y, side);//数字的遮盖
	draw_alt_Standy_shadow(center_x, center_y, side);//数字显示的上下的小阴影
	draw_standy_alt_main(center_x, center_y, side);//总遮挡
}








//===================================================================================================//





//==========================================以下为空速表============================================//



extern double airSpeed;

//绘制底框
void draw_standy_airSpeed_frame(double center_x, double center_y, double side) {
	double x = center_x - 24.5 / 96.0 * side;
	double y = center_y - 165.5 / 96.0 * side;
	double lenth = 331.0 / 96.0 * side;
	double width = 49.0 / 96.0 * side;
	
	setfillcolor(EGEARGB(0Xff, 59, 59, 59));
	ege_fillrect(x, y, width, lenth);
}

void draw_standy_airSpeed_wireframe(double center_x, double center_y, double side) {
	double x = center_x - 24.5 / 96.0 * side;
	double y = center_y - 24.0 / 96.0 * side;
	double lenth = 48.0 / 96.0 * side;
	double width = 53.0 / 96.0 * side;
	setfillcolor(BLACK);
	ege_fillrect(x, y, width, lenth);
	
	setlinewidth(side * 0.01);
	
	setcolor(EGEARGB(200, 177, 177, 178));
	ege_rectangle(x, y, width, lenth);
	
	setcolor(BLACK);
	ege_line(x, y, x, y + lenth);
}

void draw_standy_airSpeed_lines(double center_x, double center_y, double side) {
	setcolor(EGEARGB(200, 177, 177, 178));
	
	setlinewidth(side * 0.005);
	int datas[11] = {};
	double ten = fmod(airSpeed, 10);
	double data5 = airSpeed - ten;
	
	//计算出来了每条线的数据
	for (int i = 0;i < 11;i++) {
		datas[i] = (int)data5 + 10 * (i - 5);
	}
	
	double gap = side * 331.0 / 96.0 / 10;
	double x1 = center_x + 24.5 / 96 * side;
	double x2 = center_x + 16.5 / 96 * side;
	double x3 = center_x + 13.0 / 96 * side;
	
	double number_height = side * 2.5 / 96.0 * 2 * 6.5;
	double number_width = side * 2.5 / 96.0 * 5;
	if (datas[5] >= 30) {
		for (int i = 0;i < 11;i++) {
			double y = center_y - 165.5 / 96 * side + ten / 10 * gap + i * gap;//底部坐标 + 偏移坐标 + 循环坐标
			if (datas[10 - i] >= 30) {
				if (fmod(datas[10 - i] - 100, 20) == 0) {
					setlinewidth(side * 0.02);
					ege_line(x1, y, x2, y);
				}
				else
				{
					setlinewidth(side * 0.02);
					ege_line(x1, y, x3, y);
				}
			}
			
			for (int i = 0;i < 11;i++) {
				double y = center_y - 165.5 / 96 * side + ten / 10 * gap + i * gap;//底部坐标 + 偏移坐标 + 循环坐标
				double x = center_x - 5.0 / 96 * side;
				int h = datas[i] / 100;
				if (fmod(datas[10 - i], 20) == 0 && datas[10 - i] >= 30)
				{
					if (datas[10 - i] < 1000 && datas[10 - i] > -1000) {
						setfont(number_height * 0.8, number_width * 0.8, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
						LOGFONTW FMC_font;
						getfont(&FMC_font);
						FMC_font.lfWeight = side * 3;
						setfont(&FMC_font);
						char str[64];
						snprintf(str, sizeof(str), "%.0f", (float)datas[10 - i]);
						ege_drawtext(str, x + side * 0.08, y);
					}
					else if (datas[10 - i] >= 1000 && datas[10 - i] <= 10000)
					{
						setfont(number_height * 0.8, number_width * 0.8, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
						LOGFONTW FMC_font;
						getfont(&FMC_font);
						FMC_font.lfWeight = side * 3;
						setfont(&FMC_font);
						double x1 = center_x + 11.0 / 96 * side;
						char str[64];
						snprintf(str, sizeof(str), "%.0f", (float)datas[10 - i]);
						ege_drawtext(str, x1, y);
					}
					else
					{
						double x1 = center_x + 6.5 / 96 * side;
						char str[64];
						snprintf(str, sizeof(str), "%.0f", (float)datas[10 - i]);
						ege_drawtext(str, x1, y);
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0;i < 11;i++) {
			datas[i] = 30 + 10 * (i - 5);
		}
		for (int i = 0;i < 11;i++) {
			double y = center_y - 165.5 / 96 * side + 0 / 10 * gap + i * gap;//底部坐标 + 偏移坐标 + 循环坐标
			if (datas[10 - i] >= 30) {
				if (fmod(datas[10 - i] - 100, 20) == 0) {
					setlinewidth(side * 0.02);
					ege_line(x1, y, x2, y);
				}
				else
				{
					setlinewidth(side * 0.02);
					ege_line(x1, y, x3, y);
				}
			}
			setfont(number_height * 0.8, number_width * 0.8, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
			LOGFONTW FMC_font;
			getfont(&FMC_font);
			FMC_font.lfWeight = side * 3;
			setfont(&FMC_font);
			for (int i = 0;i < 11;i++) {
				double y = center_y - 165.5 / 96 * side + 0 / 10 * gap + i * gap;//底部坐标 + 偏移坐标 + 循环坐标
				double x = center_x - 5.0 / 96 * side;
				int h = datas[i] / 100;
				if (fmod(datas[10 - i], 20) == 0 && datas[10 - i] >= 30)
				{
					if (datas[10 - i] < 1000 && datas[10 - i] > -1000) {
						char str[64];
						snprintf(str, sizeof(str), "%.0f", (float)datas[10 - i]);
						ege_drawtext(str, x + side * 0.08, y);
					}
					else if (datas[10 - i] >= 1000 && datas[10 - i] <= 10000)
					{
						double x1 = center_x + 11.0 / 96 * side;
						char str[64];
						snprintf(str, sizeof(str), "%.0f", (float)datas[10 - i]);
						ege_drawtext(str, x1, y);
					}
					else
					{
						double x1 = center_x + 6.5 / 96 * side;
						char str[64];
						snprintf(str, sizeof(str), "%.0f", (float)datas[10 - i]);
						ege_drawtext(str, x1, y);
					}
				}
			}
		}
	}
	
	
	settextjustify(LEFT_TEXT, TOP_TEXT);
	number_height = side * 2.5 / 96.0 * 2 * 6.5 * 0.7;
	number_width = side * 2.5 / 96.0 * 5 * 0.7;
	setfont(number_height, number_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
}

void draw_airSpeed_10(double center_x, double center_y, double side,double speed) {
	setcolor(EGEARGB(200, 177, 177, 178));
	double y = center_y - side * 0.17;
	double x = center_x;
	double number_height = side * 2.5 / 96.0 * 2 * 6.5;
	double number_width = side * 2.5 / 96.0 * 5;
	
	
	char num[] = { '9','0','1','2','3','4','5','6','7','8','9','0'};
	char zeros[] = { '0','0','0','0','0','0','0','0','0' };
	double usefulHeight10 = fmod(speed, 10);//得到 （十 + 个）
	double uesfulHeight1 = fmod(speed, 1);//得到个位
	
	
	int num2 = usefulHeight10 / 1 ;//准确的十位;
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
	double y_100 = uesfulHeight1 / 1.0 * number_height * 0.6 + y;
	//设定字体
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setfont(number_height, number_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	//将背景颜色设置成透明
	
	setbkmode(1);
	//将区间进一步分段
	double judge = fmod(speed, 1);
	if (judge >= 0 && judge < 0.35) {
		for (int i = 0;i < 3;i++) {
			outtextxy(x + 10.0 / 96.0 * side, y_100 + number_height * 0.6 * -(i - 1), nums[i + 1]);
		}
	}
	else if (judge >= 0.35 && judge <= 0.75)
	{
		for (int i = 0;i < 4;i++) {
			outtextxy(x + 10.0 / 96.0 * side, y_100 + number_height * 0.6 * -(i - 1), nums[i + 1]);
		}
	}
	else
	{
		for (int i = 0;i < 3;i++) {
			outtextxy(x + 10.0 / 96.0 * side, y_100 + number_height * 0.6 * -(i), nums[i + 2]);
		}
	}
}

void draw_airSpeed_else(double center_x, double center_y, double side, double speed) {
	char num[] = { '9','0','1','2','3','4','5','6','7','8','9','0' };
	double y = center_y - side * 0.17;
	double number_height = side * 2.5 / 96.0 * 2 * 6.5;
	double number_width = side * 2.5 / 96.0 * 5;
	
	setfont(number_height, number_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	int hun = speed / 100;
	int ten = speed / 10;
	ten = ten % 10;
	if (speed >= 100) {
		outtextxy(center_x - number_width * 1.7, y - number_height * 0.025,num[hun + 1]);
		outtextxy(center_x - number_width * 0.5, y - number_height * 0.025, num[ten + 1]);
	}
	else {
		outtextxy(center_x - number_width * 0.5, y - number_height * 0.025, num[ten + 1]);
	}
	
}

void draw_airSpeed_shadow(double center_x, double center_y, double side) {
	double number_height = side * 2.5 / 96.0 * 2 * 6.5;
	double number_width = side * 2.5 / 96.0 * 5;
	setfillcolor(EGEARGB(0Xff, 59, 59, 59));
	double x = center_x - 24.5 / 96.0 * side;
	double y = center_y - 24.0 / 96.0 * side;
	double lenth = 48.0 / 96.0 * side;
	double width = 53.0 / 96.0 * side;
	ege_fillrect(x, y - number_height + side * 0.001, lenth * 1.02, number_height);
	ege_fillrect(x, y + width - side * 0.046, lenth * 1.02, number_height);
	
	setfillcolor(BLACK);
	ege_fillrect(x, y, lenth * 1.02, side * 0.025);
	ege_fillrect(x, y + width - side * 0.046 - side * 0.025, lenth * 1.02, side * 0.025);
	
	//draw_standy_airSpeed_wireframe(center_x, center_y, side);
	x = center_x - 24.5 / 96.0 * side;
	y = center_y - 24.0 / 96.0 * side;
	lenth = 48.0 / 96.0 * side;
	width = 53.0 / 96.0 * side;
	ege_rectangle(x, y, width, lenth);
}

void draw_airSpeed_shadow_main(double center_x, double center_y, double side) {
	double x = center_x - 24.5 / 96.0 * side;
	double y = center_y - 165.5 / 96.0 * side;
	double lenth = 331.0 / 96.0 * side;
	double width = 49.0 / 96.0 * side;
	
	double a = side * 0.44;
	setfillcolor(BLACK);
	ege_fillrect(x, y - a, width, a);
	ege_fillrect(x, y + lenth, width, a);
}

void draw_standy_airSpeed(double center_x, double center_y, double side) {
	double speed = 0;
	if (airSpeed < 30) {
		speed = 30;
	}
	else {
		speed = airSpeed;
	}
	draw_standy_airSpeed_frame(center_x, center_y, side);
	draw_standy_airSpeed_lines(center_x, center_y, side);
	
	draw_standy_airSpeed_wireframe(center_x, center_y, side);
	draw_airSpeed_10(center_x, center_y, side, speed);
	draw_airSpeed_else(center_x, center_y, side, speed);
	
	draw_airSpeed_shadow(center_x, center_y, side);
	draw_airSpeed_shadow_main(center_x, center_y, side);
}

