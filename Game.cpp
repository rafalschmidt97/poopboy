#include "Game.hpp"
#include <QFontDatabase>

Game *Game::instance = 0;

Game *Game::getInstance(){
  if (instance == 0)
    instance = new Game();

  return instance;
}

Character *Game::getCharacter() {
  return character;
}

int Game::getStoryProgress() {
  return storyProgress;
}

void Game::setStoryProgress(int newProgress) {
  storyProgress = newProgress;
}

FightScene *Game::getFightScene() {
  return fightScene;
}

StoryScene *Game::getStoryScene(){
  return storyScene;
}

TextScene *Game::getTextScene() {
  return textScene;
}

Game::Game(){
  QFontDatabase::addApplicationFont(":/resources/assets/fonts/upheavtt.ttf");
  storyProgress = 0;

  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setFixedSize(RESOLUTION_WIDTH, RESOLUTION_HEIGHT);

  character = new Character();
  storyScene = new StoryScene();
  fightScene = new FightScene();
  textScene = new TextScene();

  setScene(textScene);

  musicPlaylist = new QMediaPlaylist();
  musicPlaylist->addMedia(QUrl("qrc:/resources/assets/sounds/background.mp3"));
  musicPlaylist->setPlaybackMode(QMediaPlaylist::Loop);

  musicPlayer = new QMediaPlayer();
  musicPlayer->setPlaylist(musicPlaylist);
  musicPlayer->setVolume(50);
  musicPlayer->play();
}

Game::~Game() {
  musicPlayer->stop();
}
