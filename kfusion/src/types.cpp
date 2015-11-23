#include <kfusion/types.hpp>

using namespace kfusion;
using namespace kfusion::convert;

void vertex_to_pclCloudNormal(vertexes &v,pcl::PointCloud<pcl::PointNormal> &p)
{
	for(int i=0;i<v.size();i++)
	{
		pcl::PointNormal point;
		point.x=v[i].x;
		point.y=v[i].y;
		point.z=v[i].z;
		p.push_back(point);
	}
}
void pclCloudNormal_to_vertex(pcl::PointCloud<pcl::PointNormal> &p,vertexes &v)
{
	for(int i=0;i<p.size();i++)
	{
		cv::Point3d vertex;
		vertex.x=p[i].x;
		vertex.y=p[i].y;
		vertex.z=p[i].z;
		v.push_back(vertex);
	}
}