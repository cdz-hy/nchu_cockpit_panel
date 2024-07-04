#include <windows.h>
#include <stdio.h>
#include <graphics.h>

#include "G_variable.h"

char* WideCharToStringPFD(const WCHAR* wideStr);

typedef struct {
	//放置pfd所需要传送的数据

	double OUTBDangle;
	int FPV;
	double pitchAngle;
	double rollAngle;
	double sideSlipAngle;
	double headingIndication;
	double glideIndication;
	double airSpeed;
	double airSpeed_acceleration;
	double airSpeed_mach;
	double airSpeed_instruction;
	int MTRS;
	double altitude;
	double indicated_number;
	double altitude2;
	double rotationangle;
	int course;
	double verticalRate;
	double driftAngle;
	double pathAngle;
	double attackAngle;

	int egeWidth;
	int egeHeight;

} SharedDataPFD;


int show_pfd() {

	while (is_run()) {

		if (showPFDJudge == 1) {
			WCHAR mySharedMemoryPFDW[] =  L"Global\\MySharedMemoryPFD";
			char* mySharedMemoryPFDA = WideCharToStringPFD(mySharedMemoryPFDW);


			// 创建共享内存
			HANDLE hMapFilePFD = CreateFileMapping(
			    INVALID_HANDLE_VALUE,    // 使用系统页文件
			    NULL,                    // 默认安全属性
			    PAGE_READWRITE,          // 可读可写
			    0,                       // 高位大小
			    sizeof(SharedDataPFD),          // 低位大小
			    mySharedMemoryPFDA // 共享内存名称
			    );

			if (hMapFilePFD == NULL) {
				printf("CreateFileMapping failed (%d).\n", GetLastError());
				return -1;
			}

			// 映射共享内存到进程地址空间
			SharedDataPFD* pDataPFD = (SharedDataPFD*)MapViewOfFile(
			    hMapFilePFD,               // 共享内存句柄
			    FILE_MAP_ALL_ACCESS,    // 可读可写
			    0,                      // 高位文件偏移
			    0,                      // 低位文件偏移
			    sizeof(SharedDataPFD)          // 要映射的长度
			    );

			if (pDataPFD == NULL) {
				printf("MapViewOfFile failed (%d).\n", GetLastError());
				CloseHandle(hMapFilePFD);
				return -1;
			}

			// 创建子进程
			PROCESS_INFORMATION pi;
			ZeroMemory(&pi, sizeof(pi));

			STARTUPINFO si;
			ZeroMemory(&si, sizeof(si));
			si.cb = sizeof(si);

			WCHAR commandLinePFDW[] = L"D:/小熊猫C++/Program/B737-800,B727-200F仪表模拟/737PFD/PFD.exe";
			WCHAR currentDirectoryPFDW[] = L".";

			char*  commandLinePFDA = WideCharToStringPFD(commandLinePFDW);
			char* currentDirectoryPFDA  = WideCharToStringPFD(currentDirectoryPFDW);


			if (!CreateProcess(
			        NULL,
			        commandLinePFDA, // 子进程的路径
			        NULL,
			        NULL,
			        FALSE,
			        CREATE_NEW_CONSOLE,
			        NULL,
			        currentDirectoryPFDA,
			        &si,
			        &pi
			    )) {
				printf("CreateProcess failed (%d).\n", GetLastError());
				CloseHandle(hMapFilePFD);
				UnmapViewOfFile(pDataPFD);
				return -1;
			}

			printf("Shared memory mapped at address: %p\n", (void*)pDataPFD);
			
			while (is_run()) {


				pDataPFD -> OUTBDangle = OUTBDangle ;

				pDataPFD -> pitchAngle = pitchAngle ;
				pDataPFD -> rollAngle = rollAngle;

				pDataPFD ->sideSlipAngle = sideSlipAngle;
				pDataPFD ->headingIndication = headingIndication;
				pDataPFD ->glideIndication = glideIndication;

				pDataPFD ->airSpeed = airSpeed;
//				printf("airSpeed :%lf\n\n\n\n\n",airSpeed);
//				printf("pDatapfd-> airSpeed ::%lf\n\n\n\n\n\n\n",pDataPFD ->airSpeed);
				
				pDataPFD ->airSpeed_acceleration = airSpeed_acceleration;
				pDataPFD ->airSpeed_mach = airSpeed_mach;
				pDataPFD ->airSpeed_instruction = airSpeed_instruction;

				pDataPFD ->MTRS = MTRS;
				pDataPFD ->altitude = altitude;
				pDataPFD ->indicated_number = indicated_number;
				pDataPFD ->altitude2 = altitude2;
				pDataPFD ->rotationangle = rotationangle;
				pDataPFD ->course = course;

				pDataPFD ->verticalRate = verticalRate;

				pDataPFD ->attackAngle = attackAngle;
				pDataPFD ->FPV = FPV;
				pDataPFD -> driftAngle = driftAngle;
				pDataPFD ->pathAngle = pathAngle;

				pDataPFD ->egeHeight = egeHeight;
				pDataPFD ->egeWidth = egeWidth;

				if (WaitForSingleObject(pi.hProcess, 0) == WAIT_OBJECT_0) {
					// 子进程已经结束
					showPFDJudge = 0;
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


			CloseHandle(hMapFilePFD);
			UnmapViewOfFile(pDataPFD);

			free(mySharedMemoryPFDA);

		}


	}




	//printf("hello");
	return 0;
}

char* WideCharToStringPFD(const WCHAR* wideStr) {
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

