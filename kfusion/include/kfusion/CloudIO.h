#ifndef CLOULDIO_H_H
#define CLOULDIO_H_H


#include <iostream>
#include <fstream>
#include <kfusion/kinfu.hpp>



/*�����ļ�д��������*/
using namespace std;
using namespace kfusion;
using namespace pcl::io;

class CloudWriter
{
public:
	CloudWriter(void){};//û�к����壬��Ϊ��������cpp�ļ��ж����ˡ�
	virtual ~CloudWriter(void){};//�������������Ҫ���麯�������캯������Ϊ��
public:
	virtual int write(const string &file_name,cuda::DeviceArray<Point> &cloud,int precision)=0;//���ܸ����������ʵ�֣�����Ϊ�麯�����������LINK2001���麯��û��ʵ��
};


class PCDFilewriter:public CloudWriter{

public:
	PCDFilewriter():CloudWriter(),infobox("PCDFilewriter"),valid_point(0){};//�����к����壬��Ϊû����.cpp�ļ��ж��壬�������LINK2019,�麯��û��ʵ��
	~PCDFilewriter(){};
private:
	string headerGenerator(cuda::DeviceArray<Point> &cloud,bool withNormal=false);//����header�ַ���
	string headerGenerator(cuda::DeviceArray<Point> &cloud,bool withNormal=false,int valid_point=0);//ֻд����Ч����

	int writePoint(cuda::DeviceArray<Point> &cloud,std::ofstream& fs);//д���
	int writePoint_Normal(cuda::DeviceArray<Point> &cloud,cuda::DeviceArray<Normal> &normal,std::ofstream& fs);
	string writePoint_Normal(cuda::DeviceArray<Point> &cloud,cuda::DeviceArray<Normal> &normal,int &valid_point);//ֻд����Ч����

	InfoBox infobox;//����֪ͨ������
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
	string headerGenerator(cuda::DeviceArray<Point> &cloud,bool withNormal=false);//����header�ַ���
	string headerGenerator(cuda::DeviceArray<Point> &cloud,bool withNormal=false,int valid_point=0);
	int writePoint(cuda::DeviceArray<Point> &cloud,std::ofstream& fs);//д���
	int writePoint_Normal(cuda::DeviceArray<Point> &cloud,cuda::DeviceArray<Normal> &normal,std::ofstream& fs);
	string writePoint_Normal(cuda::DeviceArray<Point> &cloud,cuda::DeviceArray<Normal> &normal,int &valid_point);

	InfoBox infobox;
	int valid_point;
public:
	virtual int write(const string &file_name,cuda::DeviceArray<Point> &cloud,int precision=5);
	virtual int write(const string &file_name,cuda::DeviceArray<Point> &cloud,cuda::DeviceArray<Normal> &normal,int precision=5);
	//��Ҫһ��д���Ƶ�
};


class CloudReader
{
public:
	CloudReader(void){};
	virtual ~CloudReader(void){};//�������������Ҫ���麯�������캯������Ϊ��
public:
	virtual int read(const string &file_name,cv::Mat &cloud_host)=0;//��ȡ������
	virtual int readToVertexes(const string &file_name,vertexes &cloud_vertex,bool normal)=0;//��ȡ���ɶ���
};


class PLYFilereader:public CloudReader{

public:
	PLYFilereader():CloudReader(),infobox("PLYFileReader"),valid_point(0){};
	~PLYFilereader(){};
public:
	virtual int read(const string &file_name,cv::Mat &cloud_host);//��ȡ������
	virtual int readToVertexes(const string &file_name,vertexes &cloud_vertex,bool normal);//��ȡ���ɶ���
	virtual int readToVertexes(const string &file_name,pcl::PointCloud<pcl::PointNormal> &input,vertexes &cloud_vertex,bool normal);
private:
	InfoBox infobox;
	int valid_point;
private:
	bool loadPlyCloud (const std::string &filename, pcl::PointCloud<pcl::PointNormal> &cloud);//��PLY�ļ�ת��ΪPCL������
};



#endif