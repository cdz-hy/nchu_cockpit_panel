#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>
#include <ctype.h>
#include <wchar.h>
#include <string.h>

char left1_9[15] = {};//{"WMKPWSSS.f"};//{ "CDY11D" };
char left2_9[15] = {};//{"ZSCNZJHK.f"};//{ "CDY11D" };
char left3_9[15] = {};//{ "WMKPWSSS.f" };//{ "CDY11D" };
char left4_9[15] = {};//{ "WMKPWSSS.f" };//{ "CDY11D" };

char right1_9[15] = {};//{"ZSCNZJHK.f"};//{ "RW01" };
char right2_9[15] = {};//{ "ZSCNZJHK.f" };//{ "RW18L" };
char right3_9[15] = {};//{ "ZSCNZJHK.f" };//{ "RW18R" };
char right4_9[15] = {};//{ "ZSCNZJHK.f" };//{ "RW19" };
char input_9[64] = {};//{"ZBAA"};

void draw_frame_9(double side, double center_x, double center_y) {
	double width = side * 650 / 685;
	double height = side * 540 / 685;
	double x = center_x - width / 2;
	double y = center_y - height / 2;
	setfillcolor(BLACK);
	ege_fillrect(x, y, width, height);
}

void draw_topic_9(double side, double center_x, double center_y) {
	double single = side / 67.0 * 5.7;
	double height = side * 0.035 * 2;
	double wide = side * 0.035 * 2;
	double x = center_x - single * 2.5;
	double y = center_y - side * 210 / 685;
	setcolor(EGEARGB(255, 32, 220, 224));
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	ege_drawtext("CO ROUTE LIST", x, y);

	x = center_x + side * 0.3;
	ege_drawtext("1/1", x, y);
}

void draw_line1_upper_9(double side, double center_x, double center_y) {
	double single = side / 67.0 * 5.7;
	double height = side * 0.035 * 2 / 2;
	double wide = side * 0.035 * 2 / 2;
	double x = center_x - single * 3.5;
	double y = center_y - side * 210 / 685 + single * 0.7;
	setcolor(EGEARGB(255, 32, 220, 224));
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	ege_drawtext("L O A D   P L A N", x, y);
	x += single * 7;
	ege_drawtext("L O A D   P L A N", x, y);

}

void draw_line1_9(double side, double center_x, double center_y) {
	setcolor(WHITE);
	setbkmode(true);
	double single = side / 67.0;

	double height = side * 0.035 * 1.5;
	double wide = side * 0.035 * 1.5;
	double y = center_y - single * 14.6;
	double x = center_x - single * 18;
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	if (strlen(left1_9) != 0) {
		ege_drawtext("<", center_x - single * 27.3, y);
		ege_drawtext(left1_9, x, y);
	}
	if (strlen(right1_9) != 0) {
		ege_drawtext(">", center_x + single * 27.3, y);
		ege_drawtext(right1_9, center_x + single * 19, y);
	}
}


void draw_line2_9(double side, double center_x, double center_y) {
	setcolor(WHITE);
	double single = side / 67.0;
	double height = side * 0.035 * 1.5;
	double wide = side * 0.035 * 1.5;
	double y = center_y - single * 7.6;
	double x = center_x - single * 18;

	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	if (strlen(left2_9) != 0) {
		ege_drawtext("<", center_x - single * 27.3, y);
		ege_drawtext(left2_9, x, y);
	}
	if (strlen(right2_9) != 0) {
		ege_drawtext(">", center_x + single * 27.3, y);
		ege_drawtext(right2_9, center_x + single * 19, y);
	}
}

void draw_line3_9(double side, double center_x, double center_y) {
	setcolor(WHITE);
	double single = side / 67.0;

	double height = side * 0.035 * 1.5;
	double wide = side * 0.035 * 1.5;
	double y = center_y - single * 0.7;
	double x = center_x - single * 18;
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);

	if (strlen(left3_9) != 0) {
		ege_drawtext("<", center_x - single * 27.3, y);
		ege_drawtext(left3_9, x, y);
	}
	if (strlen(right3_9) != 0) {
		ege_drawtext(">", center_x + single * 27.3, y);
		ege_drawtext(right3_9, center_x + single * 19, y);
	}
}

void draw_line4_9(double side, double center_x, double center_y) {
	setcolor(WHITE);
	double single = side / 67.0;
	double y = center_y + single * 6.3;
	double x = center_x - single * 18;
	double height = side * 0.035 * 1.5;
	double wide = side * 0.035 * 1.5;
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);

	if (strlen(left4_9) != 0) {
		ege_drawtext("<", center_x - single * 27.3, y);
		ege_drawtext(left4_9, x, y);
	}
	if (strlen(right4_9) != 0) {
		ege_drawtext(">", center_x + single * 27.3, y);
		ege_drawtext(right4_9, center_x + single * 19, y);
	}
}

void draw_line5_upper_9(double side, double center_x, double center_y) {
	double single = side / 67.0 * 5.7;
	double height = side * 0.035 * 2 / 2;
	double wide = side * 0.035 * 2 / 2;
	double x = center_x;
	double y = center_y + single * 1.7;
	setcolor(EGEARGB(255, 32, 220, 224));
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	ege_drawtext("——————————————————————————————————", x, y);
}

void draw_line5_9(double side, double center_x, double center_y) {
	setcolor(WHITE);
	double single = side / 67.0;
	double y = center_y + single * 13.2;
	double x = center_x - single * 23.5;
	double height = side * 0.035 * 1.5;
	double wide = side * 0.035 * 1.5;

	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);

	ege_drawtext("<FPLN", x, y);
	x = center_x + single * 18;
	ege_drawtext("ROUTE MENU>", x, y);
}

void draw_line6_upper_9(double side, double center_x, double center_y) {
	double single = side / 67.0 * 5.7;
	double height = side * 0.035 * 2 / 2;
	double wide = side * 0.035 * 2 / 2;
	double x = center_x - single * 3.5;
	double y = center_y + single * 3;
	setcolor(EGEARGB(255, 32, 220, 224));
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	ege_drawtext("A C T   S T O R E", x, y);
}

void draw_line6_9(double side, double center_x, double center_y) {
	setcolor(WHITE);
	double single = side / 67.0;
	double y = center_y + single * 20.2;
	double x = center_x - single * 20;
	double height = side * 0.035 * 1.5;
	double wide = side * 0.035 * 1.5;

	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);

	ege_drawtext("<——————", x, y);
}

void draw_input_9Box_9(double side, double center_x, double center_y) {
	setlinewidth(side * 0.0005);
	double single = side / 67.0;
	setcolor(EGEARGB(255, 32, 220, 224));
	double y = center_y + single * 23.3;
	double x1 = center_x - single * 29;
	double x2 = center_x + single * 29;
	double height = side * 0.035 * 1.8;
	double wide = side * 0.035 * 1.8;
	setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
	LOGFONTW FMC_font;
	getfont(&FMC_font);
	FMC_font.lfWeight = side * 3;
	setfont(&FMC_font);
	ege_drawtext("[", x1, y);
	ege_drawtext("]", x2, y);

	setcolor(WHITE);
	//绘制输入框的输入值
	if (!strlen(input_9) == 0) {
		height = side * 0.035 * 1.8 * 0.8;
		wide = side * 0.035 * 1.8 / 2;
		setfont(height, wide, "Calibri", 0, 0, 0, 0, 0, 0);//设定字体
		y = y - height / 2;
		for (int i = 0; i < strlen(input_9); i++) {
			outtextxy(x1 + single * 0.2 + wide * i, y, input_9[i]);
		}
	}
}


char* WideCharToString1(const WCHAR* wideStr) {
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

void fileopen()
{
	
	WIN32_FIND_DATAW findFileData; // 使用宽字符版本的结构体
	HANDLE hFind;
	LPCWSTR lpFileName = L"*.*"; // 使用LPCWSTR明确为宽字符字符串
	
	hFind = FindFirstFileW(lpFileName, &findFileData); // 使用宽字符版本的API
	
	if (hFind == INVALID_HANDLE_VALUE) {
		printf("Failed to find files in folder\n");
		return;
	}
	
	const int MAX_FILES = 100;
	wchar_t fileNames[MAX_FILES][MAX_PATH];
	
	int fileCount = 0;
	
	do {
		if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			wchar_t* extension = wcsrchr(findFileData.cFileName, L'.');
			if (extension != NULL && wcscmp(extension, L".fms") == 0) {
				wcscpy(fileNames[fileCount], findFileData.cFileName);
				fileCount++;
				if (fileCount == MAX_FILES) {
					printf("Exceeded maximum number of files\n");
					break;
				}
			}
		}
	} while (FindNextFileW(hFind, &findFileData) != 0);
	
	FindClose(hFind);
		

	// 输出存储的文件名
	for (int i = 0; i < fileCount; i++) {
		wprintf(L"%s\n", fileNames[i]);
	}

	for (int i = 0; i < fileCount; i++)
	{
		if (i == 0)
		{
			WideCharToMultiByte(CP_ACP, 0, fileNames[i], -1, left1_9, MAX_PATH, NULL, NULL);
		}
		else if (i == 1)
		{
			WideCharToMultiByte(CP_ACP, 0, fileNames[i], -1, right1_9, MAX_PATH, NULL, NULL);
		}
		else if (i == 2)
		{
			WideCharToMultiByte(CP_ACP, 0, fileNames[i], -1, left2_9, MAX_PATH, NULL, NULL);
		}
		else if (i == 3)
		{
			WideCharToMultiByte(CP_ACP, 0, fileNames[i], -1, right2_9, MAX_PATH, NULL, NULL);
		}
		else if (i == 4)
		{
			WideCharToMultiByte(CP_ACP, 0, fileNames[i], -1, left3_9, MAX_PATH, NULL, NULL);
		}
		else if (i == 5)
		{
			WideCharToMultiByte(CP_ACP, 0, fileNames[i], -1, right3_9, MAX_PATH, NULL, NULL);
		}
		else if (i == 6)
		{
			WideCharToMultiByte(CP_ACP, 0, fileNames[i], -1, left4_9, MAX_PATH, NULL, NULL);
		}
		else if (i == 7)
		{
			WideCharToMultiByte(CP_ACP, 0, fileNames[i], -1, right4_9, MAX_PATH, NULL, NULL);
		}
	}
}

char* getinformation_9(int site)
{
	if (site == 1)
	{
		return left1_9;
	}
	else if (site == 2)
	{
		return right1_9;
	}
	else if (site == 3)
	{
		return left2_9;
	}
	else if (site == 4)
	{
		return right2_9;
	}
	else if (site == 5)
	{
		return left3_9;
	}
	else if (site == 6)
	{
		return right3_9;
	}
	else if (site == 7)
	{
		return left4_9;
	}
	else if (site == 8)
	{
		return right4_9;
	}
	
	
}

void draw_CO_ROUTE_LIST(double side, double center_x, double center_y) {
	draw_frame_9(side, center_x, center_y);
	draw_topic_9(side, center_x, center_y);
	draw_line1_upper_9(side, center_x, center_y);
	draw_line1_9(side, center_x, center_y);

	draw_line2_9(side, center_x, center_y);

	draw_line3_9(side, center_x, center_y);

	draw_line4_9(side, center_x, center_y);

	draw_line5_9(side, center_x, center_y);
	draw_line5_upper_9(side, center_x, center_y);
	draw_line6_upper_9(side, center_x, center_y);
	draw_line6_9(side, center_x, center_y);
	draw_input_9Box_9(side, center_x, center_y);
	fileopen();
}
