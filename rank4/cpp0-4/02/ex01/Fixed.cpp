/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:39:32 by davigome          #+#    #+#             */
/*   Updated: 2025/05/25 08:17:53 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() :_value(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::~Fixed(){
	std::cout << "Destructor called" << std::endl;
}

int	Fixed::getRawBits(void) const{
	std::cout << "getRawBits member function called" << std::endl;
	return (this->_value);
}

Fixed::Fixed(const Fixed&fixed)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = fixed;
}

Fixed& Fixed::operator=(const Fixed& fixed)
{
	std::cout << "Copy assigment operator called" << std::endl;
	if (this != &fixed)
		this->_value = fixed.getRawBits();
	return *this;
 }

void	Fixed::setRawBits(int const raw)
{
	this->_value = raw;
}

Fixed::Fixed (const int _value){
	std::cout<< "Int constructor called" << std::endl;
	this->_value = _value << this->_bits;
}

Fixed::Fixed(const float _value)
{
	std::cout << "Float constructor called" << std::endl;
	this->_value = static_cast<int>(roundf(_value * (1 << _bits)));
}
int	Fixed::toInt() const{
	return this->_value >> this->_bits;
}

float Fixed::toFloat() const{
	return this->_value / float(1 << this->_bits);
}

std::ostream &operator<<(std::ostream &stream, const Fixed &_value)
{
	stream << _value.toFloat();
	return stream;
}