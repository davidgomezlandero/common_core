/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:22:54 by davigome          #+#    #+#             */
/*   Updated: 2025/05/22 19:08:50 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
#define HUMANB_HPP

#include <iostream>
#include <string>
#include "Weapon.hpp"

class HumanB{

	private:

		std::string _name;
		Weapon *_weapon;
	public:
		HumanB(std::string _name);
		void setWeapon(Weapon &_weapon);
		void attack();
		~HumanB();
};

#endif