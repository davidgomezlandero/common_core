/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:52:53 by davigome          #+#    #+#             */
/*   Updated: 2025/06/15 09:56:20 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"


AForm::AForm() : _name("Default"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150)
{
}

AForm::AForm(std::string name, int gradeToSign, int gradeToExecute) : _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	if (_gradeToExecute < 1 || _gradeToSign < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (_gradeToSign > 150 || _gradeToExecute > 150)
		throw Bureaucrat::GradeTooLowException();
}

AForm::AForm(const AForm &other) : _name(other._name) , _isSigned(other._isSigned), _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{
}

AForm	&AForm::operator=(const AForm &other)
{
	if (this != &other)
		this->_isSigned = other._isSigned;
	return *this;
}

AForm::~AForm()
{
}

const std::string	AForm::getName() const
{
	return _name;
}

int AForm::getGradeToSign() const
{
	return _gradeToSign;
}

int AForm::getGradeToExecute() const
{
	return _gradeToExecute;
}

bool AForm::getIsSigned() const
{
	return _isSigned;
}

const char* AForm::GradeTooHighException::what() const throw()
{
	return "Grade is too high!";
}

const char* AForm::GradeTooLowException::what() const throw()
{
	return "Grade is too low";
}

const char* AForm::FormNotSigned::what() const throw()
{
	return "Cannot execute the form because is not signed yet";
}

void	AForm::beSigned(Bureaucrat &other)
{
	if (other.getGrade() <= this->getGradeToSign())
		this->_isSigned = true;
	else
		throw AForm::GradeTooLowException();
}

std::ostream& operator<<(std::ostream& stream, const AForm& b) {
	stream << b.getName() << ", AForm grade to sign and to execute are " << b.getGradeToSign() << " and " << b.getGradeToExecute() << ". Finally, the AForm is signed: " << b.getIsSigned() << ".";
    return stream;
}

void AForm::execute(Bureaucrat const & executor) const
{
	if (executor.getGrade() > this->getGradeToExecute())
		throw AForm::GradeTooLowException();
	if (!this->getIsSigned())
		throw AForm::FormNotSigned();
}