/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:13:52 by davigome          #+#    #+#             */
/*   Updated: 2025/06/25 19:56:46 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Array.hpp"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"
#define MAX_VAL 750
/* int main(int, char**)
{
    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }
    delete [] mirror;
    return 0;
} */

void test_int_array() {
    std::cout << GREEN << "[Test] Array<int>" << RESET << std::endl;
    Array<int> a(5);
    for (unsigned int i = 0; i < a.size(); i++)
        a[i] = i * 10;
    for (unsigned int i = 0; i < a.size(); i++)
        std::cout << "a[" << i << "] = " << a[i] << std::endl;
}

void test_string_array() {
    std::cout << GREEN << "[Test] Array<std::string>" << RESET << std::endl;
    Array<std::string> words(3);
    words[0] = "Hello";
    words[1] = "42";
    words[2] = "Network";
    for (unsigned int i = 0; i < words.size(); i++)
        std::cout << "words[" << i << "] = " << words[i] << std::endl;
}

void test_copy_constructor() {
    std::cout << GREEN << "[Test] Copy constructor" << RESET << std::endl;
    Array<float> a(3);
    for (unsigned int i = 0; i < a.size(); i++)
        a[i] = i + 0.5f;
    Array<float> b(a);
    for (unsigned int i = 0; i < b.size(); i++)
        std::cout << "b[" << i << "] = " << b[i] << std::endl;
}

void test_assignment_operator() {
    std::cout << GREEN << "[Test] Assignment operator" << RESET << std::endl;
    Array<char> a(2);
    a[0] = 'A';
    a[1] = 'B';
    Array<char> b;
    b = a;
    for (unsigned int i = 0; i < b.size(); i++)
        std::cout << "b[" << i << "] = " << b[i] << std::endl;
}

void test_exceptions() {
    std::cout << GREEN << "[Test] Out of bounds exceptions" << RESET << std::endl;
    Array<int> arr(5);
    try {
        arr[10] = 5;
    } catch (const std::exception& e) {
        std::cerr << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }
    try {
        arr[-1] = 42;
    } catch (const std::exception& e) {
        std::cerr << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }
}

void test_empty_array() {
    std::cout << GREEN << "[Test] Empty array" << RESET << std::endl;
    Array<int> empty;
    std::cout << "Size = " << empty.size() << std::endl;
    try {
        empty[0] = 1;
    } catch (const std::exception& e) {
        std::cerr << RED << "Expected exception: " << e.what() << RESET << std::endl;
    }
}

int main() {
    test_int_array();
    test_string_array();
    test_copy_constructor();
    test_assignment_operator();
    test_exceptions();
    test_empty_array();
    return 0;
}
