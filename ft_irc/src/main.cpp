#include "ft_irc.hpp"

static void removeUsers(Server &server, std::set<int> &fdsToRemove);
static std::string checkIncomingMessage(const std::string &buffer);
static int manageUserMassage(User *user, char *buffer, ssize_t bytesRecv);
static void signalHandler(int signum); // signal handler
const std::map<const std::string, enum commandName>	getCommandNames();

Server* g_server = NULL; // global server pointer for signal handling!!!
volatile sig_atomic_t g_shouldExit = 0;

int main(int argc, char **argv)
{
	// Set signals
	signal(SIGINT, signalHandler);	// (ctrl + c)
	signal(SIGQUIT, signalHandler); // (ctrl + \)
	signal(SIGPIPE, SIG_IGN); // broken pipe

	// Check arguments
	int port;

	if (checkArgv(argc, argv, port) == 1) {
		return 1;
	}

	std::string password(argv[2]);

	// Server creation
	std::cout << "--- SERVER ---" << std::endl;
	Server server(port, password);
	g_server = &server; // Set global server pointer for signal handling

	try {
		server.createSocket();
		server.bindSocket();
		server.initPollfd();
	} catch (const std::runtime_error &e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	server.getFds().push_back(server.getServerPollfd());
	
	std::set<int> fdsToRemove; // Set to keep track of fds to remove

	const std::map<const std::string, enum commandName>	commandNames = getCommandNames();

	// Users management
	while (!g_shouldExit) {
		int pollRet = poll(server.getFds().data(), server.getFds().size(), -1);
		if (pollRet == -1) {
			std::cerr << "Error in poll()" << std::endl;
			break;
		}
		else if (pollRet == 0) {
			continue;
		}

		// Accept new users
		if (server.getFds()[0].revents & POLLIN) {
			server.acceptUserConnection();
		}

		// Handle polls
		for (size_t i = 1; i < server.getFds().size(); i++) {
			short revents = server.getFds()[i].revents;
			int fd = server.getFds()[i].fd;
			User *user = server.getUsers()[fd];

			if (revents & POLLIN) {
				char buffer[MAX_COMMAND_LENGTH];
				ssize_t bytesRecv = recv(fd, buffer, sizeof(buffer), 0);

				if (bytesRecv == -1) {
					if (errno != EAGAIN && errno != EWOULDBLOCK) {
						std::cout << "Read error on fd " << fd << std::endl;
						fdsToRemove.insert(fd);
						continue;
					}
				} else if (bytesRecv == 0) {
					fdsToRemove.insert(fd);
					continue;
				}

				if (manageUserMassage(user, buffer, bytesRecv) == 1) {
					continue;
				}
				logCommandToServer(user->getMessage(), *user);

				parseMessage(commandNames, server.getUsers(), fd, server.getMembership(), server.getPassword(), fdsToRemove);
			}
						
			if (revents & POLLOUT) {
				user->trySendMessage();
			}
			
			if (revents & (POLLERR | POLLHUP | POLLNVAL)) {
				std::cerr << "Error on fd " << fd << std::endl;
				fdsToRemove.insert(fd);
			}
		}
		removeUsers(server, fdsToRemove);
		fdsToRemove.clear();
	}

	server.shutdown();

	std::cout << "Server closed" << std::endl;
	return 0;
}

std::string checkIncomingMessage(const std::string &buffer) {
	std::string processedBuffer;

	for (size_t i = 0; i < buffer.size(); i++) {
		if (buffer[i] == '\n') {
			if (i == 0 || buffer[i - 1] != '\r') {
				processedBuffer += '\r';
			}
		}
		processedBuffer += buffer[i];
	}
	return processedBuffer;
}

// Remove all users that are marked for removal (based on fd)
void removeUsers(Server &server, std::set<int> &fdsToRemove) {
	command quit;
	quit.push_back("QUIT");

	std::set<int>::iterator it = fdsToRemove.begin();
	while (it != fdsToRemove.end()) {
		int fd = *it;

		std::vector<pollfd> &fds = server.getFds();
		std::vector<pollfd>::iterator fdsIt;

		for (fdsIt = fds.begin(); fdsIt != fds.end(); ++fdsIt) {
			if (fdsIt->fd == fd) {
				server.disconnectUser(fd, quit);
				break;
			}
		}
		it++;
	}
}

/*
	Takes users input, appends it to the user's message buffer
	Then checks if the buffer contains a newline character
	If it does then it checks if buffer has \r\n if not it adds \r before the newline (checkIncomingMessage)
	Then sets the user's message to the processed buffer and clears the message buffer
	Finally prints the user's nickname, socket fd, and message to the console

	If message sent by user does not contain a newline character, it returns 1 to indicate that the message is not complete
*/
int manageUserMassage(User *user, char *buffer, ssize_t bytesRecv) {
	user->setMessageBuffer(user->getMessageBuffer() + std::string(buffer, bytesRecv));
	if (user->getMessageBuffer().find('\n') == std::string::npos) {
		return 1;
	}
	std::string processedBuffer = checkIncomingMessage(user->getMessageBuffer());
	user->setMessage(processedBuffer);
	user->setMessageBuffer("");

	return 0;
}

void signalHandler(int signum) {
	std::cout << "\nSignal " << signum << " received. Shutting down..." << std::endl;
	g_shouldExit = 1;
}

const std::map<const std::string, enum commandName>	getCommandNames() {
	std::map<const std::string, enum commandName>	commandNames;
	commandNames.insert(std::make_pair("CAP", CAP));
	commandNames.insert(std::make_pair("PASS", PASS));
	commandNames.insert(std::make_pair("NICK", NICK));
	commandNames.insert(std::make_pair("USER", USER));
	commandNames.insert(std::make_pair("PING", PING));
	commandNames.insert(std::make_pair("QUIT", QUIT));
	commandNames.insert(std::make_pair("PRIVMSG", PRIVMSG));
	commandNames.insert(std::make_pair("JOIN", JOIN));
	commandNames.insert(std::make_pair("KICK", KICK));
	commandNames.insert(std::make_pair("INVITE", INVITE));
	commandNames.insert(std::make_pair("TOPIC", TOPIC));
	commandNames.insert(std::make_pair("MODE", MODE));
	commandNames.insert(std::make_pair("WHO", WHO));
	commandNames.insert(std::make_pair("PRINT", PRINT));
	return commandNames;
}