
//引用头文件
#include <graphics.h>
#include <windows.h>
#include <math.h>
#include <string>
#include <iostream>
#include <thread>
using namespace std;

#include "DrawPanels.h"
#include "DataReceive.h"
#include "DataReceive2.h"
#include "MapReceive.h"
#include "G_variable.h"
#include "G_structs.h"
#include "KeyboardControl.h"
#include "ReadFiles.h"
#include "NewWindows.h"
#include "ShowMap.h"
#include "ShowPFD.h"
#include "ShowND.h"
#include "ShowEICAS.h"
#include "ShowEICAS2.h"
#include "ShowFMC.h"

int main() {
	
	//读取文件初始化环境
	read_files();
	
	//绘图环境设置
	initgraph(length, height, INIT_ANIMATION);
	setcaption("Boeing727-200F&737-800仪表模拟");
	setrendermode(RENDER_MANUAL);
	setbkcolor(EGEARGB(0xff, 0x1b, 0x20, 0x25));
	setbkcolor(EGEARGB(0xff, 0x37, 0x37, 0x3d));
	setbkcolor(EGEARGB(0xff, 0x14, 0x17, 0x19));
	ege_enable_aa(true);
	
//	egeHDC = getHDC();
	egeHWND = getHWnd();
	
	DWORD dwLength = GetModuleFileNameW(NULL, path, MAX_PATH);
	
	//设置窗口无边框
	HWND hwnd = getHWnd();
	
	LONG style = GetWindowLong(hwnd, GWL_STYLE);
	style &= ~(WS_CAPTION | WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
	SetWindowLong(hwnd, GWL_STYLE, style);
		
	// 强制窗口重绘
	RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
	
	
	//创建读取文件和绘制表盘(带按钮操作)两个线程
	
	thread panels(draw_panels);
	thread datas(data_receive);	
	thread datas2(data_receive2);	
//	thread control(get_keymsg);	
	thread maps(map_receive);
	thread info(info_receive);
	thread newWindows(create_new_windows);
	thread showMap(show_map);
	thread routeWay(read_routeWays);
	thread showPFD(show_pfd);
	thread showND(show_nd);
	thread showEICAS(show_eicas);
	thread showEICAS2(show_eicas2);
	thread showFMC(show_fmc);
	
	panels.join();
	datas.join();
	datas2.join();
//	control.join();
	maps.join();
	info.join();
	newWindows.join();
	showMap.join();
	routeWay.join();
	showPFD.join();
	showND.join();
	showEICAS.join();
	showEICAS2.join();
	showFMC.join();
	
	closegraph();
	return 0;
	
}

