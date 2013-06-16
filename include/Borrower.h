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

class Borrower {
public:
    Borrower(const std::string& firstname,  const std::string& lastname, const Address& address, const std::string& phoneNumber = "None", int id = -1);
	Borrower(const Borrower&);
	virtual ~Borrower();

	bool rent();
	bool bringBack();

	const Address& getAddress() const;
	void setAddress(const Address& address);
	const std::string& getFirstName() const;
	void setFirstName(const std::string& firstName);
	int getId() const;
	void setId(int id);
	const std::string& getLastName() const;
	void setLastName(const std::string& lastName);
	const std::string& getPhoneNumber() const;
    Address& getAddress();
	void setPhoneNumber(const std::string& phoneNumber);

	friend std::ostream& operator<< (std::ostream& out, const Borrower& borrower);
	friend std::istream& operator>> (std::istream& in, Borrower& borrower);

private:
    static int _nbInstance;
	int _id;
	std::string _firstName;
	std::string _lastName;
	Address _address;

	// Optional members
	std::string _phoneNumber;
};

#endif /* BORROWER_H_ */
