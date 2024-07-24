
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>
#include <mutex>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>



//#define _CRT_SECURE_NO_WARNINGS
//#define _CRT_SECURE_NO_WARNINGS 1 

using namespace std;



int windowsWidth = 400;
int windowsHeight = 400;
int changeSize = 0;

short zDelta = 0;
int change = 0;

WNDPROC originalWndProc;

LRESULT CALLBACK NewWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// 你的自定义处理逻辑
	if (uMsg == WM_SIZE)
	{

		//DefWindowProc(hwnd, uMsg, wParam, lParam);

		windowsWidth = LOWORD(lParam);
		windowsHeight = HIWORD(lParam);
		changeSize = 1;

		return 0;
	}

	// 对于其他消息，调用原始窗口过程函数处理
	return CallWindowProc(originalWndProc, hwnd, uMsg, wParam, lParam);
}




typedef struct waypoint {

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
	//放置nd所需要传送的数据

	int HDGMAG;
	double rotationangle;
	double ndpointrotationangle;
	double mapDistance;
	double MINSRef;
	double baroUnit;
	int VOR1;
	int VOR2;
	int CTR;
	double EHISMode;
	int ARPT;
	int POS;
	int WPT;
	int STA;
	int DATA;
	int WXR;
	int TERR;
	double INBDangle;
	double GS;
	double TAS;
	double WS;
	double WD;
	int course3;
	int course2;

	int egeWidth;
	int egeHeight;

	double latitude;
	double longitude;

	WAYPOINT route[1000];

} SharedDataND;





//函数声明
void draw_ND(double ND_x, double ND_y, double ND_side);
char* WideCharToString(const WCHAR* wideStr);

SharedDataND* pDataND;

std::mutex mtx;

//放置nd需要接受的数据
int HDGMAG;
double rotationangle;
double ndpointrotationangle;
double mapDistance;
double MINSRef;
double baroUnit;
int VOR1;
int VOR2;
int CTR;
double EHISMode;
int ARPT;
int POS;
int WPT;
int STA;
int DATA;
int WXR;
int TERR;
double INBDangle;
double GS;
double TAS;
double WS;
double WD;
int course3;
int course2;

int egeWidth;
int egeHeight;

double latitude;
double longitude;


vector<WAYPOINT> waypoints;
vector<WAYPOINT> route;
vector<WAYPOINT> VORs;
vector<WAYPOINT> airports;


int main() {





	//=================读取文件开始=================//


	//读取航路点文件

	string inputTmp;
	ifstream inputFile("earth_fix.dat");

	if (inputFile.is_open()) {
		while (getline(inputFile, inputTmp)) {


			WAYPOINT wpTmp;
			istringstream issTmp(inputTmp);

			string stringTmp[10];

			issTmp >> wpTmp.lat >> wpTmp.lon >> stringTmp[0] >> stringTmp[1] >> stringTmp[2] >> stringTmp[3];

			strcpy(wpTmp.name, stringTmp[0].c_str());
			strcpy(wpTmp.type, stringTmp[1].c_str());
			strcpy(wpTmp.FIRName, stringTmp[2].c_str());
			strcpy(wpTmp.fullType, stringTmp[3].c_str());
			wpTmp.num = 1;
			wpTmp.range = 130;

			waypoints.push_back(wpTmp);

		}
	}

	inputFile.close();



	FILE* file1;
	int linenum = 1;
	char line[1024];

	// 打开文件，以只读模式（"r"）  
	file1 = fopen("arpt.dat", "r");
	if (file1 == NULL) {
		// 如果文件打开失败，打印错误消息  
		perror("Error opening file");
	}

	WAYPOINT wpTmp1;

	// 逐行读取文件内容  
	while (fgets(line, sizeof(line), file1) != NULL) {
		if (linenum % 8 == 2)//读取经度信息
		{
			char str[64];
			if (sscanf(line, "%14c %lf", str, &wpTmp1.lat))
			{

			}
		}
		else if (linenum % 8 == 3)//读取纬度信息
		{
			char str[64];
			if (sscanf(line, "%14c %lf", str, &wpTmp1.lon))
			{

			}
		}
		else if (linenum % 8 == 7)//读取机场名
		{
			char str[64];
			if (sscanf(line, "%14c %s", str, wpTmp1.name))
			{
				airports.push_back(wpTmp1);
			}
		}
		linenum++;
	}
	// 关闭文件  
	fclose(file1);




	//读取VOR塔台文件

	ifstream inputFile4("earth_nav.dat");

	if (inputFile4.is_open()) {
		while (getline(inputFile4, inputTmp)) {

			WAYPOINT wpTmp;
			istringstream issTmp(inputTmp);

			string stringTmp[20];

			if (issTmp >> stringTmp[0] >> wpTmp.lat >> wpTmp.lon >> stringTmp[1] >> stringTmp[2] >> wpTmp.range >> stringTmp[4] >> stringTmp[5] >> stringTmp[6] >> stringTmp[7] >> stringTmp[8] >> stringTmp[9]) {

				strcpy(wpTmp.code, stringTmp[0].c_str());
				strcpy(wpTmp.name, stringTmp[5].c_str());
				strcpy(wpTmp.fullName, stringTmp[5].c_str());

				wpTmp.num = 3;

				VORs.push_back(wpTmp);

			}
			else {
				continue;
			}

		}
	}

	inputFile4.close();


	//==============读取航路文件结束===============//












	WCHAR mySharedMemoryNDW[] = L"Global\\MySharedMemoryND";
	char* mySharedMemoryNDA = WideCharToString(mySharedMemoryNDW);

	// 打开共享内存
	HANDLE hMapFileND = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,    // 可读可写
		FALSE,                  // 不从继承句柄中映射
		mySharedMemoryNDW // 共享内存名称
	);


	if (hMapFileND == NULL) {
		printf("OpenFileMapping failed (%d).\n", GetLastError());
		return -1;
	}

	// 映射共享内存到进程地址空间
	SharedDataND* pDataND0 = (SharedDataND*)MapViewOfFile(
		hMapFileND,               // 共享内存句柄
		FILE_MAP_ALL_ACCESS,    // 可读可写
		0,                      // 高位文件偏移
		0,                      // 低位文件偏移
		sizeof(SharedDataND)          // 要映射的长度
	);

	if (pDataND0 == NULL) {
		printf("MapViewOfFile failed (%d).\n", GetLastError());
		CloseHandle(hMapFileND);
		return -1;
	}

	pDataND = pDataND0;

	egeHeight = pDataND->egeHeight;
	egeWidth = pDataND->egeWidth;

	initgraph(windowsWidth, windowsHeight, INIT_RENDERMANUAL);
	setbkcolor(BLACK);
	setcaption("ND");

	HWND hwnd = getHWnd();

	LONG style = GetWindowLong(hwnd, GWL_STYLE);
	style |= WS_THICKFRAME | WS_MAXIMIZEBOX;
	SetWindowLong(hwnd, GWL_STYLE, style);


	//设置窗口最顶层
	SetWindowPos(getHWnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	originalWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)NewWndProc);


	ege_enable_aa(true);

	for (; is_run(); delay_fps(60))
	{



		if (changeSize == 1) {
			if (windowsHeight >= 200 && windowsWidth >= 200) {
				resizewindow(windowsWidth, windowsHeight);
			}
			changeSize = 0;
		}
		else if (changeSize == 2) {
			HDC hdc = GetDC(NULL); // 获取屏幕的设备上下文，NULL参数表示获取整个屏幕的DC
			int windowsWidthTmp = 0;
			int windowsHeightTmp = 0;
			if (hdc)
			{
				windowsWidthTmp = GetDeviceCaps(hdc, HORZRES); // 获取屏幕水平分辨率
				windowsHeightTmp = GetDeviceCaps(hdc, VERTRES); // 获取屏幕垂直分辨率
				ReleaseDC(NULL, hdc); // 使用完毕后，释放设备上下文
			}
			HWND hwnd = getHWnd();

			resizewindow(windowsWidthTmp, windowsHeightTmp);
			SendMessage(hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		}


		cleardevice();
		std::unique_lock<std::mutex> lock(mtx);
		draw_ND(windowsWidth * 1.0 / 2, windowsHeight * 1.0 / 2, windowsWidth);

		HDGMAG = pDataND->HDGMAG;
		rotationangle = pDataND->rotationangle;
		ndpointrotationangle = pDataND->ndpointrotationangle;
		mapDistance = pDataND->mapDistance;
		MINSRef = pDataND->MINSRef;
		baroUnit = pDataND->baroUnit;
		VOR1 = pDataND->VOR1;
		VOR2 = pDataND->VOR2;
		CTR = pDataND->CTR;
		EHISMode = pDataND->EHISMode;
		ARPT = pDataND->ARPT;
		POS = pDataND->POS;
		WPT = pDataND->WPT;
		STA = pDataND->STA;
		DATA = pDataND->DATA;
		WXR = pDataND->WXR;
		TERR = pDataND->TERR;
		INBDangle = pDataND->INBDangle;
		GS = pDataND->GS;
		TAS = pDataND->TAS;
		WS = pDataND->WS;
		WD = pDataND->WD;
		course3 = pDataND->course3;
		course2 = pDataND->course2;

		latitude = pDataND->latitude;
		longitude = pDataND->longitude;

		lock.unlock();
	}


	// 清理
	CloseHandle(hMapFileND);
	UnmapViewOfFile(pDataND);
	UnmapViewOfFile(pDataND0);
	free(mySharedMemoryNDA);
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

// 目录：
/*
1.函数声明
2.变量声明
3.绘制总表的函数
4.绘制关于ND表表框的部分
5.APP+CENTER  VOR+CENTER 模式函数（第60行左右）
6.APP VOR  MAP  MAP+CENTER 模式函数（第250行左右）
7.PLN PLN+CENTER 模式函数 (第500行左右)
*/


// 函数声明
void draw_smallCircle(double x, double y, double r);
void draw_ND_app_center(double center_x, double center_y, double side);//
void draw_acr(double center_x, double center_y, double side);
void draw_map_scale(double center_x, double center_y, double side);
void draw_ndtext(double center_x, double center_y, double side);
void draw_ndpoint(double center_x, double center_y, double side);
void draw_ndcenterangle(double center_x, double center_y, double side);
void draw_ndtoptriangle(double center_x, double center_y, double side);
void draw_ndtoprectangle(double center_x, double center_y, double side);
void draw_ndcourse(double compass_x, double compass_y, double side);
void draw_ndtoptext(double center_x, double center_y, double side);
void draw_ND_app(double center_x, double center_y, double side);//
void draw_ND_map(double center_x, double center_y, double side);//
void draw_ND_pln(double center_x, double center_y, double side);//
void draw_ND_frame_chassis(double center_x, double center_y, double side);//
void draw_ND_smallWhiteCircle(double center_x, double center_y, double side);
void draw_ND_Speed(double center_x, double center_y, double side);
void draw_ndcourse2(double compass_x, double compass_y, double side);
// 变量声明
//APP+CENTER  VOR+CENTER 模式:
double realrotationAngle = 0;
double pointrationAngle = 0;// 小剑的对应角度
//APP VOR  MAP  MAP+CENTER 模式
double realrotationangle2 = 0;//实际的旋转角度
int ndcourse = 0;
double ndtoprotationangle = 0;//顶部三角形的偏转角度
//PLN PLN+CENTER 模式
//暂无





//====================显示信息函数开始=======================//




//函数头文件
double toRadians(double a);
double getDistance(double latitude1, double longitude1, double latitude2, double longitude2);
void draw_waypoint(WAYPOINT wp1, WAYPOINT wp2, double dir, double ratio, double x, double y, double side);
double getBearing(double lat1, double lon1, double lat2, double lon2);



//测算比例可知，在单位长度5海里时，ND上距离5390m = 5.390km = 2.910367海里(nmi) = 16.553/186*side (即0.08890)
//则在单位长度5海里时，1km显示在ND上为0.016511*side；单位长度1海里时，1km显示为0.082555*side
//==============================以上作废===========================//


//测算比例可知，在单位长度5海里时，ND上距离2560m = 2.56km = 1.3822894海里(nmi) = 16.553/186*side (即0.08890)
//则在单位长度5海里时，1km显示在ND上为0.0347635*side；单位长度1海里时，1km显示为0.1738176*side



//绘制航路点（三角形）

extern vector<WAYPOINT> waypoints;

void draw_waypoint(WAYPOINT nowPos, double dir, double ratio, double x, double y, double side) {

	for (auto wp : waypoints) {

		if (fabs(wp.lat - nowPos.lat) > 0.8 || fabs(wp.lon - nowPos.lon) > 0.8) {
			continue;
		}


		double dis = getDistance(nowPos.lat, nowPos.lon, wp.lat, wp.lon);
		double bearing = getBearing(nowPos.lat, nowPos.lon, wp.lat, wp.lon);

		double rside = 0.010752 * side;
		double rhigh = 0.015129 * side;
		double rl = dis / 1000 * 0.1738176 * side / ratio;
		double rx = (cos(toRadians(bearing - dir - 90)) * rl) + x;
		double ry = (sin(toRadians(bearing - dir - 90)) * rl) + y;

		//当航路点在圆内时再绘制
		if (pow(rl, 2) <= pow(side / 104 * 40, 2)) {

			ege_point pointTmp[4] = {
				{rx,ry - rhigh / 3},
				{rx - rside / 2,ry + rhigh / 2},
				{rx + rside / 2,ry + rhigh / 2},
				{rx,ry - rhigh / 3},
			};

			setlinewidth(0.002 * side);
			//		setcolor(WHITE);
			setcolor(EGEARGB(0xff, 0x3e, 0x70, 0x9c));
			ege_drawpoly(4, pointTmp);

			if (0.01 * side > 5) {
				setfont(0.01 * side, 0.01 * side, "黑体");
				outtextxy(rx, ry + rhigh / 2 + 0.007 * side, wp.name);
			}

		}

	}


}


//绘制机场（圆形）

extern vector<WAYPOINT> airports;
void draw_airports(WAYPOINT nowPos, double dir, double ratio, double x, double y, double side) {



	for (auto wp : airports) {

		if (fabs(wp.lat - nowPos.lat) > 3 || fabs(wp.lon - nowPos.lon) > 3) {
			continue;
		}


		double dis = getDistance(nowPos.lat, nowPos.lon, wp.lat, wp.lon);
		double bearing = getBearing(nowPos.lat, nowPos.lon, wp.lat, wp.lon);

		double rside = 0.010752 * side;
		double rhigh = 0.015129 * side;
		double rl = dis / 1000 * 0.1738176 * side / ratio;
		double rx = (cos(toRadians(bearing - dir - 90)) * rl) + x;
		double ry = (sin(toRadians(bearing - dir - 90)) * rl) + y;

		//当航路点在圆内时再绘制
		if (pow(rl, 2) <= pow(side / 104 * 40, 2)) {

			setlinewidth(0.001 * side);
			setcolor(WHITE);
			ege_ellipse(rx - rhigh / 2, ry - rhigh / 2, rhigh, rhigh);

			if (0.01 * side > 5) {
				setcolor(WHITE);
				setfont(0.01 * side, 0.01 * side, "黑体");

				outtextxy(rx, ry, wp.name);
			}

		}

	}
}


//绘制VOR台（六边形）

extern vector<WAYPOINT> VORs;
void draw_VORs(WAYPOINT nowPos, double dir, double ratio, double x, double y, double side) {



	for (auto wp : VORs) {

		if (fabs(wp.lat - nowPos.lat) > 3 || fabs(wp.lon - nowPos.lon) > 3) {
			continue;
		}


		double dis = getDistance(nowPos.lat, nowPos.lon, wp.lat, wp.lon);
		double bearing = getBearing(nowPos.lat, nowPos.lon, wp.lat, wp.lon);

		double rside = 0.010752 * side;
		double rhigh = 0.015129 * side;
		double rl = dis / 1000 * 0.1738176 * side / ratio;
		double rx = (cos(toRadians(bearing - dir - 90)) * rl) + x;
		double ry = (sin(toRadians(bearing - dir - 90)) * rl) + y;

		//当点在圆内时再绘制
		if (pow(rl, 2) <= pow(side / 104 * 40, 2)) {

			ege_point pointTmp[6] = {
				{rx + rside / 1.3,ry},
				{rx + rside / 2.6,ry + rside / 2.6 * 1.732},
				{rx - rside / 2.6,ry + rside / 2.6 * 1.732},
				{rx - rside / 1.3,ry},
				{rx - rside / 2.6,ry - rside / 2.6 * 1.732},
				{rx + rside / 2.6,ry - rside / 2.6 * 1.732},
			};

			setfillcolor(EGEARGB(0x80, 0xff, 0xff, 0xff));
			ege_fillpoly(6, pointTmp);

			if (0.01 * side > 5) {
				setcolor(WHITE);
				setfont(0.01 * side, 0.01 * side, "黑体");

				outtextxy(rx, ry, wp.name);
			}


		}

	}
}


vector<WAYPOINT> routePassed;
int nowPos = 0;

void draw_route(WAYPOINT wp, double dir, double ratio, double x, double y, double side) {

	routePassed.clear();
	routePassed.push_back(pDataND->route[0]);

	route.clear();

	for (int i = 0; i < 1000; i++) {
		route.push_back(pDataND->route[i]);
	}

	if (route.size() >= 1) {

		for (auto it = route.begin(); it + 1 != route.end(); it++) {

			WAYPOINT wp1 = *(it);
			WAYPOINT wp2 = *(it + 1);

			double dis = getDistance(wp.lat, wp.lon, wp1.lat, wp1.lon);
			double bearing = getBearing(wp.lat, wp.lon, wp1.lat, wp1.lon);

			//		double rside = 0.010752 * side;
			//		double rhigh = 0.015129 * side;
			double rl = dis / 1000 * 0.1738176 * side / ratio;
			double rx = (cos(toRadians(bearing - dir - 90)) * rl) + x;
			double ry = (sin(toRadians(bearing - dir - 90)) * rl) + y;


			double dis2 = getDistance(wp.lat, wp.lon, wp2.lat, wp2.lon);
			double bearing2 = getBearing(wp.lat, wp.lon, wp2.lat, wp2.lon);

			double rl2 = dis2 / 1000 * 0.1738176 * side / ratio;
			double rx2 = (cos(toRadians(bearing2 - dir - 90)) * rl2) + x;
			double ry2 = (sin(toRadians(bearing2 - dir - 90)) * rl2) + y;

			//圆的直径
			double d = side / 104 * 40 * 2;

			setlinewidth(0.003 * side);

			//先判断这段路线是不是接下来的一段，从而设置不同颜色
			//警告：这里一旦尝试读取没有内容的vector的迭代器会导致程序直接闪退
//			if(routePassed.size() > 0 && !strcmp((*(routePassed.end() - 1)).name, wp1.name)){
			if (nowPos > 0 && !strcmp(routePassed[nowPos - 1].name, wp1.name)) {

				setcolor(EGEARGB(0xff, 0xa8, 0x05, 0xa8));

			}
			else {

				//			setcolor(WHITE);
				setcolor(EGEARGB(0xFF, 0xff, 0xff, 0xff));
			}

			//先判断两点是不是都在范围内，如果都在，直接链接即可
			if (rx > x - d / 2 && rx < x + d / 2 && ry > y - d / 2 && ry < y + d / 2 && rx2 > x - d / 2 && rx2 < x + d / 2 && ry2 > y - d / 2 && ry2 < y + d / 2) {
				//都在，不用处理
				ege_line(rx, ry, rx2, ry2);
			}
			//若有一点不在，要计算连线与边缘的交点，连在内的点和交点
			//第二个点不在时
			else if ((rx > x - d / 2 && rx < x + d / 2 && ry > y - d / 2 && ry < y + d / 2) && (rx2 < x - d / 2 || rx2 > x + d / 2 || ry2 < y - d / 2 || ry2 > y + d / 2)) {
				//现坐标系是以x，y为中心；x正方向向右，y正方向向下
				//两点的直线方程以矩阵表示，矩阵a的第一行是这个直线，第二行是边缘的方程，现在默认第二行都是0
				double a[2][3] = { {-(ry2 - ry) / (rx2 - rx) , 1, -(ry2 - ry) / (rx2 - rx) * rx + ry} , {} };

				//b的每一行是边缘方程的矩阵表示
				double b[4][3] = { {0, 1 , (y + d / 2)}, {1, 0 , (x + d / 2)}, {0, 1, (y - d / 2)}, {1, 0, (x - d / 2)} };

				for (int i = 0; i < 4; i++) {

					for (int k = 0; k < 3; k++) {
						a[1][k] = b[i][k];
					}

					double xTmp = ((a[1][1] * a[0][2]) - (a[0][1] * a[1][2])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));
					double yTmp = ((a[0][0] * a[1][2]) - (a[0][2] * a[1][0])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));

					//要取的是在边缘范围内的交点，同时还要保证交点是在第一个点到第二个点中间！！！(保证在中间通过)
					if (xTmp >= x - 1.0001 * d / 2 && xTmp <= x + 1.0001 * d / 2 && yTmp >= y - 1.0001 * d / 2 && yTmp <= y + 1.0001 * d / 2
						&& xTmp <= max(rx, rx2) && xTmp >= min(rx, rx2) && yTmp <= max(ry, ry2) && yTmp >= min(ry, ry2)) {
						rx2 = xTmp;
						ry2 = yTmp;

						ege_line(rx, ry, rx2, ry2);

						break;
					}


				}

			}
			//第一个点不在时
			else if ((rx < x - d / 2 || rx > x + d / 2 || ry < y - d / 2 || ry > y + d / 2) && (rx2 > x - d / 2 && rx2 < x + d / 2 && ry2 > y - d / 2 && ry2 < y + d / 2)) {

				double a[2][3] = { {-(ry2 - ry) / (rx2 - rx) , 1, -(ry2 - ry) / (rx2 - rx) * rx + ry} , {} };

				//b的每一行是边缘方程的矩阵表示
				double b[4][3] = { {0, 1 , (y + d / 2)}, {1, 0 , (x + d / 2)}, {0, 1, (y - d / 2)}, {1, 0, (x - d / 2)} };

				for (int i = 0; i < 4; i++) {

					for (int k = 0; k < 3; k++) {
						a[1][k] = b[i][k];
					}

					double xTmp = ((a[1][1] * a[0][2]) - (a[0][1] * a[1][2])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));
					double yTmp = ((a[0][0] * a[1][2]) - (a[0][2] * a[1][0])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));

					//要取的是在边缘范围内的交点，同时还要保证交点是在第一个点到第二个点中间！！！(保证在中间通过)
					if (xTmp >= x - 1.0001 * d / 2 && xTmp <= x + 1.0001 * d / 2 && yTmp >= y - 1.0001 * d / 2 && yTmp <= y + 1.0001 * d / 2
						&& xTmp <= max(rx, rx2) && xTmp >= min(rx, rx2) && yTmp <= max(ry, ry2) && yTmp >= min(ry, ry2)) {
						rx = xTmp;
						ry = yTmp;

						ege_line(rx, ry, rx2, ry2);
						break;
					}


				}

			}
			//两个点都不在时
//			else if(( rx < x - d / 2 || rx > x + d / 2 || ry < y - d / 2 || ry > y + d / 2 ) && (rx2 < x - d / 2 || rx2 > x + d / 2 || ry2 < y - d / 2 || ry2 > y + d / 2 )){
			else {
				double a[2][3] = { {-(ry2 - ry) / (rx2 - rx) , 1, -(ry2 - ry) / (rx2 - rx) * rx + ry} , {} };

				//b的每一行是边缘方程的矩阵表示
				double b[4][3] = { {0, 1 , (y + d / 2)}, {1, 0 , (x + d / 2)}, {0, 1, (y - d / 2)}, {1, 0, (x - d / 2)} };

				int xTmps[5];
				int yTmps[5];
				int cot = 0;

				for (int i = 0; i < 4; i++) {

					for (int k = 0; k < 3; k++) {
						a[1][k] = b[i][k];
					}

					double xTmp = ((a[1][1] * a[0][2]) - (a[0][1] * a[1][2])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));
					double yTmp = ((a[0][0] * a[1][2]) - (a[0][2] * a[1][0])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));

					//两点都不在边缘内侧，直线与边缘要么没有交点，要么有两个；  此时不用判断交点在不在两个点中间
					if (xTmp >= x - 1.0001 * d / 2 && xTmp <= x + 1.0001 * d / 2 && yTmp >= y - 1.0001 * d / 2 && yTmp <= y + 1.0001 * d / 2) {
						rx = xTmp;
						ry = yTmp;
						cot++;

						xTmps[cot] = xTmp;
						yTmps[cot] = yTmp;

						break;
					}

				}

				//判断有几个交点,两个时则绘制
				if (cot == 2) {

					ege_line(xTmps[0], yTmps[0], xTmps[1], yTmps[1]);
				}


			}



		}


		int cot = 0;

		//上述代码执行了绘制线路
		//以下代码执行绘制各个航点
		for (auto wpTmp : route) {

			double dis = getDistance(wp.lat, wp.lon, wpTmp.lat, wpTmp.lon);
			double bearing = getBearing(wp.lat, wp.lon, wpTmp.lat, wpTmp.lon);

			double rside = 0.010752 * side;
			double rhigh = 0.015129 * side;
			double rl = dis / 1000 * 0.1738176 * side / ratio;
			double rx = (cos(toRadians(bearing - dir - 90)) * rl) + x;
			double ry = (sin(toRadians(bearing - dir - 90)) * rl) + y;

			//当航路点在圆内时再绘制
			if (pow(rl, 2) <= pow(side / 104 * 40, 2)) {

				//			if(wpTmp.num == 1){

				ege_point pointTmp[4] = {
					{rx,ry - rhigh / 3},
					{rx - rside / 2,ry + rhigh / 2},
					{rx + rside / 2,ry + rhigh / 2},
					{rx,ry - rhigh / 3},
				};

				//				if(cot > 0 && routePassed.size() > 0 && !strcmp((*(routePassed.end() - 1)).name, (*(route.begin() + cot - 1)).name)){
				if (!strcmp(route[nowPos].name, wpTmp.name)) {
					setfillcolor(EGEARGB(0xbb, 0xa8, 0x05, 0xa8));
					setcolor(RED);
				}
				else {
					setfillcolor(WHITE);
					setcolor(WHITE);
				}

				ege_fillpoly(4, pointTmp);

				if (0.01 * side > 5) {

					setfont(0.01 * side, 0.01 * side, "黑体");

					outtextxy(rx, ry, wpTmp.name);
				}

				//			}
				//			else if(wpTmp.num == 2){
				//				
				//				ege_point pointTmp[6] = {
				//					{rx + rside / 1.3,ry},
				//					{rx + rside / 2.6,ry + rside / 2.6 * 1.732},
				//					{rx - rside / 2.6,ry + rside / 2.6 * 1.732},
				//					{rx - rside / 1.3,ry},
				//					{rx - rside / 2.6,ry - rside / 2.6 * 1.732},
				//					{rx + rside / 2.6,ry - rside / 2.6 * 1.732},
				//				};
				//				
				//				setfillcolor(WHITE);
				//				ege_fillpoly(6, pointTmp);
				//				
				//				if(0.01 * side > 5){
				//					setcolor(WHITE);
				//					setfont(0.01 * side, 0.01 * side , "黑体");
				//					
				//					outtextxy(rx,ry,wpTmp.name);
				//				}
				//				
				//			}
				//			else if(wpTmp.num == 3){
				//				
				//				setfillcolor(WHITE);
				//				ege_ellipse(rx - rhigh / 2, ry - rhigh / 2, rhigh, rhigh);
				//				
				//				if(0.01 * side > 5){
				//					setcolor(WHITE);
				//					setfont(0.01 * side, 0.01 * side , "黑体");
				//					
				//					outtextxy(rx,ry,wpTmp.name);
				//				}
				//				
				//			}

				cot++;

			}

		}


	}



}



//这个x，y是同上
//传进来的是三角形中心,也是图上飞机位置！
void draw_waypoint_map(WAYPOINT nowPos, double dir, double ratio, double x, double y, double side) {

	routePassed.clear();
	routePassed.push_back(pDataND->route[0]);

	route.clear();

	for (int i = 0; i < 1000; i++) {
		route.push_back(pDataND->route[i]);
	}

	for (auto wp : waypoints) {

		if (fabs(wp.lat - nowPos.lat) > 3 || fabs(wp.lon - nowPos.lon) > 3) {
			continue;
		}

		double dis = getDistance(nowPos.lat, nowPos.lon, wp.lat, wp.lon);
		double bearing = getBearing(nowPos.lat, nowPos.lon, wp.lat, wp.lon);

		double rside = 0.010752 * side;
		double rhigh = 0.015129 * side;
		double rl = dis / 1000 * 0.1738176 * side / ratio;
		double rx = (cos(toRadians(bearing - dir - 90)) * rl) + x;
		double ry = (sin(toRadians(bearing - dir - 90)) * rl) + y;

		//当航路点在范围内内时再绘制
		if (pow(rx - x, 2) + pow(ry - y, 2) <= pow(side / 104 * 71, 2)
			&& ry <= y + side * 16 / 104 / 3 && rx <= x + side * 48 / 104 && rx >= x - side * 48 / 104) {

			ege_point pointTmp[4] = {
				{rx,ry - rhigh / 3},
				{rx - rside / 2,ry + rhigh / 2},
				{rx + rside / 2,ry + rhigh / 2},
				{rx,ry - rhigh / 3},
			};

			setlinewidth(0.002 * side);
			//		setcolor(WHITE);
			setcolor(EGEARGB(0xff, 0x3e, 0x70, 0x9c));
			ege_drawpoly(4, pointTmp);

			if (0.01 * side > 5) {
				setfont(0.01 * side, 0.01 * side, "黑体");
				outtextxy(rx, ry + rhigh / 2 + 0.007 * side, wp.name);
			}

		}

	}


}


//传进来的是三角形中心,也是图上飞机位置！
void draw_route_map(WAYPOINT wp, double dir, double ratio, double x, double y, double side) {


	if (route.size() >= 1) {


		for (auto it = route.begin(); it + 1 != route.end(); it++) {

			WAYPOINT wp1 = *(it);
			WAYPOINT wp2 = *(it + 1);

			double dis = getDistance(wp.lat, wp.lon, wp1.lat, wp1.lon);
			double bearing = getBearing(wp.lat, wp.lon, wp1.lat, wp1.lon);


			double rl = dis / 1000 * 0.1738176 * side / ratio;
			double rx = (cos(toRadians(bearing - dir - 90)) * rl) + x;
			double ry = (sin(toRadians(bearing - dir - 90)) * rl) + y;


			double dis2 = getDistance(wp.lat, wp.lon, wp2.lat, wp2.lon);
			double bearing2 = getBearing(wp.lat, wp.lon, wp2.lat, wp2.lon);

			double rl2 = dis2 / 1000 * 0.1738176 * side / ratio;
			double rx2 = (cos(toRadians(bearing2 - dir - 90)) * rl2) + x;
			double ry2 = (sin(toRadians(bearing2 - dir - 90)) * rl2) + y;

			setlinewidth(0.003 * side);

			//先判断这段路线是不是接下来的一段，从而设置不同颜色
			//警告：这里一旦尝试读取没有内容的vector的迭代器会导致程序直接闪退
			if (routePassed.size() > 0 && !strcmp((*(routePassed.end() - 1)).name, wp1.name)) {

				setcolor(EGEARGB(0xff, 0xa8, 0x05, 0xa8));

			}
			else {

				//			setcolor(WHITE);
				setcolor(EGEARGB(0xFF, 0xff, 0xff, 0xff));
			}


			//先判断两点是不是都在范围内，如果都在，直接链接即可
			//这个时候判断rx和ry在不在范围是判断的两者在不在矩形区域中！
//		if(pow(rx - x, 2) + pow(ry - (y - side * 2 / 3 * 8 / 104), 2) <= pow(side / 104 * 71, 2) && ry <= y + side * 8 / 104 / 3 && rx <= x + side * 48 / 104 && rx >= x - side * 48 / 104 
//			&& pow(rx2 - x, 2) + pow(ry2 - (y - side * 2 / 3 * 8 / 104), 2) <= pow(side / 104 * 71, 2) && ry2 <= y + side * 8 / 104 / 3 && rx2 <= x + side * 48 / 104 && rx2 >= x - side * 48 / 104)
			if (ry >= y - side * (71.0 / 104) && ry <= y + side * 16 / 104 / 3 && rx <= x + side * 48 / 104 && rx >= x - side * 48 / 104
				&& ry2 >= y - side * (71.0 / 104) && ry2 <= y + side * 16 / 104 / 3 && rx2 <= x + side * 48 / 104 && rx2 >= x - side * 48 / 104) {
				//都在，不用处理
				ege_line(rx, ry, rx2, ry2);

			}
			//若有一点不在，要计算连线与边缘的交点，连在内的点和交点
			//第二个点不在时
			//这里一定要是71.0!!!!!!!!!!!!!!!!!!!
			else if (ry >= y - side * (71.0 / 104) && ry <= y + side * 16 / 104 / 3 && rx <= x + side * 48 / 104 && rx >= x - side * 48 / 104
				&& (ry2 < y - side * (71.0 / 104) || ry2 > y + side * 16 / 104 / 3 || rx2 > x + side * 48 / 104 || rx2 < x - side * 48 / 104)) {
				//现坐标系是以x，y为中心；x正方向向右，y正方向向下
				//两点的直线方程以矩阵表示，矩阵a的第一行是这个直线，第二行是边缘的方程，现在默认第二行都是0
				double a[2][3] = { {-(ry2 - ry) / (rx2 - rx) , 1, -(ry2 - ry) / (rx2 - rx) * rx + ry} , {} };

				//b的每一行是边缘方程的矩阵表示
				double b[4][3] = { {0, 1 , (y + side * 16 / 104 / 3)}, {1, 0 , (x + side * 48 / 104)}, {0, 1, (y - side * (71.0 / 104))}, {1, 0, (x - side * 48 / 104)} };

				for (int i = 0; i < 4; i++) {

					for (int k = 0; k < 3; k++) {
						a[1][k] = b[i][k];
					}

					double xTmp = ((a[1][1] * a[0][2]) - (a[0][1] * a[1][2])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));
					double yTmp = ((a[0][0] * a[1][2]) - (a[0][2] * a[1][0])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));

					//要取的是在边缘范围内的交点，同时还要保证交点是在第一个点到第二个点中间！！！(保证在中间通过)
					if (yTmp >= y - 1.0001 * side * (71.0 / 104) && yTmp <= y + 1.0001 * side * 16 / 104 / 3 && xTmp <= x + 1.0001 * side * 48 / 104 && xTmp >= x - 1.0001 * side * 48 / 104
						&& xTmp <= max(rx, rx2) && xTmp >= min(rx, rx2) && yTmp <= max(ry, ry2) && yTmp >= min(ry, ry2)) {
						rx2 = xTmp;
						ry2 = yTmp;

						ege_line(rx, ry, rx2, ry2);

						break;
					}


				}

			}
			//第一个点不在时
			else if ((ry < y - side * (71.0 / 104) || ry > y + side * 16 / 104 / 3 || rx > x + side * 48 / 104 || rx < x - side * 48 / 104)
				&& ry2 >= y - side * (71.0 / 104) && ry2 <= y + side * 16 / 104 / 3 && rx2 <= x + side * 48 / 104 && rx2 >= x - side * 48 / 104) {

				double a[2][3] = { {-(ry2 - ry) / (rx2 - rx) , 1, -(ry2 - ry) / (rx2 - rx) * rx + ry} , {} };

				//b的每一行是边缘方程的矩阵表示
				double b[4][3] = { {0, 1 , (y + side * 16 / 104 / 3)}, {1, 0 , (x + side * 48 / 104)}, {0, 1, (y - side * (71.0 / 104))}, {1, 0, (x - side * 48 / 104)} };

				for (int i = 0; i < 4; i++) {

					for (int k = 0; k < 3; k++) {
						a[1][k] = b[i][k];
					}

					double xTmp = ((a[1][1] * a[0][2]) - (a[0][1] * a[1][2])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));
					double yTmp = ((a[0][0] * a[1][2]) - (a[0][2] * a[1][0])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));

					//要取的是在边缘范围内的交点，同时还要保证交点是在第一个点到第二个点中间！！！(保证在中间通过)
					if (yTmp >= y - 1.0001 * side * (71.0 / 104) && yTmp <= y + 1.0001 * side * 16 / 104 / 3 && xTmp <= x + 1.0001 * side * 48 / 104 && xTmp >= x - 1.0001 * side * 48 / 104
						&& xTmp <= max(rx, rx2) && xTmp >= min(rx, rx2) && yTmp <= max(ry, ry2) && yTmp >= min(ry, ry2)) {
						rx = xTmp;
						ry = yTmp;

						ege_line(rx, ry, rx2, ry2);
						break;
					}


				}

			}
			//两个点都不在时
//			else if((ry < y - side * (71.0 / 104) || ry > y + side * 16 / 104 / 3 || rx > x + side * 48 / 104 || rx < x - side * 48 / 104)
//				&& (ry2 < y - side * (71.0 / 104) || ry2 > y + side * 16 / 104 / 3 || rx2 > x + side * 48 / 104 || rx2 < x - side * 48 / 104)){
			else {
				double a[2][3] = { {-(ry2 - ry) / (rx2 - rx) , 1, -(ry2 - ry) / (rx2 - rx) * rx + ry} , {} };

				//b的每一行是边缘方程的矩阵表示
				double b[4][3] = { {0, 1 , (y + side * 16 / 104 / 3)}, {1, 0 , (x + side * 48 / 104)}, {0, 1, (y - side * (71.0 / 104))}, {1, 0, (x - side * 48 / 104)} };

				int xTmps[5];
				int yTmps[5];
				int cot = 0;

				for (int i = 0; i < 4; i++) {

					for (int k = 0; k < 3; k++) {
						a[1][k] = b[i][k];
					}

					double xTmp = ((a[1][1] * a[0][2]) - (a[0][1] * a[1][2])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));
					double yTmp = ((a[0][0] * a[1][2]) - (a[0][2] * a[1][0])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));

					//两点都不在边缘内侧，直线与边缘要么没有交点，要么有两个；  此时不用判断交点在不在两个点中间
					if (yTmp >= y - 1.0001 * side * (71.0 / 104) && yTmp <= y + 1.0001 * side * 16 / 104 / 3 && xTmp <= x + 1.0001 * side * 48 / 104 && xTmp >= x - 1.0001 * side * 48 / 104) {
						rx = xTmp;
						ry = yTmp;
						cot++;

						xTmps[cot] = xTmp;
						yTmps[cot] = yTmp;

						break;
					}

				}

				//判断有几个交点,两个时则绘制
				if (cot == 2) {

					ege_line(xTmps[0], yTmps[0], xTmps[1], yTmps[1]);
				}


			}



		}



		int cot = 0;

		//上述代码执行了绘制线路
		//以下代码执行绘制各个航点
		for (auto wpTmp : route) {

			double dis = getDistance(wp.lat, wp.lon, wpTmp.lat, wpTmp.lon);
			double bearing = getBearing(wp.lat, wp.lon, wpTmp.lat, wpTmp.lon);

			double rside = 0.010752 * side;
			double rhigh = 0.015129 * side;
			double rl = dis / 1000 * 0.1738176 * side / ratio;
			double rx = (cos(toRadians(bearing - dir - 90)) * rl) + x;
			double ry = (sin(toRadians(bearing - dir - 90)) * rl) + y;

			//当航路点在范围内时再绘制
			if (ry >= y - side * (71.0 / 104) && ry <= y + side * 16 / 104 / 3 && rx <= x + side * 48 / 104 && rx >= x - side * 48 / 104) {

				ege_point pointTmp[4] = {
					{rx,ry - rhigh / 3},
					{rx - rside / 2,ry + rhigh / 2},
					{rx + rside / 2,ry + rhigh / 2},
					{rx,ry - rhigh / 3},
				};

				if (cot > 0 && routePassed.size() > 0 && !strcmp((*(routePassed.end() - 1)).name, (*(route.begin() + cot - 1)).name)) {
					setfillcolor(EGEARGB(0xbb, 0xa8, 0x05, 0xa8));
					setcolor(RED);
				}
				else {
					setfillcolor(WHITE);
					setcolor(WHITE);
				}

				ege_fillpoly(4, pointTmp);

				if (0.01 * side > 5) {

					setfont(0.01 * side, 0.01 * side, "黑体");

					outtextxy(rx, ry, wpTmp.name);
				}


				cot++;

			}

		}




	}


}





double toRadians(double a) {
	return a * (PI / 180);
}

//Vincenty公式计算两点距离
//return the distance of two point, unit is meter
double getDistance(double latitude1, double longitude1, double latitude2, double longitude2) {
	// R is the radius of the earth in meters
	double R = 6371004;  //EARTH_RADIUS
	double deltaLatitude = toRadians(latitude2 - latitude1);
	double deltaLongitude = toRadians(longitude2 - longitude1);
	latitude1 = toRadians(latitude1);
	latitude2 = toRadians(latitude2);
	double a = pow(sin(deltaLatitude / 2), 2) + cos(latitude1) * cos(latitude2) * pow(sin(deltaLongitude / 2), 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));

	double d = R * c;
	return d;
}

double getBearing(double lat1, double lon1, double lat2, double lon2) {
	lat1 = toRadians(lat1);
	lat2 = toRadians(lat2);
	lon1 = toRadians(lon1);
	lon2 = toRadians(lon2);
	double dLon = lon2 - lon1;
	double y = sin(dLon) * cos(lat2);
	double x = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(dLon);
	double brng = atan2(y, x);
	brng = brng * 180 / PI;
	brng = fmod((brng + 360), 360);
	return brng;
}


















//==================================以下为绘制总表部分========================================//
void draw_ND(double ND_x, double ND_y, double ND_side) {




	int ratio = 5;
	if (ratio != 0) {
		ratio = 5 * pow(2, mapDistance / 30) / 2;
	}



	draw_ND_frame_chassis(ND_x, ND_y, ND_side);



	setbkmode(TRANSPARENT);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setfont(ND_side / 35, 0, "黑体");
	setcolor(EGEARGB(180, 100, 149, 237));

	if (MINSRef == 55) {

	}
	if (MINSRef == 125) {

	}

	if (baroUnit == 55) {

	}
	if (baroUnit == 125) {

	}

	if (VOR1 == 1) {

	}
	if (VOR2 == 1) {

	}

	if (CTR == 0) {

		if (EHISMode == 55 || EHISMode == 80) {

			draw_ND_app(ND_x, ND_y + ND_side * 32 / 104, ND_side);
		}
		else if (EHISMode == 110) {

			draw_ND_map(ND_x, ND_y + ND_side * 32 / 104, ND_side);

		}
		else if (EHISMode == 135) {

			draw_ND_pln(ND_x, ND_y, ND_side);

		}




		if (ARPT == 1) {
			setbkmode(TRANSPARENT);
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			setfont(ND_side / 35, 0, "黑体");
			setcolor(EGEARGB(180, 100, 149, 237));
			outtextxy(ND_x - ND_side / 2.21, ND_y + ND_side / 6, "ARPT");

			//			if()
			if (EHISMode == 135) {
				WAYPOINT nowPos = { 0,"", latitude, longitude, "", "", "", 100, "", "" };
				draw_airports(nowPos, 0, ratio, ND_x, ND_y, ND_side);
			}

		}
		if (WPT == 1) {
			setbkmode(TRANSPARENT);
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			setfont(ND_side / 35, 0, "黑体");
			setcolor(EGEARGB(180, 100, 149, 237));
			outtextxy(ND_x - ND_side / 2.18, ND_y + ND_side / 5.1, "WPT");

			if (EHISMode == 55 || EHISMode == 80 || EHISMode == 110) {
				WAYPOINT nowPos = { 0,"", latitude, longitude, "", "", "", 100, "", "" };
				draw_waypoint_map(nowPos, rotationangle, ratio, ND_x, ND_y + ND_side * 32 / 104, ND_side);
				draw_route_map(nowPos, rotationangle, ratio, ND_x, ND_y + ND_side * 32 / 104, ND_side);
			}
			else if (EHISMode == 135) {
				WAYPOINT nowPos = { 0,"", latitude, longitude, "", "", "", 100, "", "" };
				draw_waypoint(nowPos, 0, ratio, ND_x, ND_y, ND_side);
				draw_route(nowPos, 0, ratio, ND_x, ND_y, ND_side);
			}
		}
		if (STA == 1) {
			setbkmode(TRANSPARENT);
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			setfont(ND_side / 35, 0, "黑体");
			setcolor(EGEARGB(180, 100, 149, 237));
			outtextxy(ND_x - ND_side / 2.18, ND_y + ND_side / 4.5, "STA");


			if (EHISMode == 135) {
				WAYPOINT nowPos = { 0,"", latitude, longitude, "", "", "", 100, "", "" };
				draw_VORs(nowPos, 0, ratio, ND_x, ND_y, ND_side);
			}


		}
		if (WXR == 1) {
			setbkmode(TRANSPARENT);
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			setfont(ND_side / 35, 0, "黑体");
			setcolor(EGEARGB(180, 100, 149, 237));
			outtextxy(ND_x - ND_side / 2.2, ND_y + ND_side / 4, "WXR");
		}

		if (DATA == 1) {

		}
		if (POS == 1) {

		}
		if (TERR == 1) {

		}




	}
	else if (CTR == 1) {

		if (EHISMode == 55 || EHISMode == 80) {

			draw_ND_app_center(ND_x, ND_y, ND_side);

		}
		else if (EHISMode == 110) {

			draw_ND_map(ND_x, ND_y + ND_side * 32 / 104, ND_side);

		}
		else if (EHISMode == 135) {

			draw_ND_pln(ND_x, ND_y, ND_side);

		}



		if (ARPT == 1) {
			if (EHISMode == 135) {
				WAYPOINT nowPos = { 0,"", latitude, longitude, "", "", "", 100, "", "" };
				draw_airports(nowPos, 0, ratio, ND_x, ND_y, ND_side);
			}

		}
		if (WPT == 1) {

			if (EHISMode == 110) {
				WAYPOINT nowPos = { 0,"", latitude, longitude, "", "", "", 100, "", "" };
				draw_waypoint_map(nowPos, rotationangle, ratio, ND_x, ND_y + ND_side * 32 / 104, ND_side);
				draw_route_map(nowPos, rotationangle, ratio, ND_x, ND_y + ND_side * 32 / 104, ND_side);
			}
			else if (EHISMode == 135) {
				WAYPOINT nowPos = { 0,"", latitude, longitude, "", "", "", 100, "", "" };
				draw_waypoint(nowPos, 0, ratio, ND_x, ND_y, ND_side);
				draw_route(nowPos, 0, ratio, ND_x, ND_y, ND_side);
			}

		}
		if (STA == 1) {

			if (EHISMode == 135) {
				WAYPOINT nowPos = { 0,"", latitude, longitude, "", "", "", 100, "", "" };
				draw_VORs(nowPos, 0, ratio, ND_x, ND_y, ND_side);
			}

		}
		if (WXR == 1) {

		}

		if (DATA == 1) {

		}
		if (POS == 1) {

		}
		if (TERR == 1) {

		}

	}


	draw_ND_Speed(ND_x, ND_y, ND_side);

	//灯光遮盖效果
	setfillcolor(EGEARGB(255 - (int)INBDangle, 0x00, 0x00, 0x00));
	ege_fillrect(ND_x - ND_side / 2 / 0.95, ND_y - ND_side / 1.95, ND_side * 1.05, ND_side * 1.05);

	//draw_PFD_frame(ND_x, ND_y, ND_side);

	//draw_ND_smallWhiteCircle(ND_x - ND_side / 2.4, ND_y +  ND_side / 1.72, ND_side / 22);

	///draw_screw3(ND_x + ND_side / 2, ND_y +  ND_side / 1.668,ND_side / 22, 45);

}

//==========================================================================================//
/*
关于2*4=8种模式下的说明
对应旋钮的从左至右有：
APP APP+CENTER
VOR VOR+CENTER
MAP MAP+CENTER
PLN PLN+CENTER

其中:
APP+CENTER  VOR+CENTER 是一种模式
APP VOR  MAP  MAP+CENTER 这四个是一种模式
PLN PLN+CENTER 是一种模式
*/

//===============================关于表框及表框内部的部分==================================//

// 绘制表框黑色底盘
void draw_ND_frame_chassis(double center_x, double center_y, double side) {
	setfillcolor(BLACK);
	ege_fillrect(center_x - side * 1.1 / 2, center_y - side * 1.1 / 2, side * 1.1, side * 1.1);
}

// 绘制表框下部白色的小圆球
void draw_ND_smallWhiteCircle(double center_x, double center_y, double side) {
	setfillcolor(EGEARGB(0xff, 79, 79, 75));
	ege_fillellipse(center_x - side / 2, center_y - side / 2, side, side);
}

// 绘制表盘左上角的真实空速，对地速度，风速风向
void draw_ND_Speed(double center_x, double center_y, double side) {
	// 真实空速，对地速度，风速风向显示
	setbkmode(TRANSPARENT);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setcolor(WHITE);
	setfont(side / 30, 0, "黑体");// 这是对字体的大小的设置
	char ch[64];
	outtextxy(center_x - side / 2.2, center_y - side / 2.3, "GS");
	outtextxy(center_x - side / 3.1, center_y - side / 2.3, "TAS");
	if (WS == 0 && WD == 0) {
		if (TAS <= 100) {
			GS = TAS;
			setfont(side / 23, 0, "黑体");
			sprintf_s(ch, "%d", (int)GS);
			if (TAS <= 10)
				outtextxy(center_x - side / 2.6, center_y - side / 2.3, ch);
			else {
				outtextxy(center_x - side / 2.54, center_y - side / 2.3, ch);
			}
			outtextxy(center_x - side / 3.88, center_y - side / 2.3, "---");
		}
		else {
			GS = TAS;
			setfont(side / 23, 0, "黑体");
			sprintf_s(ch, "%d", (int)GS);
			outtextxy(center_x - side / 2.56, center_y - side / 2.3, ch);
			outtextxy(center_x - side / 4.1, center_y - side / 2.3, ch);
		}
		outtextxy(center_x - side / 2.3, center_y - side / 2.58, "---");
		outtextxy( center_x - side / 2.64, center_y - side / 2.44, ".");
		outtextxy(center_x - side / 2.74, center_y - side / 2.58, "/");
		outtextxy(center_x - side / 3.18, center_y - side / 2.58, "---");
	}
	else {
		GS = sqrt(fabs(TAS * TAS + WS * WS + 2 * TAS * WS * cos(WD)));
		setfont(side / 23, 0, "黑体");
		if (TAS <= 100) {
			sprintf_s(ch, "%d", (int)GS);
			if (GS <= 10)
				outtextxy(center_x - side / 2.6, center_y - side / 2.3, ch);
			else {
				outtextxy(center_x - side / 2.54, center_y - side / 2.3, ch);
			}
			outtextxy(center_x - side / 3.88, center_y - side / 2.3, "---");
			if (WS == 0 && WD != 0) {
				sprintf_s(ch, "%d", (int)WD);
				outtextxy(center_x - side / 2.3, center_y - side / 2.58, ch);
				outtextxy(center_x - side / 2.64, center_y - side / 2.44, ".");
				outtextxy(center_x - side / 2.74, center_y - side / 2.58, "/");
				outtextxy(center_x - side / 3.18, center_y - side / 2.58, "---");
			}
			else if ((WD == 0 && WS != 0)) {
				outtextxy(center_x - side / 2.3, center_y - side / 2.58, "---");
				outtextxy(center_x - side / 2.64, center_y - side / 2.44, ".");
				outtextxy(center_x - side / 2.74, center_y - side / 2.58, "/");
				sprintf_s(ch, "%d", (int)WS);
				outtextxy(center_x - side / 3.18, center_y - side / 2.58, ch);
			}
			else {
				sprintf_s(ch, "%d", (int)WD);
				outtextxy(center_x - side / 2.3, center_y - side / 2.58, ch);
				outtextxy(center_x - side / 2.64, center_y - side / 2.44, ".");
				outtextxy(center_x - side / 2.74, center_y - side / 2.58, "/");
				sprintf_s(ch, "%d", (int)WS);
				outtextxy(center_x - side / 3.18, center_y - side / 2.58, ch);
			}
		}
		else {
			sprintf_s(ch, "%d", (int)GS);
			if (GS <= 10)
				outtextxy(center_x - side / 2.6, center_y - side / 2.3, ch);
			else {
				outtextxy(center_x - side / 2.54, center_y - side / 2.3, ch);
			}
			sprintf_s(ch, "%d", (int)TAS);
			outtextxy(center_x - side / 4.1, center_y - side / 2.3, ch);
			if (WS == 0 && WD != 0) {
				sprintf_s(ch, "%d", (int)WD);
				outtextxy(center_x - side / 2.3, center_y - side / 2.58, ch);
				outtextxy(center_x - side / 2.64, center_y - side / 2.44, ".");
				outtextxy(center_x - side / 2.74, center_y - side / 2.58, "/");
				outtextxy(center_x - side / 3.18, center_y - side / 2.58, "---");
			}
			else if ((WD == 0 && WS != 0)) {
				outtextxy(center_x - side / 2.3, center_y - side / 2.58, "---");
				outtextxy(center_x - side / 2.64, center_y - side / 2.44, ".");
				outtextxy(center_x - side / 2.74, center_y - side / 2.58, "/");
				sprintf_s(ch, "%d", (int)WS);
				outtextxy(center_x - side / 3.18, center_y - side / 2.58, ch);
			}
			else {
				sprintf_s(ch, "%d", (int)WD);
				outtextxy(center_x - side / 2.3, center_y - side / 2.58, ch);
				outtextxy(center_x - side / 2.64, center_y - side / 2.44, ".");
				outtextxy(center_x - side / 2.74, center_y - side / 2.58, "/");
				sprintf_s(ch, "%d", (int)WS);
				outtextxy(center_x - side / 3.18, center_y - side / 2.58, ch);
			}
		}
	}
}


//================================APP+CENTER  VOR+CENTER 模式==================================//

void draw_smallCircle(double x, double y, double r) {
	setfillcolor(WHITE);
	ege_ellipse(x + r * 0.45 * cos(-(pointrationAngle + realrotationAngle) * PI / 180) - r * 0.025,
		y - r * 0.025 - r * 0.45 * sin(-(pointrationAngle + realrotationAngle) * PI / 180), r * 0.05, r * 0.05);
	ege_ellipse(x - r * 0.45 * cos(-(pointrationAngle + realrotationAngle) * PI / 180) - r * 0.025,
		y - r * 0.025 + r * 0.45 * sin(-(pointrationAngle + realrotationAngle) * PI / 180), r * 0.05, r * 0.05);
	ege_ellipse(x + r * 0.25 * cos(-(pointrationAngle + realrotationAngle) * PI / 180) - r * 0.025,
		y - r * 0.025 - r * 0.25 * sin(-(pointrationAngle + realrotationAngle) * PI / 180), r * 0.05, r * 0.05);
	ege_ellipse(x - r * 0.25 * cos(-(pointrationAngle + realrotationAngle) * PI / 180) - r * 0.025,
		y - r * 0.025 + r * 0.25 * sin(-(pointrationAngle + realrotationAngle) * PI / 180), r * 0.05, r * 0.05);
}

void draw_ND_app_center(double center_x, double center_y, double side) {

	// 初始数据设置
	double r = side / 115 * 37.5;
	realrotationAngle = 360 - rotationangle;
	setcolor(EGEARGB(0xff, 177, 177, 178));

	// 长长刻度
	setlinewidth(side / 250);
	for (double i = 45; i < 360; i += 45)
	{	// 长长刻度对应比例： (1- 2/37.5)
		double scaleAngle = 0 + i;
		double rad = scaleAngle * PI / 180.0;
		ege_line(center_x + 1.15 * r * sin(rad), center_y - 1.15 * r * cos(rad), center_x + 0.98 * r * sin(rad), center_y - 0.98 * r * cos(rad));
	}
	//长刻度
	setlinewidth(side / 250);// 这是对长刻度的粗细设定
	for (double i = 0; i < 360; i += 10)
	{	// 长刻度对应比例：(1- 5/37.5)
		double scaleAngle = realrotationAngle + i;
		double rad = scaleAngle * PI / 180.0;
		ege_line(center_x + r * sin(rad), center_y - r * cos(rad), center_x + (1 - 5 / 37.5) * r * sin(rad), center_y - (1 - 5 / 37.5) * r * cos(rad));
	}
	//短刻度
	setlinewidth(side / 280);// 这是对短刻度的粗细设定
	for (double i = 5; i < 360; i += 10)
	{	// 短刻度对应比例： (1- 2/37.5)
		double scaleAngle = realrotationAngle + i;
		double rad = scaleAngle * PI / 180.0;
		ege_line(center_x + r * sin(rad), center_y - r * cos(rad), center_x + (1 - 2 / 37.5) * r * sin(rad), center_y - (1 - 2 / 37.5) * r * cos(rad));
	}
	// 上下两个长刻度
	ege_line(center_x, center_y - r,
		center_x, center_y - (1 - 19 / 37.5) * r
	);
	ege_line(center_x, center_y + r,
		center_x, center_y + (1 - 19 / 37.5) * r
	);
	ege_line(center_x - r / 32, center_y - (1 - 12 / 37.5) * r,
		center_x + r / 32, center_y - (1 - 12 / 37.5) * r);
	ege_line(center_x - r / 32, center_y + (1 - 12 / 37.5) * r,
		center_x + r / 32, center_y + (1 - 12 / 37.5) * r);

	// 旋转数字绘制
	for (int i = 0; i < 360; i += 30) {
		double textAngle = realrotationAngle + i;
		double rad = textAngle * PI / 180.0;
		double textPosX = center_x + 0.75 * r * sin(rad);//*0.85是调节数字与中心坐标位置的关系，依据自己的位置条件适当修改，如可能在你的表上*0.7是恰好在需要的位置上，则改为*0.7
		double textPosY = center_y - 0.75 * r * cos(rad);

		LOGFONTW font;
		setfont(side / 23.3333333333, 0, "黑体");
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		getfont(&font);
		font.lfEscapement = -textAngle * 10;
		font.lfWeight = 550;
		setfont(&font);
# if 0
		//xyprintf(x + 0.8 * r * cos(rad), y - 0.8 * r * sin(rad), "%d", i);//忽略此行，如不放心，可将前面*的数字改为上面注释位置修改的数-0.05，如上面的数字是*0.7，则此处改为*0.65
# endif
		char strBuffer[64];
		sprintf_s(strBuffer, "%d", i / 10);
		outtextxy(textPosX, textPosY, strBuffer);
	}

	// 上面小三角形
	ege_point points1[4] = {
		center_x - side / 85, center_y - r / 0.91,// 左上
		center_x + side / 85,center_y - r / 0.91,// 右上
		center_x,center_y - r / 0.97,// 下
		center_x - side / 85,center_y - r / 0.91
	};
	ege_drawpoly(4, points1);

	// 小三角形上面的3条线
	ege_point points2[4] = {
		center_x - side / 19, center_y - r / 0.8,// 左上
		center_x - side / 19, center_y - r / 0.91,// 左下
		center_x + side / 19, center_y - r / 0.91,// 右下
		center_x + side / 19, center_y - r / 0.8// 右上
	};
	ege_drawpoly(4, points2);

	// 上面数字显示
	setbkmode(TRANSPARENT);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setfont(side / 19, 0, "黑体");// 这是对数字的大小的设置
	char ch[64];
	sprintf(ch, "%03d", HDGMAG);
	outtextxy(center_x, center_y - r / 0.85, ch);

	setcolor(EGEARGB(250, 76, 153, 0));// 这是对两边字体的颜色设置绿色
	setfont(side / 25, 0, "黑体");// 这是对字体的大小设置
	outtextxy(center_x - r / 3.5, center_y - r / 0.85, "HDG");
	outtextxy(center_x + r / 3.5, center_y - r / 0.85, "MAG" );

	// 北字绘制
	setlinewidth(side / 250);
	setcolor(EGEARGB(200, 177, 177, 178));
	ege_line(center_x - r / 16, center_y - r / 7,
		center_x - r / 16, center_y + r / 7);
	ege_line(center_x + r / 16, center_y - r / 7,
		center_x + r / 16, center_y + r / 7);
	ege_line(center_x - r / 16, center_y,
		center_x - r / 5, center_y);
	ege_line(center_x + r / 16, center_y,
		center_x + r / 5, center_y);
	ege_line(center_x - r / 16, center_y + r / 7,
		center_x - r / 8, center_y + r / 7);
	ege_line(center_x + r / 16, center_y + r / 7,
		center_x + r / 8, center_y + r / 7);

	// 四个小圆绘制
	draw_smallCircle(center_x, center_y, r);


	setlinewidth(side / 250);
	setcolor(EGEARGB(0xff, 177, 177, 178));

	double rad = -(pointrationAngle + rotationangle) * PI / 180;

	ege_point points3[14] = {
		//center_x - r / 30,center_y - r / 2.9,// 1 
		-r / 30 * cos(rad) - (-r / 2.9) * sin(rad) + center_x, (-r / 2.9) * cos(rad) + (-r / 30) * sin(rad) + center_y,
		//center_x - r / 30,center_y - r / 2.55,//2 
		-r / 30 * cos(rad) - (-r / 2.55) * sin(rad) + center_x, (-r / 2.55) * cos(rad) + (-r / 30) * sin(rad) + center_y,
		//center_x - r / 13,center_y - r / 2.55,//3 
		-r / 13 * cos(rad) - (-r / 2.55) * sin(rad) + center_x, (-r / 2.55) * cos(rad) + (-r / 13) * sin(rad) + center_y,
		//center_x - r / 13,center_y - r / 2.2,//4 
		-r / 13 * cos(rad) - (-r / 2.2) * sin(rad) + center_x, (-r / 2.2) * cos(rad) + (-r / 13) * sin(rad) + center_y,
		//center_x - r / 30,center_y - r / 2.2,//5 
		-r / 30 * cos(rad) - (-r / 2.2) * sin(rad) + center_x, (-r / 2.2) * cos(rad) + (-r / 30) * sin(rad) + center_y,
		//center_x - r / 30,center_y - r / 1.12,//6 
		-r / 30 * cos(rad) - (-r / 1.12) * sin(rad) + center_x, (-r / 1.12) * cos(rad) + (-r / 30) * sin(rad) + center_y,
		//center_x , center_y - r / 1.08,//7 
		r / 1.08 * sin(rad) + center_x, -r / 1.08 * cos(rad) + center_y,
		//center_x + r / 30,center_y - r / 1.12,//8 
		r / 30 * cos(rad) - (-r / 1.12) * sin(rad) + center_x, (-r / 1.12) * cos(rad) + r / 30 * sin(rad) + center_y,
		//center_x + r / 30,center_y - r / 2.2,//9 
		r / 30 * cos(rad) - (-r / 2.2) * sin(rad) + center_x, (-r / 2.2) * cos(rad) + r / 30 * sin(rad) + center_y,
		//center_x + r / 13,center_y - r / 2.2,//10 
		r / 13 * cos(rad) - (-r / 2.2) * sin(rad) + center_x, (-r / 2.2) * cos(rad) + r / 13 * sin(rad) + center_y,
		//center_x + r / 13,center_y - r / 2.55,//11 
		r / 13 * cos(rad) - (-r / 2.55) * sin(rad) + center_x, (-r / 2.55) * cos(rad) + r / 13 * sin(rad) + center_y,
		//center_x + r / 30,center_y - r / 2.55,//12 
		r / 30 * cos(rad) - (-r / 2.55) * sin(rad) + center_x, (-r / 2.55) * cos(rad) + r / 30 * sin(rad) + center_y,
		//center_x + r / 30,center_y - r / 2.9,//13 
		r / 30 * cos(rad) - (-r / 2.9) * sin(rad) + center_x, (-r / 2.9) * cos(rad) + r / 30 * sin(rad) + center_y,
		//center_x - r / 30,center_y - r / 2.9//1 
		-r / 30 * cos(rad) - (-r / 2.9) * sin(rad) + center_x, (-r / 2.9) * cos(rad) + (-r / 30) * sin(rad) + center_y,
	};
	ege_drawpoly(14, points3);

	ege_point points4[6] = {
		//center_x - r / 30,center_y + r / 2.9,// 1 
		-r / 30 * cos(rad) - (r / 2.9) * sin(rad) + center_x, (r / 2.9) * cos(rad) + (-r / 30) * sin(rad) + center_y,
		//center_x + r / 30,center_y + r / 2.9,//2 
		r / 30 * cos(rad) - (r / 2.9) * sin(rad) + center_x, (r / 2.9) * cos(rad) + (r / 30) * sin(rad) + center_y,
		//center_x + r / 30,center_y + r / 1.12,//3 
		r / 30 * cos(rad) - (r / 1.12) * sin(rad) + center_x, (r / 1.12) * cos(rad) + (r / 30) * sin(rad) + center_y,
		//center_x , center_y + r / 1.08,//4 
		-r / 1.08 * sin(rad) + center_x, r / 1.08 * cos(rad) + center_y,
		//center_x - r / 30,center_y + r / 1.12,//5 
		-r / 30 * cos(rad) - (r / 1.12) * sin(rad) + center_x, (r / 1.12) * cos(rad) + (-r / 30) * sin(rad) + center_y,
		//center_x - r / 30,center_y + r / 2.9//1 
		-r / 30 * cos(rad) - (r / 2.9) * sin(rad) + center_x, (r / 2.9) * cos(rad) + (-r / 30) * sin(rad) + center_y,
	};
	ege_drawpoly(6, points4);

	draw_ndcourse2(center_x, center_y, side);
}

//画选定的航向
void draw_ndcourse2(double compass_x, double compass_y, double side)
{
	double compass_r = side / 115 * 37.5;//表盘的半径

	//画指示标志
	setcolor(EGEARGB(0x99, 0xDE, 0x58, 0xC5));
	setlinewidth(compass_r * 0.007);
	ege_point graphics[22];

	double rad = (course2 + realrotationangle2) * PI / 180;

	if ((course2 + realrotationangle2) > 310 || (course2 + realrotationangle2) < 50) {
		graphics[0].x = -compass_r * sin(0.5 * PI / 180) * cos(rad) - (-compass_r * cos(0.5 * PI / 180) * sin(rad)) + compass_x;
		graphics[0].y = -compass_r * cos(0.5 * PI / 180) * cos(rad) - compass_r * sin(0.5 * PI / 180) * sin(rad) + compass_y;

		graphics[1].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.2 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 0.75 / 96) * sin(rad)) + compass_x;
		graphics[1].y = (-compass_r * cos(0.5 * PI / 180) - side * 0.75 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.2 / 96) * sin(rad) + compass_y;

		graphics[2].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.2 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 0.75 / 96) * sin(rad)) + compass_x;
		graphics[2].y = (-compass_r * cos(0.5 * PI / 180) - side * 0.75 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.2 / 96) * sin(rad) + compass_y;

		graphics[3].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.4 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[3].y = (-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.4 / 96) * sin(rad) + compass_y;

		graphics[4].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.6 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[4].y = (-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.6 / 96) * sin(rad) + compass_y;

		graphics[5].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.6 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[5].y = (-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.6 / 96) * sin(rad) + compass_y;

		graphics[6].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[6].y = (-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[7].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 0.7 / 96) * sin(rad)) + compass_x;
		graphics[7].y = (-compass_r * cos(0.5 * PI / 180) - side * 0.7 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[8].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 0.7 / 96) * sin(rad)) + compass_x;
		graphics[8].y = (-compass_r * cos(0.5 * PI / 180) - side * 0.7 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[9].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) + side * 0.1 / 96) * sin(rad)) + compass_x;
		graphics[9].y = (-compass_r * cos(0.5 * PI / 180) + side * 0.1 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[10].x = compass_r * sin(rad) + compass_x;
		graphics[10].y = -compass_r * cos(rad) + compass_y;

		graphics[11].x = compass_r * sin(rad) + compass_x;
		graphics[11].y = -compass_r * cos(rad) + compass_y;

		graphics[12].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) + side * 0.1 / 96) * sin(rad)) + compass_x;
		graphics[12].y = (-compass_r * cos(-0.5 * PI / 180) + side * 0.1 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[13].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 0.7 / 96) * sin(rad)) + compass_x;
		graphics[13].y = (-compass_r * cos(-0.5 * PI / 180) - side * 0.7 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[14].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 0.7 / 96) * sin(rad)) + compass_x;
		graphics[14].y = (-compass_r * cos(-0.5 * PI / 180) - side * 0.7 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[15].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[15].y = (-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[16].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.6 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[16].y = (-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.6 / 96) * sin(rad) + compass_y;

		graphics[17].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.6 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[17].y = (-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.6 / 96) * sin(rad) + compass_y;

		graphics[18].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.4 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[18].y = (-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.4 / 96) * sin(rad) + compass_y;

		graphics[19].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.2 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 0.75 / 96) * sin(rad)) + compass_x;
		graphics[19].y = (-compass_r * cos(-0.5 * PI / 180) - side * 0.75 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.2 / 96) * sin(rad) + compass_y;

		graphics[20].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.2 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 0.75 / 96) * sin(rad)) + compass_x;
		graphics[20].y = (-compass_r * cos(-0.5 * PI / 180) - side * 0.75 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.2 / 96) * sin(rad) + compass_y;

		graphics[21].x = (-compass_r * sin(-0.5 * PI / 180)) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180)) * sin(rad)) + compass_x;
		graphics[21].y = (-compass_r * cos(-0.5 * PI / 180)) * cos(rad) - (compass_r * sin(-0.5 * PI / 180)) * sin(rad) + compass_y;

		ege_bezier(22, graphics);
	}
}
//================================APP VOR  MAP  MAP+CENTER 模式==================================//


//画指向航向的指针
void draw_ndpoint2(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径

	setcolor(EGEARGB(0x99, 0xff, 0xff, 0xff));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽

	double rad = (realrotationangle2 + ndpointrotationangle) * PI / 180;

	if ((realrotationangle2 + ndpointrotationangle) >= 300 || (realrotationangle2 + ndpointrotationangle) <= 60) {
		//画出指针
		ege_line(center_x, center_y, r * sin(rad) + center_x, -r * cos(rad) + center_y);
		ege_line(-r * 0.02 * cos(rad) - (-r / 4 * sin(rad)) + center_x, -r / 4 * cos(rad) - r * 0.02 * sin(rad) + center_y, r * 0.02 * cos(rad) - (-r / 4 * sin(rad)) + center_x, -r / 4 * cos(rad) + r * 0.02 * sin(rad) + center_y);
		ege_line(-r * 0.02 * cos(rad) - (-r / 2 * sin(rad)) + center_x, -r / 2 * cos(rad) - r * 0.02 * sin(rad) + center_y, r * 0.02 * cos(rad) - (-r / 2 * sin(rad)) + center_x, -r / 2 * cos(rad) + r * 0.02 * sin(rad) + center_y);
		ege_line(-r * 0.02 * cos(rad) - (-r * 3 / 4 * sin(rad)) + center_x, -r * 3 / 4 * cos(rad) - r * 0.02 * sin(rad) + center_y, r * 0.02 * cos(rad) - (-r * 3 / 4 * sin(rad)) + center_x, -r * 3 / 4 * cos(rad) + r * 0.02 * sin(rad) + center_y);
	}
}

//画顶部会移动的三角形
void draw_ndtoptriangle2(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径

	setcolor(EGEARGB(0x99, 0xff, 0xff, 0xff));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽

	double rad = 0;//将旋转角度化成弧度制

	if (1/*(ndtoprotationangle + realrotationangle2) > 310 || (ndtoprotationangle + realrotationangle2) < 50*/) {
		//画顶部会移动的三角形
		ege_point toptriangle[4];

		toptriangle[0].x = r * sin(rad) + center_x;
		toptriangle[0].y = -r * cos(rad) + center_y;

		toptriangle[1].x = -side * 2 / 104 * cos(rad) + (r + side * 3 / 104) * sin(rad) + center_x;
		toptriangle[1].y = (-r - side * 3 / 104) * cos(rad) - side * 2 / 104 * sin(rad) + center_y;

		toptriangle[2].x = side * 2 / 104 * cos(rad) + (r + side * 3 / 104) * sin(rad) + center_x;
		toptriangle[2].y = (-r - side * 3 / 104) * cos(rad) + side * 2 / 104 * sin(rad) + center_y;

		toptriangle[3].x = r * sin(rad) + center_x;
		toptriangle[3].y = -r * cos(rad) + center_y;

		ege_drawpoly(4, toptriangle);
	}
}

//画顶部显示的文字内容
void draw_ndtoptext2(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径

	setcolor(EGEARGB(0x99, 0xff, 0xff, 0xff));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽

	//顶部中间的数字显示
	LOGFONTW font;
	setfont(r * 0.09, 0, "Leelawadee");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font);
	font.lfEscapement = 0;
	font.lfWeight = 550;
	setfont(&font);

	char stringBuffer[64];
	ndcourse = rotationangle;
	sprintf_s(stringBuffer, "%03d", ndcourse);
	outtextxy(center_x, center_y - r - side * 6 / 104, stringBuffer);

	//顶部左边的字母显示
	setfont(r * 0.07, 0, "Leelawadee");
	setcolor(EGEARGB(0x99, 0x75, 0xf9, 0x4d));
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font);
	font.lfEscapement = 0;
	font.lfWeight = 550;
	setfont(&font);
	outtextxy(center_x - side * 11 / 104, center_y - r - side * 6 / 104, "HDG");

	//顶部右边的字母显示
	setfont(r * 0.07, 0, "Leelawadee");
	setcolor(EGEARGB(0x99, 0x75, 0xf9, 0x4d));
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font);
	font.lfEscapement = 0;
	font.lfWeight = 550;
	setfont(&font);
	outtextxy(center_x + side * 12 / 104, center_y - r - side * 6 / 104, "MAG");
}

//画预定航线
void draw_reserveroad(double center_x, double center_y, double side)
{
	double compass_r = side * 71 / 104;//表盘的半径

	double rad = (course3 + realrotationangle2) * PI / 180;

	if ((course3 + realrotationangle2) > 360)
	{
		rad = (course3 + realrotationangle2 - 360) * PI / 180;
	}

	//ege_line(300, 400, 400, 300);
	/*char str[64];
	sprintf_s(str, "%lf", rad * 180 / PI);
	outtextxy( 400, 400,str);*/
	if (center_x + compass_r * sin(rad) >= center_x - compass_r * sin(45 * PI / 180) && center_x + compass_r * sin(rad) <= center_x + compass_r * sin(45 * PI / 180) && center_y - compass_r * cos(rad) <= center_y + side * 33 / 104) {
		ege_line(center_x + compass_r * 0.2 * sin(rad), center_y - compass_r * 0.2 * cos(rad), center_x + compass_r * sin(rad), center_y - compass_r * cos(rad));
	}
	//else if(center_x + compass_r * sin(rad) < center_x - compass_r * sin(45 * PI / 180) && center_y - compass_r * cos(rad) <= )
	setlinestyle(CENTER_LINE);
	setlinewidth(compass_r * 0.007);
	ege_line(center_x - compass_r * 0.2 * sin(rad), center_y + compass_r * 0.2 * cos(rad), center_x - compass_r * 0.3 * sin(rad), center_y + compass_r * 0.3 * cos(rad));
	setlinestyle(SOLID_LINE);
}

//画刻度盘上的弧线
void draw_acr(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径

	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽

	ege_arc(center_x - r, center_y - r, r * 2, r * 2, -40.0, -100.0);
}

//画刻度
void draw_map_scale(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径

	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽

	//短刻度
	for (int i = 5; i < 360; i += 10)
	{
		double scaleAngle = realrotationangle2 + i;
		double rad = scaleAngle * PI / 180.0;
		double scalePosX = center_x + 0.975 * r * sin(rad);
		double scalePosY = center_y - 0.975 * r * cos(rad);

		if (scalePosX >= center_x - r * sin(55 * PI / 180) && scalePosX <= center_x + r * sin(55 * PI / 180) && scalePosY <= center_y - r * cos(55 * PI / 180) && scalePosY >= center_y - r) //判断文字是否在输出区域内，在区域内则输出，不在区域内则不输出
			ege_line(center_x + r * sin(rad), center_y - r * cos(rad), center_x + 0.975 * r * sin(rad), center_y - 0.975 * r * cos(rad));
	}

	//长刻度
	for (int i = 0; i < 360; i += 10)
	{
		double scaleAngle = realrotationangle2 + i;
		double rad = scaleAngle * PI / 180.0;
		double scalePosX = center_x + 0.975 * r * sin(rad);
		double scalePosY = center_y - 0.975 * r * cos(rad);

		if (scalePosX >= center_x - r * sin(55 * PI / 180) && scalePosX <= center_x + r * sin(55 * PI / 180) && scalePosY <= center_y - r * cos(55 * PI / 180) && scalePosY >= center_y - r) //判断文字是否在输出区域内，在区域内则输出，不在区域内则不输出
			ege_line(center_x + r * sin(rad), center_y - r * cos(rad), center_x + 0.96 * r * sin(rad), center_y - 0.96 * r * cos(rad));
	}
}

//画刻度值
void draw_ndtext(double center_x, double center_y, double side) {
	double r = side * 71 / 104;//表盘的半径

	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽

	for (int i = 0; i < 360; i += 30) //循环输出表上的刻度值
	{
		double textAngle = realrotationangle2 + i;
		double rad = textAngle * PI / 180.0;
		double textPosX = center_x + 0.92 * r * sin(rad);
		double textPosY = center_y - 0.92 * r * cos(rad);

		//设置文字的格式
		LOGFONTW font;
		setcolor(EGEARGB(0x99, 0xff, 0xff, 0xff));
		setfont(r * 0.09, 0, "Leelawadee");
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		getfont(&font);
		font.lfEscapement = -textAngle * 10;
		font.lfWeight = 500;
		setfont(&font);
#if 0
		xyprintf(compass_x + 0.8 * compass_r * cos(rad), compass_y - 0.8 * compass_r * sin(rad), "%d", i);
#endif
		if (textPosX >= center_x - r * sin(50 * PI / 180) && textPosX <= center_x + r * sin(55 * PI / 180) && textPosY <= center_y - r * cos(55 * PI / 180) && textPosY >= center_y - r) //判断文字是否在输出区域内，在区域内则输出，不在区域内则不输出
		{
			char strBuffer[64];
			sprintf_s(strBuffer, "%d", i / 10);
			outtextxy(textPosX, textPosY, strBuffer);
		}
	}
}

//画指向航向的固定指针
void draw_ndpoint1(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径

	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽

	//画出指针
	ege_line(center_x, center_y, center_x, center_y - r - 3 * side / 104);
	ege_line(center_x - r * 0.02, center_y - r / 4, center_x + r * 0.02, center_y - r / 4);
	ege_line(center_x - r * 0.02, center_y - r / 2, center_x + r * 0.02, center_y - r / 2);
	ege_line(center_x - r * 0.02, center_y - r * 3 / 4, center_x + r * 0.02, center_y - r * 3 / 4);
}

//画表中间的一个三角形
void draw_ndcenterangle(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径

	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽

	//画表中间的一个三角形
	ege_point centerangle[4];

	centerangle[0].x = center_x;
	centerangle[0].y = center_y;

	centerangle[1].x = center_x - side * 3.5 / 104;
	centerangle[1].y = center_y + side * 8 / 104;

	centerangle[2].x = center_x + side * 3.5 / 104;
	centerangle[2].y = center_y + side * 8 / 104;

	centerangle[3].x = center_x;
	centerangle[3].y = center_y;

	ege_drawpoly(4, centerangle);
}

//画顶部会移动的三角形
void draw_ndtoptriangle1(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径

	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽

	double rad = (ndtoprotationangle + realrotationangle2) * PI / 180;//将旋转角度化成弧度制

	if ((ndtoprotationangle + realrotationangle2) > 310 || (ndtoprotationangle + realrotationangle2) < 50) {
		//画顶部会移动的三角形
		ege_point toptriangle[4];

		toptriangle[0].x = r * sin(rad) + center_x;
		toptriangle[0].y = -r * cos(rad) + center_y;

		toptriangle[1].x = -side * 2 / 104 * cos(rad) + (r + side * 3 / 104) * sin(rad) + center_x;
		toptriangle[1].y = (-r - side * 3 / 104) * cos(rad) - side * 2 / 104 * sin(rad) + center_y;

		toptriangle[2].x = side * 2 / 104 * cos(rad) + (r + side * 3 / 104) * sin(rad) + center_x;
		toptriangle[2].y = (-r - side * 3 / 104) * cos(rad) + side * 2 / 104 * sin(rad) + center_y;

		toptriangle[3].x = r * sin(rad) + center_x;
		toptriangle[3].y = -r * cos(rad) + center_y;

		ege_drawpoly(4, toptriangle);
	}
}

//画顶部不闭合的矩形
void draw_ndtoprectangle(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径

	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽

	//画顶部不闭合的矩形
	ege_point toprectangle[4];

	toprectangle[0].x = center_x - 6.5 * side / 104;
	toprectangle[0].y = center_y - r - 9 * side / 104;

	toprectangle[1].x = center_x - 6.5 * side / 104;
	toprectangle[1].y = center_y - r - 3 * side / 104;

	toprectangle[2].x = center_x + 6.5 * side / 104;
	toprectangle[2].y = center_y - r - 3 * side / 104;

	toprectangle[3].x = center_x + 6.5 * side / 104;
	toprectangle[3].y = center_y - r - 9 * side / 104;

	ege_drawpoly(4, toprectangle);
}

//画顶部显示的文字内容
void draw_ndtoptext1(double center_x, double center_y, double side)
{
	double r = side * 71 / 104;//表盘的半径

	setcolor(EGEARGB(150, 177, 177, 178));//设置线条颜色
	setlinewidth(r * 0.008);//设置线宽

	//顶部中间的数字显示
	LOGFONTW font;
	setfont(r * 0.09, 0, "Leelawadee");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font);
	font.lfEscapement = 0;
	font.lfWeight = 550;
	setfont(&font);

	char stringBuffer[64];
	ndcourse = ndpointrotationangle;
	sprintf_s(stringBuffer, "%03d", ndcourse);
	outtextxy(center_x, center_y - r - side * 6 / 104, stringBuffer);

	//顶部左边的字母显示
	setfont(r * 0.07, 0, "Leelawadee");
	setcolor(EGEARGB(0x99, 0x75, 0xf9, 0x4d));
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font);
	font.lfEscapement = 0;
	font.lfWeight = 550;
	setfont(&font);
	outtextxy(center_x - side * 11 / 104, center_y - r - side * 6 / 104, "TRK");

	//顶部右边的字母显示
	setfont(r * 0.07, 0, "Leelawadee");
	setcolor(EGEARGB(0x99, 0x75, 0xf9, 0x4d));
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	getfont(&font);
	font.lfEscapement = 0;
	font.lfWeight = 550;
	setfont(&font);
	outtextxy(center_x + side * 12 / 104, center_y - r - side * 6 / 104, "MAG");
}

//画选定的航向
void draw_ndcourse(double compass_x, double compass_y, double side)
{
	double compass_r = side * 71 / 104;//表盘的半径

	//画指示标志
	setcolor(EGEARGB(0x99, 0xDE, 0x58, 0xC5));
	setlinewidth(compass_r * 0.007);
	ege_point graphics[22];

	double rad = (course2 + realrotationangle2) * PI / 180;

	if ((course2 + realrotationangle2) > 310 || (course2 + realrotationangle2) < 50) {
		graphics[0].x = -compass_r * sin(0.5 * PI / 180) * cos(rad) - (-compass_r * cos(0.5 * PI / 180) * sin(rad)) + compass_x;
		graphics[0].y = -compass_r * cos(0.5 * PI / 180) * cos(rad) - compass_r * sin(0.5 * PI / 180) * sin(rad) + compass_y;

		graphics[1].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.2 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 0.75 / 96) * sin(rad)) + compass_x;
		graphics[1].y = (-compass_r * cos(0.5 * PI / 180) - side * 0.75 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.2 / 96) * sin(rad) + compass_y;

		graphics[2].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.2 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 0.75 / 96) * sin(rad)) + compass_x;
		graphics[2].y = (-compass_r * cos(0.5 * PI / 180) - side * 0.75 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.2 / 96) * sin(rad) + compass_y;

		graphics[3].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.4 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[3].y = (-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.4 / 96) * sin(rad) + compass_y;

		graphics[4].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.6 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[4].y = (-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.6 / 96) * sin(rad) + compass_y;

		graphics[5].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.6 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[5].y = (-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.6 / 96) * sin(rad) + compass_y;

		graphics[6].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[6].y = (-compass_r * cos(0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[7].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 0.7 / 96) * sin(rad)) + compass_x;
		graphics[7].y = (-compass_r * cos(0.5 * PI / 180) - side * 0.7 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[8].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) - side * 0.7 / 96) * sin(rad)) + compass_x;
		graphics[8].y = (-compass_r * cos(0.5 * PI / 180) - side * 0.7 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[9].x = (-compass_r * sin(0.5 * PI / 180) - side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(0.5 * PI / 180) + side * 0.1 / 96) * sin(rad)) + compass_x;
		graphics[9].y = (-compass_r * cos(0.5 * PI / 180) + side * 0.1 / 96) * cos(rad) - (compass_r * sin(0.5 * PI / 180) + side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[10].x = compass_r * sin(rad) + compass_x;
		graphics[10].y = -compass_r * cos(rad) + compass_y;

		graphics[11].x = compass_r * sin(rad) + compass_x;
		graphics[11].y = -compass_r * cos(rad) + compass_y;

		graphics[12].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) + side * 0.1 / 96) * sin(rad)) + compass_x;
		graphics[12].y = (-compass_r * cos(-0.5 * PI / 180) + side * 0.1 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[13].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 0.7 / 96) * sin(rad)) + compass_x;
		graphics[13].y = (-compass_r * cos(-0.5 * PI / 180) - side * 0.7 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[14].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 0.7 / 96) * sin(rad)) + compass_x;
		graphics[14].y = (-compass_r * cos(-0.5 * PI / 180) - side * 0.7 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[15].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.8 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[15].y = (-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.8 / 96) * sin(rad) + compass_y;

		graphics[16].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.6 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[16].y = (-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.6 / 96) * sin(rad) + compass_y;

		graphics[17].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.6 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[17].y = (-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.6 / 96) * sin(rad) + compass_y;

		graphics[18].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.4 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * sin(rad)) + compass_x;
		graphics[18].y = (-compass_r * cos(-0.5 * PI / 180) - side * 1.5 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.4 / 96) * sin(rad) + compass_y;

		graphics[19].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.2 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 0.75 / 96) * sin(rad)) + compass_x;
		graphics[19].y = (-compass_r * cos(-0.5 * PI / 180) - side * 0.75 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.2 / 96) * sin(rad) + compass_y;

		graphics[20].x = (-compass_r * sin(-0.5 * PI / 180) + side * 0.2 / 96) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180) - side * 0.75 / 96) * sin(rad)) + compass_x;
		graphics[20].y = (-compass_r * cos(-0.5 * PI / 180) - side * 0.75 / 96) * cos(rad) - (compass_r * sin(-0.5 * PI / 180) - side * 0.2 / 96) * sin(rad) + compass_y;

		graphics[21].x = (-compass_r * sin(-0.5 * PI / 180)) * cos(rad) - ((-compass_r * cos(-0.5 * PI / 180)) * sin(rad)) + compass_x;
		graphics[21].y = (-compass_r * cos(-0.5 * PI / 180)) * cos(rad) - (compass_r * sin(-0.5 * PI / 180)) * sin(rad) + compass_y;

		ege_bezier(22, graphics);
	}
}

//画MAP模式下的NP表
void draw_ND_map(double center_x, double center_y, double side)
{
	realrotationangle2 = 360 - ndpointrotationangle;
	ndtoprotationangle = rotationangle;

	draw_acr(center_x, center_y, side);

	draw_map_scale(center_x, center_y, side);

	draw_ndtext(center_x, center_y, side);

	draw_ndpoint1(center_x, center_y, side);

	draw_ndcourse(center_x, center_y, side);

	draw_ndcenterangle(center_x, center_y, side);

	draw_ndtoptriangle1(center_x, center_y, side);

	draw_ndtoprectangle(center_x, center_y, side);

	draw_ndtoptext1(center_x, center_y, side);
}

//画APP模式下的ND表
void draw_ND_app(double center_x, double center_y, double side)
{
	realrotationangle2 = 360 - rotationangle;

	draw_reserveroad(center_x, center_y, side);

	draw_acr(center_x, center_y, side);

	draw_map_scale(center_x, center_y, side);

	draw_ndtext(center_x, center_y, side);

	draw_ndpoint2(center_x, center_y, side);

	draw_ndcourse(center_x, center_y, side);

	draw_ndcenterangle(center_x, center_y, side);

	draw_ndtoptriangle2(center_x, center_y, side);

	draw_ndtoprectangle(center_x, center_y, side);

	draw_ndtoptext2(center_x, center_y, side);
}

//================================PLN PLN+CENTER 模式==================================//


void draw_ND_pln(double center_x, double center_y, double side) {

	side = side / 2;

	double small_r = side / 104 * 40;// 确定大圆小圆的半径
	double big_r = side / 104 * 80;

	setlinewidth(side / 125);// 这是圆弧线的线宽设置
	setcolor(EGEARGB(0xff, 177, 177, 178));// 这是对于线的颜色的设置,与数字颜色的设置（白色）
	ege_arc(center_x - small_r, center_y - small_r,
		small_r * 2, small_r * 2,
		97, 166);
	/*
	数据怎么算的:
	97是比90多了多少度，166是180-7*2得来的——这个多少度越大，圆弧就越短
	-83是90减去多的度数，再加个负号
	*/

	ege_arc(center_x - small_r, center_y - small_r,
		small_r * 2, small_r * 2,
		-83, 166);

	ege_arc(center_x - big_r, center_y - big_r,
		big_r * 2, big_r * 2,
		94, 172);

	ege_arc(center_x - big_r, center_y - big_r,
		big_r * 2, big_r * 2,
		-86, 172);

	// 数字显示与WSNE显示
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setfont(side / 14, 0, "黑体");// 这是对数字的大小的设置
	char ch[64];
	int mapdistance_small = 0;
	int mapdistance_big = 0;
	if (mapDistance == 0) {
		mapdistance_small = 0;
		mapdistance_big = 5;
	}
	else if (mapDistance == 30) {
		mapdistance_small = 5;
		mapdistance_big = 10;
	}
	else if (mapDistance == 60) {
		mapdistance_small = 10;
		mapdistance_big = 20;
	}
	else if (mapDistance == 90) {
		mapdistance_small = 20;
		mapdistance_big = 40;
	}
	else if (mapDistance == 120) {
		mapdistance_small = 40;
		mapdistance_big = 80;
	}
	else if (mapDistance == 150) {
		mapdistance_small = 80;
		mapdistance_big = 160;
	}
	else if (mapDistance == 180) {
		mapdistance_small = 160;
		mapdistance_big = 320;
	}
	else if (mapDistance == 210) {
		mapdistance_small = 320;
		mapdistance_big = 640;
	}
	if (mapDistance == 0) {
		outtextxy(center_x, center_y - small_r / 1.01, "");
		outtextxy(center_x, center_y + small_r / 0.99, "");
		sprintf_s(ch, "%d", mapdistance_big);// 上40输出
		outtextxy(center_x, center_y - big_r / 1.01, ch);
		sprintf_s(ch, "%d", mapdistance_big);// 下40输出
		outtextxy(center_x, center_y + big_r / 0.99, ch);
	}
	else {
		if (mapDistance >= 180)
			setfont(side / 18, 0, "黑体");
		sprintf_s(ch, "%d", mapdistance_small);// 上20输出
		outtextxy(center_x, center_y - small_r / 1.01, ch);
		sprintf_s(ch, "%d", mapdistance_small);// 下20输出
		outtextxy(center_x, center_y + small_r / 0.99, ch);
		sprintf_s(ch, "%d", mapdistance_big);// 上40输出
		outtextxy(center_x, center_y - big_r / 1.01, ch);
		sprintf_s(ch, "%d", mapdistance_big);// 下40输出
		outtextxy(center_x, center_y + big_r / 0.99, ch);
	}

	/*
	* 上面的加减是输出数字的位置坐标
	*/
	setcolor(EGEARGB(250, 76, 153, 0));// 这是对NSME以及箭头颜色的设置（绿色）
	setfont(side / 12.5, 0, "黑体");// 这是对WSNE的大小的设置
	outtextxy(center_x - side / 33.3333, center_y - big_r / 0.9, "N"); // side / 33.3333是N向左偏移的位置
	outtextxy(center_x, center_y + big_r / 0.9, "S");
	outtextxy(center_x - big_r / 0.9, center_y, "W");
	outtextxy(center_x + big_r / 0.9, center_y, "E");

	setlinewidth(side / 160);// 这是对绘制箭头线的粗细设定
	ege_line(center_x + side / 34, center_y - big_r / 0.93,// 第一个坐标是靠下的,第二个坐标是靠上的
		center_x + side / 34, center_y - big_r / 0.87);
	ege_line(center_x + side / 34, center_y - big_r / 0.87,// 第一个坐标是靠上的,第二个坐标是靠左的
		center_x + side / 85, center_y - big_r / 0.89);
	ege_line(center_x + side / 34, center_y - big_r / 0.87,// 第一个坐标是靠上的,第二个坐标是靠右的
		center_x + side / 22, center_y - big_r / 0.89);
}



