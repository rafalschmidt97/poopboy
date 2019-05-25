#include "Enemy.hpp"
#include "Game.hpp"

Enemy::Enemy() {
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(move()));

  hitSoundEnemy = new QMediaPlayer();
  hitSoundEnemy->setMedia(QUrl("qrc:/resources/assets/sounds/hit-enemy.mp3"));

  alive = false;
  setVisible(false);
}

int Enemy::getHealth() {
  return health;
}

char Enemy::getDirection(){
  return direction;
}

void Enemy::setDirection(char newDirection) {
  direction = newDirection;
}

QTimer *Enemy::getTimer(){
  return timer;
}

void Enemy::getDamage(char damageDirection) {
  health--;

  if (hitSoundEnemy->state() == QMediaPlayer::PlayingState){
    hitSoundEnemy->setPosition(0);
  } else if (hitSoundEnemy->state() == QMediaPlayer::StoppedState){
     hitSoundEnemy->play();
  }

  moveCollisionBullet(damageDirection);

  if (health == 0) {
    alive = false;
    setVisible(false);
    timer->stop();
  }
}

void Enemy::move() {
  switch(direction) {
    case 'U': {
      setPixmap(QPixmap(":/resources/assets/images/ghost/back.png"));
      if (pos().y() > 50){
        setPos(x(),y()-5);
      } else {
        direction = 'D';
      }
      break;
    }
    case 'D': {
      setPixmap(QPixmap(":/resources/assets/images/ghost/front.png"));
      if (pos().y() < 720 - 50 - 77){
        setPos(x(),y()+5);
      } else {
        direction = 'U';
      }
      break;
    }
    case 'L': {
      setPixmap(QPixmap(":/resources/assets/images/ghost/left.png"));
      if (pos().x() > 50){
        setPos(x() - 5,y());
      } else {
        direction = 'R';
      }
      break;
    }
    case 'R': {
      setPixmap(QPixmap(":/resources/assets/images/ghost/right.png"));
      if (pos().x() < 1280 - 50 - 90){
        setPos(x() + 5,y());
      } else {
        direction = 'L';
      }
      break;
    }
    default: return;
  }
}

void Enemy::moveCollision() {
  switch(direction) {
    case 'U': {
      if (y() > 50 + 100) {
        setPos(x(), y() + 100);
      } else {
        setDirection('D');
      }
      break;
    }
    case 'D': {
      if (y() < 720 - 50 - 100 - 76) {
        setPos(x(), y() - 100);
      } else {
        setDirection('U');
      }
      break;
    }
    case 'L': {
      if (x() > 50 + 100) {
        setPos(x() + 100, y());
      } else {
        setDirection('R');
      }
      break;
    }
    case 'R': {
      if (x() < 1280 - 50 - 100 - 76) {
        setPos(x() - 100, y());
      } else {
        setDirection('L');
      }
      break;
    }
    default: return;
  }
}

bool Enemy::getAlive() {
  return alive;
}

void Enemy::setAlive(bool isAlive) {
  alive = isAlive;

  if(alive) {
    health = 3;
    setVisible(true);
    int randomX = (qrand() % (1280 - 100 - 83 - 100)) + 50 + 100;
    int randomY = (qrand() % (720 - 100 - 95 - 100)) + 50 + 100;
    setPos(randomX, randomY);

    if(randomX > (1280 - 50 - (83 / 2)) / 2) {
      if(randomY > (720 - 50 - (95 / 2)) / 2) {
        direction = 'L';
      } else {
        direction = 'U';
      }
    } else {
      if(randomY > (720 - 50 - (95 / 2)) / 2) {
        direction = 'R';
      } else {
        direction = 'D';
      }
    }

    timer->start(16);
  } else {
    setVisible(false);
    timer->stop();
  }
}

void Enemy::moveCollisionBullet(char moveCollision) {
  switch(moveCollision) {
    case 'U': {
      setDirection('D');
      if (y() > 50 + 100) {
        setPos(x(), y() - 100);
      }
      break;
    }
    case 'D': {
      setDirection('U');
      if (y() < 720 - 50 - 100 - 76) {
        setPos(x(), y() + 100);
      }
      break;
    }
    case 'L': {
      setDirection('R');
      if (x() > 50 + 100) {
        setPos(x() - 100, y());
      } else {
        setPos(50, y());
      }
      break;
    }
    case 'R': {
      setDirection('L');
      if (x() < 1280 - 50 - 100 - 76) {
        setPos(x() + 100, y());
      }
      break;
    }
    default: return;
  }
}
