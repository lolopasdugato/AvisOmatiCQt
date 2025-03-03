/**
 *@file		CopyContainer.h
 *@author	Alpha
 *@vesrion
 *@date     30 mai 2013
 *@brief
 *@details
 */

#ifndef COPYCONTAINER_H_
#define COPYCONTAINER_H_

#include <map>
#include <sstream>
#include <vector>
#include "CopyContainer.h"
#include "Copy.h"

class CopyContainer {
private:
    std::map<int, Copy*> _copyContainer;

public:
	CopyContainer();
	virtual ~CopyContainer();

    //Getters and Setters
    std::map<int, Copy*>& getCopyContainer();
    void setCopyContainer(const std::map<int, Copy*>& copyContainer);

    //Functions
    void add(int i, Vehicle* vehicle);
    void add(const int& kilometers, const Copy::Status& status, const bool& dispo, Vehicle* vehicle, int id = -1, bool active=true);
    void erase(Copy* copy);
    int getNumberOf(Vehicle*vehicle);
    int size();

    //Display
    std::vector<std::string> display(int i);
    std::vector<std::string> display(int i, Vehicle::Type c);
};

#endif /* COPYCONTAINER_H_ */
