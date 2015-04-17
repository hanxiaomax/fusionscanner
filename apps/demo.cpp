#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/viz/vizcore.hpp>
#include <kfusion/kinfu.hpp>
#include <io/capture.hpp>
#include <fstream>
#include <io/CloudIO.h>

using namespace std;
using namespace kfusion;


struct KinFuApp
{
	//键盘按键处理
    static void KeyboardCallback(const cv::viz::KeyboardEvent& event, void* pthis)
    {
        KinFuApp& kinfu = *static_cast<KinFuApp*>(pthis);

        if(event.action != cv::viz::KeyboardEvent::KEY_DOWN)
            return;

        if(event.code == 't' || event.code == 'T')
            kinfu.take_cloud(*kinfu.kinfu_);//获取点云

        if(event.code == 'i' || event.code == 'I')
            kinfu.iteractive_mode_ = !kinfu.iteractive_mode_;//交互模式开关
    }

	/*KinFuApp主函数
	*param：
		OpenNISource& source 数据源
	*init:
		exit_ (false),  iteractive_mode_(false), capture_ (source)
	*/
    KinFuApp(OpenNISource& source) : exit_ (false),  iteractive_mode_(false), capture_ (source)
    {
        KinFuParams params = KinFuParams::default_params();//设置默认参数
        kinfu_ = KinFu::Ptr( new KinFu(params) );//创建Kinfu对象

        capture_.setRegistration(true);//设置点云配准

        cv::viz::WCube cube(cv::Vec3d::all(0), cv::Vec3d(params.volume_size), true, cv::viz::Color::apricot());//坐标系？
        viz.showWidget("cube", cube, params.volume_pose);//showWideget()会创建一个窗口部件
        viz.showWidget("coor", cv::viz::WCoordinateSystem(0.1));
        viz.registerKeyboardCallback(KeyboardCallback, this);//注册键盘回调函数：KeyboardCallback
    }

	/*显示深度数据
	*param：
		const cv::Mat& depth
	*/
    void show_depth(const cv::Mat& depth)
    {
        cv::Mat display;
        //cv::normalize(depth, display, 0, 255, cv::NORM_MINMAX, CV_8U);
        depth.convertTo(display, CV_8U, 255.0/4000);
		/*cout<<depth.at<ushort>(1,2)<<endl;*/
		/*imshow是highgui提供的接口
		在Depth窗口中显示view_host_*/
        cv::imshow("Depth", display);
    }

	/*raycast*/
    void show_raycasted(KinFu& kinfu)
    {
		/*mode=1	渲染无色图片
		mode=2		渲染彩色图片
		mode=3		双色
		*/
        const int mode =3;
		/*交互模式下，渲染图片，获取观察者姿态，否则不获取，调用重载的renderImage函数*/
        if (iteractive_mode_){
			//cout<<"iteractive_mode_"<<"-->render mode:";	
            kinfu.renderImage(view_device_, viz.getViewerPose(), mode);//viz.getViewerPose()：Returns the current pose of the viewer.
		}
        else
		{	//cout<<"Not iteractive_mode_"<<"-->render mode:";
            kinfu.renderImage(view_device_, mode);
		}

        view_host_.create(view_device_.rows(), view_device_.cols(), CV_8UC4);//创建矩阵储存像素
        view_device_.download(view_host_.ptr<void>(), view_host_.step);

        cv::imshow("Scene", view_host_);//在Scene窗口中显示view_host_
    }

	/*获取点云*/
    void take_cloud(KinFu& kinfu)
    {
		/*获取点云相关*/ 
        cuda::DeviceArray<Point> cloud = kinfu.tsdf().fetchCloud(cloud_buffer);//GPU内存中的一维矩阵
        cv::Mat cloud_host(1, (int)cloud.size(), CV_32FC4);//一维矩阵，存放无序点云(1行，n列) CV_32FC4 32位浮点4通道
        cloud.download(cloud_host.ptr<Point>());
		

		/*把点云数据写入ply文件*/
		{
			ScopeTime st("ply writer");
			PLYFilewriter PLYw;
			PLYw .write("cloud_file.ply",cloud);
		}
		
		/*把点云数据写入pcd文件*/
		{
			ScopeTime st("pcd writer");
			PCDFilewriter PCDw;
			PCDw.write("cloud_file.pcd",cloud);
		}
		

		/*显示点云或有颜色的点云*/

        //viz.showWidget("cloud", cv::viz::WCloud(cloud_host));//显示点云
        viz.showWidget("cloud", cv::viz::WPaintedCloud(cloud_host));//显示有颜色的点云
		//viz.showWidget("normal",cv::viz::WCloudNormals(cloud_host,cloud_host));//显示法线（法线是否已经计算？）
    }

	/*App执行函数*/
    bool execute()
    {
        KinFu& kinfu = *kinfu_;
        cv::Mat depth, image;//存放深度数据和图像
        double time_ms = 0;
        bool has_image = false;

		/*循环处理每一帧数据*/
        for (int i = 0; !exit_ && !viz.wasStopped(); ++i)
        {
            bool has_frame = capture_.grab(depth, image);//从source获取深度和图像
            if (!has_frame)//无法取得当前帧
                return cout << "Can't grab" << endl, false;

			
            depth_device_.upload(depth.data, depth.step, depth.rows, depth.cols);
			
			{
                SampledScopeTime fps(time_ms); 
				(void)fps;
                has_image = kinfu(depth_device_)   ;//kinfu算法处理，成功返回true
				
			}

            if (has_image)
                show_raycasted(kinfu);

            show_depth(depth);//显示当前帧的深度数据
            cv::imshow("Image", image);//显示当前帧的图像

            if (!iteractive_mode_)//重置相机为当前帧视角
                viz.setViewerPose(kinfu.getCameraPose());

            int key = cv::waitKey(3);//等待按键

			//按键处理
            switch(key)
            {
            case 't': case 'T' : take_cloud(kinfu); break;
            case 'i': case 'I' : iteractive_mode_ = !iteractive_mode_; break;//切换交互模式
            case 27: case 32: exit_ = true; break;
            }

            //exit_ = exit_ || i > 100;
            viz.spinOnce(3, true);
        }
        return true;
    }

    bool exit_, iteractive_mode_;
    OpenNISource& capture_;
    KinFu::Ptr kinfu_;
    cv::viz::Viz3d viz;

    cv::Mat view_host_;
    cuda::Image view_device_;
    cuda::Depth depth_device_;
    cuda::DeviceArray<Point> cloud_buffer;//点云数据缓存
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main (int argc, char* argv[])
{
    int device = 0;
    cuda::setDevice (device);//设置GPU：0
    cuda::printShortCudaDeviceInfo (device);//打印GPU信息
	

	//检查GPU架构是否支持
    if(cuda::checkIfPreFermiGPU(device))
        return cout << endl << "Kinfu is not supported for pre-Fermi GPU architectures, and not built for them by default. Exiting..." << endl, 1;

    OpenNISource capture;//实例化一个OpenNI数据源对象

    capture.open (0);//打开默认的OpenNI设备及其配置

    KinFuApp app (capture);//初始化app，参数为某个OpenNI设备

    // executing
    try { app.execute (); }
    catch (const std::bad_alloc& /*e*/) { cout << "Bad alloc" << endl; }
    catch (const std::exception& /*e*/) { cout << "Exception" << endl; }

    return 0;
}
