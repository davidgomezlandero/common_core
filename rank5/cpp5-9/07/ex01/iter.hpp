/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:14:09 by davigome          #+#    #+#             */
/*   Updated: 2025/06/28 10:51:23 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

template<typename T>
void iter(T *array, size_t length, void (*func)(T const &))
{
	for (size_t i = 0; i < length ; i++)
		func(array[i]);
}

template<typename T>
void iter(T *array, size_t length, void (*func)(T &))
{
	for (size_t i = 0; i < length ; i++)
		func(array[i]);
}