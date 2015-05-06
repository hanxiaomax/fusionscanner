/*Cmake规定include路径为-->D:\SEU\3dSCAN\kinfu_remake\kfusion\include
* 包含如下两个文件夹
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
		infobox.printInfo("无法打开文件:"+file_name,InfoBox::ERR);
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
		infobox.printInfo("无法打开文件:"+file_name,InfoBox::ERR);
		return 0;
	}
	else{
		f<<headerGenerator(cloud,true);
		return writePoint_Normal(cloud,normal,f);
	}
	f.close();

}



string PLYFilewriter::headerGenerator(cuda::DeviceArray<Point> &cloud,bool withNormal){
	ostringstream oss;//使用ostringstream逐步构造字符串
	oss<<"ply";
	oss<<"\nformat ascii 1.0";
	oss<<"\ncomment author Lingfeng Ai";
	oss<<"\nelement vertex "<<(int)cloud.size();

	if(withNormal)
		oss<<"\nproperty float x\nproperty float y\nproperty float z\nproperty float nx\nproperty float ny\nproperty float nz";
	else
		oss<<"\nproperty float x\nproperty float y\nproperty float z";

	oss<<"\nend_header\n";
	infobox.printInfo("PLY 头文件已生成",InfoBox::INFO);
	return (oss.str());
}




/*
* params:点云
* params:文件流
*/
int PLYFilewriter::writePoint(cuda::DeviceArray<Point> &cloud ,std::ofstream& fs){
	
	infobox.printInfo("正在写入点",InfoBox::INFO);
	cv::Mat cloud_host(1, (int)cloud.size(), CV_32FC4);//一维矩阵，存放无序点云(1行，n列) CV_32FC4 32位浮点4通道
	cloud.download(cloud_host.ptr<Point>());

	for (int i=0;i<cloud_host.cols;i++)
	{	
		float x=cloud_host.at<cv::Vec4f>(0,i)[0];
		float y=cloud_host.at<cv::Vec4f>(0,i)[1];
		float z=cloud_host.at<cv::Vec4f>(0,i)[2];
		fs<<x<<" "<<y<<" "<<z<<endl;			
	}
	
	infobox.printInfo("点云数据写入完成",InfoBox::INFO);
	infobox.printInfo("PLY文件生成成功",InfoBox::SUC);
	
	return 1;
}

int PLYFilewriter::writePoint_Normal(cuda::DeviceArray<Point> &cloud ,cuda::DeviceArray<Point> &normal,std::ofstream& fs){

	infobox.printInfo("正在写入点",InfoBox::INFO);
	cv::Mat cloud_host(1, (int)cloud.size(), CV_32FC4);//一维矩阵，存放无序点云(1行，n列) CV_32FC4 32位浮点4通道
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
	infobox.printInfo("点云数据及其法向量写入完成",InfoBox::INFO);
	infobox.printInfo("PLY文件生成成功",InfoBox::SUC);
	
	return 1;
}


/////////////////////////////////////////////////////////////////////////
int  PCDFilewriter::write(const string &file_name,cuda::DeviceArray<Point> &cloud,int precision){
	ofstream f(file_name);
	f.precision(precision);
	if (!f){
		infobox.printInfo("无法打开文件:"+file_name,InfoBox::ERR);
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
		infobox.printInfo("无法打开文件:"+file_name,InfoBox::ERR);
		return 0;
	}
	else{
		f<<headerGenerator(cloud,true);
		return writePoint_Normal(cloud,normal,f);
	}
	f.close();
}


string PCDFilewriter::headerGenerator(cuda::DeviceArray<Point> &cloud,bool withNormal){
	ostringstream oss;//使用ostringstream逐步构造字符串
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
	
	infobox.printInfo("PCD 头文件已生成",InfoBox::INFO);

	return (oss.str());
}


/*
* params:点云
* params:文件流
*/
int PCDFilewriter::writePoint(cuda::DeviceArray<Point> &cloud ,std::ofstream& fs){
	infobox.printInfo("正在写入点",InfoBox::INFO);
	cv::Mat cloud_host(1, (int)cloud.size(), CV_32FC4);//一维矩阵，存放无序点云(1行，n列) CV_32FC4 32位浮点4通道
	cloud.download(cloud_host.ptr<Point>());

	for (int i=0;i<cloud_host.cols;i++)
	{	
		float x=cloud_host.at<cv::Vec4f>(0,i)[0];
		float y=cloud_host.at<cv::Vec4f>(0,i)[1];
		float z=cloud_host.at<cv::Vec4f>(0,i)[2];
		fs<<x<<" "<<y<<" "<<z<<endl;			
	}

	infobox.printInfo("点云数据写入完成",InfoBox::INFO);
	infobox.printInfo("PCD文件生成成功",InfoBox::SUC);
	return 1;
}

int PCDFilewriter::writePoint_Normal(cuda::DeviceArray<Point> &cloud ,cuda::DeviceArray<Point> &normal,std::ofstream& fs){
	infobox.printInfo("正在写入点",InfoBox::INFO);
	cv::Mat cloud_host(1, (int)cloud.size(), CV_32FC4);//一维矩阵，存放无序点云(1行，n列) CV_32FC4 32位浮点4通道
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

	infobox.printInfo("点云数据及其法向量写入完成",InfoBox::INFO);
	infobox.printInfo("PCD文件生成成功",InfoBox::SUC);
	
	return 1;
}


