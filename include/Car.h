/*
 * Car.h
 *
 *  Created on: Apr 13, 2013
 *      Author: lord-nazdar
 */

#ifndef CAR_H_
#define CAR_H_

#include "Vehicle.h"

#include <string>

class Car: public Vehicle {
public:
	Car(const std::string& model, const std::string& brand = "Default");
	Car(const Car& car);
	virtual ~Car();

	const std::string& getModel() const;
	void setModel(const std::string& model);

	const std::string& getName() const;

	friend std::ostream& operator<< (std::ostream& out, const Car& car);
	friend std::istream& operator>> (std::istream& in, Car& car);

private:
	std::string _model;
};

#endif /* CAR_H_ */
