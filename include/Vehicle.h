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
    //Enum to set whenever it's a car or a motorcycle
    enum Type{
        car,
        moto
    };

    Vehicle(const std::string& brand = "Default", const float& dailyCost = 0);
	Vehicle(const Vehicle& vehicle);
	virtual ~Vehicle();

    //Getters and Setters
	const std::string& getBrand() const;
    void setBrand(const std::string& brand);

    const float& getDailyCost() const;
    void setDailyCost(const float& cost);

	virtual const std::string& getName() const=0;

    virtual const Type& getType() const=0;

    //Display
    std::vector<std::string> display();
protected:
	std::string _brand;
    Type _type;
    float _dailyCost;
};

#endif /* VEHICLE_H_ */
