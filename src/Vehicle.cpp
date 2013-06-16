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
Vehicle::Vehicle(const std::string& brand, const float& cost) {
	_brand = brand;
    _dailyCost = cost;
}

/**
 * @brief copy constructor
 * @param vehicle
 */
Vehicle::Vehicle(const Vehicle& vehicle) {
	_brand = vehicle._brand;
    _dailyCost = vehicle._dailyCost;
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

/**
 *
 * @return
 */
const float& Vehicle::getDailyCost() const {
    return _dailyCost;
}

/**
 *
 * @param brand
 */
void Vehicle::setDailyCost(const float& cost) {
    this->_dailyCost = cost;
}
