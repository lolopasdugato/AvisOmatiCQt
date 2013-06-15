/*
 * Vehicle.h
 *
 *  Created on: Apr 13, 2013
 *      Author: lord-nazdar
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <string>
#include <iostream>

class Vehicle {
public:
    enum Type{
        car,
        moto
    };

	Vehicle(const std::string& brand = "Default");
	Vehicle(const Vehicle& vehicle);
	virtual ~Vehicle();

	const std::string& getBrand() const;
	void setBrand(const std::string& brand);
	virtual const std::string& getName() const=0;

    virtual const Type& getType() const=0;

protected:
	std::string _brand;
    Type _type;
};

#endif /* VEHICLE_H_ */
