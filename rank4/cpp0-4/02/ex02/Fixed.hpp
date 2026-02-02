/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:39:48 by davigome          #+#    #+#             */
/*   Updated: 2025/05/27 12:17:43 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed{

	private:
		static const int _bits = 8;
		int _value;
	public:
	Fixed();
	Fixed(const Fixed &fixed);
	Fixed &operator=(const Fixed &fixed);
	~Fixed();
	Fixed(const int  _value);
	Fixed(const float _value);
	int toInt(void) const;
	float toFloat(void) const;
	int	getRawBits(void) const;
	void	setRawBits(int const raw);


	bool	operator > (Fixed const &fixed) const;
	bool	operator < (Fixed const &fixed) const;
	bool	operator >= (Fixed const &fixed) const;
	bool	operator <= (Fixed const &fixed) const;
	bool	operator == (Fixed const &fixed) const;
	bool	operator != (Fixed const &fixed) const;
	Fixed	operator + (Fixed const &fixed);
	Fixed	operator - (Fixed const &fixed);
	Fixed	operator * (Fixed const &fixed);
	Fixed	operator / (Fixed const &fixed);
	Fixed	operator ++ ();
	Fixed	operator ++(int);
	Fixed	operator --(int);
	Fixed	operator --();
	static Fixed const &min(Fixed const &a, Fixed const &b);
	static Fixed const &max(Fixed const &a, Fixed const &b);
	static Fixed &min(Fixed &a, Fixed &b);
	static Fixed &max(Fixed &a, Fixed &b);
};

std::ostream &operator<<(std::ostream &stream, const Fixed &fixed);

#endif