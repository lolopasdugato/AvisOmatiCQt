/**
 * \file      VehicleContainer.h
 * \author    Lord Nazdar
 * \version   
 * \date      May 30, 2013
 * \brief     
 * \details  
 */

#ifndef VEHICLECONTAINER_H_
#define VEHICLECONTAINER_H_
#include <vector>
#include <string>
#include <map>
#include "Vehicle.h"
#include "Car.h"
#include "Motorcycle.h"

class VehicleContainer {
public:
	VehicleContainer();
	virtual ~VehicleContainer();

	Vehicle* at(int i);
	int count();
    std::vector<std::string> search(std::string brand);
    std::vector<Vehicle *> search(std::vector<std::string> keywords);
    const std::vector<Vehicle*>& getVehicleList() const;

    int size();

    std::vector<std::string> display(int i);
    std::vector<std::string> display(int i, Vehicle::Type t);

    void add(const std::string& brand, const std::string& name, const Vehicle::Type &type, float dailyCost);

private:
    std::vector<Vehicle*> _vehicleList;
};

#endif /* VEHICLECONTAINER_H_ */
