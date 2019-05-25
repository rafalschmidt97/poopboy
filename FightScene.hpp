#ifndef FIGHTSCENE_HPP
#define FIGHTSCENE_HPP

#define RESOLUTION_WIDTH 1280
#define RESOLUTION_HEIGHT 720

#include <QGraphicsScene>
#include "Enemy.hpp"
#include <QTimer>
#include <string>
#include "Door.hpp"

class FightScene : public QGraphicsScene {
  Q_OBJECT
public:
  FightScene();
  void setEnemies(int amount);
  void killEnemies();
  void showMessage(std::string message);
  Door *getEscapeDoor();
  void setProgress(int newProgress);

private:
  Enemy *enemies[30];
  QTimer *timer;
  Door *escapeDoor;
  int progress;
  QMediaPlayer *winSoundPlayer;

private slots:
  void winChecker();
};

#endif // FIGHTSCENE_HPP
