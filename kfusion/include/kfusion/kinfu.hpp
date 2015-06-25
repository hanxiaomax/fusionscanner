#pragma once

#include <kfusion/types.hpp>
#include <kfusion/cuda/tsdf_volume.hpp>
#include <kfusion/cuda/projective_icp.hpp>
#include <vector>
#include <string>



/*
kfusion::KinFuParams 结构体
kfusion::cuda
kfusion::KinFu
*/
namespace kfusion 
{
    namespace cuda//cuda函数，区别于cuda类型
    {
		KF_EXPORTS struct CUDAinfo
		{
			string device_name;
			string driver;
			float RAM;
			int core;
			string computerCap;
		};
        KF_EXPORTS int getCudaEnabledDeviceCount();//获取可用CUDA设备数量
		
        KF_EXPORTS void setDevice(int device);//设置CUDA设备
        KF_EXPORTS std::string getDeviceName(int device);//获取设备名称
        KF_EXPORTS bool checkIfPreFermiGPU(int device);//检查GUP架构
        KF_EXPORTS void printCudaDeviceInfo(int device);//打印CUDA设备信息
        KF_EXPORTS void printShortCudaDeviceInfo(int device);//打印简短的GUDA设备信息
		KF_EXPORTS CUDAinfo getShortCudaDeviceInfo(int device);//获取简短的CUDA设备信息

		

    }

    struct KF_EXPORTS KinFuParams //导出类 kinfu参数
    {
        static KinFuParams default_params();//设置默认参数
		static KinFuParams set_params(kfusion::KinFuParams& User_params);//设置kinfu参数
		

        int cols;  //pixels
        int rows;  //pixels
		
        Intr intr;  //Camera parameters//相机Intrinsics参数

        Vec3i volume_dims; //number of voxels
        Vec3f volume_size; //meters
        Affine3f volume_pose; //meters, inital pose 初始化姿态

        float bilateral_sigma_depth;   //meters
        float bilateral_sigma_spatial;   //pixels
        int   bilateral_kernel_size;   //pixels

        float icp_truncate_depth_dist; //meters 截断深度（过滤超过此值的深度数据）
        float icp_dist_thres;          //meters 深度阀值（过滤低于此值的深度数据）
        float icp_angle_thres;         //radians
        std::vector<int> icp_iter_num; //iterations for level index 0,1,..,3

        float tsdf_min_camera_movement; //meters, integrate only if exceedes
        float tsdf_trunc_dist;             //meters;
        int tsdf_max_weight;               //frames tsdf最大重量（帧为单位）

        float raycast_step_factor;   // in voxel sizes
        float gradient_delta_factor; // in voxel sizes

        Vec3f light_pose; //meters

    };

    class KF_EXPORTS KinFu
    {
    public:        
        typedef cv::Ptr<KinFu> Ptr;//智能指针

        KinFu(const KinFuParams& params);//构造函数（单参数）

        const KinFuParams& params() const;//参数函数，返回kinfu参数的引用（const）
        KinFuParams& params();

        const cuda::TsdfVolume& tsdf() const;//获取tsdf函数，返回tsdf volume的引用（const）
        cuda::TsdfVolume& tsdf();

        const cuda::ProjectiveICP& icp() const;//获取icp函数，返回icp对象引用
        cuda::ProjectiveICP& icp();

        void reset();//kinfu重置（软件复位）
		void PrintKFparms(); 

        bool operator()(const cuda::Depth& dpeth, const cuda::Image& image = cuda::Image());//操作符重载，给定深度和图像数据，进行kinfu操作

        void renderImage(cuda::Image& image, int flags = 0);//渲染图像
        void renderImage(cuda::Image& image, const Affine3f& pose, int flags = 0);

        Affine3f getCameraPose (int time = -1) const;//获取摄像机姿态
    private:
        void allocate_buffers();//分配缓存

        int frame_counter_;//帧计数器
        KinFuParams params_;//kinfu参数

        std::vector<Affine3f> poses_;//摄像机姿态

        cuda::Dists dists_;
        cuda::Frame curr_, prev_;//当前帧和上一帧

        cuda::Cloud points_;//点云数据
        cuda::Normals normals_;//法线数据
        cuda::Depth depths_;//深度数据

        cv::Ptr<cuda::TsdfVolume> volume_;//TSDF体指针
        cv::Ptr<cuda::ProjectiveICP> icp_;//迭代最近点指针
    };
}
