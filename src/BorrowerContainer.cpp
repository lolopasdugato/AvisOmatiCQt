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

std::map<int,Borrower*>& BorrowerContainer::getBorrowerContainer() {
	return _borrowerContainer;
}

void BorrowerContainer::setBorrowerContainer(
        const std::map<int,Borrower*>& borrowerContainer) {
	_borrowerContainer = borrowerContainer;
}

void BorrowerContainer::add(const std::string& firstname, const std::string& lastname, const Address& address, const std::string& phoneNumber = "None", int id, bool active) {
    Borrower* a = new Borrower (firstname, lastname, address, phoneNumber, id);
    _borrowerContainer[a->getId()] = a;
    a->setActive(active);
    return;
}

void BorrowerContainer::erase(Borrower* borrower) {
    _borrowerContainer[borrower->getId()]->setActive(false);
}

std::vector<std::string> BorrowerContainer::display(int i){
    return _borrowerContainer[i]->display();
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
            if(concat.find((*iter))!=std::string::npos) //if one parameter is found in our concat string
                counter++;
        }
        if(counter!=0){ //One or more match found
            list.insert(std::make_pair(counter,(*iter2).second));
        }

        counter=0;
    }

    std::vector<Borrower*> returnValue;
    for(std::multimap<int, Borrower*>::reverse_iterator it3 = list.rbegin(); it3 != list.rend(); it3++) {
        returnValue.push_back((*it3).second);   //We only keep the Borrower* part
    }

    return returnValue;
}
