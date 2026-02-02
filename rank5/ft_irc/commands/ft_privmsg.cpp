#include "../Server.hpp"

void Server::ft_privmsg(std::string buffer, int fd)
{
	std::istringstream iss(buffer);
	std::string token;
	std::string destination;
	std::string message;

	iss >> token;
	Client* sender = getClientByFd(fd);
    if (!sender)
		return;
	if (token[0] == '#')
	{
		token.erase(0 ,1);
		destination = token;
		Channel *channel = getChannel(destination);

		if (!channel)
		{
			sendfillmessage(ERR_NOSUCHCHANNEL, destination, fd);
            return;
		}
		if (!channel->checkClientExist(fd))
		{
			sendfillmessage(ERR_CANNOTSENDTOCHAN, destination, fd);
            return ;
		}
		buffer.erase(0, token.size() + 1);
		message = generateResponse(trimLeading(buffer));
		if (message.empty())
		{
			sendfillmessage(ERR_NOTEXTTOSEND, "", fd);
			return ;
		}
		std::string response = ":" + sender->getNickName() + "!" + sender->getUserName() + "@localhost PRIVMSG #" + destination + " :" + message + "\r\n";
        channelSendResponse(destination, response, fd);
	}
	else
	{
		destination = token;
		Client *client = getClientByNick(destination);

		if (!client)
		{
			sendfillmessage(ERR_NOSUCHNICK, destination, fd);
            return ;
		}
		buffer.erase(0, token.size() + 1);
		message = generateResponse(trimLeading(buffer));
		if (message.empty())
		{
			sendfillmessage(ERR_NOTEXTTOSEND, "", fd);
			return ;
		}
        std::string response = ":" + sender->getNickName() + "!" + sender->getUserName() + "@localhost PRIVMSG " + destination + " :" + message + "\r\n";
        sendResponse(response, client->getClifd());
	}

	return ;
}

std::string Server::generateResponse(std::string message)
{
	std::string response;

	if (message[0] != ':')
	{
		std::istringstream iss(message);

		iss >> response;
	}
	else
	{
		response = message.erase(0, 1);
	}
	return response;
}