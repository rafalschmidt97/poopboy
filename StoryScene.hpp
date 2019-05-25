#ifndef STORYSCENE_HPP
#define STORYSCENE_HPP

#define RESOLUTION_WIDTH 1280
#define RESOLUTION_HEIGHT 720

#include <QGraphicsScene>
#include <QTimer>
#include "Door.hpp"

class StoryScene : public QGraphicsScene {
  Q_OBJECT
public:
  StoryScene();
private:
  QTimer *timer;
  Door *firstDoor;
  Door *secondDoor;
  Door *thirdDoor;
  Door *fourthDoor;
  Door *fifthDoor;
  Door *sixthDoor;
  Door *seventhDoor;

private slots:
  void doorChecker();
};

#endif // STORYSCENE_HPP
