#pragma once

#include "Server.hpp"

class Client;
class Server;

class Channel
{
	private:
		std::vector <Client> *clients_vector;
		std::string channelName;
		std::vector<std::pair<int , bool> > clients_pairs;
		std::string topic;
		bool pass_boolean;
		std::string pass_string;
		bool invite_only;
		bool topic_bolean;
		bool limit_bolean;
		int limit;
		std::pair<int , bool> max_members;
		std::vector<std::pair<int, bool> > members_invite;
	public:
		Channel(std::string channelName, int fd, std::vector <Client> *lients_vector);
		~Channel();

		void setChannelName(std::string channelName);
		std::string getChannelName();

		const std::vector<Client>& getClientsVector() const;

		void addNewMember(int fd);
		bool checkClientExist(int fd);
		void eraseClientChannel(int fd);
		bool checkIfAdmin(int fd);


		std::vector<std::pair<int, bool> > &getClients_pairs();

		bool checkIfLastAdmin(int fd);


		void setPassBoolean(bool pass);

		void setInviteOnly(bool invite_only);

		void setPassString(std::string pass_string);

		void setLimitBolean(bool limit_bolean);
		void setLimit(int limit);
		
		void setTopicBolean(bool topic_bolean);


		bool getPassBoolean();


		bool getInviteOnly();

		bool getTopicBolean();
		void setTopic(std::string topic);
		std::string getTopic();

		bool getLimitBolean();
		int	getLimit();
		std::string getPassString();

		std::vector<std::pair<int, bool> > getMemberInvite();

		bool inviteMember(int fd);

		bool checkIfInvite(int fd);

		bool checkPasswordChannel(std::string pass);
};
