/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:39:48 by davigome          #+#    #+#             */
/*   Updated: 2025/05/29 17:46:36 by davigome         ###   ########.fr       */
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
	Fixed(const int  _value);
	Fixed(const float _value);
	int toInt(void) const;
	float toFloat(void) const;
	Fixed &operator=(const Fixed &fixed);
	~Fixed();
	int	getRawBits(void) const;
	void	setRawBits(int const raw);
};

p0

#endif