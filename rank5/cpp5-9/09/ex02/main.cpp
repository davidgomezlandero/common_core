/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:16:48 by davigome          #+#    #+#             */
/*   Updated: 2025/07/04 10:21:20 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	std::string nums;
	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	for (int i = 1; i < argc; i++)
	{
		std::istringstream iss(argv[i]);
		std::string token;
		if (!(iss >> token))
		{
			std::cerr << "Error" << std::endl;
			return 1;
		}
		nums += argv[i];
		if (i < argc - 1)
			nums += " ";
	}
	try{
		PmergeMe merge(nums);

		merge.mergeDeque();
		merge.mergeVector();
		merge.showUnsorted(nums);
		merge.sorted();
		merge.showDequeTime();
		merge.showVectorTime();
	}catch(std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}