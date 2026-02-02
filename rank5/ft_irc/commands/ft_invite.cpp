#include "../Server.hpp"

void Server::ft_invite(std::string buffer, int fd)
{
	std::istringstream iss(buffer);
	std::string token;
	std::string response;

	if (!(iss >> token))
	{
		sendfillmessage(ERR_NEEDMOREPARAMS, "INVITE", fd);
		return ;
	}
	Client *client = getClientByNick(token);
	Client *client_aux = getClientByFd(fd);
	if (!client)
	{
		response = ":" + this->name + " 401 " + client_aux->getNickName() + " " + token + " :No such nick/channel"+ "\r\n";
		sendResponse(response, fd);
		return ;
	}
	if (!(iss >> token))
	{
		sendfillmessage(ERR_NEEDMOREPARAMS, "INVITE", fd);
		return ;
	}
	if (token[0] != '#')
	{
		sendfillmessage(ERR_NOSUCHCHANNEL, token, fd);
		return ;
	}
	token.erase(0, 1);
	Channel *channel = getChannel(token);
	if (!channel)
	{
		sendfillmessage(ERR_NOSUCHCHANNEL, token, fd);
		return ;
	}
	if (!channel->checkClientExist(fd))
	{
		sendfillmessage(ERR_NOTONCHANNEL, channel->getChannelName(), fd);
		return ;
	}
	if (channel->checkClientExist(client->getClifd()))
	{
		response = ":" + this->name + " 443 " + client_aux->getNickName() + " " + client->getNickName() + " #"+ channel->getChannelName() + " :is already on channel\r\n";
		sendResponse(response, fd);
		return ;
	}
	if (!channel->checkIfAdmin(fd) && channel->getInviteOnly())
	{
		sendfillmessage(ERR_CHANOPRIVSNEEDED, channel->getChannelName(), fd);
		return ;
	}
	channel->inviteMember(client->getClifd());
	response = ":" + this->name + " 341 " + client_aux->getNickName() + " " + client->getNickName() + " #"+ channel->getChannelName() + "\r\n";
	sendResponse(response, fd);
	std::string inviteMsg = ":" + client_aux->getNickName() + "!" + client_aux->getUserName() + "@localhost INVITE " + client->getNickName() + " :#" + channel->getChannelName() + "\r\n";
	sendResponse(inviteMsg, client->getClifd());
	return ;
}