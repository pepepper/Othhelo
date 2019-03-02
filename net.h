#include <SDL_net.h>
#include <string>
#include <utility>
class Net
{
  public:
	Net();
	~Net();
	int connect(std::string host);
	int put(int x,int y);
	std::tuple<const char*,int,int> get();
	int myturn;//0:black is my turn
  private:
	IPaddress server;
	TCPsocket connection;
	SDLNet_SocketSet sockets;
};