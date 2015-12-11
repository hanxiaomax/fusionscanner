/*Cmake规定include路径为-->D:\SEU\3dSCAN\kinfu_remake\kfusion\include
* 包含如下两个文件夹
* io
* kfusion
*/
#include <kfusion/CloudIO.h>
#include <sstream>
#include <cmath>  

////////////////////////////////////////////////////////////////////////////////////////////
int  PLYFilewriter::write(const string &file_name,cuda::DeviceArray<Point> &cloud,int precision){
	ofstream f(file_name);
	//f.precision(precision);
	if (!f){
		infobox.printInfo("无法打开文件:"+file_name,InfoBox::ERR);
		return 0;
	}
	else{
		//f<<headerGenerator(cloud);
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
		string result = writePoint_Normal(cloud,normal,valid_point);
		f<<headerGenerator(cloud,true,valid_point);
		f<<result;
		return 1;
	}
	f.close();
	
}
int PLYFilewriter::write(const string &finle_name,pcl::PointCloud<pcl::PointNormal> &cloud,bool with_normal)
{
	//PLYWriter w

	pcl::PLYWriter w;
	w.write(finle_name,cloud);
	return 1;
}

string PLYFilewriter::headerGenerator(cuda::DeviceArray<Point> &cloud,bool withNormal,int valid_point)
{
	ostringstream oss;//使用ostringstream逐步构造字符串
	oss<<"ply";
	oss<<"\nformat ascii 1.0";
	oss<<"\ncomment author Lingfeng Ai";
	oss<<"\nelement vertex "<<valid_point;

	if(withNormal)
		oss<<"\nproperty float x\nproperty float y\nproperty float z\nproperty float nx\nproperty float ny\nproperty float nz";
	else
		oss<<"\nproperty float x\nproperty float y\nproperty float z";

	oss<<"\nend_header\n";
	infobox.printInfo("PLY 头文件已生成",InfoBox::INFO);
	return (oss.str());
}
////
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
int PLYFilewriter::writePoint	(cuda::DeviceArray<Point> &cloud ,std::ofstream& fs){
	
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
/////
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

string PLYFilewriter::writePoint_Normal(cuda::DeviceArray<Point> &cloud ,cuda::DeviceArray<Point> &normal,int &valid_point)
{
	ostringstream oss;
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
		if (nx<1&&ny<1&&nz<1)
		{
			valid_point++;
			oss<<x<<" "<<y<<" "<<z<<" "<<nx<<" "<<ny<<" "<<nz<<endl;			
		}	
	}
	infobox.printInfo("点云数据及其法向量写入完成",InfoBox::INFO);
	infobox.printInfo("PLY文件生成成功",InfoBox::SUC);
	return (oss.str());
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
		//f<<headerGenerator(cloud);
		return writePoint(cloud,f);
	}
	f.close();
}

int  PCDFilewriter::write(const string &file_name,cuda::DeviceArray<Point> &cloud,cuda::DeviceArray<Point> &normal,int precision)
{
	ofstream f(file_name);
	f.precision(precision);
	if (!f){
		infobox.printInfo("无法打开文件:"+file_name,InfoBox::ERR);
		return 0;
	}
	else{
		string result = writePoint_Normal(cloud,normal,valid_point);
		f<<headerGenerator(cloud,true,valid_point);
		f<<result;
		return 1;
	}
	f.close();
}


string PCDFilewriter::headerGenerator(cuda::DeviceArray<Point> &cloud,bool withNormal,int valid_point){
	ostringstream oss;//使用ostringstream逐步构造字符串
	oss<<"# .PCD v0.7 - Point Cloud Data file format";
	oss<<"\nVERSION 0.7";
	if (withNormal)
	{
		oss<<"\nFIELDS x y z normal_x normal_y normal_z";
		oss<<"\nSIZE 4 4 4 4 4 4";
		oss<<"\nTYPE F F F F F F";
		oss<<"\nCOUNT 1 1 1 1 1 1";
	}
	else
	{
		oss<<"\nFIELDS x y z";
		oss<<"\nSIZE 4 4 4";
		oss<<"\nTYPE F F F";
		oss<<"\nCOUNT 1 1 1";
	}


	oss<<"\nWIDTH "<<valid_point;
	oss<<"\nHEIGHT 1";
	oss<<"\nVIEWPOINT 0 0 0 1 0 0 0";
	oss<<"\nPOINTS "<<valid_point;
	oss<<"\nDATA ascii\n";

	infobox.printInfo("PCD 头文件已生成",InfoBox::INFO);
	cout<<"cloud size :"<<(int)cloud.size()<<endl;
	cout<<"valid_point :"<<valid_point<<endl;


	return (oss.str());
}

/////
string PCDFilewriter::headerGenerator(cuda::DeviceArray<Point> &cloud,bool withNormal){
	ostringstream oss;//使用ostringstream逐步构造字符串
	oss<<"# .PCD v0.7 - Point Cloud Data file format";
	oss<<"\nVERSION 0.7";
	if (withNormal)
	{
		oss<<"\nFIELDS x y z normal_x normal_y normal_z";
		oss<<"\nSIZE 4 4 4 4 4 4";
		oss<<"\nTYPE F F F F F F";
		oss<<"\nCOUNT 1 1 1 1 1 1";
	}
	else
	{
		oss<<"\nFIELDS x y z";
		oss<<"\nSIZE 4 4 4";
		oss<<"\nTYPE F F F";
		oss<<"\nCOUNT 1 1 1";
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

/////////////////
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

string PCDFilewriter::writePoint_Normal(cuda::DeviceArray<Point> &cloud,cuda::DeviceArray<Normal> &normal,int &valid_point)
{
	infobox.printInfo("正在写入点",InfoBox::INFO);
	ostringstream oss;
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
		
		if (nx<1&&ny<1&&nz<1)
		{
			valid_point++;
			oss<<x<<" "<<y<<" "<<z<<" "<<nx<<" "<<ny<<" "<<nz<<endl;			
		}
	}

	infobox.printInfo("点云数据及其法向量写入完成",InfoBox::INFO);
	infobox.printInfo("PCD文件生成成功",InfoBox::SUC);
	
	return (oss.str());
}


///////////////////////////

int PLYFilereader::read(const string &file_name,cv::Mat &cloud_host)
{
	return 0;
}

int PLYFilereader::readToVertexes(const string &file_name,vertexes &cloud_vertex,bool normal)
{
	pcl::PointCloud<pcl::PointNormal> input;
	if(loadPlyCloud(file_name,input))
	{
		for(int i=0;i<input.points.size();i++)
		{	
			cv::Point3d vertex;
			vertex.x=input.points[i].x;
			vertex.y=input.points[i].y;
			vertex.z=input.points[i].z;
			cloud_vertex.push_back(vertex);
		}
		return 1;
		
	}
	return 0;
}
int PLYFilereader::readToVertexes(const string &file_name,pcl::PointCloud<pcl::PointNormal> &input,vertexes &cloud_vertex,bool normal)
{
	if(loadPlyCloud(file_name,input))
	{
		for(int i=0;i<input.points.size();i++)
		{	
			cv::Point3d vertex;
			vertex.x=input.points[i].x;
			vertex.y=input.points[i].y;
			vertex.z=input.points[i].z;
			cloud_vertex.push_back(vertex);
		}
		return 1;

	}
	
	return 0;
}

bool PLYFilereader::loadPlyCloud (const std::string &filename, pcl::PointCloud<pcl::PointNormal> &cloud)
{
	if (loadPLYFile(filename, cloud) < 0)
		return (false);
    return (true);

}