/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:13:52 by davigome          #+#    #+#             */
/*   Updated: 2025/06/28 10:52:10 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include "iter.hpp"

/* template <typename T>
void print(T &x) {
    std::cout << x << std::endl;
}

void increment(int &x) {
    ++x;
}

void addExclamation(std::string &s) {
    s += "!";
}

// Test program
int main() {
    std::cout << "=== Integer Array ===" << std::endl;
    int intArray[] = {1, 2, 3, 4, 5};
    iter(intArray, 5, print<int>);
    iter(intArray, 5, increment);
	std::cout << "===Post increment" << std::endl;
    iter(intArray, 5, print<int>);
    std::cout << "\n=== String Array ===" << std::endl;
    std::string strArray[] = {"hello", "world", "iter"};
    iter(strArray, 3, print<std::string>);
    iter(strArray, 3, addExclamation);
	std::cout << "===Post add exclamation===" << std::endl;
    iter(strArray, 3, print<std::string>);
    return 0;
} */

class Awesome
{
public:
	Awesome(void) : _n(42) {}
	int get(void) const { return this->_n; }

private:
	int _n;
};

std::ostream& operator<<(std::ostream& o, Awesome const& rhs)
{
	o << rhs.get();
	return o;
}

template<typename T>
void print(const T& x)
{
	std::cout << x << std::endl;
}

int main()
{
	int tab[] = { 0, 1, 2, 3, 4 };
	Awesome tab2[5];

	iter(tab, 5, print);
	iter(tab2, 5, print);

	return 0;
}

