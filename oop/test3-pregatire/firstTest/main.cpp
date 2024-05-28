#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <iostream>
#include <string>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Login");
    window.resize(250,100);

    QLabel *usernameLabel = new QLabel(&window);
    usernameLabel->setText("&Username: ");
    usernameLabel->move(10, 10);

    QLineEdit *usernameEdit = new QLineEdit(&window);
    usernameEdit->move(80,10);
    usernameLabel->setBuddy(usernameEdit);

    QLabel *passwordLabel = new QLabel(&window);
    passwordLabel->setText("&Password: ");
    passwordLabel->move(10,40);

    QLineEdit *passwordEdit = new QLineEdit(&window);
    passwordEdit->move(80,40);
    passwordEdit->setEchoMode(QLineEdit::Password);

    passwordLabel->setBuddy(passwordEdit);

    QPushButton *sendButton = new QPushButton(&window);
    sendButton->setText("Login");
    sendButton->move(80,70);

    window.show();

    return app.exec();
}
