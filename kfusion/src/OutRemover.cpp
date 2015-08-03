#include <kfusion\OutRemover.h>


OutRemover::OutRemover(int mean_k,float std_dev_mul):mean_k(mean_k),std_dev_mul(std_dev_mul),negative(0)
{

}


OutRemover::~OutRemover(void)
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

  pcl::PointIndices::Ptr removed_indices (new PointIndices),
                         indices (new PointIndices);
  std::vector<int> valid_indices;
  
  removeNaNFromPointCloud<PointXYZ> (*xyz_cloud_pre, *xyz_cloud, valid_indices);

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
  filter.getRemovedIndices (*removed_indices);
  
 
  printf("���\n");
  printf("��ʱ��%g ����\n",tt.toc ());
  printf("�Ƴ��㣺%d ��\n",removed_indices->indices.size ());


  for (size_t i = 0; i < removed_indices->indices.size (); ++i)
      indices->indices.push_back (valid_indices[removed_indices->indices[i]]);

  //���ʣ��ĵ�
  pcl::ExtractIndices<pcl::PCLPointCloud2> ei;
  ei.setInputCloud (input);
  ei.setIndices (indices);
  ei.setNegative (true);
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
		 return (-1);
  
	  //�����˲�
	   pcl::PCLPointCloud2 output;
	   runfilter(cloud, output, mean_k, std_dev_mul, negative);

	  //������Ƶ�ply
	   saveCloud (basedir+filename_out, output);
}