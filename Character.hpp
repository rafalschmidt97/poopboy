#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QKeyEvent>
#include <QTimer>
#include <QTime>

class Character : public QObject, public QGraphicsPixmapItem  {
  Q_OBJECT
public:
  Character();
  int getHealth();
  void setHealth(int amount);

private:
  int health;
  bool isPressedLeft = false;
  bool isPressedRight = false;
  bool isPressedUp = false;
  bool isPressedDown = false;
  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);
  QTimer *moveTimer;
  QTimer *healthTimer;
  char hitDirection;
  unsigned int hitTime;
  QMediaPlayer *hitSoundPlayer;
  QMediaPlayer *hurtSoundPlayer;

private slots:
  void move();
  void hit(char hitDirection);
  void healthChecker();
};

#endif // CHARACTER_HPP
