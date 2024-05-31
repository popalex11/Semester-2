#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    const int boardSize = 10;


private slots:
    void attackCell();
    void startNewGame();

private:
    Ui::MainWindow *ui;
    bool loadConfiguration(int configNumber);

    QTableWidget *tableWidget;
    QPushButton *attackButton;
    QLabel *movesLabel;
    QLabel *statusLabel;
    QLineEdit *configLineEdit;
    QPushButton *newGameButton;

    std::vector<std::vector<int>> board;
    std::vector<std::vector<bool>> attacked;
    int movesLeft;

    void updateTable();
    void checkGameStatus();
};

#endif // MAINWINDOW_H
