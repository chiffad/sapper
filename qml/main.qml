import QtQuick 2.12
import QtQuick.Window 2.12

Window
{
  id: root_window
  visible: true
  visibility: Window.FullScreen
  title: qsTr("Hello World")

  Rectangle
  {
    id: background
    color: "dark grey"
    anchors.fill: parent
  }

  Column
  {
    id: elems
    anchors.fill: parent
    spacing: 2

    TopMenu
    {
      id: top_menu
      width: elems.width
      height: elems.height/10
    }

    Board
    {
      id: board
      height: elems.height - top_menu.height
      width: elems.width
    }

  }
}
