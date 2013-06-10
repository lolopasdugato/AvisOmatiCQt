/*
 * Date.cpp
 *
 *  Created on: 13 avr. 2013
 *      Author: Lo�c
 */

#include "../include/Date.h"

/**
 *
 * @param day
 * @param month
 * @param year
 */
Date::Date(const int& day, const int& month, const int& year) {
	_day = day;
	_month = month;
	_year = year;
}

/**
 * @brief copy constructor
 * @param date
 */
Date::Date(const Date& date) {
	_day = date._day;
	_month = date._month;
	_year = date._year;
}

Date::~Date() {
}

/**
 *
 * @return
 */
int Date::getDay() const {
	return _day;
}

/**
 *
 * @param day
 */
void Date::setDay(int day) {
	_day = day;
}

/**
 *
 * @return
 */
int Date::getMonth() const {
	return _month;
}

/**
 *
 * @param month
 */
void Date::setMonth(int month) {
	_month = month;
}

/**
 *
 * @return
 */
int Date::getYear() const {
	return _year;
}

/**
 *
 * @param year
 */
void Date::setYear(int year) {
	_year = year;
}

/**
 * @brief overload stream <<
 * @param out
 * @param date
 * @return
 */
std::ostream& operator <<(std::ostream& out, const Date& date) {
	out << date._day << "/" << date._month << "/" << date._year;
	return out;
}


/**
 * @brief overload stream >>
 * @param in
 * @param date
 * @return
 */
std::istream& operator >>(std::istream& in, Date& date) {

	std::cout << "Please enter a day: ";
	in >> date._day;
	if (date._day > 31 || date._day < 1) {
		do {
			std::cout << "Invalid day !";
			std::cout << "\nPlease enter a day: ";
			in >> date._day;
		}while (date._day > 31 || date._day < 1);
	}

	std::cout << "\nPlease enter a month: ";
	in >> date._month;
	if (date._month < 1 || date._month > 12) {
		do {
			std::cout << "Invalid month !";
			std::cout << "\nPlease enter a month: ";
			in >> date._month;
		}while (date._month < 1 || date._month > 12);
	}

	std::cout << "\nPlease enter a year: ";
	in >> date._year;
	if (date._year < 2013) {
		do {
			std::cout << "Invalid year !";
			std::cout << "\nPlease enter a year: ";
			in >> date._year;
		}while (date._year < 2013);
	}
	return in;
}

/**
 * @brief overload comparison <
 * @param date1
 * @param date2
 * @return
 */
bool operator< (const Date& date1, const Date& date2) {
	if (date1._year < date2._year) return true;
	else if (date1._month < date2._month) return true;
	else if (date1._day < date2._day) return true;
	else return false;
}

/**
 * @brief overload comparison >
 * @param date1
 * @param date2
 * @return
 */
bool operator> (const Date& date1, const Date& date2) {
	if (date1._year > date2._year) return true;
	else if (date1._month > date2._month) return true;
	else if (date1._day > date2._day) return true;
	else return false;
}
