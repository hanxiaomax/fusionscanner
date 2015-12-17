#include <kfusion/MCmesh.h>

using namespace mesh;
MCmesh::MCmesh(void):
	input_(new pcl::PointCloud<pcl::PointNormal>()),
	tree_(new pcl::KdTreeFLANN<pcl::PointNormal>()),
	min_p(), max_p()
{
	iso_level=0.0f;
	res_x=res_y=res_z=50;
	extend_percentage=0.01;
	count_in=0;
	count_out=0;
}


MCmesh::~MCmesh(void)
{
}
void MCmesh::voxelizeData ()
{
	for (int x = 0; x < res_x; ++x)
		for (int y = 0; y < res_y; ++y)
			for (int z = 0; z < res_z; ++z)
			{
				std::vector<int> nn_indices;
				std::vector<float> nn_sqr_dists;
				Eigen::Vector3f point;
				point[0] = min_p[0] + (max_p[0] - min_p[0]) * float (x) / float (res_x);
				point[1] = min_p[1] + (max_p[1] - min_p[1]) * float (y) / float (res_y);
				point[2] = min_p[2] + (max_p[2] - min_p[2]) * float (z) / float (res_z);
				pcl::PointNormal p;
				p.getVector3fMap () = point;
				tree_->nearestKSearch (p, 1, nn_indices, nn_sqr_dists);
				grid[x * res_y*res_z + y * res_z + z] = input_->points[nn_indices[0]].getNormalVector3fMap ().dot (
					point - input_->points[nn_indices[0]].getVector3fMap ());
			}
}

//************************************
// Method:    interpolate
// FullName:  mesh::MCmesh::interpolate
// Access:    private 
// Returns:   void
// Qualifier: ���Բ�ֵ�����ֵ��ͱߵĽ���
// Parameter: Eigen::Vector3f & p1 p1�������
// Parameter: Eigen::Vector3f & p2 p2�������
// Parameter: float v1			p1��ı���ֵ
// Parameter: float v2			p2��ı���ֵ
// Parameter: Eigen::Vector3f & output ��������
//************************************
void MCmesh::interpolate (Eigen::Vector3f &p1, Eigen::Vector3f &p2, float v1, float v2, Eigen::Vector3f &output)
{
	//p=p1+(isovalue-v1)(p2-p1)/(v2-v1)
	//r=(isovalue-v1)/(v2-v1)
	float r = (iso_level - v1) / (v2-v1);
	output = p1 + r * (p2 - p1);
}
void MCmesh::createSurface (std::vector<float> &node,Eigen::Vector3i &index_3d,pcl::PointCloud<pcl::PointNormal> &cloud)
{
	int cubeindex = 0;//���������8λ�����ţ����ڲ��
	Eigen::Vector3f vertex_list[12];//���12�����ϵĽ���
	//����8λ����
	if (node[0] < iso_level) cubeindex |= 1;
	if (node[1] < iso_level) cubeindex |= 2;
	if (node[2] < iso_level) cubeindex |= 4;
	if (node[3] < iso_level) cubeindex |= 8;
	if (node[4] < iso_level) cubeindex |= 16;
	if (node[5] < iso_level) cubeindex |= 32;
	if (node[6] < iso_level) cubeindex |= 64;
	if (node[7] < iso_level) cubeindex |= 128;

	// ������û�б���ֵ���и�����蹹����,�����ǳ��ߣ����90%��Ӧ�����ȹ��ˣ�
	if (edgeTable[cubeindex] == 0)
	{
		count_out++;
		return;
	}
	count_in++;
	//Eigen::Vector4f index_3df (index_3d[0], index_3d[1], index_3d[2], 0.0f);
	Eigen::Vector3f center;// TODO coeff wise product = min_p_ + Eigen::Vector4f (1.0f/res_x_, 1.0f/res_y_, 1.0f/res_z_) * index_3df * (max_p_ - min_p_);
	//�����ģ�
	//min_p_ ��Сpoint
	//max_p_ ���point
	center[0] = min_p[0] + (max_p[0] - min_p[0]) * float (index_3d[0]) / float (res_x);
	center[1] = min_p[1] + (max_p[1] - min_p[1]) * float (index_3d[1]) / float (res_y);
	center[2] = min_p[2] + (max_p[2] - min_p[2]) * float (index_3d[2]) / float (res_z);



	std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f> > p;//�������8������
	p.resize (8);
	for (int i = 0; i < 8; ++i)
	{
		Eigen::Vector3f point = center;
		if(i & 0x4)
			point[1] = static_cast<float> (center[1] + (max_p[1] - min_p[1]) / float (res_y));

		if(i & 0x2)
			point[2] = static_cast<float> (center[2] + (max_p[2] - min_p[2]) / float (res_z));

		if((i & 0x1) ^ ((i >> 1) & 0x1))
			point[0] = static_cast<float> (center[0] + (max_p[0] - min_p[0]) / float (res_x));

		p[i] = point;
	}


	// Find the vertices where the surface intersects the cube
	//��߱����õ��ıߵ������12λ���ֱ��12λ�ĸ�λ1���룬����1=000000000001�����жϵ�һλ�Ƿ���1
	//�ж���һλ��1�������1�����ʾ���и��ô�������Բ�ֵ����õ��и�㣬����vertex_list��12������12���и�㣬û�е������ 
	//node��ʲô������ֵ
	if (edgeTable[cubeindex] & 1)
		interpolate (p[0], p[1], node[0], node[1], vertex_list[0]);
	if (edgeTable[cubeindex] & 2)
		interpolate (p[1], p[2], node[1], node[2], vertex_list[1]);
	if (edgeTable[cubeindex] & 4)
		interpolate (p[2], p[3], node[2], node[3], vertex_list[2]);
	if (edgeTable[cubeindex] & 8)
		interpolate (p[3], p[0], node[3], node[0], vertex_list[3]);
	if (edgeTable[cubeindex] & 16)
		interpolate (p[4], p[5], node[4], node[5], vertex_list[4]);
	if (edgeTable[cubeindex] & 32)
		interpolate (p[5], p[6], node[5], node[6], vertex_list[5]);
	if (edgeTable[cubeindex] & 64)
		interpolate (p[6], p[7], node[6], node[7], vertex_list[6]);
	if (edgeTable[cubeindex] & 128)
		interpolate (p[7], p[4], node[7], node[4], vertex_list[7]);
	if (edgeTable[cubeindex] & 256)
		interpolate (p[0], p[4], node[0], node[4], vertex_list[8]);
	if (edgeTable[cubeindex] & 512)
		interpolate (p[1], p[5], node[1], node[5], vertex_list[9]);
	if (edgeTable[cubeindex] & 1024)
		interpolate (p[2], p[6], node[2], node[6], vertex_list[10]);
	if (edgeTable[cubeindex] & 2048)
		interpolate (p[3], p[7], node[3], node[7], vertex_list[11]);

	// Create the triangle
	//����������
	//�������α�ÿ��3������ֱ������-1ֹͣ
	//triTable[cubeindex]�鵽256���иʽ�е�һ�֣�ʵ�����Ǳߵ���ϣ�����ÿ���������У���������ǹ̶���
	//Ȼ�����ζ�ȡ�ߵ�������
	//���ݱߵ������ŴӸղ����ɵ�vertex_list��ȡ�øñ��Ͻ��������
	for (int i = 0; triTable[cubeindex][i] != -1; i+=3)
	{
		pcl::PointNormal p1,p2,p3;
		Eigen::Vector3f result;

		p1.x = vertex_list[triTable[cubeindex][i  ]][0];
		p1.y = vertex_list[triTable[cubeindex][i  ]][1];
		p1.z = vertex_list[triTable[cubeindex][i  ]][2];
		p2.x = vertex_list[triTable[cubeindex][i+1]][0];
		p2.y = vertex_list[triTable[cubeindex][i+1]][1];
		p2.z = vertex_list[triTable[cubeindex][i+1]][2];
		p3.x = vertex_list[triTable[cubeindex][i+2]][0];
		p3.y = vertex_list[triTable[cubeindex][i+2]][1];
		p3.z = vertex_list[triTable[cubeindex][i+2]][2];
		Eigen::Vector3f u(p2.x-p1.x,p2.y-p1.y,p2.z-p1.z);
		Eigen::Vector3f v(p3.x-p1.x,p3.y-p1.y,p3.z-p1.z);
		result=u.cross(v);
		result.normalize();
		p1.normal_x=result.x();
		p1.normal_y=result.y();
		p1.normal_z=result.z();
		p2.normal_x=result.x();
		p2.normal_y=result.y();
		p2.normal_z=result.z();
		p3.normal_x=result.x();
		p3.normal_y=result.y();
		p3.normal_z=result.z();
		cloud.push_back (p1);
		cloud.push_back (p2);
		cloud.push_back (p3);
	}
}
void MCmesh::getBoundingBox ()
{
	pcl::getMinMax3D(*input_, min_p, max_p);

	
	min_p -= (max_p - min_p) * extend_percentage/2;
	max_p += (max_p - min_p) * extend_percentage/2;

	Eigen::Vector4f bounding_box_size = max_p - min_p;

	bounding_box_size = max_p - min_p;
	
	//PCL_DEBUG ("[pcl::MarchingCubesHoppe::getBoundingBox] Size of Bounding Box is [%f, %f, %f]\n",
	//	bounding_box_size.x (), bounding_box_size.y (), bounding_box_size.z ());
	double max_size =(std::max) ((std::max)(bounding_box_size.x (), bounding_box_size.y ()),bounding_box_size.z ());
	(void)max_size;
	
	/*PCL_DEBUG ("[pcl::MarchingCubesHoppe::getBoundingBox] Lower left point is [%f, %f, %f]\n",
		min_p_.x (), min_p_.y (), min_p_.z ());
	PCL_DEBUG ("[pcl::MarchingCubesHoppe::getBoundingBox] Upper left point is [%f, %f, %f]\n",
		max_p_.x (), max_p_.y (), max_p_.z ());*/
}
float MCmesh::getValue (Eigen::Vector3i pos)
{
	if (pos[0] < 0 || pos[0] >= res_x)
		return -1.0f;
	if (pos[1] < 0 || pos[1] >= res_y)
		return -1.0f;
	if (pos[2] < 0 || pos[2] >= res_z)
		return -1.0f;
	//grid�����ά��������ݽṹ
	return grid[pos[0]*res_y*res_z + pos[1]*res_z + pos[2]];

}
void MCmesh::getNeighborsValue(std::vector<float> &node,Eigen::Vector3i &index3d)
{
	node = std::vector<float> (8, 0.0f);

	node[0] = getValue (index3d);
	node[1] = getValue (index3d + Eigen::Vector3i (1, 0, 0));
	node[2] = getValue (index3d + Eigen::Vector3i (1, 0, 1));
	node[3] = getValue (index3d + Eigen::Vector3i (0, 0, 1));
	node[4] = getValue (index3d + Eigen::Vector3i (0, 1, 0));
	node[5] = getValue (index3d + Eigen::Vector3i (1, 1, 0));
	node[6] = getValue (index3d + Eigen::Vector3i (1, 1, 1));
	node[7] = getValue (index3d + Eigen::Vector3i (0, 1, 1));
}
void MCmesh::performReconstruction(pcl::PolygonMesh &output)
{
	if (!(iso_level >= 0 && iso_level < 1))
	{
		
		output.cloud.width = output.cloud.height = 0;
		output.cloud.data.clear ();
		output.polygons.clear ();
		return;
	}
	// Create grid
	grid = std::vector<float> (res_x*res_y*res_z, 0.0f);//����һ�����񣬴�С�Ǹ�ά�ȷֱ����ܺ�(50*50*50),Ĭ��ֵΪ0
	// Populate tree
	//����������Ƴ�kdtree
	tree_->setInputCloud (input_);
	getBoundingBox ();
	// Transform the point cloud into a voxel grid
	// This needs to be implemented in a child class
	// �������ػ�����Ҫ��������ʵ��
	// rbf��hoppe�и��Ե�ʵ��
	voxelizeData ();

	// Run the actual marching cubes algorithm, store it into a point cloud,
	// and copy the point cloud + connectivity into output
	// ִ���㷨������浽������
	pcl::PointCloud<pcl::PointNormal> cloud;

	for (int x = 1; x < res_x-1; ++x)
		for (int y = 1; y < res_y-1; ++y)
			for (int z = 1; z < res_z-1; ++z)
			{
				Eigen::Vector3i index_3d (x, y, z);//��ά������ʵ�������ص�����
				std::vector<float> node;
				getNeighborsValue (node, index_3d);
				createSurface (node, index_3d, cloud);//�浽һ��pointcloud<pointT>������
			}
			pcl::toPCLPointCloud2 (cloud, output.cloud);//ͨ��һ����ģ��ĵ�����ת

			output.polygons.resize (cloud.size () / 3);
			for (size_t i = 0; i < output.polygons.size (); ++i)
			{
			 	pcl::Vertices v;
				v.vertices.resize (3);
				for (int j = 0; j < 3; ++j)
					v.vertices[j] = static_cast<int> (i) * 3 + j;
				output.polygons[i] = v;
			}

	cout<<"in cube:\t"<<count_in<<endl;
	cout<<"out cube:\t"<<count_out<<endl;
	cout<<"in/total:\t"<<count_in/(count_out+count_in)*100<<"%"<<endl;
	

}

