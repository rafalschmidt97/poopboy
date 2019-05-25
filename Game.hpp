#ifndef GAME_HPP
#define GAME_HPP

#define RESOLUTION_WIDTH 1280
#define RESOLUTION_HEIGHT 720

#include <QGraphicsView>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include "Character.hpp"
#include "FightScene.hpp"
#include "StoryScene.hpp"
#include "TextScene.hpp"

class Game : public QGraphicsView {
public:
  static Game *getInstance();
  FightScene *getFightScene();
  StoryScene *getStoryScene();
  TextScene *getTextScene();
  Character *getCharacter();
  int getStoryProgress();
  void setStoryProgress(int newProgress);

private:
  Game();
  ~Game();
  static Game *instance;
  QMediaPlaylist *musicPlaylist;
  QMediaPlayer *musicPlayer;
  FightScene *fightScene;
  StoryScene *storyScene;
  TextScene *textScene;
  Character *character;
  int storyProgress;
};

#endif // GAME_HPP
