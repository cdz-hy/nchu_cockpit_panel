void draw_ND_pln(double center_x, double center_y, double side) {
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