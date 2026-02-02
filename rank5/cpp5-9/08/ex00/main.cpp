/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:07:59 by davigome          #+#    #+#             */
/*   Updated: 2025/06/26 21:52:43 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <list>
#include "easyfind.hpp"

int main() {
    try {
        std::vector<int> vec;
        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);
        vec.push_back(40);

        std::list<int> lst;
        lst.push_back(5);
        lst.push_back(15);
        lst.push_back(25);
        lst.push_back(35);

        std::cout << "Searching for 30 in the vector...\n";
        std::vector<int>::iterator itVec = easyfind(vec, 30);
        std::cout << "Found in vector: " << *itVec << "\n";

        std::cout << "Searching for 25 in the list...\n";
        std::list<int>::iterator itList = easyfind(lst, 25);
        std::cout << "Found in list: " << *itList << "\n";

        std::cout << "Searching for 50 in the vector...\n";
        easyfind(vec, 50); // Will throw

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << "\n";
    }

    return 0;
}
