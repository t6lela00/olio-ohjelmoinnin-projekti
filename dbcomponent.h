#ifndef DBCOMPONENT_H
#define DBCOMPONENT_H

#include <vector>

#include <QString>
#include <QDebug>

#include "dbcomponent_global.h"

class DbComponent
{
public:
    bool DBCOMPONENTSHARED_EXPORT getBalance(QString cardNumber, int *balance);
    bool DBCOMPONENTSHARED_EXPORT withdraw(QString cardNumber, int sum);
    bool DBCOMPONENTSHARED_EXPORT getPIN(QString cardNumber, QString *pin);
    bool DBCOMPONENTSHARED_EXPORT getTransactions(QString cardNumber, std::vector<QString> &transactions);
    bool DBCOMPONENTSHARED_EXPORT getAccount(QString cardNumber, QString *account);
};

#endif
