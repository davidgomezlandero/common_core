/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:49:05 by davigome          #+#    #+#             */
/*   Updated: 2025/05/17 18:46:18 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact {
private:
	std::string FirstName;
	std::string LastName;
	std::string NickName;
	std::string PhoneNumber;
	std::string DarkestSecret;

public:
	void setFirstName();
	std::string getFirstName() const;
	
	void setLastName();
	std::string getLastName() const;
	
	void setNickName();
	std::string getNickName() const;
	
	void setPhoneNumber();
	std::string getPhoneNumber() const;
	
	void setDarkestSecret();
	std::string getDarkestSecret() const;
};

#endif