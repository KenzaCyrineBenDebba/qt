#ifndef JOURSFERIES_H
#define JOURSFERIES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class joursferies
{
public:
    joursferies();
    joursferies(QString,int,QString);

    QString get_nom_jour();
    int get_jour();
    QString get_mois();


    bool ajouter2();
    QSqlQueryModel *afficher2();
    bool supprimer2(int);
    bool modifier2(QString,int,QString);
   QSqlQueryModel * rechercher2(int);
    QSqlQueryModel * trier2();





private:
    int jour;
    QString nom_jour,mois;


};

#endif // JOURSFERIES_H
