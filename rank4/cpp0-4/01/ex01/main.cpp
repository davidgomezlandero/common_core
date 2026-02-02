/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 21:09:39 by davigome          #+#    #+#             */
/*   Updated: 2025/05/19 18:20:58 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include "Zombie.hpp"

int main(void)
{
	Zombie *zombies;

	zombies = zombieHorde(4, "erSombie");
	for (int i = 0; i < 4; ++i)
	{
		std::cout << "Zombie: " << i + 1;
		zombies[i].announce();
	}	
	delete[] zombies;
	return (0);
}
