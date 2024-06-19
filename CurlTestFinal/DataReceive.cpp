#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>

#include "G_variable.h"
#include "xplaneConnect.h"

double getDis(double latitude1, double longitude1, double latitude2, double longitude2);

void data_receive(){
	
	for(;is_run();api_sleep(16)){
		
		
		if (UDP_transmission) {
			
			XPCSocket sock = aopenUDP(IP_address, UDP_port, UDP_port);
			
			//读取接收的信息
			const int rows = 28;
			float data[rows][9] = {0};
			if (readDATA(sock, data, rows) && data[1][1] > 0) {
				
//				for(int i = 0; i ++; i < rows){
//					
//					if((int)data[i][0] == 17){
//						pitchAngle = data[i][1];
//						rollAngle = data[i][2];
//					}
//					else if((int)data[i][0] == 18){
//						sideSlipAngle = -data[i][8] * PI / 4 / 16;
//					}
//					else if((int)data[i][0] == 20){
//						altitude = data[i][6];
//					}
//					else if((int)data[i][0] == 7){
//						INGH_data = data[i][1];
//						MILLIBARS_data = INGH_data * 33.8639;
//					}
//					else if((int)data[i][0] == 3){
//						airSpeed = data[i][1];
//					}
//					else if((int)data[i][0] == 4){
//						vmo_speed = data[i][1] * 10;
//					}
//					
//				}
				
				for(int i = 0; i < rows; i ++){
					
					if(fabs(data[i][0] - 17) <= 0.001){
						pitchAngle = data[i][1] * PI / 180;
						rollAngle = -data[i][2] * PI / 180;
						rotationangle = data[i][4];
						ndpointrotationangle = data[i][3];//临时航迹
//						 = data[i][3];
					}
					else if(fabs(data[i][0] - 18) <= 0.001){
						sideSlipAngle = -data[i][8] * PI / 4 / 16 * 0.7;
						attackAngle = data[i][1];
					}
					else if(fabs(data[i][0] - 20) <= 0.001){
						altitude = data[i][6];
						altitude2 = data[i][4] - 4;
						latitude = data[i][1];
						longitude = data[i][2];
						
					}
					else if(fabs(data[i][0] - 7) <= 0.001){
						INGH_data = data[i][1];
						MILLIBARS_data = INGH_data * 33.8639;
					}
					else if(fabs(data[i][0] - 3) <= 0.001){
						airSpeed = data[i][1];
						TAS = data[i][3];
					}
					else if(fabs(data[i][0] - 4) <= 0.001){
						vmo_speed = data[i][1] * 10;
						verticalRate = data[i][3];
					}
					else if(fabs(data[i][0] - 32) <= 0.001){
						vmo_speed = data[i][1] * 10;
						verticalRate = data[i][3];
					}
					else if(fabs(data[i][0] - 41) <= 0.001){
						fanSpeed = data[i][1];
						fanSpeed_1 = data[i][2];
					}
					else if(fabs(data[i][0] - 42) <= 0.001){
						N21 = data[i][1];
						N22 = data[i][2];
					}
					else if(fabs(data[i][0] - 45) <= 0.001){
						FuelFlowSpeed = data[i][1] / 1000;
						FuelFlowSpeed_1 = data[i][2] / 1000;
						FF1 = FuelFlowSpeed;
						FF2 = FuelFlowSpeed_1;
					}
					else if(fabs(data[i][0] - 47) <= 0.001){
						gastemp = data[i][1];
						gastemp_1 = data[i][2];
					}
					else if(fabs(data[i][0] - 49) <= 0.001){
						oilPress1 = data[i][1];
						oilPress2 = data[i][2];
					}
					else if(fabs(data[i][0] - 50) <= 0.001){
						oilTemp1 = data[i][1];
						oilTemp2 = data[i][2];
					}
					else if(fabs(data[i][0] - 62) <= 0.001){
						Fuelrest_1 = data[i][1] / 1000;
						Fuelrest_2 = data[i][2] / 1000;
						Fuelrest_3 = data[i][3] / 1000;
						Fuelrest_total = Fuelrest_1 + Fuelrest_2 + Fuelrest_3;
					}
					else if(fabs(data[i][0] - 118) <= 0.001){
						airSpeed_instruction = data[i][1];
						indicated_number = data[i][4];
					}
				}
				
//				pitchAngle = data[3][1] * PI / 180;
//				rollAngle = -data[3][2] * PI / 180;
//
//				sideSlipAngle = -data[4][8] * PI / 4 / 16;
//
//				airSpeed = data[0][1];
//				vmo_speed = data[1][1] * 10;
//
//				verticalRate = data[1][3];
//
//				altitude = data[6][6];
//
//				INGH_data = data[2][1];
//
//				MILLIBARS_data = INGH_data * 33.8639;
//				
//				rotationangle = data[3][4];
//				compass_angle_original_data = data[10][1];
//				
//				latitude = data[6][1];
//				longitude = data[6][2];
				
			}
			
			closeUDP(sock);
		}
		
		//记录经过的完整航线
		if(fabs(fmod(fclock(),1)) <= 0.01){
			WAYPOINT wpTmp = {0, "", latitude, longitude,};
			fullRoute.push_back(wpTmp);
		}
		
		//判断经纬度是不是在下一个的范围内，如果在就加入已经经过的航线中
		if(getDis(latitude, longitude, route[nowPos].lat, route[nowPos].lon) <= 1860){
			routePassed.push_back(route[nowPos]);
			nowPos ++;
		}
		
	}
	

}




//转弧度制(临时)
double toRad(double a) {
	return a * (PI / 180);
}
//Vincenty公式计算两点距离(临时)
double getDis(double latitude1, double longitude1, double latitude2, double longitude2) {
	// R is the radius of the earth in meters
	double R = 6371004;  //EARTH_RADIUS
	double deltaLatitude = toRad(latitude2-latitude1);
	double deltaLongitude = toRad(longitude2-longitude1);
	latitude1 =toRad(latitude1);
	latitude2 =toRad(latitude2);
	double a = pow(sin(deltaLatitude/2), 2)+ cos(latitude1)* cos(latitude2)* pow(sin(deltaLongitude/2), 2);
	double c = 2 * atan2(sqrt(a),sqrt(1-a));
	double d = R * c;
	return d;
}
