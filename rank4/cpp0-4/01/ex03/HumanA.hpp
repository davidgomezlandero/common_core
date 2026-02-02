/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:22:48 by davigome          #+#    #+#             */
/*   Updated: 2025/05/22 19:09:35 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
#define HUMANA_HPP

#include <iostream>
#include <string>
#include "Weapon.hpp"

class HumanA{

	private:

		std::string _name;
		Weapon &_weapon;
	public:
		HumanA(std::string _name, Weapon &_weapon);
		void attack();
		~HumanA();
};

#endif