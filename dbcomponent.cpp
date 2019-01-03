
#include "dbcomponent.h"
#include "dbquery.h"

bool DbComponent::getBalance(QString cardNumber, int* balance)
{
    bool status;
    DbQuery *olioDbQuery = new DbQuery;
    status = olioDbQuery->getBalance(cardNumber, balance);
    delete olioDbQuery;
    return status;
}

bool DbComponent::withdraw(QString cardNumber, int sum)
{
    bool status;
    DbQuery *olioDbQuery = new DbQuery;
    status = olioDbQuery->withdraw(cardNumber, sum);
    delete olioDbQuery;
    return status;
}

bool DbComponent::getPIN(QString cardNumber, QString *pin)
{
    bool status;
    DbQuery *olioDbQuery = new DbQuery;
    status = olioDbQuery->getPIN(cardNumber, pin);
    delete olioDbQuery;
    return status;
}

bool DbComponent::getTransactions(QString cardNumber, std::vector<QString> &transactions)
{
    bool status;
    DbQuery *olioDbQuery = new DbQuery;
    status = olioDbQuery->getTransactions(cardNumber, transactions);
    delete olioDbQuery;
    return status;
}

bool DbComponent::getAccount(QString cardNumber, QString *account)
{
    bool status;
    DbQuery *olioDbQuery = new DbQuery;
    status = olioDbQuery->getAccount(cardNumber, account);
    delete olioDbQuery;
    return status;
}
