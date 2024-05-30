#ifndef SONGCONTROLLER_H
#define SONGCONTROLLER_H

#include <QObject>
#include <QVector>
#include "song.h"

class SongController : public QObject {
    Q_OBJECT

public:
    explicit SongController(QObject *parent = nullptr);

    void addSong(const Song &song);
    void removeSong(int index);
    void updateSong(int index, const Song &song);
    QVector<Song> getSongs() const;

    void addToPlaylist(int index);
    void removeFromPlaylist(int index);
    QVector<Song> getPlaylist() const;

signals:
    void songsChanged();
    void playlistChanged();

private:
    QVector<Song> songs;
    QVector<Song> playlist;
};

#endif // SONGCONTROLLER_H
