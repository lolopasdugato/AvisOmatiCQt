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
    Motorcycle(const std::string& brand = "Default", const std::string& cylinder = "Default");
	Motorcycle(const Motorcycle& motorcycle);
    Motorcycle(Vehicle*& vehicle);
	virtual ~Motorcycle();

    const std::string& getCylinder() const;
    void setCylinder(std::string cylinder);

	const std::string& getName() const;
    const Vehicle::Type& getType() const;

	friend std::ostream& operator<< (std::ostream& out, const Motorcycle& motorcycle);
	friend std::istream& operator>> (std::istream& in, Motorcycle& motorcycle);

private:
    std::string _cylinder;
    Vehicle::Type _type;
};

#endif /* MOTORCYCLE_H_ */
