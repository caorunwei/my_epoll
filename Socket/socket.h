// 1. 跨平台头文件包含
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
//#pragma comment(lib, "ws2_32.lib")  // Windows 链接网络库
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#endif

// 2. 跨平台类型/宏定义
#ifdef _WIN32
typedef SOCKET SocketFdType;       // Windows 套接字句柄类型
#define INVALID_FD INVALID_SOCKET  // 无效套接字值（Windows 下为 (SOCKET)(~0)）
#define CLOSE_FD(fd) closesocket(fd)  // 关闭套接字函数
#define GET_SOCK_ERR() WSAGetLastError()  // 获取错误码函数
#else
typedef int SocketFdType;          // Linux 套接字句柄类型（int）
#define INVALID_FD -1              // 无效套接字值（Linux 下为 -1）
#define CLOSE_FD(fd) close(fd)     // 关闭套接字函数
#define GET_SOCK_ERR() errno       // 获取错误码函数
#endif

#include <string>
#include "logger.h"
using std::string;

namespace crw {
namespace socket {
class Socket {
public:
    Socket();                  // 构造函数：创建新套接字
    Socket(SocketFdType sockfd);  // 构造函数：用已有的套接字初始化
    ~Socket();                 // 析构函数：关闭套接字
    bool init();               // 初始化网络环境（Windows 专用）
    bool bind(const string& ip, int port);  // 绑定 IP 和端口
    bool listen(int backlog);  // 监听连接（服务端）
    bool connect(const string& ip, int port);  // 连接服务器（客户端）
    int accept();              // 接收客户端连接（返回新套接字）
    int send(const char* buf, int len);  // 发送数据
    int recv(char* buf, int len);        // 接收数据
    void close();              // 关闭套接字

protected:
    string m_ip;               // 绑定/连接的 IP 地址
    int m_port;                // 绑定/连接的端口号
    SocketFdType m_sockfd;     // 套接字句柄（跨平台类型）
};
}  // namespace socket
}  // namespace crw