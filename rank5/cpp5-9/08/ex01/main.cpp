/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 09:17:19 by davigome          #+#    #+#             */
/*   Updated: 2025/06/28 12:54:35 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int main()
{
    std::cout << "---- Test 1: Basic functionality ----" << std::endl;
    try {
        Span sp(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        
        std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest Span: " << sp.longestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "\n---- Test 2: Adding too many numbers ----" << std::endl;
    try {
        Span sp(3);
        sp.addNumber(1);
        sp.addNumber(2);
        sp.addNumber(3);
        sp.addNumber(4); // should throw
    } catch (const std::exception& e) {
        std::cerr << "Expected error: " << e.what() << std::endl;
    }

    std::cout << "\n---- Test 3: Not enough numbers for span ----" << std::endl;
    try {
        Span sp(2);
        sp.addNumber(42);
        std::cout << sp.shortestSpan() << std::endl; // should throw
    } catch (const std::exception& e) {
        std::cerr << "Expected error: " << e.what() << std::endl;
    }

    std::cout << "\n---- Test 4: Range addition ----" << std::endl;
    try {
        Span sp(6);
        std::vector<int> vec;
        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);

        sp.addNumber(vec.begin(), vec.end());
        sp.addNumber(100);
        sp.addNumber(200);
        sp.addNumber(300); // should fill it

        std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest Span: " << sp.longestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "\n---- Test 5: Copy constructor and assignment ----" << std::endl;
    try {
        Span original(3);
        original.addNumber(5);
        original.addNumber(15);
        original.addNumber(25);

        Span copy(original); // copy constructor
        Span assigned(1); // dummy init
        assigned = original; // assignment

        std::cout << "Original Shortest: " << original.shortestSpan() << std::endl;
        std::cout << "Copy Shortest: " << copy.shortestSpan() << std::endl;
        std::cout << "Assigned Shortest: " << assigned.shortestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "\n---- Test 6: Performance with large number of elements ----" << std::endl;
    try {
        Span bigSpan(10000);
        for (int i = 0; i < 10000; ++i)
            bigSpan.addNumber(rand());

        std::cout << "Shortest Span: " << bigSpan.shortestSpan() << std::endl;
        std::cout << "Longest Span: " << bigSpan.longestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
