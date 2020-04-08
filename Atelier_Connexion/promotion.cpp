#include "promotion.h"
#include <QString>
#include <QSqlQuery>
#include<QSqlQueryModel>

promotion::promotion()
{
    id=0;
    nom_client="";
    pourcentage="";
    nombre_colis=0;
}

promotion::promotion(int id, QString nom_client, QString pourcentage,int nombre_colis)
{
    this ->id=id;
    this->nom_client=nom_client;
    this->pourcentage=pourcentage;
    this ->nombre_colis=nombre_colis;
}

QString promotion::get_nom_client() {return nom_client;}
QString promotion::get_pourcentage() {return pourcentage;}
int promotion::get_id() {return id;}
int promotion::get_nombre_colis() {return nombre_colis;}

bool promotion::ajouter()
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("INSERT INTO promotion (id,nom_client,pourcentage,nombre_colis)"
                  "VALUES (:id, :nom_client, :pourcentage, :nombre_colis)");
    query.bindValue(":id",res);
    query.bindValue(":nom_client",nom_client);
    query.bindValue(":pourcentage",pourcentage);
    query.bindValue(":nombre_colis", nombre_colis);
    return query.exec();

}

QSqlQueryModel * promotion::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from promotion");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_CLIENT "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("POURCENTAGE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOMBRE_COLIS"));
    return model;
}

bool promotion::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from promotion where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}

bool promotion::modifier(int idd,QString nom_client,QString pourcentage,int nombre_colis)
{ QSqlQuery query;
    QString res= QString::number(idd);
    query.prepare("UPDATE promotion SET NOM_CLIENT=:nom_client,POURCENTAGE=:pourcentage ,NOMBRE_COLIS=:nombre_colis where ID=:id");
    query.bindValue(":id",res);
    query.bindValue(":nom_client",nom_client);
    query.bindValue(":pourcentage",pourcentage);
     query.bindValue(":nombre_colis",nombre_colis);
    return query.exec();

}

QSqlQueryModel *  promotion::rechercher(int id)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    QString res=QString::number(id);
    model->setQuery("select * from promotion where (id LIKE '"+res+"%' ) ");


            return  model;


}
QSqlQueryModel * promotion::trier()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from promotion ORDER BY nom_client");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("nom_client "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("pourcentage"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("nombre_colis"));
        return model;
}



