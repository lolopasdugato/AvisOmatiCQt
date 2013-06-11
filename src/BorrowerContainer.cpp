/**
 *@file		BorrowerContainer.cpp
 *@author	Alpha
 *@vesrion
 *@date     30 mai 2013
 *@brief
 *@details
 */

#include "../include/BorrowerContainer.h"

BorrowerContainer::BorrowerContainer() {
	// TODO Auto-generated constructor stub

}

const std::map<int,Borrower*>& BorrowerContainer::getBorrowerContainer() const {
	return _borrowerContainer;
}

void BorrowerContainer::setBorrowerContainer(
        const std::map<int,Borrower*>& borrowerContainer) {
	_borrowerContainer = borrowerContainer;
}

std::map<int, Borrower*> BorrowerContainer::search(std::string firstName, std::string lastName) {
    std::map<int, Borrower*> sorted;
    for(std::map<int, Borrower*>::iterator it = _borrowerContainer.begin(); it != _borrowerContainer.end(); it++) {
        if(firstName != "none" && firstName == (*it).second->getFirstName()) sorted[(*it).first] = (*it).second;
        else if(lastName != "none" && lastName == (*it).second->getLastName()) sorted[(*it).first] = (*it).second;
	}
	return sorted;
}

void BorrowerContainer::add(const std::string& firstname, const std::string& lastname, const Address& address, const std::string& phoneNumber = "None") {
    Borrower* a = new Borrower (firstname, lastname, address, phoneNumber);
    _borrowerContainer[a->getId()] = a;
    return;
}

BorrowerContainer::~BorrowerContainer() {
	// TODO Auto-generated destructor stub
}

