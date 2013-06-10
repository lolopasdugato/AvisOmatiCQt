/*
 * Copy.cpp
 *
 *  Created on: 13 avr. 2013
 *      Author: Lo�c
 */

#include "../include/Copy.h"
#include <iostream>

/**
 *
 * @param number
 * @param kilometers
 */
Copy::Copy(const int& number, const int& kilometers, Vehicle* vehicle) {
	_number = number;
	_kilometers = kilometers;
	_vehicle = vehicle;
}

/**
 * @brief copy constructor
 * @param copy
 */
Copy::Copy(const Copy& copy) {
	_number = copy._number;
	_kilometers = copy._kilometers;
	_vehicle = copy._vehicle;
}

Copy::~Copy() {
}
/**
 *
 * @return
 */
bool Copy::bringBack() {
	return false;
}

/**
 *
 * @return
 */
bool Copy::rent() {
	return false;
}

/**
 *
 * @return
 */
int Copy::getKilometers() const {
	return _kilometers;
}

/**
 *
 * @param kilometers
 */
void Copy::setKilometers(int kilometers) {
	_kilometers = kilometers;
}

/**
 *
 * @return
 */
int Copy::getNumber() const {
	return _number;
}

/**
 *
 * @param number
 */
void Copy::setNumber(int number) {
	_number = number;
}

/**
 * @brief overload stream <<
 * @param out
 * @param copy
 * @return
 */
std::ostream& operator<< (std::ostream& out, const Copy& copy) {
	out << "Copy's number: " << copy._number;
	out << "\nCopy's kilometers: " << copy._kilometers;
	return out;
}

/**
 * @brief overload stream >>
 * @param in
 * @param copy
 * @return
 */
std::istream& operator>> (std::istream& in, Copy& copy) {
	std::cout << "Please enter copy's number: ";
	in >> copy._number;
	std::cout << "\nPlease enter copy's kilometers: ";
	in >> copy._kilometers;
	return in;
}
