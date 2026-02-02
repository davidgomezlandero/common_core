/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:39:23 by davigome          #+#    #+#             */
/*   Updated: 2025/05/28 19:12:04 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include <iostream>

/* int main( void )
{
	ClapTrap pepe("pepe"), manue("manue");

	pepe.attack("manue");
	pepe.beRepaired(4);
	pepe.takeDamage(3);
} */

int main() {
    // 1) Constructor parametrizado
    ClapTrap hero("Hero");

    // 2) Prueba de attack, takeDamage y beRepaired
    hero.attack("Monster");
    hero.takeDamage(5);
    hero.beRepaired(3);

    // Mostrar estado interno con los getters
    std::cout
        << "HP: "  << hero.getHitPoints()
        << ", EP: " << hero.getEnergyPoints()
        << std::endl;

    std::cout << "--------------------------" << std::endl;

    // 3) Constructor de copia
    ClapTrap heroCopy(hero);

    // 4) Operador de asignación
    ClapTrap heroAssigned;
    heroAssigned = hero;

    // Mostrar que copia y asignación replican el estado
    std::cout
        << "Copy HP:     " << heroCopy.getHitPoints()
        << ", EP: "      << heroCopy.getEnergyPoints()
        << std::endl;
    std::cout
        << "Assigned HP: " << heroAssigned.getHitPoints()
        << ", EP: "      << heroAssigned.getEnergyPoints()
        << std::endl;

    return 0;
}