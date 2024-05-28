#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    // Main widget and layout
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // Left layout for the song list and input fields
    QVBoxLayout *leftLayout = new QVBoxLayout();

    // Song table
    songTable = new QTableWidget(0, 3, this);
    songTable->setHorizontalHeaderLabels({"Title", "Artist", "Duration"});
    initializeSongTable();
    leftLayout->addWidget(songTable);

    // Song detail inputs
    QGridLayout *formLayout = new QGridLayout();
    formLayout->addWidget(new QLabel("Title:"), 0, 0);
    titleInput = new QLineEdit(this);
    formLayout->addWidget(titleInput, 0, 1);

    formLayout->addWidget(new QLabel("Artist:"), 1, 0);
    artistInput = new QLineEdit(this);
    formLayout->addWidget(artistInput, 1, 1);

    formLayout->addWidget(new QLabel("Duration:"), 2, 0);
    durationInput = new QLineEdit(this);
    formLayout->addWidget(durationInput, 2, 1);

    formLayout->addWidget(new QLabel("Path:"), 3, 0);
    pathInput = new QLineEdit(this);
    formLayout->addWidget(pathInput, 3, 1);

    leftLayout->addLayout(formLayout);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *addButton = new QPushButton("Add", this);
    QPushButton *deleteButton = new QPushButton("Delete", this);
    QPushButton *updateButton = new QPushButton("Update", this);
    QPushButton *filterButton = new QPushButton("Filter", this);
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(updateButton);
    buttonLayout->addWidget(filterButton);
    leftLayout->addLayout(buttonLayout);

    mainLayout->addLayout(leftLayout);

    // Middle layout for the button
    QVBoxLayout *middleLayout = new QVBoxLayout();
    QPushButton *toPlaylistButton = new QPushButton(">", this);
    middleLayout->addStretch();
    middleLayout->addWidget(toPlaylistButton);
    middleLayout->addStretch();
    mainLayout->addLayout(middleLayout);

    // Right layout for the playlist
    QVBoxLayout *rightLayout = new QVBoxLayout();
    playlistWidget = new QListWidget(this);
    rightLayout->addWidget(playlistWidget);

    // Play and Next buttons
    QHBoxLayout *playlistButtonLayout = new QHBoxLayout();
    QPushButton *playButton = new QPushButton("Play", this);
    QPushButton *nextButton = new QPushButton("Next", this);
    playlistButtonLayout->addWidget(playButton);
    playlistButtonLayout->addWidget(nextButton);
    rightLayout->addLayout(playlistButtonLayout);

    mainLayout->addLayout(rightLayout);

    // Connect signals to slots
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addSong);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteSong);
    connect(updateButton, &QPushButton::clicked, this, &MainWindow::updateSong);
    connect(filterButton, &QPushButton::clicked, this, &MainWindow::filterSongs);
    connect(toPlaylistButton, &QPushButton::clicked, this, &MainWindow::addToPlaylist);
    connect(playButton, &QPushButton::clicked, this, &MainWindow::playSong);
    connect(nextButton, &QPushButton::clicked, this, &MainWindow::nextSong);
}

void MainWindow::initializeSongTable() {
    // Add initial songs to the table
    QStringList titles = {"Song A", "Song B", "Song C"};
    QStringList artists = {"Artist 1", "Artist 2", "Artist 3"};
    QStringList durations = {"3:30", "4:00", "2:45"};
    for (int i = 0; i < titles.size(); ++i) {
        int row = songTable->rowCount();
        songTable->insertRow(row);
        songTable->setItem(row, 0, new QTableWidgetItem(titles[i]));
        songTable->setItem(row, 1, new QTableWidgetItem(artists[i]));
        songTable->setItem(row, 2, new QTableWidgetItem(durations[i]));
    }
}

void MainWindow::addSong() {
    int row = songTable->rowCount();
    songTable->insertRow(row);
    songTable->setItem(row, 0, new QTableWidgetItem(titleInput->text()));
    songTable->setItem(row, 1, new QTableWidgetItem(artistInput->text()));
    songTable->setItem(row, 2, new QTableWidgetItem(durationInput->text()));
}

void MainWindow::deleteSong() {
    int row = songTable->currentRow();
    if (row >= 0) {
        songTable->removeRow(row);
    } else {
        QMessageBox::warning(this, "Warning", "Please select a song to delete");
    }
}

void MainWindow::updateSong() {
    int row = songTable->currentRow();
    if (row >= 0) {
        songTable->item(row, 0)->setText(titleInput->text());
        songTable->item(row, 1)->setText(artistInput->text());
        songTable->item(row, 2)->setText(durationInput->text());
    } else {
        QMessageBox::warning(this, "Warning", "Please select a song to update");
    }
}

void MainWindow::filterSongs() {
    QString filterText = titleInput->text();
    for (int i = 0; i < songTable->rowCount(); ++i) {
        bool match = songTable->item(i, 0)->text().contains(filterText, Qt::CaseInsensitive);
        songTable->setRowHidden(i, !match);
    }
}

void MainWindow::addToPlaylist() {
    int row = songTable->currentRow();
    if (row >= 0) {
        QString songDetails = songTable->item(row, 0)->text() + " - " +
                              songTable->item(row, 1)->text() + " (" +
                              songTable->item(row, 2)->text() + ")";
        playlistWidget->addItem(songDetails);
    } else {
        QMessageBox::warning(this, "Warning", "Please select a song to add to the playlist");
    }
}

void MainWindow::playSong() {
    if (playlistWidget->count() > 0) {
        QMessageBox::information(this, "Playing", "Playing: " + playlistWidget->currentItem()->text());
    } else {
        QMessageBox::information(this, "Information", "No songs in the playlist");
    }
}

void MainWindow::nextSong() {
    int currentRow = playlistWidget->currentRow();
    if (currentRow < playlistWidget->count() - 1) {
        playlistWidget->setCurrentRow(currentRow + 1);
        playSong();
    } else {
        QMessageBox::information(this, "Information", "No more songs in the playlist");
    }
}
