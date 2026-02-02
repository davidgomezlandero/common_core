/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:39:23 by davigome          #+#    #+#             */
/*   Updated: 2025/05/27 08:22:04 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main() {
    std::cout << "=== Pruebas de ClapTrap ===" << std::endl;
    ClapTrap clap("CL4P-TP");
    clap.attack("bandido");
    clap.takeDamage(5);
    clap.beRepaired(3);
    std::cout << "-- Agotando energía de ClapTrap --" << std::endl;
    for (int i = 0; i < 11; ++i) // consume 11 puntos; el último debe fallar
        clap.attack("objetivo");

    std::cout << "\n=== Pruebas de ScavTrap ===" << std::endl;
    ScavTrap scav("SC4V-TP");
    scav.attack("intruso");
    scav.takeDamage(25);
    scav.beRepaired(10);
    scav.guardGate();
    std::cout << "-- Agotando energía de ScavTrap --" << std::endl;
    for (int i = 0; i < 51; ++i) // consume 51 puntos; el último debe fallar
        scav.attack("objetivo");

    std::cout << "\n=== Pruebas de FragTrap ===" << std::endl;
    FragTrap frag("FR4G-TP");
    frag.attack("enemigo");
    frag.takeDamage(50);
    frag.beRepaired(20);
    frag.highFivesGuys();
    std::cout << "-- Agotando energía de FragTrap --" << std::endl;
    for (int i = 0; i < 101; ++i) // consume 101 puntos; el último debe fallar
        frag.attack("objetivo");

    return 0;
}

