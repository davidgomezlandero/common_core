/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:39:54 by davigome          #+#    #+#             */
/*   Updated: 2025/05/28 10:23:29 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(std::string _name) : _name(_name),_hitPoints(10),  _energyPoints(10), _attackDamage(0) 
{
	std::cout << "Default constructor called for " << this->getName() << std::endl;
}

ClapTrap::ClapTrap()
{
	std::cout << "Default constructor called." << std::endl;
	this->_name = "name";
	this->_hitPoints = 10;
	this->_energyPoints = 10;
	this->_attackDamage = 0;
}

ClapTrap::~ClapTrap(){
	std::cout << "Default destructor called for ClapTrap."<< std::endl;
}

std::string	ClapTrap::getName(void) const{
	return (this->_name);
}

ClapTrap::ClapTrap(const ClapTrap &src)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = src;
}

int ClapTrap::getHitPoints(void) const
{
	return this->_hitPoints;
}
int	ClapTrap::getEnergyPoints(void) const
{
	return this->_energyPoints;
}
int ClapTrap::getAttackDamage(void) const
{
	return this->_attackDamage;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& src)
{
	std::cout << "Copy assigment operator called" << std::endl;
	if (this != &src)
	{
		this->_name = src.getName();
		this->_hitPoints = src.getHitPoints();
		this->_energyPoints = src.getEnergyPoints();
		this->_attackDamage = src.getAttackDamage();
	}
	return *this;
 }
 
 void ClapTrap::attack(const std::string &target)
 {
	if (this->_energyPoints == 0 || this->_hitPoints <= 0)
	{
		std::cout << this->_name  << " can't do anything because has not any energy point or hit point" << std::endl;
		return ;
	}
	else
	{
		--this->_energyPoints;
		std::cout << this->_name << " attacks " << target << " and has this points left " << this->_energyPoints << std::endl;
	}
 }
 
void ClapTrap::takeDamage(unsigned int amount)
{
	if (this->_energyPoints == 0 || this->_hitPoints <= 0)
	{
		std::cout << this->_name  << " can't do anything because has not any energy point or hit point" << std::endl;
		return ;
	}
	this->_hitPoints -= amount;
	std::cout << this->_name << " has taken damage and has " << this->_hitPoints << " left." << std::endl; 
}
void ClapTrap::beRepaired(unsigned int amount)
{
	if (this->_energyPoints == 0 || this->_hitPoints <= 0)
	{
		std::cout << this->_name  << " can't do anything because has not any energy point or hit point" << std::endl;
		return ;
	}
	else
	{
		--this->_energyPoints;
		this->_hitPoints += amount;
		std::cout << this->_name << " has repaired  " << amount << " points" << " and now has this points " << this->getHitPoints() << std::endl;
	}
}

void ClapTrap::setHitPoints(int points)
{
	this->_hitPoints = points;
}
void ClapTrap::setEnergyPoints(int points)
{
	this->_energyPoints = points;
}
void ClapTrap::setAttackDamage(int points)
{
	this->_attackDamage = points;
}