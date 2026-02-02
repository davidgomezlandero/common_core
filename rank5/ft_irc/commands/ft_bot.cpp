#include "../Server.hpp"

#include <ctime>

	
void Server::ft_bot(std::string buffer, int fd)
{
	std::istringstream iss(buffer);
	std::string token;
	std::string bot;
	std::string response;
	std::string base;
	Client *client = getClientByFd(fd);

	base = "bot!bot@localhost NOTICE " + client->getNickName() + " :";
	std::srand(std::time(NULL));
	int r = std::rand() % 3;
	switch(r){
		case 0:
			bot = "rock";
			break;
		case 1:
			bot = "scissors";
			break;
		default:
			bot = "paper";
			break;
	}
	if (!(iss >> token))
	{
		sendfillmessage(ERR_NEEDMOREPARAMS, "BOT", fd);
		return;
	}
	if (token != "paper" && token != "scissors" &&token != "rock")
	{
		std::string invalidMsg = ":BOT sólo acepta 'rock', 'paper' o 'scissors'\r\n";
		sendResponse(invalidMsg, fd);
		return;
	}
	if (bot == token)
	{
		response = "You played " + token + ", I played " + bot + ", that is a draw\r\n";
	}else if ((bot == "scissors" && token == "paper") || (bot == "paper" && token == "rock") 
		|| (bot == "rock" && token == "scissors"))
		response = "You played " + token + ", I played " + bot + ", bot is the winner\r\n";
	else
		response = "You played " + token + ", I played " + bot + ", you are the winner\r\n";
	sendResponse(base + response, fd);
}