#include "TextScene.hpp"
#include <QTimer>
#include "Game.hpp"

TextScene::TextScene() {
  setSceneRect(0,0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT);
  setBackgroundBrush(QBrush(QImage(":/resources/assets/images/scene/background.jpg")));
  setStickyFocus(true);

  messageText = new QGraphicsTextItem();
  messageText->setPlainText("Every game must have a hero. However everybody forgot about one of them. One that could change the world. Change tomorrow into better place. Just like everybody has a dream to collect as many points as anybody can ever get. Very far away dream but still possible to make it real . . . \n \nWould you like to add extra 2 points to make dreams comes true?\n\n     [ a ] Just do it      [ d ] No");
  messageText->setPos(250, 120);
  messageText->setTextWidth(700);
  messageText->setFont(QFont("Upheaval TT (BRK)", 35));
  messageText->setDefaultTextColor("#ffffff");
  addItem(messageText);

  isDecided = false;

  selectSoundPlayer = new QMediaPlayer();
  selectSoundPlayer->setMedia(QUrl("qrc:/resources/assets/sounds/button.mp3"));
}

void TextScene::keyReleaseEvent(QKeyEvent *event) {
  if(!isDecided) {
    switch(event->key()) {
      case Qt::Key_A: {
        selectSoundPlayer->play();
        messageText->setPos(messageText->x(), 320);
        messageText->setPlainText("Congratulation! You get 1 extra health points!");
        Game::getInstance()->getCharacter()->setHealth(Game::getInstance()->getCharacter()->getHealth() + 1);
        break;
      }
      case Qt::Key_D: {
        selectSoundPlayer->play();
        messageText->setPos(messageText->x(), 320);
        messageText->setPlainText("Ohh... PoopBoy started crying and loses health point.");
        Game::getInstance()->getCharacter()->setHealth(Game::getInstance()->getCharacter()->getHealth() - 1);
        break;
      }
      default: return;
    }
    isDecided = true;

    QTimer::singleShot(3000, [=] {
      Game::getInstance()->getStoryScene()->addItem(Game::getInstance()->getCharacter());
      Game::getInstance()->setScene(Game::getInstance()->getStoryScene());
    });
  }
}
