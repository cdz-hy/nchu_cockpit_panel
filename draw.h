#pragma once
double verticalRate = 0;//垂直速率
double RNG = 44;//小飞机周围半径
int choice_light = 16;//RCDI表盘亮度
double RMI_frame_angle = 0;//RMI表盘旋转角度
double RMI_point_angle_1 = 0;
double RMI_point_angle_2 = 0;
double RMI_point_angle_3 = 30;
int RMI_change = 0;
int RMI_change_1 = 0;
double konb_angle = 0;//旋钮旋转角度
void draw_RCDI(double RCDI_x, double RCDI_y, double RCDI_side);
void draw_pointer(double RCDI_X, double RCDI_Y, double RCDI_R, double speed);
double CalAngle(double speed);
void draw_frame(double center_x, double center_y, double side);
void draw_screw(double screw_x, double screw_y, double screw_r, double angle);
void draw_RMI(double RMI_x, double RMI_y, double RMI_side);
void draw_back(double center_x, double center_y, double unitLength);





//电子表
void draw_Part_RCDI(double centerx, double centery, double side);
void draw_PFD_top(double top_x, double top_y, double side);
void draw_1(double x, double y, double side);