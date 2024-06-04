#include <windows.h> 
#include <graphics.h> 

#include "G_variable.h"

void get_keymsg() {
	//键盘模拟操作测试
	
	if (GetAsyncKeyState(0x41) & 0x8000)
		rollAngle -= 0.005;
	if (GetAsyncKeyState(0x44) & 0x8000)
		rollAngle += 0.005;
	if (GetAsyncKeyState(0x57) & 0x8000)
		pitchAngle += 0.005;
	if (GetAsyncKeyState(0x53) & 0x8000)
		pitchAngle -= 0.005;
	if (GetAsyncKeyState(0x4b) & 0x8000) {
		if (sideSlipAngle / PI * 360 <= 45) {
			sideSlipAngle += 0.002;
		}
	}
	if (GetAsyncKeyState(0x4a) & 0x8000) {
		if (sideSlipAngle / PI * 360 >= -45) {
			sideSlipAngle -= 0.002;
		}
	}
	
	
	if (GetAsyncKeyState(0x4c) & 0x8000) {
		if (glideIndication <= 2) {
			glideIndication += 0.02;
		}
	}
	if (GetAsyncKeyState(0x4d) & 0x8000) {
		if (glideIndication >= -2) {
			glideIndication -= 0.02;
		}
	}
	
	if (GetAsyncKeyState(0x51) & 0x8000) {
		if (headingIndication >= -1) {
			headingIndication -= 0.01;
		}
	}
	if (GetAsyncKeyState(0x45) & 0x8000) {
		if (headingIndication <= 1) {
			headingIndication += 0.01;
		}
	}
	
	
	if (GetAsyncKeyState(0x5a) & 0x8000) {
		if (airSpeed < 800) {
			airSpeed += 1;
		}
	}
	if (GetAsyncKeyState(0x58) & 0x8000) {
		if (airSpeed > -5) {
			airSpeed -= 1;
		}
	}
	
	
	if (GetAsyncKeyState(0x42) & 0x8000) {
		if (RCDI_speed < 9999) {
			verticalRate += 10;
		}
	}
	if (GetAsyncKeyState(0x4e) & 0x8000) {
		if (RCDI_speed > -9999) {
			verticalRate -= 10;
		}
	}
	
	if (GetAsyncKeyState(0x49) & 0x8000) {
		if (altitude < 99999) {
			altitude += 10;
			MILLIBARS_data += 3;
			INGH_data += 2;
		}
	}
	if (GetAsyncKeyState(0x4f) & 0x8000) {
		if (altitude > -99999) {
			altitude -= 10;
			MILLIBARS_data -= 3;
			INGH_data -= 2;
		}
	}
	
	
	if (GetAsyncKeyState(0x47) & 0x8000) {
		if (angle <= 360) {
			angle += 1;
		}
	}
	if (GetAsyncKeyState(0x48) & 0x8000) {
		if (angle >= 0) {
			angle -= 1;
		}
	}
	
	if (GetAsyncKeyState(0x31) & 0x8000) {
		if (compass_angle_original_data <= 360) {
			compass_angle_original_data += 1;
		}
	}
	if (GetAsyncKeyState(0x32) & 0x8000) {
		if (compass_angle_original_data >= 0) {
			compass_angle_original_data -= 1;
		}
	}
	
	
}
