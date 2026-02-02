/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:48:55 by davigome          #+#    #+#             */
/*   Updated: 2025/05/29 20:43:37 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal()
{
	std::cout << "Animal basic constructor called" << std::endl;
	this->setType("nonSpecifiedType");
}

Animal::Animal(std::string _type)
{
	std::cout << "Animal basic constructor called" << std::endl;
	this->setType(_type);
}

Animal::Animal(const Animal &animal)
{
	std::cout << "Animal copy constructor called." << std::endl;
	*this  = animal;
}
Animal& Animal::operator=(const Animal &animal)
{
	std::cout << "Copy assigment operator called" << std::endl;
	if (this != &animal)
		this->_type = animal._type;
	return *this;
}
Animal::~Animal()
{
	std::cout << "Animal destructor called." << std::endl; 
}
std::string Animal::getType(void) const
{
	return (this->_type);
}
void Animal::setType(std::string type)
{
	this->_type = type;
}
void	Animal::makeSound(void) const
{
	std::cout << "Animal random sound." << std::endl;
}
