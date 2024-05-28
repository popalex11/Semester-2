#include "mainwindow.h"

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QTableWidget>
#include <QStringList>
#include <QHeaderView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget window;
    window.setWindowTitle("Planets");
    window.resize(600,500);

    QLabel *label = new QLabel("Planets of the Solar System", &window);
    label->move(10,10);
    label->resize(480,20);

    QTableWidget *tableWidget = new QTableWidget(&window);
    tableWidget->move(10,40);
    tableWidget->resize(580,300);
    tableWidget->setRowCount(8);
    tableWidget->setColumnCount(4);

    QStringList headers = {"Name", "Distance from the Sun(AU)", "Diameter (km)", "Revolution Period (Earth years)"};
    tableWidget->setHorizontalHeaderLabels(headers);

    QStringList planetNames = {"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptun"};
    QStringList distances = {"0.39", "0.72", "1.00", "1.52", "5.20", "9.58", "19.22", "30.05"};
    QStringList diameters = {"4879", "12104", "12756", "6792", "142984", "120536", "51118", "49528"};
    QStringList revolutionPeriods = {"0.24", "0.62", "1.00", "1.88", "11.86", "29.46", "84.01", "164.79"};

    for(int i = 0; i < planetNames.size(); i++){
        tableWidget->setItem(i, 0, new QTableWidgetItem(planetNames.at(i)));
        tableWidget->setItem(i, 1, new QTableWidgetItem(distances.at(i)));
        tableWidget->setItem(i, 2, new QTableWidgetItem(diameters.at(i)));
        tableWidget->setItem(i, 3, new QTableWidgetItem(revolutionPeriods.at(i)));
    }

    tableWidget->horizontalHeader()->setVisible(true);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableWidget->verticalHeader()->setVisible(false);

//    QListWidget *list = new QListWidget(&window);
//    list->move(10,40);
//    list->resize(180,200);

//    list->addItem("Mercury");
//    list->addItem("Venus");
//    list->addItem("Earth");
//    list->addItem("Mars");
//    list->addItem("Jupiter");
//    list->addItem("Saturn");
//    list->addItem("Uranus");
//    list->addItem("Neptun");

    window.show();


    return a.exec();
}
