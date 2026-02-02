/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:23:02 by davigome          #+#    #+#             */
/*   Updated: 2025/05/22 19:07:58 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>
#include <string>

class Weapon{

	private:
		std::string type;

	public:
		Weapon(std::string type);
		~Weapon();
		void	setType(std::string type);
		const std::string &getType();
		
};

#endif