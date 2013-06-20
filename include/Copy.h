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
    //Enum to define the three different status of damage
    enum Status{
        NEW,
        DAMAGED,
        UNUSABLE
    };

    static int currentId;

    Copy(Vehicle* vehicle);
    Copy(const int &kilometers, const Status& status, const bool& dispo, Vehicle *vehicle, int id = -1);
	Copy(const Copy& copy);
	virtual ~Copy();

    //Getters and Setters
    int getId() const;
    void setId(int id);

	int getKilometers() const;
	void setKilometers(int kilometers);

    Vehicle* getVehicle() const;

    void setDispo(const bool &dispo);
    bool isDispo();

    const Status& getStatus();
    void setStatus(Status status);

    const bool& isActive();
    void setActive(bool b);

    //Overload
	friend std::ostream& operator<< (std::ostream& out, const Copy& copy);
	friend std::istream& operator>> (std::istream& in, Copy& copy);
private:
    int _id;
	int _kilometers;
    bool _dispo;
    bool _active;
    Status _status;

	Vehicle* _vehicle;
};

#endif /* COPY_H_ */
