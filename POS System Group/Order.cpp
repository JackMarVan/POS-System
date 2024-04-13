#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>
#include "Order.h"

Order::Order() {
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "%m/%d/%Y - %I:%M:%S", timeinfo);

	date = buffer;
	supplier = "";
	contactAddress = "";
	emailAddress = "";
	phoneNumber = 1000000000;
	delivered = false;
	orderDebt = 0.0;

}

Order::Order(Inventory* item, string supplier, string contactAddress, string emailAddress, int phoneNumber) {
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "%m/%d/%Y - %I:%M:%S", timeinfo);

	date = buffer;
	this->supplier = supplier;
	this->contactAddress = contactAddress;
	this->emailAddress = emailAddress;
	this->phoneNumber = phoneNumber;
	delivered = false;
	orderDebt = item->getCount() * item->getPrice();

	setCategory(item->getCategory());
	setID(item->getID());
	setName(item->getName());
	setPrice(item->getPrice());
	setCount(item->getCount());
	setThreshold(item->getThreshold());

}

Order::Order(const Order& order) {
	this->date = order.date;
	this->supplier = order.supplier;
	this->contactAddress = order.contactAddress;
	this->emailAddress = order.emailAddress;
	this->phoneNumber = order.phoneNumber;
	this->delivered = order.delivered;
	this->orderDebt = order.orderDebt;
}

Order::~Order() 
{
}

//double Order::getPrice() {
//	return price;
//}

string Order::getDate() {
	return this->date;
}

void Order::setDate(string date) {
	this->date = date;
}

string Order::getSupplier() {
	return this->supplier;
}

void Order::setSupplier(string supplier) {
	this->supplier = supplier;
}

string Order::getContactAddress() {
	return this->contactAddress;
}

void Order::setContactAddress(string contactAddress) {
	this->contactAddress = contactAddress;
}

string Order::getEmailAddress() {
	return this->emailAddress;
}

void Order::setEmailAddress(string emailAddress) {
	this->emailAddress = emailAddress;
}

int Order::getPhoneNumber() {
	return this->phoneNumber;
}

void Order::setPhoneNumber(int phoneNumber) {
	this->phoneNumber = phoneNumber;
}

string Order::getDelivered() {
	if (this->delivered) {
		return "Arrived";
	}
	return "Transit";
}

void Order::deliver() {
	this->delivered = true;
	//may want to put any code here that is relevant to order delivery -JMV
}

double Order::getOrderDebt() {
	return this->orderDebt;
}

//returns the remainder of the debt paid if it would exceed the total debt -JMV
int Order::payDebt(double toPay) {
	if (this->orderDebt - toPay <= 0) {
		int remainder = ((this->orderDebt - toPay) * -1.0);
		this->orderDebt = 0.0;
		return remainder;
	}
	else {
		this->orderDebt = this->orderDebt - toPay;
		return 0;
	}
}

void Order::orderPrint() {
	cout << left << setw(25) << this->getDate() << setw(25)
		<< this->getName() << setw(25) << this->getCount() << setw(25)
		<< this->getSupplier() << setw(25) << this->getContactAddress() << setw(25)
		<< this->getEmailAddress() << setw(15) << this->getPhoneNumber() << setw(15) 
		<< this->getDelivered() << setw(8) << this->getOrderDebt() << endl;
}