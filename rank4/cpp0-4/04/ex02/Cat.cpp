/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:02:07 by davigome          #+#    #+#             */
/*   Updated: 2025/05/29 18:55:07 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : Animal("Cat")
{
	std::cout << "Cat constructor called." << std::endl;
	this->_brain = new Brain();
}

Cat::Cat(const Cat &cat) : Animal(cat)
{
	std::cout << "Cat copy constructor called. " << std::endl;
	this->_brain = new Brain(*cat._brain);
}

Cat& Cat::operator=(const Cat &cat)
{
	std::cout << "Cat assignation constructor called." << std::endl;
	if (this != &cat)
	{
		delete _brain;
		this->_type = cat._type;
		this->_brain = new Brain(*cat._brain); //Deep copy	
	}
	return *this;
}

Cat::~Cat()
{
	std::cout << "Cat destructor called" << std::endl;
	delete this->_brain;
}

void	Cat::makeSound(void) const
{
	std::cout << "Mew Mew" << std::endl;
}