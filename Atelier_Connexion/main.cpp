#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"


#include "connection.h"
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
QT_CHARTS_USE_NAMESPACE



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    QT_CHARTS_USE_NAMESPACE
            QBarSet *set0 = new QBarSet("% colis n°1");
            QBarSet *set1 = new QBarSet("% colis n°2");
            QBarSet *set2 = new QBarSet("% colis n°3");
            QBarSet *set3 = new QBarSet("% colis n°4");
            QBarSet *set4 = new QBarSet("% colis n°5");
             QBarSet *set5 = new QBarSet("% colis n°6");

            *set0 << 5 << 0 << 0 << 0 << 0 << 0;
            *set1 << 0 << 20 << 0 << 0 << 0 << 0;
            *set2 << 0 << 0 << 10 << 0 << 0 << 0;
            *set3 << 0 << 0 << 0 << 30 << 0 << 0;
            *set4 << 0 << 0 << 0 << 0 << 20 << 0;
            *set5 << 0 << 0 << 0 << 0 << 0 << 40;
            QBarSeries *series = new QBarSeries();
            series->append(set0);
            series->append(set1);
            series->append(set2);
            series->append(set3);
            series->append(set4);
            series->append(set5);
            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("pourcentge promotion pour chaque client");
            chart->setAnimationOptions(QChart::AllAnimations);
            QStringList categories;
            categories << "1er client" << "2eme client" << "3eme client" << "4eme client" << "5eme client" << "6eme client";
            QBarCategoryAxis *axis = new QBarCategoryAxis();
            axis->append(categories);
            chart->createDefaultAxes();
            chart->setAxisX(axis, series);
            chart->legend()->setVisible(true);
            chart->legend()->setAlignment(Qt::AlignBottom);
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            QPalette pal = qApp->palette();
            pal.setColor(QPalette::Window, QRgb(0xffffff));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));

            qApp->setPalette(pal);
             MainWindow window;
            window.setCentralWidget(chartView);
            window.resize(420, 300);
            window.show();



    MainWindow w;
    Connection c;



    bool test=c.ouvrirConnection();
    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Ok to continue."), QMessageBox::Ok);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);




    return a.exec();
}
