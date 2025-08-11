


#include <curl/curl.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>

using namespace std;

extern double longitude;
extern double latitude;

extern vector<double> bewolkung_vec;
extern int aktuelle_stunde;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userdata)
{
	
    ((std::string*)userdata)->append((char*)contents, size * nmemb);
	
    return size * nmemb;
}


void wetter_daten()


{
	
	
	
	
	
	
	
	CURL *curl;
	CURLcode sende_rc;

	curl = curl_easy_init();

	struct curl_slist *header = NULL;

	
	

	
	
	
	
	string wetter_url;
	wetter_url = "https://api.open-meteo.com/v1/forecast?latitude=" + to_string(latitude) + "&longitude=" + to_string(longitude) + "&hourly=cloud_cover&timezone=Europe%2FBerlin&forecast_days=1";
	
	
	
	curl_easy_setopt(curl, CURLOPT_URL, wetter_url.c_str());
	
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 2L);
	
	
	
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	string http_rueckgabe;	
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &http_rueckgabe);
	
	sende_rc = curl_easy_perform(curl);
	if(sende_rc != CURLE_OK)
	{
		cout<<"curl code#"<<sende_rc<<"#"<<endl;
		cout<<"Fehler #"<<curl_easy_strerror(sende_rc)<<"#"<<endl;
		exit(1);
	}
		
	
	
	curl_easy_cleanup(curl);	
	curl_global_cleanup();	
	
	

	string description_1 ;
	int wo_ist_description = -1;
	int wo_ist_icon = -1;
	int wo_ist_doppelpunkt = -1;
	int wo_ist_klammer = -1;
	string bewolkung;
	int wo_ist_eckige_klammer_auf = -1;
	int wo_ist_eckige_klammer_zu = -1;
	int wo_ist_komma = -1;
	
	string diffuse_radiation_string;
	string http_rueckgabe_temp;

	
	
		
		
		
		wo_ist_description = http_rueckgabe.find("cloud_cover\":[");

		
				
		http_rueckgabe = http_rueckgabe.substr(wo_ist_description,http_rueckgabe.length());
		

		wo_ist_eckige_klammer_auf = http_rueckgabe.find("[");
		wo_ist_eckige_klammer_zu = http_rueckgabe.find("]");
		
		
		http_rueckgabe = http_rueckgabe.substr(wo_ist_eckige_klammer_auf + 1,wo_ist_eckige_klammer_zu - wo_ist_eckige_klammer_auf - 1);
		
		http_rueckgabe_temp = http_rueckgabe;
		
		
		for (int i = 0; i < 24; i++)
		{
			wo_ist_komma = http_rueckgabe_temp.find(",");
			
			
			diffuse_radiation_string = http_rueckgabe_temp.substr(0, wo_ist_komma);
			
			
			bewolkung_vec.push_back(stoi(diffuse_radiation_string));
			http_rueckgabe_temp = http_rueckgabe_temp.substr(wo_ist_komma + 1, http_rueckgabe_temp.length());
			
		}



	

}



















