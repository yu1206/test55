
#include "MSRCR.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> 
#include <io.h>
#include <Windows.h>
#include "opencv\cv.h"
#include "opencv\highgui.h"
#include <direct.h>

using namespace cv;
using namespace std;


void SplitString(const string& s, vector<string>& v, const string& c)
{
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

int test55(int argc, char *argv[])
{
	string imgpath1 = "E:\\LISA-Traffic-Light\\dayTrain\\dayClip5";
	string drawpath = "E:\\LISA-Traffic-Light\\dayTrain\\dayClip5\\drawtxt";
	mkdir(drawpath.c_str());
	
	fstream finRead;
	string inputPathtxt = imgpath1 + "\\"  + "output.txt";
	finRead.open(inputPathtxt, ios::in);
	if (!finRead.is_open())
	{
		cout << "finRead1 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}
	string line;
	while (getline(finRead, line))
	{
		vector<string> vs;
		SplitString(line, vs, " ");
		string imgfile = imgpath1 + "\\"+"frames"+"\\" + vs[0];
		Mat img = imread(imgfile);
		cout << imgfile.c_str() << endl;
		if (img.data == NULL)
		{

			printf("图像为空!\n");
			cout << imgfile.c_str() << endl;
			system("pause");
		}
		for (int i = 1; i < vs.size();i++)
		{
			string str = vs[i];
			vector<string> ints;
			SplitString(str, ints, ",");
			int x1, y1, x2, y2, label;
			x1 = atoi(ints[0].c_str());
			y1 = atoi(ints[1].c_str());
			x2 = atoi(ints[2].c_str());
			y2 = atoi(ints[3].c_str());
			label = atoi(ints[4].c_str());

			Point pt1, pt2;
			pt1.x = x1; pt1.y = y1;
			pt2.x = x2; pt2.y = y2;
			rectangle(img,pt1,pt2,Scalar(0,0,255));
			Point pt3; pt3.x = x2 + 5; pt3.y = y2 + 5;
			putText(img, ints[4], pt3, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 255, 0));
		}

		string file = drawpath + "\\" + vs[0];
		
		imwrite(file,img);
		
	}
	
	return 0;
}









