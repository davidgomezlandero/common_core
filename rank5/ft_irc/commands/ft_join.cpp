#include "../Server.hpp"

void Server::ft_join(std::string buffer, int fd)
{
	std::istringstream iss(buffer);
	std::string token;
	const std::string invalidChars = " ,";

	iss >> token;
	if (!token.empty() && token [0] == '#')
    	token.erase(0, 1);
	else 
	{
		sendfillmessage(ERR_NOSUCHCHANNEL, token, fd);
    	return;
	}
	if (token.empty())
	{
		sendfillmessage(ERR_NEEDMOREPARAMS, "CHANNEL NAME IS EMPTY", fd);
		return;
	}
	if (token.find_first_of(invalidChars) != std::string::npos || (token.length() > 1 && token.substr(0,2)== "^G")
		|| token.find(' ') != std::string::npos)
	{  
		sendfillmessage(ERR_NOSUCHCHANNEL, token, fd);
    	return ;
	}
	if (Channel_already_created(token))
	{
		Channel *channel  = getChannel(token);
		if (channel->checkClientExist(fd))
		{
			return ;
		}
		if (channel->getInviteOnly())
		{
			if (!channel->checkIfInvite(fd))
			{
				 sendfillmessage(ERR_INVITEONLYCHAN, channel->getChannelName(), fd);
       			 return ;
			}
		}
		if (channel->getPassBoolean())
		{
			iss >> token;
			if (!channel->checkPasswordChannel(token))
			{
				sendfillmessage(ERR_BADCHANNELKEY, channel->getChannelName(), fd);
        		return ;
			}
		}
		if (channel->getLimitBolean())
		{
			if (channel->getClients_pairs().size() + 1 >= static_cast<size_t>(channel->getLimit()))
			{
				sendfillmessage(ERR_CHANNELISFULL, channel->getChannelName(), fd);
        		return ;
			}
		}
		channel->addNewMember(fd);
		sendfillmessage(CMD_JOIN, channel->getChannelName(), fd);
		Client* joiningClient = getClientByFd(fd);
		std::string joinMsg = ":" + joiningClient->getNickName() + "!" + joiningClient->getUserName() + "@localhost JOIN #" + channel->getChannelName() + "\r\n";
		std::vector<std::pair<int, bool> >& clients_pairs = channel->getClients_pairs();
		for (size_t i = 0; i < clients_pairs.size(); i++) {
			sendResponse(joinMsg, clients_pairs[i].first);
		}
		sendfillmessage(RPL_NAMREPLY, channel->getChannelName(), fd);
		if (!channel->getTopic().empty())
    		sendfillmessage(RPL_TOPIC, channel->getChannelName(), fd);
		else
    		sendfillmessage(RPL_NOTOPIC, channel->getChannelName(), fd);
		sendfillmessage(RPL_ENDOFNAMES, channel->getChannelName(), fd);
		return;
	}
	Channel channel(token, fd, &clients_vector);
	channels_vector.push_back(channel);
	sendfillmessage(CMD_JOIN, channel.getChannelName(), fd);
	sendfillmessage(RPL_NAMREPLY, channel.getChannelName(), fd);
	if (!channel.getTopic().empty())
    	sendfillmessage(RPL_TOPIC, channel.getChannelName(), fd);
	else
    	sendfillmessage(RPL_NOTOPIC, channel.getChannelName(), fd);
	sendfillmessage(RPL_ENDOFNAMES, channel.getChannelName(), fd);
	return;
}