#include <SDL_net.h>
#include <string>
#include <utility>
class Net
{
  public:
	Net();
	~Net();
	int connnect(std::string host);
	int put(int x,int y);
	std::tuple<int,int> get();
	int myturn;//0:black is my turn
  private:
	IPAddress address;
	TCPsocket connection;
	SDLNet_SocketSet sockets;
}