#include <windows.h>
#include <stdio.h>
#include <graphics.h>
#include <mutex>

std::mutex mx;
#include "G_variable.h"
#include "WinStringUtil.h"
typedef struct {
	//放置pfd所需要传送的数据
	
	char FMCFileName[20];
	
	int egeFMCWidth;
	int egeFMCHeight;
	
	int MainPanelLight;
	
	int ceshi;
	
	char FMC_routepoints[12][7];
} SharedDataFMC;

int ceshi;

char FMC_routepoints1[12][7];
char FMC_routepoints2[12][7];

int show_fmc() {
	
	while (is_run()) {
		
		if (showFMCJudge == 1) {
			WCHAR mySharedMemoryFMCW[] =  L"Global\\MySharedMemoryFMC";
			char* mySharedMemoryFMCA = WideCharToAnsi(mySharedMemoryFMCW);
			
			
			// 创建共享内存
			HANDLE hMapFileFMC = CreateFileMapping(
				INVALID_HANDLE_VALUE,    // 使用系统页文件
				NULL,                    // 默认安全属性
				PAGE_READWRITE,          // 可读可写
				0,                       // 高位大小
				sizeof(SharedDataFMC),          // 低位大小
				mySharedMemoryFMCA // 共享内存名称
				);
			
			if (hMapFileFMC == NULL) {
				printf("CreateFileMapping failed (%d).\n", GetLastError());
				return -1;
			}
			
			// 映射共享内存到进程地址空间
			SharedDataFMC* pDataFMC = (SharedDataFMC*)MapViewOfFile(
				hMapFileFMC,               // 共享内存句柄
				FILE_MAP_ALL_ACCESS,    // 可读可写
				0,                      // 高位文件偏移
				0,                      // 低位文件偏移
				sizeof(SharedDataFMC)          // 要映射的长度
				);
			
			if (pDataFMC == NULL) {
				printf("MapViewOfFile failed (%d).\n", GetLastError());
				CloseHandle(hMapFileFMC);
				return -1;
			}
//			
//			WCHAR eventDataFMC[] =  L"EventDataFMCAvailable";
//			char* eventDataFMCA  = WideCharToStringFMC(eventDataFMC);
//			
//			//创建事件对象
//			HANDLE hEventFMC = CreateEvent(
//				NULL, 
//				FALSE, 
//				FALSE, 
//				eventDataFMCA
//				);
//			
//			if(hEventFMC == NULL){
//				printf("CreateEvent failed (%d).\n",GetLastError());
//				return -1;
//			}
//			
			
			// 创建子进程
			PROCESS_INFORMATION pi;
			ZeroMemory(&pi, sizeof(pi));
			
			STARTUPINFO si;
			ZeroMemory(&si, sizeof(si));
			si.cb = sizeof(si);
			
			// Derive subprocess path from main executable location
			WCHAR exeDir[MAX_PATH];
			wcscpy(exeDir, path);
			WCHAR* lastSlash = wcsrchr(exeDir, L'\\');
			if (lastSlash) *(lastSlash + 1) = L'\0';
			WCHAR commandLineFMCW[MAX_PATH];
			swprintf(commandLineFMCW, MAX_PATH, L"%ssubprocess\\FMC\\FMC.exe", exeDir);
			WCHAR currentDirectoryFMCW[] = L".";

			char* commandLineFMCA = WideCharToAnsi(commandLineFMCW);
			char* currentDirectoryFMCA = WideCharToAnsi(currentDirectoryFMCW);
			
			
			if (!CreateProcess(
				NULL,
				commandLineFMCA, // 子进程的路径
				NULL,
				NULL,
				TRUE,
				CREATE_NEW_CONSOLE,
				NULL,
				currentDirectoryFMCA,
				&si,
				&pi
				)) {
				printf("CreateProcess failed (%d).\n", GetLastError());
				CloseHandle(hMapFileFMC);
				UnmapViewOfFile(pDataFMC);
				return -1;
			}
			
			while (is_run()) {
				
				pDataFMC ->egeFMCHeight = egeFMCHeight;
				pDataFMC ->egeFMCWidth = egeFMCWidth;
				pDataFMC ->MainPanelLight = MainPanelLight;
				
				mx.lock();
				int judge = 1;
				
				for (int i = 0; i < 12; ++i) {
					for (int j = 0; j < 7; ++j) {
						if (FMC_routepoints1[i][j] != pDataFMC->FMC_routepoints[i][j]) {
							judge = 0; 
							break;
						}
					}
					if (judge == 0) {
						break;
					}
				}
				
				
				extern vector<WAYPOINT> route;
				
				//2才是你最终想得到的数据
				
				if(judge == 0){
					
					for (int i = 0; i < 12; ++i) {
						for (int j = 0; j < 7; ++j) {
							FMC_routepoints2[i][j] = pDataFMC->FMC_routepoints[i][j];
						}
					}
					
					for (int i = 0; i < 12; ++i) {
						for (int j = 0; j < 7; ++j) {
							FMC_routepoints1[i][j] = pDataFMC->FMC_routepoints[i][j];
						}
					}
					
					
					route.clear();
					
					for(int i = 0;i < 12;i ++){
						if(strlen(FMC_routepoints2[i]) > 2){
							
							for(auto it : airports){
								if(!strcmp(it.name, FMC_routepoints2[i])){
									route.push_back(it);
									break;
								}
							}
							
							for(auto it : VORs){
								if(!strcmp(it.name, FMC_routepoints2[i])){
									route.push_back(it);
									break;
								}
							}
							
							for(auto it : waypoints){
								if(!strcmp(it.name, FMC_routepoints2[i])){
									route.push_back(it);
									break;
								}
							}
							
						}
					}
					
					
					
					
					
					
				}
				
//				if(pDataFMC ->FMCFileName!=NULL)
//				{
				
				
				if(FMCFileName!=NULL&&strlen(pDataFMC->FMCFileName)!=NULL&&strcmp(pDataFMC->FMCFileName,FMCFileName))
					strcpy(FMCFileName,pDataFMC->FMCFileName);
//				}			
				
				strcpy(pDataFMC->FMCFileName,"");
//				strcpy(FMCFileName,"");
				
				mx.unlock();
//				ceshi = pDataFMC->ceshi;
//				printf("%d\n\n\n\n",ceshi);
				
//				if(WaitForSingleObject(hEventFMC,0) == WAIT_OBJECT_0){
//					
//					FMCFileName[20] = pDataFMC-> FMCFileName[20];
//					
//					ResetEvent(hEventFMC);
//				}
				
				if (WaitForSingleObject(pi.hProcess, 0) == WAIT_OBJECT_0) {
					// 子进程已经结束
					showFMCJudge = 0;
					break;
				}
//				printf("airSpeed :%lf\n\n\n\n\n",airSpeed);
//				printf("pDatapfd-> airSpeed ::%lf\n\n\n\n\n\n\n",pDataPFD ->airSpeed);
//				printf("Shared memory mapped at address: %p\n\n\n", (void*)pDataPFD);
			}
			
			
			// 等待子进程退出
			//WaitForSingleObject(pi.hProcess, INFINITE);
			
			
			// 清理
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
//			CloseHandle(hEventFMC);
			
			CloseHandle(hMapFileFMC);
			UnmapViewOfFile(pDataFMC);
			
			free(mySharedMemoryFMCA);
			
		}
		
		
	}
	
	
	
	
	//printf("hello");
	return 0;
}



