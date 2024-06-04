
#ifndef G_STRUCTS
#define G_STRUCTS

#include <string>
using namespace std;

////ege函数不能输出string，弃用
//typedef struct waypoint{
//	
//	string code;	// 编号（3/12表示是NDB/VOR?）
//	double lat;		// 纬度
//	double lon;		// 经度
//	string name;	// 塔台名称
//	string type; 	// 塔台类型（是否航路上都能用（ENRT））
//	string freq;	// 频率
//	double range;	// 接收范围
//	string devi;	// 磁偏差
//	string FIRName;	// 情报区代码
//	string fullName;	// 名称（更长）
//	string fullType;	// 塔台类型（更全）
//}WAYPOINT;

typedef struct waypoint{
	
	char *code;	// 编号（3/12表示是NDB/VOR?）
	double lat;		// 纬度
	double lon;		// 经度
	char *name;	// 塔台名称
	char *type; 	// 塔台类型（是否航路上都能用（ENRT））
	char *freq;	// 频率
	double range;	// 接收范围
	char *devi;	// 磁偏差
	char *FIRName;	// 情报区代码
	char *fullName;	// 名称（更长）
	char *fullType;	// 塔台类型（更全）
	
}WAYPOINT;

#endif

