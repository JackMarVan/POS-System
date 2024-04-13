#pragma once
#ifndef SALE_H_
#define SALE_H_
#include "Inventory.h"
#include <vector>

//Sales class extends InvetoryList class
class Sale :
    public Inventory
{
private:
    int unitsSold;
    //double weightSold;
    double saleTotal;
    //string customerName;
    //int customerPhoneNumber;
    string saleDate;
    //vector<int> salePrices;

public:
    Sale();
	Sale(Inventory* item, int u);
    Sale(const Sale&);
    ~Sale();
	int getUnitsSold();
    double getSaleTotal();
	string getSaleDate();

    //double calculateTotalSale();
    //void addItem(Inventory* item, int u, double w);
    void salePrint();
};

#endif // !SALE_H_

