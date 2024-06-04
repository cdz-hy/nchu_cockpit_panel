
//引用头文件
#include <graphics.h>
#include <windows.h>
#include <math.h>
#include <cstdio>
#include <string>
#include <regex>
#include <iostream>
#include <thread>
using namespace std;

#include "DrawPanels.h"
#include "DataReceive.h"
#include "G_variable.h"

void get_keymsg();


int main() {


	//读取配置文件
	regex pattern_height(R"(Window Height = [0-9]+)");
	regex pattern_length(R"(Window Length = [0-9]+)");

	char tmp[0xFF];
	FILE *file = fopen("Panels simulation.ini", "r");

	if (file != NULL) {
		while (!feof(file)) {
			fgets(tmp, 0xFF, file);
			char *p = NULL;
			//窗口长
			if (strstr(tmp, "Length")) {
				p = strstr(tmp, "=");
				p += 2;
				length = stoi(p);
			}
			//窗口高（宽）
			else if (strstr(tmp, "Height")) {
				p = strstr(tmp, "=");
				p += 2;
				height = stoi(p);
			}
			//是否显示背景等
			else if (strstr(tmp, "Show Background")) {
				p = strstr(tmp, "=");
				p += 2;

//				if(!strcmp("false",p)){
//					is_showbk = 0;
//				}

				is_showbk = stoi(p);
			}
			//是否开启UDP传输数据
			else if (strstr(tmp, "UDP transmission")) {
				p = strstr(tmp, "=");
				p += 2;
				UDP_transmission = stoi(p);
			}
			//IP地址
			else if (strstr(tmp, "IP address")) {
				p = strstr(tmp, "=");
				p += 2;
				IP_address = p;
			}
			//UDP端口
			else if (strstr(tmp, "UDP port")) {
				p = strstr(tmp, "=");
				p += 2;
				UDP_port = stoi(p);
			}
			//显示背景
			else if (strstr(tmp, "Show Background")) {
				p = strstr(tmp, "=");
				p += 2;
				showFPS = stoi(p);
			}
		}
	}


	//绘图环境设置
	initgraph(length, height, INIT_ANIMATION);
	setcaption("Boeing727-200F&737-800仪表模拟");
	setrendermode(RENDER_MANUAL);
	setbkcolor(EGEARGB(0xff, 0x1b, 0x20, 0x25));
	setbkcolor(EGEARGB(0xff, 0x37, 0x37, 0x3d));
	ege_enable_aa(true);

	
	//创建读取文件和绘制表盘(带按钮操作)两个线程
	
	thread panels(draw_panels);
	thread datas(data_receive);		
	
	
	panels.join();
	datas.join();

	
	closegraph();
	return 0;
	
}
