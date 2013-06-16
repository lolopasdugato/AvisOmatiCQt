/*
 * Copy.h
 *
 *  Created on: 13 avr. 2013
 *      Author: Lo�c
 */

#ifndef COPY_H_
#define COPY_H_

#include <iostream>
#include "Vehicle.h"

class Copy {
public:
    Copy(Vehicle* vehicle);
    Copy(const int &kilometers, Vehicle *vehicle);
	Copy(const Copy& copy);
	virtual ~Copy();

	bool bringBack();
	bool rent();
	int getKilometers() const;
	void setKilometers(int kilometers);
    int getId() const;
    void setId(int id);
    const Vehicle* getVehicle() const;

    static int currentId;

	friend std::ostream& operator<< (std::ostream& out, const Copy& copy);
	friend std::istream& operator>> (std::istream& in, Copy& copy);
private:
    int _id;
	int _kilometers;
	Vehicle* _vehicle;
};

#endif /* COPY_H_ */
