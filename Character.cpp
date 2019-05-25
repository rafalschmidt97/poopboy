#include "Character.hpp"
#include <chrono>
#include "Game.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include <QMessageBox>

Character::Character() {
  health = 2;
  setPos(580,300);
  setFlag(QGraphicsItem::ItemIsFocusable);
  setFocus();
  setPixmap(QPixmap(":/resources/assets/images/character/front.png"));

  moveTimer = new QTimer(this);
  connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));

  healthTimer = new QTimer(this);
  connect(moveTimer, SIGNAL(timeout()), this, SLOT(healthChecker()));
  healthTimer->start(16);

  hitSoundPlayer = new QMediaPlayer();
  hitSoundPlayer->setMedia(QUrl("qrc:/resources/assets/sounds/hit.mp3"));

  hurtSoundPlayer = new QMediaPlayer();
  hurtSoundPlayer->setMedia(QUrl("qrc:/resources/assets/sounds/hurt.mp3"));

  hitTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

int Character::getHealth() {
  return health;
}

void Character::setHealth(int amount) {
  health = amount;
}

void Character::keyPressEvent(QKeyEvent *event) {
  if (!event->isAutoRepeat()) {
    switch(event->key()) {
      case Qt::Key_Left: {
        isPressedLeft = true;
        moveTimer->start(16);
        break;
      }
      case Qt::Key_Right: {
        isPressedRight = true;
        moveTimer->start(16);
        break;
      }
      case Qt::Key_Up: {
        isPressedUp = true;
        moveTimer->start(16);
        break;
      }
      case Qt::Key_Down: {
        isPressedDown = true;
        moveTimer->start(16);
        break;
      }
      case Qt::Key_W: {
        hit('U');
        break;
      }
      case Qt::Key_S: {
        hit('D');
        break;
      }
      case Qt::Key_D: {
        hit('R');
        break;
      }
      case Qt::Key_A: {
        hit('L');
        break;
      }
      default: return;
    }
  }
}

void Character::keyReleaseEvent(QKeyEvent *event) {
  if (!event->isAutoRepeat()) {

    if (event->key() == Qt::Key_Left && event->key() == Qt::Key_Right && event->key() == Qt::Key_Up && event->key() == Qt::Key_Down){
      moveTimer->stop();
    }

    switch(event->key()) {
      case Qt::Key_Left: {
        isPressedLeft = false;
        break;
      }
      case Qt::Key_Right: {
        isPressedRight = false;
        break;
      }
      case Qt::Key_Up: {
        isPressedUp= false;
        break;
      }
      case Qt::Key_Down: {
        isPressedDown = false;
        break;
      }
      default: return;
    }
  }
}

void Character::move() {
  QList<QGraphicsItem *> collizion = collidingItems();
  for (int i = 0, n = collizion.size(); i < n; ++i){
    Enemy * enemy = dynamic_cast<Enemy *>(collizion[i]);
    if (enemy) {
      if(health > 0) {
        health--;

        if (hurtSoundPlayer->state() == QMediaPlayer::PlayingState){
          hurtSoundPlayer->setPosition(0);
        } else if (hurtSoundPlayer->state() == QMediaPlayer::StoppedState){
           hurtSoundPlayer->play();
        }
      }

      switch(enemy->getDirection()) {
        case 'U': {
          if (y() > 50 + 100) {
            setPos(x(), y() - 100);
          } else {
            setPos(x(), 50);
          }
          break;
        }
        case 'D': {
          if (y() < 720 - 50 - 100 - 76) {
            setPos(x(), y() + 100);
          } else {
            setPos(x(), 720 - 50 - 76);
          }
          break;
        }
        case 'L': {
          if (x() > 50 + 100) {
            setPos(x() - 100, y());
          } else {
            setPos(50, y());
          }
          break;
        }
        case 'R': {
          if (x() < 1280 - 50 - 100 - 76) {
            setPos(x() + 100, y());
          } else {
            setPos(1280 - 50 - 77, y());
          }
          break;
        }
        default: return;
      }
      enemy->moveCollision();
      return;
    }
  }

  if (isPressedLeft){
    if (pos().x() > 0 + 50)
      setPos(x() - 5,y());
  }

  if (isPressedRight){
    if (pos().x() + 77 < 1280 - 50)
      setPos(x() + 5,y());
  }

  if (isPressedUp){
    if (pos().y() > 0 + 50)
      setPos(x(),y() - 5);
  }

  if (isPressedDown){
    if (pos().y() + 90 < 720 - 50)
      setPos(x(),y() + 5);
  }
}

void Character::hit(char hitDirection) {
  unsigned int now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

  if (hitTime + 300 < now)  {
    hitTime = now;
    Bullet *bullet;
    switch(hitDirection) {
      case 'U': {
        setPixmap(QPixmap(":/resources/assets/images/character/back.png"));
        bullet = new Bullet('U');
        bullet->setPos(x() + 20,y() - 33 - 25);
        break;
      }
      case 'D': {
        setPixmap(QPixmap(":/resources/assets/images/character/front.png"));
        bullet = new Bullet('D');
        bullet->setPos(x() + 20,y() + 90 + 25);
        break;
      }
      case 'R': {
        setPixmap(QPixmap(":/resources/assets/images/character/right.png"));
        bullet = new Bullet('R');
        bullet->setPos(x() + 90 + 25,y() + 45);
        break;
      }
      case 'L': {
        setPixmap(QPixmap(":/resources/assets/images/character/left.png"));
        bullet = new Bullet('L');
        bullet->setPos(x() - 33 - 25,y() + 45);
        break;
      }
      default: return;
    }

    scene()->addItem(bullet);

    if (hitSoundPlayer->state() == QMediaPlayer::PlayingState){
      hitSoundPlayer->setPosition(0);
    } else if (hitSoundPlayer->state() == QMediaPlayer::StoppedState){
       hitSoundPlayer->play();
    }
  }
}

void Character::healthChecker() {
  if (health == 0) {
    healthTimer->stop();
    Game::getInstance()->getFightScene()->killEnemies();
    Game::getInstance()->getFightScene()->addItem(Game::getInstance()->getFightScene()->getEscapeDoor());
    Game::getInstance()->getFightScene()->showMessage("!!! YOU DIED !!!");
    health = 1;
  }
}
