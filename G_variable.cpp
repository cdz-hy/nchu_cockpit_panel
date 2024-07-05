#include <vector>
#include<graphics.h>
#include <mutex>
# include <condition_variable>
# include <functional>
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
double driftAngle = 0;//偏流角（左右）
double pathAngle = 0;//航迹角（上下）

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

//FMC表需要打开的文件名
char FMCFileName[20];

//==================================//

//==========以下为设置相关==========//

////显示的界面（线程）
//// 1 - 机械表	 2 - 电子 
//int Page = 2;

//程序所在绝对路径
WCHAR path[MAX_PATH];

//当前界面	0为默认六个机械仪表
// 仅限于机械表时不同表的切换
int show = 10;

int ND_choice = 3;

//默认画布大小
int height = 800;
int length = 1200;

//ege窗口上下文
HDC egeHDC = nullptr;
HWND egeHWND = nullptr;

//新窗口显示范围
int ifNewWindows = 0;//是否弹窗显示新窗口
double windwsShow_x = 0;//新窗口需要显示的左上角x坐标
double windwsShow_y = 0;//新窗口需要显示的左上角y坐标
double windwsShow_lenth = 0;//新窗口需要显示的x长度
double windwsShow_height = 0;//新窗口需要显示的y高度

//新窗口所需
std::mutex mtx;
std::condition_variable cv;
bool ready = true;

mutex g_globalMutex;

//默认显示背景
int is_showbk = 1;

//默认不开启UDP通信
int UDP_transmission = 0;

//初始IP地址和端口
char *IP_address = "192.168.0.0";
int UDP_port = 49001;

// 子进程ege窗口的大小
int egeWidth = 400;
int egeHeight = 400;

// 子进程egeFMC窗口大小
int egeFMCWidth = 600;
int egeFMCHeight = 800;

//map上打印的数据
char mapProvince[64] = "安徽省";
char mapCity[64] = "合肥市";
char mapAdcode[64] =  "合肥工业大学";
char mapTownship[64] = "丰和南大道696号";
char mapStreet[64] = "幸福大道";
char mapWeather[64] = "晴朗";
char mapTemperature[64] = "30";
char mapWinddirection[64] = "西北风";
char mapWindpower[64] = "2";
char mapHumidity[64] = "潮湿";

//是否显示地图
int showMap = 0;

//是否显示pfd
int showPFDJudge = 0;

//是否显示nd 
int showNDJudge = 0;

//是否显示EICAS
int showEICASJudge = 0;

//是否显示EICAS2
int showEICAS2Judge = 0;

// 是否显示FMC
int showFMCJudge = 0;

//地图更新状态
int renewMap = 1;

//展示FPS
int showFPS = 1;

//表盘灯光效果
int G_light = 0x00;

double OUTBDangle = 200;
double INBDangle = 200;
double LOWERangle = 200;
double LOWERangle_1 = 0;
double INBDangle_1 = 0;
double UPPERangle = 200;
double Brightangle = 200;
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
PIMAGE pimg14;
PIMAGE pimg15;
PIMAGE pimg16;
PIMAGE pimg17;
PIMAGE pimg18;
PIMAGE pimg19;
PIMAGE pimg20;
PIMAGE pimg21;
PIMAGE pimg22;
PIMAGE pimg23;
PIMAGE pimg24;
PIMAGE pimg25;
PIMAGE pimg26;
PIMAGE pimg27;
PIMAGE pimg28;
PIMAGE pimg29;
PIMAGE pimg30;
PIMAGE pimg31;
PIMAGE pimg32;

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
PIMAGE pimg14sta;
PIMAGE pimg15sta;
PIMAGE pimg16sta;
PIMAGE pimg17sta;
PIMAGE pimg18sta;
PIMAGE pimg19sta;
PIMAGE pimg20sta;
PIMAGE pimg21sta;
PIMAGE pimg22sta;
PIMAGE pimg23sta;
PIMAGE pimg24sta;
PIMAGE pimg25sta;
PIMAGE pimg26sta;
PIMAGE pimg27sta;
PIMAGE pimg28sta;
PIMAGE pimg29sta;
PIMAGE pimg30sta;
PIMAGE pimg31sta;
PIMAGE pimg32sta;

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
int gearCTR = 0;//A
int gearCTR_1 = 0;//B
double mapDistance = 0;
int gearTFC = 0;//A
int gearTFC_1 = 0;//B
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

double MainpanelDU = 120;
double LOWERDU = 120;
int MainpanelDU_gear = 1;
int LOWERDU_gear = 1;

//自动驾驶控制板
double COURSE_1 = 0;//0上1下
double COURSE_2 = 0;
int FD_1 = 0;
int FD_2 = 0;
int COURSE_1NUM = 110;
int change_COURSE_1NUM = 0;
int COURSE_2NUM = 110;
int change_COURSE_2NUM = 0;
int AT = 1;//0下1上

int N1 = 0;
int SPEED = 0;
int LVLCHG = 0;
int VNAV = 0;
int LNAV = 0;
int VORLOC = 0;
int APP = 0;
int HDGSEL = 0;
int CO = 0;//1显示左边，0显示右边
int CO_1 = 11;
int CO_1_change = 0;
int CO_2 = 110;//右边数字
int CO_2_change = 0;
int SPDINTV = 0;
double INSMACHangle = 0;
int HEADING = 100;
double HEADING_1 = 0;//上面那层
int HEADING_1_change = 0;
double HEADING_2 = 90;//下面那层
int ALTHLD = 0;
int VS = 0;
double ALTITUDEangle = 0;
int ALTITUDE = 99400;
int ALTITUDE_change = 0;
double VERTSPEEDangle = 0;
int VERTSPEED = -5000;
int VERTSPEED_change = 0;
int ALTINTV = 0;


int CMDA = 0;
int CWSA = 0;
int CWSB = 0;
int CMDB = 0;

int CMDA_1 = 0 ;
int CWSA_1 = 0;
int CWSB_1 = 0 ;
int CMDB_1  = 0;

int SPEED_1 = 0;
int FD_1_1 =0;
int HDGSEL_1 = 0;
int ALTHLD_1 = 0;
int VS_1 = 0;
int choicetransfromAUTO = 0;

//自动驾驶控制相关
double autopilot_mode = 0;
double flight_director_mode = 0;
double altitude_mode = 0;
double autopilot_bk_mode=0;
double altitude_bk_mode=0;
double flight_director_bk_mode=0;
int choicetransformAT = 0;

//方向舵
double SteeringWeelLevel = 0;
double SteeringWeelVertical = 0 ;
double SteeringWeelFootPedals = 0;
int choiceSteeringWeel = 0;
int transformSteeringWeel = 0;

//起落架
int stateLandingGear = 0;

//油门和刹车
int statebrake =0;//刹车接收
int statebrake_change =0;//刹车操作
double accelerator = 0;//油门
double accelerator_change = 0;//油门变化

//襟翼
double gearFlaps = 0;//襟翼接收A
double Flapschange = 0;//襟翼改变B