#include <vector>
#include<graphics.h>
#include <mutex>
# include <condition_variable>
# include <functional>
#include "G_structs.h"
using namespace std;


//==================================//

//==========以下为飞行参数==========//

extern double pitchAngle;
extern double rollAngle;
extern double sideSlipAngle;
extern double headingIndication;
extern double glideIndication;
extern double ndpointrotationangle; 
extern double driftAngle;//偏流角（左右）
extern double pathAngle;//航迹角（上下）

extern double RCDI_speed;
extern double verticalRate;
extern double RNG;//初始显示RNG 5

extern double altitude;
extern double altitude2;//对地
extern double MILLIBARS_data;
extern double INGH_data;
extern double indicated_number;

extern double attackAngle;//攻角

extern double airSpeed;
extern double vmo_speed;
extern double airSpeed_acceleration;
extern double airSpeed_mach;
extern double airSpeed_instruction;
extern double GS;
extern double TAS;
extern double WS;
extern double WD;

extern double rotationangle;
//double pointrotationangle = 0; 
extern double compass_angle_original_data;
extern int course;
extern int HDGMAG;
extern int course2;
extern int course3;

extern double RMI_point_angle_1;
extern double RMI_point_angle_2;
extern int RMI_change;//左按钮变化
extern int RMI_change_1;//右按钮变化

//发动机相关
extern double Oangle_1;
extern double Oangle_2;
extern double Oangle_3;
extern double Oangle_4;
extern double fanSpeed;
extern double fanSpeed_1 ;
extern double gastemp ;
extern double gastemp_1 ;
extern double FuelFlowSpeed;
extern double FuelFlowSpeed_1;
extern double Fuelrest_1;
extern double Fuelrest_2;
extern double Fuelrest_3;
extern double Fuelrest_total;
extern int TAT;


extern double N21;
extern double N22;

extern double FF1;
extern double FF2;

extern double oilPress1;
extern double oilPress2;

extern double oilTemp1;
extern double oilTemp2;

extern double oilQTY1;
extern double oilQTY2;

extern double VIB1;
extern double VIB2;



//时间相关
extern int hour1;
extern int minute1;
extern int month1;
extern int date1;
extern int hour2;
extern int minute2;
extern int month2;
extern int date2;


//临时
extern double angle;


//经纬度
extern double latitude;
extern double longitude;

//所存储的所有航点和nav信息
extern vector<WAYPOINT> waypoints;
extern vector<WAYPOINT> route;

//已经走过的航线
extern vector<WAYPOINT> routePassed;
extern int nowPos;//目前刚经过第几个航路点

//机场信息
extern vector<WAYPOINT> airports;

//VOR台信息
extern vector<WAYPOINT> VORs;

//经过的路线（航线）（显示在地图上）
extern vector<WAYPOINT> fullRoute;

//FMC表需要打开的文件名
extern char FMCFileName[20];

//==================================//

//==========以下为设置相关==========//

//显示的界面（线程）
//// 1 - 机械表	 2 - 电子 
//extern int Page;

//程序所在绝对路径
extern WCHAR path[MAX_PATH];

//当前界面	0为默认六个机械仪表
extern int show;

extern int ND_choice;

//默认画布大小
extern int height;
extern int length;

//ege窗口上下文
extern HDC egeHDC;
extern HWND egeHWND;

//新窗口显示范围
extern int ifNewWindows;//是否弹窗显示新窗口
extern double windwsShow_x;//新窗口需要显示的左上角x坐标
extern double windwsShow_y;//新窗口需要显示的左上角y坐标
extern double windwsShow_lenth;//新窗口需要显示的x长度
extern double windwsShow_height;//新窗口需要显示的y高度

//新窗口所需 
extern std::mutex mtx;
extern std::condition_variable cv;
extern bool ready;

extern mutex g_globalMutex;

//默认显示背景
extern int is_showbk;

//默认不开启UDP通信
extern int UDP_transmission;

// 子进程ege窗口的大小
extern int egeWidth;
extern int egeHeight;

// 子进程egeFMC窗口的大小
extern int egeFMCWidth;
extern int egeFMCHeight;

// map上打印的数据
extern char mapProvince[64];
extern char mapCity[64];
extern char mapAdcode[64];
extern char mapWeather[64];
extern char mapTemperature[64];
extern char mapWinddirection[64];
extern char mapWindpower[64];
extern char mapHumidity[64];
extern char mapTownship[64];
extern char mapStreet[64];

//是否显示地图
extern int showMap;

//是否显示pfd
extern int showPFDJudge;

//是都显示nd
extern int showNDJudge;

//是否显示EICAS
extern int showEICASJudge;

//是否显示EICAS2
extern int showEICAS2Judge;

//是否显示FMC
extern int showFMCJudge;

//地图更新状态
extern int renewMap;

//初始IP地址和端口
extern char* IP_address;
extern int UDP_port;

//地图更新状态
extern int renewMap;

//地图更新状态
extern int renewMap;

//展示FPS
extern int showFPS;

//表盘灯光效果
extern int G_light;

//控制板
extern double OUTBDangle;
extern double INBDangle;
extern double LOWERangle;
extern double LOWERangle_1;
extern double INBDangle_1;
extern double UPPERangle;
extern double Brightangle;
extern double changecolor;
extern int MainPanelLight;


extern PIMAGE pimg1;
extern PIMAGE pimg2;
extern PIMAGE pimg3;
extern PIMAGE pimg4;
extern PIMAGE pimg5;
extern PIMAGE pimg6;
extern PIMAGE pimg7;
extern PIMAGE pimg8;
extern PIMAGE pimg9;
extern PIMAGE pimg10;
extern PIMAGE pimg11;
extern PIMAGE pimg12;
extern PIMAGE pimg13;
extern PIMAGE pimg14;
extern PIMAGE pimg15;
extern PIMAGE pimg16;
extern PIMAGE pimg17;
extern PIMAGE pimg18;
extern PIMAGE pimg19;
extern PIMAGE pimg20;
extern PIMAGE pimg21;
extern PIMAGE pimg22;
extern PIMAGE pimg23;
extern PIMAGE pimg24;
extern PIMAGE pimg25;
extern PIMAGE pimg26;
extern PIMAGE pimg27;
extern PIMAGE pimg28;
extern PIMAGE pimg29;
extern PIMAGE pimg30;

extern PIMAGE pimg32;

extern PIMAGE pimg1sta;
extern PIMAGE pimg2sta;
extern PIMAGE pimg3sta;
extern PIMAGE pimg4sta;
extern PIMAGE pimg5sta;
extern PIMAGE pimg6sta;
extern PIMAGE pimg7sta;
extern PIMAGE pimg8sta;
extern PIMAGE pimg9sta;
extern PIMAGE pimg10sta;
extern PIMAGE pimg11sta;
extern PIMAGE pimg12sta;
extern PIMAGE pimg13sta;
extern PIMAGE pimg14sta;
extern PIMAGE pimg15sta;
extern PIMAGE pimg16sta;
extern PIMAGE pimg17sta;
extern PIMAGE pimg18sta;
extern PIMAGE pimg19sta;
extern PIMAGE pimg20sta;
extern PIMAGE pimg21sta;
extern PIMAGE pimg22sta;
extern PIMAGE pimg23sta;
extern PIMAGE pimg24sta;
extern PIMAGE pimg25sta;
extern PIMAGE pimg26sta;
extern PIMAGE pimg27sta;
extern PIMAGE pimg28sta;
extern PIMAGE pimg29sta;
extern PIMAGE pimg30sta;

extern PIMAGE pimg32sta;
//==================================//

//==========以下为警告信息==========//

extern int alert_pullup;
extern int alert_beloGS;
extern int alert_ALT;
extern int alert_MDA;
extern int alert_autoPilot;

//==================================//

//==========以下为控制板信息==========//

//旋钮面板
extern double MINSKonb;
extern double MINSRef;
extern double baroKnob;
extern double baroUnit;
extern double EHISMode;
extern double mapDistance;
extern int gearCTR;//A
extern int  gearCTR_1;//B
extern int gearTFC;//A
extern int gearTFC_1;//B
extern int FPV;
extern int MTRS;
extern int RST;
extern int STD;
extern int CTR;
extern int TFC;
extern int WXR;
extern int STA;
extern int WPT;
extern int ARPT;
extern int DATA;
extern int POS;
extern int TERR;
extern int VOR1;
extern int VOR2;

extern double backGroundLight ;
extern double AFDSFLOODLight ;

extern double MainpanelDU;
extern double LOWERDU;
extern int MainpanelDU_gear;
extern int LOWERDU_gear;

//自动驾驶控制板
extern int MainPanelLight;
extern double COURSE_1;
extern double COURSE_2;
extern int FD_1;
extern int FD_2;
extern int COURSE_1NUM;//左边course示数
extern int change_COURSE_1NUM;
extern int COURSE_2NUM;//右边course示数
extern int change_COURSE_2NUM;
extern int AT;
extern int N1;
extern int SPEED;
extern int LVLCHG;
extern int VNAV;
extern int LNAV;
extern int VORLOC;
extern int APP;
extern int HDGSEL;
extern int CO;//1为左，0为右
extern int CO_1;//左边显示
extern int CO_1_change;
extern int CO_2 ;//右边显示
extern int CO_2_change;
extern int SPDINTV;
extern double INSMACHangle;
extern int HEADING;
extern double HEADING_1;
extern int HEADING_1_change;
extern double HEADING_2;
extern int ALTHLD;
extern int VS;
extern double ALTITUDEangle;
extern int ALTITUDE;
extern int ALTITUDE_change;
extern double VERTSPEEDangle;
extern int VERTSPEED;
extern int VERTSPEED_change;
extern int ALTINTV;

extern int CMDA ;
extern int CWSA ;
extern int CWSB ;
extern int CMDB ;

extern int SPEED_1;
extern int FD_1_1;
extern int HDGSEL_1 ;
extern int ALTHLD_1 ;
extern int VS_1 ;
extern int choicetransfromAUTO;


//自动驾驶控制相关
extern double autopilot_mode;
extern double flight_director_mode ;


//方向舵
extern double SteeringWeelLevel;
extern double SteeringWeelVertical;
extern double SteeringWeelFootPedals;
extern int choiceSteeringWeel;
extern int transformSteeringWeel;

//起落架
extern int stateLandingGear;

//油门和刹车
extern int statebrake ;//刹车
extern double accelerator;//油门
extern double accelerator_change;//油门变化
extern int statebrake_change;//刹车操作