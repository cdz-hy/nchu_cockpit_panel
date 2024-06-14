#include <vector>
#include<graphics.h>
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

//==================================//

//==========以下为设置相关==========//

//显示的界面（线程）
//// 1 - 机械表	 2 - 电子 
//extern int Page;

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
extern char* IP_address;
extern int UDP_port;

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

extern PIMAGE pimg1sta;
extern PIMAGE pimg2sta;
extern PIMAGE pimg3sta;
extern PIMAGE pimg4sta;
extern PIMAGE pimg5sta;
extern PIMAGE pimg6sta;

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
