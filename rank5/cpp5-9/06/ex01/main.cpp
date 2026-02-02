 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 10:56:41 by davigome          #+#    #+#             */
/*   Updated: 2025/06/17 08:07:56 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int main(void)
{
	Data data;
	uintptr_t raw;
	Data *post;

	std::cout << "---------Data before serialize---------" << std::endl;
	data.c = 'a';
	data.i = 23;
	data.str = "Hola cara cola";
	std::cout << "Char: " << data.c << std::endl << "Int: " << data.i << std::endl << "String: " << data.str << std::endl;
	raw = Serializer::serialize(&data);
	post = Serializer::deserialize(raw);
	std::cout << "---------Data after serialize---------" << std::endl;
	std::cout << "Char: " << post->c << std::endl << "Int: " << post->i << std::endl << "String: " << post->str << std::endl;
	return 0;
}