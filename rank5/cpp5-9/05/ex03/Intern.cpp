/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:14:24 by davigome          #+#    #+#             */
/*   Updated: 2025/06/15 18:40:30 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern()
{
	
}
Intern::Intern(const Intern &other)
{
	(void)other;
}
Intern &Intern::operator=(const Intern &other)
{
	if (this != &other)
	{
		
	}
	return *this;
}
Intern::~Intern()
{
	
}

static AForm *createPresidentialPardonForm(const std::string target)
{
	return new PresidentialPardonForm(target);
}

static AForm *createRobotomyRequestForm(const std::string target)
{
	return new RobotomyRequestForm(target);
}

static AForm *createShrubberyCreationForm(const std::string target)
{
	return new ShrubberyCreationForm(target);
}

typedef AForm *(*formCreationFunction)(const std::string target);

AForm	*Intern::makeForm(std::string name, std::string target)
{
	AForm *form = NULL;

	const std::string names[] = {"robotomy request", "presidential pardon", "shrubbery creation"};
	formCreationFunction creators[] = {createRobotomyRequestForm, createPresidentialPardonForm, createShrubberyCreationForm};
	
	for (int i = 0; i < 3; i++)
	{
		if (names[i] == name)
		{
			std::cout << "Intern creates " << name << std::endl;
			form = creators[i](target);
			break;
		}
	}
	if (form == NULL)
		std::cerr << "Intern cannot create " << name << std::endl;
	return form;
}