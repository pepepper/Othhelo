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
	int makeconnect(std::string host);
	std::tuple<int, int> login(int room, std::string pass);
	std::tuple<int, int> login(int room);
	int makeroom();
	int setpassword(std::string pass);
	int setboardsize(int x, int y);
	int put(int x, int y);
	int freeput(int x, int y);
	std::tuple<const char*, int, int> get();
	int closed,ready,started;
	private:
	struct hostent *host;
	struct sockaddr_in server;
	SOCKET sock;
};
