#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>

#include "G_variable.h"
#include "xplaneConnect.h"

extern mutex dataMtx;

void data_receive2(){
	
	dataMtx.lock();
	
	XPCSocket sock = openUDP("10.83.8.124");
	
	dataMtx.unlock();
	
	for(;is_run();){
		
		//接收数据
	
		const char* drefs[1] =
		{
			"sim/cockpit2/gauges/indicators/airspeed_acceleration_kts_sec_copilot",
		};
		float* results[1];
		int sizes[1] = { 20, };
		for (int i = 0; i < 1; ++i)
		{
			results[i] = (float*)malloc(20 * sizeof(float));
		}
		if(getDREFs(sock, drefs, results, 1, sizes) == 0){
			getDREFs(sock, drefs, results, 1, sizes);
			airSpeed_acceleration = results[0][0];
		}
		
		
		
		//回传数据
		
		if(choiceSteeringWeel){
			
			{
				const char* dref = "sim/joystick/FC_ptch";
				float gear = SteeringWeelVertical;
				int size = 1;
				sendDREF(sock, dref, &gear, 1);
			}
			
			
			
			{
				const char* dref = "sim/joystick/FC_roll";
				float gear = SteeringWeelLevel;
				int size = 1;
				sendDREF(sock, dref, &gear, 1); 
				
				
				dref = "sim/joystick/FC_hdng";
				gear = 0.5 * SteeringWeelFootPedals;
				sendDREF(sock, dref, &gear, 1); 
			}
		
		}
		
		
	}
	
	
	closeUDP(sock);
	
}
