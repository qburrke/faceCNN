#include <network.hpp>
#include <matrix.hpp>

#define P(x) std::cout << x << std::endl

int main(){
	Net net;
	n_create(net, 10, 4, 4, 2);
	n_rand(net);
	n_save("data/net.data", net);
	n_free(net);
	Net net2;
	n_load("data/net.data", net2);
	n_save("data/net2.data", net2);
	n_free(net2);
	return 0;
}
