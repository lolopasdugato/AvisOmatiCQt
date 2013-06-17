/*
 * Copy.cpp
 *
 *  Created on: 13 avr. 2013
 *      Author: Lo�c
 */

#include "../include/Copy.h"
#include <iostream>

int Copy::currentId = 0;

/**
 *
 * @param number
 * @param kilometers
 */
Copy::Copy(const int &kilometers, const Status& status, const bool& dispo, Vehicle *vehicle, int id) {
    if (id >= 0) {
        _id = id;
        currentId = id;
    }
    else _id = currentId;
	_kilometers = kilometers;
    _status = status;
    _dispo = dispo;
	_vehicle = vehicle;

    currentId++;
}

Copy::Copy(Vehicle* vehicle) {
    _id = currentId;
    _kilometers = -1;
    _vehicle = vehicle;
    _dispo = true;
    _status = NEW;
    currentId++;
}

/**
 * @brief copy constructor
 * @param copy
 */
Copy::Copy(const Copy& copy) {
    _id = copy._id;
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
int Copy::getId() const {
    return _id;
}

/**
 *
 * @param id
 */
void Copy::setId(int id) {
    _id = id;
}

void Copy::setDispo(const bool& dispo){
    _dispo = dispo;
}

bool Copy::isDispo() {
    return _dispo;
}

const Copy::Status& Copy::getStatus() {
    return _status;
}

void Copy::setStatus(Status status) {
    _status = status;
}

/**
 * @brief overload stream <<
 * @param out
 * @param copy
 * @return
 */
std::ostream& operator<< (std::ostream& out, const Copy& copy) {
    out << "Copy's number: " << copy._id;
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
    in >> copy._id;
	std::cout << "\nPlease enter copy's kilometers: ";
	in >> copy._kilometers;
	return in;
}


const Vehicle* Copy::getVehicle() const{
    return _vehicle;
}
