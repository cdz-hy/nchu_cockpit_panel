
//引用头文件
#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>

#include "DrawAI.h"
#include "DrawAirspeed.h"
#include "DrawRCDI.h"
#include "DrawAlt.h"
#include "DrawCompass.h"
#include "DrawRMI.h"
#include "DrawFrame.h"
#include "DrawScrew.h"
#include "DrawBackground.h"
#include "G_variable.h"


#include "DrawPFD.h"
#include "DrawPFDStandby.h"
#include "DrawEICAS.h"
#include "DrawChronometer.h"
#include "DrawEHISControl.h"
#include "DrawND.h"
#include "DrawNDInfo.h"
#include "DrawLightControl.h"
#include "DrawFMC.h"
#include "DrawAutoControl.h"
#include "DrawSteeringWheel.h"


void getZoomImage(PIMAGE& pimg, PIMAGE& pimgStatic, int width, int height);
void draw_electricPanel_backgrounds(double PFD_x, double PFD_y, double PFD_side);
void draw_getImage();
void  draw_delImage();
void draw_resizeImage(double PFD_x, double PFD_y, double PFD_side);
void draw_BACKPICTURE(double PFD_x, double PFD_y, double PFD_side);

void draw_map();


extern std::mutex mtx;
extern std::condition_variable cv;
extern bool ready;

//===map所需变量=====//


//实现移动
int is_down = 0;
double pos_x_move = 0;
double pos_y_move = 0;
double pos_x_move_tmp = 0;
double pos_y_move_tmp = 0;
double pos_x_move_plane = 0;
double pos_y_move_plane = 0;

//记录鼠标
int map_mouse_x = 0;
int map_mouse_y = 0;
int map_mouse_x_cur = 0;
int map_mouse_y_cur = 0;

//地图中心点坐标
WAYPOINT map_center = {0, "", 28.877, 115.91,};

//临时地图中心点坐标
WAYPOINT map_centerTmp = {0, "", 28.877, 115.91,};

PIMAGE img;
PIMAGE mapShow;

//图片显示范围(在原图上)
double side = 500;
double pos_x = 2048 / 2 - side / 2;
double pos_y = 2048 / 2 - side / 2;

//地图显示位置和大小（在窗口上）
double map_x = 0;
double map_y = 0;
double map_side = 480;


//==================//


void draw_panels(){
	
	
	
	img = newimage();
	mapShow = newimage();
	
	
//	//读取图片
//	if(renewMap == 2){
//		getimage(img, "map.png");
//		renewMap = 0;
//	}
	
	//鼠标位置
	int mouse_x = 0;
	int mouse_y = 0;
	
	//表盘初始中心	保存最初状态
	double center_x_static = getwidth() / 2;
	double center_y_static = getheight() / 2;
	double unit_side_static = getheight() / 20;
	
	//表盘初始中心
	//默认六个表盘的拟合中心是正中心
	double center_x = getwidth() / 2;
	double center_y = getheight() / 2;
	double center_x1 = getwidth() / 2;
	double center_y1 = getheight() / 2;
	//单位长度，初始为0.05高
	double unit_side = getheight() / 20;
	double unit_side1 = getheight() / 20;
	
	
	//各个表盘移动的距离
	double AI_move_x = 0;
	double AI_move_y = 0;
	double AI_move_x_tmp = 0;
	double AI_move_y_tmp = 0;
	double compass_move_x = 0;
	double compass_move_y = 0;
	double compass_move_x_tmp = 0;
	double compass_move_y_tmp = 0;
	double airspeed_move_x = 0;
	double airspeed_move_y = 0;
	double airspeed_move_x_tmp = 0;
	double airspeed_move_y_tmp = 0;
	double RMI_move_x = 0;
	double RMI_move_y = 0;
	double RMI_move_x_tmp = 0;
	double RMI_move_y_tmp = 0;
	double alt_move_x = 0;
	double alt_move_y = 0;
	double alt_move_x_tmp = 0;
	double alt_move_y_tmp = 0;
	double RCDI_move_x = 0;
	double RCDI_move_y = 0;
	double RCDI_move_x_tmp = 0;
	double RCDI_move_y_tmp = 0;
	double center_move_x = 0;
	double center_move_y = 0;
	double center_move_x_tmp = 0;
	double center_move_y_tmp = 0;
	
	double PFD_move_x = 0;
	double PFD_move_y = 0;
	double PFD_move_x_tmp = 0;
	double PFD_move_y_tmp = 0;
//	double ND_move_x = 0;
//	double ND_move_y = 0;
//	double ND_move_x_tmp = 0;
//	double ND_move_y_tmp = 0;
	
	
	// 此时鼠标是否按下
	int is_down = 0;
	
	// 保存刚按下鼠标时的鼠标坐标
	int mouse_x_cur = 0;
	int mouse_y_cur = 0;
	
	//存储鼠标按下时间判断双击
	double click_time = -1;
	
	// 这里会报错，因为pfd的相关参数在循环里面
	draw_getImage();
	
	for (; is_run(); delay_fps(60)) {
		
		//刷新清屏
		cleardevice();
		
		if(UDP_transmission){
			
		}
		else{
			if(showFPS){
				setcolor(WHITE);
				setfont(20, 10, "黑体");
				xyprintf(length - 50, height - 25, "本地");
			}
		}
		
		
		//显示帧率
		setfont(20, 10, "黑体");
		setcolor(WHITE);
		char tmp[10];
		sprintf(tmp, "%.0f", getfps());
		xyprintf(20, 20, tmp);
		
		
		//中心位置，会变化
		center_x = center_x_static + center_move_x;
		center_y = center_y_static + center_move_y;
		
		//编辑六个表盘初始位置和大小,但是这里的数值会随循环中的拖动而变化，是拖动中实际的位置
		//几个表盘的
		//姿态仪
		double AI_side = 9.00 * unit_side;//此时宽9,但高已经是9.6了，所以下面的比例都是9.6比出来的
		double AI_x = center_x + AI_move_x * unit_side;
		double AI_y = center_y - 4.30 * unit_side + AI_move_y * unit_side;
		//航向仪
		double compass_side = 8.00 * unit_side;
		double compass_x = center_x + compass_move_x * unit_side;
		double compass_y = center_y + 5.20 * unit_side + compass_move_y * unit_side;
		//空速表
		double airspeed_side = 6.40 * unit_side;
		double airspeed_x = center_x - 9.20 * unit_side + airspeed_move_x * unit_side;
		double airspeed_y = center_y - 2.70 * unit_side + airspeed_move_y * unit_side;
		//电磁指示仪
		double RMI_side = 6.40 * unit_side;
		double RMI_x = center_x - 9.20 * unit_side + RMI_move_x * unit_side;
		double RMI_y = center_y + 3.90 * unit_side + RMI_move_y * unit_side;
		//垂直速率表
		double RCDI_side = 6.40 * unit_side;
		double RCDI_x = center_x + 9.20 * unit_side + RCDI_move_x * unit_side;
		double RCDI_y = center_y + 3.05 * unit_side + RCDI_move_y * unit_side;
		//高度表
		double alt_side = 6.40 * unit_side;
		double alt_x = center_x + 9.20 * unit_side + alt_move_x * unit_side;
		double alt_y = center_y - 3.55 * unit_side + alt_move_y * unit_side;
		
		//PFD
		double PFD_side = 15 * unit_side1;
		double PFD_x;
		if(PFD_move_x<15&&PFD_move_x>0){
			PFD_x= center_x1 + PFD_move_x * unit_side1;
		}else if(PFD_move_x>=15){
			PFD_move_x = 15;
			PFD_x= center_x1 + PFD_move_x * unit_side1;
		}else if(PFD_move_x<=0&&PFD_move_x>=-80){
			PFD_x= center_x1 + PFD_move_x * unit_side1;
		}else{
			PFD_move_x = -80;
			PFD_x= center_x1 + PFD_move_x * unit_side1;
		}
		
		double PFD_y;
		if(PFD_move_y<20&&PFD_move_y>1){
			PFD_y = center_y1 + PFD_move_y * unit_side1;
		}else if(PFD_move_y>=20){
			PFD_move_y = 20;
			PFD_y = center_y1 + PFD_move_y * unit_side1;
		}else if(PFD_move_y>=0&&PFD_move_y<=1){
			PFD_y = center_y1 + PFD_move_y * unit_side1;
		}else{
			PFD_move_y = 1;
			PFD_y = center_y1 + PFD_move_y * unit_side1;
		}
		
//		//ND
//		double ND_side = 15 * unit_side;
//		double ND_x = 1.2 * center_x + ND_move_x * unit_side;
//		double ND_y = 1.2 * center_y + ND_move_y * unit_side;
		
		
		
		//界面为0时显示全部六个机械表盘
		if (show == 0) {
			
			if (is_showbk)
				draw_back(center_x, center_y + 0.8 * unit_side, unit_side);
			
			draw_compass(compass_x, compass_y, compass_side);
			
			draw_AI(AI_x, AI_y, AI_side);
			
//				//由于遮盖会超出边界，所以只能放在最底层
//			draw_compass(compass_x, compass_y ,compass_side);
			
			draw_airspeed(airspeed_x, airspeed_y, airspeed_side);
			
			draw_RMI(RMI_x, RMI_y, RMI_side);
			
			draw_alt(alt_x, alt_y, alt_side);
			
			draw_RCDI(RCDI_x, RCDI_y, RCDI_side);
			
			
			
			mousepos(&mouse_x, &mouse_y);
			
			if (mouse_x >= AI_x - 0.5 * AI_side && mouse_x <= AI_x + 0.5 * AI_side && mouse_y >= AI_y - 0.5 * AI_side && mouse_y <= AI_y + 0.5 * AI_side) {
				setcolor(EGEARGB(0x50, 0xff, 0xff, 0xff));
				setlinewidth(0.05 * unit_side_static);
				ege_rectangle(AI_x - 0.50 * AI_side, AI_y - 0.53 * AI_side, AI_side, 1.05 * AI_side);
			}
			if (mouse_x >= compass_x - 0.5 * compass_side && mouse_x <= compass_x + 0.5 * compass_side && mouse_y >= compass_y - 0.5 * compass_side && mouse_y <= compass_y + 0.5 * compass_side) {
				setcolor(EGEARGB(0x50, 0xff, 0xff, 0xff));
				setlinewidth(0.05 * unit_side_static);
				ege_rectangle(compass_x - 0.50 * compass_side, compass_y - 0.50 * compass_side, compass_side, compass_side);
			}
			if (mouse_x >= airspeed_x - 0.5 * airspeed_side && mouse_x <= airspeed_x + 0.5 * airspeed_side && mouse_y >= airspeed_y - 0.5 * airspeed_side && mouse_y <= airspeed_y + 0.5 * airspeed_side) {
				setcolor(EGEARGB(0x50, 0xff, 0xff, 0xff));
				setlinewidth(0.05 * unit_side_static);
				ege_rectangle(airspeed_x - 0.50 * airspeed_side, airspeed_y - 0.50 * airspeed_side, airspeed_side, airspeed_side);
			}
			if (mouse_x >= alt_x - 0.5 * alt_side && mouse_x <= alt_x + 0.5 * alt_side && mouse_y >= alt_y - 0.5 * alt_side && mouse_y <= alt_y + 0.5 * alt_side) {
				setcolor(EGEARGB(0x50, 0xff, 0xff, 0xff));
				setlinewidth(0.05 * unit_side_static);
				ege_rectangle(alt_x - 0.5 * alt_side, alt_y - 0.5 * alt_side, alt_side, alt_side);
			}
			if (mouse_x >= RMI_x - 0.5 * RMI_side && mouse_x <= RMI_x + 0.5 * RMI_side && mouse_y >= RMI_y - 0.5 * RMI_side && mouse_y <= RMI_y + 0.5 * RMI_side) {
				setcolor(EGEARGB(0x50, 0xff, 0xff, 0xff));
				setlinewidth(0.05 * unit_side_static);
				ege_rectangle(RMI_x - 0.5 * RMI_side, RMI_y - 0.5 * RMI_side, RMI_side, RMI_side);
			}
			if (mouse_x >= RCDI_x - 0.5 * RCDI_side && mouse_x <= RCDI_x + 0.5 * RCDI_side && mouse_y >= RCDI_y - 0.5 * RCDI_side && mouse_y <= RCDI_y + 0.5 * RCDI_side) {
				setcolor(EGEARGB(0x50, 0xff, 0xff, 0xff));
				setlinewidth(0.05 * unit_side_static);
				ege_rectangle(RCDI_x - 0.5 * RCDI_side, RCDI_y - 0.5 * RCDI_side, 1.05 * RCDI_side, RCDI_side);
			}
			
			
			//在按下ctrl时的操作
			if (GetAsyncKeyState(0x11) & 0x8000) {
				
				// 表盘整体移动
				if (GetAsyncKeyState(0x01) & 0x8000) {
					if (is_down == 0 && (
						(mouse_x >= AI_x - 0.5 * AI_side && mouse_x <= AI_x + 0.5 * AI_side && mouse_y >= AI_y - 0.5 * AI_side && mouse_y <= AI_y + 0.5 * AI_side) ||
						(mouse_x >= compass_x - 0.5 * compass_side && mouse_x <= compass_x + 0.5 * compass_side && mouse_y >= compass_y - 0.5 * compass_side && mouse_y <= compass_y + 0.5 * compass_side) ||
						(mouse_x >= airspeed_x - 0.5 * airspeed_side && mouse_x <= airspeed_x + 0.5 * airspeed_side && mouse_y >= airspeed_y - 0.5 * airspeed_side && mouse_y <= airspeed_y + 0.5 * airspeed_side) ||
						(mouse_x >= alt_x - 0.5 * alt_side && mouse_x <= alt_x + 0.5 * alt_side && mouse_y >= alt_y - 0.5 * alt_side && mouse_y <= alt_y + 0.5 * alt_side) ||
						(mouse_x >= RMI_x - 0.5 * alt_side && mouse_x <= RMI_x + 0.5 * alt_side && mouse_y >= RMI_y - 0.5 * alt_side && mouse_y <= RMI_y + 0.5 * alt_side) ||
						(mouse_x >= RCDI_x - 0.5 * RCDI_side && mouse_x <= RCDI_x + 0.5 * RCDI_side && mouse_y >= RCDI_y - 0.5 * RCDI_side && mouse_y <= RCDI_y + 0.5 * RCDI_side)
						)) {
						is_down = 10;
						mouse_x_cur = mouse_x;
						mouse_y_cur = mouse_y;
					}
					if (is_down == 10) {
						mousepos(&mouse_x, &mouse_y);
						center_move_x = (mouse_x - mouse_x_cur);
						center_move_y = (mouse_y - mouse_y_cur);
						center_move_x += center_move_x_tmp;
						center_move_y += center_move_y_tmp;
					}
				} else if (is_down == 10) {
					is_down = 0;
					center_move_x_tmp = center_move_x;
					center_move_y_tmp = center_move_y;
				}
				//滚轮实现放大缩小
				mouse_msg msgRecord = { 0 };
				bool redraw = true;
				
				while (mousemsg()) {
					//getmouse 获取鼠标消息
					msgRecord = getmouse();
					redraw = true;
				}
				if (redraw) {
					
					if (msgRecord.is_wheel()) {
						if (msgRecord.wheel > 0 && unit_side < 130) {
							unit_side += msgRecord.wheel / 30;
						} else if (msgRecord.wheel < 0 && unit_side > 15) {
							unit_side += msgRecord.wheel / 30;
						}
					}
					
				}
				
			}
			//未按下ctrl的操作
			// 单个表盘移动
			else {
				
				//实现姿态仪的移动
				if (GetAsyncKeyState(0x01) & 0x8000) {
					if (is_down == 0 && mouse_x >= AI_x - 0.5 * AI_side && mouse_x <= AI_x + 0.5 * AI_side && mouse_y >= AI_y - 0.5 * AI_side && mouse_y <= AI_y + 0.5 * AI_side) {
						is_down = 1;
						mouse_x_cur = mouse_x;
						mouse_y_cur = mouse_y;
					}
					if (is_down == 1) {
						mousepos(&mouse_x, &mouse_y);
						AI_move_x = (mouse_x - mouse_x_cur) / unit_side;
						AI_move_y = (mouse_y - mouse_y_cur) / unit_side;
						AI_move_x += AI_move_x_tmp;
						AI_move_y += AI_move_y_tmp;
					}
				} else if (is_down == 1) {
					
					//获取鼠标双击信息并单仪表全屏展示
					//因为这里上面的if判断并进入的条件是按着左键，所以这里不能直接用&0x0001来获取点击，只能用这种 没有按下 的else来判断完成了点击一次
					if (mouse_x >= AI_x - 0.5 * AI_side && mouse_x <= AI_x + 0.5 * AI_side && mouse_y >= AI_y - 0.5 * AI_side && mouse_y <= AI_y + 0.5 * AI_side) {
						if (fclock() - click_time < 0.3) {
							show = 1;
						} else {
							click_time = fclock();
						}
					}
					
					is_down = 0;
					AI_move_x_tmp = AI_move_x;
					AI_move_y_tmp = AI_move_y;
				}
				
				
				//实现罗盘的移动
				if (GetAsyncKeyState(0x01) & 0x8000) {
					if (is_down == 0 && mouse_x >= compass_x - 0.5 * compass_side && mouse_x <= compass_x + 0.5 * compass_side && mouse_y >= compass_y - 0.5 * compass_side && mouse_y <= compass_y + 0.5 * compass_side) {
						is_down = 2;
						mouse_x_cur = mouse_x;
						mouse_y_cur = mouse_y;
					}
					if (is_down == 2) {
						mousepos(&mouse_x, &mouse_y);
						compass_move_x = (mouse_x - mouse_x_cur) / unit_side;
						compass_move_y = (mouse_y - mouse_y_cur) / unit_side;
						compass_move_x += compass_move_x_tmp;
						compass_move_y += compass_move_y_tmp;
					}
				} else if (is_down == 2) {
					
					//全屏展示罗盘
					if (mouse_x >= compass_x - 0.5 * compass_side && mouse_x <= compass_x + 0.5 * compass_side && mouse_y >= compass_y - 0.5 * compass_side && mouse_y <= compass_y + 0.5 * compass_side) {
						if (fclock() - click_time < 0.3) {
							show = 2;
						} else {
							click_time = fclock();
						}
					}
					
					is_down = 0;
					compass_move_x_tmp = compass_move_x;
					compass_move_y_tmp = compass_move_y;
				}
				
				
				//实现空速表的移动
				if (GetAsyncKeyState(0x01) & 0x8000) {
					if (is_down == 0 && mouse_x >= airspeed_x - 0.5 * airspeed_side && mouse_x <= airspeed_x + 0.5 * airspeed_side && mouse_y >= airspeed_y - 0.5 * airspeed_side && mouse_y <= airspeed_y + 0.5 * airspeed_side) {
						is_down = 3;
						mouse_x_cur = mouse_x;
						mouse_y_cur = mouse_y;
					}
					if (is_down == 3) {
						mousepos(&mouse_x, &mouse_y);
						airspeed_move_x = (mouse_x - mouse_x_cur) / unit_side;
						airspeed_move_y = (mouse_y - mouse_y_cur) / unit_side;
						airspeed_move_x += airspeed_move_x_tmp;
						airspeed_move_y += airspeed_move_y_tmp;
					}
				} else if (is_down == 3) {
					
					//全屏展示空速表
					if (mouse_x >= airspeed_x - 0.5 * airspeed_side && mouse_x <= airspeed_x + 0.5 * airspeed_side && mouse_y >= airspeed_y - 0.5 * airspeed_side && mouse_y <= airspeed_y + 0.5 * airspeed_side) {
						if (fclock() - click_time < 0.3) {
							show = 3;
						} else {
							click_time = fclock();
						}
					}
					
					is_down = 0;
					airspeed_move_x_tmp = airspeed_move_x;
					airspeed_move_y_tmp = airspeed_move_y;
				}
				
				
				//实现电磁指示仪的移动
				if (GetAsyncKeyState(0x01) & 0x8000) {
					if (is_down == 0 && mouse_x >= RMI_x - 0.5 * RMI_side && mouse_x <= RMI_x + 0.5 * RMI_side && mouse_y >= RMI_y - 0.5 * RMI_side && mouse_y <= RMI_y + 0.5 * RMI_side) {
						is_down = 4;
						mouse_x_cur = mouse_x;
						mouse_y_cur = mouse_y;
					}
					if (is_down == 4) {
						mousepos(&mouse_x, &mouse_y);
						RMI_move_x = (mouse_x - mouse_x_cur) / unit_side;
						RMI_move_y = (mouse_y - mouse_y_cur) / unit_side;
						RMI_move_x += RMI_move_x_tmp;
						RMI_move_y += RMI_move_y_tmp;
					}
				} else if (is_down == 4) {
					
					//全屏展示电磁指示仪
					if (mouse_x >= RMI_x - 0.5 * RMI_side && mouse_x <= RMI_x + 0.5 * RMI_side && mouse_y >= RMI_y - 0.5 * RMI_side && mouse_y <= RMI_y + 0.5 * RMI_side) {
						if (fclock() - click_time < 0.3) {
							show = 4;
						} else {
							click_time = fclock();
						}
					}
					
					is_down = 0;
					RMI_move_x_tmp = RMI_move_x;
					RMI_move_y_tmp = RMI_move_y;
				}
				
				
				//实现高度表的移动
				if (GetAsyncKeyState(0x01) & 0x8000) {
					if (is_down == 0 && mouse_x >= alt_x - 0.5 * alt_side && mouse_x <= alt_x + 0.5 * alt_side && mouse_y >= alt_y - 0.5 * alt_side && mouse_y <= alt_y + 0.5 * alt_side) {
						is_down = 5;
						mouse_x_cur = mouse_x;
						mouse_y_cur = mouse_y;
					}
					if (is_down == 5) {
						mousepos(&mouse_x, &mouse_y);
						alt_move_x = (mouse_x - mouse_x_cur) / unit_side;
						alt_move_y = (mouse_y - mouse_y_cur) / unit_side;
						alt_move_x += alt_move_x_tmp;
						alt_move_y += alt_move_y_tmp;
					}
				} else if (is_down == 5) {
					
					//全屏展示高度表
					if (mouse_x >= alt_x - 0.5 * alt_side && mouse_x <= alt_x + 0.5 * alt_side && mouse_y >= alt_y - 0.5 * alt_side && mouse_y <= alt_y + 0.5 * alt_side) {
						if (fclock() - click_time < 0.3) {
							show = 5;
						} else {
							click_time = fclock();
						}
					}
					
					is_down = 0;
					alt_move_x_tmp = alt_move_x;
					alt_move_y_tmp = alt_move_y;
				}
				
				
				//实现垂直速率表的移动
				if (GetAsyncKeyState(0x01) & 0x8000) {
					if (is_down == 0 && mouse_x >= RCDI_x - 0.5 * RCDI_side && mouse_x <= RCDI_x + 0.5 * RCDI_side && mouse_y >= RCDI_y - 0.5 * RCDI_side && mouse_y <= RCDI_y + 0.5 * RCDI_side) {
						is_down = 6;
						mouse_x_cur = mouse_x;
						mouse_y_cur = mouse_y;
					}
					if (is_down == 6) {
						mousepos(&mouse_x, &mouse_y);
						RCDI_move_x = (mouse_x - mouse_x_cur) / unit_side;
						RCDI_move_y = (mouse_y - mouse_y_cur) / unit_side;
						RCDI_move_x += RCDI_move_x_tmp;
						RCDI_move_y += RCDI_move_y_tmp;
					}
				} else if (is_down == 6) {
					
					//全屏展示垂直速率表
					if (mouse_x >= RCDI_x - 0.5 * RCDI_side && mouse_x <= RCDI_x + 0.5 * RCDI_side && mouse_y >= RCDI_y - 0.5 * RCDI_side && mouse_y <= RCDI_y + 0.5 * RCDI_side) {
						if (fclock() - click_time < 0.3) {
							show = 6;
						} else {
							click_time = fclock();
						}
					}
					
					is_down = 0;
					RCDI_move_x_tmp = RCDI_move_x;
					RCDI_move_y_tmp = RCDI_move_y;
				}
				
				
			}
			
			
			
			// 复位表盘
			//这里因为按钮都是通过右键实现的，所以好像按钮控制加上后就不能再是右键了，识别不到&0001按下
			//所以改为鼠标中键复位
			if (GetAsyncKeyState(0x04) & 0x0001) {
				mousepos(&mouse_x, &mouse_y);
				//复位姿态仪
				if (mouse_x >= AI_x - 0.5 * AI_side && mouse_x <= AI_x + 0.5 * AI_side && mouse_y >= AI_y - 0.5 * AI_side && mouse_y <= AI_y + 0.5 * AI_side) {
					AI_move_x = 0;
					AI_move_y = 0;
					AI_move_x_tmp = 0;
					AI_move_y_tmp = 0;
				}
				//复位罗盘
				if (mouse_x >= compass_x - 0.5 * compass_side && mouse_x <= compass_x + 0.5 * compass_side && mouse_y >= compass_y - 0.5 * compass_side && mouse_y <= compass_y + 0.5 * compass_side) {
					compass_move_x = 0;
					compass_move_y = 0;
					compass_move_x_tmp = 0;
					compass_move_y_tmp = 0;
				}
				//复位空速表
				if (mouse_x >= airspeed_x - 0.5 * airspeed_side && mouse_x <= airspeed_x + 0.5 * airspeed_side && mouse_y >= airspeed_y - 0.5 * airspeed_side && mouse_y <= airspeed_y + 0.5 * airspeed_side) {
					airspeed_move_x = 0;
					airspeed_move_y = 0;
					airspeed_move_x_tmp = 0;
					airspeed_move_y_tmp = 0;
				}
				//复位电磁指示仪
				if (mouse_x >= RMI_x - 0.5 * RMI_side && mouse_x <= RMI_x + 0.5 * RMI_side && mouse_y >= RMI_y - 0.5 * RMI_side && mouse_y <= RMI_y + 0.5 * RMI_side) {
					RMI_move_x = 0;
					RMI_move_y = 0;
					RMI_move_x_tmp = 0;
					RMI_move_y_tmp = 0;
				}
				//复位高度表
				if (mouse_x >= alt_x - 0.5 * alt_side && mouse_x <= alt_x + 0.5 * alt_side && mouse_y >= alt_y - 0.5 * alt_side && mouse_y <= alt_y + 0.5 * alt_side) {
					alt_move_x = 0;
					alt_move_y = 0;
					alt_move_x_tmp = 0;
					alt_move_y_tmp = 0;
				}
				//复位垂直速率
				if (mouse_x >= RCDI_x - 0.5 * RCDI_side && mouse_x <= RCDI_x + 0.5 * RCDI_side && mouse_y >= RCDI_y - 0.5 * RCDI_side && mouse_y <= RCDI_y + 0.5 * RCDI_side) {
					RCDI_move_x = 0;
					RCDI_move_y = 0;
					RCDI_move_x_tmp = 0;
					RCDI_move_y_tmp = 0;
				}
			}
			
			
			if (GetAsyncKeyState(0x39) & 0x8000) {
				unit_side *= 1.05;
			} else if (GetAsyncKeyState(0x30) & 0x8000) {
				unit_side /= 1.05;
			}
			
			
		}
		//界面不是0（默认显示所有表盘）则按界面编号全屏显示不同的表盘
		else if(show < 10){
			
			switch (show) {
			case 1:
				// 1-姿态仪
				draw_AI(center_x_static, center_y_static, 16 * unit_side_static);
				break;
			case 2:
				// 2-罗盘
				draw_compass(center_x_static, center_y_static, 16 * unit_side_static);
				break;
			case 3:
				// 3-空速表
				draw_airspeed(center_x_static, center_y_static, 16 * unit_side_static);
				break;
			case 4:
				// 4-电磁指示仪
				draw_RMI(center_x_static, center_y_static, 16 * unit_side_static);
				break;
			case 5:
				// 5-高度表
				draw_alt(center_x_static, center_y_static, 16 * unit_side_static);
				break;
			case 6:
				// 6-垂直速率表
				draw_RCDI(center_x_static, center_y_static, 16 * unit_side_static);
				break;
			default:
				break;
			}
			
			
			//双击返回
			if (GetAsyncKeyState(0x01) & 0x0001) {
				if (fclock() - click_time < 0.3) {
					show = 0;
					//如果不重置click_time会导致鼠标位置在表盘上的时候无法退出
					click_time = -1;
				} else {
					click_time = fclock();
				}
			}
			
			
		}
		
		
		//====================================================================================//
		
		
		//界面为10时显示所有电子仪表
		else if(show == 10){
			
			mousepos(&mouse_x, &mouse_y);
			
			std::lock_guard<std::mutex> guard(mtx);
			ready = true;
			
			
			
			draw_resizeImage(PFD_x, PFD_y, PFD_side);
			draw_BACKPICTURE(PFD_x, PFD_y , PFD_side);
			
			draw_Background_2(PFD_x, PFD_y , PFD_side);
			
			
			extern int MainpanelDU_gear;
			extern int LOWERDU_gear;
			
			if(MainpanelDU_gear == 0){
				
				//ND表
				draw_ND(PFD_x + 0.06 * PFD_side, PFD_y, PFD_side);
				
				//画PFD
				draw_PFD(PFD_x + 1.24 * PFD_side, PFD_y, PFD_side);
			}
			else if(MainpanelDU_gear == 1){
				
				//画PFD
				draw_PFD(PFD_x, PFD_y, PFD_side);
				
				//ND表
				draw_ND(PFD_x + 1.3 * PFD_side, PFD_y, PFD_side);
				
			}
			else if(MainpanelDU_gear == 2){
				
				
				//画PFD
				draw_PFD(PFD_x + 0 * PFD_side, PFD_y, PFD_side);
				
				//画EICAS
				draw_EICAS(PFD_x + 1.3 * PFD_side, PFD_y, PFD_side);
				
				
				
			}
			else if(MainpanelDU_gear == 3){
				
				//画PFD
				draw_PFD(PFD_x + 0 * PFD_side, PFD_y, PFD_side);
				
				//画EICAS
				draw_PFD(PFD_x + 1.24 * PFD_side, PFD_y, PFD_side);
				
			}
			
			//备用表
			draw_PFD_standby(PFD_x + 2.26 * PFD_side, PFD_y - 0.3 * PFD_side, 0.35/2 * PFD_side);
			
			//画计时器
			draw_Chronometer(PFD_x - 0.85 * PFD_side, PFD_y - 0.3 * PFD_side, 0.45 * PFD_side);
			draw_Chronometer(PFD_x + 7 * PFD_side, PFD_y - 0.3 * PFD_side, 0.45 * PFD_side);
			//画EICAS
			draw_EICAS(PFD_x + 3.225 * PFD_side, PFD_y, PFD_side);
			
			//画EICAS2
			draw_EICAS2(PFD_x + 3.125 * PFD_side, PFD_y + 1.38 * PFD_side, PFD_side * 1.07);
			
			//画EHIS的控制面板
			draw_EHIS_control(PFD_x + PFD_side * 1.5, PFD_y - 1.4 * PFD_side, PFD_side*0.8);
			draw_EHIS_control(PFD_x + PFD_side * 5.32, PFD_y - 1.4 * PFD_side, PFD_side*0.8);
			
			//灯光控制
			draw_Light_contral(PFD_x + PFD_side * 0.15, PFD_y + 1.03 * PFD_side, PFD_side*0.67);
			
			//灯光控制2
			draw_Light_contral_1(PFD_x + PFD_side * 0.87, PFD_y + 1.03 * PFD_side, PFD_side*0.67);
			
			//显示屏的控制板
			draw_TopContral(PFD_x + PFD_side * 0.65, PFD_y - 0.83 * PFD_side, PFD_side*0.8);
			
			//画FMC
			draw_FMC(PFD_x + PFD_side * 1.99, PFD_y + 1.67 * PFD_side, PFD_side * 0.63);
            draw_FMC_2(PFD_x + PFD_side * 4.245, PFD_y + 1.67 * PFD_side, PFD_side * 0.63);
			
			//画自动驾驶控制板
			draw_auto_control(PFD_x + PFD_side * 3.41, PFD_y - 1.4 * PFD_side, PFD_side*3);
			
			draw_ND(PFD_x + 4.81 * PFD_side, PFD_y, PFD_side);
			draw_PFD(PFD_x + 6 * PFD_side, PFD_y, PFD_side);
			
			draw_electricPanel_backgrounds(PFD_x, PFD_y , PFD_side);

            //画方向舵显示器
			draw_SteeringWeel(PFD_x + 2.2 * PFD_side, PFD_y - 0.9 * PFD_side, PFD_side / 5);
			
			
//			//直接显示的地图（暂时不用）
//			if(showMap == 1)
//				draw_map();
			
			
			if(GetAsyncKeyState(0x41)&0x0001){
				ifNewWindows = 1;
				ifNewWindows = 1;
				
			}
			
			
//			//调试用
//			printf("%d",showMap);
			
//			egeHDC = getHDC();
			cv.notify_one();
			
			windwsShow_x = PFD_x - PFD_side / 2;
			windwsShow_y = PFD_y - PFD_side / 2;
			windwsShow_lenth = PFD_side;
			windwsShow_height = PFD_side;
			
			
			
			//实现移动
			if (GetAsyncKeyState(0x01) & 0x8000) {
				if (is_down == 0) {
					is_down = 11;
					mouse_x_cur = mouse_x;
					mouse_y_cur = mouse_y;
				}
				if (is_down == 11) {
					mousepos(&mouse_x, &mouse_y);
					PFD_move_x = (mouse_x - mouse_x_cur) / unit_side1;
					PFD_move_y = (mouse_y - mouse_y_cur) / unit_side1;
					PFD_move_x += PFD_move_x_tmp;
					PFD_move_y += PFD_move_y_tmp;
				}
			} else if (is_down == 11) {
				
//				//全屏展示PFD表
//				if (mouse_x >= PFD_x - 0.5 * PFD_side && mouse_x <= PFD_x + 0.5 * PFD_side && mouse_y >= PFD_y - 0.5 * PFD_side && mouse_y <= PFD_y + 0.5 * PFD_side) {
//					if (fclock() - click_time < 0.3) {
//						show = 11;
//					} else {
//						click_time = fclock();
//					}
//				}
				
				is_down = 0;
				PFD_move_x_tmp = PFD_move_x;
				PFD_move_y_tmp = PFD_move_y;
			}
			
			
			//在按下ctrl时的操作
			if (GetAsyncKeyState(0x11) & 0x8000) {
				
				//滚轮实现放大缩小
				mouse_msg msgRecord = { 0 };
				bool redraw = true;
				
				while (mousemsg()) {
					//getmouse 获取鼠标消息
					msgRecord = getmouse();
					redraw = true;
				}
				if (redraw) {
					
					if (msgRecord.is_wheel()) {
						if (msgRecord.wheel > 0 && unit_side1 < 130) {
							unit_side1 += msgRecord.wheel / 30;
						} else if (msgRecord.wheel < 0 && unit_side1 > 15) {
							unit_side1 += msgRecord.wheel / 30;
						}
					}
					
				}
				
			}
			
			
		}
		
		
		
		if (UDP_transmission != 1) {
//			get_keymsg();
		}
		
		
		
		//按3增加亮度，按4减小亮度
		if (GetAsyncKeyState(0x33) & 0x8000) {
			if (G_light < 255) {
				G_light += 1;
			}
		}
		if (GetAsyncKeyState(0x34) & 0x8000) {
			if (G_light > 1) {
				G_light -= 1;
			}
		}
		
		
		//按k切换界面（机械/电子）
		if(GetAsyncKeyState(0x0d) & 0x0001){
			if(show == 0)
				show = 10;
			else if(show == 10)
				show = 0;
		}
		
		// M键，控制MAP显示的
		if(GetAsyncKeyState(0x4d) & 0x0001){
			showMap += 1;
			showMap %= 2;
		}
		
		// P键 控制pfd显示的
		if(GetAsyncKeyState(0x50) & 0x0001){
			if(showPFDJudge == 0){
				showPFDJudge = 1;
			}
		}
		
		// N键 控制ND表显示
		if(GetAsyncKeyState(0x4E) & 0x0001){
			if(showNDJudge == 0){
				showNDJudge = 1;
			}
		}
		
		//E键 控制EICAS表显示
		if(GetAsyncKeyState(0x45) & 0x0001){
			if(showEICASJudge == 0){
				showEICASJudge = 1;
			}
		}
		
		//R键 控制EICAS2表显示
		if(GetAsyncKeyState(0x52) & 0x0001){
			if(showEICAS2Judge == 0){
				showEICAS2Judge = 1;
			}
		}
		
		//f键 控制FMC表显示
		if(GetAsyncKeyState(0x46) & 0x0001){
			if(showFMCJudge == 0){
				showFMCJudge = 1;
			}
		}
		
		//实现窗口关闭
		mousepos(&mouse_x, &mouse_y);
		if(mouse_x >= 0.0 * height && mouse_y >= 0.0 * length && mouse_x <= 0.06 * height && mouse_y <= 0.06 * length){
			setfillcolor(EGEARGB(0x77,0xba,0x00,0x0c));
			if((mouse_x - 0.03 * height) * (mouse_x - 0.03 * height) + (mouse_y - 0.025 * length) * (mouse_y - 0.025 * length) <= (0.01 * height) * (0.01 * height)){
				setfillcolor(EGEARGB(0x99,0xba,0x00,0x0c));
				setcolor(EGEARGB(0x30, 0xff, 0xff, 0xff));
				setlinewidth(0.003 * height);
				ege_ellipse(0.02 * height, 0.015 * length, 0.02 * height, 0.02 * height);
			}
			ege_fillellipse(0.02 * height, 0.015 * length, 0.02 * height, 0.02 * height);
			if(GetAsyncKeyState(0x01) & 0x8000){
				is_down = -999;
			}
			else if(is_down == -999){
				is_down = 0;
				HWND hWnd = getHWnd();
				SendMessage(hWnd, WM_CLOSE, 0, 0);
			}
		}
		
		
	}
	
	
	draw_delImage();
	delimage(img);
}


void draw_getImage() {
	
	pimg1 = newimage();
	getimage(pimg1, "./res/NOSEWHEEL.png");
	pimg2 = newimage();
	getimage(pimg2, "./res/B1776.png");
	pimg3 = newimage();
	getimage(pimg3, "./res/LIGHTSETC.png");
	pimg4 = newimage();
	getimage(pimg4, "./res/standbyPFDup.png");
	pimg5 = newimage();
	getimage(pimg5, "./res/standbyPFDdown.png");
	pimg6 = newimage();
	getimage(pimg6, "./res/737-baffle.png");
	pimg7 = newimage();
	getimage(pimg7, "./res/横杠.png");
	pimg8 = newimage();
	getimage(pimg8, "./res/陀螺仪.png");
	pimg9 = newimage();
	getimage(pimg9, "./res/back.jpg");
	pimg10 = newimage();
	getimage(pimg10, "./res/陀螺仪旁边.png");
	pimg11 = newimage();
	getimage(pimg11, "./res/中间的杠.png");
	pimg12 = newimage();
	getimage(pimg12, "./res/左边的杠.png");
	pimg13 = newimage();
	getimage(pimg13, "./res/左上面的杠.png");
	pimg14 = newimage();
	getimage(pimg14, "./res/k1.png");
	pimg15 = newimage();
	getimage(pimg15, "./res/k1d.png");
	pimg16 = newimage();
	getimage(pimg16, "./res/gan.png");
	pimg17 = newimage();
	getimage(pimg17, "./res/k2d.png");
	pimg18 = newimage();
	getimage(pimg18, "./res/k2.png");
	pimg19 = newimage();
	getimage(pimg19, "./res/k2x.png");
	pimg20 = newimage();
	getimage(pimg20, "./res/k3.png");
	pimg21 = newimage();
	getimage(pimg21, "./res/lk.png");
	pimg22 = newimage();
	getimage(pimg22, "./res/ck.png");
	pimg23 = newimage();
	getimage(pimg23, "./res/rk.png");
	pimg24 = newimage();
	getimage(pimg24, "./res/B1776_1.png");
	pimg25 = newimage();
	getimage(pimg25, "./res/4.png");
	pimg26 = newimage();
	getimage(pimg26, "./res/右上面的杠.png");
	pimg27 = newimage();
	getimage(pimg27, "./res/右门.png");
	pimg28 = newimage();
	getimage(pimg28, "./res/6.png");
	pimg29 = newimage();
	getimage(pimg29, "./res/11.png");
	pimg30 = newimage();
	getimage(pimg30, "./res/09.png");
	
	
	pimg1sta = newimage();
	getimage(pimg1sta, "./res/NOSEWHEEL.png");
	pimg2sta = newimage();
	getimage(pimg2sta, "./res/B1776.png");
	pimg3sta = newimage();
	getimage(pimg3sta, "./res/LIGHTSETC.png");
	pimg4sta = newimage();
	getimage(pimg4sta, "./res/standbyPFDup.png");
	pimg5sta = newimage();
	getimage(pimg5sta, "./res/standbyPFDdown.png");
	pimg6sta = newimage();
	getimage(pimg6sta, "./res/737-baffle.png");
	pimg7sta = newimage();
	getimage(pimg7sta, "./res/横杠.png");
	pimg8sta = newimage();
	getimage(pimg8sta, "./res/陀螺仪.png");
	pimg9sta = newimage();
	getimage(pimg9sta, "./res/背景.jpg");
	pimg10sta = newimage();
	getimage(pimg10sta, "./res/陀螺仪旁边.png");
	pimg11sta = newimage();
	getimage(pimg11sta, "./res/中间的杠.png");
	pimg12sta = newimage();
	getimage(pimg12sta, "./res/左边的杠.png");
	pimg13sta = newimage();
	getimage(pimg13sta, "./res/左上面的杠.png");
	pimg14sta = newimage();
	getimage(pimg14sta, "./res/k1.png");
	pimg15sta = newimage();
	getimage(pimg15sta, "./res/k1d.png");
	pimg16sta = newimage();
	getimage(pimg16sta, "./res/gan.png");
	pimg17sta = newimage();
	getimage(pimg17sta, "./res/k2d.png");
	pimg18sta = newimage();
	getimage(pimg18sta, "./res/k2.png");
	pimg19sta = newimage();
	getimage(pimg19sta, "./res/k2x.png");
	pimg20sta = newimage();
	getimage(pimg20sta, "./res/k3.png");
	pimg21sta = newimage();
	getimage(pimg21sta, "./res/lk.png");
	pimg22sta = newimage();
	getimage(pimg22sta, "./res/ck.png");
	pimg23sta = newimage();
	getimage(pimg23sta, "./res/rk.png");
	pimg24sta = newimage();
	getimage(pimg24sta, "./res/B1776_1.png");
	pimg25sta = newimage();
	getimage(pimg25sta, "./res/4.png");
	pimg26sta = newimage();
	getimage(pimg26sta, "./res/右上面的杠.png");
	pimg27sta = newimage();
	getimage(pimg27sta, "./res/右门.png");
	pimg28sta = newimage();
	getimage(pimg28sta, "./res/6.png");
	pimg29sta = newimage();
	getimage(pimg29sta, "./res/11.png");
	pimg30sta = newimage();
	getimage(pimg30sta, "./res/09.png");
	
}

void draw_resizeImage(double PFD_x, double PFD_y, double PFD_side) {
	getZoomImage(pimg1, pimg1sta,PFD_side*0.545, PFD_side*0.25);
	getZoomImage(pimg2, pimg2sta, PFD_side * 0.5, PFD_side * 0.18);
	getZoomImage(pimg3, pimg3sta, PFD_side * 0.8, PFD_side * 0.5);
	getZoomImage(pimg4, pimg4sta, PFD_side * 0.52, PFD_side * 0.52);
	getZoomImage(pimg5, pimg5sta, PFD_side * 0.52, PFD_side * 0.52);
	getZoomImage(pimg7, pimg7sta, PFD_side*3.17, PFD_side*0.25);
	getZoomImage(pimg6, pimg6sta, PFD_side*3.4, PFD_side*1.2);
	getZoomImage(pimg8, pimg8sta, PFD_side*0.38, PFD_side*0.38);
	getZoomImage(pimg9, pimg9sta, length, height);
	getZoomImage(pimg10, pimg10sta, PFD_side*0.54, PFD_side*0.46);
	getZoomImage(pimg11, pimg11sta, PFD_side*1.2, PFD_side*2.5);
	getZoomImage(pimg12, pimg12sta, PFD_side*3.8, PFD_side*7.2);
	getZoomImage(pimg13, pimg13sta, PFD_side*8.4, PFD_side*1.2);
	getZoomImage(pimg14, pimg14sta, PFD_side*0.9, PFD_side*0.55);
	getZoomImage(pimg15, pimg15sta, PFD_side*0.35, PFD_side*0.35);
	getZoomImage(pimg16, pimg16sta, PFD_side*0.36, PFD_side*1.44);
	getZoomImage(pimg17, pimg17sta, PFD_side*0.28, PFD_side*0.28);
	getZoomImage(pimg18, pimg18sta, PFD_side*0.58, PFD_side*0.29);
	getZoomImage(pimg19, pimg19sta, PFD_side*0.8, PFD_side*0.16);
	getZoomImage(pimg20, pimg20sta, PFD_side*0.8, PFD_side*0.4);
	getZoomImage(pimg21, pimg21sta, PFD_side*0.15, PFD_side*0.15);
	getZoomImage(pimg22, pimg22sta, PFD_side*0.15, PFD_side*0.15);
	getZoomImage(pimg23, pimg23sta, PFD_side*0.15, PFD_side*0.15);
	getZoomImage(pimg24, pimg24sta, PFD_side * 0.5, PFD_side * 0.18);
	getZoomImage(pimg25, pimg25sta, PFD_side * 3.36, PFD_side * 1.4);
	getZoomImage(pimg26, pimg26sta, PFD_side * 7.5, PFD_side * 1.65);
	getZoomImage(pimg27, pimg27sta, PFD_side * 6.2, PFD_side * 6.82);
	getZoomImage(pimg28, pimg28sta, PFD_side * 2.1, PFD_side * 0.32);
	getZoomImage(pimg29, pimg29sta, PFD_side * 0.735, PFD_side * 0.49);
	getZoomImage(pimg30, pimg30sta, PFD_side * 0.735, PFD_side * 0.49);
	
}

void draw_BACKPICTURE(double PFD_x, double PFD_y, double PFD_side){
	putimage_withalpha(NULL, pimg9, 0 , 0 );
	putimage_withalpha(NULL, pimg26, PFD_x + 2.6 * PFD_side, PFD_y - 4.87 * PFD_side);
	putimage_withalpha(NULL, pimg13, PFD_x - 5.05 * PFD_side, PFD_y - 4.35 * PFD_side);

	putimage_withalpha(NULL, pimg11, PFD_x + 2.7 * PFD_side, PFD_y - 4.22 * PFD_side);
	
	putimage_withalpha(NULL, pimg12, PFD_x - 5.35 * PFD_side, PFD_y - 4.72 * PFD_side);
	putimage_withalpha(NULL, pimg27, PFD_x + 7.7 * PFD_side, PFD_y - 4.33 * PFD_side);

	
}
void draw_electricPanel_backgrounds(double PFD_x, double PFD_y, double PFD_side) {
	
	putimage_withalpha(NULL, pimg1, PFD_x - 1.15 * PFD_side, PFD_y - 0.07 * PFD_side);
	putimage_withalpha(NULL, pimg2, PFD_x - 1.11 * PFD_side, PFD_y + 0.168 * PFD_side);
	putimage_withalpha(NULL, pimg3, PFD_x + 1.13 * PFD_side, PFD_y - 1.12 * PFD_side);
	putimage_withalpha(NULL, pimg4, PFD_x + 2 * PFD_side, PFD_y - 1.1 * PFD_side);
	putimage_withalpha(NULL, pimg5, PFD_x + 2 * PFD_side, PFD_y - 0.01* PFD_side);
	putimage_withalpha(NULL, pimg7, PFD_x + 0.7 * PFD_side, PFD_y - 1.835 * PFD_side);
	putimage_withalpha(NULL, pimg6, PFD_x - 2.26 * PFD_side, PFD_y - 1.8 * PFD_side);
	putimage_withalpha(NULL, pimg8, PFD_x - 1.25 * PFD_side, PFD_y + 0.85 * PFD_side);
	putimage_withalpha(NULL, pimg10, PFD_x - 0.80 * PFD_side, PFD_y + 0.8 * PFD_side);
	putimage_withalpha(NULL, pimg14, PFD_x + 2.55 * PFD_side, PFD_y - 1.17 * PFD_side);
	putimage_withalpha(NULL, pimg15, PFD_x + 3.45 * PFD_side, PFD_y - 1.15 * PFD_side);
	putimage_withalpha(NULL, pimg16, PFD_x + 3.87 * PFD_side, PFD_y - 0.79 * PFD_side);
	putimage_withalpha(NULL, pimg17, PFD_x + 4.28 * PFD_side, PFD_y - 1.05 * PFD_side);
	putimage_withalpha(NULL, pimg18, PFD_x + 4.62 * PFD_side, PFD_y - 1.05 * PFD_side);
	putimage_withalpha(NULL, pimg19, PFD_x + 4.42 * PFD_side, PFD_y - 0.79 * PFD_side);
	putimage_withalpha(NULL, pimg20, PFD_x + 5.2 * PFD_side, PFD_y - 1.05 * PFD_side);
	putimage_withalpha(NULL, pimg21, PFD_x + 3.9 * PFD_side, PFD_y - 0.95 * PFD_side);
	putimage_withalpha(NULL, pimg22, PFD_x + 3.98 * PFD_side, PFD_y - 1.11 * PFD_side);
	putimage_withalpha(NULL, pimg23, PFD_x + 4.06 * PFD_side, PFD_y - 0.95 * PFD_side);
	putimage_withalpha(NULL, pimg24, PFD_x + 6.76 * PFD_side, PFD_y + 0.2 * PFD_side);
	putimage_withalpha(NULL, pimg25, PFD_x + 5.65 * PFD_side, PFD_y - 1.88 * PFD_side);
	putimage_withalpha(NULL, pimg28, PFD_x + 3.65 * PFD_side, PFD_y - 1.87 * PFD_side);
	putimage_withalpha(NULL, pimg29, PFD_x + 5.1 * PFD_side, PFD_y + 0.80 * PFD_side);
	putimage_withalpha(NULL, pimg30, PFD_x + 5.87 * PFD_side, PFD_y + 0.80 * PFD_side);
	putimage_withalpha(NULL, pimg8, PFD_x + 7.2 * PFD_side, PFD_y + 0.85 * PFD_side);
	putimage_withalpha(NULL, pimg10, PFD_x + 6.65 * PFD_side, PFD_y + 0.82 * PFD_side);
}

void  draw_delImage() {
	delimage(pimg1);
	delimage(pimg2);
	delimage(pimg3);
	delimage(pimg4);
	delimage(pimg5);
	delimage(pimg7);
	delimage(pimg6);
	delimage(pimg8);
	delimage(pimg9);
	delimage(pimg10);
	delimage(pimg11);
	delimage(pimg12);
	delimage(pimg13);
	delimage(pimg14);
	delimage(pimg15);
	delimage(pimg16);
	delimage(pimg17);
	delimage(pimg18);
	delimage(pimg19);
	delimage(pimg20);
	delimage(pimg21);
	delimage(pimg22);
	delimage(pimg23);
	delimage(pimg24);
	delimage(pimg25);
	delimage(pimg26);
	delimage(pimg27);
	delimage(pimg28);
	delimage(pimg29);
	delimage(pimg30);
}
void getZoomImage(PIMAGE& pimg, PIMAGE& pimgStatic, int width, int height)
{
//	if (pimg == NULL)
//		return;
//	
//	PIMAGE temp = pimg;
////	getimage(temp, fileName);
////	
////	if ((getwidth(pimg) != width) || (getheight(pimg) != height))
////		resize(pimg, width, height);
//	
//	putimage(pimg, 0, 0, width, height, temp, 0, 0, getwidth(temp), getheight(temp));
//	
//	delimage(temp);
	
	
	//pimg为空，或目标图像大小和原图像一样，则不用缩放，直接返回
	if ((pimg == NULL) || (width == getwidth(pimg) && height == getheight(pimg)))
		return;
	
	PIMAGE zoomImage = newimage(width, height);
	putimage(zoomImage, 0, 0, width, height, pimgStatic, 0, 0, getwidth(pimgStatic), getheight(pimgStatic));
	delimage(pimg);
	
	pimg = zoomImage;
	
	
}




//=====================================================//




void change_size(PIMAGE& pimg, int width, int height){
	
	//pimg为空，或目标图像大小和原图像一样，则不用缩放，直接返回
	if ((pimg == NULL) || (width == getwidth(pimg) && height == getheight(pimg)))
		return;
	
	PIMAGE tmp = newimage(width, height);
	putimage(tmp, 0, 0, width, height, pimg, 0, 0, getwidth(pimg), getheight(pimg));
	delimage(pimg);
	
	pimg = tmp;
}


double toRadians1(double a) {
	return a * (PI / 180);
}

//===============地图工具类函数===========//


//Vincenty公式计算两点距离
//return the distance of two point, unit is meter
double getDistance1(double latitude1, double longitude1, double latitude2, double longitude2) {
	// R is the radius of the earth in meters
	double R = 6371004;  //EARTH_RADIUS
	double deltaLatitude = toRadians1(latitude2-latitude1);
	double deltaLongitude = toRadians1(longitude2-longitude1);
	latitude1 =toRadians1(latitude1);
	latitude2 =toRadians1(latitude2);
	double a = pow(sin(deltaLatitude/2), 2)+ cos(latitude1)* cos(latitude2)* pow(sin(deltaLongitude/2), 2);
	double c = 2 * atan2(sqrt(a),sqrt(1-a));
	
	double d = R * c;
	return d;
}

double getBearing1(double lat1, double lon1, double lat2, double lon2){
	lat1 = toRadians1(lat1);
	lat2 = toRadians1(lat2);
	lon1 = toRadians1(lon1);
	lon2 = toRadians1(lon2);
	double dLon = lon2 - lon1;
	double y = sin(dLon) * cos(lat2);
	double x = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos( dLon);
	double brng = atan2(y, x);
	brng=brng * 180 / PI;
	brng = fmod((brng + 360), 360);
	return brng;
}

//==================================//


void draw_plane(double center_x, double center_y, double side,double angle)
{
	//对参数的说明：
	//center_x ，center_y 是中心点的坐标，side 是这个飞机的长（机头到机尾）
	
	angle = angle * PI / 180;
	
	double single = side / 15;
	
	setfillcolor(EGEARGB(0xff, 0xba, 0x3c, 0x1a));
	
	double x01 = 0, y01 =  - single * 7.9;
	double x02 =  - single * 1.25, y02 =  - single * 7;
	double x03 =  - single * 1.25, y03 =  + single * 4.5;
	double x04 =  - single * 4, y04 =  + single * 7.5;
	double x05 =  - single * 3, y05 =  + single * 8.5;
	double x06 = 0, y06 =  + single * 6.7;
	double x07 =  + single * 3, y07 =  + single * 8.5;
	double x08 =  + single * 4, y08 =  + single * 7.5;
	double x09 =  + single * 1.25, y09 =  + single * 4.5;
	double x010 =  + single * 1.25, y010 =  - single * 7;
	
	ege_point points1[11] = {
		{x01 * cos(angle) - y01 * sin(angle) + center_x,x01 * sin(angle) + y01 * cos(angle) + center_y},
		{x02 * cos(angle) - y02 * sin(angle) + center_x,x02 * sin(angle) + y02 * cos(angle) + center_y},
		{x03 * cos(angle) - y03 * sin(angle) + center_x,x03 * sin(angle) + y03 * cos(angle) + center_y},
		{x04 * cos(angle) - y04 * sin(angle) + center_x,x04 * sin(angle) + y04 * cos(angle) + center_y},
		{x05 * cos(angle) - y05 * sin(angle) + center_x,x05 * sin(angle) + y05 * cos(angle) + center_y},
		{x06 * cos(angle) - y06 * sin(angle) + center_x,x06 * sin(angle) + y06 * cos(angle) + center_y},
		{x07 * cos(angle) - y07 * sin(angle) + center_x,x07 * sin(angle) + y07 * cos(angle) + center_y},
		{x08 * cos(angle) - y08 * sin(angle) + center_x,x08 * sin(angle) + y08 * cos(angle) + center_y},
		{x09 * cos(angle) - y09 * sin(angle) + center_x,x09 * sin(angle) + y09 * cos(angle) + center_y},
		{x010 * cos(angle) - y010 * sin(angle) + center_x,x010 * sin(angle) + y010 * cos(angle) + center_y},
		{x01 * cos(angle) - y01 * sin(angle) + center_x,x01 * sin(angle) + y01 * cos(angle) + center_y}
	};
	ege_fillpoly(11,points1);
	
	double x11 = -single * 1.25, y11 = -single * 3;
	double x12 = -single * 7, y12 = -single * 0.5;
	double x13 = -single * 7, y13 = +single + 1.5;
	double x14 = -single * 1.25, y14 = 0;
	ege_point points2[5] = {
		{x11 * cos(angle) - y11 * sin(angle) + center_x,x11 * sin(angle) + y11 * cos(angle) + center_y},
		{x12 * cos(angle) - y12 * sin(angle) + center_x,x12 * sin(angle) + y12 * cos(angle) + center_y},
		{x13 * cos(angle) - y13 * sin(angle) + center_x,x13 * sin(angle) + y13 * cos(angle) + center_y},
		{x14 * cos(angle) - y14 * sin(angle) + center_x,x14 * sin(angle) + y14 * cos(angle) + center_y},
		{x11 * cos(angle) - y11 * sin(angle) + center_x,x11 * sin(angle) + y11 * cos(angle) + center_y}
	};
	ege_fillpoly(5,points2);
	
	double x21 = single * 1.25, y21 = -single * 3;
	double x22 = single * 7, y22 = -single * 0.5;
	double x23 = single * 7, y23 = +single + 1.5;
	double x24 = single * 1.25, y24 = 0;
	
	ege_point points3[5] = {
		{x21 * cos(angle) - y21 * sin(angle) + center_x,x21 * sin(angle) + y21 * cos(angle) + center_y},
		{x22 * cos(angle) - y22 * sin(angle) + center_x,x22 * sin(angle) + y22 * cos(angle) + center_y},
		{x23 * cos(angle) - y23 * sin(angle) + center_x,x23 * sin(angle) + y23 * cos(angle) + center_y},
		{x24 * cos(angle) - y24 * sin(angle) + center_x,x24 * sin(angle) + y24 * cos(angle) + center_y},
		{x21 * cos(angle) - y21 * sin(angle) + center_x,x21 * sin(angle) + y21 * cos(angle) + center_y}
	};
	ege_fillpoly(5, points3);
}



extern int renewMap;
extern vector<WAYPOINT> fullRoute;

void draw_map(){
	
	setfillcolor(WHITE);
	ege_fillrect(map_x,map_y,map_side,map_side);
	
	//对更新信号进行更新 2是更新完成，1是需要更新，0保持不变
	if(renewMap == 2){
		PIMAGE imgTmp = newimage();
		getimage(imgTmp, "./map.png");
		delimage(img);
		img = imgTmp;
		renewMap = 0;
		map_center.lat = map_centerTmp.lat;
		map_center.lon = map_centerTmp.lon;
	}
	
	//快要出边界发出更新信号
	if(pos_x + pos_x_move_plane + side >= 1800 || pos_y + pos_y_move_plane + side >= 1800 ||
		pos_x + pos_x_move_plane <= 100 || pos_y + pos_y_move_plane <= 100){
		
		renewMap = 1;
		map_centerTmp.lat = latitude;
		map_centerTmp.lon = longitude;
	}
	
	
	//截取原图一部分
	getimage(mapShow, img, pos_x + pos_x_move + pos_x_move_plane, pos_y + pos_y_move + pos_y_move_plane, side, side);
	
	//调整大小，正好显示下
	change_size(mapShow, map_side, map_side);
	
	//显示图片
	putimage_withalpha(NULL, mapShow, map_x, map_y);
	
	
	
	
	
	//在按下shift时进行地图的移动和放大
	if (GetAsyncKeyState(0x10) & 0x8000) {
		
		//实现移动
		if (GetAsyncKeyState(0x01) & 0x8000) {
			
			if (is_down == 0) {
				mousepos(&map_mouse_x, &map_mouse_y);
				is_down = 100;
				map_mouse_x_cur = map_mouse_x;
				map_mouse_y_cur = map_mouse_y;
			}
			if (is_down == 100) {
				mousepos(&map_mouse_x, &map_mouse_y);
				pos_x_move = -(map_mouse_x - map_mouse_x_cur);
				pos_y_move = -(map_mouse_y - map_mouse_y_cur);
				pos_x_move += pos_x_move_tmp;
				pos_y_move += pos_y_move_tmp;
			}
		} else if (is_down == 100) {
			is_down = 0;
			pos_x_move_tmp = pos_x_move;
			pos_y_move_tmp = pos_y_move;
		}
		
		//滚轮实现放大缩小
		mouse_msg msgRecord = { 0 };
		bool redraw = true;
		
		while (mousemsg()) {
			//getmouse 获取鼠标消息
			msgRecord = getmouse();
			redraw = true;
		}
		if (redraw) {
			
			if (msgRecord.is_wheel()) {
				if (msgRecord.wheel < 0 && side < 1024) {
					side -= msgRecord.wheel / 10;
				} else if (msgRecord.wheel > 0 && side > 15) {
					side -= msgRecord.wheel / 10;
				}
			}
			
		}
		
	}
	
	//地图大小始终2048不需要设置为变量
	pos_x = 2048 / 2 - side / 2;
	pos_y = 2048 / 2 - side / 2;
	
	//改变显示范围，始终以飞机为中心
	//323.148572641130506974593（原图2048*2048） 对应21784.4393 m
	//即每个像素对应67.413076041 m
	//则图形变换后在ege中 每个像素对应500 / 480 * 67.413076041 m  即 70.221954209375 m  //主要看缩放那里
	double angle = getBearing1(map_center.lat, map_center.lon, latitude, longitude);
	double dis = getDistance1(map_center.lat, map_center.lon, latitude, longitude);
	pos_x_move_plane =  dis * sin(toRadians1(angle)) / 70.22195420;//实际上这个67好像就是ege窗口上每个像素对应的距离
	pos_y_move_plane = - dis * cos(toRadians1(angle)) / 70.22195420;
	
	
	double plane_x = map_x + map_side / 2 - pos_x_move * (500.0 / side);
	double plane_y = map_y + map_side / 2 - pos_y_move * (500.0 / side);
	
//	setfillcolor(EGEARGB(0x90, 0x00, 0x00, 0x00));
//	ege_fillellipse(plane_x - 10 , plane_y - 10, 20, 20);
//	setlinewidth(3);
//	setcolor(BLACK);
//	ege_ellipse(plane_x - 10 , plane_y - 10, 20, 20);
	if(plane_x > map_x + map_side || plane_y >= map_y + map_side){
	}
	else{
		draw_plane(plane_x, plane_y, 30, rotationangle);
	}
	
//	//显示更新信号
//	char tmp[10];
//	sprintf(tmp, "%d", renewMap);
//	xyprintf(100, 100 ,tmp);
	
	
	//绘制已经走过的航线
	for(auto it = fullRoute.begin(); it + 1 != fullRoute.end(); it ++){
		
		WAYPOINT wp1 = *(it);
		WAYPOINT wp2 = *(it + 1);
		
		
		double dis = getDistance1(latitude, longitude, wp1.lat, wp1.lon);
		double bearing = getBearing1(latitude, longitude, wp1.lat, wp1.lon);
		
		
		double rl = dis / ((1.0 * side / map_side) * 67.413076041);
		double rx = (cos(toRadians1(bearing - 90)) * rl) + (map_x + map_side / 2);
		double ry = (sin(toRadians1(bearing - 90)) * rl) + (map_y + map_side / 2);
		
		
		double dis2 = getDistance1(latitude, longitude, wp2.lat, wp2.lon);
		double bearing2 = getBearing1(latitude, longitude, wp2.lat, wp2.lon);
		
		double rl2 = dis2 / ((1.0 * side / map_side) * 67.413076041);
		double rx2 = (cos(toRadians1(bearing2 - 90)) * rl2) + (map_x + map_side / 2);
		double ry2 = (sin(toRadians1(bearing2 - 90)) * rl2) + (map_y + map_side / 2);
		
		setlinewidth(0.003 * side);
		
		if(rx > map_x + map_side || ry >= map_y + map_side || rx2 > map_x + map_side || ry2 >= map_y + map_side){
			continue;
		}
		ege_line(rx - pos_x_move * (500.0 / side), ry - pos_y_move * (500.0 / side), rx2 - pos_x_move * (500.0 / side), ry2 - pos_y_move * (500.0 / side));
		
	}
	
}
