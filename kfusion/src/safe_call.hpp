#pragma once

#include "cuda_runtime_api.h"

namespace kfusion
{
    namespace cuda
    {
        void error(const char *error_string, const char *file, const int line, const char *func);
    }
}
//�����궨�庯��cudaSafeCall(expr)
#if defined(__GNUC__)//GCC������
    #define cudaSafeCall(expr)  kfusion::cuda::_cudaSafeCall(expr, __FILE__, __LINE__, __func__)
#else /* defined(__CUDACC__) || defined(__MSVC__) *///ʹ��CUDACC����΢��VC������
    #define cudaSafeCall(expr)  kfusion::cuda::_cudaSafeCall(expr, __FILE__, __LINE__)    
#endif


/*����kfusion::cuda::__cudaSafeCall����*/
namespace kfusion
{
    namespace cuda
    {

        static inline void _cudaSafeCall(cudaError_t err, const char *file, const int line, const char *func = "")
        {
            if (cudaSuccess != err)//������ɹ����ɹ��Ļ�cudaSuccess=0
                error(cudaGetErrorString(err), file, line, func);
        }        

        static inline int divUp(int total, int grain) { return (total + grain - 1) / grain; }
    }

	///////ʲô��˼��
    namespace device
    {
        using kfusion::cuda::divUp;
    }
}
