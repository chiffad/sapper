import QtQuick 2.12
import QtQuick.Window 2.12
import board.model 1.0

Window
{
  visible: true
  visibility: Window.FullScreen
  title: qsTr("Hello World")

  ListView
  {
    id: view
    anchors.fill: parent
    model: BoardEntryModel {}
    delegate: Text
    {
      text: model.display
    }
  }
}
