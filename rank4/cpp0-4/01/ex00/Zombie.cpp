/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 21:10:10 by davigome          #+#    #+#             */
/*   Updated: 2025/05/19 17:44:35 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(std::string name){
	this->name = name;
};

void	Zombie::announce(){
	std::cout << this->name << ": BraiiiiiiinnnzzzZ..." <<std::endl;
};


Zombie::~Zombie(){
	std::cout << this->name << " zombie was deleted" << std::endl;
};
