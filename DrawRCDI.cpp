#include<graphics.h>
#include<math.h>
#include "DrawScrew.h"

extern double verticalRate;
extern double RNG;
int choice_light = 48;
double konb_angle = 0;

double CalAngle(double RCDI_speed);//函数声明
void draw_pointer(double RCDI_X, double RCDI_Y, double RCDI_R, double RCDI_speed);
void draw_screw(double screw_x, double screw_y, double screw_r, double angle);

int RCDI_mouse_x = 0, RCDI_mouse_y = 0;
int RCDI_is_down = 0;
int RCDI_mouse_y_cur = 0, RCDI_mouse_x_cur = 0;

void draw_pointer(double RCDI_X, double RCDI_Y, double RCDI_R, double verticalRate);
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
		if (RCDI_is_down == 0) {
			RCDI_is_down = 1;
			mousepos(&RCDI_mouse_x, &RCDI_mouse_y);
			RCDI_mouse_x_cur = RCDI_mouse_x;
			RCDI_mouse_y_cur = RCDI_mouse_y;
		}
		if (RCDI_is_down == 1) {
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
	else if (RCDI_is_down == 1) {
		RCDI_is_down = 0;
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
	
	
	setcolor(EGEARGB(0XFF,(int)(choice_light / 3), (int)(choice_light / 3), (int)(choice_light / 3)));
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
	setfillcolor(EGEARGB(0XFF,(int)(choice_light / 3), (int)(choice_light / 3), (int)(choice_light / 3)));
	floodfill(RCDI_x, RCDI_y, EGEARGB(0XFF,(int)(choice_light / 3), (int)(choice_light / 3), (int)(choice_light / 3)));
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
	xyprintf(RCDI_x - R - RCDI_side / 52 * 3, RCDI_y  , "0");
	xyprintf(RCDI_x - R * cos(35 * PI / 180.0) - RCDI_side / 52 * 3.1, RCDI_y - RCDI_side / 26 * 5.5, ".5");
	xyprintf(RCDI_x - R * cos(35 * PI / 180.0) - RCDI_side / 52 * 3.1, RCDI_y + RCDI_side / 26 * 5.5, ".5");
	xyprintf(RCDI_x - R * cos(70 * PI / 180.0) - RCDI_side / 52 * 2, RCDI_y - RCDI_side / 26 * 9.2, "1");
	xyprintf(RCDI_x - R * cos(70 * PI / 180.0) - RCDI_side / 52 * 2, RCDI_y + RCDI_side / 26 * 9.2, "1");
	xyprintf(RCDI_x - R * cos(106 * PI / 180.0) + RCDI_side / 52 * 2.5, RCDI_y - RCDI_side / 26 * 9.5, "2");
	xyprintf(RCDI_x - R * cos(106 * PI / 180.0) + RCDI_side / 52 * 2.5, RCDI_y + RCDI_side / 26 * 9.5, "2");
	xyprintf(RCDI_x - R * cos(140 * PI / 180.0) + RCDI_side / 52 * 3.7, RCDI_y - RCDI_side / 26 * 6.5, "4");
	xyprintf(RCDI_x - R * cos(140 * PI / 180.0) + RCDI_side / 52 * 3.7, RCDI_y + RCDI_side / 26 * 6.5, "4");
	xyprintf(RCDI_x + R + RCDI_side / 52 * 3.5, RCDI_y  , "6");

	
	
	setcolor(EGEARGB(0XFF, 0XBB, 0XBB, 0XBB));
	setfont(char_height, char_weight, "微软雅黑", 0, 0, RCDI_side / 52 * 90, 0, 0, 0);
	xyprintf(RCDI_lefttop_x + RCDI_side / 52 * 37 + RCDI_side / 520 * 18, RCDI_lefttop_y + RCDI_side - RCDI_side / 52 * 1.5 - RCDI_side / 520 * 5, "BRT");
	xyprintf(RCDI_x + R + RCDI_side / 52 * 7.8 + RCDI_side / 520 * 4, RCDI_y + RCDI_side / 52 * 10, "DN");
	xyprintf(RCDI_x + R + RCDI_side / 52 * 8.3, RCDI_y - RCDI_side / 52 * 8, "UP");
	
	setcolor(EGEARGB(0XFF, 0XBB, 0XC1, 0X2B));
	setfont(char_height + RCDI_side / 520 * 10, char_weight + RCDI_side / 520 * 2 , "微软雅黑", 0, 0, RCDI_side / 52 * 80, 0, 0, 0);
	xyprintf(RCDI_x - R  + RCDI_side / 520 * 25, RCDI_y + R , "NO TCAS");
	
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
		xyprintf(RCDI_x + R - RCDI_side / 520 * 25, RCDI_y - R - RCDI_side / 520 * 15, "RNG 40");
	}
	if (RNG == 20) {
		xyprintf(RCDI_x + R - RCDI_side / 520 * 25, RCDI_y - R - RCDI_side / 520 * 15, "RNG 30");
	}
	if (RNG == 32) {
		xyprintf(RCDI_x + R - RCDI_side / 520 * 25, RCDI_y - R - RCDI_side / 520 * 15, "RNG 20");
	}
	if (RNG == 44) {
		xyprintf(RCDI_x + R - RCDI_side / 520 * 25, RCDI_y - R - RCDI_side / 520 * 15, "RNG 10");
	}
	if (RNG == 56) {
		xyprintf(RCDI_x + R - RCDI_side / 520 * 25, RCDI_y - R - RCDI_side / 520 * 15, "RNG 5");
	}
	if (RNG == 68) {
		xyprintf(RCDI_x + R - RCDI_side / 520 * 25, RCDI_y - R - RCDI_side / 520 * 15, "RNG 3");
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
