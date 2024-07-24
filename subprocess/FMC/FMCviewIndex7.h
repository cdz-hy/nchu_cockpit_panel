#pragma once

struct rountpoint
{
	char rountpoints[10][7];
};

void draw_FPLN_panel_7(double side, double center_x, double center_y);
void FMC_Scanner_panel_7(char* information, int FMC_keyword);
rountpoint FMC_getpointsinformation();
