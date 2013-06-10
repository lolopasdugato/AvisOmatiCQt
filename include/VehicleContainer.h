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
#include "Vehicle.h"

class VehicleContainer {
public:
	VehicleContainer();
	virtual ~VehicleContainer();

	Vehicle* at(int i);
	int count();
	std::vector<std::string> search(std::string brand);
	const std::vector<Vehicle*>& getVehicleList() const;

private:
	std::vector<Vehicle*> _vehicleList;
};

#endif /* VEHICLECONTAINER_H_ */
