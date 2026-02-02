/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:39:32 by davigome          #+#    #+#             */
/*   Updated: 2025/05/27 12:25:33 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() :_value(0)
{
	/* std::cout << "Default constructor called" << std::endl; */
}

Fixed::~Fixed(){
	/* std::cout << "Destructor called" << std::endl; */
}

int	Fixed::getRawBits(void) const{
	/* std::cout << "getRawBits member function called" << std::endl; */
	return (this->_value);
}

Fixed::Fixed(const Fixed&fixed)
{
/* 	std::cout << "Copy constructor called" << std::endl; */
	*this = fixed;
}

Fixed& Fixed::operator=(const Fixed& fixed)
{
/* 	std::cout << "Copy assigment operator called" << std::endl; */
	if (this != &fixed)
		this->_value = fixed.getRawBits();
	return *this;
 }

void	Fixed::setRawBits(int const raw)
{
	this->_value = raw;
}

Fixed::Fixed (const int _value){
/* 	std::cout<< "Int constructor called" << std::endl; */
	this->_value = _value << this->_bits;
}

Fixed::Fixed(const float _value)
{
/* 	std::cout << "Float constructor called" << std::endl; */
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

bool	Fixed::operator>(Fixed const &fixed) const{
	if (this->_value > fixed.getRawBits())
		return true;
	return false;
}

bool	Fixed::operator<(Fixed const &fixed) const
{
	if (this->_value < fixed.getRawBits())
		return true;
	return false;
}
bool	Fixed::operator >= (Fixed const &fixed) const
{
	if (this->_value >= fixed.getRawBits())
		return true;
	return false;
}
bool	Fixed::operator <= (Fixed const &fixed) const
{
	if (this->_value <= fixed.getRawBits())
		return true;
	return false;
}
bool	Fixed::operator == (Fixed const &fixed) const
{
	if (this->_value == fixed.getRawBits())
		return true;
	return false;
}
bool	Fixed::operator != (Fixed const &fixed) const
{
	if (this->_value != fixed.getRawBits())
		return true;
	return false;
}
Fixed	Fixed::operator + (Fixed const &fixed)
{
	Fixed result;
	result.setRawBits(this->_value + fixed.getRawBits());
	return result;
}
Fixed	Fixed::operator - (Fixed const &fixed)
{
	Fixed result;
	result.setRawBits(this->_value - fixed.getRawBits());
	return result;
}
Fixed	Fixed::operator * (Fixed const &fixed)
{
	Fixed result;
	result.setRawBits((this->_value * fixed.getRawBits()) >> Fixed::_bits);
	return result;
}

Fixed	Fixed::operator / (Fixed const &fixed)
{
	Fixed result;
	result.setRawBits((this->_value << this->_bits) / fixed.getRawBits());
	return result;
} 
Fixed	Fixed::operator ++ ()
{
	this->_value++;
	return *this;
}
Fixed	Fixed::operator ++ (int)
{
	Fixed tmp(*this);
	++(*this);
	return tmp;
}
Fixed	Fixed::operator --(int)
{
	Fixed tmp(*this);
	--(*this);
	return tmp;
}
Fixed	Fixed::operator --()
{
	this->_value--;
	return *this;
}
Fixed const &Fixed::min(Fixed const &a, Fixed const &b)
{
	if (a.getRawBits() < b.getRawBits())
		return a;
	return b;
}
Fixed const &Fixed::max(Fixed const &a, Fixed const &b)
{
	if (a.getRawBits() < b.getRawBits())
		return b;
	return a;
}
Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	if (a.getRawBits() < b.getRawBits())
		return a;
	return b;
}
Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	if (a.getRawBits() < b.getRawBits())
		return b;
	return a;
}