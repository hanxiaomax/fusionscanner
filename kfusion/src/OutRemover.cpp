#include <kfusion\OutRemover.h>


OutRemover::OutRemover(int mean_k,float std_dev_mul):mean_k(mean_k),std_dev_mul(std_dev_mul),negative(0)
{

}



bool OutRemover::loadCloud (const std::string &filename, pcl::PCLPointCloud2 &cloud)
{
	if (loadPLYFile(filename, cloud) < 0)
		return (false);
    return (true);
}
void OutRemover::runfilter(const pcl::PCLPointCloud2::ConstPtr &input, pcl::PCLPointCloud2 &output,
          int mean_k, double std_dev_mul, bool negative)
{
	
	PointCloud<PointXYZ>::Ptr xyz_cloud_pre (new pcl::PointCloud<PointXYZ> ()),
                            xyz_cloud (new pcl::PointCloud<PointXYZ> ());

   
  fromPCLPointCloud2 (*input, *xyz_cloud_pre);//把点云数据转换为点云对象

  pcl::PointIndices::Ptr removed_indices (new PointIndices); 

  TicToc tt;
  tt.tic ();
  PointCloud<PointXYZ>::Ptr xyz_cloud_filtered (new PointCloud<PointXYZ> ());
  
  StatisticalOutlierRemoval<PointXYZ> filter (true);//新建滤波器

  /*设置滤波器参数*/
  filter.setInputCloud (xyz_cloud);
  filter.setMeanK (mean_k);
  filter.setStddevMulThresh (std_dev_mul);
  filter.setNegative (negative);
  filter.setKeepOrganized (0);

  printf("共计 %lu 个点， mean_k：%d, std_dev_mul： %f\n", xyz_cloud->size (), filter.getMeanK (), filter.getStddevMulThresh ());

  filter.filter (*xyz_cloud_filtered);
    // Get the indices that have been explicitly removed
  filter.getRemovedIndices (*removed_indices);//获取被滤掉的点的索引
  
 
  printf("完成\n");
  printf("耗时：%g 毫秒\n",tt.toc ());
  printf("移除点：%d 个\n",removed_indices->indices.size ());


	
  //提取点云索引滤波器
  pcl::ExtractIndices<pcl::PCLPointCloud2> ei;
  ei.setInputCloud (input);
  ei.setIndices (removed_indices);
  ei.setNegative (false);//取外点
  ei.filter (output);//输出点云数据结构
}	

void OutRemover::saveCloud (const std::string &filename, const pcl::PCLPointCloud2 &output)
{
	  TicToc tt;
	  tt.tic ();
	  printf("保存中...\n");
	  PLYWriter w;
	  w.writeASCII (filename, output);//写ply文件
}


std::vector<string> OutRemover::splitFilename(std::string filename)
{
	  std::string name,ext;
	  vector<string> result(128);
	  bool in_name = true;
	  for(string::iterator it=filename.begin();it!=filename.end();it++)
	  {	  
		  if(*it=='.'){
			in_name = false;
		  }
		  if(in_name){
			name.push_back(*it);
		  }
		  else{
			  ext.push_back(*it);
		  }
	  }
	  result[0]=name;
	  result[1]=ext;
	  return result;
}

bool OutRemover::execute()
{
	   std::vector<string> Filename(128);
	   std::string basedir = "../build/apps/";
	   std::string filename ="cloud_file-n.ply";
	   std::string filename_out;

	   Filename=splitFilename(filename);//获取文件名和扩展名

	   filename_out = Filename[0]+"-filterd"+Filename[1];//生成输出文件名

	  // Load the first file
	   pcl::PCLPointCloud2::Ptr cloud (new pcl::PCLPointCloud2);
	   if (!loadCloud (basedir+filename, *cloud))
		 return (false);
  
	  //进行滤波
	   pcl::PCLPointCloud2 output;
	   runfilter(cloud, output, mean_k, std_dev_mul, negative);

	  //保存点云到ply
	   saveCloud (basedir+filename_out, output);
	   return true;
}


bool OutRemover::execute(const pcl::PointCloud<pcl::PointNormal>::ConstPtr &input, pcl::PointCloud<pcl::PointNormal> &output)
{
	  // Load the first file
	  PointCloud<PointNormal>::Ptr cloud_filtered (new PointCloud<PointNormal> ());
  
	  //进行滤波
	  runfilter(input,output,mean_k, std_dev_mul, negative);

	  printf("保存中...\n");
	  PLYWriter w;
	  w.write("./filtered.ply", output);
	  printf("成功...\n");
	  return true;
}
bool OutRemover::execute(const std::string &filename)
{
	printf("ok");
	return true;

}

//pcl::ExtractIndices<> ei;不支持PointNormal
void OutRemover::runfilter(const pcl::PointCloud<pcl::PointNormal>::ConstPtr &input, pcl::PointCloud<pcl::PointNormal> &output,
          int mean_k, double std_dev_mul, bool negative)
{
	
	  pcl::PointIndices::Ptr removed_indices (new PointIndices);

	  TicToc tt;
	  tt.tic ();
	  PointCloud<PointNormal>::Ptr cloud_filtered (new PointCloud<PointNormal> ());//滤波后点云
  
	  StatisticalOutlierRemoval<pcl::PointNormal> filter (true);//新建滤波器

	  /*设置滤波器参数*/
	  filter.setInputCloud (input);
	  filter.setMeanK (mean_k);
	  filter.setStddevMulThresh (std_dev_mul);
	  filter.setNegative (false);//取内点
	  filter.setKeepOrganized (0);

	  printf("共计 %lu 个点， mean_k：%d, std_dev_mul： %f\n",input->size(), filter.getMeanK (), filter.getStddevMulThresh ());
	  filter.filter (output);//执行滤波保存处理后的结果
	  filter.getRemovedIndices (*removed_indices);
  
 
	  printf("完成\n");
	  printf("耗时：%g 毫秒\n",tt.toc ());
	  printf("移除点：%d 个\n",removed_indices->indices.size ()); 

	  //输出剩余的点
	  //pcl::ExtractIndices<pcl::PointNormal> ei;
	  //ei.setInputCloud(input);
	  //ei.setIndices (removed_indices);
	  //ei.setNegative (true);
	  //ei.filter (output);//输出点云数据结构
}