#ifndef CLOULDIO_H_H
#define CLOULDIO_H_H

#include <iostream>
#include <fstream>
#include <kfusion/kinfu.hpp>



/*点云文件写操作基类*/
using namespace std;
using namespace kfusion;

class CloudWriter
{
public:
	CloudWriter(void);//没有函数体，因为函数体在cpp文件中定义了。
	virtual ~CloudWriter(void);//基类的析构函数要是虚函数，构造函数不能为虚
public:
	
	virtual int write(const string &file_name,cuda::DeviceArray<Point> &cloud,int precision)=0;//不能给出有意义的实现，定义为虚函数，否则出现LINK2001，虚函数没有实现
};


class PCDFilewriter:public CloudWriter{

public:
	PCDFilewriter():CloudWriter(),infobox("PCDFilewriter"){};//必须有函数体，因为没有在.cpp文件中定义，否则出现LINK2019,虚函数没有实现
	~PCDFilewriter(){};
private:
	string headerGenerator(cuda::DeviceArray<Point> &cloud,bool withNormal=false);//生成header字符串
	int writePoint(cuda::DeviceArray<Point> &cloud,std::ofstream& fs);//写入点
	int writePoint_Normal(cuda::DeviceArray<Point> &cloud,cuda::DeviceArray<Normal> &normal,std::ofstream& fs);
	InfoBox infobox;//创建通知处理器
public:
	virtual int write(const string &file_name,cuda::DeviceArray<Point> &cloud,int precision=5);
	virtual int write(const string &file_name,cuda::DeviceArray<Point> &cloud,cuda::DeviceArray<Point> &normal,int precision=5);
	
};

class PLYFilewriter:public CloudWriter{

public:
	PLYFilewriter():CloudWriter(),infobox("PLYFilewriter"){};
	~PLYFilewriter(){};
private:
	string headerGenerator(cuda::DeviceArray<Point> &cloud,bool withNormal=false);//生成header字符串
	int writePoint(cuda::DeviceArray<Point> &cloud,std::ofstream& fs);//写入点
	int writePoint_Normal(cuda::DeviceArray<Point> &cloud,cuda::DeviceArray<Normal> &normal,std::ofstream& fs);
	InfoBox infobox;
public:
	virtual int write(const string &file_name,cuda::DeviceArray<Point> &cloud,int precision=5);
	virtual int write(const string &file_name,cuda::DeviceArray<Point> &cloud,cuda::DeviceArray<Normal> &normal,int precision=5);
};

#endif