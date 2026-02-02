/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:42:09 by davigome          #+#    #+#             */
/*   Updated: 2025/07/01 09:35:03 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <algorithm>
#include <exception>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <cerrno>
#include <climits>

class BitcoinExchange
{
	private:
	std::map<std::string,float> _data;

	BitcoinExchange(BitcoinExchange const &other);
	BitcoinExchange &operator=(BitcoinExchange const &other);
	BitcoinExchange();

	public:
		BitcoinExchange(std::string &inputTxt);
		~BitcoinExchange();

		void parseInput(std::string &inputTxt);
		void execute(std::string line, std::string date, std::string btcs);
};