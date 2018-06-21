#include <iostream>
#include <windows.h>
#include <ctime>
#include <fstream>

using namespace std;

#define chas_v_sek 3600

int bliz_time(double otrezok, double pogres, int kolvo_kartinok) {
	int bliz = 1;
	otrezok*=60;
	int time_v_min = (time(0) + (int)(pogres * chas_v_sek)) % (24*3600);
	for (; bliz < kolvo_kartinok; bliz++) {
		time_v_min-=otrezok;
		if (time_v_min < otrezok)
			break;
	} 
	return bliz;
}

void set_image_on_desktop(const char directoriya_and_filename[]) {
	char filename[200];
	strcpy(filename,directoriya_and_filename);
	SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, &filename, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
}

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	//ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
	
	double pogres;
	int kolvo_kartinok;
	
	char dir[200],
	name_kartinka[100],
	rash[20], 
	stringi[8];

	ifstream read;
	read.open("setting.txt", ios_base::in);
	
	read >> dir >> name_kartinka >> rash;
	read >> kolvo_kartinok >> pogres;
	
	read.close();
	
	double otrezok_time = 1440.0 / kolvo_kartinok;//минут
	while (1) {
		int i = bliz_time(otrezok_time, pogres, kolvo_kartinok);
		
		itoa(i, stringi, 10);
		
		string a = "";
		a = a + dir + name_kartinka + stringi + rash;
		set_image_on_desktop(a.c_str());
		while (bliz_time(otrezok_time, pogres, kolvo_kartinok) == i)//Это памятник моей лени и тупости //это оказалось достаточно годной идеей
			Sleep(600000);//10 мин
			//Sleep(420000);//7 мин
			//Sleep(300000);//5 мин
	}
	
}
