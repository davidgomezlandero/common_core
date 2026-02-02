#pragma once

#include <string>
#include <iostream>
#include <fcntl.h> 
#include <unistd.h>  

class Client
{
	private:
		int  cli_fd;
		std::string ip;
		int port;
		bool logIn;
		bool logNick;
		bool registered;
		std::string user_name;
		std::string nick_name;

	public:
		Client(int cli_fd, std::string ip, int port);
		~Client();


		void setlogIn(bool logIn);
		void setLogNick(bool logNick);
		void setUserName(std::string user_name);
		void setNickName(std::string nick_name);
		void setRegistered(bool registered);



		bool getlogIn();
		bool getLogNick();
		int getClifd();
		std::string getUserName();
		std::string getNickName();
		std::string getIp();
		bool getRegistered();
};