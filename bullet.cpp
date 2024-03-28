#include"bullet.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QList>
#include <enemy.h>
#include <player.h>

Bullet::Bullet(Player *player) : QObject(), QGraphicsPixmapItem(), player(player) {
    // ***  Setting the bullet's size ****
 setPixmap(QPixmap(":/resources/img/bullet 3.png").scaled(50, 70));
    // ***  Generating the Bullets automatically ****
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);


    QAudioOutput *enemySound = new QAudioOutput;
    enemySound->setVolume(100);
    chickenSound = new QMediaPlayer;
    chickenSound->setAudioOutput(enemySound);
    chickenSound->setSource(QUrl("qrc:/resources/img/rubber-chicken-squeak-toy-1-181416.mp3"));

}


// Move function is used to move the bullet upwards and handle the collision of the bullets with enemies
void Bullet::move() {
    // ***  Getting the colliding items with the Bullet ****
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0; i < colliding_items.size(); i++) {
        if (typeid(*colliding_items[i]) == typeid(Enemy)) {
            scene()->removeItem(colliding_items[i]);
            chickenSound->play();
            scene()->removeItem(this);
            player->increase(); // Call increase() from the Player object to increase score
            delete this;
            delete colliding_items[i];
            return; // Exit the function after increasing the score
        }
    }





    // ***  Moving the bullets upward ****
    setPos(x(), y() -  10);
    if (pos().y() + pixmap().height() < 0) {
        scene()->removeItem(this);
        delete this;
}
}