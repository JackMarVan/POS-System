#ifndef MENU_H
#define MENU_H
#include "Inventory.h"
#include "InventoryList.h"
#include "Order.h"
#include "Sale.h"


class Menu {
public:
	Menu();
	~Menu();
	int selection(vector<InventoryList*>& allLists, vector<Order*>& orderList, vector<Sale*>& saleList); //Default menu selection - JMV
	void order(vector<InventoryList*>& allLists, vector<Order*>& orderList); //The primary function for inventory supplying - JMV
	void sale(vector<InventoryList*>& allLists, vector<Order*>& orderList, vector<Sale*>& saleList); //The primary function for customer sales - JW
	void supplierOrder(vector<Order*>& orderList, Inventory* item); //This function is called for each order and resupply - JMV
	void loadList(vector<InventoryList*>& allLists);
	void calcBalance(vector<Order*>& orderList, vector<Sale*>& saleList);
	string getDateTime();
	void completeDelivery(vector<InventoryList*> &allLists, vector<Order*> &orderList, vector<string>);

};


#endif // !MENU_H

