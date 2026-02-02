#include "../Server.hpp"

void Server::ft_kick(std::string buffer, int fd)
{	
	std::istringstream iss(buffer);
	std::string token;
	std::string response;
	std::string reason;
	Client *client_aux = getClientByFd(fd);
	iss >> token;
	if (token[0] == '#')
		token.erase(0, 1);
	else
	{
		sendfillmessage(ERR_NOSUCHCHANNEL, token, fd);
        return;
	}
	std::string nick;
	iss >> nick;
	if (!(iss >> reason))
		reason = "*";
	if (Channel_already_created(token))
	{
		Channel *channel = getChannel(token);

		if (!channel)
			return ;
		if (!channel->checkIfAdmin(fd))
		{
			sendfillmessage(ERR_CHANOPRIVSNEEDED, channel->getChannelName(), fd);
            return ;
		}

		Client *client = getClientByNick(nick);
		if (!client)
			return ;
		if (!channel->checkClientExist(client->getClifd()))
		{
			std::string requester = getClientByFd(fd)->getNickName();
            response = ":" + this->name + " 441 " + requester + " " + nick + " #" + channel->getChannelName() + " :They aren't on that channel\r\n";
            sendResponse(response, fd);
            return ;
		}
		if (fd == client->getClifd())
		{
			if (channel->checkIfLastAdmin(fd))
			{
				addRandomAdmin(fd, channel->getChannelName());
			}
		}
		std::vector<std::pair<int, bool> > members = channel->getClients_pairs(); // Copy before removal
		std::string modeMsg = ":" + client_aux->getNickName() + "!" + client_aux->getUserName() +"@localhost KICK #" + channel->getChannelName() + " " + nick + " :" + reason + "\r\n";
		for (size_t i = 0; i < members.size(); i++)
		{
			sendResponse(modeMsg, members[i].first);
		}
		channel->eraseClientChannel(client->getClifd());
		if (channel->getClients_pairs().empty())
		{
			removeChannel(channel->getChannelName());
			return ;
		}
		
	}
	else
	{
		sendfillmessage(ERR_NOSUCHCHANNEL, token, fd);
	}

	return ;
}


