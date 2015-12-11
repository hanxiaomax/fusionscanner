#pragma once

#include <kfusion/types.hpp>

namespace kfusion
{
    namespace cuda
    {
		/*截断符号距离函数*/
        class KF_EXPORTS TsdfVolume
        {
        public:
            TsdfVolume(const cv::Vec3i& dims);
            virtual ~TsdfVolume(); 

            void create(const Vec3i& dims);

			///////Getter//////////////////////////////////////
            Vec3i getDims() const;
            Vec3f getVoxelSize() const;

            const CudaData data() const;
            CudaData data();

			///////Getter & Setter//////////////////////////////////////
            Vec3f getSize() const;
            void setSize(const Vec3f& size);

            float getTruncDist() const;//获取截断距离
            void setTruncDist(float distance);//设置截断距离

            int getMaxWeight() const;//获取最大重量 //权重
            void setMaxWeight(int weight);//获取最大重量

            Affine3f getPose() const;//获取姿态
            void setPose(const Affine3f& pose);//设置姿态

            float getRaycastStepFactor() const;//获取raycast步长因子
            void setRaycastStepFactor(float factor);

            float getGradientDeltaFactor() const;//获取梯度
            void setGradientDeltaFactor(float factor);

            Vec3i getGridOrigin() const;
            void setGridOrigin(const Vec3i& origin);
			///////////////////////////////////////////////////////////////////


            virtual void clear();
            virtual void applyAffine(const Affine3f& affine);
            virtual void integrate(const Dists& dists, const Affine3f& camera_pose, const Intr& intr);//融合
            virtual void raycast(const Affine3f& camera_pose, const Intr& intr, Depth& depth, Normals& normals);//执行raycast
            virtual void raycast(const Affine3f& camera_pose, const Intr& intr, Cloud& points, Normals& normals);

            void swap(CudaData& data);

            DeviceArray<Point> fetchCloud(DeviceArray<Point>& cloud_buffer) const;//获取点云
            DeviceArray<Point> fetchNormals(const DeviceArray<Point>& cloud, DeviceArray<Normal>& normals) const;//获取法线


			//half是什么东西？
            struct Entry
            {
                typedef unsigned short half;

                half tsdf;
                unsigned short weight;

				//这两个函数均没有具体实现
                static float half2float(half value);
                static half float2half(float value);
            };
        private:
			void printTSDFparams();//输出全部当前参数
            CudaData data_;//TSDF存放在GPU中数据

            float trunc_dist_;//截断距离
            int max_weight_;//最大weight
            Vec3i dims_;//体素的维数[512,512,512]
            Vec3f size_;//volume的尺寸（米）,[3,3,3]
            Affine3f pose_;


            float gradient_delta_factor_;//梯度变化因素
            float raycast_step_factor_;//光照步长
        };
    }
}
