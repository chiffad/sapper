#include "logger.hpp"
#include "sapper.hpp"

#include <QGuiApplication>

namespace sapper
{

struct QGuiApplicationMy : public QGuiApplication
{
  Q_OBJECT

public:
  QGuiApplicationMy(int argc, char **argv) : QGuiApplication(argc, argv)
  {
    QObject::connect(this, SIGNAL(applicationStateChanged(Qt::ApplicationState)),
                     this, SLOT  (state_changed          (Qt::ApplicationState)));
  }

  Sapper game;

public slots:
  virtual void state_changed(Qt::ApplicationState state)
  {
    LOG_DBG<<"signal received!!!!";
    if(state != Qt::ApplicationActive) game.save_game();
  }
};

}//namepsace sapper
