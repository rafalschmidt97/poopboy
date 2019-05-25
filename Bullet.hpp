#ifndef BULLET_HPP
#define BULLET_HPP

#include <QObject>
#include <QGraphicsPixmapItem>

class Bullet : public QObject, public QGraphicsPixmapItem  {
  Q_OBJECT
public:
  Bullet(char currentDirection);
private:
  char direction;
private slots:
  void move();
};


#endif // BULLET_HPP
