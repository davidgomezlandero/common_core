/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:27:41 by davigome          #+#    #+#             */
/*   Updated: 2025/05/19 19:17:41 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main(void)
{
	std::string zombie = "HI THIS IS BRAIN";
	
	std::string* stringPTR = &zombie;
	std::string& stringREF = zombie;

	std::cout << "Adress of the string variable: " << &zombie <<std::endl;
	std::cout << "Memory address held by stringPTR: "<< stringPTR << std::endl;
	std::cout << "Memory address held by stringREF: "<< &stringREF << std::endl;

	std::cout << "The value of the string variable: "<< zombie << std::endl;
	std::cout << "The value pointed to by stringPTR: "<< *stringPTR << std::endl;
	std::cout << "The value pointed to by stringREF: "<< stringREF << std::endl;

	return (0);
}