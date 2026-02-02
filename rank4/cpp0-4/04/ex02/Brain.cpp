/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 06:05:43 by davigome          #+#    #+#             */
/*   Updated: 2025/05/29 19:17:48 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
{
	std::cout << "Constructor for Brain called." << std::endl;
}

Brain::Brain(const Brain &brain)
{
	std::cout << "Brain copy constructor called" << std::endl;
	*this = brain;
}

Brain& Brain::operator=(const Brain &brain)
{
	std::cout <<"Copy assigment operator for Brain called." << std::endl;
	if (this != &brain)
	{
		int i = -1;
		while (++i < 100)
			this->ideas[i] = brain.ideas[i];
	}
	return *this;
}
Brain::~Brain()
{
	std::cout << "Destructor for Brain called" << std::endl;
}