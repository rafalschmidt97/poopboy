#ifndef HEARTH_HPP
#define HEARTH_HPP

#include <QObject>
#include <QGraphicsPixmapItem>

class Hearth : public QObject, public QGraphicsPixmapItem  {
  Q_OBJECT
public:
  Hearth(int which);

private:
  int number;
private slots:
  void updateHearth();
};

#endif // HEARTH_HPP
