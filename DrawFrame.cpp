#include<graphics.h>
#include<math.h>

void draw_frame(double center_x, double center_y, double side) {
	// 注意！这里的side并不是边框边长，而是中间圆的半径，两者14：13
	// 为了解决以上问题，在传参时就已经处理为中间圆半径了（*13/14）
	
	double lefttop_x = center_x - side / 2.0;
	double lefttop_y = center_y - side / 2.0;
	//这是内圈圆的半径！
	double R = side / 52.0 * 25;
	double R1 = side / 2;
	
	setcolor(EGEARGB(0X4F, 0X00, 0X00, 0X00));
	setlinewidth(5);
	int RCDI_num_points_frame_edge = 16;
	ege_point RCDI_polypoints_frame_edge[16] = { {lefttop_x + side / 26 * 3,lefttop_y - side / 26},{lefttop_x - side / 26 ,lefttop_y + side / 26 * 3},
		
		{lefttop_x - side / 26 ,lefttop_y + side / 26 * 3},{lefttop_x - side / 26 ,lefttop_y + side / 26 * 3},
		
		{lefttop_x - side / 26,lefttop_y + side - side / 26 * 3},{lefttop_x - side / 26,lefttop_y + side - side / 26 * 3},
		
		{lefttop_x - side / 26,lefttop_y + side - side / 26 * 3},{lefttop_x + side / 26 * 3,lefttop_y + side + side / 26},
		
		
		{lefttop_x + side / 26 * 3,lefttop_y + side + side / 26},{lefttop_x + side / 26 * 3,lefttop_y + side + side / 26},
		
		{lefttop_x + side - side / 26 * 3,lefttop_y + side + side / 26},{lefttop_x + side - side / 26 * 3,lefttop_y + side + side / 26},
		
		{lefttop_x + side - side / 26 * 3,lefttop_y + side + side / 26},{lefttop_x + side + side / 26,lefttop_y + side - side / 26 * 3},
		
		{lefttop_x + side + side / 26,lefttop_y + side - side / 26 * 3},{lefttop_x + side + side / 26,lefttop_y + side - side / 26 * 3}
		
		
	};
	ege_bezier(RCDI_num_points_frame_edge, RCDI_polypoints_frame_edge);
	
	
	int num_points2 = 4;
	ege_point polypoints2[4] = {
		//{lefttop_x - side / 26 + side / 250,lefttop_y + side / 26 * 3 - side / 250} ,
		{lefttop_x + side / 26 * 3 + side / 250,lefttop_y - side / 26 - side / 250},
		{lefttop_x + side - side / 26 * 3 + side / 250,lefttop_y - side / 26 - side / 250},
		{lefttop_x + side + side / 26 + side / 250,lefttop_y + side / 26 * 3 - side / 250} ,
		{lefttop_x + side + side / 26 + side / 250,lefttop_y + side - side / 26 * 3 - side / 250}
	};
	
	ege_setpattern_lineargradient(lefttop_x + side / 26 * 3 + side / 250, lefttop_y - side / 26 - side / 250, EGEARGB(0X6F, 0XFF, 0XFF, 0XFF),
		lefttop_x + side + side / 26 + side / 250, lefttop_y + side - side / 26 * 3 - side / 250, EGEARGB(0X2F, 0XFF, 0XFF, 0XFF));
	ege_fillpoly(num_points2, polypoints2);
	ege_setpattern_none();
	
	
	// 边框颜色
	int num_points3 = 8;
	ege_point polypoints3[8] = {
		{lefttop_x - side / 26 ,lefttop_y + side / 26 * 3},
		{lefttop_x + side / 26 * 3,lefttop_y - side / 26},
		{lefttop_x + side - side / 26 * 3,lefttop_y - side / 26},
		{lefttop_x + side + side / 26,lefttop_y + side / 26 * 3},
		{lefttop_x + side + side / 26,lefttop_y + side - side / 26 * 3},
		{lefttop_x + side - side / 26 * 3,lefttop_y + side + side / 26},
		{lefttop_x + side / 26 * 3,lefttop_y + side + side / 26},
		{lefttop_x - side / 26,lefttop_y + side - side / 26 * 3}
	};
	ege_setpattern_lineargradient(lefttop_x + side + side / 26, lefttop_y + side / 26 * 3, EGEARGB(0XFF, 0X1F, 0X23, 0X2C),
		lefttop_x - side / 26, lefttop_y + side - side / 26 * 3, EGEARGB(0XFF, 0X17, 0X1A, 0X20));
	ege_fillpoly(num_points3, polypoints3);
	ege_setpattern_none();
	
	// 表盘阴影
	ege_setpattern_lineargradient(center_x + R1 * cos(PI / 4), center_y - R1 * sin(PI / 4), EGEARGB(0XFF, 0X00, 0X00, 0X00),
		center_x - R1 * cos(PI / 4), center_y + R1 * sin(PI / 4), EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillellipse(lefttop_x, lefttop_y, side, side);
	ege_setpattern_none();
	
	// 表盘颜色
	ege_setpattern_lineargradient(center_x + R * cos(PI / 4), center_y - R * sin(PI / 4), EGEARGB(0XFF, 0X15, 0X15, 0X15),
		center_x - R * cos(PI / 4), center_y + R * sin(PI / 4), EGEARGB(0XFF, 0X10, 0X10, 0X10));
	
	ege_fillellipse(lefttop_x + side / 52, lefttop_y + side / 52, side - side / 26, side - side / 26);
	ege_setpattern_none();
	
}
