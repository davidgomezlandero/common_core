#include "Client.hpp"

Client::Client(int cli_fd, std::string ip, int port)
{
	this->cli_fd = cli_fd;
	this->ip = ip;
	this->port = port;
	this->logIn = false;
	this->logNick = false;
	this->registered = false;
	this->user_name = "";
	this->nick_name = "";
}

Client::~Client()
{
/* 	close(this->cli_fd); */
}

void Client::setlogIn(bool logIn)
{
	this->logIn = logIn;
}

void Client::setLogNick(bool logNick)
{
	this->logNick = logNick;
}

bool Client::getlogIn()
{
	return logIn;
}

bool Client::getLogNick()
{
	return this->logNick;
}

int Client::getClifd()
{
	return cli_fd;
}



void Client::setRegistered(bool registered)
{
	this->registered = registered;
}

void Client::setUserName(std::string user_name)
{
	this->user_name = user_name;
}

void Client::setNickName(std::string nick_name)
{
	this->nick_name = nick_name;
}

std::string Client::getUserName()
{
	return user_name;
}

std::string Client::getNickName()
{
	return nick_name;
}

std::string Client::getIp()
{
	return this->ip;
}

bool Client::getRegistered()
{
	return registered;
}

