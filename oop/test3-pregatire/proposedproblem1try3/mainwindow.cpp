#include "mainwindow.h"
#include "song.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), songController(new SongController(this)) {
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

    connect(songController, &SongController::songsChanged, this, &MainWindow::updateSongTable);
    connect(songController, &SongController::playlistChanged, this, &MainWindow::updatePlaylist);
}

MainWindow::~MainWindow() {
    delete songController;
}

void MainWindow::initializeSongTable() {
    // Initialize the song table with some sample songs
    songController->addSong(Song("Song A", "Artist 1", "3:30", "/path/to/songA.mp3"));
    songController->addSong(Song("Song B", "Artist 2", "4:00", "/path/to/songB.mp3"));
    songController->addSong(Song("Song C", "Artist 3", "2:45", "/path/to/songC.mp3"));
}

void MainWindow::updateSongTable() {
    songTable->setRowCount(0);
    QVector<Song> songs = songController->getSongs();
    for (int i = 0; i < songs.size(); ++i) {
        const Song &song = songs[i];
        songTable->insertRow(i);
        songTable->setItem(i, 0, new QTableWidgetItem(song.getTitle()));
        songTable->setItem(i, 1, new QTableWidgetItem(song.getArtist()));
        songTable->setItem(i, 2, new QTableWidgetItem(song.getDuration()));
    }
}

void MainWindow::updatePlaylist() {
    playlistWidget->clear();
    QVector<Song> playlist = songController->getPlaylist();
    for (const Song &song : playlist) {
        QString songDetails = song.getTitle() + " - " + song.getArtist() + " (" + song.getDuration() + ")";
        playlistWidget->addItem(songDetails);
    }
}

void MainWindow::addSong() {
    QString title = titleInput->text();
    QString artist = artistInput->text();
    QString duration = durationInput->text();
    QString path = pathInput->text();
    songController->addSong(Song(title, artist, duration, path));
}

void MainWindow::deleteSong() {
    int row = songTable->currentRow();
    if (row >= 0) {
        songController->removeSong(row);
    } else {
        QMessageBox::warning(this, "Warning", "Please select a song to delete");
    }
}

void MainWindow::updateSong() {
    int row = songTable->currentRow();
    if (row >= 0) {
        QString title = titleInput->text();
        QString artist = artistInput->text();
        QString duration = durationInput->text();
        QString path = pathInput->text();
        songController->updateSong(row, Song(title, artist, duration, path));
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
        songController->addToPlaylist(row);
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
