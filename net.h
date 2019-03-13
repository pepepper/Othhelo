#include <string>
#include <utility>

#ifdef Linux_System
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#else
#include <winsock2.h>
#endif // 

class Net{
	public:
	Net();
	~Net();
	void close();
	int makeconnect(std::string host);
	std::tuple<int, int> login(long long room, std::string pass);
	std::tuple<int, int> login(long long room);
	long long makeroom(int x,int y);
	int setpassword(std::string pass);
	int put(int x, int y);
	int freeput(int x, int y);
	std::tuple<std::string, int, int> get();
	int closed,ready,started;
	private:
	struct hostent *host;
	struct sockaddr_in server;
	SOCKET sock;
};
