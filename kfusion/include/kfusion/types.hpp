#pragma once
#ifndef TYPE_HH
#define TYPE_HH

#include <kfusion/cuda/device_array.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/core/affine.hpp>
#include <opencv2/viz/vizcore.hpp>
#include <iosfwd>
#include <string>
#include <pcl/ply_io.h>
#include <pcl/point_types.h>
#include <pcl/conversions.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/PolygonMesh.h>
using namespace std;
struct CUevent_st;

namespace kfusion
{
    typedef cv::Matx33f Mat3f;//小矩阵<3*3 float>
    typedef cv::Vec3f Vec3f;//基于Matx的短向量<3 float>
    typedef cv::Vec3i Vec3i;
    typedef cv::Affine3f Affine3f;//仿射
	
	typedef vector<cv::Point3d> vertexes;//点云顶点


    struct KF_EXPORTS Intr//
    {
        float fx, fy, cx, cy;

        Intr ();
        Intr (float fx, float fy, float cx, float cy);
        Intr operator()(int level_index) const;//以类成员的方式重载操作符
    };

    KF_EXPORTS std::ostream& operator << (std::ostream& os, const Intr& intr);//以非成员函数的方式重载操作符，左操作数为os stream

	//点数据结构
    struct Point
    {
        union
        {
            float data[4];
            struct { float x, y, z; };
        };
    };
	//法向量使用同点一样的数据结构
    typedef Point Normal;
	//颜色值数据结构 BGR
    struct RGB
    {
        union
        {
            struct { unsigned char b, g, r; };
            int bgra;
        };
    };

	//像素颜色值
    struct PixelRGB
    {
        unsigned char r, g, b;
    };
	//执行可视化点云到pcl::PointNormal点云的转换
	namespace convert
	{
		void FromVertex(vertexes &v,pcl::PointCloud<pcl::PointNormal> &p);
		void ToVertex(pcl::PointCloud<pcl::PointNormal> &p,vertexes &v);
	}

	///////用于在CUDA设备上面使用的数据结构
    namespace cuda
    {
        typedef cuda::DeviceMemory CudaData;
		typedef cuda::DeviceArray2D<int> tempCudaData;

        typedef cuda::DeviceArray2D<unsigned short> Depth;
        typedef cuda::DeviceArray2D<unsigned short> Dists;
        typedef cuda::DeviceArray2D<RGB> Image;
        typedef cuda::DeviceArray2D<Normal> Normals;
        typedef cuda::DeviceArray2D<Point> Cloud;

		//帧数据结构
        struct Frame
        {
            bool use_points;

            std::vector<Depth> depth_pyr;
            std::vector<Cloud> points_pyr;
            std::vector<Normals> normals_pyr;
        };
    }

    inline float deg2rad (float alpha) { return alpha * 0.017453293f; }//角度转弧度弧度

	/*计算并输出某段代码耗时*/
    struct KF_EXPORTS ScopeTime
    {
        const char* name;
        double start;
        ScopeTime(const char *name);
        ~ScopeTime();
    };


    struct KF_EXPORTS SampledScopeTime
    {
    public:
        enum { EACH = 33 };
        SampledScopeTime(double& time_ms);
        ~SampledScopeTime();
    private:
        double getTime();
        SampledScopeTime(const SampledScopeTime&);
        SampledScopeTime& operator=(const SampledScopeTime&);

        double& time_ms_;
        double start;
    };
	/*全局通知生成器
	
	*/
	class InfoBox
	{
		public:
			InfoBox(){};
			InfoBox(const char *_name):name(_name){};
			~InfoBox(){};
		public:
			enum{
				ERR=0,
				SUC=1,
				INFO=2
			};
		private:
			const char *name;
		public:
			void printInfo(const string info,int infotype=INFO);
	};

	
}
#endif