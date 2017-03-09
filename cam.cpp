#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "zbar.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include <windows.h>

//#pragma comment(lib, "winmm.lib")
#include <mmsystem.h>

using namespace std;
using namespace zbar;//添加zbar名称空间
using namespace cv;

extern char location[20];

VideoCapture cap(0);

extern void writefile();
extern void get_systime(char *systime);

void cam_init()
{
	if (!cap.isOpened())
	{
		cerr << "Capture Device ID" << "1" << "cannot be opened." << endl;
		return ;
	}
		else
	{
		cout << "done!" << endl;
		cap.set(CV_CAP_PROP_FRAME_WIDTH,200);
		cap.set(CV_CAP_PROP_FRAME_HEIGHT,200);	
	}
}

void zbar_cap()
{
	ImageScanner scanner;
    scanner.set_config(ZBAR_NONE,ZBAR_CFG_ENABLE,1);
    Mat image;

	cam_init();

	while(1)
	{
		cap >> image;

		Mat imageGray;
		cvtColor(image,imageGray,CV_RGB2GRAY);
		int width = imageGray.cols;
		int height = imageGray.rows;
		uchar *raw = (uchar *)imageGray.data;
		Image imageZbar(width,height,"Y800",raw,width* height);

		scanner.scan(imageZbar);//扫描条码

		Image::SymbolIterator symbol = imageZbar.symbol_begin();

		if(imageZbar.symbol_begin()==imageZbar.symbol_end())
		{
			cout<<".";
			imshow("Source Image",image);
			waitKey(1);
			continue;
		}
		destroyWindow("Source Image");
		PlaySound(TEXT("./spark.wav"), NULL, SND_FILENAME);

		for(;symbol != imageZbar.symbol_end();++symbol)
		{
			cout<<"类型："<<endl<<symbol->get_type_name()<<endl;
			cout<<"条码："<<endl<<symbol->get_data()<<endl;
			cout << "地点:" <<"     "<<location<<endl ;
			cout << "1 = confirm "<<"       "<<"0 = cancel"<< endl;
			uchar confirm; 
			
			cin >> confirm;
			if (  confirm == '1')			
			{
				ofstream oFile;
				char systime[20];
				get_systime(systime);
				oFile.open("data.csv",ios::out|ios::app);
				oFile << symbol->get_data() <<","<< systime <<","<<location<<","<<endl;
			}
			else
			{
				;
			}
		}

		imageZbar.set_data(NULL,0);
		break;
	}
	//system("pause");
	return ;
}
