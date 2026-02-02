/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:04:17 by davigome          #+#    #+#             */
/*   Updated: 2025/06/15 16:30:51 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreationForm", 145, 137) 
{
	_target =  "DEFAULT";
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : AForm("ShrubberyCreationForm", 145, 137) 
{
	_target = target;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other) : AForm(other), _target(other._target)
{	
}
ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		this->_target = other._target;
	}
	return *this;
}

std::string ShrubberyCreationForm::getTarget() const
{
	return _target;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

void	ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	AForm::execute(executor);
	
	std::ofstream out((this->getTarget() + "_shrubbery").c_str());
    if (!out.is_open()) {
        std::cerr << "Error:cannot open the file." << std::endl;
        return;
    }

    out << "       # #### #### ##           \n"
        << "     ### \\/#|###|/####         \n"
        << "    ##\\/#/ \\||/##/_/##/#      \n"
        << "  ###  \\/###|/ \\/ # #####     \n"
        << " ##_\\_#\\_\\##|#/###_/_####    \n"
        << "## #### # \\ #|/#### ##/##      \n"
        << " __#_--###` |{,###---###~       \n"
        << "          \\ }{                 \n"
        << "           }}{                  \n"
        << "           }}{                  \n"
        << "          {{{}}                 \n"
        << "     ,_-=-~{ .-^- _:)           \n";

    out.close();
}
