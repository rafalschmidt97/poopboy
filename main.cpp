#include "Game.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
  qsrand(time(NULL));

  QApplication app(argc, argv);
  Game::getInstance()->show();

  return app.exec();
}
