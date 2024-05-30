#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "songcontroller.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addSong();
    void deleteSong();
    void updateSong();
    void filterSongs();
    void addToPlaylist();
    void playSong();
    void nextSong();

    void updateSongTable();
    void updatePlaylist();

private:
    void initializeSongTable();

    QTableWidget *songTable;
    QListWidget *playlistWidget;
    QLineEdit *titleInput;
    QLineEdit *artistInput;
    QLineEdit *durationInput;
    QLineEdit *pathInput;

    SongController *songController;
};

#endif // MAINWINDOW_H
