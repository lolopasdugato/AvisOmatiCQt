/**
 *@file		CopyContainer.cpp
 *@author	Alpha
 *@vesrion
 *@date     30 mai 2013
 *@brief
 *@details
 */

#include "../include/CopyContainer.h"

CopyContainer::CopyContainer() {
	// TODO Auto-generated constructor stub

}

Copy* CopyContainer::at(const int& i) {
	return _copyContainer[i];
}

std::map<int, Copy *> &CopyContainer::getCopyContainer() {
	return _copyContainer;
}

void CopyContainer::setCopyContainer(const std::map<int, Copy*>& copyContainer) {
	_copyContainer = copyContainer;
}

std::vector<std::string> CopyContainer::display(int i){
    std::vector<std::string> returnVector;

    std::string s1;
    std::stringstream out1;
    out1 << _copyContainer[i]->getId();
    returnVector.push_back(out1.str());

    const Vehicle *vehicle = _copyContainer[i]->getVehicle();

    returnVector.push_back(vehicle->getBrand());

    switch(vehicle->getType()){
    case Vehicle::car:
        returnVector.push_back("Car");
        break;
    case Vehicle::moto:
        returnVector.push_back("Motorcycle");
        break;
    }

    returnVector.push_back(vehicle->getName());

    std::string s;
    std::stringstream out;
    out << _copyContainer[i]->getKilometers();
    returnVector.push_back(out.str());

    return returnVector;
}

std::map<int, Copy*> CopyContainer::search(const int& number, const int& kilometers) {
    std::map<int, Copy*> sorted;
    std::map<int, Copy*>::iterator it;
	for (it = _copyContainer.begin(); it != _copyContainer.end(); it++) {
        if (number != -1 && number == (*it).second->getId()) sorted[(*it).first] = (*it).second;
        else if (kilometers != -1 && (*it).second->getKilometers()) sorted[(*it).first] = (*it).second;
	}
	return sorted;
}

int CopyContainer::getNumberOf(Vehicle* vehicle){
    std::map<int, Copy*>::iterator it;
    int returnValue=0;
    for (it = _copyContainer.begin(); it != _copyContainer.end(); it++) {
        if((*it).second->getVehicle()->getName()==vehicle->getName() && (*it).second->getVehicle()->getBrand()==vehicle->getBrand())
            returnValue++;
    }

    return returnValue;
}

int CopyContainer::size(){
    return _copyContainer.size();
}

void CopyContainer::add(int i, Vehicle* vehicle){
    for(int j=0;j<i;j++){
        Copy* copy = new Copy(vehicle);
        _copyContainer.insert(std::make_pair(copy->getId(),copy));
    }
}

CopyContainer::~CopyContainer() {
	// TODO Auto-generated destructor stub
}

