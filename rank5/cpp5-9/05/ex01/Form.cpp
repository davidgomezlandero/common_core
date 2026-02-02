/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:52:53 by davigome          #+#    #+#             */
/*   Updated: 2025/06/15 09:44:24 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"


Form::Form() : _name("Default"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150)
{
	std::cout << _name << " Form default constructor called." << std::endl;
}

Form::Form(std::string name, int gradeToSign, int gradeToExecute) : _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	if (_gradeToExecute < 1 || _gradeToSign < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (_gradeToSign > 150 || _gradeToExecute > 150)
		throw Bureaucrat::GradeTooLowException();
}

Form::Form(const Form &other) : _name(other._name) , _isSigned(other._isSigned), _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{
	std::cout << "Form copy constructor called" << std::endl;
}

Form	&Form::operator=(const Form &other)
{
	std::cout << "Form asignator operator called." << std::endl;
	if (this != &other)
		this->_isSigned = other._isSigned;
	return *this;
}

Form::~Form()
{
	std::cout << "Form destructor called" << std::endl;
}

const std::string	Form::getName() const
{
	return _name;
}

int Form::getGradeToSign() const
{
	return _gradeToSign;
}

int Form::getGradeToExecute() const
{
	return _gradeToExecute;
}

bool Form::getIsSigned() const
{
	return _isSigned;
}

const char* Form::GradeTooHighException::what() const throw()
{
	return "Grade is too high!";
}

const char* Form::GradeTooLowException::what() const throw()
{
	return "Grade is too low";
}

void	Form::beSigned(Bureaucrat &other)
{
	if (other.getGrade() <= this->getGradeToSign())
		this->_isSigned = true;
	else
		throw Form::GradeTooLowException();
}

std::ostream& operator<<(std::ostream& stream, const Form& b) {
	stream << b.getName() << ", Form grade to sign and to execute are " << b.getGradeToSign() << " and " << b.getGradeToExecute() << ". Finally, the Form is signed: " << b.getIsSigned() << ".";
    return stream;
}