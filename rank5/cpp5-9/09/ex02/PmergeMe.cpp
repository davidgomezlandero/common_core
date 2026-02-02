/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:16:27 by davigome          #+#    #+#             */
/*   Updated: 2025/07/04 16:32:00 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _arg(""), _timeDeque(0), _timeVector(0)
{}

PmergeMe::~PmergeMe()
{}

PmergeMe::PmergeMe(PmergeMe const &other) : _deque(other._deque), _vector(other._vector), _arg(other._arg), _timeDeque(0), _timeVector(0)
{
}

PmergeMe &PmergeMe::operator=(PmergeMe const &other)
{
	if (this != &other)
	{
		this->_arg = other._arg;
		this->_vector = other._vector;
		this->_deque = other._deque;
		this->_timeDeque = other._timeDeque;
		this->_timeVector = other._timeVector;
	}
	return *this;
}

PmergeMe::PmergeMe(std::string arg)
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
	if (errno == ERANGE || *endptr != '\0' || val < 0 || val > INT_MAX)
		error();
	return val;
}

void PmergeMe::showUnsorted(std::string arg)
{
	std::istringstream iss(arg);
	std::string token;
	std::cout << "Before:  ";
	iss >> token;
	std::cout << token;
	int i = 1;
	while(iss >> token)
	{
		if (i == 4 && this->_deque.size() > 5)
		{
			std::cout << " [...]";
			break; 
		}
		std::cout << " ";
		std::cout << token;
		++i;
	}
	std::cout << std::endl;
}

void PmergeMe::sorted()
{
	std::cout << "After:	 ";
	std::cout << this->_deque[0];
	int j = 1;
	for (size_t i = 1; i < this->_deque.size(); i++)
	{
		if (j == 4 && this->_deque.size() > 5)
		{
			std::cout << " [...]";
			break; 
		}
		std::cout << " " << this->_deque[i];
		++j;
	}
	std::cout << std::endl;
}

static std::deque<long int> insertionOrderDeque(size_t size)
{
	std::deque<long int> order;
	int j0 = 0;
	int j1 = 1;
	if (size == 1)
	{
		order.push_back(0);
		return order;
	}
	while (static_cast<size_t>(j1) < size)
	{
		if (std::find(order.begin(), order.end(), j1) == order.end())
		{
			order.push_back(j1);
			if (j0 == 0)
				order.push_back(0);
			int aux = j1;
			while(--aux > j0)
				order.push_back(aux);
		}
		int next = j1 + 2 * j0;
		j0 = j1;
		j1 = next;
	}
	for (size_t i = 0; i < size; i++)
	{
		if (std::find(order.begin(), order.end(), i) == order.end())
			order.push_back(i);
	}
	return order;
}

static std::vector<long int> insertionOrderVector(size_t size)
{
	std::vector<long int> order;
	int j0 = 0;
	int j1 = 1;
	if (size == 1)
	{
		order.push_back(0);
		return order;
	}
	while (static_cast<size_t>(j1) < size)
	{
		if (std::find(order.begin(), order.end(), j1) == order.end())
		{
			order.push_back(j1);
			if (j0 == 0)
				order.push_back(0);
			int aux = j1;
			while(--aux > j0)
				order.push_back(aux);
		}
		int next = j1 + 2 * j0;
		j0 = j1;
		j1 = next;
	}
	for (size_t i = 0; i < size; i++)
	{
		if (std::find(order.begin(), order.end(), i) == order.end())
			order.push_back(i);
	}
	return order;
}

void PmergeMe::fordJhonsonDeque(std::deque<long int> &deque)
{
	std::deque<long int> a;
	std::deque<long int> b;

	if (deque.size() <= 1)
		return ;
	long int struggle = -1;
	for(size_t i = 0; i + 1 < deque.size(); i+=2)
	{
		long int first = deque[i];
		long int second = deque[i + 1];
		
		if (first > second)
		{
			a.push_back(first);
			b.push_back(second);
		}else
		{
			a.push_back(second);
			b.push_back(first);
		}
	}
	if (deque.size() % 2 != 0)
	{
		struggle = deque.back();
		deque.pop_back();
	}
	fordJhonsonDeque(a);
	std::deque<long int> order = insertionOrderDeque(b.size());
	for (size_t i = 0; i < order.size(); ++i)
	{
		int index = order[i];
		std::deque<long int>::iterator pos = std::lower_bound(a.begin(), a.end(), b[index]);
		a.insert(pos, b[index]);
	}
	if (struggle != -1)
	{
		std::deque<long int>::iterator pos = std::lower_bound(a.begin(), a.end(), struggle);
		a.insert(pos, struggle);
	}
	deque = a;
}

void PmergeMe::showDequeTime()
{
	std::cout << "Time to process a range of " << this->_deque.size() << " elements with std::deque : " << std::fixed << std::setprecision(5) << this->_timeDeque << " us" << std::endl;
}

void PmergeMe::showVectorTime()
{
	std::cout << "Time to process a range of " << this->_vector.size() << " elements with std::vector : " << std::fixed << std::setprecision(5)<< this->_timeVector << " us" << std::endl;
}

void PmergeMe::mergeDeque()
{
	std::istringstream iss(this->_arg);
	std::string token;
	clock_t start = clock();

	while(iss >> token)
	{
		this->_deque.push_back(parseInt(token));
	}
	if (this->_deque.size() < 2)
		error();
	fordJhonsonDeque(this->_deque);
	clock_t end = clock();
	float seconds = static_cast<float>(end - start) / CLOCKS_PER_SEC * 1000.0;
	this->_timeDeque = seconds;
}

void PmergeMe::fordJhonsonVector(std::vector<long int> &vector)
{
	std::vector<long int> a;
	std::vector<long int> b;

	if (vector.size() <= 1)
		return ;
	long int struggle = -1;
	for(size_t i = 0; i + 1 < vector.size(); i+=2)
	{
		long int first = vector[i];
		long int second = vector[i + 1];
		
		if (first > second)
		{
			a.push_back(first);
			b.push_back(second);
		}else
		{
			a.push_back(second);
			b.push_back(first);
		}
	}
	if (vector.size() % 2 != 0)
	{
		struggle = vector.back();
		vector.pop_back();
	}
	fordJhonsonVector(a);
	std::vector<long int> order = insertionOrderVector(b.size());
	for (size_t i = 0; i < order.size(); ++i)
	{
		int index = order[i];
			std::vector<long int>::iterator pos = std::lower_bound(a.begin(), a.end(), b[index]);
			a.insert(pos, b[index]);
	}
	if (struggle != -1)
	{
		std::vector<long int>::iterator pos = std::lower_bound(a.begin(), a.end(), struggle);
		a.insert(pos, struggle);
	}
	vector = a;
}

void PmergeMe::mergeVector()
{
	std::istringstream iss(this->_arg);
	std::string token;
	clock_t start = clock();

	while(iss >> token)
	{
		this->_vector.push_back(parseInt(token));
	}
	if (this->_vector.size() < 2)
		error();
	fordJhonsonVector(this->_vector);
	clock_t end = clock();
	float seconds = static_cast<float>(end - start) / CLOCKS_PER_SEC* 1000.0 ;
	this->_timeVector = seconds;
}