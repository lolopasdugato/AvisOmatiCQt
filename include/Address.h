/*
 * Address.h
 *
 *  Created on: Apr 13, 2013
 *      Author: lord-nazdar
 */

#ifndef Address_H_
#define Address_H_

#include <string>
#include <iostream>
#include <sstream>

class Address {
public:
	Address(const int& number = -1, const std::string& street = "DefaultStreet", const std::string& PC = "DefaultPostalCode", const std::string& city = "DefaultCity");
	Address(Address const& address);
	virtual ~Address();

	const std::string& getCity() const;
	void setCity(const std::string& city);
	int getNumber() const;
	void setNumber(int number);
	const std::string& getPc() const;
	void setPc(const std::string& pc);
	const std::string& getStreet() const;
	void setStreet(const std::string& street);

    std::string display();

	//overload
	friend std::ostream& operator<< (std::ostream& out, const Address& address);
	friend std::istream& operator>> (std::istream& in, Address& address);
private:
	int _number;
	std::string _street;
	std::string _PC;
	std::string _city;
};

#endif /* Address_H_ */
