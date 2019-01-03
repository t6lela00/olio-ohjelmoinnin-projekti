#ifndef DBQUERY_H
#define DBQUERY_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

#include <vector>

class DbQuery
{
public:
    DbQuery();
    ~DbQuery();

    bool getBalance(QString account, int *balance);
    bool withdraw(QString account, int sum);
    bool getPIN(QString cardNumber, QString *pin);
    bool getTransactions(QString cardNumber, std::vector<QString> &transactions);
    bool getAccount(QString cardNumber, QString* account);

private:
    QString connectionType;
    QString connectionName;
    QSqlDatabase db;
};

#endif // DBQUERY_H
