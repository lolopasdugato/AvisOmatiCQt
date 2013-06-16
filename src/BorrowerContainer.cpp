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

void BorrowerContainer::add(const std::string& firstname, const std::string& lastname, const Address& address, const std::string& phoneNumber = "None", int id) {
    Borrower* a = new Borrower (firstname, lastname, address, phoneNumber, id);
    _borrowerContainer[a->getId()] = a;
    return;
}

std::vector<std::string> BorrowerContainer::display(int i){
    std::vector<std::string> returnVector;
    returnVector.push_back(_borrowerContainer[i]->getFirstName());
    returnVector.push_back(_borrowerContainer[i]->getLastName());
    returnVector.push_back(_borrowerContainer[i]->getAddress().display());
    returnVector.push_back(_borrowerContainer[i]->getPhoneNumber());
    return returnVector;
}

BorrowerContainer::~BorrowerContainer() {
	// TODO Auto-generated destructor stub
}

int BorrowerContainer::size(){
    return _borrowerContainer.size();
}

std::vector<Borrower*> BorrowerContainer::search(std::vector<std::string> keywords){
    int counter=0;
    std::multimap<int,Borrower*> list;
    std::string concat="";

    for(std::map<int,Borrower*>::iterator iter2=_borrowerContainer.begin();iter2 != _borrowerContainer.end();iter2++){
        concat=(*iter2).second->getFirstName() +" "+ (*iter2).second->getLastName() +" "+(*iter2).second->getAddress().getStreet();  //Concat all elements
        for(std::vector<std::string>::iterator iter=keywords.begin();iter != keywords.end();iter++){   //Go throught all parameters
            if(concat.find((*iter))!=std::string::npos)
                counter++;
        }
        if(counter!=0){ //One or more match found
            list.insert(std::make_pair(counter,(*iter2).second));
        }

        counter=0;
    }

    std::vector<Borrower*> returnValue;
    for(std::multimap<int, Borrower*>::iterator it3 = list.begin(); it3 != list.end(); it3++) {
        returnValue.push_back((*it3).second);
    }

    return returnValue;
}
