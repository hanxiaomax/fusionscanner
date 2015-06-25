#include "precomp.hpp"
#include "internal.hpp"
#include <iostream>
using namespace std;
using namespace kfusion;
using namespace kfusion::cuda;

//#define USE_DEPTH
static inline float deg2rad (float alpha) { return alpha * 0.017453293f; }//角度转弧度

/*kfusion::KinFuParams类default_params()的具体实现*/
kfusion::KinFuParams kfusion::KinFuParams::default_params()//设置默认参数
{
    const int iters[] = {10, 5, 4, 0};
    const int levels = sizeof(iters)/sizeof(iters[0]);//ICP迭代层数

    KinFuParams p;//参数结构体

	//分辨率640*480
    p.cols = 640;  //pixels
    p.rows = 480;  //pixels
    p.intr = Intr(525.f, 525.f, p.cols/2 - 0.5f, p.rows/2 - 0.5f);

    p.volume_dims = Vec3i::all(512);  //number of voxels
    p.volume_size = Vec3f::all(3.f);  //meters
    p.volume_pose = Affine3f().translate(Vec3f(-p.volume_size[0]/2, -p.volume_size[1]/2, 0.5f));

    p.bilateral_sigma_depth = 0.04f;  //meter
    p.bilateral_sigma_spatial = 4.5; //pixels
    p.bilateral_kernel_size = 7;     //pixels

	//迭代最近点ICP参数
    p.icp_truncate_depth_dist = 0.f;        //meters, disabled	截断深度（过滤超过此值的深度数据）设置为0则不过滤
    p.icp_dist_thres = 0.1f;                //meters			深度阀值（过滤低于此值的深度数据）
    p.icp_angle_thres = deg2rad(30.f); //radians				参数是角度
    p.icp_iter_num.assign(iters, iters + levels);

    p.tsdf_min_camera_movement = 0.f; //meters, disabled		//进行融合的最小摄像机位移
    p.tsdf_trunc_dist = 0.04f; //meters;
    p.tsdf_max_weight = 64;   //frames

    p.raycast_step_factor = 0.75f;  //in voxel sizes
    p.gradient_delta_factor = 0.5f; //in voxel sizes

    //p.light_pose = p.volume_pose.translation()/4; //meters
    p.light_pose = Vec3f::all(0.f); //meters

    return p;
}

kfusion::KinFuParams kfusion::KinFuParams::set_params(kfusion::KinFuParams& User_params)
{
	const int iters[] = {10, 5, 4, 0};
	const int levels = sizeof(iters)/sizeof(iters[0]);//ICP迭代层数

	KinFuParams p;//参数结构体

	//分辨率640*480
	p.cols = 640;  //pixels
	p.rows = 480;  //pixels
	p.intr = Intr(525.f, 525.f, p.cols/2 - 0.5f, p.rows/2 - 0.5f);

	p.volume_dims = Vec3i::all(512);  //number of voxels
	p.volume_size = Vec3f::all(3.f);  //meters
	p.volume_pose = Affine3f().translate(Vec3f(-p.volume_size[0]/2, -p.volume_size[1]/2, 0.5f));

	p.bilateral_sigma_depth = User_params.bilateral_sigma_depth;  //meter
	p.bilateral_sigma_spatial = User_params.bilateral_sigma_spatial; //pixels
	p.bilateral_kernel_size = User_params.bilateral_kernel_size;     //pixels

	//迭代最近点ICP参数
	p.icp_truncate_depth_dist = User_params.icp_truncate_depth_dist;        //meters, disabled //似乎过滤的是近处的数据
	p.icp_dist_thres = User_params.icp_dist_thres;                //meters
	p.icp_angle_thres = deg2rad(User_params.icp_angle_thres); //radians//参数是角度
	p.icp_iter_num.assign(iters, iters + levels);

	p.tsdf_min_camera_movement = User_params.tsdf_min_camera_movement; //meters, disabled //进行融合的最小摄像机位移
	p.tsdf_trunc_dist = User_params.tsdf_trunc_dist; //meters;
	p.tsdf_max_weight = User_params.tsdf_max_weight;   //frames

	p.raycast_step_factor = User_params.raycast_step_factor;  //in voxel sizes
	p.gradient_delta_factor = User_params.gradient_delta_factor; //in voxel sizes

	//p.light_pose = p.volume_pose.translation()/4; //meters
	p.light_pose = Vec3f::all(0.f); //meters

	return p;
}

/*KinFu类构造函数具体实现
* init：
	frame_counter_(0)
	params_(params)
*/
kfusion::KinFu::KinFu(const KinFuParams& params) : frame_counter_(0), params_(params)
{
    CV_Assert(params.volume_dims[0] % 32 == 0);

    volume_ = cv::Ptr<cuda::TsdfVolume>(new cuda::TsdfVolume(params_.volume_dims));

    volume_->setTruncDist(params_.tsdf_trunc_dist);
    volume_->setMaxWeight(params_.tsdf_max_weight);
    volume_->setSize(params_.volume_size);
    volume_->setPose(params_.volume_pose);
    volume_->setRaycastStepFactor(params_.raycast_step_factor);
    volume_->setGradientDeltaFactor(params_.gradient_delta_factor);

    icp_ = cv::Ptr<cuda::ProjectiveICP>(new cuda::ProjectiveICP());
    icp_->setDistThreshold(params_.icp_dist_thres);
    icp_->setAngleThreshold(params_.icp_angle_thres);
    icp_->setIterationsNum(params_.icp_iter_num);

    allocate_buffers();
    reset();
}

/*返回参数*/
const kfusion::KinFuParams& kfusion::KinFu::params() const
{ return params_; }

kfusion::KinFuParams& kfusion::KinFu::params()
{ return params_; }

void kfusion::KinFu::PrintKFparms()
{
	
	cout<<"----------分辨率------------------------"<<endl;
	cout<<"clos*rows :\t"<<params_.cols<<"*"<<params_.rows<<endl;

	cout<<"----------Volume------------------------"<<endl;
	cout<<"volume_dims :\t"<<params_.volume_dims<<endl;
	cout<<"volume_size :\t"<<params_.volume_size<<endl;
	
	cout<<"----------双边滤波参数------------------"<<endl;
	cout<<"双边sigma深度 :\t"<<params_.bilateral_sigma_depth<<endl;  //meter
	cout<<"双边sigma_spatial :\t"<<params_.bilateral_sigma_spatial<<endl;//pixels
	cout<<"双边核大小 :\t"<<params_.bilateral_kernel_size<<endl;  //pixels

	//迭代最近点ICP参数
	cout<<"----------ICP参数-----------------------"<<endl;
	cout<<"ICP截断深度距离 :\t"<<params_.icp_truncate_depth_dist<<endl;        //meters, disabled 
	cout<<"ICP距离阀值 :\t"<<params_.icp_dist_thres<<endl;               //meters
	cout<<"ICP角度阀值 :\t"<<params_.icp_angle_thres<<endl;//radians//参数是角度

	

	cout<<"----------TSDF参数------------------------"<<endl;
	cout<<"摄像机最小位移 :\t"<<params_.tsdf_min_camera_movement<<endl; //meters, disabled //进行融合的最小摄像机位移
	cout<<"TSDF截断距离 :\t"<<params_.tsdf_trunc_dist<<endl; //meters;
	cout<<"TSDF最大重量 :\t"<<params_.tsdf_max_weight<<endl;   //frames

	cout<<"光照步长因数 :\t"<<params_.raycast_step_factor<<endl;  //in voxel sizes
	cout<<"梯度变化因数 :\t"<<params_.gradient_delta_factor<<endl; //in voxel sizes
}
const kfusion::cuda::TsdfVolume& kfusion::KinFu::tsdf() const
{ return *volume_; }

kfusion::cuda::TsdfVolume& kfusion::KinFu::tsdf()
{ return *volume_; }


const kfusion::cuda::ProjectiveICP& kfusion::KinFu::icp() const
{ return *icp_; }

kfusion::cuda::ProjectiveICP& kfusion::KinFu::icp()
{ return *icp_; }


void kfusion::KinFu::allocate_buffers()
{
    const int LEVELS = cuda::ProjectiveICP::MAX_PYRAMID_LEVELS;

    int cols = params_.cols;
    int rows = params_.rows;

    dists_.create(rows, cols);

    curr_.depth_pyr.resize(LEVELS);
    curr_.normals_pyr.resize(LEVELS);
    prev_.depth_pyr.resize(LEVELS);
    prev_.normals_pyr.resize(LEVELS);

    curr_.points_pyr.resize(LEVELS);
    prev_.points_pyr.resize(LEVELS);

    for(int i = 0; i < LEVELS; ++i)
    {
        curr_.depth_pyr[i].create(rows, cols);
        curr_.normals_pyr[i].create(rows, cols);

        prev_.depth_pyr[i].create(rows, cols);
        prev_.normals_pyr[i].create(rows, cols);

        curr_.points_pyr[i].create(rows, cols);
        prev_.points_pyr[i].create(rows, cols);

        cols /= 2;
        rows /= 2;
    }

    depths_.create(params_.rows, params_.cols);
    normals_.create(params_.rows, params_.cols);
    points_.create(params_.rows, params_.cols);
}

/*软件复位*/
void kfusion::KinFu::reset()
{
    if (frame_counter_)
        cout << "软件复位" << endl;

    frame_counter_ = 0;//帧数归零
    poses_.clear();//姿态清零
    poses_.reserve(30000);
    poses_.push_back(Affine3f::Identity());
    volume_->clear();
}

/*获取摄像机姿态
params:
	int time
return:
	kfusion::Affine3f poses_[time](时间作为索引)
	
*/
kfusion::Affine3f kfusion::KinFu::getCameraPose (int time) const
{
    if (time > (int)poses_.size () || time < 0)
        time = (int)poses_.size () - 1;
    return poses_[time];
}

/*----------------------------------------*
 *  功能描述:   核心算法操作符
 
 ----------------------------------------*/ 
bool kfusion::KinFu::operator()(const kfusion::cuda::Depth& depth, const kfusion::cuda::Image& /*image*/)
{
	//创建参数的引用
    const KinFuParams& p = params_;
    const int LEVELS = icp_->getUsedLevelsNum();//设置ICP层级（由粗到细）

    cuda::computeDists(depth, dists_, p.intr);//cuda计算距离
    cuda::depthBilateralFilter(depth, curr_.depth_pyr[0], p.bilateral_kernel_size, p.bilateral_sigma_spatial, p.bilateral_sigma_depth);//cuda双边滤波


    if (p.icp_truncate_depth_dist > 0)//如果设置了深度截断距离，则进行截断，0为关闭此功能
        kfusion::cuda::depthTruncation(curr_.depth_pyr[0], p.icp_truncate_depth_dist);

    for (int i = 1; i < LEVELS; ++i)
        cuda::depthBuildPyramid(curr_.depth_pyr[i-1], curr_.depth_pyr[i], p.bilateral_sigma_depth);

    for (int i = 0; i < LEVELS; ++i)

#if defined USE_DEPTH
        cuda::computeNormalsAndMaskDepth(p.intr, curr_.depth_pyr[i], curr_.normals_pyr[i]);
#else
        cuda::computePointNormals(p.intr(i), curr_.depth_pyr[i], curr_.points_pyr[i], curr_.normals_pyr[i]);
#endif

    cuda::waitAllDefaultStream();

    //can't perform more on first frame
    if (frame_counter_ == 0)
    {
        volume_->integrate(dists_, poses_.back(), p.intr);
#if defined USE_DEPTH
        curr_.depth_pyr.swap(prev_.depth_pyr);
#else
        curr_.points_pyr.swap(prev_.points_pyr);
#endif
        curr_.normals_pyr.swap(prev_.normals_pyr);
        return ++frame_counter_, false;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    // ICP
    Affine3f affine; // cur -> prev//仿射变换
    {
        //ScopeTime time("icp");//该语句可以打印icp时间
		
#if defined USE_DEPTH
        bool ok = icp_->estimateTransform(affine, p.intr, curr_.depth_pyr, curr_.normals_pyr, prev_.depth_pyr, prev_.normals_pyr);
#else
        bool ok = icp_->estimateTransform(affine, p.intr, curr_.points_pyr, curr_.normals_pyr, prev_.points_pyr, prev_.normals_pyr);
#endif
        if (!ok)
            return reset(), false;
    }

    poses_.push_back(poses_.back() * affine); // curr -> global

    ///////////////////////////////////////////////////////////////////////////////////////////
    // Volume integration TSDF体合成

    // We do not integrate volume if camera does not move.
    float rnorm = (float)cv::norm(affine.rvec());
    float tnorm = (float)cv::norm(affine.translation());
    bool integrate = (rnorm + tnorm)/2 >= p.tsdf_min_camera_movement;
    if (integrate)
    {
        //ScopeTime time("tsdf");//该语句可以打印tsdf时间
        volume_->integrate(dists_, poses_.back(), p.intr);
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    // Ray casting 光线投射
    {
        //ScopeTime time("ray-cast-all");//该语句可以打印ray-cast-all时间
#if defined USE_DEPTH
        volume_->raycast(poses_.back(), p.intr, prev_.depth_pyr[0], prev_.normals_pyr[0]);
        for (int i = 1; i < LEVELS; ++i)
            resizeDepthNormals(prev_.depth_pyr[i-1], prev_.normals_pyr[i-1], prev_.depth_pyr[i], prev_.normals_pyr[i]);
#else
        volume_->raycast(poses_.back(), p.intr, prev_.points_pyr[0], prev_.normals_pyr[0]);
        for (int i = 1; i < LEVELS; ++i)
            resizePointsNormals(prev_.points_pyr[i-1], prev_.normals_pyr[i-1], prev_.points_pyr[i], prev_.normals_pyr[i]);
#endif
        cuda::waitAllDefaultStream();
    }

    return ++frame_counter_, true;
}


/*渲染图像*/
void kfusion::KinFu::renderImage(cuda::Image& image, int flag)
{
    const KinFuParams& p = params_;//params应该为同一个，这里是创建了它的引用。
    image.create(p.rows, flag != 3 ? p.cols : p.cols * 2);

#if defined USE_DEPTH
    #define PASS1 prev_.depth_pyr
#else
    #define PASS1 prev_.points_pyr
#endif

    if (flag <= 1 || flag > 3){
        cuda::renderImage(PASS1[0], prev_.normals_pyr[0], params_.intr, params_.light_pose, image);
	}
    else if (flag == 2){
        cuda::renderTangentColors(prev_.normals_pyr[0], image);
	}
    else /* if (flag == 3) */
    {
        DeviceArray2D<RGB> i1(p.rows, p.cols, image.ptr(), image.step());
        DeviceArray2D<RGB> i2(p.rows, p.cols, image.ptr() + p.cols, image.step());

        cuda::renderImage(PASS1[0], prev_.normals_pyr[0], params_.intr, params_.light_pose, i1);
        cuda::renderTangentColors(prev_.normals_pyr[0], i2);
    }
#undef PASS1
}

/*渲染图片
//iteractive_mode_模式下三参数renderImage()
*params：
	cuda::Image& image		输入图片（引用）
	const Affine3f& pose	摄像机姿态（引用）？好像不是摄像机姿态因为画面不会动
	int flag				模式：
								mode=1		渲染无色图片
								mode=2		渲染彩色图片
								mode=3		双色

*/
void kfusion::KinFu::renderImage(cuda::Image& image, const Affine3f& pose, int flag)
{
    const KinFuParams& p = params_;
    image.create(p.rows, flag != 3 ? p.cols : p.cols * 2);
    depths_.create(p.rows, p.cols);
    normals_.create(p.rows, p.cols);
    points_.create(p.rows, p.cols);


#if defined USE_DEPTH
    #define PASS1 depths_
#else
    #define PASS1 points_
#endif

    volume_->raycast(pose, p.intr, PASS1, normals_);


    if (flag <= 1 || flag > 3){
		//cout<<flag<<endl;
        cuda::renderImage(PASS1, normals_, params_.intr, params_.light_pose, image);
	}
    else if (flag == 2){
		//cout<<flag<<endl;
        cuda::renderTangentColors(normals_, image);
	}
    else /* if (flag == 3) */
    {
		//cout<<flag<<endl;
        DeviceArray2D<RGB> i1(p.rows, p.cols, image.ptr(), image.step());
        DeviceArray2D<RGB> i2(p.rows, p.cols, image.ptr() + p.cols, image.step());

        cuda::renderImage(PASS1, normals_, params_.intr, params_.light_pose, i1);
        cuda::renderTangentColors(normals_, i2);
    }
#undef PASS1
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//namespace pcl
//{
//    Eigen::Vector3f rodrigues2(const Eigen::Matrix3f& matrix)
//    {
//        Eigen::JacobiSVD<Eigen::Matrix3f> svd(matrix, Eigen::ComputeFullV | Eigen::ComputeFullU);
//        Eigen::Matrix3f R = svd.matrixU() * svd.matrixV().transpose();

//        double rx = R(2, 1) - R(1, 2);
//        double ry = R(0, 2) - R(2, 0);
//        double rz = R(1, 0) - R(0, 1);

//        double s = sqrt((rx*rx + ry*ry + rz*rz)*0.25);
//        double c = (R.trace() - 1) * 0.5;
//        c = c > 1. ? 1. : c < -1. ? -1. : c;

//        double theta = acos(c);

//        if( s < 1e-5 )
//        {
//            double t;

//            if( c > 0 )
//                rx = ry = rz = 0;
//            else
//            {
//                t = (R(0, 0) + 1)*0.5;
//                rx = sqrt( std::max(t, 0.0) );
//                t = (R(1, 1) + 1)*0.5;
//                ry = sqrt( std::max(t, 0.0) ) * (R(0, 1) < 0 ? -1.0 : 1.0);
//                t = (R(2, 2) + 1)*0.5;
//                rz = sqrt( std::max(t, 0.0) ) * (R(0, 2) < 0 ? -1.0 : 1.0);

//                if( fabs(rx) < fabs(ry) && fabs(rx) < fabs(rz) && (R(1, 2) > 0) != (ry*rz > 0) )
//                    rz = -rz;
//                theta /= sqrt(rx*rx + ry*ry + rz*rz);
//                rx *= theta;
//                ry *= theta;
//                rz *= theta;
//            }
//        }
//        else
//        {
//            double vth = 1/(2*s);
//            vth *= theta;
//            rx *= vth; ry *= vth; rz *= vth;
//        }
//        return Eigen::Vector3d(rx, ry, rz).cast<float>();
//    }
//}


