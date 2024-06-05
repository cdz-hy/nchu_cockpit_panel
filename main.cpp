
//引用头文件
#include <graphics.h>
#include <windows.h>
#include <math.h>
#include <cstdio>
#include <string>
#include <regex>
#include <iostream>
#include <thread>
#include <fstream>
using namespace std;

#include "DrawPanels.h"
#include "DataReceive.h"
#include "G_variable.h"
#include "G_structs.h"
#include "KeyboardControl.h"


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

	
	
	//读取航路点文件
	
	extern vector<WAYPOINT> waypoints;
	string inputTmp;
	ifstream inputFile("fix_data.dat");
	
	if (inputFile.is_open()) {
		while (getline(inputFile,inputTmp)) {
			
			WAYPOINT wpTmp;
			istringstream issTmp(inputTmp);
			
			string stringTmp[10];
			
			issTmp >> wpTmp.lat >> wpTmp.lon >> stringTmp[0] >> stringTmp[1] >> stringTmp[2] >> stringTmp[3];
			
			strcpy(wpTmp.name, stringTmp[0].c_str());
			strcpy(wpTmp.type, stringTmp[1].c_str());
			strcpy(wpTmp.FIRName, stringTmp[2].c_str());
			strcpy(wpTmp.fullType, stringTmp[3].c_str());
			wpTmp.num = 1;
			
			waypoints.push_back(wpTmp);
			
		}
	}
	
	inputFile.close();
	
	
	//读取航路文件
	
	extern vector<WAYPOINT> route;
	ifstream inputFile2("ZSCNZSSS.fms");
	
	if (inputFile2.is_open()) {
		while (getline(inputFile2,inputTmp)) {
			
			WAYPOINT wpTmp;
			istringstream issTmp(inputTmp);
			
			string stringTmp[10];
			
			if(issTmp >> stringTmp[0] >> stringTmp[1] >> stringTmp[2] >> wpTmp.lat >> wpTmp.lon ){
				
				strcpy(wpTmp.code, stringTmp[0].c_str());
				strcpy(wpTmp.name, stringTmp[1].c_str());
				strcpy(wpTmp.fullName, stringTmp[1].c_str());
				
				if(stringTmp[1].length() == 3){
					wpTmp.num = 2;//VOR
				}
				else if(stringTmp[1].length() == 5){
					wpTmp.num = 1;//waypoint
				}
				else if(stringTmp[1].length() == 3){
					wpTmp.num = 4;//airport
				}
				
				route.push_back(wpTmp);
				
			}
			else{
				continue;
			}
			
		}
	}
	
	inputFile2.close();
	
	
	
	
	
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
	thread control(get_keymsg);	
	
	panels.join();
	datas.join();
	control.join();

	
	closegraph();
	return 0;
	
}
