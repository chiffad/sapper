#include "board_logic.hpp"
#include "qguiapplicationmy.hpp"

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQuick/QQuickView>


int main(int argc, char *argv[])
{
  sapper::QGuiApplicationMy app(argc, argv);

  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("GameWorld", &app.game);
  engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

  if(engine.rootObjects().isEmpty()) return -1;

  return app.exec();
}
