#include "InventoryList.h"
#include <vector>
#include <iostream>
#include <fstream>


//initializes vector list to nullptr
InventoryList::InventoryList() {
	//list = nullptr; //Couldn't this be a new inventory vector? -JMV
	list = new vector<Inventory>;
}
//I changed it to a new vector since I was running into other problems that were since fixed by the change -JMV

//initializes vector list with first item
InventoryList::InventoryList(const Inventory item) {
	list = new vector<Inventory>;
	list->push_back(item);
}

//copy constructor
InventoryList::InventoryList(const InventoryList& inList) {
	this->list = inList.list;
}

InventoryList::~InventoryList()
{
}

int InventoryList::listSize() {
	return list->size();
}

//adds inventory item to vector
void InventoryList::listAdd(Inventory item) {
	if (list == nullptr) {
		list = new vector<Inventory>;
	}
	
	if (list->size() == 0) {
		list->push_back(item);
		return;
	}
	else {
		for (int i = 0; i < list->size(); i++) {
			if (list->at(i).getID() == item.getID()) {
				list->at(i).setCount(list->at(i).getCount() + item.getCount());
				return;
			}
		}
		list->push_back(item);
	}
}

//gets reference to item by id
Inventory* InventoryList::listGetByID(int ID) {
	for (int i = 0; i < list->size(); ++i) {
		if (list->at(i).getID() == ID) {
			Inventory *item = &list->at(i);
			return item;
		}
	}
	Inventory *item = nullptr;
	return item;
}

//removes item by id
void InventoryList::listRemoveByID(int ID) {
	for (int i = 0; i < list->size(); ++i) {
		if (list->at(i).getID() == ID) {
			list->erase(list->begin() + i);
		}
	}
}

//checks if ID is contained -JMV
bool InventoryList::listContainsID(int ID) {
	for (int i = 0; i < list->size(); ++i) {
		if (list->at(i).getID() == ID) {
			return true;
		}
	}
	return false;
}

//checks quantities and thresholds in the list, notifying the user if the result is unsatisfactory -JMV
void InventoryList::checkThresholds() {
	int count = 0;
	for (int i = 0; i < list->size(); ++i) {
		if (list->at(i).getCount() < list->at(i).getThreshold()) {
			cout << "URGENT: item ID " << list->at(i).getID() << " is below threshold of " << 
				list->at(i).getThreshold() << " at " << list->at(i).getCount() << endl;
			count++;
		}
	}
	if (count > 0) {
		cout << "It is advised to resupply these items with haste" << endl << endl;
	}
}

//prints the elements of the list -JMV
void InventoryList::listPrint() {
	if (list != nullptr) {
		for (int i = 0; i < list->size(); ++i) {
			list->at(i).print();
		}
	}
}

void InventoryList::saveList(string filename) {
	fstream out;
	out.open("./savedLists/" + filename + ".txt", ios::out | ios::trunc);
	if (!out.is_open()) {
		cout << filename << " failed to open" << endl;
	}

	for (Inventory item : *list) {
		out << item.getCategory() << ","
			<< item.getID() << ","
			<< item.getName() << ","
			<< item.getPrice() << ","
			<< item.getCount() << ","
			<< item.getThreshold() << endl;
	}

	out.close();
}

void InventoryList::loadList(string filename) {
	fstream in;
	string inCat;
	int inID;
	string inName;
	double inPrice;
	int inCount;
	int inThresh;
	in.open("./savedLists/" + filename + ".txt", ios::in);
	
	if (!in.is_open()) {
		cout << filename << " failed to open" << endl;
	}

	//char* buffer = "";
	/*while (in >> inCat >> inID >> inName >> inPrice >> inCount >> inThresh) {
		Inventory item(inCat, inID, inName, inPrice, inCount, inThresh);
		this->listAdd(item);
	}*/
	while (in.good()) {
		string input;
		
		getline(in, input, '\n');
		if (input == "") {
			break;
		}
		
		//split input into variables
		inCat = input.substr(0, input.find(','));
		input = input.substr(input.find(',') + 1);
		inID = stoi(input.substr(0, input.find(',')));
		input = input.substr(input.find(',') + 1);
		inName = input.substr(0, input.find(','));
		input = input.substr(input.find(',') + 1);
		inPrice = stod(input.substr(0, input.find(',')));
		input = input.substr(input.find(',') + 1);
		inCount = stoi(input.substr(0, input.find(',')));
		input = input.substr(input.find(',') + 1);
		inThresh = stoi(input);
		
		Inventory item(inCat, inID, inName, inPrice, inCount, inThresh);
		this->listAdd(item);
	}

	in.close();
}