/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 07:41:25 by davigome          #+#    #+#             */
/*   Updated: 2025/05/27 08:16:54 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap()
{
	std::cout << "FragTrap default constructor called" << std::endl;
	this->setHitPoints(100);
	this->setEnergyPoints(100);
	this->setAttackDamage(30);
}

FragTrap::FragTrap(const std::string &_name) : ClapTrap(_name)
{
	std::cout << "FragTrap constructor for " << this->getName() << " called." << std::endl;
	this->setHitPoints(100);
	this->setEnergyPoints(100);
	this->setAttackDamage(30);
}

FragTrap::FragTrap(const FragTrap& src) : ClapTrap(src)
{
	std::cout << "FragTrap copy constructor called." << std::endl;
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap default destructor called." << std::endl;
}

void FragTrap::highFivesGuys(void) const{
	std::cout << "FragTrap " << this->getName() << " says: Give me five!" << std::endl;
}
