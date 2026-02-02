/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:50:29 by davigome          #+#    #+#             */
/*   Updated: 2025/06/15 18:47:02 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "Bureaucrat.hpp"

int main() {
    std::cout << "=== Creating Intern ===" << std::endl;
    Intern someRandomIntern;

    std::cout << "\n=== Creating Bureaucrats ===" << std::endl;
    Bureaucrat high("HighRank", 1);
    Bureaucrat mid("MidRank", 50);
    Bureaucrat low("LowRank", 150);

    std::cout << high << std::endl;
    std::cout << mid << std::endl;
    std::cout << low << std::endl;

    std::cout << "\n=== Intern creates valid forms ===" << std::endl;
    AForm *shrub = someRandomIntern.makeForm("shrubbery creation", "garden");
    AForm *robot = someRandomIntern.makeForm("robotomy request", "marvin");
    AForm *pardon = someRandomIntern.makeForm("presidential pardon", "arthur");

    std::cout << "\n=== Intern attempts to create invalid form ===" << std::endl;
    AForm *unknown = someRandomIntern.makeForm("galactic invasion", "earth");

    std::cout << "\n=== Signing and executing forms ===" << std::endl;

    if (shrub) {
        mid.signAForm(*shrub);
        mid.executeForm(*shrub);
        delete shrub;
    }

    if (robot) {
        mid.signAForm(*robot);
        try {
            mid.executeForm(*robot); // Should fail: mid's grade is 50, robot requires 45
        } catch (std::exception &e) {
            std::cerr << "Execution failed: " << e.what() << std::endl;
        }
        high.executeForm(*robot); // Should succeed
        delete robot;
    }

    if (pardon) {
        high.signAForm(*pardon);
        high.executeForm(*pardon);
        delete pardon;
    }

    if (unknown)
        delete unknown;

    std::cout << "\n=== End of tests ===" << std::endl;
    return 0;
}
