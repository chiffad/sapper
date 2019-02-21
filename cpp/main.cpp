#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "board_logic.hpp"

int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);


  sapper::board_logic_t b;
  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/res/main.qml")));
  if (engine.rootObjects().isEmpty())
      return -1;

  return app.exec();
}
