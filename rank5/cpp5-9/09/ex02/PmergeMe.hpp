/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:16:41 by davigome          #+#    #+#             */
/*   Updated: 2025/07/04 10:27:29 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <algorithm>
#include <exception>
#include <deque>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cerrno>
#include <climits>
#include <iomanip>

class PmergeMe
{
	private:
		std::deque<long int> _deque;
		std::vector<long int> _vector;
		

		std::string _arg;
		float _timeDeque;
		float _timeVector;
	public:
		PmergeMe();
		PmergeMe(PmergeMe const &other);
		PmergeMe &operator=(PmergeMe const &other);
		~PmergeMe();

		PmergeMe(std::string arg);
		void mergeDeque();
		void mergeVector();
		void showUnsorted(std::string arg);
		void sorted();
		void fordJhonsonDeque(std::deque<long int> &deque);
		void fordJhonsonVector(std::vector<long int> &vector);
		void showDequeTime();
		void showVectorTime();
};
