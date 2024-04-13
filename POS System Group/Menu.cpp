/*
*   Contains methods for menu funcationality
*   Meant to help keep main light
*   -JW
*/

#include "Menu.h"
#include "Balance.h"
#include <string>
#include <iostream>
#include <iomanip>



/*
*	The primary function for inventory supplying
*	Takes an inventory list as the parameter which should only ever be the list of all lists
*
*
*	FEATURES:
*	proper menu functionality
*	items can be fully made and added to the parameter's list, continuing until the user specifies that they're done
*	individual lists are updated as well as a comprehensive list
*	a notification is generated for quantities below thresholds
*	specific items can be resupplied using their IDs
*	requests supplier details then makes an order record for both normal orders and resupply orders in the orderList vector
*
*	-JMV
*/

Menu::Menu() {}
Menu::~Menu() {}

int Menu::selection(vector<InventoryList*>& allLists, vector<Order*>& orderList, vector<Sale*>& saleList) { //-JMV
	int input = 0;
	cout << "Please choose a type of action: " << endl;
	cout << "(1) Place Orders" << endl;
	cout << "(2) Make Sales" << endl;
	cout << "(3) Management" << endl;
	cout << "(4) Exit Primo POS" << endl << endl;
	cin >> input;

	if (input == 1) {
		order(allLists, orderList);
	}
	else if (input == 2) {
		sale(allLists, orderList, saleList);
	}
	else if (input == 3) {
		//manage inventory branch
		//Charles may want to start here
		Management:
		cout << "(1) Calculate Balance" << endl;
		cout << "(2) Load Inventory from file" << endl;
		
		cin >> input;
		if (input == 1) {
			//calculate balance
			calcBalance(orderList, saleList);
		}
		else if (input == 2) {
			//load inventory from file
			loadList(allLists);
		}
		else {
			cout << "Invalid input" << endl;
			goto Management;
		}
	}

	return input;
}

void Menu::calcBalance(vector<Order*>& orderList, vector<Sale*>& saleList) {
	static vector<Balance*> balanceList;
	double totalDebt = 0;
	double totalSale = 0;
	
	if (orderList.size() > 0) {
		for (int i = 0; i < orderList.size(); i++) {
			totalDebt += orderList.at(i)->getOrderDebt();
		}
	}
	if (saleList.size() > 0) {
		for (int i = 0; i < saleList.size(); i++) {
			totalSale += saleList.at(i)->getSaleTotal();
		}
	}

	Balance* balance = new Balance(totalSale - totalDebt, totalDebt, totalSale);
	balanceList.push_back(balance);

	cout << left << setw(25) << "Date" << setw(25) << "Total Debt" << setw(25) << "Total Sales" << setw(25) << "Balance" << setw(25) << "Invoice ID" << endl;
	//cout << left << setw(25) << getDateTime() << setw(25) << totalDebt << setw(25) << totalSale << setw(25) << totalSale - totalDebt << endl;
	for (Balance* b : balanceList) {
		cout << left << setw(25) << getDateTime() << setw(25) << b->getDebt() << setw(25) << b->getSales() << setw(25) << b->getBalance() << "Invoice#" << b->getInvoiceID() << endl;
	}
}

string Menu::getDateTime() {
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "%m/%d/%Y - %I:%M:%S", timeinfo);
	
	return buffer;
}

void Menu::loadList(vector<InventoryList*>& allLists) {
	cout << "(1) Load from Default" << endl;
	cout << "(2) Load from user input" << endl;

	int input;
	string userString;

	cin >> input;
	switch (input) {
	case 1:
		allLists.at(0)->loadList();
		break;
	case 2:
		cout << "Enter name of file: ";
		cin >> userString;
		allLists.at(0)->loadList(userString);
		break;
	default:
		cout << input << " is not a possible option." << endl;
	}
}

void Menu::order(vector<InventoryList*>& allLists, vector<Order*>& orderList) {
	vector<string> validCategories = { "Beverages", "Bread", "Snacks", "Dairy", "Grains & Pasta", "Fruits & Vegetables",
										"Meat & Seafood", "Miscellaneous", "Paper Products", "Pet Care", "Pharmacy" };
	int input = 0;
	int category = -1;
	int id = 0;
	string itemName;
	double price = 0;
	int quantity = 0;
	int threshold = 0;

	allLists.at(0)->checkThresholds();
	cout << "Would you like to supply something to the Inventory?" << endl;

	while (input != 6) {
		cout << "(1) Display Current Inventory" << endl;
		cout << "(2) Display Current Orders" << endl;
		cout << "(3) Order More Inventory" << endl;
		cout << "(4) Resupply by ID" << endl;
		cout << "(5) Complete Delivery" << endl;
		cout << "(6) Previous Menu" << endl << endl;
		cin >> input;

		if (input == 1) {
			cout << left << setw(10) << "Quantity" << setw(25) << "Category" << setw(10)
				<< "ID" << setw(25) << "Item Name" << setw(5) << "Price" << endl;

			//allLists.at(0) = new InventoryList;
			//allLists.at(0)->loadList();
			allLists.at(0)->listPrint();
			cout << endl;
		}
		else if (input == 2) {
			cout << left << setw(25) << "Date" << setw(25)
				 << "Item Name" << setw(25) << "Item Count" << setw(25)
				 << "Supplier" << setw(25) << "Address" << setw(25)
				 << "Email" << setw(15) << "Phone #" << setw(15)
				 << "Delivered" << setw(8) << "Cost" << endl;
			for (int i = 0; i < orderList.size(); i++) {
				orderList.at(i)->orderPrint();
			}
		}
		else if (input == 3) {
			char userContinue = 'T';
			while (userContinue != 'F' && userContinue != 'f') {

				cout << "Valid categories are: " << endl;

				for (int i = 0; i < validCategories.size(); ++i) {
					cout << "(" << i + 1 << ") " << validCategories.at(i) << endl;
				}

				cout << "Enter a category number (1 through 11): " << endl;
				cin >> category;
				category--;
				while (category < 0 && category >= validCategories.size()) {
					cout << "Invalid category. Valid categories are: " << endl;
					for (int i = 0; i < validCategories.size(); ++i) {
						cout << "(" << i + 1 << ") " << validCategories.at(i) << endl;
					}
					cout << "Enter a category: " << endl;
					cin >> category;
					category--;
				}

				cout << "Enter an integer ID: " << endl;
				cin >> id;
				while (allLists.at(0)->listContainsID(id) || id < 0) {
					cout << "ID invalid. Please enter another ID. It must be unique and above 0: " << endl;
					cin >> id;
				}

				cout << "Enter a name for the item: " << endl;
				getline(cin >> ws, itemName);

				cout << "Enter a price: " << endl;
				cin >> price;
				while (price < 0.01) {
					cout << "Invalid price. Enter price higher than $0.00: " << endl;
					cin >> price;
				}

				cout << "Enter a quantity" << endl;
				cin >> quantity;
				while (quantity < 1) {
					cout << "Invalid quantity. Order at least 1: " << endl;
					cin >> quantity;
				}

				cout << "Enter an internal threshold for inventory quantity: " << endl;
				cin >> threshold;
				while (threshold < 0) {
					cout << "Invalid threshold. Enter a non-negative integer: " << endl;
					cin >> threshold;
				}

				Inventory* item = new Inventory(validCategories.at(category), id, itemName, price, quantity, threshold);
				supplierOrder(orderList, item);

				cout << "Continue? (T/F): ";
				cin >> userContinue;
			}
		}
		else if (input == 4) {
			int userInput = 0;
			while (userInput >= 0) {
				cout << "Please enter the ID of the item to resupply (-1 returns to previous menu): " << endl;
				cin >> userInput;
				if (userInput < 0) {
					break;
				}
				else if (allLists.at(0)->listContainsID(userInput)) {
					int qtyToAdd = 0;
					cout << "Enter quantity to resupply (or take away if negative): " << endl;
					cin >> qtyToAdd;
					//allLists.at(0)->listGetByID(userInput)->addCount(qtyToAdd);
					//int currentCategory = allLists.at(0)->listGetByID(userInput)->getCategoryInt();
					//allLists.at(currentCategory)->listGetByID(userInput)->addCount(qtyToAdd);

					//you can probably tell I was getting tired here but it seems like it works lol -JMV
					Inventory item = *allLists.at(0)->listGetByID(userInput);
					item.setCount(qtyToAdd);
					//int oldQty = item->getCount();
					//item->setCount(qtyToAdd);
					supplierOrder(orderList, &item);
					//item->setCount(oldQty);

					//cout << "Quantity is now: " << allLists.at(0)->listGetByID(userInput)->getCount() << endl;
				}
				else {
					cout << "ID not in list." << endl << endl;
				}
			}
		}
		else if (input == 5) {
			completeDelivery(allLists, orderList, validCategories); //edited to not have category -JMV
			cout << "Delivery Completed / Inventory has been updated." << endl << endl;
		}
	}
}

void Menu::completeDelivery(vector<InventoryList*> &allLists, vector<Order*> &orderList, vector<string> validCategories) {
	//Inventory* item = nullptr;
	if (orderList.size() == 0) {
		cout << "No orders to complete." << endl;
	}
	else {
		for (Order* order : orderList) {
			if (order->getDelivered() == "Transit") {
				order->deliver();
				string category = order->getCategory();
				int id = order->getID();
				string itemName = order->getName();
				int quantity = order->getCount();
				double price = order->getPrice();
				int threshold = order->getThreshold();
				Inventory* item = new Inventory(category, id, itemName, price, quantity, threshold);

				allLists.at(0)->listAdd(*item);
				allLists.at(order->getCategoryInt())->listAdd(*item); //adds to list of respective category as well -JMV
			}
		}
	}

	allLists.at(0)->saveList();
	for (int i = 1; i < allLists.size(); i++) {
		allLists.at(i)->saveList(validCategories.at(i - 1));
	}
}

/*
*	This function is called for each order and resupply. The user enters all the relevant details
*	of the supplier for the item requested and both the snapshotted inventory details and supply details
*	are stored in the orderList vector.
*	For debugging and user convenience, the option to repeat the last supplier is provided.
*
*	-JMV
*/
void Menu::supplierOrder(vector<Order*>& orderList, Inventory* item) {
	char choice = 'F';
	cout << "Provide the supplier's details." << endl;

	if (orderList.size() > 0) {
		cout << "Would you like to use the same supplier as the last order? (T/F): " << endl;
		cin >> choice;
	}
	
	if ((choice == 't' || choice == 'T') && orderList.size() > 0) {
		Order* previousOrder = orderList.at(orderList.size() - 1);
		Order* currentOrder = new Order(item, previousOrder->getSupplier(),
			previousOrder->getContactAddress(), previousOrder->getEmailAddress(), previousOrder->getPhoneNumber());
		orderList.push_back(currentOrder);

	}
	else {
		string supplier;
		string contactAddress;
		string emailAddress;
		string phoneNumber;
		int phoneNum = 0;

		cout << "Enter the supplier's name: " << endl;
		getline(cin >> ws, supplier);

		cout << "Enter their contact address: " << endl;
		getline(cin, contactAddress);

		cout << "Enter their email address: " << endl;
		getline(cin, emailAddress);

		cout << "Enter their phone number (form ##########): " << endl;
		cin >> phoneNumber;
		
		PhoneNumCheck:
		while (phoneNumber.size() != 10) {
			cout << "Invalid phone number, must be 10 digits." << endl;
			cin >> phoneNumber;
		}

		try {
			phoneNum = stoi(phoneNumber);
		}
		catch (exception e) {
			cout << "Invalid phone number, must be 10 digits." << endl;
			cin >> phoneNumber;
			goto PhoneNumCheck;
		}

		
		
		Order* order = new Order(item, supplier, contactAddress, emailAddress, phoneNum);
		orderList.push_back(order);
		
	}
	cout << "Order will be delivered." << endl << endl;

}

/*
*  Primary function for customer sales
*
*
* -JW
*/
void Menu::sale(vector<InventoryList*>& allLists, vector<Order*>& orderList, vector<Sale*>& saleList) {
	vector<string> validCategories = { "Beverages", "Bread", "Snacks", "Dairy", "Grains & Pasta", "Fruits & Vegetables",
									"Meat & Seafood", "Miscellaneous", "Paper Products", "Pet Care", "Pharmacy" };
	int input = 0;
	cout << "Would you like to sell an item?" << endl;
	while (input != 3) {
		cout << "(1) Add an item to cart" << endl;
		cout << "(2) Checkout" << endl;
		cout << "(3) Previous Menu" << endl << endl;
		cin >> input;

		if (input == 1) {
			/// Getting Customer name and phone number for records as requested in project statement. - JW
			//string custName;
			//cout << "Please enter customer name: " << endl;
			//cin >> custName;
			 
			//int custPhone;
			//cout << "Please enter customer phone number: " << endl;
			//cin >> custPhone;

			int category = 0;
			int id = 0;
			int quantity = 0;

			for (int i = 0; i < validCategories.size(); i++) {
				cout << "(" << i + 1 << ") " << validCategories.at(i) << endl;
			}
			cout << "Please enter the category of the item you would like to sell: " << endl;
			cin >> category;
			while (category < 1 || category > validCategories.size()) {
				cout << "Invalid category, please enter a number between 1 and " << validCategories.size() << "." << endl;
				cin >> category;
			}
			allLists.at(category) = new InventoryList;
			allLists.at(category)->loadList(validCategories.at(category - 1));
			while (allLists.at(category)->listSize() == 0) {
				cout << "There are no items in this category, please select another." << endl;
				cin >> category;
				while (category < 1 || category > validCategories.size()) {
					cout << "Invalid category, please enter a number between 1 and " << validCategories.size() << "." << endl;
					cin >> category;
				}
				allLists.at(category)->loadList(validCategories.at(category - 1));
			}
			allLists.at(category)->listPrint();
			cout << "Please enter the ID of the item you would like to sell: " << endl;
			cin >> id;
			while (!allLists.at(category)->listContainsID(id)) {
				cout << "Invalid ID, please enter a valid ID." << endl;
				cin >> id;
			}
			cout << "Please enter the quantity of the item you would like to sell: " << endl;
			cin >> quantity;
			while (quantity < 1) {
				cout << "Invalid quantity, please enter a quantity greater than 0." << endl;
				cin >> quantity;
			}

			Inventory* item = allLists.at(0)->listGetByID(id);

			if (item->getCount() < quantity) {
				cout << "Not enough items in stock, please enter a quantity less than " << item->getCount() << "." << endl;
				cin >> quantity;
			}
			else {
				item->addCount(-quantity);
				//allLists.at(0)->listGetByID(id)->addCount(-quantity);
				allLists.at(category)->listGetByID(id)->addCount(-quantity);
				Sale* sale = new Sale(item, quantity);
				saleList.push_back(sale);
				
				cout << "Item has been added to the customer's cart." << endl << endl;
			}

			allLists.at(0)->saveList();
			allLists.at(category)->saveList(validCategories.at(category - 1));
		}
		else if (input == 2) {
			if (saleList.size() == 0) {
				cout << "No items in customer's cart." << endl << endl;
			}
			else {
				double totalSale = 0;

				cout << "Items currently in Customer's Cart: " << endl;
				cout << left << setw(30) << "Name" << setw(30) << "Quantity" << setw(30) << "Price" << endl;
				for (int i = 0; i < saleList.size(); i++) {
					///Moved into salePrint in sale class
					//cout << left << setw(30) << saleList.at(i)->getName() << setw(5) << saleList.at(i)->getUnitsSold() 
					//<< setw(25) << saleList.at(i)->getSaleTotal() << endl; 
					saleList.at(i)->salePrint();
					totalSale += saleList.at(i)->getSaleTotal();
				}
				cout << "Total Sale: " << totalSale << endl << endl;

				///Customer paying for items - JW
				double payment;
				double amountDue = totalSale;
				bool paid = false;
				cout << "Please enter the amount paid: " << endl;
				while (paid == false) {
					cin >> payment;
					if (payment < amountDue) {
						//Paid partially - JW
						amountDue = amountDue - payment;
						cout << "Insufficient payment.\n New total: " << amountDue << endl << endl;
						cout << "Please continue entering payment: " << endl;
					}
					else if (amountDue == payment) {
						//paid in full - JW
						cout << "Payment completed." << endl;
						cout << "Exiting Checkout..." << endl;
						paid = true;
					}
					else if (payment > amountDue) {
						//overpaid, thus has change - JW
						double change = payment - amountDue;
						cout << "Payment completed." << endl;
						cout << "The customer's change is: $" << change << endl;
						cout << "Exiting Checkout..." << endl << endl;
						paid = true;
					}
				}
			}
		}
		else if (input == 3) {
			cout << "Returning to previous menu..." << endl << endl;
		}
		else {
			cout << "Invalid input, please enter a number between 1 and 3." << endl << endl;
		}
	}
}