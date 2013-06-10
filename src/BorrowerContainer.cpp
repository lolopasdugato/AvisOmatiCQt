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

const std::vector<Borrower*>& BorrowerContainer::getBorrowerContainer() const {
	return _borrowerContainer;
}

void BorrowerContainer::setBorrowerContainer(
		const std::vector<Borrower*>& borrowerContainer) {
	_borrowerContainer = borrowerContainer;
}

std::vector<Borrower*> BorrowerContainer::search(std::string firstName, std::string lastName) {
	std::vector<Borrower*> sorted;
	for(std::vector<Borrower*>::iterator it = _borrowerContainer.begin(); it != _borrowerContainer.end(); it++) {
		if(firstName != "none" && firstName == (*it)->getFirstName()) sorted.push_back(*it);
		else if(lastName != "none" && lastName == (*it)->getLastName()) sorted.push_back(*it);
	}
	return sorted;
}

BorrowerContainer::~BorrowerContainer() {
	// TODO Auto-generated destructor stub
}

