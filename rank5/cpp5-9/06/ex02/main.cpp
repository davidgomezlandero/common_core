 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 10:56:41 by davigome          #+#    #+#             */
/*   Updated: 2025/06/17 08:07:56 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include <cstdlib>
#include <ctime>

Base *generate(void)
{
	std::srand(std::time(NULL));
	int r = std::rand() % 3;
	switch(r){
		case 0:
			{
				std::cout << "Base A"<< std::endl;
				 return new A();
			}
		case 1:
			{
				std::cout << "Base B"<< std::endl;
				 return new B();
			}
		default:
			{
				std::cout << "Base C"<< std::endl;
				 return new C();
			}
	}
}

void identify(Base *p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
}

void identify(Base &p)
{
	try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    } catch (std::exception &e) {}

    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    } catch (std::exception &e) {}

    try {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return;
    } catch (std::exception &e) {}
}

int main(void)
{
	Base *p = generate();

	std::cout << "Identify Base *p" << std::endl;
	identify(p);


	std::cout << "Identify Base &p" << std::endl;
	identify(*p);
	delete p;
	return 0;
}