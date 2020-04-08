#include "joursferies.h"
#include <QString>
#include <QSqlQuery>
#include<QSqlQueryModel>

joursferies::joursferies()
{
    nom_jour="";
    jour=0;
    mois="";
}

joursferies::joursferies( QString nom_jour,int jour, QString mois)
{
    this->nom_jour=nom_jour;
    this ->jour=jour;
    this->mois=mois;

}

int joursferies::get_jour() {return jour;}
QString joursferies::get_nom_jour() {return nom_jour;}
QString joursferies::get_mois() {return mois;}


bool joursferies::ajouter2()
{
    QSqlQuery query;
    QString res=QString::number(jour);
    query.prepare("INSERT INTO joursferies (jour,nom_jour,mois)"
                  "VALUES (:jour, :nom_jour, :mois)");
    query.bindValue(":jour",res);
    query.bindValue(":nom_jour",nom_jour);
    query.bindValue(":mois",mois);
    return query.exec();

}

QSqlQueryModel * joursferies::afficher2()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from joursferies");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_CLIENT "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("POURCENTAGE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOMBRE_COLIS"));
    return model;
}

bool joursferies::supprimer2(int jourd)
{
QSqlQuery query;
QString res= QString::number(jourd);
query.prepare("Delete from joursferies where JOUR = :jour ");
query.bindValue(":jour", res);
return    query.exec();
}

bool joursferies::modifier2(QString nom_jour,int jourd, QString mois)
{ QSqlQuery query;
    QString res= QString::number(jourd);
    query.prepare("UPDATE joursferies SET NOM_JOUR=:nom_jour ,MOIS=:mois where JOUR=:jour");
    query.bindValue(":jour",res);
    query.bindValue(":nom_jour",nom_jour);
    query.bindValue(":mois",mois);
    return query.exec();

}


QSqlQueryModel *  joursferies::rechercher2(int jour)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    QString res=QString::number(jour);
    model->setQuery("select * from joursferies where (jour LIKE '"+res+"%' ) ");


            return  model;


}
QSqlQueryModel * joursferies::trier2()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from joursferies ORDER BY jour");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("jour"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("nom_jour "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("mois"));
        return model;
}



