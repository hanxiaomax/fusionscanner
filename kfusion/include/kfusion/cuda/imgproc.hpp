#pragma once
/**********************************
* 图像处理模块
**********************************/
#include <kfusion/types.hpp>

namespace kfusion
{
    namespace cuda
    {
		//双边滤波
        KF_EXPORTS void depthBilateralFilter(const Depth& in, Depth& out, int ksz, float sigma_spatial, float sigma_depth);
		//深度数据截断
        KF_EXPORTS void depthTruncation(Depth& depth, float threshold);
		//深度数据金字塔？
        KF_EXPORTS void depthBuildPyramid(const Depth& depth, Depth& pyramid, float sigma_depth);
		//计算法线和mask深度？
        KF_EXPORTS void computeNormalsAndMaskDepth(const Intr& intr, Depth& depth, Normals& normals);
		//计算点云和法线
        KF_EXPORTS void computePointNormals(const Intr& intr, const Depth& depth, Cloud& points, Normals& normals);
		//计算距离
        KF_EXPORTS void computeDists(const Depth& depth, Dists& dists, const Intr& intr);
		//调整深度，法线尺寸
        KF_EXPORTS void resizeDepthNormals(const Depth& depth, const Normals& normals, Depth& depth_out, Normals& normals_out);
		//调整点云，法线尺寸
        KF_EXPORTS void resizePointsNormals(const Cloud& points, const Normals& normals, Cloud& points_out, Normals& normals_out);
		//等待同步
        KF_EXPORTS void waitAllDefaultStream();
		//渲染颜色
        KF_EXPORTS void renderTangentColors(const Normals& normals, Image& image);
		//渲染图像，深度
        KF_EXPORTS void renderImage(const Depth& depth, const Normals& normals, const Intr& intr, const Vec3f& light_pose, Image& image);
		//渲染图像，点云
        KF_EXPORTS void renderImage(const Cloud& points, const Normals& normals, const Intr& intr, const Vec3f& light_pose, Image& image);
    }
}
