/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:41:38 by davigome          #+#    #+#             */
/*   Updated: 2025/07/10 08:35:12 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (1);
	}
	try {
		std::string input(argv[1]);
		BitcoinExchange exchange(input);
	}catch(std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return 0;
}