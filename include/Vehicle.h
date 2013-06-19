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
#include <vector>
#include <sstream>

class Vehicle {
public:
    enum Type{
        car,
        moto
    };

    Vehicle(const std::string& brand = "Default", const float& dailyCost = 0);
	Vehicle(const Vehicle& vehicle);
	virtual ~Vehicle();

	const std::string& getBrand() const;
    const float& getDailyCost() const;
    void setDailyCost(const float& cost);
	void setBrand(const std::string& brand);
	virtual const std::string& getName() const=0;

    std::vector<std::string> display();

    virtual const Type& getType() const=0;

protected:
	std::string _brand;
    Type _type;
    float _dailyCost;
};

#endif /* VEHICLE_H_ */
