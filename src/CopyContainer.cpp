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

const std::vector<Copy*>& CopyContainer::getCopyContainer() const {
	return _copyContainer;
}

void CopyContainer::setCopyContainer(const std::vector<Copy*>& copyContainer) {
	_copyContainer = copyContainer;
}

std::vector<Copy*> CopyContainer::search(const int& number, const int& kilometers) {
	std::vector<Copy*> sorted;
	std::vector<Copy*>::iterator it;
	for (it = _copyContainer.begin(); it != _copyContainer.end(); it++) {
		if (number != -1 && number == (*it)->getNumber()) sorted.push_back(*it);
		else if (kilometers != -1 && (*it)->getKilometers()) sorted.push_back(*it);
	}
	return sorted;
}

CopyContainer::~CopyContainer() {
	// TODO Auto-generated destructor stub
}

