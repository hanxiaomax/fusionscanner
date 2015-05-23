#pragma once

#include "cuda_runtime_api.h"

namespace kfusion
{
    namespace cuda
    {
        void error(const char *error_string, const char *file, const int line, const char *func);
    }
}
//创建宏定义函数cudaSafeCall(expr)
#if defined(__GNUC__)//GCC编译器
    #define cudaSafeCall(expr)  kfusion::cuda::_cudaSafeCall(expr, __FILE__, __LINE__, __func__)
#else /* defined(__CUDACC__) || defined(__MSVC__) *///使用CUDACC或者微软VC编译器
    #define cudaSafeCall(expr)  kfusion::cuda::_cudaSafeCall(expr, __FILE__, __LINE__)    
#endif


/*定义kfusion::cuda::__cudaSafeCall函数*/
namespace kfusion
{
    namespace cuda
    {

        static inline void _cudaSafeCall(cudaError_t err, const char *file, const int line, const char *func = "")
        {
            if (cudaSuccess != err)//如果不成功，成功的话cudaSuccess=0
                error(cudaGetErrorString(err), file, line, func);
        }        

        static inline int divUp(int total, int grain) { return (total + grain - 1) / grain; }
    }

	///////什么意思？
    namespace device
    {
        using kfusion::cuda::divUp;
    }
}
