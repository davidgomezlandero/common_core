#include "Server.hpp"

bool ft_check_args(char **av)
{
	std::string port(av[1]);
	std::string password(av[2]);

	if (port.empty() || port.find_first_not_of("0123456789") != std::string::npos)
		return (std::cerr << "Invalid port!\n", 0);
	if (port.size() > 5)
		return (std::cerr << "Invalid port!\n", 0);
	int portNum = atoi(port.c_str());
	if (portNum < 1024 || portNum > 65535)
		return (std::cerr << "Invalid port range!\n", 0);
	if (password.empty())
		return (std::cerr << "Password must not be empty!\n", 0);
	for (size_t i = 0; i < password.size(); i++)
	{
		if (!std::isalnum(password[i]))
			return (std::cerr << "Password must be alphanumeric!\n", 0);			
	}
	return (true);
}

int main(int ac, char **av)
{
	if (ac != 3)
		return (std::cerr << "Error!\n" << av[0] << " <port> <password>" << std::endl, 1);
	if (!ft_check_args(av))
		return 1;
	try
	{
		Server server(av[1], av[2]);
		server.init();
	}
	catch (...)
	{
		return (1);
	}
}


