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
    typedef cv::Matx33f Mat3f;//С����<3*3 float>
    typedef cv::Vec3f Vec3f;//����Matx�Ķ�����<3 float>
    typedef cv::Vec3i Vec3i;
    typedef cv::Affine3f Affine3f;//����
	
	typedef vector<cv::Point3d> vertexes;//���ƶ���


    struct KF_EXPORTS Intr//
    {
        float fx, fy, cx, cy;

        Intr ();
        Intr (float fx, float fy, float cx, float cy);
        Intr operator()(int level_index) const;//�����Ա�ķ�ʽ���ز�����
    };

    KF_EXPORTS std::ostream& operator << (std::ostream& os, const Intr& intr);//�Էǳ�Ա�����ķ�ʽ���ز��������������Ϊos stream

	//�����ݽṹ
    struct Point
    {
        union
        {
            float data[4];
            struct { float x, y, z; };
        };
    };
	//������ʹ��ͬ��һ�������ݽṹ
    typedef Point Normal;
	//��ɫֵ���ݽṹ BGR
    struct RGB
    {
        union
        {
            struct { unsigned char b, g, r; };
            int bgra;
        };
    };

	//������ɫֵ
    struct PixelRGB
    {
        unsigned char r, g, b;
    };
	//ִ�п��ӻ����Ƶ�pcl::PointNormal���Ƶ�ת��
	namespace convert
	{
		void FromVertex(vertexes &v,pcl::PointCloud<pcl::PointNormal> &p);
		void ToVertex(pcl::PointCloud<pcl::PointNormal> &p,vertexes &v);
	}

	///////������CUDA�豸����ʹ�õ����ݽṹ
    namespace cuda
    {
        typedef cuda::DeviceMemory CudaData;
		typedef cuda::DeviceArray2D<int> tempCudaData;

        typedef cuda::DeviceArray2D<unsigned short> Depth;
        typedef cuda::DeviceArray2D<unsigned short> Dists;
        typedef cuda::DeviceArray2D<RGB> Image;
        typedef cuda::DeviceArray2D<Normal> Normals;
        typedef cuda::DeviceArray2D<Point> Cloud;

		//֡���ݽṹ
        struct Frame
        {
            bool use_points;

            std::vector<Depth> depth_pyr;
            std::vector<Cloud> points_pyr;
            std::vector<Normals> normals_pyr;
        };
    }

    inline float deg2rad (float alpha) { return alpha * 0.017453293f; }//�Ƕ�ת���Ȼ���

	/*���㲢���ĳ�δ����ʱ*/
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
	/*ȫ��֪ͨ������
	
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