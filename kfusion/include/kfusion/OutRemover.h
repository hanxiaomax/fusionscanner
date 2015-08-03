#pragma once
#include "pcl/PCLPointCloud2.h"
#include "pcl/point_types.h"
#include "pcl/ply_io.h"
#include "pcl/time.h"
#include "pcl/statistical_outlier_removal.h"
#include "pcl/extract_indices.h"
#include <vector>
#include <stdio.h>
#include <string>

using namespace pcl;
using namespace pcl::io;
using namespace pcl::console;
using namespace std;

class OutRemover
{
public:
	OutRemover(int mean_k,float std_dev_mul);
	~OutRemover(void);
public:
	bool execute();
private:
	bool loadCloud (const std::string &filename, pcl::PCLPointCloud2 &cloud);//���ص���
	void runfilter(const pcl::PCLPointCloud2::ConstPtr &input, pcl::PCLPointCloud2 &output,
          int mean_k, double std_dev_mul, bool negative);//ִ���˲���
	
	void saveCloud (const std::string &filename, const pcl::PCLPointCloud2 &output);//������Ƶ�ply�ļ�
	std::vector<string> splitFilename(std::string filename);//�ָ��ļ���
private:
   //����Ĭ�ϲ���
    int mean_k ;
    double std_dev_mul;
    int negative;
};

