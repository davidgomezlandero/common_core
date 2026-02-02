/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 21:35:38 by davigome          #+#    #+#             */
/*   Updated: 2025/06/27 21:59:03 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stack>
#include <deque>
#include <list>
#include <exception>
#include <algorithm>

template <typename T>
class MutantStack : public std::stack<T>{
	public:
		MutantStack() : std::stack<T>(){}
		MutantStack(MutantStack const &other) : std::stack<T>(other){}
		MutantStack &operator=(MutantStack const &other)
		{
			std::stack<T>::operator=(other);
			return *this;
		}
		~MutantStack(){}
		typedef typename std::stack<T>::container_type::iterator iterator;
		
		iterator begin()
		{
			return std::stack<T>::c.begin();
		}
		iterator end()
		{
			return std::stack<T>::c.end();
		}
};