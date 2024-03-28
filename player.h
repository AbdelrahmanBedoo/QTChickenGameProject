#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QAudioOutput>
#include <QMediaPlayer>

class QGraphicsScene;
class QTimer;
class QGraphicsTextItem;

class Player: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Player(QGraphicsScene *scene);
public:
    void keyPressEvent(QKeyEvent * event);
    void decrease();
    void increase();


public slots:
    void createEnemy();


private:
    QGraphicsScene *scene; // Pointer to the scene
    int health;
    int score;
    QGraphicsTextItem *healthText;
    QGraphicsTextItem *scoreText;
    QAudioOutput *bulletSoundOutput;
    QMediaPlayer *bulletSound;
};

#endif // PLAYER_H
