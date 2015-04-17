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
	//���̰�������
    static void KeyboardCallback(const cv::viz::KeyboardEvent& event, void* pthis)
    {
        KinFuApp& kinfu = *static_cast<KinFuApp*>(pthis);

        if(event.action != cv::viz::KeyboardEvent::KEY_DOWN)
            return;

        if(event.code == 't' || event.code == 'T')
            kinfu.take_cloud(*kinfu.kinfu_);//��ȡ����

        if(event.code == 'i' || event.code == 'I')
            kinfu.iteractive_mode_ = !kinfu.iteractive_mode_;//����ģʽ����
    }

	/*KinFuApp������
	*param��
		OpenNISource& source ����Դ
	*init:
		exit_ (false),  iteractive_mode_(false), capture_ (source)
	*/
    KinFuApp(OpenNISource& source) : exit_ (false),  iteractive_mode_(false), capture_ (source)
    {
        KinFuParams params = KinFuParams::default_params();//����Ĭ�ϲ���
        kinfu_ = KinFu::Ptr( new KinFu(params) );//����Kinfu����

        capture_.setRegistration(true);//���õ�����׼

        cv::viz::WCube cube(cv::Vec3d::all(0), cv::Vec3d(params.volume_size), true, cv::viz::Color::apricot());//����ϵ��
        viz.showWidget("cube", cube, params.volume_pose);//showWideget()�ᴴ��һ�����ڲ���
        viz.showWidget("coor", cv::viz::WCoordinateSystem(0.1));
        viz.registerKeyboardCallback(KeyboardCallback, this);//ע����̻ص�������KeyboardCallback
    }

	/*��ʾ�������
	*param��
		const cv::Mat& depth
	*/
    void show_depth(const cv::Mat& depth)
    {
        cv::Mat display;
        //cv::normalize(depth, display, 0, 255, cv::NORM_MINMAX, CV_8U);
        depth.convertTo(display, CV_8U, 255.0/4000);
		/*cout<<depth.at<ushort>(1,2)<<endl;*/
		/*imshow��highgui�ṩ�Ľӿ�
		��Depth��������ʾview_host_*/
        cv::imshow("Depth", display);
    }

	/*raycast*/
    void show_raycasted(KinFu& kinfu)
    {
		/*mode=1	��Ⱦ��ɫͼƬ
		mode=2		��Ⱦ��ɫͼƬ
		mode=3		˫ɫ
		*/
        const int mode =3;
		/*����ģʽ�£���ȾͼƬ����ȡ�۲�����̬�����򲻻�ȡ���������ص�renderImage����*/
        if (iteractive_mode_){
			//cout<<"iteractive_mode_"<<"-->render mode:";	
            kinfu.renderImage(view_device_, viz.getViewerPose(), mode);//viz.getViewerPose()��Returns the current pose of the viewer.
		}
        else
		{	//cout<<"Not iteractive_mode_"<<"-->render mode:";
            kinfu.renderImage(view_device_, mode);
		}

        view_host_.create(view_device_.rows(), view_device_.cols(), CV_8UC4);//�������󴢴�����
        view_device_.download(view_host_.ptr<void>(), view_host_.step);

        cv::imshow("Scene", view_host_);//��Scene��������ʾview_host_
    }

	/*��ȡ����*/
    void take_cloud(KinFu& kinfu)
    {
		/*��ȡ�������*/ 
        cuda::DeviceArray<Point> cloud = kinfu.tsdf().fetchCloud(cloud_buffer);//GPU�ڴ��е�һά����
        cv::Mat cloud_host(1, (int)cloud.size(), CV_32FC4);//һά���󣬴���������(1�У�n��) CV_32FC4 32λ����4ͨ��
        cloud.download(cloud_host.ptr<Point>());
		

		/*�ѵ�������д��ply�ļ�*/
		{
			ScopeTime st("ply writer");
			PLYFilewriter PLYw;
			PLYw .write("cloud_file.ply",cloud);
		}
		
		/*�ѵ�������д��pcd�ļ�*/
		{
			ScopeTime st("pcd writer");
			PCDFilewriter PCDw;
			PCDw.write("cloud_file.pcd",cloud);
		}
		

		/*��ʾ���ƻ�����ɫ�ĵ���*/

        //viz.showWidget("cloud", cv::viz::WCloud(cloud_host));//��ʾ����
        viz.showWidget("cloud", cv::viz::WPaintedCloud(cloud_host));//��ʾ����ɫ�ĵ���
		//viz.showWidget("normal",cv::viz::WCloudNormals(cloud_host,cloud_host));//��ʾ���ߣ������Ƿ��Ѿ����㣿��
    }

	/*Appִ�к���*/
    bool execute()
    {
        KinFu& kinfu = *kinfu_;
        cv::Mat depth, image;//���������ݺ�ͼ��
        double time_ms = 0;
        bool has_image = false;

		/*ѭ������ÿһ֡����*/
        for (int i = 0; !exit_ && !viz.wasStopped(); ++i)
        {
            bool has_frame = capture_.grab(depth, image);//��source��ȡ��Ⱥ�ͼ��
            if (!has_frame)//�޷�ȡ�õ�ǰ֡
                return cout << "Can't grab" << endl, false;

			
            depth_device_.upload(depth.data, depth.step, depth.rows, depth.cols);
			
			{
                SampledScopeTime fps(time_ms); 
				(void)fps;
                has_image = kinfu(depth_device_)   ;//kinfu�㷨�����ɹ�����true
				
			}

            if (has_image)
                show_raycasted(kinfu);

            show_depth(depth);//��ʾ��ǰ֡���������
            cv::imshow("Image", image);//��ʾ��ǰ֡��ͼ��

            if (!iteractive_mode_)//�������Ϊ��ǰ֡�ӽ�
                viz.setViewerPose(kinfu.getCameraPose());

            int key = cv::waitKey(3);//�ȴ�����

			//��������
            switch(key)
            {
            case 't': case 'T' : take_cloud(kinfu); break;
            case 'i': case 'I' : iteractive_mode_ = !iteractive_mode_; break;//�л�����ģʽ
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
    cuda::DeviceArray<Point> cloud_buffer;//�������ݻ���
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main (int argc, char* argv[])
{
    int device = 0;
    cuda::setDevice (device);//����GPU��0
    cuda::printShortCudaDeviceInfo (device);//��ӡGPU��Ϣ
	

	//���GPU�ܹ��Ƿ�֧��
    if(cuda::checkIfPreFermiGPU(device))
        return cout << endl << "Kinfu is not supported for pre-Fermi GPU architectures, and not built for them by default. Exiting..." << endl, 1;

    OpenNISource capture;//ʵ����һ��OpenNI����Դ����

    capture.open (0);//��Ĭ�ϵ�OpenNI�豸��������

    KinFuApp app (capture);//��ʼ��app������Ϊĳ��OpenNI�豸

    // executing
    try { app.execute (); }
    catch (const std::bad_alloc& /*e*/) { cout << "Bad alloc" << endl; }
    catch (const std::exception& /*e*/) { cout << "Exception" << endl; }

    return 0;
}
