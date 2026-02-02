/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:45:57 by davigome          #+#    #+#             */
/*   Updated: 2025/06/18 12:10:49 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

template<typename T>
void swap(T &a, T &b)
{
	T c;
	c = a;
	a = b;
	b = c;
}

template<typename T>
T min(T a, T b)
{
	if (a > b)
		return b;
	else if (a < b)
		return a;
	else
		return b;
}

template<typename T>
T max(T a, T b)
{
	if (a > b)
		return a;
	else if (a < b)
		return b;
	else
		return b;
}
