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

std::vector<Vehicle*> VehicleContainer::search(std::vector<std::string> keywords) {
    int counter=0;
    std::multimap<int,Vehicle*> list;
    std::string concat="";

    for(std::vector<Vehicle*>::iterator iter2=_vehicleList.begin();iter2 != _vehicleList.end();iter2++){
        concat=(*iter2)->getBrand() +" "+ (*iter2)->getName();  //Concat all elements
        for(std::vector<std::string>::iterator iter=keywords.begin();iter != keywords.end();iter++){   //Go throught all parameters
            if(concat.find((*iter))!=std::string::npos)
                counter++;
        }
        if(counter!=0){ //One or more match found
            list.insert(std::make_pair(counter,(*iter2)));
        }

        counter=0;
    }

    std::vector<Vehicle*> returnValue;
    for(std::multimap<int, Vehicle*>::iterator it3 = list.begin(); it3 != list.end(); it3++) {
        returnValue.push_back((*it3).second);
    }

    return returnValue;
}

int VehicleContainer::size(){
    return _vehicleList.size();
}

const std::vector<Vehicle*>& VehicleContainer::getVehicleList() const {
	return _vehicleList;
}

std::vector<std::string> VehicleContainer::display(int i){
    std::vector<std::string> returnVector;
    returnVector.push_back(_vehicleList[i]->getBrand());

    switch(_vehicleList[i]->getType()){
    case Vehicle::car:
        returnVector.push_back("Car");
        break;
    case Vehicle::moto:
        returnVector.push_back("Motorcycle");
        break;
    }

    returnVector.push_back(_vehicleList[i]->getName());

    std::ostringstream os;
      os << _vehicleList[i]->getDailyCost();

    returnVector.push_back(os.str());
    return returnVector;
}

void VehicleContainer::add(const std::string& brand, const std::string& name, const Vehicle::Type& type, float dailyCost){
    Vehicle *c;

    switch(type){
    case Vehicle::car:
        c = new Car(name,brand,dailyCost);
        break;
    case Vehicle::moto:
        c = new Motorcycle(brand,name,dailyCost);
        break;
    }
    _vehicleList.push_back(c);
}
