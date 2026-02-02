/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:42:36 by davigome          #+#    #+#             */
/*   Updated: 2025/07/04 16:13:42 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &other) : _data(other._data)
{}


BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &other)
{
	if (this != &other)
	{
		this->_data = other._data;
	}
	return *this;
}
BitcoinExchange::~BitcoinExchange()
{}

static int badInput(std::string line)
{
	std::cout << "Error: bad input => " + line << std::endl;
	return false;
}

static bool checkDate(std::string date, std::string line)
{
	if (date.length() != 10 || date[0] < '2' || date[0] > '9' 
		|| date[1] < '0' || date[1] > '9')
		return badInput(line);
	if (date[2] < '0' || date[2] > '9' || date[3] < '0' || date[3] > '9' || date[4] != '-')
		return badInput(line);
	if (date[5] > '1' || date [5] < '0' || date [6] < '0' || date [6] > '9' || date[7] != '-')
		return badInput(line);
	if (date[8] > '3' || date[8] < '0' || date[9] > '9' || date[9] < '0')
		return badInput(line);
	if (date[5] == '1' && date[6] > '2')
		return badInput(line);
	if (date[5] == '0' && date[6] == '0')
		return badInput(line);
	if ((date[5] == '0' && date[6] == '1' && date[8] == '3' && date[9] > '1') 
		|| (date[5] == '0' && date[6] == '2' && date[8] == '3')
		|| (date[5] == '0' && date[6] == '3' && date[8] == '3' && date[9] > '1')
		|| (date[5] == '0' && date[6] == '4' && date[8] == '3' && date[9] > '0')
		|| (date[5] == '0' && date[6] == '5' && date[8] == '3' && date[9] > '1')
		|| (date[5] == '0' && date[6] == '6' && date[8] == '3' && date[9] > '0')
		|| (date[5] == '0' && date[6] == '7' && date[8] == '3' && date[9] > '1')
		|| (date[5] == '0' && date[6] == '8' && date[8] == '3' && date[9] > '1')
		|| (date[5] == '0' && date[6] == '9' && date[8] == '3' && date[9] > '0')
		|| (date[5] == '1' && date[6] == '0' && date[8] == '3' && date[9] > '1')
		|| (date[5] == '1' && date[6] == '1' && date[8] == '3' && date[9] > '0')
		|| (date[5] == '1' && date[6] == '2' && date[8] == '3' && date[9] > '1'))
		return badInput(line);
	std::string year = date.substr(0, 4);
	int bi = 0;
	errno = 0;
	char *endptr = NULL;

	long val = std::strtol(year.c_str(), &endptr, 10);
	if (val % 4 == 0)
	{
		if (val % 100 != 0)
		{
			bi = 1;
		}else if (val % 400 == 0)
			bi = 1;
	}
	if (date[5] == '0' && date[6] == '2' && date[8] == '2' && date[9] == '9' && bi == 0)
		return badInput(line);
	return true;
}

static bool checkBtcs(std::string btcs, std::string line)
{
	char *endptr = NULL;
	errno = 0;
	float val = std::strtof(btcs.c_str(), &endptr);
	if (*endptr != '\0' || errno == ERANGE)
		return badInput(line);
	if (val > 1000.0)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}
	if (val < 0.0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}
	return true;
}

void BitcoinExchange::execute(std::string line, std::string date, std::string btcs)
{
	float coins;
	float value;

	char *endptr = NULL;
	errno = 0;
	coins = std::strtof(btcs.c_str(), &endptr);
	std::map<std::string, float>::iterator it = this->_data.lower_bound(date);
	if (it != this->_data.end() && it->first == date)
	{
		value = coins * it->second;
		std::cout << date << " => " << btcs << " = "<< value << std::endl;
	}
	else if (it == this->_data.begin())
	{
		badInput(line);
	}
	else
	{
		--it;
		value = coins * it->second;
		std::cout << date << " => " << btcs << " = "<< value << std::endl;
	}
}

void BitcoinExchange::parseInput(std::string &inputTxt)
{
	std::ifstream file(inputTxt.c_str());
	std::string line;
	std::string date;
	std::string pipe;
	std::string btcs;
	std::string err;
	
	if (!file.is_open())
		throw std::runtime_error("Error: could not open file.");
	getline(file, line);
	if (line != "date | value")
		throw std::runtime_error("Error: the first line must be \"data | value\".");
	while (getline(file, line))
	{
		std::istringstream iss(line);
		if (!(iss >> date))
		{
			badInput(line);
			continue;
		}
		if (!(iss >> pipe))
		{
			badInput(line);
			continue;
		}
		if (!(iss >> btcs))
		{
			badInput(line);
			continue;
		}
		if (iss >> err)
		{
			badInput(line);
			continue;
		}
		if (!checkDate(date, line))
			continue;
		if (pipe != "|")
		{
			badInput(line);
			continue;
		}
		if (!checkBtcs(btcs, line))
			continue;
		execute(line, date, btcs);
	}
	file.close();
}

BitcoinExchange::BitcoinExchange(std::string &inputTxt)
{
	std::ifstream file("data.csv");
	std::string line;
	
	if (!file.is_open())
		throw std::runtime_error("Error: could not open file.");
	getline(file, line);
	
	while (getline(file, line))
	{
		std::istringstream iss(line);
		std::string date;
		double value;
		if (getline(iss, date, ',') && iss >> value)
			this->_data[date] = value;
	}
	file.close();
	parseInput(inputTxt);
}