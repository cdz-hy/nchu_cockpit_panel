#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include <math.h>
#include <graphics.h>

extern double latitude;
extern double longitude;

char* key = "b20a1e6b66164c7e2cef9f767f53beb5";

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
	size_t realsize = size * nmemb;
	FILE* file = (FILE*)userp;
	if (!file) {
		return 0;
	}
	return fwrite(contents, size, nmemb, file); 
}

extern int renewMap;

void map_receive() {
	
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
