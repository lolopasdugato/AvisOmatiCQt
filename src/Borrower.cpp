/*
 * Borrower.cpp
 *
 *  Created on: Apr 13, 2013
 *      Author: lord-nazdar
 */

#include "../include/Borrower.h"

int Borrower::_nbInstance = 0;

/**
 *
 * @param id
 * @param firstname
 * @param lastname
 * @param address
 * @param phoneNumber
 */
Borrower::Borrower(const std::string& firstname,  const std::string& lastname, const Address& address, const std::string& phoneNumber, int id) {
    if (id >= 0) {
        _id = id;
        _nbInstance = id;
    }
    else _id = _nbInstance;
	_firstName = firstname;
	_lastName = lastname;
    _address = address;
    _active=true;

	// Optional members
	_phoneNumber = phoneNumber;
    _nbInstance++;
}

Borrower::Borrower(const Borrower& borrower) {
	_id = borrower._id;
	_firstName = borrower._firstName;
	_lastName = borrower._lastName;
	_address = borrower._address;
    _active=true;
        // Optional members
	_phoneNumber = borrower._phoneNumber;
}

Borrower::~Borrower() {
}

/**
 *
 * @return
 */
bool Borrower::rent() {
	return false;
}

/**
 *
 * @return
 */
bool Borrower::bringBack() {
	return false;
}

/**
 *
 * @return
 */
const Address& Borrower::getAddress() const {
	return _address;
}

/**
 *
 * @param address
 */

void Borrower::setAddress(const Address& address) {
	_address = address;
}

/**
 *
 * @return
 */

const std::string& Borrower::getFirstName() const {
	return _firstName;
}

/**
 *
 * @param firstName
 */

void Borrower::setFirstName(const std::string& firstName) {
	_firstName = firstName;
}

/**
 *
 * @return
 */

int Borrower::getId() const {
	return _id;
}

/**
 *
 * @param id
 */

void Borrower::setId(int id) {
	_id = id;
}

/**
 *
 * @return
 */

const std::string& Borrower::getLastName() const {
	return _lastName;
}

/**
 *
 * @param lastName
 */

void Borrower::setLastName(const std::string& lastName) {
	_lastName = lastName;
}

/**
 *
 * @return
 */
const std::string& Borrower::getPhoneNumber() const {
	return _phoneNumber;
}

/**
 *
 * @param phoneNumber
 */
void Borrower::setPhoneNumber(const std::string& phoneNumber) {
	_phoneNumber = phoneNumber;
}

Address &Borrower::getAddress(){
    return _address;
}

/**
 * @brief overload stream <<
 * @param out
 * @param borrower
 * @return
 */
std::ostream& operator<< (std::ostream& out, const Borrower& borrower) {
	out << "Borrower's ID: ";
	out << borrower._id;
	out << "\nBorrower's first name: ";
	out << borrower._firstName;
	out << "\nBorrower's last name: ";
	out << borrower._lastName;
	out << "\nBorrower's phone number: ";
	out << borrower._phoneNumber;
	return out;
}

/**
 * @brief overload stream >>
 * @param in
 * @param borrower
 * @return
 */
std::istream& operator>> (std::istream& in, Borrower& borrower) {
	std::cout << "Enter Borrower's ID: ";
	in >> borrower._id;
	std::cout << "\nEnter Borrower's first name: ";
	in >> borrower._firstName;
	std::cout << "\nEnter Borrower's last name: ";
	in >> borrower._lastName;
	std::cout << "\nEnter Borrower's phone number";
	in >> borrower._phoneNumber;
	return in;
}

std::vector<std::string> Borrower::display(){
    std::vector<std::string> returnVector;
    returnVector.push_back(getFirstName());
    returnVector.push_back(getLastName());
    returnVector.push_back(getAddress().display());
    returnVector.push_back(getPhoneNumber());
    return returnVector;
}


const bool &Borrower::isActive(){
    return _active;
}

void Borrower::setActive(bool b){
    _active=b;
}
