#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>

#include <time.h>
using namespace std;

extern char location[20]; 
extern void get_systime(char *systime);

void get_location()
{
	cout << "Enter Where You Are"<<endl;
	cin >> location;
}

void get_systime(char *systime)
{
	struct tm *curTime;
	time_t now;	
	now = time(NULL);
	curTime = localtime(&now);
	sprintf(systime,"%04d%02d%02d_%02d%02d%02d",curTime->tm_year+1900,curTime->tm_mon+1,curTime->tm_mday,curTime->tm_hour,curTime->tm_min,curTime->tm_sec);
	return ;
}
