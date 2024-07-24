#include <windows.h>
#include <stdio.h>
#include <graphics.h>

#include "G_variable.h"
#include "WinStringUtil.h"

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
	
	int egeMapWidth;
	int egeMapHeight;
	
} SharedData;


int show_map() {	
	
	
	
	while(is_run()){
		
		
		
		if(showMap == 1){
			
			lock_guard<std::mutex> lock(g_globalMutex);
			
			WCHAR mySharedMemory[] =  L"Global\\MySharedMemory";
			char* mySharedMemoryA = WideCharToAnsi(mySharedMemory);
			
			WCHAR eventData[] =  L"EventDataAvailable";
			char* eventDataA  = WideCharToAnsi(eventData);
			
			HANDLE hMapFile = NULL;
			HANDLE hEvent = NULL;
			
			hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, mySharedMemoryA);
			
			hEvent = OpenEvent(EVENT_MODIFY_STATE, FALSE, eventDataA);
			
			
			PROCESS_INFORMATION pi;
			STARTUPINFO si;
			
			if(hMapFile == NULL){
				
				// 创建共享内存
				hMapFile = CreateFileMapping(
					INVALID_HANDLE_VALUE,    // 使用系统页文件
					NULL,                    // 默认安全属性
					PAGE_READWRITE,          // 可读可写
					0,                       // 高位大小
					sizeof(SharedData),      // 低位大小
					mySharedMemoryA // 共享内存名称
					);
				
				if (hMapFile == NULL) {
					printf("CreateFileMapping failed (%d).\n", GetLastError());
					return -1;
				}
				
			}
			
			
			if(hEvent == NULL){
				
				//创建事件对象
				hEvent = CreateEvent(
					NULL, 
					FALSE, 
					FALSE,
					eventDataA
					);
				
				if(hEvent == NULL){
					printf("CreateEvent failed (%d).\n",GetLastError());
					return -1;
				}
				
			}
			
			
			
			// 映射共享内存到进程地址空间
			SharedData* pData = (SharedData*)MapViewOfFile(
				hMapFile,               // 共享内存句柄nm
				FILE_MAP_ALL_ACCESS,    // 可读可写
				0,                      // 高位文件偏移
				0,                      // 低位文件偏移
				sizeof(SharedData)      // 要映射的长度
				);
			
			if (pData == NULL) {
				printf("MapViewOfFile failed (%d).\n", GetLastError());
				CloseHandle(hMapFile);
				return -1;
			}
			
			
			// 创建子进程
			if(&pi == NULL)
				ZeroMemory(&pi, sizeof(pi));
			
			if(&si == NULL){
				ZeroMemory(&si, sizeof(si));
				si.cb = sizeof(si);
			}
			
			// Derive subprocess path from main executable location
			WCHAR exeDir[MAX_PATH];
			wcscpy(exeDir, path);
			WCHAR* lastSlash = wcsrchr(exeDir, L'\\');
			if (lastSlash) *(lastSlash + 1) = L'\0';
			WCHAR commandLineW[MAX_PATH];
			swprintf(commandLineW, MAX_PATH, L"%ssubprocess\\Map\\MapTest.exe", exeDir);
			WCHAR currentDirectoryW[] = L".";

			char* commandLineA = WideCharToAnsi(commandLineW);
			char* currentDirectoryA = WideCharToAnsi(currentDirectoryW);
			
			
			if (!CreateProcess(
				NULL,
				commandLineA, // 子进程的路径
				NULL,
				NULL,
				TRUE,
				CREATE_NEW_CONSOLE,
				NULL,
				currentDirectoryA,
				&si,
				&pi
				)) {
				printf("CreateProcess failed (%d).\n", GetLastError());
				CloseHandle(hMapFile);
				UnmapViewOfFile(pData);
				return -1;
			}
			
			
			while(is_run()){
				
				strcpy(pData->mapProvince,mapProvince);
				strcpy(pData->mapCity,mapCity);
				strcpy(pData->mapAdcode,mapAdcode);
				strcpy(pData->mapWeather,mapWeather);
				strcpy(pData->mapTemperature,mapTemperature);
				strcpy(pData->mapWinddirection,mapWinddirection);
				strcpy(pData->mapWindpower,mapWindpower);
				strcpy(pData->mapHumidity,mapHumidity);
				strcpy(pData->mapTownship,mapTownship);
				strcpy(pData->mapStreet,mapStreet);
				
				pData->egeMapHeight = egeHeight;
				pData->egeMapWidth = egeWidth;
//				printf("g:%d ",renewMap);
//				printf("pData:%d \n",pData->renewMap);
				
				//更新共享内存中的数据
				//对renewMap进行特判处理（因为子进程也会修改）
				if(renewMap == 2){
					pData ->renewMap = 2;
					renewMap = 0;
				}
				if(pData->renewMap == 1){
					renewMap = 1;
					pData->renewMap = 0;
				}
				pData->latitude = latitude;
				pData->longitude = longitude;
				pData->rotationangle = rotationangle;
				
				//全部航线
				for(int i = 0; i < fullRoute.size(); i++){
					pData->fullRoute[i] = fullRoute[i];
				}
				
				pData->routeNum = fullRoute.size();
				
				printf("%d",pData->routeNum);
				
				//		pData->fullRoute = fullRoute;//共享内存不能传vector!内存分配机制不同！
				//		printf("%d",pData->renewMap);
				//		printf("%d ",pData->fullRoute.size());
				
//				if(WaitForSingleObject(hEvent,0) == WAIT_OBJECT_0){
//					renewMap  = pData->renewMap ;
//					ResetEvent(hEvent);
//				}
				
				
				if (WaitForSingleObject(pi.hProcess, 0) == WAIT_OBJECT_0) {
					// 子进程已经结束
					showMap = 0;
					break; 
				}
				
			}
			
			
			// 清理
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			
			
			CloseHandle(hEvent);
			
			CloseHandle(hMapFile);
			UnmapViewOfFile(pData);
			
			
			free(mySharedMemoryA);
		}
		
	}
	
	
	
	
	
	return 0;
}




