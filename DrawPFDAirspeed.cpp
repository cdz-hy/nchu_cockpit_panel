#include <graphics.h>
#include <math.h>
#include<stdio.h>

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
