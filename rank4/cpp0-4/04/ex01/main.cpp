/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:01:04 by davigome          #+#    #+#             */
/*   Updated: 2025/05/29 20:16:28 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main(void)
{
	int n = 10;
	Animal *animals[n];
	Animal *zoo[2];
	std::cout << "------Copy constructor and correct deep copy.------" << std::endl;
	zoo[0] = new Cat();
	zoo[1] = new Cat(*dynamic_cast<Cat*>(zoo[0]));
	delete zoo[0];
	delete zoo[1];

	std::cout << "-----End of deletes from copy constructor-----" << std::endl;
	
	int i = -1;
	while (++i < n)
	{
		std::cout << "Animal " << i << std::endl << std::endl;
		if (i < n/2)
			animals[i] = new Dog();
		else
			animals[i] = new Cat();
		std::cout << std::endl;
	}
	i = -1;
	while(++i < n)
		delete animals[i];
}