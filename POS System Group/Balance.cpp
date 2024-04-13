#include "Balance.h"

static int invoiceID;

Balance::Balance()
{
	balance = 0;
	debt = 0;
	sales = 0;
	currentInvoiceID = invoiceID++;
}

Balance::Balance(double b, double d, double s)
{
	balance = b;
	debt = d;
	sales = s;
	currentInvoiceID = invoiceID++;
}

Balance::Balance(const Balance& balance)
{
	this->balance = balance.balance;
	this->debt = balance.debt;
	this->sales = balance.sales;
	this->currentInvoiceID = balance.currentInvoiceID;
}

Balance::~Balance()
{
}

double Balance::getBalance()
{
	return balance;
}

void Balance::setBalance(double b)
{
	balance = b;
}

double Balance::getDebt()
{
	return debt;
}

void Balance::setDebt(double d)
{
	debt = d;
}

double Balance::getSales()
{
	return sales;
}

void Balance::setSales(double s)
{
	sales = s;
}

int Balance::getInvoiceID()
{
	return currentInvoiceID;
}
