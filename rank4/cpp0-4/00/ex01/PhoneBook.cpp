/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:50:24 by davigome          #+#    #+#             */
/*   Updated: 2025/05/19 12:06:20 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>

PhoneBook::PhoneBook(){
	contactCount = 0;
}

void PhoneBook::addContact(){
	Contact newContact;

	newContact.setFirstName();
	newContact.setLastName();
	newContact.setNickName();
	newContact.setPhoneNumber();
	newContact.setDarkestSecret();
	
	int index = contactCount % 8;
	
	contacts[index] = newContact;
	contactCount++;
}

void PhoneBook::searchContacts() const{
	
	int size = 0;
	std::string aux;
	
	if (contactCount == 0)
	{
		std::cout << "PhoneBook is empty" << std::endl;
		return ;
	}
	
	if (contactCount > 8)
		size = 8;
	else
		size = contactCount;

	std::cout << std::setw(10) << "Index" << "|"
				<< std::setw(10) << "First Name" << "|"
				<< std::setw(10) << "Last Name" << "|"
				<< std::setw(10) << "Nickname" << "|" << std::endl;
	
	for (int i = 0; i < size; i++)
	{
		std::cout<< std::setw(10)<< i+1 << "|";
		aux = contacts[i].getFirstName();
		if (aux.length() > 10)
		{
			aux = aux.substr(0, 8);
			std::cout << std::setw(9)<< aux << ".|";
		}
		else
			std::cout<< std::setw(10) << aux << "|";
		aux = contacts[i].getLastName();
		if (aux.length() > 10)
		{
			aux = aux.substr(0, 8);
			std::cout << std::setw(9)<< aux << ".|";
		}
		else
			std::cout<< std::setw(10)<< aux << "|";
		
		aux = contacts[i].getNickName();
		if (aux.length() > 10)
		{
			aux = aux.substr(0, 8);
			std::cout<< std::setw(9) << aux << ".|"<< std::endl;
		}
		else
			std::cout << std::setw(10)<< aux << std::endl;
	}
	std::cout << "Specify the index of the contact:"<<std::endl;
	if(!std::getline(std::cin, aux))
		exit(0);
	std::stringstream ss(aux);
	int i;
	ss >> i;
	
	if (i > contactCount || i < 1 || i > 8)
		std::cout<< "Error" << std::endl;
	else
	{
		std::cout << "First name: "<<contacts[i - 1].getFirstName()<<std::endl;
		std::cout << "Last name : "<<contacts[i - 1].getLastName()<<std::endl;
		std::cout << "Nickname : "<<contacts[i - 1].getNickName()<<std::endl;
		std::cout << "Phone number: "<<contacts[i- 1].getPhoneNumber()<<std::endl;
		std::cout << "Darckest secret: "<<contacts[i-1].getDarkestSecret()<<std::endl;
	}
}