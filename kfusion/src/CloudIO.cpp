/*Cmake�涨include·��Ϊ-->D:\SEU\3dSCAN\kinfu_remake\kfusion\include
* �������������ļ���
* io
* kfusion
*/
#include <kfusion/CloudIO.h>
#include <sstream>

CloudWriter::CloudWriter(void)
{

}


CloudWriter::~CloudWriter(void)
{

}
////////////////////////////////////////////////////////////////////////////////////////////
int  PLYFilewriter::write(const string &file_name,cuda::DeviceArray<Point> &cloud,int precision){
	ofstream f(file_name);
	//f.precision(precision);
	if (!f){
		infobox.printInfo("�޷����ļ�:"+file_name,InfoBox::ERR);
		return 0;
	}
	else{
		f<<headerGenerator(cloud);
		return writePoint(cloud,f);
	}
	f.close();
	
}
int  PLYFilewriter::write(const string &file_name,cuda::DeviceArray<Point> &cloud,cuda::DeviceArray<Normal> &normal,int precision){
	ofstream f(file_name);
	//f.precision(precision);
	if (!f){
		infobox.printInfo("�޷����ļ�:"+file_name,InfoBox::ERR);
		return 0;
	}
	else{
		f<<headerGenerator(cloud,true);
		return writePoint_Normal(cloud,normal,f);
	}
	f.close();

}



string PLYFilewriter::headerGenerator(cuda::DeviceArray<Point> &cloud,bool withNormal){
	ostringstream oss;//ʹ��ostringstream�𲽹����ַ���
	oss<<"ply";
	oss<<"\nformat ascii 1.0";
	oss<<"\ncomment author Lingfeng Ai";
	oss<<"\nelement vertex "<<(int)cloud.size();

	if(withNormal)
		oss<<"\nproperty float x\nproperty float y\nproperty float z\nproperty float nx\nproperty float ny\nproperty float nz";
	else
		oss<<"\nproperty float x\nproperty float y\nproperty float z";

	oss<<"\nend_header\n";
	infobox.printInfo("PLY ͷ�ļ�������",InfoBox::INFO);
	return (oss.str());
}




/*
* params:����
* params:�ļ���
*/
int PLYFilewriter::writePoint(cuda::DeviceArray<Point> &cloud ,std::ofstream& fs){
	
	infobox.printInfo("����д���",InfoBox::INFO);
	cv::Mat cloud_host(1, (int)cloud.size(), CV_32FC4);//һά���󣬴���������(1�У�n��) CV_32FC4 32λ����4ͨ��
	cloud.download(cloud_host.ptr<Point>());

	for (int i=0;i<cloud_host.cols;i++)
	{	
		float x=cloud_host.at<cv::Vec4f>(0,i)[0];
		float y=cloud_host.at<cv::Vec4f>(0,i)[1];
		float z=cloud_host.at<cv::Vec4f>(0,i)[2];
		fs<<x<<" "<<y<<" "<<z<<endl;			
	}
	
	infobox.printInfo("��������д�����",InfoBox::INFO);
	infobox.printInfo("PLY�ļ����ɳɹ�",InfoBox::SUC);
	
	return 1;
}

int PLYFilewriter::writePoint_Normal(cuda::DeviceArray<Point> &cloud ,cuda::DeviceArray<Point> &normal,std::ofstream& fs){

	infobox.printInfo("����д���",InfoBox::INFO);
	cv::Mat cloud_host(1, (int)cloud.size(), CV_32FC4);//һά���󣬴���������(1�У�n��) CV_32FC4 32λ����4ͨ��
	cv::Mat normal_host(1, (int)cloud.size(), CV_32FC4);

	cloud.download(cloud_host.ptr<Point>());
	normal.download(normal_host.ptr<Normal>());

	for (int i=0;i<cloud_host.cols;i++)
	{	
		float x=cloud_host.at<cv::Vec4f>(0,i)[0];
		float y=cloud_host.at<cv::Vec4f>(0,i)[1];
		float z=cloud_host.at<cv::Vec4f>(0,i)[2];
		float nx=normal_host.at<cv::Vec4f>(0,i)[0];
		float ny=normal_host.at<cv::Vec4f>(0,i)[1];
		float nz=normal_host.at<cv::Vec4f>(0,i)[2];
		fs<<x<<" "<<y<<" "<<z<<" "<<nx<<" "<<ny<<" "<<nz<<endl;			
	}
	infobox.printInfo("�������ݼ��䷨����д�����",InfoBox::INFO);
	infobox.printInfo("PLY�ļ����ɳɹ�",InfoBox::SUC);
	
	return 1;
}


/////////////////////////////////////////////////////////////////////////
int  PCDFilewriter::write(const string &file_name,cuda::DeviceArray<Point> &cloud,int precision){
	ofstream f(file_name);
	f.precision(precision);
	if (!f){
		infobox.printInfo("�޷����ļ�:"+file_name,InfoBox::ERR);
		return 0;
	}
	else{
		f<<headerGenerator(cloud);
		return writePoint(cloud,f);
	}
	f.close();
}

int  PCDFilewriter::write(const string &file_name,cuda::DeviceArray<Point> &cloud,cuda::DeviceArray<Point> &normal,int precision){
	ofstream f(file_name);
	f.precision(precision);
	if (!f){
		infobox.printInfo("�޷����ļ�:"+file_name,InfoBox::ERR);
		return 0;
	}
	else{
		f<<headerGenerator(cloud,true);
		return writePoint_Normal(cloud,normal,f);
	}
	f.close();
}


string PCDFilewriter::headerGenerator(cuda::DeviceArray<Point> &cloud,bool withNormal){
	ostringstream oss;//ʹ��ostringstream�𲽹����ַ���
	oss<<"# .PCD v0.7 - Point Cloud Data file format";
	oss<<"\nVERSION 0.7";
	if (withNormal)
	{
		oss<<"\nFIELDS x y z normal_x normal_y normal_z";
		oss<<"\nSIZE 4 4 4";
		oss<<"\nTYPE F F F";
		oss<<"\nCOUNT 1 1 1";
	}
	else
	{
		oss<<"\nFIELDS x y z";
		oss<<"\nSIZE 4 4 4 4 4 4";
		oss<<"\nTYPE F F F F F F";
		oss<<"\nCOUNT 1 1 1 1 1 1";
	}
	
	
	oss<<"\nWIDTH "<<(int)cloud.size();
	oss<<"\nHEIGHT 1";
	oss<<"\nVIEWPOINT 0 0 0 1 0 0 0";
	oss<<"\nPOINTS "<<(int)cloud.size();
	oss<<"\nDATA ascii\n";
	
	infobox.printInfo("PCD ͷ�ļ�������",InfoBox::INFO);

	return (oss.str());
}


/*
* params:����
* params:�ļ���
*/
int PCDFilewriter::writePoint(cuda::DeviceArray<Point> &cloud ,std::ofstream& fs){
	infobox.printInfo("����д���",InfoBox::INFO);
	cv::Mat cloud_host(1, (int)cloud.size(), CV_32FC4);//һά���󣬴���������(1�У�n��) CV_32FC4 32λ����4ͨ��
	cloud.download(cloud_host.ptr<Point>());

	for (int i=0;i<cloud_host.cols;i++)
	{	
		float x=cloud_host.at<cv::Vec4f>(0,i)[0];
		float y=cloud_host.at<cv::Vec4f>(0,i)[1];
		float z=cloud_host.at<cv::Vec4f>(0,i)[2];
		fs<<x<<" "<<y<<" "<<z<<endl;			
	}

	infobox.printInfo("��������д�����",InfoBox::INFO);
	infobox.printInfo("PCD�ļ����ɳɹ�",InfoBox::SUC);
	return 1;
}

int PCDFilewriter::writePoint_Normal(cuda::DeviceArray<Point> &cloud ,cuda::DeviceArray<Point> &normal,std::ofstream& fs){
	infobox.printInfo("����д���",InfoBox::INFO);
	cv::Mat cloud_host(1, (int)cloud.size(), CV_32FC4);//һά���󣬴���������(1�У�n��) CV_32FC4 32λ����4ͨ��
	cv::Mat normal_host(1, (int)cloud.size(), CV_32FC4);
	cloud.download(cloud_host.ptr<Point>());
	normal.download(normal_host.ptr<Normal>());
	for (int i=0;i<cloud_host.cols;i++)
	{	
		float x=cloud_host.at<cv::Vec4f>(0,i)[0];
		float y=cloud_host.at<cv::Vec4f>(0,i)[1];
		float z=cloud_host.at<cv::Vec4f>(0,i)[2];
		float nx=normal_host.at<cv::Vec4f>(0,i)[0];
		float ny=normal_host.at<cv::Vec4f>(0,i)[1];
		float nz=normal_host.at<cv::Vec4f>(0,i)[2];

		fs<<x<<" "<<y<<" "<<z<<" "<<nx<<" "<<ny<<" "<<nz<<endl;			
	}

	infobox.printInfo("�������ݼ��䷨����д�����",InfoBox::INFO);
	infobox.printInfo("PCD�ļ����ɳɹ�",InfoBox::SUC);
	
	return 1;
}


