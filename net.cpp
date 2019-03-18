#include "net.h"
#include<vector>
#include<sstream>
#include <functional>
#include <iostream>
#include <errno.h>
#ifdef Linux_System
Net::Net():closed(0),ready(0){}

Net::~Net(){
	close(sock);
}

int Net::makeconnect(std::string ip){
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock==-1){
		std::cout<<"socket error:"<<errno<<std::endl;
		return -1;
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(45451);
	host = gethostbyname(ip.c_str());
	if(host == NULL)	return -1;
	server.sin_addr.s_addr = *(unsigned int *)host->h_addr_list[0];
	return connect(sock, (struct sockaddr *)&server, sizeof(server));
}
#else
Net::Net():closed(0), ready(0){
	WSADATA wsaData;
	WSAStartup(2, &wsaData);
}

Net::~Net(){
	closesocket(sock);
	WSACleanup();
}

int Net::makeconnect(std::string ip){
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock==-1){
		std::cout<<"socket error:"<<errno<<std::endl;
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(45451);	send(host, req.c_str(), req.length() + 1, 0);
	send(guest, req.c_str(), req.length() + 1, 0);
	host = gethostbyname(ip.c_str());
	if(host == NULL)	return -1;
	server.sin_addr.S_un.S_addr = *(unsigned int *)host->h_addr_list[0];
	if(connect(sock, (struct sockaddr *)&server, sizeof(server))==-1){
		std::cout<<"connect error:"<<errno<<std::endl;
		return -1;
	}
	return 0;
}
#endif

void Net::closing(){
	std::string request = "CLOSED";
	if(send(sock, request.c_str(), request.size() + 1, 0)==-1)std::cout<<"send error:"<<errno<<std::endl;
	closed = 1;
}

std::tuple<int, int> Net::login(long long room){
	std::string request = "LOGIN " + std::to_string(room);
	char data[32] = {0};
	std::string reply;
	int result, length = request.length()+1;
	result = send(sock, request.c_str(), request.size() + 1, 0);
	if(result==-1){
		std::cout<<"send error:"<<errno<<std::endl;
		return std::make_tuple<int, int>(-1, -1);
	}
	
	if(length > result)
		return std::make_tuple<int, int>(-1, -1);
	if(recv(sock, data, 32, 0)==-1)std::cout<<"recv error:"<<errno<<std::endl;
	reply += data;

	std::stringstream stream(reply);
	std::string temp;
	std::vector<std::string> replys;
	while(std::getline(stream, temp, ' ')){
		if(!temp.empty()){
			replys.push_back(temp);
		}
	}
	if(!replys[0].compare("SUCCESS")){
		return std::make_tuple<int, int>(std::stoi(replys[1]), std::stoi(replys[2]));
	}
	closed = 1;
	return std::make_tuple<int, int>(-1, -1);
}

std::tuple<int, int> Net::login(long long room, std::string pass){
	std::string request = "LOGIN " + std::to_string(room) + " PASSWORD " + pass;
	char data[32] = {0};
	std::string reply;
	int result, length = request.length()+1;
	result = send(sock, request.c_str(), request.size() + 1, 0);
	if(result==-1){
		std::cout<<"send error:"<<errno<<std::endl;
		return std::make_tuple<int, int>(-1, -1);
	}
	
	if(length > result)
		return std::make_tuple<int, int>(-1, -1);
	if(recv(sock, data, 32, 0)==-1)std::cout<<"recv error:"<<errno<<std::endl;
	reply += data;
	std::stringstream stream(reply);
	std::string temp;
	std::vector<std::string> replys;
	while(std::getline(stream, temp, ' ')){
		if(!temp.empty()){
			replys.push_back(temp);
		}
	}
	if(!replys[0].compare("SUCCESS")){
		return std::make_tuple<int, int>(std::stoi(replys[1]), std::stoi(replys[2]));
	}
	closed = 1;
	return std::make_tuple<int, int>(-1, -1);
}

long long Net::makeroom(int x, int y){
	std::string request = "ROOM " + std::to_string(x) + " " + std::to_string(y);
	char data[32] = {0};
	std::string reply;
	int result, length = request.length()+1;
	result = send(sock, request.c_str(), request.size() + 1, 0);
	if(length > result){
		if(result==-1)std::cout<<"send error:"<<errno<<std::endl;
		return -1;
	}
	if(recv(sock, data, 32, 0)==-1)std::cout<<"recv error:"<<errno<<std::endl;
	reply.assign(data);
	std::stringstream stream(reply);
	std::string temp;
	std::vector<std::string> replys;
	while(std::getline(stream, temp, ' ')){
		if(!temp.empty()){
			replys.push_back(temp);
		}
	}
	if(!replys[0].compare("SUCCESS")){
		return std::stoll(replys[1]);
	}
	closed = 1;
	return -1;
}

int Net::setpassword(std::string pass){
	std::string request = "SETPASSWORD " + pass;
	char data[32] = {0};
	std::string reply;
	int result, length = request.length();
	result = send(sock, request.c_str(), request.size() + 1, 0);
	
	if(length > result){
		if(result==-1)std::cout<<"send error:"<<errno<<std::endl;
		return -1;
	}
	if(recv(sock, data, 32, 0)==-1)std::cout<<"recv error:"<<errno<<std::endl;
	reply += data;
	if(!reply.compare("SUCCESS"))return 0;
	closed = 1;
	return -1;
}

int Net::put(int x, int y){
	char data[32] = {0};
	std::string reply;
	std::string request = "PUT " + std::to_string(x) + " " + std::to_string(y);
	int result, length = request.length();
	result = send(sock, request.c_str(), request.size() + 1, 0);
	
	if(length > result){
		if(result==-1)std::cout<<"send error:"<<errno<<std::endl;
		return -1;
	}
		if(recv(sock, data, 32, 0)==-1)std::cout<<"recv error:"<<errno<<std::endl;
	reply += data;
	if(!reply.compare("SUCCESS"))return 0;
	closed = 1;
	return -1;
}

int Net::freeput(int x, int y){
	char data[32] = {0};
	std::string reply;
	std::string request = "FREEPUT " + std::to_string(x) + " " + std::to_string(y);
	int result, length = request.length();
	result = send(sock, request.c_str(), request.size() + 1, 0);
	
	if(length > result){
		if(result==-1)std::cout<<"send error:"<<errno<<std::endl;
		closed=1;
		return -1;
	}
		if(recv(sock, data, 32, 0)==-1)std::cout<<"recv error:"<<errno<<std::endl;
	reply += data;
	if(!reply.compare("SUCCESS"))return 0;
	closed = 1;
	return -1;
}

std::tuple<std::string, int, int> Net::get(){
	char data[32];
	memset(data, 0, sizeof(data));
	std::string ret;
	int n = recv(sock, data, 32, 0);
	if(n < 1){
		if(n==-1)std::cout<<"recv error:"<<errno<<std::endl;
		return std::make_tuple("nodata", -1, -1);
	}
	ret.assign(data);
	std::vector<std::string> parsed;
	std::stringstream stream{ret};
	std::string buf;
	while(std::getline(stream, buf, ' ')){
		parsed.push_back(buf);
	}
	if(parsed.size() == 3)
		return std::make_tuple(parsed[0], std::stoi(parsed[1]), std::stoi(parsed[2]));
	else
		return std::make_tuple(parsed[0], -1, -1);
}

