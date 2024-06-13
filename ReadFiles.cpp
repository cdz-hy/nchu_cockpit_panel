//引用头文件
#include <windows.h>
#include <math.h>
#include <cstdio>
#include <fstream>
#include <string>
#include <regex>
#include <iostream>
using namespace std;

#include "G_variable.h"


void read_files(){
	
	
	//读取配置文件
	regex pattern_height(R"(Window Height = [0-9]+)");
	regex pattern_length(R"(Window Length = [0-9]+)");
	
	char tmp[0xFF];
	FILE *file = fopen("Panels simulation.ini", "r");
	
	if (file != NULL) {
		while (!feof(file)) {
			fgets(tmp, 0xFF, file);
			char *p = NULL;
//			//窗口长
//			if (strstr(tmp, "Length")) {
//				p = strstr(tmp, "=");
//				p += 2;
//				length = stoi(p);
//			}
//			//窗口高（宽）
//			else if (strstr(tmp, "Height")) {
//				p = strstr(tmp, "=");
//				p += 2;
//				height = stoi(p);
//			}
			//是否显示背景等
			/*else */if (strstr(tmp, "Show Background")) {
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
	
	
	//获取设备上下文获取屏幕分辨率
	HDC screenHDC = GetDC(NULL);
	if(screenHDC == NULL){
		
	}
	else{
		length = GetDeviceCaps(screenHDC, HORZRES);
		height = GetDeviceCaps(screenHDC, VERTRES);
	}
	
	ReleaseDC(NULL, screenHDC); // 释放设备上下文
	
	
	
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
			wpTmp.range = 130;
			
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
				else if(stringTmp[1].length() == 4){
					wpTmp.num = 3;//airport
				}
				
				route.push_back(wpTmp);
				
			}
			else{
				continue;
			}
			
		}
	}
	
	inputFile2.close();
	
	
	
	//读取机场文件
	
//	extern vector<WAYPOINT> airports;
//	ifstream inputFile3("arpt_data.dat");
//	
//	if (inputFile3.is_open()) {
//		while (getline(inputFile3,inputTmp)) {
//			
//			WAYPOINT wpTmp;
//			istringstream issTmp(inputTmp);
//			
//			string stringTmp[20];
//			
////			if(issTmp >> stringTmp[0] >> wpTmp.lat >> wpTmp.lon >> stringTmp[1] >> stringTmp[2] >> stringTmp[3] >> stringTmp[4] >> stringTmp[5] >> stringTmp[6] >> stringTmp[7] >> stringTmp[8] >> stringTmp[9] >> stringTmp[10]){
////				
////				
////				
////				strcpy(wpTmp.code, stringTmp[0].c_str());
////				strcpy(wpTmp.name, stringTmp[6].c_str());
////				strcpy(wpTmp.fullName, stringTmp[6].c_str());
////				
//////				wpTmp.num = 3;
////				
////				airports.push_back(wpTmp);
////				
////			}
//			if(issTmp >> stringTmp[0] >> wpTmp.lat >> wpTmp.lon >> stringTmp[1] >> stringTmp[2] >> stringTmp[3] >> stringTmp[4] >> stringTmp[5] >> stringTmp[6] >> stringTmp[7] >> stringTmp[8] >> stringTmp[9]){
//				
//				strcpy(wpTmp.code, stringTmp[0].c_str());
//				strcpy(wpTmp.name, stringTmp[6].c_str());
//				strcpy(wpTmp.fullName, stringTmp[6].c_str());
//				
//				wpTmp.num = 3;
//				
//				airports.push_back(wpTmp);
//				
//			}
//			else{
//				continue;
//			}
//			
//		}
//	}
//	
//	inputFile3.close();
	
	extern vector<WAYPOINT> airports;
	FILE* file1;
	int linenum = 1;
	char line[1024];
	
	// 打开文件，以只读模式（"r"）  
	file1 = fopen("arpt.dat", "r");
	if (file1 == NULL) {
		// 如果文件打开失败，打印错误消息  
		perror("Error opening file");
		return; // 如果文件打开失败，返回并退出程序  
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
		linenum ++;
	}
	// 关闭文件  
	fclose(file1);

	
	
	
	//读取VOR塔台文件
	
	extern vector<WAYPOINT> VORs;
	ifstream inputFile4("nav_data.dat");
	
	if (inputFile4.is_open()) {
		while (getline(inputFile4,inputTmp)) {
			
			WAYPOINT wpTmp;
			istringstream issTmp(inputTmp);
			
			string stringTmp[20];
			
			if(issTmp >> stringTmp[0] >> wpTmp.lat >> wpTmp.lon >> stringTmp[1] >> stringTmp[2] >> wpTmp.range >> stringTmp[4] >> stringTmp[5] >> stringTmp[6] >> stringTmp[7] >> stringTmp[8] >> stringTmp[9]){
				
				strcpy(wpTmp.code, stringTmp[0].c_str());
				strcpy(wpTmp.name, stringTmp[6].c_str());
				strcpy(wpTmp.fullName, stringTmp[6].c_str());
				
				wpTmp.num = 3;
				
				VORs.push_back(wpTmp);
				
			}
			else{
				continue;
			}
			
		}
	}
	
	inputFile4.close();
	
	
	
	
//	extern vector<WAYPOINT> routePassed;
//	WAYPOINT wpTmp2 = {0,"ZSCN", 28.877, 115.91, "ZSCN", "ZSCN", "ZSCN", 100, "ZSCN", "ZSCN"};
//	routePassed.push_back(wpTmp2);
	
}


