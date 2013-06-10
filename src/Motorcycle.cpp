/*
 * Motorcycle.cpp
 *
 *  Created on: Apr 13, 2013
 *      Author: lord-nazdar
 */

#include "../include/Motorcycle.h"

/**
 *
 * @param brand
 * @param cylinder
 */
Motorcycle::Motorcycle(const std::string& brand, const int& cylinder): Vehicle(brand) {
	_cylinder = cylinder;
}

/**
 * @brief copy constructor
 * @param motorcycle
 */
Motorcycle::Motorcycle(const Motorcycle& motorcycle) {
	_cylinder = motorcycle._cylinder;
}

Motorcycle::~Motorcycle() {
}

/**
 *
 * @return
 */
int Motorcycle::getCylinder() const {
	return _cylinder;
}

/**
 *
 * @param cylinder
 */
void Motorcycle::setCylinder(int cylinder) {
	_cylinder = cylinder;
}

/**
 * @brief overload stream <<
 * @param out
 * @param motorcycle
 * @return
 */

std::ostream& operator<< (std::ostream& out, const Motorcycle& motorcycle) {
	out << "Motorcycle's brand: " << motorcycle._brand;
	out << "Motorcycle's number of cylinder: " << motorcycle._cylinder;
	return out;
}

const std::string& Motorcycle::getName() const{
    std::ostringstream oss;
    oss << getCylinder();
	return oss.str() + "cc";
}

/**
 * @brief overload stream >>
 * @param in
 * @param motorcycle
 * @return
 */
std::istream& operator>> (std::istream& in, Motorcycle& motorcycle) {
	std::cout << "Please enter Motorcycle's brand: ";
	in >> motorcycle._brand;
	std::cout << "\nPlease enter Motorcycle's number of cylinder: ";
	in >> motorcycle._cylinder;
	return in;
}
