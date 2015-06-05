#pragma warning (disable :4996)
#undef _CRT_SECURE_NO_DEPRECATE
#include "XnCppWrapper.h"
#include <io/capture.hpp>
#include <iostream>

using namespace std;
using namespace xn;

//const std::string XMLConfig =
//"<OpenNI>"
//        "<Licenses>"
//        "<License vendor=\"PrimeSense\" key=\"0KOIk2JeIBYClPWVnMoRKn5cdY4=\"/>"
//        "</Licenses>"
//        "<Log writeToConsole=\"false\" writeToFile=\"false\">"
//                "<LogLevel value=\"3\"/>"
//                "<Masks>"
//                        "<Mask name=\"ALL\" on=\"true\"/>"
//                "</Masks>"
//                "<Dumps>"
//                "</Dumps>"
//        "</Log>"
//        "<ProductionNodes>"
//                "<Node type=\"Image\" name=\"Image1\">"
//                        "<Configuration>"
//                                "<MapOutputMode xRes=\"640\" yRes=\"480\" FPS=\"30\"/>"
//                                "<Mirror on=\"false\"/>"
//                        "</Configuration>"
//                "</Node> "
//                "<Node type=\"Depth\" name=\"Depth1\">"
//                        "<Configuration>"
//                                "<MapOutputMode xRes=\"640\" yRes=\"480\" FPS=\"30\"/>"
//                                "<Mirror on=\"false\"/>"
//                        "</Configuration>"
//                "</Node>"
//        "</ProductionNodes>"
//"</OpenNI>";

#define REPORT_ERROR(msg) kfusion::cuda::error ((msg), __FILE__, __LINE__)


/*OpenNI设备的一些节点和元数据*/
struct kfusion::OpenNISource::Impl
{
    Context context;//设备上下文
    ScriptNode scriptNode;//脚本节点
    DepthGenerator depth;//深度生成器节点
    ImageGenerator image;//图像生成器节点
    ProductionNode node;//生产节点
    DepthMetaData depthMD;//深度元数据
    ImageMetaData imageMD;//图像元数据
    XnChar strError[1024];

    bool has_depth;
    bool has_image;
};

//demo使用的初始化方法
kfusion::OpenNISource::OpenNISource() : depth_focal_length_VGA (0.f), baseline (0.f),
    shadow_value (0), no_sample_value (0), pixelSize (0.0), max_depth (0) ,_beginRange(100),_endRange(2000){}

//利用默认参数初始化设备
kfusion::OpenNISource::OpenNISource(int device) :depth_focal_length_VGA (0.f), baseline (0.f),
	shadow_value (0), no_sample_value (0), pixelSize (0.0), max_depth (0) ,_beginRange(100),_endRange(2000){open (device); }

//利用自定义参数初始化设备
kfusion::OpenNISource::OpenNISource(int device,kinectParams &p):depth_focal_length_VGA (0.f), baseline (0.f),
	shadow_value (0), no_sample_value (0), pixelSize (0.0), max_depth (0) ,_beginRange(p.beginRange),_endRange(p.endRange){open(device);}

kfusion::OpenNISource::OpenNISource(const string& filename) {open (filename); }

kfusion::OpenNISource::~OpenNISource() { release ();}

void kfusion::OpenNISource::open (int device)
{
    impl_ = cv::Ptr<Impl>( new Impl () );

    XnMapOutputMode mode;
    mode.nXRes = XN_VGA_X_RES;
    mode.nYRes = XN_VGA_Y_RES;
    mode.nFPS = 30;

	//场景分析器
	xn::SceneAnalyzer xn_scene;


    XnStatus _status;
    _status = impl_->context.Init ();
    if (_status != XN_STATUS_OK)
    {
        sprintf (impl_->strError, "Init failed: %s\n", xnGetStatusString (_status));
        REPORT_ERROR (impl_->strError);
    }

    xn::NodeInfoList devicesList;
    _status = impl_->context.EnumerateProductionTrees ( XN_NODE_TYPE_DEVICE, NULL, devicesList, 0 );
    if (_status != XN_STATUS_OK)
    {
        sprintf (impl_->strError, "Init failed: %s\n", xnGetStatusString (_status));
        REPORT_ERROR (impl_->strError);
    }

    xn::NodeInfoList::Iterator it = devicesList.Begin ();
    for (int i = 0; i < device; ++i)
        it++;

    NodeInfo node = *it;
    _status = impl_->context.CreateProductionTree ( node, impl_->node );
    if (_status != XN_STATUS_OK)
    {
        sprintf (impl_->strError, "Init failed: %s\n", xnGetStatusString (_status));
        REPORT_ERROR (impl_->strError);
    }

    XnLicense license;
    const char* vendor = "PrimeSense";
    const char* key = "0KOIk2JeIBYClPWVnMoRKn5cdY4=";
    sprintf (license.strKey, key);
    sprintf (license.strVendor, vendor);

    _status = impl_->context.AddLicense (license);
    if (_status != XN_STATUS_OK)
    {
        sprintf (impl_->strError, "licence failed: %s\n", xnGetStatusString (_status));
        REPORT_ERROR (impl_->strError);
    }

    _status = impl_->depth.Create (impl_->context);
    if (_status != XN_STATUS_OK)
    {
        sprintf (impl_->strError, "Depth generator  failed: %s\n", xnGetStatusString (_status));
        REPORT_ERROR (impl_->strError);
    }
    //_status = impl_->depth.SetIntProperty("HoleFilter", 1);
    _status = impl_->depth.SetMapOutputMode (mode);
    impl_->has_depth = true;

    _status = impl_->image.Create (impl_->context);
    if (_status != XN_STATUS_OK)
    {
        printf ("Image generator creation failed: %s\n", xnGetStatusString (_status));
        impl_->has_image = false;
    }
    else
    {
        impl_->has_image = true;
        _status = impl_->image.SetMapOutputMode (mode);
    }
	/*场景分析器节点*/
	_status = xn_scene.Create(impl_->context);
	if (_status != XN_STATUS_OK)
	{
		std::cout << "Failed to create scene analyzer: " << xnGetStatusString(
			_status) << endl;
	}


	XnPlane3D floorCoords;
	XnPoint3D floorPoint;

	xnGetFloor(xn_scene, &floorCoords);

	floorPoint = floorCoords.ptPoint;

	cout << floorCoords.vNormal.X << " " << floorCoords.vNormal.Y << " " << floorCoords.vNormal.Z << endl;
	cout << floorCoords.ptPoint.X << " " << floorCoords.ptPoint.Y << " " << floorCoords.ptPoint.Z  << "\n" << endl;

	//////////////////////////////////////

    getParams ();
	cout<<"已连接"<<endl;
    _status = impl_->context.StartGeneratingAll ();
    if (_status != XN_STATUS_OK)
    {
        sprintf (impl_->strError, "Start failed: %s\n", xnGetStatusString (_status));
        REPORT_ERROR (impl_->strError);
    }

}

void kfusion::OpenNISource::open(const std::string& filename)
{
    impl_ = cv::Ptr<Impl> ( new Impl () );

    XnStatus _status;

    _status = impl_->context.Init ();
    if (_status != XN_STATUS_OK)
    {
        sprintf (impl_->strError, "Init failed: %s\n", xnGetStatusString (_status));
        REPORT_ERROR (impl_->strError);
    }

    _status = impl_->context.OpenFileRecording (filename.c_str (), impl_->node);
    if (_status != XN_STATUS_OK)
    {
        sprintf (impl_->strError, "Open failed: %s\n", xnGetStatusString (_status));
        REPORT_ERROR (impl_->strError);
    }

    _status = impl_->context.FindExistingNode (XN_NODE_TYPE_DEPTH, impl_->depth);
    impl_->has_depth = (_status == XN_STATUS_OK);

    _status = impl_->context.FindExistingNode (XN_NODE_TYPE_IMAGE, impl_->image);
    impl_->has_image = (_status == XN_STATUS_OK);

    if (!impl_->has_depth)
        REPORT_ERROR ("No depth nodes. Check your configuration");

    if (impl_->has_depth)
        impl_->depth.GetMetaData (impl_->depthMD);

    if (impl_->has_image)
        impl_->image.GetMetaData (impl_->imageMD);

    // RGB is the only image format supported.
    if (impl_->imageMD.PixelFormat () != XN_PIXEL_FORMAT_RGB24)
        REPORT_ERROR ("Image format must be RGB24\n");

    getParams ();
}

void kfusion::OpenNISource::release ()
{
    if (impl_)
    {
        impl_->context.StopGeneratingAll ();
        impl_->context.Release ();
    }

    impl_.release();;
    depth_focal_length_VGA = 0;
    baseline = 0.f;
    shadow_value = 0;
    no_sample_value = 0;
    pixelSize = 0.0;
	cout<<"设备关闭"<<endl; 
}

/*设置深度数据采集的阀值*/
void kfusion::OpenNISource::filter(cv::Mat &depth,int xRES,int yRES,int threshold_A,int threshold_B){
	for (size_t ix=0;ix<xRES;ix++)
	{
		for (size_t iy=0;iy<yRES;iy++)
		{
			if (depth.at<ushort>(iy,ix)>threshold_B || depth.at<ushort>(iy,ix)<threshold_A)
			{
				depth.at<ushort>(iy,ix)=0;
			}
		}
	}
	return;
}

/*抓取一帧数据
* depth：CV_16U 单通道
* image：CV_8UC3 三通道
*/
bool kfusion::OpenNISource::grab(cv::Mat& depth, cv::Mat& image)
{
    XnStatus _status = XN_STATUS_OK;

    _status = impl_->context.WaitAndUpdateAll ();
    if (_status != XN_STATUS_OK)
        return printf ("Read failed: %s\n", xnGetStatusString (_status)), false;
	 
	/*获取深度数据,只能得到z方向的数据*/
    if (impl_->has_depth)
    {
        impl_->depth.GetMetaData (impl_->depthMD);//GetMetaData(DepthMetaData &metaData)
		/*Data返回深度矩阵首元素地址，行主序，16-bit。16位数据的高3位可能还没有被使用，可以留作他用*/
        const XnDepthPixel* pDepth = impl_->depthMD.Data ();
        int x = impl_->depthMD.FullXRes ();//640：cols
        int y = impl_->depthMD.FullYRes ();//480：rows
        cv::Mat(y, x, CV_16U, (void*)pDepth).copyTo(depth);//注意y在x之前，行主序
		

		//cout<<_beginRange<<" "<<_endRange<<endl;
   		//filter(depth,x,y,_beginRange,_endRange);//保留0~1200范围内的点
		filter(depth,x,y,0,1800);//保留0~1200范围内的点
    }
    else
    {
        depth.release();
        printf ("no depth\n");
    }
	/*获取图像数据*/
    if (impl_->has_image)
    {
        impl_->image.GetMetaData (impl_->imageMD);
        const XnRGB24Pixel* pImage = impl_->imageMD.RGB24Data ();
        int x = impl_->imageMD.FullXRes ();
        int y = impl_->imageMD.FullYRes ();
        image.create(y, x, CV_8UC3);

        cv::Vec3b *dptr = image.ptr<cv::Vec3b>();
        for(size_t i = 0; i < image.total(); ++i)
            dptr[i] = cv::Vec3b(pImage[i].nBlue, pImage[i].nGreen, pImage[i].nRed);
    }
    else
    {
        image.release();
        printf ("no image\n");
    }

    return impl_->has_image || impl_->has_depth;
}


/*所有的Property在下面的链接可以找到
*https://github.com/hanxiaomax/SensorKinect/blob/unstable/Include/XnStreamParams.h
TODO：搞清楚这个函数是做什么的
*/
void kfusion::OpenNISource::getParams ()
{
    XnStatus _status = XN_STATUS_OK;

    max_depth = impl_->depth.GetDeviceMaxDepth ();

	/*ZPPS-->pixel size at zero plane
	*获取像素尺寸，存放在pixelSize中
	*/
    _status = impl_->depth.GetRealProperty ( "ZPPS", pixelSize );  // in mm
    if (_status != XN_STATUS_OK)
    {
        sprintf (impl_->strError, "ZPPS failed: %s\n", xnGetStatusString (_status));
        REPORT_ERROR (impl_->strError);
    }

    XnUInt64 depth_focal_length_SXGA_mm;   //in mm
	/*ZPD-->zero plane distance
	*获取焦距？
	*/
    _status = impl_->depth.GetIntProperty ("ZPD", depth_focal_length_SXGA_mm);
    if (_status != XN_STATUS_OK)
    {
        sprintf (impl_->strError, "ZPD failed: %s\n", xnGetStatusString (_status));
        REPORT_ERROR (impl_->strError);
    }
	/**/
    XnDouble baseline_local;

    _status = impl_->depth.GetRealProperty ("LDDIS", baseline_local);
    if (_status != XN_STATUS_OK)
    {
        sprintf (impl_->strError, "ZPD failed: %s\n", xnGetStatusString (_status));
        REPORT_ERROR (impl_->strError);
    }
	/**/
    XnUInt64 shadow_value_local;

    _status = impl_->depth.GetIntProperty ("ShadowValue", shadow_value_local);
    if (_status != XN_STATUS_OK)
    {
        sprintf (impl_->strError, "ShadowValue failed: %s\n", xnGetStatusString (_status));
        REPORT_ERROR (impl_->strError);
    }
    shadow_value = (int)shadow_value_local;
	/**/
    XnUInt64 no_sample_value_local;
    _status = impl_->depth.GetIntProperty ("NoSampleValue", no_sample_value_local);
    if (_status != XN_STATUS_OK)
    {
        sprintf (impl_->strError, "NoSampleValue failed: %s\n", xnGetStatusString (_status));
        REPORT_ERROR (impl_->strError);
    }
    no_sample_value = (int)no_sample_value_local;


	/*单位转换*/
    // baseline from cm -> mm
    baseline = (float)(baseline_local * 10);

    //focal length from mm -> pixels (valid for 1280x1024)
    float depth_focal_length_SXGA = static_cast<float>(depth_focal_length_SXGA_mm / pixelSize);
    depth_focal_length_VGA = depth_focal_length_SXGA / 2;


	/*so the depthmap gives back the Z-value for each pixel in mm
	(millimeters). Thus if you want to get the full 3D position (X,Y,Z) of a
	pixel (u,v), then use following formula:

	XnUInt64 F_;
	XnDouble pixel_size_;

	// get the focal length in mm (ZPS = zero plane distance)
	depth_.GetIntProperty ("ZPD", F_)

	// get the pixel size in mm ("ZPPS" = pixel size at zero plane)
	depth_.GetRealProperty ("ZPPS", pixel_size_)

	X = (u - 320) * depth_md_[k] * pixel_size_ * 0.001 / F_;
	Y = (v - 240) * depth_md_[k] * pixel_size_ * 0.001 / F_;
	Z = depth_md_[k] * 0.001; // from mm in meters!
	*/
}


/*
TODO：搞清楚这个函数是做什么的
*/
bool kfusion::OpenNISource::setRegistration (bool value)
{
    XnStatus _status = XN_STATUS_OK;

    if (value)
    {
        if (!impl_->has_image)
            return false;

        if (impl_->depth.GetAlternativeViewPointCap ().IsViewPointAs (impl_->image) )
            return true;

        if (!impl_->depth.GetAlternativeViewPointCap ().IsViewPointSupported (impl_->image) )
        {
            printf ("SetRegistration failed: Unsupported viewpoint.\n");
            return false;
        }

        _status = impl_->depth.GetAlternativeViewPointCap ().SetViewPoint (impl_->image);
        if (_status != XN_STATUS_OK)
            printf ("SetRegistration failed: %s\n", xnGetStatusString (_status));

    }
    else   // "off"
    {
        _status = impl_->depth.GetAlternativeViewPointCap ().ResetViewPoint ();
        if (_status != XN_STATUS_OK)
            printf ("SetRegistration failed: %s\n", xnGetStatusString (_status));
    }

    getParams ();
    return _status == XN_STATUS_OK;
}
