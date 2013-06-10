/*
 * Vehicle.cpp
 *
 *  Created on: Apr 13, 2013
 *      Author: lord-nazdar
 */

#include "../include/Vehicle.h"

/**
 *
 * @param brand
 */
Vehicle::Vehicle(const std::string& brand) {
	_brand = brand;
}

/**
 * @brief copy constructor
 * @param vehicle
 */
Vehicle::Vehicle(const Vehicle& vehicle) {
	_brand = vehicle._brand;
}

Vehicle::~Vehicle() {
}

/**
 *
 * @return
 */
const std::string& Vehicle::getBrand() const {
	return _brand;
}

/**
 *
 * @param brand
 */
void Vehicle::setBrand(const std::string& brand) {
	this->_brand = brand;
}
