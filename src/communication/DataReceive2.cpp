#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>

#include "G_variable.h"
#include "xplaneConnect.h"

extern mutex dataMtx;
extern mutex dataMtx2;

void data_receive2(){
	
	dataMtx.lock();
	
	XPCSocket sock = openUDP(IP_address);
	
	dataMtx.unlock();
	
	for(;is_run();){
		
		//接收数据
	
		{

			const char* drefs[1] =
			{
				"sim/cockpit2/gauges/indicators/airspeed_acceleration_kts_sec_copilot",

			};
			float* results[1];
			int sizes[1] = { 20, };
			results[0] = (float*)malloc(20 * sizeof(float));
			if(getDREFs(sock, drefs, results, 1, sizes) == 0){
				getDREFs(sock, drefs, results, 1, sizes);
				airSpeed_acceleration = results[0][0];
			}
			free(results[0]);

		}


		{

			const char* drefs[1] =
			{
				"sim/cockpit/autopilot/autopilot_state",

			};
			float* results[1];
			int sizes[1] = { 20, };
			results[0] = (float*)malloc(20 * sizeof(float));
			if(getDREFs(sock, drefs, results, 1, sizes) == 0){
				getDREFs(sock, drefs, results, 1, sizes);
				autopilot_mode = results[0][0];
			}
			free(results[0]);

		}
		
		
		
		
		
		
		//回传数据
		
		if(transformSteeringWeel){
			
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
		
		
		if(ALTITUDE_change != 0){
			
			dataMtx2.lock();
			
			
			{
				
				printf("%d\n",ALTITUDE_change);
				
				const char* dref = "sim/cockpit/autopilot/altitude";
				float gear = ALTITUDE + ALTITUDE_change;
				int size = 1;
				sendDREF(sock, dref, &gear, 1);
				ALTITUDE_change = 0;
				ALTITUDEangle = 0;
				api_sleep(0);
//				printf("%d",ALTITUDE_change);
			}
			
			dataMtx2.unlock();
		}
		
		
		if(HEADING_1_change){
			
			dataMtx2.lock();
			
			const char* dref = "sim/cockpit/autopilot/heading";
			float gear = HEADING_1 + HEADING_1_change;
			int size = 1;
			sendDREF(sock, dref, &gear, 1);
			HEADING_1_change = 0;
			
			dataMtx2.unlock();
		}
		
		
		if(CO_2_change){
			
			dataMtx2.lock();
			
			printf("%d\n",CO_2_change);
			
			const char* dref = "sim/cockpit/autopilot/airspeed";
			float gear = CO_2 + CO_2_change;
			int size = 1;
			sendDREF(sock, dref, &gear, 1);
			CO_2_change = 0;
			
			dataMtx2.unlock();
			
		}
		
		
		if(VERTSPEED_change != 0){
			
			dataMtx2.lock();
			
			const char* dref = "sim/cockpit/autopilot/vertical_velocity";
			float gear = VERTSPEED + VERTSPEED_change;
			int size = 1;
			sendDREF(sock, dref, &gear, 1);
			VERTSPEED_change = 0;
			
			dataMtx2.unlock();
		}
		
		
		if(choicetransfromAUTO){
			
			dataMtx2.lock();
			
			{
				const char* dref = "sim/cockpit/autopilot/autopilot_state";
				float gear = autopilot_bk_mode;
				int size = 1;
				sendDREF(sock, dref, &gear, 1);
			}
			
			
			{
				const char* dref = "sim/cockpit2/autopilot/flight_director_mode";
				float gear = flight_director_bk_mode;
				int size = 1;
				sendDREF(sock, dref, &gear, 1);
			}
			
			{
				const char* dref = "sim/cockpit2/autopilot/altitude_mode";
				float gear = altitude_bk_mode;
				int size = 1;
				sendDREF(sock, dref, &gear, 1);
			}
			
			
			choicetransfromAUTO = 0;
			
			dataMtx2.unlock();
			
		}
		
		
		if(accelerator_change){
			
			dataMtx2.lock();
			
			{
				const char* dref = "sim/cockpit2/engine/actuators/throttle_ratio_all";
				float gear = accelerator + accelerator_change;
				int size = 1;
				
				printf("%f\n",accelerator + accelerator_change);
				sendDREF(sock, dref, &gear, 1);
				accelerator_change = 0;
			}
			
			
			dataMtx2.unlock();
			
		}
		
		
		extern int stateLandingGear_change;
		extern int stateLandingGear;
		
		if(stateLandingGear_change){
			
			dataMtx2.lock();
			
			{
				const char* dref = "sim/cockpit2/controls/gear_handle_down";
				float gear = stateLandingGear;
				int size = 1;
				
				sendDREF(sock, dref, &gear, 1);
				stateLandingGear_change = 0;
			}
			
			
			dataMtx2.unlock();
			
		}

		extern int statebrake_change;
		extern int statebrake;
		
		if(statebrake_change){
			
			dataMtx2.lock();
			
			{
				const char* dref = "sim/flightmodel/controls/parkbrake";
				float gear = statebrake;
				int size = 1;
				
				sendDREF(sock, dref, &gear, 1);
				statebrake_change = 0;
			}
			
			
			dataMtx2.unlock();
			
		}
		
		
		if(Flapschange){
			
			dataMtx2.lock();
			
			{
				const char* dref = "sim/multiplayer/controls/flap_request";
				float gear = gearFlaps;
				int size = 1;
				
				sendDREF(sock, dref, &gear, 1);
				Flapschange = 0;
			}
			
			
			dataMtx2.unlock();
			
		}
		
//		{
//			
//			printf("123456789\n\n");
//			
//			float data[1][9] = { 0 };
//			// Initialize data values to -998 to not overwrite values.
//			for (int i = 0; i < 1; i++)
//			{
//				for (int j = 0; j < 9; j++)
//				{
//					data[i][j] = -998;
//				}
//			}
//			
//			
//			data[0][0] = 118; // Alpha
//			data[0][1] = 100;
//			data[0][2] = 200;
//			data[0][3] = 300;
//			data[0][4] = 10000;
//			
//			sendDATA(sock, data, 1);
//			
//		}
		
	}
	
	
	closeUDP(sock);
	
}
