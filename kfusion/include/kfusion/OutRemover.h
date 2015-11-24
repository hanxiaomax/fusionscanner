#ifndef OUTREMOVER_HH
#define OUTREMOVER_HH

#pragma once
#include <kfusion/types.hpp>
#include "pcl/time.h"
#include "pcl/statistical_outlier_removal.h"
#include "pcl/extract_indices.h"
#include <vector>
#include <string>

using namespace pcl;
using namespace pcl::io;
using namespace pcl::console;
using namespace std;

class OutRemover
{
public:
	OutRemover(int mean_k,float std_dev_mul);
	~OutRemover(){};
public:
	bool execute();
	bool execute(const std::string &filename);
	bool execute(const pcl::PointCloud<pcl::PointNormal>::ConstPtr &input, pcl::PointCloud<pcl::PointNormal> &output);

private:
	bool loadCloud (const std::string &filename, pcl::PCLPointCloud2 &cloud);//���ص���
	void runfilter(const pcl::PCLPointCloud2::ConstPtr &input, pcl::PCLPointCloud2 &output,
          int mean_k, double std_dev_mul, bool negative);//ִ���˲���
	void runfilter(const pcl::PointCloud<pcl::PointNormal>::ConstPtr &input, pcl::PointCloud<pcl::PointNormal> &output,
          int mean_k, double std_dev_mul, bool negative);


	void saveCloud (const std::string &filename, const pcl::PCLPointCloud2 &output);//������Ƶ�ply�ļ�
	std::vector<string> splitFilename(std::string filename);//�ָ��ļ���
private:
   //����Ĭ�ϲ���
    int mean_k ;
    double std_dev_mul;
    int negative;
};

#endif