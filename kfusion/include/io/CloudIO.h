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
	virtual ~CloudWriter(void);
public:
	
	virtual int write(const string &file_name,cuda::DeviceArray<Point> &cloud)=0;//不能给出有意义的实现，定义为虚函数，否则出现LINK2001，虚函数没有实现
};


class PCDFilewriter:public CloudWriter{

public:
	PCDFilewriter():CloudWriter(){};//必须有函数体，因为没有在.cpp文件中定义，否则出现LINK2019,虚函数没有实现
	~PCDFilewriter(){};
private:
	string headerGenerator(cuda::DeviceArray<Point> &cloud);//生成header字符串
	int writePoint(cuda::DeviceArray<Point> &cloud,std::ofstream& fs);//写入点
public:
	virtual int write(const string &file_name,cuda::DeviceArray<Point> &cloud);
	
};

class PLYFilewriter:public CloudWriter{

public:
	PLYFilewriter():CloudWriter(){};
	~PLYFilewriter(){};
private:
	string headerGenerator(cuda::DeviceArray<Point> &cloud);//生成header字符串
	int writePoint(cuda::DeviceArray<Point> &cloud,std::ofstream& fs);//写入点
public:
	virtual int write(const string &file_name,cuda::DeviceArray<Point> &cloud);
};