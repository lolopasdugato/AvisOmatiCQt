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

    const std::map<int, Copy*>& getCopyContainer() const;
    void setCopyContainer(const std::map<int, Copy*>& copyContainer);
};

#endif /* COPYCONTAINER_H_ */
