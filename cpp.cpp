/*
此文件对C++的某些函数进行重载。
或者添加一些全局支持。
C++全局变量的构造及析构需小心使用(尽量不用)
*/

extern "C"
{

#include "appconfig.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "wm_include.h"

    extern void * cpp_malloc(size_t nsize);
    extern void cpp_free(void *p);
    extern void cpp_abort();

}


static  __unused const char * TAG="cpp";



//重载operator new
void* operator new(size_t nsize)
{
    void *p=cpp_malloc(nsize);

#if CONFIG_CPP_OP_NEW_DEBUG == 1
    wm_printf("%s:operator new addr=%08X,length=%u\n\r",TAG,(unsigned int )p,nsize);
#endif // CONFIG_CPP_OP_NEW_DEBUG

    return p;
}




//重载operator delete
void operator delete(void* pointee)
{
#if CONFIG_CPP_OP_DELETE_DEBUG == 1
    wm_printf("%s:operator delete addr=%08X\n\r",TAG,(unsigned int)pointee);
#endif // CONFIG_CPP_OP_DELETE_DEBUG
    cpp_free(pointee);
}


