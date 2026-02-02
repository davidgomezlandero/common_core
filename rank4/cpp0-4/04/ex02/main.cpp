/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:01:04 by davigome          #+#    #+#             */
/*   Updated: 2025/05/29 19:41:42 by davigome         ###   ########.fr       */
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
	//const Animal *meta = new Animal();
	const Animal *dog = new Dog();
	const Animal *cat = new Cat();
	const WrongAnimal *wrongAnimal = new WrongAnimal();
	const WrongAnimal *wrongCat = new WrongCat();

	/* std::cout << "---------Animals thinks----------\n";
	std::cout << meta->getType() << std::endl;
	meta->makeSound();  */

	std::cout << "---------Dog thinks-------------\n";
	std::cout << dog->getType() << std::endl;
	dog->makeSound();
	
	std::cout << "---------Cat thinks-------------\n";
	std::cout << cat->getType() << std::endl;
	cat->makeSound();
	
	std::cout << "--------WrongAnimal thinks------\n";
	std::cout << wrongAnimal->getType() << std::endl;
	wrongAnimal->makeSound();

	std::cout << "---------WrongCat thinks---------\n";
	std::cout << wrongCat->getType() << std::endl;
	wrongCat->makeSound();
	
/* 	delete meta; */
	delete dog;
	delete cat;
	delete wrongAnimal;
	delete wrongCat;
}


/* int main(void)
{
	int n = 10;
	Animal *animals[n];

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
} */