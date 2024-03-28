#include "enemy.h"
#include "player.h" // Include the player header to access its class definition
#include <QGraphicsScene>
#include <QTimer>
#include <QList>
#include <QGraphicsPixmapItem>
#include <QDebug>

Enemy::Enemy() {
    // Set the enemy image
    setPixmap(QPixmap(":/resources/img/chiken.png").scaled(100, 100));

    // Set the position of the enemy within the view dimensions
    int random_number = rand() % 700;
    setPos(random_number, 0);

    // Move the enemies downwards automatically every 50 milliseconds
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Enemy::move() {
    //Check for collision with the player
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0; i < colliding_items.size(); i++) {
        // If the colliding item is the player, remove the enemy and call decrease() on the player
        if (typeid(*(colliding_items[i])) == typeid(Player)) {
            scene()->removeItem(this);
            delete this;
            Player player = dynamic_cast<Player>(colliding_items[i]);
            player->decrease(); // Call decrease() on the player object
            return; // Exit the function after collision
        }
    }

    setPos(x(), y() + 5); // Move the enemy downwards

    // Remove the enemy if it reaches the bottom of the scene
    if (y() + pixmap().height() > scene()->height()) {
        scene()->removeItem(this);
        delete this;
    }
}