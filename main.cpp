#include <QApplication>
#include <QTimer>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QMessageBox>
#include "player.h"
#include "QGraphicsTextItem"
#include <QMessageBox>
#include <QAudioOutput>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMediaPlayer>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Create the View
    QGraphicsView view;
    view.setFixedSize(800, 600);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Create the Scene
    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 800, 600);

    // Create the Player
    Player *player = new Player(&scene); // Pass the scene pointer to the Player constructor
    player->setPixmap(QPixmap(":/resources/img/ship.png").scaled(100, 100));
    player->setPos(view.width() / 2 - player->pixmap().width() / 2, view.height() - player->pixmap().height());

    // Add the Player to the Scene
    scene.addItem(player);

    // Set focus to the Player
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // Assign scene to the view
    view.setScene(&scene);
    view.show();

    // Create the Enemies automatically
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), player, SLOT(createEnemy()));
    timer->start(1500);

    QAudioOutput *mainThemeSoundOutput = new QAudioOutput;
    mainThemeSoundOutput->setVolume(1);
    QMediaPlayer *mainThemeSound = new QMediaPlayer;
    mainThemeSound->setAudioOutput(mainThemeSoundOutput);
    mainThemeSound->setSource(QUrl("qrc:/resources/img/the-epic-2-by-rafael-krux(chosic.com).mp3"));
    mainThemeSound->setLoops(QMediaPlayer::Infinite);
    mainThemeSound->play();

    return a.exec();
}
