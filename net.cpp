#include "net.h"
#include<vector>
#include<sstream>
#include <functional>
#ifdef Linux_System
Net::Net():closed(0){}

Net::~Net(){
	close(sock);
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
#endif
int Net::makeconnect(std::string ip){
	sock = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_port = htons(12345);
	host = gethostbyname(ip.c_str());
	if(host == NULL)	return -1;
	server.sin_addr.S_un.S_addr = *(unsigned int *)host->h_addr_list[0];
	connect(sock, (struct sockaddr *)&server, sizeof(server));
	return 0;
}

std::tuple<int, int> Net::login(int room){
	std::string request = "LOGIN " + std::to_string(room);
	char data;
	std::string reply;
	int result, length = request.length();
	result = send(sock, request.c_str(), request.length(), 0);
	if(length > result)
		return std::make_tuple<int, int>(-1, -1);
	while(recv(sock, &data, 1, 0)){
		reply += data;
	}
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

std::tuple<int, int> Net::login(int room, std::string pass){
	std::string request = "LOGIN " + std::to_string(room) + "\r\nPASSWORD" + pass;
	char data;
	std::string reply;
	int result, length = request.length();
	result = send(sock, request.c_str(), request.length(), 0);
	if(length > result)
		return std::make_tuple<int, int>(-1, -1);
	while(recv(sock, &data, 1, 0)){
		reply += data;
	}
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

int Net::makeroom(){
	std::string request = "ROOM";
	char data;
	std::string reply;
	int result, length = request.length();
	result = send(sock, request.c_str(), request.length(), 0);
	if(length > result)
		return -1;
	while(recv(sock, &data, 1, 0)){
		reply += data;
	}
	std::stringstream stream(reply);
	std::string temp;
	std::vector<std::string> replys;
	while(std::getline(stream, temp, ' ')){
		if(!temp.empty()){
			replys.push_back(temp);
		}
	}
	if(!replys[0].compare("SUCCESS")){
		return std::stoi(replys[1]);
	}
	closed = 1;
	return -1;
}

int Net::setpassword(std::string pass){
	std::string request = "SETPASSWORD" + pass;
	char data;
	std::string reply;
	int result, length = request.length();
	result = send(sock, request.c_str(), request.length(), 0);
	if(length > result)
		return -1;
	while(recv(sock, &data, 1, 0)){
		reply += data;
	}
	if(!reply.compare("SUCCESS"))return 0;
	closed = 1;
	return -1;
}

int Net::setboardsize(int x, int y){
	std::string request = "SETBOARD" + std::to_string(x) + std::to_string(y);
	char data;
	std::string reply;
	int result, length = request.length();
	result = send(sock, request.c_str(), request.length(), 0);
	if(length > result)
		return -1;
	while(recv(sock, &data, 1, 0)){
		reply += data;
	}
	if(!reply.compare("SUCCESS"))return 0;
	closed = 1;
	return -1;
}

int Net::put(int x, int y){
	std::string request = "PUT " + std::to_string(x) + " " + std::to_string(y);
	int result, length = request.length();
	result = send(sock, request.c_str(), request.length(), 0);
	if(length > result)
		return -1;
	return 0;
}

int Net::freeput(int x, int y){
	std::string request = "FREEPUT " + std::to_string(x) + " " + std::to_string(y);
	int result, length = request.length();
	result = send(sock, request.c_str(), request.length(), 0);
	if(length > result){
		closed = 1;
		return -1;
	}
	return 0;
}

#ifdef Linux_System
std::tuple<const char*, int, int> Net::get(){
	char data;
	std::string ret;
	int n = 0;
	u_long val = 1;
	ioctl(sock, FIONBIO, &val);
	n = recv(sock, &data, 1, 0);
	if(n < 1){
		if(WSAGetLastError() == WSAEWOULDBLOCK){
			val = 0;
			ioctl(sock, FIONBIO, &val);
			return std::make_tuple("nodata", -1, -1);
		} else{
			val = 0;
			ioctl(sock, FIONBIO, &val);
			closed = 1;
			return std::make_tuple("nodata", -1, -1);
		}
	} else{
		ret = data;
		while(recv(sock, &data, 1, 0) > 0){
			ret += data;
		}
		std::vector<std::string> parsed;
		std::stringstream stream{ret};
		std::string buf;
		while(std::getline(stream, buf, ' ')){
			parsed.push_back(buf);
		}
		val = 0;
		ioctl(sock, FIONBIO, &val);
		if(parsed.size() == 3)
			return std::make_tuple(parsed[0].c_str(), std::stoi(parsed[1]), std::stoi(parsed[2]));
		else
			return std::make_tuple(parsed[0].c_str(), -1, -1);
	}
}
#else
std::tuple<const char*, int, int> Net::get(){
	char data;
	std::string ret;
	int n = 0;
	u_long val = 1;
	ioctlsocket(sock, FIONBIO, &val);
	n = recv(sock, &data, 1, 0);
	if(n < 1){
		if(WSAGetLastError() == WSAEWOULDBLOCK){
			val = 0;
			ioctlsocket(sock, FIONBIO, &val);
			return std::make_tuple("nodata", -1, -1);
		} else{
			val = 0;
			ioctlsocket(sock, FIONBIO, &val);
			closed = 1;
			return std::make_tuple("nodata", -1, -1);
		}
	} else{
		ret = data;
		while(recv(sock, &data, 1, 0) > 0){
			ret += data;
		}
		std::vector<std::string> parsed;
		std::stringstream stream{ret};
		std::string buf;
		while(std::getline(stream, buf, ' ')){
			parsed.push_back(buf);
		}
		val = 0;
		ioctlsocket(sock, FIONBIO, &val);
		if(parsed.size() == 3)
			return std::make_tuple(parsed[0].c_str(), std::stoi(parsed[1]), std::stoi(parsed[2]));
		else
			return std::make_tuple(parsed[0].c_str(), -1, -1);
	}
}
#endif // Linux_System

