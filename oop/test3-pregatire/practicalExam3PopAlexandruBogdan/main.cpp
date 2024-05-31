#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.setWindowTitle("Exam3");
    mainWindow.show();
    return a.exec();
}

// The exam was solved in QT IDE. I had problems with reading from files and made a resources file and changed the
// implementation to read like that from the resources. I used "run qmake" when the program was not building properly.
