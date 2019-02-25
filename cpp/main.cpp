#include "board_logic.hpp"
#include "sapper.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQuick/QQuickView>

#include <QDebug>

int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  sapper::Sapper game;
  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("GameWorld", &game);
  engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

  if(engine.rootObjects().isEmpty()) return -1;

  return app.exec();
}
