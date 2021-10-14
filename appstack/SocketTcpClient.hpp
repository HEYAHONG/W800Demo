#ifndef SOCKETTCPCLIENT_H
#define SOCKETTCPCLIENT_H

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
#include "stdbool.h"
#include "wm_include.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdint.h"
#include "string.h"

typedef struct __sockettcpclient_cfg_t
{
    //套接字任务栈大小
    uint32_t task_stack_size;//小于2048按2048
    //套接字任务优先级
    uint32_t task_priority;//为0时自动分配
    //连接前回调函数
    void (*before_connect)(const struct __sockettcpclient_cfg_t * cfg,int socket_fd);
    //连接成功后回调函数
    void (*after_connect)(const struct __sockettcpclient_cfg_t *cfg,int socketfd);
    //成功连接后循环内回调函数(只能进行发送与接收操作),不可长时间阻塞
    bool (*onloop)(const struct __sockettcpclient_cfg_t *cfg,int socketfd);//返回false重启socket
    //关闭前回调
    void (*before_close)(const struct __sockettcpclient_cfg_t *cfg,int socketfd);
    //用户使用变量(appsocket中不使用)
    void * userptr;

} sockettcpclient_cfg_t;

#ifdef __cplusplus
}
#endif // __cplusplus

#ifdef __cplusplus


class SocketTcpClient
{
public:
    SocketTcpClient();
    virtual ~SocketTcpClient();
    SocketTcpClient(const SocketTcpClient& other);

    SocketTcpClient & operator = (const SocketTcpClient& other);

    void setconfig(sockettcpclient_cfg_t _cfg);

    bool start();//以已有的参数启动
    bool start(const char * hostname,uint16_t port);//启动

    bool is_running();//是否正在运行

    void stop();//停止

protected:
    void __start_task();

    static void __task_entry(void *arg);

    bool __is_task_running();

    void __stop_task();

private:
    struct
    {
        sockettcpclient_cfg_t cfg;
        tls_os_task_t taskhandle;
        void *taskstack;
        struct
        {
            uint32_t is_pending_stop:1;//是否准备停止
            uint32_t is_waiting_delete:1;//受否等待栓除
        } task_flag;
    } context;

    char * hostname;
    uint16_t    port;

    void socket_loop();

};

#endif // __cplusplus

#endif // SOCKETTCPCLIENT_H
