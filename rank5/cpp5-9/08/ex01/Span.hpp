/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 09:18:01 by davigome          #+#    #+#             */
/*   Updated: 2025/06/29 09:59:19 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <exception>

class Span
{
	private:
		unsigned int _size;
		std::vector<int> _vector;
	public:
		Span();
		Span(unsigned int size);
		Span(Span const &other);
		Span &operator=(Span const &other);
		~Span();
		

		void addNumber(int n);
		void addNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end);
		int shortestSpan();
		int longestSpan();

		class FullException : public std::exception{
			virtual const char* what() const throw();
		};
		class NotEnoughException : public std::exception {
			virtual const char*  what() const throw();	
		};
		
};