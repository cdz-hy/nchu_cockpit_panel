

#include <graphics.h>
#include <vector>
#include <math.h>
using namespace std;

typedef struct waypoint {

	int num;	//��ʾ��̨���ͣ������Լ��ӵģ�����������VOR������ͨ���� 1/2/3	����/VOR/����
	char code[20];	// ��ţ�3/12��ʾ��NDB/VOR?��
	double lat;		// γ��
	double lon;		// ����
	char name[20];	// ��̨����
	char type[20]; 	// ��̨���ͣ��Ƿ�·�϶����ã�ENRT����
	char freq[20];	// Ƶ��
	double range;	// ���շ�Χ
	char devi[20];	// ��ƫ��
	char FIRName[20];	// �鱨������
	char fullName[20];	// ���ƣ�������
	char fullType[20];	// ��̨���ͣ���ȫ��

}WAYPOINT;

typedef struct {

	//�ɻ���������
	double latitude;
	double longitude;
	int renewMap;

	//�����ĺ���
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

void change_size(PIMAGE& pimg, int width, int height);
double toRadians(double a);
double getDistance(double latitude1, double longitude1, double latitude2, double longitude2);
double getBearing(double lat1, double lon1, double lat2, double lon2);
char* WideCharToString(const WCHAR* wideStr);
void draw_plane(double center_x, double center_y, double side, double angle);

//�����ĺ���
vector<WAYPOINT> fullRoute;

//ʵ���ƶ�
int is_down = 0;
double pos_x_move = 0;
double pos_y_move = 0;
double pos_x_move_tmp = 0;
double pos_y_move_tmp = 0;
double pos_x_move_plane = 0;
double pos_y_move_plane = 0;

//��¼���
int mouse_x = 0;
int mouse_y = 0;
int mouse_x_cur = 0;
int mouse_y_cur = 0;

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

//��ͼ���ĵ�����
WAYPOINT map_center = { 0, "", 0, 0, };

//��ʱ��ͼ���ĵ�����
WAYPOINT map_centerTmp = { 0, "", 0, 0, };

//�ɻ�����lat��lon�ڹ����ڴ���

//��ʾģʽ����ͷ���ϻ����������ϣ�
int showMode = 0;



int windowsWidth = 720;
int windowsHeight = 545;
int changeSize = 0;

short zDelta = 0;
int change = 0;

WNDPROC originalWndProc;

LRESULT CALLBACK NewWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// ����Զ��崦���߼�
	if (uMsg == WM_SIZE)
	{

		//DefWindowProc(hwnd, uMsg, wParam, lParam);

		windowsWidth = LOWORD(lParam);
		windowsHeight = HIWORD(lParam);
		changeSize = 1;

		return 0;
	}

	// ����������Ϣ������ԭʼ���ڹ��̺�������
	return CallWindowProc(originalWndProc, hwnd, uMsg, wParam, lParam);
}






int main()
{
	WCHAR mySharedMemory[] = L"Global\\MySharedMemory";
	char* mySharedMemoryA = WideCharToString(mySharedMemory);

	WCHAR eventData[] = L"EventDataAvailable";
	char* eventDataA = WideCharToString(eventData);

	// �򿪹����ڴ�
	HANDLE hMapFile = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,    // �ɶ���д
		FALSE,                  // ���Ӽ̳о����ӳ��
		mySharedMemory // �����ڴ�����
	);


	if (hMapFile == NULL) {
		printf("OpenFileMapping failed (%d).\n", GetLastError());
		return -1;
	}

	// ���¼�
	HANDLE hEvent = OpenEvent(
		EVENT_ALL_ACCESS,
		false,
		eventData
		//		TEXT("Global\\MySharedEvent")
	);

	if (hEvent == NULL) {
		printf("OpenEvent failed (%d).\n", GetLastError());
		return -1;
	}

	// ӳ�乲���ڴ浽���̵�ַ�ռ�
	SharedData* pData = (SharedData*)MapViewOfFile(
		hMapFile,               // �����ڴ���
		FILE_MAP_ALL_ACCESS,    // �ɶ���д
		0,                      // ��λ�ļ�ƫ��
		0,                      // ��λ�ļ�ƫ��
		sizeof(SharedData)          // Ҫӳ��ĳ���
	);

	if (pData == NULL) {
		printf("MapViewOfFile failed (%d).\n", GetLastError());
		CloseHandle(hMapFile);
		return -1;
	}

	//	// �ӽ����������¼����
	//	HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	//	initgraph( 480, 480, INIT_RENDERMANUAL);
	//	setbkcolor(WHITE);
	initgraph(windowsWidth, windowsHeight, INIT_RENDERMANUAL);
	setbkcolor(EGEARGB(0XFF, 46, 69, 93));
	setcaption("Map");

	HWND hwnd = getHWnd();

	LONG style = GetWindowLong(hwnd, GWL_STYLE);
	style |= WS_THICKFRAME | WS_MAXIMIZEBOX;
	SetWindowLong(hwnd, GWL_STYLE, style);


	//���ô������
	SetWindowPos(getHWnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	originalWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)NewWndProc);



	ege_enable_aa(true);

	//���ô������
	SetWindowPos(getHWnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	PIMAGE img = newimage();
	PIMAGE show = newimage();

	//ͼƬ��ʾ��Χ
	double side = 500;
	double pos_x = 2048 / 2 - side / 2;
	double pos_y = 2048 / 2 - side / 2;

	//��ͼ��������
	double map_x = 0;
	double map_y = 0;
	double map_side = 480;

	//��ȡͼƬ
	if (pData->renewMap == 2) {
		getimage(img, "map.png");
		pData->renewMap = 0;
		SetEvent(hEvent);
	}

	for (; is_run(); delay_fps(60))
	{



		if (changeSize == 1) {
			if (windowsHeight >= 200 && windowsWidth >= 200) {
				resizewindow(windowsWidth, windowsHeight);
			}
			changeSize = 0;
		}
		else if (changeSize == 2) {
			HDC hdc = GetDC(NULL); // ��ȡ��Ļ���豸�����ģ�NULL������ʾ��ȡ������Ļ��DC
			int windowsWidthTmp = 0;
			int windowsHeightTmp = 0;
			if (hdc)
			{
				windowsWidthTmp = GetDeviceCaps(hdc, HORZRES); // ��ȡ��Ļˮƽ�ֱ���
				windowsHeightTmp = GetDeviceCaps(hdc, VERTRES); // ��ȡ��Ļ��ֱ�ֱ���
				ReleaseDC(NULL, hdc); // ʹ����Ϻ��ͷ��豸������
			}
			HWND hwnd = getHWnd();

			resizewindow(windowsWidthTmp, windowsHeightTmp);
			SendMessage(hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		}


		cleardevice();

		//--------------------------------------//
		setfillcolor(EGEARGB(0XFF, 38, 50, 64));
		ege_fillrect(0, 0, windowsWidth, windowsHeight * 1.0 / 13.625);

		setbkmode(TRANSPARENT);
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		setfont(windowsWidth * 1.0 / 20.5714285714285, 0, "����");
		setcolor(EGEARGB(150, 177, 177, 178));
		outtextxy(windowsWidth * 1.0 / 2, windowsHeight * 1.0 / 22.7083333333333333, "MAP");
		//--------------------------------------//

		strcpy(mapProvince, pData->mapProvince);
		strcpy(mapCity, pData->mapCity);
		strcpy(mapAdcode, pData->mapAdcode);
		strcpy(mapWeather, pData->mapWeather);
		strcpy(mapTemperature, pData->mapTemperature);
		strcpy(mapWinddirection, pData->mapWinddirection);
		strcpy(mapWindpower, pData->mapWindpower);
		strcpy(mapHumidity, pData->mapHumidity);
		strcpy(mapTownship, pData->mapTownship);
		strcpy(mapStreet, pData->mapStreet);

		//�Ը����źŽ��и��� 2�Ǹ�����ɣ�1����Ҫ���£�0���ֲ���
		if (pData->renewMap == 2) {
			PIMAGE imgTmp = newimage();
			getimage(imgTmp, "./map.png");
			delimage(img);
			img = imgTmp;
			pData->renewMap = 0;
			map_center.lat = map_centerTmp.lat;
			map_center.lon = map_centerTmp.lon;
		}

		//��Ҫ���߽緢�������ź�
		if (pos_x + pos_x_move_plane + side >= 1800 || pos_y + pos_y_move_plane + side >= 1800 ||
			pos_x + pos_x_move_plane <= 100 || pos_y + pos_y_move_plane <= 100) {

			pData->renewMap = 1;
			map_centerTmp.lat = pData->latitude;
			map_centerTmp.lon = pData->longitude;

		}


		//��ȡԭͼһ����
		getimage(show, img, pos_x + pos_x_move + pos_x_move_plane, pos_y + pos_y_move + pos_y_move_plane, side, side);

		//������С��������ʾ��

		if (windowsWidth * 1.0 / 1.5 > windowsHeight * 1.0 / 1.135416666666) {

			map_side = windowsHeight * 1.0 / 1.135416666666;

		}
		else {

			map_side = windowsWidth * 1.0 / 1.5;

		}

		change_size(show, map_side, map_side);

		//��ʾͼƬ
//		putimage_withalpha(NULL, show, 0, 0);
		//--------------------------------------//

		putimage_withalpha(NULL, show, windowsWidth * 1.0 / 60, windowsHeight * 1.0 / 10.283018867);


		//--------------------------------------//


		//ʵ���ƶ�
		if (GetAsyncKeyState(0x01) & 0x8000) {
			if (is_down == 0) {
				mousepos(&mouse_x, &mouse_y);
				is_down = 1;
				mouse_x_cur = mouse_x;
				mouse_y_cur = mouse_y;
			}
			if (is_down == 1) {
				mousepos(&mouse_x, &mouse_y);
				pos_x_move = -(mouse_x - mouse_x_cur);
				pos_y_move = -(mouse_y - mouse_y_cur);
				pos_x_move += pos_x_move_tmp;
				pos_y_move += pos_y_move_tmp;
			}
		}
		else if (is_down == 1) {
			is_down = 0;
			pos_x_move_tmp = pos_x_move;
			pos_y_move_tmp = pos_y_move;
		}

		//�ڰ���ctrlʱ�Ĳ���
		if (GetAsyncKeyState(0x11) & 0x8000) {

			//����ʵ�ַŴ���С
			mouse_msg msgRecord = { 0 };
			bool redraw = true;

			while (mousemsg()) {
				//getmouse ��ȡ�����Ϣ
				msgRecord = getmouse();
				redraw = true;
			}
			if (redraw) {

				if (msgRecord.is_wheel()) {
					if (msgRecord.wheel < 0 && side < 800) {
						side -= msgRecord.wheel / 10;
					}
					else if (msgRecord.wheel > 0 && side > 100) {
						side -= msgRecord.wheel / 10;
					}
				}

			}

		}



		pos_x = 2048 / 2 - side / 2;
		pos_y = 2048 / 2 - side / 2;


		//�ı���ʾ��Χ��ʼ���Էɻ�Ϊ����
		//323.148572641130506974593��ԭͼ2048*2048������ ��Ӧ21784.4393 m
		//��ÿ�����ض�Ӧ67.413076041 m
		//��ͼ�α任����ege�� ÿ�����ض�Ӧ500 / 480 * 67.413076041 m  �� 70.221954209375 m  //��Ҫ����������
		double angle = getBearing(map_center.lat, map_center.lon, pData->latitude, pData->longitude);
		double dis = getDistance(map_center.lat, map_center.lon, pData->latitude, pData->longitude);
		pos_x_move_plane = dis * sin(toRadians(angle)) / 70.22195420;//ʵ�������67�������ege������ÿ�����ض�Ӧ�ľ���
		pos_y_move_plane = -dis * cos(toRadians(angle)) / 70.22195420;


		//������

		double plane_x = map_side / 2 - pos_x_move * (map_side / side) + windowsWidth  * 1.0 / 60;
		double plane_y = map_side / 2 - pos_y_move * (map_side / side) + windowsHeight * 1.0 / 10.283018867;


		setfont(windowsWidth * 1.0 / 30, 0, "����");
		setcolor(WHITE);
		outtextxy(windowsWidth * 1.0 / 1.18811881188, windowsHeight * 1.0 / 5.5, "λ��");
		outtextxy(windowsWidth * 1.0 / 1.18811881188, windowsHeight * 1.0 / 2.0801526717557251908, "���ٷ���");
		outtextxy(windowsWidth * 1.0 / 1.1803278688524590163934, windowsHeight * 1.0 / 1.39030612244, "�����¶�ʪ��");

		setfillcolor(BLACK);
		ege_fillrect(windowsWidth * 1.0 / 1.411764705882352,
			windowsHeight * 1.0 / 4.5416666666,
			windowsWidth * 1.0 / 3.6,
			windowsHeight * 1.0 / 21.8);
		ege_fillrect(windowsWidth * 1.0 / 1.411764705882352,
			windowsHeight * 1.0 / 3.585526315,
			windowsWidth * 1.0 / 3.6,
			windowsHeight * 1.0 / 21.8);
		ege_fillrect(windowsWidth * 1.0 / 1.411764705882352,
			windowsHeight * 1.0 / 2.96195652,
			windowsWidth * 1.0 / 3.6,
			windowsHeight * 1.0 / 21.8);


		ege_fillrect(windowsWidth * 1.0 / 1.411764705882352,
			windowsHeight * 1.0 / 1.92579505,
			windowsWidth * 1.0 / 3.6,
			windowsHeight * 1.0 / 21.8);
		ege_fillrect(windowsWidth * 1.0 / 1.411764705882352,
			windowsHeight * 1.0 / 1.7356687,
			windowsWidth * 1.0 / 3.6,
			windowsHeight * 1.0 / 21.8);

		ege_fillrect(windowsWidth * 1.0 / 1.411764705882352,
			windowsHeight * 1.0 / 1.3228155339,
			windowsWidth * 1.0 / 3.6,
			windowsHeight * 1.0 / 21.8);
		ege_fillrect(windowsWidth * 1.0 / 1.411764705882352,
			windowsHeight * 1.0 / 1.22747747747,
			windowsWidth * 1.0 / 3.6,
			windowsHeight * 1.0 / 21.8);
		ege_fillrect(windowsWidth * 1.0 / 1.411764705882352,
			windowsHeight * 1.0 / 1.1449579831,
			windowsWidth * 1.0 / 3.6,
			windowsHeight * 1.0 / 21.8);

		setfont(windowsHeight * 1.0 / 30.27777777, 0, "����");
		setcolor(EGEARGB(0xff, 177, 177, 178));
		outtextxy(windowsWidth * 1.0 / 1.2631, windowsHeight * 1.0 / 4.037, mapProvince);
		outtextxy(windowsWidth * 1.0 / 1.132, windowsHeight * 1.0 / 4.037, mapCity);
		outtextxy(windowsWidth * 1.0 / 1.18811881188, windowsHeight * 1.0 / 3.263, mapTownship);
		outtextxy(windowsWidth * 1.0 / 1.18811881188, windowsHeight * 1.0 / 2.73, mapStreet);

		outtextxy(windowsWidth * 1.0 / 1.18811881188, windowsHeight * 1.0 / 1.8412, mapWindpower);
		outtextxy(windowsWidth * 1.0 / 1.18811881188, windowsHeight * 1.0 / 1.66158, mapWinddirection);

		outtextxy(windowsWidth * 1.0 / 1.18811881188, windowsHeight * 1.0 / 1.27934, mapWeather);
		outtextxy(windowsWidth * 1.0 / 1.18811881188, windowsHeight * 1.0 / 1.18736, mapTemperature);
		outtextxy(windowsWidth * 1.0 / 1.18811881188, windowsHeight * 1.0 / 1.1122, mapHumidity);

		//���º���
		fullRoute.clear();
		for (int i = 0; i < pData->routeNum; i++) {
			fullRoute.push_back(pData->fullRoute[i]);
		}


		//���ƺ���
		for (auto it = fullRoute.begin(); it + 1 != fullRoute.end(); it++) {

			WAYPOINT wp1 = *(it);
			WAYPOINT wp2 = *(it + 1);


			double dis = getDistance(pData->latitude, pData->longitude, wp1.lat, wp1.lon);
			double bearing = getBearing(pData->latitude, pData->longitude, wp1.lat, wp1.lon);


			double rl = dis / ((1.0 * side / map_side) * 67.413076041);
			double rx = (cos(toRadians(bearing - 90)) * rl) + (map_x + map_side / 2) + windowsWidth * 1.0 / 60;
			double ry = (sin(toRadians(bearing - 90)) * rl) + (map_y + map_side / 2) + windowsHeight * 1.0 / 10.283018867;


			double dis2 = getDistance(pData->latitude, pData->longitude, wp2.lat, wp2.lon);
			double bearing2 = getBearing(pData->latitude, pData->longitude, wp2.lat, wp2.lon);

			double rl2 = dis2 / ((1.0 * side / map_side) * 67.413076041);
			double rx2 = (cos(toRadians(bearing2 - 90)) * rl2) + (map_x + map_side / 2) + windowsWidth * 1.0 / 60;
			double ry2 = (sin(toRadians(bearing2 - 90)) * rl2) + (map_y + map_side / 2) + windowsHeight * 1.0 / 10.283018867;

			setfillcolor(EGEARGB(0x99, 0x8c, 0x8c, 0x8c));
			setlinewidth(3);

			//			if(rx > map_x + pos_x_move + map_side || ry >= map_y + pos_y_move + map_side || rx2 > map_x + pos_x_move + map_side || ry2 >= map_y + pos_y_move + map_side){
			//				continue;
			//			}
			//			if(rx + pos_x_move > map_side || ry + pos_y_move > map_side || rx2 > map_x + pos_x_move + map_side || ry2 >= map_y + pos_y_move + map_side){
			//				continue;
			//			}

			if (rx - pos_x_move * (map_side / side) > map_x + 1.05 * map_side || ry - pos_y_move * (map_side / side) >= map_y + 1.05 * map_side || rx2 - pos_x_move * (map_side / side) > map_x + 1.05 * map_side || ry2 - pos_y_move * (map_side / side) >= map_y + 1.05 * map_side) {

			}
			else {
				ege_line(rx - pos_x_move * (map_side / side), ry - pos_y_move * (map_side / side), rx2 - pos_x_move * (map_side / side), ry2 - pos_y_move * (map_side / side));
			}


		}

		//		printf("%d    ",fullRoute.size());

		if (plane_x > map_x + 1.05 * map_side || plane_y >= map_y + 1.05 * map_side) {

		}
		else {
			draw_plane(plane_x, plane_y, 30, pData->rotationangle);
		}

	}


	// ����
	CloseHandle(hMapFile);


	UnmapViewOfFile(pData);
	delimage(img);
	free(mySharedMemoryA);
	CloseHandle(hEvent);
	closegraph();
	return 0;
}

char* WideCharToString(const WCHAR* wideStr) {
	// ������ֽ��ַ�������Ļ�������С
	int size = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, NULL, 0, NULL, NULL);

	// ������ֽ��ַ���������
	char* mbStr = (char*)malloc(size * sizeof(char));
	if (mbStr == NULL) {
		// �����ڴ�ʧ�ܣ����� NULL
		return NULL;
	}

	// ִ��ת��
	WideCharToMultiByte(CP_ACP, 0, wideStr, -1, mbStr, size, NULL, NULL);

	return mbStr;
}



//�����ຯ�����������Ƕȵ�

void change_size(PIMAGE& pimg, int width, int height) {

	//pimgΪ�գ���Ŀ��ͼ���С��ԭͼ��һ�����������ţ�ֱ�ӷ���
	if ((pimg == NULL) || (width == getwidth(pimg) && height == getheight(pimg)))
		return;

	PIMAGE tmp = newimage(width, height);
	putimage(tmp, 0, 0, width, height, pimg, 0, 0, getwidth(pimg), getheight(pimg));
	delimage(pimg);

	pimg = tmp;
}

double toRadians(double a) {
	return a * (PI / 180);
}

//Vincenty��ʽ�����������
//return the distance of two point, unit is meter
double getDistance(double latitude1, double longitude1, double latitude2, double longitude2) {
	// R is the radius of the earth in meters
	double R = 6371004;  //EARTH_RADIUS
	double deltaLatitude = toRadians(latitude2 - latitude1);
	double deltaLongitude = toRadians(longitude2 - longitude1);
	latitude1 = toRadians(latitude1);
	latitude2 = toRadians(latitude2);
	double a = pow(sin(deltaLatitude / 2), 2) + cos(latitude1) * cos(latitude2) * pow(sin(deltaLongitude / 2), 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));

	double d = R * c;
	return d;
}

double getBearing(double lat1, double lon1, double lat2, double lon2) {
	lat1 = toRadians(lat1);
	lat2 = toRadians(lat2);
	lon1 = toRadians(lon1);
	lon2 = toRadians(lon2);
	double dLon = lon2 - lon1;
	double y = sin(dLon) * cos(lat2);
	double x = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(dLon);
	double brng = atan2(y, x);
	brng = brng * 180 / PI;
	brng = fmod((brng + 360), 360);
	return brng;
}


void draw_plane(double center_x, double center_y, double side, double angle)
{
	//�Բ�����˵����
	//center_x ��center_y �����ĵ�����꣬side ������ɻ��ĳ�����ͷ����β��

	angle = angle * PI / 180;

	double single = side / 15;

	setfillcolor(EGEARGB(0xff, 0xba, 0x3c, 0x1a));

	double x01 = 0, y01 = -single * 7.9;
	double x02 = -single * 1.25, y02 = -single * 7;
	double x03 = -single * 1.25, y03 = +single * 4.5;
	double x04 = -single * 4, y04 = +single * 7.5;
	double x05 = -single * 3, y05 = +single * 8.5;
	double x06 = 0, y06 = +single * 6.7;
	double x07 = +single * 3, y07 = +single * 8.5;
	double x08 = +single * 4, y08 = +single * 7.5;
	double x09 = +single * 1.25, y09 = +single * 4.5;
	double x010 = +single * 1.25, y010 = -single * 7;

	ege_point points1[11] = {
		{x01 * cos(angle) - y01 * sin(angle) + center_x,x01 * sin(angle) + y01 * cos(angle) + center_y},
		{x02 * cos(angle) - y02 * sin(angle) + center_x,x02 * sin(angle) + y02 * cos(angle) + center_y},
		{x03 * cos(angle) - y03 * sin(angle) + center_x,x03 * sin(angle) + y03 * cos(angle) + center_y},
		{x04 * cos(angle) - y04 * sin(angle) + center_x,x04 * sin(angle) + y04 * cos(angle) + center_y},
		{x05 * cos(angle) - y05 * sin(angle) + center_x,x05 * sin(angle) + y05 * cos(angle) + center_y},
		{x06 * cos(angle) - y06 * sin(angle) + center_x,x06 * sin(angle) + y06 * cos(angle) + center_y},
		{x07 * cos(angle) - y07 * sin(angle) + center_x,x07 * sin(angle) + y07 * cos(angle) + center_y},
		{x08 * cos(angle) - y08 * sin(angle) + center_x,x08 * sin(angle) + y08 * cos(angle) + center_y},
		{x09 * cos(angle) - y09 * sin(angle) + center_x,x09 * sin(angle) + y09 * cos(angle) + center_y},
		{x010 * cos(angle) - y010 * sin(angle) + center_x,x010 * sin(angle) + y010 * cos(angle) + center_y},
		{x01 * cos(angle) - y01 * sin(angle) + center_x,x01 * sin(angle) + y01 * cos(angle) + center_y}
	};
	ege_fillpoly(11, points1);

	double x11 = -single * 1.25, y11 = -single * 3;
	double x12 = -single * 7, y12 = -single * 0.5;
	double x13 = -single * 7, y13 = +single + 1.5;
	double x14 = -single * 1.25, y14 = 0;
	ege_point points2[5] = {
		{x11 * cos(angle) - y11 * sin(angle) + center_x,x11 * sin(angle) + y11 * cos(angle) + center_y},
		{x12 * cos(angle) - y12 * sin(angle) + center_x,x12 * sin(angle) + y12 * cos(angle) + center_y},
		{x13 * cos(angle) - y13 * sin(angle) + center_x,x13 * sin(angle) + y13 * cos(angle) + center_y},
		{x14 * cos(angle) - y14 * sin(angle) + center_x,x14 * sin(angle) + y14 * cos(angle) + center_y},
		{x11 * cos(angle) - y11 * sin(angle) + center_x,x11 * sin(angle) + y11 * cos(angle) + center_y}
	};
	ege_fillpoly(5, points2);

	double x21 = single * 1.25, y21 = -single * 3;
	double x22 = single * 7, y22 = -single * 0.5;
	double x23 = single * 7, y23 = +single + 1.5;
	double x24 = single * 1.25, y24 = 0;

	ege_point points3[5] = {
		{x21 * cos(angle) - y21 * sin(angle) + center_x,x21 * sin(angle) + y21 * cos(angle) + center_y},
		{x22 * cos(angle) - y22 * sin(angle) + center_x,x22 * sin(angle) + y22 * cos(angle) + center_y},
		{x23 * cos(angle) - y23 * sin(angle) + center_x,x23 * sin(angle) + y23 * cos(angle) + center_y},
		{x24 * cos(angle) - y24 * sin(angle) + center_x,x24 * sin(angle) + y24 * cos(angle) + center_y},
		{x21 * cos(angle) - y21 * sin(angle) + center_x,x21 * sin(angle) + y21 * cos(angle) + center_y}
	};
	ege_fillpoly(5, points3);
}
