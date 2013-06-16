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

	Copy* at(const int& i);
    std::map<int, Copy*> search(const int& number = -1, const int& kilometers = -1);

    void add(int i, Vehicle* vehicle);

    int getNumberOf(Vehicle*vehicle);

    int size();

    std::vector<std::string> display(int i);

    std::map<int, Copy*>& getCopyContainer();
    void setCopyContainer(const std::map<int, Copy*>& copyContainer);
};

#endif /* COPYCONTAINER_H_ */
