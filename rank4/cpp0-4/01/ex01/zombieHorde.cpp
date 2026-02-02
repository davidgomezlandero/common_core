/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:53:50 by davigome          #+#    #+#             */
/*   Updated: 2025/05/19 18:14:20 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* zombieHorde( int N, std::string name)
{
	Zombie *zombies = new Zombie[N];
	
	for (int i = 0; i < N; ++i)
	{
		zombies[i].setName(name);
	}
	return (zombies);
};
