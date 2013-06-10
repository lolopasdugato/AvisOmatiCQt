/*
 * Rent.h
 *
 *  Created on: 13 avr. 2013
 *      Author: Lo�c
 */

#ifndef RENT_H_
#define RENT_H_

#include "Date.h"
#include "Vehicle.h"
#include "Copy.h"

class Rent {
public:
	Rent(Copy* copy, Vehicle* vehicle, const Date& begin, const Date& end, const int& number = -1, const int& price = -1);
	Rent(const Rent& rent);
	virtual ~Rent();

	const Date& getBegin() const;
	void setBegin(const Date& _begin);
	const Date& getEnd() const;
	void setEnd(const Date& _end);
	int getNumber() const;
	void setNumber(int _number);

	friend std::ostream& operator<< (std::ostream& out, const Rent& rent);
	friend std::istream& operator>> (std::istream& in, Rent& rent);

private:
	int _number;
	int _price;
	Copy* _copy;
	Vehicle* _vehicle;
	Date _begin;
	Date _end;
};

#endif /* RENT_H_ */
