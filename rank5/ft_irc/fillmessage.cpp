#include "Server.hpp"
#include "irc_messages.hpp"


std::string Server::joinNameReply(std::string channelName)
{
	std::string list;
	Channel *channel = getChannel(channelName);


	for (size_t i = 0; i < channel->getClients_pairs().size(); i++)
	{
		Client *client = getClientByFd(channel->getClients_pairs()[i].first);
		if ( i > 0)
			list += " ";
		if (channel->getClients_pairs()[i].second == true)
			list += "@" + client->getNickName();
		else
			list += client->getNickName();
	}
	return list;
}

std::string Server::channelModeis(std::string channelName)
{
	std::string mode;
	Channel *channel = getChannel(channelName);

	mode += "+";
	if (channel->getInviteOnly() == true)
		mode += "i";
	if (channel->getPassBoolean() == true)
		mode += "k";
	if (channel->getTopicBolean() == true)
		mode += "t";
	if (channel->getLimitBolean() == true)
		mode += "l";
	if (channel->getPassBoolean() == true)
		mode += " " + channel->getPassString();
	if (channel->getLimitBolean() == true)
	{
		std::stringstream ss;
		ss << channel->getLimit();
		mode += " " + ss.str();
	}
	return mode;
}

void Server::sendfillmessage(int mesage_type, std::string channelName, int fd)
{
	Client *client = getClientByFd(fd);

	if (!client)
        return ;

	Channel *channel = NULL;
	if (channelName != "")
	{
		channel = getChannel(channelName);
	}
	std::string joinMsg = "";

	switch (mesage_type)
	{
		case (CMD_JOIN):
			joinMsg = ":" + client->getNickName() +"!" + client->getUserName() + "@localhost JOIN #" + channel->getChannelName() +  "\r\n";
			break;
		case (RPL_WELCOME):
			joinMsg = ":" + this->name + " 001 " + client->getNickName() + " :Welcome to IRC" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 002 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_CREATED):
			joinMsg = ":" + this->name + " 003 " + client->getNickName() + " :This server was created ..." + "\r\n";
			break;
		case (RPL_MYINFO):
			joinMsg = ":" + this->name + " 004 " + client->getNickName() +
              " " + this->name + " ft_irc-1.0" + " o" + " itkl" + "\r\n";
			break;
		case (RPL_CHANNELMODEIS):
			joinMsg = ":" + this->name + " 324 " + client->getNickName() + " #" + channelName + " " + channelModeis(channelName) + "\r\n";
			break;
		case (RPL_NOTOPIC):
			joinMsg = ":" + this->name + " 331 " + client->getNickName() + " #" + channelName + " :No topic is set" +  "\r\n";
			break;
		case (RPL_TOPIC):
			joinMsg = ":" + this->name + " 332 " + client->getNickName() + " #" + channelName + " :" + channel->getTopic() +  "\r\n";
			break;
		case (RPL_NAMREPLY):
			joinMsg = ":" + this->name + " 353 " + client->getNickName() + " = #" + channel->getChannelName() + " :" + joinNameReply(channelName) + "\r\n";
			break;
		case (RPL_ENDOFNAMES):
			joinMsg = ":" + this->name + " 366 " + client->getNickName() + " #" + channel->getChannelName() + " :End of NAMES list" + "\r\n";
			break;
		case (ERR_NOSUCHCHANNEL):
			joinMsg = ":" + this->name + " 403 " + client->getNickName() + " #" + channelName + " :No such channel" +  "\r\n";
			break;
		case (ERR_CANNOTSENDTOCHAN):
			joinMsg = ":" + this->name + " 404 " + client->getNickName() + " #" + channelName + " :Cannot send to channel" +  "\r\n";
			break;
		case (ERR_NOTEXTTOSEND):
			joinMsg = ":" + this->name + " 412 " + client->getNickName() + " :No text to send" + "\r\n";
			break;
		case (ERR_NOTONCHANNEL):
			joinMsg = ":" + this->name + " 442 " + client->getNickName() + " #" + channelName + " :You're not on that channel" +  "\r\n";
			break;
		case (ERR_NEEDMOREPARAMS):
			joinMsg = ":" + this->name + " 461 " + client->getNickName() + " "+ channelName + " :Not enough parameters\r\n";
			break;
		case (ERR_KEYSET):
			joinMsg = ":" + this->name + " 467 " + client->getNickName() + " #" + channelName + " :Channel key already set" +  "\r\n";
			break;
		case (ERR_CHANNELISFULL):
			joinMsg = ":" + this->name + " 471 " + client->getNickName() + " #" + channelName + " :Cannot join channel" +  "\r\n";
			break;
		case (ERR_INVITEONLYCHAN):
			joinMsg = ":" + this->name + " 473 " + client->getNickName() + " #" + channelName + " :Cannot join channel" +  "\r\n";
			break;
		case (ERR_BADCHANNELKEY):
			joinMsg = ":" + this->name + " 475 " + client->getNickName() + " #" + channelName + " :Cannot join channel" +  "\r\n";
			break;
		case (ERR_CHANOPRIVSNEEDED):
			joinMsg = ":" + this->name + " 482 " + client->getNickName() + " #" + channelName + " :You're not operator" +  "\r\n";
			break;
		default:
			break;
	}
	sendResponse(joinMsg, fd);
}




