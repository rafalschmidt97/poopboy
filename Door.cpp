#include "Door.hpp"
#include <QList>
#include "Game.hpp"
#include "Character.hpp"
#include <QDebug>

Door::Door(char direction, int x, int y, int enemiesAmount, int progressRequired) {
  setPos(x, y);
  progress = progressRequired;
  enemies = enemiesAmount;

  switch(direction) {
    case 'U': {
      setPixmap(QPixmap(":/resources/assets/images/door/front.png"));
      break;
    }
    case 'D': {
      setPixmap(QPixmap(":/resources/assets/images/door/back.png"));
      break;
    }
    case 'R': {
      setPixmap(QPixmap(":/resources/assets/images/door/right.png"));
      break;
    }
    case 'L': {
      setPixmap(QPixmap(":/resources/assets/images/door/left.png"));
      break;
    }
    default: return;
  }

  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(changeScene()));
  timer->start(16);
}

void Door::changeScene() {
  QList<QGraphicsItem *> collizion = collidingItems();
  for (int i = 0, n = collizion.size(); i < n; ++i){
    Character *character = dynamic_cast<Character *>(collizion[i]);

    if (character) {
      if (progress <= Game::getInstance()->getStoryProgress()) {
        if (progress != -1) {
          Game::getInstance()->getCharacter()->clearFocus();
          Game::getInstance()->getStoryScene()->removeItem(Game::getInstance()->getCharacter());
          Game::getInstance()->getFightScene()->addItem(Game::getInstance()->getCharacter());
          Game::getInstance()->setScene(Game::getInstance()->getFightScene());
          Game::getInstance()->getCharacter()->setFocus();
          Game::getInstance()->getCharacter()->setPos(100,100);
          Game::getInstance()->getFightScene()->setEnemies(enemies);
          Game::getInstance()->getFightScene()->setProgress(progress);
        } else {
          Game::getInstance()->getCharacter()->clearFocus();
          Game::getInstance()->getFightScene()->removeItem(Game::getInstance()->getCharacter());
          Game::getInstance()->getStoryScene()->addItem(Game::getInstance()->getCharacter());
          Game::getInstance()->setScene(Game::getInstance()->getStoryScene());
          Game::getInstance()->getCharacter()->setFocus();
          Game::getInstance()->getCharacter()->setPos(580,300);
          Game::getInstance()->getFightScene()->removeItem(Game::getInstance()->getFightScene()->getEscapeDoor());
        }
      } else {
        qDebug() << "You can't play this level";
      }
    }
  }
}
