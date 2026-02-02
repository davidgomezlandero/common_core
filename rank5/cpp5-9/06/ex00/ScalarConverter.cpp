/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:18:35 by davigome          #+#    #+#             */
/*   Updated: 2025/06/17 06:58:04 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter(){
	
}
ScalarConverter::~ScalarConverter(){
	
}
ScalarConverter::ScalarConverter(const ScalarConverter &other){
	*this = other;
}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other){
	(void)other;
	return *this;
}

void	ScalarConverter::isChar(const std::string &argv, std::string &type)
{
	if (argv.length() > 1 || !std::isprint(argv[0]) || std::isdigit(argv[0]))
		return ;
	type = "CHAR";
}

void	ScalarConverter::isInt(const std::string &argv, std::string &type)
{
	errno = 0;
	char *endptr = NULL;

	long val = std::strtol(argv.c_str(), &endptr, 10);
	if (errno == ERANGE || *endptr != '\0' || val < INT_MIN || val > INT_MAX)
		return ;
	type = "INT";
}

void	ScalarConverter::isFloat(const std::string &argv, std::string &type)
{
	std::string num;
	
	if (argv == "-inff" || argv == "+inff" || argv == "nanf")
	{
		type = "FLOAT";
		return ;
	}
	if (argv[argv.length() - 1] != 'f' || argv.length() < 3)
		return ;
	num = argv.substr(0, argv.length() - 1);
	char *endptr = NULL;
	errno = 0;
	float val = std::strtof(num.c_str(), &endptr);
	if (*endptr != '\0' || errno == ERANGE)
		return ;
	int i = -1;
	int count = 0;
	while (argv[++i])
	{
		if (argv[i] == '.')
			++count;
	}
	if (count != 1)
		return ;
	i = num.find('.');
	num = num.substr(i + 1);
	if (num == "" || num.length() != 1 || !std::isdigit(num[0]))
		return ;
	(void)val;
	type = "FLOAT";
}

void	ScalarConverter::isDouble(const std::string &argv, std::string &type)
{
	std::string num;
	
	if (argv == "-inf" || argv == "+inf" || argv == "nan")
	{
		type = "DOUBLE";
		return ;
	}
	if (argv.length() < 2)
		return ;
	num = argv;
	char *endptr = NULL;
	errno = 0;
	double val = std::strtod(num.c_str(), &endptr);
	if (*endptr != '\0' || errno == ERANGE)
		return ;
	int i = -1;
	int count = 0;
	while (argv[++i])
	{
		if (argv[i] == '.')
			++count;
	}
	if (count != 1)
		return ;
	i = num.find('.');
	num = num.substr(i + 1);
	if (num == "" || num.length() != 1 || !std::isdigit(num[0]))
		return ;
	(void)val;
	type = "DOUBLE";
}

void	ScalarConverter::printChar(const std::string &argv)
{
	std::cout << "char: " << argv[0] << std::endl;
	int i = argv[0];
	std::cout << "int: " << i << std::endl;
	std::cout << "float: " << i << ".0f" << std::endl;
	std::cout << "double: " << i << ".0" << std::endl;
}

void	ScalarConverter::printInt(const std::string &argv)
{	
	char *endptr = NULL;

	long val = std::strtol(argv.c_str(), &endptr, 10);
	std::cout << "char: ";
	char c = val;
	if (!isprint(c))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << c << std::endl;
	std::cout << "int: " << val << std::endl;
	std::cout << "float: " << val<< ".0f" << std::endl;
	std::cout << "double: " << val << ".0" << std::endl;
}

void	ScalarConverter::printFloat(const std::string &argv)
{
	std::string num;
	
	if (argv == "-inff" || argv == "+inff" || argv == "nanf")
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int : impossible" << std::endl;
		std::cout << "float: " << argv << std::endl;
		num = argv.substr(0, argv.length() - 1);
		std::cout << "double: " << num << std::endl;
		return ;
	}
	if (argv[argv.length() - 1] != 'f' || argv.length() < 3)
		return ;
	num = argv.substr(0, argv.length() - 1);
	char *endptr = NULL;
	errno = 0;
	float val = std::strtof(num.c_str(), &endptr);
	char c = val;
	std::cout << "char: ";
	if (!isprint(c))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout <<  c << std::endl;
	int i(val);
	std::cout << "int: " << i << std::endl;
	std::cout << "float: " << argv << std::endl;
	std::cout << "double: " << num << std::endl;
}

void	ScalarConverter::printDouble(const std::string &argv)
{
	std::string num = argv;
	if (argv == "-inf" || argv == "+inf" || argv == "nan")
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int : impossible" << std::endl;
		std::cout << "float: " << argv << "f" << std::endl;
		std::cout << "double: " << argv << std::endl;
		return ;
	}
	char *endptr = NULL;
	errno = 0;
	double val = std::strtod(num.c_str(), &endptr);
	int i = val;
	char c = val;
	std::cout << "char: ";
	if (!isprint(c))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout <<  c << std::endl;
	std::cout << "int: " << i << std::endl;
	std::cout << "float: " << argv << "f" << std::endl;
	std::cout << "double: " << argv << std::endl;
}

void	ScalarConverter::convert(const std::string &argv)
{
	std::string type = "";
	ScalarConverter converter;
	
	converter.isChar(argv, type);
	converter.isInt(argv, type);
	converter.isFloat(argv, type);
	converter.isDouble(argv, type);
	if (type == "")
	{
		std::cerr << "Invalid input" << std::endl;
		return ;
	}
	if (type == "CHAR")
		converter.printChar(argv);
	if (type == "INT")
		converter.printInt(argv);
	if (type == "FLOAT")
		converter.printFloat(argv);
	if (type == "DOUBLE")
		converter.printDouble(argv);
}