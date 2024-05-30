#include "song.h"

Song::Song(const QString &title, const QString &artist, const QString &duration, const QString &mediaPath)
    : title(title), artist(artist), duration(duration), mediaPath(mediaPath) {}

QString Song::getTitle() const { return title; }
QString Song::getArtist() const { return artist; }
QString Song::getDuration() const { return duration; }
QString Song::getMediaPath() const { return mediaPath; }
