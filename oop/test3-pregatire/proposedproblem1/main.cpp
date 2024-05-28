#include "mainwindow.h"

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QStringList>
#include <QHeaderView>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget window;
    window.setWindowTitle("Music");
    window.resize(800,800);



//Widgets - music and playlists
    QLabel *labelMusic = new QLabel("My music", &window);
    QLabel *labelPlaylists = new QLabel("Playlists", &window);
    labelMusic->move(10,10);
    labelMusic->resize(380,20);
    labelPlaylists->move(510,10);
    labelPlaylists->resize(280,20);

    QTableWidget *myMusic = new QTableWidget(&window);
    QTableWidget *playlists = new QTableWidget(&window);
    myMusic->move(10,40);
    myMusic->resize(380,500);
    myMusic->setColumnCount(3);
    playlists->move(510,40);
    playlists->resize(280,500);

    QStringList musicHeaders = {"Title","Artist", "Duration"};
    myMusic->setHorizontalHeaderLabels(musicHeaders);

    QHeaderView *header = myMusic->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Fixed);
    header->setDefaultSectionSize(126);

//Form for actions in music table

    QFormLayout *formLayoutMusic{new QFormLayout(&window)};

    QLineEdit* titleEdit{new QLineEdit{&window}};
    QLabel* titleLabel{new QLabel{"&Title: "}};
    titleLabel->setBuddy(titleEdit);

    QLineEdit* artistEdit{new QLineEdit{&window}};
    QLabel* artistLabel{new QLabel{"&Artist: "}};
    artistLabel->setBuddy(artistEdit);

    QLineEdit* durationEdit{new QLineEdit{&window}};
    QLabel* durationLabel{new QLabel{"&Title: "}};
    durationLabel->setBuddy(durationEdit);

    formLayoutMusic->addRow(titleLabel, titleEdit);
    formLayoutMusic->addRow(artistLabel, artistEdit);
    formLayoutMusic->addRow(durationLabel, durationEdit);

    QVBoxLayout *containerLayout = new QVBoxLayout();
    containerLayout->addWidget(labelMusic);
    containerLayout->addLayout(formLayoutMusic);



    window.show();
    return a.exec();
}
