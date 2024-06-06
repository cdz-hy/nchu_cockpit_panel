#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <math.h>
#include <vector>
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

extern vector<WAYPOINT> waypoints;

void draw_waypoint(WAYPOINT nowPos, double dir, double ratio,double x, double y, double side){
	
	for(auto wp : waypoints){
		
		if(fabs(wp.lat - nowPos.lat) > 0.3 || fabs(wp.lon - nowPos.lon) > 0.3){
			continue;
		}
		
		
		double dis = getDistance(nowPos.lat, nowPos.lon, wp.lat, wp.lon);
		double bearing = getBearing(nowPos.lat, nowPos.lon, wp.lat, wp.lon);
		
		double rside = 0.010752 * side;
		double rhigh = 0.015129 * side;
		double rl = dis / 1000 * 0.1738176 * side / ratio;
		double rx = (cos(toRadians(bearing - dir - 90)) * rl) + x;
		double ry = (sin(toRadians(bearing - dir - 90)) * rl) + y;
		
		//当航路点在圆内时再绘制
		if(pow(rl, 2) <= pow(side / 104 * 40, 2)){
			
			ege_point pointTmp[4] = {
				{rx,ry - rhigh / 3},
				{rx - rside / 2,ry + rhigh / 2},
				{rx + rside / 2,ry + rhigh / 2},
				{rx,ry - rhigh / 3},
			};
			
			setlinewidth(0.001 * side);
//		setcolor(WHITE);
			setcolor(EGEARGB(0xff,0x64,0x7B,0x94));
			ege_drawpoly(4, pointTmp);
			
			if(0.01 * side > 5){
				setfont(0.01 * side, 0.01 * side , "黑体");
				ege_drawtext(wp.name,rx,ry + rhigh / 2 + 0.007 * side);
			}
			
		}
		
	}
	

}


//绘制机场（圆形）

extern vector<WAYPOINT> airports;
void draw_airports(WAYPOINT nowPos, double dir, double ratio,double x, double y, double side){
	
	
	
	for(auto wp : airports){
		
		if(fabs(wp.lat - nowPos.lat) > 0.3 || fabs(wp.lon - nowPos.lon) > 0.3){
			continue;
		}
		
		
		double dis = getDistance(nowPos.lat, nowPos.lon, wp.lat, wp.lon);
		double bearing = getBearing(nowPos.lat, nowPos.lon, wp.lat, wp.lon);
		
		double rside = 0.010752 * side;
		double rhigh = 0.015129 * side;
		double rl = dis / 1000 * 0.1738176 * side / ratio;
		double rx = (cos(toRadians(bearing - dir - 90)) * rl) + x;
		double ry = (sin(toRadians(bearing - dir - 90)) * rl) + y;
		
		//当航路点在圆内时再绘制
		if(pow(rl, 2) <= pow(side / 104 * 40, 2)){
			
			setlinewidth(0.001 * side);
			setcolor(WHITE);
			ege_ellipse(rx - rhigh / 2, ry - rhigh / 2, rhigh, rhigh);
			
			if(0.01 * side > 5){
				setcolor(WHITE);
				setfont(0.01 * side, 0.01 * side , "黑体");
				
				ege_drawtext(wp.name,rx,ry);
			}
			
		}
		
	}
}


//绘制VOR台（六边形）

extern vector<WAYPOINT> VORs;
void draw_VORs(WAYPOINT nowPos, double dir, double ratio,double x, double y, double side){
	
	
	
	for(auto wp : VORs){
		
		if(fabs(wp.lat - nowPos.lat) > 0.3 || fabs(wp.lon - nowPos.lon) > 0.3){
			continue;
		}
		
		
		double dis = getDistance(nowPos.lat, nowPos.lon, wp.lat, wp.lon);
		double bearing = getBearing(nowPos.lat, nowPos.lon, wp.lat, wp.lon);
		
		double rside = 0.010752 * side;
		double rhigh = 0.015129 * side;
		double rl = dis / 1000 * 0.1738176 * side / ratio;
		double rx = (cos(toRadians(bearing - dir - 90)) * rl) + x;
		double ry = (sin(toRadians(bearing - dir - 90)) * rl) + y;
		
		//当点在圆内时再绘制
		if(pow(rl, 2) <= pow(side / 104 * 40, 2)){
			
			setlinewidth(0.001 * side);
			setfillcolor(WHITE);
			ege_ellipse(rx - rhigh / 2, ry - rhigh / 2, rhigh, rhigh);
			
			if(0.01 * side > 5){
				setcolor(WHITE);
				setfont(0.01 * side, 0.01 * side , "黑体");
				
				ege_drawtext(wp.name,rx,ry);
			}
			
			
		}
		
	}
}


extern vector<WAYPOINT> route;
extern vector<WAYPOINT> routePassed;

void draw_route(WAYPOINT wp, double dir, double ratio,double x, double y, double side){
	
	for(auto it = route.begin(); it + 1 != route.end(); it ++){
		
		WAYPOINT wp1 = *(it);
		WAYPOINT wp2 = *(it + 1);
		
		double dis = getDistance(wp.lat, wp.lon, wp1.lat, wp1.lon);
		double bearing = getBearing(wp.lat, wp.lon, wp1.lat, wp1.lon);
		
//		double rside = 0.010752 * side;
//		double rhigh = 0.015129 * side;
		double rl = dis / 1000 * 0.1738176 * side / ratio;
		double rx = (cos(toRadians(bearing - dir - 90)) * rl) + x;
		double ry = (sin(toRadians(bearing - dir - 90)) * rl) + y;
		
		
		double dis2 = getDistance(wp.lat, wp.lon, wp2.lat, wp2.lon);
		double bearing2 = getBearing(wp.lat, wp.lon, wp2.lat, wp2.lon);
		
		double rl2 = dis2 / 1000 * 0.1738176 * side / ratio;
		double rx2 = (cos(toRadians(bearing2 - dir - 90)) * rl2) + x;
		double ry2 = (sin(toRadians(bearing2 - dir - 90)) * rl2) + y;
	
		//圆的直径
		double d = side / 104 * 40 * 2;
		
		setlinewidth(0.003 * side);
		
		//先判断这段路线是不是接下来的一段，从而设置不同颜色
		//警告：这里一旦尝试读取没有内容的vector的迭代器会导致程序直接闪退
		if(routePassed.size() > 0 && !strcmp((*(routePassed.end() - 1)).name, wp1.name)){
			
			setcolor(EGEARGB(0x99,0xa8,0x05,0xa8));
			
		}
		else{
			
//			setcolor(WHITE);
			setcolor(EGEARGB(0x66,0xff,0xff,0xff));
		}
		
		//先判断两点是不是都在范围内，如果都在，直接链接即可
		if(rx > x - d / 2 && rx < x + d / 2 && ry > y - d / 2 && ry < y + d / 2 && rx2 > x - d / 2 && rx2 < x + d / 2 && ry2 > y - d / 2 && ry2 < y + d / 2 ){
			//都在，不用处理
			ege_line(rx, ry, rx2, ry2);
		}
		//若有一点不在，要计算连线与边缘的交点，连在内的点和交点
		//第二个点不在时
		else if(( rx > x - d / 2 && rx < x + d / 2 && ry > y - d / 2 && ry < y + d / 2 ) && (rx2 < x - d / 2 || rx2 > x + d / 2 || ry2 < y - d / 2 || ry2 > y + d / 2 )){
			//现坐标系是以x，y为中心；x正方向向右，y正方向向下
			//两点的直线方程以矩阵表示，矩阵a的第一行是这个直线，第二行是边缘的方程，现在默认第二行都是0
			double a[2][3] = {{-(ry2 - ry) / (rx2 - rx) , 1, -(ry2 - ry) / (rx2 - rx) * rx + ry} , {}};
			
			//b的每一行是边缘方程的矩阵表示
			double b[4][3] = {{0, 1 , (y + d / 2)}, {1, 0 , (x + d / 2)}, {0, 1, (y - d / 2)}, {1, 0, (x - d / 2)}};
			
			for(int i = 0; i < 4; i ++){
				
				for(int k = 0; k < 3; k ++){
					a[1][k] = b[i][k];			
				}
				
				double xTmp = ((a[1][1] * a[0][2]) - (a[0][1] * a[1][2])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));
				double yTmp = ((a[0][0] * a[1][2]) - (a[0][2] * a[1][0])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));
				
				//要取的是在边缘范围内的交点，同时还要保证交点是在第一个点到第二个点中间！！！(保证在中间通过)
				if(xTmp >= x - 1.0001 * d / 2 && xTmp <= x + 1.0001 * d / 2 && yTmp >= y - 1.0001 * d / 2 && yTmp <= y + 1.0001 * d / 2
					&& xTmp <= max(rx, rx2) && xTmp >= min(rx, rx2) && yTmp <= max(ry, ry2) && yTmp >= min(ry, ry2)){
					rx2 = xTmp;
					ry2 = yTmp;
					
					ege_line(rx, ry, rx2, ry2);
					
					break;
				}
				
				
			}
			
		}
		//第一个点不在时
		else if(( rx < x - d / 2 || rx > x + d / 2 || ry < y - d / 2 || ry > y + d / 2 ) && (rx2 > x - d / 2 && rx2 < x + d / 2 && ry2 > y - d / 2 && ry2 < y + d / 2 )){
			
			double a[2][3] = {{-(ry2 - ry) / (rx2 - rx) , 1, -(ry2 - ry) / (rx2 - rx) * rx + ry} , {}};
			
			//b的每一行是边缘方程的矩阵表示
			double b[4][3] = {{0, 1 , (y + d / 2)}, {1, 0 , (x + d / 2)}, {0, 1, (y - d / 2)}, {1, 0, (x - d / 2)}};
			
			for(int i = 0; i < 4; i ++){
				
				for(int k = 0; k < 3; k ++){
					a[1][k] = b[i][k];			
				}
				
				double xTmp = ((a[1][1] * a[0][2]) - (a[0][1] * a[1][2])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));
				double yTmp = ((a[0][0] * a[1][2]) - (a[0][2] * a[1][0])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));
				
				//要取的是在边缘范围内的交点，同时还要保证交点是在第一个点到第二个点中间！！！(保证在中间通过)
				if(xTmp >= x - 1.0001 * d / 2 && xTmp <= x + 1.0001 * d / 2 && yTmp >= y - 1.0001 * d / 2 && yTmp <= y + 1.0001 * d / 2
					&& xTmp <= max(rx, rx2) && xTmp >= min(rx, rx2) && yTmp <= max(ry, ry2) && yTmp >= min(ry, ry2)){
					rx = xTmp;
					ry = yTmp;
					
					ege_line(rx, ry, rx2, ry2);
					break;
				}
				
				
			}
			
		}
		//两个点都不在时
		else if(( rx < x - d / 2 || rx > x + d / 2 || ry < y - d / 2 || ry > y + d / 2 ) && (rx2 < x - d / 2 || rx2 > x + d / 2 || ry2 < y - d / 2 || ry2 > y + d / 2 )){
			
			double a[2][3] = {{-(ry2 - ry) / (rx2 - rx) , 1, -(ry2 - ry) / (rx2 - rx) * rx + ry} , {}};
			
			//b的每一行是边缘方程的矩阵表示
			double b[4][3] = {{0, 1 , (y + d / 2)}, {1, 0 , (x + d / 2)}, {0, 1, (y - d / 2)}, {1, 0, (x - d / 2)}};
			
			int xTmps[5];
			int yTmps[5];
			int cot = 0;
			
			for(int i = 0; i < 4; i ++){
				
				for(int k = 0; k < 3; k ++){
					a[1][k] = b[i][k];			
				}
				
				double xTmp = ((a[1][1] * a[0][2]) - (a[0][1] * a[1][2])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));
				double yTmp = ((a[0][0] * a[1][2]) - (a[0][2] * a[1][0])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));
				
				//两点都不在边缘内侧，直线与边缘要么没有交点，要么有两个；  此时不用判断交点在不在两个点中间
				if(xTmp >= x - 1.0001 * d / 2 && xTmp <= x + 1.0001 * d / 2 && yTmp >= y - 1.0001 * d / 2 && yTmp <= y + 1.0001 * d / 2){
					rx = xTmp;
					ry = yTmp;
					cot ++;
					
					xTmps[cot] = xTmp;
					yTmps[cot] = yTmp;
					
					break;
				}
				
			}
			
			//判断有几个交点,两个时则绘制
			if(cot == 2){
				
				ege_line(xTmps[0], yTmps[0], xTmps[1], yTmps[1]);
			}
			
			
		}
		
		
		
	}
	
	
	int cot = 0;
			
	//上述代码执行了绘制线路
	//以下代码执行绘制各个航点
	for(auto wpTmp : route){
		
		double dis = getDistance(wp.lat, wp.lon, wpTmp.lat, wpTmp.lon);
		double bearing = getBearing(wp.lat, wp.lon, wpTmp.lat, wpTmp.lon);
		
		double rside = 0.010752 * side;
		double rhigh = 0.015129 * side;
		double rl = dis / 1000 * 0.1738176 * side / ratio;
		double rx = (cos(toRadians(bearing - dir - 90)) * rl) + x;
		double ry = (sin(toRadians(bearing - dir - 90)) * rl) + y;
		
		//当航路点在圆内时再绘制
		if(pow(rl, 2) <= pow(side / 104 * 40, 2)){
			
//			if(wpTmp.num == 1){
				
				ege_point pointTmp[4] = {
					{rx,ry - rhigh / 3},
					{rx - rside / 2,ry + rhigh / 2},
					{rx + rside / 2,ry + rhigh / 2},
					{rx,ry - rhigh / 3},
				};
				
				if(cot > 0 && routePassed.size() > 0 && !strcmp((*(routePassed.end() - 1)).name, (*(route.begin() + cot - 1)).name)){
					setfillcolor(EGEARGB(0xbb,0xa8,0x05,0xa8));
					setcolor(RED);
				}
				else{
					setfillcolor(WHITE);
					setcolor(WHITE);
				}
			
				ege_fillpoly(4, pointTmp);
				
				if(0.01 * side > 5){
					
					setfont(0.01 * side, 0.01 * side , "黑体");
					
					ege_drawtext(wpTmp.name,rx,ry);
				}
				
//			}
//			else if(wpTmp.num == 2){
//				
//				ege_point pointTmp[6] = {
//					{rx + rside / 1.3,ry},
//					{rx + rside / 2.6,ry + rside / 2.6 * 1.732},
//					{rx - rside / 2.6,ry + rside / 2.6 * 1.732},
//					{rx - rside / 1.3,ry},
//					{rx - rside / 2.6,ry - rside / 2.6 * 1.732},
//					{rx + rside / 2.6,ry - rside / 2.6 * 1.732},
//				};
//				
//				setfillcolor(WHITE);
//				ege_fillpoly(6, pointTmp);
//				
//				if(0.01 * side > 5){
//					setcolor(WHITE);
//					setfont(0.01 * side, 0.01 * side , "黑体");
//					
//					ege_drawtext(wpTmp.name,rx,ry);
//				}
//				
//			}
//			else if(wpTmp.num == 3){
//				
//				setfillcolor(WHITE);
//				ege_ellipse(rx - rhigh / 2, ry - rhigh / 2, rhigh, rhigh);
//				
//				if(0.01 * side > 5){
//					setcolor(WHITE);
//					setfont(0.01 * side, 0.01 * side , "黑体");
//					
//					ege_drawtext(wpTmp.name,rx,ry);
//				}
//				
//			}
			
			cot ++;
			
		}
		
	}
	
	
}



//这个x，y是同上
//传进来的是三角形中心,也是图上飞机位置！
void draw_waypoint_map(WAYPOINT nowPos, double dir, double ratio,double x, double y, double side){
	
	for(auto wp : waypoints){
		
		if(fabs(wp.lat - nowPos.lat) > 0.3 || fabs(wp.lon - nowPos.lon) > 0.3){
			continue;
		}
		
		double dis = getDistance(nowPos.lat, nowPos.lon, wp.lat, wp.lon);
		double bearing = getBearing(nowPos.lat, nowPos.lon, wp.lat, wp.lon);
		
		double rside = 0.010752 * side;
		double rhigh = 0.015129 * side;
		double rl = dis / 1000 * 0.1738176 * side / ratio;
		double rx = (cos(toRadians(bearing - dir - 90)) * rl) + x;
		double ry = (sin(toRadians(bearing - dir - 90)) * rl) + y;
		
		//当航路点在范围内内时再绘制
		if(pow(rx - x, 2) + pow(ry - y, 2) <= pow(side / 104 * 71, 2)
			&& ry <= y + side * 16 / 104 / 3 && rx <= x + side * 48 / 104 && rx >= x - side * 48 / 104){
			
			ege_point pointTmp[4] = {
				{rx,ry - rhigh / 3},
				{rx - rside / 2,ry + rhigh / 2},
				{rx + rside / 2,ry + rhigh / 2},
				{rx,ry - rhigh / 3},
			};
			
			setlinewidth(0.001 * side);
//		setcolor(WHITE);
			setcolor(EGEARGB(0xff,0x64,0x7B,0x94));
			ege_drawpoly(4, pointTmp);
			
			if(0.01 * side > 5){
				setfont(0.01 * side, 0.01 * side , "黑体");
				ege_drawtext(wp.name,rx,ry + rhigh / 2 + 0.007 * side);
			}
			
		}
		
	}
	
	
}


//传进来的是三角形中心,也是图上飞机位置！
void draw_route_map(WAYPOINT wp, double dir, double ratio,double x, double y, double side){
	
	for(auto it = route.begin(); it + 1 != route.end(); it ++){
		
		WAYPOINT wp1 = *(it);
		WAYPOINT wp2 = *(it + 1);
		
		double dis = getDistance(wp.lat, wp.lon, wp1.lat, wp1.lon);
		double bearing = getBearing(wp.lat, wp.lon, wp1.lat, wp1.lon);
		
		
		double rl = dis / 1000 * 0.1738176 * side / ratio;
		double rx = (cos(toRadians(bearing - dir - 90)) * rl) + x;
		double ry = (sin(toRadians(bearing - dir - 90)) * rl) + y;
		
		
		double dis2 = getDistance(wp.lat, wp.lon, wp2.lat, wp2.lon);
		double bearing2 = getBearing(wp.lat, wp.lon, wp2.lat, wp2.lon);
		
		double rl2 = dis2 / 1000 * 0.1738176 * side / ratio;
		double rx2 = (cos(toRadians(bearing2 - dir - 90)) * rl2) + x;
		double ry2 = (sin(toRadians(bearing2 - dir - 90)) * rl2) + y;
		
		setlinewidth(0.003 * side);
		
		//先判断这段路线是不是接下来的一段，从而设置不同颜色
		//警告：这里一旦尝试读取没有内容的vector的迭代器会导致程序直接闪退
		if(routePassed.size() > 0 && !strcmp((*(routePassed.end() - 1)).name, wp1.name)){
			
			setcolor(EGEARGB(0x99,0xa8,0x05,0xa8));
			
		}
		else{
			
//			setcolor(WHITE);
			setcolor(EGEARGB(0x66,0xff,0xff,0xff));
		}
		
		
		//先判断两点是不是都在范围内，如果都在，直接链接即可
		//这个时候判断rx和ry在不在范围是判断的两者在不在矩形区域中！
//		if(pow(rx - x, 2) + pow(ry - (y - side * 2 / 3 * 8 / 104), 2) <= pow(side / 104 * 71, 2) && ry <= y + side * 8 / 104 / 3 && rx <= x + side * 48 / 104 && rx >= x - side * 48 / 104 
//			&& pow(rx2 - x, 2) + pow(ry2 - (y - side * 2 / 3 * 8 / 104), 2) <= pow(side / 104 * 71, 2) && ry2 <= y + side * 8 / 104 / 3 && rx2 <= x + side * 48 / 104 && rx2 >= x - side * 48 / 104)
		if(ry >= y - side * (71.0 / 104) && ry <= y + side * 16 / 104 / 3 && rx <= x + side * 48 / 104 && rx >= x - side * 48 / 104 
			&& ry2 >= y - side * (71.0 / 104) && ry2 <= y + side * 16 / 104 / 3 && rx2 <= x + side * 48 / 104 && rx2 >= x - side * 48 / 104){
			//都在，不用处理
			ege_line(rx, ry, rx2, ry2);
			
		}
		//若有一点不在，要计算连线与边缘的交点，连在内的点和交点
		//第二个点不在时
		//这里一定要是71.0!!!!!!!!!!!!!!!!!!!
		else if(ry >= y - side * (71.0 / 104) && ry <= y + side * 16 / 104 / 3 && rx <= x + side * 48 / 104 && rx >= x - side * 48 / 104 
			&& (ry2 < y - side * (71.0 / 104) || ry2 > y + side * 16 / 104 / 3 || rx2 > x + side * 48 / 104 || rx2 < x - side * 48 / 104)){
			//现坐标系是以x，y为中心；x正方向向右，y正方向向下
			//两点的直线方程以矩阵表示，矩阵a的第一行是这个直线，第二行是边缘的方程，现在默认第二行都是0
			double a[2][3] = {{-(ry2 - ry) / (rx2 - rx) , 1, -(ry2 - ry) / (rx2 - rx) * rx + ry} , {}};
			
			//b的每一行是边缘方程的矩阵表示
			double b[4][3] = {{0, 1 , (y + side * 16 / 104 / 3)}, {1, 0 , (x + side * 48 / 104)}, {0, 1, (y - side * (71.0 / 104) )}, {1, 0, (x - side * 48 / 104)}};
			
			for(int i = 0; i < 4; i ++){
				
				for(int k = 0; k < 3; k ++){
					a[1][k] = b[i][k];			
				}
				
				double xTmp = ((a[1][1] * a[0][2]) - (a[0][1] * a[1][2])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));
				double yTmp = ((a[0][0] * a[1][2]) - (a[0][2] * a[1][0])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));
				
				//要取的是在边缘范围内的交点，同时还要保证交点是在第一个点到第二个点中间！！！(保证在中间通过)
				if(yTmp >= y - 1.0001 * side * (71.0 / 104) && yTmp <= y + 1.0001 * side * 16 / 104 / 3 && xTmp<= x + 1.0001 * side * 48 / 104 && xTmp >= x - 1.0001 * side * 48 / 104
					&& xTmp <= max(rx, rx2) && xTmp >= min(rx, rx2) && yTmp <= max(ry, ry2) && yTmp >= min(ry, ry2)){
					rx2 = xTmp;
					ry2 = yTmp;
					
					ege_line(rx, ry, rx2, ry2);
					
					break;
				}
				
				
			}
			
		}
		//第一个点不在时
		else if((ry < y - side * (71.0 / 104) || ry > y + side * 16 / 104 / 3 || rx > x + side * 48 / 104 || rx < x - side * 48 / 104) 
			&& ry2 >= y - side * (71.0 / 104) && ry2 <= y + side * 16 / 104 / 3 && rx2 <= x + side * 48 / 104 && rx2 >= x - side * 48 / 104){
			
			double a[2][3] = {{-(ry2 - ry) / (rx2 - rx) , 1, -(ry2 - ry) / (rx2 - rx) * rx + ry} , {}};
			
			//b的每一行是边缘方程的矩阵表示
			double b[4][3] = {{0, 1 , (y + side * 16 / 104 / 3)}, {1, 0 , (x + side * 48 / 104)}, {0, 1, (y - side * (71.0 / 104) )}, {1, 0, (x - side * 48 / 104)}};
			
			for(int i = 0; i < 4; i ++){
				
				for(int k = 0; k < 3; k ++){
					a[1][k] = b[i][k];			
				}
				
				double xTmp = ((a[1][1] * a[0][2]) - (a[0][1] * a[1][2])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));
				double yTmp = ((a[0][0] * a[1][2]) - (a[0][2] * a[1][0])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));
				
				//要取的是在边缘范围内的交点，同时还要保证交点是在第一个点到第二个点中间！！！(保证在中间通过)
				if(yTmp >= y - 1.0001 * side * (71.0 / 104) && yTmp <= y + 1.0001 * side * 16 / 104 / 3 && xTmp<= x + 1.0001 * side * 48 / 104 && xTmp >= x - 1.0001 * side * 48 / 104
					&& xTmp <= max(rx, rx2) && xTmp >= min(rx, rx2) && yTmp <= max(ry, ry2) && yTmp >= min(ry, ry2)){
					rx = xTmp;
					ry = yTmp;
					
					ege_line(rx, ry, rx2, ry2);
					break;
				}
				
				
			}
			
		}
		//两个点都不在时
		else if((ry < y - side * (71.0 / 104) || ry > y + side * 16 / 104 / 3 || rx > x + side * 48 / 104 || rx < x - side * 48 / 104)
			|| (ry2 < y - side * (71.0 / 104) || ry2 > y + side * 16 / 104 / 3 || rx2 > x + side * 48 / 104 || rx2 < x - side * 48 / 104)){
			
			double a[2][3] = {{-(ry2 - ry) / (rx2 - rx) , 1, -(ry2 - ry) / (rx2 - rx) * rx + ry} , {}};
			
			//b的每一行是边缘方程的矩阵表示
			double b[4][3] = {{0, 1 , (y + side * 16 / 104 / 3)}, {1, 0 , (x + side * 48 / 104)}, {0, 1, (y - side * (71.0 / 104) )}, {1, 0, (x - side * 48 / 104)}};
			
			int xTmps[5];
			int yTmps[5];
			int cot = 0;
			
			for(int i = 0; i < 4; i ++){
				
				for(int k = 0; k < 3; k ++){
					a[1][k] = b[i][k];			
				}
				
				double xTmp = ((a[1][1] * a[0][2]) - (a[0][1] * a[1][2])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));
				double yTmp = ((a[0][0] * a[1][2]) - (a[0][2] * a[1][0])) / ((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));
				
				//两点都不在边缘内侧，直线与边缘要么没有交点，要么有两个；  此时不用判断交点在不在两个点中间
				if(yTmp >= y - 1.0001 * side * (71.0 / 104) && yTmp <= y + 1.0001 * side * 16 / 104 / 3 && xTmp<= x + 1.0001 * side * 48 / 104 && xTmp >= x - 1.0001 * side * 48 / 104){
					rx = xTmp;
					ry = yTmp;
					cot ++;
					
					xTmps[cot] = xTmp;
					yTmps[cot] = yTmp;
					
					break;
				}
				
			}
			
			//判断有几个交点,两个时则绘制
			if(cot == 2){
				
				ege_line(xTmps[0], yTmps[0], xTmps[1], yTmps[1]);
			}
			
			
		}
		
		
		
	}
	
	
	
	int cot = 0;
	
	//上述代码执行了绘制线路
	//以下代码执行绘制各个航点
	for(auto wpTmp : route){
		
		double dis = getDistance(wp.lat, wp.lon, wpTmp.lat, wpTmp.lon);
		double bearing = getBearing(wp.lat, wp.lon, wpTmp.lat, wpTmp.lon);
		
		double rside = 0.010752 * side;
		double rhigh = 0.015129 * side;
		double rl = dis / 1000 * 0.1738176 * side / ratio;
		double rx = (cos(toRadians(bearing - dir - 90)) * rl) + x;
		double ry = (sin(toRadians(bearing - dir - 90)) * rl) + y;
		
		//当航路点在范围内时再绘制
		if(ry >= y - side * (71.0 / 104) && ry <= y + side * 16 / 104 / 3 && rx <= x + side * 48 / 104 && rx >= x - side * 48 / 104){
			
			ege_point pointTmp[4] = {
				{rx,ry - rhigh / 3},
				{rx - rside / 2,ry + rhigh / 2},
				{rx + rside / 2,ry + rhigh / 2},
				{rx,ry - rhigh / 3},
			};
			
			if(cot > 0 && routePassed.size() > 0 && !strcmp((*(routePassed.end() - 1)).name, (*(route.begin() + cot - 1)).name)){
				setfillcolor(EGEARGB(0xbb,0xa8,0x05,0xa8));
				setcolor(RED);
			}
			else{
				setfillcolor(WHITE);
				setcolor(WHITE);
			}
			
			ege_fillpoly(4, pointTmp);
			
			if(0.01 * side > 5){
				
				setfont(0.01 * side, 0.01 * side , "黑体");
				
				ege_drawtext(wpTmp.name,rx,ry);
			}
			
			
			cot ++;
			
		}
		
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

