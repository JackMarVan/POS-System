#pragma once
#ifndef ORDER_H_
#define ORDER_H_
#include "Inventory.h"

class Order : public Inventory
{
private:
	string date;
	string supplier;
	string contactAddress;
	string emailAddress;
	int phoneNumber;
	bool delivered;
	double orderDebt;
public:
	Order();
	Order(Inventory* item, string, string, string, int);
	Order(const Order&);
	~Order();
	string getDate();
	void setDate(string);
	string getSupplier();
	void setSupplier(string);
	string getContactAddress();
	void setContactAddress(string);
	string getEmailAddress();
	void setEmailAddress(string);
	int getPhoneNumber();
	void setPhoneNumber(int);
	string getDelivered();
	//double getPrice();
	
	void deliver();
	double getOrderDebt();
	int payDebt(double);
	void orderPrint();
};

#endif // !ORDER_H_