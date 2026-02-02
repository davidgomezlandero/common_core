/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:32:59 by davigome          #+#    #+#             */
/*   Updated: 2025/05/19 18:21:21 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main(int argc, char **argv)
{
	if (argc == 1)
		std::cout << "\033[34m* LOUD AND UNBEARABLE FEEDBACK NOISE *\033[0m" << std::endl;
	else
	{
		for (int i = 1; i < argc; ++i )
		{
			std::string arg(argv[i]);
			for (size_t j = 0; j < arg.length(); j++)
				std::cout << (char)std::toupper(arg[j]);
		}
		std::cout << std::endl;
	}
	return (0);
}
