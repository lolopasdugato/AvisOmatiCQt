/**
 *@file		BorrowerContainer.h
 *@author	Alpha
 *@vesrion
 *@date     30 mai 2013
 *@brief
 *@details
 */

#ifndef BORROWERCONTAINER_H_
#define BORROWERCONTAINER_H_

#include <map>
#include <vector>
#include "Borrower.h"

class BorrowerContainer {
private:
    std::map<int, Borrower*> _borrowerContainer;
public:
	BorrowerContainer();
	virtual ~BorrowerContainer();

    std::map<int, Borrower*> search(std::string firstName = "none", std::string lastName = "none");
    void add(const std::string& firstname, const std::string& lastname, const Address& address, const std::string& phoneNumber, int id = -1);
    std::map<int, Borrower*>& getBorrowerContainer();
    void setBorrowerContainer(const std::map<int, Borrower*>& borrowerContainer);
    std::vector<std::string> display(int i);

    std::vector<Borrower*> search(std::vector<std::string> keywords);
    void erase(Borrower*);

    int size();
};

#endif /* BORROWERCONTAINER_H_ */
