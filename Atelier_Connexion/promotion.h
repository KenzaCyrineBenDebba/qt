#ifndef PROMOTION_H
#define PROMOTION_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class promotion
{
public:
    promotion();
    promotion(int,QString,QString,int);
    int get_id();
    QString get_nom_client();
    QString get_pourcentage();
    int get_nombre_colis();

    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,int);
   QSqlQueryModel * rechercher(int);
    QSqlQueryModel * trier();





private:
    int id,nombre_colis;
    QString nom_client,pourcentage;


};

#endif // PROMOTION_H
