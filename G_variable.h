//==================================//

//==========以下为飞行参数==========//

double pitchAngle = 0;
double rollAngle = 0;
double sideSlipAngle = 0;
double headingIndication = 0;
double glideIndication = 0;

double RCDI_speed = 0;
double verticalRate = 0;
double RNG = 56;//初始显示RNG 5

double altitude = 0;
double MILLIBARS_data = 0;
double INGH_data = 0;

double airSpeed = 0;
double vmo_speed = 0;

double rotationangle = 0;
//double pointrotationangle = 0; 
double compass_angle_original_data = 0;

double RMI_point_angle_1 = 0;
double RMI_point_angle_2 = 0;

//临时
double angle = 0;



//==================================//

//==========以下为设置相关==========//


//默认画布大小
int height = 800;
int length = 1200;

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


//==================================//

//==========以下为警告信息==========//

int alert_pullup = 0;
int alert_beloGS = 0;
int alert_ALT = 0;
int alert_MDA = 0;
int alert_autoPilot = 0;

