//引用头文件
#include <stdio.h>
#include <graphics.h>
#include <windows.h>

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
//#include "DrawNDPln.h"
#include "DrawPFDStandby.h"
//#include "DrawNDMap.h"
//#include "DrawNDAppCenter.h"
#include "DrawEICAS.h"
#include "DrawChronometer.h"
#include "DrawEHISControl.h"

#include "DrawND.h"

#include "DrawNDInfo.h"


void draw_panels(){
	
	
	
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
	//单位长度，初始为0.05高
	double unit_side = getheight() / 20;
	
	
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
	double ND_move_x = 0;
	double ND_move_y = 0;
	double ND_move_x_tmp = 0;
	double ND_move_y_tmp = 0;
	
	
	// 此时鼠标是否按下
	int is_down = 0;
	
	// 保存刚按下鼠标时的鼠标坐标
	int mouse_x_cur = 0;
	int mouse_y_cur = 0;
	
	//存储鼠标按下时间判断双击
	double click_time = -1;

	
	double dirtmp = 0;
	
	for (; is_run(); delay_fps(60)) {
		dirtmp += 0.3;
		
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
		double PFD_side = 15 * unit_side;
		double PFD_x = center_x + PFD_move_x * unit_side;
		double PFD_y = center_y + PFD_move_y * unit_side;
		
		//ND
		double ND_side = 15 * unit_side;
		double ND_x = 1.2 * center_x + ND_move_x * unit_side;
		double ND_y = 1.2 * center_y + ND_move_y * unit_side;
		
		
		
		//界面为0时显示全部六个机械表盘
		if (show == 0) {
			
//			char tmp[10];
//			sprintf(tmp,"%d",is_showbk);
//			xyprintf(20,20,tmp);
			
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
				
				
				
//				//使用鼠标右键和GetAsyncKeyState异步实现放大变小
//				if(GetAsyncKeyState(0x02) & 0x8000){
//					if(is_down == 0){
//						is_down = 11;
//						mouse_x_cur = mouse_x;
//						mouse_y_cur = mouse_y;
//					}
//					if(is_down == 11){
//						mousepos(&mouse_x, &mouse_y);
//						if(mouse_y > mouse_y_cur){
//							if(unit_side > 15){
//								unit_side -= (mouse_y - mouse_y_cur) / 200;
//							}
//						}
//						else{
//							if(unit_side < 100){
//								unit_side -= (mouse_y - mouse_y_cur) / 200;
//							}
//						}
//					}
//
//				}
//				else if(is_down == 11){
//					is_down = 0;
//				}
				
				
				
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
//					AI_move_x_tmp = AI_move_x;
//					AI_move_y_tmp = AI_move_y;
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
//					AI_move_x = AI_move_x_tmp;
//					AI_move_y = AI_move_y_tmp;
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
		
		
		
		//界面为10时显示所有电子仪表
		else if(show == 10){
			
			//设置底座颜色
			setfillcolor(BLACK);
//				//正常大小
//			ege_fillrect(PFD_x - PFD_side / 2, PFD_y - PFD_side / 2,1.07 * PFD_side, PFD_side);
			//为遮盖compass多余部分的版本
			ege_fillrect(PFD_x - PFD_side / 2, PFD_y - PFD_side / 2,1.07 * PFD_side,1.05 * PFD_side);
			
			mousepos(&mouse_x, &mouse_y);
			if(mouse_x >= PFD_x - PFD_side / 2 && mouse_y >= PFD_y - PFD_side / 2 && mouse_x <= PFD_x + 0.57 * PFD_side && mouse_y <= PFD_y + PFD_side / 2){
				setcolor(EGEARGB(0x50, 0xff, 0xff, 0xff));
				setlinewidth(0.05 * unit_side_static);
				ege_rectangle(PFD_x - PFD_side / 2, PFD_y - PFD_side / 2,1.07 * PFD_side, PFD_side);
			}
			
			
//			Draw_PFD_frame(PFD_x + 0.06 * PFD_side, PFD_y ,PFD_side);
//			draw_PFD_AI(PFD_x, PFD_y ,PFD_side);
//			
//			
//			draw_PFD_compass(PFD_x , PFD_y + 60.0 / 96 * PFD_side,PFD_side);
////			draw_PFD_compass(PFD_x , PFD_y + 63.0 / 96 * PFD_side,PFD_side);
////			draw_PFD_compass(PFD_x , PFD_y + 66.0 / 96 * PFD_side,PFD_side);
//			
//			draw_PFD_airspeed(PFD_x - 34.5 / 96 * PFD_side, PFD_y ,PFD_side);
//			draw_PFD_alt(PFD_x + 35.0 / 96 * PFD_side, PFD_y ,PFD_side);
//			draw_PFD_RCDI(PFD_x + 49.5 / 96 * PFD_side, PFD_y ,PFD_side);
////			draw_PFD_standby(PFD_x + 1.5 * PFD_side, PFD_y ,PFD_side / 3);
//			draw_PFD_top(PFD_x, PFD_y - 41.0 / 96 * PFD_side,PFD_side);
//			draw_1(PFD_x  + 20.0 / 96 * PFD_side, PFD_y - 31.0 / 96 * PFD_side,PFD_side);
			
			draw_PFD(PFD_x, PFD_y ,PFD_side);
			
//			//设置ND底座颜色
//			setfillcolor(BLACK);
//			ege_fillrect(PFD_x + 1.2 * PFD_side - PFD_side / 2, PFD_y - PFD_side / 2,1.07 * PFD_side,1.05 * PFD_side);
			
			
//			draw_PFD_frame(PFD_x + 1.4 * PFD_side, PFD_y ,PFD_side);
//			
//			if(ND_choice == 1){
//				draw_ND_pln(PFD_x + 1.4 * PFD_side, PFD_y ,PFD_side);
//				WAYPOINT nowPos = {0,"", 28.877 - 0.01 * dirtmp, 115.91 + 0.005 * dirtmp, "", "", "", 100, "", ""};
////				WAYPOINT nowPos = {0,"", latitude, longitude, "", "", "", 100, "", ""};
//				draw_waypoint(nowPos,rotationangle,mapDistance,PFD_x + 1.4 * PFD_side, PFD_y ,PFD_side);
//				draw_route(nowPos,dirtmp,mapDistance,PFD_x + 1.4 * PFD_side, PFD_y ,PFD_side);
//			}
//			else if(ND_choice == 2){
//				draw_ND_map(PFD_x + 1.4 * PFD_side, PFD_y + PFD_side * 32 / 104 /* + PFD_side / 3 */,PFD_side);
//				WAYPOINT nowPos = {0,"", 28.877, 115.91, "", "", "", 100, "", ""};
////				draw_waypoint_map(nowPos,dirtmp,mapDistance,PFD_x + 1.4 * PFD_side, PFD_y + PFD_side * 37.6 / 104 ,PFD_side);
////				draw_route_map(nowPos,dirtmp,mapDistance,PFD_x + 1.4 * PFD_side, PFD_y + PFD_side * 37.6 / 104, PFD_side);
//				draw_waypoint_map(nowPos,dirtmp,mapDistance,PFD_x + 1.4 * PFD_side, PFD_y + PFD_side * 32 / 104 ,PFD_side);
//				draw_route_map(nowPos,dirtmp,mapDistance,PFD_x + 1.4 * PFD_side, PFD_y + PFD_side * 32 / 104, PFD_side);
//			}
//			else if(ND_choice == 3){
//				draw_ND_app_center(PFD_x + 1.4 * PFD_side, PFD_y ,PFD_side);
//			}
			
			draw_ND(PFD_x + 1.4 * PFD_side, PFD_y ,PFD_side);
			
			if(GetAsyncKeyState(0x35) & 0x0001){
				ND_choice += 1;
				ND_choice %= 4;
			}
			
			//备用表
			draw_PFD_standby(PFD_x + 3.8 * PFD_side, PFD_y ,PFD_side / 5);
			
			//画计时器
			draw_Chronometer(PFD_x - 0.85 * PFD_side, PFD_y - 0.3 * PFD_side,0.45 * PFD_side);
			
			
			//画EICAS
			draw_EICAS(PFD_x + 2.7 * PFD_side, PFD_y ,PFD_side);
			
			//画EHIS的控制面板
			draw_EHIS_control(PFD_x, PFD_y - 1 * PFD_side ,PFD_side);
			
			//实现PFD的移动
			if (GetAsyncKeyState(0x01) & 0x8000) {
				if (is_down == 0/* && mouse_x >= PFD_x - PFD_side / 2 && mouse_y >= PFD_y - PFD_side / 2 && mouse_x <= PFD_x + 0.57 * PFD_side && mouse_y <= PFD_y + PFD_side / 2*/) {
					is_down = 11;
					mouse_x_cur = mouse_x;
					mouse_y_cur = mouse_y;
				}
				if (is_down == 11) {
					mousepos(&mouse_x, &mouse_y);
					PFD_move_x = (mouse_x - mouse_x_cur) / unit_side;
					PFD_move_y = (mouse_y - mouse_y_cur) / unit_side;
					PFD_move_x += PFD_move_x_tmp;
					PFD_move_y += PFD_move_y_tmp;
				}
			} else if (is_down == 11) {
				
				//全屏展示PFD表
				if (mouse_x >= PFD_x - 0.5 * PFD_side && mouse_x <= PFD_x + 0.5 * PFD_side && mouse_y >= PFD_y - 0.5 * PFD_side && mouse_y <= PFD_y + 0.5 * PFD_side) {
					if (fclock() - click_time < 0.3) {
						show = 11;
					} else {
						click_time = fclock();
					}
				}
				
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
						if (msgRecord.wheel > 0 && unit_side < 130) {
							unit_side += msgRecord.wheel / 30;
						} else if (msgRecord.wheel < 0 && unit_side > 15) {
							unit_side += msgRecord.wheel / 30;
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
		
	}
	
	
}


