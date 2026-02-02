/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:50:29 by davigome          #+#    #+#             */
/*   Updated: 2025/06/13 16:46:43 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bureaucrat.hpp"


int main()
{
	 Bureaucrat	pepe("pepe", 55);
	std::cout << pepe << std::endl;

	try {
		Bureaucrat manuel("manuel", 200);
	} catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl << std::endl ;
	}
	try {
		Bureaucrat jose("jose", 0);
	} catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl << std::endl;
	}
	try {
		Bureaucrat maria("maria", 23);
		maria.decrementGrade();
		std::cout << maria << std::endl << std::endl; 
	} catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	try {
		Bureaucrat jose("jose", 1);
		jose.incrementGrade();
		std::cout << jose << std::endl; 
	} catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl << std::endl;
	}
	try {
		Bureaucrat paco("paco", 150);
		paco.decrementGrade();
		std::cout << paco << std::endl; 
	} catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}