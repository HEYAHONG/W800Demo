#include "wm_include.h"
#include "stdbool.h"
#include "appconfig.h"

void * cpp_malloc(size_t nsize)
{
    return tls_mem_alloc(nsize);
}
void cpp_free(void *p)
{
    return tls_mem_free(p);
}


void cpp_abort()
{
    //复位
    NVIC_SystemReset();
}
