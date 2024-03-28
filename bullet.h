// bullet.h
#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsRectItem>
#include <player.h> // Include the player header to access its class definition
#include <QAudioOutput>
#include <QMediaPlayer>

class Bullet : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bullet(Player *player); // Constructor with a reference to the Player object

public slots:
    void move(); // Slot to move the bullet and handle collisions

private:
    Player *player; // Reference to the Player object
    QAudioOutput *enemySound;
    QMediaPlayer *chickenSound;
};

#endif // BULLET_H
