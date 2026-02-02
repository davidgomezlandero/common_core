/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 06:05:59 by davigome          #+#    #+#             */
/*   Updated: 2025/05/29 17:59:53 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>

class Brain{
		private:
			std::string ideas[100];
		public:
			Brain();
			Brain(const Brain &brain);
			Brain& operator=(const Brain &brain);
			~Brain();
};

#endif