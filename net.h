#include <SDL_net.h>
#include <string>
#include <utility>
class Net{
	public:
	Net();
	~Net();
	int connect(std::string host);
	std::tuple<int, int> login(int room, std::string pass);
	std::tuple<int, int> login(int room);
	int makeroom();
	int setpassword(std::string pass);
	int setboardsize(int x, int y);
	int put(int x, int y);
	std::tuple<const char*, int, int> get();
	int myturn;//0:black is my turn
	private:
	IPaddress server;
	TCPsocket connection;
	SDLNet_SocketSet sockets;
};