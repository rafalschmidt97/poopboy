#include "Hearth.hpp"
#include <QTimer>
#include "Game.hpp"

Hearth::Hearth(int which) {
  number = which;
  setPixmap(QPixmap(":/resources/assets/images/scene/heart-full.png"));
  if (which <= 30) {
    setPos(40 * number, 20);
  } else {
    setPos(40 * (number - 30), 50);
  }

  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(updateHearth()));
  timer->start(16);
}

void Hearth::updateHearth() {
  if (Game::getInstance()->getCharacter()->getHealth() >= number) {
    setVisible(true);
  } else {
    setVisible(false);
  }
}
