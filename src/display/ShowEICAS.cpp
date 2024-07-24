#include <windows.h>
#include <stdio.h>
#include <graphics.h>

#include "G_variable.h"
#include "WinStringUtil.h"

typedef struct {
	//放置EICAS需要接受的数据
	
	double Oangle_1;
	double Oangle_2;
	double Oangle_3;
	double Oangle_4;
	double fanSpeed;
	double fanSpeed_1 ;
	double gastemp ;
	double gastemp_1 ;
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

int show_eicas() {
	
	while (is_run()) {
		
		if (showEICASJudge == 1) {
			
			WCHAR mySharedMemoryEICASW[] =  L"Global\\MySharedMemoryEICAS";
			char* mySharedMemoryEICASA = WideCharToAnsi(mySharedMemoryEICASW);
			
			// 创建共享内存
			HANDLE hMapFileEICAS = CreateFileMapping(
				INVALID_HANDLE_VALUE,    // 使用系统页文件
				NULL,                    // 默认安全属性
				PAGE_READWRITE,          // 可读可写
				0,                       // 高位大小
				sizeof(SharedDataEICAS),          // 低位大小
				mySharedMemoryEICASA // 共享内存名称
				);
			
			if (hMapFileEICAS == NULL) {
				printf("CreateFileMapping failed (%d).\n", GetLastError());
				return -1;
			}
			
			// 映射共享内存到进程地址空间
			SharedDataEICAS* pDataEICAS = (SharedDataEICAS*)MapViewOfFile(
				hMapFileEICAS,               // 共享内存句柄
				FILE_MAP_ALL_ACCESS,    // 可读可写
				0,                      // 高位文件偏移
				0,                      // 低位文件偏移
				sizeof(SharedDataEICAS)          // 要映射的长度
				);
			
			if (pDataEICAS == NULL) {
				printf("MapViewOfFile failed (%d).\n", GetLastError());
				CloseHandle(hMapFileEICAS);
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
			WCHAR commandLineEICASW[MAX_PATH];
			swprintf(commandLineEICASW, MAX_PATH, L"%ssubprocess\\MFD1\\MFD1.exe", exeDir);
			WCHAR currentDirectoryEICASW[] = L".";

			char* commandLineEICASA = WideCharToAnsi(commandLineEICASW);
			char* currentDirectoryEICASA = WideCharToAnsi(currentDirectoryEICASW);
			
			
			if (!CreateProcess(
				NULL,
				commandLineEICASA, // 子进程的路径
				NULL,
				NULL,
				TRUE,
				CREATE_NEW_CONSOLE,
				NULL,
				currentDirectoryEICASA,
				&si,
				&pi
				)) {
				printf("CreateProcess failed (%d).\n", GetLastError());
				CloseHandle(hMapFileEICAS);
				UnmapViewOfFile(pDataEICAS);
				return -1;
			}
			
			//printf("Shared memory mapped at address: %p\n", (void*)pDataPFD);
			
			while (is_run()) {
				
				
				pDataEICAS->Oangle_1 = Oangle_1;
				pDataEICAS->Oangle_2 = Oangle_2;
				pDataEICAS->Oangle_3 = Oangle_3;
				pDataEICAS->Oangle_4 = Oangle_4;
				pDataEICAS->fanSpeed = fanSpeed;
				pDataEICAS->fanSpeed_1 = fanSpeed_1;
				pDataEICAS->gastemp = gastemp;
				pDataEICAS->gastemp_1 = gastemp_1;
				pDataEICAS->FuelFlowSpeed = FuelFlowSpeed;
				pDataEICAS->FuelFlowSpeed_1 = FuelFlowSpeed_1;
				pDataEICAS->Fuelrest_1 = Fuelrest_1;
				pDataEICAS->Fuelrest_2 = Fuelrest_2;
				pDataEICAS->Fuelrest_3 = Fuelrest_3;
				pDataEICAS->Fuelrest_total = Fuelrest_total;
				pDataEICAS->TAT = TAT;
				pDataEICAS->UPPERangle = UPPERangle;
				
				pDataEICAS ->egeHeight = egeHeight;
				pDataEICAS ->egeWidth = egeWidth;
				
				
				if (WaitForSingleObject(pi.hProcess, 0) == WAIT_OBJECT_0) {
					// 子进程已经结束
					showEICASJudge = 0;
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
			
			
			CloseHandle(hMapFileEICAS);
			UnmapViewOfFile(pDataEICAS);
			
			free(mySharedMemoryEICASA);
			
		}
		
		
	}
	
	
	
	
	//printf("hello");
	return 0;
}


