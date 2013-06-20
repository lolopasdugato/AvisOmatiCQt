/*
 * Borrower.h
 *
 *  Created on: Apr 13, 2013
 *      Author: lord-nazdar
 */

#ifndef BORROWER_H_
#define BORROWER_H_

#include <string>
#include "Address.h"
#include <vector>

class Borrower {
public:
    Borrower(const std::string& firstname,  const std::string& lastname, const Address& address, const std::string& phoneNumber = "None", int id = -1);
	Borrower(const Borrower&);
	virtual ~Borrower();

    //Getters and Setters
    int getId() const;
    void setId(int id);

    const std::string& getFirstName() const;
    void setFirstName(const std::string& firstName);

    const std::string& getLastName() const;
    void setLastName(const std::string& lastName);

	const Address& getAddress() const;
	void setAddress(const Address& address);

	const std::string& getPhoneNumber() const;
    void setPhoneNumber(const std::string& phoneNumber);

    Address& getAddress();

    const bool& isActive();
    void setActive(bool b);

    //Display
    std::vector<std::string> display();

    //Overload
	friend std::ostream& operator<< (std::ostream& out, const Borrower& borrower);
	friend std::istream& operator>> (std::istream& in, Borrower& borrower);

private:
    static int _nbInstance;
	int _id;
	std::string _firstName;
	std::string _lastName;
	Address _address;
    bool _active;

	// Optional members
	std::string _phoneNumber;
};

#endif /* BORROWER_H_ */
