/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:39:23 by davigome          #+#    #+#             */
/*   Updated: 2025/06/11 12:04:33 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"
#include <iostream>

int main() {
    std::cout << "----- Creando ScavTrap Alice -----\n";
    ScavTrap alice("Alice");

    std::cout << "\n----- Acción: atacar, recibir daño y reparar -----\n";
    alice.attack("Bob");
    alice.takeDamage(20);
    alice.beRepaired(10);

    std::cout << "\n----- Acción: guardGate -----\n";
    alice.guardGate();

    std::cout << "\n----- Constructor de copia -----\n";
    ScavTrap copyAlice(alice);

    std::cout << "\n----- Operador de asignación -----\n";
    ScavTrap assigned("Temp");
    assigned = alice;

    std::cout << "\n----- Saliendo de main (destrucción) -----\n";
    return 0;
}
