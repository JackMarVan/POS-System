#pragma once
#ifndef INVENTORY_H_
#define INVENTORY_H_
#include <string>

using namespace std;

class Inventory
{
private:
	string category;
	int ID;
	//string itemName;
	int threshold;
protected:
	string itemName;
	double price;
	int count;
public:
	Inventory();
	Inventory(string, int, string, double, int, int);
	Inventory(const Inventory&);
	~Inventory();
	void setCount(int);
	int getCount();
	void setThreshold(int); //-JMV
	int getThreshold();
	void addCount(int);
	void subCount();
	void setCategory(string);
	string getCategory();
	int getCategoryInt(); //-JMV
	void setID(int);
	int getID();
	void setName(string);
	string getName();
	void setPrice(double);
	double getPrice();
	void print(); //-JMV
};

#endif

