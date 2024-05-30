#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>

//函数声明

void draw_PFD_standby_AI(double PFD_x, double PFD_y, double PFD_side);
void draw_PFD_standby_compass();
void draw_PFD_standby_alt();
void draw_PFD_standby_airspeed();
void draw_PFD_standby_else();

//引用全局变量
extern double pitchAngle;
extern double rollAngle;
extern double sideSlipAngle;
extern double headingIndication;
extern double glideIndication;
extern double altitude;


//注意，这里的side并不是真正的边长，而只是PFD的高，PFD并非严格正方形
void draw_PFD_standby(double PFD_x, double PFD_y, double PFD_side){
	
	//绘制备用PFD姿态仪
	draw_PFD_standby_AI(PFD_x, PFD_y, PFD_side);
	
	//绘制备用PFD高度
	
}

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
	AI_pointTmp4_y = (AI_y - 0.88 * AI_side - AI_y) * cos(rollAngle) + (AI_x - 0.08 * AI_side - AI_x) * sin(rollAngle) + AI_y;
	AI_pointTmp5_x = (AI_x + 0.04 * AI_side - AI_x) * cos(rollAngle) - (AI_y - 0.88 * AI_side - AI_y) * sin(rollAngle) + AI_x;
	AI_pointTmp5_y = (AI_y - 0.88 * AI_side - AI_y) * cos(rollAngle) + (AI_x + 0.08 * AI_side - AI_x) * sin(rollAngle) + AI_y;
	
	
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
	ege_fillrect(AI_x - 1.2 * AI_r, AI_y + 1 * AI_side, 2.4 * AI_r, 1.2 * AI_r - AI_side);
	ege_fillrect(AI_x - 1.2 * AI_r, AI_y - 1.2 * AI_r, 1.32 * AI_r - AI_side , 2.4 * AI_r);
	ege_fillrect(AI_x + 0.88 * AI_side, AI_y - 1.2 * AI_r, 1.32 * AI_r - AI_side , 2.4 * AI_r);
	
	
}
