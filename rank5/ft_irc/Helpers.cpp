#include "Server.hpp"

// Compares two strings case-insensitively; returns true if they are equal, false otherwise.
bool iequals(const std::string &a, const std::string &b) 
{
	if (a.size() != b.size()) 
		return false;
	for (size_t i = 0; i < a.size(); ++i)
	{
		if (tolower(a[i]) != tolower(b[i]))
			return false;
	}
	return true;
}

// Removes leading whitespace (spaces, tabs, newlines, carriage returns) from the string.
std::string trimLeading(std::string s) 
{
	size_t pos = s.find_first_not_of(" \t\r\n");
	if (pos != std::string::npos)
		s.erase(0, pos);
	return s;
}


// Removes the command prefix from buffer and trims leading whitespace from the remaining string.
std::string getCommandArg(std::string buffer, const std::string &cmd) 
{
	if (buffer.size() < cmd.size()) 
		return "";
	buffer.erase(0, cmd.size());
	return trimLeading(buffer);
}
