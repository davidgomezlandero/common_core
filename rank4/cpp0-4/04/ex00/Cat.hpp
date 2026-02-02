/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:02:17 by davigome          #+#    #+#             */
/*   Updated: 2025/05/29 18:42:27 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
#define CAT_HPP
#include "Animal.hpp"
class Cat : public Animal
{
	public:
		Cat();
		Cat(const Cat &cat);
		~Cat();
		using Animal::operator=;
		
		void makeSound(void) const;
};

#endif