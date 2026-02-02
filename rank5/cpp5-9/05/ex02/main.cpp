/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:50:29 by davigome          #+#    #+#             */
/*   Updated: 2025/06/15 16:46:55 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main() {
    std::cout << "\n=== Creating Bureaucrats ===\n";
    Bureaucrat high("HighRank", 1);
    Bureaucrat mid("MidRank", 50);
    Bureaucrat low("LowRank", 150);

    std::cout << high << std::endl;
    std::cout << mid << std::endl;
    std::cout << low << std::endl;

    std::cout << "\n=== Creating Forms ===\n";
    ShrubberyCreationForm shrubbery("garden");
    RobotomyRequestForm robotomy("marvin");
    PresidentialPardonForm pardon("arthur");

    std::cout << shrubbery << std::endl;
    std::cout << robotomy << std::endl;
    std::cout << pardon << std::endl;

    std::cout << "\n=== Trying to sign forms with low rank ===\n";
    low.signAForm(shrubbery);
    low.signAForm(robotomy);
    low.signAForm(pardon);

    std::cout << "\n=== Signing forms with appropriate rank ===\n";
    mid.signAForm(shrubbery);
    mid.signAForm(robotomy);
    high.signAForm(pardon); // Needs high grade

    std::cout << "\n=== Trying to execute forms with low rank ===\n";
    try { low.executeForm(shrubbery); }
    catch (const std::exception &e) { std::cerr << e.what() << std::endl; }

    try { low.executeForm(robotomy); }
    catch (const std::exception &e) { std::cerr << e.what() << std::endl; }

    try { low.executeForm(pardon); }
    catch (const std::exception &e) { std::cerr << e.what() << std::endl; }

    std::cout << "\n=== Executing forms with sufficient rank ===\n";
    try { mid.executeForm(shrubbery); }
    catch (const std::exception &e) { std::cerr << e.what() << std::endl; }

    try { mid.executeForm(robotomy); }
    catch (const std::exception &e) { std::cerr << e.what() << std::endl; }

    try { high.executeForm(pardon); }
    catch (const std::exception &e) { std::cerr << e.what() << std::endl; }

    std::cout << "\n=== Executing already executed or repeated ===\n";
    try { high.executeForm(pardon); }
    catch (const std::exception &e) { std::cerr << e.what() << std::endl; }

    return 0;
}

