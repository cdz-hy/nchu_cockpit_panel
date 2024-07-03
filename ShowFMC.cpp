#include <windows.h>
#include <stdio.h>
#include <graphics.h>

#include "G_variable.h"

char* WideCharToStringFMC(const WCHAR* wideStr);
typedef struct {
	//放置pfd所需要传送的数据
	
	char FMCFileName[20];
	
	int egeFMCWidth;
	int egeFMCHeight;
	
	int MainPanelLight;
	
	int ceshi;
	
} SharedDataFMC;

int ceshi;

int show_fmc() {
	
	while (is_run()) {
		
		if (showFMCJudge == 1) {
			WCHAR mySharedMemoryFMCW[] =  L"Global\\MySharedMemoryFMC";
			char* mySharedMemoryFMCA = WideCharToStringFMC(mySharedMemoryFMCW);
			
			
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
			
			WCHAR commandLineFMCW[] = L"D:/Git/sls/737FMC/737FMC.exe";
			WCHAR currentDirectoryFMCW[] = L".";
			
			char*  commandLineFMCA = WideCharToStringFMC(commandLineFMCW);
			char* currentDirectoryFMCA  = WideCharToStringFMC(currentDirectoryFMCW);
			
			
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
				
				if(pDataFMC ->FMCFileName!=NULL)
				{
					strcpy(FMCFileName,pDataFMC->FMCFileName);
				}			
				
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

char* WideCharToStringFMC(const WCHAR* wideStr) {
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

