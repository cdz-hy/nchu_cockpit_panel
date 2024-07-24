#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>
#include <mutex>
#include "DrawFrame.h"
#pragma warning(disable : 4996)

typedef struct {
	//放置EICAS需要接受的数据

	double Oangle_1;
	double Oangle_2;
	double Oangle_3;
	double Oangle_4;
	double fanSpeed;
	double fanSpeed_1;
	double gastemp;
	double gastemp_1;
	double FuelFlowSpeed;
	double FuelFlowSpeed_1;
	double Fuelrest_1;
	double Fuelrest_2;
	double Fuelrest_3;
	double Fuelrest_total;
	int TAT;
	double UPPERangle;

	int egeWidth;
	int egeHeight;

} SharedDataEICAS;


//函数声明
void draw_EICAS(double Oilcenterx, double Oilcentery, double side);
char* WideCharToString(const WCHAR* wideStr);

SharedDataEICAS* pDataEICAS;

std::mutex mtx;

//放置EICAS需要接受的数据
double Oangle_1;
double Oangle_2;
double Oangle_3;
double Oangle_4;
double fanSpeed;
double fanSpeed_1;
double gastemp;
double gastemp_1;
double FuelFlowSpeed;
double FuelFlowSpeed_1;
double Fuelrest_1;
double Fuelrest_2;
double Fuelrest_3;
double Fuelrest_total;
int TAT;
double UPPERangle;

int egeWidth;
int egeHeight;



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
	else if (uMsg == SC_MAXIMIZE) {
		HDC hdc = GetDC(NULL); // 获取屏幕的设备上下文，NULL参数表示获取整个屏幕的DC
		if (hdc)
		{
			windowsWidth = GetDeviceCaps(hdc, HORZRES); // 获取屏幕水平分辨率
			windowsHeight = GetDeviceCaps(hdc, VERTRES); // 获取屏幕垂直分辨率
			ReleaseDC(NULL, hdc); // 使用完毕后，释放设备上下文
		}
		changeSize = 2;
		return 0;
	}

	// 对于其他消息，调用原始窗口过程函数处理
	return CallWindowProc(originalWndProc, hwnd, uMsg, wParam, lParam);
}





int main() {

	WCHAR mySharedMemoryEICASW[] = L"Global\\MySharedMemoryEICAS";
	char* mySharedMemoryEICASA = WideCharToString(mySharedMemoryEICASW);

	// 打开共享内存
	HANDLE hMapFileEICAS = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,    // 可读可写
		FALSE,                  // 不从继承句柄中映射
		mySharedMemoryEICASW // 共享内存名称
	);


	if (hMapFileEICAS == NULL) {
		printf("OpenFileMapping failed (%d).\n", GetLastError());
		return -1;
	}

	// 映射共享内存到进程地址空间
	SharedDataEICAS* pDataEICAS0 = (SharedDataEICAS*)MapViewOfFile(
		hMapFileEICAS,               // 共享内存句柄
		FILE_MAP_ALL_ACCESS,    // 可读可写
		0,                      // 高位文件偏移
		0,                      // 低位文件偏移
		sizeof(SharedDataEICAS)          // 要映射的长度
	);

	if (pDataEICAS0 == NULL) {
		printf("MapViewOfFile failed (%d).\n", GetLastError());
		CloseHandle(hMapFileEICAS);
		return -1;
	}

	pDataEICAS = pDataEICAS0;

	egeHeight = pDataEICAS->egeHeight;
	egeWidth = pDataEICAS->egeWidth;

	initgraph(egeWidth, egeHeight, INIT_RENDERMANUAL);
	setbkcolor(BLACK);
	setcaption("MFD1");

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
			SendMessage(getHWnd(), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		}




		cleardevice();
		std::unique_lock<std::mutex> lock(mtx);

		draw_EICAS(windowsWidth * 1.0 / 2, windowsHeight * 1.0 / 2, windowsHeight * 0.97);

		Oangle_1 = pDataEICAS->Oangle_1;
		Oangle_2 = pDataEICAS->Oangle_2;
		Oangle_3 = pDataEICAS->Oangle_3;
		Oangle_4 = pDataEICAS->Oangle_4;
		fanSpeed = pDataEICAS->fanSpeed;
		fanSpeed_1 = pDataEICAS->fanSpeed_1;
		gastemp = pDataEICAS->gastemp;
		gastemp_1 = pDataEICAS->gastemp_1;
		FuelFlowSpeed = pDataEICAS->FuelFlowSpeed;
		FuelFlowSpeed_1 = pDataEICAS->FuelFlowSpeed_1;
		Fuelrest_1 = pDataEICAS->Fuelrest_1;
		Fuelrest_2 = pDataEICAS->Fuelrest_2;
		Fuelrest_3 = pDataEICAS->Fuelrest_3;
		Fuelrest_total = pDataEICAS->Fuelrest_total;
		TAT = pDataEICAS->TAT;
		UPPERangle = pDataEICAS->UPPERangle;



		lock.unlock();
	}


	// 清理
	CloseHandle(hMapFileEICAS);
	UnmapViewOfFile(pDataEICAS);
	UnmapViewOfFile(pDataEICAS0);
	free(mySharedMemoryEICASA);
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



void draw_EICAS(double Oilcenterx, double Oilcentery, double side) {

	setfillcolor(BLACK);
	ege_fillrect(Oilcenterx - side / 1.9, Oilcentery - side / 1.9, 1.1 * side, 1.1 * side);

	settextjustify(CENTER_TEXT, CENTER_TEXT);

	double Ulength = side / 84;
	double R = Ulength * 7.5;
	double linewidth_1 = Ulength / 3;
	double linelength = Ulength * 1.5;


	setlinewidth(linewidth_1);
	setcolor(EGEARGB(0XFF, 0XE0, 0XE0, 0XE0));


	setfillcolor(EGEARGB(0XFF, 0X3A, 0X31, 0X38));

	ege_rectangle(Oilcenterx - Ulength * 29, Oilcentery - Ulength * 32.5, Ulength * 11.5, Ulength * 4);
	ege_rectangle(Oilcenterx - Ulength * 6, Oilcentery - Ulength * 32.5, Ulength * 11.5, Ulength * 4);
	setfont(Ulength * 5, 0, "Calibri");
	LOGFONTA font;
	getfont(&font);
	font.lfHeight = Ulength * 5;
	font.lfWeight = Ulength * 50;
	font.lfQuality = ANTIALIASED_QUALITY;
	setfont(&font);
	char num[64];//左上上
	sprintf_s(num, "%.1f", fanSpeed);
	ege_drawtext(num, Oilcenterx - Ulength * 23.5, Oilcentery - Ulength * 32.5);



	char nums[64];//左上上
	sprintf_s(nums, "%.1f", fanSpeed_1);


	ege_drawtext(nums, Oilcenterx - Ulength * 0.5, Oilcentery - Ulength * 32.5);

	if (fanSpeed_1 <= 101.5 && fanSpeed_1 >= 0) {
		Oangle_3 = fanSpeed_1 / 10 * 19;
	}
	else if (fanSpeed_1 > 101.5) {
		Oangle_3 = 101.5 / 10 * 19;
	}
	else {
		Oangle_3 = 0;
	}



	if (fanSpeed <= 101.5 && fanSpeed >= 0) {
		Oangle_1 = fanSpeed / 10 * 19;
	}
	else if (fanSpeed > 101.5) {
		Oangle_1 = 101.5 / 10 * 19;
	}
	else {
		Oangle_1 = 0;
	}

	if (gastemp < 999) {
		char num_1[64];//左上中
		sprintf_s(num_1, "%.0f", gastemp);
		ege_drawtext(num_1, Oilcenterx - Ulength * 25, Oilcentery - Ulength * 17.5);

	}
	else
	{
		char num_1[64];//左上中
		ege_drawtext("999", Oilcenterx - Ulength * 25, Oilcentery - Ulength * 17.5);

	}

	if (gastemp_1 < 999) {
		char nums_1[64];//左上中
		sprintf_s(nums_1, "%.0f", gastemp_1);

		ege_drawtext(nums_1, Oilcenterx - Ulength * 2, Oilcentery - Ulength * 17.5);
	}
	else
	{
		char nums_1[64];//左上中

		ege_drawtext("999", Oilcenterx - Ulength * 2, Oilcentery - Ulength * 17.5);
	}
	if (gastemp <= 950 && gastemp >= 0) {
		Oangle_2 = gastemp * 198 / 950;
	}
	else if (gastemp > 950) {
		Oangle_2 = 198;
	}
	else {
		Oangle_2 = 0;
	}
	if (gastemp_1 <= 950 && gastemp_1 >= 0) {
		Oangle_4 = gastemp_1 * 198 / 950;
	}
	else if (gastemp_1 > 950) {
		Oangle_4 = 198;
	}
	else {
		Oangle_4 = 0;
	}




	setfont(Ulength * 4, 0, "Calibri");
	getfont(&font);
	font.lfHeight = Ulength * 4.5;
	font.lfWeight = Ulength * 40;
	font.lfQuality = ANTIALIASED_QUALITY;
	setfont(&font);
	if (FuelFlowSpeed < 10) {
		char num_2[64];//左上下左
		sprintf_s(num_2, "%.2f", FuelFlowSpeed);
		ege_drawtext(num_2, Oilcenterx - Ulength * 26.5, Oilcentery + Ulength * 4.7);
	}
	else if (FuelFlowSpeed >= 10) {
		char num_2[64];
		sprintf_s(num_2, "%.1f", FuelFlowSpeed);
		ege_drawtext(num_2, Oilcenterx - Ulength * 26.5, Oilcentery + Ulength * 4.7);
	}
	if (FuelFlowSpeed_1 < 10) {
		char num_7[64];//左上下右
		sprintf_s(num_7, "%.2f", FuelFlowSpeed_1);
		ege_drawtext(num_7, Oilcenterx - Ulength * 3.5, Oilcentery + Ulength * 4.7);
	}
	else if (FuelFlowSpeed_1 >= 10) {
		char num_7[64];//左上下右
		sprintf_s(num_7, "%.1f", FuelFlowSpeed_1);
		ege_drawtext(num_7, Oilcenterx - Ulength * 3.5, Oilcentery + Ulength * 4.7);
	}

	char num12[64];//最上TAT
	sprintf_s(num12, "%d", TAT);
	ege_drawtext(num12, Oilcenterx - Ulength * 23.5, Oilcentery - Ulength * 40.5);

	ege_drawtext("C", Oilcenterx - Ulength * 20.5, Oilcentery - Ulength * 40.5);
	if (fanSpeed > 101) {
		setfillcolor(EGEARGB(0X9F, 0X7F, 0X06, 0X03));
	}
	else {
		setfillcolor(EGEARGB(0XFF, 0X3A, 0X31, 0X38));

	}

	ege_fillpie(Oilcenterx - Ulength * 29 - R, Oilcentery - Ulength * 27.5 - R, 2 * R, 2 * R, 0, Oangle_1);
	ege_fillpie(Oilcenterx - Ulength * 6 - R, Oilcentery - Ulength * 27.5 - R, 2 * R, 2 * R, 0, Oangle_1);

	if (gastemp >= 915 && gastemp < 950) {
		setfillcolor(EGEARGB(0X9F, 0X89, 0X4A, 0X03));
	}
	else if (gastemp >= 950) {
		setfillcolor(EGEARGB(0X9F, 0X7F, 0X06, 0X03));
	}
	else {
		setfillcolor(EGEARGB(0XFF, 0X3A, 0X31, 0X38));;
	}

	ege_fillpie(Oilcenterx - Ulength * 29 - R, Oilcentery - Ulength * 12.5 - R, 2 * R, 2 * R, 0, Oangle_2);
	ege_fillpie(Oilcenterx - Ulength * 6 - R, Oilcentery - Ulength * 12.5 - R, 2 * R, 2 * R, 0, Oangle_2);



	ege_line(Oilcenterx - Ulength * 29 - R * cos((Oangle_1 - 180) * PI / 180), Oilcentery - Ulength * 27.5 - R * sin((Oangle_1 - 180) * PI / 180),
		Oilcenterx - Ulength * 29, Oilcentery - Ulength * 27.5);
	ege_line(Oilcenterx - Ulength * 6 - R * cos((Oangle_1 - 180) * PI / 180), Oilcentery - Ulength * 27.5 - R * sin((Oangle_1 - 180) * PI / 180),
		Oilcenterx - Ulength * 6, Oilcentery - Ulength * 27.5);

	ege_line(Oilcenterx - Ulength * 29 - R * cos((Oangle_2 - 180) * PI / 180), Oilcentery - Ulength * 12.5 - R * sin((Oangle_2 - 180) * PI / 180),
		Oilcenterx - Ulength * 29, Oilcentery - Ulength * 12.5);
	ege_line(Oilcenterx - Ulength * 6 - R * cos((Oangle_2 - 180) * PI / 180), Oilcentery - Ulength * 12.5 - R * sin((Oangle_2 - 180) * PI / 180),
		Oilcenterx - Ulength * 6, Oilcentery - Ulength * 12.5);



	ege_arc(Oilcenterx - Ulength * 29 - R, Oilcentery - Ulength * 27.5 - R, 2 * R, 2 * R, 0, 198);
	ege_arc(Oilcenterx - Ulength * 6 - R, Oilcentery - Ulength * 27.5 - R, 2 * R, 2 * R, 0, 198);
	ege_arc(Oilcenterx - Ulength * 29 - R, Oilcentery - Ulength * 12.5 - R, 2 * R, 2 * R, 0, 198);
	ege_arc(Oilcenterx - Ulength * 6 - R, Oilcentery - Ulength * 12.5 - R, 2 * R, 2 * R, 0, 198);







	for (int i = 10; i >= -180; i -= 19) {
		ege_line(Oilcenterx - Ulength * 29 - R * cos(i * PI / 180), Oilcentery - Ulength * 27.5 - R * sin(i * PI / 180),
			Oilcenterx - Ulength * 29 - (R - linelength) * cos(i * PI / 180), Oilcentery - Ulength * 27.5 - (R - linelength) * sin(i * PI / 180));
	}
	for (int i = 10; i >= -180; i -= 19) {
		ege_line(Oilcenterx - Ulength * 6 - R * cos(i * PI / 180), Oilcentery - Ulength * 27.5 - R * sin(i * PI / 180),
			Oilcenterx - Ulength * 6 - (R - linelength) * cos(i * PI / 180), Oilcentery - Ulength * 27.5 - (R - linelength) * sin(i * PI / 180));
	}



	ege_rectangle(Oilcenterx - Ulength * 29, Oilcentery - Ulength * 17.5, Ulength * 7, Ulength * 4);
	ege_rectangle(Oilcenterx - Ulength * 6, Oilcentery - Ulength * 17.5, Ulength * 7, Ulength * 4);

	ege_rectangle(Oilcenterx - Ulength * 31, Oilcentery + Ulength * 5.5, Ulength * 8.5, Ulength * 3);
	ege_rectangle(Oilcenterx - Ulength * 8, Oilcentery + Ulength * 5.5, Ulength * 8.5, Ulength * 3);

	setcolor(EGEARGB(0XFF, 0X3A, 0X31, 0X38));
	setlinewidth(linewidth_1 * 1.5);
	ege_rectangle(Oilcenterx + Ulength * 8.5, Oilcentery - Ulength * 36, Ulength * 15, Ulength * 5);
	ege_rectangle(Oilcenterx + Ulength * 8.5, Oilcentery - Ulength * 31, Ulength * 15, Ulength * 5);
	ege_rectangle(Oilcenterx + Ulength * 8.5, Oilcentery - Ulength * 26, Ulength * 15, Ulength * 5);

	ege_rectangle(Oilcenterx + Ulength * 25.5, Oilcentery - Ulength * 36, Ulength * 15, Ulength * 5);
	ege_rectangle(Oilcenterx + Ulength * 25.5, Oilcentery - Ulength * 31, Ulength * 15, Ulength * 5);
	ege_rectangle(Oilcenterx + Ulength * 25.5, Oilcentery - Ulength * 26, Ulength * 15, Ulength * 5);

	setfillcolor(EGEARGB(0XFF, 0X2A, 0X21, 0X28));
	ege_fillrect(Oilcenterx + Ulength * 12.5, Oilcentery - Ulength * 38.2, Ulength * 6.5, Ulength * 2.2);
	ege_fillrect(Oilcenterx + Ulength * 29.5, Oilcentery - Ulength * 38.2, Ulength * 6.5, Ulength * 2.2);

	setcolor(EGEARGB(0XFF, 0X17, 0XAF, 0XAB));
	setfont(Ulength * 2.8, 0, "Calibri");
	ege_drawtext("ENG 1", Oilcenterx + Ulength * 16, Oilcentery - Ulength * 39.3);
	ege_drawtext("ENG 2", Oilcenterx + Ulength * 33, Oilcentery - Ulength * 39.3);
	ege_drawtext("TAT", Oilcenterx - Ulength * 34.5, Oilcentery - Ulength * 39.3);

	int pointnum = 22;
	ege_point ploypoint[22] = {
		{Oilcenterx + Ulength * 11 , Oilcentery + Ulength * 28.5},
		{Oilcenterx + Ulength * 11 , Oilcentery + Ulength * 28.5},
		{Oilcenterx + Ulength * 11 , Oilcentery + Ulength * 28.5},
		{Oilcenterx + Ulength * 9 , Oilcentery + Ulength * 28.5},


		{Oilcenterx + Ulength * 8.5 , Oilcentery + Ulength * 28.5},
		{Oilcenterx + Ulength * 7.5 , Oilcentery + Ulength * 29},
		{Oilcenterx + Ulength * 7.5 , Oilcentery + Ulength * 30},


		{Oilcenterx + Ulength * 7.5 , Oilcentery + Ulength * 35.5},
		{Oilcenterx + Ulength * 7.5 , Oilcentery + Ulength * 36.5},
		{Oilcenterx + Ulength * 8.5 , Oilcentery + Ulength * 37},

		{Oilcenterx + Ulength * 9 , Oilcentery + Ulength * 37},
		{Oilcenterx + Ulength * 39 , Oilcentery + Ulength * 37},
		{Oilcenterx + Ulength * 39 , Oilcentery + Ulength * 37},

		{Oilcenterx + Ulength * 40.5 , Oilcentery + Ulength * 37},
		{Oilcenterx + Ulength * 40.5 , Oilcentery + Ulength * 36.5},
		{Oilcenterx + Ulength * 40.5 , Oilcentery + Ulength * 35.5},

		{Oilcenterx + Ulength * 40.5 , Oilcentery + Ulength * 30},
		{Oilcenterx + Ulength * 40.5 , Oilcentery + Ulength * 29},
		{Oilcenterx + Ulength * 39.5 , Oilcentery + Ulength * 28.5},

		{Oilcenterx + Ulength * 39 , Oilcentery + Ulength * 28.5},
		{Oilcenterx + Ulength * 37 , Oilcentery + Ulength * 28.5},
		{Oilcenterx + Ulength * 37 , Oilcentery + Ulength * 28.5},



	};
	setcolor(EGEARGB(0XFF, 0X17, 0XAF, 0XBB));
	setlinewidth(linewidth_1);
	ege_line(Oilcenterx + Ulength * 24, Oilcentery + Ulength * 29, Oilcenterx + Ulength * 22, Oilcentery + Ulength * 29);
	ege_bezier(pointnum, ploypoint);
	setfont(Ulength * 3.5, 0, "Calibri");
	LOGFONTA f;
	getfont(&f);
	f.lfHeight = Ulength * 3.5;
	f.lfWeight = Ulength * 60;
	f.lfWidth = Ulength / 6 * 8;
	f.lfQuality = ANTIALIASED_QUALITY;
	setfont(&f);
	xyprintf(Oilcenterx + Ulength * 16.5, Oilcentery + Ulength * 29, "FUEL QTY");
	xyprintf(Oilcenterx + Ulength * 30.5, Oilcentery + Ulength * 29, "LBS X 1000");
	xyprintf(Oilcenterx + Ulength * 14, Oilcentery + Ulength * 40, "TOTAL");


	xyprintf(Oilcenterx - Ulength * 17, Oilcentery - Ulength * 22, "N1");
	xyprintf(Oilcenterx - Ulength * 17, Oilcentery - Ulength * 7, "EGT");
	xyprintf(Oilcenterx - Ulength * 17, Oilcentery + Ulength * 7, "FF");



	LOGFONTA f1;
	getfont(&f1);
	f1.lfHeight = Ulength * 5.5;
	f1.lfWeight = Ulength * 40;
	f1.lfWidth = 6;
	f1.lfQuality = ANTIALIASED_QUALITY;
	setfont(&f1);
	setcolor(EGEARGB(0XFF, 0XE0, 0XE0, 0XE0));
	char num_3[64];//      1
	sprintf_s(num_3, "%.2f", Fuelrest_1);
	ege_drawtext(num_3, Oilcenterx + Ulength * 13.5, Oilcentery + Ulength * 30.5);

	char num_4[64];//      2
	sprintf_s(num_4, "%.2f", Fuelrest_2);
	ege_drawtext(num_4, Oilcenterx + Ulength * 23, Oilcentery + Ulength * 30.5);

	char num_5[64];//      3
	sprintf_s(num_5, "%.2f", Fuelrest_3);
	ege_drawtext(num_5, Oilcenterx + Ulength * 33, Oilcentery + Ulength * 30.5);

	setfont(Ulength * 6.5, 0, "Calibri");
	char num_6[64];//      
	sprintf_s(num_6, "%.1f", Fuelrest_total);
	ege_drawtext(num_6, Oilcenterx + Ulength * 22.5, Oilcentery + Ulength * 37);


	setcolor(EGEARGB(0XFF, 0X8F, 0X16, 0X13));
	ege_line(Oilcenterx - Ulength * 28.5 - R, Oilcentery - Ulength * 21.75 - R, Oilcenterx - Ulength * 30.5 - R, Oilcentery - Ulength * 22.75 - R);

	ege_line(Oilcenterx - Ulength * 5.5 - R, Oilcentery - Ulength * 21.75 - R, Oilcenterx - Ulength * 7.5 - R, Oilcentery - Ulength * 22.75 - R);

	ege_line(Oilcenterx - Ulength * 28.5 - R, Oilcentery - Ulength * 7 - R, Oilcenterx - Ulength * 30.5 - R, Oilcentery - Ulength * 7.75 - R);

	ege_line(Oilcenterx - Ulength * 5.5 - R, Oilcentery - Ulength * 7 - R, Oilcenterx - Ulength * 7.5 - R, Oilcentery - Ulength * 7.75 - R);

	setcolor(EGEARGB(0XFF, 0X99, 0X5A, 0X13));

	ege_line(Oilcenterx - Ulength * 29 - R, Oilcentery - Ulength * 6.4 - R, Oilcenterx - Ulength * 30 - R, Oilcentery - Ulength * 6.7 - R);

	ege_line(Oilcenterx - Ulength * 6 - R, Oilcentery - Ulength * 6.4 - R, Oilcenterx - Ulength * 7 - R, Oilcentery - Ulength * 6.7 - R);



	setcolor(EGEARGB(0XFF, 0X2F, 0X87, 0X1B));
	ege_line(Oilcenterx - Ulength * 29 - R, Oilcentery - Ulength * 22 - R, Oilcenterx - Ulength * 30 - R, Oilcentery - Ulength * 22.5 - R);
	ege_line(Oilcenterx - Ulength * 30 - R, Oilcentery - Ulength * 22.5 - R, Oilcenterx - Ulength * 31 - R, Oilcentery - Ulength * 24 - R);
	ege_line(Oilcenterx - Ulength * 30 - R, Oilcentery - Ulength * 22.5 - R, Oilcenterx - Ulength * 31.5 - R, Oilcentery - Ulength * 22 - R);

	ege_line(Oilcenterx - Ulength * 6 - R, Oilcentery - Ulength * 22 - R, Oilcenterx - Ulength * 7 - R, Oilcentery - Ulength * 22.5 - R);
	ege_line(Oilcenterx - Ulength * 7 - R, Oilcentery - Ulength * 22.5 - R, Oilcenterx - Ulength * 8 - R, Oilcentery - Ulength * 24 - R);
	ege_line(Oilcenterx - Ulength * 7 - R, Oilcentery - Ulength * 22.5 - R, Oilcenterx - Ulength * 8.5 - R, Oilcentery - Ulength * 22 - R);


	//灯光遮盖效果
	setfillcolor(EGEARGB(255 - (int)UPPERangle, 0x00, 0x00, 0x00));
	ege_fillrect(Oilcenterx - side / 2, Oilcentery - side / 2, side, side);



	//draw_PFD_frame(Oilcenterx, Oilcentery, side);

}

