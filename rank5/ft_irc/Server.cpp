#include "Server.hpp"

bool Server::g_signal = false;

void Server::signal_handler(int sig)
{
	(void)sig;
	std::cout << "Signal recieved!\n";
	g_signal = true;

}

Server::Server()
{
	this->port = 0;
	this->password = "";
	this->name = "localhost.irc";
	this->channels_vector.clear();
}

Server::~Server()
{
}

void Server::throw_error(std::string error_msg)
{
	throw std::runtime_error(error_msg);
}

void Server::createServerSocket()
{
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);

	int opt = 1;
	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (server_fd == -1)
		throw_error("Failed to create socket!");
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		throw_error("Failed to set socket to reuse mode");
	if (fcntl(server_fd, F_SETFL, O_NONBLOCK) == -1)
		throw_error("Failed to set socket to non-block mode!");
	if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		throw_error("Failed to bind socket");
	if (listen(server_fd, SOMAXCONN) == -1)
		throw_error("Failed to set socket in listen state!");

	struct pollfd new_fd;

	new_fd.fd = server_fd;
	new_fd.events = POLLIN;
	new_fd.revents = 0;
	poll_fds.push_back(new_fd);
}

Server::Server(std::string const &port, std::string const &password)
{
	this->port = std::atoi(port.c_str());
	this->password = password;
}

void Server::accept_connection()
{
	struct sockaddr_in cli_addr;
	socklen_t len = sizeof(cli_addr);

	int client_fd = accept(server_fd, (struct sockaddr *)&cli_addr, &len);
	if (client_fd == -1)
		throw_error("Failed to accept client");
	if (fcntl(client_fd, F_SETFL, O_NONBLOCK) == -1)
		throw_error("Failed to set client to non-block mode!");

	struct pollfd new_fd;
	new_fd.fd = client_fd;
	new_fd.events = POLLIN;
	new_fd.revents = 0;
	poll_fds.push_back(new_fd);

	Client client(client_fd, inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
	clients_vector.push_back(client);
	std::cout << "Connection has been accetpted! to ip: " <<  inet_ntoa(cli_addr.sin_addr) << std::endl;
	sendResponse("Password baby\r\n", client_fd);
}

Client *Server::getClient(int fd)
{
	for (size_t i = 0; i < clients_vector.size(); i++)
	{
		if (clients_vector[i].getClifd() == fd)
			return (&clients_vector[i]);
	}
	return NULL;
}

void Server::sendResponse(std::string msg, int fd)
{
	if (send(fd, msg.c_str(), msg.size(), 0) == -1)
		throw_error("Failed to send response!\r\n");
}


void Server::checkLogIn(std::string buffer, std::string token, int fd) 
{
	Client *client = getClient(fd);

	if (!client) 
		throw_error("Error!");

	if (client->getlogIn()) 
	{
		std::string error = ":" + this->name + " 462 " + client->getNickName() + " :You may not reregister\r\n";
		sendResponse(error, fd);
		return ;
	}
	std::string pass = getCommandArg(buffer, token);
	std::string msg = ":" + this->name + " 464 " + client->getNickName() + " :Password incorrect\r\n";
	if (pass.empty()) 
	{
		sendResponse(msg, fd);
		return ;
	}
	if (pass == this->password)
		client->setlogIn(true);
	else 
	{
		sendResponse(msg, fd);
		return ;
	}
	sendResponse("Please put your Nickname\r\n",fd);
}

bool Server::isNickTaken(const std::string& nick) {
    for (std::vector<Client>::iterator it = clients_vector.begin(); it != clients_vector.end(); ++it) {
        if (it->getNickName() == nick) {
            return true;
        }
    }
    return false;
}

void Server::checkNick(std::string buffer, std::string token, int fd) 
{
	const std::string invalidChars = ",*?!@.";
	const std::string invalidStart = "$:#&~%+";


	Client *client = getClient(fd);
	if (!client) 
		throw_error("Error!");

	std::string nick = getCommandArg(buffer, token);
	std::string error = ":" + this->name + " 432 * " + nick + " :Erroneous nickname\r\n";
	if (nick.empty() || nick.find_first_of(invalidChars) != std::string::npos
		|| invalidStart.find(nick[0]) !=  std::string::npos || nick.find(' ') != std::string::npos) 
	{
		sendResponse(error, fd);
		return ;
	}
	error = ":" + this->name + " 433 * " + nick + " :Nickname is already in use\r\n";
	if (isNickTaken(nick))
	{
		sendResponse(error, fd);
		return ;
	}
	if (!client->getLogNick())
	{
		client->setNickName(nick);
		client->setLogNick(true);
		sendResponse("Please put your User\r\n", fd);
	}
	else
	{
		std::string message =":" + client->getNickName() + "!" + client->getUserName() + "@" + this->name + " NICK :" + nick + "\r\n";
		sendResponse(message, fd);
		client->setNickName(nick);
	}

	return ;
}

void Server::checkUser(std::string buffer, std::string token, int fd) 
{
	Client *client = getClient(fd);
	if (!client) 
		throw_error("Error!\r\n");

	std::string user = getCommandArg(buffer, token);
	if (user.empty()) 
	{
		sendResponse("Invalid user!\r\n", fd);
		return ;
	}
	std::istringstream iss(user);
	std::string cleanUser;

	iss >> cleanUser;
	client->setUserName(cleanUser);
	if (!client->getRegistered())
	{
		sendfillmessage(RPL_WELCOME, "", fd);
		sendfillmessage(RPL_YOURHOST, "" , fd);
		sendfillmessage(RPL_CREATED, "", fd);
		sendfillmessage(RPL_MYINFO, "", fd);
	}
	client->setRegistered(true);
	return ;
}

bool Server::checkRegistration(std::string buffer, std::string token, int fd)
{
	Client *client = getClient(fd);

	if (iequals(token, "PASS"))
		checkLogIn(buffer, token, fd);
	else if(!client->getlogIn())
		sendResponse("Please before nick or user put your password\r\n", fd);
	else if (iequals(token, "NICK") && client->getlogIn())
		checkNick(buffer, token, fd);
	else if (!client->getLogNick())
		sendResponse("Please before user put your nickname\r\n", fd);
	else if (iequals(token, "USER") && client->getLogNick())
		checkUser(buffer, token, fd);

	if (client->getlogIn() && client->getUserName() != "" && client->getNickName() != "")
		return true;
	return false;
}

bool Server::iequalscommands(std::string token, std::string &buffer)
{
	if (iequals(token, "JOIN") || iequals(token, "PART") || iequals(token, "MODE"))
	{
		buffer = getCommandArg(buffer, token);
		return true;
	}
	else if (iequals(token, "LIST") || iequals(token, "INVITE") || iequals(token, "KICK"))
	{
		buffer = getCommandArg(buffer, token);
		return true;
	}
	else if (iequals(token, "TOPIC")|| iequals(token, "PRIVMSG") || iequals(token, "BOT"))
	{
		buffer = getCommandArg(buffer, token);
		return true;
	}
	return false;
}	

void Server::proccesCommand(std::string buffer, int fd) 
{
	Client *client = getClient(fd);
	if (!client) throw_error("Error!");

	// Sanitize input: remove trailing \r or \n
	while (!buffer.empty() && (buffer[buffer.size() - 1] == '\n' || buffer[buffer.size() - 1] == '\r'))
		buffer.erase(buffer.size() - 1);

	std::string token;
	std::istringstream iss(buffer);
	iss >> token;

	if (iequals(token, "PASS") || iequals(token, "USER") || iequals(token, "NICK") || iequals(token, "CAP"))
	{
		if (iequals(token, "CAP"))
			return ;
		if (!checkRegistration(buffer, token, fd))
			return ;
	}
	else if (!client->getlogIn() || client->getUserName() == "" || client->getNickName() == "")
		sendResponse("you haven't register yet!\r\n", fd);
	else if (iequalscommands(token, buffer))
	{
		if (iequals(token, "JOIN"))
			ft_join(buffer, fd);
		else if (iequals(token, "MODE"))
			ft_mode(buffer, fd);
		else if (iequals(token, "INVITE"))
			ft_invite(buffer, fd);
		else if (iequals(token, "KICK"))
			ft_kick(buffer, fd);
		else if (iequals(token, "TOPIC"))
			ft_topic(buffer, fd);
		else if (iequals(token, "PRIVMSG"))
			ft_privmsg(buffer, fd);
		else if (iequals(token, "BOT"))
			ft_bot(buffer, fd);
	}
	else
		sendResponse("Command not found: " + token+"\r\n", fd);
}

void Server::eraseClientFromChannels(int fd, std::string quitMessage)
{
	Client *client = getClientByFd(fd);
	std::string message;
	message = ":" + client->getNickName() +"!" + client->getUserName() + "@" + this->name + " QUIT " + quitMessage;

	for (std::vector<Channel>::iterator it = channels_vector.begin(); it != channels_vector.end(); ++it) 
    {
		if (it->checkClientExist(fd) && it->getClients_pairs().size() <= 1)
		{
			it->eraseClientChannel(fd);
			removeChannel(it->getChannelName());
			it--;
		}
		else if (it->checkClientExist(fd))
		{	
			addRandomAdmin(fd, it->getChannelName());
			channelSendResponse(it->getChannelName(), message, fd);
			it->eraseClientChannel(fd);
		}
    }
}

void Server::recieved_data(int fd)
{
	char buffer[1024];
	ssize_t bytes_read = recv(fd, buffer, sizeof(buffer) - 1, 0);
	std::string token;

	buffer[bytes_read] = '\0';
	std::string quitMessage(buffer);
	std::istringstream iss(buffer);
	iss >> token;
	if (bytes_read == -1)
		throw_error("Failed to recieved data!\r\n");
	if (bytes_read == 0 || token == "QUIT" || token == "quit")
	{
		/* if (bytes_read == 0)
		{
			std::cout << "Client has been desconnected " << fd << std::endl;
			close_client(fd);
			return ;
		} */
		if (bytes_read == 0)
		{
			quitMessage = ":Says goodbye\r\n";
		}
		else
		{
			if (strlen(buffer) > token.length())
				quitMessage = quitMessage.substr(token.length());
			size_t firstChar = quitMessage.find_first_not_of(" \t");
			if (firstChar != std::string::npos)
				quitMessage = quitMessage.substr(firstChar);
			if (quitMessage[0] != ':')
			{
				sendResponse("Invalid quit message\r\n", fd);
				return;
			}
		}
		eraseClientFromChannels(fd, quitMessage);
		std::cout << "Client has been desconnected " << fd << std::endl;
		close_client(fd);
		return ;
	}
	else
	{
		this->_buffer += buffer;

		if (strstr(_buffer.c_str(), "\r\n") || strchr(_buffer.c_str(), '\n'))
		{
			std::istringstream iss(_buffer);
			std::string line;
			while (getline(iss, line))
				proccesCommand(line, fd);
			_buffer.clear();
		}
		else
		{
			setbuffer(this->_buffer);
		}
	}
	buffer[0] = '\0';
}

void Server::launchServer()
{
	while (!g_signal)
	{
		signal(SIGINT, Server::signal_handler);
		signal(SIGQUIT, Server::signal_handler);
		if (poll(&poll_fds[0], poll_fds.size(), -1) == -1)
			throw_error("Poll has failed!");
		for (size_t i = 0; i < poll_fds.size(); i++)
		{
			if (poll_fds[i].revents & POLLIN)
			{
				if (poll_fds[i].fd == server_fd)
					accept_connection();
				else
					recieved_data(poll_fds[i].fd);
			}
		}
	}
}

void Server::init()
{
	createServerSocket();
	std::cout << "Server has been created!" << std::endl;
	launchServer();
}

void Server::close_client(int fd)
{
	std::vector<struct pollfd>::iterator itt = poll_fds.begin();
	while (itt != poll_fds.end())
	{
		if (itt->fd == fd)
			poll_fds.erase(itt);
		else
			++itt;
	}

	std::vector<Client>::iterator it = clients_vector.begin();
	while (it != clients_vector.end())
	{
		if (it->getClifd() == fd)
		{
			close(fd);
			it = clients_vector.erase(it);
		}
		else
			++it;
	}
}

void Server::setbuffer(std::string buffer)
{
	this->_buffer = buffer;
}

std::string Server::getbuffer()
{
	return _buffer;
}

bool Server::Channel_already_created(std::string name)
{
	if (channels_vector.empty())
		return false;
	for (size_t i = 0; i < channels_vector.size(); i++)
	{
		if (channels_vector[i].getChannelName() == name)
			return true;
	}
	return false;
}

Channel *Server::getChannel(std::string name)
{
	for (size_t i = 0; i < channels_vector.size(); i++)
	{
		if(channels_vector[i].getChannelName() == name)
			return &channels_vector[i];
	}
	return NULL;
}

Client *Server::getClientByNick(std::string nick)
{
	for (size_t i = 0; i < clients_vector.size(); i++)
	{
		if (clients_vector[i].getNickName() == nick)
			return &clients_vector[i];
	}
	return NULL;
}

Client *Server::getClientByFd(int fd)
{
	for (size_t i = 0; i < clients_vector.size(); i++)
	{
		if (clients_vector[i].getClifd() == fd)
			return &clients_vector[i];
	}
	return NULL;
}

void Server::channelSendResponse(std::string channelName, std::string response, int fd)
{
    Channel *channel = getChannel(channelName);

    if (!channel)
        return;

    std::vector<std::pair<int, bool> > clients = channel->getClients_pairs();
    for (size_t i = 0; i < clients.size(); ++i)
    {
		if (clients[i].first == fd)
			continue ;
        sendResponse(response, clients[i].first);
    }
}

void Server::removeChannel(std::string channelName)
{
    for (std::vector<Channel>::iterator it = channels_vector.begin(); it != channels_vector.end(); ++it) 
    {
        if (it->getChannelName() == channelName) 
        {
            channels_vector.erase(it);
            break;
        }
    }
}

void Server::addRandomAdmin(int fd, std::string channelName)
{
	Channel *channel = getChannel(channelName);
	std::vector<std::pair<int, bool> >& clients_pairs = channel->getClients_pairs();
	for (size_t i = 0; i < clients_pairs.size(); i++)
	{
		if (clients_pairs[i].first != fd)
		{
			clients_pairs[i].second = true;
			Client *client_aux = getClientByFd(clients_pairs[i].first);
			std::string modeMsg = ":" + client_aux->getNickName() + "!" + client_aux->getUserName() +"@localhost MODE #" + channelName + " +o " + client_aux->getNickName() + "\r\n";
			std::vector<std::pair<int, bool> >& members = channel->getClients_pairs();
			for (size_t j = 0; j < members.size(); j++)
			{
				sendResponse(modeMsg, members[j].first);
			}
			return;
		}
	}
}
