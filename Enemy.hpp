#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QMediaPlayer>

class Enemy : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT
public:
  Enemy();
  void getDamage(char damageDirection);
  int getHealth();
  char getDirection();
  void setDirection(char newDirection);
  QTimer *getTimer();
  void moveCollision();
  bool getAlive();
  void setAlive(bool isAlive);

private:
  char direction;
  int health = 3;
  bool alive;
  QTimer *timer;
  void moveCollisionBullet(char moveDirection);
  QMediaPlayer *hitSoundEnemy;

private slots:
  void move();
};

#endif // ENEMY_HPP
