#pragma once//C++��ע���������֧�֣����ͷ�ļ�ֻ�ᱻ����һ��

//�ж��Ƿ���WINƽ̨�������KFUSION API
#if (defined WIN32 || defined _WIN32 || defined WINCE) && defined KFUSION_API_EXPORTS
  #define KF_EXPORTS __declspec(dllexport) //����Ϊ��������
#else
  #define KF_EXPORTS //���������ݣ��൱�ڿհ�
#endif
