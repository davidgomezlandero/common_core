/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:18:50 by davigome          #+#    #+#             */
/*   Updated: 2025/06/16 18:00:25 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <climits>

class ScalarConverter
{
	public:
		static void	convert(const std::string &argv);
	private:
		ScalarConverter();
		~ScalarConverter();
		ScalarConverter(const ScalarConverter &other);
		ScalarConverter &operator=(const ScalarConverter &other);

		void	isChar(const std::string &argv, std::string &type);
		void	isInt(const std::string &argv, std::string &type);
		void	isFloat(const std::string &argv, std::string &type);
		void	isDouble(const std::string &argv, std::string &type);

		void	printChar(const std::string &argv);
		void	printInt(const std::string &argv);
		void	printFloat(const std::string &argv);
		void	printDouble(const std::string &argv);
};