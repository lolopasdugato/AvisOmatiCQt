/*
 * Motorcycle.h
 *
 *  Created on: Apr 13, 2013
 *      Author: lord-nazdar
 */

#ifndef MOTORCYCLE_H_
#define MOTORCYCLE_H_

#include "Vehicle.h"
#include <string>
#include <sstream>


class Motorcycle: public Vehicle {
public:
	Motorcycle(const std::string& brand = "Default", const int& cylinder = -1);
	Motorcycle(const Motorcycle& motorcycle);
	virtual ~Motorcycle();

	int getCylinder() const;
	void setCylinder(int cylinder);

	const std::string& getName() const;

	friend std::ostream& operator<< (std::ostream& out, const Motorcycle& motorcycle);
	friend std::istream& operator>> (std::istream& in, Motorcycle& motorcycle);

private:
	int _cylinder;
};

#endif /* MOTORCYCLE_H_ */
