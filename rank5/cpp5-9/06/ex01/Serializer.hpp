/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 07:54:52 by davigome          #+#    #+#             */
/*   Updated: 2025/06/17 08:25:49 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

typedef unsigned long uintptr_t;

struct Data
{
	int 		i;
	std::string str;
	char		c;	
};

class Serializer
{
	public: 
		static uintptr_t	serialize(Data* ptr);
		static Data			*deserialize(uintptr_t raw);
	
	private:
		Serializer();
		Serializer &operator=(const Serializer &other);
		Serializer(const Serializer &other);
		~Serializer();
};