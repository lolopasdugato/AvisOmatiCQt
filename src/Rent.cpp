/*
 * Rent.cpp
 *
 *  Created on: 13 avr. 2013
 *      Author: Lo�c
 */

#include "../include/Rent.h"

/**
 *
 * @param number
 * @param begin
 * @param end
 */
Rent::Rent(Copy* copy, Vehicle* vehicle, const Date& begin, const Date& end, const int& number, const int& price) {
	_number = number;
	_begin = begin;
	_end = end;
	_copy = copy;
	_vehicle = vehicle;

	// initialisation du prix en fonction du nombre de kilomètres de l'exemplaire.
	int factor = 0;
	for(int cpt = 50000; cpt <= _copy->getKilometers(); cpt += 50000) {
		factor++;
	}
	_price = price - (factor/10);
}

/**
 * @brief copy constructor
 * @param rent
 */
Rent::Rent(const Rent& rent) {
	_number = rent._number;
	_begin = rent._begin;
	_end = rent._end;
	_price = rent._price;
	_vehicle = rent._vehicle;
	_copy = rent._copy;
}

Rent::~Rent() {
}

/**
 *
 * @return
 */
const Date& Rent::getBegin() const {
	return _begin;
}

/**
 *
 * @param begin
 */
void Rent::setBegin(const Date& begin) {
	_begin = begin;
}

/**
 *
 * @return
 */
const Date& Rent::getEnd() const {
	return _end;
}

/**
 *
 * @param end
 */
void Rent::setEnd(const Date& end) {
	_end = end;
}

/**
 *
 * @return
 */
int Rent::getNumber() const {
	return _number;
}

/**
 *
 * @param number
 */
void Rent::setNumber(int number) {
	_number = number;
}

/**
 * @brief overload stream <<
 * @param out
 * @param rent
 * @return
 */
std::ostream& operator<< (std::ostream& out, const Rent& rent) {
	out << "Rent's number: " << rent._number;
	out << "\nRent's begin date: " << rent._begin;
	out << "\nRent's end date: " << rent._end;
	return out;
}

/**
 * @brief overload stream >>
 * @param in
 * @param rent
 * @return
 */
std::istream& operator>> (std::istream& in, Rent& rent) {
	std::cout << "Please, enter rent's number: ";
	in >> rent._number;
	std::cout << "\nPlease, enter rent's begin date\n";
	in >> rent._begin;
	std::cout << "\nPlease, enter rent's end date\n";
	in >> rent._end;
	if (rent._begin > rent._end) {
		do {
			std::cout << "Invalid rent dates !";
			std::cout << "\nPlease, enter rent's begin date\n";
			in >> rent._begin;
			std::cout << "\nPlease, enter rent's end date\n";
			in >> rent._end;
		}while (rent._begin > rent._end);
	}
	return in;
}
