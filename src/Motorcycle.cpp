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
Motorcycle::Motorcycle(const std::string& brand, const std::string &cylinder, const float& cost): Vehicle(brand, cost) {
	_cylinder = cylinder;
    _type = Vehicle::moto;
}

Motorcycle::Motorcycle(Vehicle *&vehicle) {
    _cylinder = vehicle->getName();
    _type = vehicle->getType();
    _brand = vehicle->getBrand();
    _dailyCost = vehicle->getDailyCost();
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
const std::string &Motorcycle::getCylinder() const {
	return _cylinder;
}

/**
 *
 * @param cylinder
 */
void Motorcycle::setCylinder(std::string cylinder) {
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
    return getCylinder();
}

const Vehicle::Type& Motorcycle::getType() const{
    return _type;
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
