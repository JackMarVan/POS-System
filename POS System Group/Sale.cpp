#include "Sale.h"
#include <string>
#include <iostream>
#include <iomanip>

Sale::Sale() {
	//Same date function as in the order class for simplicity - JW
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "%m/%d/%Y - %I:%M:%S", timeinfo);

	saleDate = buffer;
	//customerName = "John Doe";
	//customerPhoneNumber = 2000000000;
	unitsSold = 0;
	//weightSold = 0.0;
	saleTotal = 0.0;

}

Sale::Sale(Inventory* item, int units) {
	//Same date function as in the order class for simplicity - JW
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "%m/%d/%Y - %I:%M:%S", timeinfo);

	itemName = item->getName();
	saleDate = buffer;
	//this->customerName = name;
	//this->customerPhoneNumber = phone;
	this->unitsSold = units;
	//this->weightSold = weight;
	this->saleTotal = item->getPrice() * units;

	//addItem(item, units, weight);
}

Sale::Sale(const Sale& sale) {
	this->saleDate = sale.saleDate;
	this->saleTotal = sale.saleTotal;
	this->unitsSold = sale.unitsSold;
	//this->customerName = sale.customerName;
	//this->customerPhoneNumber = sale.customerPhoneNumber;
	//this->weightSold = sale.weightSold;
}

Sale::~Sale() {

}

int Sale::getUnitsSold() {
	return unitsSold;
}

double Sale::getSaleTotal() {
	return saleTotal;
}

string Sale::getSaleDate() {
	return saleDate;
}

//void Sale::addItem(Inventory* item, int units, double weight) {
//	if (weight != 0 && units && 0) {
//		this->salePrices.push_back(weight * (item->getPrice()));
//	}
//	else if (units != 0) {
//		this->salePrices.push_back(units * (item->getPrice()));
//	}
//}
//
//double Sale::calculateTotalSale() {
//	for (int i = 0; i < salePrices.size(); i++) {
//		this->saleTotal += salePrices.at(i);
//	}
//	return saleTotal;
//}

void Sale::salePrint() {
	cout << left << setw(30) << this->getName() << setw(5) << this->getUnitsSold() << 
		setw(25) << this->getSaleTotal() << endl;
}