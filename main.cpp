#include "zbar.h"
#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;
using namespace zbar;//添加zbar名称空间
using namespace cv;

extern void cam_init();
extern void zbar_cap();
extern void get_location();
char location[20] = "0";

int main (int argc,char* argv[])
{
   while(1)
   {
	   cout << "资产监控系统" <<endl;
	   //cout << "1、输出清单"<< endl;
	   cout << "2、设定位置"<< endl;
	   cout << "3、打开扫描物品"<<endl;
	   //cout << "4、手动输入物品"<<endl;
	   cout << "5、退出"<<endl;

	   uchar order;
	   cin >> order;
	   
	   switch(order)
	   {
		case('1'):break;
		case('2'):get_location();break;
		case('3'):
			if (location[0] == '0')
			{
				cout << "No Location!!!" << endl;
				system("pause");
			}
			else
			{
				zbar_cap();
			}
			break;
		case('4'):break;
		case('5'):return(0);break;
	   }
	   system("cls");
   }

	return 0;
}