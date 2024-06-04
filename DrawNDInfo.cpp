#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>
#include "G_structs.h"

//函数头文件
double toRadians(double a);
double getDistance(double latitude1, double longitude1, double latitude2, double longitude2);
void draw_waypoint(WAYPOINT wp1, WAYPOINT wp2, double dir, double ratio,double x, double y, double side);
double getBearing(double lat1, double lon1, double lat2, double lon2);



//测算比例可知，在单位长度5海里时，ND上距离5390m = 5.390km = 2.910367海里(nmi) = 16.553/186*side (即0.08890)
//则在单位长度5海里时，1km显示在ND上为0.016511*side；单位长度1海里时，1km显示为0.082555*side
//==============================以上作废===========================//


//测算比例可知，在单位长度5海里时，ND上距离2560m = 2.56km = 1.3822894海里(nmi) = 16.553/186*side (即0.08890)
//则在单位长度5海里时，1km显示在ND上为0.0347635*side；单位长度1海里时，1km显示为0.1738176*side



//绘制航路点（三角形）

void draw_waypoint(WAYPOINT wp1, WAYPOINT wp2, double dir, double ratio,double x, double y, double side){
	
	double dis = getDistance(wp1.lat, wp1.lon, wp2.lat, wp2.lon);
	double bearing = getBearing(wp1.lat, wp1.lon, wp2.lat, wp2.lon);
	
	double rside = 0.010752 * side;
	double rhigh = 0.015129 * side;
	double rl = dis / 1000 * 0.1738176 * side / ratio;
	double rx = (cos(toRadians(bearing - dir - 90)) * rl) + x;
	double ry = (sin(toRadians(bearing - dir - 90)) * rl) + y;
	
	ege_point pointTmp[4] = {
		{rx,ry - rhigh / 2},
		{rx - rside / 2,ry + rhigh / 2},
		{rx + rside / 2,ry + rhigh / 2},
		{rx,ry - rhigh / 2},
	};
	
	setlinewidth(0.001 * side);
	setcolor(WHITE);
	ege_drawpoly(4, pointTmp);
	
	if(0.01 * side > 5){
		setfont(0.01 * side, 0.01 * side , "黑体");
		ege_drawtext(wp2.name,rx,ry + rhigh / 2 + 0.005 * side);
	}
}


double toRadians(double a) {
	return a * (PI / 180);
}

//Vincenty公式计算两点距离
//return the distance of two point, unit is meter
double getDistance(double latitude1, double longitude1, double latitude2, double longitude2) {
	// R is the radius of the earth in meters
	double R = 6371004;  //EARTH_RADIUS
	double deltaLatitude = toRadians(latitude2-latitude1);
	double deltaLongitude = toRadians(longitude2-longitude1);
	latitude1 =toRadians(latitude1);
	latitude2 =toRadians(latitude2);
	double a = pow(sin(deltaLatitude/2), 2)+ cos(latitude1)* cos(latitude2)* pow(sin(deltaLongitude/2), 2);
	double c = 2 * atan2(sqrt(a),sqrt(1-a));
	
	double d = R * c;
	return d;
}

double getBearing(double lat1, double lon1, double lat2, double lon2){
	lat1 = toRadians(lat1);
	lat2 = toRadians(lat2);
	lon1 = toRadians(lon1);
	lon2 = toRadians(lon2);
	double dLon = lon2 - lon1;
	double y = sin(dLon) * cos(lat2);
	double x = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos( dLon);
	double brng = atan2(y, x);
	brng=brng * 180 / PI;
	brng = fmod((brng + 360), 360);
	return brng;
}

