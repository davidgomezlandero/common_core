#include "Channel.hpp"
#include "irc_messages.hpp"
#include "Server.hpp"

Channel::Channel(std::string channelName, int fd, std::vector <Client> *clients_vector)
 : clients_vector(clients_vector)
{
	this->channelName = channelName;
	clients_pairs.clear();
	this->clients_pairs.push_back(std::make_pair(fd, true));
	this->topic = "";
	this->pass_boolean = false;
	this->invite_only = false;
	this->topic_bolean = true;
	this->limit_bolean = false;
	this->limit = -1;
}

const std::vector<Client>& Channel::getClientsVector() const
{
    return *clients_vector;
}

void Channel::addNewMember(int fd)
{
	Server server;
	this->clients_pairs.push_back(std::make_pair(fd, false));
}

Channel::~Channel()
{}

std::string Channel::getChannelName()
{
	return this->channelName;
}

void Channel::setChannelName(std::string channelName)
{
	this->channelName = channelName;
}

bool Channel::checkClientExist(int fd)
{
	if (clients_pairs.empty())
		return false;
	for (size_t i = 0; i < clients_pairs.size(); i++) 
	{
        if (clients_pairs[i].first == fd)
			return true;
    }
    return false;
}

void Channel::eraseClientChannel(int fd)
{
    std::vector<std::pair<int, bool> >::iterator it;
    
    if (clients_pairs.empty())
        return;
    for (it = clients_pairs.begin(); it != clients_pairs.end(); it++) 
	{
        if (it->first == fd) 
		{
            it = clients_pairs.erase(it);
			it--;
        } 
    }

	std::vector<std::pair<int, bool> >::iterator it2;
    
    if (members_invite.empty())
        return;
    for (it2 = members_invite.begin(); it2 != members_invite.end(); it2++) 
	{
        if (it2->first == fd) 
		{
            it2 = members_invite.erase(it2);
			it2--;
        } 
    }
}

bool Channel::checkIfAdmin(int fd)
{
	for (size_t i = 0; i < clients_pairs.size(); i++) 
	{
        if (clients_pairs[i].first == fd)
		{
			if (clients_pairs[i].second == true)
				return true;
			else
				return false;
		}
    }
    return false;
}

std::vector<std::pair<int, bool> > &Channel::getClients_pairs()
{
	return clients_pairs;
}

void Channel::setPassBoolean(bool pass)
{
	this->pass_boolean = pass;
}

void Channel::setInviteOnly(bool invite_only)
{
	this->invite_only = invite_only;
}

void Channel::setTopicBolean(bool topic_bolean)
{
	this->topic_bolean = topic_bolean;
}

void Channel::setLimitBolean(bool limit_bolean)
{
	this->limit_bolean = limit_bolean;
}

void Channel::setLimit(int limit)
{
	this->limit = limit;
}

void Channel::setPassString(std::string pass_string)
{
	this->pass_string = pass_string;
}

bool Channel::getPassBoolean()
{
	return this->pass_boolean;
}

bool Channel::getTopicBolean()
{
	return this->topic_bolean;
}

void Channel::setTopic(std::string topic)
{
	this->topic = topic;
}

std::string Channel::getTopic()
{
	return this->topic;
}

bool Channel::getLimitBolean()
{
	return this->limit_bolean;
}
int	Channel::getLimit()
{
	return this->limit;
}

bool 	Channel::getInviteOnly()
{
	return this->invite_only;
}

std::string Channel::getPassString()
{
	return this->pass_string;
}

std::vector<std::pair<int, bool> > Channel::getMemberInvite()
{
	return this->members_invite;
}

bool Channel::checkIfInvite(int fd)
{
	for (std::vector<std::pair<int, bool> >::iterator it = members_invite.begin(); it != members_invite.end(); )
	{
		bool client_exists = false;

		for (size_t i = 0; i < clients_vector->size(); ++i)
		{
			if ((*clients_vector)[i].getClifd() == it->first)
			{
				client_exists = true;
				break;
			}
		}

		if (!client_exists)
		{
			it = members_invite.erase(it);
			continue;
		}
	
		if (it->first == fd && it->second == true)
			return true;
		++it;
	}
	return false;
}


bool Channel::inviteMember(int fd)
{
	bool clientExists = false;
	for (size_t i = 0; i < clients_vector->size(); ++i)
	{
		if ((*clients_vector)[i].getClifd() == fd)
		{
			clientExists = true;
			break;
		}
	}
	if (!clientExists)
		return false;

	for (size_t i = 0; i < members_invite.size(); ++i)
	{
		if (members_invite[i].first == fd)
			return true;
	}

	members_invite.push_back(std::make_pair(fd, true));
	return true;
}

bool Channel::checkPasswordChannel(std::string pass)
{
	if (this->pass_string == pass)
		return true;
	else
		return false;
}

bool Channel::checkIfLastAdmin(int fd)
{
	int admins = 0;

	if (!this->checkIfAdmin(fd))
		return false;

	for (size_t i = 0; i < clients_pairs.size(); i++) 
	{
        if (clients_pairs[i].second == true)
		{
			admins++;
		}
    }
	if (admins <= 1)
		return true;
    return false;
}
