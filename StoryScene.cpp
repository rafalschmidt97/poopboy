#include "StoryScene.hpp"
#include <Game.hpp>
#include "Hearth.hpp"

StoryScene::StoryScene() {
  setSceneRect(0,0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT);
  setBackgroundBrush(QBrush(QImage(":/resources/assets/images/scene/background.jpg")));
  setStickyFocus(true);

  firstDoor = new Door('U', 240, 0, 3, 0);
  firstDoor->setVisible(false);
  addItem(firstDoor);

  secondDoor = new Door('U', 600, 0, 6, 1);
  secondDoor->setVisible(false);
  addItem(secondDoor);

  thirdDoor = new Door('U', 960, 0, 9, 2);
  thirdDoor->setVisible(false);
  addItem(thirdDoor);

  fourthDoor = new Door('R', 1280 - 56, 300, 12, 3);
  fourthDoor->setVisible(false);
  addItem(fourthDoor);

  fifthDoor = new Door('D', 960, 720 - 56, 15, 4);
  fifthDoor->setVisible(false);
  addItem(fifthDoor);

  sixthDoor = new Door('D', 600, 720 - 56, 18, 5);
  sixthDoor->setVisible(false);
  addItem(sixthDoor);

  seventhDoor = new Door('D', 240, 720 - 56, 30, 6);
  seventhDoor->setVisible(false);
  addItem(seventhDoor);

  for (int i = 1; i < 60; i++) {
    addItem(new Hearth(i));
  }

  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(doorChecker()));
  timer->start(16);
}

void StoryScene::doorChecker() {
  switch(Game::getInstance()->getStoryProgress()) {
    case 0: {
      if (!firstDoor->isVisible())
        firstDoor->setVisible(true);
      break;
    }
    case 1: {
      if(!secondDoor->isVisible())
        secondDoor->setVisible(true);
      break;
    }
    case 2: {
      if(!thirdDoor->isVisible())
        thirdDoor->setVisible(true);
      break;
    }
    case 3: {
      if(!fourthDoor->isVisible())
        fourthDoor->setVisible(true);
      break;
    }
    case 4: {
      if(!fifthDoor->isVisible())
        fifthDoor->setVisible(true);
      break;
    }
    case 5: {
      if(!sixthDoor->isVisible())
        sixthDoor->setVisible(true);
      break;
    }
    case 6: {
      if(!seventhDoor->isVisible())
        seventhDoor->setVisible(true);
      break;
    }
    default: return;
  }
}
