#include <vector>
#include "G_structs.h"
using namespace std;


//==================================//

//==========以下为飞行参数==========//

extern double pitchAngle;
extern double rollAngle;
extern double sideSlipAngle;
extern double headingIndication;
extern double glideIndication;
extern double ndtoprotationangle;

extern double RCDI_speed;
extern double verticalRate;
extern double RNG;//初始显示RNG 5

extern double altitude;
extern double MILLIBARS_data;
extern double INGH_data;
extern double indicated_number;

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

extern double RMI_point_angle_1;
extern double RMI_point_angle_2;
extern int RMI_change;//左按钮变化
extern int RMI_change_1;//右按钮变化

//发动机相关
extern double Oangle_1;
extern double Oangle_2;
extern double fanSpeed;
extern double gastemp;
extern double FuelFlowSpeed;
extern double Fuelrest_1;
extern double Fuelrest_2;
extern double Fuelrest_3;
extern double Fuelrest_total;

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

extern double Anum;

//经纬度
extern double latitude;
extern double longitude;

//所存储的所有航点和nav信息
extern vector<WAYPOINT> waypoints;
extern vector<WAYPOINT> route;

//已经走过的航线
extern vector<WAYPOINT> routePassed;

//机场信息
extern vector<WAYPOINT> airports;

//VOR台信息
extern vector<WAYPOINT> VORs;

//==================================//

//==========以下为设置相关==========//

//当前界面	0为默认六个机械仪表
extern int show;

extern int ND_choice;

//默认画布大小
extern int height;
extern int length;

//默认显示背景
extern int is_showbk;

//默认不开启UDP通信
extern int UDP_transmission;

//初始IP地址和端口
extern char *IP_address;
extern int UDP_port;

//展示FPS
extern int showFPS;

//表盘灯光效果
extern int G_light;


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
extern double changecolor;
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
extern int MainPanelLight;
