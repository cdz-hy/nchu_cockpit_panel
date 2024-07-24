#include <windows.h>
#include <stdio.h>
#include <graphics.h>

#include "G_variable.h"
#include "WinStringUtil.h"

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


int show_nd() {
	
	
	while (is_run()) {
		
		if (showNDJudge == 1) {
		
			WCHAR mySharedMemoryNDW[] =  L"Global\\MySharedMemoryND";
			char* mySharedMemoryNDA = WideCharToAnsi(mySharedMemoryNDW);
			
			// 创建共享内存
			HANDLE hMapFileND = CreateFileMapping(
				INVALID_HANDLE_VALUE,    // 使用系统页文件
				NULL,                    // 默认安全属性
				PAGE_READWRITE,          // 可读可写
				0,                       // 高位大小
				sizeof(SharedDataND),          // 低位大小
				mySharedMemoryNDA // 共享内存名称
				);
			
			if (hMapFileND == NULL) {
				printf("CreateFileMapping failed (%d).\n", GetLastError());
				return -1;
			}
			
			// 映射共享内存到进程地址空间
			SharedDataND* pDataND = (SharedDataND*)MapViewOfFile(
				hMapFileND,               // 共享内存句柄
				FILE_MAP_ALL_ACCESS,    // 可读可写
				0,                      // 高位文件偏移
				0,                      // 低位文件偏移
				sizeof(SharedDataND)          // 要映射的长度
				);
			
			if (pDataND == NULL) {
				printf("MapViewOfFile failed (%d).\n", GetLastError());
				CloseHandle(hMapFileND);
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
			WCHAR commandLineNDW[MAX_PATH];
			swprintf(commandLineNDW, MAX_PATH, L"%ssubprocess\\ND\\ND.exe", exeDir);
			WCHAR currentDirectoryNDW[] = L".";

			char* commandLineNDA = WideCharToAnsi(commandLineNDW);
			char* currentDirectoryNDA = WideCharToAnsi(currentDirectoryNDW);
			
			
			if(showNDJudge == 1){
				if (!CreateProcess(
					NULL,
					commandLineNDA, // 子进程的路径
					NULL,
					NULL,
					TRUE,
					CREATE_NEW_CONSOLE,
					NULL,
					currentDirectoryNDA,
					&si,
					&pi
					)) {
					printf("CreateProcess failed (%d).\n", GetLastError());
					CloseHandle(hMapFileND);
					UnmapViewOfFile(pDataND);
					return -1;
				}
			
				
				
				
				
			while (is_run()) {
				
				
				pDataND -> HDGMAG = HDGMAG;
				pDataND -> rotationangle = rotationangle;
				pDataND -> ndpointrotationangle = ndpointrotationangle;
				pDataND -> mapDistance = mapDistance;
				pDataND -> MINSRef = MINSRef;
				pDataND -> baroUnit = baroUnit;
				pDataND -> VOR1 = VOR1;
				pDataND -> VOR2 = VOR2;
				pDataND -> CTR = CTR;
				pDataND -> EHISMode  = EHISMode;
				pDataND -> ARPT = ARPT;
				pDataND -> POS = POS;
				pDataND -> WPT = WPT;
				pDataND -> STA = STA;
				pDataND -> DATA  =DATA;
				pDataND -> WXR = WXR;
				pDataND -> TERR = TERR;
				pDataND -> INBDangle = INBDangle;
				pDataND -> GS = GS;
				pDataND -> TAS = TAS;
				pDataND -> WS = WS;
				pDataND -> WD = WD;
				pDataND -> course3 = course3;
				pDataND -> course2 = course2;
				
				pDataND ->egeWidth = egeWidth;
				pDataND ->egeHeight = egeHeight;
				
				pDataND->latitude = latitude;
				pDataND->longitude = longitude;
				
				int cot = 0;
				
				for(auto it : route){
					
					pDataND->route[cot] = it;
					
					cot ++;
				}
				
				
				if (WaitForSingleObject(pi.hProcess, 0) == WAIT_OBJECT_0) {
					// 子进程已经结束
					showNDJudge = 0;
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
			
			
			CloseHandle(hMapFileND);
			UnmapViewOfFile(pDataND);
			
			free(mySharedMemoryNDA);
			
			}
		}
		
	}
	
	
	
	
	//printf("hello");
	return 0;
}


