#pragma once
#ifndef INVENTORYLIST_H_
#define INVENTORYLIST_H_
#include <vector>
#include "Inventory.h"


class InventoryList
{
private:
	vector<Inventory> *list;
public:
	InventoryList();
	InventoryList(const Inventory);
	InventoryList(const InventoryList&);
	~InventoryList();
	void listAdd(const Inventory);
	Inventory* listGetByID(int); //Modified to be a reference -JMV
	void listRemoveByID(int);
	bool listContainsID(int); //-JMV
	void checkThresholds(); //-JMV
	void listPrint(); //-JMV
	int listSize();
	void saveList(string filename = "InventoryList");
	void loadList(string filename = "InventoryList");
};

#endif // !INVENTORYLIST_H_
