#include <iostream>
#include <cstring>
#include <cstdio>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cerrno>
#include <cstdlib>
#include "helper_files/badFixHeader.hpp"

using namespace std;
//irc messages https://www.rfc-editor.org/rfc/rfc2812
void checkActivity(Server &server, sockaddr_in cli_addr, int clientsock[10], int addrlen) {
	while (true)
	{
		int newsock = accept(server.getSockFd(), (struct sockaddr*)&cli_addr, (socklen_t*)&addrlen);
		if (newsock == -1) {
			if (errno == EWOULDBLOCK || errno == EAGAIN) {
				// no more connections to accept
				break;
			}
			else {
				// error accepting connection
				cout << "Error accepting connection" << endl;
				break;
			}
		}
		else {
			cout << "New client connected: " << inet_ntoa(cli_addr.sin_addr) << ":" << ntohs(cli_addr.sin_port) << endl;

			// add the new client socket to the file descriptor set
			int i;
			struct pollfd *pollFd = server.getPollFd();
			for (i = 1; i <= MAX_CLIENTS; i++) {
				if (pollFd[i].fd == -1) {
					pollFd[i].fd = newsock;
					pollFd[i].events = POLLIN | POLLOUT | POLLHUP | POLLERR;
					clientsock[i-1] = newsock;
					break;
				}
			}

			// check if maximum number of clients has been reached
			if (i > MAX_CLIENTS) {
				cout << "Maximum number of clients reached" << endl;
				close(newsock);
			}
		}
	}
}

void runServerLoop(Server &server) {
	while (true) {
		// wait for activity on any of the file descriptors
		int ready = poll(server.getPollFd(), MAX_EVENTS, -1);
		if (ready == -1 && errno != EINTR) {
			cout << "Error polling file descriptors" << endl;
			break;
		}

		// check for incoming connections on the server socket
		struct sockaddr_in cli_addr = {};
		int addrlen = sizeof(server.getServAddr());
		int clientSockets[MAX_CLIENTS];
		char buffer[1024] = {0}; //Message limit should be 512 bytes gotta figure out some way to enforce that
		char message[1029] = {0};
		if (server.getPollFd()[0].revents & POLLIN) {
			checkActivity(server, cli_addr, clientSockets, addrlen);
		}

		// check for incoming data from clients
		struct pollfd *pollFd = server.getPollFd();
		for (int i = 1; i <= MAX_CLIENTS; i++) {
			if (pollFd[i].fd == -1 || !(pollFd[i].revents & POLLIN))
				continue;

			ssize_t valRead = read(pollFd[i].fd, buffer, sizeof(buffer));
			if (valRead == 0) {
				// client disconnected
				cout << "Client disconnected: " << inet_ntoa(cli_addr.sin_addr) << ":" << ntohs(cli_addr.sin_port) << endl;

				server.removeUser(pollFd[i].fd);

				// remove the client socket from the file descriptor set
				pollFd[i].fd = -1;

				// closeServer the client socket
				close(clientSockets[i - 1]);

				// clear the client socket from the list of connected clients
				clientSockets[i - 1] = 0;
			}
			else {
				// add client address to message and forward to all other clients
				memset(&message, 0, sizeof(message));
				sprintf(message, "[%s:%d] %s", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), buffer);

				server.receivedMessage(message, pollFd[i].fd);
			}
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		cout << "Correct usage " << argv[0] << " <port> <password>" << endl;
		return 0;
	}
	char *endptr;
	long int port = ::strtol(argv[1], &endptr, 10);
	if (*endptr != 0 || port < 0 || port > 65535) { //TODO check port limits
		cout << "Invalid port: " << argv[1] << "\nPlease ensure the port you give is between 0 and 65535" << endl;
		return 1;
	}

	size_t passLen = strlen(argv[2]);
	if (passLen < 3 || passLen > 64) { //TODO check what min/max pass len should be
		cout << "Please keep your password between 3 and 64 characters" << endl;
		return 1;
	}

	try {
		Server server = Server((int) port, string(argv[2]));
		runServerLoop(server);
		server.closeServer();
	} catch (exception &e) {
		cout << e.what() << endl;
		return 1;
	}
	return 0;
}
