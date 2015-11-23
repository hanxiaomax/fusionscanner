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

   
  fromPCLPointCloud2 (*input, *xyz_cloud_pre);//�ѵ�������ת��Ϊ���ƶ���

  pcl::PointIndices::Ptr removed_indices (new PointIndices); 

  TicToc tt;
  tt.tic ();
  PointCloud<PointXYZ>::Ptr xyz_cloud_filtered (new PointCloud<PointXYZ> ());
  
  StatisticalOutlierRemoval<PointXYZ> filter (true);//�½��˲���

  /*�����˲�������*/
  filter.setInputCloud (xyz_cloud);
  filter.setMeanK (mean_k);
  filter.setStddevMulThresh (std_dev_mul);
  filter.setNegative (negative);
  filter.setKeepOrganized (0);

  printf("���� %lu ���㣬 mean_k��%d, std_dev_mul�� %f\n", xyz_cloud->size (), filter.getMeanK (), filter.getStddevMulThresh ());

  filter.filter (*xyz_cloud_filtered);
    // Get the indices that have been explicitly removed
  filter.getRemovedIndices (*removed_indices);//��ȡ���˵��ĵ������
  
 
  printf("���\n");
  printf("��ʱ��%g ����\n",tt.toc ());
  printf("�Ƴ��㣺%d ��\n",removed_indices->indices.size ());


	
  //��ȡ���������˲���
  pcl::ExtractIndices<pcl::PCLPointCloud2> ei;
  ei.setInputCloud (input);
  ei.setIndices (removed_indices);
  ei.setNegative (false);//ȡ���
  ei.filter (output);//����������ݽṹ
}	

void OutRemover::saveCloud (const std::string &filename, const pcl::PCLPointCloud2 &output)
{
	  TicToc tt;
	  tt.tic ();
	  printf("������...\n");
	  PLYWriter w;
	  w.writeASCII (filename, output);//дply�ļ�
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

	   Filename=splitFilename(filename);//��ȡ�ļ�������չ��

	   filename_out = Filename[0]+"-filterd"+Filename[1];//��������ļ���

	  // Load the first file
	   pcl::PCLPointCloud2::Ptr cloud (new pcl::PCLPointCloud2);
	   if (!loadCloud (basedir+filename, *cloud))
		 return (false);
  
	  //�����˲�
	   pcl::PCLPointCloud2 output;
	   runfilter(cloud, output, mean_k, std_dev_mul, negative);

	  //������Ƶ�ply
	   saveCloud (basedir+filename_out, output);
	   return true;
}


bool OutRemover::execute(const pcl::PointCloud<pcl::PointNormal>::ConstPtr &input, pcl::PointCloud<pcl::PointNormal> &output)
{
	  // Load the first file
	  PointCloud<PointNormal>::Ptr cloud_filtered (new PointCloud<PointNormal> ());
  
	  //�����˲�
	  runfilter(input,output,mean_k, std_dev_mul, negative);

	  printf("������...\n");
	  PLYWriter w;
	  w.write("./filtered.ply", output);
	  printf("�ɹ�...\n");
	  return true;
}
bool OutRemover::execute(const std::string &filename)
{
	printf("ok");
	return true;

}

//pcl::ExtractIndices<> ei;��֧��PointNormal
void OutRemover::runfilter(const pcl::PointCloud<pcl::PointNormal>::ConstPtr &input, pcl::PointCloud<pcl::PointNormal> &output,
          int mean_k, double std_dev_mul, bool negative)
{
	
	  pcl::PointIndices::Ptr removed_indices (new PointIndices);

	  TicToc tt;
	  tt.tic ();
	  PointCloud<PointNormal>::Ptr cloud_filtered (new PointCloud<PointNormal> ());//�˲������
  
	  StatisticalOutlierRemoval<pcl::PointNormal> filter (true);//�½��˲���

	  /*�����˲�������*/
	  filter.setInputCloud (input);
	  filter.setMeanK (mean_k);
	  filter.setStddevMulThresh (std_dev_mul);
	  filter.setNegative (false);//ȡ�ڵ�
	  filter.setKeepOrganized (0);

	  printf("���� %lu ���㣬 mean_k��%d, std_dev_mul�� %f\n",input->size(), filter.getMeanK (), filter.getStddevMulThresh ());
	  filter.filter (output);//ִ���˲����洦���Ľ��
	  filter.getRemovedIndices (*removed_indices);
  
 
	  printf("���\n");
	  printf("��ʱ��%g ����\n",tt.toc ());
	  printf("�Ƴ��㣺%d ��\n",removed_indices->indices.size ()); 

	  //���ʣ��ĵ�
	  //pcl::ExtractIndices<pcl::PointNormal> ei;
	  //ei.setInputCloud(input);
	  //ei.setIndices (removed_indices);
	  //ei.setNegative (true);
	  //ei.filter (output);//����������ݽṹ
}