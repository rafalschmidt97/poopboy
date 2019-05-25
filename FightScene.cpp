#include "FightScene.hpp"
#include "Game.hpp"
#include "Hearth.hpp"
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>

FightScene::FightScene() {
  setSceneRect(0,0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT);
  setBackgroundBrush(QBrush(QImage(":/resources/assets/images/scene/background.jpg")));
  setStickyFocus(true);
  escapeDoor = new Door('U', 600, 0, 0, -1);

  for (int i = 1; i < 60; i++) {
    addItem(new Hearth(i));
  }

  for (int i = 0; i < 30; i++) {
    enemies[i] = new Enemy();
    addItem(enemies[i]);
  }

  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(winChecker()));

  winSoundPlayer = new QMediaPlayer();
  winSoundPlayer->setMedia(QUrl("qrc:/resources/assets/sounds/level-win.mp3"));
}

void FightScene::setEnemies(int amount) {
  for (int i = 0; i < amount; i++) {
    enemies[i]->setAlive(true);
  }
  timer->start(16);
}

void FightScene::killEnemies() {
  for (int i = 0; i < 30; i++) {
    enemies[i]->setAlive(false);
  }
  timer->stop();
}

void FightScene::showMessage(std::string message) {
  QGraphicsPixmapItem *messageBackground = new QGraphicsPixmapItem();
  messageBackground->setPixmap(QPixmap(":/resources/assets/images/scene/alert.png"));
  messageBackground->setPos(1280/2 - 704/2, 720/2 - 470/2);
  addItem(messageBackground);

  QGraphicsTextItem *messageText = new QGraphicsTextItem();
  messageText->setPlainText(QString::fromStdString(message));
  messageText->setPos(470, 415);
  messageText->setFont(QFont("Upheaval TT (BRK)", 45));
  messageText->setDefaultTextColor("#362f2d");
  addItem(messageText);

  QTimer::singleShot(1000, [=] {
    removeItem(messageBackground);
    removeItem(messageText);

    delete messageBackground;
    delete messageText;
  });
}

Door *FightScene::getEscapeDoor() {
  return escapeDoor;
}

void FightScene::setProgress(int newProgress) {
  progress = newProgress;
}

void FightScene::winChecker() {
  bool isWin = true;

  for (int i = 0; i < 30; i++) {
    if (enemies[i]->getAlive()) {
      isWin = false;
    }
  }

  if (isWin) {
    if (winSoundPlayer->state() == QMediaPlayer::PlayingState){
      winSoundPlayer->setPosition(0);
    } else if (winSoundPlayer->state() == QMediaPlayer::StoppedState){
       winSoundPlayer->play();
    }

    timer->stop();
    Game::getInstance()->getCharacter()->setHealth(Game::getInstance()->getCharacter()->getHealth() + 1);
    if (Game::getInstance()->getStoryProgress() <= progress) {
      Game::getInstance()->setStoryProgress(Game::getInstance()->getStoryProgress() + 1);

      if (Game::getInstance()->getStoryProgress() < 7) {
        showMessage("YOU UNLOCKED \n  NEW LEVEL !");
      } else {
        showMessage("CONGRATULATION! \n  NEW WIN !");
      }
    }

    addItem(escapeDoor);
  }
}
