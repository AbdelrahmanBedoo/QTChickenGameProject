#include "player.h"
#include <QKeyEvent>
#include "bullet.h"
#include "enemy.h"
#include <QGraphicsScene>
#include <QMessageBox>
#include <QTimer>
#include <QList>
#include <QGraphicsPixmapItem>
#include <QCoreApplication>
#include <QFont>
#include <QAudioOutput>
#include <QMediaPlayer>

Player::Player(QGraphicsScene *scene) : scene(scene), health(3), score(0), healthText(nullptr), scoreText(nullptr) {
    // Set the player image
    setPixmap(QPixmap(":/img/img/ship.png").scaled(100, 100));

    // Initialize health and score text items
    healthText = new QGraphicsTextItem();
    healthText->setPlainText(QString("Health: ") + QString::number(health));
    healthText->setDefaultTextColor(Qt::red);
    healthText->setFont(QFont("times", 16));
    scene->addItem(healthText);
    healthText->setPos(0, 0);

    scoreText = new QGraphicsTextItem();
    scoreText->setPlainText(QString("Score: ") + QString::number(score));
    scoreText->setDefaultTextColor(Qt::blue);
    scoreText->setFont(QFont("times", 16));
    scene->addItem(scoreText);
    scoreText->setPos(0, 20);

    QAudioOutput *bulletSoundOutput = new QAudioOutput;
    bulletSoundOutput->setVolume(100);
    bulletSound = new QMediaPlayer;
    bulletSound->setAudioOutput(bulletSoundOutput);
    bulletSound->setSource(QUrl("qrc:/img/img/bullet-hit-metal-84818.mp3"));
}

void Player::createEnemy()
{
    Enemy* enemy = new Enemy();
    scene->addItem(enemy);
}
void Player::keyPressEvent(QKeyEvent *event) {
    // Event Handling for the Player
    if(event->key() == Qt::Key_Left) {
        if(x() > 0) // to prevent the player from getting out of the screen
            setPos(x() - 10, y());
    } else if(event->key() == Qt::Key_Right) {
        if(x() + 100 < 800) // to prevent the player from getting out of the screen
            setPos(x() + 10, y());
    } else if(event->key() == Qt::Key_Space) {
        Bullet *bullet = new Bullet(this);
        bullet->setPos(x() +25, y()-50);
        scene->addItem(bullet);
        if (bulletSound->playbackState() == QMediaPlayer::PlayingState) {
            bulletSound->setPosition(0);
        } else if (bulletSound->playbackState() == QMediaPlayer::StoppedState) {
            bulletSound->play();
        }
    }

}


void Player::decrease() {
    health--;
    healthText->setPlainText(QString("Health: ") + QString::number(health));
    if (health < 1) {
        QMessageBox::information(nullptr, "Game Over", "You lost! Your final score is: " + QString::number(score));
        // Handle game over logic
        scene->clear();
        QCoreApplication::quit();
        exit(EXIT_FAILURE);
    }
}

void Player::increase() {
    score++;
    scoreText->setPlainText(QString("Score: ") + QString::number(score));
}


