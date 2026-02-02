/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:15:51 by davigome          #+#    #+#             */
/*   Updated: 2025/07/04 13:55:27 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() : _arg("")
{}

RPN::~RPN()
{}

RPN::RPN(RPN const &other) : _stack(other._stack), _arg(other._arg)
{}

RPN &RPN::operator=(RPN const &other)
{
	if (this != &other)
	{
		this->_stack = other._stack;
		this->_arg = other._arg;
	}
	return *this;
}

RPN::RPN(std::string arg)
{
	this->_arg = arg;
}

static void error()
{
	throw std::runtime_error("Error");
}

static long int parseInt(std::string token)
{
	errno = 0;
	char *endptr = NULL;

	long val = std::strtol(token.c_str(), &endptr, 10);
	if (errno == ERANGE || *endptr != '\0' || val < INT_MIN || val > 9)
		error();
	return val;
}

static void parseArg(std::string arg)
{
	std::istringstream iss(arg);
	std::string token;
	
	if (!(iss >> token))
		error();
}

void RPN::calculator()
{
	std::istringstream iss(this->_arg);
	std::string token;
	long int aux1;
	long int aux2;
	parseArg(this->_arg);
	if (this->_arg.empty())
		return error();
	while (iss >> token)
	{
		if (token == "-" || token == "+" || token == "/" || token == "*")
		{
			if (this->_stack.size() < 2)
				return error();
				
			aux1 = this->_stack.top();
			this->_stack.pop();
			aux2 = this->_stack.top();
			this->_stack.pop();
			if (token == "-")
			{
				aux1 = aux2 - aux1;
			}else if (token == "+")
			{
				aux1 = aux2 + aux1;
			}else if (token == "/")
			{
				if (aux1 == 0)
					return error();
				aux1 = aux2 / aux1;
			}else if (token == "*")
			{
				aux1 = aux2 * aux1;
			}
			if (aux1 > INT_MAX || aux1 < INT_MIN)
				return error();
			this->_stack.push(aux1);
		}
		else
		{
			this->_stack.push(parseInt(token));
		}
	}
	if (this->_stack.size() > 1)
		error();
	std::cout << this->_stack.top() << std::endl;
}