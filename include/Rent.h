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

    static int currentId;

    //Getters and Setters
    int getId() const;
    void setId(int id);

	const Date& getBegin() const;
	void setBegin(const Date& _begin);

	const Date& getEnd() const;
	void setEnd(const Date& _end);

    void setInsurance(const bool& i);
    bool getInsurance() const;

    bool getStatus() const;
    void setStatus(const bool& i);

    int getFuelMalus();
    void setFuelMalus(int f);

    Copy *getCopy();

    Borrower *getBorrower() const;

    //Overload
	friend std::ostream& operator<< (std::ostream& out, const Rent& rent);
	friend std::istream& operator>> (std::istream& in, Rent& rent);

private:
    int _id;
	int _price;
    bool _status; //true = returned
    bool _insurance;
    int _fuelMalus;
	Copy* _copy;
    Borrower* _borrower;
	Date _begin;
	Date _end;
};

#endif /* RENT_H_ */
