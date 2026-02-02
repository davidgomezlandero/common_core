/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:25:06 by davigome          #+#    #+#             */
/*   Updated: 2025/05/23 09:42:23 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <fstream>
#include <cstring>

std::string	replace(std::string line, std::string s1, std::string s2)
{
	std::string result;
	size_t i = 0;

	while (i < line.length())
	{
		if (line.substr(i, s1.length()) == s1)
		{
			result += s2;
			i += s1.length();
		}
		else
		{
			result += line[i];
			++i;
		}
	}
	return result;
}

int main (int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << "Usage: ./replace <filename> <s1> <s2>" << std::endl;
        return (1);
	}
	std::string filename = argv[1];
	std::string s1 = argv[2];
	std::string s2 = argv[3];

	if (s1.empty() || s2.empty())
	{
		std::cerr << "Error: s1 and s2 cannot be empty." << std::endl;
		return (1);
	}
	std::ifstream infile(filename.c_str());
	if (!infile)
	{
		std::cerr << "Error: could not open input file." << std::endl;
		return (1);
	}
	std::ofstream outfile((filename + ".replace").c_str());
	if (!outfile)
	{
		std::cerr << "Error: could not open output file." << std::endl;
		return (1);
	}
	
	std::string line;
	while (std::getline(infile, line))
	{
		std::string replaced = replace(line, s1, s2);
		outfile << replaced << std::endl;
	}
	infile.close();
	outfile.close();
}