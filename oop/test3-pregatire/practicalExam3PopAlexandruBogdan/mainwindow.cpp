#include "mainwindow.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QFont>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      tableWidget(new QTableWidget(boardSize, boardSize, this)),
      attackButton(new QPushButton("Attack selected cell", this)),
      movesLabel(new QLabel("Moves left: 30", this)),
      statusLabel(new QLabel("In progress", this)),
      configLineEdit(new QLineEdit(this)),
      newGameButton(new QPushButton("Start new game", this)),
      movesLeft(30)
{
    this->resize(800,600);
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(tableWidget);
    mainLayout->addWidget(attackButton);
    mainLayout->addWidget(movesLabel);

    QFont statusFont = statusLabel->font();
    statusFont.setPointSize(16);
    statusLabel->setFont(statusFont);
    statusLabel->setStyleSheet("color:black");

    mainLayout->addWidget(statusLabel);

    QHBoxLayout *newGameLayout = new QHBoxLayout();
    newGameLayout->addWidget(configLineEdit);
    newGameLayout->addWidget(newGameButton);
    mainLayout->addLayout(newGameLayout);

    tableWidget->setSelectionMode(QTableWidget::SingleSelection);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(attackButton, &QPushButton::clicked, this, &MainWindow::attackCell);
    connect(newGameButton, &QPushButton::clicked, this, &MainWindow::startNewGame);

    loadConfiguration(1);
    updateTable();
}

MainWindow::~MainWindow()
{
}

bool MainWindow::loadConfiguration(int configNumber)
{
    QString fileName = QString(":/configuration%1.txt").arg(configNumber);
    QFile file(fileName);

    if (!file.exists()) {
        QMessageBox::warning(this, "Error", QString("File does not exist: %1").arg(fileName));
        return false;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", QString("Unable to open file: %1").arg(fileName));
        return false;
    }

    QTextStream in(&file);
    board.clear();
    for (int i = 0; i < boardSize; ++i) {
        std::vector<int> row;
        for (int j = 0; j < boardSize; ++j) {
            int value;
            in >> value;
            row.push_back(value);
        }
        board.push_back(row);
    }

    attacked = std::vector<std::vector<bool>>(boardSize, std::vector<bool>(boardSize, false));
    file.close();
    return true;
}

// This implementation was made before i knew i had to read from files.
//void MainWindow::loadConfiguration(int configNumber)
//{
//    std::vector<std::vector<int>> config1 = {
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 1, 1, 1, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
//        {0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
//        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
//    };
//    std::vector<std::vector<int>> config2 = {
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 1, 1, 1, 1, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
//    };
//    std::vector<std::vector<int>> config3 = {
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//    };
//    std::vector<std::vector<int>> config4 = {
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 1, 1, 1, 1, 0},
//    };
//    std::vector<std::vector<int>> config5 = {
//        {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
//    };
//    switch (configNumber) {
//    case 1:
//        board = config1;
//        break;
//    case 2:
//        board = config2;
//        break;
//    case 3:
//        board = config3;
//        break;
//    case 4:
//        board = config4;
//        break;
//    case 5:
//        board = config5;
//        break;
//    default:
//        board = config1;
//        break;
//    }

//    attacked = std::vector<std::vector<bool>>(boardSize, std::vector<bool>(boardSize, false));
//}

void MainWindow::updateTable()
{
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem();
            if (attacked[row][col]) {
                if (board[row][col] == 1) {
                    item->setText("*");
                    item->setBackground(Qt::red);
                } else {
                    item->setText("o");
                    item->setBackground(Qt::blue);
                }
            } else {
                item->setText("x");
                item->setBackground(Qt::lightGray);
            }
            tableWidget->setItem(row, col, item);
        }
    }

    movesLabel->setText(QString("Moves left: %1").arg(movesLeft));
    checkGameStatus();
}

void MainWindow::checkGameStatus()
{
    bool won = true;
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            if (board[row][col] == 1 && !attacked[row][col]) {
                won = false;
                break;
            }
        }
        if (!won) break;
    }

    if (won) {
        statusLabel->setText("Player wins!");
        statusLabel->setStyleSheet("color:green");
        QMessageBox::information(this,"Game Over", "You win!");
        attackButton->setEnabled(false);
    } else if (movesLeft == 0) {
        statusLabel->setText("Player loses!");
        statusLabel->setStyleSheet("color:red");
        QMessageBox::information(this,"Game Over", "You lose!");
        attackButton->setEnabled(false);
    } else {
        statusLabel->setText("In progress");
    }
}

void MainWindow::attackCell()
{
    QModelIndexList selected = tableWidget->selectionModel()->selectedIndexes();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Error", "No cell selected");
        return;
    }

    int row = selected.first().row();
    int col = selected.first().column();

    if (attacked[row][col]) {
        QMessageBox::warning(this, "Error", "Cell already attacked");
        return;
    }

    attacked[row][col] = true;
    --movesLeft;

    updateTable();

}

void MainWindow::startNewGame()
{
    bool ok;
    int configNumber = configLineEdit->text().toInt(&ok);
    if (!ok || configNumber < 1 || configNumber > 5) {
        QMessageBox::warning(this, "Error", "Invalid configuration number. Should be 1-5");
        return;
    }

    movesLeft = 30;
    loadConfiguration(configNumber);
    updateTable();
    attackButton->setEnabled(true);
}
