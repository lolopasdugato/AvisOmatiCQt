/*
 * Date.h
 *
 *  Created on: 13 avr. 2013
 *      Author: Lo�c
 */

#ifndef DATE_H_
#define DATE_H_

#include <iostream>

class Date {
public:
	Date(const int& day = -1, const int& month = -1, const int& year = -1);
	Date(const Date& date);
	virtual ~Date();

    //Getters and Setters
	int getDay() const;
	void setDay(int day);

	int getMonth() const;
	void setMonth(int month);

	int getYear() const;
	void setYear(int year);

    //Overload
	friend std::ostream& operator<< (std::ostream& out, const Date& date);
	friend std::istream& operator>> (std::istream& in, Date& date);
	friend bool operator< (const Date& date1, const Date& date2);
	friend bool operator> (const Date& date1, const Date& date2);

private:
	int _day;
	int _month;
	int _year;
};

#endif /* DATE_H_ */
