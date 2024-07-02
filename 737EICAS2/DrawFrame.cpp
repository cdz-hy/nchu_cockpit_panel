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


void draw_PFD_frame(double PFDframe_x, double PFDframe_y, double side) {
	
	double Ulength = side / 96;
	double linewidth = side / 96 * 2;
	
	
	ege_enable_aa(false);
	
	
	setcolor(EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	setlinewidth(linewidth);
	int Frame_num3 = 13;//最外层
	ege_point Frame_ploypoints3[13] = {
		{PFDframe_x - Ulength * 60.5 , PFDframe_y - Ulength * 59},
		{PFDframe_x + Ulength * 60.5 , PFDframe_y - Ulength * 59},
		{PFDframe_x + Ulength * 60.5 , PFDframe_y - Ulength * 59},
		{PFDframe_x + Ulength * 60.5 , PFDframe_y - Ulength * 59},
		
		{PFDframe_x + Ulength * 60.5 , PFDframe_y + Ulength * 51.5},
		{PFDframe_x + Ulength * 60.5 , PFDframe_y + Ulength * 51.5},
		{PFDframe_x + Ulength * 60.5 , PFDframe_y + Ulength * 51.5},
		
		{PFDframe_x - Ulength * 60.5 , PFDframe_y + Ulength * 51.5},
		{PFDframe_x - Ulength * 60.5 , PFDframe_y + Ulength * 51.5},
		{PFDframe_x - Ulength * 60.5 , PFDframe_y + Ulength * 51.5},
		
		{PFDframe_x - Ulength * 60.5 , PFDframe_y - Ulength * 60},
		{PFDframe_x - Ulength * 60.5 , PFDframe_y - Ulength * 60},
		{PFDframe_x - Ulength * 60.5 , PFDframe_y - Ulength * 60},
	};
	
	ege_bezier(Frame_num3, Frame_ploypoints3);
	
	
	setcolor(EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	setlinewidth(linewidth);
	int Frame_num2 = 25;//中间层
	ege_point Frame_ploypoints2[25] = {
		{PFDframe_x - Ulength * 54.5 , PFDframe_y - Ulength * 50},
		{PFDframe_x - Ulength * 54 , PFDframe_y - Ulength * 52},
		{PFDframe_x - Ulength * 53 , PFDframe_y - Ulength * 52.5},
		{PFDframe_x - Ulength * 51.5, PFDframe_y - Ulength * 52},
		
		{PFDframe_x + Ulength * 51.5, PFDframe_y - Ulength * 52},
		{PFDframe_x + Ulength * 51.5, PFDframe_y - Ulength * 52},
		{PFDframe_x + Ulength * 51.5, PFDframe_y - Ulength * 52},
		
		{PFDframe_x + Ulength * 53 , PFDframe_y - Ulength * 52.5},
		{PFDframe_x + Ulength * 54 , PFDframe_y - Ulength * 52},
		{PFDframe_x + Ulength * 54.5 , PFDframe_y - Ulength * 50},
		
		{PFDframe_x + Ulength * 54.5 , PFDframe_y + Ulength * 46},
		{PFDframe_x + Ulength * 54.5 , PFDframe_y + Ulength * 46},
		{PFDframe_x + Ulength * 54.5 , PFDframe_y + Ulength * 46},
		
		{PFDframe_x + Ulength * 54 , PFDframe_y + Ulength * 48},
		{PFDframe_x + Ulength * 53 , PFDframe_y + Ulength * 48.5},
		{PFDframe_x + Ulength * 51.5, PFDframe_y + Ulength * 49},
		
		{PFDframe_x - Ulength * 51.5, PFDframe_y + Ulength * 49},
		{PFDframe_x - Ulength * 51.5, PFDframe_y + Ulength * 49},
		{PFDframe_x - Ulength * 51.5, PFDframe_y + Ulength * 49},
		
		{PFDframe_x - Ulength * 53 , PFDframe_y + Ulength * 48.5},
		{PFDframe_x - Ulength * 54 , PFDframe_y + Ulength * 48},
		{PFDframe_x - Ulength * 54.5 , PFDframe_y + Ulength * 46},
		
		{PFDframe_x - Ulength * 54.5 , PFDframe_y - Ulength * 51},
		{PFDframe_x - Ulength * 54.5 , PFDframe_y - Ulength * 51},
		{PFDframe_x - Ulength * 54.5 , PFDframe_y - Ulength * 51}
	};
	ege_bezier(Frame_num2, Frame_ploypoints2);
	setfillcolor(EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(PFDframe_x + Ulength * 57.5, PFDframe_y - Ulength * 57, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(PFDframe_x - Ulength * 57.5, PFDframe_y - Ulength * 57, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(PFDframe_x - Ulength * 57.5, PFDframe_y + Ulength * 50, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(PFDframe_x + Ulength * 57.5, PFDframe_y + Ulength * 50, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(PFDframe_x + Ulength * 58.5, PFDframe_y - Ulength * 13, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(PFDframe_x - Ulength * 58.5, PFDframe_y - Ulength * 13, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(PFDframe_x - Ulength * 58.5, PFDframe_y + Ulength * 13, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(PFDframe_x + Ulength * 58.5, PFDframe_y + Ulength * 13, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(PFDframe_x + Ulength * 15, PFDframe_y - Ulength * 57, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(PFDframe_x - Ulength * 15, PFDframe_y - Ulength * 57, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(PFDframe_x - Ulength * 15, PFDframe_y + Ulength * 50, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(PFDframe_x + Ulength * 15, PFDframe_y + Ulength * 50, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	
	
	
	
	setcolor(EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	setlinewidth(linewidth / 2);
	int Frame_num4 = 25;//中间层
	ege_point Frame_ploypoints4[25] = {
		{PFDframe_x - Ulength * 54.5 , PFDframe_y - Ulength * 50},
		{PFDframe_x - Ulength * 54 , PFDframe_y - Ulength * 52},
		{PFDframe_x - Ulength * 53 , PFDframe_y - Ulength * 52.5},
		{PFDframe_x - Ulength * 51.5, PFDframe_y - Ulength * 52},
		
		{PFDframe_x + Ulength * 51.5, PFDframe_y - Ulength * 52},
		{PFDframe_x + Ulength * 51.5, PFDframe_y - Ulength * 52},
		{PFDframe_x + Ulength * 51.5, PFDframe_y - Ulength * 52},
		
		{PFDframe_x + Ulength * 53 , PFDframe_y - Ulength * 52.5},
		{PFDframe_x + Ulength * 54 , PFDframe_y - Ulength * 52},
		{PFDframe_x + Ulength * 54.5 , PFDframe_y - Ulength * 50},
		
		{PFDframe_x + Ulength * 54.5 , PFDframe_y + Ulength * 46},
		{PFDframe_x + Ulength * 54.5 , PFDframe_y + Ulength * 46},
		{PFDframe_x + Ulength * 54.5 , PFDframe_y + Ulength * 46},
		
		{PFDframe_x + Ulength * 54 , PFDframe_y + Ulength * 48},
		{PFDframe_x + Ulength * 53 , PFDframe_y + Ulength * 48.5},
		{PFDframe_x + Ulength * 51.5, PFDframe_y + Ulength * 49},
		
		{PFDframe_x - Ulength * 51.5, PFDframe_y + Ulength * 49},
		{PFDframe_x - Ulength * 51.5, PFDframe_y + Ulength * 49},
		{PFDframe_x - Ulength * 51.5, PFDframe_y + Ulength * 49},
		
		{PFDframe_x - Ulength * 53 , PFDframe_y + Ulength * 48.5},
		{PFDframe_x - Ulength * 54 , PFDframe_y + Ulength * 48},
		{PFDframe_x - Ulength * 54.5 , PFDframe_y + Ulength * 46},
		
		{PFDframe_x - Ulength * 54.5 , PFDframe_y - Ulength * 51},
		{PFDframe_x - Ulength * 54.5 , PFDframe_y - Ulength * 51},
		{PFDframe_x - Ulength * 54.5 , PFDframe_y - Ulength * 51}
	};
	ege_bezier(Frame_num4, Frame_ploypoints4);
	setfillcolor(EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	
	
	setcolor(EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	setlinewidth(linewidth / 2);
	//最里面一层
	int Frame_num1 = 25;
	ege_point Frame_ploypoints1[25] = {
		{PFDframe_x - Ulength * 49.5 , PFDframe_y - Ulength * 45},
		{PFDframe_x - Ulength * 49 , PFDframe_y - Ulength * 47},
		{PFDframe_x - Ulength * 48 , PFDframe_y - Ulength * 47.5},
		{PFDframe_x - Ulength * 46.5, PFDframe_y - Ulength * 48},
		
		{PFDframe_x + Ulength * 46.5, PFDframe_y - Ulength * 48},
		{PFDframe_x + Ulength * 46.5, PFDframe_y - Ulength * 48},
		{PFDframe_x + Ulength * 46.5, PFDframe_y - Ulength * 48},
		
		{PFDframe_x + Ulength * 48 , PFDframe_y - Ulength * 47.5},
		{PFDframe_x + Ulength * 49 , PFDframe_y - Ulength * 47},
		{PFDframe_x + Ulength * 49.5 , PFDframe_y - Ulength * 45},
		
		{PFDframe_x + Ulength * 49.5 , PFDframe_y + Ulength * 45},
		{PFDframe_x + Ulength * 49.5 , PFDframe_y + Ulength * 45},
		{PFDframe_x + Ulength * 49.5 , PFDframe_y + Ulength * 45},
		
		{PFDframe_x + Ulength * 49 , PFDframe_y + Ulength * 47},
		{PFDframe_x + Ulength * 48 , PFDframe_y + Ulength * 47.5},
		{PFDframe_x + Ulength * 46.5, PFDframe_y + Ulength * 48},
		
		{PFDframe_x - Ulength * 46.5, PFDframe_y + Ulength * 48},
		{PFDframe_x - Ulength * 46.5, PFDframe_y + Ulength * 48},
		{PFDframe_x - Ulength * 46.5, PFDframe_y + Ulength * 48},
		
		{PFDframe_x - Ulength * 48 , PFDframe_y + Ulength * 47.5},
		{PFDframe_x - Ulength * 49 , PFDframe_y + Ulength * 47},
		{PFDframe_x - Ulength * 49.5 , PFDframe_y + Ulength * 45},
		
		{PFDframe_x - Ulength * 49.5 , PFDframe_y - Ulength * 45},
		{PFDframe_x - Ulength * 49.5 , PFDframe_y - Ulength * 45},
		{PFDframe_x - Ulength * 49.5 , PFDframe_y - Ulength * 45}
		
		
	};
	ege_bezier(Frame_num1, Frame_ploypoints1);
	setfillcolor(EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	floodfill(PFDframe_x - Ulength * 53.5, PFDframe_y - Ulength * 45, EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	floodfill(PFDframe_x + Ulength * 53.5, PFDframe_y - Ulength * 45, EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	floodfill(PFDframe_x - Ulength * 53.5, PFDframe_y + Ulength * 44, EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	floodfill(PFDframe_x + Ulength * 53.5, PFDframe_y + Ulength * 44, EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	floodfill(PFDframe_x - Ulength * 13.5, PFDframe_y - Ulength * 51, EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	floodfill(PFDframe_x + Ulength * 13.5, PFDframe_y - Ulength * 51, EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	floodfill(PFDframe_x - Ulength * 13.5, PFDframe_y + Ulength * 48, EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	floodfill(PFDframe_x + Ulength * 13.5, PFDframe_y + Ulength * 48, EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	floodfill(PFDframe_x - Ulength * 53.5, PFDframe_y - Ulength * 12, EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	floodfill(PFDframe_x + Ulength * 53.5, PFDframe_y - Ulength * 12, EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	floodfill(PFDframe_x + Ulength * 53.5, PFDframe_y + Ulength * 12, EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	floodfill(PFDframe_x - Ulength * 53.5, PFDframe_y + Ulength * 12, EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	
	ege_enable_aa(true);
	
	setcolor(EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	setlinewidth(linewidth / 2 );
	int Frame_num2_1 = 25;
	ege_point Frame_ploypoints2_1[25] = {
		{PFDframe_x - Ulength * 54.5 , PFDframe_y - Ulength * 50},
		{PFDframe_x - Ulength * 54 , PFDframe_y - Ulength * 52},
		{PFDframe_x - Ulength * 53 , PFDframe_y - Ulength * 52.5},
		{PFDframe_x - Ulength * 51.5, PFDframe_y - Ulength * 52},
		
		{PFDframe_x + Ulength * 51.5, PFDframe_y - Ulength * 52},
		{PFDframe_x + Ulength * 51.5, PFDframe_y - Ulength * 52},
		{PFDframe_x + Ulength * 51.5, PFDframe_y - Ulength * 52},
		
		{PFDframe_x + Ulength * 53 , PFDframe_y - Ulength * 52.5},
		{PFDframe_x + Ulength * 54 , PFDframe_y - Ulength * 52},
		{PFDframe_x + Ulength * 54.5 , PFDframe_y - Ulength * 50},
		
		{PFDframe_x + Ulength * 54.5 , PFDframe_y + Ulength * 46},
		{PFDframe_x + Ulength * 54.5 , PFDframe_y + Ulength * 46},
		{PFDframe_x + Ulength * 54.5 , PFDframe_y + Ulength * 46},
		
		{PFDframe_x + Ulength * 54 , PFDframe_y + Ulength * 48},
		{PFDframe_x + Ulength * 53 , PFDframe_y + Ulength * 48.5},
		{PFDframe_x + Ulength * 51.5, PFDframe_y + Ulength * 49},
		
		{PFDframe_x - Ulength * 51.5, PFDframe_y + Ulength * 49},
		{PFDframe_x - Ulength * 51.5, PFDframe_y + Ulength * 49},
		{PFDframe_x - Ulength * 51.5, PFDframe_y + Ulength * 49},
		
		{PFDframe_x - Ulength * 53 , PFDframe_y + Ulength * 48.5},
		{PFDframe_x - Ulength * 54 , PFDframe_y + Ulength * 48},
		{PFDframe_x - Ulength * 54.5 , PFDframe_y + Ulength * 46},
		
		{PFDframe_x - Ulength * 54.5 , PFDframe_y - Ulength * 51},
		{PFDframe_x - Ulength * 54.5 , PFDframe_y - Ulength * 51},
		{PFDframe_x - Ulength * 54.5 , PFDframe_y - Ulength * 51}
	};
	ege_bezier(Frame_num2_1, Frame_ploypoints2_1);
	
	
	
	setcolor(EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	setlinewidth(linewidth * 0.6);
	//最里面一层
	int Frame_num1_1 = 25;
	ege_point Frame_ploypoints1_1[25] = {
		{PFDframe_x - Ulength * 49.5 , PFDframe_y - Ulength * 45},
		{PFDframe_x - Ulength * 49 , PFDframe_y - Ulength * 47},
		{PFDframe_x - Ulength * 48 , PFDframe_y - Ulength * 47.5},
		{PFDframe_x - Ulength * 46.5, PFDframe_y - Ulength * 48},
		
		{PFDframe_x + Ulength * 46.5, PFDframe_y - Ulength * 48},
		{PFDframe_x + Ulength * 46.5, PFDframe_y - Ulength * 48},
		{PFDframe_x + Ulength * 46.5, PFDframe_y - Ulength * 48},
		
		{PFDframe_x + Ulength * 48 , PFDframe_y - Ulength * 47.5},
		{PFDframe_x + Ulength * 49 , PFDframe_y - Ulength * 47},
		{PFDframe_x + Ulength * 49.5 , PFDframe_y - Ulength * 45},
		
		{PFDframe_x + Ulength * 49.5 , PFDframe_y + Ulength * 45},
		{PFDframe_x + Ulength * 49.5 , PFDframe_y + Ulength * 45},
		{PFDframe_x + Ulength * 49.5 , PFDframe_y + Ulength * 45},
		
		{PFDframe_x + Ulength * 49 , PFDframe_y + Ulength * 47},
		{PFDframe_x + Ulength * 48 , PFDframe_y + Ulength * 47.5},
		{PFDframe_x + Ulength * 46.5, PFDframe_y + Ulength * 48},
		
		{PFDframe_x - Ulength * 46.5, PFDframe_y + Ulength * 48},
		{PFDframe_x - Ulength * 46.5, PFDframe_y + Ulength * 48},
		{PFDframe_x - Ulength * 46.5, PFDframe_y + Ulength * 48},
		
		{PFDframe_x - Ulength * 48 , PFDframe_y + Ulength * 47.5},
		{PFDframe_x - Ulength * 49 , PFDframe_y + Ulength * 47},
		{PFDframe_x - Ulength * 49.5 , PFDframe_y + Ulength * 45},
		
		{PFDframe_x - Ulength * 49.5 , PFDframe_y - Ulength * 45},
		{PFDframe_x - Ulength * 49.5 , PFDframe_y - Ulength * 45},
		{PFDframe_x - Ulength * 49.5 , PFDframe_y - Ulength * 45}
		
		
	};
	ege_bezier(Frame_num1_1, Frame_ploypoints1_1);
	
	ege_setpattern_lineargradient(PFDframe_x, PFDframe_y + Ulength * 61.5, EGEARGB(0XFF, 0X00, 0X00, 0X00),
		PFDframe_x, PFDframe_y + Ulength * 47, EGEARGB(0XFF, 0X15, 0X1A, 0X1D));
	ege_fillrect(PFDframe_x - Ulength * 61.5, PFDframe_y + Ulength * 47, Ulength * 123, Ulength * 14.5);
	ege_setpattern_none();
	
	setfillcolor(EGEARGB(0XFF, 0X18, 0X1C, 0X20));
	int Frame_num_left = 12;//底下左边
	ege_point Frame_ploypoints_left[12] = {
		{PFDframe_x - Ulength * 61.5,PFDframe_y + Ulength * 51.5},
		{PFDframe_x - Ulength * 21.5,PFDframe_y + Ulength * 51.5},
		{PFDframe_x - Ulength * 21.5,PFDframe_y + Ulength * 53.5},
		{PFDframe_x - Ulength * 25,PFDframe_y + Ulength * 53.5},
		{PFDframe_x - Ulength * 25,PFDframe_y + Ulength * 55.5},
		{PFDframe_x - Ulength * 21.5,PFDframe_y + Ulength * 55.5},
		{PFDframe_x - Ulength * 21.5,PFDframe_y + Ulength * 57.5},
		{PFDframe_x - Ulength * 25,PFDframe_y + Ulength * 57.5},
		{PFDframe_x - Ulength * 25,PFDframe_y + Ulength * 59.5},
		{PFDframe_x - Ulength * 21.5,PFDframe_y + Ulength * 59.5},
		{PFDframe_x - Ulength * 21.5,PFDframe_y + Ulength * 61.5},
		{PFDframe_x - Ulength * 61.5,PFDframe_y + Ulength * 61.5},
		
	};
	ege_fillpoly(Frame_num_left, Frame_ploypoints_left);
	
	int Frame_num_right = 12;//底下右边
	ege_point Frame_ploypoints_right[12] = {
		{PFDframe_x - Ulength * 20.5,PFDframe_y + Ulength * 51.5},
		{PFDframe_x - Ulength * 20.5,PFDframe_y + Ulength * 53.6},
		{PFDframe_x - Ulength * 23.5,PFDframe_y + Ulength * 53.6},
		{PFDframe_x - Ulength * 23.5,PFDframe_y + Ulength * 55.3},
		{PFDframe_x - Ulength * 20.5,PFDframe_y + Ulength * 55.3},
		{PFDframe_x - Ulength * 20.5,PFDframe_y + Ulength * 57.6},
		{PFDframe_x - Ulength * 23.5,PFDframe_y + Ulength * 57.6},
		{PFDframe_x - Ulength * 23.5,PFDframe_y + Ulength * 59.3},
		{PFDframe_x - Ulength * 20.5,PFDframe_y + Ulength * 59.3},
		{PFDframe_x - Ulength * 20.5,PFDframe_y + Ulength * 61.5},
		{PFDframe_x + Ulength * 61.5,PFDframe_y + Ulength * 61.5},
		{PFDframe_x + Ulength * 61.5,PFDframe_y + Ulength * 51.5},
		
		
	};
	ege_fillpoly(Frame_num_right, Frame_ploypoints_right);
	
	
	
	
	
	setcolor(EGEARGB(0X40, 0X40, 0X40, 0X40));
	setlinewidth(linewidth / 3);
	
	ege_line(PFDframe_x - Ulength * 61.5, PFDframe_y - Ulength * 59, PFDframe_x + Ulength * 61.5, PFDframe_y - Ulength * 59);
	ege_line(PFDframe_x + Ulength * 61.5, PFDframe_y - Ulength * 59, PFDframe_x + Ulength * 61.5, PFDframe_y + Ulength * 51.5);
	
	
	ege_line(PFDframe_x - Ulength * 61.5, PFDframe_y + Ulength * 51.5, PFDframe_x - Ulength * 21.5, PFDframe_y + Ulength * 51.5);
	ege_line(PFDframe_x - Ulength * 20.5, PFDframe_y + Ulength * 51.5, PFDframe_x + Ulength * 61.5, PFDframe_y + Ulength * 51.5);
	
	ege_line(PFDframe_x - Ulength * 21.5, PFDframe_y + Ulength * 51.5, PFDframe_x - Ulength * 21.5, PFDframe_y + Ulength * 53.5);
	ege_line(PFDframe_x - Ulength * 21.5, PFDframe_y + Ulength * 55.5, PFDframe_x - Ulength * 21.5, PFDframe_y + Ulength * 57.5);
	ege_line(PFDframe_x - Ulength * 21.5, PFDframe_y + Ulength * 59.5, PFDframe_x - Ulength * 21.5, PFDframe_y + Ulength * 61.5);
	
	ege_line(PFDframe_x + Ulength * 61.5, PFDframe_y + Ulength * 61.5, PFDframe_x + Ulength * 61.5, PFDframe_y + Ulength * 51.5);
	
	setcolor(EGEARGB(0X4F, 0X00, 0X00, 0X00));
	ege_line(PFDframe_x - Ulength * 61.5, PFDframe_y - Ulength * 59, PFDframe_x - Ulength * 61.5, PFDframe_y + Ulength * 51.5);
	ege_line(PFDframe_x - Ulength * 61.5, PFDframe_y + Ulength * 51.5, PFDframe_x - Ulength * 61.5, PFDframe_y + Ulength * 61.5);
	ege_line(PFDframe_x - Ulength * 61.5, PFDframe_y + Ulength * 61.5, PFDframe_x - Ulength * 21.5, PFDframe_y + Ulength * 61.5);
	ege_line(PFDframe_x - Ulength * 20.5, PFDframe_y + Ulength * 61.5, PFDframe_x + Ulength * 61.5, PFDframe_y + Ulength * 61.5);
	
	
}

