#include"socket.h"
using namespace crw::socket;

bool Socket::init(){
#ifdef _WIN32
	WSADATA wsaData;
	return WSAStartup(MAKEWORD(2,2),&wsaData) == 0;
#else
	return true;
#endif
}

Socket::Socket() : m_ip(""),m_port(0),m_sockfd((SocketFdType)0) {
	#ifdef _WIN32
	WSAData wsaData;
	WSAStartup(MAKEWORD(2,2),&wsaData);
	#endif
	m_sockfd = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (m_sockfd < 0) {
		log_error("failed to create socket: %d",GET_SOCK_ERR());
	}
}

Socket::Socket(SocketFdType sockfd) : m_ip(""), m_port(0), m_sockfd(sockfd) {

}

Socket::~Socket() {
	close();
}

bool Socket::bind(const string& ip, int port) {
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	if (inet_pton(AF_INET, ip.c_str(), &local.sin_addr) <= 0) {
		log_error("Invalid address: %d",ip);
		return false;
	}

	if (::bind(m_sockfd, (struct sockaddr*)&local, sizeof(local)) < 0){
		log_error("bind listen socket failed !!! errorcode : %d",GET_SOCK_ERR());
		return false;
	}
	m_ip = ip;
	m_port = port;
	return true;
}

bool Socket::listen(int backlog) {
	if (::listen(m_sockfd, backlog) == SOCKET_ERROR) {
		log_error("socket listen error !!! errorcode : %d",GET_SOCK_ERR());
		return false;
	}
	else {
		log_info("socket listening ...");
		return true;
	}
}

bool Socket::connect(const string& ip,int port) {
	sockaddr_in sockaddr = { 0 };
	sockaddr.sin_family = AF_INET;
	if (inet_pton(AF_INET, ip.c_str(), &sockaddr.sin_addr) <= 0) {
		log_error("Invalid addredd: %d",ip);
		return false;
	}
	if (::connect(m_sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
		log_error("connect error: error=%d",GET_SOCK_ERR());
		return false;
	}
	m_ip = ip;
	m_port = port;
	return true;
}

int Socket::accept() {
	int connfd = ::accept(m_sockfd,nullptr,nullptr);
	if (connfd < 0) {
		log_error("socket accept error: error=%d\n",GET_SOCK_ERR());
		return -1;
	}
	return connfd;
}

int Socket::send(const char * buf,int len) {
	return ::send(m_sockfd,buf,len,0);
}

int Socket::recv(char * buf,int len) {
	return ::recv(m_sockfd,buf,len,0);
}

void Socket::close() {
    if (m_sockfd != INVALID_FD) {  // 用 INVALID_FD 判断，避免平台差异（Windows 下 SOCKET 可能是 unsigned，>0 不准确）
        CLOSE_FD(m_sockfd);  // 跨平台关闭函数
        m_sockfd = INVALID_FD;  // 重置为无效值，而非 0
    }
}