/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:18:51 by davigome          #+#    #+#             */
/*   Updated: 2025/05/19 18:21:31 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "PhoneBook.hpp"

int main() {
   
	PhoneBook PhoneBook;
	std::string aux;
	
	while (1)
	{
		std::cout << "Say the next action: EXIT, ADD or SEARCH:"<< std::endl;
		if (!std::getline(std::cin, aux) || aux == "EXIT")
			break;
		else if (aux == "ADD")
			PhoneBook.addContact();
		else if (aux == "SEARCH")
			PhoneBook.searchContacts();
		else
			std::cout << "Not valid command" << std::endl;
	}
	return (0);
}