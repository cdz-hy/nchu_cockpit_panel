
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
#include "ReadFiles.h"

int main() {

	//读取文件初始化环境
	read_files();
	
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
