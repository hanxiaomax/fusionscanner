#pragma once
/**********************************
* ͼ����ģ��
**********************************/
#include <kfusion/types.hpp>

namespace kfusion
{
    namespace cuda
    {
		//˫���˲�
        KF_EXPORTS void depthBilateralFilter(const Depth& in, Depth& out, int ksz, float sigma_spatial, float sigma_depth);
		//������ݽض�
        KF_EXPORTS void depthTruncation(Depth& depth, float threshold);
		//������ݽ�������
        KF_EXPORTS void depthBuildPyramid(const Depth& depth, Depth& pyramid, float sigma_depth);
		//���㷨�ߺ�mask��ȣ�
        KF_EXPORTS void computeNormalsAndMaskDepth(const Intr& intr, Depth& depth, Normals& normals);
		//������ƺͷ���
        KF_EXPORTS void computePointNormals(const Intr& intr, const Depth& depth, Cloud& points, Normals& normals);
		//�������
        KF_EXPORTS void computeDists(const Depth& depth, Dists& dists, const Intr& intr);
		//������ȣ����߳ߴ�
        KF_EXPORTS void resizeDepthNormals(const Depth& depth, const Normals& normals, Depth& depth_out, Normals& normals_out);
		//�������ƣ����߳ߴ�
        KF_EXPORTS void resizePointsNormals(const Cloud& points, const Normals& normals, Cloud& points_out, Normals& normals_out);
		//�ȴ�ͬ��
        KF_EXPORTS void waitAllDefaultStream();
		//��Ⱦ��ɫ
        KF_EXPORTS void renderTangentColors(const Normals& normals, Image& image);
		//��Ⱦͼ�����
        KF_EXPORTS void renderImage(const Depth& depth, const Normals& normals, const Intr& intr, const Vec3f& light_pose, Image& image);
		//��Ⱦͼ�񣬵���
        KF_EXPORTS void renderImage(const Cloud& points, const Normals& normals, const Intr& intr, const Vec3f& light_pose, Image& image);
    }
}
