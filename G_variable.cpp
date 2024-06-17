#include <vector>
#include<graphics.h>
#include "G_structs.h"
using namespace std;


//==================================//

//==========以下为飞行参数==========//

double pitchAngle = 0;
double rollAngle = 0;
double sideSlipAngle = 0;
double headingIndication = 0;
double glideIndication = 0;
double ndpointrotationangle = 0;

double RCDI_speed = 7866;
double verticalRate = -7866;
double RNG = 56;//初始显示RNG 5

double altitude = 0;
double altitude2 = -4;//对地
double MILLIBARS_data = 0;
double INGH_data = 29.92;//气压
double indicated_number = 200;

double attackAngle = 0;//攻角

double airSpeed = 120;
double vmo_speed = 0;
double airSpeed_acceleration = 0;
double airSpeed_mach = 0.5;
double airSpeed_instruction = 130;
double GS = 0;
double TAS = 166;
double WS = 0;//风速
double WD = 0;//风向

double rotationangle = 0;
//double pointrotationangle = 0; 
double compass_angle_original_data = 0;
int course = 0;
int HDGMAG = 95;
int course2 = 0;
int course3 = 0;

double RMI_point_angle_1 = 0;
double RMI_point_angle_2 = 0;
int RMI_change = 0;//左按钮变化
int RMI_change_1 = 0;//右按钮变化

//发动机相关
double Oangle_1 = 1;
double Oangle_2 = 2;
double Oangle_3 = 3;
double Oangle_4 = 4;

double fanSpeed = 5;
double fanSpeed_1 = 6;
double gastemp = 7;
double gastemp_1 = 8;
double FuelFlowSpeed = 2.04;
double FuelFlowSpeed_1 = 1.02;
int TAT = -7;


double Fuelrest_1 = 5.65;
double Fuelrest_2 = 0.02;
double Fuelrest_3 = 5.65;
double Fuelrest_total = Fuelrest_1 + Fuelrest_2 + Fuelrest_3;


double N21 = 3.3;
double N22 = 0.9;

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




//时间相关
int hour1;
int minute1;
int month1;
int date1;
int hour2;
int minute2;
int month2;
int date2;


//临时
double angle = 0;


//经纬度
double latitude = 28.877;
double longitude = 115.91;

//所存储的所有航点和nav信息
vector<WAYPOINT> waypoints;
vector<WAYPOINT> route;

//已经走过的航路点
vector<WAYPOINT> routePassed;
int nowPos = 0;//目前刚经过第几个航路点

//机场信息
vector<WAYPOINT> airports;

//VOR台信息
vector<WAYPOINT> VORs;


//经过的路线（航线）（显示在地图上）
vector<WAYPOINT> fullRoute;


//==================================//

//==========以下为设置相关==========//

////显示的界面（线程）
//// 1 - 机械表	 2 - 电子 
//int Page = 2;

//当前界面	0为默认六个机械仪表
// 仅限于机械表时不同表的切换
int show = 10;

int ND_choice = 3;

//默认画布大小
int height = 800;
int length = 1200;

//新窗口显示范围
int ifNewWindows = 0;//是否弹窗显示新窗口
double windwsShow_x = 0;//新窗口需要显示的左上角x坐标
double windwsShow_y = 0;//新窗口需要显示的左上角y坐标
double windwsShow_lenth = 0;//新窗口需要显示的x长度
double windwsShow_height = 0;//新窗口需要显示的y高度

//默认显示背景
int is_showbk = 1;

//默认不开启UDP通信
int UDP_transmission = 0;

//初始IP地址和端口
char *IP_address = "192.168.0.0";
int UDP_port = 49001;

//展示FPS
int showFPS = 1;

//表盘灯光效果
int G_light = 0x00;

double OUTBDangle = 200;
double INBDangle = 200;
double LOWERangle = 0;
double LOWERangle_1 = 0;
double INBDangle_1 = 0;
double UPPERangle = 0;
double Brightangle = -20;
double changecolor = 0;
int MainPanelLight = 0;

PIMAGE pimg1;
PIMAGE pimg2;
PIMAGE pimg3;
PIMAGE pimg4;
PIMAGE pimg5;
PIMAGE pimg6;
PIMAGE pimg7;
PIMAGE pimg8;
PIMAGE pimg9;
PIMAGE pimg10;
PIMAGE pimg11;
PIMAGE pimg12;
PIMAGE pimg13;

PIMAGE pimg1sta;
PIMAGE pimg2sta;
PIMAGE pimg3sta;
PIMAGE pimg4sta;
PIMAGE pimg5sta;
PIMAGE pimg6sta;
PIMAGE pimg7sta;
PIMAGE pimg8sta;
PIMAGE pimg9sta;
PIMAGE pimg10sta;
PIMAGE pimg11sta;
PIMAGE pimg12sta;
PIMAGE pimg13sta;

//==================================//

//==========以下为警告信息==========//

int alert_pullup = 0;
int alert_beloGS = 0;
int alert_ALT = 0;
int alert_MDA = 0;
int alert_autoPilot = 0;



//==================================//

//==========以下为控制板信息==========//

//旋钮面板
double MINSKonb = 0;
double MINSRef = 125;
double baroKnob = 0;
double baroUnit = 125;
double EHISMode = 135;
double mapDistance = 0;
int RST = 0;
int STD = 0;
int CTR = 1;
int TFC = 0;

int FPV = 0;
int MTRS = 0;

int WXR = 1;
int STA = 1;
int WPT = 1;
int ARPT = 1;
int DATA = 0;
int POS = 0;
int TERR = 0;

int VOR1 = 2;
int VOR2 = 2;

double backGroundLight = -20;
double AFDSFLOODLight = -20;

double MainpanelDU = 75;
double LOWERDU = 75;
int MainpanelDU_gear = 0;
int LOWERDU_gear = 0;


