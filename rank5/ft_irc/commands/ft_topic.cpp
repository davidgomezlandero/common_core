#include "../Server.hpp"
void Server::ft_topic(std::string buffer, int fd) 
{
	std::istringstream iss(buffer);
    std::string channelName;
    
    iss >> channelName;
    
    if (!channelName.empty() && channelName[0] == '#')
        channelName = channelName.substr(1);
    
    Channel* channel = getChannel(channelName);
    Client* client = getClientByFd(fd);
    if (!channel) {
        sendfillmessage(ERR_NOSUCHCHANNEL, "", fd);
        return;
    }
	if (!channel->checkClientExist(fd)) {
        sendfillmessage(ERR_NOTONCHANNEL, channelName, fd);
        return;
	}
    std::string newTopic;
    size_t double_dot = buffer.find(":");
    if (double_dot != std::string::npos)
        newTopic = buffer.substr(double_dot + 1);
if (newTopic.empty()) {
        if (!channel->getTopic().empty()) {
            sendfillmessage(RPL_TOPIC, channelName, fd);
        } else {
            sendfillmessage(RPL_NOTOPIC, channelName, fd);
        }
    } else {
        if (channel->getTopicBolean() && !channel->checkIfAdmin(fd)) {
            sendfillmessage(ERR_CHANOPRIVSNEEDED, channelName, fd);
            return;
        }
        channel->setTopic(newTopic);
        std::string topicMsg = ":" + client->getNickName() + "!" + client->getUserName() + "@localhost TOPIC #" + channelName + " :" + newTopic + "\r\n";
        std::vector<std::pair<int, bool> >& members = channel->getClients_pairs();
        for (size_t i = 0; i < members.size(); i++) {
            sendResponse(topicMsg, members[i].first);
        }
    }
}
