/*
 * Address.cpp
 *
 *  Created on: Apr 13, 2013
 *      Author: lord-nazdar
 */

#include "../include/Address.h"

/**
 * @brief Address constructor
 * @param number
 * @param street
 * @param PC
 * @param city
 */
Address::Address(const int& number, const std::string& street, const std::string& PC, const std::string& city) {
	_number = number;
	_street = street;
	_PC = PC;
	_city = city;
}

/**
 * @brief copy constructor
 * @param address
 */
Address::Address(const Address& address) {
	_number = address._number;
	_street = address._street;
	_PC = address._PC;
	_city = address._city;
}

Address::~Address() {
}

/**
 *
 * @return city
 */
const std::string& Address::getCity() const {
	return _city;
}

/**
 *
 * @param city
 */
void Address::setCity(const std::string& city) {
	_city = city;
}

/**
 *
 * @return
 */
int Address::getNumber() const {
	return _number;
}

/**
 *
 * @param number
 */
void Address::setNumber(int number) {
	_number = number;
}

/**
 *
 * @return
 */
const std::string& Address::getPc() const {
	return _PC;
}

/**
 *
 * @param pc
 */
void Address::setPc(const std::string& pc) {
	_PC = pc;
}

/**
 *
 * @return
 */
const std::string& Address::getStreet() const {
	return _street;
}

/**
 *
 * @param street
 */
void Address::setStreet(const std::string& street) {
	_street = street;
}

/**
 * @brief Overload stream <<
 * @param out
 * @param address
 * @return
 */
std::ostream& operator <<(std::ostream& out,const Address& address) {
	out << "Address number: ";
	out << address._number;
	out << "\nStreet: ";
	out << address._street;
	out << "\nPostal code: ";
	out << address._PC;
	out << "\nCity: ";
	out << address._city;
	return out;
}

/**
 * @brief Overload stream >>
 * @param in
 * @param address
 * @return
 */
std::istream& operator >>(std::istream& in, Address& address) {

	//TODO : repeat the method used in samy's code
	std::cout << "Please, enter the address number: ";
	in >> address._number;
	std::cout << "\nPlease, enter the street name: ";
	in >> address._street;
	std::cout << "\nPlease, enter the postal code: ";
	in >> address._PC;
	std::cout << "\nPlease, enter the city name: ";
	in >> address._city;
	return in;
}
