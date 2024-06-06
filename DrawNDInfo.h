#pragma once

#include "G_structs.h"

#include <vector>

//void draw_waypoint(WAYPOINT wp1, WAYPOINT wp2, double dir, double ratio,double x, double y, double side);
void draw_waypoint(WAYPOINT nowPos, double dir, double ratio,double x, double y, double side);

void draw_route(WAYPOINT wp, double dir, double ratio,double x, double y, double side);

void draw_waypoint_map(WAYPOINT nowPos, double dir, double ratio,double x, double y, double side);

void draw_route_map(WAYPOINT wp, double dir, double ratio,double x, double y, double side);
