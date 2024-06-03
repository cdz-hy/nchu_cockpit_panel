#include<graphics.h>
#include <stdio.h>
#include <math.h>

void DrawPFDframe(double PFDframe_x, double PFDframe_y, double side) {
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
	floodfill(PFDframe_x + Ulength * 59.5, PFDframe_y - Ulength * 52, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(PFDframe_x - Ulength * 59.5, PFDframe_y - Ulength * 52, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(PFDframe_x - Ulength * 59.5, PFDframe_y + Ulength * 52, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(PFDframe_x + Ulength * 59.5, PFDframe_y + Ulength * 52, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(PFDframe_x + Ulength * 59.5, PFDframe_y - Ulength * 13, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(PFDframe_x - Ulength * 59.5, PFDframe_y - Ulength * 13, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(PFDframe_x - Ulength * 59.5, PFDframe_y + Ulength * 13, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(PFDframe_x + Ulength * 59.5, PFDframe_y + Ulength * 13, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(PFDframe_x + Ulength * 15, PFDframe_y - Ulength * 55, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(PFDframe_x - Ulength * 15, PFDframe_y - Ulength * 55, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(PFDframe_x - Ulength * 15, PFDframe_y + Ulength * 52, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	floodfill(PFDframe_x + Ulength * 15, PFDframe_y + Ulength * 52, EGEARGB(0XFF, 0X1A, 0X1F, 0X23));
	



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



	setfillcolor(EGEARGB(0XFF, 0XFF, 0XFF, 0XFF));
	ege_fillrect(PFDframe_x - Ulength * 30.5, PFDframe_y + Ulength * 52,  Ulength * 2, Ulength * 2);
}
