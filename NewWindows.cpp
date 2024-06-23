#include<graphics.h>
#include<windows.h>
#include<stdio.h>
#include <iostream>
#include <thread>
#include <mutex>
# include <condition_variable>
# include <queue>
# include <vector>
# include <functional>

#undef WinMain

extern HDC egeHDC;
extern HWND egeHWND;

extern std::mutex mtx;
extern std::condition_variable cv;
extern bool ready;

extern int ifNewWindows;//是否弹窗显示新窗口
extern double windwsShow_x;//新窗口需要显示的左上角x坐标
extern double windwsShow_y;//新窗口需要显示的左上角y坐标
extern double windwsShow_lenth;//新窗口需要显示的x长度
extern double windwsShow_height;//新窗口需要显示的y高度

// 回调函数
LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//依次是窗口句柄，消息标识符，第一个消息参数，第二个消息参数
{
	PAINTSTRUCT ps;
	HDC hdc;
	
	switch (uMsg)//通过判断消息进行消息响应
	{
		case WM_CLOSE: {
			DestroyWindow(hwnd);//销毁窗口并发送WM_DESTROY消息，但是程序没有退出
			ifNewWindows = 0;
			break;
		}
	case WM_DESTROY:
		PostQuitMessage(0);//发出WM_QUIT消息，结束消息循环
		break;
		case WM_CREATE: /*窗口在创建时，会接收到该消息，通常在这里进行初始化操作*/
		
		break;
		case WM_PAINT:/*窗口有绘图操作更新时,会收到这个消息*/
		/*返回一个绘图设备句柄（Device Context，简称HDC），存储在hdc变量中。
		同时，BeginPaint函数还接收一个指向PAINTSTRUCT结构的指针&ps，用于存储有关绘制过程的信息。*/
		
		hdc = BeginPaint(hwnd, &ps);
		
		// 假设egeHDC已经正确初始化，并且是有效的
		if (egeHDC != nullptr) {
			// 使用egeHDC的内容进行BitBlt操作
			RECT windowRect;
			GetWindowRect(hwnd, &windowRect);
			int width = windowRect.right - windowRect.left; // 窗口宽度
			int height = windowRect.bottom - windowRect.top; // 窗口高度
			StretchBlt(hdc, 0, 0, width, width, egeHDC, windwsShow_x, windwsShow_y, windwsShow_lenth, windwsShow_height, SRCCOPY);
		}
		EndPaint(hwnd, &ps);
		
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//对不感兴趣的消息进行缺省处理，必须有该代码，否则程序有问题
	}
	return 0;
}



void create_new_windows() {
	while (is_run()) {
		api_sleep(17);
		egeHDC = getHDC();
		if (ifNewWindows == 1) {
//			ifNewWindows = 0;
			WNDCLASS wndcls; //创建一个窗体类
			wndcls.cbClsExtra = 0;//类的额外内存，默认为0即可
			wndcls.cbWndExtra = 0;//窗口的额外内存，默认为0即可
			
			wndcls.hbrBackground = NULL;//获取画刷句柄（将返回的HGDIOBJ进行强制类型转换）
			wndcls.hCursor = LoadCursor(NULL, IDC_CROSS);//设置光标 //加载光标，也就是我们电脑屏幕上常见的箭头，十字，转圈等图形
			wndcls.hIcon = LoadIcon(NULL, IDI_ASTERISK);//设置窗体左上角的图标 //加载图标资源//也就是窗体左上角//IDI_ERROR
//				wndcls.hInstance = hInstance;//设置窗体所属的应用程序实例     /*重要*/
			wndcls.lpfnWndProc = WinProc;//设置窗体的回调函数，就是上面的函数   /*重要*/
			wndcls.lpszClassName = "test";//设置窗体的类名
			wndcls.lpszMenuName = NULL;//设置窗体的菜单,没有，填NULL
			wndcls.style = CS_HREDRAW | CS_VREDRAW;//设置窗体风格为水平重画和垂直重画
			RegisterClass(&wndcls);//向操作系统注册窗体
			
			//产生一个窗体，并返回该窗体的句柄，第一个参数必须为要创建的窗体的类名，第二个参数为窗体标题名
			HWND hwnd = CreateWindow("test", "我的第一个窗口",// 第一个参数为创建的窗体类名
				WS_OVERLAPPEDWINDOW,// 窗体风格
				windwsShow_x, windwsShow_y,// 窗口坐标
				windwsShow_lenth, windwsShow_height,// 窗口大小
				egeHWND,// 父窗口的句柄
				NULL,// 菜单句柄
				NULL,// 应用程序实例，这里就用到了WinMain的第一个参数
				NULL);// 额外的数据
			
			// 窗体创建后默认隐藏
			ShowWindow(hwnd, SW_SHOWNORMAL);//把窗体显示出来 //窗口显示的方式
			UpdateWindow(hwnd);//更新窗体 // 上面创建窗口时返回的窗口句柄，作用就是给窗口发个消息，命令它马上重新画一下窗口
			
			MSG msg;
			//消息循环——使得窗口可以跟着你的鼠标运动
			while (GetMessage(&msg, NULL, 0, 0))//拿到消息 //如果消息不是WM_QUIT,返回非零值；如果消息是WM_QUIT，返回零
			{
				TranslateMessage(&msg);//翻译消息，如把WM_KEYDOWN和WM_KEYUP翻译成一个WM_CHAR消息
				DispatchMessage(&msg);//派发消息
				
				// 检查是否需要重绘
				std::unique_lock<std::mutex> lock(mtx);
				cv.wait(lock, [] { return ready; }); // 等待绘图完成
				ready = false;
				lock.unlock();
				
				// 触发重绘
				InvalidateRect(hwnd, NULL, TRUE);
			}
		}
	}
	return;
}

