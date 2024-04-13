#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "Inventory.h"
#include "InventoryList.h"
#include "Order.h"
#include "Sale.h"
#include "Menu.h"

/*
*  supplierOrder() & order() have been moved into Menu class.
*  selection() has also been moved into Menu class
*
*   -JW
*/

//Main loop will be done here
int main() {

	//Test code commented out -JMV

	/*
	string* category = nullptr;
	int* ID = nullptr;
	string* itemName = nullptr;
	double* price = nullptr;
	Inventory* item = nullptr;
	InventoryList* Inlist = nullptr;

	//Create inventory items here


	//Inventory Test
	category = new string("Category 1");
	ID = new int(0);
	itemName = new string("Bottle of Water");
	price = new double(1.0);
	item = new Inventory(*category, *ID, *itemName, *price);
	item->print();
	delete category;
	delete ID;
	delete itemName;
	delete price;
	delete item;
	*/

	//pointer to a menu item that contains all menu functions -JW
	Menu* menu = new Menu();

	vector<InventoryList*> allLists;
	//allLists contains each inventory list where the list at 0 is all lists and 1-11 are category specified -JMV

	InventoryList* inList = nullptr;
	inList = new InventoryList();
	allLists.push_back(inList);

	//Separate lists for orders and sales because I found it easier.
	//Sale list will probably need to be passed to all menu functions as a parameter as well. -JMV
	vector<Order*> orderList;
	vector<Sale*> saleList;

	//Iteration amount is the amount of files we'll have for inventory minus one -JMV
	for (int i = 0; i < 11; i++) { 
		InventoryList* fileList = new InventoryList();
		allLists.push_back(fileList);
	}

	cout << "Welcome to Primo POS!" << endl << endl;

	//runs selection menu until given exit answer. -JW
	while (true) {
		if (menu->selection(allLists, orderList, saleList) == 4) {
			break;
		}
	}

	//delete all lists
	for (int i = 0; i < allLists.size(); i++) {
		if (allLists.at(i)->listSize() > 0) {
			delete allLists.at(i);
		}
	}
	
	//delete all orders
	for (int i = 0; i < orderList.size(); i++) {
		delete orderList[i];
	}
	
	//delete all sales
	for (int i = 0; i < saleList.size(); i++) {
		delete saleList[i];
	}
	
	//delete menu
	delete menu;

	cout << "Goodbye!" << endl;

	return 0;

}
