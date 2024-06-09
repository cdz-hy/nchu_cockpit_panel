#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>

#include "G_variable.h"
#include "xplaneConnect.h"

void data_receive(){
	
	for(;is_run();api_sleep(16)){
		
		
		if (UDP_transmission) {
			
			XPCSocket sock = aopenUDP(IP_address, UDP_port, UDP_port);
			
			//读取接收的信息
			const int rows = 18;
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
		
		
	}
	

}

