#include <iostream>
#include <fstream>
#include <kfusion/kinfu.hpp>


/*�����ļ�д��������*/
using namespace std;
using namespace kfusion;

class CloudWriter
{
public:
	CloudWriter(void);//û�к����壬��Ϊ��������cpp�ļ��ж����ˡ�
	virtual ~CloudWriter(void);//�������������Ҫ���麯�������캯������Ϊ��
public:
	
	virtual int write(const string &file_name,cuda::DeviceArray<Point> &cloud)=0;//���ܸ����������ʵ�֣�����Ϊ�麯�����������LINK2001���麯��û��ʵ��
};


class PCDFilewriter:public CloudWriter{

public:
	PCDFilewriter():CloudWriter(),infobox("PCDFilewriter"){};//�����к����壬��Ϊû����.cpp�ļ��ж��壬�������LINK2019,�麯��û��ʵ��
	~PCDFilewriter(){};
private:
	string headerGenerator(cuda::DeviceArray<Point> &cloud);//����header�ַ���
	int writePoint(cuda::DeviceArray<Point> &cloud,std::ofstream& fs);//д���
	InfoBox infobox;//����֪ͨ������
public:
	virtual int write(const string &file_name,cuda::DeviceArray<Point> &cloud);
	
};

class PLYFilewriter:public CloudWriter{

public:
	PLYFilewriter():CloudWriter(),infobox("PLYFilewriter"){};
	~PLYFilewriter(){};
private:
	string headerGenerator(cuda::DeviceArray<Point> &cloud);//����header�ַ���
	int writePoint(cuda::DeviceArray<Point> &cloud,std::ofstream& fs);//д���
	InfoBox infobox;
public:
	virtual int write(const string &file_name,cuda::DeviceArray<Point> &cloud);
};