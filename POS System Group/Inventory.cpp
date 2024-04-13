#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>
#include "Inventory.h"


//Create methods here
//Date info moved to order definition -JMV
Inventory::Inventory() {
	category = "";
	ID = NULL;
	itemName = "";
	price = NULL;
	count = 0;
	threshold = 0;
}

Inventory::Inventory(string category = "", int ID = NULL, string itemName = "", double price = NULL, int quantity = 0, int threshold = 0) {
	this->category = category;
	this->ID = ID;
	this->itemName = itemName;
	this->price = price;
	this->count = quantity;
	this->threshold = threshold;
}

Inventory::Inventory(const Inventory& item) {
	this->category = item.category;
	this->ID = item.ID;
	this->itemName = item.itemName;
	this->price = item.price;
	this->count = item.count;
	this->threshold = item.threshold;
}

Inventory::~Inventory()
{
}

int Inventory::getCount() {
	return this->count;
}

void Inventory::setThreshold(int threshold) {
	this->threshold = threshold;
}

int Inventory::getThreshold()
{
	return this->threshold;
}

string Inventory::getCategory() {
	return this->category;
}

void Inventory::setCategory(string category) {
	this->category = category;
}

//sometimes helpful for list access; will return index of the respective list  -JMV
int Inventory::getCategoryInt() {
	if (getCategory() == "Beverages") {
		return 1;
	}
	else if (getCategory() == "Bread") {
		return 2;
	}
	else if (getCategory() == "Snacks") {
		return 3;
	}
	else if (getCategory() == "Dairy") {
		return 4;
	}
	else if (getCategory() == "Grains/Pasta") {
		return 5;
	}
	else if (getCategory() == "Produce: Fruits & Vegetables") {
		return 6;
	}
	else if (getCategory() == "Meat & Seafood") {
		return 7;
	}
	else if (getCategory() == "Miscellaneous") {
		return 8;
	}
	else if (getCategory() == "Paper Products") {
		return 9;
	}
	else if (getCategory() == "Pet Care") {
		return 10;
	}
	else {
		//Category is Pharmacy
		return 11;
	}
}

void Inventory::setID(int ID) {
	this->ID = ID;
}

int Inventory::getID() {
	return this->ID;
}

void Inventory::setName(string name) {
	this->itemName = name;
}

string Inventory::getName() {
	return this->itemName;
}

void Inventory::setPrice(double price) {
	this->price = price;
}

double Inventory::getPrice() {
	return this->price;
}

//Additional quantity and threshold getters and setters -JMV
void Inventory::setCount(int count) {
	this->count = count;
}

void Inventory::addCount(int toAdd) {
	this->count += toAdd;
}

void Inventory::subCount() {
	this->count--;
}

//Prints the node with a predefined format
//Date info moved to order definition -JMV
void Inventory::print() {
	cout << left << setw(10) << this->getCount() << setw(25)
		<< this->getCategory() << setw(10) << this->getID() << setw(25) 
		<< this->getName() << fixed << setprecision(2) << "$" << setw(5) << this->getPrice() << endl;
}
