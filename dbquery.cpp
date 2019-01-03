
#include "dbquery.h"

DbQuery::DbQuery() :
    connectionType("QMYSQL"),
    connectionName("yhteys")
{
    db = QSqlDatabase::addDatabase(connectionType, connectionName);
    db.setHostName("esi.merkki.fi");
    db.setDatabaseName("esimerkkitietokanta");
    db.setUserName("esimerkkikayttaja");
    db.setPassword("esimerkkisalasana");
    db.setPort(3306);
    db.open();
}

DbQuery::~DbQuery()
{
    db.close();
    db = QSqlDatabase();
    db.removeDatabase(connectionName);
}

bool DbQuery::getBalance(QString cardNumber, int* balance)
{
    QString account;
    QSqlQuery withdrawSelectQuery(db);

    if(db.isOpen()) {
        if(getAccount(cardNumber, &account)) {
            withdrawSelectQuery.prepare("SELECT sentit FROM BankSimul_Tili WHERE id_tili = :tili");
            withdrawSelectQuery.bindValue(":tili", account);
            if(withdrawSelectQuery.exec()) {
                if(withdrawSelectQuery.next()) {
                    *balance = withdrawSelectQuery.value(0).toInt();
                    return true;
                }
            }
        }
    }
    return false;
}

bool DbQuery::withdraw(QString cardNumber, int sum)
{
    QSqlQuery withdrawUpdateQuery(db);
    int saldo, saldoNostonJalkeen;
    QString account;

    if(db.isOpen()) {
        if(getAccount(cardNumber, &account)) {
            if(getBalance(cardNumber, &saldo)) {
                if(sum <= saldo) {
                    saldoNostonJalkeen = saldo - sum;

                    withdrawUpdateQuery.prepare("UPDATE BankSimul_Tili SET sentit = :saldoNostonJalkeen WHERE id_tili = :tili");
                    withdrawUpdateQuery.bindValue(":tili", account);
                    withdrawUpdateQuery.bindValue(":saldoNostonJalkeen", saldoNostonJalkeen);
                    if(withdrawUpdateQuery.exec()) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool DbQuery::getAccount(QString cardNumber, QString* account)
{
    QSqlQuery accountSelectQuery(db);

    if(db.isOpen()) {
        accountSelectQuery.prepare("SELECT id_tili FROM BankSimul_Kortti WHERE id_kortti = :kortti");
        accountSelectQuery.bindValue(":kortti", cardNumber);
        if(accountSelectQuery.exec()) {
            if(accountSelectQuery.next()) {
                *account = accountSelectQuery.value(0).toString();
                return true;
            }
        }
    }
    return false;
}

bool DbQuery::getPIN(QString cardNumber, QString *pin)
{
    QSqlQuery pinSelectQuery(db);

    if(db.isOpen()) {
        pinSelectQuery.prepare("SELECT tunnusluku FROM BankSimul_Kortti WHERE id_kortti = :kortti");
        pinSelectQuery.bindValue(":kortti", cardNumber);
        if(pinSelectQuery.exec()) {
            if(pinSelectQuery.next()) {
                *pin = pinSelectQuery.value(0).toString();
                return true;
            }
        }
    }
    return false;
}

bool DbQuery::getTransactions(QString cardNumber, std::vector<QString> &transactions)
{
    QSqlQuery transactionSelectQuery(db);
    QString account;

    if(db.isOpen()) {
        if(getAccount(cardNumber, &account)) {
            transactionSelectQuery.prepare("SELECT muutos, ts FROM BankSimul_Tilitapahtumat WHERE id_tili = :tili ORDER BY ts DESC LIMIT 10");
            transactionSelectQuery.bindValue(":tili", account);
            if(transactionSelectQuery.exec()) {
                while(transactionSelectQuery.next()) {
                    transactions.push_back(transactionSelectQuery.value(0).toString());
                    transactions.push_back(transactionSelectQuery.value(1).toString());
                    QString* date;
                    date = &(transactions[transactions.size() - 1]);
                    if(date->contains("T")) {
                        (*date)[date->indexOf("T")] = QChar(' ');
                    }
                }
                return true;
            }
        }
    }
    return false;
}
