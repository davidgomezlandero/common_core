/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:16:03 by davigome          #+#    #+#             */
/*   Updated: 2025/07/01 18:57:53 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <algorithm>
#include <exception>
#include <stack>
#include <fstream>
#include <sstream>
#include <string>
#include <cerrno>
#include <climits>

class RPN
{
	private:
		std::stack<long int> _stack;
		std::string _arg;
		
		RPN();
		RPN(RPN const &other);
		RPN &operator=(RPN const &other);
	public:
		
		RPN(std::string arg);
		~RPN();
		void calculator();		
};