/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongWrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:05:18 by davigome          #+#    #+#             */
/*   Updated: 2025/05/28 21:53:40 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal()
{
	std::cout << "WrongAnimal basic constructor called" << std::endl;
	this->setType("nonSpecifiedType");
}

WrongAnimal::WrongAnimal(std::string _type)
{
	std::cout << "WrongAnimal basic constructor called" << std::endl;
	this->setType(_type);
}

WrongAnimal::WrongAnimal(const WrongAnimal &wrongAnimal)
{
	std::cout << "WrongAnimal copy constructor called." << std::endl;
	*this  = wrongAnimal;
}
WrongAnimal& WrongAnimal::operator=(const WrongAnimal &wrongAnimal)
{
	std::cout << "Copy assigment operator called" << std::endl;
	if (this != &wrongAnimal)
		this->_type = wrongAnimal._type;
	return *this;
}
WrongAnimal::~WrongAnimal()
{
	std::cout << "WrongAnimal destructor called." << std::endl; 
}
std::string WrongAnimal::getType(void) const
{
	return (this->_type);
}
void WrongAnimal::setType(std::string type)
{
	this->_type = type;
}
void	WrongAnimal::makeSound(void) const
{
	std::cout << "WrongAnimal random sound." << std::endl;
}