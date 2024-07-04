#include<graphics.h>
#include <stdio.h>
#include <math.h>


extern double SteeringWeelLevel;
extern double SteeringWeelVertical;
extern double SteeringWeelFootPedals;
extern int choiceSteeringWeel;
void draw_SteeringWeel(double center_x,double center_y,double side) {
	double Ulength = side / 100;
	setcolor(EGEARGB(0X30, 0X80, 0X80, 0X80));
	ege_rectangle(center_x - side, center_y - side, 2 * side, 2 * side);
	ege_line(center_x - side / 5, center_y, center_x + side / 5, center_y);
	ege_line(center_x, center_y - side / 5, center_x, center_y + side / 5);
	int x, y;
	mousepos(&x, &y);
	if (x >= center_x - side && x <= center_x + side && y >= center_y - side && y < center_y + side) {
		if (GetAsyncKeyState(0x02) & 0x0001) {
			if (choiceSteeringWeel == 1) {
				choiceSteeringWeel = 0;
			}
			else if (choiceSteeringWeel == 0) {
				choiceSteeringWeel = 1;
			}
		}
		
	}
	else{
		choiceSteeringWeel = 0;
	}
	
	if (x >= center_x - side && x <= center_x + side && y >= center_y - side && y < center_y + side) {
		if (choiceSteeringWeel == 1) {
			setcolor(EGEARGB(0XB0, 0X80, 0X80, 0X80));
			ege_ellipse(x - Ulength * 2, y - Ulength * 2, Ulength * 4, Ulength * 4);
			setcolor(EGEARGB(0XB0, 0X80, 0X80, 0X80));
			ege_rectangle(center_x - side, center_y - side, 2 * side, 2 * side);
			ege_line(center_x - side / 5, center_y, center_x + side / 5, center_y);
			ege_line(center_x, center_y - side / 5, center_x, center_y + side / 5);
			
			SteeringWeelLevel = -((center_x - x) / side);
			SteeringWeelVertical = -((center_y - y) / side);
			SteeringWeelFootPedals = -((center_x - x) / side / 5.0);
		}else{
			double x1 = SteeringWeelLevel * side + center_x;
			double y1 = SteeringWeelVertical * side + center_y;
			setcolor(EGEARGB(0X30, 0X80, 0X80, 0X80));
			ege_ellipse(x1 - Ulength * 2, y1 - Ulength * 2, Ulength * 4, Ulength * 4);
		}
		
		
	}else{
		double x2 = SteeringWeelLevel * side + center_x;
		double y2 = SteeringWeelVertical * side + center_y;
		setcolor(EGEARGB(0X30, 0X80, 0X80, 0X80));
		ege_ellipse(x2 - Ulength * 2, y2 - Ulength * 2, Ulength * 4, Ulength * 4);
		
	}
	
}