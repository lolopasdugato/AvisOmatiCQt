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

std::map<int, Copy *> &CopyContainer::getCopyContainer() {
	return _copyContainer;
}

void CopyContainer::setCopyContainer(const std::map<int, Copy*>& copyContainer) {
	_copyContainer = copyContainer;
}

std::vector<std::string> CopyContainer::display(int i){
    std::vector<std::string> returnVector;
    i++;
    std::string s1;
    std::stringstream out1;
    out1 << _copyContainer[i]->getId();
    returnVector.push_back(out1.str());

    const Vehicle *vehicle = _copyContainer[i]->getVehicle();

    switch(vehicle->getType()){
    case Vehicle::car:
        returnVector.push_back("Car");
        break;
    case Vehicle::moto:
        returnVector.push_back("Motorcycle");
        break;
    }

    returnVector.push_back(vehicle->getBrand());

    returnVector.push_back(vehicle->getName());

    switch(_copyContainer[i]->getStatus()){
    case Copy::NEW:
        returnVector.push_back("New");
        break;
    case Copy::DAMAGED:
        returnVector.push_back("Damaged");
        break;
    case Copy::UNUSABLE:
        returnVector.push_back("Unusable");
        break;
    }

    std::string s;
    std::stringstream out;
    out << _copyContainer[i]->getKilometers();
    returnVector.push_back(out.str());

    return returnVector;
}

std::vector<std::string> CopyContainer::display(int i, Vehicle::Type c){
    std::vector<std::string> returnVector;
    if(_copyContainer[i]->getVehicle()->getType()==c){
        std::string s1;
        std::stringstream out1;
        out1 << _copyContainer[i]->getId();
        returnVector.push_back(out1.str());

        const Vehicle *vehicle = _copyContainer[i]->getVehicle();

        switch(vehicle->getType()){
        case Vehicle::car:
            returnVector.push_back("Car");
            break;
        case Vehicle::moto:
            returnVector.push_back("Motorcycle");
            break;
        }

        returnVector.push_back(vehicle->getBrand());

        returnVector.push_back(vehicle->getName());

        switch(_copyContainer[i]->getStatus()){
        case Copy::NEW:
            returnVector.push_back("New");
            break;
        case Copy::DAMAGED:
            returnVector.push_back("Damaged");
            break;
        case Copy::UNUSABLE:
            returnVector.push_back("Unusable");
            break;
        }

        std::string s;
        std::stringstream out;
        out << _copyContainer[i]->getKilometers();
        returnVector.push_back(out.str());
    }

    return returnVector;
}

int CopyContainer::getNumberOf(Vehicle* vehicle){
    std::map<int, Copy*>::iterator it;
    int returnValue=0;
    for (it = _copyContainer.begin(); it != _copyContainer.end(); it++) {
        if((*it).second->getVehicle()->getName()==vehicle->getName() && (*it).second->getVehicle()->getBrand()==vehicle->getBrand())
            returnValue++;
    }

    return returnValue; //return the number of one vehicle in copy
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

void CopyContainer::add(const int& kilometers, const Copy::Status& status, const bool& dispo, Vehicle* vehicle, int id, bool active) {
    Copy* a = new Copy (kilometers, status, dispo, vehicle, id);
    _copyContainer[a->getId()] = a;
    a->setActive(active);
    return;
}

void CopyContainer::erase(Copy* copy) {
    _copyContainer[copy->getId()]->setActive(false);
}

CopyContainer::~CopyContainer() {
	// TODO Auto-generated destructor stub
}


