/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:15:38 by davigome          #+#    #+#             */
/*   Updated: 2025/07/10 08:35:48 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "RPN.hpp"

int main(int argc,  char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}
	std::string nums(argv[1]);
	try{
		RPN calculator(nums);
		calculator.calculator();
	}catch(std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return 0;
}