#include "songcontroller.h"

SongController::SongController(QObject *parent) : QObject(parent) {}

void SongController::addSong(const Song &song) {
    songs.append(song);
    emit songsChanged();
}

void SongController::removeSong(int index) {
    if (index >= 0 && index < songs.size()) {
        songs.removeAt(index);
        emit songsChanged();
    }
}

void SongController::updateSong(int index, const Song &song) {
    if (index >= 0 && index < songs.size()) {
        songs[index] = song;
        emit songsChanged();
    }
}

QVector<Song> SongController::getSongs() const {
    return songs;
}

void SongController::addToPlaylist(int index) {
    if (index >= 0 && index < songs.size()) {
        playlist.append(songs[index]);
        emit playlistChanged();
    }
}

void SongController::removeFromPlaylist(int index) {
    if (index >= 0 && index < playlist.size()) {
        playlist.removeAt(index);
        emit playlistChanged();
    }
}

QVector<Song> SongController::getPlaylist() const {
    return playlist;
}
