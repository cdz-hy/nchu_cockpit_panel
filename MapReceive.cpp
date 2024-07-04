#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include <math.h>
#include <mutex>
#include <graphics.h>

#include "G_variable.h"

#define URL_LENGTH 256     //Url地址
#define DATA_LENGTH 10240  //接收数据的长度

extern double latitude;
extern double longitude;

char* key = "b20a1e6b66164c7e2cef9f767f53beb5";

//std::mutex mtxReceive;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
	size_t realsize = size * nmemb;
	FILE* file = (FILE*)userp;
	if (!file) {
		return 0;
	}
	return fwrite(contents, size, nmemb, file); 
}


//处理数据回调函数
size_t write_data(char* duffer, size_t size, size_t nmend, void* userp) {
	char* data = (char*)userp;          //将传入的空指针的地址给一个指针
	memset(data, DATA_LENGTH, 0);
	size_t bytes = size * nmend;        //求出这个数据包的长度
	memcpy(data, duffer, bytes);        //将收到的数据交给前面定义的指针
	return bytes;                       //返回数据包的长度
}


extern int renewMap;

void map_receive() {
	
	//否则会在最开始还没有接收到本地数据的时候就用初始的经纬度（不是实际的）获得了地图
	//使得程序误认为这个地图是以此时的实际经纬为中心的地图
	api_sleep(100);
	
//	for(;is_run();api_sleep(10000)){
	for(;is_run(); api_sleep(10)){
//		if(fabs(fmod(fclock(), 5)) <= 0.001){
		
		if(renewMap == 1){
			
			CURL* curl;
			FILE* fp;
			CURLcode res;
			
			curl_global_init(CURL_GLOBAL_DEFAULT);
			
			curl = curl_easy_init();
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
			
			if (curl) {
				char url[512];
				sprintf(url, "https://restapi.amap.com/v3/staticmap?location=%f,%f&scale=2&zoom=9&size=1200*1200&key=%s", longitude, latitude, key);
				
				fp = fopen("map.png", "wb");
				if (!fp) {
					perror("Failed to open file for writing");
					return;
				}
				
				curl_easy_setopt(curl, CURLOPT_URL, url);
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
				
				res = curl_easy_perform(curl);
				
				if (res != CURLE_OK) {
					fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
				}
				else {
//					printf("Map image downloaded successfully.\n");
				}
				
				fclose(fp);
				curl_easy_cleanup(curl);
			}
			
			curl_global_cleanup();
			
			
			api_sleep(1000);
			renewMap = 2;
			
		}
		
//		}
		
		
		
	}
	
	

	
}


//获取地址信息，天气信息并处理
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include <map>

std::vector<char> ReadFile(const std::string& fileName) {
	std::ifstream file(fileName, std::ios::binary);
	if (!file) {
		std::cerr << "Error opening file: " << fileName << std::endl;
		return {};
	}
	
	file.seekg(0, std::ios::end);
	std::streampos fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	
	std::vector<char> fileContent(fileSize);
	file.read(fileContent.data(), fileSize);
	
	return fileContent;
}

// 定义一个简单的 JSON 解析函数
std::map<std::string, std::string> parseJSON(const std::string& jsonString) {
	std::map<std::string, std::string> data;
	
	size_t startPos = jsonString.find_first_of('{');
	size_t endPos = jsonString.find_last_of('}');
	
	if (startPos != std::string::npos && endPos != std::string::npos && endPos > startPos) {
		std::string jsonContent = jsonString.substr(startPos, endPos - startPos + 1);
		
		size_t keyStart = jsonContent.find_first_of('"');
		while (keyStart != std::string::npos) {
			++keyStart;
			size_t keyEnd = jsonContent.find('"', keyStart);
			std::string key = jsonContent.substr(keyStart, keyEnd - keyStart);
			
			size_t valueStart = jsonContent.find(':', keyEnd);
			size_t valueEnd = jsonContent.find_first_of(",}", valueStart);
			std::string value = jsonContent.substr(valueStart + 1, valueEnd - valueStart - 1);
			
			data[key] = value;
			
			keyStart = jsonContent.find_first_of('"', valueEnd);
		}
	}
	
	return data;
}

// 辅助函数，用于移除字符串中的所有双引号  
std::string removeQuotes(const std::string& str) {
	std::string result;
	for (char c : str) {
		if (c != '"') { // 如果字符不是双引号，则添加到结果字符串中  
			result += c;
		}
	}
	return result;
}


bool WriteFile(const std::string& fileName, const std::vector<char>& data) {
	std::ofstream file(fileName, std::ios::binary);
	if (!file) {
		std::cerr << "Error opening file for writing: " << fileName << std::endl;
		return false;
	}
	
	file.write(data.data(), data.size());
	return true;
}

void info_receive(){
	
	
	while(is_run()){
		
		if(fabs(fmod(fclock(), 3)) == 0){
			
			
			//请求位置
			{
				CURL* curl = NULL;
				CURLcode ret;
				FILE* fd = NULL;
				char url[URL_LENGTH]; //请求的url
				char data[DATA_LENGTH];  //接收的数据
				//拼接请求的URL地址
				snprintf(url, sizeof(url), "https://restapi.amap.com/v3/geocode/regeo?output=json&location=%f,%f&key=%s&radius=0&extensions=base", longitude, latitude, key);
				curl_global_init(CURL_GLOBAL_DEFAULT);
				curl = curl_easy_init(); //初始化curl
				curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
				
				if (curl) {
					curl_easy_setopt(curl, CURLOPT_URL, url); //请求的url
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); //请求的数据放入回调函数中进行处理
					curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);           //返回出回调函数中的void*指针
					ret = curl_easy_perform(curl);        //发送数据
					if (ret != CURLE_OK) {
						//失败的情况
						fprintf(stderr, "curl_easy_perform feild is %s\n", curl_easy_strerror(ret));
					}
					else {
						//将数据写入文件中
						fd = fopen("data.json", "w+");
						api_sleep(300);
						fwrite(data, 1, sizeof(data), fd);
						fclose(fd);
						fd = NULL;
					}
					curl_easy_cleanup(curl);
				}
				curl_global_cleanup();
				
				
				//处理并存储信息
				
				std::string inputFile = "data.json"; // UTF-8编码的输入文件名
				std::string outputFile = "jsonRead.txt"; // 转换后的GBK编码输出文件名
				
				// 读取UTF-8文件
				std::vector<char> utf8Data = ReadFile(inputFile);
				if (utf8Data.empty()) continue;
				
				// 计算UTF-16LE所需缓冲区大小
				int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, utf8Data.data(), utf8Data.size(), NULL, 0);
				if (unicodeLen == 0) {
					std::cerr << "Error in getting Unicode length." << std::endl;
					continue;
				}
				
				// 转换到UTF-16LE
				std::vector<WCHAR> strUnicode(unicodeLen);
				if (MultiByteToWideChar(CP_UTF8, 0, utf8Data.data(), utf8Data.size(), strUnicode.data(), unicodeLen) != unicodeLen) {
					std::cerr << "UTF-8 to Unicode conversion failed." << std::endl;
					continue;
				}
				
				// 计算GBK编码所需缓冲区大小
				int gbkLen = WideCharToMultiByte(CP_ACP, 0, strUnicode.data(), unicodeLen, NULL, 0, NULL, NULL);
				if (gbkLen == 0) {
					std::cerr << "Error in getting GBK length." << std::endl;
					continue;
				}
				
				// 转换到GBK
				std::vector<char> strGBK(gbkLen);
				if (WideCharToMultiByte(CP_ACP, 0, strUnicode.data(), unicodeLen, strGBK.data(), gbkLen, NULL, NULL) != gbkLen) {
					std::cerr << "Unicode to GBK conversion failed." << std::endl;
					continue;
				}
				
				
				// 将GBK编码的数据写入文件
				if (!WriteFile(outputFile, strGBK)) {
					std::cerr << "Failed to write GBK data to file." << std::endl;
					continue;
				}
				
				// 将strGBK转换为char[]
				char* gbkArray = new char[strGBK.size() + 1]; // 分配内存，并多分配一个字节用于存储'\0'
				std::copy(strGBK.begin(), strGBK.end(), gbkArray); // 使用std::copy将数据复制到char[]
				gbkArray[strGBK.size()] = '\0'; // 在末尾添加'\0'，使其成为C风格字符串
				
				//std::cout << gbkArray << std::endl;
				//将char[]提取
				
				std::map<std::string, std::string> jsonData = parseJSON(gbkArray);
				
				// 提取特定字段
				std::vector<std::string> extractedData;
				extractedData.push_back(jsonData["adcode"]);
				extractedData.push_back(jsonData["township"]);
				extractedData.push_back(jsonData["street"]);
				
				for (auto& str : extractedData) {
					str = removeQuotes(str);
				}
				
//				for(auto it:extractedData){
//					std::cout << it << " ";
//				}
	
	
				strcpy(mapAdcode, extractedData[0].c_str());
				strcpy(mapTownship, extractedData[1].c_str());
				if(strcmp(extractedData[2].c_str(),"[]"))
					strcpy(mapStreet, extractedData[2].c_str());
				else
					strcpy(mapStreet, "");
			}
			
			
			api_sleep(100);
			
			//请求天气
			{
				
				CURL* curl = NULL;
				CURLcode ret;
				FILE* fd = NULL;
				char url[URL_LENGTH]; //请求的url
				char data[DATA_LENGTH];  //接收的数据
				//拼接请求的URL地址
				snprintf(url, sizeof(url), "https://restapi.amap.com/v3/weather/weatherInfo?city=%s&key=%s&output=json&extensions=base",mapAdcode ,key);
				curl_global_init(CURL_GLOBAL_DEFAULT);
				curl = curl_easy_init(); //初始化curl
				curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
				
				if (curl) {
					curl_easy_setopt(curl, CURLOPT_URL, url); //请求的url
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); //请求的数据放入回调函数中进行处理
					curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);           //返回出回调函数中的void*指针
					ret = curl_easy_perform(curl);        //发送数据
					if (ret != CURLE_OK) {
						//失败的情况
						fprintf(stderr, "curl_easy_perform feild is %s\n", curl_easy_strerror(ret));
					}
					else {
						//将数据写入文件中
						fd = fopen("data.json", "w+");
						api_sleep(300);
						fwrite(data, 1, sizeof(data), fd);
						fclose(fd);
						fd = NULL;
					}
					curl_easy_cleanup(curl);
				}
				curl_global_cleanup();
				
				
				//处理并存储信息
				
				std::string inputFile = "data.json"; // UTF-8编码的输入文件名
				std::string outputFile = "jsonRead.txt"; // 转换后的GBK编码输出文件名
				
				// 读取UTF-8文件
				std::vector<char> utf8Data = ReadFile(inputFile);
				if (utf8Data.empty()) continue;;
				
				// 计算UTF-16LE所需缓冲区大小
				int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, utf8Data.data(), utf8Data.size(), NULL, 0);
				if (unicodeLen == 0) {
					std::cerr << "Error in getting Unicode length." << std::endl;
					continue;
				}
				
				// 转换到UTF-16LE
				std::vector<WCHAR> strUnicode(unicodeLen);
				if (MultiByteToWideChar(CP_UTF8, 0, utf8Data.data(), utf8Data.size(), strUnicode.data(), unicodeLen) != unicodeLen) {
					std::cerr << "UTF-8 to Unicode conversion failed." << std::endl;
					continue;
				}
				
				// 计算GBK编码所需缓冲区大小
				int gbkLen = WideCharToMultiByte(CP_ACP, 0, strUnicode.data(), unicodeLen, NULL, 0, NULL, NULL);
				if (gbkLen == 0) {
					std::cerr << "Error in getting GBK length." << std::endl;
					continue;
				}
				
				// 转换到GBK
				std::vector<char> strGBK(gbkLen);
				if (WideCharToMultiByte(CP_ACP, 0, strUnicode.data(), unicodeLen, strGBK.data(), gbkLen, NULL, NULL) != gbkLen) {
					std::cerr << "Unicode to GBK conversion failed." << std::endl;
					continue;
				}
				
				
				// 将GBK编码的数据写入文件
				if (!WriteFile(outputFile, strGBK)) {
					std::cerr << "Failed to write GBK data to file." << std::endl;
					continue;
				}
				// 将strGBK转换为char[]
				char* gbkArray = new char[strGBK.size() + 1]; // 分配内存，并多分配一个字节用于存储'\0'
				std::copy(strGBK.begin(), strGBK.end(), gbkArray); // 使用std::copy将数据复制到char[]
				gbkArray[strGBK.size()] = '\0'; // 在末尾添加'\0'，使其成为C风格字符串
				
				//std::cout << gbkArray << std::endl;
				//将char[]提取
				
				std::map<std::string, std::string> jsonData = parseJSON(gbkArray);
				
				// 提取特定字段
				std::vector<std::string> extractedData;
				extractedData.push_back(jsonData["lives"]);
				extractedData.push_back(jsonData["city"]);
				extractedData.push_back(jsonData["adcode"]);
				extractedData.push_back(jsonData["weather"]);
				extractedData.push_back(jsonData["temperature"]);
				extractedData.push_back(jsonData["winddirection"]);
				extractedData.push_back(jsonData["windpower"]);
				extractedData.push_back(jsonData["humidity"]);
				
				for (auto& str : extractedData) {
					str = removeQuotes(str);
				}
				
				// 确保extractedData中至少有一个元素
				if (!extractedData.empty()) {
					std::string& firstElement = extractedData[0]; // 获取第一个元素的引用
					size_t pos = firstElement.find(":"); // 寻找冒号的位置
					if (pos != std::string::npos) {
						firstElement = firstElement.substr(pos + 1); // 去掉冒号及其前面的字符
					}
				}
				
//				for(auto it:extractedData){
//					std::cout << it << " ";
//				}

				
				strcpy(mapProvince, extractedData[0].c_str());
				strcpy(mapCity, extractedData[1].c_str());
				strcpy(mapWeather, extractedData[3].c_str());
				strcpy(mapTemperature, extractedData[4].c_str());
				strcpy(mapWinddirection, extractedData[5].c_str());
				strcpy(mapWindpower, extractedData[6].c_str());
				strcpy(mapHumidity, extractedData[7].c_str());
				
				printf("%s\n",mapCity);
				
			}
			
		}
		
		
		

		
		
		
	}
	

	
}


