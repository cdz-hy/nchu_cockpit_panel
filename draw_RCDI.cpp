#include<graphics.h>
#include <windows.h>
#include<math.h>
#include<stdio.h>
extern double verticalRate;
extern double RNG;
extern int choice_light;
extern double konb_angle;
int RCDI_mouse_x = 0, RCDI_mouse_y = 0;
int RCDI_speed_is_down = 0;
int RCDI_mouse_y_cur = 0, RCDI_mouse_x_cur = 0;
double CalAngle(double verticalRate);//函数声明
void draw_RMI(double RMI_x, double RMI_y, double RMI_r);
void draw_pointer(double RCDI_X, double RCDI_Y, double RCDI_R, double verticalRate);
void draw_screw(double screw_x, double screw_y, double screw_r, double angle);
double CalAngle(double verticalRate);//函数声明
void draw_RCDI(double RCDI_x, double RCDI_y, double RCDI_side) {


	RCDI_side = RCDI_side / 14 * 13;
	double RCDI_lefttop_x = RCDI_x - RCDI_side / 2.0;
	double RCDI_lefttop_y = RCDI_y - RCDI_side / 2.0;
	double R = RCDI_side / 52.0 * 17;//白色圆半径
	double big_scales_longth = RCDI_side / 52.0 * 3;//大刻度长
	double small_scales_longth = RCDI_side / 52.0 * 1;//小刻度长
	double medium_scales_longth = RCDI_side / 52.0 * 2;//中刻度长
	double big_scales_width = RCDI_side / 520.0 * 5;//大刻度宽
	double medium_scales_width = RCDI_side / 520.0 * 4.5;//中刻度宽
	double small_scales_width = RCDI_side / 520.0 * 3;//小刻度宽
	double figure_height = RCDI_side / 52 * 4;//字体的高
	double figure_weight = RCDI_side / 520.0 * 15;//字体的宽
	double char_height = RCDI_side / 520 * 30;
	double char_weight = RCDI_side / 520 * 9;


	int x, y;
	mousepos(&x, &y);//鼠标坐标

	//高光
	int RCDI_num_points_highlights = 5;
	ege_point RCDI_polypoints_highlight[5] = { {RCDI_lefttop_x - RCDI_side / 26 * 2 + RCDI_side / 250,RCDI_lefttop_y + RCDI_side / 26 * 3 - RCDI_side / 250} ,{RCDI_lefttop_x + RCDI_side / 26 * 2 + RCDI_side / 250,RCDI_lefttop_y - RCDI_side / 26 - RCDI_side / 250},{RCDI_lefttop_x + RCDI_side - RCDI_side / 26 * 2 + RCDI_side / 250,RCDI_lefttop_y - RCDI_side / 26 - RCDI_side / 250},
		{RCDI_lefttop_x + RCDI_side + RCDI_side / 26 * 2 + RCDI_side / 250,RCDI_lefttop_y + RCDI_side / 26 * 3 - RCDI_side / 250} ,{RCDI_lefttop_x + RCDI_side + RCDI_side / 26 * 2 + RCDI_side / 250,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3 - RCDI_side / 250} };
	ege_setpattern_lineargradient(RCDI_lefttop_x + RCDI_side / 26 * 2 + RCDI_side / 250, RCDI_lefttop_y - RCDI_side / 26 - RCDI_side / 250, EGEARGB(0X5F, 0XFF, 0XFF, 0XFF), RCDI_lefttop_x + RCDI_side + RCDI_side / 26 * 2 + RCDI_side / 250, RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3 - RCDI_side / 250, EGEARGB(0X12, 0XFF, 0XFF, 0XFF));
	ege_fillpoly(RCDI_num_points_highlights, RCDI_polypoints_highlight);
	ege_setpattern_none();

	//边框底
	int RCDI_num_points_frame = 8;
	ege_point RCDI_polypoints_frame[8] = { {RCDI_lefttop_x - RCDI_side / 26 * 2 ,RCDI_lefttop_y + RCDI_side / 26 * 3},{RCDI_lefttop_x + RCDI_side / 26 * 2 ,RCDI_lefttop_y - RCDI_side / 26},
		{RCDI_lefttop_x + RCDI_side - RCDI_side / 26 * 2,RCDI_lefttop_y - RCDI_side / 26},{RCDI_lefttop_x + RCDI_side + RCDI_side / 26 * 2,RCDI_lefttop_y + RCDI_side / 26 * 3},
		{RCDI_lefttop_x + RCDI_side + RCDI_side / 26 * 2,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3},{RCDI_lefttop_x + RCDI_side - RCDI_side / 26 * 2 ,RCDI_lefttop_y + RCDI_side + RCDI_side / 26},
		{RCDI_lefttop_x + RCDI_side / 26 * 2 ,RCDI_lefttop_y + RCDI_side + RCDI_side / 26},{RCDI_lefttop_x - RCDI_side / 26 * 2,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3} };
	ege_setpattern_lineargradient(RCDI_lefttop_x + RCDI_side + RCDI_side / 26 * 2, RCDI_lefttop_y + RCDI_side / 26 * 3, EGEARGB(0XFF, 0X28, 0X29, 0X2E), RCDI_lefttop_x - RCDI_side / 26 * 2, RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3, EGEARGB(0XFF, 0X1D, 0X1E, 0X23));
	ege_fillpoly(RCDI_num_points_frame, RCDI_polypoints_frame);
	ege_setpattern_none();

	


	setcolor(EGEARGB(0X4F, 0X00, 0X00, 0X00));
	setlinewidth(RCDI_side / 520.0 * 2);
	int RCDI_frame_edge_pointsNum = 16;
	ege_point RCDI_frame_edge_polyPoints[16] = { {RCDI_lefttop_x + RCDI_side / 26 * 2 ,RCDI_lefttop_y - RCDI_side / 26},{RCDI_lefttop_x - RCDI_side / 26 * 2 ,RCDI_lefttop_y + RCDI_side / 26 * 3},

		{RCDI_lefttop_x - RCDI_side / 26 * 2 ,RCDI_lefttop_y + RCDI_side / 26 * 3},{RCDI_lefttop_x - RCDI_side / 26 * 2 ,RCDI_lefttop_y + RCDI_side / 26 * 3},

		{RCDI_lefttop_x - RCDI_side / 26 * 2,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3},{RCDI_lefttop_x - RCDI_side / 26 * 2,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3},

		{RCDI_lefttop_x - RCDI_side / 26 * 2,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3},{RCDI_lefttop_x - RCDI_side / 26 * 2,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3},


		{RCDI_lefttop_x - RCDI_side / 26 * 2,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3},{RCDI_lefttop_x + RCDI_side / 26 * 2 ,RCDI_lefttop_y + RCDI_side + RCDI_side / 26},
		{RCDI_lefttop_x + RCDI_side / 26 * 2 ,RCDI_lefttop_y + RCDI_side + RCDI_side / 26},{RCDI_lefttop_x + RCDI_side / 26 * 2 ,RCDI_lefttop_y + RCDI_side + RCDI_side / 26},

		{RCDI_lefttop_x + RCDI_side - RCDI_side / 26 * 2 ,RCDI_lefttop_y + RCDI_side + RCDI_side / 26},{RCDI_lefttop_x + RCDI_side - RCDI_side / 26 * 2 ,RCDI_lefttop_y + RCDI_side + RCDI_side / 26},

		{RCDI_lefttop_x + RCDI_side - RCDI_side / 26 * 2 ,RCDI_lefttop_y + RCDI_side + RCDI_side / 26},{RCDI_lefttop_x + RCDI_side + RCDI_side / 26 * 2,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3}


	};
	ege_bezier(RCDI_frame_edge_pointsNum, RCDI_frame_edge_polyPoints);



	//表盘阴影
	setcolor(EGEARGB(0XFF, 0X38, 0X38, 0X3D));
	setlinewidth(3);
	int RCDI_aroundShade_pointsNum = 25;
	ege_point RCDI_aroundShade_polyPoints[25] = { {RCDI_lefttop_x + RCDI_side / 52 * 4.5 - RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 8 },{RCDI_lefttop_x + RCDI_side / 52 * 5.5 - RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 6 },
		{RCDI_lefttop_x + RCDI_side / 52 * 6 - RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 5.5 },{RCDI_lefttop_x + RCDI_side / 52 * 8 - RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 4.5 },

		{RCDI_lefttop_x + RCDI_side / 52 * 42 + RCDI_side / 520 * 13 + RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 4.5 },{RCDI_lefttop_x + RCDI_side / 52 * 42 + RCDI_side / 520 * 13 + RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 4.5 },

	{RCDI_lefttop_x + RCDI_side / 52 * 42 + RCDI_side / 520 * 13 + RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 4.5 }, {RCDI_lefttop_x + RCDI_side / 52 * 44 + RCDI_side / 520 * 13 + RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 5.5  },
		{RCDI_lefttop_x + RCDI_side / 52 * 44.5 + RCDI_side / 520 * 13 + RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 6 }, {RCDI_lefttop_x + RCDI_side / 52 * 45.5 + RCDI_side / 520 * 13 + RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 8  } ,

		{ RCDI_lefttop_x + RCDI_side / 52 * 45.5 + RCDI_side / 520 * 13 + RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 36 + RCDI_side / 520.0 * 5},{ RCDI_lefttop_x + RCDI_side / 52 * 45.5 + RCDI_side / 520 * 13 + RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 36 + RCDI_side / 520.0 * 5},

	{ RCDI_lefttop_x + RCDI_side / 52 * 45.5 + RCDI_side / 520 * 13 + RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 36 + RCDI_side / 520.0 * 5},{RCDI_lefttop_x + RCDI_side / 52 * 45 + RCDI_side / 520 * 13 + RCDI_side / 26,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 10 + RCDI_side / 520 * 10},
		{RCDI_lefttop_x + RCDI_side / 52 * 41 + RCDI_side / 520 * 13 + RCDI_side / 26,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 6 },{RCDI_lefttop_x + RCDI_side / 52 * 36 + RCDI_side / 520 * 13 + RCDI_side / 26,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 4.5} ,

		{RCDI_lefttop_x + RCDI_side / 52 * 36 + RCDI_side / 520 * 13 + RCDI_side / 26,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 4.5},{RCDI_lefttop_x + RCDI_side / 52 * 36 + RCDI_side / 520 * 13 + RCDI_side / 26,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 4.5},

	{RCDI_lefttop_x + RCDI_side / 26 * 7 - RCDI_side / 26,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 4.5 } ,{RCDI_lefttop_x + RCDI_side / 52 * 9 - RCDI_side / 26,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 6 },
		{RCDI_lefttop_x + RCDI_side / 52 * 5 - RCDI_side / 26 ,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 10 + RCDI_side / 520 * 10},{RCDI_lefttop_x + RCDI_side / 52 * 4.5 - RCDI_side / 26 , RCDI_lefttop_y + RCDI_side / 52 * 36 },

	{RCDI_lefttop_x + RCDI_side / 52 * 4.5 - RCDI_side / 26 , RCDI_lefttop_y + RCDI_side / 52 * 8 },{RCDI_lefttop_x + RCDI_side / 52 * 4.5 - RCDI_side / 26 , RCDI_lefttop_y + RCDI_side / 52 * 8 },
		{RCDI_lefttop_x + RCDI_side / 52 * 4.5 - RCDI_side / 26 , RCDI_lefttop_y + RCDI_side / 52 * 8 } };

	ege_bezier(RCDI_aroundShade_pointsNum, RCDI_aroundShade_polyPoints);
	setfillcolor(EGEARGB(0XFF, 0X38, 0X38, 0X3D));
	floodfill(RCDI_x, RCDI_y, EGEARGB(0XFF, 0X38, 0X38, 0X3D));



	//边框阴影右
	setcolor(EGEARGB(0X8A, 0X00, 0X00, 0X00));
	setlinewidth(RCDI_side / 520.0 * 8);
	int RCDI_rightShade_pointsNum = 13;
	ege_point RCDI_rightShade_polyPoints[13] = {
		{RCDI_lefttop_x + RCDI_side / 52 * 42 + RCDI_side / 520 * 10 + RCDI_side / 26  , RCDI_lefttop_y + RCDI_side / 52 * 4.5 + RCDI_side / 520.0 * 2 },{RCDI_lefttop_x + RCDI_side / 52 * 43.5 + RCDI_side / 520 * 11 + RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 5.5 - RCDI_side / 520.0 },
		{RCDI_lefttop_x + RCDI_side / 52 * 44.5 + RCDI_side / 520 * 11 + RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 6 - RCDI_side / 520.0},{RCDI_lefttop_x + RCDI_side / 52 * 45.5 + RCDI_side / 520 * 11 + RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 8 - RCDI_side / 520.0 },

		{RCDI_lefttop_x + RCDI_side / 52 * 45.5 + RCDI_side / 520 * 11 + RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 36 + RCDI_side / 520.0 },{RCDI_lefttop_x + RCDI_side / 52 * 45.5 + RCDI_side / 520 * 11 + RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 36 + RCDI_side / 520.0 },

	{RCDI_lefttop_x + RCDI_side / 52 * 45.5 + RCDI_side / 520 * 11 + RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 36 + RCDI_side / 520.0 * 3},{RCDI_lefttop_x + RCDI_side / 52 * 45 + RCDI_side / 520 * 11 + RCDI_side / 26,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 10 + RCDI_side / 520 * 8},
		{RCDI_lefttop_x + RCDI_side / 52 * 41 + RCDI_side / 520 * 11 + RCDI_side / 26,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 6 - RCDI_side / 520.0 * 2},{RCDI_lefttop_x + RCDI_side / 52 * 36 + RCDI_side / 520 * 11 + RCDI_side / 26,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 4.5 - RCDI_side / 520.0 * 2},

		{RCDI_lefttop_x + RCDI_side / 52 * 33 + RCDI_side / 26 + RCDI_side / 520 * 2,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 4.5},
		{RCDI_lefttop_x + RCDI_side / 52 * 33 + RCDI_side / 26 + RCDI_side / 520 * 2,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 4.5},
		{RCDI_lefttop_x + RCDI_side / 52 * 33 + RCDI_side / 26 + RCDI_side / 520 * 2,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 4.5}

	};
	ege_bezier(RCDI_rightShade_pointsNum, RCDI_rightShade_polyPoints);


	//边框阴影上
	int RCDI_top_pointsNum = 4;
	ege_point RCDI_top_polyPoints[4] = { {RCDI_lefttop_x + RCDI_side / 52 * 8 + RCDI_side / 520 * 5 - RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 4.5 - RCDI_side / 520 * 2 },{RCDI_lefttop_x + RCDI_side / 52 * 8 + RCDI_side / 520 * 5 - RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 4.5 + RCDI_side / 520 * 5},
		{RCDI_lefttop_x + RCDI_side / 52 * 42 + RCDI_side / 520 * 13 + RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 4.5 + RCDI_side / 520 * 5},{RCDI_lefttop_x + RCDI_side / 52 * 42 + RCDI_side / 520 * 13 + RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 4.5 - RCDI_side / 520 * 2} };
	ege_setpattern_lineargradient(RCDI_lefttop_x + RCDI_side / 52 * 8 + RCDI_side / 520 * 5 - RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 4.5 + RCDI_side / 520 * 5, EGEARGB(0XFF, 0X38, 0X38, 0X3D),
		RCDI_lefttop_x + RCDI_side / 52 * 42 + RCDI_side / 520 * 13 + RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 4.5 - RCDI_side / 520 * 2, EGEARGB(0XBF, 0X00, 0X00, 0X00));
	ege_fillpoly(RCDI_top_pointsNum, RCDI_top_polyPoints);
	ege_setpattern_none();

	//边框左下角螺丝绘制
	// 
	//两端阴影
	setlinewidth(RCDI_side / 520.0 * 6);
	setcolor(EGEARGB(0XFF, 0X11, 0X11, 0X11));
	int RCDI_leftBottom_screw_shade_pointsNum_1 = 4;
	ege_point RCDI_leftBottom_screw_shade_polyPoints_1[4] = {
		{RCDI_lefttop_x + RCDI_side / 26 * 4.5 - RCDI_side / 52 ,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 1.5 - RCDI_side / 52},
		{RCDI_lefttop_x + RCDI_side / 26 * 4.5 - RCDI_side / 52 ,RCDI_lefttop_y + RCDI_side + RCDI_side / 26 - RCDI_side / 52},
		{RCDI_lefttop_x + RCDI_side / 26 * 4.5 - RCDI_side / 52 ,RCDI_lefttop_y + RCDI_side + RCDI_side / 26 - RCDI_side / 52},
		{RCDI_lefttop_x + RCDI_side / 26 * 2 - RCDI_side / 52 ,RCDI_lefttop_y + RCDI_side + RCDI_side / 26 - RCDI_side / 52}
	};
	ege_bezier(RCDI_leftBottom_screw_shade_pointsNum_1, RCDI_leftBottom_screw_shade_polyPoints_1);

	int RCDI_leftBottom_screw_shade_pointsNum_2 = 4;
	ege_point RCDI_leftBottom_screw_shade_polyPoints_2[4] = {
		{RCDI_lefttop_x - RCDI_side / 26 * 2 + RCDI_side / 52,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3 + RCDI_side / 52},
		{RCDI_lefttop_x - RCDI_side / 26 * 2 + RCDI_side / 52,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 5.5 + RCDI_side / 52},
		{RCDI_lefttop_x - RCDI_side / 26 * 2 + RCDI_side / 52,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 5.5 + RCDI_side / 52},
		{RCDI_lefttop_x + RCDI_side / 52 + RCDI_side / 52,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 5.5 + RCDI_side / 52}
	};
	ege_bezier(RCDI_leftBottom_screw_shade_pointsNum_2, RCDI_leftBottom_screw_shade_polyPoints_2);

	//螺丝边框
	setcolor(EGEARGB(0XFF, 0X21, 0X21, 0X23));
	setlinewidth(3);
	int RCDI_leftBottom_screw_pointsNum = 16;
	ege_point RCDI_leftBottom_screw_polyPoints[16]{
		{RCDI_lefttop_x - RCDI_side / 26 * 2 + RCDI_side / 52,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3 + RCDI_side / 52},

		{RCDI_lefttop_x - RCDI_side / 26 * 2 + RCDI_side / 52,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 5.5 + RCDI_side / 52},{RCDI_lefttop_x - RCDI_side / 26 * 2 + RCDI_side / 52,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 5.5 + RCDI_side / 52},

		{RCDI_lefttop_x + RCDI_side / 52 + RCDI_side / 52,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 5.5 + RCDI_side / 52},{RCDI_lefttop_x + RCDI_side / 52 + RCDI_side / 52,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 5.5 + RCDI_side / 52},
		{RCDI_lefttop_x + RCDI_side / 52 + RCDI_side / 52,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 5.5 + RCDI_side / 52},

		{RCDI_lefttop_x + RCDI_side / 26 * 4.5 - RCDI_side / 52 ,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 1.5 - RCDI_side / 52},

		{RCDI_lefttop_x + RCDI_side / 26 * 4.5 - RCDI_side / 52 ,RCDI_lefttop_y + RCDI_side + RCDI_side / 26 - RCDI_side / 52},{RCDI_lefttop_x + RCDI_side / 26 * 4.5 - RCDI_side / 52 ,RCDI_lefttop_y + RCDI_side + RCDI_side / 26 - RCDI_side / 52},

		{RCDI_lefttop_x + RCDI_side / 26 * 2 - RCDI_side / 52 ,RCDI_lefttop_y + RCDI_side + RCDI_side / 26 - RCDI_side / 52},{RCDI_lefttop_x - RCDI_side / 26 * 2 + RCDI_side / 52,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3 + RCDI_side / 52},
		{RCDI_lefttop_x - RCDI_side / 26 * 2 + RCDI_side / 52,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3 + RCDI_side / 52},{RCDI_lefttop_x - RCDI_side / 26 * 2 + RCDI_side / 52,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3 + RCDI_side / 52},

		{RCDI_lefttop_x - RCDI_side / 26 * 2 + RCDI_side / 52,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3 + RCDI_side / 52},{RCDI_lefttop_x - RCDI_side / 26 * 2 + RCDI_side / 52,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3 + RCDI_side / 52},
		{RCDI_lefttop_x - RCDI_side / 26 * 2 + RCDI_side / 52,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3 + RCDI_side / 52}
	};
	ege_bezier(RCDI_leftBottom_screw_pointsNum, RCDI_leftBottom_screw_polyPoints);
	setfillcolor(EGEARGB(0XFF, 0X21, 0X21, 0X23));
	floodfill(RCDI_lefttop_x - RCDI_side / 26 * 2 + RCDI_side / 52 * 3, RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3 + RCDI_side / 52, EGEARGB(0XFF, 0X21, 0X21, 0X23));

	//两个圆形
	setfillcolor(EGEARGB(0XFF, 0X10, 0X10, 0X10));
	ege_fillellipse(RCDI_lefttop_x - RCDI_side / 52 * 0.5, RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3.6, RCDI_side / 52 * 5.7, RCDI_side / 52 * 5.7);
	setfillcolor(EGEARGB(0XFF, 0X4B, 0X4C, 0X47));
	ege_fillellipse(RCDI_lefttop_x + RCDI_side / 520 * 2, RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3.2, RCDI_side / 52 * 4, RCDI_side / 52 * 4);

	setfillcolor(EGEARGB(0XFF, 0X11, 0X11, 0X11));
	ege_fillellipse(RCDI_lefttop_x - RCDI_side / 26 * 1.3, RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 4.6, RCDI_side / 52 * 2, RCDI_side / 52 * 2);
	ege_fillellipse(RCDI_lefttop_x + RCDI_side / 26 * 2.6, RCDI_lefttop_y + RCDI_side - RCDI_side / 26, RCDI_side / 52 * 2, RCDI_side / 52 * 2);


	setcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	setlinewidth(RCDI_side / 520.0 * 4);
	ege_line(RCDI_lefttop_x - RCDI_side / 26 * 1.3 + RCDI_side / 52, RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 4.6, RCDI_lefttop_x - RCDI_side / 26 * 1.3 + RCDI_side / 52, RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 4.6 + RCDI_side / 52 * 2);
	ege_line(RCDI_lefttop_x - RCDI_side / 26 * 1.3, RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 4.6 + RCDI_side / 52, RCDI_lefttop_x - RCDI_side / 26 * 1.3 + RCDI_side / 52 * 2, RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 4.6 + RCDI_side / 52);
	ege_line(RCDI_lefttop_x + RCDI_side / 26 * 2.6 + RCDI_side / 52, RCDI_lefttop_y + RCDI_side - RCDI_side / 26, RCDI_lefttop_x + RCDI_side / 26 * 2.6 + RCDI_side / 52, RCDI_lefttop_y + RCDI_side - RCDI_side / 26 + RCDI_side / 52 * 2);
	ege_line(RCDI_lefttop_x + RCDI_side / 26 * 2.6, RCDI_lefttop_y + RCDI_side - RCDI_side / 26 + RCDI_side / 52, RCDI_lefttop_x + RCDI_side / 26 * 2.6 + RCDI_side / 52 * 2, RCDI_lefttop_y + RCDI_side - RCDI_side / 26 + RCDI_side / 52);

	//正方形
	setfillcolor(EGEARGB(0XFF, 0X27, 0X28, 0X20));
	int RCDI_leftBottom_screw_shade_pointsNum_3 = 4;
	ege_point RCDI_leftBottom_screw_shade_polyPoints_3[4] = {
		{RCDI_lefttop_x + RCDI_side / 520 * 2 + RCDI_side / 52 * 2, RCDI_lefttop_y + RCDI_side - RCDI_side / 520 * 60},
		{RCDI_lefttop_x + RCDI_side / 520 * 2 + RCDI_side / 520 * 36, RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3.2 + RCDI_side / 52 * 2},
		{RCDI_lefttop_x + RCDI_side / 520 * 2 + RCDI_side / 52 * 2, RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3.3 + RCDI_side / 520 * 38},
		{RCDI_lefttop_x + RCDI_side / 520 * 6 , RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3.2 + RCDI_side / 52 * 2}
	};
	ege_fillpoly(RCDI_leftBottom_screw_shade_pointsNum_3, RCDI_leftBottom_screw_shade_polyPoints_3);

	//右下角线条
	setlinewidth(RCDI_side / 520.0 * 2);
	setcolor(EGEARGB(0XFF, 0X10, 0X10, 0X10));
	ege_line(RCDI_lefttop_x + RCDI_side / 26 * 2 - RCDI_side / 52, RCDI_lefttop_y + RCDI_side + RCDI_side / 26 - RCDI_side / 52 * 0.9, RCDI_lefttop_x + RCDI_side / 26 * 4.5 - RCDI_side / 52 * 2.6, RCDI_lefttop_y + RCDI_side + RCDI_side / 26 - RCDI_side / 52);
	ege_line(RCDI_lefttop_x - RCDI_side / 26 * 2, RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3, RCDI_lefttop_x + RCDI_side / 26 * 2 - RCDI_side / 52, RCDI_lefttop_y + RCDI_side + RCDI_side / 26 - RCDI_side / 52 * 0.9);
	//右上角线条
	setcolor(EGEARGB(0XFF, 0X60, 0X60, 0X60));
	ege_line(RCDI_lefttop_x - RCDI_side / 26 * 2 + RCDI_side / 52 * 2.4, RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 5.5 + RCDI_side / 52, RCDI_lefttop_x + RCDI_side / 52 + RCDI_side / 52, RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 5.5 + RCDI_side / 52);
	ege_line(RCDI_lefttop_x + RCDI_side / 52 + RCDI_side / 52, RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 5.5 + RCDI_side / 52, RCDI_lefttop_x + RCDI_side / 26 * 4.5 - RCDI_side / 52, RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 1.5 - RCDI_side / 52);



	//按键边框

	//高光
	setfillcolor(EGEARGB(0XFF, 0X60, 0X60, 0X60));
	int RCDI_button_light_pointsNum = 4;
	ege_point RCDI_button_light_ployPoints[4] = {
		{RCDI_lefttop_x + RCDI_side + RCDI_side / 52 * 3 + RCDI_side / 520.0 * 8.5,RCDI_lefttop_y + RCDI_side / 520 * 61 },
		{RCDI_lefttop_x + RCDI_side / 52 * 48.3 + RCDI_side / 520 * 8 , RCDI_lefttop_y + RCDI_side / 520 * 61 },
		{RCDI_lefttop_x + RCDI_side / 52 * 48.3 + RCDI_side / 520 * 8 , RCDI_lefttop_y + RCDI_side / 52 * 7 + RCDI_side / 520 * 5},
		{RCDI_lefttop_x + RCDI_side + RCDI_side / 52 * 3 + RCDI_side / 520.0 * 8.5,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3},

	};
	ege_setpattern_lineargradient(RCDI_lefttop_x + RCDI_side / 52 * 48.3 + RCDI_side / 520 * 8, RCDI_lefttop_y + RCDI_side / 52 * 6, EGEARGB(0XFF, 0X60, 0X60, 0X60),
		RCDI_lefttop_x + RCDI_side + RCDI_side / 52 * 3 + RCDI_side / 520.0 * 5, RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3, EGEARGB(0XFF, 0X28, 0X29, 0X2E));
	ege_fillpoly(RCDI_button_light_pointsNum, RCDI_button_light_ployPoints);
	ege_setpattern_none();
	//阴影
	int RCDI_button_shade_pointsNum = 4;
	ege_point RCDI_button_shade_ployPoints[4] = {
		{RCDI_lefttop_x + RCDI_side / 52 * 35 + RCDI_side / 520 * 2  ,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 3.5 - RCDI_side / 520 * 5},
		{RCDI_lefttop_x + RCDI_side / 52 * 35 + RCDI_side / 520 * 2  ,RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 3 - RCDI_side / 520 * 8},
		{RCDI_lefttop_x + RCDI_side / 52 * 47 + RCDI_side / 520 * 2 ,RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 3 - RCDI_side / 520 * 8},
		{RCDI_lefttop_x + RCDI_side / 52 * 47 + RCDI_side / 520 * 2  ,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 3.5 - RCDI_side / 520 * 5}
	};
	ege_setpattern_lineargradient(RCDI_lefttop_x + RCDI_side / 52 * 35 + RCDI_side / 520 * 2, RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 3.5 - RCDI_side / 520 * 5, EGEARGB(0XFF, 0X12, 0X12, 0X12),
		RCDI_lefttop_x + RCDI_side / 52 * 47 + RCDI_side / 520 * 2, RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 3 - RCDI_side / 520 * 8, EGEARGB(0X5F, 0X12, 0X12, 0X12));
	ege_fillpoly(RCDI_button_shade_pointsNum, RCDI_button_shade_ployPoints);
	ege_setpattern_none();


	setcolor(EGEARGB(0XFF, 0X21, 0X21, 0X23));
	setlinewidth(3);
	int RCDI_button_frame_pointsNum = 25;
	ege_point RCDI_button_frame_polyPoints[25] = {
		{RCDI_lefttop_x + RCDI_side / 52 * 48.3 + RCDI_side / 520 * 8 , RCDI_lefttop_y + RCDI_side / 52 * 6 + RCDI_side / 520 * 5},
		{RCDI_lefttop_x + RCDI_side / 52 * 48.3 + RCDI_side / 520 * 8 , RCDI_lefttop_y + RCDI_side / 52 * 6 + RCDI_side / 520 * 5},
		{RCDI_lefttop_x + RCDI_side / 52 * 48.3 + RCDI_side / 520 * 8 , RCDI_lefttop_y + RCDI_side / 52 * 6 + RCDI_side / 520 * 5},

		{ RCDI_lefttop_x + RCDI_side / 520 * 493  , RCDI_lefttop_y + RCDI_side / 52 * 37 },
		{RCDI_lefttop_x + RCDI_side / 520 * 482   ,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 9 + RCDI_side / 520 * 5},
		{RCDI_lefttop_x + RCDI_side / 520 * 442   ,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 5 - RCDI_side / 520 * 5},
		{RCDI_lefttop_x + RCDI_side / 520 * 392   ,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 3.5 - RCDI_side / 520 * 5},

		{RCDI_lefttop_x + RCDI_side / 52 * 35 + RCDI_side / 520 * 8  ,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 3.5 - RCDI_side / 520 * 5},
		{RCDI_lefttop_x + RCDI_side / 52 * 35 + RCDI_side / 520 * 8  ,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 3.5 - RCDI_side / 520 * 5},
		{RCDI_lefttop_x + RCDI_side / 52 * 35 + RCDI_side / 520 * 8  ,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 3.5 - RCDI_side / 520 * 5},

		{RCDI_lefttop_x + RCDI_side / 52 * 35 + RCDI_side / 520 * 8  ,RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 2.1 - RCDI_side / 520 * 6},
		{RCDI_lefttop_x + RCDI_side / 52 * 35 + RCDI_side / 520 * 8  ,RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 2.1 - RCDI_side / 520 * 6},
		{RCDI_lefttop_x + RCDI_side / 52 * 35 + RCDI_side / 520 * 8  ,RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 2.1 - RCDI_side / 520 * 6},

		{RCDI_lefttop_x + RCDI_side - RCDI_side / 26 * 2 ,RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 2.1 - RCDI_side / 520 * 6},
		{RCDI_lefttop_x + RCDI_side - RCDI_side / 26 * 2 ,RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 2.1 - RCDI_side / 520 * 6},
		{RCDI_lefttop_x + RCDI_side - RCDI_side / 26 * 2 ,RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 2.1 - RCDI_side / 520 * 6},

		{RCDI_lefttop_x + RCDI_side + RCDI_side / 52 * 3 + RCDI_side / 520.0 * 5,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3},
		{RCDI_lefttop_x + RCDI_side + RCDI_side / 52 * 3 + RCDI_side / 520.0 * 5,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3},
		{RCDI_lefttop_x + RCDI_side + RCDI_side / 52 * 3 + RCDI_side / 520.0 * 5,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3},

		{RCDI_lefttop_x + RCDI_side + RCDI_side / 52 * 3 + RCDI_side / 520.0 * 5,RCDI_lefttop_y + RCDI_side / 52 * 6 + RCDI_side / 520 * 5},
		{RCDI_lefttop_x + RCDI_side + RCDI_side / 52 * 3 + RCDI_side / 520.0 * 5,RCDI_lefttop_y + RCDI_side / 52 * 6 + RCDI_side / 520 * 5},
		{RCDI_lefttop_x + RCDI_side + RCDI_side / 52 * 3 + RCDI_side / 520.0 * 5,RCDI_lefttop_y + RCDI_side / 52 * 6 + RCDI_side / 520 * 5},

		{RCDI_lefttop_x + RCDI_side / 52 * 48.3 + RCDI_side / 520 * 8 , RCDI_lefttop_y + RCDI_side / 52 * 6 + RCDI_side / 520 * 5},
		{RCDI_lefttop_x + RCDI_side / 52 * 48.3 + RCDI_side / 520 * 8 , RCDI_lefttop_y + RCDI_side / 52 * 6 + RCDI_side / 520 * 5},
		{RCDI_lefttop_x + RCDI_side / 52 * 48.3 + RCDI_side / 520 * 8 , RCDI_lefttop_y + RCDI_side / 52 * 6 + RCDI_side / 520 * 5}
	};
	ege_bezier(RCDI_button_frame_pointsNum, RCDI_button_frame_polyPoints);
	setfillcolor(EGEARGB(0XFF, 0X21, 0X21, 0X23));
	floodfill(RCDI_lefttop_x + RCDI_side / 52 * 50.5 + RCDI_side / 520 * 8, RCDI_lefttop_y + RCDI_side / 52 * 40 + RCDI_side / 520 * 5, EGEARGB(0XFF, 0X21, 0X21, 0X23));
	setfillcolor(EGEARGB(0XFF, 0X11, 0X11, 0X11));
	ege_fillellipse(RCDI_lefttop_x + RCDI_side / 52 * 35 + RCDI_side / 520 * 8, RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 3.5 - RCDI_side / 520 * 5, RCDI_side / 52 * 2, RCDI_side / 52 * 2);
	ege_fillellipse(RCDI_x + R + RCDI_side / 52 * 9, RCDI_y - RCDI_side / 52, RCDI_side / 52 * 2, RCDI_side / 52 * 2);
	ege_fillellipse(RCDI_x + R + RCDI_side / 52 * 9, RCDI_y - RCDI_side / 52 * 19, RCDI_side / 52 * 2, RCDI_side / 52 * 2);
	ege_fillellipse(RCDI_x + R + RCDI_side / 52 * 8, RCDI_y + RCDI_side / 52 * 15, RCDI_side / 52 * 2, RCDI_side / 52 * 2);

	setcolor(BLACK);
	setlinewidth(RCDI_side / 520);
	ege_rectangle(RCDI_lefttop_x + RCDI_side / 52 * 37 + RCDI_side / 520 * 8, RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 1.5 - RCDI_side / 520 * 5, RCDI_side / 52 * 5, RCDI_side / 52 * 3);
	ege_rectangle(RCDI_x + R + RCDI_side / 52 * 8, RCDI_y + RCDI_side / 52 * 9, RCDI_side / 52 * 3, RCDI_side / 52 * 5);
	ege_rectangle(RCDI_x + R + RCDI_side / 52 * 8, RCDI_y - RCDI_side / 52 * 9, RCDI_side / 52 * 3, RCDI_side / 52 * 5);

	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillrect(RCDI_x + R + RCDI_side / 52 * 8, RCDI_y - RCDI_side / 52 * 15, RCDI_side / 52 * 3, RCDI_side / 52 * 5);
	ege_fillrect(RCDI_x + R + RCDI_side / 52 * 8, RCDI_y + RCDI_side / 52 * 3, RCDI_side / 52 * 3, RCDI_side / 52 * 5);


	//setfillcolor(EGEARGB(0XFF, 0X60, 0X60, 0X60));
	ege_setpattern_lineargradient(RCDI_x + R + RCDI_side / 52 * 8.5, RCDI_y - RCDI_side / 52 * 15.5, EGEARGB(0XFF, 0X60, 0X60, 0X60),
		RCDI_x + R + RCDI_side / 52 * 11.5, RCDI_y - RCDI_side / 52 * 10.5, EGEARGB(0XFF, 0X21, 0X21, 0X23));
	ege_fillrect(RCDI_x + R + RCDI_side / 52 * 8.5, RCDI_y - RCDI_side / 52 * 15.5, RCDI_side / 52 * 3, RCDI_side / 52 * 5);

	ege_setpattern_lineargradient(RCDI_x + R + RCDI_side / 52 * 8.5, RCDI_y + RCDI_side / 52 * 2.5, EGEARGB(0XFF, 0X60, 0X60, 0X60),
		RCDI_x + R + RCDI_side / 52 * 11.5, RCDI_y + RCDI_side / 52 * 7.5, EGEARGB(0XFF, 0X21, 0X21, 0X23));
	ege_fillrect(RCDI_x + R + RCDI_side / 52 * 8.5, RCDI_y + RCDI_side / 52 * 2.5, RCDI_side / 52 * 3, RCDI_side / 52 * 5);

	ege_setpattern_none();


	setfillcolor(EGEARGB(0XFF, 0X27, 0X27, 0X29));
	ege_fillrect(RCDI_x + R + RCDI_side / 52 * 8.3, RCDI_y - RCDI_side / 52 * 15.3, RCDI_side / 52 * 3, RCDI_side / 52 * 5);

	ege_fillrect(RCDI_x + R + RCDI_side / 52 * 8.3, RCDI_y + RCDI_side / 52 * 2.7, RCDI_side / 52 * 3, RCDI_side / 52 * 5);

	setcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	setlinewidth(RCDI_side / 520.0 * 4);
	ege_line(RCDI_lefttop_x + RCDI_side / 52 * 36 + RCDI_side / 520 * 8, RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 3.5 - RCDI_side / 520 * 5, RCDI_lefttop_x + RCDI_side / 52 * 36 + RCDI_side / 520 * 8, RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 1.5 - RCDI_side / 520 * 5);
	ege_line(RCDI_lefttop_x + RCDI_side / 52 * 35 + RCDI_side / 520 * 8, RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 2.5 - RCDI_side / 520 * 5, RCDI_lefttop_x + RCDI_side / 52 * 37 + RCDI_side / 520 * 8, RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 2.5 - RCDI_side / 520 * 5);
	ege_line(RCDI_x + R + RCDI_side / 52 * 10, RCDI_y - RCDI_side / 52, RCDI_x + R + RCDI_side / 52 * 10, RCDI_y + RCDI_side / 52);
	ege_line(RCDI_x + R + RCDI_side / 52 * 9, RCDI_y, RCDI_x + R + RCDI_side / 52 * 11, RCDI_y);
	ege_line(RCDI_x + R + RCDI_side / 52 * 10, RCDI_y - RCDI_side / 52 * 19, RCDI_x + R + RCDI_side / 52 * 10, RCDI_y - RCDI_side / 52 * 17);
	ege_line(RCDI_x + R + RCDI_side / 52 * 9, RCDI_y - RCDI_side / 52 * 18, RCDI_x + R + RCDI_side / 52 * 11, RCDI_y - RCDI_side / 52 * 18);
	ege_line(RCDI_x + R + RCDI_side / 52 * 9, RCDI_y + RCDI_side / 52 * 15, RCDI_x + R + RCDI_side / 52 * 9, RCDI_y + RCDI_side / 52 * 17);
	ege_line(RCDI_x + R + RCDI_side / 52 * 8, RCDI_y + RCDI_side / 52 * 16, RCDI_x + R + RCDI_side / 52 * 10, RCDI_y + RCDI_side / 52 * 16);


	//
	if (GetAsyncKeyState(0x02) & 0x8000) {
		if (RCDI_speed_is_down == 0) {
			RCDI_speed_is_down = 1;
			mousepos(&RCDI_mouse_x, &RCDI_mouse_y);
			RCDI_mouse_x_cur = RCDI_mouse_x;
			RCDI_mouse_y_cur = RCDI_mouse_y;
		}
		if (RCDI_speed_is_down == 1) {
			if ((RCDI_mouse_x_cur >= RCDI_lefttop_x + RCDI_side - RCDI_side / 52 * 6 - RCDI_side / 520.0 * 8 + RCDI_side / 208) && (RCDI_mouse_x_cur <=  RCDI_lefttop_x + RCDI_side - RCDI_side / 52 * 6 - RCDI_side / 520.0 * 8 + RCDI_side / 208 + RCDI_side / 104 * 13)
				&& (RCDI_mouse_y_cur >= RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 2.1 - RCDI_side / 520 * 10 - RCDI_side / 52 * 10 + RCDI_side / 208) && (RCDI_mouse_y_cur <= RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 2.1 - RCDI_side / 520 * 10 - RCDI_side / 52 * 10 + RCDI_side / 208 + RCDI_side / 104 * 13)) {
				
				mousepos(&RCDI_mouse_x, &RCDI_mouse_y);
				if (RCDI_mouse_y < RCDI_mouse_y_cur) {
					konb_angle += (RCDI_mouse_y - RCDI_mouse_y_cur) / 70;
					if (choice_light < 155) {
						choice_light += 1;
					}
				}
				else {
					konb_angle += (RCDI_mouse_y - RCDI_mouse_y_cur) / 70;
					if (choice_light > 0) {
						choice_light -= 1;
					}
				}
			}
		}

	}
	else if (RCDI_speed_is_down == 1) {
		RCDI_speed_is_down = 0;
	}

	//绘制旋钮
	
	//高光
	int RCDI_knob_light_pointsNum = 4;
	ege_point RCDI_konb_light_ploypoints[4] = {
		{RCDI_lefttop_x + RCDI_side - RCDI_side / 52 * 4 + RCDI_side / 520.0 * 2 ,RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 2.1 - RCDI_side / 520 * 6 - RCDI_side / 520.0 * 3},
		{RCDI_lefttop_x + RCDI_side + RCDI_side / 52 * 3 + RCDI_side / 520.0 * 5 + RCDI_side / 520.0 * 2,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 6 - RCDI_side / 520.0 * 3},
		{RCDI_lefttop_x + RCDI_side - RCDI_side / 52 * 6 + RCDI_side / 520.0 + RCDI_side / 520.0 * 2,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 12 - RCDI_side / 520.0 * 2},
		{RCDI_lefttop_x + RCDI_side - RCDI_side / 52 * 11 - RCDI_side / 520.0 * 4 + RCDI_side / 520.0 * 2,RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 2.1 - RCDI_side / 520 * 6 - RCDI_side / 26 * 5 - RCDI_side / 520.0 * 2}
	};
	ege_setpattern_lineargradient(RCDI_lefttop_x + RCDI_side - RCDI_side / 52 * 11 - RCDI_side / 520.0 * 4, RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 2.1 - RCDI_side / 520 * 6 - RCDI_side / 26 * 5, EGEARGB(0XFF, 0X60, 0X60, 0X60),
		RCDI_lefttop_x + RCDI_side + RCDI_side / 52 * 4 + RCDI_side / 520.0 * 5, RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 5, EGEARGB(0XFF, 0X21, 0X21, 0X23));
	ege_fillpoly(RCDI_knob_light_pointsNum, RCDI_konb_light_ploypoints);
	ege_setpattern_none();
	//阴影
	
	int RCDI_knob_shade_pointsNum = 4;
	
	ege_point RCDI_knob_shade_ploypoints[4] = {
		{RCDI_lefttop_x + RCDI_side - RCDI_side / 52 * 4 - RCDI_side / 520.0 * 4 ,RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 2.1 - RCDI_side / 520 * 6 + RCDI_side / 520.0 * 5},
		{RCDI_lefttop_x + RCDI_side + RCDI_side / 52 * 3 + RCDI_side / 520.0 * 5 - RCDI_side / 520.0 * 4,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 6 + RCDI_side / 520.0 * 5},
		{RCDI_lefttop_x + RCDI_side - RCDI_side / 52 * 6 + RCDI_side / 520.0 - RCDI_side / 520.0 * 4,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 12 + RCDI_side / 520.0 * 4},
		{RCDI_lefttop_x + RCDI_side - RCDI_side / 52 * 11 - RCDI_side / 520.0 * 4 - RCDI_side / 520.0 * 4,RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 2.1 - RCDI_side / 520 * 6 - RCDI_side / 26 * 5 + RCDI_side / 520.0 * 4}
	};
	ege_setpattern_lineargradient(RCDI_lefttop_x + RCDI_side - RCDI_side / 52 * 6 + RCDI_side / 520.0 - RCDI_side / 520.0 * 2, RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 12 + RCDI_side / 520.0 * 2, EGEARGB(0XFF, 0X00, 0X00, 0X00),
		RCDI_lefttop_x + RCDI_side + RCDI_side / 52 * 3 + RCDI_side / 520.0 * 5 - RCDI_side / 520.0 * 2, RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 6 + RCDI_side / 520.0 * 3, EGEARGB(0XFF, 0X00, 0X00, 0X00));
	
	ege_fillpoly(RCDI_knob_shade_pointsNum, RCDI_knob_shade_ploypoints);
	
	ege_setpattern_none();


	setfillcolor(EGEARGB(0XFF, 0X18, 0X1B, 0X1D));
	int RCDI_knob_pointsNum = 4;
	ege_point RCDI_konb_ploypoints[4] = {
		{RCDI_lefttop_x + RCDI_side - RCDI_side / 26 * 2 ,RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 2.1 - RCDI_side / 520 * 6},
		{RCDI_lefttop_x + RCDI_side + RCDI_side / 52 * 3 + RCDI_side / 520.0 * 5,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 3},
		{RCDI_lefttop_x + RCDI_side - RCDI_side / 52 * 6 + RCDI_side / 520.0 ,RCDI_lefttop_y + RCDI_side - RCDI_side / 26 * 6},
		{RCDI_lefttop_x + RCDI_side - RCDI_side / 52 * 11  - RCDI_side / 520.0 * 4,RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 2.1 - RCDI_side / 520 * 6 -RCDI_side / 26 * 5}
	};
	ege_fillpoly(RCDI_knob_pointsNum, RCDI_konb_ploypoints);

	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillellipse(RCDI_lefttop_x + RCDI_side - RCDI_side / 52 * 6 - RCDI_side / 520.0 * 8, RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 2.1 - RCDI_side / 520 * 10 - RCDI_side / 52 * 10,
		RCDI_side / 52 * 7 ,RCDI_side / 52 * 7);
	
	setfillcolor(EGEARGB(0XFF, 0X12, 0X17, 0X1D));
	ege_fillellipse(RCDI_lefttop_x + RCDI_side - RCDI_side / 52 * 6 - RCDI_side / 520.0 * 8 + RCDI_side / 208, RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 2.1 - RCDI_side / 520 * 10 - RCDI_side / 52 * 10 + RCDI_side / 208,
		RCDI_side / 104 * 13, RCDI_side / 104 * 13);

	setfillcolor(EGEARGB(0XFF, 0X23, 0X27, 0X29));
	ege_fillellipse(RCDI_lefttop_x + RCDI_side - RCDI_side / 52 * 6 - RCDI_side / 520.0 * 8 + RCDI_side / 52, RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 2.1 - RCDI_side / 520 * 10 - RCDI_side / 52 * 10 + RCDI_side / 52,
		RCDI_side / 104 * 10, RCDI_side / 104 * 10);

	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillellipse(RCDI_lefttop_x + RCDI_side - RCDI_side / 52 * 6 - RCDI_side / 520.0 * 8 + RCDI_side / 104 * 5, RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 2.1 - RCDI_side / 520 * 10 - RCDI_side / 52 * 10 + RCDI_side / 104 * 5,
		RCDI_side / 52 * 2, RCDI_side / 52 * 2);

	setfillcolor(EGEARGB(0XFF, 0X31, 0X37, 0X3A));
	ege_fillellipse(RCDI_lefttop_x + RCDI_side - RCDI_side / 52 * 6 - RCDI_side / 520.0 * 8 + RCDI_side / 416 * 21, RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 2.1 - RCDI_side / 520 * 10 - RCDI_side / 52 * 10 + RCDI_side / 416 * 21,
		RCDI_side / 208 * 7 , RCDI_side / 208 * 7 );

	setcolor(EGEARGB(0XFF, 0X31, 0X37, 0X3A));

	for (int j = 0; j < 360; j += 45) {
		ege_line(RCDI_lefttop_x + RCDI_side - RCDI_side / 52 * 6 - RCDI_side / 520.0 * 8 + RCDI_side / 416 * 28 - (RCDI_side / 52) * cos((j + konb_angle) * PI / 180), 
			RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 2.1 - RCDI_side / 520 * 10 - RCDI_side / 52 * 10 + RCDI_side / 416 * 28 - (RCDI_side / 52) * sin((j + konb_angle) * PI / 180),
			RCDI_lefttop_x + RCDI_side - RCDI_side / 52 * 6 - RCDI_side / 520.0 * 8 + RCDI_side / 416 * 28 - (RCDI_side / 208 * 9) * cos((j + konb_angle) * PI / 180),
			RCDI_lefttop_y + RCDI_side + RCDI_side / 52 * 2.1 - RCDI_side / 520 * 10 - RCDI_side / 52 * 10 + RCDI_side / 416 * 28 - (RCDI_side / 208 * 9) * sin((j + konb_angle) * PI / 180)
			);
	}
	//表盘绘制
	

	setcolor(EGEARGB(0XFF, (int)(choice_light / 3), (int)(choice_light / 3), (int)(choice_light / 3)));
	setlinewidth(4);
	int RCDI_dial_pointsNum = 25;
	ege_point RCDI_polypoints_dial[25] = { {RCDI_lefttop_x + RCDI_side / 52 * 4.5 + RCDI_side / 520 * 5 - RCDI_side / 26, RCDI_lefttop_y + RCDI_side / 52 * 8 + RCDI_side / 520 * 5},{RCDI_lefttop_x + RCDI_side / 52 * 3.5 + RCDI_side / 520 * 5  , RCDI_lefttop_y + RCDI_side / 52 * 6 + RCDI_side / 520 * 5},
		{RCDI_lefttop_x + RCDI_side / 52 * 4 + RCDI_side / 520 * 5  , RCDI_lefttop_y + RCDI_side / 52 * 5.5 + RCDI_side / 520 * 5},{RCDI_lefttop_x + RCDI_side / 52 * 6 + RCDI_side / 520 * 5  , RCDI_lefttop_y + RCDI_side / 52 * 4.5 + RCDI_side / 520 * 5},

		{RCDI_lefttop_x + RCDI_side / 52 * 44 + RCDI_side / 520 * 8  , RCDI_lefttop_y + RCDI_side / 52 * 4.5 + RCDI_side / 520 * 5},{RCDI_lefttop_x + RCDI_side / 52 * 44 + RCDI_side / 520 * 8  , RCDI_lefttop_y + RCDI_side / 52 * 4.5 + RCDI_side / 520 * 5},

	{RCDI_lefttop_x + RCDI_side / 52 * 44 + RCDI_side / 520 * 8  , RCDI_lefttop_y + RCDI_side / 52 * 4.5 + RCDI_side / 520 * 5}, {RCDI_lefttop_x + RCDI_side / 52 * 46 + RCDI_side / 520 * 8  , RCDI_lefttop_y + RCDI_side / 52 * 5.5 + RCDI_side / 520 * 5 },
		{RCDI_lefttop_x + RCDI_side / 52 * 47.5 + RCDI_side / 520 * 8  , RCDI_lefttop_y + RCDI_side / 52 * 6 + RCDI_side / 520 * 5}, {RCDI_lefttop_x + RCDI_side / 52 * 47.5 + RCDI_side / 520 * 8 , RCDI_lefttop_y + RCDI_side / 52 * 8 + RCDI_side / 520 * 5 } ,

		{ RCDI_lefttop_x + RCDI_side / 52 * 47.5 + RCDI_side / 520 * 8  , RCDI_lefttop_y + RCDI_side / 52 * 36 },{ RCDI_lefttop_x + RCDI_side / 52 * 47.5 + RCDI_side / 520 * 8  , RCDI_lefttop_y + RCDI_side / 52 * 36 },

	{ RCDI_lefttop_x + RCDI_side / 52 * 47.5 + RCDI_side / 520 * 8  , RCDI_lefttop_y + RCDI_side / 52 * 36 },{RCDI_lefttop_x + RCDI_side / 52 * 47 + RCDI_side / 520 * 8  ,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 10 + RCDI_side / 520 * 5},
		{RCDI_lefttop_x + RCDI_side / 52 * 43 + RCDI_side / 520 * 8  ,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 6 - RCDI_side / 520 * 5},{RCDI_lefttop_x + RCDI_side / 52 * 38 + RCDI_side / 520 * 8  ,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 4.5 - RCDI_side / 520 * 5} ,

		{RCDI_lefttop_x + RCDI_side / 52 * 38 + RCDI_side / 520 * 8  ,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 4.5 - RCDI_side / 520 * 5},{RCDI_lefttop_x + RCDI_side / 52 * 38 + RCDI_side / 520 * 8  ,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 4.5 - RCDI_side / 520 * 5},

	{RCDI_lefttop_x + RCDI_side / 26 * 6 + RCDI_side / 520 * 5  ,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 4.5 - RCDI_side / 520 * 5} ,{RCDI_lefttop_x + RCDI_side / 52 * 7 + RCDI_side / 520 * 5  ,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 6 - RCDI_side / 520 * 5},
		{RCDI_lefttop_x + RCDI_side / 52 * 3 + RCDI_side / 520 * 5  ,RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 10 + RCDI_side / 520 * 5},{RCDI_lefttop_x + RCDI_side / 52 * 2.5 + RCDI_side / 520 * 5  , RCDI_lefttop_y + RCDI_side / 52 * 36 - RCDI_side / 520 * 5},

	{RCDI_lefttop_x + RCDI_side / 52 * 2.5 + RCDI_side / 520 * 5 , RCDI_lefttop_y + RCDI_side / 52 * 8 + RCDI_side / 520 * 5},{RCDI_lefttop_x + RCDI_side / 52 * 2.5 + RCDI_side / 520 * 5  , RCDI_lefttop_y + RCDI_side / 26 * 4 + RCDI_side / 520 * 5},
		{RCDI_lefttop_x + RCDI_side / 52 * 2.5 + RCDI_side / 520 * 5  , RCDI_lefttop_y + RCDI_side / 52 * 8 + RCDI_side / 520 * 5} };

	ege_bezier(RCDI_dial_pointsNum, RCDI_polypoints_dial);
	setfillcolor(EGEARGB(0XFF, (int)(choice_light / 3), (int)(choice_light / 3), (int)(choice_light / 3)));
	floodfill(RCDI_x, RCDI_y, EGEARGB(0XFF, (int)(choice_light / 3), (int)(choice_light / 3), (int)(choice_light / 3)));
	ege_setpattern_none();

	//白色圆绘制
	setcolor(EGEARGB(choice_light + 100, 0XFF, 0XFF, 0XFF));
	setlinewidth(RCDI_side / 520.0 * 2);
	ege_ellipse(RCDI_x - R, RCDI_y - R, 2 * R, 2 * R);


	//刻度绘制
	setcolor(EGEARGB(choice_light + 100, 0XFF, 0XFF, 0XFF));//刻度颜色
	setlinewidth(big_scales_width);//绘制最粗且最长的刻度
	ege_line(RCDI_x - R, RCDI_y, RCDI_x - R - small_scales_longth, RCDI_y);
	ege_line(RCDI_x - R * cos(70 * PI / 180.0), RCDI_y + R * sin(70 * PI / 180.0), RCDI_x - (R + big_scales_longth) * cos(70 * PI / 180.0), RCDI_y + (R + big_scales_longth) * sin(70 * PI / 180.0));
	ege_line(RCDI_x - R * cos(70 * PI / 180.0), RCDI_y - R * sin(70 * PI / 180.0), RCDI_x - (R + big_scales_longth) * cos(70 * PI / 180.0), RCDI_y - (R + big_scales_longth) * sin(70 * PI / 180.0));
	ege_line(RCDI_x - R * cos(106 * PI / 180.0), RCDI_y + R * sin(106 * PI / 180.0), RCDI_x - (R + big_scales_longth) * cos(106 * PI / 180.0), RCDI_y + (R + big_scales_longth) * sin(106 * PI / 180.0));
	ege_line(RCDI_x - R * cos(106 * PI / 180.0), RCDI_y - R * sin(106 * PI / 180.0), RCDI_x - (R + big_scales_longth) * cos(106 * PI / 180.0), RCDI_y - (R + big_scales_longth) * sin(106 * PI / 180.0));
	ege_line(RCDI_x - R * cos(124 * PI / 180.0), RCDI_y - R * sin(124 * PI / 180.0), RCDI_x - (R + big_scales_longth) * cos(124 * PI / 180.0), RCDI_y - (R + big_scales_longth) * sin(124 * PI / 180.0));
	ege_line(RCDI_x - R * cos(124 * PI / 180.0), RCDI_y + R * sin(124 * PI / 180.0), RCDI_x - (R + big_scales_longth) * cos(124 * PI / 180.0), RCDI_y + (R + big_scales_longth) * sin(124 * PI / 180.0));
	ege_line(RCDI_x - R * cos(140 * PI / 180.0), RCDI_y - R * sin(140 * PI / 180.0), RCDI_x - (R + big_scales_longth) * cos(140 * PI / 180.0), RCDI_y - (R + big_scales_longth) * sin(140 * PI / 180.0));
	ege_line(RCDI_x - R * cos(140 * PI / 180.0), RCDI_y + R * sin(140 * PI / 180.0), RCDI_x - (R + big_scales_longth) * cos(140 * PI / 180.0), RCDI_y + (R + big_scales_longth) * sin(140 * PI / 180.0));
	ege_line(RCDI_x - R * cos(156 * PI / 180.0), RCDI_y - R * sin(156 * PI / 180.0), RCDI_x - (R + big_scales_longth) * cos(156 * PI / 180.0), RCDI_y - (R + big_scales_longth) * sin(156 * PI / 180.0));
	ege_line(RCDI_x - R * cos(156 * PI / 180.0), RCDI_y + R * sin(156 * PI / 180.0), RCDI_x - (R + big_scales_longth) * cos(156 * PI / 180.0), RCDI_y + (R + big_scales_longth) * sin(156 * PI / 180.0));
	ege_line(RCDI_x - R * cos(170 * PI / 180.0), RCDI_y - R * sin(170 * PI / 180.0), RCDI_x - (R + big_scales_longth) * cos(170 * PI / 180.0), RCDI_y - (R + big_scales_longth) * sin(170 * PI / 180.0));
	ege_line(RCDI_x - R * cos(170 * PI / 180.0), RCDI_y + R * sin(170 * PI / 180.0), RCDI_x - (R + big_scales_longth) * cos(170 * PI / 180.0), RCDI_y + (R + big_scales_longth) * sin(170 * PI / 180.0));


	setlinewidth(medium_scales_width);//绘制中等粗且中等长的刻度
	ege_line(RCDI_x - R * cos(35 * PI / 180.0), RCDI_y - R * sin(35 * PI / 180.0), RCDI_x - (R + medium_scales_longth) * cos(35 * PI / 180.0), RCDI_y - (R + medium_scales_longth) * sin(35 * PI / 180.0));
	ege_line(RCDI_x - R * cos(35 * PI / 180.0), RCDI_y + R * sin(35 * PI / 180.0), RCDI_x - (R + medium_scales_longth) * cos(35 * PI / 180.0), RCDI_y + (R + medium_scales_longth) * sin(35 * PI / 180.0));
	ege_line(RCDI_x - R * cos(88 * PI / 180.0), RCDI_y - R * sin(88 * PI / 180.0), RCDI_x - (R + medium_scales_longth) * cos(88 * PI / 180.0), RCDI_y - (R + medium_scales_longth) * sin(88 * PI / 180.0));
	ege_line(RCDI_x - R * cos(88 * PI / 180.0), RCDI_y + R * sin(88 * PI / 180.0), RCDI_x - (R + medium_scales_longth) * cos(88 * PI / 180.0), RCDI_y + (R + medium_scales_longth) * sin(88 * PI / 180.0));
	ege_line(RCDI_x - R * cos(115 * PI / 180.0), RCDI_y - R * sin(115 * PI / 180.0), RCDI_x - (R + medium_scales_longth) * cos(115 * PI / 180.0), RCDI_y - (R + medium_scales_longth) * sin(115 * PI / 180.0));
	ege_line(RCDI_x - R * cos(115 * PI / 180.0), RCDI_y + R * sin(115 * PI / 180.0), RCDI_x - (R + medium_scales_longth) * cos(115 * PI / 180.0), RCDI_y + (R + medium_scales_longth) * sin(115 * PI / 180.0));
	ege_line(RCDI_x - R * cos(132 * PI / 180.0), RCDI_y - R * sin(132 * PI / 180.0), RCDI_x - (R + medium_scales_longth) * cos(132 * PI / 180.0), RCDI_y - (R + medium_scales_longth) * sin(132 * PI / 180.0));
	ege_line(RCDI_x - R * cos(132 * PI / 180.0), RCDI_y + R * sin(132 * PI / 180.0), RCDI_x - (R + medium_scales_longth) * cos(132 * PI / 180.0), RCDI_y + (R + medium_scales_longth) * sin(132 * PI / 180.0));
	ege_line(RCDI_x - R * cos(148 * PI / 180.0), RCDI_y - R * sin(148 * PI / 180.0), RCDI_x - (R + medium_scales_longth) * cos(148 * PI / 180.0), RCDI_y - (R + medium_scales_longth) * sin(148 * PI / 180.0));
	ege_line(RCDI_x - R * cos(148 * PI / 180.0), RCDI_y + R * sin(148 * PI / 180.0), RCDI_x - (R + medium_scales_longth) * cos(148 * PI / 180.0), RCDI_y + (R + medium_scales_longth) * sin(148 * PI / 180.0));
	ege_line(RCDI_x - R * cos(163 * PI / 180.0), RCDI_y - R * sin(163 * PI / 180.0), RCDI_x - (R + medium_scales_longth) * cos(163 * PI / 180.0), RCDI_y - (R + medium_scales_longth) * sin(163 * PI / 180.0));
	ege_line(RCDI_x - R * cos(163 * PI / 180.0), RCDI_y + R * sin(163 * PI / 180.0), RCDI_x - (R + medium_scales_longth) * cos(163 * PI / 180.0), RCDI_y + (R + medium_scales_longth) * sin(163 * PI / 180.0));

	setlinewidth(small_scales_width);//绘制短且细的刻度
	for (double angle = 7; angle < 30; angle = angle + 7) {
		ege_line(RCDI_x - R * cos(angle * PI / 180.0), RCDI_y - R * sin(angle * PI / 180.0), RCDI_x - (R + small_scales_longth) * cos(angle * PI / 180.0), RCDI_y - (R + small_scales_longth) * sin(angle * PI / 180.0));
	}
	for (double angle = 7; angle < 30; angle = angle + 7) {
		ege_line(RCDI_x - R * cos(angle * PI / 180.0), RCDI_y + R * sin(angle * PI / 180.0), RCDI_x - (R + small_scales_longth) * cos(angle * PI / 180.0), RCDI_y + (R + small_scales_longth) * sin(angle * PI / 180.0));
	}



	for (double angle = 42; angle < 70; angle = angle + 7) {
		ege_line(RCDI_x - R * cos(angle * PI / 180.0), RCDI_y - R * sin(angle * PI / 180.0), RCDI_x - (R + small_scales_longth) * cos(angle * PI / 180.0), RCDI_y - (R + small_scales_longth) * sin(angle * PI / 180.0));
	}
	for (double angle = 42; angle < 70; angle = angle + 7) {
		ege_line(RCDI_x - R * cos(angle * PI / 180.0), RCDI_y + R * sin(angle * PI / 180.0), RCDI_x - (R + small_scales_longth) * cos(angle * PI / 180.0), RCDI_y + (R + small_scales_longth) * sin(angle * PI / 180.0));
	}

	//绘制数字
	setbkmode(TRANSPARENT);
	setcolor(EGEARGB(0XFF, choice_light + 100, choice_light + 100, choice_light + 100));
	setfont(figure_height, figure_weight, "微软雅黑");
	xyprintf(RCDI_x - R - RCDI_side / 52 * 4, RCDI_y - RCDI_side / 52 * 2, "0");
	xyprintf(RCDI_x - R * cos(35 * PI / 180.0) - RCDI_side / 52 * 4.1, RCDI_y - RCDI_side / 26 * 6.5, ".5");
	xyprintf(RCDI_x - R * cos(35 * PI / 180.0) - RCDI_side / 52 * 4.1, RCDI_y + RCDI_side / 26 * 4.5, ".5");
	xyprintf(RCDI_x - R * cos(70 * PI / 180.0) - RCDI_side / 52 * 3, RCDI_y - RCDI_side / 26 * 10.2, "1");
	xyprintf(RCDI_x - R * cos(70 * PI / 180.0) - RCDI_side / 52 * 3, RCDI_y + RCDI_side / 26 * 8.2, "1");
	xyprintf(RCDI_x - R * cos(106 * PI / 180.0) + RCDI_side / 52 * 1.5, RCDI_y - RCDI_side / 26 * 10.5, "2");
	xyprintf(RCDI_x - R * cos(106 * PI / 180.0) + RCDI_side / 52 * 1.5, RCDI_y + RCDI_side / 26 * 8.5, "2");
	xyprintf(RCDI_x - R * cos(140 * PI / 180.0) + RCDI_side / 52 * 2.7, RCDI_y - RCDI_side / 26 * 7.5, "4");
	xyprintf(RCDI_x - R * cos(140 * PI / 180.0) + RCDI_side / 52 * 2.7, RCDI_y + RCDI_side / 26 * 5.5, "4");
	xyprintf(RCDI_x + R + RCDI_side / 52 * 2.5, RCDI_y - RCDI_side / 52 * 2, "6");


	setcolor(EGEARGB(0XFF, 0XBB, 0XBB, 0XBB));
	setfont(char_height, char_weight, "微软雅黑", 0, 0, RCDI_side / 52 * 90, 0, 0, 0);
	xyprintf(RCDI_lefttop_x + RCDI_side / 52 * 37 + RCDI_side / 520 * 18, RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 1.5 - RCDI_side / 520 * 5, "BRT");
	xyprintf(RCDI_x + R + RCDI_side / 52 * 7.8 + RCDI_side / 520 * 4, RCDI_y + RCDI_side / 52 * 10, "DN");
	xyprintf(RCDI_x + R + RCDI_side / 52 * 8.3, RCDI_y - RCDI_side / 52 * 8, "UP");
	
	setcolor(EGEARGB(0XFF, 0XBB, 0XC1, 0X2B));
	setfont(char_height + RCDI_side / 520 * 10, char_weight + RCDI_side / 520 * 2 , "微软雅黑", 0, 0, RCDI_side / 52 * 80, 0, 0, 0);
	xyprintf(RCDI_x - R -RCDI_side / 520 * 34, RCDI_y + R - RCDI_side / 520 * 25, "NO TCAS");
	
	//指针绘制
	draw_pointer(RCDI_x, RCDI_y, R, verticalRate / 1000);

	//螺丝绘制
	draw_screw(RCDI_lefttop_x - RCDI_side / 52 * 2, RCDI_lefttop_y, RCDI_side / 52 * 2, 20);
	draw_screw(RCDI_lefttop_x + RCDI_side / 52 * 2 + RCDI_side, RCDI_lefttop_y, RCDI_side / 52 * 2, 20);
	draw_screw(RCDI_lefttop_x - RCDI_side / 52 * 2, RCDI_lefttop_y + RCDI_side, RCDI_side / 52 * 2, 20);
	draw_screw(RCDI_lefttop_x + RCDI_side / 52 * 2 + RCDI_side, RCDI_lefttop_y + RCDI_side, RCDI_side / 52 * 2, 20);

	//绘制小飞机

	setcolor(EGEARGB(0XFF, 0X5E, 0XB2, 0XB4));
	setlinewidth(RCDI_side / 520.0 * 2);
	ege_line(RCDI_x, RCDI_y + R / 2 - R / 40 * 3, RCDI_x, RCDI_y + R / 2 - R / 40 * 6);
	ege_line(RCDI_x - R / 40 * 1, RCDI_y + R / 2 - R / 40 * 3 , RCDI_x + R / 40 * 1, RCDI_y + R / 2 - R / 40 * 3);
	ege_line(RCDI_x, RCDI_y + R / 2 - R / 40 * 5, RCDI_x - R / 40 * 1.7, RCDI_y + R / 2 - R / 40 * 4.2);
	ege_line(RCDI_x, RCDI_y + R / 2 - R / 40 * 5, RCDI_x + R / 40 * 1.7, RCDI_y + R / 2 - R / 40 * 4.2);

	setcolor(WHITE);
	if (x > RCDI_x + R + RCDI_side / 52 * 8.3 && x< RCDI_x + R + RCDI_side / 52 * 11.3 &&
		y>RCDI_y - RCDI_side / 52 * 15.3 && y < RCDI_y - RCDI_side / 52 * 10.3) {
		ege_rectangle(RCDI_x + R + RCDI_side / 52 * 8.3, RCDI_y - RCDI_side / 52 * 15.3, RCDI_side / 52 * 3, RCDI_side / 52 * 5);
		if (GetAsyncKeyState(0x04) & 0x0001) {
			if (RNG > 8) {

				RNG = RNG - 12;

			}
		}
	}
		if (x > RCDI_x + R + RCDI_side / 52 * 8.3 && x< RCDI_x + R + RCDI_side / 52 * 11.3 &&
			y>RCDI_y + RCDI_side / 52 * 2.7 && y < RCDI_y + RCDI_side / 52 * 7.7) {
			ege_rectangle(RCDI_x + R + RCDI_side / 52 * 8.3, RCDI_y + RCDI_side / 52 * 2.7, RCDI_side / 52 * 3, RCDI_side / 52 * 5);
			if (GetAsyncKeyState(0x04) & 0x0001) {
				if (RNG < 68) {
					RNG = RNG + 12;
				}
			}
		}
		setcolor(EGEARGB(choice_light, 0X5E, 0XB2, 0XB4));
		setfont(char_height + RCDI_side / 520 * 12, char_weight + RCDI_side / 520 * 5, "微软雅黑", 0, 0, RCDI_side / 52 * 80, 0, 0, 0);
		if (RNG == 8) {
			xyprintf(RCDI_x + R - RCDI_side / 520 * 70, RCDI_y - R - RCDI_side / 520 * 40, "RNG 40");
		}
		if (RNG == 20) {
			xyprintf(RCDI_x + R - RCDI_side / 520 * 70, RCDI_y - R - RCDI_side / 520 * 40, "RNG 30");
		}
		if (RNG == 32) {
			xyprintf(RCDI_x + R - RCDI_side / 520 * 70, RCDI_y - R - RCDI_side / 520 * 40, "RNG 20");
		}
		if (RNG == 44) {
			xyprintf(RCDI_x + R - RCDI_side / 520 * 70, RCDI_y - R - RCDI_side / 520 * 40, "RNG 10");
		}
		if (RNG == 56) {
			xyprintf(RCDI_x + R - RCDI_side / 520 * 70, RCDI_y - R - RCDI_side / 520 * 40, "RNG 5");
		}
		if (RNG == 68) {
			xyprintf(RCDI_x + R - RCDI_side / 520 * 70, RCDI_y - R - RCDI_side / 520 * 40, "RNG 3");
		}
	setfillcolor(EGEARGB(0XFF, 0X5E, 0XB2, 0XB4));
	for (int i = 0; i <= 360; i += 30)
	{
		ege_fillellipse(RCDI_x - RNG * RCDI_side / 520  * 1.5 * cos(i * PI / 180), RCDI_y + R / 2 - R / 40 * 4.5 - RNG *RCDI_side / 520 * 1.5 * sin(i * PI / 180), R / 40, R / 40);
	}
	

}
//速度到角度的转换
double CalAngle(double verticalRate) {
	double angle = 0;
	if (verticalRate >= 0 && verticalRate <= 1) {
		angle = 70.0 * verticalRate;
	}
	else if (verticalRate > 1 && verticalRate <= 2) {
		angle = 70.0 + (verticalRate - 1) * 36;
	}
	else if (verticalRate > 2 && verticalRate <= 3) {
		angle = 106.0 + (verticalRate - 2) * 18;
	}
	else if (verticalRate > 3 && verticalRate <= 4) {
		angle = 124.0 + (verticalRate - 3) * 16;
	}
	else if (verticalRate > 4 && verticalRate <= 5) {
		angle = 140.0 + (verticalRate - 4) * 16;
	}
	else if (verticalRate > 5 && verticalRate <= 6) {
		angle = 156.0 + (verticalRate - 5) * 14;
	}
	else if (verticalRate > 6) {
		angle = 170 ;
	}else if (verticalRate <= 0 && verticalRate >= -1) {
		angle = -(70.0 * -verticalRate);
	}
	else if (verticalRate >= -2 && verticalRate < -1) {
		angle = -(70.0 + (-verticalRate - 1) * 36);
	}
	else if (verticalRate >= -3 && verticalRate < -2) {
		angle = -(106.0 + (-verticalRate - 2) * 18);
	}
	else if (verticalRate >= -4 && verticalRate < -3) {
		angle = -(124.0 + (-verticalRate - 3) * 16);
	}
	else if (verticalRate >= -5 && verticalRate < -4) {
		angle = -(140.0 + (-verticalRate - 4) * 16);
	}
	else if (verticalRate >= -6 && verticalRate < -5) {
		angle = -(156.0 + (-verticalRate - 5) * 14);
	}
	else { angle = -170 ; }


	return angle;
}
void draw_pointer(double RCDI_X, double RCDI_Y, double RCDI_R, double verticalRate) {



		double Angle = CalAngle(verticalRate) * PI / 180;
		setfillcolor(EGEARGB(choice_light + 100, 0XFF, 0XFF, 0XFF));

		int RCDI_pointer_num_points = 7;
		ege_point RCDI_pointer_polypoints[7] = {
			{ -RCDI_R / 52 * sin(Angle) + RCDI_X ,RCDI_R / 52 * cos(Angle) + RCDI_Y},
			{ RCDI_R / 52 * sin(Angle) + RCDI_X ,-RCDI_R / 52 * cos(Angle) + RCDI_Y},
			{-RCDI_R / 52 * 40 * cos(Angle) + RCDI_R / 52 * sin(Angle) + RCDI_X,-RCDI_R / 52 * cos(Angle) - RCDI_R / 52 * 40 * sin(Angle) + RCDI_Y},
			{-RCDI_R / 52 * 40 * cos(Angle) + RCDI_R / 26 * sin(Angle) + RCDI_X,-RCDI_R / 26 * cos(-Angle) - RCDI_R / 52 * 40 * sin(Angle) + RCDI_Y},
			{-RCDI_R * cos(Angle) + RCDI_X,-RCDI_R * sin(Angle) + RCDI_Y},
			{-RCDI_R / 52 * 40 * cos(Angle) - RCDI_R / 26 * sin(Angle) + RCDI_X,RCDI_R / 26 * cos(Angle) - RCDI_R / 52 * 40 * sin(Angle) + RCDI_Y},
			{-RCDI_R / 52 * 40 * cos(Angle) - RCDI_R / 52 * sin(Angle) + RCDI_X,RCDI_R / 52 * cos(Angle) - RCDI_R / 52 * 40 * sin(Angle) + RCDI_Y}
		};
		ege_fillpoly(RCDI_pointer_num_points, RCDI_pointer_polypoints);
		ege_setpattern_none();
}


void draw_screw(double screw_x, double screw_y, double screw_r, double angle) {

	ege_setpattern_lineargradient(
		screw_x - screw_r, screw_y - screw_r, EGEARGB(200, 255, 255, 255),
		screw_x + screw_r, screw_y + screw_r, EGEARGB(0xff, 0x1b, 0x20, 0x25)
	);
	ege_fillellipse(
		screw_x - screw_r * 0.97, screw_y - screw_r * 1.03, 2 * screw_r * 1, 2 * screw_r * 1
	);


	ege_setpattern_lineargradient(
		screw_x - screw_r, screw_y - screw_r, EGEARGB(200, 0, 0, 0),
		screw_x + screw_r, screw_y + screw_r, EGEARGB(0xff, 0x1b, 0x20, 0x25)
	);
	ege_fillellipse(
		screw_x - screw_r * 1.03, screw_y - screw_r * 0.97, 2 * screw_r * 1, 2 * screw_r * 1
	);

	// 倒数第二层
	ege_setpattern_lineargradient(
		screw_x - screw_r, screw_y - screw_r, EGEARGB(0XFF, 0X1F, 0X23, 0X2C),
		screw_x + screw_r, screw_y + screw_r, EGEARGB(0XFF, 0X17, 0X1A, 0X24)
	);
	ege_fillellipse(
		screw_x - screw_r, screw_y - screw_r, 2 * screw_r, 2 * screw_r
	);

	// 绘制中间螺丝
	angle = -angle;
	angle = angle * PI / 180;

	double x01 = -screw_r * 0.7, y01 = -screw_r * 0.2;
	double x02 = -screw_r * 0.7, y02 = +screw_r * 0.2;
	double x03 = +screw_r * 0.7, y03 = +screw_r * 0.2;
	double x04 = +screw_r * 0.7, y04 = -screw_r * 0.2;

	ege_setpattern_lineargradient(
		x01 * cos(angle) - y01 * sin(angle) + screw_x, x01 * sin(angle) + y01 * cos(angle) + screw_y, BLACK,
		x03 * cos(angle) - y03 * sin(angle) + screw_x, x03 * sin(angle) + y03 * cos(angle) + screw_y, BLACK
	);
	ege_point polypoints1[4] = {
		{x01 * cos(angle) - y01 * sin(angle) + screw_x,x01 * sin(angle) + y01 * cos(angle) + screw_y},// 左上
		{x02 * cos(angle) - y02 * sin(angle) + screw_x,x02 * sin(angle) + y02 * cos(angle) + screw_y},// 右上
		{x03 * cos(angle) - y03 * sin(angle) + screw_x,x03 * sin(angle) + y03 * cos(angle) + screw_y},// 右下
		{x04 * cos(angle) - y04 * sin(angle) + screw_x,x04 * sin(angle) + y04 * cos(angle) + screw_y} // 左下
	};
	ege_fillpoly(4, polypoints1);


	double x11 = -screw_r * 0.2, y11 = -screw_r * 0.7;
	double x12 = -screw_r * 0.2, y12 = +screw_r * 0.7;
	double x13 = +screw_r * 0.2, y13 = +screw_r * 0.7;
	double x14 = +screw_r * 0.2, y14 = -screw_r * 0.7;

	ege_setpattern_lineargradient(
		x11 * cos(angle) - y11 * sin(angle) + screw_x, x11 * sin(angle) + y11 * cos(angle) + screw_y, BLACK,
		x13 * cos(angle) - y13 * sin(angle) + screw_x, x13 * sin(angle) + y13 * cos(angle) + screw_y, BLACK
	);
	ege_point polypoints2[4] = {
		{x11 * cos(angle) - y11 * sin(angle) + screw_x,x11 * sin(angle) + y11 * cos(angle) + screw_y},// 左上
		{x12 * cos(angle) - y12 * sin(angle) + screw_x,x12 * sin(angle) + y12 * cos(angle) + screw_y},// 右上
		{x13 * cos(angle) - y13 * sin(angle) + screw_x,x13 * sin(angle) + y13 * cos(angle) + screw_y},// 右下
		{x14 * cos(angle) - y14 * sin(angle) + screw_x,x14 * sin(angle) + y14 * cos(angle) + screw_y} // 左下
	};
	ege_fillpoly(4, polypoints2);


	// 螺丝中间菱形
	double x21 = -screw_r * 0.53, y21 = 0;
	double x22 = 0, y22 = +screw_r * 0.53;
	double x23 = +screw_r * 0.53, y23 = 0;
	double x24 = 0, y24 = -screw_r * 0.53;
	setcolor(BLACK);
	ege_setpattern_lineargradient(
		x21 * cos(angle) - y21 * sin(angle) + screw_x, x21 * sin(angle) + y21 * cos(angle) + screw_y, BLACK,
		x23 * cos(angle) - y23 * sin(angle) + screw_x, x23 * sin(angle) + y23 * cos(angle) + screw_y, BLACK
	);
	ege_point polypoints5[5] = {
		{x21 * cos(angle) - y21 * sin(angle) + screw_x,x21 * sin(angle) + y21 * cos(angle) + screw_y},// 上
		{x22 * cos(angle) - y22 * sin(angle) + screw_x,x22 * sin(angle) + y22 * cos(angle) + screw_y},// 右
		{x23 * cos(angle) - y23 * sin(angle) + screw_x,x23 * sin(angle) + y23 * cos(angle) + screw_y},// 下
		{x24 * cos(angle) - y24 * sin(angle) + screw_x,x24 * sin(angle) + y24 * cos(angle) + screw_y},//左
		{x21 * cos(angle) - y21 * sin(angle) + screw_x,x21 * sin(angle) + y21 * cos(angle) + screw_y}
	};
	ege_fillpoly(5, polypoints5);

	ege_setpattern_none();
}
extern double RMI_point_angle_2;//粗指针
extern double RMI_frame_angle;//表盘
extern double RMI_point_angle_1;//细指针
extern double RMI_point_angle_3;//偏移量
extern int RMI_change;//左按钮变化
extern int RMI_change_1;//右按钮变化
void draw_RMI(double RMI_x, double RMI_y, double RMI_side) {

	double RMI_r = RMI_side / 28 * 13;
	double R = RMI_r / 52 * 38;
	double triangle_R = RMI_r / 52 * 46;
	double length_1 = RMI_r / 52 * 8;//长刻度
	double length_2 = RMI_r / 52 * 6;//中刻度
	double length_3 = RMI_r / 52 * 4;//短刻度
	double triangle_height = RMI_r / 52 * 4;
	double side2 = RMI_side * 13 / 14;
	double lefttop_x = RMI_x - side2 / 2.0;
	double lefttop_y = RMI_y - side2 / 2.0;
	double R2 = side2 / 52.0 * 21;//表盘半径
	double R1 = side2 / 52.0 * 22;//表盘阴影半径
	int x, y;
	mousepos(&x, &y);




	setcolor(EGEARGB(0X4F, 0X00, 0X00, 0X00));
	setlinewidth(5);
	int RCDI_frame_edge_pointsNum = 16;
	ege_point RCDI_frame_edge_polyPoints[16] = { {lefttop_x + side2 / 26 * 3,lefttop_y - side2 / 26},{lefttop_x - side2 / 26 ,lefttop_y + side2 / 26 * 3},

		{lefttop_x - side2 / 26 ,lefttop_y + side2 / 26 * 3},{lefttop_x - side2 / 26 ,lefttop_y + side2 / 26 * 3},

		{lefttop_x - side2 / 26,lefttop_y + side2 - side2 / 26 * 3},{lefttop_x - side2 / 26,lefttop_y + side2 - side2 / 26 * 3},

		{lefttop_x - side2 / 26,lefttop_y + side2 - side2 / 26 * 3},{lefttop_x + side2 / 26 * 3,lefttop_y + side2 + side2 / 26},


		{lefttop_x + side2 / 26 * 3,lefttop_y + side2 + side2 / 26},{lefttop_x + side2 / 26 * 3,lefttop_y + side2 + side2 / 26},

		{lefttop_x + side2 - side2 / 26 * 3,lefttop_y + side2 + side2 / 26},{lefttop_x + side2 - side2 / 26 * 3,lefttop_y + side2 + side2 / 26},

		{lefttop_x + side2 - side2 / 26 * 3,lefttop_y + side2 + side2 / 26},{lefttop_x + side2 + side2 / 26,lefttop_y + side2 - side2 / 26 * 3},

		{lefttop_x + side2 + side2 / 26,lefttop_y + side2 - side2 / 26 * 3},{lefttop_x + side2 + side2 / 26,lefttop_y + side2 - side2 / 26 * 3}


	};
	ege_bezier(RCDI_frame_edge_pointsNum, RCDI_frame_edge_polyPoints);


	int num_points2 = 4;
	ege_point polypoints2[4] = {
		{lefttop_x + side2 / 26 * 3 + side2 / 250,lefttop_y - side2 / 26 - side2 / 250},
		{lefttop_x + side2 - side2 / 26 * 3 + side2 / 250,lefttop_y - side2 / 26 - side2 / 250},
		{lefttop_x + side2 + side2 / 26 + side2 / 250,lefttop_y + side2 / 26 * 3 - side2 / 250} ,
		{lefttop_x + side2 + side2 / 26 + side2 / 250,lefttop_y + side2 - side2 / 26 * 3 - side2 / 250}
	};

	ege_setpattern_lineargradient(lefttop_x + side2 / 26 * 3 + side2 / 250, lefttop_y - side2 / 26 - side2 / 250, EGEARGB(0X6F, 0XFF, 0XFF, 0XFF),
		lefttop_x + side2 + side2 / 26 + side2 / 250, lefttop_y + side2 - side2 / 26 * 3 - side2 / 250, EGEARGB(0X2F, 0XFF, 0XFF, 0XFF));
	ege_fillpoly(num_points2, polypoints2);
	ege_setpattern_none();


	// 边框颜色
	int num_points3 = 8;
	ege_point polypoints3[8] = {
		{lefttop_x - side2 / 26 ,lefttop_y + side2 / 26 * 3},
		{lefttop_x + side2 / 26 * 3,lefttop_y - side2 / 26},
		{lefttop_x + side2 - side2 / 26 * 3,lefttop_y - side2 / 26},
		{lefttop_x + side2 + side2 / 26,lefttop_y + side2 / 26 * 3},
		{lefttop_x + side2 + side2 / 26,lefttop_y + side2 - side2 / 26 * 3},
		{lefttop_x + side2 - side2 / 26 * 3,lefttop_y + side2 + side2 / 26},
		{lefttop_x + side2 / 26 * 3,lefttop_y + side2 + side2 / 26},
		{lefttop_x - side2 / 26,lefttop_y + side2 - side2 / 26 * 3}
	};
	ege_setpattern_lineargradient(lefttop_x + side2 + side2 / 26, lefttop_y + side2 / 26 * 3, EGEARGB(0XFF, 0X1F, 0X23, 0X2C),
		lefttop_x - side2 / 26, lefttop_y + side2 - side2 / 26 * 3, EGEARGB(0XFF, 0X17, 0X1A, 0X20));
	ege_fillpoly(num_points3, polypoints3);
	ege_setpattern_none();


	//按钮
	ege_enable_aa(false);
	setcolor(BLACK);
	if (RMI_change == 0) {
		int left_pointsNum_1 = 10;
		ege_point left_ploypoints_1[10] = {
			{lefttop_x - side2 / 26 + side2 / 52 * 3,lefttop_y + side2 - side2 / 52 * 5},
			{lefttop_x - side2 / 26 + side2 / 52 * 5,lefttop_y + side2 - side2 / 52 * 2},
			{lefttop_x - side2 / 26 + side2 / 52 * 9,lefttop_y + side2 },
			{lefttop_x - side2 / 26 + side2 / 52 * 10,lefttop_y + side2 - side2 / 26 * 3 },

			{lefttop_x - side2 / 26 + side2 / 52 * 8,lefttop_y + side2 - side2 / 26 * 6},
			{lefttop_x - side2 / 26 + side2 / 52 * 6,lefttop_y + side2 - side2 / 26 * 7},
			{lefttop_x - side2 / 26 + side2 / 52 * 4,lefttop_y + side2 - side2 / 26 * 7},

			{lefttop_x - side2 / 26 + side2 / 52 * 1,lefttop_y + side2 - side2 / 26 * 5},
			{lefttop_x - side2 / 26 + side2 / 52 * 2,lefttop_y + side2 - side2 / 26 * 3},
			{lefttop_x - side2 / 26 + side2 / 52 * 3,lefttop_y + side2 - side2 / 52 * 5}

		};
		ege_bezier(left_pointsNum_1, left_ploypoints_1);
		setfillcolor(BLACK);
		floodfill(lefttop_x - side2 / 26 + side2 / 52 * 3, lefttop_y + side2 - side2 / 52 * 7, BLACK);
	}
	else {
		int left_pointNum_2 = 10;
		ege_point left_ploypoints_2[10]{
			{lefttop_x - side2 / 26 + side2 / 52 * 8,lefttop_y + side2 - side2 / 52 * 8},
			{lefttop_x - side2 / 26 + side2 / 52 * 2,lefttop_y + side2 - side2 / 52 * 8 },
			{lefttop_x - side2 / 26 + side2 / 52 * 3,lefttop_y + side2 + side2 / 52 * 0 },
			{lefttop_x - side2 / 26 + side2 / 52 * 9,lefttop_y + side2 - side2 / 52 * 1 },

			{lefttop_x - side2 / 26 + side2 / 52 * 16,lefttop_y + side2 - side2 / 52 * 1 },
			{lefttop_x - side2 / 26 + side2 / 52 * 17,lefttop_y + side2 - side2 / 52 * 2 },
			{lefttop_x - side2 / 26 + side2 / 52 * 16,lefttop_y + side2 - side2 / 52 * 3 },

			{lefttop_x - side2 / 26 + side2 / 52 * 12,lefttop_y + side2 - side2 / 52 * 7 },
			{lefttop_x - side2 / 26 + side2 / 52 * 9,lefttop_y + side2 - side2 / 52 * 8 },
			{lefttop_x - side2 / 26 + side2 / 52 * 8,lefttop_y + side2 - side2 / 52 * 8}


		};
		ege_bezier(left_pointNum_2, left_ploypoints_2);
		setfillcolor(BLACK);
		floodfill(lefttop_x - side2 / 26 + side2 / 52 * 8, lefttop_y + side2 - side2 / 52 * 7, BLACK);
	}
	if (RMI_change_1 == 0) {
		int right_pointsNum_1 = 10;
		ege_point right_ploypoints_1[10] = {
			{lefttop_x - side2 / 26 - side2 / 52 * 6 + side2,lefttop_y + side2 - side2 / 26 * 3},
			{lefttop_x - side2 / 26 - side2 / 52 * 6 + side2 / 52 * 1 + side2,lefttop_y + side2 },
			{lefttop_x - side2 / 26 - side2 / 52 * 6 + side2 / 52 * 5 + side2,lefttop_y + side2 - side2 / 52 * 2},
			{lefttop_x - side2 / 26 - side2 / 52 * 6 + side2 / 52 * 7 + side2,lefttop_y + side2 - side2 / 26 * 3 },

			{lefttop_x - side2 / 26 - side2 / 52 * 6 + side2 / 52 * 7 + side2,lefttop_y + side2 - side2 / 26 * 3 },
			{lefttop_x - side2 / 26 - side2 / 52 * 6 + side2 / 52 * 10 + side2,lefttop_y + side2 - side2 / 26 * 8 },
			{lefttop_x - side2 / 26 - side2 / 52 * 6 + side2 / 52 * 7 + side2,lefttop_y + side2 - side2 / 26 * 7 },

			{lefttop_x - side2 / 26 - side2 / 52 * 8 + side2 / 52 * 7 + side2,lefttop_y + side2 - side2 / 26 * 7 },
			{lefttop_x - side2 / 26 - side2 / 52 * 13 + side2 / 52 * 7 + side2,lefttop_y + side2 - side2 / 26 * 5 },
			{lefttop_x - side2 / 26 - side2 / 52 * 6 + side2,lefttop_y + side2 - side2 / 26 * 3}

		};
		ege_bezier(right_pointsNum_1, right_ploypoints_1);
		setfillcolor(BLACK);
		floodfill(lefttop_x - side2 / 26 - side2 / 52 * 5 + side2, lefttop_y + side2 - side2 / 26 * 4, BLACK);
	}
	else {
		int right_pointsNum_2 = 10;
		ege_point right_ploypoints_2[10] = {
			{lefttop_x - side2 / 26 - side2 / 52 * 2 + side2,lefttop_y + side2 - side2 / 52 * 1},
			{lefttop_x - side2 / 26 - side2 / 52 * 2 + side2,lefttop_y + side2 - side2 / 52 * 1 },
			{lefttop_x - side2 / 26 - side2 / 52 * 2 + side2 / 52 * 4 + side2,lefttop_y + side2 - side2 / 52 * 5},
			{lefttop_x - side2 / 26 - side2 / 52 * 4 + side2,lefttop_y + side2 - side2 / 52 * 7 },

			{lefttop_x - side2 / 26 - side2 / 52 * 4 + side2,lefttop_y + side2 - side2 / 52 * 7 },
			{lefttop_x - side2 / 26 - side2 / 52 * 10 + side2,lefttop_y + side2 - side2 / 52 * 7 },
			{lefttop_x - side2 / 26 - side2 / 52 * 13 + side2,lefttop_y + side2 - side2 / 52 * 2 },

			{lefttop_x - side2 / 26 - side2 / 52 * 13 + side2,lefttop_y + side2  },
			{lefttop_x - side2 / 26 - side2 / 52 * 10 + side2,lefttop_y + side2 + side2 / 52 * 2 },
			{lefttop_x - side2 / 26 - side2 / 52 * 2 + side2,lefttop_y + side2 - side2 / 52 * 1 }

		};
		ege_bezier(right_pointsNum_2, right_ploypoints_2);
		setfillcolor(BLACK);
		floodfill(lefttop_x - side2 / 26 - side2 / 52 * 2 + side2, lefttop_y + side2 - side2 / 52 * 2, BLACK);
	}
	ege_enable_aa(true);
	setcolor(BLACK);
	if (RMI_change == 0) {
		int left_pointsNum_1_1 = 10;
		ege_point left_ploypoints_1_1[10] = {
			{lefttop_x - side2 / 26 + side2 / 52 * 3,lefttop_y + side2 - side2 / 52 * 5},
			{lefttop_x - side2 / 26 + side2 / 52 * 5,lefttop_y + side2 - side2 / 52 * 2},
			{lefttop_x - side2 / 26 + side2 / 52 * 9,lefttop_y + side2 },
			{lefttop_x - side2 / 26 + side2 / 52 * 10,lefttop_y + side2 - side2 / 26 * 3 },

			{lefttop_x - side2 / 26 + side2 / 52 * 8,lefttop_y + side2 - side2 / 26 * 6},
			{lefttop_x - side2 / 26 + side2 / 52 * 6,lefttop_y + side2 - side2 / 26 * 7},
			{lefttop_x - side2 / 26 + side2 / 52 * 4,lefttop_y + side2 - side2 / 26 * 7},

			{lefttop_x - side2 / 26 + side2 / 52 * 1,lefttop_y + side2 - side2 / 26 * 5},
			{lefttop_x - side2 / 26 + side2 / 52 * 2,lefttop_y + side2 - side2 / 26 * 3},
			{lefttop_x - side2 / 26 + side2 / 52 * 3,lefttop_y + side2 - side2 / 52 * 5}

		};
		ege_bezier(left_pointsNum_1_1, left_ploypoints_1_1);
	}
	else {
		int left_pointsNum_2_1 = 10;
		ege_point left_ploypoints_2_1[10] = {
			{lefttop_x - side2 / 26 + side2 / 52 * 8,lefttop_y + side2 - side2 / 52 * 8},
			{lefttop_x - side2 / 26 + side2 / 52 * 2,lefttop_y + side2 - side2 / 52 * 8 },
			{lefttop_x - side2 / 26 + side2 / 52 * 3,lefttop_y + side2 + side2 / 52 * 0 },
			{lefttop_x - side2 / 26 + side2 / 52 * 9,lefttop_y + side2 - side2 / 52 * 1 },

			{lefttop_x - side2 / 26 + side2 / 52 * 16,lefttop_y + side2 - side2 / 52 * 1 },
			{lefttop_x - side2 / 26 + side2 / 52 * 17,lefttop_y + side2 - side2 / 52 * 2 },
			{lefttop_x - side2 / 26 + side2 / 52 * 16,lefttop_y + side2 - side2 / 52 * 3 },

			{lefttop_x - side2 / 26 + side2 / 52 * 12,lefttop_y + side2 - side2 / 52 * 7 },
			{lefttop_x - side2 / 26 + side2 / 52 * 9,lefttop_y + side2 - side2 / 52 * 8 },
			{lefttop_x - side2 / 26 + side2 / 52 * 8,lefttop_y + side2 - side2 / 52 * 8}

		};
		ege_bezier(left_pointsNum_2_1, left_ploypoints_2_1);
	}
	if (RMI_change_1 == 0) {
		int right_pointsNum_1_1 = 10;
		ege_point right_ploypoints_1_1[10] = {
			{lefttop_x - side2 / 26 - side2 / 52 * 6 + side2,lefttop_y + side2 - side2 / 26 * 3},
			{lefttop_x - side2 / 26 - side2 / 52 * 6 + side2 / 52 * 1 + side2,lefttop_y + side2 },
			{lefttop_x - side2 / 26 - side2 / 52 * 6 + side2 / 52 * 5 + side2,lefttop_y + side2 - side2 / 52 * 2},
			{lefttop_x - side2 / 26 - side2 / 52 * 6 + side2 / 52 * 7 + side2,lefttop_y + side2 - side2 / 26 * 3 },

			{lefttop_x - side2 / 26 - side2 / 52 * 6 + side2 / 52 * 7 + side2,lefttop_y + side2 - side2 / 26 * 3 },
			{lefttop_x - side2 / 26 - side2 / 52 * 6 + side2 / 52 * 10 + side2,lefttop_y + side2 - side2 / 26 * 8 },
			{lefttop_x - side2 / 26 - side2 / 52 * 6 + side2 / 52 * 7 + side2,lefttop_y + side2 - side2 / 26 * 7 },

			{lefttop_x - side2 / 26 - side2 / 52 * 8 + side2 / 52 * 7 + side2,lefttop_y + side2 - side2 / 26 * 7 },
			{lefttop_x - side2 / 26 - side2 / 52 * 13 + side2 / 52 * 7 + side2,lefttop_y + side2 - side2 / 26 * 5 },
			{lefttop_x - side2 / 26 - side2 / 52 * 6 + side2,lefttop_y + side2 - side2 / 26 * 3}

		};
		ege_bezier(right_pointsNum_1_1, right_ploypoints_1_1);
		setcolor(EGEARGB(0XFF, 0X60, 0X60, 0X60));
		setlinewidth(side2 / 520 * 2);
		ege_line(lefttop_x - side2 / 26 * 3.5 + side2, lefttop_y + side2 - side2 / 26 * 3, lefttop_x - side2 / 26 * 2.5 + side2, lefttop_y + side2 - side2 / 26 * 5);
		ege_line(lefttop_x - side2 / 26 * 2.8 + side2, lefttop_y + side2 - side2 / 26 * 5.5, lefttop_x - side2 / 26 * 2.5 + side2, lefttop_y + side2 - side2 / 26 * 5);
		ege_line(lefttop_x - side2 / 26 * 2.8 + side2, lefttop_y + side2 - side2 / 26 * 5.5, lefttop_x - side2 / 26 * 1 + side2, lefttop_y + side2 - side2 / 26 * 6);


		ege_line(lefttop_x - side2 / 26 * 2.5 + side2, lefttop_y + side2 - side2 / 26 * 2, lefttop_x - side2 / 26 * 1.5 + side2, lefttop_y + side2 - side2 / 26 * 4);
		ege_line(lefttop_x - side2 / 26 * 1 + side2, lefttop_y + side2 - side2 / 26 * 3.7, lefttop_x - side2 / 26 * 1.5 + side2, lefttop_y + side2 - side2 / 26 * 4);
		ege_line(lefttop_x - side2 / 26 * 1 + side2, lefttop_y + side2 - side2 / 26 * 3.7, lefttop_x - side2 / 26 * 1 + side2, lefttop_y + side2 - side2 / 26 * 6);
	}
	else {
		int right_pointsNum_2_1 = 10;
		ege_point right_ploypoints_2_1[10] = {
			{lefttop_x - side2 / 26 - side2 / 52 * 2 + side2,lefttop_y + side2 - side2 / 52 * 1},
			{lefttop_x - side2 / 26 - side2 / 52 * 2 + side2,lefttop_y + side2 - side2 / 52 * 1 },
			{lefttop_x - side2 / 26 - side2 / 52 * 2 + side2 / 52 * 4 + side2,lefttop_y + side2 - side2 / 52 * 5},
			{lefttop_x - side2 / 26 - side2 / 52 * 4 + side2,lefttop_y + side2 - side2 / 52 * 7 },

			{lefttop_x - side2 / 26 - side2 / 52 * 4 + side2,lefttop_y + side2 - side2 / 52 * 7 },
			{lefttop_x - side2 / 26 - side2 / 52 * 10 + side2,lefttop_y + side2 - side2 / 52 * 7 },
			{lefttop_x - side2 / 26 - side2 / 52 * 13 + side2,lefttop_y + side2 - side2 / 52 * 2 },

			{lefttop_x - side2 / 26 - side2 / 52 * 13 + side2,lefttop_y + side2  },
			{lefttop_x - side2 / 26 - side2 / 52 * 10 + side2,lefttop_y + side2 + side2 / 52 * 2 },
			{lefttop_x - side2 / 26 - side2 / 52 * 2 + side2,lefttop_y + side2 - side2 / 52 * 1 }

		};
		ege_bezier(right_pointsNum_2_1, right_ploypoints_2_1);
		setcolor(EGEARGB(0XFF, 0X60, 0X60, 0X60));
		setlinewidth(side2 / 520 * 2);
		ege_line(lefttop_x - side2 / 26 - side2 / 52 * 2 + side2, lefttop_y + side2 - side2 / 52 * 3, lefttop_x - side2 / 26 - side2 / 52 * 7 + side2, lefttop_y + side2 - side2 / 52 * 2);
		ege_line(lefttop_x - side2 / 26 - side2 / 52 * 7 + side2, lefttop_y + side2 - side2 / 52 * 2, lefttop_x - side2 / 26 - side2 / 52 * 6.8 + side2, lefttop_y + side2 - side2 / 52 * 1);
		ege_line(lefttop_x - side2 / 26 - side2 / 52 * 6.8 + side2, lefttop_y + side2 - side2 / 52 * 1, lefttop_x - side2 / 26 - side2 / 52 * 10.8 + side2, lefttop_y + side2 - side2 / 52 * 2);


		ege_line(lefttop_x - side2 / 26 - side2 / 52 * 3 + side2, lefttop_y + side2 - side2 / 52 * 5, lefttop_x - side2 / 26 - side2 / 52 * 8 + side2, lefttop_y + side2 - side2 / 52 * 4);
		ege_line(lefttop_x - side2 / 26 - side2 / 52 * 8 + side2, lefttop_y + side2 - side2 / 52 * 4, lefttop_x - side2 / 26 - side2 / 52 * 8.2 + side2, lefttop_y + side2 - side2 / 52 * 5);
		ege_line(lefttop_x - side2 / 26 - side2 / 52 * 8.2 + side2, lefttop_y + side2 - side2 / 52 * 5, lefttop_x - side2 / 26 - side2 / 52 * 10.8 + side2, lefttop_y + side2 - side2 / 52 * 2);
	}



	//左边箭头
	if (RMI_change == 0) {
		int num = 7;
		ege_point polypoints[7] = {
			{lefttop_x - side2 / 26 + side2 / 52 * 6, lefttop_y + side2 - side2 / 52 * 3.1},
			{lefttop_x - side2 / 26 + side2 / 52 * 7, lefttop_y + side2 - side2 / 52 * 3.5},
			{lefttop_x - side2 / 26 + side2 / 52 * 6, lefttop_y + side2 - side2 / 52 * 8.4},
			{lefttop_x - side2 / 26 + side2 / 52 * 7, lefttop_y + side2 - side2 / 52 * 9},
			{lefttop_x - side2 / 26 + side2 / 52 * 5, lefttop_y + side2 - side2 / 52 * 11},
			{lefttop_x - side2 / 26 + side2 / 52 * 4, lefttop_y + side2 - side2 / 52 * 7.5},
			{lefttop_x - side2 / 26 + side2 / 52 * 5, lefttop_y + side2 - side2 / 52 * 8}
		};
		setfillcolor(EGEARGB(0XFF, 0X60, 0X60, 0X60));
		ege_fillpoly(num, polypoints);
	}
	else {
		int num_1 = 7;
		ege_point polypoints_1[7] = {
			{lefttop_x - side2 / 26 + side2 / 52 * 6,lefttop_y + side2 - side2 / 52 * 5},
			{lefttop_x - side2 / 26 + side2 / 52 * 6,lefttop_y + side2 - side2 / 52 * 4},
			{lefttop_x - side2 / 26 + side2 / 52 * 12,lefttop_y + side2 - side2 / 52 * 3},
			{lefttop_x - side2 / 26 + side2 / 52 * 12,lefttop_y + side2 - side2 / 52 * 2},
			{lefttop_x - side2 / 26 + side2 / 52 * 14,lefttop_y + side2 - side2 / 52 * 3.2},
			{lefttop_x - side2 / 26 + side2 / 52 * 12,lefttop_y + side2 - side2 / 52 * 5},
			{lefttop_x - side2 / 26 + side2 / 52 * 12,lefttop_y + side2 - side2 / 52 * 4}
		};
		setfillcolor(EGEARGB(0XFF, 0X60, 0X60, 0X60));
		ege_fillpoly(num_1, polypoints_1);
	}

	// 表盘阴影
	ege_setpattern_lineargradient(RMI_x + R1 * cos(PI / 4), RMI_y - R1 * sin(PI / 4), EGEARGB(0XFF, 0X00, 0X00, 0X00),
		RMI_x - R1 * cos(PI / 4), RMI_y + R1 * sin(PI / 4), EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillellipse(lefttop_x + side2 / 52 * 2, lefttop_y + side2 / 52 * 2, side2 - side2 / 26 * 2, side2 - side2 / 26 * 2);
	ege_setpattern_none();

	// 表盘颜色
	ege_setpattern_lineargradient(RMI_x + R2 * cos(PI / 4), RMI_y - R2 * sin(PI / 4), EGEARGB(0XFF, 0X15, 0X15, 0X15),
		RMI_x - R2 * cos(PI / 4), RMI_y + R2 * sin(PI / 4), EGEARGB(0XFF, 0X10, 0X10, 0X10));

	ege_fillellipse(lefttop_x + side2 / 52 * 3, lefttop_y + side2 / 52 * 3, side2 - side2 / 26 * 3, side2 - side2 / 26 * 3);
	ege_setpattern_none();


	setcolor(WHITE);
	setlinewidth(2);
	for (int i = 0; i <= 360; i += 30) {
		ege_line(RMI_x - R * cos((i + RMI_frame_angle) * PI / 180), RMI_y - R * sin((i + RMI_frame_angle) * PI / 180),
			RMI_x - (R + length_1) * cos((i + RMI_frame_angle) * PI / 180), RMI_y - (R + length_1) * sin((i + RMI_frame_angle) * PI / 180));
	}
	for (int i = 5; i < 360; i += 10) {
		ege_line(RMI_x - R * cos((i + RMI_frame_angle) * PI / 180), RMI_y - R * sin((i + RMI_frame_angle) * PI / 180),
			RMI_x - (R + length_3) * cos((i + RMI_frame_angle) * PI / 180), RMI_y - (R + length_3) * sin((i + RMI_frame_angle) * PI / 180));
	}
	for (int i = 10; i <= 360; i += 10) {
		ege_line(RMI_x - R * cos((i + RMI_frame_angle) * PI / 180), RMI_y - R * sin((i + RMI_frame_angle) * PI / 180),
			RMI_x - (R + length_2) * cos((i + RMI_frame_angle) * PI / 180), RMI_y - (R + length_2) * sin((i + RMI_frame_angle) * PI / 180));
	}
	setcolor(EGEARGB(0XFF, 0X80, 0X80, 0X80));
	ege_line(RMI_x - (R - RMI_side / 520 * 3) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 3) * sin(RMI_point_angle_1 * PI / 180),
		RMI_x - (R - RMI_side / 520 * 33) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 33) * sin(RMI_point_angle_1 * PI / 180));
	ege_line(RMI_x - (R - RMI_side / 520 * 63) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 63) * sin(RMI_point_angle_1 * PI / 180),
		RMI_x - (R - RMI_side / 520 * 93) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 93) * sin(RMI_point_angle_1 * PI / 180));
	ege_line(RMI_x - (R - RMI_side / 520 * 123) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 123) * sin(RMI_point_angle_1 * PI / 180),
		RMI_x - (R - RMI_side / 520 * 153) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 153) * sin(RMI_point_angle_1 * PI / 180));
	ege_line(RMI_x - (R - RMI_side / 520 * 183) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 183) * sin(RMI_point_angle_1 * PI / 180),
		RMI_x - (R - RMI_side / 520 * 213) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 213) * sin(RMI_point_angle_1 * PI / 180));
	ege_line(RMI_x - (R - RMI_side / 520 * 243) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 243) * sin(RMI_point_angle_1 * PI / 180),
		RMI_x - (R - RMI_side / 520 * 273) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 273) * sin(RMI_point_angle_1 * PI / 180));
	ege_line(RMI_x - (R - RMI_side / 520 * 303) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 303) * sin(RMI_point_angle_1 * PI / 180),
		RMI_x - (R - RMI_side / 520 * 333) * cos(RMI_point_angle_1 * PI / 180), RMI_y - (R - RMI_side / 520 * 333) * sin(RMI_point_angle_1 * PI / 180));




	ege_line((-R + RMI_side / 520 * 83) * cos(RMI_point_angle_2 * PI / 180) - (-RMI_side / 104 * 3) * sin(RMI_point_angle_2 * PI / 180) + RMI_x,
		(-RMI_side / 104 * 3) * cos(RMI_point_angle_2 * PI / 180) + (-R + RMI_side / 520 * 83) * sin(RMI_point_angle_2 * PI / 180) + RMI_y,
		(-R + RMI_side / 520 * 263) * cos(RMI_point_angle_2 * PI / 180) - (-RMI_side / 104 * 3) * sin(RMI_point_angle_2 * PI / 180) + RMI_x,
		(-RMI_side / 104 * 3) * cos(RMI_point_angle_2 * PI / 180) + (-R + RMI_side / 520 * 263) * sin(RMI_point_angle_2 * PI / 180) + RMI_y);
	ege_line((-R + RMI_side / 520 * 83) * cos(RMI_point_angle_2 * PI / 180) - (RMI_side / 104 * 3) * sin(RMI_point_angle_2 * PI / 180) + RMI_x,
		(RMI_side / 104 * 3) * cos(RMI_point_angle_2 * PI / 180) + (-R + RMI_side / 520 * 83) * sin(RMI_point_angle_2 * PI / 180) + RMI_y,
		(-R + RMI_side / 520 * 263) * cos(RMI_point_angle_2 * PI / 180) - (RMI_side / 104 * 3) * sin(RMI_point_angle_2 * PI / 180) + RMI_x,
		(RMI_side / 104 * 3) * cos(RMI_point_angle_2 * PI / 180) + (-R + RMI_side / 520 * 263) * sin(RMI_point_angle_2 * PI / 180) + RMI_y);


	for (int j = -45; j < 46; j += 45) {
		setfillcolor(EGEARGB(0XFF, 0XFF, 0XFF, 0XFF));
		int num_points = 3;
		ege_point ploypoints[3] = {
			{RMI_x - (triangle_R - triangle_height) * cos(j * PI / 180),RMI_y - (triangle_R - triangle_height) * sin(j * PI / 180)},
			{RMI_x - triangle_R * cos((j - 2) * PI / 180),RMI_y - triangle_R * sin((j - 2) * PI / 180)},
			{RMI_x - triangle_R * cos((j + 2) * PI / 180),RMI_y - triangle_R * sin((j + 2) * PI / 180)}
		};
		ege_fillpoly(num_points, ploypoints);

	}
	for (int j = 135; j < 226; j += 45) {
		setfillcolor(EGEARGB(0XFF, 0XFF, 0XFF, 0XFF));
		int num_points = 3;
		ege_point ploypoints[3] = {
			{RMI_x - (triangle_R - triangle_height) * cos(j * PI / 180),RMI_y - (triangle_R - triangle_height) * sin(j * PI / 180)},
			{RMI_x - triangle_R * cos((j - 2) * PI / 180),RMI_y - triangle_R * sin((j - 2) * PI / 180)},
			{RMI_x - triangle_R * cos((j + 2) * PI / 180),RMI_y - triangle_R * sin((j + 2) * PI / 180)}
		};
		ege_fillpoly(num_points, ploypoints);
	}
	setfillcolor(EGEARGB(0XFF, 0XFF, 0XFF, 0XFF));
	int num_points_1 = 5;
	ege_point ploypoints_1[5] = {
		{RMI_x , RMI_y - triangle_R + triangle_height},
		{RMI_x - (triangle_R - triangle_height / 2) * cos(88 * PI / 180),RMI_y - (triangle_R - triangle_height / 2) * sin(88 * PI / 180)},
		{RMI_x - (triangle_R - triangle_height / 2) * cos(88 * PI / 180),RMI_y - (triangle_R - triangle_height / 2) * sin(88 * PI / 180) - side2 / 520 * 10},
		{RMI_x - (triangle_R - triangle_height / 2) * cos(92 * PI / 180),RMI_y - (triangle_R - triangle_height / 2) * sin(92 * PI / 180) - side2 / 520 * 10},
		{RMI_x - (triangle_R - triangle_height / 2) * cos(92 * PI / 180),RMI_y - (triangle_R - triangle_height / 2) * sin(92 * PI / 180)}
	};
	ege_fillpoly(num_points_1, ploypoints_1);

	int num_points_2 = 5;
	ege_point ploypoints_2[5] = {
		{RMI_x , RMI_y + triangle_R - triangle_height},
		{RMI_x - (triangle_R - triangle_height / 2) * cos(88 * PI / 180),RMI_y - (triangle_R - triangle_height / 2) * sin(272 * PI / 180)},
		{RMI_x - (triangle_R - triangle_height / 2) * cos(88 * PI / 180),RMI_y - (triangle_R - triangle_height / 2) * sin(272 * PI / 180) + side2 / 520 * 10},
		{RMI_x - (triangle_R - triangle_height / 2) * cos(92 * PI / 180),RMI_y - (triangle_R - triangle_height / 2) * sin(268 * PI / 180) + side2 / 520 * 10},
		{RMI_x - (triangle_R - triangle_height / 2) * cos(92 * PI / 180),RMI_y - (triangle_R - triangle_height / 2) * sin(268 * PI / 180)}
	};
	ege_fillpoly(num_points_1, ploypoints_2);

	setfillcolor(EGEARGB(0XFF, 0X20, 0X20, 0X20));
	ege_fillellipse(RMI_x - RMI_side / 104 * 5, RMI_y - RMI_side / 104 * 5, RMI_side / 52 * 5, RMI_side / 52 * 5);
	setfillcolor(BLACK);
	ege_fillellipse(RMI_x - RMI_side / 104 * 3, RMI_y - RMI_side / 104 * 3, RMI_side / 52 * 3, RMI_side / 52 * 3);
	setfillcolor(EGEARGB(0XFF, 0X20, 0X20, 0X20));
	ege_fillellipse(RMI_x - RMI_side / 416 * 11, RMI_y - RMI_side / 416 * 11, RMI_side / 208 * 11, RMI_side / 208 * 11);

	setfillcolor(EGEARGB(0XFF, 0X80, 0X80, 0X80));
	int num_points_3 = 6;
	ege_point ploypoints_3[6] = {
		{ (-R + RMI_side / 520 * 263) * cos(RMI_point_angle_2 * PI / 180) - (-RMI_side / 208 * 7) * sin(RMI_point_angle_2 * PI / 180) + RMI_x ,
		 (-RMI_side / 208 * 7) * cos(RMI_point_angle_2 * PI / 180) + (-R + RMI_side / 520 * 263) * sin(RMI_point_angle_2 * PI / 180) + RMI_y},
		{(-R + RMI_side / 520 * 288) * cos(RMI_point_angle_2 * PI / 180) - (-RMI_side / 208 * 2) * sin(RMI_point_angle_2 * PI / 180) + RMI_x,
		(-RMI_side / 208 * 2) * cos(RMI_point_angle_2 * PI / 180) + (-R + RMI_side / 520 * 288) * sin(RMI_point_angle_2 * PI / 180) + RMI_y },
		{ (-R + RMI_side / 520 * 343) * cos(RMI_point_angle_2 * PI / 180) - (-RMI_side / 416) * sin(RMI_point_angle_2 * PI / 180) + RMI_x,
		(-RMI_side / 416) * cos(RMI_point_angle_2 * PI / 180) + (-R + RMI_side / 520 * 343) * sin(RMI_point_angle_2 * PI / 180) + RMI_y},
		{ (-R + RMI_side / 520 * 343) * cos(RMI_point_angle_2 * PI / 180) - (RMI_side / 416) * sin(RMI_point_angle_2 * PI / 180) + RMI_x,
		(RMI_side / 416) * cos(RMI_point_angle_2 * PI / 180) + (-R + RMI_side / 520 * 343) * sin(RMI_point_angle_2 * PI / 180) + RMI_y},
		{(-R + RMI_side / 520 * 288) * cos(RMI_point_angle_2 * PI / 180) - (RMI_side / 208 * 2) * sin(RMI_point_angle_2 * PI / 180) + RMI_x,
		(RMI_side / 208 * 2) * cos(RMI_point_angle_2 * PI / 180) + (-R + RMI_side / 520 * 288) * sin(RMI_point_angle_2 * PI / 180) + RMI_y },
		{ (-R + RMI_side / 520 * 263) * cos(RMI_point_angle_2 * PI / 180) - (RMI_side / 208 * 7) * sin(RMI_point_angle_2 * PI / 180) + RMI_x ,
		 (RMI_side / 208 * 7) * cos(RMI_point_angle_2 * PI / 180) + (-R + RMI_side / 520 * 263) * sin(RMI_point_angle_2 * PI / 180) + RMI_y}
	};
	ege_fillpoly(num_points_3, ploypoints_3);

	int num_points_4 = 6;
	ege_point ploypoints_4[6] = {
		{ (-R + RMI_side / 520 * 263) * cos(RMI_point_angle_1 * PI / 180) - (-RMI_side / 208 * 3) * sin(RMI_point_angle_1 * PI / 180) + RMI_x ,
		 (-RMI_side / 208 * 3) * cos(RMI_point_angle_1 * PI / 180) + (-R + RMI_side / 520 * 263) * sin(RMI_point_angle_1 * PI / 180) + RMI_y},
		 {(-R + RMI_side / 520 * 288) * cos(RMI_point_angle_1 * PI / 180) - (-RMI_side / 208) * sin(RMI_point_angle_1 * PI / 180) + RMI_x,
		(-RMI_side / 208) * cos(RMI_point_angle_1 * PI / 180) + (-R + RMI_side / 520 * 288) * sin(RMI_point_angle_1 * PI / 180) + RMI_y },
		{ (-R + RMI_side / 520 * 343) * cos(RMI_point_angle_1 * PI / 180) - (-RMI_side / 416) * sin(RMI_point_angle_1 * PI / 180) + RMI_x,
		(-RMI_side / 416) * cos(RMI_point_angle_1 * PI / 180) + (-R + RMI_side / 520 * 343) * sin(RMI_point_angle_1 * PI / 180) + RMI_y},
		{ (-R + RMI_side / 520 * 343) * cos(RMI_point_angle_1 * PI / 180) - (RMI_side / 416) * sin(RMI_point_angle_1 * PI / 180) + RMI_x,
		(RMI_side / 416) * cos(RMI_point_angle_1 * PI / 180) + (-R + RMI_side / 520 * 343) * sin(RMI_point_angle_1 * PI / 180) + RMI_y},
		{(-R + RMI_side / 520 * 288) * cos(RMI_point_angle_1 * PI / 180) - (RMI_side / 208) * sin(RMI_point_angle_1 * PI / 180) + RMI_x,
		(RMI_side / 208) * cos(RMI_point_angle_1 * PI / 180) + (-R + RMI_side / 520 * 288) * sin(RMI_point_angle_1 * PI / 180) + RMI_y },
		{ (-R + RMI_side / 520 * 263) * cos(RMI_point_angle_1 * PI / 180) - (RMI_side / 208 * 3) * sin(RMI_point_angle_1 * PI / 180) + RMI_x ,
		 (RMI_side / 208 * 3) * cos(RMI_point_angle_1 * PI / 180) + (-R + RMI_side / 520 * 263) * sin(RMI_point_angle_1 * PI / 180) + RMI_y}


	};
	ege_fillpoly(num_points_4, ploypoints_4);


	if (x >= lefttop_x - side2 / 26 + side2 / 52 * 3 && x <= lefttop_x - side2 / 26 + side2 / 52 * 10 &&
		y <= lefttop_y + side2 && y >= lefttop_y + side2 - side2 / 26 * 4) {
		if (GetAsyncKeyState(0x04) & 0x0001) {
			if (RMI_change == 1) {
				RMI_change = 0;
			}
			else {
				RMI_change = 1;
			}
		}
	}
	
	if (x >= lefttop_x - side2 / 26 - side2 / 52 * 6 + side2 && x <= lefttop_x - side2 / 26 + side2 / 52 * 2 + side2 &&
		y <= lefttop_y + side2 - side2 / 52 * 1 && y >= lefttop_y + side2 - side2 / 52 * 7) {
		if (GetAsyncKeyState(0x04) & 0x0001) {
			if (RMI_change_1 == 1) {
				RMI_change_1 = 0;
			}
			else {
				RMI_change_1 = 1;
			}
		}
	}
}

int alert_pullup = 1;
int alert_beloGS = 1;
int alert_ALT = 1;
int alert_MDA = 1;
int alert_autoPilot = 1;

void draw_back(double center_x, double center_y, double unitLength) {
	setcolor(BLACK);
	setlinewidth(unitLength / 10);
	ege_line(center_x - unitLength * 24, center_y - unitLength * 14, center_x - unitLength * 5, center_y - unitLength * 16);
	ege_line(center_x + unitLength * 5, center_y - unitLength * 16, center_x - unitLength * 5, center_y - unitLength * 16);

	ege_line(center_x + unitLength * 5, center_y - unitLength * 16, center_x  + unitLength * 24, center_y - unitLength * 20);

	ege_line(center_x + unitLength * 5, center_y + unitLength * 24, center_x + unitLength * 5, center_y - unitLength * 16);
	ege_line(center_x - unitLength * 5, center_y + unitLength * 24, center_x - unitLength * 5, center_y - unitLength * 16);
	setcolor(EGEARGB(0X20, 0XFF, 0XFF, 0XFF));
	setlinewidth(unitLength / 20);

	ege_line(center_x - unitLength * 24, center_y - unitLength * 14 - unitLength / 20, center_x - unitLength * 5, center_y - unitLength * 16 - unitLength / 20);
	ege_line(center_x + unitLength * 5, center_y - unitLength * 16 - unitLength / 20, center_x - unitLength * 5, center_y - unitLength * 16 - unitLength / 20);

	ege_line(center_x + unitLength * 5, center_y - unitLength * 16 - unitLength / 20, center_x + unitLength * 24, center_y - unitLength * 20);

	ege_line(center_x + unitLength * 5 + unitLength / 20, center_y + unitLength * 24, center_x + unitLength * 5 + unitLength / 20, center_y - unitLength * 16);
	ege_line(center_x - unitLength * 5 - unitLength / 20, center_y + unitLength * 24, center_x - unitLength * 5 - unitLength / 20, center_y - unitLength * 16);


	//阴影
	setfillcolor(BLACK);
	//右2
	ege_fillrect(center_x + unitLength * 5 + unitLength / 20 * 2, center_y - unitLength * 10 - unitLength / 20 * 11, unitLength * 2.46, unitLength * 2.7);
	ege_fillrect(center_x + unitLength * 5 + unitLength / 20 * 2, center_y - unitLength * 13 - unitLength / 20 * 11, unitLength * 2.46, unitLength * 2.7);
	//左1
	ege_fillrect(center_x - unitLength * 13 + unitLength / 20 * 2, center_y - unitLength * 10 - unitLength / 20 * 11, unitLength * 2.46, unitLength * 2.7);
	//左二小矩形
	ege_fillrect(center_x - unitLength * 9 + unitLength / 20 * 3, center_y - unitLength * 9.7 - unitLength / 20 * 7, unitLength * 2.4, unitLength * 1.4);
	ege_fillrect(center_x - unitLength * 9 + unitLength / 20 * 3, center_y - unitLength * 8.6 - unitLength / 20 * 7, unitLength * 2.4, unitLength * 1.4);




	//主体
	setfillcolor(EGEARGB(0XFF, 0X32, 0X15, 0X04));
	//右2
	ege_fillrect(center_x + unitLength * 5 + unitLength / 20 * 5, center_y - unitLength * 10 - unitLength / 20 * 4, unitLength * 2.16, unitLength * 2.1);
	ege_fillrect(center_x + unitLength * 5 + unitLength / 20 * 5, center_y - unitLength * 13 - unitLength / 20 * 4, unitLength * 2.16, unitLength * 2.1);
	//左1
	ege_fillrect(center_x - unitLength * 13 + unitLength / 20 * 5, center_y - unitLength * 10 - unitLength / 20 * 4, unitLength * 2.16, unitLength * 2.1);
	//左二小矩形
	setfillcolor(EGEARGB(0XFF, 0X11, 0X12, 0X14));
	ege_fillrect(center_x - unitLength * 9 + unitLength / 20 * 5, center_y - unitLength * 9.7 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);
	ege_fillrect(center_x - unitLength * 9 + unitLength / 20 * 5, center_y - unitLength * 8.6 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);



	//右小矩形方阵
	ege_enable_aa(false);
	setcolor(EGEARGB(0XFF, 0X22, 0X27, 0X2D));
	int right_pointNums = 25;
	ege_point right_ploypoints[25] = {
		{center_x + unitLength * 8.2, center_y - unitLength * 13.2 - unitLength / 20 * 4},{center_x + unitLength * 8.3, center_y - unitLength * 13.6 - unitLength / 20 * 4},
		{center_x + unitLength * 8.4, center_y - unitLength * 13.7 - unitLength / 20 * 4},{center_x + unitLength * 8.6, center_y - unitLength * 13.8 - unitLength / 20 * 4},

		{center_x + unitLength * 14.1, center_y - unitLength * 13.8 - unitLength / 20 * 4},{center_x + unitLength * 14.1, center_y - unitLength * 13.8 - unitLength / 20 * 4},
		{center_x + unitLength * 14.1, center_y - unitLength * 13.8 - unitLength / 20 * 4},

		{center_x + unitLength * 14.3, center_y - unitLength * 13.7 - unitLength / 20 * 4},{center_x + unitLength * 14.4, center_y - unitLength * 13.6 - unitLength / 20 * 4},
		{center_x + unitLength * 14.5, center_y - unitLength * 13.2 - unitLength / 20 * 4},

		{center_x + unitLength * 14.5, center_y - unitLength * 8.4 - unitLength / 20 * 4},{center_x + unitLength * 14.5, center_y - unitLength * 8.4 - unitLength / 20 * 4},
		{center_x + unitLength * 14.5, center_y - unitLength * 8.4 - unitLength / 20 * 4},

		{center_x + unitLength * 14.4, center_y - unitLength * 8 - unitLength / 20 * 4},{center_x + unitLength * 14.3, center_y - unitLength * 7.9 - unitLength / 20 * 4},
		{center_x + unitLength * 14.1, center_y - unitLength * 7.8 - unitLength / 20 * 4},

		{center_x + unitLength * 8.6, center_y - unitLength * 7.8 - unitLength / 20 * 4},{center_x + unitLength * 8.6, center_y - unitLength * 7.8 - unitLength / 20 * 4},
		{center_x + unitLength * 8.6, center_y - unitLength * 7.8 - unitLength / 20 * 4},

		{center_x + unitLength * 8.4, center_y - unitLength * 7.9 - unitLength / 20 * 4},{center_x + unitLength * 8.3, center_y - unitLength * 8 - unitLength / 20 * 4},
		{center_x + unitLength * 8.2, center_y - unitLength * 8.4 - unitLength / 20 * 4},

		{center_x + unitLength * 8.2, center_y - unitLength * 13.2 - unitLength / 20 * 4},{center_x + unitLength * 8.2, center_y - unitLength * 13.2 - unitLength / 20 * 4},
		{center_x + unitLength * 8.2, center_y - unitLength * 13.2 - unitLength / 20 * 4},

	};
	setfillcolor(EGEARGB(0XFF, 0X22, 0X27, 0X2D));
	ege_bezier(right_pointNums, right_ploypoints);
	floodfill(center_x + unitLength * 10.2, center_y - unitLength * 10.4 - unitLength / 20 * 4, EGEARGB(0XFF, 0X22, 0X27, 0X2D));

	setcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	int right_pointNums_top = 25;
	ege_point right_ploypoints_top[25] = {
		{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},{center_x + unitLength * 9.8, center_y - unitLength * 15.8 - unitLength / 20 * 4},
		{center_x + unitLength * 9.9, center_y - unitLength * 15.9 - unitLength / 20 * 4},{center_x + unitLength * 10.1, center_y - unitLength * 16 - unitLength / 20 * 4},

		{center_x + unitLength * 12.6, center_y - unitLength * 16 - unitLength / 20 * 4},{center_x + unitLength * 12.6, center_y - unitLength * 16 - unitLength / 20 * 4},
		{center_x + unitLength * 12.6, center_y - unitLength * 16 - unitLength / 20 * 4},

		{center_x + unitLength * 12.8, center_y - unitLength * 15.9 - unitLength / 20 * 4},{center_x + unitLength * 12.9, center_y - unitLength * 15.8 - unitLength / 20 * 4},
		{center_x + unitLength * 13, center_y - unitLength * 15.4 - unitLength / 20 * 4},

		{center_x + unitLength * 13, center_y - unitLength * 14.7 - unitLength / 20 * 4},{center_x + unitLength * 13, center_y - unitLength * 14.7 - unitLength / 20 * 4},
		{center_x + unitLength * 13, center_y - unitLength * 14.7 - unitLength / 20 * 4},

		{center_x + unitLength * 12.9, center_y - unitLength * 14.3 - unitLength / 20 * 4},{center_x + unitLength * 12.8, center_y - unitLength * 14.2 - unitLength / 20 * 4},
		{center_x + unitLength * 12.6, center_y - unitLength * 14.1 - unitLength / 20 * 4},

		{center_x + unitLength * 9.9, center_y - unitLength * 14.1 - unitLength / 20 * 4},{center_x + unitLength * 9.9, center_y - unitLength * 14.1 - unitLength / 20 * 4},
		{center_x + unitLength * 9.9, center_y - unitLength * 14.1 - unitLength / 20 * 4},

		{center_x + unitLength * 9.9, center_y - unitLength * 14.2 - unitLength / 20 * 4},{center_x + unitLength * 9.8, center_y - unitLength * 14.3 - unitLength / 20 * 4},
		{center_x + unitLength * 9.7, center_y - unitLength * 14.7 - unitLength / 20 * 4},

		{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},
		{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},

	};
	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_bezier(right_pointNums_top, right_ploypoints_top);
	floodfill(center_x + unitLength * 11.2, center_y - unitLength * 14.4 - unitLength / 20 * 4, EGEARGB(0XFF, 0X00, 0X00, 0X00));


	int center_pointNums_top = 25;
	ege_point center_ploypoints_top[25] = {
		{center_x - unitLength * 3.9, center_y - unitLength * 12.7 - unitLength / 20 * 4},{center_x - unitLength * 3.8, center_y - unitLength * 13.1 - unitLength / 20 * 4},
		{center_x - unitLength * 3.7, center_y - unitLength * 13.2 - unitLength / 20 * 4},{center_x - unitLength * 3.5, center_y - unitLength * 13.3 - unitLength / 20 * 4},

		{center_x + unitLength * 3.1, center_y - unitLength * 13.3 - unitLength / 20 * 4},{center_x + unitLength * 3.1, center_y - unitLength * 13.3 - unitLength / 20 * 4},
		{center_x + unitLength * 3.1, center_y - unitLength * 13.3 - unitLength / 20 * 4},

		{center_x + unitLength * 3.3, center_y - unitLength * 13.2 - unitLength / 20 * 4},{center_x + unitLength * 3.4, center_y - unitLength * 13.1 - unitLength / 20 * 4},
		{center_x + unitLength * 3.5, center_y - unitLength * 12.7 - unitLength / 20 * 4},

		{center_x + unitLength * 3.5, center_y - unitLength * 12.7 - unitLength / 20 * 4},{center_x + unitLength * 3.5, center_y - unitLength * 12.7 - unitLength / 20 * 4},
		{center_x + unitLength * 3.5, center_y - unitLength * 12.7 - unitLength / 20 * 4},

		{center_x + unitLength * 3.4, center_y - unitLength * 12.3 - unitLength / 20 * 4},{center_x + unitLength * 3.3, center_y - unitLength * 12.2 - unitLength / 20 * 4},
		{center_x + unitLength * 3.1, center_y - unitLength * 12.1 - unitLength / 20 * 4},

		{center_x - unitLength * 3.5, center_y - unitLength * 12.1 - unitLength / 20 * 4},{center_x - unitLength * 3.5, center_y - unitLength * 12.1 - unitLength / 20 * 4},
		{center_x - unitLength * 3.5, center_y - unitLength * 12.1 - unitLength / 20 * 4},

		{center_x - unitLength * 3.7, center_y - unitLength * 12.2 - unitLength / 20 * 4},{center_x - unitLength * 3.8, center_y - unitLength * 12.3 - unitLength / 20 * 4},
		{center_x - unitLength * 3.9, center_y - unitLength * 12.7 - unitLength / 20 * 4},

		{center_x - unitLength * 3.9, center_y - unitLength * 12.7 - unitLength / 20 * 4},{center_x - unitLength * 3.9, center_y - unitLength * 12.7 - unitLength / 20 * 4},
		{center_x - unitLength * 3.9, center_y - unitLength * 12.7 - unitLength / 20 * 4}

	};
	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_bezier(center_pointNums_top, center_ploypoints_top);
	floodfill(center_x - unitLength * 1.8, center_y - unitLength * 13.2 - unitLength / 20 * 4, EGEARGB(0XFF, 0X00, 0X00, 0X00));


	setcolor(EGEARGB(0XFF, 0X10, 0X10, 0X10));
	int pointsNum_center = 13;
	ege_point ploypoints_center[13] = {
		{center_x + unitLength * 4 + unitLength / 20 * 2, center_y - unitLength * 9.5 - unitLength / 20 * 11},
		{center_x + unitLength * 5 + unitLength / 20 * 2, center_y - unitLength * 10 - unitLength / 20 * 11},
		{center_x + unitLength * 5 + unitLength / 20 * 2, center_y - unitLength * 10.5 - unitLength / 20 * 11},
		{center_x + unitLength * 4 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20 * 11},

		{center_x - unitLength * 4.2 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20 * 11},
		{center_x - unitLength * 4.2 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20 * 11},
		{center_x - unitLength * 4.2 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20 * 11},

		{center_x - unitLength * 5.2 + unitLength / 20 * 2, center_y - unitLength * 10.5 - unitLength / 20 * 11},
		{center_x - unitLength * 5.2 + unitLength / 20 * 2, center_y - unitLength * 10 - unitLength / 20 * 11},
		{center_x - unitLength * 4.2 + unitLength / 20 * 2, center_y - unitLength * 9.5 - unitLength / 20 * 11},

		{center_x + unitLength * 4 + unitLength / 20 * 2, center_y - unitLength * 9.5 - unitLength / 20 * 11},
		{center_x + unitLength * 4 + unitLength / 20 * 2, center_y - unitLength * 9.5 - unitLength / 20 * 11},
		{center_x + unitLength * 4 + unitLength / 20 * 2, center_y - unitLength * 9.5 - unitLength / 20 * 11}


	};
	setfillcolor(EGEARGB(0XFF, 0X10, 0X10, 0X10));

	ege_bezier(pointsNum_center, ploypoints_center);
	floodfill(center_x - unitLength * 3.2 + unitLength / 20 * 2, center_y - unitLength * 10 - unitLength / 20 * 11, EGEARGB(0XFF, 0X10, 0X10, 0X10));



	ege_enable_aa(true);


	setcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	int right_pointNums_1 = 25;
	ege_point right_ploypoints_1[25] = {
		{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},{center_x + unitLength * 9.8, center_y - unitLength * 15.8 - unitLength / 20 * 4},
		{center_x + unitLength * 9.9, center_y - unitLength * 15.9 - unitLength / 20 * 4},{center_x + unitLength * 10.1, center_y - unitLength * 16 - unitLength / 20 * 4},

		{center_x + unitLength * 12.6, center_y - unitLength * 16 - unitLength / 20 * 4},{center_x + unitLength * 12.6, center_y - unitLength * 16 - unitLength / 20 * 4},
		{center_x + unitLength * 12.6, center_y - unitLength * 16 - unitLength / 20 * 4},

		{center_x + unitLength * 12.8, center_y - unitLength * 15.9 - unitLength / 20 * 4},{center_x + unitLength * 12.9, center_y - unitLength * 15.8 - unitLength / 20 * 4},
		{center_x + unitLength * 13, center_y - unitLength * 15.4 - unitLength / 20 * 4},

		{center_x + unitLength * 13, center_y - unitLength * 14.7 - unitLength / 20 * 4},{center_x + unitLength * 13, center_y - unitLength * 14.7 - unitLength / 20 * 4},
		{center_x + unitLength * 13, center_y - unitLength * 14.7 - unitLength / 20 * 4},

		{center_x + unitLength * 12.9, center_y - unitLength * 14.3 - unitLength / 20 * 4},{center_x + unitLength * 12.8, center_y - unitLength * 14.2 - unitLength / 20 * 4},
		{center_x + unitLength * 12.6, center_y - unitLength * 14.1 - unitLength / 20 * 4},

		{center_x + unitLength * 9.9, center_y - unitLength * 14.1 - unitLength / 20 * 4},{center_x + unitLength * 9.9, center_y - unitLength * 14.1 - unitLength / 20 * 4},
		{center_x + unitLength * 9.9, center_y - unitLength * 14.1 - unitLength / 20 * 4},

		{center_x + unitLength * 9.9, center_y - unitLength * 14.2 - unitLength / 20 * 4},{center_x + unitLength * 9.8, center_y - unitLength * 14.3 - unitLength / 20 * 4},
		{center_x + unitLength * 9.7, center_y - unitLength * 14.7 - unitLength / 20 * 4},

		{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},
		{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},


	};
	ege_bezier(right_pointNums_1, right_ploypoints_1);

	setcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	int right_pointNums_top_1 = 25;
	ege_point right_ploypoints_top_1[25] = {
		{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},{center_x + unitLength * 9.8, center_y - unitLength * 15.8 - unitLength / 20 * 4},
		{center_x + unitLength * 9.9, center_y - unitLength * 15.9 - unitLength / 20 * 4},{center_x + unitLength * 10.1, center_y - unitLength * 16 - unitLength / 20 * 4},

		{center_x + unitLength * 12.6, center_y - unitLength * 16 - unitLength / 20 * 4},{center_x + unitLength * 12.6, center_y - unitLength * 16 - unitLength / 20 * 4},
		{center_x + unitLength * 12.6, center_y - unitLength * 16 - unitLength / 20 * 4},

		{center_x + unitLength * 12.8, center_y - unitLength * 15.9 - unitLength / 20 * 4},{center_x + unitLength * 12.9, center_y - unitLength * 15.8 - unitLength / 20 * 4},
		{center_x + unitLength * 13, center_y - unitLength * 15.4 - unitLength / 20 * 4},

		{center_x + unitLength * 13, center_y - unitLength * 14.7 - unitLength / 20 * 4},{center_x + unitLength * 13, center_y - unitLength * 14.7 - unitLength / 20 * 4},
		{center_x + unitLength * 13, center_y - unitLength * 14.7 - unitLength / 20 * 4},

		{center_x + unitLength * 12.9, center_y - unitLength * 14.3 - unitLength / 20 * 4},{center_x + unitLength * 12.8, center_y - unitLength * 14.2 - unitLength / 20 * 4},
		{center_x + unitLength * 12.6, center_y - unitLength * 14.1 - unitLength / 20 * 4},

		{center_x + unitLength * 9.9, center_y - unitLength * 14.1 - unitLength / 20 * 4},{center_x + unitLength * 9.9, center_y - unitLength * 14.1 - unitLength / 20 * 4},
		{center_x + unitLength * 9.9, center_y - unitLength * 14.1 - unitLength / 20 * 4},

		{center_x + unitLength * 9.9, center_y - unitLength * 14.2 - unitLength / 20 * 4},{center_x + unitLength * 9.8, center_y - unitLength * 14.3 - unitLength / 20 * 4},
		{center_x + unitLength * 9.7, center_y - unitLength * 14.7 - unitLength / 20 * 4},

		{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},
		{center_x + unitLength * 9.7, center_y - unitLength * 15.4 - unitLength / 20 * 4},

	};

	ege_bezier(right_pointNums_top_1, right_ploypoints_top_1);


	setcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	int pointsNum_center_1 = 13;
	ege_point ploypoints_center_1[13] = {
		{center_x + unitLength * 4 + unitLength / 20 * 2, center_y - unitLength * 9.5 - unitLength / 20 * 11},
		{center_x + unitLength * 5 + unitLength / 20 * 2, center_y - unitLength * 10 - unitLength / 20 * 11},
		{center_x + unitLength * 5 + unitLength / 20 * 2, center_y - unitLength * 10.5 - unitLength / 20 * 11},
		{center_x + unitLength * 4 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20 * 11},

		{center_x - unitLength * 4.2 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20 * 11},
		{center_x - unitLength * 4.2 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20 * 11},
		{center_x - unitLength * 4.2 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20 * 11},

		{center_x - unitLength * 5.2 + unitLength / 20 * 2, center_y - unitLength * 10.5 - unitLength / 20 * 11},
		{center_x - unitLength * 5.2 + unitLength / 20 * 2, center_y - unitLength * 10 - unitLength / 20 * 11},
		{center_x - unitLength * 4.2 + unitLength / 20 * 2, center_y - unitLength * 9.5 - unitLength / 20 * 11},

		{center_x + unitLength * 4 + unitLength / 20 * 2, center_y - unitLength * 9.5 - unitLength / 20 * 11},
		{center_x + unitLength * 4 + unitLength / 20 * 2, center_y - unitLength * 9.5 - unitLength / 20 * 11},
		{center_x + unitLength * 4 + unitLength / 20 * 2, center_y - unitLength * 9.5 - unitLength / 20 * 11}


	};
	ege_bezier(pointsNum_center_1, ploypoints_center_1);


	int center_pointNums_top_1 = 25;
	ege_point center_ploypoints_top_1[25] = {
		{center_x - unitLength * 3.9, center_y - unitLength * 12.7 - unitLength / 20 * 4},{center_x - unitLength * 3.8, center_y - unitLength * 13.1 - unitLength / 20 * 4},
		{center_x - unitLength * 3.7, center_y - unitLength * 13.2 - unitLength / 20 * 4},{center_x - unitLength * 3.5, center_y - unitLength * 13.3 - unitLength / 20 * 4},

		{center_x + unitLength * 3.1, center_y - unitLength * 13.3 - unitLength / 20 * 4},{center_x + unitLength * 3.1, center_y - unitLength * 13.3 - unitLength / 20 * 4},
		{center_x + unitLength * 3.1, center_y - unitLength * 13.3 - unitLength / 20 * 4},

		{center_x + unitLength * 3.3, center_y - unitLength * 13.2 - unitLength / 20 * 4},{center_x + unitLength * 3.4, center_y - unitLength * 13.1 - unitLength / 20 * 4},
		{center_x + unitLength * 3.5, center_y - unitLength * 12.7 - unitLength / 20 * 4},

		{center_x + unitLength * 3.5, center_y - unitLength * 12.7 - unitLength / 20 * 4},{center_x + unitLength * 3.5, center_y - unitLength * 12.7 - unitLength / 20 * 4},
		{center_x + unitLength * 3.5, center_y - unitLength * 12.7 - unitLength / 20 * 4},

		{center_x + unitLength * 3.4, center_y - unitLength * 12.3 - unitLength / 20 * 4},{center_x + unitLength * 3.3, center_y - unitLength * 12.2 - unitLength / 20 * 4},
		{center_x + unitLength * 3.1, center_y - unitLength * 12.1 - unitLength / 20 * 4},

		{center_x - unitLength * 3.5, center_y - unitLength * 12.1 - unitLength / 20 * 4},{center_x - unitLength * 3.5, center_y - unitLength * 12.1 - unitLength / 20 * 4},
		{center_x - unitLength * 3.5, center_y - unitLength * 12.1 - unitLength / 20 * 4},

		{center_x - unitLength * 3.7, center_y - unitLength * 12.2 - unitLength / 20 * 4},{center_x - unitLength * 3.8, center_y - unitLength * 12.3 - unitLength / 20 * 4},
		{center_x - unitLength * 3.9, center_y - unitLength * 12.7 - unitLength / 20 * 4},

		{center_x - unitLength * 3.9, center_y - unitLength * 12.7 - unitLength / 20 * 4},{center_x - unitLength * 3.9, center_y - unitLength * 12.7 - unitLength / 20 * 4},
		{center_x - unitLength * 3.9, center_y - unitLength * 12.7 - unitLength / 20 * 4}

	};

	ege_bezier(center_pointNums_top_1, center_ploypoints_top_1);


	setfillcolor(EGEARGB(0XFF, 0X32, 0X15, 0X04));
	ege_fillrect(center_x - unitLength * 3.6 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20 * 7, unitLength * 2.16 / 2.2, unitLength * 2.1 / 2);
	ege_fillrect(center_x - unitLength * 3.6 + unitLength / 20 * 2.2 + unitLength * 2.16 / 2.2, center_y - unitLength * 11 - unitLength / 20 * 7, unitLength * 2.16 / 2.2, unitLength * 2.1 / 2);
	ege_fillrect(center_x - unitLength * 3.6 + unitLength / 20 * 2.4 + unitLength * 2.16 / 2.2 * 2, center_y - unitLength * 11 - unitLength / 20 * 7, unitLength * 2.16 / 2.2, unitLength * 2.1 / 2);
	ege_fillrect(center_x - unitLength * 3.6 + unitLength / 20 * 2.6 + unitLength * 2.16 / 2.2 * 3, center_y - unitLength * 11 - unitLength / 20 * 7, unitLength * 2.16 / 2.2, unitLength * 2.1 / 2);
	ege_fillrect(center_x - unitLength * 3.6 + unitLength / 20 * 2.8 + unitLength * 2.16 / 2.2 * 4, center_y - unitLength * 11 - unitLength / 20 * 7, unitLength * 2.16 / 2.2, unitLength * 2.1 / 2);
	ege_fillrect(center_x - unitLength * 3.6 + unitLength / 20 * 3 + unitLength * 2.16 / 2.2 * 5, center_y - unitLength * 11 - unitLength / 20 * 7, unitLength * 2.16 / 2.2, unitLength * 2.1 / 2);
	ege_fillrect(center_x - unitLength * 3.6 + unitLength / 20 * 3.2 + unitLength * 2.16 / 2.2 * 6, center_y - unitLength * 11 - unitLength / 20 * 7, unitLength * 2.16 / 2.2, unitLength * 2.1 / 2);


	setcolor(EGEARGB(0XFF, 0X4A, 0X51, 0X52));
	setfont(unitLength * 0.55, unitLength * 0.18, "微软雅黑", 0, 0, unitLength, 0, 0, 0);
	xyprintf(center_x - unitLength * 3 + unitLength / 20, center_y - unitLength * 10.7 - unitLength / 20 * 7, "MON");
	xyprintf(center_x - unitLength * 3 + unitLength / 20, center_y - unitLength * 10.7, "PWR");
	xyprintf(center_x - unitLength * 2 + unitLength / 20, center_y - unitLength * 10.7 - unitLength / 20 * 2, "HOG");
	xyprintf(center_x - unitLength * 1 + unitLength / 20, center_y - unitLength * 10.7 - unitLength / 20 * 2, "PLLCH");
	xyprintf(center_x + unitLength / 20 * 3, center_y - unitLength * 10.7 - unitLength / 20 * 2, "ROLL");
	xyprintf(center_x + unitLength * 1 + unitLength / 20, center_y - unitLength * 10.7 - unitLength / 20 * 2, "GS");
	xyprintf(center_x + unitLength * 2 + unitLength / 20, center_y - unitLength * 10.7 - unitLength / 20 * 2, "LGC");
	xyprintf(center_x + unitLength * 3 + unitLength / 20, center_y - unitLength * 10.7 - unitLength / 20 * 2, "ALT");



	draw_screw(center_x + unitLength * 8.7, center_y - unitLength * 12.6 - unitLength / 20 * 4, unitLength / 3, 0);
	draw_screw(center_x + unitLength * 8.7, center_y - unitLength * 9 - unitLength / 20 * 4, unitLength / 3, 0);
	draw_screw(center_x + unitLength * 14, center_y - unitLength * 12.6 - unitLength / 20 * 4, unitLength / 3, 0);
	draw_screw(center_x + unitLength * 14, center_y - unitLength * 9 - unitLength / 20 * 4, unitLength / 3, 0);
	draw_screw(center_x - unitLength * 4 + unitLength / 20 * 2, center_y - unitLength * 11 + unitLength / 20 * 3, unitLength / 4, 0);
	draw_screw(center_x - unitLength * 2.3 + unitLength / 20 * 3.2 + unitLength * 2.16 / 2.2 * 6, center_y - unitLength * 11 + unitLength / 20 * 3, unitLength / 4, 0);


	setfillcolor(EGEARGB(0XFF, 0X60, 0X60, 0X60));
	ege_fillellipse(center_x - unitLength * 4.8 + unitLength / 20 * 3, center_y - unitLength * 11 - unitLength / 20 * 2, unitLength / 3, unitLength / 3);
	ege_fillellipse(center_x + unitLength * 4.2 + unitLength / 20 * 3, center_y - unitLength * 11 - unitLength / 20 * 2, unitLength / 3, unitLength / 3);



	setfillcolor(EGEARGB(0XFF, 0X00, 0X00, 0X00));
	ege_fillellipse(center_x - unitLength * 4.8 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20, unitLength / 3, unitLength / 3);
	ege_fillellipse(center_x + unitLength * 4.2 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20, unitLength / 3, unitLength / 3);



	setfillcolor(BLACK);
	ege_fillrect(center_x + unitLength * 9.1, center_y - unitLength * 13.7 - unitLength / 20 * 4, unitLength * 2.14 * 2.1, unitLength * 5.6);

	setfillcolor(EGEARGB(0XFF, 0X11, 0X12, 0X14));
	ege_fillrect(center_x + unitLength * 9.2, center_y - unitLength * 9.2 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);
	ege_fillrect(center_x + unitLength * 9.2, center_y - unitLength * 10.3 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);
	ege_fillrect(center_x + unitLength * 9.2, center_y - unitLength * 11.4 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);
	ege_fillrect(center_x + unitLength * 9.2, center_y - unitLength * 12.5 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);
	ege_fillrect(center_x + unitLength * 9.2, center_y - unitLength * 13.6 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);

	ege_fillrect(center_x + unitLength * 11.44, center_y - unitLength * 9.2 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);
	ege_fillrect(center_x + unitLength * 11.44, center_y - unitLength * 10.3 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);
	ege_fillrect(center_x + unitLength * 11.44, center_y - unitLength * 11.4 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);
	ege_fillrect(center_x + unitLength * 11.44, center_y - unitLength * 12.5 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);
	ege_fillrect(center_x + unitLength * 11.44, center_y - unitLength * 13.6 - unitLength / 20 * 4, unitLength * 2.14, unitLength * 1);



	if (alert_ALT == 1) {
		setfillcolor(EGEARGB(0X40, 0X72, 0X55, 0X34));
		ege_fillrect(center_x + unitLength * 5 + unitLength / 20 * 5, center_y - unitLength * 10 - unitLength / 20 * 4, unitLength * 2.16, unitLength * 2.1);
	}
	else {
		setfillcolor(EGEARGB(0XFF, 0X32, 0X15, 0X04));
		ege_fillrect(center_x + unitLength * 5 + unitLength / 20 * 5, center_y - unitLength * 10 - unitLength / 20 * 4, unitLength * 2.16, unitLength * 2.1);
	}
	if (alert_MDA == 1) {
		setfillcolor(EGEARGB(0X40, 0X72, 0X55, 0X34));
		ege_fillrect(center_x + unitLength * 5 + unitLength / 20 * 5, center_y - unitLength * 13 - unitLength / 20 * 4, unitLength * 2.16, unitLength * 2.1);

	}
	else {
		setfillcolor(EGEARGB(0XFF, 0X32, 0X15, 0X04));
		ege_fillrect(center_x + unitLength * 5 + unitLength / 20 * 5, center_y - unitLength * 13 - unitLength / 20 * 4, unitLength * 2.16, unitLength * 2.1);
	}
	if (alert_autoPilot == 1) {
		//		setfillcolor(EGEARGB(0X40, 0X72, 0X55, 0X34));
		setfillcolor(EGEARGB(0XFF, 0X4d, 0X07, 0X07));
		ege_fillrect(center_x - unitLength * 13 + unitLength / 20 * 5, center_y - unitLength * 10 - unitLength / 20 * 4, unitLength * 2.16, unitLength * 2.1);
	}
	else {
		//		setfillcolor(EGEARGB(0XFF, 0X32, 0X15, 0X04));
		setfillcolor(EGEARGB(0XFF, 0X38, 0X05, 0X05));
		ege_fillrect(center_x - unitLength * 13 + unitLength / 20 * 5, center_y - unitLength * 10 - unitLength / 20 * 4, unitLength * 2.16, unitLength * 2.1);
	}

	setcolor(BLACK);
	setbkmode(TRANSPARENT);
	setfont(unitLength * 1, unitLength * 0.38, "微软雅黑", 0, 0, unitLength, 0, 0, 0);
	xyprintf(center_x + unitLength * 6.3 + unitLength / 20 * 3, center_y - unitLength * 10 + unitLength / 20 * 15, "ALT");
	xyprintf(center_x + unitLength * 6.3 + unitLength / 20 * 3, center_y - unitLength * 13 + unitLength / 20 * 15, "MDA");
	setcolor(EGEARGB(0XFF, 0X80, 0X80, 0X80));
	setfont(unitLength * 0.8, unitLength * 0.3, "微软雅黑", 0, 0, unitLength, 0, 0, 0);
	xyprintf(center_x - unitLength * 11.9 + unitLength / 20 * 6, center_y - unitLength * 9.5 - unitLength / 20 * 4, "AUTO");
	xyprintf(center_x - unitLength * 11.9 + unitLength / 20 * 6, center_y - unitLength * 9.5 + unitLength / 20 * 11, "PILOT");
	setfont(unitLength * 0.35, unitLength * 0.15, "微软雅黑", 0, 0, unitLength, 0, 0, 0);
	xyprintf(center_x - unitLength * 11.7 + unitLength / 20 * 2, center_y - unitLength * 8.5 + unitLength / 20 * 4, "DISENGAGE");

	setcolor(EGEARGB(0XFF, 0X4A, 0X51, 0X52));
	setfont(unitLength * 0.8, unitLength * 0.25, "微软雅黑", 0, 0, unitLength, 0, 0, 0);
	xyprintf(center_x - unitLength * 0.2, center_y - unitLength * 12.8 - unitLength / 20 * 2, "INSTRUMENT COMPARATOR");
	xyprintf(center_x + unitLength * 11.3, center_y - unitLength * 15 - unitLength / 20 * 12, "APD");
	xyprintf(center_x + unitLength * 10.3, center_y - unitLength * 15 + unitLength / 20 * 2, "F/D");
	xyprintf(center_x + unitLength * 12.5, center_y - unitLength * 15 + unitLength / 20 * 2, "A/P");

	if (alert_pullup == 1) {
		setcolor(WHITE);
		setfont(unitLength * 0.8, unitLength * 0.25, "微软雅黑", 0, 0, unitLength, 0, 0, 0);
		xyprintf(center_x - unitLength * 7.5 - unitLength / 20 * 2, center_y - unitLength * 9 - unitLength / 20 * 4, "PULL UP");
	}
	else {
		setcolor(BLACK);
		setfont(unitLength * 0.8, unitLength * 0.25, "微软雅黑", 0, 0, unitLength, 0, 0, 0);
		xyprintf(center_x - unitLength * 7.5 - unitLength / 20 * 2, center_y - unitLength * 9.3 - unitLength / 20 * 4, "PULL UP");
	}
	if (alert_beloGS == 1) {
		setcolor(EGEARGB(0XFF, 0X9D, 0X42, 0X0E));
		setfont(unitLength * 0.6, unitLength * 0.20, "微软雅黑", 0, 0, unitLength, 0, 0, 0);
		xyprintf(center_x - unitLength * 7.5 - unitLength / 20 * 5, center_y - unitLength * 8.2 - unitLength / 20 * 6, "BELO G/S");
		setfont(unitLength * 0.6, unitLength * 0.15, "微软雅黑", 0, 0, unitLength, 0, 0, 0);
		xyprintf(center_x - unitLength * 7.8, center_y - unitLength * 7.7 - unitLength / 20 * 6, "P-INHIBIT");
	}
	else {
		setcolor(BLACK);
		setfont(unitLength * 0.6, unitLength * 0.20, "微软雅黑", 0, 0, unitLength, 0, 0, 0);
		xyprintf(center_x - unitLength * 7.5 - unitLength / 20 * 5, center_y - unitLength * 8.2 - unitLength / 20 * 6, "BELO G/S");
		setfont(unitLength * 0.6, unitLength * 0.15, "微软雅黑", 0, 0, unitLength, 0, 0, 0);
		xyprintf(center_x - unitLength * 7.8, center_y - unitLength * 7.7 - unitLength / 20 * 6, "P-INHIBIT");
	}

	setfillcolor(EGEARGB(0X50, 0X60, 0X60, 0X60));
	ege_fillrect(center_x - unitLength * 4.2 + unitLength / 20 * 2, center_y - unitLength * 11 - unitLength / 20 * 13, unitLength * 2.16 / 2.2 * 8.4, unitLength * 2.1 * 0.8);
}