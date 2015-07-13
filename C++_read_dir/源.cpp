#include <io.h>  
#include <fstream>  
#include <string>  
#include <vector>  
#include <iostream>  
#include "opencv.hpp";
using namespace std;  
using namespace cv;  
  
//获取所有的文件名  
void GetAllFiles( string path, vector<string>& files)    
{    
  
    long  hFile   =   0;    
    //文件信息    
    struct _finddata_t fileinfo;    
    string p;    
    if( ( hFile = _findfirst( p.assign(path).append("\\*").c_str(), &fileinfo) ) !=  -1 )    
    {    
        do    
        {     
            if( ( fileinfo.attrib &  _A_SUBDIR ) )    //如果文件的属性是文件夹
            {    
                if( (strcmp( fileinfo.name, "." ) != 0 ) && ( strcmp( fileinfo.name, ".." ) != 0) ) //避开'.' 和'..'    
                {  
                    //files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  //目录名不应保存
                    GetAllFiles( p.assign(path).append("\\").append(fileinfo.name), files );   //递归抓取文件名
                }  
            }    
            else    
            {    
                files.push_back(p.assign(path).append("\\").append(fileinfo.name) );    
            }   
  
        }while(_findnext(hFile, &fileinfo)  == 0);    
  
        _findclose(hFile);   
    }   
  
}    
 
/**
  获取特定格式的文件名
  输入： string path, vector<string>& files,string format
  输出： void
*/
void GetAllFormatFiles( string path, vector<string>& files,string format)    
{    
	//format变成小写
	unsigned int pos = 0;
	for(auto var : format)
	{
		format[pos] = tolower(var);
		pos++;
	}
    //文件句柄    
    long   hFile = 0;    
    //文件信息    
    struct _finddata_t fileinfo;    
    string p;    
    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)    
    {    
        do    
        {      
            if((fileinfo.attrib == _A_SUBDIR))    
            {    
                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)    
                {  
                    //files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  
                    GetAllFormatFiles( p.assign(path).append("\\").append(fileinfo.name), files,format);   
                }  
            }    
            else    
            {   //判断文件类型是否符合
				string str = fileinfo.name; //转化成string
				string str_end = str.substr(str.size() - format.size(), format.size());  //取末尾字串
				//cout <<"str_end :   " <<str_end<<endl;
				unsigned int i = 0;
				for(auto var : str_end)//变成小写再比较
				{
					str_end[i] = tolower(var);
					i++;
				}
			    if (str_end == format)
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  
				} 
            }    
        }while(_findnext(hFile, &fileinfo)  == 0);    
  
        _findclose(hFile);   
    }   
}   
 
  
int main()  
{  
    //string filePath = "testimages\\water";    
	string filePath = "C:\\\\Users\\董师周\\Desktop\\testpic";  //'\' 表示转义符
    vector<string> files;    
    char * distAll = "AllFiles.txt";  
  
    //读取所有的文件，包括子文件的文件  
    // GetAllFiles(filePath, files);  

 
    //读取所有格式为jpg的文件  
    string format = ".jpg";  
    GetAllFormatFiles(filePath, files,format);  
    //输出到文件
    ofstream ofn(distAll);  
    int size = files.size();   
    ofn<<size<<endl;  
    for (int i = 0; i < size; i++)    
    {    
        ofn<<files[i]<<endl;   
        cout<< files[i] << endl;  
    }  
    ofn.close();  
	cout << "============================================"<<endl;
	//取出图片 全部显示出来
	for (int i = 0; i < size; i++)    
	{     
	  cout<< files[i] << endl;  
	  Mat img = imread(files[i]);
	  namedWindow(files[i]);
	  imshow(files[i],img);
	} 
	waitKey();
    return 0;  
}  

/*
取出的文件带有路径：
C:\\Users\董师周\Desktop\testpic\color.jpg
C:\\Users\董师周\Desktop\testpic\pic.jpg
C:\\Users\董师周\Desktop\testpic\road.jpg
C:\\Users\董师周\Desktop\testpic\test\color.jpg
*/