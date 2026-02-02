/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 21:09:57 by davigome          #+#    #+#             */
/*   Updated: 2025/05/19 17:44:22 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>
#include <iostream>

class Zombie{
	private:
	std::string name;

	public:
	Zombie(std::string name);
	void announce(void);
	~Zombie();
};

Zombie* newZombie( std::string name );
void randomChump( std::string name );

#endif