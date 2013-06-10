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

#include <vector>
#include "Borrower.h"

class BorrowerContainer {
private:
	std::vector<Borrower*> _borrowerContainer;
public:
	BorrowerContainer();
	virtual ~BorrowerContainer();

	std::vector<Borrower*> search(std::string firstName = "none", std::string lastName = "none");

	const std::vector<Borrower*>& getBorrowerContainer() const;
	void setBorrowerContainer(const std::vector<Borrower*>& borrowerContainer);
};

#endif /* BORROWERCONTAINER_H_ */
