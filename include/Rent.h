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
#include "Borrower.h"

class Rent {
public:
    Rent(Copy*& copy, Borrower*& borrower, const Date& begin, const Date& end);
	Rent(const Rent& rent);
	virtual ~Rent();

	const Date& getBegin() const;
	void setBegin(const Date& _begin);
	const Date& getEnd() const;
	void setEnd(const Date& _end);
    int getId() const;
    void setId(int id);
    void setInsurance(const bool& i);
    const bool getInsurance() const;
    const Copy* getCopy() const;
    const Borrower* getBorrower() const;

    bool isReturned();

    static int currentId;

	friend std::ostream& operator<< (std::ostream& out, const Rent& rent);
	friend std::istream& operator>> (std::istream& in, Rent& rent);

private:
    int _id;
	int _price;
    bool _status; //true = returned
    bool _insurance;
	Copy* _copy;
    Borrower* _borrower;
	Date _begin;
	Date _end;
};

#endif /* RENT_H_ */
