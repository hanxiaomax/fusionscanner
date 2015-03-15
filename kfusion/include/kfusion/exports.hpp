#pragma once//C++杂注，如编译器支持，则该头文件只会被编译一次

//判断是否是WIN平台，且输出KFUSION API
#if (defined WIN32 || defined _WIN32 || defined WINCE) && defined KFUSION_API_EXPORTS
  #define KF_EXPORTS __declspec(dllexport) //声明为导出函数
#else
  #define KF_EXPORTS //不定义内容，相当于空白
#endif
