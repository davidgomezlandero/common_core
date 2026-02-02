/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 21:09:39 by davigome          #+#    #+#             */
/*   Updated: 2025/05/19 18:21:09 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include "Zombie.hpp"

int main(void)
{
	Zombie *zombie;

	zombie = newZombie("Elpepe");
	
	std::cout << "Random zombie announce."<< std::endl;
	randomChump("Manue");
	std::cout << "Now the zombie with reserved memory" << std::endl;
	zombie->announce();
	delete zombie;
	return (0);
}
