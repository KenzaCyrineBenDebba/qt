#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "promotion.h"
#include "joursferies.h"
#include <QMessageBox>
#include <QApplication>
#include <QtWidgets/QMainWindow>
 #include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

#include <QPdfWriter>
#include <QPainter>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

#include <QRegExpValidator>
#define CARACTERES_ETRANGERS "~{}[]()|-`'^ç@_]\"°01234567890+=£$*µ/§!?,.&#;><"
#include<QIntValidator>

/*#include "widget.h"*/

#include "tableprinter.h"
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QPainter>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);model = new QSqlTableModel;
    model->select();
    ui->tabpromotion->setModel(tmppromotion.afficher());
    ui->tabjoursferies->setModel(tmpjoursferies.afficher2());
//controle de saisie
        QIntValidator *roll=new QIntValidator(1,9999999);
        ui->lineEdit_id->setValidator(roll);
        ui->lineEdit_jour->setValidator(roll);
        ui->lineEdit_nombre_colis->setValidator(roll);

}


MainWindow::~MainWindow()
{
    delete ui;delete model;
}


void MainWindow::on_pb_supprimer_clicked()
{
int id = ui->lineEdit_id->text().toInt();
bool test=tmppromotion.supprimer(id);
if(test)
{ui->tabpromotion->setModel(tmppromotion.afficher());//refresh
    QMessageBox::information(nullptr, QObject::tr("Supprimer une promotion"),
                QObject::tr("promotion supprimé.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("Supprimer promotion"),
                QObject::tr("Erreur !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pb_supprimer2_clicked()
{
int jour = ui->lineEdit_jour->text().toInt();
bool test=tmpjoursferies.supprimer2(jour);
if(test)
{ui->tabjoursferies->setModel(tmpjoursferies.afficher2());//refresh
    QMessageBox::information(nullptr, QObject::tr("Supprimer un jour ferie"),
                QObject::tr("jour ferie supprimé.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("Supprimer jour ferie"),
                QObject::tr("Erreur !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pb_modifier_clicked()
{
    int id = ui->lineEdit_id->text().toInt();
      QString nom_client= ui->lineEdit_nom_client->text();
      QString pourcentage= ui->lineEdit_pourcentage->text();
      int nombre_colis = ui->lineEdit_nombre_colis->text().toInt();
     promotion p;
     bool test=p.modifier(id,nom_client,pourcentage,nombre_colis);
   if(test)
     {
        ui->tabpromotion->setModel(tmppromotion.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Modifier une promotion !"),
                          QObject::tr(" promotion modifiée ! \n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
     }

     else {

         QMessageBox::critical(nullptr, QObject::tr("Modifier une promotion"),
                     QObject::tr("Erreur !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
     }
}

void MainWindow::on_pb_modifier2_clicked()
{
      QString nom_jour= ui->lineEdit_nom_jour->text();
      int jour = ui->lineEdit_jour->text().toInt();
      QString mois= ui->lineEdit_mois->text();

     joursferies j;
     bool test=j.modifier2(nom_jour,jour,mois);
   if(test)
     {
        ui->tabjoursferies->setModel(tmpjoursferies.afficher2());//refresh
        QMessageBox::information(nullptr, QObject::tr("Modifier un jour ferie !"),
                          QObject::tr(" jour ferie modifiée ! \n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
     }

     else {

         QMessageBox::critical(nullptr, QObject::tr("Modifier jour ferie"),
                     QObject::tr("Erreur !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
     }
}

void MainWindow::on_pb_ajouter_clicked()
{
    int id = ui->lineEdit_id->text().toInt();
    QString nom_client= ui->lineEdit_nom_client->text();
    QString pourcentage= ui->lineEdit_pourcentage->text();
    int nombre_colis = ui->lineEdit_nombre_colis->text().toInt();
  promotion p(id,nom_client,pourcentage,nombre_colis);
  bool test=p.ajouter();
  if(test)
{

      ui->tabpromotion->setModel(tmppromotion.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter une promotion"),
                  QObject::tr("promotion ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter une promotion"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pb_ajouter2_clicked()
{
    QString nom_jour= ui->lineEdit_nom_jour->text();
    int jour = ui->lineEdit_jour->text().toInt();
    QString mois= ui->lineEdit_mois->text();

  joursferies j(nom_jour,jour,mois);
  bool test=j.ajouter2();
  if(test)
{

      ui->tabjoursferies->setModel(tmpjoursferies.afficher2());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter un jour ferie"),
                  QObject::tr("jour ferie ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un jour ferie"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pb_rechercher_clicked()
{
    {
        int id = ui->lineEdit_id->text().toInt();
       ui->tabpromotion->setModel(tmppromotion.rechercher(id));

    }
}

void MainWindow::on_pb_rechercher2_clicked()
{
    {
        int jour = ui->lineEdit_jour->text().toInt();
       ui->tabjoursferies->setModel(tmpjoursferies.rechercher2(jour));

    }
}

void MainWindow::on_pb_trier_clicked()
{
    bool test=true;
            if(test){

                   { ui->tabpromotion->setModel(tmppromotion.trier());
                    QMessageBox::information(nullptr, QObject::tr("trier promotion"),
                                QObject::tr("promotion trier.\n"
                                            "Voulez-vous enregistrer les modifications ?"),
                                       QMessageBox::Save
                                       | QMessageBox::Cancel,
                                      QMessageBox::Save);
    }

                }
                else
                    QMessageBox::critical(nullptr, QObject::tr("trier promotion"),
                                QObject::tr("Erreur !.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pb_trier2_clicked()
{
    bool test=true;
            if(test){

                   { ui->tabjoursferies->setModel(tmpjoursferies.trier2());
                    QMessageBox::information(nullptr, QObject::tr("trier jour ferie"),
                                QObject::tr("jours feries trier.\n"
                                            "Voulez-vous enregistrer les modifications ?"),
                                       QMessageBox::Save
                                       | QMessageBox::Cancel,
                                      QMessageBox::Save);
    }

                }
                else
                    QMessageBox::critical(nullptr, QObject::tr("trier jours feries"),
                                QObject::tr("Erreur !.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);

}

/* void MainWindow::on_pb_statistique_clicked() */




//controle de saisie
void MainWindow::on_lineEdit_nom_client_textEdited(const QString &arg1)
{
        QString texte=arg1;
    QString caracteresEtrangers(CARACTERES_ETRANGERS);
    for (int i=0; i<texte.size(); i++)
    foreach (const QChar &y, caracteresEtrangers)
        if(texte.at(i)==y)
            texte[i]=' ';

    ui->lineEdit_nom_client->setText(texte);
}

void MainWindow::on_lineEdit_nom_jour_textEdited(const QString &arg1)
{
        QString texte=arg1;
    QString caracteresEtrangers(CARACTERES_ETRANGERS);
    for (int i=0; i<texte.size(); i++)
    foreach (const QChar &y, caracteresEtrangers)
        if(texte.at(i)==y)
            texte[i]=' ';
    ui->lineEdit_nom_jour->setText(texte);
}



// ----------------- example of inharitance from PagePrepare ---------------------

class PrintBorder : public PagePrepare
{
public:
    virtual void preparePage(QPainter *painter);
    static int pageNumber;
};

int PrintBorder::pageNumber = 0;

void PrintBorder::preparePage(QPainter *painter)
{ // print a border on each page
    QRect rec = painter->viewport();
    painter->setPen(QPen(QColor(0, 0, 0), 1));
    painter->drawRect(rec);
    painter->translate(10, painter->viewport().height() - 10);
    painter->drawText(0, 0, QString("Page %1").arg(pageNumber));
    pageNumber += 1;
}

// --------------------------------------------------------------------------------




void MainWindow::print(QPrinter *printer) {

    // ------------------ simplest example --------------------------

    QPainter painter;
    if(!painter.begin(printer)) {
        qWarning() << "can't start printer";
        return;
    }
    // print table
    TablePrinter tablePrinter(&painter, printer);
    QVector<int> columnStretch = QVector<int>() << 2 << 5 << 10 << 15;
    if(!tablePrinter.printTable(ui->tabpromotion->model(), columnStretch)) {
        qDebug() << tablePrinter.lastError();
    }
    painter.end();
}

void MainWindow::print2(QPrinter *printer) {

    // ------------------ simplest example --------------------------

    QPainter painter;
    if(!painter.begin(printer)) {
        qWarning() << "can't start printer";
        return;
    }
    // print table
    TablePrinter tablePrinter(&painter, printer);
    QVector<int> columnStretch = QVector<int>() << 2 << 5 << 10;
    if(!tablePrinter.printTable(ui->tabjoursferies->model(), columnStretch)) {
        qDebug() << tablePrinter.lastError();
    }
    painter.end();
}

void MainWindow::print_two_tables(QPrinter *printer) {

    // ------------------ two tables example --------------------------

    QPainter painter;
    if(!painter.begin(printer)) {
        qWarning() << "can't start printer";
        return;
    }
    // print table
    TablePrinter tablePrinter(&painter, printer);
    QVector<int> columnStretch = QVector<int>() << 2 << 5 << 10 << 15;
    if(!tablePrinter.printTable(ui->tabpromotion->model(), columnStretch)) {
        qDebug() << tablePrinter.lastError();
    }
    // print second table
    painter.translate(0, 100);
    if(!tablePrinter.printTable(ui->tabpromotion->model(), columnStretch)) {
        qDebug() << tablePrinter.lastError();
    }
    painter.end();
}

void MainWindow::print_two_tables2(QPrinter *printer) {

    // ------------------ two tables example --------------------------

    QPainter painter;
    if(!painter.begin(printer)) {
        qWarning() << "can't start printer";
        return;
    }
    // print table
    TablePrinter tablePrinter(&painter, printer);
    QVector<int> columnStretch = QVector<int>() << 2 << 5 << 10;
    if(!tablePrinter.printTable(ui->tabjoursferies->model(), columnStretch)) {
        qDebug() << tablePrinter.lastError();
    }
    // print second table
    painter.translate(0, 100);
    if(!tablePrinter.printTable(ui->tabjoursferies->model(), columnStretch)) {
        qDebug() << tablePrinter.lastError();
    }
    painter.end();
}


void MainWindow::uglyPrint(QPrinter *printer) {

    // ---------------- death-to-designers example ------------------

    QPainter uglyPainter;
    if(!uglyPainter.begin(printer)) {
        qWarning() << "can't start printer";
        return;
    }
    TablePrinter uglyTablePrinter(&uglyPainter, printer);
    QVector<int> colStretch = QVector<int>() << 5 << 5 << 0 << 10;
    uglyTablePrinter.setPen(QPen(QColor(0, 100, 255), 3, Qt::DotLine)); // pen for borders
    uglyTablePrinter.setHeaderColor(Qt::red);
    uglyTablePrinter.setContentColor(Qt::green);
    QFont font1; // font for headers
    font1.setBold(true);
    QFont font2; // font for content
    font2.setItalic(true);
    uglyTablePrinter.setHeadersFont(font1);
    uglyTablePrinter.setContentFont(font2);
    PrintBorder *printB = new PrintBorder;
    printB->pageNumber = 1;
    uglyTablePrinter.setPagePrepare(printB);
    QVector<QString> headers = QVector<QString>() << "ID" << "NOM_CLIENT" << "POURCENTAGE" << "NOMBRE_COLIS";
    uglyPainter.setPen(QPen(Qt::yellow));
    uglyPainter.drawText(uglyPainter.viewport().width()/2 - 40, 40, "TABLE PROMOTION");
    uglyPainter.translate(0, 60); // start print point
    uglyTablePrinter.setCellMargin(10, 5, 5, 5);
    uglyTablePrinter.setPageMargin(100, 40, 40, 40);
    if(!uglyTablePrinter.printTable(ui->tabpromotion->model(), colStretch, headers)) {
        qDebug() << uglyTablePrinter.lastError();
    }
    uglyPainter.end();
    delete printB;
}

void MainWindow::uglyPrint2(QPrinter *printer) {

    // ---------------- death-to-designers example ------------------

    QPainter uglyPainter;
    if(!uglyPainter.begin(printer)) {
        qWarning() << "can't start printer";
        return;
    }
    TablePrinter uglyTablePrinter(&uglyPainter, printer);
    QVector<int> colStretch = QVector<int>() << 5 << 5 << 0 ;
    uglyTablePrinter.setPen(QPen(QColor(0, 100, 255), 3, Qt::DotLine)); // pen for borders
    uglyTablePrinter.setHeaderColor(Qt::red);
    uglyTablePrinter.setContentColor(Qt::green);
    QFont font1; // font for headers
    font1.setBold(true);
    QFont font2; // font for content
    font2.setItalic(true);
    uglyTablePrinter.setHeadersFont(font1);
    uglyTablePrinter.setContentFont(font2);
    PrintBorder *printB = new PrintBorder;
    printB->pageNumber = 1;
    uglyTablePrinter.setPagePrepare(printB);
    QVector<QString> headers = QVector<QString>() << "NOM_JOUR" << "JOUR" << "MOIS";
    uglyPainter.setPen(QPen(Qt::yellow));
    uglyPainter.drawText(uglyPainter.viewport().width()/2 - 40, 40, "TABLE JOURS FERIES");
    uglyPainter.translate(0, 60); // start print point
    uglyTablePrinter.setCellMargin(10, 5, 5, 5);
    uglyTablePrinter.setPageMargin(100, 40, 40, 40);
    if(!uglyTablePrinter.printTable(ui->tabjoursferies->model(), colStretch, headers)) {
        qDebug() << uglyTablePrinter.lastError();
    }
    uglyPainter.end();
    delete printB;
}

void MainWindow::on_pushButton_5_clicked() {
    QPrintPreviewDialog dialog;
    connect(&dialog, SIGNAL(paintRequested(QPrinter*)), this, SLOT(uglyPrint(QPrinter*)));
    dialog.exec();
}

void MainWindow::on_pushButton_7_clicked() {
    QPrintPreviewDialog dialog;
    connect(&dialog, SIGNAL(paintRequested(QPrinter*)), this, SLOT(uglyPrint2(QPrinter*)));
    dialog.exec();
}

void MainWindow::on_pushButton_4_clicked() {
    QPrintPreviewDialog dialog;
    connect(&dialog, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print(QPrinter*)));
    dialog.exec();
}

void MainWindow::on_pushButton_8_clicked() {
    QPrintPreviewDialog dialog;
    connect(&dialog, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print2(QPrinter*)));
    dialog.exec();
}

void MainWindow::on_pushButton_6_clicked() {
    QPrintPreviewDialog dialog;
    connect(&dialog, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print_two_tables(QPrinter*)));
    dialog.exec();
}

void MainWindow::on_pushButton_9_clicked() {
    QPrintPreviewDialog dialog;
    connect(&dialog, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print_two_tables2(QPrinter*)));
    dialog.exec();
}
