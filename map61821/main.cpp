#include <graphics.h>
#include <bits/stdc++.h>
#include <math.h>
using namespace std;

typedef struct waypoint{
	
	int num;	//表示塔台类型，这是自己加的，便于区分是VOR还是普通航点 1/2/3	航点/VOR/机场
	char code[20];	// 编号（3/12表示是NDB/VOR?）
	double lat;		// 纬度
	double lon;		// 经度
	char name[20];	// 塔台名称
	char type[20]; 	// 塔台类型（是否航路上都能用（ENRT））
	char freq[20];	// 频率
	double range;	// 接收范围
	char devi[20];	// 磁偏差
	char FIRName[20];	// 情报区代码
	char fullName[20];	// 名称（更长）
	char fullType[20];	// 塔台类型（更全）
	
}WAYPOINT;

typedef struct {
	
	//飞机中心坐标
	double latitude ;
	double longitude ;
	int renewMap;
	
	//经过的航线
	WAYPOINT fullRoute[30000];
	int routeNum;
	
	double rotationangle;
	
	char mapProvince[64];
	char mapCity[64];
	char mapAdcode[64];
	char mapWeather[64];
	char mapTemperature[64];
	char mapWinddirection[64];
	char mapWindpower[64];
	char mapHumidity[64];
	char mapTownship[64];
	char mapStreet[64];
	
} SharedData;

void change_size(PIMAGE& pimg, int width, int height);
double toRadians(double a);
double getDistance(double latitude1, double longitude1, double latitude2, double longitude2);
double getBearing(double lat1, double lon1, double lat2, double lon2);
char* WideCharToString(const WCHAR* wideStr);
void draw_plane(double center_x, double center_y, double side,double angle);

//经过的航线
vector<WAYPOINT> fullRoute;

//实现移动
int is_down = 0;
double pos_x_move = 0;
double pos_y_move = 0;
double pos_x_move_tmp = 0;
double pos_y_move_tmp = 0;
double pos_x_move_plane = 0;
double pos_y_move_plane = 0;

//记录鼠标
int mouse_x = 0;
int mouse_y = 0;
int mouse_x_cur = 0;
int mouse_y_cur = 0;

char mapProvince[64];
char mapCity[64];
char mapAdcode[64];
char mapWeather[64];
char mapTemperature[64];
char mapWinddirection[64];
char mapWindpower[64];
char mapHumidity[64];
char mapTownship[64];
char mapStreet[64];

//地图中心点坐标
//WAYPOINT map_center = {0, "", 28.877, 115.91,};
WAYPOINT map_center = {0, "", 0, 0,};

//临时地图中心点坐标
//WAYPOINT map_centerTmp = {0, "", 28.877, 115.91,};
WAYPOINT map_centerTmp = {0, "", 0, 0,};

//飞机坐标lat和lon在共享内存中

//显示模式（机头向上或者正北向上）
int showMode = 0;

int main()
{
	WCHAR mySharedMemory[] =  L"Global\\MySharedMemory";
	char* mySharedMemoryA = WideCharToString(mySharedMemory);
	
	WCHAR eventData[] =  L"EventDataAvailable";
	char* eventDataA  = WideCharToString(eventData);
	
	// 打开共享内存
	HANDLE hMapFile = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,    // 可读可写
		FALSE,                  // 不从继承句柄中映射
		mySharedMemoryA // 共享内存名称
		);

	
	if (hMapFile == NULL) {
		printf("OpenFileMapping failed (%d).\n", GetLastError());
		return -1;
	}
	
	// 打开事件
	HANDLE hEvent = OpenEvent(
		EVENT_ALL_ACCESS,
		false, 
		eventDataA
//		TEXT("Global\\MySharedEvent")
		);
	
	if (hEvent == NULL) {
		printf("OpenEvent failed (%d).\n", GetLastError());
		return -1;
	}
	
	// 映射共享内存到进程地址空间
	SharedData* pData = (SharedData*)MapViewOfFile(
		hMapFile,               // 共享内存句柄
		FILE_MAP_ALL_ACCESS,    // 可读可写
		0,                      // 高位文件偏移
		0,                      // 低位文件偏移
		sizeof(SharedData)          // 要映射的长度
		);
	
	if (pData == NULL) {
		printf("MapViewOfFile failed (%d).\n", GetLastError());
		CloseHandle(hMapFile);
		return -1;
	}
	
//	// 子进程中声明事件句柄
//	HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	
//	initgraph( 480, 480, INIT_RENDERMANUAL);
//	setbkcolor(WHITE);
	initgraph(720, 545, INIT_RENDERMANUAL);
	setbkcolor(EGEARGB(0XFF, 46,69,93));
	
	ege_enable_aa(true);
	
	//设置窗口最顶层
	SetWindowPos(getHWnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	
	PIMAGE img = newimage();
	PIMAGE show = newimage();
	
	//图片显示范围
	double side = 500;
	double pos_x = 2048 / 2 - side / 2;
	double pos_y = 2048 / 2 - side / 2;
	
	//地图中心坐标
	double map_x = 0;
	double map_y = 0;
	double map_side = 480;
	
	//读取图片
	if(pData->renewMap == 2){
		getimage(img, "map.png");
		pData->renewMap = 0;
		SetEvent(hEvent);
	}
	
	for ( ; is_run(); delay_fps(60) )
	{
		
		cleardevice();
		
		//--------------------------------------//
		setfillcolor(EGEARGB(0XFF, 38,50,64));
		ege_fillrect(0,0,720,40);
		
		setbkmode(TRANSPARENT);
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		setfont(35, 0, "黑体");
		setcolor(EGEARGB(150, 177, 177, 178));
		ege_drawtext("MAP", 360,24);
		//--------------------------------------//
		
		strcpy(mapProvince, pData->mapProvince);
		strcpy(mapCity, pData->mapCity);
		strcpy(mapAdcode, pData->mapAdcode);
		strcpy(mapWeather, pData->mapWeather);
		strcpy(mapTemperature, pData->mapTemperature);
		strcpy(mapWinddirection, pData->mapWinddirection);
		strcpy(mapWindpower, pData->mapWindpower);
		strcpy(mapHumidity, pData->mapHumidity);
		strcpy(mapTownship,pData->mapTownship);
		strcpy(mapStreet,pData->mapStreet);
		
		//对更新信号进行更新 2是更新完成，1是需要更新，0保持不变
		if(pData->renewMap == 2){
			PIMAGE imgTmp = newimage();
			getimage(imgTmp, "./map.png");
			delimage(img);
			img = imgTmp;
			pData->renewMap = 0;
//			printf("%d",pData->renewMap);
//			SetEvent(hEvent);
//			printf("reading");
//			printf("%d\n",pData->renewMap);
			map_center.lat = map_centerTmp.lat;
			map_center.lon = map_centerTmp.lon;
		}
		
		//快要出边界发出更新信号
		if(pos_x + pos_x_move_plane + side >= 1800 || pos_y + pos_y_move_plane + side >= 1800 ||
			pos_x + pos_x_move_plane <= 100 || pos_y + pos_y_move_plane <= 100){
			
			pData->renewMap = 1;
//			SetEvent(hEvent);
			map_centerTmp.lat = pData->latitude;
			map_centerTmp.lon = pData->longitude;

		}
		
			
		//截取原图一部分
		getimage(show, img, pos_x + pos_x_move + pos_x_move_plane, pos_y + pos_y_move + pos_y_move_plane, side, side);
		
		//调整大小，正好显示下
		change_size(show, 480, 480);
		
		//显示图片
//		putimage_withalpha(NULL, show, 0, 0);
		//--------------------------------------//
		
		putimage_withalpha(NULL, show, 12, 38+15);
		
		//--------------------------------------//
			
		
		//实现移动
		if (GetAsyncKeyState(0x01) & 0x8000) {
			if (is_down == 0) {
				mousepos(&mouse_x, &mouse_y);
				is_down = 1;
				mouse_x_cur = mouse_x;
				mouse_y_cur = mouse_y;
			}
			if (is_down == 1) {
				mousepos(&mouse_x, &mouse_y);
				pos_x_move = -(mouse_x - mouse_x_cur);
				pos_y_move = -(mouse_y - mouse_y_cur);
				pos_x_move += pos_x_move_tmp;
				pos_y_move += pos_y_move_tmp;
			}
		} else if (is_down == 1) {
			is_down = 0;
			pos_x_move_tmp = pos_x_move;
			pos_y_move_tmp = pos_y_move;
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
					if (msgRecord.wheel < 0 && side < 800) {
						side -= msgRecord.wheel / 10;
					} else if (msgRecord.wheel > 0 && side > 100) {
						side -= msgRecord.wheel / 10;
					}
				}
				
			}
			
		}
		
		
		
		pos_x = 2048 / 2 - side / 2;
		pos_y = 2048 / 2 - side / 2;
		
		
		//改变显示范围，始终以飞机为中心
		//323.148572641130506974593（原图2048*2048）像素 对应21784.4393 m
		//即每个像素对应67.413076041 m
		//则图形变换后在ege中 每个像素对应500 / 480 * 67.413076041 m  即 70.221954209375 m  //主要看缩放那里
		double angle = getBearing(map_center.lat, map_center.lon, pData->latitude, pData->longitude);
		double dis = getDistance(map_center.lat, map_center.lon, pData->latitude, pData->longitude);
		pos_x_move_plane =  dis * sin(toRadians(angle)) / 70.22195420;//实际上这个67好像就是ege窗口上每个像素对应的距离
		pos_y_move_plane = - dis * cos(toRadians(angle)) / 70.22195420;
		
		//调试用
//		char tmp[10];
//		sprintf(tmp,"%.2f",pData->latitude);
//		xyprintf(50,50,tmp);
//		sprintf(tmp,"%.2f",pData->longitude);
//		xyprintf(50,70,tmp);
//		sprintf(tmp,"%.2f",map_center.lat);
//		xyprintf(50,90,tmp);
//		sprintf(tmp,"%.2f",map_center.lon);
//		xyprintf(50,120,tmp);
//		sprintf(tmp,"%d",pData->renewMap);
//		xyprintf(50,140,tmp);
		
//		sprintf(tmp,"%d",pData->fullRoute.size());
//		xyprintf(50,140,tmp);
			
				
//		double plane_x = 480 / 2 - pos_x_move * (500.0 / side);
//		double plane_y = 480 / 2 - pos_y_move * (500.0 / side);
		double plane_x = 480 / 2 - pos_x_move * (500.0 / side) + 12;
		double plane_y = 480 / 2 - pos_y_move * (500.0 / side) + 38 + 15;
		
//		setfillcolor(EGEARGB(0x90, 0x00, 0x00, 0x00));
//		ege_fillellipse(plane_x - 10 , plane_y - 10, 20, 20);
//		setlinewidth(3);
//		setcolor(BLACK);
//		ege_ellipse(plane_x - 10 , plane_y - 10, 20, 20);
		
		
		//--------------------------------------//
//		setfillcolor(EGEARGB(0x90, 0x00, 0x00, 0x00));
//		ege_fillellipse(plane_x - 10 , plane_y - 10, 20, 20);
//		setlinewidth(3);
//		setcolor(BLACK);
//		ege_ellipse(plane_x - 10 , plane_y - 10, 20, 20);
		
		
		setfont(24, 0, "黑体");
		setcolor(WHITE);
		ege_drawtext("位置",606,100);
		ege_drawtext("风速风向",606,262);
		ege_drawtext("天气温度湿度",610,392);
		
		setfillcolor(BLACK);
		ege_fillrect(510,120,200,25);
		ege_fillrect(510,152,200,25);
		ege_fillrect(510,184,200,25);
		
		ege_fillrect(510,282,200,25);
		ege_fillrect(510,314,200,25);
		
		ege_fillrect(510,412,200,25);
		ege_fillrect(510,444,200,25);
		ege_fillrect(510,476,200,25);
		
		setfont(18, 0, "黑体");
		setcolor(EGEARGB(0xff, 177, 177, 178));
		ege_drawtext(mapProvince,570,135);
		ege_drawtext(mapCity,636,135);
		ege_drawtext(mapTownship,606,167);
		ege_drawtext(mapStreet,606,199);
		
		ege_drawtext(mapWindpower,606,296);
		ege_drawtext(mapWinddirection,606,328);
		
		ege_drawtext(mapWeather,606,426);
		ege_drawtext(mapTemperature,606,459);
		ege_drawtext(mapHumidity,606,490);
		
		//更新航线
		fullRoute.clear();
		for(int i = 0; i < pData->routeNum; i ++){
			fullRoute.push_back(pData->fullRoute[i]);
		}
		
		
		//绘制航线
		for(auto it = fullRoute.begin(); it + 1 != fullRoute.end(); it ++){
			
			WAYPOINT wp1 = *(it);
			WAYPOINT wp2 = *(it + 1);
			
			
			double dis = getDistance(pData->latitude, pData->longitude, wp1.lat, wp1.lon);
			double bearing = getBearing(pData->latitude, pData->longitude, wp1.lat, wp1.lon);
			
			
			double rl = dis / ((1.0 * side / map_side) * 67.413076041);
			double rx = (cos(toRadians(bearing - 90)) * rl) + (map_x + map_side / 2);
			double ry = (sin(toRadians(bearing - 90)) * rl) + (map_y + map_side / 2);
			
			
			double dis2 = getDistance(pData->latitude, pData->longitude, wp2.lat, wp2.lon);
			double bearing2 = getBearing(pData->latitude, pData->longitude, wp2.lat, wp2.lon);
			
			double rl2 = dis2 / ((1.0 * side / map_side) * 67.413076041);
			double rx2 = (cos(toRadians(bearing2 - 90)) * rl2) + (map_x + map_side / 2);
			double ry2 = (sin(toRadians(bearing2 - 90)) * rl2) + (map_y + map_side / 2);
			
			setfillcolor(EGEARGB(0x99, 0x8c, 0x8c, 0x8c));
			setlinewidth(3);
			
//			if(rx > map_x + pos_x_move + map_side || ry >= map_y + pos_y_move + map_side || rx2 > map_x + pos_x_move + map_side || ry2 >= map_y + pos_y_move + map_side){
//				continue;
//			}
//			if(rx + pos_x_move > map_side || ry + pos_y_move > map_side || rx2 > map_x + pos_x_move + map_side || ry2 >= map_y + pos_y_move + map_side){
//				continue;
//			}
			ege_line(rx - pos_x_move * (500.0 / side), ry - pos_y_move * (500.0 / side), rx2 - pos_x_move * (500.0 / side), ry2 - pos_y_move * (500.0 / side));
			
		}
		
//		printf("%d    ",fullRoute.size());
			
		if(plane_x > map_x + map_side || plane_y >= map_y + map_side){
			
		}
		else{
			draw_plane(plane_x, plane_y, 30, pData->rotationangle);
		}
			
	}
	
	
	// 清理
	CloseHandle(hMapFile);
	
	
	UnmapViewOfFile(pData);
	delimage(img);
	free(mySharedMemoryA);
	CloseHandle(hEvent);
	closegraph();
	return 0;
}

char* WideCharToString(const WCHAR* wideStr) {
	// 计算多字节字符串所需的缓冲区大小
	int size = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, NULL, 0, NULL, NULL);
	
	// 分配多字节字符串缓冲区
	char* mbStr = (char*)malloc(size * sizeof(char));
	if (mbStr == NULL) {
		// 分配内存失败，返回 NULL
		return NULL;
	}
	
	// 执行转换
	WideCharToMultiByte(CP_ACP, 0, wideStr, -1, mbStr, size, NULL, NULL);
	
	return mbStr;
}



//工具类函数，计算距离角度等

void change_size(PIMAGE& pimg, int width, int height){
	
	//pimg为空，或目标图像大小和原图像一样，则不用缩放，直接返回
	if ((pimg == NULL) || (width == getwidth(pimg) && height == getheight(pimg)))
		return;
	
	PIMAGE tmp = newimage(width, height);
	putimage(tmp, 0, 0, width, height, pimg, 0, 0, getwidth(pimg), getheight(pimg));
	delimage(pimg);
	
	pimg = tmp;
}

double toRadians(double a) {
	return a * (PI / 180);
}

//Vincenty公式计算两点距离
//return the distance of two point, unit is meter
double getDistance(double latitude1, double longitude1, double latitude2, double longitude2) {
	// R is the radius of the earth in meters
	double R = 6371004;  //EARTH_RADIUS
	double deltaLatitude = toRadians(latitude2-latitude1);
	double deltaLongitude = toRadians(longitude2-longitude1);
	latitude1 =toRadians(latitude1);
	latitude2 =toRadians(latitude2);
	double a = pow(sin(deltaLatitude/2), 2)+ cos(latitude1)* cos(latitude2)* pow(sin(deltaLongitude/2), 2);
	double c = 2 * atan2(sqrt(a),sqrt(1-a));
	
	double d = R * c;
	return d;
}

double getBearing(double lat1, double lon1, double lat2, double lon2){
	lat1 = toRadians(lat1);
	lat2 = toRadians(lat2);
	lon1 = toRadians(lon1);
	lon2 = toRadians(lon2);
	double dLon = lon2 - lon1;
	double y = sin(dLon) * cos(lat2);
	double x = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos( dLon);
	double brng = atan2(y, x);
	brng=brng * 180 / PI;
	brng = fmod((brng + 360), 360);
	return brng;
}


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
