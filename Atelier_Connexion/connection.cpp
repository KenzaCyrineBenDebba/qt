#include "connection.h"

Connection::Connection()
{

}

bool Connection::ouvrirConnection()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projet_2a");
db.setUserName("kenza");//inserer nom de l'utilisateur
db.setPassword("181JFT0998");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;
    return  test;
}

void Connection::fermerConnection()
{db.close();}
