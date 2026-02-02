/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:49:37 by davigome          #+#    #+#             */
/*   Updated: 2025/05/19 12:06:05 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"
#include <iostream>
#include <cstdlib>

void Contact::setFirstName(){
	std::string input;
	
	do{
    std::cout << "First name: " << std::endl;
	if (!std::getline(std::cin, input))
		exit(0);
	if (input.empty())
			std::cout << "This field cannot be empty. Please try again." << std::endl;
	} while (input.empty());
	FirstName = input;
}

std::string Contact::getFirstName() const {
	return FirstName;
}

void Contact::setLastName(){
	std::string input;

	do{
    std::cout << "Last name: " << std::endl;
	if (!std::getline(std::cin, input))
		exit(0);
	if (input.empty())
			std::cout << "This field cannot be empty. Please try again." << std::endl;
	} while (input.empty());
	LastName = input;
}

std::string Contact::getLastName() const {
	return LastName;
}

void Contact::setNickName(){
	std::string input;

	do{
    std::cout << "Nick name: " << std::endl;
	if (!std::getline(std::cin, input))
		exit(0);
	if (input.empty())
			std::cout << "This field cannot be empty. Please try again." << std::endl;
	} while (input.empty());
	NickName = input;
}

std::string Contact::getNickName() const {
	return NickName;
}

int flag = -1;

void Contact::setPhoneNumber(){
	std::string input;

	do{
    std::cout << "Phone number: " << std::endl;
	if (!std::getline(std::cin, input))
		exit(0);
	if (input.empty())
			std::cout << "This field cannot be empty. Please try again." << std::endl;
	int i = -1;
	flag = -1;
	while (!input.empty() && input[++i])
	{
		if (input[i] > '9' || input[i] < '0')
		{
			std::cout << "The phone number only has numbers" << std::endl;
			flag = 0;
			break;
		}
	}
	} while (input.empty() || flag == 0);
	PhoneNumber = input;
}

std::string Contact::getPhoneNumber() const {
	return PhoneNumber;
}

void Contact::setDarkestSecret(){
	std::string input;

	do{
    std::cout << "Darkest secret: " << std::endl;
	if (!std::getline(std::cin, input))
		exit(0);
	if (input.empty())
			std::cout << "This field cannot be empty. Please try again." << std::endl;
	} while (input.empty());
	DarkestSecret = input;
}

std::string Contact::getDarkestSecret() const {
	return DarkestSecret;
}