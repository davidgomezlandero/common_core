/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:39:17 by davigome          #+#    #+#             */
/*   Updated: 2025/05/27 12:26:06 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Fixed.hpp"

/* int main( void ) {
	Fixed a;
	Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << Fixed::max( a, b ) << std::endl;
	return (0);
} */

int main() {
    // Inicialización desde int
    Fixed a(1);
    // Inicialización desde int
    Fixed b(2);

    std::cout << std::boolalpha;  // para imprimir true/false
    std::cout << "=== Comparisons ===\n";
    std::cout << "a = " << a << ", b = " << b << "\n";
    std::cout << "a <  b: " << (a <  b) << "\n";
    std::cout << "a >  b: " << (a >  b) << "\n";
    std::cout << "a <= b: " << (a <= b) << "\n";
    std::cout << "a >= b: " << (a >= b) << "\n";
    std::cout << "a == b: " << (a == b) << "\n";
    std::cout << "a != b: " << (a != b) << "\n\n";

    std::cout << "=== Arithmetic ===\n";
    std::cout << "a + b = " << (a + b) << "\n";
    std::cout << "a - b = " << (a - b) << "\n";
    std::cout << "a * b = " << (a * b) << "\n";
    std::cout << "b / a = " << (b / a) << "\n\n";

    std::cout << "=== Increment/Decrement ===\n";
    std::cout << "Initial a: " << a << "\n";
    std::cout << "++a = "    << ++a << "\n";
    std::cout << "a++ = "    <<  a++ << "\n";
    std::cout << "Now a = "  <<   a << "\n\n";

    std::cout << "Initial b: " << b << "\n";
    std::cout << "--b = "    << --b << "\n";
    std::cout << "b-- = "    <<  b-- << "\n";
    std::cout << "Now b = "  <<   b << "\n\n";

    std::cout << "=== Min / Max ===\n";
    std::cout << "min(a, b) = " << Fixed::min(a, b) << "\n";
    std::cout << "max(a, b) = " << Fixed::max(a, b) << "\n";

    return 0;
}