#include <windows.h>
#include <stdio.h>
#include <graphics.h>

#include "G_variable.h"
#include "WinStringUtil.h"


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


int show_eicas2() {
	
	while (is_run()) {
		
		if (showEICAS2Judge == 1) {
			
			WCHAR mySharedMemoryEICAS2W[] =  L"Global\\MySharedMemoryEICAS2";
			char* mySharedMemoryEICAS2A = WideCharToAnsi(mySharedMemoryEICAS2W);
			
			
			// 创建共享内存
			HANDLE hMapFileEICAS2 = CreateFileMapping(
				INVALID_HANDLE_VALUE,    // 使用系统页文件
				NULL,                    // 默认安全属性
				PAGE_READWRITE,          // 可读可写
				0,                       // 高位大小
				sizeof(SharedDataEICAS2),          // 低位大小
				mySharedMemoryEICAS2A // 共享内存名称
				);
			
			if (hMapFileEICAS2 == NULL) {
				printf("CreateFileMapping failed (%d).\n", GetLastError());
				return -1;
			}
			
			// 映射共享内存到进程地址空间
			SharedDataEICAS2* pDataEICAS2 = (SharedDataEICAS2*)MapViewOfFile(
				hMapFileEICAS2,               // 共享内存句柄
				FILE_MAP_ALL_ACCESS,    // 可读可写
				0,                      // 高位文件偏移
				0,                      // 低位文件偏移
				sizeof(SharedDataEICAS2)          // 要映射的长度
				);
			
			if (pDataEICAS2 == NULL) {
				printf("MapViewOfFile failed (%d).\n", GetLastError());
				CloseHandle(hMapFileEICAS2);
				return -1;
			}
			
			
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
			WCHAR commandLineEICAS2W[MAX_PATH];
			swprintf(commandLineEICAS2W, MAX_PATH, L"%ssubprocess\\MFD2\\MFD2.exe", exeDir);
			WCHAR currentDirectoryEICAS2W[] = L".";

			char* commandLineEICAS2A = WideCharToAnsi(commandLineEICAS2W);
			char* currentDirectoryEICAS2A = WideCharToAnsi(currentDirectoryEICAS2W);
			
			if (!CreateProcess(
				NULL,
				commandLineEICAS2A, // 子进程的路径
				NULL,
				NULL,
				TRUE,
				CREATE_NEW_CONSOLE,
				NULL,
				currentDirectoryEICAS2A,
				&si,
				&pi
				)) {
				printf("CreateProcess failed (%d).\n", GetLastError());
				CloseHandle(hMapFileEICAS2);
				UnmapViewOfFile(pDataEICAS2);
				return -1;
			}
			
			
			
			while (is_run()) {
				
				pDataEICAS2->N21 = N21;
				pDataEICAS2->N22 = N22;
				pDataEICAS2->FF1 = FF1;
				pDataEICAS2->FF2 = FF2;
				pDataEICAS2->oilPress1 = oilPress1;
				pDataEICAS2->oilPress2 = oilPress2;
				pDataEICAS2->oilTemp1 = oilTemp1;
				pDataEICAS2->oilTemp2 = oilTemp2;
				pDataEICAS2->oilQTY1 = oilQTY1;
				pDataEICAS2->oilQTY2 = oilQTY2;
				pDataEICAS2->VIB1 = VIB1;
				pDataEICAS2->VIB2 = VIB2;
				
				pDataEICAS2 ->egeHeight = egeHeight;
				pDataEICAS2 ->egeWidth = egeWidth;
				
				if (WaitForSingleObject(pi.hProcess, 0) == WAIT_OBJECT_0) {
					// 子进程已经结束
					showEICAS2Judge = 0;
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
			
			
			CloseHandle(hMapFileEICAS2);
			UnmapViewOfFile(pDataEICAS2);
			
			free(mySharedMemoryEICAS2A);
			
		}
		
		
	}
	
	
	
	
	//printf("hello");
	return 0;
}


