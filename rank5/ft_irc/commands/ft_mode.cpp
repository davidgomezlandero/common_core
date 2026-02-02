#include "../Server.hpp"

void Server::addModeArgument(std::string &token, std::vector<std::pair<std::string, std::string> > &mode_options, std::istringstream &iss)
{
	size_t i = 0;

	while (!token.empty() && i < mode_options.size())
	{
		if (mode_options[i].first == "-i" || mode_options[i].first == "+i" || mode_options[i].first == "-k"
			|| mode_options[i].first == "-l" || mode_options[i].first == "-t" || mode_options[i].first == "+t")
		{
			i++;
			continue ;
		}
		else
		{
			mode_options[i].second = token;
			i++;
		}
		if (!(iss >> token))
			break ;
	}
}

void Server::executeMode(std::vector<std::pair<std::string, std::string> > &mode_options, std::string channelName, int fd)
{
	for (size_t i = 0; i < mode_options.size(); i++)
	{
		std::string first = mode_options[i].first;
		std::string second = mode_options[i].second;
		if (first == "+o" || first == "-o")
			oMode(first, second, channelName, fd);
		else if (first == "+i" || first == "-i")
			iMode(first, channelName, fd);
		else if (first == "+k" || first == "-k")
			kMode(first, second, channelName, fd);
		else if (first == "+l" || first == "-l")
			lMode(first, second, channelName, fd);
		else if (first == "+t" || first == "-t")
			tMode(first, channelName, fd);
	}
}


void Server::oMode(std::string mode, std::string arg, std::string channelName, int fd)
{
	std::string response;
	Channel *channel = getChannel(channelName);
	Client *client = getClientByNick(arg);

	if (arg == "")
	{
		sendfillmessage(ERR_NEEDMOREPARAMS, mode, fd); 
		return;
	}
	if (!client)
	{
		Client *requester = getClientByFd(fd);
		response = ":" + this->name + " 401 " + (requester ? requester->getNickName() : "*") + " " + arg + " :No such nick/channel\r\n";
		sendResponse(response, fd);
		return ;
	}
	if (!channel)
		return ;

	for (size_t i = 0; i < channel->getClients_pairs().size(); i++) 
	{
        if (channel->getClients_pairs()[i].first == client->getClifd())
		{
			if (mode == "+o")
				channel->getClients_pairs()[i].second = true;
			else if (mode == "-o")
			{
				if (client->getNickName() == arg)
					return;
				channel->getClients_pairs()[i].second = false;
			}
		}
    }
}

void Server::iMode(std::string mode, std::string channelName, int fd)
{
	Channel *channel = getChannel(channelName);
	(void)fd;
	if (mode == "+i")
		channel->setInviteOnly(true);
	else
		channel->setInviteOnly(false);
}

void Server::kMode(std::string mode, std::string arg, std::string channelName, int fd)
{
	Channel *channel = getChannel(channelName);
	Client *client = getClientByFd(fd);

	if (!channel || !client)
		return;

	if (!channel->checkIfAdmin(fd)) 
	{
		sendfillmessage(ERR_CHANOPRIVSNEEDED, channelName, fd);
		return;
	}

	if (mode == "+k") 
	{
		if (arg.empty())
		 {
			sendfillmessage(ERR_NEEDMOREPARAMS, channelName, fd);
			return;
		}
		channel->setPassBoolean(true);
		channel->setPassString(arg);
	}
	else
		channel->setPassBoolean(false);
}

void Server::lMode(std::string mode, std::string arg, std::string channelName, int fd)
{
	Channel *channel = getChannel(channelName);

	if (!channel)
		return;

	if (!channel->checkIfAdmin(fd)) 
	{
		sendfillmessage(ERR_CHANOPRIVSNEEDED, channelName, fd);
		return;
	}

	if (mode == "+l") 
	{
		if (arg.empty()) 
		{
			sendfillmessage(ERR_NEEDMOREPARAMS, channelName, fd);
			return;
		}

		char* endptr = NULL;
		errno = 0;
		long limit = std::strtol(arg.c_str(), &endptr, 10);

		if (errno == ERANGE || limit > INT_MAX || limit <= 0 || *endptr != '\0') 
		{
			sendfillmessage(ERR_INVALIDMODEPARAM, channelName, fd);  // 696
			return;
		}
		if (static_cast<int>(limit) > 100 || static_cast<size_t>(limit) < channel->getClients_pairs().size()) 
		{
			sendfillmessage(ERR_INVALIDMODEPARAM, channelName, fd);  // 696
			return;
		}

		channel->setLimitBolean(true);
		channel->setLimit(static_cast<int>(limit));
	}
	else
		channel->setLimitBolean(false);

}

void Server::tMode(std::string mode, std::string channelName, int fd)
{
	Channel *channel = getChannel(channelName);
	(void)fd;
	if (mode == "+t")
		channel->setTopicBolean(true);
	else
		channel->setTopicBolean(false);
}

void Server:: sendModes(std::vector<std::pair<std::string, std::string> > &mode_options, std::string channelName, int fd)
{
	Channel *channel = getChannel(channelName);
	std::string modes;
	std::string  c;
	Client *client = getClientByFd(fd);

	modes = "";
	(void)channel;
	for (size_t i = 0; i < mode_options.size(); i++)
	{
		if (i == 0)
		{
			if (mode_options[0].first == "-o" && mode_options[0].second == client->getNickName())
				continue;
			c = mode_options[0].first;
			modes += c;
			continue;
		}
		if (modes.empty())
		{
			c = mode_options[i].first;
			modes += c;
			continue;
		}
		if (c[0] != mode_options[i].first[0])
		{
			c = mode_options[i].first;
			modes += " " + c;
		}else
			modes += mode_options[i].first[1];
	}
	for (size_t i = 0; i < mode_options.size(); i++)
	{
		if (mode_options[i].first == "-o" && client->getNickName() == mode_options[i].second)
			continue;
		if (!mode_options[i].second.empty())
		{
			modes += " " + mode_options[i].second;
		}
	}
	std::string modeMsg = ":" + client->getNickName() + "!" + client->getUserName() +"@localhost MODE #" + channelName + " " + modes + "\r\n";
	std::vector<std::pair<int, bool> >& members = channel->getClients_pairs();
    for (size_t i = 0; i < members.size(); i++)
    {
        sendResponse(modeMsg, members[i].first);
    }
}

void Server::ft_mode(std::string buffer, int fd)
{
	std::istringstream iss(buffer);
	std::string channelName;
	std::vector<std::pair<std::string, std::string> > mode_options;
	std::string token;

	iss >> channelName;


	if (channelName[0] == '#')
		channelName.erase(0, 1);
	else
	{
		sendfillmessage(ERR_NOSUCHCHANNEL, channelName, fd);
    	return ;
	}
	if (Channel_already_created(channelName))
	{
		if (!(iss >> token))
		{
			sendfillmessage(RPL_CHANNELMODEIS, channelName, fd);
			return;
		}
		Channel *channel = getChannel(channelName);
		if (!channel->checkIfAdmin(fd))
		{
			sendfillmessage(ERR_CHANOPRIVSNEEDED, channelName, fd);
			return;
		}
		if (!checkModeOptions(token, iss, mode_options, fd))
		{
			sendfillmessage(ERR_UNKNOWNMODE, token, fd);
			return ;
		}
		addModeArgument(token, mode_options, iss);
		executeMode(mode_options, channelName, fd);
		sendModes(mode_options, channelName, fd);
	}
	else
		sendfillmessage(ERR_NOSUCHCHANNEL, channelName, fd);

	return ;
}

bool Server::checkModeOptions(std::string &token, std::istringstream &iss, std::vector<std::pair<std::string, std::string> > &mode_options, int fd)
{
	std::string mode;
	std::string sign;
	
	if (token[0] != '+' && token[0] != '-')
	{
		return false;
	}
	while (!token.empty() && (token[0] == '+' || token[0] == '-'))
	{
		sign = token[0];
		for (size_t i = 1; i < token.size(); i++)
		{
			if (token[i] != 'o' && token[i] != 'i' && token[i] != 'k' &&  token[i] != 'l' && token[i] != 't')
			{
				sendfillmessage(ERR_UNKNOWNMODE, std::string(1, token[i]), fd);
			}
			else
			{
				mode = sign + token[i];
				mode_options.push_back(std::make_pair(mode, ""));
			}
		}
		if (!(iss >> token))
		{
			token.clear();
			break ;
		}
	}
	return true;

}
