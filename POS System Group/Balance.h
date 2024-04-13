#pragma once
#ifndef BALANCE_H_
#define BALANCE_H_
#include <string>

using namespace std;

class Balance
{
private:
	string date;
	double balance;
	double debt;
	double sales;
	int currentInvoiceID;
public:
	Balance();
	Balance(double, double, double);
	Balance(const Balance&);
	~Balance();
	double getBalance();
	void setBalance(double);
	double getDebt();
	void setDebt(double);
	double getSales();
	void setSales(double);
	int getInvoiceID();
	//void balancePrint();
};


#endif // !BALANCE_H_
