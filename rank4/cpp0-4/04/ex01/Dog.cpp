/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:01:45 by davigome          #+#    #+#             */
/*   Updated: 2025/05/29 19:01:29 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : Animal("Dog")
{
	std::cout << "Dog constructor called." << std::endl;
	this->_brain = new Brain();
}

Dog::Dog(const Dog &dog) : Animal(dog)
{
	std::cout << "Dog copy constructor called. " << std::endl;
	this->_brain = new Brain(*dog._brain);
}

Dog& Dog::operator=(const Dog &dog)
{
	std::cout << "Dog assignation constuctor called." << std::endl;
	if (this != &dog)
	{
		delete _brain;
		this->_type = dog._type;
		this->_brain = new Brain(*dog._brain);
	}
	return *this;
}

Dog::~Dog()
{
	std::cout << "Dog destructor called" << std::endl;
	delete this->_brain;
}

void	Dog::makeSound(void) const
{
	std::cout << "Wouf Wouf" << std::endl;
}