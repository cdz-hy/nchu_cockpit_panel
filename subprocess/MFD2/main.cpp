#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>
#include <mutex>

typedef struct {
	//放置EICAS2需要接受的数据

	double N21;
	double N22;
	double FF1;
	double FF2;
	double oilPress1;
	double oilPress2;
	double oilTemp1;
	double oilTemp2;
	double oilQTY1;
	double oilQTY2;
	double VIB1;
	double VIB2;

	int egeWidth;
	int egeHeight;

} SharedDataEICAS2;


//函数声明
void draw_EICAS2(double Oilcenterx, double Oilcentery, double side);
char* WideCharToString(const WCHAR* wideStr);

SharedDataEICAS2* pDataEICAS2;

std::mutex mtx;

//放置EICAS2需要接受的数据

double N21;
double N22;
double FF1;
double FF2;
double oilPress1;
double oilPress2;
double oilTemp1;
double oilTemp2;
double oilQTY1;
double oilQTY2;
double VIB1;
double VIB2;

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

	WCHAR mySharedMemoryEICAS2W[] = L"Global\\MySharedMemoryEICAS2";
	char* mySharedMemoryEICAS2A = WideCharToString(mySharedMemoryEICAS2W);

	// 打开共享内存
	HANDLE hMapFileEICAS2 = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,    // 可读可写
		FALSE,                  // 不从继承句柄中映射
		mySharedMemoryEICAS2W // 共享内存名称
	);


	if (hMapFileEICAS2 == NULL) {
		printf("OpenFileMapping failed (%d).\n", GetLastError());
		return -1;
	}

	// 映射共享内存到进程地址空间
	SharedDataEICAS2* pDataEICAS20 = (SharedDataEICAS2*)MapViewOfFile(
		hMapFileEICAS2,               // 共享内存句柄
		FILE_MAP_ALL_ACCESS,    // 可读可写
		0,                      // 高位文件偏移
		0,                      // 低位文件偏移
		sizeof(SharedDataEICAS2)          // 要映射的长度
	);

	if (pDataEICAS20 == NULL) {
		printf("MapViewOfFile failed (%d).\n", GetLastError());
		CloseHandle(hMapFileEICAS2);
		return -1;
	}

	pDataEICAS2 = pDataEICAS20;

	egeWidth = pDataEICAS2->egeWidth;
	egeHeight = pDataEICAS2->egeHeight;

	initgraph(windowsWidth, windowsHeight, INIT_RENDERMANUAL);
	setbkcolor(BLACK);
	setcaption("MFD2");

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

		draw_EICAS2(windowsWidth * 1.0 / 2, windowsHeight * 1.0 / 2, windowsHeight);

		N21 = pDataEICAS2->N21;
		N22 = pDataEICAS2->N22;
		FF1 = pDataEICAS2->FF1;
		FF2 = pDataEICAS2->FF2;
		oilPress1 = pDataEICAS2->oilPress1;
		oilPress2 = pDataEICAS2->oilPress2;
		oilTemp1 = pDataEICAS2->oilTemp1;
		oilTemp2 = pDataEICAS2->oilTemp2;
		oilQTY1 = pDataEICAS2->oilQTY1;
		oilQTY2 = pDataEICAS2->oilQTY2;
		VIB1 = pDataEICAS2->VIB1;
		VIB2 = pDataEICAS2->VIB2;


		lock.unlock();
	}


	// 清理
	CloseHandle(hMapFileEICAS2);
	UnmapViewOfFile(pDataEICAS2);
	UnmapViewOfFile(pDataEICAS20);
	free(mySharedMemoryEICAS2A);
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


void draw_LowerEICAS_frame(double x, double y, double side) {
	setfillcolor(BLACK);
	ege_fillrect(x, y, side * 1254 / 500, side * 1235 / 500);
}

void draw_LowerEICAS_lineFrames(double x, double y, double side) {
	setlinewidth(side * 0.007);
	setcolor(WHITE);

	//第一行两个框
	ege_rectangle(x + 229.0 / 500 * side, y + 94.0 / 500 * side, side * 169.0 / 500, side * 62.0 / 500);
	ege_rectangle(x + 567.0 / 500 * side, y + 94.0 / 500 * side, side * 169.0 / 500, side * 62.0 / 500);

	//第二行两个框
	ege_rectangle(x + 149.0 / 500 * side, y + 350.0 / 500 * side, side * 135.0 / 500, side * 63.0 / 500);
	ege_rectangle(x + 514.0 / 500 * side, y + 350.0 / 500 * side, side * 135.0 / 500, side * 63.0 / 500);

	//第三行两个框
	ege_rectangle(x + 202.0 / 500 * side, y + 503.0 / 500 * side, side * 85.0 / 500, side * 55.0 / 500);
	ege_rectangle(x + 514.0 / 500 * side, y + 503.0 / 500 * side, side * 85.0 / 500, side * 55.0 / 500);

	//第四行两个框
	ege_rectangle(x + 202.0 / 500 * side, y + 747.0 / 500 * side, side * 85.0 / 500, side * 55.0 / 500);
	ege_rectangle(x + 514.0 / 500 * side, y + 747.0 / 500 * side, side * 85.0 / 500, side * 55.0 / 500);

	//第五行两个框
	ege_rectangle(x + 222.0 / 500 * side, y + 878.0 / 500 * side, side * 63.0 / 500, side * 56.0 / 500);
	ege_rectangle(x + 515.0 / 500 * side, y + 878.0 / 500 * side, side * 63.0 / 500, side * 56.0 / 500);

	//第六行两个框
	ege_rectangle(x + 202.0 / 500 * side, y + 1043.0 / 500 * side, side * 86.0 / 500, side * 56.0 / 500);
	ege_rectangle(x + 516.0 / 500 * side, y + 1043.0 / 500 * side, side * 86.0 / 500, side * 56.0 / 500);


}

void draw_LowerEICAS_lines(double x, double y, double side) {
	//绘制第一组橙色小横线
	setcolor(EGEARGB(255, 0X85, 0X49, 0X06));
	ege_line(x + side * 305.0 / 500, y + side * 585.0 / 500, x + side * 313.0 / 500, y + side * 585.0 / 500);
	ege_line(x + side * 488.0 / 500, y + side * 585.0 / 500, x + side * 496.0 / 500, y + side * 585.0 / 500);

	//绘制第二组橙色小横线；
	ege_line(x + side * 306.0 / 500, y + side * 706.0 / 500, x + side * 313.0 / 500, y + side * 706.0 / 500);
	ege_line(x + side * 489.0 / 500, y + side * 706.0 / 500, x + side * 496.0 / 500, y + side * 706.0 / 500);

	//第一组竖线
	setcolor(WHITE);
	ege_line(x + side * 306.0 / 500, y + side * 456.0 / 500, x + side * 306.0 / 500, y + side * 599.0 / 500);
	ege_line(x + side * 496.0 / 500, y + side * 456.0 / 500, x + side * 496.0 / 500, y + side * 599.0 / 500);

	//第二组竖线
	ege_line(x + side * 306.0 / 500, y + side * 698.0 / 500, x + side * 306.0 / 500, y + side * 840.0 / 500);
	ege_line(x + side * 497.0 / 500, y + side * 698.0 / 500, x + side * 497.0 / 500, y + side * 840.0 / 500);

	//第三组竖线
	ege_line(x + side * 306.0 / 500, y + side * 998.0 / 500, x + side * 306.0 / 500, y + side * 1147.0 / 500);
	ege_line(x + side * 497.0 / 500, y + side * 998.0 / 500, x + side * 497.0 / 500, y + side * 1147.0 / 500);

	//一组白色横线
	ege_line(x + side * 306.0 / 500, y + side * 1028.0 / 500, x + side * 315.0 / 500, y + side * 1028.0 / 500);
	ege_line(x + side * 488.0 / 500, y + side * 1028.0 / 500, x + side * 497.0 / 500, y + side * 1028.0 / 500);

	//绘制第一组红色小横线
	setcolor(RED);
	ege_line(x + side * 295.0 / 500, y + side * 599.0 / 500, x + side * 323.0 / 500, y + side * 599.0 / 500);
	ege_line(x + side * 478.0 / 500, y + side * 599.0 / 500, x + side * 507.0 / 500, y + side * 599.0 / 500);

	//绘制第二组红色小横线
	ege_line(x + side * 295.0 / 500, y + side * 696.0 / 500, x + side * 323.0 / 500, y + side * 696.0 / 500);
	ege_line(x + side * 478.0 / 500, y + side * 696.0 / 500, x + side * 507.0 / 500, y + side * 696.0 / 500);

	//绘制最上方的红色线段；
	ege_line(x + side * 113.0 / 500, y + side * 100.0 / 500, x + side * 134.0 / 500, y + side * 112.0 / 500);
	ege_line(x + side * 450.0 / 500, y + side * 100.0 / 500, x + side * 472.0 / 500, y + side * 112.0 / 500);
}

void draw_LowerEICAS_arc(double x, double y, double side) {
	setcolor(WHITE);
	//绘制两个圆弧
	ege_arc(x + 229.0 / 500 * side - 112.0 / 500 * side, y + 169.0 / 500 * side - 112.0 / 500 * side, side * 224.0 / 500, side * 224.0 / 500, 0, 210);
	ege_arc(x + 567.0 / 500 * side - 112.0 / 500 * side, y + 169.0 / 500 * side - 112.0 / 500 * side, side * 224.0 / 500, side * 224.0 / 500, 0, 210);

}
void draw_LowerEICAS_arcIn(double x, double y, double side) {
	setfillcolor(EGEARGB(255, 0X27, 0X22, 0X29));
	setcolor(BLACK);
	sector(x + side * 229.0 / 500, y + side * 169 / 500, -N21 * 2 - 2, 0, 112 * side / 500, 112 * side / 500);
	sector(x + side * 567.0 / 500, y + side * 169 / 500, -N22 * 2 - 2, 0, 112 * side / 500, 112 * side / 500);
}
void draw_LowerEICAS_pointer(double x, double y, double side) {
	side = side / 500;
	double r = 112 * side;
	ege_line(x + side * 229.0, y + side * 169, x + side * 229 + r * cos(N21 * 2 * PI / 180), y + side * 169 + r * sin(N21 * 2 * PI / 180));
	ege_line(x + side * 567.0, y + side * 169, x + side * 567 + r * cos(N22 * 2 * PI / 180), y + side * 169 + r * sin(N22 * 2 * PI / 180));
}

void draw_LowerEICAS_words(double x, double y, double side) {
	//绘制N2
	setbkmode(true);
	side = side / 500;
	double number_height = 25 * side * 2.2;
	double number_width = 13 * side * 2.0;
	setcolor(EGEARGB(255, 0X3B, 0X82, 0X8F));
	setfont(number_height, number_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	outtextxy(x + side * 379, y + side * 255, 'N');
	outtextxy(x + side * 410, y + side * 268, '2');

	//绘制FF
	ege_drawtext("FF", x + 374 * side, y + 331 * side);

	//绘制OIL
	ege_drawtext("OIL", x + 374 * side, y + 462 * side);

	//绘制PRESS
	ege_drawtext("PRESS", x + 374 * side, y + 497 * side);

	//绘制OIL
	ege_drawtext("OIL", x + 374 * side, y + 702 * side);

	//绘制TEMP
	ege_drawtext("TEMP", x + 374 * side, y + 735 * side);

	//绘制OIL
	ege_drawtext("OIL", x + 340 * side, y + 854 * side);

	//绘制QTY
	ege_drawtext("QTY", x + 411 * side, y + 854 * side);

	//绘制OIL
	ege_drawtext("VIB", x + 374 * side, y + 1022 * side);
}
void draw_LowerEICAS_numbers(double x, double y, double side) {
	side = side / 500;
	double number_height = 25 * side * 2.2 * 1.5;
	double number_width = 13 * side * 2.0 * 1.5;
	setfont(number_height, number_width, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体

	setcolor(WHITE);
	char N21num[64];
	char N22num[64];
	sprintf_s(N21num, "%.1lf", N21);
	sprintf_s(N22num, "%.1lf", N22);
	//绘制N1
	if (N21 < 100) {
		ege_drawtext(N21num, x + side * 309, y + side * 77);
	}
	else {
		ege_drawtext(N21num, x + side * 290, y + side * 77);
	}
	if (N21 < 100) {
		ege_drawtext(N22num, x + side * 645, y + side * 77);
	}
	else {
		ege_drawtext(N22num, x + side * 626, y + side * 77);
	}

	//绘制FF
	char FF1num[64];
	char FF2num[64];
	sprintf_s(FF1num, "%.2lf", FF1);
	sprintf_s(FF2num, "%.2lf", FF2);
	ege_drawtext(FF1num, x + side * 191, y + side * 334);
	ege_drawtext(FF2num, x + side * 559, y + side * 334);

	//绘制oil temp
	char oiltempNum1[64];
	char oiltempNum2[64];

	sprintf_s(oiltempNum1, "%.0lf", oilTemp1);
	sprintf_s(oiltempNum2, "%.0lf", oilTemp2);

	if (oilTemp1 < 100) {
		ege_drawtext(oiltempNum1, x + side * 231, y + side * 726);
	}
	else {
		ege_drawtext(oiltempNum2, x + side * 217, y + side * 726);
	}
	if (oilTemp2 < 100) {
		ege_drawtext(oiltempNum2, x + side * 539, y + side * 726);
	}
	else {
		ege_drawtext(oiltempNum2, x + side * 530, y + side * 726);
	}

	//绘制OILQTY
	char oilqtyNum1[64];
	char oilqtyNum2[64];

	sprintf_s(oilqtyNum1, "%.0lf", oilQTY1);
	sprintf_s(oilqtyNum2, "%.0lf", oilQTY2);

	ege_drawtext(oilqtyNum1, x + side * 229, y + side * 859);
	ege_drawtext(oilqtyNum2, x + side * 522, y + side * 859);

	//绘制VIB
	char VIBNum1[64];
	char VIBNum2[64];

	sprintf_s(VIBNum1, "%.1lf", VIB1);
	sprintf_s(VIBNum2, "%.1lf", VIB2);

	ege_drawtext(VIBNum1, x + side * 219, y + side * 1024);
	ege_drawtext(VIBNum2, x + side * 534, y + side * 1024);

	//绘制OILPRESS
	char oilPRESSNum1[64];
	char oilPRESSNum2[64];

	sprintf_s(oilPRESSNum1, "%.0lf", oilPress1);
	sprintf_s(oilPRESSNum2, "%.0lf", oilPress2);
	if (oilPress1 >= 29) {
		ege_drawtext(oilPRESSNum1, x + side * 218.5, y + side * 479.5);
	}
	if (oilPress2 >= 29) {
		ege_drawtext(oilPRESSNum2, x + side * 530.5, y + side * 479.5);
	}

}

void draw_EICAS2(double x, double y, double side) {

	side /= 2.35;

	x = x - side * 1254 / 500 / 2;
	y = y - side * 1235 / 500 / 2;
	ege_enable_aa(true);
	draw_LowerEICAS_frame(x, y, side);//底框
	draw_LowerEICAS_lineFrames(x, y, side);//绘制矩形线框
	draw_LowerEICAS_lines(x, y, side);//绘制直线
	draw_LowerEICAS_arcIn(x, y, side);//绘制阴影区域
	draw_LowerEICAS_arc(x, y, side);//绘制圆弧
	draw_LowerEICAS_pointer(x, y, side);//绘制指针
	draw_LowerEICAS_words(x, y, side);//绘制所有的英文字母
	draw_LowerEICAS_numbers(x, y, side);//绘制所有的数字
}
