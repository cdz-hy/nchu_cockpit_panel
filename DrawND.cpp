#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>

#include "DrawFrame.h"
#include "G_variable.h"
#include "DrawScrew.h"
#include "DrawNDInfo.h"

// 目录：
/*
1.函数声明
2.变量声明
3.绘制总表的函数
4.绘制关于ND表表框的部分
5.APP+CENTER  VOR+CENTER 模式函数（第60行左右）
6.APP VOR  MAP  MAP+CENTER 模式函数（第250行左右）
7.PLN PLN+CENTER 模式函数 (第500行左右)
*/


// 函数声明
void draw_smallCircle(double x, double y, double r);
void draw_ND_app_center(double center_x, double center_y, double side);//
void draw_acr(double center_x, double center_y, double side);
void draw_map_scale(double center_x, double center_y, double side);
void draw_ndtext(double center_x, double center_y, double side);
void draw_ndpoint(double center_x, double center_y, double side);
void draw_ndcenterangle(double center_x, double center_y, double side);
void draw_ndtoptriangle(double center_x, double center_y, double side);
void draw_ndtoprectangle(double center_x, double center_y, double side);
void draw_ndtoptext(double center_x, double center_y, double side);
void draw_ND_map(double center_x, double center_y, double side);//
void draw_ND_pln(double center_x, double center_y, double side);//
void draw_ND_frame_chassis(double center_x, double center_y, double side);//
void draw_ND_smallWhiteCircle(double center_x, double center_y, double side);


// 变量声明
//APP+CENTER  VOR+CENTER 模式:
double realrotationAngle = 0;
double pointrationAngle = 0;// 小剑的对应角度
extern int HDGMAG;
extern double rotationangle;// 用于传入用
//APP VOR  MAP  MAP+CENTER 模式
double realrotationangle2 = 0;//实际的旋转角度
int ndcourse = 0;
extern double rotationangle;//表盘刻度的旋转角度
extern double ndtoprotationangle;//顶部三角形的偏转角度
//PLN PLN+CENTER 模式
//暂无



//==================================以下为绘制总表部分========================================//
void draw_ND(double ND_x, double ND_y, double ND_side)  {
	
	draw_ND_frame_chassis(ND_x, ND_y, ND_side);
	
	if(MINSRef = 55) {
		
	}
	if(MINSRef = 125) {
		
	}
	
	if(baroUnit = 55) {
		
	}
	if(baroUnit = 125) {
		
	}
	
	if(VOR1 == 1){
		
	}
	if(VOR2 == 1){
		
	}	
	
	if(CTR == 0){
		if(EHSIMode == 55 || EHSIMode == 80 || EHSIMode == 110){
			
			draw_ND_map(ND_x, ND_y + ND_side * 32 / 104, ND_side);
			
		}else if(EHSIMode == 135){
			
			draw_ND_pln(ND_x, ND_y, ND_side);
			
		}
	}else if(CTR == 1){
		if(EHSIMode == 55 || EHSIMode == 80){
			
			draw_ND_app_center(ND_x, ND_y, ND_side);
			
		}else if(EHSIMode == 110){
			
			draw_ND_map(ND_x, ND_y + ND_side * 32 / 104, ND_side);
			
		}else if(EHSIMode == 135){
			
			draw_ND_pln(ND_x , ND_y, ND_side);
			
		}
	}
	
	
	setbkmode(TRANSPARENT);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setfont(ND_side/ 35, 0, "黑体");
	setcolor(EGEARGB(180, 100, 149, 237));
	
	if(ARPT == 1) {
		ege_drawtext("ARPT", ND_x - ND_side / 2.21,ND_y + ND_side / 6);
	}
	if(WPT == 1) {
		ege_drawtext("WPT", ND_x - ND_side / 2.18,ND_y + ND_side / 5.1);
	}
	if(STA == 1) {
		ege_drawtext("STA", ND_x - ND_side / 2.18,ND_y + ND_side / 4.5);
	}
	
	setfont(ND_side/ 30, 0, "黑体");
	if(WXR == 1) {
		ege_drawtext("WXR", ND_x - ND_side / 2.2,ND_y + ND_side / 4);
	}
	
	if(DATA == 1){
		
	}
	if(POS == 1) {
		
	}
	if(TERR == 1) {
		
	}
	
	
	draw_PFD_frame(ND_x, ND_y, ND_side);
	
	draw_ND_smallWhiteCircle(ND_x - ND_side / 2.4, ND_y +  ND_side / 1.72, ND_side / 22);
	
	draw_screw3(ND_x + ND_side / 2, ND_y +  ND_side / 1.668,ND_side / 22, 45);
}

//==========================================================================================//
/*
关于2*4=8种模式下的说明
对应旋钮的从左至右有：
APP APP+CENTER
VOR VOR+CENTER
MAP MAP+CENTER
PLN PLN+CENTER

其中:
APP+CENTER  VOR+CENTER 是一种模式
APP VOR  MAP  MAP+CENTER 这四个是一种模式
PLN PLN+CENTER 是一种模式
*/

//===============================关于表框的部分==================================//

// 绘制表框黑色底盘
void draw_ND_frame_chassis(double center_x, double center_y, double side){
	setfillcolor(BLACK);
	ege_fillrect(center_x - side * 1.1 /2,center_y - side * 1.1 /2,side*1.1,side*1.1);
}

// 绘制表框下部白色的小圆球
void draw_ND_smallWhiteCircle(double center_x, double center_y, double side){
	setfillcolor(EGEARGB(0xff,79,79,75));
	ege_fillellipse(center_x - side / 2,center_y - side /2,side,side);
}

//================================APP+CENTER  VOR+CENTER 模式==================================//

void draw_smallCircle(double x, double y, double r) {
	setfillcolor(WHITE);
	ege_ellipse(x + r * 0.45 * cos(-(pointrationAngle + realrotationAngle) * PI / 180) - r * 0.025, 
		y - r * 0.025 - r * 0.45 * sin(-(pointrationAngle + realrotationAngle) * PI / 180), r * 0.05, r * 0.05);
	ege_ellipse(x - r * 0.45 * cos(-(pointrationAngle + realrotationAngle) * PI / 180) - r * 0.025, 
		y - r * 0.025 + r * 0.45 * sin(-(pointrationAngle + realrotationAngle) * PI / 180), r * 0.05, r * 0.05);
	ege_ellipse(x + r * 0.25 * cos(-(pointrationAngle + realrotationAngle) * PI / 180) - r * 0.025, 
		y - r * 0.025 - r * 0.25 * sin(-(pointrationAngle + realrotationAngle) * PI / 180), r * 0.05, r * 0.05);
	ege_ellipse(x - r * 0.25 * cos(-(pointrationAngle + realrotationAngle) * PI / 180) - r * 0.025, 
		y - r * 0.025 + r * 0.25 * sin(-(pointrationAngle + realrotationAngle) * PI / 180), r * 0.05, r * 0.05);
}

void draw_ND_app_center(double center_x, double center_y, double side) {
	
	// 初始数据设置
	double r = side / 115 * 37.5;
	realrotationAngle = 360 - rotationangle;
	setcolor(EGEARGB(200, 177, 177, 178));
	
	// 长长刻度
	setlinewidth(side / 250);
	for (double i = 45; i < 360; i += 45)
	{	// 长长刻度对应比例： (1- 2/37.5)
		double scaleAngle = 0 + i;
		double rad = scaleAngle * PI / 180.0;
		ege_line(center_x + 1.15 *r * sin(rad), center_y - 1.15*r * cos(rad), center_x + 0.98* r * sin(rad), center_y - 0.98 * r * cos(rad));
	}
	//长刻度
	setlinewidth(side / 250);// 这是对长刻度的粗细设定
	for (double i = 0; i < 360; i += 10)
	{	// 长刻度对应比例：(1- 5/37.5)
		double scaleAngle = realrotationAngle + i;
		double rad = scaleAngle * PI / 180.0;
		ege_line(center_x + r * sin(rad), center_y - r * cos(rad), center_x + (1- 5/37.5)* r * sin(rad), center_y - (1 - 5 / 37.5) * r * cos(rad));
	}
	//短刻度
	setlinewidth(side/ 280);// 这是对短刻度的粗细设定
	for (double i = 5; i < 360; i += 10)
	{	// 短刻度对应比例： (1- 2/37.5)
		double scaleAngle = realrotationAngle + i;
		double rad = scaleAngle * PI / 180.0;
		ege_line(center_x + r * sin(rad), center_y - r * cos(rad), center_x + (1 - 2 / 37.5) * r * sin(rad), center_y - (1 - 2 / 37.5) * r * cos(rad));
	}
	// 上下两个长刻度
	ege_line(center_x,center_y - r,
		center_x, center_y - (1 - 19/37.5)*r
		);
	ege_line(center_x, center_y + r,
		center_x, center_y + (1 - 19 / 37.5) * r
		);
	ege_line(center_x - r / 32,center_y - (1 - 12 / 37.5) * r,
		center_x + r / 32, center_y - (1 - 12 / 37.5) * r );
	ege_line(center_x - r / 32, center_y + (1 - 12 / 37.5) * r,
		center_x + r / 32, center_y + (1 - 12 / 37.5) * r);
	
	// 旋转数字绘制
	for (int i = 0; i < 360; i += 30) {
		double textAngle = realrotationAngle + i;
		double rad = textAngle * PI / 180.0;
		double textPosX = center_x + 0.75 * r * sin(rad);//*0.85是调节数字与中心坐标位置的关系，依据自己的位置条件适当修改，如可能在你的表上*0.7是恰好在需要的位置上，则改为*0.7
		double textPosY = center_y - 0.75 * r * cos(rad);
		
		LOGFONTW font;
		setfont(side/ 23.3333333333, 0, "黑体");
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		getfont(&font);
		font.lfEscapement = -textAngle * 10;
		font.lfWeight = 550;
		setfont(&font);
# if 0
		//xyprintf(x + 0.8 * r * cos(rad), y - 0.8 * r * sin(rad), "%d", i);//忽略此行，如不放心，可将前面*的数字改为上面注释位置修改的数-0.05，如上面的数字是*0.7，则此处改为*0.65
# endif
		char strBuffer[64];
		sprintf_s(strBuffer, "%d", i / 10);
		ege_drawtext(strBuffer, textPosX, textPosY);
	}
	
	// 上面小三角形
	ege_point points1 [4] = {
		center_x - side / 85, center_y - r / 0.91,// 左上
		center_x + side / 85,center_y - r / 0.91,// 右上
		center_x,center_y - r / 0.97,// 下
		center_x - side / 85,center_y - r / 0.91
	};
	ege_drawpoly(4,points1);
	
	// 小三角形上面的3条线
	ege_point points2[4] = {
		center_x - side / 19, center_y - r / 0.8,// 左上
		center_x - side / 19, center_y - r / 0.91,// 左下
		center_x + side / 19, center_y - r / 0.91,// 右下
		center_x + side / 19, center_y - r / 0.8// 右上
	};
	ege_drawpoly(4, points2);
	
	// 上面数字显示
	setbkmode(TRANSPARENT);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setfont(side / 19, 0, "黑体");// 这是对数字的大小的设置
	char ch[64];
	sprintf(ch, "%03d", HDGMAG);
	ege_drawtext(ch, center_x, center_y - r / 0.85);
	
	setcolor(EGEARGB(250, 76, 153, 0));// 这是对两边字体的颜色设置绿色
	setfont(side / 25, 0, "黑体");// 这是对字体的大小设置
	ege_drawtext("HDG", center_x - r / 3.5,center_y - r / 0.85);
	ege_drawtext("MAG", center_x + r / 3.5, center_y - r / 0.85);
	
	// 北字绘制
	setlinewidth(side / 250);
	setcolor(EGEARGB(200, 177, 177, 178));
	ege_line(center_x-r/16,center_y - r/7,
		center_x - r / 16, center_y + r / 7);
	ege_line(center_x + r / 16, center_y - r / 7,
		center_x + r / 16, center_y + r / 7);
	ege_line(center_x - r / 16, center_y,
		center_x - r / 5, center_y);
	ege_line(center_x + r / 16, center_y,
		center_x + r / 5, center_y);
	ege_line(center_x - r / 16, center_y + r / 7,
		center_x - r / 8, center_y + r / 7);
	ege_line(center_x + r / 16, center_y + r / 7,
		center_x + r / 8, center_y + r / 7);
	
	// 四个小圆绘制
	draw_smallCircle(center_x,center_y,r);
	
	
	setlinewidth(side / 250);
	setcolor(EGEARGB(200, 177, 177, 178));
	
	double rad = -(pointrationAngle + rotationangle) * PI / 180;
	
	ege_point points3[14] = {
		//center_x - r / 30,center_y - r / 2.9,// 1 
		-r / 30 * cos(rad) - (-r / 2.9) * sin(rad) + center_x, (-r / 2.9) * cos(rad) + (-r / 30) * sin(rad) + center_y,
		//center_x - r / 30,center_y - r / 2.55,//2 
		-r / 30 * cos(rad) - (-r / 2.55) * sin(rad) + center_x, (-r / 2.55) * cos(rad) + (-r / 30) * sin(rad) + center_y,
		//center_x - r / 13,center_y - r / 2.55,//3 
		-r / 13 * cos(rad) - (-r / 2.55) * sin(rad) + center_x, (-r / 2.55) * cos(rad) + (-r / 13) * sin(rad) + center_y,
		//center_x - r / 13,center_y - r / 2.2,//4 
		-r / 13 * cos(rad) - (-r / 2.2) * sin(rad) + center_x, (-r / 2.2) * cos(rad) + (-r / 13) * sin(rad) + center_y,
		//center_x - r / 30,center_y - r / 2.2,//5 
		-r / 30 * cos(rad) - (-r / 2.2) * sin(rad) + center_x, (-r / 2.2) * cos(rad) + (-r / 30) * sin(rad) + center_y,
		//center_x - r / 30,center_y - r / 1.12,//6 
		-r / 30 * cos(rad) - (-r / 1.12) * sin(rad) + center_x, (-r / 1.12) * cos(rad) + (-r / 30) * sin(rad) + center_y,
		//center_x , center_y - r / 1.08,//7 
		r / 1.08 * sin(rad) + center_x, -r / 1.08 * cos(rad) + center_y,
		//center_x + r / 30,center_y - r / 1.12,//8 
		r / 30 * cos(rad) - (-r / 1.12) * sin(rad) + center_x, (-r / 1.12) * cos(rad) + r / 30 * sin(rad) + center_y,
		//center_x + r / 30,center_y - r / 2.2,//9 
		r / 30 * cos(rad) - (-r / 2.2) * sin(rad) + center_x, (-r / 2.2) * cos(rad) + r / 30 * sin(rad) + center_y,
		//center_x + r / 13,center_y - r / 2.2,//10 
		r / 13 * cos(rad) - (-r / 2.2) * sin(rad) + center_x, (-r / 2.2) * cos(rad) + r / 13 * sin(rad) + center_y,
		//center_x + r / 13,center_y - r / 2.55,//11 
		r / 13 * cos(rad) - (-r / 2.55) * sin(rad) + center_x, (-r / 2.55) * cos(rad) + r / 13 * sin(rad) + center_y,
		//center_x + r / 30,center_y - r / 2.55,//12 
		r / 30 * cos(rad) - (-r / 2.55) * sin(rad) + center_x, (-r / 2.55) * cos(rad) + r / 30 * sin(rad) + center_y,
		//center_x + r / 30,center_y - r / 2.9,//13 
		r / 30 * cos(rad) - (-r / 2.9) * sin(rad) + center_x, (-r / 2.9) * cos(rad) + r / 30 * sin(rad) + center_y,
		//center_x - r / 30,center_y - r / 2.9//1 
		-r / 30 * cos(rad) - (-r / 2.9) * sin(rad) + center_x, (-r / 2.9) * cos(rad) + (-r / 30) * sin(rad) + center_y,
	};
	ege_drawpoly(14, points3);
	
	ege_point points4[6] = {
		//center_x - r / 30,center_y + r / 2.9,// 1 
		-r / 30 * cos(rad) - (r / 2.9) * sin(rad) + center_x, (r / 2.9) * cos(rad) + (-r / 30) * sin(rad) + center_y,
		//center_x + r / 30,center_y + r / 2.9,//2 
		r / 30 * cos(rad) - (r / 2.9) * sin(rad) + center_x, (r / 2.9) * cos(rad) + (r / 30) * sin(rad) + center_y,
		//center_x + r / 30,center_y + r / 1.12,//3 
		r / 30 * cos(rad) - (r / 1.12) * sin(rad) + center_x, (r / 1.12) * cos(rad) + (r / 30) * sin(rad) + center_y,
		//center_x , center_y + r / 1.08,//4 
		-r / 1.08 * sin(rad) + center_x, r / 1.08 * cos(rad) + center_y,
		//center_x - r / 30,center_y + r / 1.12,//5 
		-r / 30 * cos(rad) - (r / 1.12) * sin(rad) + center_x, (r / 1.12) * cos(rad) + (-r / 30) * sin(rad) + center_y,
		//center_x - r / 30,center_y + r / 2.9//1 
		-r / 30 * cos(rad) - (r / 2.9) * sin(rad) + center_x, (r / 2.9) * cos(rad) + (-r / 30) * sin(rad) + center_y,
	};
	ege_drawpoly(6, points4);
}


//================================APP VOR  MAP  MAP+CENTER 模式==================================//

//画刻度盘上的弧线
void draw_acr(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径
	
	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽
	
	ege_arc(center_x - r, center_y - r, r * 2, r * 2, -44.0, -92.0);
}

//画刻度
void draw_map_scale(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径
	
	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽
	
	//短刻度
	for (int i = 5; i < 360; i += 10)
	{
		double scaleAngle = realrotationangle2 + i;
		double rad = scaleAngle * PI / 180.0;
		double scalePosX = center_x + 0.975 * r * sin(rad);
		double scalePosY = center_y - 0.975 * r * cos(rad);
		
		if (scalePosX >= center_x - r * sin(55 * PI / 180) && scalePosX <= center_x + r * sin(55 * PI / 180) && scalePosY <= center_y - r * cos(55 * PI / 180) && scalePosY >= center_y - r) //判断文字是否在输出区域内，在区域内则输出，不在区域内则不输出
			ege_line(center_x + r * sin(rad), center_y - r * cos(rad), center_x + 0.975 * r * sin(rad), center_y - 0.975 * r * cos(rad));
	}
	
	//长刻度
	for (int i = 0; i < 360; i += 10)
	{
		double scaleAngle = realrotationangle2 + i;
		double rad = scaleAngle * PI / 180.0;
		double scalePosX = center_x + 0.975 * r * sin(rad);
		double scalePosY = center_y - 0.975 * r * cos(rad);
		
		if (scalePosX >= center_x - r * sin(55 * PI / 180) && scalePosX <= center_x + r * sin(55 * PI / 180) && scalePosY <= center_y - r * cos(55 * PI / 180) && scalePosY >= center_y - r) //判断文字是否在输出区域内，在区域内则输出，不在区域内则不输出
			ege_line(center_x + r * sin(rad), center_y - r * cos(rad), center_x + 0.96 * r * sin(rad), center_y - 0.96 * r * cos(rad));
	}
}

//画刻度值
void draw_ndtext(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径
	
	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽
	
	for (int i = 0; i < 360; i += 30) //循环输出表上的刻度值
	{
		double textAngle = realrotationangle2 + i;
		double rad = textAngle * PI / 180.0;
		double textPosX = center_x + 0.92 * r * sin(rad);
		double textPosY = center_y - 0.92 * r * cos(rad);
		
		//设置文字的格式
		LOGFONTW font;
		setcolor(EGEARGB(0x99, 0xff, 0xff, 0xff));
		setfont(r * 0.09, 0, "Leelawadee");
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		getfont(&font);
		font.lfEscapement = -textAngle * 10;
		font.lfWeight = 500;
		setfont(&font);
#if 0
		xyprintf(compass_x + 0.8 * compass_r * cos(rad), compass_y - 0.8 * compass_r * sin(rad), "%d", i);
#endif
		if (textPosX >= center_x - r * sin(50 * PI / 180) && textPosX <= center_x + r * sin(55 * PI / 180) && textPosY <= center_y - r * cos(55 * PI / 180) && textPosY >= center_y - r) //判断文字是否在输出区域内，在区域内则输出，不在区域内则不输出
		{
			char strBuffer[64];
			sprintf_s(strBuffer, "%d", i / 10);
			ege_drawtext(strBuffer, textPosX, textPosY);
		}
	}
}

//画指向航向的固定指针
void draw_ndpoint(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径
	
	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽
	
	//画出指针
	ege_line(center_x, center_y, center_x, center_y - r);
	ege_line(center_x - r * 0.02, center_y - r / 4, center_x + r * 0.02, center_y - r / 4);
	ege_line(center_x - r * 0.02, center_y - r / 2, center_x + r * 0.02, center_y - r / 2);
	ege_line(center_x - r * 0.02, center_y - r * 3 / 4, center_x + r * 0.02, center_y - r * 3 / 4);
}

//画表中间的一个三角形
void draw_ndcenterangle(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径
	
	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽
	
	//画表中间的一个三角形
	ege_point centerangle[4];
	
	centerangle[0].x = center_x;
	centerangle[0].y = center_y;
	
	centerangle[1].x = center_x - side * 3.5 / 104;
	centerangle[1].y = center_y + side * 8 / 104;
	
	centerangle[2].x = center_x + side * 3.5 / 104;
	centerangle[2].y = center_y + side * 8 / 104;
	
	centerangle[3].x = center_x;
	centerangle[3].y = center_y;
	
	ege_drawpoly(4, centerangle);
}

//画顶部会移动的三角形
void draw_ndtoptriangle(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径
	
	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽
	
	double rad = ndtoprotationangle * PI / 180;//将旋转角度化成弧度制
	
	//画顶部会移动的三角形
	ege_point toptriangle[4];
	
	toptriangle[0].x = r * sin(rad) + center_x;
	toptriangle[0].y = -r * cos(rad) + center_y;
	
	toptriangle[1].x = -side * 2 / 104 * cos(rad) + (r + side * 3 / 104) * sin(rad) + center_x;
	toptriangle[1].y = (-r - side * 3 / 104) * cos(rad) - side * 2 / 104 * sin(rad) + center_y;
	
	toptriangle[2].x = side * 2 / 104 * cos(rad) + (r + side * 3 / 104) * sin(rad) + center_x;
	toptriangle[2].y = (-r - side * 3 / 104) * cos(rad) + side * 2 / 104 * sin(rad) + center_y;
	
	toptriangle[3].x = r * sin(rad) + center_x;
	toptriangle[3].y = -r * cos(rad) + center_y;
	
	ege_drawpoly(4, toptriangle);
}

//画顶部不闭合的矩形
void draw_ndtoprectangle(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径
	
	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽
	
	//画顶部不闭合的矩形
	ege_point toprectangle[4];
	
	toprectangle[0].x = center_x - 6.5 * side / 104;
	toprectangle[0].y = center_y - r - 9 * side / 104;
	
	toprectangle[1].x = center_x - 6.5 * side / 104;
	toprectangle[1].y = center_y - r - 3 * side / 104;
	
	toprectangle[2].x = center_x + 6.5 * side / 104;
	toprectangle[2].y = center_y - r - 3 * side / 104;
	
	toprectangle[3].x = center_x + 6.5 * side / 104;
	toprectangle[3].y = center_y - r - 9 * side / 104;
	
	ege_drawpoly(4, toprectangle);
}

//画顶部显示的文字内容
void draw_ndtoptext(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径
	
	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽
	
	//顶部中间的数字显示
	LOGFONTW font;
	setfont(r * 0.09, 0, "Leelawadee");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font);
	font.lfEscapement = 0;
	font.lfWeight = 550;
	setfont(&font);
	
	char stringBuffer[64];
	sprintf_s(stringBuffer, "%03d", ndcourse);
	ege_drawtext(stringBuffer, center_x, center_y - r - side * 6 / 104);
	
	//顶部左边的字母显示
	setfont(r * 0.07, 0, "Leelawadee");
	setcolor(EGEARGB(0x99, 0x75, 0xf9, 0x4d));
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font);
	font.lfEscapement = 0;
	font.lfWeight = 550;
	setfont(&font);
	ege_drawtext("TRK", center_x - side * 11 / 104, center_y - r - side * 6 / 104);
	
	//顶部右边的字母显示
	setfont(r * 0.07, 0, "Leelawadee");
	setcolor(EGEARGB(0x99, 0x75, 0xf9, 0x4d));
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font);
	font.lfEscapement = 0;
	font.lfWeight = 550;
	setfont(&font);
	ege_drawtext("MAG", center_x + side * 12 / 104, center_y - r - side * 6 / 104);
}

//画MAP模式下的ND表
void draw_ND_map(double center_x, double center_y, double side)
{

	realrotationangle2 = 360 - rotationangle;
	
	draw_acr(center_x, center_y, side);
	
	draw_map_scale(center_x, center_y, side);
	
	draw_ndtext(center_x, center_y, side);
	
	draw_ndpoint(center_x, center_y, side);
	
	draw_ndcenterangle(center_x, center_y, side);
	
	draw_ndtoptriangle(center_x, center_y, side);
	
	draw_ndtoprectangle(center_x, center_y, side);
	
	draw_ndtoptext(center_x, center_y, side);
}


//================================PLN PLN+CENTER 模式==================================//

void draw_ND_pln(double center_x, double center_y, double side) {
	
	side = side / 2;
	
	double small_r = side / 104 * 40;// 确定大圆小圆的半径
	double big_r = side / 104 * 80;
	
	setlinewidth(side / 125);// 这是圆弧线的线宽设置
	setcolor(EGEARGB(150, 177, 177, 178));// 这是对于线的颜色的设置,与数字颜色的设置（白色）
	ege_arc(center_x - small_r, center_y - small_r,
		small_r * 2, small_r * 2,
		97, 166);
	/*
	数据怎么算的:
	97是比90多了多少度，166是180-7*2得来的——这个多少度越大，圆弧就越短
	-83是90减去多的度数，再加个负号
	*/
	
	ege_arc(center_x - small_r, center_y - small_r,
		small_r * 2, small_r * 2,
		-83, 166);
	
	ege_arc(center_x - big_r, center_y - big_r,
		big_r * 2, big_r * 2,
		94, 172);
	
	ege_arc(center_x - big_r, center_y - big_r,
		big_r * 2, big_r * 2,
		-86, 172);
	
	// 数字显示与WSNE显示
	setbkmode(TRANSPARENT);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setfont(side / 16.666666, 0, "黑体");// 这是对数字的大小的设置
	char ch[64];
	sprintf_s(ch, "%d", 20);// 上20输出
	ege_drawtext(ch, center_x, center_y - small_r / 1.01);
	sprintf_s(ch, "%d", 20);// 下20输出
	ege_drawtext(ch, center_x, center_y + small_r / 0.99);
	sprintf_s(ch, "%d", 40);// 上40输出
	ege_drawtext(ch, center_x, center_y - big_r / 1.01);
	sprintf_s(ch, "%d", 40);// 下40输出
	ege_drawtext(ch, center_x, center_y + big_r / 0.99);
	/*
	* 上面的加减是40,20输出的位置坐标
	*/
	setcolor(EGEARGB(250, 76, 153, 0));// 这是对NSME以及箭头颜色的设置（绿色）
	setfont(side / 12.5, 0, "黑体");// 这是对WSNE的大小的设置
	ege_drawtext("N", center_x - side / 33.3333, center_y - big_r / 0.9); // side / 33.3333是N向左偏移的位置
	ege_drawtext("S", center_x, center_y + big_r / 0.9);
	ege_drawtext("W", center_x - big_r / 0.9, center_y);
	ege_drawtext("E", center_x + big_r / 0.9, center_y);
	
	setlinewidth(side / 160);// 这是对绘制箭头线的粗细设定
	ege_line(center_x + side / 34, center_y - big_r / 0.93,// 第一个坐标是靠下的,第二个坐标是靠上的
		center_x + side / 34, center_y - big_r / 0.87);
	ege_line(center_x + side / 34, center_y - big_r / 0.87,// 第一个坐标是靠上的,第二个坐标是靠左的
		center_x + side / 85, center_y - big_r / 0.89);
	ege_line(center_x + side / 34, center_y - big_r / 0.87,// 第一个坐标是靠上的,第二个坐标是靠右的
		center_x + side / 22, center_y - big_r / 0.89);
}
