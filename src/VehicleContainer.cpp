/**
 * \file      VehicleContainer.cpp
 * \author    Lord Nazdar
 * \version   
 * \date      May 30, 2013
 * \brief     
 * \details  
 */

#include "../include/VehicleContainer.h"

VehicleContainer::VehicleContainer() {
	// TODO Auto-generated constructor stub

}

VehicleContainer::~VehicleContainer() {
	// TODO Auto-generated destructor stub
}

Vehicle* VehicleContainer::at(int i) {
	return this->_vehicleList.at(i);
}

int VehicleContainer::count() {
	return _vehicleList.size();
}

std::vector<std::string> VehicleContainer::search(std::string brand) {
	std::vector<std::string> list;
	for(std::vector<Vehicle*>::iterator iter=_vehicleList.begin();iter != _vehicleList.end();iter++){
		if((*iter)->getBrand()==brand)
			list.push_back((*iter)->getName());
	}

	return list;
}

const std::vector<Vehicle*>& VehicleContainer::getVehicleList() const {
	return _vehicleList;
}
