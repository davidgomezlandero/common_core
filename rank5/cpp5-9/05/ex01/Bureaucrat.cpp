/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:51:06 by davigome          #+#    #+#             */
/*   Updated: 2025/06/15 18:42:57 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : _name("Default") , _grade(150)
{
	std::cout << _name <<" Default Bureaucrat constructor called" << std::endl;
}

Bureaucrat::Bureaucrat(std::string name, int grade) : _name(name)
{
	std::cout << "Parametric constructor called" << std::endl;
	if (grade < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
	this->_grade = grade;
}

Bureaucrat	&Bureaucrat::operator=(const Bureaucrat &other)
{
	std::cout << "Bureaucrat copy assignator called" << std::endl;
	if (this != &other)
		this->_grade = other._grade;
	return *this;
}

Bureaucrat::Bureaucrat(const Bureaucrat &other)
{
	std::cout << "Bureaucrat copy constructor called" << std::endl;
	if (this != &other)
		*this = other;
}
Bureaucrat::~Bureaucrat()
{
	std::cout << _name <<" Bureaucrat destructor called" << std::endl;
}

void	Bureaucrat::incrementGrade()
{
	if (this->_grade - 1 <= 0)
		throw Bureaucrat::GradeTooHighException();
	else
		--this->_grade;
}

void	Bureaucrat::decrementGrade()
{
	if (this->_grade + 1 > 150)
		throw Bureaucrat::GradeTooLowException();
	else
		++this->_grade;
}


const char* Bureaucrat::GradeTooHighException::what() const throw()
{
	return "Grade is too high!";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
	return "Grade is too low";
}

const std::string Bureaucrat::getName() const{
	return this->_name;
}

int	Bureaucrat::getGrade() const
{
	return this->_grade;
}

std::ostream& operator<<(std::ostream& stream, const Bureaucrat& b) {
	stream << b.getName() << ", bureaucrat grade " << b.getGrade() << ".";
    return stream;
}

void	Bureaucrat::signForm(Form &other)
{
	if (this->_grade <= other.getGradeToSign() && other.getIsSigned() == false)
	{
		std::cout << this->_name << " signed " << other.getName() << std::endl;
		other.beSigned(*this);
	}
	else
		std::cerr << _name << " couldn't sign " << other.getName() << " because the bureaucrat has not enough grade and/or the form is signed." << std::endl;
}