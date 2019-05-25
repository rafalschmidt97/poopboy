#include "Bullet.hpp"
#include <QTimer>
#include <QList>
#include "Game.hpp"
#include "Enemy.hpp"

Bullet::Bullet(char currentDirection) {
  direction = currentDirection;

  switch(direction) {
    case 'U': {
      setPixmap(QPixmap(":/resources/assets/images/hit/top.png"));
      break;
    }
    case 'D': {
      setPixmap(QPixmap(":/resources/assets/images/hit/bottom.png"));
      break;
    }
    case 'R': {
      setPixmap(QPixmap(":/resources/assets/images/hit/right.png"));
      break;
    }
    case 'L': {
      setPixmap(QPixmap(":/resources/assets/images/hit/left.png"));
      break;
    }
    default: return;
  }

  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(move()));

  timer->start(16);
}

void Bullet::move() {
  QList<QGraphicsItem *> collizion = collidingItems();
  for (int i = 0, n = collizion.size(); i < n; ++i){
    Enemy * enemy = dynamic_cast<Enemy *>(collizion[i]);

    if (enemy) {
      enemy->getDamage(direction);
      scene()->removeItem(this);
      delete this;
      return;
    }
  }

  switch(direction){
    case 'U': {
      setPos(x(),y() - 7);
      if (pos().y() < 50){
        scene()->removeItem(this);
        delete this;
      }
      break;
    }
    case 'D': {
      setPos(x(),y() + 7);
      if (pos().y() > 720 - 50 - 38){
        scene()->removeItem(this);
        delete this;
      }
      break;
    }
    case 'R': {
      setPos(x() + 7,y());
      if (pos().x() > 1280 - 50 - 38){
        scene()->removeItem(this);
        delete this;
      }
      break;
    }
    case 'L': {
      setPos(x() - 7,y());
      if (pos().x() < 50){
        scene()->removeItem(this);
        delete this;
      }
      break;
    }
    default: return;
  }
}
