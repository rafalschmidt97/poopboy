#ifndef TEXTSCENE_HPP
#define TEXTSCENE_HPP

#define RESOLUTION_WIDTH 1280
#define RESOLUTION_HEIGHT 720

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include <QMediaPlayer>

class TextScene : public QGraphicsScene {
public:
  TextScene();
private:
  void keyReleaseEvent(QKeyEvent *event);
  QGraphicsTextItem *messageText;
  bool isDecided;
  QMediaPlayer *selectSoundPlayer;
};

#endif // TEXTSCENE_HPP
