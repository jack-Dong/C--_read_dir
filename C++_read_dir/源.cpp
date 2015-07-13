#include <io.h>  
#include <fstream>  
#include <string>  
#include <vector>  
#include <iostream>  
#include "opencv.hpp";
using namespace std;  
using namespace cv;  
  
//��ȡ���е��ļ���  
void GetAllFiles( string path, vector<string>& files)    
{    
  
    long  hFile   =   0;    
    //�ļ���Ϣ    
    struct _finddata_t fileinfo;    
    string p;    
    if( ( hFile = _findfirst( p.assign(path).append("\\*").c_str(), &fileinfo) ) !=  -1 )    
    {    
        do    
        {     
            if( ( fileinfo.attrib &  _A_SUBDIR ) )    //����ļ����������ļ���
            {    
                if( (strcmp( fileinfo.name, "." ) != 0 ) && ( strcmp( fileinfo.name, ".." ) != 0) ) //�ܿ�'.' ��'..'    
                {  
                    //files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  //Ŀ¼����Ӧ����
                    GetAllFiles( p.assign(path).append("\\").append(fileinfo.name), files );   //�ݹ�ץȡ�ļ���
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
  ��ȡ�ض���ʽ���ļ���
  ���룺 string path, vector<string>& files,string format
  ����� void
*/
void GetAllFormatFiles( string path, vector<string>& files,string format)    
{    
	//format���Сд
	unsigned int pos = 0;
	for(auto var : format)
	{
		format[pos] = tolower(var);
		pos++;
	}
    //�ļ����    
    long   hFile = 0;    
    //�ļ���Ϣ    
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
            {   //�ж��ļ������Ƿ����
				string str = fileinfo.name; //ת����string
				string str_end = str.substr(str.size() - format.size(), format.size());  //ȡĩβ�ִ�
				//cout <<"str_end :   " <<str_end<<endl;
				unsigned int i = 0;
				for(auto var : str_end)//���Сд�ٱȽ�
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
	string filePath = "C:\\\\Users\\��ʦ��\\Desktop\\testpic";  //'\' ��ʾת���
    vector<string> files;    
    char * distAll = "AllFiles.txt";  
  
    //��ȡ���е��ļ����������ļ����ļ�  
    // GetAllFiles(filePath, files);  

 
    //��ȡ���и�ʽΪjpg���ļ�  
    string format = ".jpg";  
    GetAllFormatFiles(filePath, files,format);  
    //������ļ�
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
	//ȡ��ͼƬ ȫ����ʾ����
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
ȡ�����ļ�����·����
C:\\Users\��ʦ��\Desktop\testpic\color.jpg
C:\\Users\��ʦ��\Desktop\testpic\pic.jpg
C:\\Users\��ʦ��\Desktop\testpic\road.jpg
C:\\Users\��ʦ��\Desktop\testpic\test\color.jpg
*/