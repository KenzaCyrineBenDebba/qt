#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "promotion.h"
#include "joursferies.h"
#include <QMainWindow>
#include <QWidget>

class QPrinter;
class QSqlTableModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();
    void on_pb_supprimer_clicked();
    void on_pb_modifier_clicked();
    void on_pb_rechercher_clicked();
    void on_pb_trier_clicked();
    /*void on_pb_statistique_clicked();*/
    void on_lineEdit_nom_client_textEdited(const QString &arg1);
    void print(QPrinter *printer);
    void print_two_tables(QPrinter *printer);
    void uglyPrint(QPrinter *printer);
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_6_clicked();


    void on_pb_ajouter2_clicked();
    void on_pb_supprimer2_clicked();
    void on_pb_modifier2_clicked();
    void on_pb_rechercher2_clicked();
    void on_pb_trier2_clicked();
    /*void on_pb_statistique2_clicked();*/
    void on_lineEdit_nom_jour_textEdited(const QString &arg1);
    void print2(QPrinter *printer);
    void print_two_tables2(QPrinter *printer);
    void uglyPrint2(QPrinter *printer);
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
private:
    Ui::MainWindow *ui;
    promotion tmppromotion;
    joursferies tmpjoursferies;
    QSqlTableModel *model;

};



#endif // MAINWINDOW_H


