#ifndef CLOULDIO_H_H
#define CLOULDIO_H_H


#include <iostream>
#include <fstream>
#include <kfusion/kinfu.hpp>



/*点云文件写操作基类*/
using namespace std;
using namespace kfusion;
using namespace pcl::io;

class CloudWriter
{
public:
	CloudWriter(void){};//没有函数体，因为函数体在cpp文件中定义了。
	virtual ~CloudWriter(void){};//基类的析构函数要是虚函数，构造函数不能为虚
public:
	virtual int write(const string &file_name,cuda::DeviceArray<Point> &cloud,int precision)=0;//不能给出有意义的实现，定义为虚函数，否则出现LINK2001，虚函数没有实现
};


class PCDFilewriter:public CloudWriter{

public:
	PCDFilewriter():CloudWriter(),infobox("PCDFilewriter"),valid_point(0){};//必须有函数体，因为没有在.cpp文件中定义，否则出现LINK2019,虚函数没有实现
	~PCDFilewriter(){};
private:
	string headerGenerator(cuda::DeviceArray<Point> &cloud,bool withNormal=false);//生成header字符串
	string headerGenerator(cuda::DeviceArray<Point> &cloud,bool withNormal=false,int valid_point=0);//只写入有效数据

	int writePoint(cuda::DeviceArray<Point> &cloud,std::ofstream& fs);//写入点
	int writePoint_Normal(cuda::DeviceArray<Point> &cloud,cuda::DeviceArray<Normal> &normal,std::ofstream& fs);
	string writePoint_Normal(cuda::DeviceArray<Point> &cloud,cuda::DeviceArray<Normal> &normal,int &valid_point);//只写入有效数据

	InfoBox infobox;//创建通知处理器
	int valid_point;
public:
	virtual int write(const string &file_name,cuda::DeviceArray<Point> &cloud,int precision=5);
	virtual int write(const string &file_name,cuda::DeviceArray<Point> &cloud,cuda::DeviceArray<Point> &normal,int precision=5);
	
};

class PLYFilewriter:public CloudWriter{

public:
	PLYFilewriter():CloudWriter(),infobox("PLYFilewriter"),valid_point(0){};
	~PLYFilewriter(){};
private:
	string headerGenerator(cuda::DeviceArray<Point> &cloud,bool withNormal=false);//生成header字符串
	string headerGenerator(cuda::DeviceArray<Point> &cloud,bool withNormal=false,int valid_point=0);
	int writePoint(cuda::DeviceArray<Point> &cloud,std::ofstream& fs);//写入点
	int writePoint_Normal(cuda::DeviceArray<Point> &cloud,cuda::DeviceArray<Normal> &normal,std::ofstream& fs);
	string writePoint_Normal(cuda::DeviceArray<Point> &cloud,cuda::DeviceArray<Normal> &normal,int &valid_point);

	InfoBox infobox;
	int valid_point;
public:
	virtual int write(const string &file_name,cuda::DeviceArray<Point> &cloud,int precision=5);
	virtual int write(const string &file_name,cuda::DeviceArray<Point> &cloud,cuda::DeviceArray<Normal> &normal,int precision=5);
	//需要一个写点云的
};


class CloudReader
{
public:
	CloudReader(void){};
	virtual ~CloudReader(void){};//基类的析构函数要是虚函数，构造函数不能为虚
public:
	virtual int read(const string &file_name,cv::Mat &cloud_host)=0;//读取到矩阵
	virtual int readToVertexes(const string &file_name,vertexes &cloud_vertex,bool normal)=0;//读取生成顶点
};


class PLYFilereader:public CloudReader{

public:
	PLYFilereader():CloudReader(),infobox("PLYFileReader"),valid_point(0){};
	~PLYFilereader(){};
public:
	virtual int read(const string &file_name,cv::Mat &cloud_host);//读取到矩阵
	virtual int readToVertexes(const string &file_name,vertexes &cloud_vertex,bool normal);//读取生成顶点
	virtual int readToVertexes(const string &file_name,pcl::PointCloud<pcl::PointNormal> &input,vertexes &cloud_vertex,bool normal);
private:
	InfoBox infobox;
	int valid_point;
private:
	bool loadPlyCloud (const std::string &filename, pcl::PointCloud<pcl::PointNormal> &cloud);//将PLY文件转换为PCL点类型
};



#endif