#include <graphics.h>
#include <math.h>
#include<stdio.h>

extern double rotationangle;// 用于传入用
double realrotationangle = 0;
double pointrtationangle = 0;// 小剑的对应角度
extern int HDGMAG;// 这个参数你应该没设

void draw_smallCircle(double x, double y, double r) {
	setfillcolor(WHITE);
	ege_ellipse(x + r * 0.45 * cos(-(pointrtationangle + realrotationangle) * PI / 180) - r * 0.025, 
		y - r * 0.025 - r * 0.3 * sin(-(pointrtationangle + realrotationangle) * PI / 180), r * 0.05, r * 0.05);
	ege_ellipse(x - r * 0.45 * cos(-(pointrtationangle + realrotationangle) * PI / 180) - r * 0.025,
		y - r * 0.025 + r * 0.3 * sin(-(pointrtationangle + realrotationangle) * PI / 180), r * 0.05, r * 0.05);
	ege_ellipse(x + r * 0.25 * cos(-(pointrtationangle + realrotationangle) * PI / 180) - r * 0.025, 
		y - r * 0.025 - r * 0.6 * sin(-(pointrtationangle + realrotationangle) * PI / 180), r * 0.05, r * 0.05);
	ege_ellipse(x - r * 0.25 * cos(-(pointrtationangle + realrotationangle) * PI / 180) - r * 0.025, 
		y - r * 0.025 + r * 0.6 * sin(-(pointrtationangle + realrotationangle) * PI / 180), r * 0.05, r * 0.05);
}

void draw_ND_app_center(double center_x, double center_y, double side) {
	
	// 初始数据设置
	double r = side / 115 * 37.5;
	realrotationangle = 360 - rotationangle;
	setcolor(EGEARGB(200, 177, 177, 178));
	
	// 长长刻度
	setlinewidth(side / 250);
	for (double i = 45; i < 360; i += 45)
	{	// 短刻度对应比例： (1- 2/37.5)
		double scaleAngle = 0 + i;
		double rad = scaleAngle * PI / 180.0;
		ege_line(center_x + 1.15 *r * sin(rad), center_y - 1.15*r * cos(rad), center_x + 0.98* r * sin(rad), center_y - 0.98 * r * cos(rad));
	}
	//长刻度
	setlinewidth(side / 250);// 这是对长刻度的粗细设定
	for (double i = 0; i < 360; i += 10)
	{	// 长刻度对应比例：(1- 5/37.5)
		double scaleAngle = realrotationangle + i;
		double rad = scaleAngle * PI / 180.0;
		ege_line(center_x + r * sin(rad), center_y - r * cos(rad), center_x + (1- 5/37.5)* r * sin(rad), center_y - (1 - 5 / 37.5) * r * cos(rad));
	}
	//短刻度
	setlinewidth(side/ 280);// 这是对短刻度的粗细设定
	for (double i = 5; i < 360; i += 10)
	{	// 短刻度对应比例： (1- 2/37.5)
		double scaleAngle = realrotationangle + i;
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
		double textAngle = realrotationangle + i;
		double rad = textAngle * PI / 180.0;
		double textPosX = center_x + 0.75 * r * sin(rad);//*0.85是调节数字与中心坐标位置的关系，依据自己的位置条件适当修改，如可能在你的表上*0.7是恰好在需要的位置上，则改为*0.7
		double textPosY = center_y - 0.75 * r * cos(rad);
		
		LOGFONTW font;
		setfont(30, 0, "黑体");
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
	ege_point points3[14] = {
		center_x - r / 30,center_y-r / 2.9,// 1
		center_x - r / 30,center_y - r / 2.55,//2
		center_x - r / 13,center_y - r / 2.55,//3
		center_x - r / 13,center_y - r / 2.2,//4
		center_x - r / 30,center_y - r / 2.2,//5
		center_x - r / 30,center_y - r / 1.12,//6
		center_x , center_y - r / 1.08,//7
		center_x + r / 30,center_y - r / 1.12,//8
		center_x + r / 30,center_y - r / 2.2,//9
		center_x + r / 13,center_y - r / 2.2,//10
		center_x + r / 13,center_y - r / 2.55,//11
		center_x + r / 30,center_y - r / 2.55,// 12
		center_x + r / 30,center_y - r / 2.9,// 13
		center_x - r / 30,center_y - r / 2.9//1
	};
	ege_drawpoly(14, points3);
	
	ege_point points4[6] = {
		center_x - r / 30,center_y + r / 2.9,// 1
		center_x + r / 30,center_y + r / 2.9,//2
		center_x + r / 30,center_y + r / 1.12,//3
		center_x , center_y + r / 1.08,//4
		center_x - r / 30,center_y + r / 1.12,//5
		center_x - r / 30,center_y + r / 2.9//1
	};
	ege_drawpoly(6, points4);
}
