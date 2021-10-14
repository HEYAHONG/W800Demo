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

    extern void * cpp_malloc(size_t nsize);
    extern void cpp_free(void *p);
    extern void cpp_abort();

}


static  __unused const char * TAG="cpp";

#if 0

//重载operator new
void* operator new(size_t nsize)
{
    void *p=cpp_malloc(nsize);

#if CONFIG_CPP_OP_NEW_DEBUG == 1
    printf("%s:operator new addr=%08X,length=%u\n\r",TAG,(unsigned int )p,nsize);
#endif // CONFIG_CPP_OP_NEW_DEBUG

    return p;
}




//重载operator delete
void operator delete(void* pointee)
{
#if CONFIG_CPP_OP_DELETE_DEBUG == 1
    printf("%s:operator delete addr=%08X\n\r",TAG,(unsigned int)pointee);
#endif // CONFIG_CPP_OP_DELETE_DEBUG
    cpp_free(pointee);
}
#endif

#if 0
namespace std
{
// Helper for exception objects in <except>
void __throw_bad_exception(void)
{
    printf("%s: %s\n\r",TAG,__FUNCTION__);

#if CONFIG_CPP_RESET_ON_EXCEPTION == 1
    cpp_abort();
#endif // CONFIG_CPP_RESET_ON_EXCEPTION

}

// Helper for exception objects in <new>
void __throw_bad_alloc(void)
{
    printf("%s: %s\n\r",TAG,__FUNCTION__);

#if CONFIG_CPP_RESET_ON_EXCEPTION == 1
    cpp_abort();
#endif // CONFIG_CPP_RESET_ON_EXCEPTION

}

// Helper for exception objects in <typeinfo>
void __throw_bad_cast(void)
{
    printf("%s: %s\n\r",TAG,__FUNCTION__);

#if CONFIG_CPP_RESET_ON_EXCEPTION == 1
    cpp_abort();
#endif // CONFIG_CPP_RESET_ON_EXCEPTION
}

void __throw_bad_typeid(void)
{
    printf("%s: %s\n\r",TAG,__FUNCTION__);

#if CONFIG_CPP_RESET_ON_EXCEPTION == 1
    cpp_abort();
#endif // CONFIG_CPP_RESET_ON_EXCEPTION
}

// Helpers for exception objects in <stdexcept>
void __throw_logic_error(const char*)
{
    printf("%s: %s\n\r",TAG,__FUNCTION__);

#if CONFIG_CPP_RESET_ON_EXCEPTION == 1
    cpp_abort();
#endif // CONFIG_CPP_RESET_ON_EXCEPTION
}

void __throw_domain_error(const char*)
{
    printf("%s: %s\n\r",TAG,__FUNCTION__);

#if CONFIG_CPP_RESET_ON_EXCEPTION == 1
    cpp_abort();
#endif // CONFIG_CPP_RESET_ON_EXCEPTION
}

void __throw_invalid_argument(const char*)
{
    printf("%s: %s\n\r",TAG,__FUNCTION__);

#if CONFIG_CPP_RESET_ON_EXCEPTION == 1
    cpp_abort();
#endif // CONFIG_CPP_RESET_ON_EXCEPTION
}

void __throw_length_error(const char*)
{
    printf("%s: %s\n\r",TAG,__FUNCTION__);

#if CONFIG_CPP_RESET_ON_EXCEPTION == 1
    cpp_abort();
#endif // CONFIG_CPP_RESET_ON_EXCEPTION
}

void __throw_out_of_range(const char*)
{
    printf("%s: %s\n\r",TAG,__FUNCTION__);

#if CONFIG_CPP_RESET_ON_EXCEPTION == 1
    cpp_abort();
#endif // CONFIG_CPP_RESET_ON_EXCEPTION
}

void __throw_out_of_range_fmt(const char*, ...)
{
    printf("%s: %s\n\r",TAG,__FUNCTION__);

#if CONFIG_CPP_RESET_ON_EXCEPTION == 1
    cpp_abort();
#endif // CONFIG_CPP_RESET_ON_EXCEPTION
}

void __throw_runtime_error(const char*)
{
    printf("%s: %s\n\r",TAG,__FUNCTION__);

#if CONFIG_CPP_RESET_ON_EXCEPTION == 1
    cpp_abort();
#endif // CONFIG_CPP_RESET_ON_EXCEPTION
}

void __throw_range_error(const char*)
{
    printf("%s: %s\n\r",TAG,__FUNCTION__);

#if CONFIG_CPP_RESET_ON_EXCEPTION == 1
    cpp_abort();
#endif // CONFIG_CPP_RESET_ON_EXCEPTION
}

void __throw_overflow_error(const char*)
{
    printf("%s: %s\n\r",TAG,__FUNCTION__);

#if CONFIG_CPP_RESET_ON_EXCEPTION == 1
    cpp_abort();
#endif // CONFIG_CPP_RESET_ON_EXCEPTION
}

void __throw_underflow_error(const char*)
{
    printf("%s: %s\n\r",TAG,__FUNCTION__);

#if CONFIG_CPP_RESET_ON_EXCEPTION == 1
    cpp_abort();
#endif // CONFIG_CPP_RESET_ON_EXCEPTION
}

// Helpers for exception objects in <ios>
void __throw_ios_failure(const char*)
{
    printf("%s: %s\n\r",TAG,__FUNCTION__);

#if CONFIG_CPP_RESET_ON_EXCEPTION == 1
    cpp_abort();
#endif // CONFIG_CPP_RESET_ON_EXCEPTION
}

void __throw_system_error(int)
{
    printf("%s: %s\n\r",TAG,__FUNCTION__);

#if CONFIG_CPP_RESET_ON_EXCEPTION == 1
    cpp_abort();
#endif // CONFIG_CPP_RESET_ON_EXCEPTION
}

void __throw_future_error(int)
{
    printf("%s: %s\n\r",TAG,__FUNCTION__);

#if CONFIG_CPP_RESET_ON_EXCEPTION == 1
    cpp_abort();
#endif // CONFIG_CPP_RESET_ON_EXCEPTION
}

// Helpers for exception objects in <functional>
void __throw_bad_function_call()
{
    printf("%s: %s\n\r",TAG,__FUNCTION__);

#if CONFIG_CPP_RESET_ON_EXCEPTION == 1
    cpp_abort();
#endif // CONFIG_CPP_RESET_ON_EXCEPTION
} 

}
#endif
