#ifndef DOOR_HPP
#define DOOR_HPP

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Door : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT
public:
  Door(char direction, int x, int y, int enemiesAmount, int progressRequired);
private:
  QTimer *timer;
  int enemies;
  int progress;
private slots:
  void changeScene();
};

#endif // DOOR_HPP
