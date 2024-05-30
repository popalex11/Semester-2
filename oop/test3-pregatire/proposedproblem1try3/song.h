#ifndef SONG_H
#define SONG_H

#include <QString>

class Song {
public:
    Song(const QString &title, const QString &artist, const QString &duration, const QString &mediaPath);

    QString getTitle() const;
    QString getArtist() const;
    QString getDuration() const;
    QString getMediaPath() const;

private:
    QString title;
    QString artist;
    QString duration;
    QString mediaPath;
};

#endif // SONG_H
