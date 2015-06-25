#pragma once

#include <kfusion/types.hpp>
#include <kfusion/cuda/tsdf_volume.hpp>
#include <kfusion/cuda/projective_icp.hpp>
#include <vector>
#include <string>



/*
kfusion::KinFuParams �ṹ��
kfusion::cuda
kfusion::KinFu
*/
namespace kfusion 
{
    namespace cuda//cuda������������cuda����
    {
		KF_EXPORTS struct CUDAinfo
		{
			string device_name;
			string driver;
			float RAM;
			int core;
			string computerCap;
		};
        KF_EXPORTS int getCudaEnabledDeviceCount();//��ȡ����CUDA�豸����
		
        KF_EXPORTS void setDevice(int device);//����CUDA�豸
        KF_EXPORTS std::string getDeviceName(int device);//��ȡ�豸����
        KF_EXPORTS bool checkIfPreFermiGPU(int device);//���GUP�ܹ�
        KF_EXPORTS void printCudaDeviceInfo(int device);//��ӡCUDA�豸��Ϣ
        KF_EXPORTS void printShortCudaDeviceInfo(int device);//��ӡ��̵�GUDA�豸��Ϣ
		KF_EXPORTS CUDAinfo getShortCudaDeviceInfo(int device);//��ȡ��̵�CUDA�豸��Ϣ

		

    }

    struct KF_EXPORTS KinFuParams //������ kinfu����
    {
        static KinFuParams default_params();//����Ĭ�ϲ���
		static KinFuParams set_params(kfusion::KinFuParams& User_params);//����kinfu����
		

        int cols;  //pixels
        int rows;  //pixels
		
        Intr intr;  //Camera parameters//���Intrinsics����

        Vec3i volume_dims; //number of voxels
        Vec3f volume_size; //meters
        Affine3f volume_pose; //meters, inital pose ��ʼ����̬

        float bilateral_sigma_depth;   //meters
        float bilateral_sigma_spatial;   //pixels
        int   bilateral_kernel_size;   //pixels

        float icp_truncate_depth_dist; //meters �ض���ȣ����˳�����ֵ��������ݣ�
        float icp_dist_thres;          //meters ��ȷ�ֵ�����˵��ڴ�ֵ��������ݣ�
        float icp_angle_thres;         //radians
        std::vector<int> icp_iter_num; //iterations for level index 0,1,..,3

        float tsdf_min_camera_movement; //meters, integrate only if exceedes
        float tsdf_trunc_dist;             //meters;
        int tsdf_max_weight;               //frames tsdf���������֡Ϊ��λ��

        float raycast_step_factor;   // in voxel sizes
        float gradient_delta_factor; // in voxel sizes

        Vec3f light_pose; //meters

    };

    class KF_EXPORTS KinFu
    {
    public:        
        typedef cv::Ptr<KinFu> Ptr;//����ָ��

        KinFu(const KinFuParams& params);//���캯������������

        const KinFuParams& params() const;//��������������kinfu���������ã�const��
        KinFuParams& params();

        const cuda::TsdfVolume& tsdf() const;//��ȡtsdf����������tsdf volume�����ã�const��
        cuda::TsdfVolume& tsdf();

        const cuda::ProjectiveICP& icp() const;//��ȡicp����������icp��������
        cuda::ProjectiveICP& icp();

        void reset();//kinfu���ã������λ��
		void PrintKFparms(); 

        bool operator()(const cuda::Depth& dpeth, const cuda::Image& image = cuda::Image());//���������أ�������Ⱥ�ͼ�����ݣ�����kinfu����

        void renderImage(cuda::Image& image, int flags = 0);//��Ⱦͼ��
        void renderImage(cuda::Image& image, const Affine3f& pose, int flags = 0);

        Affine3f getCameraPose (int time = -1) const;//��ȡ�������̬
    private:
        void allocate_buffers();//���仺��

        int frame_counter_;//֡������
        KinFuParams params_;//kinfu����

        std::vector<Affine3f> poses_;//�������̬

        cuda::Dists dists_;
        cuda::Frame curr_, prev_;//��ǰ֡����һ֡

        cuda::Cloud points_;//��������
        cuda::Normals normals_;//��������
        cuda::Depth depths_;//�������

        cv::Ptr<cuda::TsdfVolume> volume_;//TSDF��ָ��
        cv::Ptr<cuda::ProjectiveICP> icp_;//���������ָ��
    };
}
