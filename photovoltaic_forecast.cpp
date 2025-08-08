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

#include <iomanip>
#include <chrono>

using namespace std;

extern double longitude;
extern double latitude;

extern vector<double> diffuse_radiation;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userdata)
{

    ((std::string*)userdata)->append((char*)contents, size * nmemb);

    return size * nmemb;
}


void photovoltaic_forecast()
{

	CURL *curl;
	CURLcode sende_rc;

	curl = curl_easy_init();

	struct curl_slist *header = NULL;

	string dhi_url;

	dhi_url = "https://api.open-meteo.com/v1/forecast?latitude=" + to_string(latitude) + "&longitude=" + to_string(longitude) + "&hourly=diffuse_radiation&timezone=Europe%2FBerlin&forecast_days=1&tilt=35&azimuth=57";

	curl_easy_setopt(curl, CURLOPT_URL, dhi_url.c_str());

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



	int wo_ist_diffuse_radiation = -1;

	wo_ist_diffuse_radiation = http_rueckgabe.find("diffuse_radiation\":[");

	http_rueckgabe = http_rueckgabe.substr(wo_ist_diffuse_radiation,http_rueckgabe.length());

	
	int wo_ist_eckige_klammer_auf = -1;
	int wo_ist_eckige_klammer_zu = -1;
	wo_ist_eckige_klammer_auf = http_rueckgabe.find("[");
	wo_ist_eckige_klammer_zu = http_rueckgabe.find("]");

	http_rueckgabe = http_rueckgabe.substr(wo_ist_eckige_klammer_auf + 1,wo_ist_eckige_klammer_zu - wo_ist_eckige_klammer_auf - 1);

	
	int wo_ist_komma = -1;

	string diffuse_radiation_string;
	string http_rueckgabe_temp;
	http_rueckgabe_temp = http_rueckgabe;
	
	for (int i = 0; i < 24; i++)
	{
		wo_ist_komma = http_rueckgabe_temp.find(",");

		diffuse_radiation_string = http_rueckgabe_temp.substr(0, wo_ist_komma);

		diffuse_radiation.push_back(stoi(diffuse_radiation_string));
		http_rueckgabe_temp = http_rueckgabe_temp.substr(wo_ist_komma + 1, http_rueckgabe_temp.length());

	}

		


}



















