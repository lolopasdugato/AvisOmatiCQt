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

const std::map<int, Copy*>& CopyContainer::getCopyContainer() const {
	return _copyContainer;
}

void CopyContainer::setCopyContainer(const std::map<int, Copy*>& copyContainer) {
	_copyContainer = copyContainer;
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

CopyContainer::~CopyContainer() {
	// TODO Auto-generated destructor stub
}

