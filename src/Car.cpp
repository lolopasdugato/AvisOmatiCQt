/*
 * Car.cpp
 *
 *  Created on: Apr 13, 2013
 *      Author: lord-nazdar
 */

#include "../include/Car.h"
#include <iostream>

/**
 *
 * @param model
 * @param brand
 */
Car::Car(const std::string& model, const std::string& brand, const float& cost):Vehicle(brand,cost) {
	_model = model;
    _type = Vehicle::car;
}

Car::Car(Vehicle *&vehicle) {
    _model = vehicle->getName();
    _type = vehicle->getType();
    _brand = vehicle->getBrand();
    _dailyCost = vehicle->getDailyCost();
}

/**
 * @brief copy constructor
 * @param car
 */
/*Car::Car(const Car& car) {
	_model = car._model;
}*/

Car::~Car() {
}

/**
 *
 * @return
 */
const std::string& Car::getModel() const {
	return _model;
}

/**
 *
 * @param model
 */
void Car::setModel(const std::string& model) {
	_model = model;
}

/**
 * @brief overload stream <<
 * @param out
 * @param car
 * @return
 */
std::ostream& operator<< (std::ostream& out, const Car& car) {
	out << "Car model: " << car._model;
	out << "\nCar brand: " << car._brand;
	return out;
}

const std::string& Car::getName() const{
	return getModel();
}

const Vehicle::Type& Car::getType() const{
    return _type;
}

/**
 * @brief overload stream >>
 * @param in
 * @param car
 * @return
 */
std::istream& operator>> (std::istream& in, Car& car) {
	std::cout << "Please, enter car's model: ";
	in >> car._model;
	std::cout << "\nPlease, enter car's brand: ";
	in >> car._brand;
	return in;
}
