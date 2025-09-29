#include<stdio.h>
#include<thread>
#include"Socket/socket.h"


#include<iostream>
using namespace crw::socket;
int main() {

	Socket server = Socket();
	server.bind("127.0.0.1",8080);
	server.listen(1024);
	while (true) {
		int connfd = server.accept();
		if (connfd < 0) {
			return 1;
		}
		Socket client(connfd);
		char rbuf[1024] = { 0 };
		
		size_t len = client.recv(rbuf,sizeof(rbuf));
		client.send("Hellow World!",100);
		std::cout << "recv: " << rbuf << std::endl;
	}
	server.close();
	return 0;
}