#include "precomp.hpp"
#include <iostream>
using namespace kfusion;
using namespace kfusion::cuda;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// TsdfVolume::Entry

float kfusion::cuda::TsdfVolume::Entry::half2float(half)
{ throw "Not implemented"; }

kfusion::cuda::TsdfVolume::Entry::half kfusion::cuda::TsdfVolume::Entry::float2half(float value)
{ throw "Not implemented"; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// TsdfVolume


/*截断距离函数体元素对象构造函数
*只会初始化一次
*/
kfusion::cuda::TsdfVolume::TsdfVolume(const Vec3i& dims) 
	:	data_(), //CUDA data
		trunc_dist_(0.03f), //截断距离
		max_weight_(64), //最大权重////////////////////////////////////////////////////////////////////////////////////////////////
		dims_(dims),//各轴的体素数量
		size_(Vec3f::all(3.f)),//大小（Vec3f类型，初值为[3,3,3]） 
		pose_(Affine3f::Identity()), 
		gradient_delta_factor_(0.75f), 
		raycast_step_factor_(0.75f)
{ 
	create(dims_);
	printTSDFparams();
}


void kfusion::cuda::TsdfVolume::printTSDFparams()
{
	std::cout <<"size:"<<size_<<std::endl;
	std::cout <<"截断距离:"<<trunc_dist_<<std::endl;
	std::cout <<"max_weight_:"<<max_weight_<<std::endl;
 	std::cout <<"dims_:"<<dims_<<std::endl;
 	std::cout <<"梯度delta因子:"<<gradient_delta_factor_<<std::endl;
 	std::cout <<"光照步长因子:"<<raycast_step_factor_<<std::endl;

}

kfusion::cuda::TsdfVolume::~TsdfVolume() {}


/*--------------------------------------------------* 
*	功能描述:	创建TSDF
*	参数：		三个轴方向的体素维数（个数）
--------------------------------------------------*/ 
void kfusion::cuda::TsdfVolume::create(const Vec3i& dims)
{
    dims_ = dims;
    int voxels_number = dims_[0] * dims_[1] * dims_[2];//计算TSDF中体素的个数
    data_.create(voxels_number * sizeof(int));//创建CUDA数据需要的空间
    setTruncDist(trunc_dist_);//设置截断距离
    clear();//volume对象
}

/*--------------------------------------------------* 
*	功能描述:	获取各轴维数
*	返回值：	各轴维数
--------------------------------------------------*/ 
Vec3i kfusion::cuda::TsdfVolume::getDims() const
{ return dims_; }


/*--------------------------------------------------* 
*	功能描述:	获取体素的大小（各轴尺寸/各轴的维数）
*	返回值：	float向量，表示每个轴上体素的大小
--------------------------------------------------*/  
Vec3f kfusion::cuda::TsdfVolume::getVoxelSize() const//const防止函数调用改变数据
{
    return Vec3f(size_[0]/dims_[0], size_[1]/dims_[1], size_[2]/dims_[2]);
	
}

const CudaData kfusion::cuda::TsdfVolume::data() const { return data_; }
CudaData kfusion::cuda::TsdfVolume::data() {  return data_; }


//const DeviceArray2D<int> kfusion::cuda::TsdfVolume::getvolume() const { return volume_;}

Vec3f kfusion::cuda::TsdfVolume::getSize() const { return size_; }
void kfusion::cuda::TsdfVolume::setSize(const Vec3f& size)
{ size_ = size; setTruncDist(trunc_dist_); }

//获取截断距离
//PCL是动态设置的，此处我们固定为0.03
float kfusion::cuda::TsdfVolume::getTruncDist() const { return trunc_dist_; }
//设置截断距离
void kfusion::cuda::TsdfVolume::setTruncDist(float distance)
{
    Vec3f vsz = getVoxelSize();
    float max_coeff = std::max<float>(std::max<float>(vsz[0], vsz[1]), vsz[2]);
    trunc_dist_ = std::max (distance, 2.1f * max_coeff);
}

int kfusion::cuda::TsdfVolume::getMaxWeight() const { return max_weight_; }
void kfusion::cuda::TsdfVolume::setMaxWeight(int weight) { max_weight_ = weight; }
Affine3f kfusion::cuda::TsdfVolume::getPose() const  { return pose_; }
void kfusion::cuda::TsdfVolume::setPose(const Affine3f& pose) { pose_ = pose; }
float kfusion::cuda::TsdfVolume::getRaycastStepFactor() const { return raycast_step_factor_; }
void kfusion::cuda::TsdfVolume::setRaycastStepFactor(float factor) { raycast_step_factor_ = factor; }
float kfusion::cuda::TsdfVolume::getGradientDeltaFactor() const { return gradient_delta_factor_; }
void kfusion::cuda::TsdfVolume::setGradientDeltaFactor(float factor) { gradient_delta_factor_ = factor; }
void kfusion::cuda::TsdfVolume::swap(CudaData& data) { data_.swap(data); }
void kfusion::cuda::TsdfVolume::applyAffine(const Affine3f& affine) { pose_ = affine * pose_; }


/*--------------------------------------------------* 
*	功能描述:	TSDF volume体初始化
--------------------------------------------------*/  
void kfusion::cuda::TsdfVolume::clear()
{ 
    device::Vec3i dims = device_cast<device::Vec3i>(dims_);//类型转换
    device::Vec3f vsz  = device_cast<device::Vec3f>(getVoxelSize());//类型转换
    device::TsdfVolume volume(data_.ptr<ushort2>(), dims, vsz, trunc_dist_, max_weight_);//device命名空间下的TsdfVolume对象
    device::clear_volume(volume);//初始化
}

//合成
void kfusion::cuda::TsdfVolume::integrate(const Dists& dists, const Affine3f& camera_pose, const Intr& intr)
{
    Affine3f vol2cam = camera_pose.inv() * pose_;

    device::Projector proj(intr.fx, intr.fy, intr.cx, intr.cy);

    device::Vec3i dims = device_cast<device::Vec3i>(dims_);
    device::Vec3f vsz  = device_cast<device::Vec3f>(getVoxelSize());
    device::Aff3f aff = device_cast<device::Aff3f>(vol2cam);

    device::TsdfVolume volume(data_.ptr<ushort2>(), dims, vsz, trunc_dist_, max_weight_);
    device::integrate(dists, volume, aff, proj);
}
//光照，深度数据（会崩溃）
void kfusion::cuda::TsdfVolume::raycast(const Affine3f& camera_pose, const Intr& intr, Depth& depth, Normals& normals)
{
    DeviceArray2D<device::Normal>& n = (DeviceArray2D<device::Normal>&)normals;

    Affine3f cam2vol = pose_.inv() * camera_pose;

    device::Aff3f aff = device_cast<device::Aff3f>(cam2vol);
    device::Mat3f Rinv = device_cast<device::Mat3f>(cam2vol.rotation().inv(cv::DECOMP_SVD));

    device::Reprojector reproj(intr.fx, intr.fy, intr.cx, intr.cy);

    device::Vec3i dims = device_cast<device::Vec3i>(dims_);
    device::Vec3f vsz  = device_cast<device::Vec3f>(getVoxelSize());

    device::TsdfVolume volume(data_.ptr<ushort2>(), dims, vsz, trunc_dist_, max_weight_);
    device::raycast(volume, aff, Rinv, reproj, depth, n, raycast_step_factor_, gradient_delta_factor_);

}
//光照，点云数据
void kfusion::cuda::TsdfVolume::raycast(const Affine3f& camera_pose, const Intr& intr, Cloud& points, Normals& normals)
{
    device::Normals& n = (device::Normals&)normals;
    device::Points& p = (device::Points&)points;

    Affine3f cam2vol = pose_.inv() * camera_pose;

    device::Aff3f aff = device_cast<device::Aff3f>(cam2vol);
    device::Mat3f Rinv = device_cast<device::Mat3f>(cam2vol.rotation().inv(cv::DECOMP_SVD));

    device::Reprojector reproj(intr.fx, intr.fy, intr.cx, intr.cy);

    device::Vec3i dims = device_cast<device::Vec3i>(dims_);
    device::Vec3f vsz  = device_cast<device::Vec3f>(getVoxelSize());

    device::TsdfVolume volume(data_.ptr<ushort2>(), dims, vsz, trunc_dist_, max_weight_);
    device::raycast(volume, aff, Rinv, reproj, p, n, raycast_step_factor_, gradient_delta_factor_);
}

//获取点云，返回的是一维点类型数组
DeviceArray<Point> kfusion::cuda::TsdfVolume::fetchCloud(DeviceArray<Point>& cloud_buffer) const
{
    enum { DEFAULT_CLOUD_BUFFER_SIZE = 10 * 1000 * 1000 };//使用枚举类型代替define

	//判断缓冲是否为空
    if (cloud_buffer.empty ())
        cloud_buffer.create (DEFAULT_CLOUD_BUFFER_SIZE);//分配空间

	//device::Point 为float4 （x,y,z,w）
    DeviceArray<device::Point>& b = (DeviceArray<device::Point>&)cloud_buffer;

    device::Vec3i dims = device_cast<device::Vec3i>(dims_);
    device::Vec3f vsz  = device_cast<device::Vec3f>(getVoxelSize());
    device::Aff3f aff  = device_cast<device::Aff3f>(pose_);

    device::TsdfVolume volume((ushort2*)data_.ptr<ushort2>(), dims, vsz, trunc_dist_, max_weight_);
    size_t size = extractCloud(volume, aff, b);//从gpu获取点云数据,返回大小

    return DeviceArray<Point>((Point*)cloud_buffer.ptr(), size);//参数为指向internal buffer的指针
}



/*获取法线*/
DeviceArray<Point> kfusion::cuda::TsdfVolume::fetchNormals(const DeviceArray<Point>& cloud, DeviceArray<Normal>& normals) const
{
    normals.create(cloud.size());
    DeviceArray<device::Point>& c = (DeviceArray<device::Point>&)cloud;//强制转换一下矩阵的格式

    device::Vec3i dims = device_cast<device::Vec3i>(dims_);
    device::Vec3f vsz  = device_cast<device::Vec3f>(getVoxelSize());
    device::Aff3f aff  = device_cast<device::Aff3f>(pose_);
    device::Mat3f Rinv = device_cast<device::Mat3f>(pose_.rotation().inv(cv::DECOMP_SVD));

    device::TsdfVolume volume((ushort2*)data_.ptr<ushort2>(), dims, vsz, trunc_dist_, max_weight_);
	//extractNormals (const TsdfVolume& volume, const PtrSz<Point>& points, const Aff3f& aff, const Mat3f& Rinv, float gradient_delta_factor, float4* output)
    device::extractNormals(volume, c, aff, Rinv, gradient_delta_factor_, (float4*)normals.ptr());

	return DeviceArray<Normal>((Point*)normals.ptr(), cloud.size());//参数为指向internal buffer的指针
}
